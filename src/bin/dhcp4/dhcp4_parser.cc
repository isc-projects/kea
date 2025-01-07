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

  case 647: // $@88: %empty
#line 2232 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 648: // pool_entry: "pool" $@88 ":" "constant string"
#line 2235 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3513 "dhcp4_parser.cc"
    break;

  case 649: // pool_id: "pool-id" ":" "integer"
#line 2241 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 650: // $@89: %empty
#line 2247 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3531 "dhcp4_parser.cc"
    break;

  case 651: // user_context: "user-context" $@89 ":" map_value
#line 2249 "dhcp4_parser.yy"
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

  case 652: // $@90: %empty
#line 2272 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3566 "dhcp4_parser.cc"
    break;

  case 653: // comment: "comment" $@90 ":" "constant string"
#line 2274 "dhcp4_parser.yy"
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

  case 654: // $@91: %empty
#line 2302 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 655: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2308 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3616 "dhcp4_parser.cc"
    break;

  case 660: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2319 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3624 "dhcp4_parser.cc"
    break;

  case 661: // $@92: %empty
#line 2324 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3634 "dhcp4_parser.cc"
    break;

  case 662: // reservation: "{" $@92 reservation_params "}"
#line 2328 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 663: // $@93: %empty
#line 2333 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 664: // sub_reservation: "{" $@93 reservation_params "}"
#line 2337 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3662 "dhcp4_parser.cc"
    break;

  case 669: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2348 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3670 "dhcp4_parser.cc"
    break;

  case 685: // $@94: %empty
#line 2371 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 686: // next_server: "next-server" $@94 ":" "constant string"
#line 2374 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 687: // $@95: %empty
#line 2380 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3698 "dhcp4_parser.cc"
    break;

  case 688: // server_hostname: "server-hostname" $@95 ":" "constant string"
#line 2383 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 689: // $@96: %empty
#line 2389 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 690: // boot_file_name: "boot-file-name" $@96 ":" "constant string"
#line 2392 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3727 "dhcp4_parser.cc"
    break;

  case 691: // $@97: %empty
#line 2398 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3736 "dhcp4_parser.cc"
    break;

  case 692: // ip_address: "ip-address" $@97 ":" "constant string"
#line 2401 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3746 "dhcp4_parser.cc"
    break;

  case 693: // $@98: %empty
#line 2407 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3755 "dhcp4_parser.cc"
    break;

  case 694: // duid: "duid" $@98 ":" "constant string"
#line 2410 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3765 "dhcp4_parser.cc"
    break;

  case 695: // $@99: %empty
#line 2416 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3774 "dhcp4_parser.cc"
    break;

  case 696: // hw_address: "hw-address" $@99 ":" "constant string"
#line 2419 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3784 "dhcp4_parser.cc"
    break;

  case 697: // $@100: %empty
#line 2425 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3793 "dhcp4_parser.cc"
    break;

  case 698: // client_id_value: "client-id" $@100 ":" "constant string"
#line 2428 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3803 "dhcp4_parser.cc"
    break;

  case 699: // $@101: %empty
#line 2434 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3812 "dhcp4_parser.cc"
    break;

  case 700: // circuit_id_value: "circuit-id" $@101 ":" "constant string"
#line 2437 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3822 "dhcp4_parser.cc"
    break;

  case 701: // $@102: %empty
#line 2443 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3831 "dhcp4_parser.cc"
    break;

  case 702: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2446 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3841 "dhcp4_parser.cc"
    break;

  case 703: // $@103: %empty
#line 2452 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3850 "dhcp4_parser.cc"
    break;

  case 704: // hostname: "hostname" $@103 ":" "constant string"
#line 2455 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3860 "dhcp4_parser.cc"
    break;

  case 705: // $@104: %empty
#line 2461 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 706: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2467 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 707: // $@105: %empty
#line 2475 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 708: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2481 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3902 "dhcp4_parser.cc"
    break;

  case 710: // $@106: %empty
#line 2489 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3914 "dhcp4_parser.cc"
    break;

  case 711: // ip_addresses: "ip-addresses" $@106 ":" list_strings
#line 2495 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3923 "dhcp4_parser.cc"
    break;

  case 712: // $@107: %empty
#line 2503 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3935 "dhcp4_parser.cc"
    break;

  case 713: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2509 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3944 "dhcp4_parser.cc"
    break;

  case 716: // client_classes_list: client_classes_list ","
#line 2516 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3952 "dhcp4_parser.cc"
    break;

  case 717: // $@108: %empty
#line 2521 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3962 "dhcp4_parser.cc"
    break;

  case 718: // client_class_entry: "{" $@108 client_class_params "}"
#line 2525 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3972 "dhcp4_parser.cc"
    break;

  case 723: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2537 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3980 "dhcp4_parser.cc"
    break;

  case 742: // $@109: %empty
#line 2563 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 743: // client_class_test: "test" $@109 ":" "constant string"
#line 2566 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 744: // $@110: %empty
#line 2572 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4008 "dhcp4_parser.cc"
    break;

  case 745: // client_class_template_test: "template-test" $@110 ":" "constant string"
#line 2575 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 746: // only_if_required: "only-if-required" ":" "boolean"
#line 2582 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4028 "dhcp4_parser.cc"
    break;

  case 747: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2588 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 748: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2596 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4048 "dhcp4_parser.cc"
    break;

  case 749: // $@111: %empty
#line 2604 "dhcp4_parser.yy"
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

  case 750: // control_socket: "control-socket" $@111 ":" "{" control_socket_params "}"
#line 2611 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4070 "dhcp4_parser.cc"
    break;

  case 751: // $@112: %empty
#line 2616 "dhcp4_parser.yy"
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

  case 752: // control_sockets: "control-sockets" $@112 ":" "[" control_socket_list "]"
#line 2623 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 757: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2634 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4100 "dhcp4_parser.cc"
    break;

  case 758: // $@113: %empty
#line 2639 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4110 "dhcp4_parser.cc"
    break;

  case 759: // control_socket_entry: "{" $@113 control_socket_params "}"
#line 2643 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4118 "dhcp4_parser.cc"
    break;

  case 762: // control_socket_params: control_socket_params ","
#line 2649 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4126 "dhcp4_parser.cc"
    break;

  case 776: // $@114: %empty
#line 2669 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4135 "dhcp4_parser.cc"
    break;

  case 777: // control_socket_type: "socket-type" $@114 ":" control_socket_type_value
#line 2672 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4144 "dhcp4_parser.cc"
    break;

  case 778: // control_socket_type_value: "unix"
#line 2678 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4150 "dhcp4_parser.cc"
    break;

  case 779: // control_socket_type_value: "http"
#line 2679 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4156 "dhcp4_parser.cc"
    break;

  case 780: // control_socket_type_value: "https"
#line 2680 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4162 "dhcp4_parser.cc"
    break;

  case 781: // $@115: %empty
#line 2683 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4172 "dhcp4_parser.cc"
    break;

  case 782: // control_socket_name: "socket-name" $@115 ":" "constant string"
#line 2687 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 783: // $@116: %empty
#line 2693 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 784: // control_socket_address: "socket-address" $@116 ":" "constant string"
#line 2697 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 785: // control_socket_port: "socket-port" ":" "integer"
#line 2703 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 786: // cert_required: "cert-required" ":" "boolean"
#line 2709 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4222 "dhcp4_parser.cc"
    break;

  case 787: // $@117: %empty
#line 2715 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 788: // http_headers: "http-headers" $@117 ":" "[" http_header_list "]"
#line 2721 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4243 "dhcp4_parser.cc"
    break;

  case 793: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2732 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4251 "dhcp4_parser.cc"
    break;

  case 794: // $@118: %empty
#line 2737 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4261 "dhcp4_parser.cc"
    break;

  case 795: // http_header: "{" $@118 http_header_params "}"
#line 2741 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4269 "dhcp4_parser.cc"
    break;

  case 798: // http_header_params: http_header_params ","
#line 2747 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4277 "dhcp4_parser.cc"
    break;

  case 804: // $@119: %empty
#line 2759 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4286 "dhcp4_parser.cc"
    break;

  case 805: // header_value: "value" $@119 ":" "constant string"
#line 2762 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4296 "dhcp4_parser.cc"
    break;

  case 806: // $@120: %empty
#line 2770 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4308 "dhcp4_parser.cc"
    break;

  case 807: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2776 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4319 "dhcp4_parser.cc"
    break;

  case 810: // auth_params: auth_params ","
#line 2785 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4327 "dhcp4_parser.cc"
    break;

  case 818: // $@121: %empty
#line 2799 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4336 "dhcp4_parser.cc"
    break;

  case 819: // auth_type: "type" $@121 ":" auth_type_value
#line 2802 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4345 "dhcp4_parser.cc"
    break;

  case 820: // auth_type_value: "basic"
#line 2807 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4351 "dhcp4_parser.cc"
    break;

  case 821: // $@122: %empty
#line 2810 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4360 "dhcp4_parser.cc"
    break;

  case 822: // realm: "realm" $@122 ":" "constant string"
#line 2813 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4370 "dhcp4_parser.cc"
    break;

  case 823: // $@123: %empty
#line 2819 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4379 "dhcp4_parser.cc"
    break;

  case 824: // directory: "directory" $@123 ":" "constant string"
#line 2822 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4389 "dhcp4_parser.cc"
    break;

  case 825: // $@124: %empty
#line 2828 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 826: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2834 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4410 "dhcp4_parser.cc"
    break;

  case 831: // not_empty_clients_list: not_empty_clients_list ","
#line 2845 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4418 "dhcp4_parser.cc"
    break;

  case 832: // $@125: %empty
#line 2850 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4428 "dhcp4_parser.cc"
    break;

  case 833: // basic_auth: "{" $@125 clients_params "}"
#line 2854 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 836: // clients_params: clients_params ","
#line 2860 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4444 "dhcp4_parser.cc"
    break;

  case 844: // $@126: %empty
#line 2874 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 845: // user_file: "user-file" $@126 ":" "constant string"
#line 2877 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 846: // $@127: %empty
#line 2883 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4472 "dhcp4_parser.cc"
    break;

  case 847: // password_file: "password-file" $@127 ":" "constant string"
#line 2886 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 848: // $@128: %empty
#line 2894 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4494 "dhcp4_parser.cc"
    break;

  case 849: // dhcp_queue_control: "dhcp-queue-control" $@128 ":" "{" queue_control_params "}"
#line 2900 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 852: // queue_control_params: queue_control_params ","
#line 2909 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4513 "dhcp4_parser.cc"
    break;

  case 859: // enable_queue: "enable-queue" ":" "boolean"
#line 2922 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4523 "dhcp4_parser.cc"
    break;

  case 860: // $@129: %empty
#line 2928 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 861: // queue_type: "queue-type" $@129 ":" "constant string"
#line 2931 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 862: // capacity: "capacity" ":" "integer"
#line 2937 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 863: // $@130: %empty
#line 2943 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 864: // arbitrary_map_entry: "constant string" $@130 ":" value
#line 2946 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4570 "dhcp4_parser.cc"
    break;

  case 865: // $@131: %empty
#line 2953 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4582 "dhcp4_parser.cc"
    break;

  case 866: // dhcp_ddns: "dhcp-ddns" $@131 ":" "{" dhcp_ddns_params "}"
#line 2959 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4593 "dhcp4_parser.cc"
    break;

  case 867: // $@132: %empty
#line 2966 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4603 "dhcp4_parser.cc"
    break;

  case 868: // sub_dhcp_ddns: "{" $@132 dhcp_ddns_params "}"
#line 2970 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4613 "dhcp4_parser.cc"
    break;

  case 871: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2978 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4621 "dhcp4_parser.cc"
    break;

  case 883: // enable_updates: "enable-updates" ":" "boolean"
#line 2996 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4631 "dhcp4_parser.cc"
    break;

  case 884: // $@133: %empty
#line 3002 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4640 "dhcp4_parser.cc"
    break;

  case 885: // server_ip: "server-ip" $@133 ":" "constant string"
#line 3005 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4650 "dhcp4_parser.cc"
    break;

  case 886: // server_port: "server-port" ":" "integer"
#line 3011 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4660 "dhcp4_parser.cc"
    break;

  case 887: // $@134: %empty
#line 3017 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4669 "dhcp4_parser.cc"
    break;

  case 888: // sender_ip: "sender-ip" $@134 ":" "constant string"
#line 3020 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4679 "dhcp4_parser.cc"
    break;

  case 889: // sender_port: "sender-port" ":" "integer"
#line 3026 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4689 "dhcp4_parser.cc"
    break;

  case 890: // max_queue_size: "max-queue-size" ":" "integer"
#line 3032 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4699 "dhcp4_parser.cc"
    break;

  case 891: // $@135: %empty
#line 3038 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 892: // ncr_protocol: "ncr-protocol" $@135 ":" ncr_protocol_value
#line 3041 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4717 "dhcp4_parser.cc"
    break;

  case 893: // ncr_protocol_value: "udp"
#line 3047 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4723 "dhcp4_parser.cc"
    break;

  case 894: // ncr_protocol_value: "tcp"
#line 3048 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4729 "dhcp4_parser.cc"
    break;

  case 895: // $@136: %empty
#line 3051 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4738 "dhcp4_parser.cc"
    break;

  case 896: // ncr_format: "ncr-format" $@136 ":" "JSON"
#line 3054 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4748 "dhcp4_parser.cc"
    break;

  case 897: // $@137: %empty
#line 3062 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4760 "dhcp4_parser.cc"
    break;

  case 898: // config_control: "config-control" $@137 ":" "{" config_control_params "}"
#line 3068 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4770 "dhcp4_parser.cc"
    break;

  case 899: // $@138: %empty
#line 3074 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4780 "dhcp4_parser.cc"
    break;

  case 900: // sub_config_control: "{" $@138 config_control_params "}"
#line 3078 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4789 "dhcp4_parser.cc"
    break;

  case 903: // config_control_params: config_control_params ","
#line 3086 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4797 "dhcp4_parser.cc"
    break;

  case 906: // $@139: %empty
#line 3096 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4809 "dhcp4_parser.cc"
    break;

  case 907: // config_databases: "config-databases" $@139 ":" "[" database_list "]"
#line 3102 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4818 "dhcp4_parser.cc"
    break;

  case 908: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3107 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4828 "dhcp4_parser.cc"
    break;

  case 909: // $@140: %empty
#line 3115 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4840 "dhcp4_parser.cc"
    break;

  case 910: // loggers: "loggers" $@140 ":" "[" loggers_entries "]"
#line 3121 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4849 "dhcp4_parser.cc"
    break;

  case 913: // loggers_entries: loggers_entries ","
#line 3130 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4857 "dhcp4_parser.cc"
    break;

  case 914: // $@141: %empty
#line 3136 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4867 "dhcp4_parser.cc"
    break;

  case 915: // logger_entry: "{" $@141 logger_params "}"
#line 3140 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4875 "dhcp4_parser.cc"
    break;

  case 918: // logger_params: logger_params ","
#line 3146 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4883 "dhcp4_parser.cc"
    break;

  case 926: // debuglevel: "debuglevel" ":" "integer"
#line 3160 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4893 "dhcp4_parser.cc"
    break;

  case 927: // $@142: %empty
#line 3166 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4902 "dhcp4_parser.cc"
    break;

  case 928: // severity: "severity" $@142 ":" "constant string"
#line 3169 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4912 "dhcp4_parser.cc"
    break;

  case 929: // $@143: %empty
#line 3175 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4924 "dhcp4_parser.cc"
    break;

  case 930: // output_options_list: "output-options" $@143 ":" "[" output_options_list_content "]"
#line 3181 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4933 "dhcp4_parser.cc"
    break;

  case 933: // output_options_list_content: output_options_list_content ","
#line 3188 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4941 "dhcp4_parser.cc"
    break;

  case 934: // $@144: %empty
#line 3193 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4951 "dhcp4_parser.cc"
    break;

  case 935: // output_entry: "{" $@144 output_params_list "}"
#line 3197 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4959 "dhcp4_parser.cc"
    break;

  case 938: // output_params_list: output_params_list ","
#line 3203 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4967 "dhcp4_parser.cc"
    break;

  case 944: // $@145: %empty
#line 3215 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4976 "dhcp4_parser.cc"
    break;

  case 945: // output: "output" $@145 ":" "constant string"
#line 3218 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4986 "dhcp4_parser.cc"
    break;

  case 946: // flush: "flush" ":" "boolean"
#line 3224 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4996 "dhcp4_parser.cc"
    break;

  case 947: // maxsize: "maxsize" ":" "integer"
#line 3230 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5006 "dhcp4_parser.cc"
    break;

  case 948: // maxver: "maxver" ":" "integer"
#line 3236 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5016 "dhcp4_parser.cc"
    break;

  case 949: // $@146: %empty
#line 3242 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5025 "dhcp4_parser.cc"
    break;

  case 950: // pattern: "pattern" $@146 ":" "constant string"
#line 3245 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5035 "dhcp4_parser.cc"
    break;

  case 951: // $@147: %empty
#line 3251 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5047 "dhcp4_parser.cc"
    break;

  case 952: // compatibility: "compatibility" $@147 ":" "{" compatibility_params "}"
#line 3257 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5056 "dhcp4_parser.cc"
    break;

  case 955: // compatibility_params: compatibility_params ","
#line 3264 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5064 "dhcp4_parser.cc"
    break;

  case 961: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3276 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5074 "dhcp4_parser.cc"
    break;

  case 962: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3282 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5084 "dhcp4_parser.cc"
    break;

  case 963: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3288 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5094 "dhcp4_parser.cc"
    break;

  case 964: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3294 "dhcp4_parser.yy"
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


  const short Dhcp4Parser::yypact_ninf_ = -1401;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     508, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,    22,    39,    44,    48,    54,   133,
     157,   209,   224,   235,   252,   260,   277,   306, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,    39,  -181,   184,   727,    72,   168,
     368,   211,   123,    78,   305,   -93,   485,    80, -1401,    63,
     114,   293,   304,   318, -1401,    42, -1401, -1401, -1401, -1401,
     350,   351,   364, -1401, -1401, -1401,   365,   380, -1401, -1401,
   -1401,   389,   393,   395,   407,   409,   413,   426,   432,   440,
     449,   469, -1401,   470,   472,   474,   479,   483, -1401, -1401,
   -1401,   484,   488,   493,   495,   499,   505,   506, -1401, -1401,
   -1401,   507, -1401, -1401, -1401, -1401, -1401,   509,   511,   513,
   -1401, -1401, -1401, -1401, -1401,   515, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,   516,   522,   525, -1401, -1401,   528, -1401,
      62, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   529,   532,   534,   536,
   -1401,    98, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,   537, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401,   116, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
     542, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401,   124, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,   378,
     466, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,   540, -1401, -1401,   546, -1401, -1401, -1401,
     547, -1401, -1401,   544,   550, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,   551,   554,
     556, -1401, -1401, -1401, -1401, -1401,   560,   559, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,   139, -1401, -1401, -1401,   566, -1401,   571, -1401,
     572,   573, -1401, -1401, -1401, -1401, -1401,   151, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,   574,   154,
   -1401, -1401, -1401, -1401,    39,    39, -1401,   349,   576, -1401,
   -1401,   577,   578,   579,   352,   355,   357,   588,   589,   590,
     374,   362,   592,   596,   602,   377,   379,   383,   386,   387,
     388,   391,   399,   401,   396,   415,   634,   420,   423,   411,
     416,   419,   651,   652,   653,   429,   444,   427,   433,   436,
     447,   450,   661,   676,   678,   453,   681,   698,   699,   707,
     708,   480,   481,   486,   714,   717,   718,   719,   741,   517,
     742,   743,   745,   746,   748,   750,   751,   535,   538,   539,
     763,   765, -1401,   727, -1401,   766,   769,   770,   543,   545,
     548,   549,    72, -1401,   771,   773,   777,   778,   779,   780,
     557,   781,   815,   816,   817,   820,   168, -1401,   821,   595,
     368, -1401,   823,   824,   825,   826,   827,   828,   829,   833,
   -1401,   211, -1401,   834,   835,   609,   838,   839,   842,   614,
   -1401,    78,   844,   621,   622,   623,   853, -1401,   305,   857,
     859,   -42, -1401,   631,   861,   635,   863,   637,   638,   866,
     867,   485, -1401,   869,   643,    80, -1401, -1401, -1401,   872,
     871,   873,   874,   877, -1401, -1401, -1401,   649,   655,   656,
   -1401, -1401,   882,   883,   886, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   662, -1401, -1401, -1401,
   -1401, -1401,   -81,   663,   664, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,   890,   891,   892, -1401,   668,   369,   894,   893,
     671, -1401, -1401, -1401,   897,   898,   899,   900,   901, -1401,
     902,   904,   907,   906,   910,   677,   684, -1401, -1401, -1401,
     913,   912, -1401,   915,   113,   187, -1401, -1401, -1401, -1401,
   -1401,   691,   692,   693,   919,   701,   702, -1401,   915,   915,
     915,   703,   927, -1401,   705, -1401, -1401,   915,   706,   710,
     711,   712,   713,   715,   716, -1401,   720,   721, -1401,   722,
     723,   724, -1401, -1401,   725, -1401, -1401, -1401,   915, -1401,
     726,   893, -1401, -1401,   728, -1401,   729, -1401, -1401,    18,
     744, -1401,   933, -1401, -1401,    39,   727,    80,    72,   247,
   -1401, -1401, -1401,   647,   647,   937, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401,   940,   941,   942, -1401, -1401,
   -1401, -1401, -1401, -1401,   954, -1401, -1401, -1401,    88,   955,
     956,   961,   309,   -50,   798,   962,   161,   485, -1401, -1401,
     963,    -1, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,   964, -1401, -1401, -1401, -1401, -1401, -1401,
     832, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401,   937, -1401,   162,   183,   189,
   -1401, -1401,   201, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
     968,   969,   973,   974,   975,   976,   977,   978,   979,   980,
   -1401,   981,   982, -1401, -1401, -1401, -1401, -1401,   216, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,   265, -1401,   983,   984, -1401, -1401,   985,   989,
   -1401, -1401,   988,   992, -1401, -1401,   996,   995, -1401, -1401,
     999,  1003, -1401, -1401, -1401, -1401, -1401, -1401,   166, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   214, -1401, -1401,  1006,
    1011, -1401, -1401,  1009,  1014, -1401,  1016,  1017,  1028,  1034,
    1037,  1039,   290, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
    1042,  1047,  1050, -1401,   296, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,  1051, -1401,  1057, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,   297, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,  1069,  1073, -1401,  1074, -1401,  1079,
   -1401, -1401, -1401,   307, -1401, -1401, -1401, -1401, -1401,   332,
   -1401,   303, -1401,  1080,  1081,  1087,  1089, -1401,   382, -1401,
   -1401, -1401, -1401, -1401,   758, -1401,  1090,  1098, -1401, -1401,
    1110, -1401,  1118, -1401, -1401, -1401,  1124,  1130,   247, -1401,
    1135,  1152,  1162,  1168,   943,   946,   950,   949,   953,   958,
     960,   965,   966,   970,  1181,   959,   971,  1182,  1183,  1190,
    1191,   647, -1401, -1401,   647, -1401,   937,   168, -1401,   940,
      78, -1401,   941,   305, -1401,   942,   292, -1401,   954,    88,
   -1401,  1378,   955, -1401,   211, -1401,   956,   -93, -1401,   961,
     986,   987,   990,   991,   993,   994,   309, -1401,   997,   998,
    1000,   -50, -1401,  1195,  1200,  1202,  1001,  1203,  1002,  1204,
     798, -1401,   798, -1401,   962,  1004,  1205,  1005,  1207,   161,
   -1401, -1401,   -19,   963, -1401,  1007,  1008,  1010,  1013,    -1,
   -1401, -1401,  1206,  1210,   368, -1401,   964,  1211, -1401, -1401,
    1012,  1018, -1401,  1020,  1021,  1023,  1024, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401,   289, -1401, -1401,
    1025,  1027,  1030,  1032, -1401,   384, -1401,   418, -1401,  1208,
   -1401,  1212, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,   421, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401,  1215,  1219, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,  1218,  1224, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401,  1220, -1401,   424, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   342,  1033,  1035, -1401,
    1226, -1401,  1209, -1401,   425, -1401, -1401,  1036, -1401,    39,
   -1401, -1401,  1230, -1401, -1401, -1401, -1401, -1401,   431, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
    1040,   434, -1401,   915, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,   292, -1401,  1234,  1235,  1041,  1043, -1401,  1378,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,    50,  1237,
   -1401, -1401, -1401,  1243,  1046,  1254,   -19, -1401, -1401, -1401,
   -1401, -1401,  1048,  1049, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,   435, -1401, -1401, -1401, -1401, -1401,
   -1401,  1261,  1269, -1401,  1276, -1401,  1052, -1401, -1401, -1401,
    1281,  1284,  1285,  1286,    50, -1401,   -37, -1401,  1237,  1288,
   -1401,  1121,  1063,  1066,  1292, -1401, -1401, -1401, -1401, -1401,
   -1401,   437, -1401, -1401, -1401, -1401,   465, -1401, -1401, -1401,
   -1401, -1401,  1291,  1296,   -37, -1401,   109,  1288, -1401, -1401,
    1295,  1299, -1401,  1076, -1401, -1401,  1300,  1306,  1307, -1401,
     462, -1401, -1401, -1401, -1401, -1401, -1401, -1401,   164, -1401,
    1291, -1401,  1310,  1070,  1085,  1088,  1314,   109, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   464, -1401, -1401, -1401,
   -1401,  1091, -1401, -1401, -1401,  1093, -1401,  1316,  1320,   164,
   -1401, -1401, -1401,  1096,  1099, -1401, -1401, -1401
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   214,     9,   391,    11,   618,    13,
     663,    15,   533,    17,   542,    19,   581,    21,   353,    23,
     867,    25,   899,    27,    46,    39,     0,     0,     0,     0,
       0,   665,     0,   544,   583,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   897,   199,   232,
       0,     0,     0,   685,   687,   689,     0,     0,   230,   243,
     245,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,   164,   171,
     173,     0,     0,     0,     0,     0,     0,     0,   382,   531,
     572,     0,   156,   177,   471,   650,   652,     0,     0,     0,
     315,   712,   654,   344,   365,     0,   330,   749,   751,   848,
     865,   187,   189,     0,     0,     0,   909,   951,     0,   141,
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
     463,   465,   459,   707,   448,   396,   397,   398,   399,   400,
     425,   426,   427,   428,   429,   446,   415,   416,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   447,     0,   393,   403,   420,   421,
     422,   404,   406,   407,   408,   409,   411,   412,   413,   405,
     401,   402,   423,   424,   410,   417,   418,   419,   414,   647,
       0,   646,   630,   631,   632,   633,   634,   635,   636,   637,
     638,   639,   640,   641,   642,   643,   626,   627,   628,   629,
     625,     0,   620,   623,   624,   644,   645,   705,   691,   693,
     695,   699,   697,   703,   701,   684,   678,   682,   683,     0,
     666,   667,   679,   680,   681,   675,   670,   676,   672,   673,
     674,   677,   671,     0,   562,   289,     0,   566,   564,   569,
       0,   558,   559,     0,   545,   546,   549,   561,   550,   551,
     552,   568,   553,   554,   555,   556,   557,   600,     0,     0,
       0,   607,   598,   599,   602,   603,     0,   584,   585,   588,
     589,   590,   591,   592,   593,   594,   597,   595,   596,   361,
     363,   358,     0,   355,   359,   360,     0,   884,     0,   887,
       0,     0,   891,   895,   882,   880,   881,     0,   869,   872,
     873,   874,   875,   876,   877,   878,   879,   906,     0,     0,
     901,   904,   905,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    69,    66,     0,     0,     0,     0,     0,
       0,     0,   203,   215,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   395,   392,     0,     0,
     622,   619,     0,     0,     0,     0,     0,     0,     0,     0,
     664,   669,   534,     0,     0,     0,     0,     0,     0,     0,
     543,   548,     0,     0,     0,     0,     0,   582,   587,     0,
       0,   357,   354,     0,     0,     0,     0,     0,     0,     0,
       0,   871,   868,     0,     0,   903,   900,    49,    41,     0,
       0,     0,     0,     0,   158,   159,   160,     0,     0,     0,
     197,   198,     0,     0,     0,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     0,   192,   193,   161,
     162,   163,     0,     0,     0,   175,   176,   183,   184,   185,
     186,   191,     0,     0,     0,   155,     0,     0,     0,     0,
       0,   467,   468,   469,     0,     0,     0,     0,     0,   748,
       0,     0,     0,     0,     0,     0,     0,   194,   195,   196,
       0,     0,    68,     0,     0,     0,   226,   227,   228,   229,
     202,     0,     0,     0,     0,     0,     0,   470,     0,     0,
       0,     0,     0,   394,     0,   649,   621,     0,     0,     0,
       0,     0,     0,     0,     0,   668,     0,     0,   560,     0,
       0,     0,   571,   547,     0,   604,   605,   606,     0,   586,
       0,     0,   356,   883,     0,   886,     0,   889,   890,     0,
       0,   870,     0,   908,   902,     0,     0,     0,     0,     0,
     686,   688,   690,     0,     0,   247,   154,   166,   167,   168,
     169,   170,   165,   172,   174,   384,   535,   574,   157,   179,
     180,   181,   182,   178,   473,    38,   651,   653,     0,     0,
     656,   346,     0,     0,     0,   753,     0,     0,   188,   190,
       0,     0,    51,   217,   220,   221,   219,   224,   225,   223,
     452,   454,   456,   611,   450,   458,   462,   464,   466,   460,
       0,   648,   706,   692,   694,   696,   700,   698,   704,   702,
     563,   290,   567,   565,   570,   601,   608,   362,   364,   885,
     888,   893,   894,   892,   896,   247,    42,     0,     0,     0,
     239,   241,     0,   234,   237,   238,   280,   282,   284,   286,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,     0,     0,   307,   309,   311,   313,   279,     0,   254,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,     0,   252,     0,   248,   249,   389,     0,   385,
     386,   540,     0,   536,   537,   579,     0,   575,   576,   478,
       0,   474,   475,   325,   326,   327,   328,   329,     0,   317,
     320,   321,   322,   323,   324,   717,     0,   714,   661,     0,
     657,   658,   351,     0,   347,   348,     0,     0,     0,     0,
       0,     0,     0,   367,   370,   371,   372,   373,   374,   375,
       0,     0,     0,   340,     0,   332,   335,   336,   337,   338,
     339,   776,   781,   783,     0,   806,     0,   787,   775,   768,
     769,   770,   773,   774,     0,   760,   763,   764,   765,   766,
     771,   772,   767,   758,     0,   754,   755,     0,   860,     0,
     863,   856,   857,     0,   850,   853,   854,   855,   858,     0,
     914,     0,   911,     0,     0,     0,     0,   960,     0,   953,
     956,   957,   958,   959,    53,   616,     0,   612,   613,   710,
       0,   709,     0,    62,   898,   200,     0,     0,   236,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   256,   231,   244,     0,   246,   251,     0,   383,   388,
     544,   532,   539,   583,   573,   578,     0,   472,   477,   319,
     316,   719,   716,   713,   665,   655,   660,     0,   345,   350,
       0,     0,     0,     0,     0,     0,   369,   366,     0,     0,
       0,   334,   331,     0,     0,     0,     0,     0,     0,     0,
     762,   750,     0,   752,   757,     0,     0,     0,     0,   852,
     849,   866,     0,   913,   910,     0,     0,     0,     0,   955,
     952,    55,     0,    54,     0,   610,   615,     0,   708,   907,
       0,     0,   235,     0,     0,     0,     0,   288,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,   305,   306,
       0,     0,     0,     0,   255,     0,   250,     0,   387,     0,
     538,     0,   577,   530,   502,   503,   504,   486,   487,   507,
     508,   509,   510,   511,   528,   489,   490,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   529,   483,   484,   485,   498,   499,   500,
     501,   495,   496,   497,     0,   480,   488,   505,   506,   491,
     492,   493,   494,   476,   318,   742,   744,     0,     0,   736,
     737,   738,   739,   740,   741,   729,   730,   734,   735,   731,
     732,   733,     0,   720,   721,   724,   725,   726,   727,   728,
     715,     0,   659,     0,   349,   376,   377,   378,   379,   380,
     381,   368,   341,   342,   343,   333,     0,     0,     0,   785,
       0,   786,     0,   761,     0,   756,   859,     0,   862,     0,
     851,   929,     0,   927,   925,   919,   923,   924,     0,   916,
     921,   922,   920,   912,   961,   962,   963,   964,   954,    52,
      57,     0,   614,     0,   240,   242,   281,   283,   285,   287,
     302,   303,   304,   301,   308,   310,   312,   314,   253,   390,
     541,   580,   482,   479,     0,     0,     0,     0,   718,   723,
     662,   352,   778,   779,   780,   777,   782,   784,     0,   789,
     759,   861,   864,     0,     0,     0,   918,   915,    56,   617,
     711,   481,     0,     0,   746,   747,   722,   818,   821,   823,
     825,   817,   816,   815,     0,   808,   811,   812,   813,   814,
     794,     0,   790,   791,     0,   926,     0,   917,   743,   745,
       0,     0,     0,     0,   810,   807,     0,   788,   793,     0,
     928,     0,     0,     0,     0,   809,   804,   803,   799,   801,
     802,     0,   796,   800,   792,   934,     0,   931,   820,   819,
     822,   824,   827,     0,   798,   795,     0,   933,   930,   832,
       0,   828,   829,     0,   797,   944,     0,     0,     0,   949,
       0,   936,   939,   940,   941,   942,   943,   932,     0,   826,
     831,   805,     0,     0,     0,     0,     0,   938,   935,   844,
     846,   843,   837,   839,   841,   842,     0,   834,   838,   840,
     830,     0,   946,   947,   948,     0,   937,     0,     0,   836,
     833,   945,   950,     0,     0,   835,   845,   847
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401,   -59, -1401,  -628, -1401,   605,
   -1401, -1401, -1401, -1401, -1401, -1401,  -665, -1401, -1401, -1401,
     -67, -1401, -1401, -1401, -1401, -1401, -1401, -1401,   587,   805,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
   -1401, -1401, -1401, -1401,    94, -1401, -1401,    97,   102,   -13,
      13,    41,    51, -1401, -1401,    53, -1401,    56, -1401,    59,
     104,    64, -1401, -1401,    66,    69,    74,    76,    79, -1401,
      81, -1401,   105, -1401, -1401, -1401, -1401, -1401,    43, -1401,
   -1401, -1401,   594,   802, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,   312, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,   512, -1401,   295, -1401,  -738,   298, -1401, -1401,
   -1400, -1401, -1370, -1401, -1401, -1401, -1401,   -63, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,  -770, -1401,  -769, -1401,  -766, -1401, -1401,
   -1401, -1401, -1401, -1401,   279, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,   255, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401,   275, -1401, -1401, -1401,   280,   767, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,   270, -1401, -1401, -1401, -1401, -1401,
   -1401, -1049, -1401, -1401, -1401,   300, -1401, -1401, -1401,   310,
     808, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1047,
   -1401,   -29, -1401,   -18, -1401,    -4, -1401,     5, -1401,   107,
     110,   112, -1401, -1401, -1401, -1401, -1401,   301, -1401, -1401,
      58,   -60, -1401, -1401, -1401, -1401, -1401,   311, -1401, -1401,
   -1401,   314, -1401,   785, -1401,   -34, -1401, -1401, -1401, -1401,
   -1401,   -27, -1401, -1401, -1401, -1401, -1401,   -32, -1401, -1401,
   -1401,   315, -1401, -1401, -1401,   319, -1401,   784, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,   249, -1401, -1401, -1401,   259,   830, -1401, -1401,
   -1401,   -44, -1401,     3, -1401,   -56, -1401, -1401, -1401,   313,
   -1401, -1401, -1401,   320, -1401,   814,   -48, -1401,    -7, -1401,
      15, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1046, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   323, -1401, -1401, -1401,
      68, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401,   316, -1401,   321,   302, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401,    19, -1401, -1401,     1, -1401, -1401, -1401, -1401,
   -1401,    26, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401,   -22, -1401, -1401,   -41, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,   317, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401,   640,   831, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401,   674,   836, -1401, -1401, -1401, -1401,
   -1401, -1401,   322, -1401, -1401,    93, -1401, -1401, -1401, -1401,
   -1401, -1401,    21, -1401, -1401,   -12, -1401, -1401, -1401, -1401,
   -1401, -1401, -1401, -1401, -1401, -1401,   326, -1401, -1401, -1401,
   -1401
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   776,
      82,    83,    39,    64,    79,    80,   793,  1014,  1122,  1123,
     867,    41,    66,    85,   458,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   486,   174,   175,   506,   176,   177,   178,   179,
     180,   181,   182,   492,   762,   183,   493,   184,   494,   185,
     186,   187,   507,   773,   188,   189,   190,   191,   192,   525,
     193,   526,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   462,   241,   242,    45,    68,   243,   535,   244,   536,
     796,   245,   537,   799,   246,   247,   248,   249,   203,   472,
     204,   463,   842,   843,   844,  1026,   845,  1027,   205,   473,
     206,   474,   894,   895,   896,  1054,   868,   869,   870,  1030,
     871,  1031,   872,  1032,   873,  1033,   874,   875,   574,   876,
     877,   878,   879,   880,   881,   882,   883,   884,   885,  1044,
    1303,   886,   887,   888,  1047,   889,  1048,   890,  1049,   891,
    1050,   207,   514,   918,   919,   920,   921,   922,   923,   924,
     208,   520,   954,   955,   956,   957,   958,   209,   517,   933,
     934,   935,  1077,    59,    75,   422,   423,   424,   589,   425,
     590,   210,   518,   942,   943,   944,   945,   946,   947,   948,
     949,   211,   502,   898,   899,   900,  1057,    47,    69,   295,
     296,   297,   548,   298,   544,   299,   545,   300,   546,   301,
     549,   302,   554,   303,   551,   304,   552,   305,   553,   212,
     213,   214,   309,   215,   508,   910,   911,   912,  1066,  1204,
    1205,   216,   503,    53,    72,   902,   903,   904,  1060,    55,
      73,   383,   384,   385,   386,   387,   388,   389,   573,   390,
     577,   391,   576,   392,   393,   578,   394,   217,   504,   906,
     907,   908,  1063,    57,    74,   406,   407,   408,   409,   410,
     582,   411,   412,   413,   414,   415,   416,   586,   311,   547,
    1016,  1017,  1018,  1124,    49,    70,   341,   342,   343,   558,
     344,   218,   509,   219,   510,   220,   516,   929,   930,   931,
    1074,    51,    71,   359,   360,   361,   221,   467,   222,   468,
     223,   469,   365,   563,   366,   564,   367,   565,   368,   567,
     369,   566,   370,   569,   371,   568,   372,   562,   318,   555,
    1020,  1021,  1127,   224,   515,   926,   927,  1071,  1232,  1233,
    1234,  1235,  1236,  1314,  1237,  1315,  1238,  1239,   225,   226,
     521,   227,   522,   984,   985,   986,  1102,   974,   975,   976,
    1093,  1325,   977,  1094,   978,  1095,   979,   980,   981,  1099,
    1361,  1362,  1363,  1376,  1391,  1392,  1393,  1403,   982,  1097,
    1354,  1355,  1356,  1370,  1399,  1357,  1371,  1358,  1372,  1359,
    1373,  1410,  1411,  1412,  1428,  1446,  1447,  1448,  1457,  1449,
    1458,   228,   523,   993,   994,   995,   996,  1106,   997,   998,
    1108,   229,   524,    61,    76,   437,   438,   439,   440,   594,
     441,   442,   596,   443,   444,   445,   599,   833,   446,   600,
     230,   461,    63,    77,   449,   450,   451,   603,   452,   231,
     530,  1001,  1002,  1112,  1278,  1279,  1280,  1281,  1335,  1282,
    1333,  1396,  1397,  1406,  1420,  1421,  1422,  1432,  1423,  1424,
    1425,  1426,  1436,   232,   531,  1008,  1009,  1010,  1011,  1012,
    1013
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   321,   355,    78,   381,   402,   421,   434,
     382,   403,   373,   314,   969,   970,   892,  1195,   971,  1196,
    1212,   315,    28,   362,   250,   312,   345,   357,  1442,   395,
     417,   775,   435,   806,   807,   808,   831,   310,   340,   356,
     404,   336,   812,   268,    29,   459,    30,   405,    31,    81,
     460,    40,   337,   419,   420,    42,   278,   322,  1443,  1442,
     375,    44,   316,   826,   363,   533,   338,   135,   136,   453,
     534,   251,   313,   346,   358,   339,   396,   418,   375,   436,
     135,   136,   279,   323,   317,   265,   364,   233,   234,  1443,
    1347,   235,   447,   448,   236,   237,   238,   239,   135,   136,
     266,   542,   267,   775,   419,   420,   543,   950,   951,   952,
     280,   324,   294,   757,   758,   759,   760,   454,   374,   556,
     281,   325,   282,   326,   557,   283,   327,   560,   284,   328,
     794,   795,   561,   286,   329,   287,   330,   158,   288,   331,
      46,  1386,   591,   289,   332,   290,   333,   592,   291,   334,
     292,   335,   761,   269,   601,   270,   271,   605,   272,   602,
     273,   274,   606,   275,    48,   533,   276,   135,   136,  1069,
    1023,   277,  1070,   285,   293,   375,   306,   376,   377,   307,
     158,   308,   378,   379,   380,  1271,   605,  1272,  1273,   135,
     136,  1024,   542,   158,    84,   135,   136,  1025,    91,    92,
      93,    94,    95,    96,  1028,   847,   848,   797,   798,  1029,
     832,   158,  1003,  1004,  1005,  1006,    50,  1072,   129,  1051,
    1073,  1348,  1349,  1350,  1052,   913,   914,   915,   916,   158,
     917,    52,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,    54,    93,    94,    95,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    56,
     252,   253,   254,  1195,   130,  1196,  1212,    58,  1051,    32,
      33,    34,    35,  1053,   840,   841,   132,   133,   135,   136,
     158,   135,   136,   255,    60,   135,   136,   256,   257,   258,
     137,   138,   139,  1086,   259,   260,   261,   455,  1087,  1091,
    1100,   262,   158,   142,  1092,  1101,  1113,   130,   158,  1114,
    1109,   263,   456,    62,  1415,  1110,  1155,  1416,  1417,  1418,
    1419,   457,    91,    92,    93,    94,    95,    96,   135,   136,
     969,   970,   969,   970,   971,   601,   971,   347,  1439,  1440,
    1111,   987,   988,   989,  1300,  1301,  1302,   348,   349,   350,
     351,   352,   353,   354,   464,   465,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   151,   152,   466,   470,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   471,  1119,   570,  1051,   130,   375,
    1120,   990,  1308,   475,   158,   607,   608,   476,   158,   477,
     132,   133,   375,   397,   376,   377,   398,   399,   400,   135,
     136,   478,   257,   479,   137,   138,   139,   480,   259,   260,
     261,   556,   135,   136,  1312,   262,  1309,   591,  1100,  1313,
     481,   401,  1321,  1330,  1336,   263,   482,   560,  1374,  1337,
    1404,   158,  1339,  1375,   483,  1405,   115,   116,   117,   118,
     119,   120,   121,   484,   123,   124,   125,   126,   936,   937,
     938,   939,   940,   941,   130,  1437,   159,  1459,  1407,   571,
    1438,  1408,  1460,   485,   487,   240,   488,   133,   489,   769,
     770,   771,   772,   490,   319,   135,   136,   491,   495,   264,
     151,   152,   496,   321,   259,   260,   261,   497,   250,   498,
     314,   262,   320,   499,   355,  1322,  1323,  1324,   315,   500,
     501,   505,   312,   511,   381,   512,   345,   513,   382,   519,
     527,   402,   158,   362,   310,   403,   528,   357,   340,   529,
     268,   336,   532,   538,   434,   158,   539,   395,   540,   356,
     541,   550,   337,   278,   417,   251,   559,   322,   572,   316,
     575,   579,   580,   581,   404,   583,   338,   435,   584,   313,
     585,   405,   588,   346,   363,   339,   151,   152,   587,   279,
     593,   317,   265,   323,   358,   595,   597,   598,   604,   609,
     610,   611,   612,   613,   396,   614,   364,   266,   615,   267,
     616,   418,   617,   618,   619,   621,   622,   280,   158,   294,
     623,   324,   135,   136,   436,   620,   624,   281,   625,   282,
     626,   325,   283,   326,   627,   284,   327,   628,   629,   328,
     286,   630,   287,   631,   329,   288,   330,   634,  1340,   331,
     289,   632,   290,   633,   332,   291,   333,   292,   636,   334,
     269,   335,   270,   271,   639,   272,   635,   273,   274,   640,
     275,   637,   641,   276,   638,   642,   643,   644,   277,   647,
     285,   293,   645,   306,   648,   652,   307,   649,   308,   426,
     427,   428,   429,   430,   431,   432,   433,   646,   650,   159,
     653,   240,   654,   651,   655,   656,   836,   846,   847,   848,
     849,   850,   851,   852,   853,   854,   855,   856,   857,   858,
     859,   860,   657,   658,   250,   861,   862,   863,   864,   865,
     866,   659,   660,   661,   662,   158,   953,   968,   664,   663,
     434,   665,   666,   667,  1007,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    87,   959,
     972,    88,   991,   435,   375,   668,   670,   671,   669,   672,
     673,   251,   674,    89,   675,   676,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   680,   677,   681,
     683,   678,   679,   684,   685,   691,   686,   692,   687,   688,
     689,   693,   694,   695,   696,   698,   960,   973,   697,   992,
     436,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   699,
     700,   701,   129,   130,   702,   704,   705,   707,   708,   709,
     710,   711,   712,   713,   131,   132,   133,   714,   716,   717,
     718,   134,   719,   720,   135,   136,   721,   722,   724,   137,
     138,   139,   140,   141,   725,   726,   727,   728,   863,   864,
     865,   730,   142,   731,   733,   734,   735,   736,   737,   738,
     739,   740,   143,   742,   743,   144,   745,   158,   746,   750,
     747,   748,   145,   146,   749,   751,   752,   147,   148,   753,
     754,   755,   756,   763,   764,   765,   766,   767,   768,   774,
      30,   777,   778,   779,   780,   781,   149,   788,   782,   783,
     150,   784,   785,   786,   789,   135,   136,   787,   790,   791,
     792,   800,   801,   802,   803,   151,   152,   153,   154,   155,
     156,   804,   805,   809,   810,   811,   813,   834,   835,   157,
     814,   815,   816,   817,   893,   818,   819,   897,   901,   905,
     820,   821,   822,   823,   824,   825,   827,   158,   829,   830,
     961,   909,   925,   928,   962,   963,   964,   965,   932,   983,
    1000,  1015,  1034,  1035,   966,   967,  1019,  1036,  1037,  1038,
    1039,  1040,  1041,  1042,  1043,  1045,  1046,  1056,  1121,  1055,
     264,  1058,  1059,   381,  1061,  1062,   402,   382,  1065,  1163,
     403,   314,  1064,  1194,  1219,  1067,  1068,   355,  1224,   315,
     421,  1225,  1075,   312,  1076,  1078,   395,  1079,  1209,   417,
    1080,  1081,  1207,  1229,   953,   310,   362,  1227,   158,   404,
     357,   268,  1082,   968,  1206,   968,   405,  1197,  1083,  1226,
    1167,  1084,   356,  1085,   278,  1274,  1088,   959,  1198,  1275,
     316,  1089,  1007,  1177,  1090,  1096,   972,   321,   972,  1210,
     313,  1098,  1199,   396,  1230,   991,   418,   363,  1276,  1208,
     279,  1200,   317,   265,  1228,  1103,  1104,   358,  1105,  1178,
     345,  1211,  1164,  1107,  1115,  1116,  1231,  1220,   266,   364,
     267,  1117,   340,  1118,   960,   336,  1125,  1165,   280,  1166,
     294,  1126,  1221,   973,  1222,   973,   337,  1179,   281,  1193,
     282,   322,   992,   283,  1223,  1277,   284,  1180,  1128,  1181,
     338,   286,  1182,   287,  1129,  1183,   288,   346,  1130,   339,
    1185,   289,  1186,   290,  1131,  1187,   291,   323,   292,  1133,
    1188,   269,  1189,   270,   271,  1190,   272,  1191,   273,   274,
    1168,   275,  1169,  1170,   276,  1171,  1134,  1172,  1173,   277,
    1174,   285,   293,  1175,   306,   324,  1135,   307,  1176,   308,
    1184,  1192,  1136,  1201,  1137,   325,  1202,   326,  1203,  1138,
     327,  1139,  1140,   328,  1141,  1147,  1150,  1151,   329,  1142,
     330,  1143,  1148,   331,  1152,  1153,  1144,  1145,   332,  1256,
     333,  1146,  1149,   334,  1257,   335,  1258,  1260,  1262,  1267,
    1332,  1269,  1289,  1290,  1329,  1293,  1310,  1245,  1246,  1316,
    1311,  1247,  1248,  1317,  1249,  1250,  1318,  1319,  1320,  1253,
    1252,  1254,  1259,  1328,  1334,  1261,  1268,  1266,  1342,  1343,
    1284,  1285,  1294,  1286,  1360,  1163,  1287,  1364,  1295,  1194,
    1296,  1297,  1219,  1298,  1299,  1304,  1224,  1305,  1366,  1225,
    1306,  1351,  1307,  1326,  1209,  1327,  1331,  1377,  1207,  1274,
    1338,  1229,  1378,  1275,  1344,  1227,  1345,  1365,  1368,  1369,
    1206,  1379,  1380,  1197,  1352,  1381,  1167,  1226,  1382,  1383,
    1384,  1398,  1276,  1400,  1198,  1395,  1401,  1402,  1409,  1177,
    1413,  1429,  1430,  1452,  1433,  1210,  1431,  1351,  1199,  1387,
    1434,  1435,  1230,  1388,  1451,  1208,  1453,  1200,  1455,  1454,
    1463,  1461,  1228,  1462,  1464,  1178,  1466,  1211,  1164,  1467,
    1352,  1353,  1389,   837,  1231,  1220,   828,  1387,   682,  1277,
    1132,  1388,   839,  1165,   690,  1166,  1255,  1022,  1214,  1154,
    1221,  1156,  1222,  1179,  1244,  1193,  1251,  1243,   732,  1158,
    1389,  1441,  1223,  1180,   703,  1181,   723,  1157,  1182,  1213,
    1341,  1183,   729,  1160,  1159,  1292,  1185,  1353,  1186,  1390,
    1162,  1187,  1161,  1291,  1444,   715,  1188,  1346,  1189,  1242,
     706,  1190,  1441,  1191,  1241,  1240,  1168,  1394,  1169,  1170,
    1385,  1171,  1263,  1172,  1173,  1414,  1174,  1390,  1450,  1175,
      93,    94,    95,    96,  1176,  1444,  1184,  1192,  1465,  1201,
    1265,   838,  1202,  1264,  1203,  1456,  1270,   999,  1427,  1367,
       0,  1445,   741,     0,     0,  1283,     0,     0,     0,     0,
       0,   744,   101,   102,   103,  1288,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1445,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   375,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1215,  1216,  1217,
    1218,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   784,   784,   754,  1066,   784,  1066,
    1066,    69,     0,    71,    68,    69,    70,    71,  1428,    73,
      74,   659,    76,   698,   699,   700,    18,    69,    70,    71,
      74,    70,   707,    69,     5,     3,     7,    74,     9,   230,
       8,     7,    70,   146,   147,     7,    69,    70,  1428,  1459,
      97,     7,    69,   728,    71,     3,    70,   117,   118,     6,
       8,    68,    69,    70,    71,    70,    73,    74,    97,    76,
     117,   118,    69,    70,    69,    69,    71,    15,    16,  1459,
      40,    19,    12,    13,    22,    23,    24,    25,   117,   118,
      69,     3,    69,   731,   146,   147,     8,   157,   158,   159,
      69,    70,    69,   194,   195,   196,   197,     3,    40,     3,
      69,    70,    69,    70,     8,    69,    70,     3,    69,    70,
      17,    18,     8,    69,    70,    69,    70,   230,    69,    70,
       7,   178,     3,    69,    70,    69,    70,     8,    69,    70,
      69,    70,   233,    69,     3,    69,    69,     3,    69,     8,
      69,    69,     8,    69,     7,     3,    69,   117,   118,     3,
       8,    69,     6,    69,    69,    97,    69,    99,   100,    69,
     230,    69,   104,   105,   106,   204,     3,   206,   207,   117,
     118,     8,     3,   230,    10,   117,   118,     8,    30,    31,
      32,    33,    34,    35,     3,    41,    42,    20,    21,     8,
     192,   230,   213,   214,   215,   216,     7,     3,    95,     3,
       6,   171,   172,   173,     8,   137,   138,   139,   140,   230,
     142,     7,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     7,    32,    33,    34,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     7,
      92,    93,    94,  1312,    96,  1312,  1312,     7,     3,   230,
     231,   232,   233,     8,    27,    28,   108,   109,   117,   118,
     230,   117,   118,   115,     7,   117,   118,   119,   120,   121,
     122,   123,   124,     3,   126,   127,   128,     4,     8,     3,
       3,   133,   230,   135,     8,     8,     3,    96,   230,     6,
       3,   143,     8,     7,   205,     8,  1054,   208,   209,   210,
     211,     3,    30,    31,    32,    33,    34,    35,   117,   118,
    1100,  1100,  1102,  1102,  1100,     3,  1102,   126,   174,   175,
       8,   180,   181,   182,    55,    56,    57,   136,   137,   138,
     139,   140,   141,   142,     4,     4,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,   198,   199,     4,     4,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,     4,     3,     8,     3,    96,    97,
       8,   230,     8,     4,   230,   454,   455,     4,   230,     4,
     108,   109,    97,    98,    99,   100,   101,   102,   103,   117,
     118,     4,   120,     4,   122,   123,   124,     4,   126,   127,
     128,     3,   117,   118,     3,   133,     8,     3,     3,     8,
       4,   126,     8,     8,     3,   143,     4,     3,     3,     8,
       3,   230,     8,     8,     4,     8,    78,    79,    80,    81,
      82,    83,    84,     4,    86,    87,    88,    89,   149,   150,
     151,   152,   153,   154,    96,     3,   533,     3,     3,     3,
       8,     6,     8,     4,     4,   542,     4,   109,     4,   110,
     111,   112,   113,     4,   116,   117,   118,     4,     4,   556,
     198,   199,     4,   560,   126,   127,   128,     4,   542,     4,
     556,   133,   134,     4,   571,   163,   164,   165,   556,     4,
       4,     4,   556,     4,   581,     4,   560,     4,   581,     4,
       4,   588,   230,   571,   556,   588,     4,   571,   560,     4,
     556,   560,     4,     4,   601,   230,     4,   581,     4,   571,
       4,     4,   560,   556,   588,   542,     4,   560,     8,   556,
       4,     4,     8,     3,   588,     4,   560,   601,     4,   556,
       4,   588,     3,   560,   571,   560,   198,   199,     8,   556,
       4,   556,   556,   560,   571,     4,     4,     4,     4,   230,
       4,     4,     4,     4,   581,   233,   571,   556,   233,   556,
     233,   588,     4,     4,     4,   233,     4,   556,   230,   556,
       4,   560,   117,   118,   601,   231,     4,   556,   231,   556,
     231,   560,   556,   560,   231,   556,   560,   231,   231,   560,
     556,   233,   556,   232,   560,   556,   560,   231,  1293,   560,
     556,   232,   556,   232,   560,   556,   560,   556,     4,   560,
     556,   560,   556,   556,   233,   556,   231,   556,   556,   233,
     556,   231,   233,   556,   231,     4,     4,     4,   556,   232,
     556,   556,   233,   556,   231,     4,   556,   231,   556,   184,
     185,   186,   187,   188,   189,   190,   191,   233,   231,   746,
       4,   748,     4,   233,   231,     4,   745,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,     4,     4,   748,    58,    59,    60,    61,    62,
      63,     4,     4,   233,   233,   230,   783,   784,     4,   233,
     787,     4,     4,     4,   791,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    11,   783,
     784,    14,   786,   787,    97,     4,     4,     4,   231,     4,
       4,   748,     4,    26,     4,     4,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     4,   233,     4,
       4,   233,   233,     4,     4,     4,   233,     4,   233,   231,
     231,     4,     4,     4,     4,     4,   783,   784,   231,   786,
     787,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     4,
       4,     4,    95,    96,     4,     4,   231,     4,     4,     4,
       4,     4,     4,     4,   107,   108,   109,     4,     4,     4,
     231,   114,     4,     4,   117,   118,     4,   233,     4,   122,
     123,   124,   125,   126,   233,   233,   233,     4,    60,    61,
      62,     4,   135,     4,   233,     4,   231,     4,   231,   231,
       4,     4,   145,     4,   231,   148,     4,   230,     7,   230,
       7,     7,   155,   156,     7,   230,   230,   160,   161,     7,
       7,     5,   230,   230,   230,     5,     5,     5,   230,     5,
       7,   230,     5,     5,     5,     5,   179,   230,     7,     7,
     183,     7,     5,     7,   230,   117,   118,     7,     5,     7,
       5,   230,   230,   230,     5,   198,   199,   200,   201,   202,
     203,   230,   230,   230,     7,   230,   230,   193,     5,   212,
     230,   230,   230,   230,     7,   230,   230,     7,     7,     7,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     162,     7,     7,     7,   166,   167,   168,   169,     7,     7,
       7,     7,     4,     4,   176,   177,   144,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   230,     6,
    1057,     6,     3,  1060,     6,     3,  1063,  1060,     3,  1066,
    1063,  1057,     6,  1066,  1071,     6,     3,  1074,  1071,  1057,
    1077,  1071,     6,  1057,     3,     6,  1060,     3,  1066,  1063,
       4,     4,  1066,  1071,  1091,  1057,  1074,  1071,   230,  1063,
    1074,  1057,     4,  1100,  1066,  1102,  1063,  1066,     4,  1071,
    1066,     4,  1074,     4,  1057,  1112,     4,  1091,  1066,  1112,
    1057,     4,  1119,  1066,     4,     4,  1100,  1124,  1102,  1066,
    1057,     4,  1066,  1060,  1071,  1109,  1063,  1074,  1112,  1066,
    1057,  1066,  1057,  1057,  1071,     6,     3,  1074,     4,  1066,
    1124,  1066,  1066,     4,     4,     4,  1071,  1071,  1057,  1074,
    1057,     4,  1124,     4,  1091,  1124,     6,  1066,  1057,  1066,
    1057,     3,  1071,  1100,  1071,  1102,  1124,  1066,  1057,  1066,
    1057,  1124,  1109,  1057,  1071,  1112,  1057,  1066,     8,  1066,
    1124,  1057,  1066,  1057,     6,  1066,  1057,  1124,     4,  1124,
    1066,  1057,  1066,  1057,     4,  1066,  1057,  1124,  1057,     4,
    1066,  1057,  1066,  1057,  1057,  1066,  1057,  1066,  1057,  1057,
    1066,  1057,  1066,  1066,  1057,  1066,     4,  1066,  1066,  1057,
    1066,  1057,  1057,  1066,  1057,  1124,     4,  1057,  1066,  1057,
    1066,  1066,     4,  1066,   231,  1124,  1066,  1124,  1066,   233,
    1124,   231,   233,  1124,   231,     4,     4,     4,  1124,   231,
    1124,   231,   233,  1124,     4,     4,   231,   231,  1124,     4,
    1124,   231,   231,  1124,     4,  1124,     4,     4,     4,     4,
    1269,     4,     6,     3,     5,     4,     8,   231,   231,     4,
       8,   231,   231,     4,   231,   231,     8,     3,     8,   231,
     233,   231,   231,     7,     4,   233,   231,   233,     4,     4,
     233,   233,   230,   233,     7,  1312,   233,     4,   230,  1312,
     230,   230,  1319,   230,   230,   230,  1319,   230,     4,  1319,
     230,  1328,   230,   230,  1312,   230,   230,     6,  1312,  1336,
     230,  1319,     3,  1336,   233,  1319,   233,   231,   230,   230,
    1312,     5,   230,  1312,  1328,     4,  1312,  1319,     4,     4,
       4,   170,  1336,   230,  1312,     7,   230,     5,     7,  1312,
       4,     6,     3,   233,     4,  1312,   230,  1374,  1312,  1376,
       4,     4,  1319,  1376,     4,  1312,   231,  1312,     4,   231,
       4,   230,  1319,   230,     4,  1312,   230,  1312,  1312,   230,
    1374,  1328,  1376,   746,  1319,  1319,   731,  1404,   533,  1336,
    1028,  1404,   748,  1312,   542,  1312,  1091,   835,  1069,  1051,
    1319,  1056,  1319,  1312,  1079,  1312,  1086,  1077,   591,  1059,
    1404,  1428,  1319,  1312,   556,  1312,   581,  1057,  1312,  1068,
    1312,  1312,   588,  1062,  1060,  1126,  1312,  1374,  1312,  1376,
    1065,  1312,  1063,  1124,  1428,   571,  1312,  1319,  1312,  1076,
     560,  1312,  1459,  1312,  1074,  1072,  1312,  1378,  1312,  1312,
    1374,  1312,  1100,  1312,  1312,  1404,  1312,  1404,  1430,  1312,
      32,    33,    34,    35,  1312,  1459,  1312,  1312,  1459,  1312,
    1104,   747,  1312,  1102,  1312,  1437,  1109,   787,  1407,  1336,
      -1,  1428,   601,    -1,    -1,  1113,    -1,    -1,    -1,    -1,
      -1,   605,    64,    65,    66,  1119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1459,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   230
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
     134,   264,   293,   294,   295,   296,   299,   301,   303,   305,
     308,   309,   310,   311,   312,   314,   455,   457,   459,   461,
     501,   530,   531,   532,   534,   535,   537,   126,   136,   137,
     138,   139,   140,   141,   142,   264,   501,   535,   537,   547,
     548,   549,   550,   552,   554,   556,   558,   560,   562,   564,
     566,   568,   570,   475,    40,    97,    99,   100,   104,   105,
     106,   264,   371,   485,   486,   487,   488,   489,   490,   491,
     493,   495,   497,   498,   500,   535,   537,    98,   101,   102,
     103,   126,   264,   371,   489,   495,   509,   510,   511,   512,
     513,   515,   516,   517,   518,   519,   520,   535,   537,   146,
     147,   264,   419,   420,   421,   423,   184,   185,   186,   187,
     188,   189,   190,   191,   264,   535,   537,   659,   660,   661,
     662,   664,   665,   667,   668,   669,   672,    12,    13,   678,
     679,   680,   682,     6,     3,     4,     8,     3,   268,     3,
       8,   675,   325,   345,     4,     4,     4,   551,   553,   555,
       4,     4,   343,   353,   355,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   286,     4,     4,     4,
       4,     4,   297,   300,   302,     4,     4,     4,     4,     4,
       4,     4,   436,   476,   502,     4,   289,   306,   468,   536,
     538,     4,     4,     4,   396,   578,   540,   412,   426,     4,
     405,   594,   596,   646,   656,   313,   315,     4,     4,     4,
     684,   708,     4,     3,     8,   331,   333,   336,     4,     4,
       4,     4,     3,     8,   448,   450,   452,   523,   446,   454,
       4,   458,   460,   462,   456,   573,     3,     8,   533,     4,
       3,     8,   571,   557,   559,   561,   565,   563,   569,   567,
       8,     3,     8,   492,   372,     4,   496,   494,   499,     4,
       8,     3,   514,     4,     4,     4,   521,     8,     3,   422,
     424,     3,     8,     4,   663,     4,   666,     4,     4,   670,
     673,     3,     8,   681,     4,     3,     8,   249,   249,   230,
       4,     4,     4,     4,   233,   233,   233,     4,     4,     4,
     231,   233,     4,     4,     4,   231,   231,   231,   231,   231,
     233,   232,   232,   232,   231,   231,     4,   231,   231,   233,
     233,   233,     4,     4,     4,   233,   233,   232,   231,   231,
     231,   233,     4,     4,     4,   231,     4,     4,     4,     4,
       4,   233,   233,   233,     4,     4,     4,     4,     4,   231,
       4,     4,     4,     4,     4,     4,     4,   233,   233,   233,
       4,     4,   273,     4,     4,     4,   233,   233,   231,   231,
     327,     4,     4,     4,     4,     4,     4,   231,     4,     4,
       4,     4,     4,   444,     4,   231,   531,     4,     4,     4,
       4,     4,     4,     4,     4,   549,     4,     4,   231,     4,
       4,     4,   233,   487,     4,   233,   233,   233,     4,   511,
       4,     4,   420,   233,     4,   231,     4,   231,   231,     4,
       4,   660,     4,   231,   679,     4,     7,     7,     7,     7,
     230,   230,   230,     7,     7,     5,   230,   194,   195,   196,
     197,   233,   298,   230,   230,     5,     5,     5,   230,   110,
     111,   112,   113,   307,     5,   251,   253,   230,     5,     5,
       5,     5,     7,     7,     7,     5,     7,     7,   230,   230,
       5,     7,     5,   260,    17,    18,   334,    20,    21,   337,
     230,   230,   230,     5,   230,   230,   260,   260,   260,   230,
       7,   230,   260,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   260,   230,   253,   230,
     230,    18,   192,   671,   193,     5,   249,   272,   678,   326,
      27,    28,   346,   347,   348,   350,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    58,    59,    60,    61,    62,    63,   264,   360,   361,
     362,   364,   366,   368,   370,   371,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   385,   386,   387,   389,
     391,   393,   360,     7,   356,   357,   358,     7,   437,   438,
     439,     7,   479,   480,   481,     7,   503,   504,   505,     7,
     469,   470,   471,   137,   138,   139,   140,   142,   397,   398,
     399,   400,   401,   402,   403,     7,   579,   580,     7,   541,
     542,   543,     7,   413,   414,   415,   149,   150,   151,   152,
     153,   154,   427,   428,   429,   430,   431,   432,   433,   434,
     157,   158,   159,   264,   406,   407,   408,   409,   410,   535,
     537,   162,   166,   167,   168,   169,   176,   177,   264,   387,
     389,   391,   535,   537,   601,   602,   603,   606,   608,   610,
     611,   612,   622,     7,   597,   598,   599,   180,   181,   182,
     230,   535,   537,   647,   648,   649,   650,   652,   653,   659,
       7,   685,   686,   213,   214,   215,   216,   264,   709,   710,
     711,   712,   713,   714,   261,     7,   524,   525,   526,   144,
     574,   575,   356,     8,     8,     8,   349,   351,     3,     8,
     363,   365,   367,   369,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   383,     4,     4,   388,   390,   392,
     394,     3,     8,     8,   359,     6,     3,   440,     6,     3,
     482,     6,     3,   506,     6,     3,   472,     6,     3,     3,
       6,   581,     3,     6,   544,     6,     3,   416,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   604,   607,   609,     4,   623,     4,   613,
       3,     8,   600,     6,     3,     4,   651,     4,   654,     3,
       8,     8,   687,     3,     6,     4,     4,     4,     4,     3,
       8,   230,   262,   263,   527,     6,     3,   576,     8,     6,
       4,     4,   347,     4,     4,     4,     4,   231,   233,   231,
     233,   231,   231,   231,   231,   231,   231,     4,   233,   231,
       4,     4,     4,     4,   361,   360,   358,   443,   439,   485,
     481,   509,   505,   264,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   288,   291,   292,   293,   294,   295,
     296,   299,   301,   303,   304,   305,   308,   309,   310,   311,
     312,   314,   316,   322,   371,   435,   453,   455,   457,   459,
     461,   463,   464,   465,   473,   474,   501,   535,   537,   550,
     552,   554,   572,   471,   398,   129,   130,   131,   132,   264,
     274,   275,   276,   322,   371,   475,   501,   535,   537,   550,
     552,   554,   582,   583,   584,   585,   586,   588,   590,   591,
     580,   547,   543,   419,   415,   231,   231,   231,   231,   231,
     231,   428,   233,   231,   231,   407,     4,     4,     4,   231,
       4,   233,     4,   602,   601,   599,   233,     4,   231,     4,
     648,   204,   206,   207,   264,   371,   535,   537,   688,   689,
     690,   691,   693,   686,   233,   233,   233,   233,   710,     6,
       3,   530,   526,     4,   230,   230,   230,   230,   230,   230,
      55,    56,    57,   384,   230,   230,   230,   230,     8,     8,
       8,     8,     3,     8,   587,   589,     4,     4,     8,     3,
       8,     8,   163,   164,   165,   605,   230,   230,     7,     5,
       8,   230,   249,   694,     4,   692,     3,     8,   230,     8,
     260,   474,     4,     4,   233,   233,   584,    40,   171,   172,
     173,   264,   535,   537,   624,   625,   626,   629,   631,   633,
       7,   614,   615,   616,     4,   231,     4,   689,   230,   230,
     627,   630,   632,   634,     3,     8,   617,     6,     3,     5,
     230,     4,     4,     4,     4,   625,   178,   264,   371,   535,
     537,   618,   619,   620,   616,     7,   695,   696,   170,   628,
     230,   230,     5,   621,     3,     8,   697,     3,     6,     7,
     635,   636,   637,     4,   619,   205,   208,   209,   210,   211,
     698,   699,   700,   702,   703,   704,   705,   696,   638,     6,
       3,   230,   701,     4,     4,     4,   706,     3,     8,   174,
     175,   264,   364,   366,   535,   537,   639,   640,   641,   643,
     637,     4,   233,   231,   231,     4,   699,   642,   644,     3,
       8,   230,   230,     4,     4,   640,   230,   230
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
     531,   531,   531,   531,   531,   531,   531,   531,   531,   531,
     531,   531,   531,   531,   531,   531,   531,   533,   532,   534,
     536,   535,   538,   537,   540,   539,   541,   541,   542,   542,
     542,   544,   543,   546,   545,   547,   547,   548,   548,   548,
     549,   549,   549,   549,   549,   549,   549,   549,   549,   549,
     549,   549,   549,   549,   549,   551,   550,   553,   552,   555,
     554,   557,   556,   559,   558,   561,   560,   563,   562,   565,
     564,   567,   566,   569,   568,   571,   570,   573,   572,   574,
     576,   575,   578,   577,   579,   579,   579,   581,   580,   582,
     582,   583,   583,   583,   584,   584,   584,   584,   584,   584,
     584,   584,   584,   584,   584,   584,   584,   584,   584,   584,
     584,   585,   587,   586,   589,   588,   590,   591,   592,   594,
     593,   596,   595,   597,   597,   598,   598,   598,   600,   599,
     601,   601,   601,   602,   602,   602,   602,   602,   602,   602,
     602,   602,   602,   602,   602,   602,   604,   603,   605,   605,
     605,   607,   606,   609,   608,   610,   611,   613,   612,   614,
     614,   615,   615,   615,   617,   616,   618,   618,   618,   619,
     619,   619,   619,   619,   621,   620,   623,   622,   624,   624,
     624,   625,   625,   625,   625,   625,   625,   625,   627,   626,
     628,   630,   629,   632,   631,   634,   633,   635,   635,   636,
     636,   636,   638,   637,   639,   639,   639,   640,   640,   640,
     640,   640,   640,   640,   642,   641,   644,   643,   646,   645,
     647,   647,   647,   648,   648,   648,   648,   648,   648,   649,
     651,   650,   652,   654,   653,   656,   655,   658,   657,   659,
     659,   659,   660,   660,   660,   660,   660,   660,   660,   660,
     660,   660,   660,   661,   663,   662,   664,   666,   665,   667,
     668,   670,   669,   671,   671,   673,   672,   675,   674,   677,
     676,   678,   678,   678,   679,   679,   681,   680,   682,   684,
     683,   685,   685,   685,   687,   686,   688,   688,   688,   689,
     689,   689,   689,   689,   689,   689,   690,   692,   691,   694,
     693,   695,   695,   695,   697,   696,   698,   698,   698,   699,
     699,   699,   699,   699,   701,   700,   702,   703,   704,   706,
     705,   708,   707,   709,   709,   709,   710,   710,   710,   710,
     710,   711,   712,   713,   714
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     3,     0,
       6,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     3,     3,     3,     3
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
    2213,  2214,  2215,  2216,  2217,  2218,  2219,  2220,  2221,  2222,
    2223,  2224,  2225,  2226,  2227,  2228,  2229,  2232,  2232,  2241,
    2247,  2247,  2272,  2272,  2302,  2302,  2313,  2314,  2317,  2318,
    2319,  2324,  2324,  2333,  2333,  2342,  2343,  2346,  2347,  2348,
    2354,  2355,  2356,  2357,  2358,  2359,  2360,  2361,  2362,  2363,
    2364,  2365,  2366,  2367,  2368,  2371,  2371,  2380,  2380,  2389,
    2389,  2398,  2398,  2407,  2407,  2416,  2416,  2425,  2425,  2434,
    2434,  2443,  2443,  2452,  2452,  2461,  2461,  2475,  2475,  2486,
    2489,  2489,  2503,  2503,  2514,  2515,  2516,  2521,  2521,  2531,
    2532,  2535,  2536,  2537,  2542,  2543,  2544,  2545,  2546,  2547,
    2548,  2549,  2550,  2551,  2552,  2553,  2554,  2555,  2556,  2557,
    2558,  2561,  2563,  2563,  2572,  2572,  2582,  2588,  2596,  2604,
    2604,  2616,  2616,  2628,  2629,  2632,  2633,  2634,  2639,  2639,
    2647,  2648,  2649,  2654,  2655,  2656,  2657,  2658,  2659,  2660,
    2661,  2662,  2663,  2664,  2665,  2666,  2669,  2669,  2678,  2679,
    2680,  2683,  2683,  2693,  2693,  2703,  2709,  2715,  2715,  2726,
    2727,  2730,  2731,  2732,  2737,  2737,  2745,  2746,  2747,  2752,
    2753,  2754,  2755,  2756,  2759,  2759,  2770,  2770,  2783,  2784,
    2785,  2790,  2791,  2792,  2793,  2794,  2795,  2796,  2799,  2799,
    2807,  2810,  2810,  2819,  2819,  2828,  2828,  2839,  2840,  2843,
    2844,  2845,  2850,  2850,  2858,  2859,  2860,  2865,  2866,  2867,
    2868,  2869,  2870,  2871,  2874,  2874,  2883,  2883,  2894,  2894,
    2907,  2908,  2909,  2914,  2915,  2916,  2917,  2918,  2919,  2922,
    2928,  2928,  2937,  2943,  2943,  2953,  2953,  2966,  2966,  2976,
    2977,  2978,  2983,  2984,  2985,  2986,  2987,  2988,  2989,  2990,
    2991,  2992,  2993,  2996,  3002,  3002,  3011,  3017,  3017,  3026,
    3032,  3038,  3038,  3047,  3048,  3051,  3051,  3062,  3062,  3074,
    3074,  3084,  3085,  3086,  3092,  3093,  3096,  3096,  3107,  3115,
    3115,  3128,  3129,  3130,  3136,  3136,  3144,  3145,  3146,  3151,
    3152,  3153,  3154,  3155,  3156,  3157,  3160,  3166,  3166,  3175,
    3175,  3186,  3187,  3188,  3193,  3193,  3201,  3202,  3203,  3208,
    3209,  3210,  3211,  3212,  3215,  3215,  3224,  3230,  3236,  3242,
    3242,  3251,  3251,  3262,  3263,  3264,  3269,  3270,  3271,  3272,
    3273,  3276,  3282,  3288,  3294
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
#line 6907 "dhcp4_parser.cc"

#line 3300 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
