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
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 321 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 321 "dhcp4_parser.yy"
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
#line 330 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 331 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 332 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 333 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 334 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 335 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 336 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 337 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 338 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 339 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 340 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 341 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 342 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 350 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 351 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 352 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 353 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 354 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 355 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 356 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 359 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 364 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 369 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 375 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 382 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 387 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 393 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 398 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 401 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 409 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 413 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 417 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 423 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 425 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 434 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 438 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 442 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 452 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 461 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 466 "dhcp4_parser.yy"
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
#line 476 "dhcp4_parser.yy"
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
#line 485 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 493 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 499 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 503 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 510 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 591 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 597 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 603 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 609 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 615 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 621 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 627 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 633 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 639 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 645 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 651 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 153: // $@20: %empty
#line 657 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 154: // server_tag: "server-tag" $@20 ":" "constant string"
#line 660 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 155: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 666 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 156: // $@21: %empty
#line 672 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 157: // allocator: "allocator" $@21 ":" "constant string"
#line 675 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 158: // echo_client_id: "echo-client-id" ":" "boolean"
#line 681 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 159: // match_client_id: "match-client-id" ":" "boolean"
#line 687 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 160: // authoritative: "authoritative" ":" "boolean"
#line 693 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 161: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 699 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 162: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 705 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 163: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 711 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 164: // $@22: %empty
#line 717 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 720 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-present"
#line 726 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "never"
#line 729 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "always"
#line 732 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "when-not-present"
#line 735 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "boolean"
#line 738 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 171: // $@23: %empty
#line 744 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 172: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 747 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 173: // $@24: %empty
#line 753 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 174: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 756 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 175: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 762 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 176: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 771 "dhcp4_parser.yy"
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
#line 781 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 784 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 790 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 793 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 796 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 799 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 183: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 804 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 184: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 810 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1546 "dhcp4_parser.cc"
    break;

  case 185: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 816 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 186: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 822 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 187: // $@26: %empty
#line 828 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 188: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 831 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 189: // $@27: %empty
#line 837 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 190: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 840 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 191: // store_extended_info: "store-extended-info" ":" "boolean"
#line 846 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 192: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 852 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 193: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 858 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 864 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 870 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 876 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 197: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 882 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1674 "dhcp4_parser.cc"
    break;

  case 198: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 888 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 199: // $@28: %empty
#line 894 "dhcp4_parser.yy"
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
#line 900 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1706 "dhcp4_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 908 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1714 "dhcp4_parser.cc"
    break;

  case 214: // $@29: %empty
#line 925 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 215: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 929 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 216: // $@30: %empty
#line 934 "dhcp4_parser.yy"
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
#line 940 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1754 "dhcp4_parser.cc"
    break;

  case 218: // $@31: %empty
#line 945 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 219: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 948 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 220: // socket_type: "raw"
#line 953 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1778 "dhcp4_parser.cc"
    break;

  case 221: // socket_type: "udp"
#line 954 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1784 "dhcp4_parser.cc"
    break;

  case 222: // $@32: %empty
#line 957 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1793 "dhcp4_parser.cc"
    break;

  case 223: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 960 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1802 "dhcp4_parser.cc"
    break;

  case 224: // outbound_interface_value: "same-as-inbound"
#line 965 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1810 "dhcp4_parser.cc"
    break;

  case 225: // outbound_interface_value: "use-routing"
#line 967 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1818 "dhcp4_parser.cc"
    break;

  case 226: // re_detect: "re-detect" ":" "boolean"
#line 971 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 227: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 977 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1838 "dhcp4_parser.cc"
    break;

  case 228: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 983 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1848 "dhcp4_parser.cc"
    break;

  case 229: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 989 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1858 "dhcp4_parser.cc"
    break;

  case 230: // $@33: %empty
#line 995 "dhcp4_parser.yy"
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
#line 1001 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 232: // $@34: %empty
#line 1008 "dhcp4_parser.yy"
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
#line 1014 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc"
    break;

  case 236: // sanity_checks_params: sanity_checks_params ","
#line 1021 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1910 "dhcp4_parser.cc"
    break;

  case 239: // $@35: %empty
#line 1030 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 240: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1033 "dhcp4_parser.yy"
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
#line 1049 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1948 "dhcp4_parser.cc"
    break;

  case 242: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1052 "dhcp4_parser.yy"
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
#line 1067 "dhcp4_parser.yy"
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
#line 1073 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1990 "dhcp4_parser.cc"
    break;

  case 245: // $@38: %empty
#line 1080 "dhcp4_parser.yy"
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
#line 1086 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 251: // not_empty_database_list: not_empty_database_list ","
#line 1097 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2019 "dhcp4_parser.cc"
    break;

  case 252: // $@39: %empty
#line 1102 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 253: // database: "{" $@39 database_map_params "}"
#line 1106 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 256: // database_map_params: database_map_params ","
#line 1114 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2047 "dhcp4_parser.cc"
    break;

  case 281: // $@40: %empty
#line 1145 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 282: // database_type: "type" $@40 ":" "constant string"
#line 1148 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2066 "dhcp4_parser.cc"
    break;

  case 283: // $@41: %empty
#line 1154 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 284: // user: "user" $@41 ":" "constant string"
#line 1157 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 285: // $@42: %empty
#line 1163 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc"
    break;

  case 286: // password: "password" $@42 ":" "constant string"
#line 1166 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 287: // $@43: %empty
#line 1172 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2113 "dhcp4_parser.cc"
    break;

  case 288: // host: "host" $@43 ":" "constant string"
#line 1175 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc"
    break;

  case 289: // port: "port" ":" "integer"
#line 1181 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2133 "dhcp4_parser.cc"
    break;

  case 290: // $@44: %empty
#line 1187 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 291: // name: "name" $@44 ":" "constant string"
#line 1190 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 292: // persist: "persist" ":" "boolean"
#line 1196 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2162 "dhcp4_parser.cc"
    break;

  case 293: // lfc_interval: "lfc-interval" ":" "integer"
#line 1202 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 294: // readonly: "readonly" ":" "boolean"
#line 1208 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 295: // connect_timeout: "connect-timeout" ":" "integer"
#line 1214 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 296: // read_timeout: "read-timeout" ":" "integer"
#line 1220 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 297: // write_timeout: "write-timeout" ":" "integer"
#line 1226 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 298: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1232 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 299: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1238 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 300: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1244 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 301: // $@45: %empty
#line 1250 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 302: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1253 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 303: // on_fail_mode: "stop-retry-exit"
#line 1258 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2266 "dhcp4_parser.cc"
    break;

  case 304: // on_fail_mode: "serve-retry-exit"
#line 1259 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2272 "dhcp4_parser.cc"
    break;

  case 305: // on_fail_mode: "serve-retry-continue"
#line 1260 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2278 "dhcp4_parser.cc"
    break;

  case 306: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1263 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2288 "dhcp4_parser.cc"
    break;

  case 307: // max_row_errors: "max-row-errors" ":" "integer"
#line 1269 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2298 "dhcp4_parser.cc"
    break;

  case 308: // $@46: %empty
#line 1275 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 309: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1278 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 310: // $@47: %empty
#line 1284 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp4_parser.cc"
    break;

  case 311: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1287 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2336 "dhcp4_parser.cc"
    break;

  case 312: // $@48: %empty
#line 1293 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2345 "dhcp4_parser.cc"
    break;

  case 313: // key_file: "key-file" $@48 ":" "constant string"
#line 1296 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2355 "dhcp4_parser.cc"
    break;

  case 314: // $@49: %empty
#line 1302 "dhcp4_parser.yy"
                           {
    ctx.unique("key-password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp4_parser.cc"
    break;

  case 315: // key_password: "key-password" $@49 ":" "constant string"
#line 1305 "dhcp4_parser.yy"
               {
    ElementPtr key_pass(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-password", key_pass);
    ctx.leave();
}
#line 2374 "dhcp4_parser.cc"
    break;

  case 316: // $@50: %empty
#line 1311 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp4_parser.cc"
    break;

  case 317: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1314 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2393 "dhcp4_parser.cc"
    break;

  case 318: // $@51: %empty
#line 1320 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2405 "dhcp4_parser.cc"
    break;

  case 319: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1326 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2414 "dhcp4_parser.cc"
    break;

  case 322: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1333 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2422 "dhcp4_parser.cc"
    break;

  case 328: // duid_id: "duid"
#line 1345 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2431 "dhcp4_parser.cc"
    break;

  case 329: // hw_address_id: "hw-address"
#line 1350 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2440 "dhcp4_parser.cc"
    break;

  case 330: // circuit_id: "circuit-id"
#line 1355 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2449 "dhcp4_parser.cc"
    break;

  case 331: // client_id: "client-id"
#line 1360 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2458 "dhcp4_parser.cc"
    break;

  case 332: // flex_id: "flex-id"
#line 1365 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2467 "dhcp4_parser.cc"
    break;

  case 333: // $@52: %empty
#line 1372 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2479 "dhcp4_parser.cc"
    break;

  case 334: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1378 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2490 "dhcp4_parser.cc"
    break;

  case 337: // multi_threading_params: multi_threading_params ","
#line 1387 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2498 "dhcp4_parser.cc"
    break;

  case 344: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1400 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2508 "dhcp4_parser.cc"
    break;

  case 345: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1406 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 346: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1412 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 347: // $@53: %empty
#line 1418 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 348: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1424 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 353: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1435 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2557 "dhcp4_parser.cc"
    break;

  case 354: // $@54: %empty
#line 1440 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2567 "dhcp4_parser.cc"
    break;

  case 355: // hooks_library: "{" $@54 hooks_params "}"
#line 1444 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2577 "dhcp4_parser.cc"
    break;

  case 356: // $@55: %empty
#line 1450 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 357: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1454 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 360: // hooks_params: hooks_params ","
#line 1462 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2605 "dhcp4_parser.cc"
    break;

  case 364: // $@56: %empty
#line 1472 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2614 "dhcp4_parser.cc"
    break;

  case 365: // library: "library" $@56 ":" "constant string"
#line 1475 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2624 "dhcp4_parser.cc"
    break;

  case 366: // $@57: %empty
#line 1481 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2633 "dhcp4_parser.cc"
    break;

  case 367: // parameters: "parameters" $@57 ":" map_value
#line 1484 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2642 "dhcp4_parser.cc"
    break;

  case 368: // $@58: %empty
#line 1490 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2654 "dhcp4_parser.cc"
    break;

  case 369: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1496 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc"
    break;

  case 372: // expired_leases_params: expired_leases_params ","
#line 1504 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2672 "dhcp4_parser.cc"
    break;

  case 379: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1517 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2682 "dhcp4_parser.cc"
    break;

  case 380: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1523 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 381: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1529 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 382: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1535 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 383: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1541 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 384: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1547 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 385: // $@59: %empty
#line 1556 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2744 "dhcp4_parser.cc"
    break;

  case 386: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1562 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 391: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1576 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2761 "dhcp4_parser.cc"
    break;

  case 392: // $@60: %empty
#line 1585 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 393: // subnet4: "{" $@60 subnet4_params "}"
#line 1589 "dhcp4_parser.yy"
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
#line 2797 "dhcp4_parser.cc"
    break;

  case 394: // $@61: %empty
#line 1611 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2807 "dhcp4_parser.cc"
    break;

  case 395: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1615 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2817 "dhcp4_parser.cc"
    break;

  case 398: // subnet4_params: subnet4_params ","
#line 1624 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2825 "dhcp4_parser.cc"
    break;

  case 452: // $@62: %empty
#line 1685 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2834 "dhcp4_parser.cc"
    break;

  case 453: // subnet: "subnet" $@62 ":" "constant string"
#line 1688 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc"
    break;

  case 454: // $@63: %empty
#line 1694 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp4_parser.cc"
    break;

  case 455: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1697 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 456: // $@64: %empty
#line 1703 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 457: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1706 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2882 "dhcp4_parser.cc"
    break;

  case 458: // $@65: %empty
#line 1712 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 459: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1715 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2901 "dhcp4_parser.cc"
    break;

  case 460: // $@66: %empty
#line 1721 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 461: // interface: "interface" $@66 ":" "constant string"
#line 1724 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 462: // $@67: %empty
#line 1730 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 463: // client_class: "client-class" $@67 ":" "constant string"
#line 1733 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 464: // $@68: %empty
#line 1740 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 465: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1746 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 466: // $@69: %empty
#line 1752 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2972 "dhcp4_parser.cc"
    break;

  case 467: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1758 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2981 "dhcp4_parser.cc"
    break;

  case 468: // $@70: %empty
#line 1763 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 469: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1769 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp4_parser.cc"
    break;

  case 470: // reservations_global: "reservations-global" ":" "boolean"
#line 1774 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3012 "dhcp4_parser.cc"
    break;

  case 471: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1780 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3022 "dhcp4_parser.cc"
    break;

  case 472: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1786 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3032 "dhcp4_parser.cc"
    break;

  case 473: // id: "id" ":" "integer"
#line 1792 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 474: // $@71: %empty
#line 1800 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 475: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1806 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 480: // shared_networks_list: shared_networks_list ","
#line 1819 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3071 "dhcp4_parser.cc"
    break;

  case 481: // $@72: %empty
#line 1824 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 482: // shared_network: "{" $@72 shared_network_params "}"
#line 1828 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3089 "dhcp4_parser.cc"
    break;

  case 485: // shared_network_params: shared_network_params ","
#line 1834 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3097 "dhcp4_parser.cc"
    break;

  case 534: // $@73: %empty
#line 1893 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 535: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1899 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3118 "dhcp4_parser.cc"
    break;

  case 536: // $@74: %empty
#line 1907 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3127 "dhcp4_parser.cc"
    break;

  case 537: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1910 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3135 "dhcp4_parser.cc"
    break;

  case 542: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1922 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3143 "dhcp4_parser.cc"
    break;

  case 543: // $@75: %empty
#line 1929 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3153 "dhcp4_parser.cc"
    break;

  case 544: // option_def_entry: "{" $@75 option_def_params "}"
#line 1933 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3165 "dhcp4_parser.cc"
    break;

  case 545: // $@76: %empty
#line 1944 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3175 "dhcp4_parser.cc"
    break;

  case 546: // sub_option_def: "{" $@76 option_def_params "}"
#line 1948 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 551: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1964 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3195 "dhcp4_parser.cc"
    break;

  case 563: // code: "code" ":" "integer"
#line 1983 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 565: // $@77: %empty
#line 1991 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 566: // option_def_type: "type" $@77 ":" "constant string"
#line 1994 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3224 "dhcp4_parser.cc"
    break;

  case 567: // $@78: %empty
#line 2000 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 568: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 2003 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 569: // $@79: %empty
#line 2009 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3252 "dhcp4_parser.cc"
    break;

  case 570: // space: "space" $@79 ":" "constant string"
#line 2012 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3262 "dhcp4_parser.cc"
    break;

  case 572: // $@80: %empty
#line 2020 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3271 "dhcp4_parser.cc"
    break;

  case 573: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2023 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3281 "dhcp4_parser.cc"
    break;

  case 574: // option_def_array: "array" ":" "boolean"
#line 2029 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3291 "dhcp4_parser.cc"
    break;

  case 575: // $@81: %empty
#line 2039 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 576: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2045 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 581: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2060 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3320 "dhcp4_parser.cc"
    break;

  case 582: // $@82: %empty
#line 2067 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 583: // option_data_entry: "{" $@82 option_data_params "}"
#line 2071 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3339 "dhcp4_parser.cc"
    break;

  case 584: // $@83: %empty
#line 2079 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3349 "dhcp4_parser.cc"
    break;

  case 585: // sub_option_data: "{" $@83 option_data_params "}"
#line 2083 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3358 "dhcp4_parser.cc"
    break;

  case 590: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2099 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3366 "dhcp4_parser.cc"
    break;

  case 603: // $@84: %empty
#line 2121 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3375 "dhcp4_parser.cc"
    break;

  case 604: // option_data_data: "data" $@84 ":" "constant string"
#line 2124 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3385 "dhcp4_parser.cc"
    break;

  case 607: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2134 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3395 "dhcp4_parser.cc"
    break;

  case 608: // option_data_always_send: "always-send" ":" "boolean"
#line 2140 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3405 "dhcp4_parser.cc"
    break;

  case 609: // option_data_never_send: "never-send" ":" "boolean"
#line 2146 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 610: // $@85: %empty
#line 2152 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3427 "dhcp4_parser.cc"
    break;

  case 611: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2158 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 612: // $@86: %empty
#line 2166 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3448 "dhcp4_parser.cc"
    break;

  case 613: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2172 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3457 "dhcp4_parser.cc"
    break;

  case 618: // not_empty_pools_list: not_empty_pools_list ","
#line 2185 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3465 "dhcp4_parser.cc"
    break;

  case 619: // $@87: %empty
#line 2190 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3475 "dhcp4_parser.cc"
    break;

  case 620: // pool_list_entry: "{" $@87 pool_params "}"
#line 2194 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 621: // $@88: %empty
#line 2200 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 622: // sub_pool4: "{" $@88 pool_params "}"
#line 2204 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 625: // pool_params: pool_params ","
#line 2212 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3513 "dhcp4_parser.cc"
    break;

  case 650: // $@89: %empty
#line 2243 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3522 "dhcp4_parser.cc"
    break;

  case 651: // pool_entry: "pool" $@89 ":" "constant string"
#line 2246 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3532 "dhcp4_parser.cc"
    break;

  case 652: // pool_id: "pool-id" ":" "integer"
#line 2252 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 653: // $@90: %empty
#line 2258 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3550 "dhcp4_parser.cc"
    break;

  case 654: // user_context: "user-context" $@90 ":" map_value
#line 2260 "dhcp4_parser.yy"
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
#line 3577 "dhcp4_parser.cc"
    break;

  case 655: // $@91: %empty
#line 2283 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3585 "dhcp4_parser.cc"
    break;

  case 656: // comment: "comment" $@91 ":" "constant string"
#line 2285 "dhcp4_parser.yy"
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
#line 3614 "dhcp4_parser.cc"
    break;

  case 657: // $@92: %empty
#line 2313 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3626 "dhcp4_parser.cc"
    break;

  case 658: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2319 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 663: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2330 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3643 "dhcp4_parser.cc"
    break;

  case 664: // $@93: %empty
#line 2335 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 665: // reservation: "{" $@93 reservation_params "}"
#line 2339 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3662 "dhcp4_parser.cc"
    break;

  case 666: // $@94: %empty
#line 2344 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3672 "dhcp4_parser.cc"
    break;

  case 667: // sub_reservation: "{" $@94 reservation_params "}"
#line 2348 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 672: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2359 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3689 "dhcp4_parser.cc"
    break;

  case 688: // $@95: %empty
#line 2382 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3698 "dhcp4_parser.cc"
    break;

  case 689: // next_server: "next-server" $@95 ":" "constant string"
#line 2385 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 690: // $@96: %empty
#line 2391 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 691: // server_hostname: "server-hostname" $@96 ":" "constant string"
#line 2394 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3727 "dhcp4_parser.cc"
    break;

  case 692: // $@97: %empty
#line 2400 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3736 "dhcp4_parser.cc"
    break;

  case 693: // boot_file_name: "boot-file-name" $@97 ":" "constant string"
#line 2403 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3746 "dhcp4_parser.cc"
    break;

  case 694: // $@98: %empty
#line 2409 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3755 "dhcp4_parser.cc"
    break;

  case 695: // ip_address: "ip-address" $@98 ":" "constant string"
#line 2412 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3765 "dhcp4_parser.cc"
    break;

  case 696: // $@99: %empty
#line 2418 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3774 "dhcp4_parser.cc"
    break;

  case 697: // duid: "duid" $@99 ":" "constant string"
#line 2421 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3784 "dhcp4_parser.cc"
    break;

  case 698: // $@100: %empty
#line 2427 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3793 "dhcp4_parser.cc"
    break;

  case 699: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2430 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3803 "dhcp4_parser.cc"
    break;

  case 700: // $@101: %empty
#line 2436 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3812 "dhcp4_parser.cc"
    break;

  case 701: // client_id_value: "client-id" $@101 ":" "constant string"
#line 2439 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3822 "dhcp4_parser.cc"
    break;

  case 702: // $@102: %empty
#line 2445 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3831 "dhcp4_parser.cc"
    break;

  case 703: // circuit_id_value: "circuit-id" $@102 ":" "constant string"
#line 2448 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3841 "dhcp4_parser.cc"
    break;

  case 704: // $@103: %empty
#line 2454 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3850 "dhcp4_parser.cc"
    break;

  case 705: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2457 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3860 "dhcp4_parser.cc"
    break;

  case 706: // $@104: %empty
#line 2463 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3869 "dhcp4_parser.cc"
    break;

  case 707: // hostname: "hostname" $@104 ":" "constant string"
#line 2466 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3879 "dhcp4_parser.cc"
    break;

  case 708: // $@105: %empty
#line 2472 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 709: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2478 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3900 "dhcp4_parser.cc"
    break;

  case 710: // $@106: %empty
#line 2486 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3912 "dhcp4_parser.cc"
    break;

  case 711: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2492 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3921 "dhcp4_parser.cc"
    break;

  case 713: // $@107: %empty
#line 2500 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3933 "dhcp4_parser.cc"
    break;

  case 714: // ip_addresses: "ip-addresses" $@107 ":" list_strings
#line 2506 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 715: // $@108: %empty
#line 2514 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3954 "dhcp4_parser.cc"
    break;

  case 716: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2520 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 719: // client_classes_list: client_classes_list ","
#line 2527 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3971 "dhcp4_parser.cc"
    break;

  case 720: // $@109: %empty
#line 2532 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3981 "dhcp4_parser.cc"
    break;

  case 721: // client_class_entry: "{" $@109 client_class_params "}"
#line 2536 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3991 "dhcp4_parser.cc"
    break;

  case 726: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2548 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3999 "dhcp4_parser.cc"
    break;

  case 745: // $@110: %empty
#line 2574 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4008 "dhcp4_parser.cc"
    break;

  case 746: // client_class_test: "test" $@110 ":" "constant string"
#line 2577 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 747: // $@111: %empty
#line 2583 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4027 "dhcp4_parser.cc"
    break;

  case 748: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2586 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4037 "dhcp4_parser.cc"
    break;

  case 749: // only_if_required: "only-if-required" ":" "boolean"
#line 2593 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4047 "dhcp4_parser.cc"
    break;

  case 750: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2599 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4057 "dhcp4_parser.cc"
    break;

  case 751: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2607 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4067 "dhcp4_parser.cc"
    break;

  case 752: // $@112: %empty
#line 2615 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4080 "dhcp4_parser.cc"
    break;

  case 753: // control_socket: "control-socket" $@112 ":" "{" control_socket_params "}"
#line 2622 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4089 "dhcp4_parser.cc"
    break;

  case 754: // $@113: %empty
#line 2627 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4102 "dhcp4_parser.cc"
    break;

  case 755: // control_sockets: "control-sockets" $@113 ":" "[" control_socket_list "]"
#line 2634 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4111 "dhcp4_parser.cc"
    break;

  case 760: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2645 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4119 "dhcp4_parser.cc"
    break;

  case 761: // $@114: %empty
#line 2650 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 762: // control_socket_entry: "{" $@114 control_socket_params "}"
#line 2654 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4137 "dhcp4_parser.cc"
    break;

  case 765: // control_socket_params: control_socket_params ","
#line 2660 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4145 "dhcp4_parser.cc"
    break;

  case 779: // $@115: %empty
#line 2680 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4154 "dhcp4_parser.cc"
    break;

  case 780: // control_socket_type: "socket-type" $@115 ":" control_socket_type_value
#line 2683 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4163 "dhcp4_parser.cc"
    break;

  case 781: // control_socket_type_value: "unix"
#line 2689 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4169 "dhcp4_parser.cc"
    break;

  case 782: // control_socket_type_value: "http"
#line 2690 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4175 "dhcp4_parser.cc"
    break;

  case 783: // control_socket_type_value: "https"
#line 2691 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4181 "dhcp4_parser.cc"
    break;

  case 784: // $@116: %empty
#line 2694 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4191 "dhcp4_parser.cc"
    break;

  case 785: // control_socket_name: "socket-name" $@116 ":" "constant string"
#line 2698 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4201 "dhcp4_parser.cc"
    break;

  case 786: // $@117: %empty
#line 2704 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4211 "dhcp4_parser.cc"
    break;

  case 787: // control_socket_address: "socket-address" $@117 ":" "constant string"
#line 2708 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4221 "dhcp4_parser.cc"
    break;

  case 788: // control_socket_port: "socket-port" ":" "integer"
#line 2714 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4231 "dhcp4_parser.cc"
    break;

  case 789: // cert_required: "cert-required" ":" "boolean"
#line 2720 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4241 "dhcp4_parser.cc"
    break;

  case 790: // $@118: %empty
#line 2726 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4253 "dhcp4_parser.cc"
    break;

  case 791: // http_headers: "http-headers" $@118 ":" "[" http_header_list "]"
#line 2732 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4262 "dhcp4_parser.cc"
    break;

  case 796: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2743 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4270 "dhcp4_parser.cc"
    break;

  case 797: // $@119: %empty
#line 2748 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4280 "dhcp4_parser.cc"
    break;

  case 798: // http_header: "{" $@119 http_header_params "}"
#line 2752 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4288 "dhcp4_parser.cc"
    break;

  case 801: // http_header_params: http_header_params ","
#line 2758 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4296 "dhcp4_parser.cc"
    break;

  case 807: // $@120: %empty
#line 2770 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4305 "dhcp4_parser.cc"
    break;

  case 808: // header_value: "value" $@120 ":" "constant string"
#line 2773 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4315 "dhcp4_parser.cc"
    break;

  case 809: // $@121: %empty
#line 2781 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4327 "dhcp4_parser.cc"
    break;

  case 810: // authentication: "authentication" $@121 ":" "{" auth_params "}"
#line 2787 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 813: // auth_params: auth_params ","
#line 2796 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4346 "dhcp4_parser.cc"
    break;

  case 821: // $@122: %empty
#line 2810 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4355 "dhcp4_parser.cc"
    break;

  case 822: // auth_type: "type" $@122 ":" auth_type_value
#line 2813 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4364 "dhcp4_parser.cc"
    break;

  case 823: // auth_type_value: "basic"
#line 2818 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4370 "dhcp4_parser.cc"
    break;

  case 824: // $@123: %empty
#line 2821 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4379 "dhcp4_parser.cc"
    break;

  case 825: // realm: "realm" $@123 ":" "constant string"
#line 2824 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4389 "dhcp4_parser.cc"
    break;

  case 826: // $@124: %empty
#line 2830 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 827: // directory: "directory" $@124 ":" "constant string"
#line 2833 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4408 "dhcp4_parser.cc"
    break;

  case 828: // $@125: %empty
#line 2839 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4420 "dhcp4_parser.cc"
    break;

  case 829: // clients: "clients" $@125 ":" "[" clients_list "]"
#line 2845 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4429 "dhcp4_parser.cc"
    break;

  case 834: // not_empty_clients_list: not_empty_clients_list ","
#line 2856 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4437 "dhcp4_parser.cc"
    break;

  case 835: // $@126: %empty
#line 2861 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4447 "dhcp4_parser.cc"
    break;

  case 836: // basic_auth: "{" $@126 clients_params "}"
#line 2865 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4455 "dhcp4_parser.cc"
    break;

  case 839: // clients_params: clients_params ","
#line 2871 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4463 "dhcp4_parser.cc"
    break;

  case 847: // $@127: %empty
#line 2885 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4472 "dhcp4_parser.cc"
    break;

  case 848: // user_file: "user-file" $@127 ":" "constant string"
#line 2888 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 849: // $@128: %empty
#line 2894 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4491 "dhcp4_parser.cc"
    break;

  case 850: // password_file: "password-file" $@128 ":" "constant string"
#line 2897 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4501 "dhcp4_parser.cc"
    break;

  case 851: // $@129: %empty
#line 2905 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4513 "dhcp4_parser.cc"
    break;

  case 852: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2911 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4524 "dhcp4_parser.cc"
    break;

  case 855: // queue_control_params: queue_control_params ","
#line 2920 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4532 "dhcp4_parser.cc"
    break;

  case 862: // enable_queue: "enable-queue" ":" "boolean"
#line 2933 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 863: // $@130: %empty
#line 2939 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4551 "dhcp4_parser.cc"
    break;

  case 864: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2942 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 865: // capacity: "capacity" ":" "integer"
#line 2948 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4571 "dhcp4_parser.cc"
    break;

  case 866: // $@131: %empty
#line 2954 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4580 "dhcp4_parser.cc"
    break;

  case 867: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2957 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 868: // $@132: %empty
#line 2964 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4601 "dhcp4_parser.cc"
    break;

  case 869: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 2970 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4612 "dhcp4_parser.cc"
    break;

  case 870: // $@133: %empty
#line 2977 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4622 "dhcp4_parser.cc"
    break;

  case 871: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 2981 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4632 "dhcp4_parser.cc"
    break;

  case 874: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2989 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4640 "dhcp4_parser.cc"
    break;

  case 886: // enable_updates: "enable-updates" ":" "boolean"
#line 3007 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4650 "dhcp4_parser.cc"
    break;

  case 887: // $@134: %empty
#line 3013 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4659 "dhcp4_parser.cc"
    break;

  case 888: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3016 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4669 "dhcp4_parser.cc"
    break;

  case 889: // server_port: "server-port" ":" "integer"
#line 3022 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4679 "dhcp4_parser.cc"
    break;

  case 890: // $@135: %empty
#line 3028 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4688 "dhcp4_parser.cc"
    break;

  case 891: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3031 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4698 "dhcp4_parser.cc"
    break;

  case 892: // sender_port: "sender-port" ":" "integer"
#line 3037 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 893: // max_queue_size: "max-queue-size" ":" "integer"
#line 3043 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4718 "dhcp4_parser.cc"
    break;

  case 894: // $@136: %empty
#line 3049 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4727 "dhcp4_parser.cc"
    break;

  case 895: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3052 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4736 "dhcp4_parser.cc"
    break;

  case 896: // ncr_protocol_value: "udp"
#line 3058 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4742 "dhcp4_parser.cc"
    break;

  case 897: // ncr_protocol_value: "tcp"
#line 3059 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4748 "dhcp4_parser.cc"
    break;

  case 898: // $@137: %empty
#line 3062 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4757 "dhcp4_parser.cc"
    break;

  case 899: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3065 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4767 "dhcp4_parser.cc"
    break;

  case 900: // $@138: %empty
#line 3073 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4779 "dhcp4_parser.cc"
    break;

  case 901: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3079 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4789 "dhcp4_parser.cc"
    break;

  case 902: // $@139: %empty
#line 3085 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4799 "dhcp4_parser.cc"
    break;

  case 903: // sub_config_control: "{" $@139 config_control_params "}"
#line 3089 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4808 "dhcp4_parser.cc"
    break;

  case 906: // config_control_params: config_control_params ","
#line 3097 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4816 "dhcp4_parser.cc"
    break;

  case 909: // $@140: %empty
#line 3107 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4828 "dhcp4_parser.cc"
    break;

  case 910: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3113 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4837 "dhcp4_parser.cc"
    break;

  case 911: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3118 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4847 "dhcp4_parser.cc"
    break;

  case 912: // $@141: %empty
#line 3126 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4859 "dhcp4_parser.cc"
    break;

  case 913: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3132 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4868 "dhcp4_parser.cc"
    break;

  case 916: // loggers_entries: loggers_entries ","
#line 3141 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4876 "dhcp4_parser.cc"
    break;

  case 917: // $@142: %empty
#line 3147 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4886 "dhcp4_parser.cc"
    break;

  case 918: // logger_entry: "{" $@142 logger_params "}"
#line 3151 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4894 "dhcp4_parser.cc"
    break;

  case 921: // logger_params: logger_params ","
#line 3157 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4902 "dhcp4_parser.cc"
    break;

  case 929: // debuglevel: "debuglevel" ":" "integer"
#line 3171 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4912 "dhcp4_parser.cc"
    break;

  case 930: // $@143: %empty
#line 3177 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4921 "dhcp4_parser.cc"
    break;

  case 931: // severity: "severity" $@143 ":" "constant string"
#line 3180 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4931 "dhcp4_parser.cc"
    break;

  case 932: // $@144: %empty
#line 3186 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4943 "dhcp4_parser.cc"
    break;

  case 933: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3192 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4952 "dhcp4_parser.cc"
    break;

  case 936: // output_options_list_content: output_options_list_content ","
#line 3199 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4960 "dhcp4_parser.cc"
    break;

  case 937: // $@145: %empty
#line 3204 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4970 "dhcp4_parser.cc"
    break;

  case 938: // output_entry: "{" $@145 output_params_list "}"
#line 3208 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4978 "dhcp4_parser.cc"
    break;

  case 941: // output_params_list: output_params_list ","
#line 3214 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4986 "dhcp4_parser.cc"
    break;

  case 947: // $@146: %empty
#line 3226 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4995 "dhcp4_parser.cc"
    break;

  case 948: // output: "output" $@146 ":" "constant string"
#line 3229 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5005 "dhcp4_parser.cc"
    break;

  case 949: // flush: "flush" ":" "boolean"
#line 3235 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5015 "dhcp4_parser.cc"
    break;

  case 950: // maxsize: "maxsize" ":" "integer"
#line 3241 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5025 "dhcp4_parser.cc"
    break;

  case 951: // maxver: "maxver" ":" "integer"
#line 3247 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5035 "dhcp4_parser.cc"
    break;

  case 952: // $@147: %empty
#line 3253 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5044 "dhcp4_parser.cc"
    break;

  case 953: // pattern: "pattern" $@147 ":" "constant string"
#line 3256 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5054 "dhcp4_parser.cc"
    break;

  case 954: // $@148: %empty
#line 3262 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5066 "dhcp4_parser.cc"
    break;

  case 955: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3268 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5075 "dhcp4_parser.cc"
    break;

  case 958: // compatibility_params: compatibility_params ","
#line 3275 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5083 "dhcp4_parser.cc"
    break;

  case 964: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3287 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5093 "dhcp4_parser.cc"
    break;

  case 965: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3293 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5103 "dhcp4_parser.cc"
    break;

  case 966: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3299 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5113 "dhcp4_parser.cc"
    break;

  case 967: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3305 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5123 "dhcp4_parser.cc"
    break;


#line 5127 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1369;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     507, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,    28,    26,    29,    39,    44,    54,
      80,    90,   111,   140,   179,   183,   193,   262, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,    26,  -168,   158,   205,   180,   726,
     784,   315,    34,   272,   321,   -79,   484,    68, -1369,   176,
     211,   252,   214,   306, -1369,    45, -1369, -1369, -1369, -1369,
     323,   338,   340, -1369, -1369, -1369,   342,   348, -1369, -1369,
   -1369,   367,   371,   372,   376,   399,   406,   409,   413,   422,
     427,   428, -1369,   431,   433,   434,   437,   439, -1369, -1369,
   -1369,   440,   445,   446,   447,   455,   456,   457, -1369, -1369,
   -1369,   458, -1369, -1369, -1369, -1369, -1369,   459,   460,   461,
   -1369, -1369, -1369, -1369, -1369,   465, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   466,   467,   468, -1369, -1369,   469, -1369,
     116, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   470,   472,   473,   474,
   -1369,   124, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   479, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   134, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     480, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   151, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   310,
     322, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   477, -1369, -1369,   482, -1369, -1369, -1369,
     483, -1369, -1369,   486,   485, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   487,   488,
     491, -1369, -1369, -1369, -1369, -1369,   489,   493, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   161, -1369, -1369, -1369,   495, -1369,   497, -1369,
     498,   501, -1369, -1369, -1369, -1369, -1369,   162, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   502,   169,
   -1369, -1369, -1369, -1369,    26,    26, -1369,   259,   503, -1369,
   -1369,   505,   506,   509,   277,   281,   283,   515,   516,   518,
     294,   295,   528,   529,   531,   309,   319,   326,   328,   330,
     302,   305,   307,   317,   334,   336,   544,   343,   344,   333,
     345,   351,   549,   551,   566,   354,   358,   361,   346,   363,
     364,   359,   573,   577,   578,   368,   579,   586,   594,   601,
     602,   374,   380,   383,   606,   614,   617,   619,   623,   396,
     627,   629,   634,   640,   642,   645,   648,   417,   420,   421,
     652,   655, -1369,   205, -1369,   658,   660,   663,   443,   444,
     448,   450,   180, -1369,   679,   680,   681,   698,   699,   708,
     481,   710,   714,   715,   734,   737,   726, -1369,   740,   514,
     784, -1369,   743,   744,   745,   746,   748,   749,   750,   751,
   -1369,   315, -1369,   758,   759,   532,   761,   762,   763,   534,
   -1369,   272,   765,   536,   537,   538,   769, -1369,   321,   770,
     771,   -43, -1369,   542,   773,   546,   777,   550,   552,   779,
     781,   484, -1369,   797,   556,    68, -1369, -1369, -1369,   798,
     796,   811,   815,   818, -1369, -1369, -1369,   595,   596,   603,
   -1369, -1369,   825,   826,   799, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   609, -1369, -1369, -1369,
   -1369, -1369,  -103,   610,   612, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   832,   847,   851, -1369,   626,   316,   853,   852,
     630, -1369, -1369, -1369,   870,   871,   872,   874,   873, -1369,
     875,   876,   879,   878,   880,   657,   659, -1369, -1369, -1369,
     881,   882, -1369,   886,   215,   120, -1369, -1369, -1369, -1369,
   -1369,   662,   664,   665,   892,   667,   668, -1369,   886,   886,
     886,   669,   897, -1369,   674, -1369, -1369,   886,   675,   676,
     677,   678,   683,   684,   685, -1369,   686,   689, -1369,   690,
     691,   692, -1369, -1369,   693, -1369, -1369, -1369,   886, -1369,
     696,   852, -1369, -1369,   697, -1369,   700, -1369, -1369,     4,
     471, -1369,   905, -1369, -1369,    26,   205,    68,   180,   329,
   -1369, -1369, -1369,   647,   647,   922, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   923,   925,   926, -1369, -1369,
   -1369, -1369, -1369, -1369,   927, -1369, -1369, -1369,   123,   928,
     929,   930,   247,   -69,   661,   931,   -74,   484, -1369, -1369,
     932,    -8, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   933, -1369, -1369, -1369, -1369, -1369, -1369,
     800, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   922, -1369,   172,   175,   181,
   -1369, -1369,   207, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     937,   938,   939,   940,   942,   943,   944,   945,   946,   947,
   -1369,   948,   949, -1369, -1369, -1369, -1369, -1369, -1369,   209,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,   210, -1369,   950,   951, -1369, -1369,
     952,   956, -1369, -1369,   954,   958, -1369, -1369,   957,   959,
   -1369, -1369,   960,   961, -1369, -1369, -1369, -1369, -1369, -1369,
     100, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   195, -1369,
   -1369,   962,   964, -1369, -1369,   963,   967, -1369,   968,   969,
     970,   971,   972,   973,   217, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   974,   975,   976, -1369,   218, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   977, -1369,   978, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   245, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   965,   982, -1369,   983,
   -1369,   984, -1369, -1369, -1369,   246, -1369, -1369, -1369, -1369,
   -1369,   297, -1369,   249, -1369,   985,   986,   987,   988, -1369,
     300, -1369, -1369, -1369, -1369, -1369,   724, -1369,   980,   991,
   -1369, -1369,   989, -1369,   992, -1369, -1369, -1369,   997,  1001,
     329, -1369,  1004,  1005,  1013,  1014,   733,   786,   791,   790,
     803,   809,   812,   814,   817,   822,  1027,   823,   846,  1054,
    1060,  1075,  1077,  1082,   647, -1369, -1369,   647, -1369,   922,
     726, -1369,   923,   272, -1369,   925,   321, -1369,   926,  1407,
   -1369,   927,   123, -1369,   349,   928, -1369,   315, -1369,   929,
     -79, -1369,   930,   855,   856,   862,   864,   867,   889,   247,
   -1369,   893,   899,   910,   -69, -1369,  1100,  1133,  1155,   953,
    1165,   941,  1173,   661, -1369,   661, -1369,   931,   955,  1178,
     966,  1180,   -74, -1369, -1369,   -20,   932, -1369,   979,   981,
     990,   993,    -8, -1369, -1369,  1181,  1185,   784, -1369,   933,
    1186, -1369, -1369,   764,   994, -1369,   995,   998,   999,  1000,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     331, -1369, -1369,  1002,  1003,  1006,  1007,  1008, -1369,   308,
   -1369,   314, -1369,  1184, -1369,  1187, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   318, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,  1190,  1193, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,  1191,  1197, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,  1194, -1369,   335, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     228,  1009,  1010, -1369,  1198, -1369,  1199, -1369,   337, -1369,
   -1369,  1011, -1369,    26, -1369, -1369,  1203, -1369, -1369, -1369,
   -1369, -1369,   347, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,  1012,   350, -1369,   886, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369,  1407, -1369,  1205,
    1206,  1015,  1017, -1369,   349, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,    73,  1204, -1369, -1369, -1369,  1208,   996,
    1212,   -20, -1369, -1369, -1369, -1369, -1369,  1016,  1021, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   356,
   -1369, -1369, -1369, -1369, -1369, -1369,  1211,  1215, -1369,  1214,
   -1369,  1022, -1369, -1369, -1369,  1216,  1217,  1218,  1219,    73,
   -1369,   -64, -1369,  1204,  1225, -1369,  1064,  1024,  1025,  1231,
   -1369, -1369, -1369, -1369, -1369, -1369,   357, -1369, -1369, -1369,
   -1369,   304, -1369, -1369, -1369, -1369, -1369,  1237,  1241,   -64,
   -1369,    18,  1225, -1369, -1369,  1240,  1245, -1369,  1028, -1369,
   -1369,  1254,  1256,  1258, -1369,   360, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,    75, -1369,  1237, -1369,  1259,  1031,  1035,
    1036,  1266,    18, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   366, -1369, -1369, -1369, -1369,  1040, -1369, -1369, -1369,
    1041, -1369,  1271,  1273,    75, -1369, -1369, -1369,  1048,  1050,
   -1369, -1369, -1369
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   214,     9,   394,    11,   621,    13,
     666,    15,   536,    17,   545,    19,   584,    21,   356,    23,
     870,    25,   902,    27,    46,    39,     0,     0,     0,     0,
       0,   668,     0,   547,   586,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   900,   199,   232,
       0,     0,     0,   688,   690,   692,     0,     0,   230,   243,
     245,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,   164,   171,
     173,     0,     0,     0,     0,     0,     0,     0,   385,   534,
     575,     0,   156,   177,   474,   653,   655,     0,     0,     0,
     318,   715,   657,   347,   368,     0,   333,   752,   754,   851,
     868,   187,   189,     0,     0,     0,   912,   954,     0,   141,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   104,   137,   138,    93,    94,    95,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   114,   115,   129,   130,   131,   133,   134,   135,
     139,   140,    78,    79,   101,    80,    81,    82,   132,    86,
      87,    76,   105,   106,   107,    77,    84,    85,    99,   100,
     102,    96,    97,    98,    83,    88,    89,    90,    91,    92,
     103,   113,   136,   216,   218,   222,     0,     0,     0,     0,
     213,     0,   201,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   454,   456,   458,   612,   452,   460,     0,   464,
     466,   468,   462,   710,   451,   399,   400,   401,   402,   403,
     428,   429,   430,   431,   432,   449,   418,   419,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   450,     0,   396,   406,   423,   424,
     425,   407,   409,   410,   411,   412,   414,   415,   416,   408,
     404,   405,   426,   427,   413,   420,   421,   422,   417,   650,
       0,   649,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   629,   630,   631,   632,
     628,     0,   623,   626,   627,   647,   648,   708,   694,   696,
     698,   702,   700,   706,   704,   687,   681,   685,   686,     0,
     669,   670,   682,   683,   684,   678,   673,   679,   675,   676,
     677,   680,   674,     0,   565,   290,     0,   569,   567,   572,
       0,   561,   562,     0,   548,   549,   552,   564,   553,   554,
     555,   571,   556,   557,   558,   559,   560,   603,     0,     0,
       0,   610,   601,   602,   605,   606,     0,   587,   588,   591,
     592,   593,   594,   595,   596,   597,   600,   598,   599,   364,
     366,   361,     0,   358,   362,   363,     0,   887,     0,   890,
       0,     0,   894,   898,   885,   883,   884,     0,   872,   875,
     876,   877,   878,   879,   880,   881,   882,   909,     0,     0,
     904,   907,   908,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    69,    66,     0,     0,     0,     0,     0,
       0,     0,   203,   215,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   398,   395,     0,     0,
     625,   622,     0,     0,     0,     0,     0,     0,     0,     0,
     667,   672,   537,     0,     0,     0,     0,     0,     0,     0,
     546,   551,     0,     0,     0,     0,     0,   585,   590,     0,
       0,   360,   357,     0,     0,     0,     0,     0,     0,     0,
       0,   874,   871,     0,     0,   906,   903,    49,    41,     0,
       0,     0,     0,     0,   158,   159,   160,     0,     0,     0,
     197,   198,     0,     0,     0,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     0,   192,   193,   161,
     162,   163,     0,     0,     0,   175,   176,   183,   184,   185,
     186,   191,     0,     0,     0,   155,     0,     0,     0,     0,
       0,   470,   471,   472,     0,     0,     0,     0,     0,   751,
       0,     0,     0,     0,     0,     0,     0,   194,   195,   196,
       0,     0,    68,     0,     0,     0,   226,   227,   228,   229,
     202,     0,     0,     0,     0,     0,     0,   473,     0,     0,
       0,     0,     0,   397,     0,   652,   624,     0,     0,     0,
       0,     0,     0,     0,     0,   671,     0,     0,   563,     0,
       0,     0,   574,   550,     0,   607,   608,   609,     0,   589,
       0,     0,   359,   886,     0,   889,     0,   892,   893,     0,
       0,   873,     0,   911,   905,     0,     0,     0,     0,     0,
     689,   691,   693,     0,     0,   247,   154,   166,   167,   168,
     169,   170,   165,   172,   174,   387,   538,   577,   157,   179,
     180,   181,   182,   178,   476,    38,   654,   656,     0,     0,
     659,   349,     0,     0,     0,   756,     0,     0,   188,   190,
       0,     0,    51,   217,   220,   221,   219,   224,   225,   223,
     455,   457,   459,   614,   453,   461,   465,   467,   469,   463,
       0,   651,   709,   695,   697,   699,   703,   701,   707,   705,
     566,   291,   570,   568,   573,   604,   611,   365,   367,   888,
     891,   896,   897,   895,   899,   247,    42,     0,     0,     0,
     239,   241,     0,   234,   237,   238,   281,   283,   285,   287,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,   308,   310,   312,   314,   316,   280,     0,
     254,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,     0,   252,     0,   248,   249,   392,
       0,   388,   389,   543,     0,   539,   540,   582,     0,   578,
     579,   481,     0,   477,   478,   328,   329,   330,   331,   332,
       0,   320,   323,   324,   325,   326,   327,   720,     0,   717,
     664,     0,   660,   661,   354,     0,   350,   351,     0,     0,
       0,     0,     0,     0,     0,   370,   373,   374,   375,   376,
     377,   378,     0,     0,     0,   343,     0,   335,   338,   339,
     340,   341,   342,   779,   784,   786,     0,   809,     0,   790,
     778,   771,   772,   773,   776,   777,     0,   763,   766,   767,
     768,   769,   774,   775,   770,   761,     0,   757,   758,     0,
     863,     0,   866,   859,   860,     0,   853,   856,   857,   858,
     861,     0,   917,     0,   914,     0,     0,     0,     0,   963,
       0,   956,   959,   960,   961,   962,    53,   619,     0,   615,
     616,   713,     0,   712,     0,    62,   901,   200,     0,     0,
     236,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   256,   231,   244,     0,   246,   251,
       0,   386,   391,   547,   535,   542,   586,   576,   581,     0,
     475,   480,   322,   319,   722,   719,   716,   668,   658,   663,
       0,   348,   353,     0,     0,     0,     0,     0,     0,   372,
     369,     0,     0,     0,   337,   334,     0,     0,     0,     0,
       0,     0,     0,   765,   753,     0,   755,   760,     0,     0,
       0,     0,   855,   852,   869,     0,   916,   913,     0,     0,
       0,     0,   958,   955,    55,     0,    54,     0,   613,   618,
       0,   711,   910,     0,     0,   235,     0,     0,     0,     0,
     289,   292,   293,   294,   295,   296,   297,   298,   299,   300,
       0,   306,   307,     0,     0,     0,     0,     0,   255,     0,
     250,     0,   390,     0,   541,     0,   580,   533,   505,   506,
     507,   489,   490,   510,   511,   512,   513,   514,   531,   492,
     493,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   532,   486,   487,
     488,   501,   502,   503,   504,   498,   499,   500,     0,   483,
     491,   508,   509,   494,   495,   496,   497,   479,   321,   745,
     747,     0,     0,   739,   740,   741,   742,   743,   744,   732,
     733,   737,   738,   734,   735,   736,     0,   723,   724,   727,
     728,   729,   730,   731,   718,     0,   662,     0,   352,   379,
     380,   381,   382,   383,   384,   371,   344,   345,   346,   336,
       0,     0,     0,   788,     0,   789,     0,   764,     0,   759,
     862,     0,   865,     0,   854,   932,     0,   930,   928,   922,
     926,   927,     0,   919,   924,   925,   923,   915,   964,   965,
     966,   967,   957,    52,    57,     0,   617,     0,   240,   242,
     282,   284,   286,   288,   303,   304,   305,   302,   309,   311,
     313,   315,   317,   253,   393,   544,   583,   485,   482,     0,
       0,     0,     0,   721,   726,   665,   355,   781,   782,   783,
     780,   785,   787,     0,   792,   762,   864,   867,     0,     0,
       0,   921,   918,    56,   620,   714,   484,     0,     0,   749,
     750,   725,   821,   824,   826,   828,   820,   819,   818,     0,
     811,   814,   815,   816,   817,   797,     0,   793,   794,     0,
     929,     0,   920,   746,   748,     0,     0,     0,     0,   813,
     810,     0,   791,   796,     0,   931,     0,     0,     0,     0,
     812,   807,   806,   802,   804,   805,     0,   799,   803,   795,
     937,     0,   934,   823,   822,   825,   827,   830,     0,   801,
     798,     0,   936,   933,   835,     0,   831,   832,     0,   800,
     947,     0,     0,     0,   952,     0,   939,   942,   943,   944,
     945,   946,   935,     0,   829,   834,   808,     0,     0,     0,
       0,     0,   941,   938,   847,   849,   846,   840,   842,   844,
     845,     0,   837,   841,   843,   833,     0,   949,   950,   951,
       0,   940,     0,     0,   839,   836,   948,   953,     0,     0,
     838,   848,   850
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   -59, -1369,  -617, -1369,   553,
   -1369, -1369, -1369, -1369, -1369, -1369,  -640, -1369, -1369, -1369,
     -67, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   540,   754,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
   -1369, -1369, -1369, -1369,    94, -1369, -1369,    97,   102,   -13,
      13,    41,    51, -1369, -1369,    53, -1369,    56, -1369,    59,
     104,    64, -1369, -1369,    66,    69,    74,    76,    79, -1369,
      81, -1369,   105, -1369, -1369, -1369, -1369, -1369,    43, -1369,
   -1369, -1369,   535,   752, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   260, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   463, -1369,   223, -1369,  -738,   239, -1369, -1369,
   -1368, -1369, -1363, -1369, -1369, -1369, -1369,   -63, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,  -770, -1369,  -769, -1369,  -766, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   224, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   201, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   219, -1369, -1369, -1369,   220,   711, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   216, -1369, -1369, -1369,
   -1369, -1369, -1369, -1052, -1369, -1369, -1369,   241, -1369, -1369,
   -1369,   248,   753, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1050, -1369,   -29, -1369,   -18, -1369,    -4, -1369,     5,
   -1369,   107,   110,   112, -1369, -1369, -1369, -1369, -1369,   235,
   -1369, -1369,   -10,   -60, -1369, -1369, -1369, -1369, -1369,   250,
   -1369, -1369, -1369,   253, -1369,   730, -1369,   -34, -1369, -1369,
   -1369, -1369, -1369,   -27, -1369, -1369, -1369, -1369, -1369,   -32,
   -1369, -1369, -1369,   251, -1369, -1369, -1369,   255, -1369,   735,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,   196, -1369, -1369, -1369,   197,   766,
   -1369, -1369, -1369,   -44, -1369,     3, -1369,   -56, -1369, -1369,
   -1369,   264, -1369, -1369, -1369,   254, -1369,   757,   -48, -1369,
      -7, -1369,    15, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1049, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   263, -1369,
   -1369, -1369,    10, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369,   222, -1369,   236,
     242, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,   -36, -1369, -1369,   -58, -1369, -1369,
   -1369, -1369, -1369,   -30, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   -83, -1369, -1369,  -111, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   244, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369,   567,   760, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   615,   767, -1369, -1369,
   -1369, -1369, -1369, -1369,   243, -1369, -1369,    22, -1369, -1369,
   -1369, -1369, -1369, -1369,   -41, -1369, -1369,   -78, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   256, -1369,
   -1369, -1369, -1369
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   776,
      82,    83,    39,    64,    79,    80,   793,  1016,  1125,  1126,
     868,    41,    66,    85,   458,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   486,   174,   175,   506,   176,   177,   178,   179,
     180,   181,   182,   492,   762,   183,   493,   184,   494,   185,
     186,   187,   507,   773,   188,   189,   190,   191,   192,   525,
     193,   526,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   462,   241,   242,    45,    68,   243,   535,   244,   536,
     796,   245,   537,   799,   246,   247,   248,   249,   203,   472,
     204,   463,   842,   843,   844,  1028,   845,  1029,   205,   473,
     206,   474,   896,   897,   898,  1057,   869,   870,   871,  1032,
     872,  1033,   873,  1034,   874,  1035,   875,   876,   574,   877,
     878,   879,   880,   881,   882,   883,   884,   885,   886,  1046,
    1307,   887,   888,   889,  1049,   890,  1050,   891,  1051,   892,
    1052,   893,  1053,   207,   514,   920,   921,   922,   923,   924,
     925,   926,   208,   520,   956,   957,   958,   959,   960,   209,
     517,   935,   936,   937,  1080,    59,    75,   422,   423,   424,
     589,   425,   590,   210,   518,   944,   945,   946,   947,   948,
     949,   950,   951,   211,   502,   900,   901,   902,  1060,    47,
      69,   295,   296,   297,   548,   298,   544,   299,   545,   300,
     546,   301,   549,   302,   554,   303,   551,   304,   552,   305,
     553,   212,   213,   214,   309,   215,   508,   912,   913,   914,
    1069,  1208,  1209,   216,   503,    53,    72,   904,   905,   906,
    1063,    55,    73,   383,   384,   385,   386,   387,   388,   389,
     573,   390,   577,   391,   576,   392,   393,   578,   394,   217,
     504,   908,   909,   910,  1066,    57,    74,   406,   407,   408,
     409,   410,   582,   411,   412,   413,   414,   415,   416,   586,
     311,   547,  1018,  1019,  1020,  1127,    49,    70,   341,   342,
     343,   558,   344,   218,   509,   219,   510,   220,   516,   931,
     932,   933,  1077,    51,    71,   359,   360,   361,   221,   467,
     222,   468,   223,   469,   365,   563,   366,   564,   367,   565,
     368,   567,   369,   566,   370,   569,   371,   568,   372,   562,
     318,   555,  1022,  1023,  1130,   224,   515,   928,   929,  1074,
    1236,  1237,  1238,  1239,  1240,  1319,  1241,  1320,  1242,  1243,
     225,   226,   521,   227,   522,   986,   987,   988,  1105,   976,
     977,   978,  1096,  1330,   979,  1097,   980,  1098,   981,   982,
     983,  1102,  1366,  1367,  1368,  1381,  1396,  1397,  1398,  1408,
     984,  1100,  1359,  1360,  1361,  1375,  1404,  1362,  1376,  1363,
    1377,  1364,  1378,  1415,  1416,  1417,  1433,  1451,  1452,  1453,
    1462,  1454,  1463,   228,   523,   995,   996,   997,   998,  1109,
     999,  1000,  1111,   229,   524,    61,    76,   437,   438,   439,
     440,   594,   441,   442,   596,   443,   444,   445,   599,   833,
     446,   600,   230,   461,    63,    77,   449,   450,   451,   603,
     452,   231,   530,  1003,  1004,  1115,  1282,  1283,  1284,  1285,
    1340,  1286,  1338,  1401,  1402,  1411,  1425,  1426,  1427,  1437,
    1428,  1429,  1430,  1431,  1441,   232,   531,  1010,  1011,  1012,
    1013,  1014,  1015
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   321,   355,    78,   381,   402,   421,   434,
     382,   403,   373,   314,   971,   972,   894,  1199,   973,  1200,
    1216,   315,   831,   362,   250,   312,   345,   357,    28,   395,
     417,    29,   435,    30,   375,    31,    40,   310,   340,   356,
     404,   336,   775,   268,   135,   136,    42,   405,   459,   135,
     136,    44,   337,   460,   135,   136,   278,   322,   806,   807,
     808,    46,   316,    81,   363,  1447,   338,   812,   419,   420,
    1448,   251,   313,   346,   358,   339,   396,   418,   375,   436,
     447,   448,   279,   323,   317,   265,   364,    48,   826,   952,
     953,   954,   757,   758,   759,   760,  1447,    50,   135,   136,
     266,  1448,   267,  1072,   419,   420,  1073,   989,   990,   991,
     280,   324,   294,  1352,   775,  1391,   847,   848,    52,   533,
     281,   325,   282,   326,   534,   283,   327,   542,   284,   328,
     129,   761,   543,   286,   329,   287,   330,   556,   288,   331,
     797,   798,   557,   289,   332,   290,   333,    54,   291,   334,
     292,   335,   158,   269,   560,   270,   271,   992,   272,   561,
     273,   274,   158,   275,   591,   601,   276,   158,    84,   592,
     602,   277,   605,   285,   293,   533,   306,   606,   605,   307,
    1025,   308,   453,  1026,   542,  1275,    56,  1276,  1277,  1027,
      58,   135,   136,   135,   136,   233,   234,   832,  1075,   235,
      60,  1076,   236,   237,   238,   239,  1005,  1006,  1007,  1008,
    1030,   158,  1054,  1054,   454,  1031,    87,  1055,  1056,    88,
    1089,  1094,   456,   158,  1420,  1090,  1095,  1421,  1422,  1423,
    1424,    89,   794,   795,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,  1353,  1354,  1355,  1103,  1112,
    1444,  1445,  1116,  1104,  1113,  1117,   455,    32,    33,    34,
      35,   915,   916,   917,   918,  1199,   919,  1200,  1216,    62,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   135,   136,
     601,   129,   130,  1122,   158,  1114,   158,  1412,  1123,   457,
    1413,  1054,   374,   131,   132,   133,  1313,   556,   570,  1159,
     134,  1317,  1314,   135,   136,   571,  1318,   464,   137,   138,
     139,   140,   141,   971,   972,   971,   972,   973,   591,   973,
    1103,   142,   465,  1326,   466,  1335,   470,    93,    94,    95,
    1341,   143,   471,   560,   144,  1342,   840,   841,  1344,  1379,
    1409,   145,   146,  1442,  1380,  1410,   147,   148,  1443,  1464,
     375,   475,   376,   377,  1465,   476,   477,   378,   379,   380,
     478,    93,    94,    95,    96,   149,  1304,  1305,  1306,   150,
     135,   136,  1327,  1328,  1329,   607,   608,   938,   939,   940,
     941,   942,   943,   479,   151,   152,   153,   154,   155,   156,
     480,   158,   130,   481,   101,   102,   103,   482,   157,   375,
     397,   376,   377,   398,   399,   400,   483,   769,   770,   771,
     772,   484,   485,   135,   136,   487,   158,   488,   489,   135,
     136,   490,   347,   491,   495,   129,   130,   375,   401,   496,
     497,   498,   348,   349,   350,   351,   352,   353,   354,   499,
     500,   501,   505,   511,   512,   513,   159,   135,   136,   519,
     527,   528,   529,   532,   538,   240,   539,   540,   541,  1219,
    1220,  1221,  1222,   550,   559,   572,   575,   579,   581,   264,
     609,   583,   584,   321,   580,   585,   588,   587,   250,   593,
     314,   595,   597,   158,   355,   598,   604,   610,   315,   611,
     612,   614,   312,   613,   381,   615,   345,   616,   382,   617,
     618,   402,   619,   362,   310,   403,   620,   357,   340,   621,
     268,   336,   622,   623,   434,   624,   630,   395,   631,   356,
     632,   625,   337,   278,   417,   251,   158,   322,   636,   316,
     633,   626,   158,   642,   404,   643,   338,   435,   627,   313,
     628,   405,   629,   346,   363,   339,   634,   639,   635,   279,
     644,   317,   265,   323,   358,   637,   638,   652,   648,   640,
     158,   653,   654,   656,   396,   641,   364,   266,   645,   267,
     657,   418,   646,   651,   647,   649,   650,   280,   658,   294,
     655,   324,   135,   136,   436,   659,   660,   281,   661,   282,
     664,   325,   283,   326,   662,   284,   327,   663,   665,   328,
     286,   666,   287,   667,   329,   288,   330,   668,   669,   331,
     289,   670,   290,   671,   332,   291,   333,   292,   672,   334,
     269,   335,   270,   271,   673,   272,   674,   273,   274,   675,
     275,   677,   676,   276,   678,   679,   680,  1345,   277,   681,
     285,   293,   683,   306,   684,   834,   307,   685,   308,   426,
     427,   428,   429,   430,   431,   432,   433,   686,   687,   159,
     688,   240,   689,   691,   692,   693,   836,   846,   847,   848,
     849,   850,   851,   852,   853,   854,   855,   856,   857,   858,
     859,   860,   694,   695,   250,   861,   862,   863,   864,   865,
     866,   867,   696,   697,   698,   158,   955,   970,   699,   700,
     434,   863,   864,   865,  1009,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   701,   961,
     974,   702,   993,   435,   704,   375,   705,   707,   708,   709,
     710,   251,   711,   712,   713,   714,    91,    92,    93,    94,
      95,    96,   716,   717,   718,   719,   720,   721,   722,   724,
     725,   726,   727,   728,   730,   731,   733,   734,   735,   135,
     136,   736,   737,   739,   738,   740,   962,   975,   743,   994,
     436,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   742,   745,   746,   755,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   747,   252,
     253,   254,   748,   130,   963,   749,   750,   751,   964,   965,
     966,   967,   753,   754,   752,   132,   133,   765,   968,   969,
     756,   763,   255,   764,   135,   136,   256,   257,   258,   137,
     138,   139,   766,   259,   260,   261,   767,   768,   774,    30,
     262,   777,   142,   115,   116,   117,   118,   119,   120,   121,
     263,   123,   124,   125,   126,   778,   779,   780,   158,   781,
     782,   130,   783,   784,   785,   786,   790,   787,   788,   791,
     789,   792,   158,   800,   133,   801,   802,   803,   804,   805,
     809,   319,   135,   136,   810,   811,   813,   814,   815,   816,
     835,   259,   260,   261,   817,   818,   819,   820,   262,   320,
     821,   822,   823,   824,   825,   151,   152,   827,   829,   895,
     899,   830,   903,   907,   911,   927,   930,   934,   985,  1002,
    1017,  1036,  1037,  1038,  1039,  1021,  1040,  1041,  1042,  1043,
    1044,  1045,  1047,  1048,  1059,  1124,  1058,   158,  1061,  1062,
    1064,  1065,  1068,  1067,  1071,  1140,  1070,  1079,  1078,  1081,
    1082,  1106,  1083,  1084,  1085,  1086,  1087,  1088,  1091,  1092,
    1093,  1099,  1101,   151,   152,  1107,  1128,  1108,  1110,  1118,
    1119,  1120,  1121,   264,  1129,  1298,   381,  1131,  1132,   402,
     382,  1133,  1167,   403,   314,  1134,  1198,  1223,  1136,  1137,
     355,  1228,   315,   421,  1229,   158,   312,  1138,  1139,   395,
    1141,  1213,   417,  1142,  1143,  1211,  1233,   955,   310,   362,
    1231,  1150,   404,   357,   268,  1144,   970,  1210,   970,   405,
    1201,  1145,  1230,  1171,  1146,   356,  1147,   278,  1278,  1148,
     961,  1202,  1279,   316,  1149,  1009,  1181,  1151,  1153,   974,
     321,   974,  1214,   313,  1154,  1203,   396,  1234,   993,   418,
     363,  1280,  1212,   279,  1204,   317,   265,  1232,  1152,  1155,
     358,  1156,  1182,   345,  1215,  1168,  1157,  1249,  1250,  1235,
    1224,   266,   364,   267,  1251,   340,  1252,   962,   336,  1253,
    1169,   280,  1170,   294,  1260,  1225,   975,  1226,   975,   337,
    1183,   281,  1197,   282,   322,   994,   283,  1227,  1281,   284,
    1184,  1254,  1185,   338,   286,  1186,   287,  1256,  1187,   288,
     346,  1257,   339,  1189,   289,  1190,   290,  1261,  1191,   291,
     323,   292,  1258,  1192,   269,  1193,   270,   271,  1194,   272,
    1195,   273,   274,  1172,   275,  1173,  1174,   276,  1175,  1262,
    1176,  1177,   277,  1178,   285,   293,  1179,   306,   324,  1264,
     307,  1180,   308,  1188,  1196,  1265,  1205,  1266,   325,  1206,
     326,  1207,  1271,   327,  1273,  1263,   328,  1293,  1294,  1270,
    1297,   329,  1315,   330,  1321,  1316,   331,  1322,  1272,  1323,
    1324,   332,  1325,   333,  1334,  1333,   334,  1339,   335,  1347,
    1348,  1365,  1369,  1288,  1337,  1289,  1371,  1382,  1383,  1384,
    1386,  1387,  1388,  1389,  1290,  1299,  1300,  1291,  1370,  1301,
    1302,  1303,  1400,  1308,  1309,  1403,  1407,  1310,  1311,  1312,
    1331,  1332,  1336,  1343,  1414,  1418,  1434,  1373,  1435,  1349,
    1167,  1350,  1374,  1385,  1198,  1405,  1406,  1223,  1438,  1436,
    1439,  1228,  1440,  1456,  1229,  1457,  1356,  1458,  1459,  1213,
    1460,  1466,  1467,  1211,  1278,  1468,  1233,  1469,  1279,  1471,
    1231,  1472,  1160,   839,   828,  1210,   837,   682,  1201,  1357,
    1135,  1171,  1230,  1158,   690,  1259,  1218,  1280,  1024,  1202,
    1247,  1248,   732,  1162,  1181,  1255,  1217,  1346,  1161,   703,
    1214,   723,  1356,  1203,  1392,  1164,  1163,  1234,  1393,  1166,
    1212,  1165,  1204,   729,  1295,  1296,   706,  1232,   715,  1269,
    1182,  1245,  1215,  1168,  1351,  1357,  1358,  1394,  1244,  1235,
    1224,  1268,  1392,  1246,  1281,  1267,  1393,  1399,  1169,  1390,
    1170,  1419,  1455,  1470,  1001,  1225,  1274,  1226,  1183,  1287,
    1197,   741,   838,  1372,  1461,  1394,  1446,  1227,  1184,     0,
    1185,  1432,   744,  1186,     0,     0,  1187,     0,  1292,     0,
       0,  1189,  1358,  1190,  1395,     0,  1191,     0,     0,  1449,
       0,  1192,     0,  1193,     0,     0,  1194,  1446,  1195,     0,
       0,  1172,     0,  1173,  1174,     0,  1175,     0,  1176,  1177,
       0,  1178,  1395,     0,  1179,     0,     0,     0,     0,  1180,
    1449,  1188,  1196,     0,  1205,     0,     0,  1206,     0,  1207,
       0,     0,     0,     0,     0,     0,  1450,    91,    92,    93,
      94,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1450,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,   130,   375,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132,   133,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,   257,     0,
     137,   138,   139,     0,   259,   260,   261,     0,     0,     0,
       0,   262,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   263,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   784,   784,   754,  1069,   784,  1069,
    1069,    69,    18,    71,    68,    69,    70,    71,     0,    73,
      74,     5,    76,     7,    98,     9,     7,    69,    70,    71,
      74,    70,   659,    69,   118,   119,     7,    74,     3,   118,
     119,     7,    70,     8,   118,   119,    69,    70,   698,   699,
     700,     7,    69,   231,    71,  1433,    70,   707,   147,   148,
    1433,    68,    69,    70,    71,    70,    73,    74,    98,    76,
      12,    13,    69,    70,    69,    69,    71,     7,   728,   158,
     159,   160,   195,   196,   197,   198,  1464,     7,   118,   119,
      69,  1464,    69,     3,   147,   148,     6,   181,   182,   183,
      69,    70,    69,    40,   731,   179,    41,    42,     7,     3,
      69,    70,    69,    70,     8,    69,    70,     3,    69,    70,
      96,   234,     8,    69,    70,    69,    70,     3,    69,    70,
      20,    21,     8,    69,    70,    69,    70,     7,    69,    70,
      69,    70,   231,    69,     3,    69,    69,   231,    69,     8,
      69,    69,   231,    69,     3,     3,    69,   231,    10,     8,
       8,    69,     3,    69,    69,     3,    69,     8,     3,    69,
       8,    69,     6,     8,     3,   205,     7,   207,   208,     8,
       7,   118,   119,   118,   119,    15,    16,   193,     3,    19,
       7,     6,    22,    23,    24,    25,   214,   215,   216,   217,
       3,   231,     3,     3,     3,     8,    11,     8,     8,    14,
       3,     3,     8,   231,   206,     8,     8,   209,   210,   211,
     212,    26,    17,    18,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,   172,   173,   174,     3,     3,
     175,   176,     3,     8,     8,     6,     4,   231,   232,   233,
     234,   138,   139,   140,   141,  1317,   143,  1317,  1317,     7,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,   118,   119,
       3,    96,    97,     3,   231,     8,   231,     3,     8,     3,
       6,     3,    40,   108,   109,   110,     8,     3,     8,  1057,
     115,     3,     8,   118,   119,     3,     8,     4,   123,   124,
     125,   126,   127,  1103,  1103,  1105,  1105,  1103,     3,  1105,
       3,   136,     4,     8,     4,     8,     4,    32,    33,    34,
       3,   146,     4,     3,   149,     8,    27,    28,     8,     3,
       3,   156,   157,     3,     8,     8,   161,   162,     8,     3,
      98,     4,   100,   101,     8,     4,     4,   105,   106,   107,
       4,    32,    33,    34,    35,   180,    55,    56,    57,   184,
     118,   119,   164,   165,   166,   454,   455,   150,   151,   152,
     153,   154,   155,     4,   199,   200,   201,   202,   203,   204,
       4,   231,    97,     4,    65,    66,    67,     4,   213,    98,
      99,   100,   101,   102,   103,   104,     4,   111,   112,   113,
     114,     4,     4,   118,   119,     4,   231,     4,     4,   118,
     119,     4,   127,     4,     4,    96,    97,    98,   127,     4,
       4,     4,   137,   138,   139,   140,   141,   142,   143,     4,
       4,     4,     4,     4,     4,     4,   533,   118,   119,     4,
       4,     4,     4,     4,     4,   542,     4,     4,     4,   130,
     131,   132,   133,     4,     4,     8,     4,     4,     3,   556,
     231,     4,     4,   560,     8,     4,     3,     8,   542,     4,
     556,     4,     4,   231,   571,     4,     4,     4,   556,     4,
       4,   234,   556,     4,   581,   234,   560,   234,   581,     4,
       4,   588,     4,   571,   556,   588,   232,   571,   560,   234,
     556,   560,     4,     4,   601,     4,   234,   581,   233,   571,
     233,   232,   560,   556,   588,   542,   231,   560,     4,   556,
     233,   232,   231,     4,   588,     4,   560,   601,   232,   556,
     232,   588,   232,   560,   571,   560,   232,   234,   232,   556,
       4,   556,   556,   560,   571,   232,   232,     4,   232,   234,
     231,     4,     4,     4,   581,   234,   571,   556,   234,   556,
       4,   588,   234,   234,   233,   232,   232,   556,     4,   556,
     232,   560,   118,   119,   601,     4,     4,   556,   234,   556,
       4,   560,   556,   560,   234,   556,   560,   234,     4,   560,
     556,     4,   556,     4,   560,   556,   560,     4,   232,   560,
     556,     4,   556,     4,   560,   556,   560,   556,     4,   560,
     556,   560,   556,   556,     4,   556,     4,   556,   556,     4,
     556,   234,     4,   556,   234,   234,     4,  1297,   556,     4,
     556,   556,     4,   556,     4,   194,   556,     4,   556,   185,
     186,   187,   188,   189,   190,   191,   192,   234,   234,   746,
     232,   748,   232,     4,     4,     4,   745,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,     4,     4,   748,    58,    59,    60,    61,    62,
      63,    64,     4,   232,     4,   231,   783,   784,     4,     4,
     787,    60,    61,    62,   791,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,     4,   783,
     784,     4,   786,   787,     4,    98,   232,     4,     4,     4,
       4,   748,     4,     4,     4,     4,    30,    31,    32,    33,
      34,    35,     4,     4,   232,     4,     4,     4,   234,     4,
     234,   234,   234,     4,     4,     4,   234,     4,   232,   118,
     119,     4,   232,     4,   232,     4,   783,   784,   232,   786,
     787,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     4,     4,     7,     5,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,     7,    93,
      94,    95,     7,    97,   163,     7,   231,   231,   167,   168,
     169,   170,     7,     7,   231,   109,   110,     5,   177,   178,
     231,   231,   116,   231,   118,   119,   120,   121,   122,   123,
     124,   125,     5,   127,   128,   129,     5,   231,     5,     7,
     134,   231,   136,    79,    80,    81,    82,    83,    84,    85,
     144,    87,    88,    89,    90,     5,     5,     5,   231,     5,
       7,    97,     7,     7,     5,     7,     5,     7,   231,     7,
     231,     5,   231,   231,   110,   231,   231,     5,   231,   231,
     231,   117,   118,   119,     7,   231,   231,   231,   231,   231,
       5,   127,   128,   129,   231,   231,   231,   231,   134,   135,
     231,   231,   231,   231,   231,   199,   200,   231,   231,     7,
       7,   231,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     4,     4,     4,     4,   145,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   231,     6,   231,     6,     3,
       6,     3,     3,     6,     3,   232,     6,     3,     6,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   199,   200,     3,     6,     4,     4,     4,
       4,     4,     4,  1060,     3,   231,  1063,     8,     6,  1066,
    1063,     4,  1069,  1066,  1060,     4,  1069,  1074,     4,     4,
    1077,  1074,  1060,  1080,  1074,   231,  1060,     4,     4,  1063,
     234,  1069,  1066,   232,   234,  1069,  1074,  1094,  1060,  1077,
    1074,     4,  1066,  1077,  1060,   232,  1103,  1069,  1105,  1066,
    1069,   232,  1074,  1069,   232,  1077,   232,  1060,  1115,   232,
    1094,  1069,  1115,  1060,   232,  1122,  1069,   234,     4,  1103,
    1127,  1105,  1069,  1060,     4,  1069,  1063,  1074,  1112,  1066,
    1077,  1115,  1069,  1060,  1069,  1060,  1060,  1074,   232,     4,
    1077,     4,  1069,  1127,  1069,  1069,     4,   232,   232,  1074,
    1074,  1060,  1077,  1060,   232,  1127,   232,  1094,  1127,   232,
    1069,  1060,  1069,  1060,     4,  1074,  1103,  1074,  1105,  1127,
    1069,  1060,  1069,  1060,  1127,  1112,  1060,  1074,  1115,  1060,
    1069,   232,  1069,  1127,  1060,  1069,  1060,   234,  1069,  1060,
    1127,   232,  1127,  1069,  1060,  1069,  1060,     4,  1069,  1060,
    1127,  1060,   232,  1069,  1060,  1069,  1060,  1060,  1069,  1060,
    1069,  1060,  1060,  1069,  1060,  1069,  1069,  1060,  1069,     4,
    1069,  1069,  1060,  1069,  1060,  1060,  1069,  1060,  1127,     4,
    1060,  1069,  1060,  1069,  1069,   234,  1069,     4,  1127,  1069,
    1127,  1069,     4,  1127,     4,   232,  1127,     6,     3,   234,
       4,  1127,     8,  1127,     4,     8,  1127,     4,   232,     8,
       3,  1127,     8,  1127,     5,     7,  1127,     4,  1127,     4,
       4,     7,     4,   234,  1273,   234,     4,     6,     3,     5,
       4,     4,     4,     4,   234,   231,   231,   234,   232,   231,
     231,   231,     7,   231,   231,   171,     5,   231,   231,   231,
     231,   231,   231,   231,     7,     4,     6,   231,     3,   234,
    1317,   234,   231,   231,  1317,   231,   231,  1324,     4,   231,
       4,  1324,     4,     4,  1324,   234,  1333,   232,   232,  1317,
       4,   231,   231,  1317,  1341,     4,  1324,     4,  1341,   231,
    1324,   231,  1059,   748,   731,  1317,   746,   533,  1317,  1333,
    1030,  1317,  1324,  1054,   542,  1094,  1072,  1341,   835,  1317,
    1080,  1082,   591,  1062,  1317,  1089,  1071,  1317,  1060,   556,
    1317,   581,  1379,  1317,  1381,  1065,  1063,  1324,  1381,  1068,
    1317,  1066,  1317,   588,  1127,  1129,   560,  1324,   571,  1107,
    1317,  1077,  1317,  1317,  1324,  1379,  1333,  1381,  1075,  1324,
    1324,  1105,  1409,  1079,  1341,  1103,  1409,  1383,  1317,  1379,
    1317,  1409,  1435,  1464,   787,  1324,  1112,  1324,  1317,  1116,
    1317,   601,   747,  1341,  1442,  1409,  1433,  1324,  1317,    -1,
    1317,  1412,   605,  1317,    -1,    -1,  1317,    -1,  1122,    -1,
      -1,  1317,  1379,  1317,  1381,    -1,  1317,    -1,    -1,  1433,
      -1,  1317,    -1,  1317,    -1,    -1,  1317,  1464,  1317,    -1,
      -1,  1317,    -1,  1317,  1317,    -1,  1317,    -1,  1317,  1317,
      -1,  1317,  1409,    -1,  1317,    -1,    -1,    -1,    -1,  1317,
    1464,  1317,  1317,    -1,  1317,    -1,    -1,  1317,    -1,  1317,
      -1,    -1,    -1,    -1,    -1,    -1,  1433,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1464,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   109,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,    -1,   121,    -1,
     123,   124,   125,    -1,   127,   128,   129,    -1,    -1,    -1,
      -1,   134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   199,   200,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,     0,     5,
       7,     9,   231,   232,   233,   234,   250,   251,   252,   257,
       7,   266,     7,   271,     7,   329,     7,   444,     7,   531,
       7,   548,     7,   480,     7,   486,     7,   510,     7,   420,
       7,   660,     7,   679,   258,   253,   267,   272,   330,   445,
     532,   549,   481,   487,   511,   421,   661,   680,   250,   259,
     260,   231,   255,   256,    10,   268,   270,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    96,
      97,   108,   109,   110,   115,   118,   119,   123,   124,   125,
     126,   127,   136,   146,   149,   156,   157,   161,   162,   180,
     184,   199,   200,   201,   202,   203,   204,   213,   231,   265,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   288,   289,   291,   292,   293,   294,
     295,   296,   297,   300,   302,   304,   305,   306,   309,   310,
     311,   312,   313,   315,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   343,   345,   353,   355,   398,   407,   414,
     428,   438,   466,   467,   468,   470,   478,   504,   538,   540,
     542,   553,   555,   557,   580,   595,   596,   598,   648,   658,
     677,   686,   710,    15,    16,    19,    22,    23,    24,    25,
     265,   327,   328,   331,   333,   336,   339,   340,   341,   342,
     538,   540,    93,    94,    95,   116,   120,   121,   122,   127,
     128,   129,   134,   144,   265,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   289,   292,   293,   294,   295,
     296,   297,   300,   302,   304,   305,   306,   309,   310,   311,
     312,   313,   315,   317,   323,   446,   447,   448,   450,   452,
     454,   456,   458,   460,   462,   464,   466,   467,   468,   469,
     504,   525,   538,   540,   542,   553,   555,   557,   575,   117,
     135,   265,   294,   295,   296,   297,   300,   302,   304,   306,
     309,   310,   311,   312,   313,   315,   458,   460,   462,   464,
     504,   533,   534,   535,   537,   538,   540,   127,   137,   138,
     139,   140,   141,   142,   143,   265,   504,   538,   540,   550,
     551,   552,   553,   555,   557,   559,   561,   563,   565,   567,
     569,   571,   573,   478,    40,    98,   100,   101,   105,   106,
     107,   265,   372,   488,   489,   490,   491,   492,   493,   494,
     496,   498,   500,   501,   503,   538,   540,    99,   102,   103,
     104,   127,   265,   372,   492,   498,   512,   513,   514,   515,
     516,   518,   519,   520,   521,   522,   523,   538,   540,   147,
     148,   265,   422,   423,   424,   426,   185,   186,   187,   188,
     189,   190,   191,   192,   265,   538,   540,   662,   663,   664,
     665,   667,   668,   670,   671,   672,   675,    12,    13,   681,
     682,   683,   685,     6,     3,     4,     8,     3,   269,     3,
       8,   678,   326,   346,     4,     4,     4,   554,   556,   558,
       4,     4,   344,   354,   356,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   287,     4,     4,     4,
       4,     4,   298,   301,   303,     4,     4,     4,     4,     4,
       4,     4,   439,   479,   505,     4,   290,   307,   471,   539,
     541,     4,     4,     4,   399,   581,   543,   415,   429,     4,
     408,   597,   599,   649,   659,   314,   316,     4,     4,     4,
     687,   711,     4,     3,     8,   332,   334,   337,     4,     4,
       4,     4,     3,     8,   451,   453,   455,   526,   449,   457,
       4,   461,   463,   465,   459,   576,     3,     8,   536,     4,
       3,     8,   574,   560,   562,   564,   568,   566,   572,   570,
       8,     3,     8,   495,   373,     4,   499,   497,   502,     4,
       8,     3,   517,     4,     4,     4,   524,     8,     3,   425,
     427,     3,     8,     4,   666,     4,   669,     4,     4,   673,
     676,     3,     8,   684,     4,     3,     8,   250,   250,   231,
       4,     4,     4,     4,   234,   234,   234,     4,     4,     4,
     232,   234,     4,     4,     4,   232,   232,   232,   232,   232,
     234,   233,   233,   233,   232,   232,     4,   232,   232,   234,
     234,   234,     4,     4,     4,   234,   234,   233,   232,   232,
     232,   234,     4,     4,     4,   232,     4,     4,     4,     4,
       4,   234,   234,   234,     4,     4,     4,     4,     4,   232,
       4,     4,     4,     4,     4,     4,     4,   234,   234,   234,
       4,     4,   274,     4,     4,     4,   234,   234,   232,   232,
     328,     4,     4,     4,     4,     4,     4,   232,     4,     4,
       4,     4,     4,   447,     4,   232,   534,     4,     4,     4,
       4,     4,     4,     4,     4,   552,     4,     4,   232,     4,
       4,     4,   234,   490,     4,   234,   234,   234,     4,   514,
       4,     4,   423,   234,     4,   232,     4,   232,   232,     4,
       4,   663,     4,   232,   682,     4,     7,     7,     7,     7,
     231,   231,   231,     7,     7,     5,   231,   195,   196,   197,
     198,   234,   299,   231,   231,     5,     5,     5,   231,   111,
     112,   113,   114,   308,     5,   252,   254,   231,     5,     5,
       5,     5,     7,     7,     7,     5,     7,     7,   231,   231,
       5,     7,     5,   261,    17,    18,   335,    20,    21,   338,
     231,   231,   231,     5,   231,   231,   261,   261,   261,   231,
       7,   231,   261,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   261,   231,   254,   231,
     231,    18,   193,   674,   194,     5,   250,   273,   681,   327,
      27,    28,   347,   348,   349,   351,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    58,    59,    60,    61,    62,    63,    64,   265,   361,
     362,   363,   365,   367,   369,   371,   372,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   386,   387,   388,
     390,   392,   394,   396,   361,     7,   357,   358,   359,     7,
     440,   441,   442,     7,   482,   483,   484,     7,   506,   507,
     508,     7,   472,   473,   474,   138,   139,   140,   141,   143,
     400,   401,   402,   403,   404,   405,   406,     7,   582,   583,
       7,   544,   545,   546,     7,   416,   417,   418,   150,   151,
     152,   153,   154,   155,   430,   431,   432,   433,   434,   435,
     436,   437,   158,   159,   160,   265,   409,   410,   411,   412,
     413,   538,   540,   163,   167,   168,   169,   170,   177,   178,
     265,   388,   390,   392,   538,   540,   604,   605,   606,   609,
     611,   613,   614,   615,   625,     7,   600,   601,   602,   181,
     182,   183,   231,   538,   540,   650,   651,   652,   653,   655,
     656,   662,     7,   688,   689,   214,   215,   216,   217,   265,
     712,   713,   714,   715,   716,   717,   262,     7,   527,   528,
     529,   145,   577,   578,   357,     8,     8,     8,   350,   352,
       3,     8,   364,   366,   368,   370,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   384,     4,     4,   389,
     391,   393,   395,   397,     3,     8,     8,   360,     6,     3,
     443,     6,     3,   485,     6,     3,   509,     6,     3,   475,
       6,     3,     3,     6,   584,     3,     6,   547,     6,     3,
     419,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   607,   610,   612,     4,
     626,     4,   616,     3,     8,   603,     6,     3,     4,   654,
       4,   657,     3,     8,     8,   690,     3,     6,     4,     4,
       4,     4,     3,     8,   231,   263,   264,   530,     6,     3,
     579,     8,     6,     4,     4,   348,     4,     4,     4,     4,
     232,   234,   232,   234,   232,   232,   232,   232,   232,   232,
       4,   234,   232,     4,     4,     4,     4,     4,   362,   361,
     359,   446,   442,   488,   484,   512,   508,   265,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   289,   292,
     293,   294,   295,   296,   297,   300,   302,   304,   305,   306,
     309,   310,   311,   312,   313,   315,   317,   323,   372,   438,
     456,   458,   460,   462,   464,   466,   467,   468,   476,   477,
     504,   538,   540,   553,   555,   557,   575,   474,   401,   130,
     131,   132,   133,   265,   275,   276,   277,   323,   372,   478,
     504,   538,   540,   553,   555,   557,   585,   586,   587,   588,
     589,   591,   593,   594,   583,   550,   546,   422,   418,   232,
     232,   232,   232,   232,   232,   431,   234,   232,   232,   410,
       4,     4,     4,   232,     4,   234,     4,   605,   604,   602,
     234,     4,   232,     4,   651,   205,   207,   208,   265,   372,
     538,   540,   691,   692,   693,   694,   696,   689,   234,   234,
     234,   234,   713,     6,     3,   533,   529,     4,   231,   231,
     231,   231,   231,   231,    55,    56,    57,   385,   231,   231,
     231,   231,   231,     8,     8,     8,     8,     3,     8,   590,
     592,     4,     4,     8,     3,     8,     8,   164,   165,   166,
     608,   231,   231,     7,     5,     8,   231,   250,   697,     4,
     695,     3,     8,   231,     8,   261,   477,     4,     4,   234,
     234,   587,    40,   172,   173,   174,   265,   538,   540,   627,
     628,   629,   632,   634,   636,     7,   617,   618,   619,     4,
     232,     4,   692,   231,   231,   630,   633,   635,   637,     3,
       8,   620,     6,     3,     5,   231,     4,     4,     4,     4,
     628,   179,   265,   372,   538,   540,   621,   622,   623,   619,
       7,   698,   699,   171,   631,   231,   231,     5,   624,     3,
       8,   700,     3,     6,     7,   638,   639,   640,     4,   622,
     206,   209,   210,   211,   212,   701,   702,   703,   705,   706,
     707,   708,   699,   641,     6,     3,   231,   704,     4,     4,
       4,   709,     3,     8,   175,   176,   265,   365,   367,   538,
     540,   642,   643,   644,   646,   640,     4,   234,   232,   232,
       4,   702,   645,   647,     3,     8,   231,   231,     4,     4,
     643,   231,   231
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   235,   237,   236,   238,   236,   239,   236,   240,   236,
     241,   236,   242,   236,   243,   236,   244,   236,   245,   236,
     246,   236,   247,   236,   248,   236,   249,   236,   250,   250,
     250,   250,   250,   250,   250,   251,   253,   252,   254,   255,
     255,   256,   256,   256,   258,   257,   259,   259,   260,   260,
     260,   262,   261,   263,   263,   264,   264,   264,   265,   267,
     266,   269,   268,   268,   270,   272,   271,   273,   273,   273,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   287,   286,   288,   290,   289,   291,   292,
     293,   294,   295,   296,   298,   297,   299,   299,   299,   299,
     299,   301,   300,   303,   302,   304,   305,   307,   306,   308,
     308,   308,   308,   309,   310,   311,   312,   314,   313,   316,
     315,   317,   318,   319,   320,   321,   322,   323,   324,   326,
     325,   327,   327,   327,   328,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   330,   329,   332,   331,   334,   333,
     335,   335,   337,   336,   338,   338,   339,   340,   341,   342,
     344,   343,   346,   345,   347,   347,   347,   348,   348,   350,
     349,   352,   351,   354,   353,   356,   355,   357,   357,   358,
     358,   358,   360,   359,   361,   361,   361,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   364,   363,   366,   365,   368,   367,   370,   369,   371,
     373,   372,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   384,   383,   385,   385,   385,   386,   387,   389,   388,
     391,   390,   393,   392,   395,   394,   397,   396,   399,   398,
     400,   400,   400,   401,   401,   401,   401,   401,   402,   403,
     404,   405,   406,   408,   407,   409,   409,   409,   410,   410,
     410,   410,   410,   410,   411,   412,   413,   415,   414,   416,
     416,   417,   417,   417,   419,   418,   421,   420,   422,   422,
     422,   422,   423,   423,   425,   424,   427,   426,   429,   428,
     430,   430,   430,   431,   431,   431,   431,   431,   431,   432,
     433,   434,   435,   436,   437,   439,   438,   440,   440,   441,
     441,   441,   443,   442,   445,   444,   446,   446,   446,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   449,   448,   451,   450,   453,   452,   455,   454,
     457,   456,   459,   458,   461,   460,   463,   462,   465,   464,
     466,   467,   468,   469,   471,   470,   472,   472,   473,   473,
     473,   475,   474,   476,   476,   476,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   479,   478,   481,   480,   482,   482,
     483,   483,   483,   485,   484,   487,   486,   488,   488,   489,
     489,   489,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   491,   492,   493,   495,   494,   497,   496,   499,
     498,   500,   502,   501,   503,   505,   504,   506,   506,   507,
     507,   507,   509,   508,   511,   510,   512,   512,   513,   513,
     513,   514,   514,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   515,   517,   516,   518,   519,   520,   521,   522,
     524,   523,   526,   525,   527,   527,   528,   528,   528,   530,
     529,   532,   531,   533,   533,   533,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     536,   535,   537,   539,   538,   541,   540,   543,   542,   544,
     544,   545,   545,   545,   547,   546,   549,   548,   550,   550,
     551,   551,   551,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   552,   554,   553,
     556,   555,   558,   557,   560,   559,   562,   561,   564,   563,
     566,   565,   568,   567,   570,   569,   572,   571,   574,   573,
     576,   575,   577,   579,   578,   581,   580,   582,   582,   582,
     584,   583,   585,   585,   586,   586,   586,   587,   587,   587,
     587,   587,   587,   587,   587,   587,   587,   587,   587,   587,
     587,   587,   587,   587,   588,   590,   589,   592,   591,   593,
     594,   595,   597,   596,   599,   598,   600,   600,   601,   601,
     601,   603,   602,   604,   604,   604,   605,   605,   605,   605,
     605,   605,   605,   605,   605,   605,   605,   605,   605,   607,
     606,   608,   608,   608,   610,   609,   612,   611,   613,   614,
     616,   615,   617,   617,   618,   618,   618,   620,   619,   621,
     621,   621,   622,   622,   622,   622,   622,   624,   623,   626,
     625,   627,   627,   627,   628,   628,   628,   628,   628,   628,
     628,   630,   629,   631,   633,   632,   635,   634,   637,   636,
     638,   638,   639,   639,   639,   641,   640,   642,   642,   642,
     643,   643,   643,   643,   643,   643,   643,   645,   644,   647,
     646,   649,   648,   650,   650,   650,   651,   651,   651,   651,
     651,   651,   652,   654,   653,   655,   657,   656,   659,   658,
     661,   660,   662,   662,   662,   663,   663,   663,   663,   663,
     663,   663,   663,   663,   663,   663,   664,   666,   665,   667,
     669,   668,   670,   671,   673,   672,   674,   674,   676,   675,
     678,   677,   680,   679,   681,   681,   681,   682,   682,   684,
     683,   685,   687,   686,   688,   688,   688,   690,   689,   691,
     691,   691,   692,   692,   692,   692,   692,   692,   692,   693,
     695,   694,   697,   696,   698,   698,   698,   700,   699,   701,
     701,   701,   702,   702,   702,   702,   702,   704,   703,   705,
     706,   707,   709,   708,   711,   710,   712,   712,   712,   713,
     713,   713,   713,   713,   714,   715,   716,   717
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
       1,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
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
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     3,     0,     6,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     3
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
  "\"cert-file\"", "\"key-file\"", "\"key-password\"", "\"cipher-list\"",
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
  "$@46", "cert_file", "$@47", "key_file", "$@48", "key_password", "$@49",
  "cipher_list", "$@50", "host_reservation_identifiers", "$@51",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@52", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@53", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@54",
  "sub_hooks_library", "$@55", "hooks_params", "hooks_param", "library",
  "$@56", "parameters", "$@57", "expired_leases_processing", "$@58",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@59",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@60",
  "sub_subnet4", "$@61", "subnet4_params", "subnet4_param", "subnet",
  "$@62", "subnet_4o6_interface", "$@63", "subnet_4o6_interface_id",
  "$@64", "subnet_4o6_subnet", "$@65", "interface", "$@66", "client_class",
  "$@67", "network_client_classes", "$@68", "require_client_classes",
  "$@69", "evaluate_additional_classes", "$@70", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "shared_networks", "$@71", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@72",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@73", "sub_option_def_list", "$@74", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@75",
  "sub_option_def", "$@76", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@77",
  "option_def_record_types", "$@78", "space", "$@79", "option_def_space",
  "option_def_encapsulate", "$@80", "option_def_array", "option_data_list",
  "$@81", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@82", "sub_option_data", "$@83",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@84",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@85", "pools_list", "$@86",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@87",
  "sub_pool4", "$@88", "pool_params", "pool_param", "pool_entry", "$@89",
  "pool_id", "user_context", "$@90", "comment", "$@91", "reservations",
  "$@92", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@93", "sub_reservation", "$@94", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@95", "server_hostname", "$@96", "boot_file_name", "$@97",
  "ip_address", "$@98", "duid", "$@99", "hw_address", "$@100",
  "client_id_value", "$@101", "circuit_id_value", "$@102", "flex_id_value",
  "$@103", "hostname", "$@104", "reservation_client_classes", "$@105",
  "relay", "$@106", "relay_map", "ip_addresses", "$@107", "client_classes",
  "$@108", "client_classes_list", "client_class_entry", "$@109",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@110",
  "client_class_template_test", "$@111", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_socket", "$@112",
  "control_sockets", "$@113", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@114",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@115", "control_socket_type_value", "control_socket_name", "$@116",
  "control_socket_address", "$@117", "control_socket_port",
  "cert_required", "http_headers", "$@118", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@119",
  "http_header_params", "http_header_param", "header_value", "$@120",
  "authentication", "$@121", "auth_params", "auth_param", "auth_type",
  "$@122", "auth_type_value", "realm", "$@123", "directory", "$@124",
  "clients", "$@125", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@126", "clients_params", "clients_param", "user_file",
  "$@127", "password_file", "$@128", "dhcp_queue_control", "$@129",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@130", "capacity", "arbitrary_map_entry", "$@131",
  "dhcp_ddns", "$@132", "sub_dhcp_ddns", "$@133", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@134", "server_port",
  "sender_ip", "$@135", "sender_port", "max_queue_size", "ncr_protocol",
  "$@136", "ncr_protocol_value", "ncr_format", "$@137", "config_control",
  "$@138", "sub_config_control", "$@139", "config_control_params",
  "config_control_param", "config_databases", "$@140",
  "config_fetch_wait_time", "loggers", "$@141", "loggers_entries",
  "logger_entry", "$@142", "logger_params", "logger_param", "debuglevel",
  "severity", "$@143", "output_options_list", "$@144",
  "output_options_list_content", "output_entry", "$@145",
  "output_params_list", "output_params", "output", "$@146", "flush",
  "maxsize", "maxver", "pattern", "$@147", "compatibility", "$@148",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   330,   330,   330,   331,   331,   332,   332,   333,   333,
     334,   334,   335,   335,   336,   336,   337,   337,   338,   338,
     339,   339,   340,   340,   341,   341,   342,   342,   350,   351,
     352,   353,   354,   355,   356,   359,   364,   364,   375,   378,
     379,   382,   387,   393,   398,   398,   405,   406,   409,   413,
     417,   423,   423,   430,   431,   434,   438,   442,   452,   461,
     461,   476,   476,   490,   493,   499,   499,   508,   509,   510,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   591,   597,   603,   609,   615,   621,   627,   633,
     639,   645,   651,   657,   657,   666,   672,   672,   681,   687,
     693,   699,   705,   711,   717,   717,   726,   729,   732,   735,
     738,   744,   744,   753,   753,   762,   771,   781,   781,   790,
     793,   796,   799,   804,   810,   816,   822,   828,   828,   837,
     837,   846,   852,   858,   864,   870,   876,   882,   888,   894,
     894,   906,   907,   908,   913,   914,   915,   916,   917,   918,
     919,   920,   921,   922,   925,   925,   934,   934,   945,   945,
     953,   954,   957,   957,   965,   967,   971,   977,   983,   989,
     995,   995,  1008,  1008,  1019,  1020,  1021,  1026,  1027,  1030,
    1030,  1049,  1049,  1067,  1067,  1080,  1080,  1091,  1092,  1095,
    1096,  1097,  1102,  1102,  1112,  1113,  1114,  1119,  1120,  1121,
    1122,  1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,
    1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,
    1142,  1145,  1145,  1154,  1154,  1163,  1163,  1172,  1172,  1181,
    1187,  1187,  1196,  1202,  1208,  1214,  1220,  1226,  1232,  1238,
    1244,  1250,  1250,  1258,  1259,  1260,  1263,  1269,  1275,  1275,
    1284,  1284,  1293,  1293,  1302,  1302,  1311,  1311,  1320,  1320,
    1331,  1332,  1333,  1338,  1339,  1340,  1341,  1342,  1345,  1350,
    1355,  1360,  1365,  1372,  1372,  1385,  1386,  1387,  1392,  1393,
    1394,  1395,  1396,  1397,  1400,  1406,  1412,  1418,  1418,  1429,
    1430,  1433,  1434,  1435,  1440,  1440,  1450,  1450,  1460,  1461,
    1462,  1465,  1468,  1469,  1472,  1472,  1481,  1481,  1490,  1490,
    1502,  1503,  1504,  1509,  1510,  1511,  1512,  1513,  1514,  1517,
    1523,  1529,  1535,  1541,  1547,  1556,  1556,  1570,  1571,  1574,
    1575,  1576,  1585,  1585,  1611,  1611,  1622,  1623,  1624,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,
    1641,  1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,
    1651,  1652,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,
    1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,
    1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,
    1681,  1682,  1685,  1685,  1694,  1694,  1703,  1703,  1712,  1712,
    1721,  1721,  1730,  1730,  1740,  1740,  1752,  1752,  1763,  1763,
    1774,  1780,  1786,  1792,  1800,  1800,  1812,  1813,  1817,  1818,
    1819,  1824,  1824,  1832,  1833,  1834,  1839,  1840,  1841,  1842,
    1843,  1844,  1845,  1846,  1847,  1848,  1849,  1850,  1851,  1852,
    1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,
    1863,  1864,  1865,  1866,  1867,  1868,  1869,  1870,  1871,  1872,
    1873,  1874,  1875,  1876,  1877,  1878,  1879,  1880,  1881,  1882,
    1883,  1884,  1885,  1886,  1893,  1893,  1907,  1907,  1916,  1917,
    1920,  1921,  1922,  1929,  1929,  1944,  1944,  1958,  1959,  1962,
    1963,  1964,  1969,  1970,  1971,  1972,  1973,  1974,  1975,  1976,
    1977,  1978,  1981,  1983,  1989,  1991,  1991,  2000,  2000,  2009,
    2009,  2018,  2020,  2020,  2029,  2039,  2039,  2052,  2053,  2058,
    2059,  2060,  2067,  2067,  2079,  2079,  2091,  2092,  2097,  2098,
    2099,  2106,  2107,  2108,  2109,  2110,  2111,  2112,  2113,  2114,
    2115,  2116,  2119,  2121,  2121,  2130,  2132,  2134,  2140,  2146,
    2152,  2152,  2166,  2166,  2179,  2180,  2183,  2184,  2185,  2190,
    2190,  2200,  2200,  2210,  2211,  2212,  2217,  2218,  2219,  2220,
    2221,  2222,  2223,  2224,  2225,  2226,  2227,  2228,  2229,  2230,
    2231,  2232,  2233,  2234,  2235,  2236,  2237,  2238,  2239,  2240,
    2243,  2243,  2252,  2258,  2258,  2283,  2283,  2313,  2313,  2324,
    2325,  2328,  2329,  2330,  2335,  2335,  2344,  2344,  2353,  2354,
    2357,  2358,  2359,  2365,  2366,  2367,  2368,  2369,  2370,  2371,
    2372,  2373,  2374,  2375,  2376,  2377,  2378,  2379,  2382,  2382,
    2391,  2391,  2400,  2400,  2409,  2409,  2418,  2418,  2427,  2427,
    2436,  2436,  2445,  2445,  2454,  2454,  2463,  2463,  2472,  2472,
    2486,  2486,  2497,  2500,  2500,  2514,  2514,  2525,  2526,  2527,
    2532,  2532,  2542,  2543,  2546,  2547,  2548,  2553,  2554,  2555,
    2556,  2557,  2558,  2559,  2560,  2561,  2562,  2563,  2564,  2565,
    2566,  2567,  2568,  2569,  2572,  2574,  2574,  2583,  2583,  2593,
    2599,  2607,  2615,  2615,  2627,  2627,  2639,  2640,  2643,  2644,
    2645,  2650,  2650,  2658,  2659,  2660,  2665,  2666,  2667,  2668,
    2669,  2670,  2671,  2672,  2673,  2674,  2675,  2676,  2677,  2680,
    2680,  2689,  2690,  2691,  2694,  2694,  2704,  2704,  2714,  2720,
    2726,  2726,  2737,  2738,  2741,  2742,  2743,  2748,  2748,  2756,
    2757,  2758,  2763,  2764,  2765,  2766,  2767,  2770,  2770,  2781,
    2781,  2794,  2795,  2796,  2801,  2802,  2803,  2804,  2805,  2806,
    2807,  2810,  2810,  2818,  2821,  2821,  2830,  2830,  2839,  2839,
    2850,  2851,  2854,  2855,  2856,  2861,  2861,  2869,  2870,  2871,
    2876,  2877,  2878,  2879,  2880,  2881,  2882,  2885,  2885,  2894,
    2894,  2905,  2905,  2918,  2919,  2920,  2925,  2926,  2927,  2928,
    2929,  2930,  2933,  2939,  2939,  2948,  2954,  2954,  2964,  2964,
    2977,  2977,  2987,  2988,  2989,  2994,  2995,  2996,  2997,  2998,
    2999,  3000,  3001,  3002,  3003,  3004,  3007,  3013,  3013,  3022,
    3028,  3028,  3037,  3043,  3049,  3049,  3058,  3059,  3062,  3062,
    3073,  3073,  3085,  3085,  3095,  3096,  3097,  3103,  3104,  3107,
    3107,  3118,  3126,  3126,  3139,  3140,  3141,  3147,  3147,  3155,
    3156,  3157,  3162,  3163,  3164,  3165,  3166,  3167,  3168,  3171,
    3177,  3177,  3186,  3186,  3197,  3198,  3199,  3204,  3204,  3212,
    3213,  3214,  3219,  3220,  3221,  3222,  3223,  3226,  3226,  3235,
    3241,  3247,  3253,  3253,  3262,  3262,  3273,  3274,  3275,  3280,
    3281,  3282,  3283,  3284,  3287,  3293,  3299,  3305
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
#line 6935 "dhcp4_parser.cc"

#line 3311 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
