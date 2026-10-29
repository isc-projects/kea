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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 421 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 427 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 433 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 439 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 481 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 487 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 493 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 499 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 325 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 505 "dhcp4_parser.cc"
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
#line 334 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 788 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 335 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 794 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 336 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 800 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 337 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 806 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 338 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 812 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 339 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 818 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 340 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 824 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 341 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 830 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 342 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 836 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 343 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 842 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 344 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 848 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 345 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 854 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 346 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 860 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 354 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 355 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 356 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 357 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 358 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 890 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 359 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 360 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 902 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 363 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 911 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 368 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 373 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 932 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 379 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 938 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 386 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 391 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 959 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 397 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 967 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 402 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 976 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 405 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 984 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 413 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 993 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 417 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1002 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 421 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1010 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 427 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1018 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 429 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1027 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 438 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1036 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 442 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1045 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 446 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1053 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 456 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 465 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 470 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1088 "dhcp4_parser.cc"
    break;

  case 61: // $@18: %empty
#line 480 "dhcp4_parser.yy"
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
#line 1103 "dhcp4_parser.cc"
    break;

  case 62: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 489 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 497 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 503 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 507 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 514 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1148 "dhcp4_parser.cc"
    break;

  case 143: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 596 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1158 "dhcp4_parser.cc"
    break;

  case 144: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 602 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 145: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 608 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1178 "dhcp4_parser.cc"
    break;

  case 146: // renew_timer: "renew-timer" ":" "integer"
#line 614 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 147: // rebind_timer: "rebind-timer" ":" "integer"
#line 620 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 148: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 626 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 149: // t1_percent: "t1-percent" ":" "floating point"
#line 632 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1218 "dhcp4_parser.cc"
    break;

  case 150: // t2_percent: "t2-percent" ":" "floating point"
#line 638 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1228 "dhcp4_parser.cc"
    break;

  case 151: // cache_threshold: "cache-threshold" ":" "floating point"
#line 644 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 152: // cache_max_age: "cache-max-age" ":" "integer"
#line 650 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 153: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 656 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 154: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 662 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 155: // $@20: %empty
#line 668 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 156: // server_tag: "server-tag" $@20 ":" "constant string"
#line 671 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 157: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 677 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 158: // $@21: %empty
#line 683 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 159: // allocator: "allocator" $@21 ":" "constant string"
#line 686 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 160: // echo_client_id: "echo-client-id" ":" "boolean"
#line 692 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 161: // match_client_id: "match-client-id" ":" "boolean"
#line 698 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 162: // authoritative: "authoritative" ":" "boolean"
#line 704 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 163: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 710 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 164: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 716 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 165: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 722 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 166: // $@22: %empty
#line 728 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 731 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-present"
#line 737 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1402 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "never"
#line 740 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1410 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "always"
#line 743 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1418 "dhcp4_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "when-not-present"
#line 746 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1426 "dhcp4_parser.cc"
    break;

  case 172: // ddns_replace_client_name_value: "boolean"
#line 749 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1435 "dhcp4_parser.cc"
    break;

  case 173: // $@23: %empty
#line 755 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 174: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 758 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc"
    break;

  case 175: // $@24: %empty
#line 764 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 176: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 767 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 177: // $@25: %empty
#line 773 "dhcp4_parser.yy"
                                     {
    ctx.unique("ddns-reverse-zone", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc"
    break;

  case 178: // ddns_reverse_zone: "ddns-reverse-zone" $@25 ":" "constant string"
#line 776 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-reverse-zone", s);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc"
    break;

  case 179: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 782 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1502 "dhcp4_parser.cc"
    break;

  case 180: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 791 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1516 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 801 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@26 ":" ddns_conflict_resolution_mode_value
#line 804 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 810 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1542 "dhcp4_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 813 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1550 "dhcp4_parser.cc"
    break;

  case 185: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 816 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1558 "dhcp4_parser.cc"
    break;

  case 186: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 819 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1566 "dhcp4_parser.cc"
    break;

  case 187: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 824 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 188: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 830 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 189: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 836 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 190: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 842 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 191: // $@27: %empty
#line 848 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 192: // hostname_char_set: "hostname-char-set" $@27 ":" "constant string"
#line 851 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 857 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 194: // hostname_char_replacement: "hostname-char-replacement" $@28 ":" "constant string"
#line 860 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 195: // store_extended_info: "store-extended-info" ":" "boolean"
#line 866 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 196: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 872 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 197: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 878 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1674 "dhcp4_parser.cc"
    break;

  case 198: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 884 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 199: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 890 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 200: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 896 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1704 "dhcp4_parser.cc"
    break;

  case 201: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 902 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 202: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 908 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 203: // $@29: %empty
#line 914 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1736 "dhcp4_parser.cc"
    break;

  case 204: // interfaces_config: "interfaces-config" $@29 ":" "{" interfaces_config_params "}"
#line 920 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc"
    break;

  case 207: // interfaces_config_params: interfaces_config_params ","
#line 928 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1754 "dhcp4_parser.cc"
    break;

  case 218: // $@30: %empty
#line 945 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1764 "dhcp4_parser.cc"
    break;

  case 219: // sub_interfaces4: "{" $@30 interfaces_config_params "}"
#line 949 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 220: // $@31: %empty
#line 954 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "dhcp4_parser.cc"
    break;

  case 221: // interfaces_list: "interfaces" $@31 ":" list_strings
#line 960 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc"
    break;

  case 222: // $@32: %empty
#line 965 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1803 "dhcp4_parser.cc"
    break;

  case 223: // dhcp_socket_type: "dhcp-socket-type" $@32 ":" socket_type
#line 968 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 224: // socket_type: "raw"
#line 973 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1818 "dhcp4_parser.cc"
    break;

  case 225: // socket_type: "udp"
#line 974 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1824 "dhcp4_parser.cc"
    break;

  case 226: // $@33: %empty
#line 977 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1833 "dhcp4_parser.cc"
    break;

  case 227: // outbound_interface: "outbound-interface" $@33 ":" outbound_interface_value
#line 980 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc"
    break;

  case 228: // outbound_interface_value: "same-as-inbound"
#line 985 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1850 "dhcp4_parser.cc"
    break;

  case 229: // outbound_interface_value: "use-routing"
#line 987 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1858 "dhcp4_parser.cc"
    break;

  case 230: // re_detect: "re-detect" ":" "boolean"
#line 991 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1868 "dhcp4_parser.cc"
    break;

  case 231: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 997 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 232: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 1003 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 233: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1009 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1898 "dhcp4_parser.cc"
    break;

  case 234: // $@34: %empty
#line 1015 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1910 "dhcp4_parser.cc"
    break;

  case 235: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 1021 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp4_parser.cc"
    break;

  case 236: // $@35: %empty
#line 1028 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1933 "dhcp4_parser.cc"
    break;

  case 237: // sanity_checks: "sanity-checks" $@35 ":" "{" sanity_checks_params "}"
#line 1034 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1942 "dhcp4_parser.cc"
    break;

  case 240: // sanity_checks_params: sanity_checks_params ","
#line 1041 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1950 "dhcp4_parser.cc"
    break;

  case 243: // $@36: %empty
#line 1050 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc"
    break;

  case 244: // lease_checks: "lease-checks" $@36 ":" "constant string"
#line 1053 "dhcp4_parser.yy"
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
#line 1979 "dhcp4_parser.cc"
    break;

  case 245: // $@37: %empty
#line 1069 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 246: // extended_info_checks: "extended-info-checks" $@37 ":" "constant string"
#line 1072 "dhcp4_parser.yy"
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
#line 2007 "dhcp4_parser.cc"
    break;

  case 247: // $@38: %empty
#line 1087 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2019 "dhcp4_parser.cc"
    break;

  case 248: // hosts_database: "hosts-database" $@38 ":" "{" database_map_params "}"
#line 1093 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 249: // $@39: %empty
#line 1100 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2042 "dhcp4_parser.cc"
    break;

  case 250: // hosts_databases: "hosts-databases" $@39 ":" "[" database_list "]"
#line 1106 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2051 "dhcp4_parser.cc"
    break;

  case 255: // not_empty_database_list: not_empty_database_list ","
#line 1117 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2059 "dhcp4_parser.cc"
    break;

  case 256: // $@40: %empty
#line 1122 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 257: // database: "{" $@40 database_map_params "}"
#line 1126 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 260: // database_map_params: database_map_params ","
#line 1134 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2087 "dhcp4_parser.cc"
    break;

  case 286: // $@41: %empty
#line 1166 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 287: // database_type: "type" $@41 ":" "constant string"
#line 1169 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 288: // $@42: %empty
#line 1175 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 289: // user: "user" $@42 ":" "constant string"
#line 1178 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 290: // $@43: %empty
#line 1184 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 291: // password: "password" $@43 ":" "constant string"
#line 1187 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 292: // $@44: %empty
#line 1193 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2153 "dhcp4_parser.cc"
    break;

  case 293: // password_file: "password-file" $@44 ":" "constant string"
#line 1196 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1202 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 295: // host: "host" $@45 ":" "constant string"
#line 1205 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 296: // port: "port" ":" "integer"
#line 1211 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 297: // $@46: %empty
#line 1217 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 298: // name: "name" $@46 ":" "constant string"
#line 1220 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2211 "dhcp4_parser.cc"
    break;

  case 299: // persist: "persist" ":" "boolean"
#line 1226 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 300: // lfc_interval: "lfc-interval" ":" "integer"
#line 1232 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2231 "dhcp4_parser.cc"
    break;

  case 301: // readonly: "readonly" ":" "boolean"
#line 1238 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2241 "dhcp4_parser.cc"
    break;

  case 302: // connect_timeout: "connect-timeout" ":" "integer"
#line 1244 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 303: // read_timeout: "read-timeout" ":" "integer"
#line 1250 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 304: // write_timeout: "write-timeout" ":" "integer"
#line 1256 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 305: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1262 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 306: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1268 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 307: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1274 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 308: // $@47: %empty
#line 1280 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 309: // on_fail: "on-fail" $@47 ":" on_fail_mode
#line 1283 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2319 "dhcp4_parser.cc"
    break;

  case 310: // on_fail_mode: "stop-retry-exit"
#line 1288 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2325 "dhcp4_parser.cc"
    break;

  case 311: // on_fail_mode: "serve-retry-exit"
#line 1289 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2331 "dhcp4_parser.cc"
    break;

  case 312: // on_fail_mode: "serve-retry-continue"
#line 1290 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2337 "dhcp4_parser.cc"
    break;

  case 313: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1293 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 314: // max_row_errors: "max-row-errors" ":" "integer"
#line 1299 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 315: // $@48: %empty
#line 1305 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 316: // trust_anchor: "trust-anchor" $@48 ":" "constant string"
#line 1308 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 317: // $@49: %empty
#line 1314 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 318: // cert_file: "cert-file" $@49 ":" "constant string"
#line 1317 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 319: // $@50: %empty
#line 1323 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2404 "dhcp4_parser.cc"
    break;

  case 320: // key_file: "key-file" $@50 ":" "constant string"
#line 1326 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2414 "dhcp4_parser.cc"
    break;

  case 321: // $@51: %empty
#line 1332 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2423 "dhcp4_parser.cc"
    break;

  case 322: // ssl_mode: "ssl-mode" $@51 ":" ssl_mode
#line 1335 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2432 "dhcp4_parser.cc"
    break;

  case 323: // ssl_mode: "disable"
#line 1340 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2440 "dhcp4_parser.cc"
    break;

  case 324: // ssl_mode: "prefer"
#line 1343 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2448 "dhcp4_parser.cc"
    break;

  case 325: // ssl_mode: "require"
#line 1346 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2456 "dhcp4_parser.cc"
    break;

  case 326: // ssl_mode: "verify-ca"
#line 1349 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2464 "dhcp4_parser.cc"
    break;

  case 327: // ssl_mode: "verify-full"
#line 1352 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2472 "dhcp4_parser.cc"
    break;

  case 328: // $@52: %empty
#line 1357 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2481 "dhcp4_parser.cc"
    break;

  case 329: // cipher_list: "cipher-list" $@52 ":" "constant string"
#line 1360 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 330: // $@53: %empty
#line 1366 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2503 "dhcp4_parser.cc"
    break;

  case 331: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1372 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2512 "dhcp4_parser.cc"
    break;

  case 334: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1379 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2520 "dhcp4_parser.cc"
    break;

  case 340: // duid_id: "duid"
#line 1391 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2529 "dhcp4_parser.cc"
    break;

  case 341: // hw_address_id: "hw-address"
#line 1396 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 342: // circuit_id: "circuit-id"
#line 1401 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2547 "dhcp4_parser.cc"
    break;

  case 343: // client_id: "client-id"
#line 1406 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2556 "dhcp4_parser.cc"
    break;

  case 344: // flex_id: "flex-id"
#line 1411 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 345: // $@54: %empty
#line 1418 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2577 "dhcp4_parser.cc"
    break;

  case 346: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1424 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 349: // multi_threading_params: multi_threading_params ","
#line 1433 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2596 "dhcp4_parser.cc"
    break;

  case 356: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1446 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2606 "dhcp4_parser.cc"
    break;

  case 357: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1452 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 358: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1458 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 359: // $@55: %empty
#line 1464 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2638 "dhcp4_parser.cc"
    break;

  case 360: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1470 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 365: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1481 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2655 "dhcp4_parser.cc"
    break;

  case 366: // $@56: %empty
#line 1486 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 367: // hooks_library: "{" $@56 hooks_params "}"
#line 1490 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 368: // $@57: %empty
#line 1496 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 369: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1500 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 372: // hooks_params: hooks_params ","
#line 1508 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2703 "dhcp4_parser.cc"
    break;

  case 376: // $@58: %empty
#line 1518 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 377: // library: "library" $@58 ":" "constant string"
#line 1521 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 378: // $@59: %empty
#line 1527 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 379: // parameters: "parameters" $@59 ":" map_value
#line 1530 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 380: // $@60: %empty
#line 1536 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 381: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1542 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 384: // expired_leases_params: expired_leases_params ","
#line 1550 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2770 "dhcp4_parser.cc"
    break;

  case 391: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1563 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 392: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1569 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2790 "dhcp4_parser.cc"
    break;

  case 393: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1575 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2800 "dhcp4_parser.cc"
    break;

  case 394: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1581 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 395: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1587 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 396: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1593 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 397: // $@61: %empty
#line 1602 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 398: // subnet4_list: "subnet4" $@61 ":" "[" subnet4_list_content "]"
#line 1608 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 403: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1622 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2859 "dhcp4_parser.cc"
    break;

  case 404: // $@62: %empty
#line 1631 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 405: // subnet4: "{" $@62 subnet4_params "}"
#line 1635 "dhcp4_parser.yy"
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
#line 2895 "dhcp4_parser.cc"
    break;

  case 406: // $@63: %empty
#line 1657 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2905 "dhcp4_parser.cc"
    break;

  case 407: // sub_subnet4: "{" $@63 subnet4_params "}"
#line 1661 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2915 "dhcp4_parser.cc"
    break;

  case 410: // subnet4_params: subnet4_params ","
#line 1670 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2923 "dhcp4_parser.cc"
    break;

  case 464: // $@64: %empty
#line 1731 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 465: // subnet: "subnet" $@64 ":" "constant string"
#line 1734 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 466: // $@65: %empty
#line 1740 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 467: // subnet_4o6_interface: "4o6-interface" $@65 ":" "constant string"
#line 1743 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 468: // $@66: %empty
#line 1749 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 469: // subnet_4o6_interface_id: "4o6-interface-id" $@66 ":" "constant string"
#line 1752 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 470: // $@67: %empty
#line 1758 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 471: // subnet_4o6_subnet: "4o6-subnet" $@67 ":" "constant string"
#line 1761 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 472: // $@68: %empty
#line 1767 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 473: // interface: "interface" $@68 ":" "constant string"
#line 1770 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 474: // $@69: %empty
#line 1777 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3030 "dhcp4_parser.cc"
    break;

  case 475: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1783 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3039 "dhcp4_parser.cc"
    break;

  case 476: // $@70: %empty
#line 1788 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3051 "dhcp4_parser.cc"
    break;

  case 477: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1794 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3060 "dhcp4_parser.cc"
    break;

  case 478: // reservations_global: "reservations-global" ":" "boolean"
#line 1799 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 479: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1805 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 480: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1811 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 481: // id: "id" ":" "integer"
#line 1817 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3100 "dhcp4_parser.cc"
    break;

  case 482: // $@71: %empty
#line 1825 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 483: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1831 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 488: // shared_networks_list: shared_networks_list ","
#line 1844 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3129 "dhcp4_parser.cc"
    break;

  case 489: // $@72: %empty
#line 1849 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 490: // shared_network: "{" $@72 shared_network_params "}"
#line 1853 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3147 "dhcp4_parser.cc"
    break;

  case 493: // shared_network_params: shared_network_params ","
#line 1859 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3155 "dhcp4_parser.cc"
    break;

  case 542: // $@73: %empty
#line 1918 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 543: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1924 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 544: // $@74: %empty
#line 1932 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3185 "dhcp4_parser.cc"
    break;

  case 545: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1935 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3193 "dhcp4_parser.cc"
    break;

  case 550: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1947 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3201 "dhcp4_parser.cc"
    break;

  case 551: // $@75: %empty
#line 1954 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 552: // option_def_entry: "{" $@75 option_def_params "}"
#line 1958 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3223 "dhcp4_parser.cc"
    break;

  case 553: // $@76: %empty
#line 1969 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 554: // sub_option_def: "{" $@76 option_def_params "}"
#line 1973 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 559: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1989 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3253 "dhcp4_parser.cc"
    break;

  case 571: // code: "code" ":" "integer"
#line 2008 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 573: // $@77: %empty
#line 2016 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3272 "dhcp4_parser.cc"
    break;

  case 574: // option_def_type: "type" $@77 ":" "constant string"
#line 2019 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 575: // $@78: %empty
#line 2025 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp4_parser.cc"
    break;

  case 576: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 2028 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 577: // $@79: %empty
#line 2034 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3310 "dhcp4_parser.cc"
    break;

  case 578: // space: "space" $@79 ":" "constant string"
#line 2037 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 580: // $@80: %empty
#line 2045 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3329 "dhcp4_parser.cc"
    break;

  case 581: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2048 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3339 "dhcp4_parser.cc"
    break;

  case 582: // option_def_array: "array" ":" "boolean"
#line 2054 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3349 "dhcp4_parser.cc"
    break;

  case 583: // $@81: %empty
#line 2064 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3361 "dhcp4_parser.cc"
    break;

  case 584: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2070 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3370 "dhcp4_parser.cc"
    break;

  case 589: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2085 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3378 "dhcp4_parser.cc"
    break;

  case 590: // $@82: %empty
#line 2092 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3388 "dhcp4_parser.cc"
    break;

  case 591: // option_data_entry: "{" $@82 option_data_params "}"
#line 2096 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3397 "dhcp4_parser.cc"
    break;

  case 592: // $@83: %empty
#line 2104 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3407 "dhcp4_parser.cc"
    break;

  case 593: // sub_option_data: "{" $@83 option_data_params "}"
#line 2108 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3416 "dhcp4_parser.cc"
    break;

  case 598: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2124 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3424 "dhcp4_parser.cc"
    break;

  case 611: // $@84: %empty
#line 2146 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3433 "dhcp4_parser.cc"
    break;

  case 612: // option_data_data: "data" $@84 ":" "constant string"
#line 2149 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 615: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2159 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 616: // option_data_always_send: "always-send" ":" "boolean"
#line 2165 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 617: // option_data_never_send: "never-send" ":" "boolean"
#line 2171 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 618: // $@85: %empty
#line 2177 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 619: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2183 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 620: // $@86: %empty
#line 2191 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 621: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2197 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 626: // not_empty_pools_list: not_empty_pools_list ","
#line 2210 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3523 "dhcp4_parser.cc"
    break;

  case 627: // $@87: %empty
#line 2215 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3533 "dhcp4_parser.cc"
    break;

  case 628: // pool_list_entry: "{" $@87 pool_params "}"
#line 2219 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3543 "dhcp4_parser.cc"
    break;

  case 629: // $@88: %empty
#line 2225 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3553 "dhcp4_parser.cc"
    break;

  case 630: // sub_pool4: "{" $@88 pool_params "}"
#line 2229 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 633: // pool_params: pool_params ","
#line 2237 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3571 "dhcp4_parser.cc"
    break;

  case 657: // $@89: %empty
#line 2267 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3580 "dhcp4_parser.cc"
    break;

  case 658: // pool_entry: "pool" $@89 ":" "constant string"
#line 2270 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3590 "dhcp4_parser.cc"
    break;

  case 659: // pool_id: "pool-id" ":" "integer"
#line 2276 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3600 "dhcp4_parser.cc"
    break;

  case 660: // $@90: %empty
#line 2282 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3608 "dhcp4_parser.cc"
    break;

  case 661: // user_context: "user-context" $@90 ":" map_value
#line 2284 "dhcp4_parser.yy"
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
#line 3635 "dhcp4_parser.cc"
    break;

  case 662: // $@91: %empty
#line 2307 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 663: // comment: "comment" $@91 ":" "constant string"
#line 2309 "dhcp4_parser.yy"
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
#line 3672 "dhcp4_parser.cc"
    break;

  case 664: // $@92: %empty
#line 2337 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3684 "dhcp4_parser.cc"
    break;

  case 665: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2343 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 670: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2354 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3701 "dhcp4_parser.cc"
    break;

  case 671: // $@93: %empty
#line 2359 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3711 "dhcp4_parser.cc"
    break;

  case 672: // reservation: "{" $@93 reservation_params "}"
#line 2363 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3720 "dhcp4_parser.cc"
    break;

  case 673: // $@94: %empty
#line 2368 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3730 "dhcp4_parser.cc"
    break;

  case 674: // sub_reservation: "{" $@94 reservation_params "}"
#line 2372 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3739 "dhcp4_parser.cc"
    break;

  case 679: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2383 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3747 "dhcp4_parser.cc"
    break;

  case 695: // $@95: %empty
#line 2406 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp4_parser.cc"
    break;

  case 696: // next_server: "next-server" $@95 ":" "constant string"
#line 2409 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3766 "dhcp4_parser.cc"
    break;

  case 697: // $@96: %empty
#line 2415 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3775 "dhcp4_parser.cc"
    break;

  case 698: // server_hostname: "server-hostname" $@96 ":" "constant string"
#line 2418 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3785 "dhcp4_parser.cc"
    break;

  case 699: // $@97: %empty
#line 2424 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3794 "dhcp4_parser.cc"
    break;

  case 700: // boot_file_name: "boot-file-name" $@97 ":" "constant string"
#line 2427 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3804 "dhcp4_parser.cc"
    break;

  case 701: // $@98: %empty
#line 2433 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3813 "dhcp4_parser.cc"
    break;

  case 702: // ip_address: "ip-address" $@98 ":" "constant string"
#line 2436 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3823 "dhcp4_parser.cc"
    break;

  case 703: // $@99: %empty
#line 2442 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3832 "dhcp4_parser.cc"
    break;

  case 704: // duid: "duid" $@99 ":" "constant string"
#line 2445 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 705: // $@100: %empty
#line 2451 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3851 "dhcp4_parser.cc"
    break;

  case 706: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2454 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3861 "dhcp4_parser.cc"
    break;

  case 707: // $@101: %empty
#line 2460 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3870 "dhcp4_parser.cc"
    break;

  case 708: // client_id_value: "client-id" $@101 ":" "constant string"
#line 2463 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3880 "dhcp4_parser.cc"
    break;

  case 709: // $@102: %empty
#line 2469 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3889 "dhcp4_parser.cc"
    break;

  case 710: // circuit_id_value: "circuit-id" $@102 ":" "constant string"
#line 2472 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3899 "dhcp4_parser.cc"
    break;

  case 711: // $@103: %empty
#line 2478 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3908 "dhcp4_parser.cc"
    break;

  case 712: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2481 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 713: // $@104: %empty
#line 2487 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3927 "dhcp4_parser.cc"
    break;

  case 714: // hostname: "hostname" $@104 ":" "constant string"
#line 2490 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3937 "dhcp4_parser.cc"
    break;

  case 715: // $@105: %empty
#line 2496 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3949 "dhcp4_parser.cc"
    break;

  case 716: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2502 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 717: // $@106: %empty
#line 2510 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3970 "dhcp4_parser.cc"
    break;

  case 718: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2516 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3979 "dhcp4_parser.cc"
    break;

  case 720: // $@107: %empty
#line 2524 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3991 "dhcp4_parser.cc"
    break;

  case 721: // ip_addresses: "ip-addresses" $@107 ":" list_strings
#line 2530 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4000 "dhcp4_parser.cc"
    break;

  case 722: // $@108: %empty
#line 2538 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4012 "dhcp4_parser.cc"
    break;

  case 723: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2544 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 728: // not_empty_classes_list: not_empty_classes_list ","
#line 2555 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4029 "dhcp4_parser.cc"
    break;

  case 729: // $@109: %empty
#line 2560 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4039 "dhcp4_parser.cc"
    break;

  case 730: // client_class_entry: "{" $@109 client_class_params "}"
#line 2564 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4049 "dhcp4_parser.cc"
    break;

  case 735: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2576 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4057 "dhcp4_parser.cc"
    break;

  case 753: // $@110: %empty
#line 2601 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4066 "dhcp4_parser.cc"
    break;

  case 754: // client_class_test: "test" $@110 ":" "constant string"
#line 2604 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4076 "dhcp4_parser.cc"
    break;

  case 755: // $@111: %empty
#line 2610 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4085 "dhcp4_parser.cc"
    break;

  case 756: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2613 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4095 "dhcp4_parser.cc"
    break;

  case 757: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2619 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 758: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2627 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4115 "dhcp4_parser.cc"
    break;

  case 759: // $@112: %empty
#line 2635 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4127 "dhcp4_parser.cc"
    break;

  case 760: // control_sockets: "control-sockets" $@112 ":" "[" control_socket_list "]"
#line 2641 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4136 "dhcp4_parser.cc"
    break;

  case 765: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2652 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4144 "dhcp4_parser.cc"
    break;

  case 766: // $@113: %empty
#line 2657 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4154 "dhcp4_parser.cc"
    break;

  case 767: // control_socket_entry: "{" $@113 control_socket_params "}"
#line 2661 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4162 "dhcp4_parser.cc"
    break;

  case 770: // control_socket_params: control_socket_params ","
#line 2667 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4170 "dhcp4_parser.cc"
    break;

  case 784: // $@114: %empty
#line 2687 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4179 "dhcp4_parser.cc"
    break;

  case 785: // control_socket_type: "socket-type" $@114 ":" control_socket_type_value
#line 2690 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4188 "dhcp4_parser.cc"
    break;

  case 786: // control_socket_type_value: "unix"
#line 2696 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4194 "dhcp4_parser.cc"
    break;

  case 787: // control_socket_type_value: "http"
#line 2697 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4200 "dhcp4_parser.cc"
    break;

  case 788: // control_socket_type_value: "https"
#line 2698 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4206 "dhcp4_parser.cc"
    break;

  case 789: // $@115: %empty
#line 2701 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4215 "dhcp4_parser.cc"
    break;

  case 790: // control_socket_name: "socket-name" $@115 ":" "constant string"
#line 2704 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4225 "dhcp4_parser.cc"
    break;

  case 791: // $@116: %empty
#line 2710 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 792: // control_socket_address: "socket-address" $@116 ":" "constant string"
#line 2713 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4244 "dhcp4_parser.cc"
    break;

  case 793: // control_socket_port: "socket-port" ":" "integer"
#line 2719 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4254 "dhcp4_parser.cc"
    break;

  case 794: // cert_required: "cert-required" ":" "boolean"
#line 2725 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4264 "dhcp4_parser.cc"
    break;

  case 795: // $@117: %empty
#line 2731 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4276 "dhcp4_parser.cc"
    break;

  case 796: // http_headers: "http-headers" $@117 ":" "[" http_header_list "]"
#line 2737 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4285 "dhcp4_parser.cc"
    break;

  case 801: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2748 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4293 "dhcp4_parser.cc"
    break;

  case 802: // $@118: %empty
#line 2753 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 803: // http_header: "{" $@118 http_header_params "}"
#line 2757 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4311 "dhcp4_parser.cc"
    break;

  case 806: // http_header_params: http_header_params ","
#line 2763 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4319 "dhcp4_parser.cc"
    break;

  case 812: // $@119: %empty
#line 2775 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4328 "dhcp4_parser.cc"
    break;

  case 813: // header_value: "value" $@119 ":" "constant string"
#line 2778 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 814: // $@120: %empty
#line 2786 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4350 "dhcp4_parser.cc"
    break;

  case 815: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2792 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4361 "dhcp4_parser.cc"
    break;

  case 818: // auth_params: auth_params ","
#line 2801 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4369 "dhcp4_parser.cc"
    break;

  case 826: // $@121: %empty
#line 2815 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4378 "dhcp4_parser.cc"
    break;

  case 827: // auth_type: "type" $@121 ":" auth_type_value
#line 2818 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4387 "dhcp4_parser.cc"
    break;

  case 828: // auth_type_value: "basic"
#line 2823 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4393 "dhcp4_parser.cc"
    break;

  case 829: // $@122: %empty
#line 2826 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4402 "dhcp4_parser.cc"
    break;

  case 830: // realm: "realm" $@122 ":" "constant string"
#line 2829 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4412 "dhcp4_parser.cc"
    break;

  case 831: // $@123: %empty
#line 2835 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4421 "dhcp4_parser.cc"
    break;

  case 832: // directory: "directory" $@123 ":" "constant string"
#line 2838 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4431 "dhcp4_parser.cc"
    break;

  case 833: // $@124: %empty
#line 2844 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4443 "dhcp4_parser.cc"
    break;

  case 834: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2850 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4452 "dhcp4_parser.cc"
    break;

  case 839: // not_empty_clients_list: not_empty_clients_list ","
#line 2861 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4460 "dhcp4_parser.cc"
    break;

  case 840: // $@125: %empty
#line 2866 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4470 "dhcp4_parser.cc"
    break;

  case 841: // basic_auth: "{" $@125 clients_params "}"
#line 2870 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4478 "dhcp4_parser.cc"
    break;

  case 844: // clients_params: clients_params ","
#line 2876 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4486 "dhcp4_parser.cc"
    break;

  case 852: // $@126: %empty
#line 2890 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4495 "dhcp4_parser.cc"
    break;

  case 853: // user_file: "user-file" $@126 ":" "constant string"
#line 2893 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 854: // $@127: %empty
#line 2901 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4517 "dhcp4_parser.cc"
    break;

  case 855: // dhcp_queue_control: "dhcp-queue-control" $@127 ":" "{" queue_control_params "}"
#line 2907 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4528 "dhcp4_parser.cc"
    break;

  case 858: // queue_control_params: queue_control_params ","
#line 2916 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4536 "dhcp4_parser.cc"
    break;

  case 865: // enable_queue: "enable-queue" ":" "boolean"
#line 2929 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4546 "dhcp4_parser.cc"
    break;

  case 866: // $@128: %empty
#line 2935 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4555 "dhcp4_parser.cc"
    break;

  case 867: // queue_type: "queue-type" $@128 ":" "constant string"
#line 2938 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4565 "dhcp4_parser.cc"
    break;

  case 868: // capacity: "capacity" ":" "integer"
#line 2944 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4575 "dhcp4_parser.cc"
    break;

  case 869: // $@129: %empty
#line 2950 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4584 "dhcp4_parser.cc"
    break;

  case 870: // arbitrary_map_entry: "constant string" $@129 ":" value
#line 2953 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4593 "dhcp4_parser.cc"
    break;

  case 871: // $@130: %empty
#line 2960 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4605 "dhcp4_parser.cc"
    break;

  case 872: // dhcp_ddns: "dhcp-ddns" $@130 ":" "{" dhcp_ddns_params "}"
#line 2966 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4616 "dhcp4_parser.cc"
    break;

  case 873: // $@131: %empty
#line 2973 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4626 "dhcp4_parser.cc"
    break;

  case 874: // sub_dhcp_ddns: "{" $@131 dhcp_ddns_params "}"
#line 2977 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4636 "dhcp4_parser.cc"
    break;

  case 877: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2985 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4644 "dhcp4_parser.cc"
    break;

  case 889: // enable_updates: "enable-updates" ":" "boolean"
#line 3003 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4654 "dhcp4_parser.cc"
    break;

  case 890: // $@132: %empty
#line 3009 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4663 "dhcp4_parser.cc"
    break;

  case 891: // server_ip: "server-ip" $@132 ":" "constant string"
#line 3012 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4673 "dhcp4_parser.cc"
    break;

  case 892: // server_port: "server-port" ":" "integer"
#line 3018 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4683 "dhcp4_parser.cc"
    break;

  case 893: // $@133: %empty
#line 3024 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4692 "dhcp4_parser.cc"
    break;

  case 894: // sender_ip: "sender-ip" $@133 ":" "constant string"
#line 3027 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4702 "dhcp4_parser.cc"
    break;

  case 895: // sender_port: "sender-port" ":" "integer"
#line 3033 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4712 "dhcp4_parser.cc"
    break;

  case 896: // max_queue_size: "max-queue-size" ":" "integer"
#line 3039 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4722 "dhcp4_parser.cc"
    break;

  case 897: // $@134: %empty
#line 3045 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4731 "dhcp4_parser.cc"
    break;

  case 898: // ncr_protocol: "ncr-protocol" $@134 ":" ncr_protocol_value
#line 3048 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4740 "dhcp4_parser.cc"
    break;

  case 899: // ncr_protocol_value: "udp"
#line 3054 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4746 "dhcp4_parser.cc"
    break;

  case 900: // ncr_protocol_value: "tcp"
#line 3055 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4752 "dhcp4_parser.cc"
    break;

  case 901: // $@135: %empty
#line 3058 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4761 "dhcp4_parser.cc"
    break;

  case 902: // ncr_format: "ncr-format" $@135 ":" "JSON"
#line 3061 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4771 "dhcp4_parser.cc"
    break;

  case 903: // $@136: %empty
#line 3069 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4783 "dhcp4_parser.cc"
    break;

  case 904: // config_control: "config-control" $@136 ":" "{" config_control_params "}"
#line 3075 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4793 "dhcp4_parser.cc"
    break;

  case 905: // $@137: %empty
#line 3081 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4803 "dhcp4_parser.cc"
    break;

  case 906: // sub_config_control: "{" $@137 config_control_params "}"
#line 3085 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4812 "dhcp4_parser.cc"
    break;

  case 909: // config_control_params: config_control_params ","
#line 3093 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4820 "dhcp4_parser.cc"
    break;

  case 912: // $@138: %empty
#line 3103 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4832 "dhcp4_parser.cc"
    break;

  case 913: // config_databases: "config-databases" $@138 ":" "[" database_list "]"
#line 3109 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4841 "dhcp4_parser.cc"
    break;

  case 914: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3114 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4851 "dhcp4_parser.cc"
    break;

  case 915: // $@139: %empty
#line 3122 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4863 "dhcp4_parser.cc"
    break;

  case 916: // loggers: "loggers" $@139 ":" "[" loggers_entries "]"
#line 3128 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4872 "dhcp4_parser.cc"
    break;

  case 919: // loggers_entries: loggers_entries ","
#line 3137 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4880 "dhcp4_parser.cc"
    break;

  case 920: // $@140: %empty
#line 3143 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4890 "dhcp4_parser.cc"
    break;

  case 921: // logger_entry: "{" $@140 logger_params "}"
#line 3147 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4898 "dhcp4_parser.cc"
    break;

  case 924: // logger_params: logger_params ","
#line 3153 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4906 "dhcp4_parser.cc"
    break;

  case 932: // debuglevel: "debuglevel" ":" "integer"
#line 3167 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4916 "dhcp4_parser.cc"
    break;

  case 933: // $@141: %empty
#line 3173 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4925 "dhcp4_parser.cc"
    break;

  case 934: // severity: "severity" $@141 ":" "constant string"
#line 3176 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4935 "dhcp4_parser.cc"
    break;

  case 935: // $@142: %empty
#line 3182 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4947 "dhcp4_parser.cc"
    break;

  case 936: // output_options_list: "output-options" $@142 ":" "[" output_options_list_content "]"
#line 3188 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4956 "dhcp4_parser.cc"
    break;

  case 939: // output_options_list_content: output_options_list_content ","
#line 3195 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4964 "dhcp4_parser.cc"
    break;

  case 940: // $@143: %empty
#line 3200 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4974 "dhcp4_parser.cc"
    break;

  case 941: // output_entry: "{" $@143 output_params_list "}"
#line 3204 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4982 "dhcp4_parser.cc"
    break;

  case 944: // output_params_list: output_params_list ","
#line 3210 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4990 "dhcp4_parser.cc"
    break;

  case 950: // $@144: %empty
#line 3222 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4999 "dhcp4_parser.cc"
    break;

  case 951: // output: "output" $@144 ":" "constant string"
#line 3225 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5009 "dhcp4_parser.cc"
    break;

  case 952: // flush: "flush" ":" "boolean"
#line 3231 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5019 "dhcp4_parser.cc"
    break;

  case 953: // maxsize: "maxsize" ":" "integer"
#line 3237 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5029 "dhcp4_parser.cc"
    break;

  case 954: // maxver: "maxver" ":" "integer"
#line 3243 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5039 "dhcp4_parser.cc"
    break;

  case 955: // $@145: %empty
#line 3249 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5048 "dhcp4_parser.cc"
    break;

  case 956: // pattern: "pattern" $@145 ":" "constant string"
#line 3252 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5058 "dhcp4_parser.cc"
    break;

  case 957: // $@146: %empty
#line 3258 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5070 "dhcp4_parser.cc"
    break;

  case 958: // compatibility: "compatibility" $@146 ":" "{" compatibility_params "}"
#line 3264 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5079 "dhcp4_parser.cc"
    break;

  case 961: // compatibility_params: compatibility_params ","
#line 3271 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5087 "dhcp4_parser.cc"
    break;

  case 967: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3283 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5097 "dhcp4_parser.cc"
    break;

  case 968: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3289 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5107 "dhcp4_parser.cc"
    break;

  case 969: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3295 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5117 "dhcp4_parser.cc"
    break;

  case 970: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3301 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5127 "dhcp4_parser.cc"
    break;


#line 5131 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1410;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     225, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410,    26,    42,    62,    67,    72,    81,
      86,    99,   104,   181,   202,   212,   222,   244, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410,    42,  -189,    43,   258,    76,   694,
    1457,    89,   -17,   133,   296,   -68,   243,    91, -1410,    65,
     117,    92,   120,   196, -1410,    51, -1410, -1410, -1410, -1410,
     239,   262,   264, -1410, -1410, -1410,   282,   295, -1410, -1410,
   -1410,   362,   377,   409,   438,   439,   455,   463,   465,   468,
     469,   472,   480, -1410,   481,   482,   484,   485,   486, -1410,
   -1410, -1410, -1410,   489,   491,   492,   493,   495,   496,   499,
   -1410, -1410, -1410,   500, -1410, -1410, -1410, -1410, -1410,   501,
     503,   504, -1410, -1410, -1410, -1410, -1410,   506, -1410, -1410,
   -1410, -1410, -1410, -1410,   507,   510,   511, -1410, -1410,   514,
   -1410,    74, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,   516,   517,
     518,   520, -1410,    82, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     523, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410,    94, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     529, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     131, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,   245,   259,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410,   256, -1410, -1410,   530, -1410, -1410, -1410,   535,
   -1410, -1410,   266,   357, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410,   538,   540,   542,
   -1410, -1410, -1410, -1410, -1410,   432,   544, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410,   141, -1410, -1410, -1410,   545, -1410,   546, -1410,   547,
     549, -1410, -1410, -1410, -1410, -1410,   142, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410,   550,   143, -1410,
   -1410, -1410, -1410,    42,    42, -1410,   321,   553, -1410, -1410,
     555,   558,   564,   332,   333,   334,   570,   571,   573,   343,
     344,   578,   579,   580,   350,   351,   353,   354,   359,   360,
     367,   369,   371,   373,   375,   374,   586,   378,   381,   386,
     391,   393,   587,   608,   614,   629,   397,   398,   402,   405,
     410,   414,   413,   647,   649,   652,   423,   655,   656,   657,
     659,   660,   429,   431,   433,   665,   667,   669,   670,   671,
     445,   677,   680,   681,   682,   683,   684,   452,   453,   454,
     688,   689, -1410,   258, -1410,   690,   691,   692,   460,   461,
     464,   466,    76, -1410,   696,   698,   699,   701,   702,   703,
     473,   705,   706,   707,   694, -1410,   708,   478,  1457, -1410,
     711,   712,   714,   715,   716,   718,   719,   726, -1410,    89,
   -1410,   727,   728,   498,   733,   734,   737,   508, -1410,   133,
     740,   509,   512,   513,   743, -1410,   296,   744,   747,   -91,
   -1410,   515,   749,   519,   751,   521,   522,   754,   755,   243,
   -1410,   756,   526,    91, -1410, -1410, -1410,   758,   769,   786,
     790,   794, -1410, -1410, -1410,   568,   569,   572, -1410, -1410,
     797,   798,   802, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   574, -1410, -1410, -1410, -1410,
   -1410,   -15,   575,   581,   582, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410,   807,   808,   809, -1410,   584,   446,   822,   823,
     597, -1410, -1410, -1410,   827,   828,   830,   831,   832, -1410,
     834,   833,   836,   841,   603,   615, -1410, -1410, -1410,   845,
     844, -1410,   847,   382,   376, -1410, -1410, -1410, -1410, -1410,
     619,   622,   623,   853,   625,   626, -1410,   847,   847,   869,
   -1410,   643, -1410, -1410,   847,   644,   658,   661,   664,   666,
     668,   672, -1410,   673,   675, -1410,   676,   678,   679, -1410,
   -1410,   685, -1410, -1410, -1410,   847, -1410,   686,   823, -1410,
   -1410,   687, -1410,   693, -1410, -1410,    28,   566, -1410,   886,
   -1410, -1410,    42,   258,    91,    76,   389, -1410, -1410, -1410,
     821,   821,   887, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410,   892,   894,   896, -1410, -1410, -1410, -1410,
   -1410, -1410,   897, -1410, -1410, -1410,   175,   898,   904,   907,
     270,    64,   908,   186,   243, -1410, -1410,   909,   159, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     910, -1410, -1410, -1410, -1410,   773, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     887, -1410,   153,   160,   168, -1410, -1410,   171, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   889,   914,   919,   920,   921,
     925,   926,   927,   928,   929, -1410,   930,   931, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     188, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410,   192, -1410,   932,   933,
   -1410, -1410,   934,   936, -1410, -1410,   935,   939, -1410, -1410,
     937,   941, -1410, -1410,   940,   942, -1410, -1410, -1410, -1410,
   -1410, -1410,   106, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     943,   944, -1410, -1410,   945,   947, -1410, -1410,   946,   950,
   -1410,   951,   952,   953,   954,   955,   956,   195, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   957,   958,   959, -1410,   213,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410,   948,   961, -1410,
     962, -1410,   963, -1410, -1410, -1410,   217, -1410, -1410, -1410,
   -1410, -1410,   234, -1410,   121, -1410,   964,   965,   966,   967,
   -1410,   236, -1410, -1410, -1410, -1410, -1410,   731, -1410,   968,
     969, -1410, -1410,   971, -1410,   970, -1410, -1410, -1410,   973,
     976,   389, -1410,   979,   983,   986,   987,   713,   700,   738,
     761,   767,   777,   779,   781,   782,   785,  1022,   803,   796,
    1030,  1037,  1047,  1048,  1050,  1052,   821, -1410, -1410,   821,
   -1410,   887,   694, -1410,   892,   133, -1410,   894,   296, -1410,
     896,  1402, -1410,   897,   175, -1410,   178, -1410,   898,    89,
   -1410,   904,   -68, -1410,   907,   826,   829,   840,   843,   849,
     850,   270, -1410,   825,   856,   858,    64, -1410,   674, -1410,
     908,   865,  1061,   871,  1100,   186, -1410, -1410,   260,   909,
   -1410,   872,   874,   879,   881,   159, -1410, -1410,  1115,  1120,
    1457, -1410,   910,  1122, -1410, -1410,   899,   903, -1410,   913,
     923,   924,   938, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410,   151, -1410, -1410,   960,   972,   974,   415,
     975,   977, -1410,   249, -1410,   257, -1410,  1123, -1410,  1167,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410,   277, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,  1124, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,  1169,
    1177, -1410, -1410, -1410, -1410, -1410, -1410,  1173, -1410,   297,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,  1178, -1410,  1180, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   298, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410,   978, -1410,    42, -1410,
   -1410,  1182, -1410, -1410, -1410, -1410, -1410,   355, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,   980,
     356, -1410,   847, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410,  1402, -1410,  1183,  1185,   981, -1410,   178,
   -1410, -1410,  1187,  1188,  1189,   982,  1191,   984,  1192,   674,
   -1410, -1410, -1410,  1193,   985,  1194,   260, -1410, -1410, -1410,
   -1410, -1410,   988,   989, -1410, -1410,   140,   990,   991, -1410,
    1195, -1410,  1196, -1410,  1198, -1410,   992, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410,    79,  1197,  1200, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410,   379, -1410, -1410,
   -1410, -1410, -1410, -1410,  1199,  1207, -1410, -1410,   172, -1410,
    1209,  1211,  1212,  1215,    79, -1410,   -53, -1410,  1197,   112,
    1200, -1410,  1026,   993,   994,  1224, -1410, -1410, -1410, -1410,
   -1410, -1410,   406, -1410, -1410, -1410, -1410,  1226,  1227,  1228,
   -1410,   407, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410,  1230,  1229,   -53, -1410,  1231,   997,  1003,
    1004,  1237,   112, -1410, -1410,  1238,  1240, -1410,  1011, -1410,
    1013, -1410, -1410, -1410,  1014, -1410,    39, -1410,  1230, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,   436,
   -1410, -1410, -1410,  1246,    39, -1410,  1017, -1410, -1410
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   218,     9,   406,    11,   629,    13,
     673,    15,   544,    17,   553,    19,   592,    21,   368,    23,
     873,    25,   905,    27,    46,    39,     0,     0,     0,     0,
       0,   675,     0,   555,   594,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   903,   203,   236,
       0,     0,     0,   695,   697,   699,     0,     0,   234,   247,
     249,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,     0,   166,
     173,   175,   177,     0,     0,     0,     0,     0,     0,     0,
     397,   542,   583,     0,   158,   181,   482,   660,   662,     0,
       0,     0,   330,   722,   664,   359,   380,     0,   345,   759,
     854,   871,   191,   193,     0,     0,     0,   915,   957,     0,
     142,     0,    67,    70,    71,    72,    73,    74,   107,   108,
     109,   110,   111,   112,    75,   103,   138,   139,    92,    93,
      94,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   114,   115,   130,   131,   132,
     134,   135,   136,   140,   141,    78,    79,   100,    80,    81,
      82,   133,    86,    87,    76,   104,   105,   106,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   113,   137,   220,   222,   226,     0,     0,
       0,     0,   217,     0,   205,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   466,   468,   470,   620,   464,   472,
       0,   474,   476,   717,   463,   411,   412,   413,   414,   415,
     438,   439,   440,   441,   442,   443,   461,   428,   429,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   462,     0,   408,   418,
     433,   434,   435,   419,   421,   422,   424,   425,   426,   420,
     416,   417,   436,   437,   423,   430,   431,   432,   427,   657,
       0,   656,   639,   640,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   637,   638,   636,
       0,   631,   634,   635,   654,   655,   715,   701,   703,   705,
     709,   707,   713,   711,   694,   688,   692,   693,     0,   676,
     677,   689,   690,   691,   685,   680,   686,   682,   683,   684,
     687,   681,     0,   573,   297,     0,   577,   575,   580,     0,
     569,   570,     0,   556,   557,   560,   572,   561,   562,   563,
     579,   564,   565,   566,   567,   568,   611,     0,     0,     0,
     618,   609,   610,   613,   614,     0,   595,   596,   599,   600,
     601,   602,   603,   604,   605,   608,   606,   607,   376,   378,
     373,     0,   370,   374,   375,     0,   890,     0,   893,     0,
       0,   897,   901,   888,   886,   887,     0,   875,   878,   879,
     880,   881,   882,   883,   884,   885,   912,     0,     0,   907,
     910,   911,    45,    50,     0,    37,    43,     0,    64,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    69,    66,     0,     0,     0,     0,     0,
       0,     0,   207,   219,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   410,   407,     0,     0,   633,   630,
       0,     0,     0,     0,     0,     0,     0,     0,   674,   679,
     545,     0,     0,     0,     0,     0,     0,     0,   554,   559,
       0,     0,     0,     0,     0,   593,   598,     0,     0,   372,
     369,     0,     0,     0,     0,     0,     0,     0,     0,   877,
     874,     0,     0,   909,   906,    49,    41,     0,     0,     0,
       0,     0,   160,   161,   162,     0,     0,     0,   201,   202,
       0,     0,     0,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,     0,   196,   197,   163,   164,
     165,     0,     0,     0,     0,   179,   180,   187,   188,   189,
     190,   195,     0,     0,     0,   157,     0,     0,     0,     0,
       0,   478,   479,   480,     0,     0,     0,     0,     0,   758,
       0,     0,     0,     0,     0,     0,   198,   199,   200,     0,
       0,    68,     0,     0,     0,   230,   231,   232,   233,   206,
       0,     0,     0,     0,     0,     0,   481,     0,     0,     0,
     409,     0,   659,   632,     0,     0,     0,     0,     0,     0,
       0,     0,   678,     0,     0,   571,     0,     0,     0,   582,
     558,     0,   615,   616,   617,     0,   597,     0,     0,   371,
     889,     0,   892,     0,   895,   896,     0,     0,   876,     0,
     914,   908,     0,     0,     0,     0,     0,   696,   698,   700,
       0,     0,   251,   156,   168,   169,   170,   171,   172,   167,
     174,   176,   178,   399,   546,   585,   159,   183,   184,   185,
     186,   182,   484,    38,   661,   663,     0,   724,   666,   361,
       0,     0,   761,     0,     0,   192,   194,     0,     0,    51,
     221,   224,   225,   223,   228,   229,   227,   467,   469,   471,
     622,   465,   473,   475,   477,     0,   658,   716,   702,   704,
     706,   710,   708,   714,   712,   574,   298,   578,   576,   581,
     612,   619,   377,   379,   891,   894,   899,   900,   898,   902,
     251,    42,     0,     0,     0,   243,   245,     0,   238,   241,
     242,   286,   288,   290,   294,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   308,     0,     0,   315,   317,
     319,   321,   323,   324,   325,   326,   327,   328,   292,   285,
       0,   258,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,     0,   256,     0,   252,
     253,   404,     0,   400,   401,   551,     0,   547,   548,   590,
       0,   586,   587,   489,     0,   485,   486,   340,   341,   342,
     343,   344,     0,   332,   335,   336,   337,   338,   339,   729,
       0,   725,   726,   671,     0,   667,   668,   366,     0,   362,
     363,     0,     0,     0,     0,     0,     0,     0,   382,   385,
     386,   387,   388,   389,   390,     0,     0,     0,   355,     0,
     347,   350,   351,   352,   353,   354,   766,     0,   762,   763,
       0,   866,     0,   869,   862,   863,     0,   856,   859,   860,
     861,   864,     0,   920,     0,   917,     0,     0,     0,     0,
     966,     0,   959,   962,   963,   964,   965,    53,   627,     0,
     623,   624,   720,     0,   719,     0,    62,   904,   204,     0,
       0,   240,   237,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   260,   235,   248,     0,
     250,   255,     0,   398,   403,   555,   543,   550,   594,   584,
     589,     0,   483,   488,   334,   331,   731,   723,   728,   675,
     665,   670,     0,   360,   365,     0,     0,     0,     0,     0,
       0,   384,   381,     0,     0,     0,   349,   346,     0,   760,
     765,     0,     0,     0,     0,   858,   855,   872,     0,   919,
     916,     0,     0,     0,     0,   961,   958,    55,     0,    54,
       0,   621,   626,     0,   718,   913,     0,     0,   239,     0,
       0,     0,     0,   296,   299,   300,   301,   302,   303,   304,
     305,   306,   307,     0,   313,   314,     0,     0,     0,     0,
       0,     0,   259,     0,   254,     0,   402,     0,   549,     0,
     588,   541,   511,   512,   513,   497,   498,   516,   517,   518,
     519,   520,   521,   539,   500,   501,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   540,   494,   495,   496,   509,   510,   506,
     507,   508,     0,   491,   499,   514,   515,   502,   503,   504,
     505,   487,   333,   753,   755,     0,   747,   748,   749,   750,
     751,   752,   740,   741,   745,   746,   742,   743,   744,     0,
     732,   733,   736,   737,   738,   739,   727,     0,   669,     0,
     364,   391,   392,   393,   394,   395,   396,   383,   356,   357,
     358,   348,   784,   789,   791,     0,   814,     0,   795,   783,
     776,   777,   778,   781,   782,     0,   768,   771,   772,   773,
     774,   779,   780,   775,   764,   865,     0,   868,     0,   857,
     935,     0,   933,   931,   925,   929,   930,     0,   922,   927,
     928,   926,   918,   967,   968,   969,   970,   960,    52,    57,
       0,   625,     0,   244,   246,   287,   289,   291,   295,   310,
     311,   312,   309,   316,   318,   320,   322,   329,   293,   257,
     405,   552,   591,   493,   490,     0,     0,     0,   730,   735,
     672,   367,     0,     0,     0,     0,     0,     0,     0,   770,
     767,   867,   870,     0,     0,     0,   924,   921,    56,   628,
     721,   492,     0,     0,   757,   734,     0,     0,     0,   793,
       0,   794,     0,   769,     0,   932,     0,   923,   754,   756,
     786,   787,   788,   785,   790,   792,     0,   797,     0,   934,
     826,   829,   831,   833,   825,   824,   823,     0,   816,   819,
     820,   821,   822,   802,     0,   798,   799,   940,     0,   937,
       0,     0,     0,     0,   818,   815,     0,   796,   801,     0,
     939,   936,     0,     0,     0,     0,   817,   812,   811,   807,
     809,   810,     0,   804,   808,   800,   950,     0,     0,     0,
     955,     0,   942,   945,   946,   947,   948,   949,   938,   828,
     827,   830,   832,   835,     0,   806,   803,     0,     0,     0,
       0,     0,   944,   941,   840,     0,   836,   837,     0,   805,
       0,   952,   953,   954,     0,   943,     0,   834,   839,   813,
     951,   956,   852,   851,   845,   847,   848,   849,   850,     0,
     842,   846,   838,     0,   844,   841,     0,   843,   853
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   -59, -1410,  -623, -1410,   525,
   -1410, -1410, -1410, -1410, -1410, -1410,  -681, -1410, -1410, -1410,
     -67, -1410, -1410, -1410, -1410, -1410, -1410, -1410,   524,   721,
     -48,    25,    44,   -45,   -19,     6,    41,    93,    98,   100,
     101, -1410, -1410, -1410, -1410,   103, -1410, -1410,   108,   111,
      38,    46,    48,    56, -1410, -1410,    61, -1410,    63, -1410,
      66, -1410,    68,   113,    71, -1410, -1410,    73,    78,    83,
      85,    88, -1410,    90, -1410,   118, -1410, -1410, -1410, -1410,
   -1410,    45, -1410, -1410, -1410,   527,   722, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410,   246, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   426, -1410,   219, -1410,  -737,
     229, -1410, -1410, -1409, -1410, -1407, -1410, -1398, -1410, -1410,
   -1410, -1410,   -63, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1058, -1410,
   -1056, -1410, -1044, -1410,   137, -1410, -1410, -1410, -1410, -1410,
   -1410,   215, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     194, -1410, -1410, -1410, -1410, -1410, -1410, -1410,   209, -1410,
   -1410, -1410,   220,   697, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410,   204, -1410, -1410, -1410, -1410, -1410, -1410, -1036, -1410,
   -1410, -1410,   233, -1410, -1410, -1410,   237,   729, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1033, -1410,   -32, -1410,
     -27, -1410,   123,   125,   128, -1410, -1410, -1410, -1410, -1410,
     228, -1410, -1410,   -16,   -60, -1410, -1410, -1410, -1410, -1410,
     241, -1410, -1410, -1410,   247, -1410,   720, -1410,   -49, -1410,
   -1410, -1410, -1410, -1410,   -43, -1410, -1410, -1410, -1410, -1410,
     -29, -1410, -1410, -1410,   248, -1410, -1410, -1410,   252, -1410,
     709, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   189, -1410, -1410, -1410,   193,
     736, -1410, -1410, -1410,   -41, -1410,    -6, -1410,   -56, -1410,
   -1410, -1410,   240, -1410, -1410, -1410,   253, -1410,   735,   -13,
   -1410,     7, -1410,    18, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1032, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
     250, -1410, -1410, -1410,    -7, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410,   226, -1410, -1410,   -14,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410,   -81, -1410, -1410,  -114, -1410, -1410, -1410,
   -1410, -1410,   -70, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410,  -130, -1410, -1410,  -142, -1410, -1410,
   -1410, -1410, -1410,   251, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410,   541,   725, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410,   585,   723, -1410, -1410, -1410, -1410, -1410,
   -1410,   242, -1410, -1410,     4, -1410, -1410, -1410, -1410, -1410,
   -1410,   -58, -1410, -1410,   -99, -1410, -1410, -1410, -1410, -1410,
   -1410, -1410, -1410, -1410, -1410,   261, -1410, -1410, -1410, -1410
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   774,
      82,    83,    39,    64,    79,    80,   790,   997,  1098,  1099,
     869,    41,    66,    85,   457,    86,    43,    67,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   486,   176,   177,   507,   178,   179,   180,
     181,   182,   183,   184,   492,   759,   185,   493,   186,   494,
     187,   495,   188,   189,   190,   508,   771,   191,   192,   193,
     194,   195,   525,   196,   526,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   461,   243,   244,    45,    68,   245,
     535,   246,   536,   793,   247,   537,   796,   248,   249,   250,
     251,   206,   471,   207,   462,   837,   838,   839,  1009,   840,
    1010,   208,   472,   209,   473,   898,   899,   900,  1039,   870,
     871,   872,  1013,   873,  1014,   874,  1015,   875,  1035,   876,
    1016,   877,   878,   572,   879,   880,   881,   882,   883,   884,
     885,   886,   887,   888,  1027,  1292,   889,   890,   891,  1030,
     892,  1031,   893,  1032,   894,  1033,   895,  1034,   210,   515,
     922,   923,   924,   925,   926,   927,   928,   211,   521,   959,
     960,   961,   962,   963,   212,   518,   938,   939,   940,  1062,
      59,    75,   421,   422,   423,   587,   424,   588,   213,   519,
     947,   948,   949,   950,   951,   952,   953,   954,   214,   503,
     902,   903,   904,  1042,    47,    69,   297,   298,   299,   548,
     300,   544,   301,   545,   302,   546,   303,   549,   304,   551,
     305,   552,   215,   216,   217,   309,   218,   509,   914,   915,
     916,  1051,  1182,  1183,   219,   504,    53,    72,   906,   907,
     908,  1045,    55,    73,   382,   383,   384,   385,   386,   387,
     388,   571,   389,   575,   390,   574,   391,   392,   576,   393,
     220,   505,   910,   911,   912,  1048,    57,    74,   405,   406,
     407,   408,   409,   580,   410,   411,   412,   413,   414,   415,
     584,   311,   547,   999,  1000,  1001,  1100,    49,    70,   340,
     341,   342,   556,   343,   221,   510,   222,   511,   223,   517,
     934,   935,   936,  1059,    51,    71,   358,   359,   360,   224,
     466,   225,   467,   226,   468,   364,   561,   365,   562,   366,
     563,   367,   565,   368,   564,   369,   567,   370,   566,   371,
     560,   318,   553,  1003,  1004,  1103,   227,   516,   930,   931,
     932,  1056,  1209,  1210,  1211,  1212,  1213,  1305,  1214,  1306,
    1215,   228,   229,   522,   967,   968,   969,  1078,  1245,  1246,
    1247,  1312,  1353,  1248,  1313,  1249,  1314,  1250,  1251,  1252,
    1318,  1374,  1375,  1376,  1386,  1402,  1403,  1404,  1424,  1253,
    1316,  1367,  1368,  1369,  1380,  1420,  1370,  1381,  1371,  1382,
    1372,  1383,  1435,  1436,  1437,  1446,  1459,  1460,  1461,  1463,
     230,   523,   976,   977,   978,   979,  1082,   980,   981,  1084,
     231,   524,    61,    76,   436,   437,   438,   439,   592,   440,
     441,   594,   442,   443,   444,   597,   828,   445,   598,   232,
     460,    63,    77,   448,   449,   450,   601,   451,   233,   530,
     984,   985,  1088,  1267,  1268,  1269,  1270,  1325,  1271,  1323,
    1378,  1379,  1389,  1411,  1412,  1413,  1427,  1414,  1415,  1416,
    1417,  1431,   234,   531,   991,   992,   993,   994,   995,   996
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     160,   242,   264,   321,   354,    78,   380,   401,   420,   433,
     381,   402,   372,   314,   896,  1175,   803,   804,  1176,  1190,
    1240,   265,  1241,   807,   268,   403,    28,   252,   312,   344,
     356,   404,   394,   416,  1242,   434,   773,  1454,   337,  1455,
     310,   339,   355,   338,   821,    81,   826,    29,  1456,    30,
     269,    31,   374,    84,   458,  1454,   315,  1455,   361,   459,
     418,   419,   253,   313,   345,   357,  1456,   395,   417,    40,
     435,   452,   137,   138,    42,   270,   316,   533,   362,    44,
     842,   843,   534,   418,   419,   542,   131,   317,    46,   363,
     543,   235,   236,    48,   266,   237,   454,   554,   238,   239,
     240,   241,   555,   446,   447,   773,    50,   279,   322,  1054,
     271,    52,  1055,   267,   296,   280,   323,   281,   324,  1360,
     453,    93,    94,    95,  1089,   282,   325,  1090,   455,  1397,
     283,   326,   284,   327,   558,   285,   328,   286,   329,   559,
     288,   330,   289,   331,   589,   599,   603,   290,   332,   590,
     600,   604,   291,   333,   292,   334,   533,   293,   335,   294,
     336,  1006,   272,   603,   137,   138,   159,   273,  1007,   274,
     275,   542,   276,   373,  1011,  1390,  1008,   277,  1391,  1012,
     278,   159,   287,   754,   755,   756,   757,   295,    54,   137,
     138,  1036,   306,   132,   307,  1036,  1037,   308,  1071,   456,
    1038,   137,   138,  1072,   137,   138,  1289,  1290,  1291,    56,
      93,    94,    95,    96,   137,   138,  1076,  1452,   868,    58,
    1085,  1077,   758,   346,   827,  1086,   955,   956,   957,    60,
     347,   348,   349,   350,   351,   352,   353,   599,   374,  1095,
     375,   376,  1087,   463,  1096,   377,   378,   379,   101,   102,
     103,    62,  1036,   568,  1361,  1362,  1363,  1299,   137,   138,
     554,  1240,   569,  1241,   570,  1300,   464,  1175,   465,    87,
    1176,  1190,    88,   159,   578,  1242,    32,    33,    34,    35,
    1303,   131,   132,   374,    89,  1304,   469,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   159,   470,
     589,  1319,  1133,   137,   138,  1311,  1320,  1350,  1351,  1352,
     159,   137,   138,   159,  1193,  1194,  1195,   917,   918,   919,
     920,  1406,   921,   159,  1407,  1408,  1409,  1410,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,  1326,   558,
     579,   131,   132,  1327,  1329,   374,   474,   159,   137,   138,
     970,   971,   972,   133,   134,   135,   986,   987,   988,   989,
     136,   475,  1384,   137,   138,   137,   138,  1385,   139,   140,
     141,   142,   143,   159,   605,   606,   794,   795,   144,   791,
     792,   374,   396,   375,   376,   397,   398,   399,   145,  1425,
    1432,   146,   159,   476,  1426,  1433,   835,   836,   147,   148,
     973,   137,   138,   149,   941,   942,   943,   944,   945,   946,
     400,   425,   426,   427,   428,   429,   430,   431,   432,  1464,
     585,   150,   477,   478,  1465,   151,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   479,
     152,   153,   154,   155,   156,   157,   160,   480,  1260,   481,
    1261,  1262,   482,   483,   158,   242,   484,   159,   861,   862,
     863,   864,   865,   866,   485,   487,   488,   264,   489,   490,
     491,   321,   159,   496,   159,   497,   498,   499,   314,   500,
     501,   252,   354,   502,   506,   512,   265,   513,   514,   268,
     520,   527,   380,   312,   528,   529,   381,   344,   532,   401,
     538,   539,   540,   402,   541,   310,   337,   550,   356,   339,
     159,   338,   433,   557,   573,   269,   253,   403,   394,   577,
     355,   315,   581,   404,   582,   416,   583,   586,   313,   591,
     593,   595,   345,   596,   602,   607,   361,   608,   434,   609,
     270,   316,   610,   357,   767,   768,   769,   770,   611,   612,
     613,   614,   317,   395,   615,   616,   362,   617,   618,   266,
     417,   619,   620,   621,   622,   623,   624,   363,   625,   626,
     635,   641,   279,   435,   627,   271,   322,   628,   267,   296,
     280,  1330,   281,   629,   323,   630,   324,   631,   632,   634,
     282,   633,   642,   636,   325,   283,   637,   284,   643,   326,
     285,   327,   286,   638,   328,   288,   329,   289,   639,   330,
     640,   331,   290,   644,   645,   646,   332,   291,   647,   292,
     648,   333,   293,   334,   294,   649,   335,   272,   336,   650,
     651,   652,   273,   653,   274,   275,   654,   276,   655,   656,
     657,   658,   277,   659,   660,   278,   661,   287,   662,   664,
     663,   665,   295,   666,   667,   668,   160,   306,   242,   307,
     669,   670,   308,   831,   671,   672,   673,   674,   675,   676,
     677,   678,   679,   680,   682,   683,   684,   685,   686,   687,
     690,   688,   691,   692,   252,   693,   694,   695,   696,   697,
     698,   699,   701,   702,   958,   704,   705,   433,   706,   707,
     708,   990,   709,   710,    91,    92,    93,    94,    95,    96,
     711,   713,   714,   715,   858,   859,   860,   716,   717,   253,
     964,   718,   974,   434,   721,   719,   722,   725,   727,   723,
     724,   728,   730,   731,   732,   733,   734,   735,   736,   737,
     739,   740,   742,   829,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   965,   743,   975,   435,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   744,   254,   255,   256,   745,   132,   137,
     138,   746,   747,   748,   750,   751,   749,   752,   753,   760,
     134,   135,   763,   764,   765,   761,   762,   257,   766,   137,
     138,   258,   259,   260,   139,   140,   141,   772,   261,   262,
      30,   775,   776,   777,   144,   778,   779,   785,   782,   780,
    1232,   781,   263,   783,  1233,  1234,  1235,  1236,   784,   786,
     787,   788,   789,   797,  1237,  1238,   798,   799,   800,   801,
     802,   841,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   854,   855,   805,   806,   808,   856,
     857,   858,   859,   860,   861,   862,   863,   864,   865,   866,
     867,   830,   809,  1017,   897,   810,   152,   153,   811,   901,
     812,   905,   813,   909,   913,   929,   814,   815,   159,   816,
     817,   933,   818,   819,   937,   966,   983,   998,  1018,   820,
     822,   824,  1002,  1019,  1020,  1021,   374,   825,   159,  1022,
    1023,  1024,  1025,  1026,  1028,  1029,  1041,  1114,  1040,  1044,
    1043,  1046,  1047,  1049,  1050,  1053,  1052,  1058,  1113,  1057,
    1061,  1060,  1063,  1064,  1079,  1065,  1066,  1067,  1068,  1069,
    1070,  1073,  1074,  1075,  1080,  1097,  1081,  1083,  1091,  1092,
    1093,  1094,  1102,  1115,  1101,   264,  1105,  1106,   380,  1104,
    1107,   401,   381,  1109,  1141,   402,   314,  1110,  1174,  1196,
    1111,  1112,   354,  1201,   265,   420,  1202,   268,  1116,   403,
     868,   312,  1117,  1142,   394,   404,  1145,   416,  1197,   958,
    1185,  1239,  1118,   310,  1119,  1204,  1120,  1121,   356,  1177,
    1122,  1263,  1184,   269,  1178,  1264,  1123,  1203,   990,   315,
     355,  1125,  1146,   321,  1126,   964,   313,  1243,  1187,   395,
    1124,  1127,   417,  1206,   974,  1186,   361,  1265,   270,   316,
    1205,  1128,  1129,   357,  1130,   159,  1131,  1147,  1188,   344,
     317,  1221,  1228,  1207,  1222,  1256,   362,   266,   337,  1189,
     965,   339,  1244,   338,  1208,  1223,  1143,   363,  1224,   975,
     279,  1198,  1266,   271,  1225,  1226,   267,   296,   280,  1156,
     281,  1229,  1148,  1230,   345,  1144,  1173,  1157,   282,  1158,
    1199,  1200,  1255,   283,  1258,   284,  1257,  1159,   285,  1273,
     286,  1274,  1160,   288,  1161,   289,  1275,  1162,  1276,  1163,
     290,  1278,  1165,  1279,  1166,   291,  1282,   292,  1307,  1167,
     293,  1301,   294,  1283,  1168,   272,  1169,  1284,   322,  1170,
     273,  1171,   274,   275,  1149,   276,   323,  1285,   324,  1150,
     277,  1151,  1152,   278,  1153,   287,   325,  1286,  1287,  1154,
     295,   326,  1155,   327,  1164,   306,   328,   307,   329,  1172,
     308,   330,  1288,   331,  1179,  1302,  1180,  1308,   332,  1181,
    1309,  1310,  1315,   333,  1317,   334,  1324,  1332,   335,  1333,
     336,  1336,  1337,  1338,  1293,  1340,  1342,  1344,  1346,  1322,
    1419,  1357,  1356,  1358,  1373,  1387,  1294,  1377,  1295,  1297,
    1388,  1298,  1321,  1392,  1328,  1393,  1394,  1339,  1334,  1395,
    1345,  1341,  1348,  1349,  1354,  1355,  1359,  1421,  1422,  1423,
    1428,  1429,  1430,  1438,  1441,  1440,  1141,  1434,  1442,  1443,
    1174,  1444,  1196,  1448,  1447,  1449,  1201,  1450,  1451,  1202,
    1466,  1468,  1239,   823,   681,  1142,  1005,  1108,  1145,  1263,
    1134,  1197,  1185,  1264,   689,  1132,  1296,   832,  1204,  1192,
    1231,  1177,   834,  1220,  1184,  1227,  1178,  1136,  1243,  1135,
    1203,  1191,  1219,   700,  1146,  1265,   729,  1331,  1138,  1364,
    1187,  1281,  1137,  1280,   703,   726,  1206,  1186,  1140,   720,
    1139,  1218,  1335,  1205,   712,  1343,  1254,  1405,  1216,  1147,
    1188,  1439,  1217,  1244,  1396,  1365,  1207,  1364,  1462,  1398,
    1266,  1189,  1467,  1399,   738,   982,   741,  1208,  1143,   833,
    1347,  1272,  1418,  1445,  1198,     0,  1259,     0,     0,     0,
       0,  1156,     0,  1365,  1148,  1400,     0,  1144,  1173,  1157,
    1366,  1158,     0,  1199,  1200,     0,  1277,     0,  1398,  1159,
       0,     0,  1399,     0,  1160,     0,  1161,     0,     0,  1162,
       0,  1163,     0,     0,  1165,     0,  1166,     0,  1366,  1453,
    1401,  1167,     0,     0,  1400,     0,  1168,     0,  1169,     0,
       0,  1170,     0,  1171,     0,     0,  1149,  1453,     0,     0,
       0,  1150,     0,  1151,  1152,  1457,  1153,     0,     0,     0,
       0,  1154,     0,     0,  1155,     0,  1164,     0,     0,  1401,
       0,  1172,     0,  1457,     0,     0,  1179,     0,  1180,     0,
       0,  1181,    91,    92,    93,    94,    95,    96,     0,     0,
    1458,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1458,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     0,     0,     0,     0,   132,   374,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   134,   135,
       0,     0,     0,     0,     0,     0,     0,   137,   138,     0,
     259,     0,   139,   140,   141,     0,   261,   262,     0,     0,
       0,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     263,   125,   126,   127,   128,     0,     0,     0,     0,     0,
       0,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
       0,   319,   137,   138,     0,     0,     0,     0,     0,     0,
       0,   261,   262,     0,     0,     0,   320,     0,     0,     0,
       0,     0,     0,     0,   152,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   751,  1051,   697,   698,  1051,  1051,
    1078,    69,  1078,   704,    69,    74,     0,    68,    69,    70,
      71,    74,    73,    74,  1078,    76,   659,  1446,    70,  1446,
      69,    70,    71,    70,   725,   234,    18,     5,  1446,     7,
      69,     9,   105,    10,     3,  1464,    69,  1464,    71,     8,
     151,   152,    68,    69,    70,    71,  1464,    73,    74,     7,
      76,     6,   125,   126,     7,    69,    69,     3,    71,     7,
      41,    42,     8,   151,   152,     3,   103,    69,     7,    71,
       8,    15,    16,     7,    69,    19,     4,     3,    22,    23,
      24,    25,     8,    12,    13,   728,     7,    69,    70,     3,
      69,     7,     6,    69,    69,    69,    70,    69,    70,    40,
       3,    32,    33,    34,     3,    69,    70,     6,     8,   182,
      69,    70,    69,    70,     3,    69,    70,    69,    70,     8,
      69,    70,    69,    70,     3,     3,     3,    69,    70,     8,
       8,     8,    69,    70,    69,    70,     3,    69,    70,    69,
      70,     8,    69,     3,   125,   126,   234,    69,     8,    69,
      69,     3,    69,    40,     3,     3,     8,    69,     6,     8,
      69,   234,    69,   198,   199,   200,   201,    69,     7,   125,
     126,     3,    69,   104,    69,     3,     8,    69,     3,     3,
       8,   125,   126,     8,   125,   126,    55,    56,    57,     7,
      32,    33,    34,    35,   125,   126,     3,   178,   179,     7,
       3,     8,   237,   134,   196,     8,   162,   163,   164,     7,
     141,   142,   143,   144,   145,   146,   147,     3,   105,     3,
     107,   108,     8,     4,     8,   112,   113,   114,    70,    71,
      72,     7,     3,     8,   175,   176,   177,     8,   125,   126,
       3,  1319,     3,  1319,     8,     8,     4,  1303,     4,    11,
    1303,  1303,    14,   234,     8,  1319,   234,   235,   236,   237,
       3,   103,   104,   105,    26,     8,     4,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   234,     4,
       3,     3,  1039,   125,   126,     8,     8,   167,   168,   169,
     234,   125,   126,   234,   136,   137,   138,   142,   143,   144,
     145,   209,   147,   234,   212,   213,   214,   215,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,     3,     3,
       3,   103,   104,     8,     8,   105,     4,   234,   125,   126,
     184,   185,   186,   115,   116,   117,   217,   218,   219,   220,
     122,     4,     3,   125,   126,   125,   126,     8,   130,   131,
     132,   133,   134,   234,   453,   454,    20,    21,   140,    17,
      18,   105,   106,   107,   108,   109,   110,   111,   150,     3,
       3,   153,   234,     4,     8,     8,    27,    28,   160,   161,
     234,   125,   126,   165,   154,   155,   156,   157,   158,   159,
     134,   188,   189,   190,   191,   192,   193,   194,   195,     3,
       8,   183,     4,     4,     8,   187,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,     4,
     202,   203,   204,   205,   206,   207,   533,     4,   208,     4,
     210,   211,     4,     4,   216,   542,     4,   234,    63,    64,
      65,    66,    67,    68,     4,     4,     4,   554,     4,     4,
       4,   558,   234,     4,   234,     4,     4,     4,   554,     4,
       4,   542,   569,     4,     4,     4,   554,     4,     4,   554,
       4,     4,   579,   554,     4,     4,   579,   558,     4,   586,
       4,     4,     4,   586,     4,   554,   558,     4,   569,   558,
     234,   558,   599,     4,     4,   554,   542,   586,   579,     4,
     569,   554,     4,   586,     4,   586,     4,     3,   554,     4,
       4,     4,   558,     4,     4,   234,   569,     4,   599,     4,
     554,   554,     4,   569,   118,   119,   120,   121,     4,   237,
     237,   237,   554,   579,     4,     4,   569,     4,   235,   554,
     586,   237,     4,     4,     4,   235,   235,   569,   235,   235,
       4,     4,   554,   599,   235,   554,   558,   237,   554,   554,
     554,  1282,   554,   236,   558,   236,   558,   236,   235,   235,
     554,   236,     4,   235,   558,   554,   235,   554,     4,   558,
     554,   558,   554,   237,   558,   554,   558,   554,   237,   558,
     237,   558,   554,     4,   237,   237,   558,   554,   236,   554,
     235,   558,   554,   558,   554,   235,   558,   554,   558,   235,
     237,     4,   554,     4,   554,   554,     4,   554,   235,     4,
       4,     4,   554,     4,     4,   554,   237,   554,   237,     4,
     237,     4,   554,     4,     4,     4,   743,   554,   745,   554,
     235,     4,   554,   742,     4,     4,     4,     4,     4,   237,
     237,   237,     4,     4,     4,     4,     4,   237,   237,   235,
       4,   235,     4,     4,   745,     4,     4,     4,   235,     4,
       4,     4,     4,   235,   781,     4,     4,   784,     4,     4,
       4,   788,     4,     4,    30,    31,    32,    33,    34,    35,
       4,     4,     4,   235,    60,    61,    62,     4,     4,   745,
     781,     4,   783,   784,     4,   237,   237,     4,     4,   237,
     237,     4,   237,     4,   235,     4,   235,   235,     4,     4,
       4,   235,     4,   197,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,   781,     7,   783,   784,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     7,   100,   101,   102,     7,   104,   125,
     126,     7,   234,   234,     7,     7,   234,     5,   234,   234,
     116,   117,     5,     5,     5,   234,   234,   123,   234,   125,
     126,   127,   128,   129,   130,   131,   132,     5,   134,   135,
       7,   234,     5,     5,   140,     5,     5,   234,     5,     7,
     166,     7,   148,     7,   170,   171,   172,   173,     7,   234,
       5,     7,     5,   234,   180,   181,   234,   234,     5,   234,
     234,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     7,   234,   234,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     5,   234,     4,     7,   234,   202,   203,   234,     7,
     234,     7,   234,     7,     7,     7,   234,   234,   234,   234,
     234,     7,   234,   234,     7,     7,     7,     7,     4,   234,
     234,   234,   149,     4,     4,     4,   105,   234,   234,     4,
       4,     4,     4,     4,     4,     4,     3,   237,     6,     3,
       6,     6,     3,     6,     3,     3,     6,     3,   235,     6,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   234,     4,     4,     4,     4,
       4,     4,     3,   235,     6,  1042,     6,     4,  1045,     8,
       4,  1048,  1045,     4,  1051,  1048,  1042,     4,  1051,  1056,
       4,     4,  1059,  1056,  1042,  1062,  1056,  1042,   237,  1048,
     179,  1042,   235,  1051,  1045,  1048,  1051,  1048,  1056,  1076,
    1051,  1078,   235,  1042,   235,  1056,   235,   235,  1059,  1051,
     235,  1088,  1051,  1042,  1051,  1088,     4,  1056,  1095,  1042,
    1059,   235,  1051,  1100,     4,  1076,  1042,  1078,  1051,  1045,
     237,     4,  1048,  1056,  1085,  1051,  1059,  1088,  1042,  1042,
    1056,     4,     4,  1059,     4,   234,     4,  1051,  1051,  1100,
    1042,   235,   237,  1056,   235,     4,  1059,  1042,  1100,  1051,
    1076,  1100,  1078,  1100,  1056,   235,  1051,  1059,   235,  1085,
    1042,  1056,  1088,  1042,   235,   235,  1042,  1042,  1042,  1051,
    1042,   235,  1051,   235,  1100,  1051,  1051,  1051,  1042,  1051,
    1056,  1056,   237,  1042,     4,  1042,   235,  1051,  1042,   237,
    1042,   237,  1051,  1042,  1051,  1042,   237,  1051,   237,  1051,
    1042,     6,  1051,     3,  1051,  1042,     4,  1042,     4,  1051,
    1042,     8,  1042,   234,  1051,  1042,  1051,   234,  1100,  1051,
    1042,  1051,  1042,  1042,  1051,  1042,  1100,   234,  1100,  1051,
    1042,  1051,  1051,  1042,  1051,  1042,  1100,   234,   234,  1051,
    1042,  1100,  1051,  1100,  1051,  1042,  1100,  1042,  1100,  1051,
    1042,  1100,   234,  1100,  1051,     8,  1051,     8,  1100,  1051,
       3,     8,     4,  1100,     4,  1100,     4,     4,  1100,     4,
    1100,     4,     4,     4,   234,     4,     4,     4,     4,  1258,
     174,     5,     7,     5,     7,     6,   234,     7,   234,   234,
       3,   234,   234,     4,   234,     4,     4,   235,   237,     4,
     235,   237,   234,   234,   234,   234,   234,   234,   234,     5,
       4,     4,     4,     4,   237,     4,  1303,     7,   235,   235,
    1303,     4,  1309,     3,     6,   234,  1309,   234,   234,  1309,
       4,   234,  1319,   728,   533,  1303,   830,  1011,  1303,  1326,
    1041,  1309,  1303,  1326,   542,  1036,  1129,   743,  1309,  1054,
    1076,  1303,   745,  1064,  1303,  1071,  1303,  1044,  1319,  1042,
    1309,  1053,  1062,   554,  1303,  1326,   589,  1303,  1047,  1356,
    1303,  1102,  1045,  1100,   558,   586,  1309,  1303,  1050,   579,
    1048,  1061,  1309,  1309,   569,  1319,  1080,  1388,  1058,  1303,
    1303,  1425,  1059,  1319,  1384,  1356,  1309,  1384,  1448,  1386,
    1326,  1303,  1464,  1386,   599,   784,   603,  1309,  1303,   744,
    1326,  1089,  1390,  1432,  1309,    -1,  1085,    -1,    -1,    -1,
      -1,  1303,    -1,  1384,  1303,  1386,    -1,  1303,  1303,  1303,
    1356,  1303,    -1,  1309,  1309,    -1,  1095,    -1,  1425,  1303,
      -1,    -1,  1425,    -1,  1303,    -1,  1303,    -1,    -1,  1303,
      -1,  1303,    -1,    -1,  1303,    -1,  1303,    -1,  1384,  1446,
    1386,  1303,    -1,    -1,  1425,    -1,  1303,    -1,  1303,    -1,
      -1,  1303,    -1,  1303,    -1,    -1,  1303,  1464,    -1,    -1,
      -1,  1303,    -1,  1303,  1303,  1446,  1303,    -1,    -1,    -1,
      -1,  1303,    -1,    -1,  1303,    -1,  1303,    -1,    -1,  1425,
      -1,  1303,    -1,  1464,    -1,    -1,  1303,    -1,  1303,    -1,
      -1,  1303,    30,    31,    32,    33,    34,    35,    -1,    -1,
    1446,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1464,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,    -1,
     128,    -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    91,    92,
     148,    94,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,
      -1,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   134,   135,    -1,    -1,    -1,   139,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   202,   203,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   202,
     203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   234
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,     0,     5,
       7,     9,   234,   235,   236,   237,   253,   254,   255,   260,
       7,   269,     7,   274,     7,   335,     7,   452,     7,   535,
       7,   552,     7,   484,     7,   490,     7,   514,     7,   428,
       7,   660,     7,   679,   261,   256,   270,   275,   336,   453,
     536,   553,   485,   491,   515,   429,   661,   680,   253,   262,
     263,   234,   258,   259,    10,   271,   273,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   103,   104,   115,   116,   117,   122,   125,   126,   130,
     131,   132,   133,   134,   140,   150,   153,   160,   161,   165,
     183,   187,   202,   203,   204,   205,   206,   207,   216,   234,
     268,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   292,   293,   295,   296,
     297,   298,   299,   300,   301,   304,   306,   308,   310,   311,
     312,   315,   316,   317,   318,   319,   321,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   349,   351,   359,   361,
     406,   415,   422,   436,   446,   470,   471,   472,   474,   482,
     508,   542,   544,   546,   557,   559,   561,   584,   599,   600,
     648,   658,   677,   686,   710,    15,    16,    19,    22,    23,
      24,    25,   268,   333,   334,   337,   339,   342,   345,   346,
     347,   348,   542,   544,   100,   101,   102,   123,   127,   128,
     129,   134,   135,   148,   268,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   293,   296,   297,   298,
     299,   300,   301,   304,   306,   308,   310,   311,   312,   315,
     316,   317,   318,   319,   321,   323,   329,   454,   455,   456,
     458,   460,   462,   464,   466,   468,   470,   471,   472,   473,
     508,   529,   542,   544,   546,   557,   559,   561,   579,   124,
     139,   268,   298,   299,   300,   301,   304,   306,   308,   310,
     312,   315,   316,   317,   318,   319,   321,   466,   468,   508,
     537,   538,   539,   541,   542,   544,   134,   141,   142,   143,
     144,   145,   146,   147,   268,   508,   542,   544,   554,   555,
     556,   557,   559,   561,   563,   565,   567,   569,   571,   573,
     575,   577,   482,    40,   105,   107,   108,   112,   113,   114,
     268,   380,   492,   493,   494,   495,   496,   497,   498,   500,
     502,   504,   505,   507,   542,   544,   106,   109,   110,   111,
     134,   268,   380,   496,   502,   516,   517,   518,   519,   520,
     522,   523,   524,   525,   526,   527,   542,   544,   151,   152,
     268,   430,   431,   432,   434,   188,   189,   190,   191,   192,
     193,   194,   195,   268,   542,   544,   662,   663,   664,   665,
     667,   668,   670,   671,   672,   675,    12,    13,   681,   682,
     683,   685,     6,     3,     4,     8,     3,   272,     3,     8,
     678,   332,   352,     4,     4,     4,   558,   560,   562,     4,
       4,   350,   360,   362,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   291,     4,     4,     4,
       4,     4,   302,   305,   307,   309,     4,     4,     4,     4,
       4,     4,     4,   447,   483,   509,     4,   294,   313,   475,
     543,   545,     4,     4,     4,   407,   585,   547,   423,   437,
       4,   416,   601,   649,   659,   320,   322,     4,     4,     4,
     687,   711,     4,     3,     8,   338,   340,   343,     4,     4,
       4,     4,     3,     8,   459,   461,   463,   530,   457,   465,
       4,   467,   469,   580,     3,     8,   540,     4,     3,     8,
     578,   564,   566,   568,   572,   570,   576,   574,     8,     3,
       8,   499,   381,     4,   503,   501,   506,     4,     8,     3,
     521,     4,     4,     4,   528,     8,     3,   433,   435,     3,
       8,     4,   666,     4,   669,     4,     4,   673,   676,     3,
       8,   684,     4,     3,     8,   253,   253,   234,     4,     4,
       4,     4,   237,   237,   237,     4,     4,     4,   235,   237,
       4,     4,     4,   235,   235,   235,   235,   235,   237,   236,
     236,   236,   235,   236,   235,     4,   235,   235,   237,   237,
     237,     4,     4,     4,     4,   237,   237,   236,   235,   235,
     235,   237,     4,     4,     4,   235,     4,     4,     4,     4,
       4,   237,   237,   237,     4,     4,     4,     4,     4,   235,
       4,     4,     4,     4,     4,     4,   237,   237,   237,     4,
       4,   277,     4,     4,     4,   237,   237,   235,   235,   334,
       4,     4,     4,     4,     4,     4,   235,     4,     4,     4,
     455,     4,   235,   538,     4,     4,     4,     4,     4,     4,
       4,     4,   556,     4,     4,   235,     4,     4,     4,   237,
     494,     4,   237,   237,   237,     4,   518,     4,     4,   431,
     237,     4,   235,     4,   235,   235,     4,     4,   663,     4,
     235,   682,     4,     7,     7,     7,     7,   234,   234,   234,
       7,     7,     5,   234,   198,   199,   200,   201,   237,   303,
     234,   234,   234,     5,     5,     5,   234,   118,   119,   120,
     121,   314,     5,   255,   257,   234,     5,     5,     5,     5,
       7,     7,     5,     7,     7,   234,   234,     5,     7,     5,
     264,    17,    18,   341,    20,    21,   344,   234,   234,   234,
       5,   234,   234,   264,   264,     7,   234,   264,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   264,   234,   257,   234,   234,    18,   196,   674,   197,
       5,   253,   276,   681,   333,    27,    28,   353,   354,   355,
     357,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   179,   268,
     367,   368,   369,   371,   373,   375,   377,   379,   380,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   394,
     395,   396,   398,   400,   402,   404,   367,     7,   363,   364,
     365,     7,   448,   449,   450,     7,   486,   487,   488,     7,
     510,   511,   512,     7,   476,   477,   478,   142,   143,   144,
     145,   147,   408,   409,   410,   411,   412,   413,   414,     7,
     586,   587,   588,     7,   548,   549,   550,     7,   424,   425,
     426,   154,   155,   156,   157,   158,   159,   438,   439,   440,
     441,   442,   443,   444,   445,   162,   163,   164,   268,   417,
     418,   419,   420,   421,   542,   544,     7,   602,   603,   604,
     184,   185,   186,   234,   542,   544,   650,   651,   652,   653,
     655,   656,   662,     7,   688,   689,   217,   218,   219,   220,
     268,   712,   713,   714,   715,   716,   717,   265,     7,   531,
     532,   533,   149,   581,   582,   363,     8,     8,     8,   356,
     358,     3,     8,   370,   372,   374,   378,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   392,     4,     4,
     397,   399,   401,   403,   405,   376,     3,     8,     8,   366,
       6,     3,   451,     6,     3,   489,     6,     3,   513,     6,
       3,   479,     6,     3,     3,     6,   589,     6,     3,   551,
       6,     3,   427,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   605,     6,
       3,     4,   654,     4,   657,     3,     8,     8,   690,     3,
       6,     4,     4,     4,     4,     3,     8,   234,   266,   267,
     534,     6,     3,   583,     8,     6,     4,     4,   354,     4,
       4,     4,     4,   235,   237,   235,   237,   235,   235,   235,
     235,   235,   235,     4,   237,   235,     4,     4,     4,     4,
       4,     4,   368,   367,   365,   454,   450,   492,   488,   516,
     512,   268,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   293,   296,   297,   298,   299,   300,   301,
     304,   306,   308,   310,   311,   312,   315,   316,   317,   318,
     319,   321,   323,   329,   380,   446,   464,   466,   468,   470,
     471,   472,   480,   481,   508,   542,   544,   557,   559,   561,
     579,   478,   409,   136,   137,   138,   268,   278,   279,   280,
     329,   380,   482,   508,   542,   544,   557,   559,   561,   590,
     591,   592,   593,   594,   596,   598,   588,   554,   550,   430,
     426,   235,   235,   235,   235,   235,   235,   439,   237,   235,
     235,   418,   166,   170,   171,   172,   173,   180,   181,   268,
     396,   398,   400,   542,   544,   606,   607,   608,   611,   613,
     615,   616,   617,   627,   604,   237,     4,   235,     4,   651,
     208,   210,   211,   268,   380,   542,   544,   691,   692,   693,
     694,   696,   689,   237,   237,   237,   237,   713,     6,     3,
     537,   533,     4,   234,   234,   234,   234,   234,   234,    55,
      56,    57,   393,   234,   234,   234,   402,   234,   234,     8,
       8,     8,     8,     3,     8,   595,   597,     4,     8,     3,
       8,     8,   609,   612,   614,     4,   628,     4,   618,     3,
       8,   234,   253,   697,     4,   695,     3,     8,   234,     8,
     264,   481,     4,     4,   237,   592,     4,     4,     4,   235,
       4,   237,     4,   607,     4,   235,     4,   692,   234,   234,
     167,   168,   169,   610,   234,   234,     7,     5,     5,   234,
      40,   175,   176,   177,   268,   542,   544,   629,   630,   631,
     634,   636,   638,     7,   619,   620,   621,     7,   698,   699,
     632,   635,   637,   639,     3,     8,   622,     6,     3,   700,
       3,     6,     4,     4,     4,     4,   630,   182,   268,   380,
     542,   544,   623,   624,   625,   621,   209,   212,   213,   214,
     215,   701,   702,   703,   705,   706,   707,   708,   699,   174,
     633,   234,   234,     5,   626,     3,     8,   704,     4,     4,
       4,   709,     3,     8,     7,   640,   641,   642,     4,   624,
       4,   237,   235,   235,     4,   702,   643,     6,     3,   234,
     234,   234,   178,   268,   371,   373,   375,   542,   544,   644,
     645,   646,   642,   647,     3,     8,     4,   645,   234
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   238,   240,   239,   241,   239,   242,   239,   243,   239,
     244,   239,   245,   239,   246,   239,   247,   239,   248,   239,
     249,   239,   250,   239,   251,   239,   252,   239,   253,   253,
     253,   253,   253,   253,   253,   254,   256,   255,   257,   258,
     258,   259,   259,   259,   261,   260,   262,   262,   263,   263,
     263,   265,   264,   266,   266,   267,   267,   267,   268,   270,
     269,   272,   271,   271,   273,   275,   274,   276,   276,   276,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   291,   290,   292,   294,   293,
     295,   296,   297,   298,   299,   300,   302,   301,   303,   303,
     303,   303,   303,   305,   304,   307,   306,   309,   308,   310,
     311,   313,   312,   314,   314,   314,   314,   315,   316,   317,
     318,   320,   319,   322,   321,   323,   324,   325,   326,   327,
     328,   329,   330,   332,   331,   333,   333,   333,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   336,   335,
     338,   337,   340,   339,   341,   341,   343,   342,   344,   344,
     345,   346,   347,   348,   350,   349,   352,   351,   353,   353,
     353,   354,   354,   356,   355,   358,   357,   360,   359,   362,
     361,   363,   363,   364,   364,   364,   366,   365,   367,   367,
     367,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   370,   369,   372,   371,
     374,   373,   376,   375,   378,   377,   379,   381,   380,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   392,   391,
     393,   393,   393,   394,   395,   397,   396,   399,   398,   401,
     400,   403,   402,   402,   402,   402,   402,   402,   405,   404,
     407,   406,   408,   408,   408,   409,   409,   409,   409,   409,
     410,   411,   412,   413,   414,   416,   415,   417,   417,   417,
     418,   418,   418,   418,   418,   418,   419,   420,   421,   423,
     422,   424,   424,   425,   425,   425,   427,   426,   429,   428,
     430,   430,   430,   430,   431,   431,   433,   432,   435,   434,
     437,   436,   438,   438,   438,   439,   439,   439,   439,   439,
     439,   440,   441,   442,   443,   444,   445,   447,   446,   448,
     448,   449,   449,   449,   451,   450,   453,   452,   454,   454,
     454,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   457,   456,   459,   458,   461,   460,
     463,   462,   465,   464,   467,   466,   469,   468,   470,   471,
     472,   473,   475,   474,   476,   476,   477,   477,   477,   479,
     478,   480,   480,   480,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     481,   481,   483,   482,   485,   484,   486,   486,   487,   487,
     487,   489,   488,   491,   490,   492,   492,   493,   493,   493,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     495,   496,   497,   499,   498,   501,   500,   503,   502,   504,
     506,   505,   507,   509,   508,   510,   510,   511,   511,   511,
     513,   512,   515,   514,   516,   516,   517,   517,   517,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     519,   521,   520,   522,   523,   524,   525,   526,   528,   527,
     530,   529,   531,   531,   532,   532,   532,   534,   533,   536,
     535,   537,   537,   537,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   540,   539,   541,
     543,   542,   545,   544,   547,   546,   548,   548,   549,   549,
     549,   551,   550,   553,   552,   554,   554,   555,   555,   555,
     556,   556,   556,   556,   556,   556,   556,   556,   556,   556,
     556,   556,   556,   556,   556,   558,   557,   560,   559,   562,
     561,   564,   563,   566,   565,   568,   567,   570,   569,   572,
     571,   574,   573,   576,   575,   578,   577,   580,   579,   581,
     583,   582,   585,   584,   586,   586,   587,   587,   587,   589,
     588,   590,   590,   591,   591,   591,   592,   592,   592,   592,
     592,   592,   592,   592,   592,   592,   592,   592,   592,   592,
     592,   592,   593,   595,   594,   597,   596,   598,   599,   601,
     600,   602,   602,   603,   603,   603,   605,   604,   606,   606,
     606,   607,   607,   607,   607,   607,   607,   607,   607,   607,
     607,   607,   607,   607,   609,   608,   610,   610,   610,   612,
     611,   614,   613,   615,   616,   618,   617,   619,   619,   620,
     620,   620,   622,   621,   623,   623,   623,   624,   624,   624,
     624,   624,   626,   625,   628,   627,   629,   629,   629,   630,
     630,   630,   630,   630,   630,   630,   632,   631,   633,   635,
     634,   637,   636,   639,   638,   640,   640,   641,   641,   641,
     643,   642,   644,   644,   644,   645,   645,   645,   645,   645,
     645,   645,   647,   646,   649,   648,   650,   650,   650,   651,
     651,   651,   651,   651,   651,   652,   654,   653,   655,   657,
     656,   659,   658,   661,   660,   662,   662,   662,   663,   663,
     663,   663,   663,   663,   663,   663,   663,   663,   663,   664,
     666,   665,   667,   669,   668,   670,   671,   673,   672,   674,
     674,   676,   675,   678,   677,   680,   679,   681,   681,   681,
     682,   682,   684,   683,   685,   687,   686,   688,   688,   688,
     690,   689,   691,   691,   691,   692,   692,   692,   692,   692,
     692,   692,   693,   695,   694,   697,   696,   698,   698,   698,
     700,   699,   701,   701,   701,   702,   702,   702,   702,   702,
     704,   703,   705,   706,   707,   709,   708,   711,   710,   712,
     712,   712,   713,   713,   713,   713,   713,   714,   715,   716,
     717
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
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       3,     0,     4,     1,     1,     1,     1,     3,     3,     3,
       3,     0,     4,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     3,     3,     3,     0,     6,     0,     6,     1,     3,
       2,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     1,     3,     2,
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     3,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     2,     1,
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
  "\"cert-file\"", "\"key-file\"", "\"ssl-mode\"", "\"disable\"",
  "\"prefer\"", "\"require\"", "\"verify-ca\"", "\"verify-full\"",
  "\"cipher-list\"", "\"valid-lifetime\"", "\"min-valid-lifetime\"",
  "\"max-valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
  "\"cache-threshold\"", "\"cache-max-age\"",
  "\"adaptive-lease-time-threshold\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"statistic-default-sample-count\"",
  "\"statistic-default-sample-age\"", "\"ddns-send-updates\"",
  "\"ddns-override-no-update\"", "\"ddns-override-client-update\"",
  "\"ddns-replace-client-name\"", "\"ddns-generated-prefix\"",
  "\"ddns-qualifying-suffix\"", "\"ddns-reverse-zone\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"ddns-ttl-percent\"", "\"ddns-ttl\"", "\"ddns-ttl-min\"",
  "\"ddns-ttl-max\"", "\"store-extended-info\"", "\"subnet4\"",
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
  "\"evaluate-additional-classes\"", "\"test\"", "\"template-test\"",
  "\"only-in-additional-list\"", "\"pool-id\"", "\"reservations\"",
  "\"ip-address\"", "\"duid\"", "\"hw-address\"", "\"circuit-id\"",
  "\"client-id\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-addresses\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
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
  "cache_max_age", "adaptive_lease_time_threshold",
  "decline_probation_period", "server_tag", "$@20", "parked_packet_limit",
  "allocator", "$@21", "echo_client_id", "match_client_id",
  "authoritative", "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@22",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@23",
  "ddns_qualifying_suffix", "$@24", "ddns_reverse_zone", "$@25",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "ddns_conflict_resolution_mode", "$@26",
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent", "ddns_ttl",
  "ddns_ttl_min", "ddns_ttl_max", "hostname_char_set", "$@27",
  "hostname_char_replacement", "$@28", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "offer_lifetime", "stash_agent_options",
  "interfaces_config", "$@29", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@30", "interfaces_list",
  "$@31", "dhcp_socket_type", "$@32", "socket_type", "outbound_interface",
  "$@33", "outbound_interface_value", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@34", "sanity_checks",
  "$@35", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@36", "extended_info_checks", "$@37", "hosts_database", "$@38",
  "hosts_databases", "$@39", "database_list", "not_empty_database_list",
  "database", "$@40", "database_map_params", "database_map_param",
  "database_type", "$@41", "user", "$@42", "password", "$@43",
  "password_file", "$@44", "host", "$@45", "port", "name", "$@46",
  "persist", "lfc_interval", "readonly", "connect_timeout", "read_timeout",
  "write_timeout", "tcp_user_timeout", "max_reconnect_tries",
  "reconnect_wait_time", "on_fail", "$@47", "on_fail_mode",
  "retry_on_startup", "max_row_errors", "trust_anchor", "$@48",
  "cert_file", "$@49", "key_file", "$@50", "ssl_mode", "$@51",
  "cipher_list", "$@52", "host_reservation_identifiers", "$@53",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@54", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@55", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@56",
  "sub_hooks_library", "$@57", "hooks_params", "hooks_param", "library",
  "$@58", "parameters", "$@59", "expired_leases_processing", "$@60",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@61",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@62",
  "sub_subnet4", "$@63", "subnet4_params", "subnet4_param", "subnet",
  "$@64", "subnet_4o6_interface", "$@65", "subnet_4o6_interface_id",
  "$@66", "subnet_4o6_subnet", "$@67", "interface", "$@68",
  "network_client_classes", "$@69", "evaluate_additional_classes", "$@70",
  "reservations_global", "reservations_in_subnet",
  "reservations_out_of_pool", "id", "shared_networks", "$@71",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@72", "shared_network_params", "shared_network_param",
  "option_def_list", "$@73", "sub_option_def_list", "$@74",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@75", "sub_option_def", "$@76",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@77",
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
  "$@108", "client_classes_list", "not_empty_classes_list",
  "client_class_entry", "$@109", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@110",
  "client_class_template_test", "$@111", "only_in_additional_list",
  "dhcp4o6_port", "control_sockets", "$@112", "control_socket_list",
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
  "$@126", "dhcp_queue_control", "$@127", "queue_control_params",
  "queue_control_param", "enable_queue", "queue_type", "$@128", "capacity",
  "arbitrary_map_entry", "$@129", "dhcp_ddns", "$@130", "sub_dhcp_ddns",
  "$@131", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "server_ip", "$@132", "server_port", "sender_ip", "$@133", "sender_port",
  "max_queue_size", "ncr_protocol", "$@134", "ncr_protocol_value",
  "ncr_format", "$@135", "config_control", "$@136", "sub_config_control",
  "$@137", "config_control_params", "config_control_param",
  "config_databases", "$@138", "config_fetch_wait_time", "loggers",
  "$@139", "loggers_entries", "logger_entry", "$@140", "logger_params",
  "logger_param", "debuglevel", "severity", "$@141", "output_options_list",
  "$@142", "output_options_list_content", "output_entry", "$@143",
  "output_params_list", "output_params", "output", "$@144", "flush",
  "maxsize", "maxver", "pattern", "$@145", "compatibility", "$@146",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   334,   334,   334,   335,   335,   336,   336,   337,   337,
     338,   338,   339,   339,   340,   340,   341,   341,   342,   342,
     343,   343,   344,   344,   345,   345,   346,   346,   354,   355,
     356,   357,   358,   359,   360,   363,   368,   368,   379,   382,
     383,   386,   391,   397,   402,   402,   409,   410,   413,   417,
     421,   427,   427,   434,   435,   438,   442,   446,   456,   465,
     465,   480,   480,   494,   497,   503,   503,   512,   513,   514,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   596,   602,   608,   614,   620,   626,   632,
     638,   644,   650,   656,   662,   668,   668,   677,   683,   683,
     692,   698,   704,   710,   716,   722,   728,   728,   737,   740,
     743,   746,   749,   755,   755,   764,   764,   773,   773,   782,
     791,   801,   801,   810,   813,   816,   819,   824,   830,   836,
     842,   848,   848,   857,   857,   866,   872,   878,   884,   890,
     896,   902,   908,   914,   914,   926,   927,   928,   933,   934,
     935,   936,   937,   938,   939,   940,   941,   942,   945,   945,
     954,   954,   965,   965,   973,   974,   977,   977,   985,   987,
     991,   997,  1003,  1009,  1015,  1015,  1028,  1028,  1039,  1040,
    1041,  1046,  1047,  1050,  1050,  1069,  1069,  1087,  1087,  1100,
    1100,  1111,  1112,  1115,  1116,  1117,  1122,  1122,  1132,  1133,
    1134,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,
    1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,
    1158,  1159,  1160,  1161,  1162,  1163,  1166,  1166,  1175,  1175,
    1184,  1184,  1193,  1193,  1202,  1202,  1211,  1217,  1217,  1226,
    1232,  1238,  1244,  1250,  1256,  1262,  1268,  1274,  1280,  1280,
    1288,  1289,  1290,  1293,  1299,  1305,  1305,  1314,  1314,  1323,
    1323,  1332,  1332,  1340,  1343,  1346,  1349,  1352,  1357,  1357,
    1366,  1366,  1377,  1378,  1379,  1384,  1385,  1386,  1387,  1388,
    1391,  1396,  1401,  1406,  1411,  1418,  1418,  1431,  1432,  1433,
    1438,  1439,  1440,  1441,  1442,  1443,  1446,  1452,  1458,  1464,
    1464,  1475,  1476,  1479,  1480,  1481,  1486,  1486,  1496,  1496,
    1506,  1507,  1508,  1511,  1514,  1515,  1518,  1518,  1527,  1527,
    1536,  1536,  1548,  1549,  1550,  1555,  1556,  1557,  1558,  1559,
    1560,  1563,  1569,  1575,  1581,  1587,  1593,  1602,  1602,  1616,
    1617,  1620,  1621,  1622,  1631,  1631,  1657,  1657,  1668,  1669,
    1670,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,
    1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,
    1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,
    1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,
    1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,  1723,  1724,
    1725,  1726,  1727,  1728,  1731,  1731,  1740,  1740,  1749,  1749,
    1758,  1758,  1767,  1767,  1777,  1777,  1788,  1788,  1799,  1805,
    1811,  1817,  1825,  1825,  1837,  1838,  1842,  1843,  1844,  1849,
    1849,  1857,  1858,  1859,  1864,  1865,  1866,  1867,  1868,  1869,
    1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,  1878,  1879,
    1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,  1888,  1889,
    1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,
    1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,  1908,  1909,
    1910,  1911,  1918,  1918,  1932,  1932,  1941,  1942,  1945,  1946,
    1947,  1954,  1954,  1969,  1969,  1983,  1984,  1987,  1988,  1989,
    1994,  1995,  1996,  1997,  1998,  1999,  2000,  2001,  2002,  2003,
    2006,  2008,  2014,  2016,  2016,  2025,  2025,  2034,  2034,  2043,
    2045,  2045,  2054,  2064,  2064,  2077,  2078,  2083,  2084,  2085,
    2092,  2092,  2104,  2104,  2116,  2117,  2122,  2123,  2124,  2131,
    2132,  2133,  2134,  2135,  2136,  2137,  2138,  2139,  2140,  2141,
    2144,  2146,  2146,  2155,  2157,  2159,  2165,  2171,  2177,  2177,
    2191,  2191,  2204,  2205,  2208,  2209,  2210,  2215,  2215,  2225,
    2225,  2235,  2236,  2237,  2242,  2243,  2244,  2245,  2246,  2247,
    2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,  2256,  2257,
    2258,  2259,  2260,  2261,  2262,  2263,  2264,  2267,  2267,  2276,
    2282,  2282,  2307,  2307,  2337,  2337,  2348,  2349,  2352,  2353,
    2354,  2359,  2359,  2368,  2368,  2377,  2378,  2381,  2382,  2383,
    2389,  2390,  2391,  2392,  2393,  2394,  2395,  2396,  2397,  2398,
    2399,  2400,  2401,  2402,  2403,  2406,  2406,  2415,  2415,  2424,
    2424,  2433,  2433,  2442,  2442,  2451,  2451,  2460,  2460,  2469,
    2469,  2478,  2478,  2487,  2487,  2496,  2496,  2510,  2510,  2521,
    2524,  2524,  2538,  2538,  2549,  2550,  2553,  2554,  2555,  2560,
    2560,  2570,  2571,  2574,  2575,  2576,  2581,  2582,  2583,  2584,
    2585,  2586,  2587,  2588,  2589,  2590,  2591,  2592,  2593,  2594,
    2595,  2596,  2599,  2601,  2601,  2610,  2610,  2619,  2627,  2635,
    2635,  2646,  2647,  2650,  2651,  2652,  2657,  2657,  2665,  2666,
    2667,  2672,  2673,  2674,  2675,  2676,  2677,  2678,  2679,  2680,
    2681,  2682,  2683,  2684,  2687,  2687,  2696,  2697,  2698,  2701,
    2701,  2710,  2710,  2719,  2725,  2731,  2731,  2742,  2743,  2746,
    2747,  2748,  2753,  2753,  2761,  2762,  2763,  2768,  2769,  2770,
    2771,  2772,  2775,  2775,  2786,  2786,  2799,  2800,  2801,  2806,
    2807,  2808,  2809,  2810,  2811,  2812,  2815,  2815,  2823,  2826,
    2826,  2835,  2835,  2844,  2844,  2855,  2856,  2859,  2860,  2861,
    2866,  2866,  2874,  2875,  2876,  2881,  2882,  2883,  2884,  2885,
    2886,  2887,  2890,  2890,  2901,  2901,  2914,  2915,  2916,  2921,
    2922,  2923,  2924,  2925,  2926,  2929,  2935,  2935,  2944,  2950,
    2950,  2960,  2960,  2973,  2973,  2983,  2984,  2985,  2990,  2991,
    2992,  2993,  2994,  2995,  2996,  2997,  2998,  2999,  3000,  3003,
    3009,  3009,  3018,  3024,  3024,  3033,  3039,  3045,  3045,  3054,
    3055,  3058,  3058,  3069,  3069,  3081,  3081,  3091,  3092,  3093,
    3099,  3100,  3103,  3103,  3114,  3122,  3122,  3135,  3136,  3137,
    3143,  3143,  3151,  3152,  3153,  3158,  3159,  3160,  3161,  3162,
    3163,  3164,  3167,  3173,  3173,  3182,  3182,  3193,  3194,  3195,
    3200,  3200,  3208,  3209,  3210,  3215,  3216,  3217,  3218,  3219,
    3222,  3222,  3231,  3237,  3243,  3249,  3249,  3258,  3258,  3269,
    3270,  3271,  3276,  3277,  3278,  3279,  3280,  3283,  3289,  3295,
    3301
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
#line 6951 "dhcp4_parser.cc"

#line 3307 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
