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
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 320 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 320 "dhcp4_parser.yy"
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
#line 329 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 330 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 331 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 332 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 333 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 334 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 335 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 336 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 337 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 338 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 339 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 340 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 341 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 349 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 350 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 351 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 352 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 353 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 354 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 355 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 358 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 363 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 368 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 374 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 381 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 386 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 392 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 397 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 400 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 408 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 412 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 416 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 422 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 424 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 433 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 437 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 441 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 451 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 460 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 465 "dhcp4_parser.yy"
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
#line 475 "dhcp4_parser.yy"
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
#line 484 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 492 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 498 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 502 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 509 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 590 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 596 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 602 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 608 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 614 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 620 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 626 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 632 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 638 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 644 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 650 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 153: // $@20: %empty
#line 656 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 154: // server_tag: "server-tag" $@20 ":" "constant string"
#line 659 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 155: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 665 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 156: // $@21: %empty
#line 671 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 157: // allocator: "allocator" $@21 ":" "constant string"
#line 674 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 158: // echo_client_id: "echo-client-id" ":" "boolean"
#line 680 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 159: // match_client_id: "match-client-id" ":" "boolean"
#line 686 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 160: // authoritative: "authoritative" ":" "boolean"
#line 692 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 161: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 698 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 162: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 704 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 163: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 710 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 164: // $@22: %empty
#line 716 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 719 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-present"
#line 725 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "never"
#line 728 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "always"
#line 731 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "when-not-present"
#line 734 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "boolean"
#line 737 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 171: // $@23: %empty
#line 743 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 172: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 746 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 173: // $@24: %empty
#line 752 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 174: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 755 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 175: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 761 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 176: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 770 "dhcp4_parser.yy"
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

  case 177: // $@25: %empty
#line 780 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 783 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 789 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 792 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 795 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 798 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 183: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 803 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 184: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 809 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1546 "dhcp4_parser.cc"
    break;

  case 185: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 815 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 186: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 821 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 187: // $@26: %empty
#line 827 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 188: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 830 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 189: // $@27: %empty
#line 836 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 190: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 839 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 191: // store_extended_info: "store-extended-info" ":" "boolean"
#line 845 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 192: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 851 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 193: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 857 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 863 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 869 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 875 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 197: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 881 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1674 "dhcp4_parser.cc"
    break;

  case 198: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 887 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 199: // $@28: %empty
#line 893 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1696 "dhcp4_parser.cc"
    break;

  case 200: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 899 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1706 "dhcp4_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 907 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1714 "dhcp4_parser.cc"
    break;

  case 214: // $@29: %empty
#line 924 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 215: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 928 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 216: // $@30: %empty
#line 933 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 217: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 939 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1754 "dhcp4_parser.cc"
    break;

  case 218: // $@31: %empty
#line 944 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 219: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 947 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 220: // socket_type: "raw"
#line 952 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1778 "dhcp4_parser.cc"
    break;

  case 221: // socket_type: "udp"
#line 953 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1784 "dhcp4_parser.cc"
    break;

  case 222: // $@32: %empty
#line 956 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1793 "dhcp4_parser.cc"
    break;

  case 223: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 959 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1802 "dhcp4_parser.cc"
    break;

  case 224: // outbound_interface_value: "same-as-inbound"
#line 964 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1810 "dhcp4_parser.cc"
    break;

  case 225: // outbound_interface_value: "use-routing"
#line 966 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1818 "dhcp4_parser.cc"
    break;

  case 226: // re_detect: "re-detect" ":" "boolean"
#line 970 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 227: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 976 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1838 "dhcp4_parser.cc"
    break;

  case 228: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 982 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1848 "dhcp4_parser.cc"
    break;

  case 229: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 988 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1858 "dhcp4_parser.cc"
    break;

  case 230: // $@33: %empty
#line 994 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 231: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 1000 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 232: // $@34: %empty
#line 1007 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1893 "dhcp4_parser.cc"
    break;

  case 233: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 1013 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc"
    break;

  case 236: // sanity_checks_params: sanity_checks_params ","
#line 1020 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1910 "dhcp4_parser.cc"
    break;

  case 239: // $@35: %empty
#line 1029 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 240: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1032 "dhcp4_parser.yy"
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
#line 1939 "dhcp4_parser.cc"
    break;

  case 241: // $@36: %empty
#line 1048 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1948 "dhcp4_parser.cc"
    break;

  case 242: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1051 "dhcp4_parser.yy"
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
#line 1967 "dhcp4_parser.cc"
    break;

  case 243: // $@37: %empty
#line 1066 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1979 "dhcp4_parser.cc"
    break;

  case 244: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1072 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1990 "dhcp4_parser.cc"
    break;

  case 245: // $@38: %empty
#line 1079 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2002 "dhcp4_parser.cc"
    break;

  case 246: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1085 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 251: // not_empty_database_list: not_empty_database_list ","
#line 1096 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2019 "dhcp4_parser.cc"
    break;

  case 252: // $@39: %empty
#line 1101 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 253: // database: "{" $@39 database_map_params "}"
#line 1105 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 256: // database_map_params: database_map_params ","
#line 1113 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2047 "dhcp4_parser.cc"
    break;

  case 280: // $@40: %empty
#line 1143 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 281: // database_type: "type" $@40 ":" "constant string"
#line 1146 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2066 "dhcp4_parser.cc"
    break;

  case 282: // $@41: %empty
#line 1152 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 283: // user: "user" $@41 ":" "constant string"
#line 1155 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 284: // $@42: %empty
#line 1161 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc"
    break;

  case 285: // password: "password" $@42 ":" "constant string"
#line 1164 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 286: // $@43: %empty
#line 1170 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2113 "dhcp4_parser.cc"
    break;

  case 287: // host: "host" $@43 ":" "constant string"
#line 1173 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc"
    break;

  case 288: // port: "port" ":" "integer"
#line 1179 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2133 "dhcp4_parser.cc"
    break;

  case 289: // $@44: %empty
#line 1185 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 290: // name: "name" $@44 ":" "constant string"
#line 1188 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 291: // persist: "persist" ":" "boolean"
#line 1194 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2162 "dhcp4_parser.cc"
    break;

  case 292: // lfc_interval: "lfc-interval" ":" "integer"
#line 1200 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 293: // readonly: "readonly" ":" "boolean"
#line 1206 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 294: // connect_timeout: "connect-timeout" ":" "integer"
#line 1212 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 295: // read_timeout: "read-timeout" ":" "integer"
#line 1218 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 296: // write_timeout: "write-timeout" ":" "integer"
#line 1224 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 297: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1230 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 298: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1236 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 299: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1242 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 300: // $@45: %empty
#line 1248 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 301: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1251 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 302: // on_fail_mode: "stop-retry-exit"
#line 1256 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2266 "dhcp4_parser.cc"
    break;

  case 303: // on_fail_mode: "serve-retry-exit"
#line 1257 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2272 "dhcp4_parser.cc"
    break;

  case 304: // on_fail_mode: "serve-retry-continue"
#line 1258 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2278 "dhcp4_parser.cc"
    break;

  case 305: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1261 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2288 "dhcp4_parser.cc"
    break;

  case 306: // max_row_errors: "max-row-errors" ":" "integer"
#line 1267 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2298 "dhcp4_parser.cc"
    break;

  case 307: // $@46: %empty
#line 1273 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 308: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1276 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 309: // $@47: %empty
#line 1282 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp4_parser.cc"
    break;

  case 310: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1285 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2336 "dhcp4_parser.cc"
    break;

  case 311: // $@48: %empty
#line 1291 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2345 "dhcp4_parser.cc"
    break;

  case 312: // key_file: "key-file" $@48 ":" "constant string"
#line 1294 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2355 "dhcp4_parser.cc"
    break;

  case 313: // $@49: %empty
#line 1300 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp4_parser.cc"
    break;

  case 314: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1303 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2374 "dhcp4_parser.cc"
    break;

  case 315: // $@50: %empty
#line 1309 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 316: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1315 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 319: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1322 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2403 "dhcp4_parser.cc"
    break;

  case 325: // duid_id: "duid"
#line 1334 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2412 "dhcp4_parser.cc"
    break;

  case 326: // hw_address_id: "hw-address"
#line 1339 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2421 "dhcp4_parser.cc"
    break;

  case 327: // circuit_id: "circuit-id"
#line 1344 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 328: // client_id: "client-id"
#line 1349 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2439 "dhcp4_parser.cc"
    break;

  case 329: // flex_id: "flex-id"
#line 1354 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2448 "dhcp4_parser.cc"
    break;

  case 330: // $@51: %empty
#line 1361 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2460 "dhcp4_parser.cc"
    break;

  case 331: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1367 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2471 "dhcp4_parser.cc"
    break;

  case 334: // multi_threading_params: multi_threading_params ","
#line 1376 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2479 "dhcp4_parser.cc"
    break;

  case 341: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1389 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2489 "dhcp4_parser.cc"
    break;

  case 342: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1395 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2499 "dhcp4_parser.cc"
    break;

  case 343: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1401 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2509 "dhcp4_parser.cc"
    break;

  case 344: // $@52: %empty
#line 1407 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 345: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1413 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 350: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1424 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2538 "dhcp4_parser.cc"
    break;

  case 351: // $@53: %empty
#line 1429 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 352: // hooks_library: "{" $@53 hooks_params "}"
#line 1433 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 353: // $@54: %empty
#line 1439 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 354: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1443 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2578 "dhcp4_parser.cc"
    break;

  case 357: // hooks_params: hooks_params ","
#line 1451 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2586 "dhcp4_parser.cc"
    break;

  case 361: // $@55: %empty
#line 1461 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 362: // library: "library" $@55 ":" "constant string"
#line 1464 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 363: // $@56: %empty
#line 1470 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2614 "dhcp4_parser.cc"
    break;

  case 364: // parameters: "parameters" $@56 ":" map_value
#line 1473 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2623 "dhcp4_parser.cc"
    break;

  case 365: // $@57: %empty
#line 1479 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2635 "dhcp4_parser.cc"
    break;

  case 366: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1485 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 369: // expired_leases_params: expired_leases_params ","
#line 1493 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2653 "dhcp4_parser.cc"
    break;

  case 376: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1506 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 377: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1512 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 378: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1518 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 379: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1524 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 380: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1530 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2703 "dhcp4_parser.cc"
    break;

  case 381: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1536 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2713 "dhcp4_parser.cc"
    break;

  case 382: // $@58: %empty
#line 1545 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2725 "dhcp4_parser.cc"
    break;

  case 383: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1551 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2734 "dhcp4_parser.cc"
    break;

  case 388: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1565 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2742 "dhcp4_parser.cc"
    break;

  case 389: // $@59: %empty
#line 1574 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 390: // subnet4: "{" $@59 subnet4_params "}"
#line 1578 "dhcp4_parser.yy"
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
#line 2778 "dhcp4_parser.cc"
    break;

  case 391: // $@60: %empty
#line 1600 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2788 "dhcp4_parser.cc"
    break;

  case 392: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1604 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2798 "dhcp4_parser.cc"
    break;

  case 395: // subnet4_params: subnet4_params ","
#line 1613 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2806 "dhcp4_parser.cc"
    break;

  case 449: // $@61: %empty
#line 1674 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2815 "dhcp4_parser.cc"
    break;

  case 450: // subnet: "subnet" $@61 ":" "constant string"
#line 1677 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2825 "dhcp4_parser.cc"
    break;

  case 451: // $@62: %empty
#line 1683 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2834 "dhcp4_parser.cc"
    break;

  case 452: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1686 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc"
    break;

  case 453: // $@63: %empty
#line 1692 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp4_parser.cc"
    break;

  case 454: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1695 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 455: // $@64: %empty
#line 1701 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 456: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1704 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2882 "dhcp4_parser.cc"
    break;

  case 457: // $@65: %empty
#line 1710 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 458: // interface: "interface" $@65 ":" "constant string"
#line 1713 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2901 "dhcp4_parser.cc"
    break;

  case 459: // $@66: %empty
#line 1719 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 460: // client_class: "client-class" $@66 ":" "constant string"
#line 1722 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 461: // $@67: %empty
#line 1729 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 462: // network_client_classes: "client-classes" $@67 ":" list_strings
#line 1735 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 463: // $@68: %empty
#line 1741 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2953 "dhcp4_parser.cc"
    break;

  case 464: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1747 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 465: // $@69: %empty
#line 1752 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2974 "dhcp4_parser.cc"
    break;

  case 466: // evaluate_additional_classes: "evaluate-additional-classes" $@69 ":" list_strings
#line 1758 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2983 "dhcp4_parser.cc"
    break;

  case 467: // reservations_global: "reservations-global" ":" "boolean"
#line 1763 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 468: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1769 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3003 "dhcp4_parser.cc"
    break;

  case 469: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1775 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3013 "dhcp4_parser.cc"
    break;

  case 470: // id: "id" ":" "integer"
#line 1781 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3023 "dhcp4_parser.cc"
    break;

  case 471: // $@70: %empty
#line 1789 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3035 "dhcp4_parser.cc"
    break;

  case 472: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1795 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 477: // shared_networks_list: shared_networks_list ","
#line 1808 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3052 "dhcp4_parser.cc"
    break;

  case 478: // $@71: %empty
#line 1813 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 479: // shared_network: "{" $@71 shared_network_params "}"
#line 1817 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 482: // shared_network_params: shared_network_params ","
#line 1823 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3078 "dhcp4_parser.cc"
    break;

  case 531: // $@72: %empty
#line 1882 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 532: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1888 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 533: // $@73: %empty
#line 1896 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3108 "dhcp4_parser.cc"
    break;

  case 534: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1899 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3116 "dhcp4_parser.cc"
    break;

  case 539: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1911 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3124 "dhcp4_parser.cc"
    break;

  case 540: // $@74: %empty
#line 1918 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3134 "dhcp4_parser.cc"
    break;

  case 541: // option_def_entry: "{" $@74 option_def_params "}"
#line 1922 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3146 "dhcp4_parser.cc"
    break;

  case 542: // $@75: %empty
#line 1933 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 543: // sub_option_def: "{" $@75 option_def_params "}"
#line 1937 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3168 "dhcp4_parser.cc"
    break;

  case 548: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1953 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3176 "dhcp4_parser.cc"
    break;

  case 560: // code: "code" ":" "integer"
#line 1972 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 562: // $@76: %empty
#line 1980 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp4_parser.cc"
    break;

  case 563: // option_def_type: "type" $@76 ":" "constant string"
#line 1983 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 564: // $@77: %empty
#line 1989 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 565: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1992 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3224 "dhcp4_parser.cc"
    break;

  case 566: // $@78: %empty
#line 1998 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 567: // space: "space" $@78 ":" "constant string"
#line 2001 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 569: // $@79: %empty
#line 2009 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3252 "dhcp4_parser.cc"
    break;

  case 570: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 2012 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3262 "dhcp4_parser.cc"
    break;

  case 571: // option_def_array: "array" ":" "boolean"
#line 2018 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3272 "dhcp4_parser.cc"
    break;

  case 572: // $@80: %empty
#line 2028 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 573: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 2034 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 578: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2049 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3301 "dhcp4_parser.cc"
    break;

  case 579: // $@81: %empty
#line 2056 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 580: // option_data_entry: "{" $@81 option_data_params "}"
#line 2060 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 581: // $@82: %empty
#line 2068 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 582: // sub_option_data: "{" $@82 option_data_params "}"
#line 2072 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3339 "dhcp4_parser.cc"
    break;

  case 587: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2088 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3347 "dhcp4_parser.cc"
    break;

  case 600: // $@83: %empty
#line 2110 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3356 "dhcp4_parser.cc"
    break;

  case 601: // option_data_data: "data" $@83 ":" "constant string"
#line 2113 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 604: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2123 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3376 "dhcp4_parser.cc"
    break;

  case 605: // option_data_always_send: "always-send" ":" "boolean"
#line 2129 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3386 "dhcp4_parser.cc"
    break;

  case 606: // option_data_never_send: "never-send" ":" "boolean"
#line 2135 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3396 "dhcp4_parser.cc"
    break;

  case 607: // $@84: %empty
#line 2141 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 608: // option_data_client_classes: "client-classes" $@84 ":" list_strings
#line 2147 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3417 "dhcp4_parser.cc"
    break;

  case 609: // $@85: %empty
#line 2155 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3429 "dhcp4_parser.cc"
    break;

  case 610: // pools_list: "pools" $@85 ":" "[" pools_list_content "]"
#line 2161 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3438 "dhcp4_parser.cc"
    break;

  case 615: // not_empty_pools_list: not_empty_pools_list ","
#line 2174 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3446 "dhcp4_parser.cc"
    break;

  case 616: // $@86: %empty
#line 2179 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3456 "dhcp4_parser.cc"
    break;

  case 617: // pool_list_entry: "{" $@86 pool_params "}"
#line 2183 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3466 "dhcp4_parser.cc"
    break;

  case 618: // $@87: %empty
#line 2189 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3476 "dhcp4_parser.cc"
    break;

  case 619: // sub_pool4: "{" $@87 pool_params "}"
#line 2193 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3486 "dhcp4_parser.cc"
    break;

  case 622: // pool_params: pool_params ","
#line 2201 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3494 "dhcp4_parser.cc"
    break;

  case 633: // $@88: %empty
#line 2218 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 634: // pool_entry: "pool" $@88 ":" "constant string"
#line 2221 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3513 "dhcp4_parser.cc"
    break;

  case 635: // pool_id: "pool-id" ":" "integer"
#line 2227 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 636: // $@89: %empty
#line 2233 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3531 "dhcp4_parser.cc"
    break;

  case 637: // user_context: "user-context" $@89 ":" map_value
#line 2235 "dhcp4_parser.yy"
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
#line 3558 "dhcp4_parser.cc"
    break;

  case 638: // $@90: %empty
#line 2258 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3566 "dhcp4_parser.cc"
    break;

  case 639: // comment: "comment" $@90 ":" "constant string"
#line 2260 "dhcp4_parser.yy"
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
#line 3595 "dhcp4_parser.cc"
    break;

  case 640: // $@91: %empty
#line 2288 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 641: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2294 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3616 "dhcp4_parser.cc"
    break;

  case 646: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2305 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3624 "dhcp4_parser.cc"
    break;

  case 647: // $@92: %empty
#line 2310 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3634 "dhcp4_parser.cc"
    break;

  case 648: // reservation: "{" $@92 reservation_params "}"
#line 2314 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 649: // $@93: %empty
#line 2319 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 650: // sub_reservation: "{" $@93 reservation_params "}"
#line 2323 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3662 "dhcp4_parser.cc"
    break;

  case 655: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2334 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3670 "dhcp4_parser.cc"
    break;

  case 671: // $@94: %empty
#line 2357 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 672: // next_server: "next-server" $@94 ":" "constant string"
#line 2360 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 673: // $@95: %empty
#line 2366 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3698 "dhcp4_parser.cc"
    break;

  case 674: // server_hostname: "server-hostname" $@95 ":" "constant string"
#line 2369 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 675: // $@96: %empty
#line 2375 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 676: // boot_file_name: "boot-file-name" $@96 ":" "constant string"
#line 2378 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3727 "dhcp4_parser.cc"
    break;

  case 677: // $@97: %empty
#line 2384 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3736 "dhcp4_parser.cc"
    break;

  case 678: // ip_address: "ip-address" $@97 ":" "constant string"
#line 2387 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3746 "dhcp4_parser.cc"
    break;

  case 679: // $@98: %empty
#line 2393 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3755 "dhcp4_parser.cc"
    break;

  case 680: // duid: "duid" $@98 ":" "constant string"
#line 2396 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3765 "dhcp4_parser.cc"
    break;

  case 681: // $@99: %empty
#line 2402 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3774 "dhcp4_parser.cc"
    break;

  case 682: // hw_address: "hw-address" $@99 ":" "constant string"
#line 2405 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3784 "dhcp4_parser.cc"
    break;

  case 683: // $@100: %empty
#line 2411 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3793 "dhcp4_parser.cc"
    break;

  case 684: // client_id_value: "client-id" $@100 ":" "constant string"
#line 2414 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3803 "dhcp4_parser.cc"
    break;

  case 685: // $@101: %empty
#line 2420 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3812 "dhcp4_parser.cc"
    break;

  case 686: // circuit_id_value: "circuit-id" $@101 ":" "constant string"
#line 2423 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3822 "dhcp4_parser.cc"
    break;

  case 687: // $@102: %empty
#line 2429 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3831 "dhcp4_parser.cc"
    break;

  case 688: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2432 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3841 "dhcp4_parser.cc"
    break;

  case 689: // $@103: %empty
#line 2438 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3850 "dhcp4_parser.cc"
    break;

  case 690: // hostname: "hostname" $@103 ":" "constant string"
#line 2441 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3860 "dhcp4_parser.cc"
    break;

  case 691: // $@104: %empty
#line 2447 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 692: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2453 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 693: // $@105: %empty
#line 2461 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 694: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2467 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3902 "dhcp4_parser.cc"
    break;

  case 696: // $@106: %empty
#line 2475 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3914 "dhcp4_parser.cc"
    break;

  case 697: // ip_addresses: "ip-addresses" $@106 ":" list_strings
#line 2481 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3923 "dhcp4_parser.cc"
    break;

  case 698: // $@107: %empty
#line 2489 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3935 "dhcp4_parser.cc"
    break;

  case 699: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2495 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3944 "dhcp4_parser.cc"
    break;

  case 702: // client_classes_list: client_classes_list ","
#line 2502 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3952 "dhcp4_parser.cc"
    break;

  case 703: // $@108: %empty
#line 2507 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3962 "dhcp4_parser.cc"
    break;

  case 704: // client_class_entry: "{" $@108 client_class_params "}"
#line 2511 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3972 "dhcp4_parser.cc"
    break;

  case 709: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2523 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3980 "dhcp4_parser.cc"
    break;

  case 728: // $@109: %empty
#line 2549 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 729: // client_class_test: "test" $@109 ":" "constant string"
#line 2552 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 730: // $@110: %empty
#line 2558 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4008 "dhcp4_parser.cc"
    break;

  case 731: // client_class_template_test: "template-test" $@110 ":" "constant string"
#line 2561 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 732: // only_if_required: "only-if-required" ":" "boolean"
#line 2568 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4028 "dhcp4_parser.cc"
    break;

  case 733: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2574 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 734: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2582 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4048 "dhcp4_parser.cc"
    break;

  case 735: // $@111: %empty
#line 2590 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4061 "dhcp4_parser.cc"
    break;

  case 736: // control_socket: "control-socket" $@111 ":" "{" control_socket_params "}"
#line 2597 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4070 "dhcp4_parser.cc"
    break;

  case 737: // $@112: %empty
#line 2602 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4083 "dhcp4_parser.cc"
    break;

  case 738: // control_sockets: "control-sockets" $@112 ":" "[" control_socket_list "]"
#line 2609 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 743: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2620 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4100 "dhcp4_parser.cc"
    break;

  case 744: // $@113: %empty
#line 2625 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4110 "dhcp4_parser.cc"
    break;

  case 745: // control_socket_entry: "{" $@113 control_socket_params "}"
#line 2629 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4118 "dhcp4_parser.cc"
    break;

  case 748: // control_socket_params: control_socket_params ","
#line 2635 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4126 "dhcp4_parser.cc"
    break;

  case 762: // $@114: %empty
#line 2655 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4135 "dhcp4_parser.cc"
    break;

  case 763: // control_socket_type: "socket-type" $@114 ":" control_socket_type_value
#line 2658 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4144 "dhcp4_parser.cc"
    break;

  case 764: // control_socket_type_value: "unix"
#line 2664 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4150 "dhcp4_parser.cc"
    break;

  case 765: // control_socket_type_value: "http"
#line 2665 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4156 "dhcp4_parser.cc"
    break;

  case 766: // control_socket_type_value: "https"
#line 2666 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4162 "dhcp4_parser.cc"
    break;

  case 767: // $@115: %empty
#line 2669 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4172 "dhcp4_parser.cc"
    break;

  case 768: // control_socket_name: "socket-name" $@115 ":" "constant string"
#line 2673 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 769: // $@116: %empty
#line 2679 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 770: // control_socket_address: "socket-address" $@116 ":" "constant string"
#line 2683 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 771: // control_socket_port: "socket-port" ":" "integer"
#line 2689 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 772: // cert_required: "cert-required" ":" "boolean"
#line 2695 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4222 "dhcp4_parser.cc"
    break;

  case 773: // $@117: %empty
#line 2701 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 774: // http_headers: "http-headers" $@117 ":" "[" http_header_list "]"
#line 2707 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4243 "dhcp4_parser.cc"
    break;

  case 779: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2718 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4251 "dhcp4_parser.cc"
    break;

  case 780: // $@118: %empty
#line 2723 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4261 "dhcp4_parser.cc"
    break;

  case 781: // http_header: "{" $@118 http_header_params "}"
#line 2727 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4269 "dhcp4_parser.cc"
    break;

  case 784: // http_header_params: http_header_params ","
#line 2733 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4277 "dhcp4_parser.cc"
    break;

  case 790: // $@119: %empty
#line 2745 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4286 "dhcp4_parser.cc"
    break;

  case 791: // header_value: "value" $@119 ":" "constant string"
#line 2748 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4296 "dhcp4_parser.cc"
    break;

  case 792: // $@120: %empty
#line 2756 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4308 "dhcp4_parser.cc"
    break;

  case 793: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2762 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4319 "dhcp4_parser.cc"
    break;

  case 796: // auth_params: auth_params ","
#line 2771 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4327 "dhcp4_parser.cc"
    break;

  case 804: // $@121: %empty
#line 2785 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4336 "dhcp4_parser.cc"
    break;

  case 805: // auth_type: "type" $@121 ":" auth_type_value
#line 2788 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4345 "dhcp4_parser.cc"
    break;

  case 806: // auth_type_value: "basic"
#line 2793 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4351 "dhcp4_parser.cc"
    break;

  case 807: // $@122: %empty
#line 2796 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4360 "dhcp4_parser.cc"
    break;

  case 808: // realm: "realm" $@122 ":" "constant string"
#line 2799 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4370 "dhcp4_parser.cc"
    break;

  case 809: // $@123: %empty
#line 2805 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4379 "dhcp4_parser.cc"
    break;

  case 810: // directory: "directory" $@123 ":" "constant string"
#line 2808 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4389 "dhcp4_parser.cc"
    break;

  case 811: // $@124: %empty
#line 2814 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 812: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2820 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4410 "dhcp4_parser.cc"
    break;

  case 817: // not_empty_clients_list: not_empty_clients_list ","
#line 2831 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4418 "dhcp4_parser.cc"
    break;

  case 818: // $@125: %empty
#line 2836 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4428 "dhcp4_parser.cc"
    break;

  case 819: // basic_auth: "{" $@125 clients_params "}"
#line 2840 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 822: // clients_params: clients_params ","
#line 2846 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4444 "dhcp4_parser.cc"
    break;

  case 830: // $@126: %empty
#line 2860 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 831: // user_file: "user-file" $@126 ":" "constant string"
#line 2863 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 832: // $@127: %empty
#line 2869 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4472 "dhcp4_parser.cc"
    break;

  case 833: // password_file: "password-file" $@127 ":" "constant string"
#line 2872 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 834: // $@128: %empty
#line 2880 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4494 "dhcp4_parser.cc"
    break;

  case 835: // dhcp_queue_control: "dhcp-queue-control" $@128 ":" "{" queue_control_params "}"
#line 2886 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 838: // queue_control_params: queue_control_params ","
#line 2895 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4513 "dhcp4_parser.cc"
    break;

  case 845: // enable_queue: "enable-queue" ":" "boolean"
#line 2908 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4523 "dhcp4_parser.cc"
    break;

  case 846: // $@129: %empty
#line 2914 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 847: // queue_type: "queue-type" $@129 ":" "constant string"
#line 2917 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 848: // capacity: "capacity" ":" "integer"
#line 2923 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 849: // $@130: %empty
#line 2929 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 850: // arbitrary_map_entry: "constant string" $@130 ":" value
#line 2932 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4570 "dhcp4_parser.cc"
    break;

  case 851: // $@131: %empty
#line 2939 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4582 "dhcp4_parser.cc"
    break;

  case 852: // dhcp_ddns: "dhcp-ddns" $@131 ":" "{" dhcp_ddns_params "}"
#line 2945 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4593 "dhcp4_parser.cc"
    break;

  case 853: // $@132: %empty
#line 2952 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4603 "dhcp4_parser.cc"
    break;

  case 854: // sub_dhcp_ddns: "{" $@132 dhcp_ddns_params "}"
#line 2956 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4613 "dhcp4_parser.cc"
    break;

  case 857: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2964 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4621 "dhcp4_parser.cc"
    break;

  case 869: // enable_updates: "enable-updates" ":" "boolean"
#line 2982 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4631 "dhcp4_parser.cc"
    break;

  case 870: // $@133: %empty
#line 2988 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4640 "dhcp4_parser.cc"
    break;

  case 871: // server_ip: "server-ip" $@133 ":" "constant string"
#line 2991 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4650 "dhcp4_parser.cc"
    break;

  case 872: // server_port: "server-port" ":" "integer"
#line 2997 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4660 "dhcp4_parser.cc"
    break;

  case 873: // $@134: %empty
#line 3003 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4669 "dhcp4_parser.cc"
    break;

  case 874: // sender_ip: "sender-ip" $@134 ":" "constant string"
#line 3006 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4679 "dhcp4_parser.cc"
    break;

  case 875: // sender_port: "sender-port" ":" "integer"
#line 3012 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4689 "dhcp4_parser.cc"
    break;

  case 876: // max_queue_size: "max-queue-size" ":" "integer"
#line 3018 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4699 "dhcp4_parser.cc"
    break;

  case 877: // $@135: %empty
#line 3024 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 878: // ncr_protocol: "ncr-protocol" $@135 ":" ncr_protocol_value
#line 3027 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4717 "dhcp4_parser.cc"
    break;

  case 879: // ncr_protocol_value: "udp"
#line 3033 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4723 "dhcp4_parser.cc"
    break;

  case 880: // ncr_protocol_value: "tcp"
#line 3034 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4729 "dhcp4_parser.cc"
    break;

  case 881: // $@136: %empty
#line 3037 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4738 "dhcp4_parser.cc"
    break;

  case 882: // ncr_format: "ncr-format" $@136 ":" "JSON"
#line 3040 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4748 "dhcp4_parser.cc"
    break;

  case 883: // $@137: %empty
#line 3048 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4760 "dhcp4_parser.cc"
    break;

  case 884: // config_control: "config-control" $@137 ":" "{" config_control_params "}"
#line 3054 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4770 "dhcp4_parser.cc"
    break;

  case 885: // $@138: %empty
#line 3060 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4780 "dhcp4_parser.cc"
    break;

  case 886: // sub_config_control: "{" $@138 config_control_params "}"
#line 3064 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4789 "dhcp4_parser.cc"
    break;

  case 889: // config_control_params: config_control_params ","
#line 3072 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4797 "dhcp4_parser.cc"
    break;

  case 892: // $@139: %empty
#line 3082 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4809 "dhcp4_parser.cc"
    break;

  case 893: // config_databases: "config-databases" $@139 ":" "[" database_list "]"
#line 3088 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4818 "dhcp4_parser.cc"
    break;

  case 894: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3093 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4828 "dhcp4_parser.cc"
    break;

  case 895: // $@140: %empty
#line 3101 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4840 "dhcp4_parser.cc"
    break;

  case 896: // loggers: "loggers" $@140 ":" "[" loggers_entries "]"
#line 3107 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4849 "dhcp4_parser.cc"
    break;

  case 899: // loggers_entries: loggers_entries ","
#line 3116 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4857 "dhcp4_parser.cc"
    break;

  case 900: // $@141: %empty
#line 3122 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4867 "dhcp4_parser.cc"
    break;

  case 901: // logger_entry: "{" $@141 logger_params "}"
#line 3126 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4875 "dhcp4_parser.cc"
    break;

  case 904: // logger_params: logger_params ","
#line 3132 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4883 "dhcp4_parser.cc"
    break;

  case 912: // debuglevel: "debuglevel" ":" "integer"
#line 3146 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4893 "dhcp4_parser.cc"
    break;

  case 913: // $@142: %empty
#line 3152 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4902 "dhcp4_parser.cc"
    break;

  case 914: // severity: "severity" $@142 ":" "constant string"
#line 3155 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4912 "dhcp4_parser.cc"
    break;

  case 915: // $@143: %empty
#line 3161 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4924 "dhcp4_parser.cc"
    break;

  case 916: // output_options_list: "output-options" $@143 ":" "[" output_options_list_content "]"
#line 3167 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4933 "dhcp4_parser.cc"
    break;

  case 919: // output_options_list_content: output_options_list_content ","
#line 3174 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4941 "dhcp4_parser.cc"
    break;

  case 920: // $@144: %empty
#line 3179 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4951 "dhcp4_parser.cc"
    break;

  case 921: // output_entry: "{" $@144 output_params_list "}"
#line 3183 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4959 "dhcp4_parser.cc"
    break;

  case 924: // output_params_list: output_params_list ","
#line 3189 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4967 "dhcp4_parser.cc"
    break;

  case 930: // $@145: %empty
#line 3201 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4976 "dhcp4_parser.cc"
    break;

  case 931: // output: "output" $@145 ":" "constant string"
#line 3204 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4986 "dhcp4_parser.cc"
    break;

  case 932: // flush: "flush" ":" "boolean"
#line 3210 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4996 "dhcp4_parser.cc"
    break;

  case 933: // maxsize: "maxsize" ":" "integer"
#line 3216 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5006 "dhcp4_parser.cc"
    break;

  case 934: // maxver: "maxver" ":" "integer"
#line 3222 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5016 "dhcp4_parser.cc"
    break;

  case 935: // $@146: %empty
#line 3228 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5025 "dhcp4_parser.cc"
    break;

  case 936: // pattern: "pattern" $@146 ":" "constant string"
#line 3231 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5035 "dhcp4_parser.cc"
    break;

  case 937: // $@147: %empty
#line 3237 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5047 "dhcp4_parser.cc"
    break;

  case 938: // compatibility: "compatibility" $@147 ":" "{" compatibility_params "}"
#line 3243 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5056 "dhcp4_parser.cc"
    break;

  case 941: // compatibility_params: compatibility_params ","
#line 3250 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5064 "dhcp4_parser.cc"
    break;

  case 947: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3262 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5074 "dhcp4_parser.cc"
    break;

  case 948: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3268 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5084 "dhcp4_parser.cc"
    break;

  case 949: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3274 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5094 "dhcp4_parser.cc"
    break;

  case 950: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3280 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5104 "dhcp4_parser.cc"
    break;


#line 5108 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1393;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     664, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,    57,    39,    83,   123,   129,   133,
     140,   142,   153,   169,   175,   199,   201,   211, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,    39,  -147,    95,   166,    72,   713,
     536,   581,    -2,   238,   558,   -96,   574,    68, -1393,   105,
     190,   225,   252,   255, -1393,    46, -1393, -1393, -1393, -1393,
     308,   309,   321, -1393, -1393, -1393,   325,   342, -1393, -1393,
   -1393,   359,   369,   376,   379,   390,   413,   424,   425,   427,
     442,   443, -1393,   465,   466,   469,   479,   481, -1393, -1393,
   -1393,   484,   485,   487,   488,   489,   491,   492, -1393, -1393,
   -1393,   495, -1393, -1393, -1393, -1393, -1393,   497,   499,   502,
   -1393, -1393, -1393, -1393, -1393,   504, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,   508,   511,   514, -1393, -1393,   515, -1393,
      52, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393,   517,   518,   520,   522,
   -1393,   111, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   523, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393,   118, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
     528, -1393, -1393, -1393, -1393, -1393, -1393,   119, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393,   271,   388, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   525,
   -1393, -1393,   530, -1393, -1393, -1393,   532, -1393, -1393,   529,
     535, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   537,   538,   540, -1393, -1393, -1393,
   -1393, -1393,   531,   543, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   121, -1393,
   -1393, -1393,   544, -1393,   550, -1393,   552,   555, -1393, -1393,
   -1393, -1393, -1393,   134, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   557,   136, -1393, -1393, -1393, -1393,
      39,    39, -1393,   132,   559, -1393, -1393,   560,   561,   562,
     329,   334,   335,   565,   567,   570,   347,   343,   575,   576,
     577,   351,   356,   357,   360,   361,   362,   365,   367,   368,
     363,   371,   585,   372,   374,   377,   389,   392,   603,   605,
     608,   394,   397,   401,   404,   406,   407,   410,   616,   636,
     641,   416,   644,   645,   646,   647,   662,   435,   438,   440,
     670,   674,   675,   676,   677,   451,   679,   681,   682,   683,
     684,   685,   689,   461,   462,   463,   693,   696, -1393,   166,
   -1393,   697,   700,   701,   475,   476,   480,   482,    72, -1393,
     708,   710,   711,   712,   720,   723,   500,   726,   728,   729,
     730,   731,   713, -1393,   732,   507,   536, -1393,   735,   736,
     737,   738,   745,   746,   747,   748, -1393,   581, -1393,   749,
     750,   524,   752,   753,   763,   541, -1393,   238,   764,   554,
     556,   579,   765, -1393,   558,   766,   767,   139, -1393,   580,
     786,   583,   804,   584,   586,   806,   812,   574, -1393,   814,
     588,    68, -1393, -1393, -1393,   816,   818,   819,   820,   822,
   -1393, -1393, -1393,   593,   594,   612, -1393, -1393,   831,   836,
     839, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,   615, -1393, -1393, -1393, -1393, -1393,  -127,   617,
     619, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   845,   846,
     847, -1393,   623,   345,   849,   848,   642, -1393, -1393, -1393,
     868,   869,   889,   890,   891, -1393,   892,   893,   896,   895,
     897,   666,   667, -1393, -1393, -1393,   898,   899, -1393,   900,
     250,   285, -1393, -1393, -1393, -1393, -1393,   678,   680,   686,
     902,   687,   688, -1393,   900,   900,   900,   690,   906, -1393,
     691, -1393, -1393,   900,   692,   694,   695,   698,   699,   702,
     703, -1393,   704,   705, -1393,   706,   707,   709, -1393, -1393,
     714, -1393, -1393, -1393,   900, -1393,   715,   848, -1393, -1393,
     716, -1393,   717, -1393, -1393,    18,   722, -1393,   904, -1393,
   -1393,    39,   166,    68,    72,   326, -1393, -1393, -1393,   817,
     817,   912, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393,   916,   919,   920, -1393, -1393, -1393, -1393, -1393, -1393,
     923, -1393, -1393, -1393,   237,   924,   931,   933,   248,   200,
      47,   934,   230,   574, -1393, -1393,   935,   -98, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   941,
   -1393, -1393, -1393, -1393, -1393, -1393,   805, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393,   912, -1393,   154,   164,   167, -1393, -1393,   171, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393,   946,   947,   948,   949,
     950,   951,   952,   953,   954,   955, -1393,   956,   957, -1393,
   -1393, -1393, -1393, -1393,   180, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   204, -1393,
     958,   959, -1393, -1393,   960,   962, -1393, -1393,   961,   965,
   -1393, -1393,   963,   967, -1393, -1393,   966,   968, -1393, -1393,
   -1393, -1393, -1393, -1393,    55, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,    86, -1393, -1393,   969,   970, -1393, -1393,   971,
     975, -1393,   976,   977,   980,   984,   987,   988,   214, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393,   994,   996,   997, -1393,
     217, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
     999, -1393,  1002, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
     218, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
    1001,  1011, -1393,  1014, -1393,  1020, -1393, -1393, -1393,   256,
   -1393, -1393, -1393, -1393, -1393,   273, -1393,    98, -1393,  1023,
    1025,  1028,  1033, -1393,   279, -1393, -1393, -1393, -1393, -1393,
     733, -1393,  1034,  1038, -1393, -1393,  1040, -1393,  1055, -1393,
   -1393, -1393,  1058,  1060,   326, -1393,  1065,  1066,  1067,  1073,
     743,   871,   851,   877,   907,   917,   922,   926,   927,   928,
    1075,   929,   930,  1146,  1151,  1156,  1159,   817, -1393, -1393,
     817, -1393,   912,   713, -1393,   916,   238, -1393,   919,   558,
   -1393,   920,   354, -1393,   923,   237, -1393,   275,   924, -1393,
     581, -1393,   931,   -96, -1393,   933,   936,   937,   938,   939,
     940,   942,   248, -1393,   932,   943,   944,   200, -1393,  1160,
    1162,  1168,   945,  1173,   964,  1174,    47, -1393,    47, -1393,
     934,   972,  1175,   973,  1176,   230, -1393, -1393,   -52,   935,
   -1393,   974,   978,   979,   981,   -98, -1393, -1393,  1177,  1179,
     536, -1393,   941,  1180, -1393, -1393,   983,   985, -1393,   986,
     989,   990,   991, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,   358, -1393, -1393,   992,   993,   995,   998,
   -1393,   290, -1393,   291, -1393,  1178, -1393,  1181, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
     292, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,  1183,  1184, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,  1182,  1188,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393,  1185, -1393,   312,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,   302,  1000,  1003, -1393,  1187, -1393,  1190, -1393,
     316, -1393, -1393,  1004, -1393,    39, -1393, -1393,  1194, -1393,
   -1393, -1393, -1393, -1393,   320, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393,  1006,   387, -1393,   900,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   354, -1393,
    1195,  1196,  1007,  1008, -1393,   275, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   179,  1199, -1393, -1393, -1393,  1197,
    1012,  1198,   -52, -1393, -1393, -1393, -1393, -1393,  1009,  1016,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
     400, -1393, -1393, -1393, -1393, -1393, -1393,  1186,  1200, -1393,
    1203, -1393,  1018, -1393, -1393, -1393,  1205,  1206,  1213,  1214,
     179, -1393,   -19, -1393,  1199,  1217, -1393,  1015,  1019,  1021,
    1221, -1393, -1393, -1393, -1393, -1393, -1393,   445, -1393, -1393,
   -1393, -1393,   188, -1393, -1393, -1393, -1393, -1393,  1220,  1225,
     -19, -1393,   -24,  1217, -1393, -1393,  1226,  1234, -1393,  1022,
   -1393, -1393,  1240,  1249,  1252, -1393,   446, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   186, -1393,  1220, -1393,  1254,  1027,
    1031,  1032,  1260,   -24, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,   456, -1393, -1393, -1393, -1393,  1035, -1393, -1393,
   -1393,  1037, -1393,  1264,  1267,   186, -1393, -1393, -1393,  1044,
    1045, -1393, -1393, -1393
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   214,     9,   391,    11,   618,    13,
     649,    15,   533,    17,   542,    19,   581,    21,   353,    23,
     853,    25,   885,    27,    46,    39,     0,     0,     0,     0,
       0,   651,     0,   544,   583,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   883,   199,   232,
       0,     0,     0,   671,   673,   675,     0,     0,   230,   243,
     245,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,   164,   171,
     173,     0,     0,     0,     0,     0,     0,     0,   382,   531,
     572,     0,   156,   177,   471,   636,   638,     0,     0,     0,
     315,   698,   640,   344,   365,     0,   330,   735,   737,   834,
     851,   187,   189,     0,     0,     0,   895,   937,     0,   141,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   104,   137,   138,    93,    94,    95,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   114,   115,   129,   130,   131,   133,   134,   135,
     139,   140,    78,    79,   101,    80,    81,    82,   132,    86,
      87,    76,   105,   106,   107,    77,    84,    85,    99,   100,
     102,    96,    97,    98,    83,    88,    89,    90,    91,    92,
     103,   113,   136,   216,   218,   222,     0,     0,     0,     0,
     213,     0,   201,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   451,   453,   455,   609,   449,   457,     0,   461,
     463,   465,   459,   693,   448,   396,   397,   398,   399,   400,
     425,   426,   427,   428,   429,   446,   415,   416,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   447,     0,   393,   403,   420,   421,
     422,   404,   406,   407,   408,   409,   411,   412,   413,   405,
     401,   402,   423,   424,   410,   417,   418,   419,   414,   633,
       0,   632,   626,   627,   628,   629,   625,     0,   620,   623,
     624,   630,   631,   691,   677,   679,   681,   685,   683,   689,
     687,   670,   664,   668,   669,     0,   652,   653,   665,   666,
     667,   661,   656,   662,   658,   659,   660,   663,   657,     0,
     562,   289,     0,   566,   564,   569,     0,   558,   559,     0,
     545,   546,   549,   561,   550,   551,   552,   568,   553,   554,
     555,   556,   557,   600,     0,     0,     0,   607,   598,   599,
     602,   603,     0,   584,   585,   588,   589,   590,   591,   592,
     593,   594,   597,   595,   596,   361,   363,   358,     0,   355,
     359,   360,     0,   870,     0,   873,     0,     0,   877,   881,
     868,   866,   867,     0,   855,   858,   859,   860,   861,   862,
     863,   864,   865,   892,     0,     0,   887,   890,   891,    45,
      50,     0,    37,    43,     0,    64,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    69,
      66,     0,     0,     0,     0,     0,     0,     0,   203,   215,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   395,   392,     0,     0,   622,   619,     0,     0,
       0,     0,     0,     0,     0,     0,   650,   655,   534,     0,
       0,     0,     0,     0,     0,     0,   543,   548,     0,     0,
       0,     0,     0,   582,   587,     0,     0,   357,   354,     0,
       0,     0,     0,     0,     0,     0,     0,   857,   854,     0,
       0,   889,   886,    49,    41,     0,     0,     0,     0,     0,
     158,   159,   160,     0,     0,     0,   197,   198,     0,     0,
       0,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,     0,   192,   193,   161,   162,   163,     0,     0,
       0,   175,   176,   183,   184,   185,   186,   191,     0,     0,
       0,   155,     0,     0,     0,     0,     0,   467,   468,   469,
       0,     0,     0,     0,     0,   734,     0,     0,     0,     0,
       0,     0,     0,   194,   195,   196,     0,     0,    68,     0,
       0,     0,   226,   227,   228,   229,   202,     0,     0,     0,
       0,     0,     0,   470,     0,     0,     0,     0,     0,   394,
       0,   635,   621,     0,     0,     0,     0,     0,     0,     0,
       0,   654,     0,     0,   560,     0,     0,     0,   571,   547,
       0,   604,   605,   606,     0,   586,     0,     0,   356,   869,
       0,   872,     0,   875,   876,     0,     0,   856,     0,   894,
     888,     0,     0,     0,     0,     0,   672,   674,   676,     0,
       0,   247,   154,   166,   167,   168,   169,   170,   165,   172,
     174,   384,   535,   574,   157,   179,   180,   181,   182,   178,
     473,    38,   637,   639,     0,     0,   642,   346,     0,     0,
       0,   739,     0,     0,   188,   190,     0,     0,    51,   217,
     220,   221,   219,   224,   225,   223,   452,   454,   456,   611,
     450,   458,   462,   464,   466,   460,     0,   634,   692,   678,
     680,   682,   686,   684,   690,   688,   563,   290,   567,   565,
     570,   601,   608,   362,   364,   871,   874,   879,   880,   878,
     882,   247,    42,     0,     0,     0,   239,   241,     0,   234,
     237,   238,   280,   282,   284,   286,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,     0,     0,   307,
     309,   311,   313,   279,     0,   254,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,     0,   252,
       0,   248,   249,   389,     0,   385,   386,   540,     0,   536,
     537,   579,     0,   575,   576,   478,     0,   474,   475,   325,
     326,   327,   328,   329,     0,   317,   320,   321,   322,   323,
     324,   703,     0,   700,   647,     0,   643,   644,   351,     0,
     347,   348,     0,     0,     0,     0,     0,     0,     0,   367,
     370,   371,   372,   373,   374,   375,     0,     0,     0,   340,
       0,   332,   335,   336,   337,   338,   339,   762,   767,   769,
       0,   792,     0,   773,   761,   754,   755,   756,   759,   760,
       0,   746,   749,   750,   751,   752,   757,   758,   753,   744,
       0,   740,   741,     0,   846,     0,   849,   842,   843,     0,
     836,   839,   840,   841,   844,     0,   900,     0,   897,     0,
       0,     0,     0,   946,     0,   939,   942,   943,   944,   945,
      53,   616,     0,   612,   613,   696,     0,   695,     0,    62,
     884,   200,     0,     0,   236,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   256,   231,   244,
       0,   246,   251,     0,   383,   388,   544,   532,   539,   583,
     573,   578,     0,   472,   477,   319,   316,   705,   702,   699,
     651,   641,   646,     0,   345,   350,     0,     0,     0,     0,
       0,     0,   369,   366,     0,     0,     0,   334,   331,     0,
       0,     0,     0,     0,     0,     0,   748,   736,     0,   738,
     743,     0,     0,     0,     0,   838,   835,   852,     0,   899,
     896,     0,     0,     0,     0,   941,   938,    55,     0,    54,
       0,   610,   615,     0,   694,   893,     0,     0,   235,     0,
       0,     0,     0,   288,   291,   292,   293,   294,   295,   296,
     297,   298,   299,     0,   305,   306,     0,     0,     0,     0,
     255,     0,   250,     0,   387,     0,   538,     0,   577,   530,
     502,   503,   504,   486,   487,   507,   508,   509,   510,   511,
     528,   489,   490,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   529,
     483,   484,   485,   498,   499,   500,   501,   495,   496,   497,
       0,   480,   488,   505,   506,   491,   492,   493,   494,   476,
     318,   728,   730,     0,     0,   722,   723,   724,   725,   726,
     727,   715,   716,   720,   721,   717,   718,   719,     0,   706,
     707,   710,   711,   712,   713,   714,   701,     0,   645,     0,
     349,   376,   377,   378,   379,   380,   381,   368,   341,   342,
     343,   333,     0,     0,     0,   771,     0,   772,     0,   747,
       0,   742,   845,     0,   848,     0,   837,   915,     0,   913,
     911,   905,   909,   910,     0,   902,   907,   908,   906,   898,
     947,   948,   949,   950,   940,    52,    57,     0,   614,     0,
     240,   242,   281,   283,   285,   287,   302,   303,   304,   301,
     308,   310,   312,   314,   253,   390,   541,   580,   482,   479,
       0,     0,     0,     0,   704,   709,   648,   352,   764,   765,
     766,   763,   768,   770,     0,   775,   745,   847,   850,     0,
       0,     0,   904,   901,    56,   617,   697,   481,     0,     0,
     732,   733,   708,   804,   807,   809,   811,   803,   802,   801,
       0,   794,   797,   798,   799,   800,   780,     0,   776,   777,
       0,   912,     0,   903,   729,   731,     0,     0,     0,     0,
     796,   793,     0,   774,   779,     0,   914,     0,     0,     0,
       0,   795,   790,   789,   785,   787,   788,     0,   782,   786,
     778,   920,     0,   917,   806,   805,   808,   810,   813,     0,
     784,   781,     0,   919,   916,   818,     0,   814,   815,     0,
     783,   930,     0,     0,     0,   935,     0,   922,   925,   926,
     927,   928,   929,   918,     0,   812,   817,   791,     0,     0,
       0,     0,     0,   924,   921,   830,   832,   829,   823,   825,
     827,   828,     0,   820,   824,   826,   816,     0,   932,   933,
     934,     0,   923,     0,     0,   822,   819,   931,   936,     0,
       0,   821,   831,   833
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393,   -59, -1393,  -614, -1393,   564,
   -1393, -1393, -1393, -1393, -1393, -1393,  -651, -1393, -1393, -1393,
     -67, -1393, -1393, -1393, -1393, -1393, -1393, -1393,   545,   757,
      16,    31,    33,   -26,   -13,    13,    41,    44,    51,    54,
   -1393, -1393, -1393, -1393,    56, -1393, -1393,    59,    62,    64,
      66,    69,    74, -1393, -1393,    76, -1393,    77, -1393,    79,
      81,    82, -1393, -1393,    84,    87,    89,    92,    94, -1393,
      97, -1393,    99, -1393, -1393, -1393, -1393, -1393,    43, -1393,
   -1393, -1393,   548,   751, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,   269, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,   467, -1393,   242, -1393,  -724,   249, -1393, -1393,
   -1392, -1393, -1386, -1393, -1393, -1393, -1393,   -63, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,  -756, -1393,  -755, -1393,  -752, -1393, -1393,
   -1393, -1393, -1393, -1393,   232, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,   212, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393,   227, -1393, -1393, -1393,   231,   719, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   228, -1393, -1393, -1393, -1393, -1393,
   -1393, -1035, -1393, -1393, -1393,   245, -1393, -1393, -1393,   254,
     760, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1033,
   -1393,   -29, -1393,   -18, -1393,     5, -1393,    71, -1393,   100,
     102,   104, -1393, -1393, -1393, -1393, -1393,   251, -1393, -1393,
       6,   -60, -1393, -1393, -1393, -1393, -1393,   258, -1393, -1393,
   -1393,   261, -1393,   742, -1393,   -34, -1393, -1393, -1393, -1393,
   -1393,   -27, -1393, -1393, -1393, -1393, -1393,   -32, -1393, -1393,
   -1393,   259, -1393, -1393, -1393,   263, -1393,   741, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,   207, -1393, -1393, -1393,   216,   776, -1393, -1393,
   -1393,   -44, -1393,     3, -1393,   -56, -1393, -1393, -1393,   262,
   -1393, -1393, -1393,   268, -1393,   773,   -48, -1393,    -7, -1393,
      15, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1032, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393,   274, -1393, -1393, -1393,
      28, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393,   244, -1393,   247,   257, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393,   -20, -1393, -1393,   -53, -1393, -1393, -1393, -1393,
   -1393,   -15, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393,   -76, -1393, -1393,   -95, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   260, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393,   578,   769, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393,   620,   768, -1393, -1393, -1393, -1393,
   -1393, -1393,   267, -1393, -1393,    36, -1393, -1393, -1393, -1393,
   -1393, -1393,   -25, -1393, -1393,   -62, -1393, -1393, -1393, -1393,
   -1393, -1393, -1393, -1393, -1393, -1393,   266, -1393, -1393, -1393,
   -1393
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   762,
      82,    83,    39,    64,    79,    80,   779,  1000,  1108,  1109,
     853,    41,    66,    85,   444,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   472,   174,   175,   492,   176,   177,   178,   179,
     180,   181,   182,   478,   748,   183,   479,   184,   480,   185,
     186,   187,   493,   759,   188,   189,   190,   191,   192,   511,
     193,   512,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   448,   241,   242,    45,    68,   243,   521,   244,   522,
     782,   245,   523,   785,   246,   247,   248,   249,   203,   458,
     204,   449,   828,   829,   830,  1012,   831,  1013,   205,   459,
     206,   460,   880,   881,   882,  1040,   854,   855,   856,  1016,
     857,  1017,   858,  1018,   859,  1019,   860,   861,   560,   862,
     863,   864,   865,   866,   867,   868,   869,   870,   871,  1030,
    1289,   872,   873,   874,  1033,   875,  1034,   876,  1035,   877,
    1036,   207,   500,   904,   905,   906,   907,   908,   909,   910,
     208,   506,   940,   941,   942,   943,   944,   209,   503,   919,
     920,   921,  1063,    59,    75,   408,   409,   410,   575,   411,
     576,   210,   504,   928,   929,   930,   931,   932,   933,   934,
     935,   211,   488,   884,   885,   886,  1043,    47,    69,   295,
     296,   297,   534,   298,   530,   299,   531,   300,   532,   301,
     535,   302,   540,   303,   537,   304,   538,   305,   539,   212,
     213,   214,   309,   215,   494,   896,   897,   898,  1052,  1190,
    1191,   216,   489,    53,    72,   888,   889,   890,  1046,    55,
      73,   369,   370,   371,   372,   373,   374,   375,   559,   376,
     563,   377,   562,   378,   379,   564,   380,   217,   490,   892,
     893,   894,  1049,    57,    74,   392,   393,   394,   395,   396,
     568,   397,   398,   399,   400,   401,   402,   572,   311,   533,
    1002,  1003,  1004,  1110,    49,    70,   327,   328,   329,   544,
     330,   218,   495,   219,   496,   220,   502,   915,   916,   917,
    1060,    51,    71,   345,   346,   347,   221,   453,   222,   454,
     223,   455,   351,   549,   352,   550,   353,   551,   354,   553,
     355,   552,   356,   555,   357,   554,   358,   548,   318,   541,
    1006,  1007,  1113,   224,   501,   912,   913,  1057,  1218,  1219,
    1220,  1221,  1222,  1300,  1223,  1301,  1224,  1225,   225,   226,
     507,   227,   508,   970,   971,   972,  1088,   960,   961,   962,
    1079,  1311,   963,  1080,   964,  1081,   965,   966,   967,  1085,
    1347,  1348,  1349,  1362,  1377,  1378,  1379,  1389,   968,  1083,
    1340,  1341,  1342,  1356,  1385,  1343,  1357,  1344,  1358,  1345,
    1359,  1396,  1397,  1398,  1414,  1432,  1433,  1434,  1443,  1435,
    1444,   228,   509,   979,   980,   981,   982,  1092,   983,   984,
    1094,   229,   510,    61,    76,   423,   424,   425,   426,   580,
     427,   428,   582,   429,   430,   431,   585,   819,   432,   586,
     230,   447,    63,    77,   435,   436,   437,   589,   438,   231,
     516,   987,   988,  1098,  1264,  1265,  1266,  1267,  1321,  1268,
    1319,  1382,  1383,  1392,  1406,  1407,  1408,  1418,  1409,  1410,
    1411,  1412,  1422,   232,   517,   994,   995,   996,   997,   998,
     999
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   321,   341,    78,   367,   388,   407,   420,
     368,   389,   359,   314,   955,   956,   878,  1181,   957,  1182,
    1198,   315,  1428,   348,   250,   312,   331,   343,  1429,   381,
     403,   761,   421,   792,   793,   794,   817,   310,   326,   342,
     390,   322,   798,   268,    29,   361,    30,   391,    31,   445,
     405,   406,   323,  1428,   446,   519,   269,    28,  1055,  1429,
     520,  1056,   316,   812,   349,   135,   136,   743,   744,   745,
     746,   251,   313,   332,   344,   324,   382,   404,   361,   422,
     433,   434,   270,    81,   317,   265,   350,   233,   234,  1058,
      40,   235,  1059,   129,   236,   237,   238,   239,   135,   136,
     266,  1099,   267,   761,  1100,    84,   747,   849,   850,   851,
     271,   439,   294,   272,   528,   989,   990,   991,   992,   529,
     273,   542,   546,   274,   577,   275,   543,   547,   276,   578,
      42,   277,   158,   278,   158,   279,    44,   587,   280,   591,
      46,   325,   588,   281,   592,   282,   283,    48,   284,    50,
     285,   286,  1257,   287,  1258,  1259,   288,   519,   289,  1372,
      52,   290,  1009,   291,   135,   136,   292,   591,   293,   306,
     528,   307,  1010,   308,  1014,  1011,    54,    87,   158,  1015,
      88,  1401,    56,  1037,  1402,  1403,  1404,  1405,  1038,   135,
     136,  1393,    89,   440,  1394,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    58,  1037,    60,   947,
     818,   158,  1039,   948,   949,   950,   951,  1072,    62,  1333,
    1077,  1086,  1073,   952,   953,  1078,  1087,   833,   834,   441,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   443,  1095,
     442,   129,   130,  1181,  1096,  1182,  1198,   780,   781,    32,
      33,    34,    35,   131,   132,   133,   587,   158,   360,   556,
     134,  1097,  1105,   135,   136,   405,   406,  1106,   137,   138,
     139,   140,   141,  1037,   542,  1298,   135,   136,  1294,  1295,
    1299,   142,   158,   135,   136,   783,   784,    93,    94,    95,
      96,   143,   450,   451,   144,   577,  1141,   135,   136,  1086,
    1307,   145,   146,  1322,  1316,   452,   147,   148,  1323,   456,
     955,   956,   955,   956,   957,   361,   957,   362,   363,   101,
     102,   103,   364,   365,   366,   149,   457,   135,   136,   150,
    1334,  1335,  1336,   826,   827,   135,   136,   936,   937,   938,
    1425,  1426,   595,   461,   151,   152,   153,   154,   155,   156,
     129,   130,   361,   462,   899,   900,   901,   902,   157,   903,
     463,   593,   594,   464,    91,    92,    93,    94,    95,    96,
     546,   557,   135,   136,   465,  1325,   158,   922,   923,   924,
     925,   926,   927,  1360,  1201,  1202,  1203,  1204,  1361,   158,
     973,   974,   975,  1286,  1287,  1288,   158,   466,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   467,   468,
     158,   469,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   470,   471,  1390,  1423,
     130,   361,   159,  1391,  1424,   755,   756,   757,   758,  1445,
     976,   240,   132,   133,  1446,  1308,  1309,  1310,   158,   473,
     474,   135,   136,   475,   257,   264,   137,   138,   139,   321,
     259,   260,   261,   476,   250,   477,   314,   262,   481,   482,
     341,   483,   484,   485,   315,   486,   487,   263,   312,   491,
     367,   497,   331,   498,   368,   158,   499,   388,   505,   348,
     310,   389,   513,   343,   326,   514,   268,   322,   515,   518,
     420,   524,   525,   381,   526,   342,   527,   536,   323,   269,
     403,   251,   545,   558,   561,   316,   565,   566,   567,   573,
     390,   569,   570,   421,   571,   313,   574,   391,   579,   332,
     349,   324,   151,   152,   581,   270,   583,   317,   265,   584,
     344,   590,   600,   596,   597,   598,   599,   601,   602,   603,
     382,   604,   350,   266,   605,   267,   607,   404,   606,   608,
     609,   610,   611,   271,   158,   294,   272,   612,   613,   622,
     422,   614,   615,   273,   620,   616,   274,   617,   275,   618,
     619,   276,   621,   623,   277,   624,   278,   628,   279,   629,
     625,   280,   630,    93,    94,    95,   281,   325,   282,   283,
     638,   284,   626,   285,   286,   627,   287,   631,  1326,   288,
     632,   289,   130,   633,   290,   634,   291,   635,   636,   292,
     639,   293,   306,   637,   307,   640,   308,   641,   642,   643,
     644,   645,   319,   135,   136,   361,   383,   362,   363,   384,
     385,   386,   259,   260,   261,   159,   646,   240,   647,   262,
     320,   648,   822,   649,   650,   135,   136,   130,   651,   652,
     653,   654,   655,   656,   387,   657,   658,   659,   660,   661,
     250,   135,   136,   662,   663,   664,   665,   666,   135,   136,
     667,   669,   939,   954,   670,   671,   420,   333,   672,   673,
     993,   674,   677,   675,   678,   679,   680,   334,   335,   336,
     337,   338,   339,   340,   681,   945,   958,   682,   977,   421,
     684,   683,   685,   686,   687,   688,   690,   251,   691,   693,
     694,   695,   696,    91,    92,    93,    94,    95,    96,   697,
     698,   699,   700,   702,   703,   704,   705,   706,   412,   413,
     414,   415,   416,   417,   418,   419,   158,   707,   710,   714,
     716,   717,   946,   959,   708,   978,   422,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   711,   158,   712,
     720,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   158,   252,   253,   254,   722,   130,
     725,   158,   713,   719,   721,   723,   726,   724,   728,   729,
     731,   132,   133,   736,   737,   732,   733,   734,   255,   735,
     135,   136,   256,   257,   258,   137,   138,   139,   739,   259,
     260,   261,   738,   740,   741,   742,   262,   749,   142,   750,
     751,   752,   753,   754,   760,    30,   263,   832,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,   843,   844,
     845,   846,   763,   764,   765,   847,   848,   849,   850,   851,
     852,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   766,   767,   774,   775,   768,   769,
     770,   771,   772,   776,   773,   778,   777,   789,   786,   821,
     787,   151,   152,   796,   361,   820,   788,   790,   791,   879,
     795,   797,   799,   883,   800,   801,   887,   891,   802,   803,
     895,   911,   804,   805,   806,   807,   808,   809,   914,   810,
     918,   969,   986,   158,   811,   813,   815,   816,  1001,  1005,
    1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1031,  1032,  1042,  1107,  1041,  1045,  1044,  1047,  1048,  1050,
    1051,  1054,  1053,  1062,  1123,  1061,   264,  1064,  1065,   367,
    1066,  1067,   388,   368,  1068,  1149,   389,   314,  1069,  1180,
    1205,  1070,  1071,   341,  1210,   315,   407,  1211,  1074,   312,
    1075,  1076,   381,  1082,  1195,   403,  1084,  1089,  1193,  1215,
     939,   310,   348,  1213,  1090,   390,   343,   268,  1091,   954,
    1192,   954,   391,  1183,  1093,  1212,  1153,  1101,   342,  1102,
     269,  1260,  1103,   945,  1184,  1261,   316,  1104,   993,  1154,
    1111,  1112,   958,   321,   958,  1196,   313,   158,  1114,   382,
    1216,   977,   404,   349,  1262,  1194,   270,  1185,   317,   265,
    1214,  1115,  1116,   344,  1117,  1155,   331,  1197,  1150,  1119,
    1120,  1121,  1217,  1206,   266,   350,   267,  1122,   326,  1133,
     946,   322,  1125,  1151,   271,  1152,   294,   272,  1207,   959,
    1208,   959,   323,  1156,   273,  1179,  1157,   274,   978,   275,
    1209,  1263,   276,  1158,  1124,   277,  1159,   278,  1160,   279,
    1126,  1161,   280,   332,  1162,   324,  1163,   281,  1164,   282,
     283,  1165,   284,  1186,   285,   286,  1166,   287,  1167,  1168,
     288,  1169,   289,  1170,  1171,   290,  1172,   291,  1127,  1173,
     292,  1174,   293,   306,  1175,   307,  1176,   308,  1128,  1177,
    1136,  1178,  1187,  1129,  1188,  1137,  1189,  1130,  1131,  1132,
    1138,  1135,  1134,  1139,  1242,  1238,  1243,  1231,  1232,  1233,
    1234,  1235,  1244,  1236,  1239,  1240,  1245,  1246,  1248,  1253,
    1255,   325,  1276,  1275,  1279,  1384,  1296,  1302,  1303,  1297,
    1304,  1305,  1363,  1306,  1314,  1315,  1318,  1247,  1320,  1328,
    1329,  1350,  1352,  1364,  1254,  1252,  1346,  1270,  1365,  1367,
    1368,  1271,  1272,  1280,  1273,  1281,  1282,  1369,  1370,  1283,
    1284,  1285,  1290,  1291,  1381,  1292,  1388,  1395,  1293,  1399,
    1312,  1149,  1415,  1313,  1317,  1180,  1324,  1416,  1205,  1354,
    1330,  1331,  1210,  1351,  1419,  1211,  1355,  1337,  1366,  1386,
    1195,  1387,  1417,  1420,  1193,  1260,  1421,  1215,  1437,  1261,
    1438,  1213,  1439,  1440,  1441,  1447,  1192,  1448,  1449,  1183,
    1338,  1450,  1153,  1212,  1452,  1453,   668,   823,  1262,   676,
    1184,   814,   825,  1118,  1142,  1154,  1140,  1200,  1008,  1241,
    1144,  1196,  1230,  1337,  1229,  1373,   718,  1143,  1216,  1374,
    1237,  1194,   689,  1185,  1327,  1199,  1146,  1145,  1214,   709,
    1148,  1155,  1147,  1197,  1150,   715,  1338,  1339,  1375,  1278,
    1217,  1206,   692,  1373,  1228,  1263,  1277,  1374,  1227,  1151,
     701,  1152,  1226,  1332,  1251,  1250,  1207,  1400,  1208,  1156,
    1436,  1179,  1157,  1249,  1380,  1371,  1375,  1427,  1209,  1158,
    1451,   985,  1159,   824,  1160,  1256,   727,  1161,  1353,   730,
    1162,  1442,  1163,  1339,  1164,  1376,  1269,  1165,  1413,  1186,
    1430,  1274,  1166,     0,  1167,  1168,     0,  1169,  1427,  1170,
    1171,     0,  1172,     0,     0,  1173,     0,  1174,     0,     0,
    1175,     0,  1176,  1376,     0,  1177,     0,  1178,  1187,     0,
    1188,  1430,  1189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1431,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1431
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   770,   770,   740,  1052,   770,  1052,
    1052,    69,  1414,    71,    68,    69,    70,    71,  1414,    73,
      74,   645,    76,   684,   685,   686,    18,    69,    70,    71,
      74,    70,   693,    69,     5,    97,     7,    74,     9,     3,
     146,   147,    70,  1445,     8,     3,    69,     0,     3,  1445,
       8,     6,    69,   714,    71,   117,   118,   194,   195,   196,
     197,    68,    69,    70,    71,    70,    73,    74,    97,    76,
      12,    13,    69,   230,    69,    69,    71,    15,    16,     3,
       7,    19,     6,    95,    22,    23,    24,    25,   117,   118,
      69,     3,    69,   717,     6,    10,   233,    60,    61,    62,
      69,     6,    69,    69,     3,   213,   214,   215,   216,     8,
      69,     3,     3,    69,     3,    69,     8,     8,    69,     8,
       7,    69,   230,    69,   230,    69,     7,     3,    69,     3,
       7,    70,     8,    69,     8,    69,    69,     7,    69,     7,
      69,    69,   204,    69,   206,   207,    69,     3,    69,   178,
       7,    69,     8,    69,   117,   118,    69,     3,    69,    69,
       3,    69,     8,    69,     3,     8,     7,    11,   230,     8,
      14,   205,     7,     3,   208,   209,   210,   211,     8,   117,
     118,     3,    26,     3,     6,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     7,     3,     7,   162,
     192,   230,     8,   166,   167,   168,   169,     3,     7,    40,
       3,     3,     8,   176,   177,     8,     8,    41,    42,     4,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,     3,     3,
       8,    95,    96,  1298,     8,  1298,  1298,    17,    18,   230,
     231,   232,   233,   107,   108,   109,     3,   230,    40,     8,
     114,     8,     3,   117,   118,   146,   147,     8,   122,   123,
     124,   125,   126,     3,     3,     3,   117,   118,     8,     8,
       8,   135,   230,   117,   118,    20,    21,    32,    33,    34,
      35,   145,     4,     4,   148,     3,  1040,   117,   118,     3,
       8,   155,   156,     3,     8,     4,   160,   161,     8,     4,
    1086,  1086,  1088,  1088,  1086,    97,  1088,    99,   100,    64,
      65,    66,   104,   105,   106,   179,     4,   117,   118,   183,
     171,   172,   173,    27,    28,   117,   118,   157,   158,   159,
     174,   175,   230,     4,   198,   199,   200,   201,   202,   203,
      95,    96,    97,     4,   137,   138,   139,   140,   212,   142,
       4,   440,   441,     4,    30,    31,    32,    33,    34,    35,
       3,     3,   117,   118,     4,     8,   230,   149,   150,   151,
     152,   153,   154,     3,   129,   130,   131,   132,     8,   230,
     180,   181,   182,    55,    56,    57,   230,     4,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     4,     4,
     230,     4,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,     4,     4,     3,     3,
      96,    97,   519,     8,     8,   110,   111,   112,   113,     3,
     230,   528,   108,   109,     8,   163,   164,   165,   230,     4,
       4,   117,   118,     4,   120,   542,   122,   123,   124,   546,
     126,   127,   128,     4,   528,     4,   542,   133,     4,     4,
     557,     4,     4,     4,   542,     4,     4,   143,   542,     4,
     567,     4,   546,     4,   567,   230,     4,   574,     4,   557,
     542,   574,     4,   557,   546,     4,   542,   546,     4,     4,
     587,     4,     4,   567,     4,   557,     4,     4,   546,   542,
     574,   528,     4,     8,     4,   542,     4,     8,     3,     8,
     574,     4,     4,   587,     4,   542,     3,   574,     4,   546,
     557,   546,   198,   199,     4,   542,     4,   542,   542,     4,
     557,     4,   233,     4,     4,     4,     4,   233,   233,     4,
     567,     4,   557,   542,     4,   542,   233,   574,   231,     4,
       4,     4,   231,   542,   230,   542,   542,   231,   231,     4,
     587,   231,   231,   542,   231,   233,   542,   232,   542,   232,
     232,   542,   231,   231,   542,   231,   542,     4,   542,     4,
     233,   542,     4,    32,    33,    34,   542,   546,   542,   542,
       4,   542,   233,   542,   542,   233,   542,   233,  1279,   542,
     233,   542,    96,   232,   542,   231,   542,   231,   231,   542,
       4,   542,   542,   233,   542,     4,   542,   231,     4,     4,
       4,     4,   116,   117,   118,    97,    98,    99,   100,   101,
     102,   103,   126,   127,   128,   732,     4,   734,   233,   133,
     134,   233,   731,   233,     4,   117,   118,    96,     4,     4,
       4,     4,   231,     4,   126,     4,     4,     4,     4,     4,
     734,   117,   118,     4,   233,   233,   233,     4,   117,   118,
       4,     4,   769,   770,     4,     4,   773,   126,   233,   233,
     777,   231,     4,   231,     4,     4,     4,   136,   137,   138,
     139,   140,   141,   142,     4,   769,   770,     4,   772,   773,
       4,   231,     4,     4,     4,     4,     4,   734,   231,     4,
       4,     4,     4,    30,    31,    32,    33,    34,    35,     4,
       4,     4,     4,     4,     4,   231,     4,     4,   184,   185,
     186,   187,   188,   189,   190,   191,   230,     4,     4,     4,
       4,     4,   769,   770,   233,   772,   773,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,   233,   230,   233,
       4,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,   230,    92,    93,    94,     4,    96,
       4,   230,   233,   233,   231,   231,     4,   231,     4,   231,
       4,   108,   109,   230,   230,     7,     7,     7,   115,     7,
     117,   118,   119,   120,   121,   122,   123,   124,     7,   126,
     127,   128,   230,     7,     5,   230,   133,   230,   135,   230,
       5,     5,     5,   230,     5,     7,   143,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   230,     5,     5,    58,    59,    60,    61,    62,
      63,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     5,     5,   230,   230,     7,     7,
       7,     5,     7,     5,     7,     5,     7,     5,   230,     5,
     230,   198,   199,     7,    97,   193,   230,   230,   230,     7,
     230,   230,   230,     7,   230,   230,     7,     7,   230,   230,
       7,     7,   230,   230,   230,   230,   230,   230,     7,   230,
       7,     7,     7,   230,   230,   230,   230,   230,     7,   144,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   230,     6,     3,     6,     6,     3,     6,
       3,     3,     6,     3,   231,     6,  1043,     6,     3,  1046,
       4,     4,  1049,  1046,     4,  1052,  1049,  1043,     4,  1052,
    1057,     4,     4,  1060,  1057,  1043,  1063,  1057,     4,  1043,
       4,     4,  1046,     4,  1052,  1049,     4,     6,  1052,  1057,
    1077,  1043,  1060,  1057,     3,  1049,  1060,  1043,     4,  1086,
    1052,  1088,  1049,  1052,     4,  1057,  1052,     4,  1060,     4,
    1043,  1098,     4,  1077,  1052,  1098,  1043,     4,  1105,  1052,
       6,     3,  1086,  1110,  1088,  1052,  1043,   230,     8,  1046,
    1057,  1095,  1049,  1060,  1098,  1052,  1043,  1052,  1043,  1043,
    1057,     6,     4,  1060,     4,  1052,  1110,  1052,  1052,     4,
       4,     4,  1057,  1057,  1043,  1060,  1043,     4,  1110,     4,
    1077,  1110,   231,  1052,  1043,  1052,  1043,  1043,  1057,  1086,
    1057,  1088,  1110,  1052,  1043,  1052,  1052,  1043,  1095,  1043,
    1057,  1098,  1043,  1052,   233,  1043,  1052,  1043,  1052,  1043,
     233,  1052,  1043,  1110,  1052,  1110,  1052,  1043,  1052,  1043,
    1043,  1052,  1043,  1052,  1043,  1043,  1052,  1043,  1052,  1052,
    1043,  1052,  1043,  1052,  1052,  1043,  1052,  1043,   231,  1052,
    1043,  1052,  1043,  1043,  1052,  1043,  1052,  1043,   231,  1052,
       4,  1052,  1052,   231,  1052,     4,  1052,   231,   231,   231,
       4,   231,   233,     4,     4,   233,     4,   231,   231,   231,
     231,   231,     4,   231,   231,   231,   231,     4,     4,     4,
       4,  1110,     3,     6,     4,   170,     8,     4,     4,     8,
       8,     3,     6,     8,     7,     5,  1255,   233,     4,     4,
       4,     4,     4,     3,   231,   233,     7,   233,     5,     4,
       4,   233,   233,   230,   233,   230,   230,     4,     4,   230,
     230,   230,   230,   230,     7,   230,     5,     7,   230,     4,
     230,  1298,     6,   230,   230,  1298,   230,     3,  1305,   230,
     233,   233,  1305,   231,     4,  1305,   230,  1314,   230,   230,
    1298,   230,   230,     4,  1298,  1322,     4,  1305,     4,  1322,
     233,  1305,   231,   231,     4,   230,  1298,   230,     4,  1298,
    1314,     4,  1298,  1305,   230,   230,   519,   732,  1322,   528,
    1298,   717,   734,  1014,  1042,  1298,  1037,  1055,   821,  1077,
    1045,  1298,  1065,  1360,  1063,  1362,   577,  1043,  1305,  1362,
    1072,  1298,   542,  1298,  1298,  1054,  1048,  1046,  1305,   567,
    1051,  1298,  1049,  1298,  1298,   574,  1360,  1314,  1362,  1112,
    1305,  1305,   546,  1390,  1062,  1322,  1110,  1390,  1060,  1298,
     557,  1298,  1058,  1305,  1090,  1088,  1305,  1390,  1305,  1298,
    1416,  1298,  1298,  1086,  1364,  1360,  1390,  1414,  1305,  1298,
    1445,   773,  1298,   733,  1298,  1095,   587,  1298,  1322,   591,
    1298,  1423,  1298,  1360,  1298,  1362,  1099,  1298,  1393,  1298,
    1414,  1105,  1298,    -1,  1298,  1298,    -1,  1298,  1445,  1298,
    1298,    -1,  1298,    -1,    -1,  1298,    -1,  1298,    -1,    -1,
    1298,    -1,  1298,  1390,    -1,  1298,    -1,  1298,  1298,    -1,
    1298,  1445,  1298,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1414,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1445
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,     0,     5,
       7,     9,   230,   231,   232,   233,   249,   250,   251,   256,
       7,   265,     7,   270,     7,   328,     7,   441,     7,   528,
       7,   545,     7,   477,     7,   483,     7,   507,     7,   417,
       7,   657,     7,   676,   257,   252,   266,   271,   329,   442,
     529,   546,   478,   484,   508,   418,   658,   677,   249,   258,
     259,   230,   254,   255,    10,   267,   269,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    95,
      96,   107,   108,   109,   114,   117,   118,   122,   123,   124,
     125,   126,   135,   145,   148,   155,   156,   160,   161,   179,
     183,   198,   199,   200,   201,   202,   203,   212,   230,   264,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   287,   288,   290,   291,   292,   293,
     294,   295,   296,   299,   301,   303,   304,   305,   308,   309,
     310,   311,   312,   314,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   342,   344,   352,   354,   395,   404,   411,
     425,   435,   463,   464,   465,   467,   475,   501,   535,   537,
     539,   550,   552,   554,   577,   592,   593,   595,   645,   655,
     674,   683,   707,    15,    16,    19,    22,    23,    24,    25,
     264,   326,   327,   330,   332,   335,   338,   339,   340,   341,
     535,   537,    92,    93,    94,   115,   119,   120,   121,   126,
     127,   128,   133,   143,   264,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   288,   291,   292,   293,   294,
     295,   296,   299,   301,   303,   304,   305,   308,   309,   310,
     311,   312,   314,   316,   322,   443,   444,   445,   447,   449,
     451,   453,   455,   457,   459,   461,   463,   464,   465,   466,
     501,   522,   535,   537,   539,   550,   552,   554,   572,   116,
     134,   264,   455,   457,   459,   461,   501,   530,   531,   532,
     534,   535,   537,   126,   136,   137,   138,   139,   140,   141,
     142,   264,   501,   535,   537,   547,   548,   549,   550,   552,
     554,   556,   558,   560,   562,   564,   566,   568,   570,   475,
      40,    97,    99,   100,   104,   105,   106,   264,   371,   485,
     486,   487,   488,   489,   490,   491,   493,   495,   497,   498,
     500,   535,   537,    98,   101,   102,   103,   126,   264,   371,
     489,   495,   509,   510,   511,   512,   513,   515,   516,   517,
     518,   519,   520,   535,   537,   146,   147,   264,   419,   420,
     421,   423,   184,   185,   186,   187,   188,   189,   190,   191,
     264,   535,   537,   659,   660,   661,   662,   664,   665,   667,
     668,   669,   672,    12,    13,   678,   679,   680,   682,     6,
       3,     4,     8,     3,   268,     3,     8,   675,   325,   345,
       4,     4,     4,   551,   553,   555,     4,     4,   343,   353,
     355,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   286,     4,     4,     4,     4,     4,   297,   300,
     302,     4,     4,     4,     4,     4,     4,     4,   436,   476,
     502,     4,   289,   306,   468,   536,   538,     4,     4,     4,
     396,   578,   540,   412,   426,     4,   405,   594,   596,   646,
     656,   313,   315,     4,     4,     4,   684,   708,     4,     3,
       8,   331,   333,   336,     4,     4,     4,     4,     3,     8,
     448,   450,   452,   523,   446,   454,     4,   458,   460,   462,
     456,   573,     3,     8,   533,     4,     3,     8,   571,   557,
     559,   561,   565,   563,   569,   567,     8,     3,     8,   492,
     372,     4,   496,   494,   499,     4,     8,     3,   514,     4,
       4,     4,   521,     8,     3,   422,   424,     3,     8,     4,
     663,     4,   666,     4,     4,   670,   673,     3,     8,   681,
       4,     3,     8,   249,   249,   230,     4,     4,     4,     4,
     233,   233,   233,     4,     4,     4,   231,   233,     4,     4,
       4,   231,   231,   231,   231,   231,   233,   232,   232,   232,
     231,   231,     4,   231,   231,   233,   233,   233,     4,     4,
       4,   233,   233,   232,   231,   231,   231,   233,     4,     4,
       4,   231,     4,     4,     4,     4,     4,   233,   233,   233,
       4,     4,     4,     4,     4,   231,     4,     4,     4,     4,
       4,     4,     4,   233,   233,   233,     4,     4,   273,     4,
       4,     4,   233,   233,   231,   231,   327,     4,     4,     4,
       4,     4,     4,   231,     4,     4,     4,     4,     4,   444,
       4,   231,   531,     4,     4,     4,     4,     4,     4,     4,
       4,   549,     4,     4,   231,     4,     4,     4,   233,   487,
       4,   233,   233,   233,     4,   511,     4,     4,   420,   233,
       4,   231,     4,   231,   231,     4,     4,   660,     4,   231,
     679,     4,     7,     7,     7,     7,   230,   230,   230,     7,
       7,     5,   230,   194,   195,   196,   197,   233,   298,   230,
     230,     5,     5,     5,   230,   110,   111,   112,   113,   307,
       5,   251,   253,   230,     5,     5,     5,     5,     7,     7,
       7,     5,     7,     7,   230,   230,     5,     7,     5,   260,
      17,    18,   334,    20,    21,   337,   230,   230,   230,     5,
     230,   230,   260,   260,   260,   230,     7,   230,   260,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   260,   230,   253,   230,   230,    18,   192,   671,
     193,     5,   249,   272,   678,   326,    27,    28,   346,   347,
     348,   350,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    58,    59,    60,
      61,    62,    63,   264,   360,   361,   362,   364,   366,   368,
     370,   371,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   385,   386,   387,   389,   391,   393,   360,     7,
     356,   357,   358,     7,   437,   438,   439,     7,   479,   480,
     481,     7,   503,   504,   505,     7,   469,   470,   471,   137,
     138,   139,   140,   142,   397,   398,   399,   400,   401,   402,
     403,     7,   579,   580,     7,   541,   542,   543,     7,   413,
     414,   415,   149,   150,   151,   152,   153,   154,   427,   428,
     429,   430,   431,   432,   433,   434,   157,   158,   159,   264,
     406,   407,   408,   409,   410,   535,   537,   162,   166,   167,
     168,   169,   176,   177,   264,   387,   389,   391,   535,   537,
     601,   602,   603,   606,   608,   610,   611,   612,   622,     7,
     597,   598,   599,   180,   181,   182,   230,   535,   537,   647,
     648,   649,   650,   652,   653,   659,     7,   685,   686,   213,
     214,   215,   216,   264,   709,   710,   711,   712,   713,   714,
     261,     7,   524,   525,   526,   144,   574,   575,   356,     8,
       8,     8,   349,   351,     3,     8,   363,   365,   367,   369,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     383,     4,     4,   388,   390,   392,   394,     3,     8,     8,
     359,     6,     3,   440,     6,     3,   482,     6,     3,   506,
       6,     3,   472,     6,     3,     3,     6,   581,     3,     6,
     544,     6,     3,   416,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   604,
     607,   609,     4,   623,     4,   613,     3,     8,   600,     6,
       3,     4,   651,     4,   654,     3,     8,     8,   687,     3,
       6,     4,     4,     4,     4,     3,     8,   230,   262,   263,
     527,     6,     3,   576,     8,     6,     4,     4,   347,     4,
       4,     4,     4,   231,   233,   231,   233,   231,   231,   231,
     231,   231,   231,     4,   233,   231,     4,     4,     4,     4,
     361,   360,   358,   443,   439,   485,   481,   509,   505,   264,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     288,   291,   292,   293,   294,   295,   296,   299,   301,   303,
     304,   305,   308,   309,   310,   311,   312,   314,   316,   322,
     371,   435,   453,   455,   457,   459,   461,   463,   464,   465,
     473,   474,   501,   535,   537,   550,   552,   554,   572,   471,
     398,   129,   130,   131,   132,   264,   274,   275,   276,   322,
     371,   475,   501,   535,   537,   550,   552,   554,   582,   583,
     584,   585,   586,   588,   590,   591,   580,   547,   543,   419,
     415,   231,   231,   231,   231,   231,   231,   428,   233,   231,
     231,   407,     4,     4,     4,   231,     4,   233,     4,   602,
     601,   599,   233,     4,   231,     4,   648,   204,   206,   207,
     264,   371,   535,   537,   688,   689,   690,   691,   693,   686,
     233,   233,   233,   233,   710,     6,     3,   530,   526,     4,
     230,   230,   230,   230,   230,   230,    55,    56,    57,   384,
     230,   230,   230,   230,     8,     8,     8,     8,     3,     8,
     587,   589,     4,     4,     8,     3,     8,     8,   163,   164,
     165,   605,   230,   230,     7,     5,     8,   230,   249,   694,
       4,   692,     3,     8,   230,     8,   260,   474,     4,     4,
     233,   233,   584,    40,   171,   172,   173,   264,   535,   537,
     624,   625,   626,   629,   631,   633,     7,   614,   615,   616,
       4,   231,     4,   689,   230,   230,   627,   630,   632,   634,
       3,     8,   617,     6,     3,     5,   230,     4,     4,     4,
       4,   625,   178,   264,   371,   535,   537,   618,   619,   620,
     616,     7,   695,   696,   170,   628,   230,   230,     5,   621,
       3,     8,   697,     3,     6,     7,   635,   636,   637,     4,
     619,   205,   208,   209,   210,   211,   698,   699,   700,   702,
     703,   704,   705,   696,   638,     6,     3,   230,   701,     4,
       4,     4,   706,     3,     8,   174,   175,   264,   364,   366,
     535,   537,   639,   640,   641,   643,   637,     4,   233,   231,
     231,     4,   699,   642,   644,     3,     8,   230,   230,     4,
       4,   640,   230,   230
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   234,   236,   235,   237,   235,   238,   235,   239,   235,
     240,   235,   241,   235,   242,   235,   243,   235,   244,   235,
     245,   235,   246,   235,   247,   235,   248,   235,   249,   249,
     249,   249,   249,   249,   249,   250,   252,   251,   253,   254,
     254,   255,   255,   255,   257,   256,   258,   258,   259,   259,
     259,   261,   260,   262,   262,   263,   263,   263,   264,   266,
     265,   268,   267,   267,   269,   271,   270,   272,   272,   272,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   286,   285,   287,   289,   288,   290,   291,
     292,   293,   294,   295,   297,   296,   298,   298,   298,   298,
     298,   300,   299,   302,   301,   303,   304,   306,   305,   307,
     307,   307,   307,   308,   309,   310,   311,   313,   312,   315,
     314,   316,   317,   318,   319,   320,   321,   322,   323,   325,
     324,   326,   326,   326,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   329,   328,   331,   330,   333,   332,
     334,   334,   336,   335,   337,   337,   338,   339,   340,   341,
     343,   342,   345,   344,   346,   346,   346,   347,   347,   349,
     348,   351,   350,   353,   352,   355,   354,   356,   356,   357,
     357,   357,   359,   358,   360,   360,   360,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     363,   362,   365,   364,   367,   366,   369,   368,   370,   372,
     371,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     383,   382,   384,   384,   384,   385,   386,   388,   387,   390,
     389,   392,   391,   394,   393,   396,   395,   397,   397,   397,
     398,   398,   398,   398,   398,   399,   400,   401,   402,   403,
     405,   404,   406,   406,   406,   407,   407,   407,   407,   407,
     407,   408,   409,   410,   412,   411,   413,   413,   414,   414,
     414,   416,   415,   418,   417,   419,   419,   419,   419,   420,
     420,   422,   421,   424,   423,   426,   425,   427,   427,   427,
     428,   428,   428,   428,   428,   428,   429,   430,   431,   432,
     433,   434,   436,   435,   437,   437,   438,   438,   438,   440,
     439,   442,   441,   443,   443,   443,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   446,
     445,   448,   447,   450,   449,   452,   451,   454,   453,   456,
     455,   458,   457,   460,   459,   462,   461,   463,   464,   465,
     466,   468,   467,   469,   469,   470,   470,   470,   472,   471,
     473,   473,   473,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   476,   475,   478,   477,   479,   479,   480,   480,   480,
     482,   481,   484,   483,   485,   485,   486,   486,   486,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   488,
     489,   490,   492,   491,   494,   493,   496,   495,   497,   499,
     498,   500,   502,   501,   503,   503,   504,   504,   504,   506,
     505,   508,   507,   509,   509,   510,   510,   510,   511,   511,
     511,   511,   511,   511,   511,   511,   511,   511,   511,   512,
     514,   513,   515,   516,   517,   518,   519,   521,   520,   523,
     522,   524,   524,   525,   525,   525,   527,   526,   529,   528,
     530,   530,   530,   531,   531,   531,   531,   531,   531,   531,
     531,   531,   531,   533,   532,   534,   536,   535,   538,   537,
     540,   539,   541,   541,   542,   542,   542,   544,   543,   546,
     545,   547,   547,   548,   548,   548,   549,   549,   549,   549,
     549,   549,   549,   549,   549,   549,   549,   549,   549,   549,
     549,   551,   550,   553,   552,   555,   554,   557,   556,   559,
     558,   561,   560,   563,   562,   565,   564,   567,   566,   569,
     568,   571,   570,   573,   572,   574,   576,   575,   578,   577,
     579,   579,   579,   581,   580,   582,   582,   583,   583,   583,
     584,   584,   584,   584,   584,   584,   584,   584,   584,   584,
     584,   584,   584,   584,   584,   584,   584,   585,   587,   586,
     589,   588,   590,   591,   592,   594,   593,   596,   595,   597,
     597,   598,   598,   598,   600,   599,   601,   601,   601,   602,
     602,   602,   602,   602,   602,   602,   602,   602,   602,   602,
     602,   602,   604,   603,   605,   605,   605,   607,   606,   609,
     608,   610,   611,   613,   612,   614,   614,   615,   615,   615,
     617,   616,   618,   618,   618,   619,   619,   619,   619,   619,
     621,   620,   623,   622,   624,   624,   624,   625,   625,   625,
     625,   625,   625,   625,   627,   626,   628,   630,   629,   632,
     631,   634,   633,   635,   635,   636,   636,   636,   638,   637,
     639,   639,   639,   640,   640,   640,   640,   640,   640,   640,
     642,   641,   644,   643,   646,   645,   647,   647,   647,   648,
     648,   648,   648,   648,   648,   649,   651,   650,   652,   654,
     653,   656,   655,   658,   657,   659,   659,   659,   660,   660,
     660,   660,   660,   660,   660,   660,   660,   660,   660,   661,
     663,   662,   664,   666,   665,   667,   668,   670,   669,   671,
     671,   673,   672,   675,   674,   677,   676,   678,   678,   678,
     679,   679,   681,   680,   682,   684,   683,   685,   685,   685,
     687,   686,   688,   688,   688,   689,   689,   689,   689,   689,
     689,   689,   690,   692,   691,   694,   693,   695,   695,   695,
     697,   696,   698,   698,   698,   699,   699,   699,   699,   699,
     701,   700,   702,   703,   704,   706,   705,   708,   707,   709,
     709,   709,   710,   710,   710,   710,   710,   711,   712,   713,
     714
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     1,
       1,     1,     1,     3,     3,     3,     3,     0,     4,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     4,     1,     1,     3,     3,     3,     3,
       0,     6,     0,     6,     1,     3,     2,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     3,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     3,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     3,     3,     3,
       3
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
  "\"ddns-ttl-percent\"", "\"ddns-ttl\"", "\"ddns-ttl-min\"",
  "\"ddns-ttl-mix\"", "\"store-extended-info\"", "\"subnet4\"",
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
  "\"http-headers\"", "\"value\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output-options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "\"ignore-dhcp-server-identifier\"",
  "\"ignore-rai-link-selection\"", "\"exclude-first-last-24\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "value", "sub_json", "map2", "$@14", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@15", "list_content",
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
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent", "ddns_ttl",
  "ddns_ttl_min", "ddns_ttl_max", "hostname_char_set", "$@26",
  "hostname_char_replacement", "$@27", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "offer_lifetime", "stash_agent_options",
  "interfaces_config", "$@28", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@29", "interfaces_list",
  "$@30", "dhcp_socket_type", "$@31", "socket_type", "outbound_interface",
  "$@32", "outbound_interface_value", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@33", "sanity_checks",
  "$@34", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@35", "extended_info_checks", "$@36", "hosts_database", "$@37",
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
  "$@66", "network_client_classes", "$@67", "require_client_classes",
  "$@68", "evaluate_additional_classes", "$@69", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "shared_networks", "$@70", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@71",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@72", "sub_option_def_list", "$@73", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@74",
  "sub_option_def", "$@75", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@76",
  "option_def_record_types", "$@77", "space", "$@78", "option_def_space",
  "option_def_encapsulate", "$@79", "option_def_array", "option_data_list",
  "$@80", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@81", "sub_option_data", "$@82",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@83",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@84", "pools_list", "$@85",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@86",
  "sub_pool4", "$@87", "pool_params", "pool_param", "pool_entry", "$@88",
  "pool_id", "user_context", "$@89", "comment", "$@90", "reservations",
  "$@91", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@92", "sub_reservation", "$@93", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@94", "server_hostname", "$@95", "boot_file_name", "$@96",
  "ip_address", "$@97", "duid", "$@98", "hw_address", "$@99",
  "client_id_value", "$@100", "circuit_id_value", "$@101", "flex_id_value",
  "$@102", "hostname", "$@103", "reservation_client_classes", "$@104",
  "relay", "$@105", "relay_map", "ip_addresses", "$@106", "client_classes",
  "$@107", "client_classes_list", "client_class_entry", "$@108",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@109",
  "client_class_template_test", "$@110", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_socket", "$@111",
  "control_sockets", "$@112", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@113",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@114", "control_socket_type_value", "control_socket_name", "$@115",
  "control_socket_address", "$@116", "control_socket_port",
  "cert_required", "http_headers", "$@117", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@118",
  "http_header_params", "http_header_param", "header_value", "$@119",
  "authentication", "$@120", "auth_params", "auth_param", "auth_type",
  "$@121", "auth_type_value", "realm", "$@122", "directory", "$@123",
  "clients", "$@124", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@125", "clients_params", "clients_param", "user_file",
  "$@126", "password_file", "$@127", "dhcp_queue_control", "$@128",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@129", "capacity", "arbitrary_map_entry", "$@130",
  "dhcp_ddns", "$@131", "sub_dhcp_ddns", "$@132", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@133", "server_port",
  "sender_ip", "$@134", "sender_port", "max_queue_size", "ncr_protocol",
  "$@135", "ncr_protocol_value", "ncr_format", "$@136", "config_control",
  "$@137", "sub_config_control", "$@138", "config_control_params",
  "config_control_param", "config_databases", "$@139",
  "config_fetch_wait_time", "loggers", "$@140", "loggers_entries",
  "logger_entry", "$@141", "logger_params", "logger_param", "debuglevel",
  "severity", "$@142", "output_options_list", "$@143",
  "output_options_list_content", "output_entry", "$@144",
  "output_params_list", "output_params", "output", "$@145", "flush",
  "maxsize", "maxver", "pattern", "$@146", "compatibility", "$@147",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   329,   329,   329,   330,   330,   331,   331,   332,   332,
     333,   333,   334,   334,   335,   335,   336,   336,   337,   337,
     338,   338,   339,   339,   340,   340,   341,   341,   349,   350,
     351,   352,   353,   354,   355,   358,   363,   363,   374,   377,
     378,   381,   386,   392,   397,   397,   404,   405,   408,   412,
     416,   422,   422,   429,   430,   433,   437,   441,   451,   460,
     460,   475,   475,   489,   492,   498,   498,   507,   508,   509,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   590,   596,   602,   608,   614,   620,   626,   632,
     638,   644,   650,   656,   656,   665,   671,   671,   680,   686,
     692,   698,   704,   710,   716,   716,   725,   728,   731,   734,
     737,   743,   743,   752,   752,   761,   770,   780,   780,   789,
     792,   795,   798,   803,   809,   815,   821,   827,   827,   836,
     836,   845,   851,   857,   863,   869,   875,   881,   887,   893,
     893,   905,   906,   907,   912,   913,   914,   915,   916,   917,
     918,   919,   920,   921,   924,   924,   933,   933,   944,   944,
     952,   953,   956,   956,   964,   966,   970,   976,   982,   988,
     994,   994,  1007,  1007,  1018,  1019,  1020,  1025,  1026,  1029,
    1029,  1048,  1048,  1066,  1066,  1079,  1079,  1090,  1091,  1094,
    1095,  1096,  1101,  1101,  1111,  1112,  1113,  1118,  1119,  1120,
    1121,  1122,  1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,
    1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,
    1143,  1143,  1152,  1152,  1161,  1161,  1170,  1170,  1179,  1185,
    1185,  1194,  1200,  1206,  1212,  1218,  1224,  1230,  1236,  1242,
    1248,  1248,  1256,  1257,  1258,  1261,  1267,  1273,  1273,  1282,
    1282,  1291,  1291,  1300,  1300,  1309,  1309,  1320,  1321,  1322,
    1327,  1328,  1329,  1330,  1331,  1334,  1339,  1344,  1349,  1354,
    1361,  1361,  1374,  1375,  1376,  1381,  1382,  1383,  1384,  1385,
    1386,  1389,  1395,  1401,  1407,  1407,  1418,  1419,  1422,  1423,
    1424,  1429,  1429,  1439,  1439,  1449,  1450,  1451,  1454,  1457,
    1458,  1461,  1461,  1470,  1470,  1479,  1479,  1491,  1492,  1493,
    1498,  1499,  1500,  1501,  1502,  1503,  1506,  1512,  1518,  1524,
    1530,  1536,  1545,  1545,  1559,  1560,  1563,  1564,  1565,  1574,
    1574,  1600,  1600,  1611,  1612,  1613,  1619,  1620,  1621,  1622,
    1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,
    1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,
    1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,
    1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1674,
    1674,  1683,  1683,  1692,  1692,  1701,  1701,  1710,  1710,  1719,
    1719,  1729,  1729,  1741,  1741,  1752,  1752,  1763,  1769,  1775,
    1781,  1789,  1789,  1801,  1802,  1806,  1807,  1808,  1813,  1813,
    1821,  1822,  1823,  1828,  1829,  1830,  1831,  1832,  1833,  1834,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1845,  1846,  1847,  1848,  1849,  1850,  1851,  1852,  1853,  1854,
    1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,
    1865,  1866,  1867,  1868,  1869,  1870,  1871,  1872,  1873,  1874,
    1875,  1882,  1882,  1896,  1896,  1905,  1906,  1909,  1910,  1911,
    1918,  1918,  1933,  1933,  1947,  1948,  1951,  1952,  1953,  1958,
    1959,  1960,  1961,  1962,  1963,  1964,  1965,  1966,  1967,  1970,
    1972,  1978,  1980,  1980,  1989,  1989,  1998,  1998,  2007,  2009,
    2009,  2018,  2028,  2028,  2041,  2042,  2047,  2048,  2049,  2056,
    2056,  2068,  2068,  2080,  2081,  2086,  2087,  2088,  2095,  2096,
    2097,  2098,  2099,  2100,  2101,  2102,  2103,  2104,  2105,  2108,
    2110,  2110,  2119,  2121,  2123,  2129,  2135,  2141,  2141,  2155,
    2155,  2168,  2169,  2172,  2173,  2174,  2179,  2179,  2189,  2189,
    2199,  2200,  2201,  2206,  2207,  2208,  2209,  2210,  2211,  2212,
    2213,  2214,  2215,  2218,  2218,  2227,  2233,  2233,  2258,  2258,
    2288,  2288,  2299,  2300,  2303,  2304,  2305,  2310,  2310,  2319,
    2319,  2328,  2329,  2332,  2333,  2334,  2340,  2341,  2342,  2343,
    2344,  2345,  2346,  2347,  2348,  2349,  2350,  2351,  2352,  2353,
    2354,  2357,  2357,  2366,  2366,  2375,  2375,  2384,  2384,  2393,
    2393,  2402,  2402,  2411,  2411,  2420,  2420,  2429,  2429,  2438,
    2438,  2447,  2447,  2461,  2461,  2472,  2475,  2475,  2489,  2489,
    2500,  2501,  2502,  2507,  2507,  2517,  2518,  2521,  2522,  2523,
    2528,  2529,  2530,  2531,  2532,  2533,  2534,  2535,  2536,  2537,
    2538,  2539,  2540,  2541,  2542,  2543,  2544,  2547,  2549,  2549,
    2558,  2558,  2568,  2574,  2582,  2590,  2590,  2602,  2602,  2614,
    2615,  2618,  2619,  2620,  2625,  2625,  2633,  2634,  2635,  2640,
    2641,  2642,  2643,  2644,  2645,  2646,  2647,  2648,  2649,  2650,
    2651,  2652,  2655,  2655,  2664,  2665,  2666,  2669,  2669,  2679,
    2679,  2689,  2695,  2701,  2701,  2712,  2713,  2716,  2717,  2718,
    2723,  2723,  2731,  2732,  2733,  2738,  2739,  2740,  2741,  2742,
    2745,  2745,  2756,  2756,  2769,  2770,  2771,  2776,  2777,  2778,
    2779,  2780,  2781,  2782,  2785,  2785,  2793,  2796,  2796,  2805,
    2805,  2814,  2814,  2825,  2826,  2829,  2830,  2831,  2836,  2836,
    2844,  2845,  2846,  2851,  2852,  2853,  2854,  2855,  2856,  2857,
    2860,  2860,  2869,  2869,  2880,  2880,  2893,  2894,  2895,  2900,
    2901,  2902,  2903,  2904,  2905,  2908,  2914,  2914,  2923,  2929,
    2929,  2939,  2939,  2952,  2952,  2962,  2963,  2964,  2969,  2970,
    2971,  2972,  2973,  2974,  2975,  2976,  2977,  2978,  2979,  2982,
    2988,  2988,  2997,  3003,  3003,  3012,  3018,  3024,  3024,  3033,
    3034,  3037,  3037,  3048,  3048,  3060,  3060,  3070,  3071,  3072,
    3078,  3079,  3082,  3082,  3093,  3101,  3101,  3114,  3115,  3116,
    3122,  3122,  3130,  3131,  3132,  3137,  3138,  3139,  3140,  3141,
    3142,  3143,  3146,  3152,  3152,  3161,  3161,  3172,  3173,  3174,
    3179,  3179,  3187,  3188,  3189,  3194,  3195,  3196,  3197,  3198,
    3201,  3201,  3210,  3216,  3222,  3228,  3228,  3237,  3237,  3248,
    3249,  3250,  3255,  3256,  3257,  3258,  3259,  3262,  3268,  3274,
    3280
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
#line 6869 "dhcp4_parser.cc"

#line 3286 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
