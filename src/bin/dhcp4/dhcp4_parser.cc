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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy"

#include <dhcp4/parser_context.h>

// Avoid warnings with the error counter.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#line 57 "dhcp4_parser.cc"


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 150 "dhcp4_parser.cc"

  /// Build a parser object.
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
#if PARSER4_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}

  Dhcp4Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  Dhcp4Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp4Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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

  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 315 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp4_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp4Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp4Parser::parse ()
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
#line 324 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 325 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 326 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 327 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 328 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 329 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 330 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 331 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 332 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 333 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 334 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 335 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 336 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 344 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 345 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 346 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 347 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 348 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 349 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 350 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 353 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 358 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 363 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 369 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 376 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 381 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 387 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 392 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 395 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 403 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 407 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 411 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 417 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 419 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 428 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 432 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 436 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 446 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 455 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 460 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1077 "dhcp4_parser.cc"
    break;

  case 61: // $@18: %empty
#line 470 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1092 "dhcp4_parser.cc"
    break;

  case 62: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 479 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 487 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 493 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 497 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 504 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 139: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 582 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 140: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 588 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 141: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 594 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 142: // renew_timer: "renew-timer" ":" "integer"
#line 600 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 143: // rebind_timer: "rebind-timer" ":" "integer"
#line 606 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 144: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 612 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 145: // t1_percent: "t1-percent" ":" "floating point"
#line 618 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 146: // t2_percent: "t2-percent" ":" "floating point"
#line 624 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 147: // cache_threshold: "cache-threshold" ":" "floating point"
#line 630 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 148: // cache_max_age: "cache-max-age" ":" "integer"
#line 636 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 149: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 642 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 150: // $@20: %empty
#line 648 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 151: // server_tag: "server-tag" $@20 ":" "constant string"
#line 651 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 152: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 657 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 663 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 154: // allocator: "allocator" $@21 ":" "constant string"
#line 666 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 155: // echo_client_id: "echo-client-id" ":" "boolean"
#line 672 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 156: // match_client_id: "match-client-id" ":" "boolean"
#line 678 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 157: // authoritative: "authoritative" ":" "boolean"
#line 684 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 158: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 690 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 696 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 160: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 702 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 708 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 711 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-present"
#line 717 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "never"
#line 720 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "always"
#line 723 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-not-present"
#line 726 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "boolean"
#line 729 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 168: // $@23: %empty
#line 735 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 169: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 738 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 170: // $@24: %empty
#line 744 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 171: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 747 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 172: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 753 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 173: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 762 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1476 "dhcp4_parser.cc"
    break;

  case 174: // $@25: %empty
#line 772 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 775 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 781 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 784 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 787 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 790 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 180: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 795 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 801 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 804 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 183: // $@27: %empty
#line 810 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 184: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 813 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 185: // store_extended_info: "store-extended-info" ":" "boolean"
#line 819 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 825 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 187: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 831 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 188: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 837 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 189: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 843 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 849 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 191: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 855 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 192: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 861 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 867 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 194: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 873 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 197: // interfaces_config_params: interfaces_config_params ","
#line 881 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1684 "dhcp4_parser.cc"
    break;

  case 208: // $@29: %empty
#line 898 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 209: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 902 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1703 "dhcp4_parser.cc"
    break;

  case 210: // $@30: %empty
#line 907 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1715 "dhcp4_parser.cc"
    break;

  case 211: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 913 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 212: // $@31: %empty
#line 918 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 213: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 921 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1742 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "raw"
#line 926 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp4_parser.cc"
    break;

  case 215: // socket_type: "udp"
#line 927 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp4_parser.cc"
    break;

  case 216: // $@32: %empty
#line 930 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 933 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "same-as-inbound"
#line 938 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 219: // outbound_interface_value: "use-routing"
#line 940 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1788 "dhcp4_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 944 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 950 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 956 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 962 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 224: // $@33: %empty
#line 968 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1840 "dhcp4_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 974 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 226: // $@34: %empty
#line 981 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1863 "dhcp4_parser.cc"
    break;

  case 227: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 987 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 230: // sanity_checks_params: sanity_checks_params ","
#line 994 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1880 "dhcp4_parser.cc"
    break;

  case 233: // $@35: %empty
#line 1003 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp4_parser.cc"
    break;

  case 234: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1006 "dhcp4_parser.yy"
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
#line 1909 "dhcp4_parser.cc"
    break;

  case 235: // $@36: %empty
#line 1022 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp4_parser.cc"
    break;

  case 236: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1025 "dhcp4_parser.yy"
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
#line 1937 "dhcp4_parser.cc"
    break;

  case 237: // $@37: %empty
#line 1040 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1949 "dhcp4_parser.cc"
    break;

  case 238: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1046 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 239: // $@38: %empty
#line 1053 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 240: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1059 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 245: // not_empty_database_list: not_empty_database_list ","
#line 1070 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1989 "dhcp4_parser.cc"
    break;

  case 246: // $@39: %empty
#line 1075 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 247: // database: "{" $@39 database_map_params "}"
#line 1079 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2009 "dhcp4_parser.cc"
    break;

  case 250: // database_map_params: database_map_params ","
#line 1087 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2017 "dhcp4_parser.cc"
    break;

  case 274: // $@40: %empty
#line 1117 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2026 "dhcp4_parser.cc"
    break;

  case 275: // database_type: "type" $@40 ":" "constant string"
#line 1120 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2036 "dhcp4_parser.cc"
    break;

  case 276: // $@41: %empty
#line 1126 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc"
    break;

  case 277: // user: "user" $@41 ":" "constant string"
#line 1129 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc"
    break;

  case 278: // $@42: %empty
#line 1135 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 279: // password: "password" $@42 ":" "constant string"
#line 1138 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 280: // $@43: %empty
#line 1144 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp4_parser.cc"
    break;

  case 281: // host: "host" $@43 ":" "constant string"
#line 1147 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2093 "dhcp4_parser.cc"
    break;

  case 282: // port: "port" ":" "integer"
#line 1153 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2103 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1159 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp4_parser.cc"
    break;

  case 284: // name: "name" $@44 ":" "constant string"
#line 1162 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2122 "dhcp4_parser.cc"
    break;

  case 285: // persist: "persist" ":" "boolean"
#line 1168 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 286: // lfc_interval: "lfc-interval" ":" "integer"
#line 1174 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 287: // readonly: "readonly" ":" "boolean"
#line 1180 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 288: // connect_timeout: "connect-timeout" ":" "integer"
#line 1186 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2162 "dhcp4_parser.cc"
    break;

  case 289: // read_timeout: "read-timeout" ":" "integer"
#line 1192 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 290: // write_timeout: "write-timeout" ":" "integer"
#line 1198 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 291: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1204 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 292: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1210 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 293: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1216 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1222 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 295: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1225 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 296: // on_fail_mode: "stop-retry-exit"
#line 1230 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2236 "dhcp4_parser.cc"
    break;

  case 297: // on_fail_mode: "serve-retry-exit"
#line 1231 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2242 "dhcp4_parser.cc"
    break;

  case 298: // on_fail_mode: "serve-retry-continue"
#line 1232 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2248 "dhcp4_parser.cc"
    break;

  case 299: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1235 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 300: // max_row_errors: "max-row-errors" ":" "integer"
#line 1241 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2268 "dhcp4_parser.cc"
    break;

  case 301: // $@46: %empty
#line 1247 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 302: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1250 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc"
    break;

  case 303: // $@47: %empty
#line 1256 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc"
    break;

  case 304: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1259 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2306 "dhcp4_parser.cc"
    break;

  case 305: // $@48: %empty
#line 1265 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp4_parser.cc"
    break;

  case 306: // key_file: "key-file" $@48 ":" "constant string"
#line 1268 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 307: // $@49: %empty
#line 1274 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc"
    break;

  case 308: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1277 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 309: // $@50: %empty
#line 1283 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2356 "dhcp4_parser.cc"
    break;

  case 310: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1289 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2365 "dhcp4_parser.cc"
    break;

  case 313: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1296 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2373 "dhcp4_parser.cc"
    break;

  case 319: // duid_id: "duid"
#line 1308 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2382 "dhcp4_parser.cc"
    break;

  case 320: // hw_address_id: "hw-address"
#line 1313 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2391 "dhcp4_parser.cc"
    break;

  case 321: // circuit_id: "circuit-id"
#line 1318 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2400 "dhcp4_parser.cc"
    break;

  case 322: // client_id: "client-id"
#line 1323 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2409 "dhcp4_parser.cc"
    break;

  case 323: // flex_id: "flex-id"
#line 1328 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1335 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 325: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1341 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2441 "dhcp4_parser.cc"
    break;

  case 328: // multi_threading_params: multi_threading_params ","
#line 1350 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2449 "dhcp4_parser.cc"
    break;

  case 335: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1363 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2459 "dhcp4_parser.cc"
    break;

  case 336: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1369 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 337: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1375 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2479 "dhcp4_parser.cc"
    break;

  case 338: // $@52: %empty
#line 1381 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 339: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1387 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 344: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1398 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2508 "dhcp4_parser.cc"
    break;

  case 345: // $@53: %empty
#line 1403 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 346: // hooks_library: "{" $@53 hooks_params "}"
#line 1407 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 347: // $@54: %empty
#line 1413 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 348: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1417 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 351: // hooks_params: hooks_params ","
#line 1425 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2556 "dhcp4_parser.cc"
    break;

  case 355: // $@55: %empty
#line 1435 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 356: // library: "library" $@55 ":" "constant string"
#line 1438 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 357: // $@56: %empty
#line 1444 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2584 "dhcp4_parser.cc"
    break;

  case 358: // parameters: "parameters" $@56 ":" map_value
#line 1447 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2593 "dhcp4_parser.cc"
    break;

  case 359: // $@57: %empty
#line 1453 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 360: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1459 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 363: // expired_leases_params: expired_leases_params ","
#line 1467 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2623 "dhcp4_parser.cc"
    break;

  case 370: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1480 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2633 "dhcp4_parser.cc"
    break;

  case 371: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1486 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 372: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1492 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 373: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1498 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 374: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1504 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 375: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1510 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 376: // $@58: %empty
#line 1519 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 377: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1525 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2704 "dhcp4_parser.cc"
    break;

  case 382: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1539 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2712 "dhcp4_parser.cc"
    break;

  case 383: // $@59: %empty
#line 1548 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 384: // subnet4: "{" $@59 subnet4_params "}"
#line 1552 "dhcp4_parser.yy"
                                {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 385: // $@60: %empty
#line 1574 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 386: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1578 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 389: // subnet4_params: subnet4_params ","
#line 1587 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2776 "dhcp4_parser.cc"
    break;

  case 439: // $@61: %empty
#line 1644 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 440: // subnet: "subnet" $@61 ":" "constant string"
#line 1647 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc"
    break;

  case 441: // $@62: %empty
#line 1653 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 442: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1656 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2814 "dhcp4_parser.cc"
    break;

  case 443: // $@63: %empty
#line 1662 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 444: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1665 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 445: // $@64: %empty
#line 1671 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 446: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1674 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 447: // $@65: %empty
#line 1680 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 448: // interface: "interface" $@65 ":" "constant string"
#line 1683 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 449: // $@66: %empty
#line 1689 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc"
    break;

  case 450: // client_class: "client-class" $@66 ":" "constant string"
#line 1692 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 451: // $@67: %empty
#line 1699 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp4_parser.cc"
    break;

  case 452: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1705 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2911 "dhcp4_parser.cc"
    break;

  case 453: // $@68: %empty
#line 1710 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 454: // evaluate_additional_classes: "evaluate-additional-classes" $@68 ":" list_strings
#line 1716 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 455: // reservations_global: "reservations-global" ":" "boolean"
#line 1721 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 456: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1727 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 457: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1733 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 458: // id: "id" ":" "integer"
#line 1739 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2972 "dhcp4_parser.cc"
    break;

  case 459: // $@69: %empty
#line 1747 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2984 "dhcp4_parser.cc"
    break;

  case 460: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1753 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 465: // shared_networks_list: shared_networks_list ","
#line 1766 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3001 "dhcp4_parser.cc"
    break;

  case 466: // $@70: %empty
#line 1771 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 467: // shared_network: "{" $@70 shared_network_params "}"
#line 1775 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3019 "dhcp4_parser.cc"
    break;

  case 470: // shared_network_params: shared_network_params ","
#line 1781 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3027 "dhcp4_parser.cc"
    break;

  case 515: // $@71: %empty
#line 1836 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3039 "dhcp4_parser.cc"
    break;

  case 516: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1842 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc"
    break;

  case 517: // $@72: %empty
#line 1850 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 518: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1853 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3065 "dhcp4_parser.cc"
    break;

  case 523: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1865 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3073 "dhcp4_parser.cc"
    break;

  case 524: // $@73: %empty
#line 1872 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3083 "dhcp4_parser.cc"
    break;

  case 525: // option_def_entry: "{" $@73 option_def_params "}"
#line 1876 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3095 "dhcp4_parser.cc"
    break;

  case 526: // $@74: %empty
#line 1887 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3105 "dhcp4_parser.cc"
    break;

  case 527: // sub_option_def: "{" $@74 option_def_params "}"
#line 1891 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3117 "dhcp4_parser.cc"
    break;

  case 532: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1907 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3125 "dhcp4_parser.cc"
    break;

  case 544: // code: "code" ":" "integer"
#line 1926 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3135 "dhcp4_parser.cc"
    break;

  case 546: // $@75: %empty
#line 1934 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp4_parser.cc"
    break;

  case 547: // option_def_type: "type" $@75 ":" "constant string"
#line 1937 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3154 "dhcp4_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1943 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp4_parser.cc"
    break;

  case 549: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1946 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1952 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 551: // space: "space" $@77 ":" "constant string"
#line 1955 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3192 "dhcp4_parser.cc"
    break;

  case 553: // $@78: %empty
#line 1963 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp4_parser.cc"
    break;

  case 554: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1966 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 555: // option_def_array: "array" ":" "boolean"
#line 1972 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3221 "dhcp4_parser.cc"
    break;

  case 556: // $@79: %empty
#line 1982 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 557: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1988 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp4_parser.cc"
    break;

  case 562: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2003 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3250 "dhcp4_parser.cc"
    break;

  case 563: // $@80: %empty
#line 2010 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3260 "dhcp4_parser.cc"
    break;

  case 564: // option_data_entry: "{" $@80 option_data_params "}"
#line 2014 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3269 "dhcp4_parser.cc"
    break;

  case 565: // $@81: %empty
#line 2022 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp4_parser.cc"
    break;

  case 566: // sub_option_data: "{" $@81 option_data_params "}"
#line 2026 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3288 "dhcp4_parser.cc"
    break;

  case 571: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2042 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3296 "dhcp4_parser.cc"
    break;

  case 584: // $@82: %empty
#line 2064 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp4_parser.cc"
    break;

  case 585: // option_data_data: "data" $@82 ":" "constant string"
#line 2067 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3315 "dhcp4_parser.cc"
    break;

  case 588: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2077 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3325 "dhcp4_parser.cc"
    break;

  case 589: // option_data_always_send: "always-send" ":" "boolean"
#line 2083 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3335 "dhcp4_parser.cc"
    break;

  case 590: // option_data_never_send: "never-send" ":" "boolean"
#line 2089 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3345 "dhcp4_parser.cc"
    break;

  case 591: // $@83: %empty
#line 2095 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp4_parser.cc"
    break;

  case 592: // option_data_client_classes: "client-classes" $@83 ":" list_strings
#line 2101 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 593: // $@84: %empty
#line 2109 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3378 "dhcp4_parser.cc"
    break;

  case 594: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2115 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3387 "dhcp4_parser.cc"
    break;

  case 599: // not_empty_pools_list: not_empty_pools_list ","
#line 2128 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3395 "dhcp4_parser.cc"
    break;

  case 600: // $@85: %empty
#line 2133 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3405 "dhcp4_parser.cc"
    break;

  case 601: // pool_list_entry: "{" $@85 pool_params "}"
#line 2137 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 602: // $@86: %empty
#line 2143 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3425 "dhcp4_parser.cc"
    break;

  case 603: // sub_pool4: "{" $@86 pool_params "}"
#line 2147 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 606: // pool_params: pool_params ","
#line 2155 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3443 "dhcp4_parser.cc"
    break;

  case 616: // $@87: %empty
#line 2171 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 617: // pool_entry: "pool" $@87 ":" "constant string"
#line 2174 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 618: // pool_id: "pool-id" ":" "integer"
#line 2180 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 619: // $@88: %empty
#line 2186 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3480 "dhcp4_parser.cc"
    break;

  case 620: // user_context: "user-context" $@88 ":" map_value
#line 2188 "dhcp4_parser.yy"
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
#line 3507 "dhcp4_parser.cc"
    break;

  case 621: // $@89: %empty
#line 2211 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 622: // comment: "comment" $@89 ":" "constant string"
#line 2213 "dhcp4_parser.yy"
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
#line 3544 "dhcp4_parser.cc"
    break;

  case 623: // $@90: %empty
#line 2241 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 624: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2247 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 629: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2258 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3573 "dhcp4_parser.cc"
    break;

  case 630: // $@91: %empty
#line 2263 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 631: // reservation: "{" $@91 reservation_params "}"
#line 2267 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 632: // $@92: %empty
#line 2272 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 633: // sub_reservation: "{" $@92 reservation_params "}"
#line 2276 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 638: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2287 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3619 "dhcp4_parser.cc"
    break;

  case 654: // $@93: %empty
#line 2310 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3628 "dhcp4_parser.cc"
    break;

  case 655: // next_server: "next-server" $@93 ":" "constant string"
#line 2313 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3638 "dhcp4_parser.cc"
    break;

  case 656: // $@94: %empty
#line 2319 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp4_parser.cc"
    break;

  case 657: // server_hostname: "server-hostname" $@94 ":" "constant string"
#line 2322 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3657 "dhcp4_parser.cc"
    break;

  case 658: // $@95: %empty
#line 2328 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3666 "dhcp4_parser.cc"
    break;

  case 659: // boot_file_name: "boot-file-name" $@95 ":" "constant string"
#line 2331 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3676 "dhcp4_parser.cc"
    break;

  case 660: // $@96: %empty
#line 2337 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3685 "dhcp4_parser.cc"
    break;

  case 661: // ip_address: "ip-address" $@96 ":" "constant string"
#line 2340 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3695 "dhcp4_parser.cc"
    break;

  case 662: // $@97: %empty
#line 2346 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3704 "dhcp4_parser.cc"
    break;

  case 663: // duid: "duid" $@97 ":" "constant string"
#line 2349 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 664: // $@98: %empty
#line 2355 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 665: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2358 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 666: // $@99: %empty
#line 2364 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 667: // client_id_value: "client-id" $@99 ":" "constant string"
#line 2367 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3752 "dhcp4_parser.cc"
    break;

  case 668: // $@100: %empty
#line 2373 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 669: // circuit_id_value: "circuit-id" $@100 ":" "constant string"
#line 2376 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 670: // $@101: %empty
#line 2382 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 671: // flex_id_value: "flex-id" $@101 ":" "constant string"
#line 2385 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 672: // $@102: %empty
#line 2391 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 673: // hostname: "hostname" $@102 ":" "constant string"
#line 2394 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 674: // $@103: %empty
#line 2400 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 675: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2406 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 676: // $@104: %empty
#line 2414 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 677: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2420 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3851 "dhcp4_parser.cc"
    break;

  case 679: // $@105: %empty
#line 2428 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 680: // ip_addresses: "ip-addresses" $@105 ":" list_strings
#line 2434 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 681: // $@106: %empty
#line 2442 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 682: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2448 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 685: // client_classes_list: client_classes_list ","
#line 2455 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3901 "dhcp4_parser.cc"
    break;

  case 686: // $@107: %empty
#line 2460 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3911 "dhcp4_parser.cc"
    break;

  case 687: // client_class_entry: "{" $@107 client_class_params "}"
#line 2464 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3921 "dhcp4_parser.cc"
    break;

  case 692: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2476 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3929 "dhcp4_parser.cc"
    break;

  case 711: // $@108: %empty
#line 2502 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 712: // client_class_test: "test" $@108 ":" "constant string"
#line 2505 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3948 "dhcp4_parser.cc"
    break;

  case 713: // $@109: %empty
#line 2511 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3957 "dhcp4_parser.cc"
    break;

  case 714: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2514 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 715: // only_if_required: "only-if-required" ":" "boolean"
#line 2521 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 716: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2527 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 3987 "dhcp4_parser.cc"
    break;

  case 717: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2535 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3997 "dhcp4_parser.cc"
    break;

  case 718: // $@110: %empty
#line 2543 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4010 "dhcp4_parser.cc"
    break;

  case 719: // control_socket: "control-socket" $@110 ":" "{" control_socket_params "}"
#line 2550 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4019 "dhcp4_parser.cc"
    break;

  case 720: // $@111: %empty
#line 2555 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 721: // control_sockets: "control-sockets" $@111 ":" "[" control_socket_list "]"
#line 2562 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 726: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2573 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4049 "dhcp4_parser.cc"
    break;

  case 727: // $@112: %empty
#line 2578 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4059 "dhcp4_parser.cc"
    break;

  case 728: // control_socket_entry: "{" $@112 control_socket_params "}"
#line 2582 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4067 "dhcp4_parser.cc"
    break;

  case 731: // control_socket_params: control_socket_params ","
#line 2588 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4075 "dhcp4_parser.cc"
    break;

  case 744: // $@113: %empty
#line 2607 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 745: // control_socket_type: "socket-type" $@113 ":" control_socket_type_value
#line 2610 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4093 "dhcp4_parser.cc"
    break;

  case 746: // control_socket_type_value: "unix"
#line 2616 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4099 "dhcp4_parser.cc"
    break;

  case 747: // control_socket_type_value: "http"
#line 2617 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4105 "dhcp4_parser.cc"
    break;

  case 748: // control_socket_type_value: "https"
#line 2618 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4111 "dhcp4_parser.cc"
    break;

  case 749: // $@114: %empty
#line 2621 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 750: // control_socket_name: "socket-name" $@114 ":" "constant string"
#line 2625 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 751: // $@115: %empty
#line 2631 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 752: // control_socket_address: "socket-address" $@115 ":" "constant string"
#line 2635 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 753: // control_socket_port: "socket-port" ":" "integer"
#line 2641 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 754: // cert_required: "cert-required" ":" "boolean"
#line 2647 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 755: // $@116: %empty
#line 2655 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4183 "dhcp4_parser.cc"
    break;

  case 756: // authentication: "authentication" $@116 ":" "{" auth_params "}"
#line 2661 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4194 "dhcp4_parser.cc"
    break;

  case 759: // auth_params: auth_params ","
#line 2670 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4202 "dhcp4_parser.cc"
    break;

  case 767: // $@117: %empty
#line 2684 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4211 "dhcp4_parser.cc"
    break;

  case 768: // auth_type: "type" $@117 ":" auth_type_value
#line 2687 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4220 "dhcp4_parser.cc"
    break;

  case 769: // auth_type_value: "basic"
#line 2692 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4226 "dhcp4_parser.cc"
    break;

  case 770: // $@118: %empty
#line 2695 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4235 "dhcp4_parser.cc"
    break;

  case 771: // realm: "realm" $@118 ":" "constant string"
#line 2698 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4245 "dhcp4_parser.cc"
    break;

  case 772: // $@119: %empty
#line 2704 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4254 "dhcp4_parser.cc"
    break;

  case 773: // directory: "directory" $@119 ":" "constant string"
#line 2707 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4264 "dhcp4_parser.cc"
    break;

  case 774: // $@120: %empty
#line 2713 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4276 "dhcp4_parser.cc"
    break;

  case 775: // clients: "clients" $@120 ":" "[" clients_list "]"
#line 2719 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4285 "dhcp4_parser.cc"
    break;

  case 780: // not_empty_clients_list: not_empty_clients_list ","
#line 2730 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4293 "dhcp4_parser.cc"
    break;

  case 781: // $@121: %empty
#line 2735 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 782: // basic_auth: "{" $@121 clients_params "}"
#line 2739 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4311 "dhcp4_parser.cc"
    break;

  case 785: // clients_params: clients_params ","
#line 2745 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4319 "dhcp4_parser.cc"
    break;

  case 793: // $@122: %empty
#line 2759 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4328 "dhcp4_parser.cc"
    break;

  case 794: // user_file: "user-file" $@122 ":" "constant string"
#line 2762 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 795: // $@123: %empty
#line 2768 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4347 "dhcp4_parser.cc"
    break;

  case 796: // password_file: "password-file" $@123 ":" "constant string"
#line 2771 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4357 "dhcp4_parser.cc"
    break;

  case 797: // $@124: %empty
#line 2779 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4369 "dhcp4_parser.cc"
    break;

  case 798: // dhcp_queue_control: "dhcp-queue-control" $@124 ":" "{" queue_control_params "}"
#line 2785 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4380 "dhcp4_parser.cc"
    break;

  case 801: // queue_control_params: queue_control_params ","
#line 2794 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4388 "dhcp4_parser.cc"
    break;

  case 808: // enable_queue: "enable-queue" ":" "boolean"
#line 2807 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 809: // $@125: %empty
#line 2813 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4407 "dhcp4_parser.cc"
    break;

  case 810: // queue_type: "queue-type" $@125 ":" "constant string"
#line 2816 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4417 "dhcp4_parser.cc"
    break;

  case 811: // capacity: "capacity" ":" "integer"
#line 2822 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4427 "dhcp4_parser.cc"
    break;

  case 812: // $@126: %empty
#line 2828 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 813: // arbitrary_map_entry: "constant string" $@126 ":" value
#line 2831 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4445 "dhcp4_parser.cc"
    break;

  case 814: // $@127: %empty
#line 2838 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4457 "dhcp4_parser.cc"
    break;

  case 815: // dhcp_ddns: "dhcp-ddns" $@127 ":" "{" dhcp_ddns_params "}"
#line 2844 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4468 "dhcp4_parser.cc"
    break;

  case 816: // $@128: %empty
#line 2851 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4478 "dhcp4_parser.cc"
    break;

  case 817: // sub_dhcp_ddns: "{" $@128 dhcp_ddns_params "}"
#line 2855 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4488 "dhcp4_parser.cc"
    break;

  case 820: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2863 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4496 "dhcp4_parser.cc"
    break;

  case 832: // enable_updates: "enable-updates" ":" "boolean"
#line 2881 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4506 "dhcp4_parser.cc"
    break;

  case 833: // $@129: %empty
#line 2887 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4515 "dhcp4_parser.cc"
    break;

  case 834: // server_ip: "server-ip" $@129 ":" "constant string"
#line 2890 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4525 "dhcp4_parser.cc"
    break;

  case 835: // server_port: "server-port" ":" "integer"
#line 2896 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4535 "dhcp4_parser.cc"
    break;

  case 836: // $@130: %empty
#line 2902 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4544 "dhcp4_parser.cc"
    break;

  case 837: // sender_ip: "sender-ip" $@130 ":" "constant string"
#line 2905 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4554 "dhcp4_parser.cc"
    break;

  case 838: // sender_port: "sender-port" ":" "integer"
#line 2911 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4564 "dhcp4_parser.cc"
    break;

  case 839: // max_queue_size: "max-queue-size" ":" "integer"
#line 2917 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4574 "dhcp4_parser.cc"
    break;

  case 840: // $@131: %empty
#line 2923 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4583 "dhcp4_parser.cc"
    break;

  case 841: // ncr_protocol: "ncr-protocol" $@131 ":" ncr_protocol_value
#line 2926 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4592 "dhcp4_parser.cc"
    break;

  case 842: // ncr_protocol_value: "udp"
#line 2932 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4598 "dhcp4_parser.cc"
    break;

  case 843: // ncr_protocol_value: "tcp"
#line 2933 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4604 "dhcp4_parser.cc"
    break;

  case 844: // $@132: %empty
#line 2936 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4613 "dhcp4_parser.cc"
    break;

  case 845: // ncr_format: "ncr-format" $@132 ":" "JSON"
#line 2939 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4623 "dhcp4_parser.cc"
    break;

  case 846: // $@133: %empty
#line 2947 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4635 "dhcp4_parser.cc"
    break;

  case 847: // config_control: "config-control" $@133 ":" "{" config_control_params "}"
#line 2953 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4645 "dhcp4_parser.cc"
    break;

  case 848: // $@134: %empty
#line 2959 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4655 "dhcp4_parser.cc"
    break;

  case 849: // sub_config_control: "{" $@134 config_control_params "}"
#line 2963 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4664 "dhcp4_parser.cc"
    break;

  case 852: // config_control_params: config_control_params ","
#line 2971 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4672 "dhcp4_parser.cc"
    break;

  case 855: // $@135: %empty
#line 2981 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4684 "dhcp4_parser.cc"
    break;

  case 856: // config_databases: "config-databases" $@135 ":" "[" database_list "]"
#line 2987 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4693 "dhcp4_parser.cc"
    break;

  case 857: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2992 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4703 "dhcp4_parser.cc"
    break;

  case 858: // $@136: %empty
#line 3000 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4715 "dhcp4_parser.cc"
    break;

  case 859: // loggers: "loggers" $@136 ":" "[" loggers_entries "]"
#line 3006 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4724 "dhcp4_parser.cc"
    break;

  case 862: // loggers_entries: loggers_entries ","
#line 3015 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4732 "dhcp4_parser.cc"
    break;

  case 863: // $@137: %empty
#line 3021 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4742 "dhcp4_parser.cc"
    break;

  case 864: // logger_entry: "{" $@137 logger_params "}"
#line 3025 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4750 "dhcp4_parser.cc"
    break;

  case 867: // logger_params: logger_params ","
#line 3031 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4758 "dhcp4_parser.cc"
    break;

  case 875: // debuglevel: "debuglevel" ":" "integer"
#line 3045 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4768 "dhcp4_parser.cc"
    break;

  case 876: // $@138: %empty
#line 3051 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 877: // severity: "severity" $@138 ":" "constant string"
#line 3054 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4787 "dhcp4_parser.cc"
    break;

  case 878: // $@139: %empty
#line 3060 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4799 "dhcp4_parser.cc"
    break;

  case 879: // output_options_list: "output-options" $@139 ":" "[" output_options_list_content "]"
#line 3066 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4808 "dhcp4_parser.cc"
    break;

  case 882: // output_options_list_content: output_options_list_content ","
#line 3073 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4816 "dhcp4_parser.cc"
    break;

  case 883: // $@140: %empty
#line 3078 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4826 "dhcp4_parser.cc"
    break;

  case 884: // output_entry: "{" $@140 output_params_list "}"
#line 3082 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4834 "dhcp4_parser.cc"
    break;

  case 887: // output_params_list: output_params_list ","
#line 3088 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4842 "dhcp4_parser.cc"
    break;

  case 893: // $@141: %empty
#line 3100 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4851 "dhcp4_parser.cc"
    break;

  case 894: // output: "output" $@141 ":" "constant string"
#line 3103 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4861 "dhcp4_parser.cc"
    break;

  case 895: // flush: "flush" ":" "boolean"
#line 3109 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4871 "dhcp4_parser.cc"
    break;

  case 896: // maxsize: "maxsize" ":" "integer"
#line 3115 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4881 "dhcp4_parser.cc"
    break;

  case 897: // maxver: "maxver" ":" "integer"
#line 3121 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4891 "dhcp4_parser.cc"
    break;

  case 898: // $@142: %empty
#line 3127 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4900 "dhcp4_parser.cc"
    break;

  case 899: // pattern: "pattern" $@142 ":" "constant string"
#line 3130 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4910 "dhcp4_parser.cc"
    break;

  case 900: // $@143: %empty
#line 3136 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4922 "dhcp4_parser.cc"
    break;

  case 901: // compatibility: "compatibility" $@143 ":" "{" compatibility_params "}"
#line 3142 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4931 "dhcp4_parser.cc"
    break;

  case 904: // compatibility_params: compatibility_params ","
#line 3149 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4939 "dhcp4_parser.cc"
    break;

  case 910: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3161 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4949 "dhcp4_parser.cc"
    break;

  case 911: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3167 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4959 "dhcp4_parser.cc"
    break;

  case 912: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3173 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4969 "dhcp4_parser.cc"
    break;

  case 913: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3179 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4979 "dhcp4_parser.cc"
    break;


#line 4983 "dhcp4_parser.cc"

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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Dhcp4Parser::context.
  Dhcp4Parser::context::context (const Dhcp4Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Dhcp4Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  Dhcp4Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  Dhcp4Parser::yysyntax_error_ (const context& yyctx) const
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


  const short Dhcp4Parser::yypact_ninf_ = -1330;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     454, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330,    74,    28,    79,    91,   123,   151,
     161,   163,   165,   189,   191,   196,   215,   244, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330,    28,  -156,    81,   688,    33,   159,
     -21,   167,   169,   219,   241,   -99,   455,    41, -1330,   138,
     105,   170,   287,   293, -1330,   103, -1330, -1330, -1330, -1330,
     294,   308,   310, -1330, -1330, -1330,   321,   323, -1330, -1330,
   -1330,   324,   338,   344,   353,   356,   371,   385,   389,   405,
     406,   407, -1330,   421,   435,   445,   451,   456, -1330, -1330,
   -1330,   457,   458,   461,   463, -1330, -1330, -1330,   464, -1330,
   -1330, -1330, -1330, -1330,   465,   467,   469, -1330, -1330, -1330,
   -1330, -1330,   471, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     475,   476,   478, -1330, -1330,   479, -1330,   109, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     481,   482,   483,   484, -1330,   119, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330,   485, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330,   137, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   486,
   -1330, -1330, -1330, -1330, -1330,   147, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330,   350,   384, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330,   366, -1330, -1330,
     489, -1330, -1330, -1330,   490, -1330, -1330,   491,   440, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330,   497,   499,   501, -1330, -1330, -1330, -1330, -1330,
     503,   504, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330,   157, -1330, -1330, -1330,
     508, -1330,   510, -1330,   511,   512, -1330, -1330, -1330, -1330,
   -1330,   158, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330,   513,   194, -1330, -1330, -1330, -1330,    28,    28,
   -1330,   295,   515, -1330, -1330,   517,   520,   521,   298,   300,
     301,   526,   527,   528,   307,   306,   531,   533,   535,   315,
     317,   318,   319,   320,   322,   326,   327,   329,   332,   333,
     543,   334,   335,   336,   337,   343,   545,   559,   562,   346,
     348,   355,   352,   577,   579,   580,   360,   583,   585,   589,
     590,   593,   372,   373,   374,   595,   600,   601,   603,   608,
     391,   614,   615,   616,   621,   623,   624,   625,   402,   404,
     414,   629,   639, -1330,   688, -1330,   640,   642,   644,   422,
     423,   427,   428,    33, -1330,   645,   651,   652,   653,   654,
     655,   434,   657,   658,   659,   660,   159, -1330,   675,   459,
     -21, -1330,   677,   680,   683,   684,   685,   687,   689,   690,
   -1330,   167, -1330,   691,   692,   466,   693,   694,   701,   480,
   -1330,   219,   702,   487,   488,   500,   703, -1330,   241,   705,
     706,   -55, -1330,   502,   708,   505,   709,   506,   507,   725,
     730,   455, -1330,   731,   514,    41, -1330, -1330, -1330,   732,
     734,   735,   736,   737, -1330, -1330, -1330,   523,   552,   553,
   -1330, -1330,   738,   744,   733, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330,   554, -1330, -1330, -1330,
   -1330, -1330,  -114,   557,   558, -1330, -1330, -1330, -1330,   779,
     780,   781, -1330,   563,   160,   782,   783,   564, -1330, -1330,
   -1330,   786,   790,   791,   792,   793, -1330,   794,   797,   800,
     799,   805,   573,   588, -1330, -1330, -1330,   809,   808, -1330,
     811,   102,   122, -1330, -1330, -1330, -1330, -1330,   592,   594,
     596,   813,   597,   598, -1330,   811,   811,   599,   818, -1330,
     602, -1330, -1330,   811,   604,   606,   607,   609,   610,   611,
     612, -1330,   613,   617, -1330,   618,   619,   622, -1330, -1330,
     626, -1330, -1330, -1330,   811, -1330,   627,   783, -1330, -1330,
     628, -1330,   630, -1330, -1330,    18,   549, -1330,   821, -1330,
   -1330,    28,   688,    41,    33,   208, -1330, -1330, -1330,   354,
     354,   832, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330,   841,   842,   843, -1330, -1330, -1330, -1330, -1330, -1330,
     847, -1330, -1330, -1330,    73,   849,   850,   851,    29,   195,
      22,   852,   -52,   455, -1330, -1330,   853,     9, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   854,
   -1330, -1330, -1330, -1330, -1330,   722, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     832, -1330,   203,   213,   254, -1330, -1330,   351, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330,   824,   860,   861,   863,   864,
     865,   866,   867,   868,   869, -1330,   870,   871, -1330, -1330,
   -1330, -1330, -1330,   368, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330,   369, -1330,   872,
     873, -1330, -1330,   874,   876, -1330, -1330,   881,   885, -1330,
   -1330,   883,   887, -1330, -1330,   886,   888, -1330, -1330, -1330,
   -1330, -1330, -1330,    40, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330,    44, -1330, -1330,   890,   891, -1330, -1330,   892,   894,
   -1330,   889,   895,   896,   897,   898,   899,   370, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330,   900,   901,   902, -1330,   380,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   903,
   -1330,   904, -1330, -1330, -1330, -1330, -1330, -1330,   382, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330,   905,   906, -1330,
     908, -1330,   910, -1330, -1330, -1330,   383, -1330, -1330, -1330,
   -1330, -1330,   416, -1330,   126, -1330,   911,   912,   913,   914,
   -1330,   418, -1330, -1330, -1330, -1330, -1330,   695, -1330,   915,
     907, -1330, -1330,   916, -1330,   917, -1330, -1330, -1330,   918,
     921,   208, -1330,   922,   923,   924,   925,   704,   649,   707,
     710,   711,   713,   714,   715,   716,   717,   927,   718,   719,
     928,   930,   931,   932,   354, -1330, -1330,   354, -1330,   832,
     159, -1330,   841,   219, -1330,   842,   241, -1330,   843,  1341,
   -1330,   847,    73, -1330,   253,   849, -1330,   167, -1330,   850,
     -99, -1330,   851,   721,   723,   724,   726,   728,   729,    29,
   -1330,   720,   739,   743,   195, -1330,   940,   947,   953,   750,
     954,   751,    22, -1330,    22, -1330,   852,   754,   956,   757,
     957,   -52, -1330, -1330,   229,   853, -1330,   758,   765,   766,
     768,     9, -1330, -1330,   992,  1000,   -21, -1330,   854,  1004,
   -1330, -1330,   784,   785, -1330,   802,   803,   807,   810, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   127,
   -1330, -1330,   815,   816,   817,   823, -1330,   424, -1330,   426,
   -1330,  1010, -1330,  1016, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330,   430, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330,  1029,  1034, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
    1035,  1046, -1330, -1330, -1330, -1330, -1330, -1330, -1330,  1044,
   -1330,   432, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330,    53,   829,   833, -1330,  1050, -1330,
   -1330,   433, -1330, -1330,   837, -1330,    28, -1330, -1330,  1060,
   -1330, -1330, -1330, -1330, -1330,   439, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330,   862,   442, -1330,
     811, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,  1341,
   -1330,  1070,  1073,   909,   919, -1330,   253, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330,   193, -1330, -1330, -1330,  1119,
     920,  1121,   229, -1330, -1330, -1330, -1330, -1330,   926,   929,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     448, -1330, -1330, -1330, -1330, -1330,  1123, -1330,   933, -1330,
   -1330, -1330,  1122,  1127,  1128,  1129,   193, -1330,  1131, -1330,
     572,   934,   935,  1130, -1330, -1330,   291, -1330, -1330, -1330,
   -1330, -1330,  1132,  -104,  1131, -1330, -1330,  1134,  1133, -1330,
   -1330,  1137,  1138,  1139, -1330,   449, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330,   251, -1330,  1132,  1140,   936,   937,   939,
    1141,  -104, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     450, -1330, -1330, -1330, -1330,   941, -1330, -1330, -1330,   943,
   -1330,  1144,  1145,   251, -1330, -1330, -1330,   944,   945, -1330,
   -1330, -1330
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   208,     9,   385,    11,   602,    13,
     632,    15,   517,    17,   526,    19,   565,    21,   347,    23,
     816,    25,   848,    27,    46,    39,     0,     0,     0,     0,
       0,   634,     0,   528,   567,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   846,   193,   226,
       0,     0,     0,   654,   656,   658,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   376,   515,   556,     0,   153,
     174,   459,   619,   621,     0,     0,     0,   309,   681,   623,
     338,   359,     0,   324,   718,   720,   797,   814,   181,   183,
       0,     0,     0,   858,   900,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     104,   134,   135,    93,    94,    95,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   101,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,    77,
      84,    85,    99,   100,   102,    96,    97,    98,    83,    88,
      89,    90,    91,    92,   103,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   441,   443,   445,   593,
     439,   447,     0,   451,   453,   449,   676,   438,   390,   391,
     392,   393,   394,   418,   419,   420,   421,   422,   436,   408,
     409,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   437,     0,   387,   397,   413,   414,
     415,   398,   400,   401,   402,   404,   405,   406,   399,   395,
     396,   416,   417,   403,   410,   411,   412,   407,   616,     0,
     615,   610,   611,   612,   609,     0,   604,   607,   608,   613,
     614,   674,   660,   662,   664,   668,   666,   672,   670,   653,
     647,   651,   652,     0,   635,   636,   648,   649,   650,   644,
     639,   645,   641,   642,   643,   646,   640,     0,   546,   283,
       0,   550,   548,   553,     0,   542,   543,     0,   529,   530,
     533,   545,   534,   535,   536,   552,   537,   538,   539,   540,
     541,   584,     0,     0,     0,   591,   582,   583,   586,   587,
       0,   568,   569,   572,   573,   574,   575,   576,   577,   578,
     581,   579,   580,   355,   357,   352,     0,   349,   353,   354,
       0,   833,     0,   836,     0,     0,   840,   844,   831,   829,
     830,     0,   818,   821,   822,   823,   824,   825,   826,   827,
     828,   855,     0,     0,   850,   853,   854,    45,    50,     0,
      37,    43,     0,    64,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    69,    66,     0,     0,     0,     0,
       0,     0,     0,   197,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   389,   386,     0,     0,
     606,   603,     0,     0,     0,     0,     0,     0,     0,     0,
     633,   638,   518,     0,     0,     0,     0,     0,     0,     0,
     527,   532,     0,     0,     0,     0,     0,   566,   571,     0,
       0,   351,   348,     0,     0,     0,     0,     0,     0,     0,
       0,   820,   817,     0,     0,   852,   849,    49,    41,     0,
       0,     0,     0,     0,   155,   156,   157,     0,     0,     0,
     191,   192,     0,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,     0,   186,   187,   158,
     159,   160,     0,     0,     0,   172,   173,   180,   185,     0,
       0,     0,   152,     0,     0,     0,     0,     0,   455,   456,
     457,     0,     0,     0,     0,     0,   717,     0,     0,     0,
       0,     0,     0,     0,   188,   189,   190,     0,     0,    68,
       0,     0,     0,   220,   221,   222,   223,   196,     0,     0,
       0,     0,     0,     0,   458,     0,     0,     0,     0,   388,
       0,   618,   605,     0,     0,     0,     0,     0,     0,     0,
       0,   637,     0,     0,   544,     0,     0,     0,   555,   531,
       0,   588,   589,   590,     0,   570,     0,     0,   350,   832,
       0,   835,     0,   838,   839,     0,     0,   819,     0,   857,
     851,     0,     0,     0,     0,     0,   655,   657,   659,     0,
       0,   241,   151,   163,   164,   165,   166,   167,   162,   169,
     171,   378,   519,   558,   154,   176,   177,   178,   179,   175,
     461,    38,   620,   622,     0,     0,   625,   340,     0,     0,
       0,   722,     0,     0,   182,   184,     0,     0,    51,   211,
     214,   215,   213,   218,   219,   217,   442,   444,   446,   595,
     440,   448,   452,   454,   450,     0,   617,   675,   661,   663,
     665,   669,   667,   673,   671,   547,   284,   551,   549,   554,
     585,   592,   356,   358,   834,   837,   842,   843,   841,   845,
     241,    42,     0,     0,     0,   233,   235,     0,   228,   231,
     232,   274,   276,   278,   280,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   294,     0,     0,   301,   303,
     305,   307,   273,     0,   248,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,     0,   246,     0,
     242,   243,   383,     0,   379,   380,   524,     0,   520,   521,
     563,     0,   559,   560,   466,     0,   462,   463,   319,   320,
     321,   322,   323,     0,   311,   314,   315,   316,   317,   318,
     686,     0,   683,   630,     0,   626,   627,   345,     0,   341,
     342,     0,     0,     0,     0,     0,     0,     0,   361,   364,
     365,   366,   367,   368,   369,     0,     0,     0,   334,     0,
     326,   329,   330,   331,   332,   333,   744,   749,   751,     0,
     755,     0,   743,   737,   738,   739,   741,   742,     0,   729,
     732,   733,   734,   735,   740,   736,   727,     0,   723,   724,
       0,   809,     0,   812,   805,   806,     0,   799,   802,   803,
     804,   807,     0,   863,     0,   860,     0,     0,     0,     0,
     909,     0,   902,   905,   906,   907,   908,    53,   600,     0,
     596,   597,   679,     0,   678,     0,    62,   847,   194,     0,
       0,   230,   227,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   250,   225,   238,     0,   240,   245,
       0,   377,   382,   528,   516,   523,   567,   557,   562,     0,
     460,   465,   313,   310,   688,   685,   682,   634,   624,   629,
       0,   339,   344,     0,     0,     0,     0,     0,     0,   363,
     360,     0,     0,     0,   328,   325,     0,     0,     0,     0,
       0,     0,   731,   719,     0,   721,   726,     0,     0,     0,
       0,   801,   798,   815,     0,   862,   859,     0,     0,     0,
       0,   904,   901,    55,     0,    54,     0,   594,   599,     0,
     677,   856,     0,     0,   229,     0,     0,     0,     0,   282,
     285,   286,   287,   288,   289,   290,   291,   292,   293,     0,
     299,   300,     0,     0,     0,     0,   249,     0,   244,     0,
     381,     0,   522,     0,   561,   514,   489,   490,   491,   474,
     475,   494,   495,   496,   497,   498,   512,   477,   478,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   513,   471,   472,   473,   486,   487,   488,   483,
     484,   485,     0,   468,   476,   492,   493,   479,   480,   481,
     482,   464,   312,   711,   713,     0,     0,   705,   706,   707,
     708,   709,   710,   698,   699,   703,   704,   700,   701,   702,
       0,   689,   690,   693,   694,   695,   696,   697,   684,     0,
     628,     0,   343,   370,   371,   372,   373,   374,   375,   362,
     335,   336,   337,   327,     0,     0,     0,   753,     0,   754,
     730,     0,   725,   808,     0,   811,     0,   800,   878,     0,
     876,   874,   868,   872,   873,     0,   865,   870,   871,   869,
     861,   910,   911,   912,   913,   903,    52,    57,     0,   598,
       0,   234,   236,   275,   277,   279,   281,   296,   297,   298,
     295,   302,   304,   306,   308,   247,   384,   525,   564,   470,
     467,     0,     0,     0,     0,   687,   692,   631,   346,   746,
     747,   748,   745,   750,   752,     0,   728,   810,   813,     0,
       0,     0,   867,   864,    56,   601,   680,   469,     0,     0,
     715,   716,   691,   767,   770,   772,   774,   766,   765,   764,
       0,   757,   760,   761,   762,   763,     0,   875,     0,   866,
     712,   714,     0,     0,     0,     0,   759,   756,     0,   877,
       0,     0,     0,     0,   758,   883,     0,   880,   769,   768,
     771,   773,   776,     0,   882,   879,   781,     0,   777,   778,
     893,     0,     0,     0,   898,     0,   885,   888,   889,   890,
     891,   892,   881,     0,   775,   780,     0,     0,     0,     0,
       0,   887,   884,   793,   795,   792,   786,   788,   790,   791,
       0,   783,   787,   789,   779,     0,   895,   896,   897,     0,
     886,     0,     0,   785,   782,   894,   899,     0,     0,   784,
     794,   796
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330,   -59, -1330,  -584, -1330,   222,
   -1330, -1330, -1330, -1330, -1330, -1330,  -635, -1330, -1330, -1330,
     -67, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   438,   648,
     -30,   -28,   -18,   -54,   -29,    -8,    47,    49,    52,    59,
   -1330, -1330, -1330, -1330,    62, -1330, -1330,    64,    65,    66,
      69,    70,    72, -1330, -1330,    77, -1330,    80, -1330,    82,
      83,    84, -1330, -1330,    85,    87, -1330,    88, -1330,    90,
   -1330, -1330, -1330, -1330, -1330,    46, -1330, -1330, -1330,   420,
     643, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     162, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   357,
   -1330,   136, -1330,  -706,   148, -1330, -1330, -1329, -1330, -1303,
   -1330, -1330, -1330, -1330,   -45, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
    -738, -1330,  -733, -1330,  -732, -1330, -1330, -1330, -1330, -1330,
   -1330,   129, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     117, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   130, -1330,
   -1330, -1330,   133,   620, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330,   125, -1330, -1330, -1330, -1330, -1330, -1330, -1006, -1330,
   -1330, -1330,   153, -1330, -1330, -1330,   156,   656, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1003, -1330,    92, -1330,
      93, -1330,   101, -1330,    95,    98,   100, -1330, -1330, -1330,
   -1330, -1330,   146, -1330, -1330,   -89,   -62, -1330, -1330, -1330,
   -1330, -1330,   164, -1330, -1330, -1330,   168, -1330,   632, -1330,
     -63, -1330, -1330, -1330, -1330, -1330,   -58, -1330, -1330, -1330,
   -1330, -1330,    10, -1330, -1330, -1330,   166, -1330, -1330, -1330,
     171, -1330,   634, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330,    96, -1330, -1330,
   -1330,    99,   663, -1330, -1330, -1330,   -49, -1330,    -3, -1330,
     -56, -1330, -1330, -1330,   149, -1330, -1330, -1330,   173, -1330,
     662,    16, -1330,    26, -1330,    36, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330,  -997, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330,   155, -1330, -1330, -1330,   -90, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     132, -1330,   131,   134, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330,  -127, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,  -165, -1330,
   -1330,  -192, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   135,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
     452,   633, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,   494,
     636, -1330, -1330, -1330, -1330, -1330, -1330,   141, -1330, -1330,
     -84, -1330, -1330, -1330, -1330, -1330, -1330,  -132, -1330, -1330,
    -158, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330, -1330,
   -1330,   140, -1330, -1330, -1330, -1330
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   742,
      82,    83,    39,    64,    79,    80,   759,   977,  1084,  1085,
     832,    41,    66,    85,   432,    86,    43,    67,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   460,   171,   172,   477,   173,   174,   175,   176,
     177,   178,   179,   466,   728,   180,   467,   181,   468,   182,
     183,   184,   478,   739,   185,   186,   496,   187,   497,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   436,   235,
     236,    45,    68,   237,   506,   238,   507,   762,   239,   508,
     765,   240,   241,   242,   243,   197,   446,   198,   437,   807,
     808,   809,   989,   810,   990,   199,   447,   200,   448,   859,
     860,   861,  1017,   833,   834,   835,   993,   836,   994,   837,
     995,   838,   996,   839,   840,   544,   841,   842,   843,   844,
     845,   846,   847,   848,   849,   850,  1007,  1260,   851,   852,
     853,  1010,   854,  1011,   855,  1012,   856,  1013,   201,   485,
     883,   884,   885,   886,   887,   888,   889,   202,   491,   919,
     920,   921,   922,   923,   203,   488,   898,   899,   900,  1040,
      59,    75,   396,   397,   398,   559,   399,   560,   204,   489,
     907,   908,   909,   910,   911,   912,   913,   914,   205,   473,
     863,   864,   865,  1020,    47,    69,   285,   286,   287,   519,
     288,   515,   289,   516,   290,   517,   291,   520,   292,   524,
     293,   522,   294,   523,   206,   207,   208,   298,   209,   479,
     875,   876,   877,  1029,  1162,  1163,   210,   474,    53,    72,
     867,   868,   869,  1023,    55,    73,   357,   358,   359,   360,
     361,   362,   363,   543,   364,   547,   365,   546,   366,   367,
     548,   368,   211,   475,   871,   872,   873,  1026,    57,    74,
     380,   381,   382,   383,   384,   552,   385,   386,   387,   388,
     389,   390,   556,   300,   518,   979,   980,   981,  1086,    49,
      70,   315,   316,   317,   528,   318,   212,   480,   213,   481,
     214,   487,   894,   895,   896,  1037,    51,    71,   333,   334,
     335,   215,   441,   216,   442,   217,   443,   339,   533,   340,
     534,   341,   535,   342,   537,   343,   536,   344,   539,   345,
     538,   346,   532,   307,   525,   983,   984,  1089,   218,   486,
     891,   892,  1034,  1190,  1191,  1192,  1193,  1194,  1271,  1195,
    1272,  1196,  1197,   219,   220,   492,   221,   493,   947,   948,
     949,  1064,   938,   939,   940,  1056,  1282,   941,  1057,   942,
    1058,   943,   944,   945,  1060,  1310,  1311,  1312,  1322,  1339,
    1313,  1323,  1314,  1324,  1315,  1325,  1347,  1348,  1349,  1363,
    1380,  1381,  1382,  1391,  1383,  1392,   222,   494,   956,   957,
     958,   959,  1068,   960,   961,  1070,   223,   495,    61,    76,
     411,   412,   413,   414,   564,   415,   416,   566,   417,   418,
     419,   569,   798,   420,   570,   224,   435,    63,    77,   423,
     424,   425,   573,   426,   225,   501,   964,   965,  1074,  1235,
    1236,  1237,  1238,  1291,  1239,  1289,  1336,  1337,  1343,  1355,
    1356,  1357,  1366,  1358,  1359,  1360,  1361,  1370,   226,   502,
     971,   972,   973,   974,   975,   976
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   257,   310,   329,    78,   355,   376,   395,   408,
     347,   378,   933,   303,   857,   261,   379,   934,   935,   244,
     301,   319,   331,  1154,   369,   391,  1155,   409,   356,   377,
     772,   773,  1170,    29,  1376,    30,   796,    31,   777,   258,
     262,   259,   741,  1032,   393,   394,  1033,  1035,   227,   228,
    1036,   260,   229,   421,   422,   230,   231,   232,   233,   791,
    1377,   263,   132,   133,  1376,   245,   302,   320,   332,    81,
     370,   392,   127,   410,    28,   723,   724,   725,   726,   299,
     314,   330,   828,   829,   830,   304,    40,   336,   393,   394,
    1377,    84,   308,   132,   133,   305,  1350,   337,    42,  1351,
    1352,  1353,  1354,   253,   254,   306,   433,   338,   428,   255,
     309,   434,   504,   741,   727,   284,   264,   505,   265,   760,
     761,   266,   513,   950,   951,   952,   155,   514,   267,  1075,
      44,   268,  1076,   269,   270,   271,   132,   133,   272,   273,
     526,   274,   763,   764,   427,   527,   275,   132,   133,   276,
     530,   277,   278,   279,   280,   531,   281,   282,    46,   283,
     561,   571,   311,   312,   295,   562,   572,   296,    48,   297,
      50,   313,    52,   953,   429,   901,   902,   903,   904,   905,
     906,   926,  1257,  1258,  1259,   927,   928,   929,   930,    91,
      92,    93,    94,    95,    96,   931,    54,   575,    56,    93,
      94,    95,   576,    58,   155,   797,   504,   878,   879,   880,
     881,   986,   882,  1279,  1280,  1281,   575,   966,   967,   968,
     969,   987,    60,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,  1303,   155,   805,   806,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   155,   246,   247,
     248,    62,   127,    32,    33,    34,    35,   513,   155,   348,
     127,   126,   988,  1154,   129,   130,  1155,   735,   736,   737,
     738,   249,  1170,   132,   133,   250,   251,   252,   134,   135,
     136,   132,   133,   253,   254,    93,    94,    95,    96,   255,
     321,   139,   812,   813,  1344,   430,   431,  1345,   438,   256,
     322,   323,   324,   325,   326,   327,   328,   132,   133,   132,
     133,  1117,   439,   349,   440,   350,   351,   101,   102,   103,
     352,   353,   354,   349,   933,   444,   933,   445,   449,   934,
     935,   934,   935,   132,   133,   349,   371,   350,   351,   372,
     373,   374,   450,   132,   133,   126,   127,   349,   451,   915,
     916,   917,   148,   149,   991,   132,   133,   452,   540,   992,
     453,  1304,  1305,  1306,   375,   132,   133,   132,   133,   577,
     578,  1014,  1014,  1049,   542,   454,  1015,  1016,  1050,  1173,
    1174,  1175,  1176,  1054,   155,  1062,  1071,   541,  1055,   455,
    1063,  1072,   155,   456,   811,   812,   813,   814,   815,   816,
     817,   818,   819,   820,   821,   822,   823,   824,   825,   457,
     458,   459,   826,   827,   828,   829,   830,   831,   155,   571,
     155,  1081,  1373,  1374,  1073,   461,  1082,  1014,  1228,   526,
    1229,  1230,  1265,  1269,  1266,   561,  1062,   156,  1270,   462,
    1278,  1286,  1292,   551,   155,   530,   234,  1293,   349,   463,
    1295,  1326,  1371,  1393,   155,   464,  1327,  1372,  1394,   257,
     465,   469,   470,   310,   244,   471,   155,   472,   476,   482,
     303,   483,   261,   484,   329,   490,   155,   301,   155,   498,
     499,   319,   500,   503,   355,   509,   510,   511,   512,   521,
     529,   376,   331,   545,   549,   378,   258,   262,   259,   550,
     379,   553,   369,   554,   408,   555,   356,   558,   260,   391,
     245,   557,   563,   377,   565,   567,   568,   574,   263,   580,
     579,   581,   409,   302,   582,   583,   584,   320,   585,   586,
     587,   588,   589,   590,   591,   592,   299,   593,   332,   594,
     314,   595,   304,   596,   597,   598,   599,   606,   370,   612,
     600,   330,   305,   601,   602,   392,   603,   336,   604,   605,
     607,   608,   306,   613,   609,   610,   614,   337,   410,   132,
     133,   611,   284,   264,   615,   265,   616,   338,   266,   155,
     618,   619,   617,   620,   621,   267,   622,   623,   268,   624,
     269,   270,   271,   625,   626,   272,   273,   627,   274,   631,
     628,   629,   630,   275,   632,   633,   276,   634,   277,   278,
     279,   280,   635,   281,   282,  1296,   283,   636,   637,   638,
     639,   295,   311,   312,   296,   640,   297,   641,   642,   643,
     644,   313,   645,   647,   400,   401,   402,   403,   404,   405,
     406,   407,   646,   648,   650,   156,   651,   234,   652,   658,
     653,   654,   801,   655,   656,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   244,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   670,
     155,   673,   918,   932,   674,   671,   408,   675,   676,   677,
     970,   678,   684,   679,   680,   682,   683,   685,   686,    87,
     924,   936,    88,   954,   409,   687,   690,   694,   688,   696,
     697,   245,   700,   702,    89,   691,   692,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   693,   705,
     699,   701,   703,   704,   706,   708,   711,   799,   721,  1338,
     709,   712,   713,   714,   715,   719,   925,   937,   716,   955,
     410,   720,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   717,   718,   722,
     126,   127,   729,   730,   731,   732,   733,   740,   734,   743,
      30,   744,   128,   129,   130,   745,   746,   747,   754,   131,
     748,   749,   132,   133,   750,   751,   752,   134,   135,   136,
     137,   138,   753,   755,   756,   757,   758,   766,   769,   767,
     139,   768,   770,   771,   774,   775,   800,   776,   997,   778,
     140,   779,   780,   141,   781,   782,   783,   784,   785,   858,
     142,   143,   786,   787,   788,   144,   145,   789,   862,   866,
     870,   790,   792,   794,   874,   795,   890,   893,   897,   946,
     963,   978,   146,   982,   998,   999,   147,  1000,  1001,  1002,
    1003,  1004,  1005,  1006,  1008,  1009,  1019,  1100,  1018,  1022,
    1021,   148,   149,   150,   151,   152,   153,  1024,  1025,  1027,
    1028,  1031,  1030,  1043,  1039,   154,  1038,  1042,  1041,  1044,
    1045,  1046,  1047,  1048,  1051,  1052,  1053,  1059,  1061,  1066,
    1088,  1065,  1067,   155,  1069,  1077,  1078,  1079,  1080,   793,
    1083,  1087,  1092,  1091,  1090,  1093,  1095,  1096,  1097,  1098,
    1099,  1109,  1112,  1101,  1113,  1114,  1115,  1103,  1102,  1104,
    1105,  1106,  1107,  1108,  1214,  1111,  1110,  1203,  1210,  1204,
    1205,  1215,  1206,   257,  1207,  1208,   355,  1216,  1218,   376,
    1224,  1226,  1125,   378,   303,  1211,   261,  1177,   379,  1212,
     329,   301,  1183,   395,   369,  1129,  1217,   391,   356,  1219,
    1165,   377,  1223,  1225,  1153,  1185,  1241,   918,   331,  1182,
     258,   262,   259,  1242,  1243,   932,  1244,   932,  1246,  1126,
    1130,  1127,   260,  1247,  1178,   924,  1179,  1231,  1250,  1251,
    1252,  1128,   263,   936,   970,   936,  1180,   302,  1267,   310,
     370,  1131,   954,   392,  1268,  1233,  1166,  1253,  1254,  1232,
     299,  1186,  1255,  1273,   332,  1256,   304,   319,  1274,  1164,
    1261,  1262,  1263,  1275,  1184,  1167,   305,   330,  1264,  1276,
    1187,   925,  1277,   336,  1283,  1168,   306,  1285,  1284,   937,
    1188,   937,  1287,   337,  1290,  1169,   284,   264,   955,   265,
    1189,  1234,   266,   338,  1298,  1152,  1132,  1299,  1133,   267,
    1181,  1134,   268,   320,   269,   270,   271,  1294,  1135,   272,
     273,  1136,   274,  1137,  1138,  1139,   314,   275,  1140,  1141,
     276,  1142,   277,   278,   279,   280,  1143,   281,   282,  1144,
     283,  1145,  1146,  1147,  1148,   295,  1149,  1150,   296,  1151,
     297,  1156,  1157,  1316,  1159,  1318,  1330,  1160,  1328,  1161,
    1158,  1331,  1332,  1333,   804,  1342,  1365,  1300,  1335,  1346,
    1364,  1367,  1368,  1369,  1385,  1389,  1317,  1301,  1397,  1398,
     802,  1320,   649,  1094,  1321,  1118,   657,   985,  1329,  1340,
    1341,  1172,  1116,  1387,  1386,  1388,  1395,  1288,  1396,  1400,
    1401,  1213,  1202,  1201,  1209,  1120,  1119,  1171,   311,   312,
    1297,   698,   669,   689,  1249,  1248,  1302,   313,  1200,  1122,
    1198,  1121,   695,   672,  1124,  1221,  1220,  1123,  1222,  1334,
    1384,  1399,  1125,   681,   707,   962,  1227,   803,  1319,  1177,
    1199,   710,  1362,  1390,  1183,  1129,  1240,     0,  1307,     0,
    1165,  1245,     0,     0,  1153,  1231,     0,  1185,     0,     0,
       0,  1182,     0,     0,     0,     0,  1308,     0,     0,  1126,
    1130,  1127,     0,  1233,     0,     0,  1178,  1232,  1179,     0,
       0,  1128,     0,     0,     0,     0,     0,     0,  1180,  1307,
       0,  1131,     0,     0,     0,     0,  1166,     0,     0,     0,
       0,     0,     0,  1186,     0,     0,     0,  1308,     0,  1164,
       0,     0,  1309,     0,     0,  1167,  1184,     0,     0,  1234,
       0,     0,  1187,     0,     0,  1168,  1375,     0,     0,     0,
       0,     0,  1188,     0,     0,  1169,     0,     0,     0,     0,
       0,     0,  1189,     0,  1378,  1152,  1132,     0,  1133,     0,
       0,  1134,  1181,  1309,     0,     0,  1375,     0,  1135,     0,
       0,  1136,     0,  1137,  1138,  1139,     0,     0,  1140,  1141,
       0,  1142,     0,     0,  1378,     0,  1143,     0,     0,  1144,
       0,  1145,  1146,  1147,  1148,     0,  1149,  1150,     0,  1151,
    1379,  1156,  1157,     0,  1159,     0,     0,  1160,     0,  1161,
    1158,    91,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1379,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,   127,   349,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   130,     0,     0,
       0,     0,     0,     0,     0,   132,   133,     0,   251,     0,
     134,   135,   136,     0,     0,   253,   254,     0,     0,     0,
       0,   255,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   256,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   155
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   750,    69,   720,    69,    74,   750,   750,    68,
      69,    70,    71,  1029,    73,    74,  1029,    76,    73,    74,
     665,   666,  1029,     5,  1363,     7,    18,     9,   673,    69,
      69,    69,   626,     3,   143,   144,     6,     3,    15,    16,
       6,    69,    19,    12,    13,    22,    23,    24,    25,   694,
    1363,    69,   114,   115,  1393,    68,    69,    70,    71,   225,
      73,    74,    93,    76,     0,   189,   190,   191,   192,    69,
      70,    71,    60,    61,    62,    69,     7,    71,   143,   144,
    1393,    10,   113,   114,   115,    69,   200,    71,     7,   203,
     204,   205,   206,   124,   125,    69,     3,    71,     3,   130,
     131,     8,     3,   697,   228,    69,    69,     8,    69,    17,
      18,    69,     3,   175,   176,   177,   225,     8,    69,     3,
       7,    69,     6,    69,    69,    69,   114,   115,    69,    69,
       3,    69,    20,    21,     6,     8,    69,   114,   115,    69,
       3,    69,    69,    69,    69,     8,    69,    69,     7,    69,
       3,     3,    70,    70,    69,     8,     8,    69,     7,    69,
       7,    70,     7,   225,     4,   146,   147,   148,   149,   150,
     151,   159,    55,    56,    57,   163,   164,   165,   166,    30,
      31,    32,    33,    34,    35,   173,     7,     3,     7,    32,
      33,    34,     8,     7,   225,   187,     3,   134,   135,   136,
     137,     8,   139,   160,   161,   162,     3,   208,   209,   210,
     211,     8,     7,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    40,   225,    27,    28,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,   225,    89,    90,
      91,     7,    93,   225,   226,   227,   228,     3,   225,    40,
      93,    92,     8,  1269,   105,   106,  1269,   107,   108,   109,
     110,   112,  1269,   114,   115,   116,   117,   118,   119,   120,
     121,   114,   115,   124,   125,    32,    33,    34,    35,   130,
     123,   132,    41,    42,     3,     8,     3,     6,     4,   140,
     133,   134,   135,   136,   137,   138,   139,   114,   115,   114,
     115,  1017,     4,    94,     4,    96,    97,    64,    65,    66,
     101,   102,   103,    94,  1062,     4,  1064,     4,     4,  1062,
    1062,  1064,  1064,   114,   115,    94,    95,    96,    97,    98,
      99,   100,     4,   114,   115,    92,    93,    94,     4,   154,
     155,   156,   193,   194,     3,   114,   115,     4,     8,     8,
       4,   168,   169,   170,   123,   114,   115,   114,   115,   428,
     429,     3,     3,     3,     8,     4,     8,     8,     8,   126,
     127,   128,   129,     3,   225,     3,     3,     3,     8,     4,
       8,     8,   225,     4,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     4,
       4,     4,    58,    59,    60,    61,    62,    63,   225,     3,
     225,     3,   171,   172,     8,     4,     8,     3,   199,     3,
     201,   202,     8,     3,     8,     3,     3,   504,     8,     4,
       8,     8,     3,     3,   225,     3,   513,     8,    94,     4,
       8,     3,     3,     3,   225,     4,     8,     8,     8,   526,
       4,     4,     4,   530,   513,     4,   225,     4,     4,     4,
     526,     4,   526,     4,   541,     4,   225,   526,   225,     4,
       4,   530,     4,     4,   551,     4,     4,     4,     4,     4,
       4,   558,   541,     4,     4,   558,   526,   526,   526,     8,
     558,     4,   551,     4,   571,     4,   551,     3,   526,   558,
     513,     8,     4,   558,     4,     4,     4,     4,   526,     4,
     225,     4,   571,   526,     4,     4,   228,   530,   228,   228,
       4,     4,     4,   226,   228,     4,   526,     4,   541,     4,
     530,   226,   526,   226,   226,   226,   226,     4,   551,     4,
     228,   541,   526,   227,   227,   558,   227,   541,   226,   226,
     226,   226,   526,     4,   228,   228,     4,   541,   571,   114,
     115,   228,   526,   526,   228,   526,   228,   541,   526,   225,
     228,     4,   227,     4,     4,   526,   226,     4,   526,     4,
     526,   526,   526,     4,     4,   526,   526,     4,   526,     4,
     228,   228,   228,   526,     4,     4,   526,     4,   526,   526,
     526,   526,     4,   526,   526,  1250,   526,   226,     4,     4,
       4,   526,   530,   530,   526,     4,   526,     4,     4,     4,
     228,   530,   228,     4,   179,   180,   181,   182,   183,   184,
     185,   186,   228,     4,     4,   712,     4,   714,     4,     4,
     228,   228,   711,   226,   226,     4,     4,     4,     4,     4,
     226,     4,     4,     4,     4,   714,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     4,
     225,     4,   749,   750,     4,   226,   753,     4,     4,     4,
     757,     4,   226,     4,     4,     4,     4,     4,     4,    11,
     749,   750,    14,   752,   753,     4,     4,     4,   228,     4,
       4,   714,     4,     4,    26,   228,   228,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   228,     4,
     228,   226,   226,   226,     4,     4,     4,   188,     5,   167,
     226,     7,     7,     7,     7,     7,   749,   750,   225,   752,
     753,     7,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,   225,   225,   225,
      92,    93,   225,   225,     5,     5,     5,     5,   225,   225,
       7,     5,   104,   105,   106,     5,     5,     5,   225,   111,
       7,     7,   114,   115,     7,     5,     7,   119,   120,   121,
     122,   123,     7,   225,     5,     7,     5,   225,     5,   225,
     132,   225,   225,   225,   225,     7,     5,   225,     4,   225,
     142,   225,   225,   145,   225,   225,   225,   225,   225,     7,
     152,   153,   225,   225,   225,   157,   158,   225,     7,     7,
       7,   225,   225,   225,     7,   225,     7,     7,     7,     7,
       7,     7,   174,   141,     4,     4,   178,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   228,     6,     3,
       6,   193,   194,   195,   196,   197,   198,     6,     3,     6,
       3,     3,     6,     4,     3,   207,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     6,     4,   225,     4,     4,     4,     4,     4,   697,
     225,     6,     4,     6,     8,     4,     4,     4,     4,     4,
     226,     4,     4,   226,     4,     4,     4,   226,   228,   226,
     226,   226,   226,   226,     4,   226,   228,   226,   228,   226,
     226,     4,   226,  1020,   226,   226,  1023,     4,     4,  1026,
       4,     4,  1029,  1026,  1020,   226,  1020,  1034,  1026,   226,
    1037,  1020,  1034,  1040,  1023,  1029,   226,  1026,  1023,   228,
    1029,  1026,   228,   226,  1029,  1034,   228,  1054,  1037,  1034,
    1020,  1020,  1020,   228,   228,  1062,   228,  1064,     6,  1029,
    1029,  1029,  1020,     3,  1034,  1054,  1034,  1074,     4,   225,
     225,  1029,  1020,  1062,  1081,  1064,  1034,  1020,     8,  1086,
    1023,  1029,  1071,  1026,     8,  1074,  1029,   225,   225,  1074,
    1020,  1034,   225,     4,  1037,   225,  1020,  1086,     4,  1029,
     225,   225,   225,     8,  1034,  1029,  1020,  1037,   225,     3,
    1034,  1054,     8,  1037,   225,  1029,  1020,     7,   225,  1062,
    1034,  1064,   225,  1037,     4,  1029,  1020,  1020,  1071,  1020,
    1034,  1074,  1020,  1037,     4,  1029,  1029,     4,  1029,  1020,
    1034,  1029,  1020,  1086,  1020,  1020,  1020,   225,  1029,  1020,
    1020,  1029,  1020,  1029,  1029,  1029,  1086,  1020,  1029,  1029,
    1020,  1029,  1020,  1020,  1020,  1020,  1029,  1020,  1020,  1029,
    1020,  1029,  1029,  1029,  1029,  1020,  1029,  1029,  1020,  1029,
    1020,  1029,  1029,     4,  1029,     4,     4,  1029,     5,  1029,
    1029,     4,     4,     4,   714,     5,     3,   228,     7,     7,
       6,     4,     4,     4,     4,     4,   226,   228,     4,     4,
     712,   225,   504,   991,   225,  1019,   513,   800,   225,   225,
     225,  1032,  1014,   226,   228,   226,   225,  1226,   225,   225,
     225,  1054,  1042,  1040,  1049,  1022,  1020,  1031,  1086,  1086,
    1269,   561,   526,   551,  1088,  1086,  1276,  1086,  1039,  1025,
    1035,  1023,   558,   530,  1028,  1064,  1062,  1026,  1066,  1326,
    1365,  1393,  1269,   541,   571,   753,  1071,   713,  1292,  1276,
    1037,   575,  1344,  1371,  1276,  1269,  1075,    -1,  1285,    -1,
    1269,  1081,    -1,    -1,  1269,  1292,    -1,  1276,    -1,    -1,
      -1,  1276,    -1,    -1,    -1,    -1,  1285,    -1,    -1,  1269,
    1269,  1269,    -1,  1292,    -1,    -1,  1276,  1292,  1276,    -1,
      -1,  1269,    -1,    -1,    -1,    -1,    -1,    -1,  1276,  1326,
      -1,  1269,    -1,    -1,    -1,    -1,  1269,    -1,    -1,    -1,
      -1,    -1,    -1,  1276,    -1,    -1,    -1,  1326,    -1,  1269,
      -1,    -1,  1285,    -1,    -1,  1269,  1276,    -1,    -1,  1292,
      -1,    -1,  1276,    -1,    -1,  1269,  1363,    -1,    -1,    -1,
      -1,    -1,  1276,    -1,    -1,  1269,    -1,    -1,    -1,    -1,
      -1,    -1,  1276,    -1,  1363,  1269,  1269,    -1,  1269,    -1,
      -1,  1269,  1276,  1326,    -1,    -1,  1393,    -1,  1269,    -1,
      -1,  1269,    -1,  1269,  1269,  1269,    -1,    -1,  1269,  1269,
      -1,  1269,    -1,    -1,  1393,    -1,  1269,    -1,    -1,  1269,
      -1,  1269,  1269,  1269,  1269,    -1,  1269,  1269,    -1,  1269,
    1363,  1269,  1269,    -1,  1269,    -1,    -1,  1269,    -1,  1269,
    1269,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1393,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,   115,    -1,   117,    -1,
     119,   120,   121,    -1,    -1,   124,   125,    -1,    -1,    -1,
      -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   193,   194,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,     0,     5,
       7,     9,   225,   226,   227,   228,   244,   245,   246,   251,
       7,   260,     7,   265,     7,   320,     7,   433,     7,   518,
       7,   535,     7,   467,     7,   473,     7,   497,     7,   409,
       7,   637,     7,   656,   252,   247,   261,   266,   321,   434,
     519,   536,   468,   474,   498,   410,   638,   657,   244,   253,
     254,   225,   249,   250,    10,   262,   264,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    92,    93,   104,   105,
     106,   111,   114,   115,   119,   120,   121,   122,   123,   132,
     142,   145,   152,   153,   157,   158,   174,   178,   193,   194,
     195,   196,   197,   198,   207,   225,   259,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   282,   283,   285,   286,   287,   288,   289,   290,   291,
     294,   296,   298,   299,   300,   303,   304,   306,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   334,   336,   344,
     346,   387,   396,   403,   417,   427,   453,   454,   455,   457,
     465,   491,   525,   527,   529,   540,   542,   544,   567,   582,
     583,   585,   625,   635,   654,   663,   687,    15,    16,    19,
      22,    23,    24,    25,   259,   318,   319,   322,   324,   327,
     330,   331,   332,   333,   525,   527,    89,    90,    91,   112,
     116,   117,   118,   124,   125,   130,   140,   259,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   283,   286,
     287,   288,   289,   290,   291,   294,   296,   298,   299,   300,
     303,   304,   306,   308,   314,   435,   436,   437,   439,   441,
     443,   445,   447,   449,   451,   453,   454,   455,   456,   491,
     512,   525,   527,   529,   540,   542,   544,   562,   113,   131,
     259,   447,   449,   451,   491,   520,   521,   522,   524,   525,
     527,   123,   133,   134,   135,   136,   137,   138,   139,   259,
     491,   525,   527,   537,   538,   539,   540,   542,   544,   546,
     548,   550,   552,   554,   556,   558,   560,   465,    40,    94,
      96,    97,   101,   102,   103,   259,   363,   475,   476,   477,
     478,   479,   480,   481,   483,   485,   487,   488,   490,   525,
     527,    95,    98,    99,   100,   123,   259,   363,   479,   485,
     499,   500,   501,   502,   503,   505,   506,   507,   508,   509,
     510,   525,   527,   143,   144,   259,   411,   412,   413,   415,
     179,   180,   181,   182,   183,   184,   185,   186,   259,   525,
     527,   639,   640,   641,   642,   644,   645,   647,   648,   649,
     652,    12,    13,   658,   659,   660,   662,     6,     3,     4,
       8,     3,   263,     3,     8,   655,   317,   337,     4,     4,
       4,   541,   543,   545,     4,     4,   335,   345,   347,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     281,     4,     4,     4,     4,     4,   292,   295,   297,     4,
       4,     4,     4,   428,   466,   492,     4,   284,   301,   458,
     526,   528,     4,     4,     4,   388,   568,   530,   404,   418,
       4,   397,   584,   586,   626,   636,   305,   307,     4,     4,
       4,   664,   688,     4,     3,     8,   323,   325,   328,     4,
       4,     4,     4,     3,     8,   440,   442,   444,   513,   438,
     446,     4,   450,   452,   448,   563,     3,     8,   523,     4,
       3,     8,   561,   547,   549,   551,   555,   553,   559,   557,
       8,     3,     8,   482,   364,     4,   486,   484,   489,     4,
       8,     3,   504,     4,     4,     4,   511,     8,     3,   414,
     416,     3,     8,     4,   643,     4,   646,     4,     4,   650,
     653,     3,     8,   661,     4,     3,     8,   244,   244,   225,
       4,     4,     4,     4,   228,   228,   228,     4,     4,     4,
     226,   228,     4,     4,     4,   226,   226,   226,   226,   226,
     228,   227,   227,   227,   226,   226,     4,   226,   226,   228,
     228,   228,     4,     4,     4,   228,   228,   227,   228,     4,
       4,     4,   226,     4,     4,     4,     4,     4,   228,   228,
     228,     4,     4,     4,     4,     4,   226,     4,     4,     4,
       4,     4,     4,     4,   228,   228,   228,     4,     4,   268,
       4,     4,     4,   228,   228,   226,   226,   319,     4,     4,
       4,     4,     4,     4,   226,     4,     4,     4,     4,   436,
       4,   226,   521,     4,     4,     4,     4,     4,     4,     4,
       4,   539,     4,     4,   226,     4,     4,     4,   228,   477,
       4,   228,   228,   228,     4,   501,     4,     4,   412,   228,
       4,   226,     4,   226,   226,     4,     4,   640,     4,   226,
     659,     4,     7,     7,     7,     7,   225,   225,   225,     7,
       7,     5,   225,   189,   190,   191,   192,   228,   293,   225,
     225,     5,     5,     5,   225,   107,   108,   109,   110,   302,
       5,   246,   248,   225,     5,     5,     5,     5,     7,     7,
       7,     5,     7,     7,   225,   225,     5,     7,     5,   255,
      17,    18,   326,    20,    21,   329,   225,   225,   225,     5,
     225,   225,   255,   255,   225,     7,   225,   255,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   255,   225,   248,   225,   225,    18,   187,   651,   188,
       5,   244,   267,   658,   318,    27,    28,   338,   339,   340,
     342,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    58,    59,    60,    61,
      62,    63,   259,   352,   353,   354,   356,   358,   360,   362,
     363,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   377,   378,   379,   381,   383,   385,   352,     7,   348,
     349,   350,     7,   429,   430,   431,     7,   469,   470,   471,
       7,   493,   494,   495,     7,   459,   460,   461,   134,   135,
     136,   137,   139,   389,   390,   391,   392,   393,   394,   395,
       7,   569,   570,     7,   531,   532,   533,     7,   405,   406,
     407,   146,   147,   148,   149,   150,   151,   419,   420,   421,
     422,   423,   424,   425,   426,   154,   155,   156,   259,   398,
     399,   400,   401,   402,   525,   527,   159,   163,   164,   165,
     166,   173,   259,   379,   381,   383,   525,   527,   591,   592,
     593,   596,   598,   600,   601,   602,     7,   587,   588,   589,
     175,   176,   177,   225,   525,   527,   627,   628,   629,   630,
     632,   633,   639,     7,   665,   666,   208,   209,   210,   211,
     259,   689,   690,   691,   692,   693,   694,   256,     7,   514,
     515,   516,   141,   564,   565,   348,     8,     8,     8,   341,
     343,     3,     8,   355,   357,   359,   361,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   375,     4,     4,
     380,   382,   384,   386,     3,     8,     8,   351,     6,     3,
     432,     6,     3,   472,     6,     3,   496,     6,     3,   462,
       6,     3,     3,     6,   571,     3,     6,   534,     6,     3,
     408,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   594,   597,   599,     4,
     603,     4,     3,     8,   590,     6,     3,     4,   631,     4,
     634,     3,     8,     8,   667,     3,     6,     4,     4,     4,
       4,     3,     8,   225,   257,   258,   517,     6,     3,   566,
       8,     6,     4,     4,   339,     4,     4,     4,     4,   226,
     228,   226,   228,   226,   226,   226,   226,   226,   226,     4,
     228,   226,     4,     4,     4,     4,   353,   352,   350,   435,
     431,   475,   471,   499,   495,   259,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   283,   286,   287,   288,
     289,   290,   291,   294,   296,   298,   299,   300,   303,   304,
     306,   308,   314,   363,   427,   445,   447,   449,   451,   453,
     454,   455,   463,   464,   491,   525,   527,   540,   542,   544,
     562,   461,   390,   126,   127,   128,   129,   259,   269,   270,
     271,   314,   363,   465,   491,   525,   527,   540,   542,   544,
     572,   573,   574,   575,   576,   578,   580,   581,   570,   537,
     533,   411,   407,   226,   226,   226,   226,   226,   226,   420,
     228,   226,   226,   399,     4,     4,     4,   226,     4,   228,
     592,   591,   589,   228,     4,   226,     4,   628,   199,   201,
     202,   259,   363,   525,   527,   668,   669,   670,   671,   673,
     666,   228,   228,   228,   228,   690,     6,     3,   520,   516,
       4,   225,   225,   225,   225,   225,   225,    55,    56,    57,
     376,   225,   225,   225,   225,     8,     8,     8,     8,     3,
       8,   577,   579,     4,     4,     8,     3,     8,     8,   160,
     161,   162,   595,   225,   225,     7,     8,   225,   244,   674,
       4,   672,     3,     8,   225,     8,   255,   464,     4,     4,
     228,   228,   574,    40,   168,   169,   170,   259,   525,   527,
     604,   605,   606,   609,   611,   613,     4,   226,     4,   669,
     225,   225,   607,   610,   612,   614,     3,     8,     5,   225,
       4,     4,     4,     4,   605,     7,   675,   676,   167,   608,
     225,   225,     5,   677,     3,     6,     7,   615,   616,   617,
     200,   203,   204,   205,   206,   678,   679,   680,   682,   683,
     684,   685,   676,   618,     6,     3,   681,     4,     4,     4,
     686,     3,     8,   171,   172,   259,   356,   358,   525,   527,
     619,   620,   621,   623,   617,     4,   228,   226,   226,     4,
     679,   622,   624,     3,     8,   225,   225,     4,     4,   620,
     225,   225
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   229,   231,   230,   232,   230,   233,   230,   234,   230,
     235,   230,   236,   230,   237,   230,   238,   230,   239,   230,
     240,   230,   241,   230,   242,   230,   243,   230,   244,   244,
     244,   244,   244,   244,   244,   245,   247,   246,   248,   249,
     249,   250,   250,   250,   252,   251,   253,   253,   254,   254,
     254,   256,   255,   257,   257,   258,   258,   258,   259,   261,
     260,   263,   262,   262,   264,   266,   265,   267,   267,   267,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     281,   280,   282,   284,   283,   285,   286,   287,   288,   289,
     290,   292,   291,   293,   293,   293,   293,   293,   295,   294,
     297,   296,   298,   299,   301,   300,   302,   302,   302,   302,
     303,   305,   304,   307,   306,   308,   309,   310,   311,   312,
     313,   314,   315,   317,   316,   318,   318,   318,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   321,   320,
     323,   322,   325,   324,   326,   326,   328,   327,   329,   329,
     330,   331,   332,   333,   335,   334,   337,   336,   338,   338,
     338,   339,   339,   341,   340,   343,   342,   345,   344,   347,
     346,   348,   348,   349,   349,   349,   351,   350,   352,   352,
     352,   353,   353,   353,   353,   353,   353,   353,   353,   353,
     353,   353,   353,   353,   353,   353,   353,   353,   353,   353,
     353,   353,   353,   353,   355,   354,   357,   356,   359,   358,
     361,   360,   362,   364,   363,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   375,   374,   376,   376,   376,   377,
     378,   380,   379,   382,   381,   384,   383,   386,   385,   388,
     387,   389,   389,   389,   390,   390,   390,   390,   390,   391,
     392,   393,   394,   395,   397,   396,   398,   398,   398,   399,
     399,   399,   399,   399,   399,   400,   401,   402,   404,   403,
     405,   405,   406,   406,   406,   408,   407,   410,   409,   411,
     411,   411,   411,   412,   412,   414,   413,   416,   415,   418,
     417,   419,   419,   419,   420,   420,   420,   420,   420,   420,
     421,   422,   423,   424,   425,   426,   428,   427,   429,   429,
     430,   430,   430,   432,   431,   434,   433,   435,   435,   435,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   438,
     437,   440,   439,   442,   441,   444,   443,   446,   445,   448,
     447,   450,   449,   452,   451,   453,   454,   455,   456,   458,
     457,   459,   459,   460,   460,   460,   462,   461,   463,   463,
     463,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   466,   465,   468,   467,   469,
     469,   470,   470,   470,   472,   471,   474,   473,   475,   475,
     476,   476,   476,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   478,   479,   480,   482,   481,   484,   483,
     486,   485,   487,   489,   488,   490,   492,   491,   493,   493,
     494,   494,   494,   496,   495,   498,   497,   499,   499,   500,
     500,   500,   501,   501,   501,   501,   501,   501,   501,   501,
     501,   501,   501,   502,   504,   503,   505,   506,   507,   508,
     509,   511,   510,   513,   512,   514,   514,   515,   515,   515,
     517,   516,   519,   518,   520,   520,   520,   521,   521,   521,
     521,   521,   521,   521,   521,   521,   523,   522,   524,   526,
     525,   528,   527,   530,   529,   531,   531,   532,   532,   532,
     534,   533,   536,   535,   537,   537,   538,   538,   538,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   541,   540,   543,   542,   545,   544,
     547,   546,   549,   548,   551,   550,   553,   552,   555,   554,
     557,   556,   559,   558,   561,   560,   563,   562,   564,   566,
     565,   568,   567,   569,   569,   569,   571,   570,   572,   572,
     573,   573,   573,   574,   574,   574,   574,   574,   574,   574,
     574,   574,   574,   574,   574,   574,   574,   574,   574,   574,
     575,   577,   576,   579,   578,   580,   581,   582,   584,   583,
     586,   585,   587,   587,   588,   588,   588,   590,   589,   591,
     591,   591,   592,   592,   592,   592,   592,   592,   592,   592,
     592,   592,   592,   592,   594,   593,   595,   595,   595,   597,
     596,   599,   598,   600,   601,   603,   602,   604,   604,   604,
     605,   605,   605,   605,   605,   605,   605,   607,   606,   608,
     610,   609,   612,   611,   614,   613,   615,   615,   616,   616,
     616,   618,   617,   619,   619,   619,   620,   620,   620,   620,
     620,   620,   620,   622,   621,   624,   623,   626,   625,   627,
     627,   627,   628,   628,   628,   628,   628,   628,   629,   631,
     630,   632,   634,   633,   636,   635,   638,   637,   639,   639,
     639,   640,   640,   640,   640,   640,   640,   640,   640,   640,
     640,   640,   641,   643,   642,   644,   646,   645,   647,   648,
     650,   649,   651,   651,   653,   652,   655,   654,   657,   656,
     658,   658,   658,   659,   659,   661,   660,   662,   664,   663,
     665,   665,   665,   667,   666,   668,   668,   668,   669,   669,
     669,   669,   669,   669,   669,   670,   672,   671,   674,   673,
     675,   675,   675,   677,   676,   678,   678,   678,   679,   679,
     679,   679,   679,   681,   680,   682,   683,   684,   686,   685,
     688,   687,   689,   689,   689,   690,   690,   690,   690,   690,
     691,   692,   693,   694
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     2,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     2,     0,
       4,     0,     6,     1,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     3,     3,     3,     0,     6,     0,     6,     1,     3,
       2,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     2,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       3,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     3,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     2,
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
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     3
  };


#if PARSER4_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"service-sockets-require-all\"", "\"service-sockets-retry-wait-time\"",
  "\"service-sockets-max-retries\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"extended-info-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"offer-lifetime\"",
  "\"stash-agent-options\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"read-timeout\"",
  "\"write-timeout\"", "\"tcp-user-timeout\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"on-fail\"", "\"stop-retry-exit\"",
  "\"serve-retry-exit\"", "\"serve-retry-continue\"",
  "\"retry-on-startup\"", "\"max-row-errors\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cipher-list\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"ddns-ttl-percent\"", "\"store-extended-info\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"never-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"parked-packet-limit\"", "\"allocator\"",
  "\"ddns-conflict-resolution-mode\"", "\"check-with-dhcid\"",
  "\"no-check-with-dhcid\"", "\"check-exists-with-dhcid\"",
  "\"no-check-without-dhcid\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"evaluate-additional-classes\"",
  "\"test\"", "\"template-test\"", "\"only-if-required\"",
  "\"only-in-additional-list\"", "\"client-class\"", "\"pool-id\"",
  "\"reservations\"", "\"ip-address\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-addresses\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"control-sockets\"", "\"socket-type\"", "\"unix\"", "\"http\"",
  "\"https\"", "\"socket-name\"", "\"socket-address\"", "\"socket-port\"",
  "\"authentication\"", "\"basic\"", "\"realm\"", "\"directory\"",
  "\"clients\"", "\"user-file\"", "\"password-file\"", "\"cert-required\"",
  "\"dhcp-queue-control\"", "\"enable-queue\"", "\"queue-type\"",
  "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"", "\"tcp\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"early-global-reservations-lookup\"",
  "\"ip-reservations-unique\"", "\"reservations-lookup-first\"",
  "\"loggers\"", "\"output-options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"compatibility\"", "\"lenient-option-parsing\"",
  "\"ignore-dhcp-server-identifier\"", "\"ignore-rai-link-selection\"",
  "\"exclude-first-last-24\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_object", "$@18", "global_object_comma", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "parked_packet_limit", "allocator", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "ddns_conflict_resolution_mode", "$@25",
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first", "offer_lifetime",
  "stash_agent_options", "interfaces_config", "$@28",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@29", "interfaces_list", "$@30", "dhcp_socket_type", "$@31",
  "socket_type", "outbound_interface", "$@32", "outbound_interface_value",
  "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@33", "sanity_checks", "$@34",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@35",
  "extended_info_checks", "$@36", "hosts_database", "$@37",
  "hosts_databases", "$@38", "database_list", "not_empty_database_list",
  "database", "$@39", "database_map_params", "database_map_param",
  "database_type", "$@40", "user", "$@41", "password", "$@42", "host",
  "$@43", "port", "name", "$@44", "persist", "lfc_interval", "readonly",
  "connect_timeout", "read_timeout", "write_timeout", "tcp_user_timeout",
  "max_reconnect_tries", "reconnect_wait_time", "on_fail", "$@45",
  "on_fail_mode", "retry_on_startup", "max_row_errors", "trust_anchor",
  "$@46", "cert_file", "$@47", "key_file", "$@48", "cipher_list", "$@49",
  "host_reservation_identifiers", "$@50",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@51", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@52", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@53",
  "sub_hooks_library", "$@54", "hooks_params", "hooks_param", "library",
  "$@55", "parameters", "$@56", "expired_leases_processing", "$@57",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@58",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@59",
  "sub_subnet4", "$@60", "subnet4_params", "subnet4_param", "subnet",
  "$@61", "subnet_4o6_interface", "$@62", "subnet_4o6_interface_id",
  "$@63", "subnet_4o6_subnet", "$@64", "interface", "$@65", "client_class",
  "$@66", "require_client_classes", "$@67", "evaluate_additional_classes",
  "$@68", "reservations_global", "reservations_in_subnet",
  "reservations_out_of_pool", "id", "shared_networks", "$@69",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@70", "shared_network_params", "shared_network_param",
  "option_def_list", "$@71", "sub_option_def_list", "$@72",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@73", "sub_option_def", "$@74",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@75",
  "option_def_record_types", "$@76", "space", "$@77", "option_def_space",
  "option_def_encapsulate", "$@78", "option_def_array", "option_data_list",
  "$@79", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@80", "sub_option_data", "$@81",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@82",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@83", "pools_list", "$@84",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@85",
  "sub_pool4", "$@86", "pool_params", "pool_param", "pool_entry", "$@87",
  "pool_id", "user_context", "$@88", "comment", "$@89", "reservations",
  "$@90", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@93", "server_hostname", "$@94", "boot_file_name", "$@95",
  "ip_address", "$@96", "duid", "$@97", "hw_address", "$@98",
  "client_id_value", "$@99", "circuit_id_value", "$@100", "flex_id_value",
  "$@101", "hostname", "$@102", "reservation_client_classes", "$@103",
  "relay", "$@104", "relay_map", "ip_addresses", "$@105", "client_classes",
  "$@106", "client_classes_list", "client_class_entry", "$@107",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@108",
  "client_class_template_test", "$@109", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_socket", "$@110",
  "control_sockets", "$@111", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@112",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@113", "control_socket_type_value", "control_socket_name", "$@114",
  "control_socket_address", "$@115", "control_socket_port",
  "cert_required", "authentication", "$@116", "auth_params", "auth_param",
  "auth_type", "$@117", "auth_type_value", "realm", "$@118", "directory",
  "$@119", "clients", "$@120", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@121", "clients_params", "clients_param", "user_file",
  "$@122", "password_file", "$@123", "dhcp_queue_control", "$@124",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@125", "capacity", "arbitrary_map_entry", "$@126",
  "dhcp_ddns", "$@127", "sub_dhcp_ddns", "$@128", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@129", "server_port",
  "sender_ip", "$@130", "sender_port", "max_queue_size", "ncr_protocol",
  "$@131", "ncr_protocol_value", "ncr_format", "$@132", "config_control",
  "$@133", "sub_config_control", "$@134", "config_control_params",
  "config_control_param", "config_databases", "$@135",
  "config_fetch_wait_time", "loggers", "$@136", "loggers_entries",
  "logger_entry", "$@137", "logger_params", "logger_param", "debuglevel",
  "severity", "$@138", "output_options_list", "$@139",
  "output_options_list_content", "output_entry", "$@140",
  "output_params_list", "output_params", "output", "$@141", "flush",
  "maxsize", "maxver", "pattern", "$@142", "compatibility", "$@143",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   324,   324,   324,   325,   325,   326,   326,   327,   327,
     328,   328,   329,   329,   330,   330,   331,   331,   332,   332,
     333,   333,   334,   334,   335,   335,   336,   336,   344,   345,
     346,   347,   348,   349,   350,   353,   358,   358,   369,   372,
     373,   376,   381,   387,   392,   392,   399,   400,   403,   407,
     411,   417,   417,   424,   425,   428,   432,   436,   446,   455,
     455,   470,   470,   484,   487,   493,   493,   502,   503,   504,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   582,
     588,   594,   600,   606,   612,   618,   624,   630,   636,   642,
     648,   648,   657,   663,   663,   672,   678,   684,   690,   696,
     702,   708,   708,   717,   720,   723,   726,   729,   735,   735,
     744,   744,   753,   762,   772,   772,   781,   784,   787,   790,
     795,   801,   801,   810,   810,   819,   825,   831,   837,   843,
     849,   855,   861,   867,   867,   879,   880,   881,   886,   887,
     888,   889,   890,   891,   892,   893,   894,   895,   898,   898,
     907,   907,   918,   918,   926,   927,   930,   930,   938,   940,
     944,   950,   956,   962,   968,   968,   981,   981,   992,   993,
     994,   999,  1000,  1003,  1003,  1022,  1022,  1040,  1040,  1053,
    1053,  1064,  1065,  1068,  1069,  1070,  1075,  1075,  1085,  1086,
    1087,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,
    1101,  1102,  1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,
    1111,  1112,  1113,  1114,  1117,  1117,  1126,  1126,  1135,  1135,
    1144,  1144,  1153,  1159,  1159,  1168,  1174,  1180,  1186,  1192,
    1198,  1204,  1210,  1216,  1222,  1222,  1230,  1231,  1232,  1235,
    1241,  1247,  1247,  1256,  1256,  1265,  1265,  1274,  1274,  1283,
    1283,  1294,  1295,  1296,  1301,  1302,  1303,  1304,  1305,  1308,
    1313,  1318,  1323,  1328,  1335,  1335,  1348,  1349,  1350,  1355,
    1356,  1357,  1358,  1359,  1360,  1363,  1369,  1375,  1381,  1381,
    1392,  1393,  1396,  1397,  1398,  1403,  1403,  1413,  1413,  1423,
    1424,  1425,  1428,  1431,  1432,  1435,  1435,  1444,  1444,  1453,
    1453,  1465,  1466,  1467,  1472,  1473,  1474,  1475,  1476,  1477,
    1480,  1486,  1492,  1498,  1504,  1510,  1519,  1519,  1533,  1534,
    1537,  1538,  1539,  1548,  1548,  1574,  1574,  1585,  1586,  1587,
    1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,
    1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,
    1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,
    1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,
    1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1644,
    1644,  1653,  1653,  1662,  1662,  1671,  1671,  1680,  1680,  1689,
    1689,  1699,  1699,  1710,  1710,  1721,  1727,  1733,  1739,  1747,
    1747,  1759,  1760,  1764,  1765,  1766,  1771,  1771,  1779,  1780,
    1781,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,
    1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,
    1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,
    1825,  1826,  1827,  1828,  1829,  1836,  1836,  1850,  1850,  1859,
    1860,  1863,  1864,  1865,  1872,  1872,  1887,  1887,  1901,  1902,
    1905,  1906,  1907,  1912,  1913,  1914,  1915,  1916,  1917,  1918,
    1919,  1920,  1921,  1924,  1926,  1932,  1934,  1934,  1943,  1943,
    1952,  1952,  1961,  1963,  1963,  1972,  1982,  1982,  1995,  1996,
    2001,  2002,  2003,  2010,  2010,  2022,  2022,  2034,  2035,  2040,
    2041,  2042,  2049,  2050,  2051,  2052,  2053,  2054,  2055,  2056,
    2057,  2058,  2059,  2062,  2064,  2064,  2073,  2075,  2077,  2083,
    2089,  2095,  2095,  2109,  2109,  2122,  2123,  2126,  2127,  2128,
    2133,  2133,  2143,  2143,  2153,  2154,  2155,  2160,  2161,  2162,
    2163,  2164,  2165,  2166,  2167,  2168,  2171,  2171,  2180,  2186,
    2186,  2211,  2211,  2241,  2241,  2252,  2253,  2256,  2257,  2258,
    2263,  2263,  2272,  2272,  2281,  2282,  2285,  2286,  2287,  2293,
    2294,  2295,  2296,  2297,  2298,  2299,  2300,  2301,  2302,  2303,
    2304,  2305,  2306,  2307,  2310,  2310,  2319,  2319,  2328,  2328,
    2337,  2337,  2346,  2346,  2355,  2355,  2364,  2364,  2373,  2373,
    2382,  2382,  2391,  2391,  2400,  2400,  2414,  2414,  2425,  2428,
    2428,  2442,  2442,  2453,  2454,  2455,  2460,  2460,  2470,  2471,
    2474,  2475,  2476,  2481,  2482,  2483,  2484,  2485,  2486,  2487,
    2488,  2489,  2490,  2491,  2492,  2493,  2494,  2495,  2496,  2497,
    2500,  2502,  2502,  2511,  2511,  2521,  2527,  2535,  2543,  2543,
    2555,  2555,  2567,  2568,  2571,  2572,  2573,  2578,  2578,  2586,
    2587,  2588,  2593,  2594,  2595,  2596,  2597,  2598,  2599,  2600,
    2601,  2602,  2603,  2604,  2607,  2607,  2616,  2617,  2618,  2621,
    2621,  2631,  2631,  2641,  2647,  2655,  2655,  2668,  2669,  2670,
    2675,  2676,  2677,  2678,  2679,  2680,  2681,  2684,  2684,  2692,
    2695,  2695,  2704,  2704,  2713,  2713,  2724,  2725,  2728,  2729,
    2730,  2735,  2735,  2743,  2744,  2745,  2750,  2751,  2752,  2753,
    2754,  2755,  2756,  2759,  2759,  2768,  2768,  2779,  2779,  2792,
    2793,  2794,  2799,  2800,  2801,  2802,  2803,  2804,  2807,  2813,
    2813,  2822,  2828,  2828,  2838,  2838,  2851,  2851,  2861,  2862,
    2863,  2868,  2869,  2870,  2871,  2872,  2873,  2874,  2875,  2876,
    2877,  2878,  2881,  2887,  2887,  2896,  2902,  2902,  2911,  2917,
    2923,  2923,  2932,  2933,  2936,  2936,  2947,  2947,  2959,  2959,
    2969,  2970,  2971,  2977,  2978,  2981,  2981,  2992,  3000,  3000,
    3013,  3014,  3015,  3021,  3021,  3029,  3030,  3031,  3036,  3037,
    3038,  3039,  3040,  3041,  3042,  3045,  3051,  3051,  3060,  3060,
    3071,  3072,  3073,  3078,  3078,  3086,  3087,  3088,  3093,  3094,
    3095,  3096,  3097,  3100,  3100,  3109,  3115,  3121,  3127,  3127,
    3136,  3136,  3147,  3148,  3149,  3154,  3155,  3156,  3157,  3158,
    3161,  3167,  3173,  3179
  };

  void
  Dhcp4Parser::yy_stack_print_ () const
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule) const
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 6732 "dhcp4_parser.cc"

#line 3185 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
