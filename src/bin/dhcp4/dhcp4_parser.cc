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
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 421 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 427 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 433 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 439 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 481 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 487 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 493 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 327 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 499 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 327 "dhcp4_parser.yy"
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
#line 336 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 788 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 337 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 794 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 338 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 800 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 339 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 806 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 340 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 812 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 341 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 818 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 342 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 824 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 343 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 830 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 344 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 836 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 345 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 842 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 346 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 848 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 347 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 854 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 348 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 860 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 356 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 357 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 358 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 359 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 360 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 890 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 361 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 362 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 902 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 365 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 911 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 370 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 375 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 932 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 381 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 938 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 388 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 393 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 959 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 399 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 967 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 404 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 976 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 407 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 984 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 415 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 993 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 419 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1002 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 423 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1010 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 429 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1018 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 431 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1027 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 440 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1036 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 444 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1045 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 448 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1053 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 458 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 467 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 472 "dhcp4_parser.yy"
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
#line 482 "dhcp4_parser.yy"
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
#line 491 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 499 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 505 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 509 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 516 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1148 "dhcp4_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 597 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1158 "dhcp4_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 603 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 609 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1178 "dhcp4_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 615 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 621 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 627 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 633 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1218 "dhcp4_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 639 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1228 "dhcp4_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 645 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 651 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 152: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 657 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 153: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 663 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 154: // $@20: %empty
#line 669 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 155: // server_tag: "server-tag" $@20 ":" "constant string"
#line 672 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 156: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 678 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 157: // $@21: %empty
#line 684 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 158: // allocator: "allocator" $@21 ":" "constant string"
#line 687 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 159: // echo_client_id: "echo-client-id" ":" "boolean"
#line 693 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 160: // match_client_id: "match-client-id" ":" "boolean"
#line 699 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 161: // authoritative: "authoritative" ":" "boolean"
#line 705 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 162: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 711 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 163: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 717 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 164: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 723 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 165: // $@22: %empty
#line 729 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 732 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "when-present"
#line 738 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1402 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "never"
#line 741 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1410 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "always"
#line 744 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1418 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "when-not-present"
#line 747 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1426 "dhcp4_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "boolean"
#line 750 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1435 "dhcp4_parser.cc"
    break;

  case 172: // $@23: %empty
#line 756 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 173: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 759 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc"
    break;

  case 174: // $@24: %empty
#line 765 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 175: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 768 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 176: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 774 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1483 "dhcp4_parser.cc"
    break;

  case 177: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 783 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1497 "dhcp4_parser.cc"
    break;

  case 178: // $@25: %empty
#line 793 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 796 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 802 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1523 "dhcp4_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 805 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1531 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 808 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1539 "dhcp4_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 811 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1547 "dhcp4_parser.cc"
    break;

  case 184: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 816 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 185: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 822 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1567 "dhcp4_parser.cc"
    break;

  case 186: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 828 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 187: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 834 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1587 "dhcp4_parser.cc"
    break;

  case 188: // $@26: %empty
#line 840 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 189: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 843 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 190: // $@27: %empty
#line 849 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 191: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 852 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 192: // store_extended_info: "store-extended-info" ":" "boolean"
#line 858 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1635 "dhcp4_parser.cc"
    break;

  case 193: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 864 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 194: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 870 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 195: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 876 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 196: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 882 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 197: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 888 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1685 "dhcp4_parser.cc"
    break;

  case 198: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 894 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1695 "dhcp4_parser.cc"
    break;

  case 199: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 900 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1705 "dhcp4_parser.cc"
    break;

  case 200: // $@28: %empty
#line 906 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 201: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 912 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 204: // interfaces_config_params: interfaces_config_params ","
#line 920 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1735 "dhcp4_parser.cc"
    break;

  case 215: // $@29: %empty
#line 937 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 216: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 941 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1754 "dhcp4_parser.cc"
    break;

  case 217: // $@30: %empty
#line 946 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp4_parser.cc"
    break;

  case 218: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 952 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc"
    break;

  case 219: // $@31: %empty
#line 957 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1784 "dhcp4_parser.cc"
    break;

  case 220: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 960 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc"
    break;

  case 221: // socket_type: "raw"
#line 965 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1799 "dhcp4_parser.cc"
    break;

  case 222: // socket_type: "udp"
#line 966 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1805 "dhcp4_parser.cc"
    break;

  case 223: // $@32: %empty
#line 969 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1814 "dhcp4_parser.cc"
    break;

  case 224: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 972 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1823 "dhcp4_parser.cc"
    break;

  case 225: // outbound_interface_value: "same-as-inbound"
#line 977 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1831 "dhcp4_parser.cc"
    break;

  case 226: // outbound_interface_value: "use-routing"
#line 979 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1839 "dhcp4_parser.cc"
    break;

  case 227: // re_detect: "re-detect" ":" "boolean"
#line 983 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1849 "dhcp4_parser.cc"
    break;

  case 228: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 989 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1859 "dhcp4_parser.cc"
    break;

  case 229: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 995 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 230: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1001 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 231: // $@33: %empty
#line 1007 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1891 "dhcp4_parser.cc"
    break;

  case 232: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 1013 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc"
    break;

  case 233: // $@34: %empty
#line 1020 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1914 "dhcp4_parser.cc"
    break;

  case 234: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 1026 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1923 "dhcp4_parser.cc"
    break;

  case 237: // sanity_checks_params: sanity_checks_params ","
#line 1033 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1931 "dhcp4_parser.cc"
    break;

  case 240: // $@35: %empty
#line 1042 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1940 "dhcp4_parser.cc"
    break;

  case 241: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1045 "dhcp4_parser.yy"
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
#line 1960 "dhcp4_parser.cc"
    break;

  case 242: // $@36: %empty
#line 1061 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp4_parser.cc"
    break;

  case 243: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1064 "dhcp4_parser.yy"
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
#line 1988 "dhcp4_parser.cc"
    break;

  case 244: // $@37: %empty
#line 1079 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 245: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1085 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 246: // $@38: %empty
#line 1092 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2023 "dhcp4_parser.cc"
    break;

  case 247: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1098 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 252: // not_empty_database_list: not_empty_database_list ","
#line 1109 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2040 "dhcp4_parser.cc"
    break;

  case 253: // $@39: %empty
#line 1114 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 254: // database: "{" $@39 database_map_params "}"
#line 1118 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 257: // database_map_params: database_map_params ","
#line 1126 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2068 "dhcp4_parser.cc"
    break;

  case 283: // $@40: %empty
#line 1158 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 284: // database_type: "type" $@40 ":" "constant string"
#line 1161 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2087 "dhcp4_parser.cc"
    break;

  case 285: // $@41: %empty
#line 1167 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 286: // user: "user" $@41 ":" "constant string"
#line 1170 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 287: // $@42: %empty
#line 1176 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 288: // password: "password" $@42 ":" "constant string"
#line 1179 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 289: // $@43: %empty
#line 1185 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 290: // password_file: "password-file" $@43 ":" "constant string"
#line 1188 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 291: // $@44: %empty
#line 1194 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2153 "dhcp4_parser.cc"
    break;

  case 292: // host: "host" $@44 ":" "constant string"
#line 1197 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 293: // port: "port" ":" "integer"
#line 1203 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1209 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 295: // name: "name" $@45 ":" "constant string"
#line 1212 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 296: // persist: "persist" ":" "boolean"
#line 1218 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 297: // lfc_interval: "lfc-interval" ":" "integer"
#line 1224 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 298: // readonly: "readonly" ":" "boolean"
#line 1230 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 299: // connect_timeout: "connect-timeout" ":" "integer"
#line 1236 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 300: // read_timeout: "read-timeout" ":" "integer"
#line 1242 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 301: // write_timeout: "write-timeout" ":" "integer"
#line 1248 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2252 "dhcp4_parser.cc"
    break;

  case 302: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1254 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2262 "dhcp4_parser.cc"
    break;

  case 303: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1260 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 304: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1266 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2282 "dhcp4_parser.cc"
    break;

  case 305: // $@46: %empty
#line 1272 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 306: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1275 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 307: // on_fail_mode: "stop-retry-exit"
#line 1280 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2306 "dhcp4_parser.cc"
    break;

  case 308: // on_fail_mode: "serve-retry-exit"
#line 1281 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2312 "dhcp4_parser.cc"
    break;

  case 309: // on_fail_mode: "serve-retry-continue"
#line 1282 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2318 "dhcp4_parser.cc"
    break;

  case 310: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1285 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 311: // max_row_errors: "max-row-errors" ":" "integer"
#line 1291 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2338 "dhcp4_parser.cc"
    break;

  case 312: // $@47: %empty
#line 1297 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 313: // trust_anchor: "trust-anchor" $@47 ":" "constant string"
#line 1300 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 314: // $@48: %empty
#line 1306 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 315: // cert_file: "cert-file" $@48 ":" "constant string"
#line 1309 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 316: // $@49: %empty
#line 1315 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 317: // key_file: "key-file" $@49 ":" "constant string"
#line 1318 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 318: // $@50: %empty
#line 1324 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2404 "dhcp4_parser.cc"
    break;

  case 319: // ssl_mode: "ssl-mode" $@50 ":" ssl_mode
#line 1327 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2413 "dhcp4_parser.cc"
    break;

  case 320: // ssl_mode: "disable"
#line 1332 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2421 "dhcp4_parser.cc"
    break;

  case 321: // ssl_mode: "prefer"
#line 1335 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2429 "dhcp4_parser.cc"
    break;

  case 322: // ssl_mode: "require"
#line 1338 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2437 "dhcp4_parser.cc"
    break;

  case 323: // ssl_mode: "verify-ca"
#line 1341 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2445 "dhcp4_parser.cc"
    break;

  case 324: // ssl_mode: "verify-full"
#line 1344 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2453 "dhcp4_parser.cc"
    break;

  case 325: // $@51: %empty
#line 1349 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2462 "dhcp4_parser.cc"
    break;

  case 326: // cipher_list: "cipher-list" $@51 ":" "constant string"
#line 1352 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 327: // $@52: %empty
#line 1358 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2484 "dhcp4_parser.cc"
    break;

  case 328: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1364 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2493 "dhcp4_parser.cc"
    break;

  case 331: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1371 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2501 "dhcp4_parser.cc"
    break;

  case 337: // duid_id: "duid"
#line 1383 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 338: // hw_address_id: "hw-address"
#line 1388 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 339: // circuit_id: "circuit-id"
#line 1393 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 340: // client_id: "client-id"
#line 1398 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2537 "dhcp4_parser.cc"
    break;

  case 341: // flex_id: "flex-id"
#line 1403 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2546 "dhcp4_parser.cc"
    break;

  case 342: // $@53: %empty
#line 1410 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 343: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1416 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 346: // multi_threading_params: multi_threading_params ","
#line 1425 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2577 "dhcp4_parser.cc"
    break;

  case 353: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1438 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 354: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1444 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 355: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1450 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2607 "dhcp4_parser.cc"
    break;

  case 356: // $@54: %empty
#line 1456 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2619 "dhcp4_parser.cc"
    break;

  case 357: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1462 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc"
    break;

  case 362: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1473 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2636 "dhcp4_parser.cc"
    break;

  case 363: // $@55: %empty
#line 1478 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2646 "dhcp4_parser.cc"
    break;

  case 364: // hooks_library: "{" $@55 hooks_params "}"
#line 1482 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2656 "dhcp4_parser.cc"
    break;

  case 365: // $@56: %empty
#line 1488 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2666 "dhcp4_parser.cc"
    break;

  case 366: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1492 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2676 "dhcp4_parser.cc"
    break;

  case 369: // hooks_params: hooks_params ","
#line 1500 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2684 "dhcp4_parser.cc"
    break;

  case 373: // $@57: %empty
#line 1510 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 374: // library: "library" $@57 ":" "constant string"
#line 1513 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2703 "dhcp4_parser.cc"
    break;

  case 375: // $@58: %empty
#line 1519 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 376: // parameters: "parameters" $@58 ":" map_value
#line 1522 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 377: // $@59: %empty
#line 1528 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2733 "dhcp4_parser.cc"
    break;

  case 378: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1534 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2743 "dhcp4_parser.cc"
    break;

  case 381: // expired_leases_params: expired_leases_params ","
#line 1542 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2751 "dhcp4_parser.cc"
    break;

  case 388: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1555 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2761 "dhcp4_parser.cc"
    break;

  case 389: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1561 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 390: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1567 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 391: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1573 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 392: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1579 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 393: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1585 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 394: // $@60: %empty
#line 1594 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 395: // subnet4_list: "subnet4" $@60 ":" "[" subnet4_list_content "]"
#line 1600 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2832 "dhcp4_parser.cc"
    break;

  case 400: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1614 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2840 "dhcp4_parser.cc"
    break;

  case 401: // $@61: %empty
#line 1623 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2850 "dhcp4_parser.cc"
    break;

  case 402: // subnet4: "{" $@61 subnet4_params "}"
#line 1627 "dhcp4_parser.yy"
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
#line 2876 "dhcp4_parser.cc"
    break;

  case 403: // $@62: %empty
#line 1649 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2886 "dhcp4_parser.cc"
    break;

  case 404: // sub_subnet4: "{" $@62 subnet4_params "}"
#line 1653 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2896 "dhcp4_parser.cc"
    break;

  case 407: // subnet4_params: subnet4_params ","
#line 1662 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2904 "dhcp4_parser.cc"
    break;

  case 462: // $@63: %empty
#line 1724 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2913 "dhcp4_parser.cc"
    break;

  case 463: // subnet: "subnet" $@63 ":" "constant string"
#line 1727 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 464: // $@64: %empty
#line 1733 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 465: // subnet_4o6_interface: "4o6-interface" $@64 ":" "constant string"
#line 1736 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 466: // $@65: %empty
#line 1742 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 467: // subnet_4o6_interface_id: "4o6-interface-id" $@65 ":" "constant string"
#line 1745 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 468: // $@66: %empty
#line 1751 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 469: // subnet_4o6_subnet: "4o6-subnet" $@66 ":" "constant string"
#line 1754 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 470: // $@67: %empty
#line 1760 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 471: // interface: "interface" $@67 ":" "constant string"
#line 1763 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 472: // $@68: %empty
#line 1769 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 473: // client_class: "client-class" $@68 ":" "constant string"
#line 1772 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 474: // $@69: %empty
#line 1779 "dhcp4_parser.yy"
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
#line 1785 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3039 "dhcp4_parser.cc"
    break;

  case 476: // $@70: %empty
#line 1791 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3051 "dhcp4_parser.cc"
    break;

  case 477: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1797 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3060 "dhcp4_parser.cc"
    break;

  case 478: // $@71: %empty
#line 1802 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 479: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1808 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 480: // reservations_global: "reservations-global" ":" "boolean"
#line 1813 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 481: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1819 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 482: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1825 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 483: // id: "id" ":" "integer"
#line 1831 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 484: // $@72: %empty
#line 1839 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3133 "dhcp4_parser.cc"
    break;

  case 485: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1845 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 490: // shared_networks_list: shared_networks_list ","
#line 1858 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3150 "dhcp4_parser.cc"
    break;

  case 491: // $@73: %empty
#line 1863 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 492: // shared_network: "{" $@73 shared_network_params "}"
#line 1867 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3168 "dhcp4_parser.cc"
    break;

  case 495: // shared_network_params: shared_network_params ","
#line 1873 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3176 "dhcp4_parser.cc"
    break;

  case 545: // $@74: %empty
#line 1933 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 546: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1939 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 547: // $@75: %empty
#line 1947 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 548: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1950 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 553: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1962 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3222 "dhcp4_parser.cc"
    break;

  case 554: // $@76: %empty
#line 1969 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3232 "dhcp4_parser.cc"
    break;

  case 555: // option_def_entry: "{" $@76 option_def_params "}"
#line 1973 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 556: // $@77: %empty
#line 1984 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 557: // sub_option_def: "{" $@77 option_def_params "}"
#line 1988 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3266 "dhcp4_parser.cc"
    break;

  case 562: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2004 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3274 "dhcp4_parser.cc"
    break;

  case 574: // code: "code" ":" "integer"
#line 2023 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 576: // $@78: %empty
#line 2031 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 577: // option_def_type: "type" $@78 ":" "constant string"
#line 2034 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 578: // $@79: %empty
#line 2040 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 579: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2043 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 580: // $@80: %empty
#line 2049 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc"
    break;

  case 581: // space: "space" $@80 ":" "constant string"
#line 2052 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 583: // $@81: %empty
#line 2060 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 584: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2063 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3360 "dhcp4_parser.cc"
    break;

  case 585: // option_def_array: "array" ":" "boolean"
#line 2069 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3370 "dhcp4_parser.cc"
    break;

  case 586: // $@82: %empty
#line 2079 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3382 "dhcp4_parser.cc"
    break;

  case 587: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2085 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3391 "dhcp4_parser.cc"
    break;

  case 592: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2100 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3399 "dhcp4_parser.cc"
    break;

  case 593: // $@83: %empty
#line 2107 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3409 "dhcp4_parser.cc"
    break;

  case 594: // option_data_entry: "{" $@83 option_data_params "}"
#line 2111 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 595: // $@84: %empty
#line 2119 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3428 "dhcp4_parser.cc"
    break;

  case 596: // sub_option_data: "{" $@84 option_data_params "}"
#line 2123 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3437 "dhcp4_parser.cc"
    break;

  case 601: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2139 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3445 "dhcp4_parser.cc"
    break;

  case 614: // $@85: %empty
#line 2161 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 615: // option_data_data: "data" $@85 ":" "constant string"
#line 2164 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3464 "dhcp4_parser.cc"
    break;

  case 618: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2174 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3474 "dhcp4_parser.cc"
    break;

  case 619: // option_data_always_send: "always-send" ":" "boolean"
#line 2180 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3484 "dhcp4_parser.cc"
    break;

  case 620: // option_data_never_send: "never-send" ":" "boolean"
#line 2186 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 621: // $@86: %empty
#line 2192 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 622: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2198 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 623: // $@87: %empty
#line 2206 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3527 "dhcp4_parser.cc"
    break;

  case 624: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2212 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3536 "dhcp4_parser.cc"
    break;

  case 629: // not_empty_pools_list: not_empty_pools_list ","
#line 2225 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3544 "dhcp4_parser.cc"
    break;

  case 630: // $@88: %empty
#line 2230 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 631: // pool_list_entry: "{" $@88 pool_params "}"
#line 2234 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 632: // $@89: %empty
#line 2240 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 633: // sub_pool4: "{" $@89 pool_params "}"
#line 2244 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 636: // pool_params: pool_params ","
#line 2252 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3592 "dhcp4_parser.cc"
    break;

  case 661: // $@90: %empty
#line 2283 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 662: // pool_entry: "pool" $@90 ":" "constant string"
#line 2286 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 663: // pool_id: "pool-id" ":" "integer"
#line 2292 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 664: // $@91: %empty
#line 2298 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3629 "dhcp4_parser.cc"
    break;

  case 665: // user_context: "user-context" $@91 ":" map_value
#line 2300 "dhcp4_parser.yy"
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
#line 3656 "dhcp4_parser.cc"
    break;

  case 666: // $@92: %empty
#line 2323 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 667: // comment: "comment" $@92 ":" "constant string"
#line 2325 "dhcp4_parser.yy"
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
#line 3693 "dhcp4_parser.cc"
    break;

  case 668: // $@93: %empty
#line 2353 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3705 "dhcp4_parser.cc"
    break;

  case 669: // reservations: "reservations" $@93 ":" "[" reservations_list "]"
#line 2359 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 674: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2370 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3722 "dhcp4_parser.cc"
    break;

  case 675: // $@94: %empty
#line 2375 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 676: // reservation: "{" $@94 reservation_params "}"
#line 2379 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 677: // $@95: %empty
#line 2384 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 678: // sub_reservation: "{" $@95 reservation_params "}"
#line 2388 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 683: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2399 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3768 "dhcp4_parser.cc"
    break;

  case 699: // $@96: %empty
#line 2422 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 700: // next_server: "next-server" $@96 ":" "constant string"
#line 2425 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3787 "dhcp4_parser.cc"
    break;

  case 701: // $@97: %empty
#line 2431 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 702: // server_hostname: "server-hostname" $@97 ":" "constant string"
#line 2434 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 703: // $@98: %empty
#line 2440 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 704: // boot_file_name: "boot-file-name" $@98 ":" "constant string"
#line 2443 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 705: // $@99: %empty
#line 2449 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 706: // ip_address: "ip-address" $@99 ":" "constant string"
#line 2452 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 707: // $@100: %empty
#line 2458 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 708: // duid: "duid" $@100 ":" "constant string"
#line 2461 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 709: // $@101: %empty
#line 2467 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 710: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2470 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 711: // $@102: %empty
#line 2476 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 712: // client_id_value: "client-id" $@102 ":" "constant string"
#line 2479 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 713: // $@103: %empty
#line 2485 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 714: // circuit_id_value: "circuit-id" $@103 ":" "constant string"
#line 2488 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3920 "dhcp4_parser.cc"
    break;

  case 715: // $@104: %empty
#line 2494 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 716: // flex_id_value: "flex-id" $@104 ":" "constant string"
#line 2497 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3939 "dhcp4_parser.cc"
    break;

  case 717: // $@105: %empty
#line 2503 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3948 "dhcp4_parser.cc"
    break;

  case 718: // hostname: "hostname" $@105 ":" "constant string"
#line 2506 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 719: // $@106: %empty
#line 2512 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3970 "dhcp4_parser.cc"
    break;

  case 720: // reservation_client_classes: "client-classes" $@106 ":" list_strings
#line 2518 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3979 "dhcp4_parser.cc"
    break;

  case 721: // $@107: %empty
#line 2526 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3991 "dhcp4_parser.cc"
    break;

  case 722: // relay: "relay" $@107 ":" "{" relay_map "}"
#line 2532 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4000 "dhcp4_parser.cc"
    break;

  case 724: // $@108: %empty
#line 2540 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4012 "dhcp4_parser.cc"
    break;

  case 725: // ip_addresses: "ip-addresses" $@108 ":" list_strings
#line 2546 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 726: // $@109: %empty
#line 2554 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4033 "dhcp4_parser.cc"
    break;

  case 727: // client_classes: "client-classes" $@109 ":" "[" client_classes_list "]"
#line 2560 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 732: // not_empty_classes_list: not_empty_classes_list ","
#line 2571 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4050 "dhcp4_parser.cc"
    break;

  case 733: // $@110: %empty
#line 2576 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4060 "dhcp4_parser.cc"
    break;

  case 734: // client_class_entry: "{" $@110 client_class_params "}"
#line 2580 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4070 "dhcp4_parser.cc"
    break;

  case 739: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2592 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4078 "dhcp4_parser.cc"
    break;

  case 758: // $@111: %empty
#line 2618 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 759: // client_class_test: "test" $@111 ":" "constant string"
#line 2621 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 760: // $@112: %empty
#line 2627 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4106 "dhcp4_parser.cc"
    break;

  case 761: // client_class_template_test: "template-test" $@112 ":" "constant string"
#line 2630 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4116 "dhcp4_parser.cc"
    break;

  case 762: // only_if_required: "only-if-required" ":" "boolean"
#line 2637 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4126 "dhcp4_parser.cc"
    break;

  case 763: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2643 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4136 "dhcp4_parser.cc"
    break;

  case 764: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2651 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4146 "dhcp4_parser.cc"
    break;

  case 765: // $@113: %empty
#line 2659 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 766: // control_sockets: "control-sockets" $@113 ":" "[" control_socket_list "]"
#line 2665 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 771: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2676 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4175 "dhcp4_parser.cc"
    break;

  case 772: // $@114: %empty
#line 2681 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4185 "dhcp4_parser.cc"
    break;

  case 773: // control_socket_entry: "{" $@114 control_socket_params "}"
#line 2685 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4193 "dhcp4_parser.cc"
    break;

  case 776: // control_socket_params: control_socket_params ","
#line 2691 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4201 "dhcp4_parser.cc"
    break;

  case 790: // $@115: %empty
#line 2711 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4210 "dhcp4_parser.cc"
    break;

  case 791: // control_socket_type: "socket-type" $@115 ":" control_socket_type_value
#line 2714 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4219 "dhcp4_parser.cc"
    break;

  case 792: // control_socket_type_value: "unix"
#line 2720 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4225 "dhcp4_parser.cc"
    break;

  case 793: // control_socket_type_value: "http"
#line 2721 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4231 "dhcp4_parser.cc"
    break;

  case 794: // control_socket_type_value: "https"
#line 2722 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4237 "dhcp4_parser.cc"
    break;

  case 795: // $@116: %empty
#line 2725 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 796: // control_socket_name: "socket-name" $@116 ":" "constant string"
#line 2728 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 797: // $@117: %empty
#line 2734 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4265 "dhcp4_parser.cc"
    break;

  case 798: // control_socket_address: "socket-address" $@117 ":" "constant string"
#line 2737 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4275 "dhcp4_parser.cc"
    break;

  case 799: // control_socket_port: "socket-port" ":" "integer"
#line 2743 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4285 "dhcp4_parser.cc"
    break;

  case 800: // cert_required: "cert-required" ":" "boolean"
#line 2749 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4295 "dhcp4_parser.cc"
    break;

  case 801: // $@118: %empty
#line 2755 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4307 "dhcp4_parser.cc"
    break;

  case 802: // http_headers: "http-headers" $@118 ":" "[" http_header_list "]"
#line 2761 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4316 "dhcp4_parser.cc"
    break;

  case 807: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2772 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4324 "dhcp4_parser.cc"
    break;

  case 808: // $@119: %empty
#line 2777 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4334 "dhcp4_parser.cc"
    break;

  case 809: // http_header: "{" $@119 http_header_params "}"
#line 2781 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4342 "dhcp4_parser.cc"
    break;

  case 812: // http_header_params: http_header_params ","
#line 2787 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4350 "dhcp4_parser.cc"
    break;

  case 818: // $@120: %empty
#line 2799 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4359 "dhcp4_parser.cc"
    break;

  case 819: // header_value: "value" $@120 ":" "constant string"
#line 2802 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4369 "dhcp4_parser.cc"
    break;

  case 820: // $@121: %empty
#line 2810 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4381 "dhcp4_parser.cc"
    break;

  case 821: // authentication: "authentication" $@121 ":" "{" auth_params "}"
#line 2816 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4392 "dhcp4_parser.cc"
    break;

  case 824: // auth_params: auth_params ","
#line 2825 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4400 "dhcp4_parser.cc"
    break;

  case 832: // $@122: %empty
#line 2839 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4409 "dhcp4_parser.cc"
    break;

  case 833: // auth_type: "type" $@122 ":" auth_type_value
#line 2842 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4418 "dhcp4_parser.cc"
    break;

  case 834: // auth_type_value: "basic"
#line 2847 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4424 "dhcp4_parser.cc"
    break;

  case 835: // $@123: %empty
#line 2850 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4433 "dhcp4_parser.cc"
    break;

  case 836: // realm: "realm" $@123 ":" "constant string"
#line 2853 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4443 "dhcp4_parser.cc"
    break;

  case 837: // $@124: %empty
#line 2859 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4452 "dhcp4_parser.cc"
    break;

  case 838: // directory: "directory" $@124 ":" "constant string"
#line 2862 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4462 "dhcp4_parser.cc"
    break;

  case 839: // $@125: %empty
#line 2868 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4474 "dhcp4_parser.cc"
    break;

  case 840: // clients: "clients" $@125 ":" "[" clients_list "]"
#line 2874 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 845: // not_empty_clients_list: not_empty_clients_list ","
#line 2885 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4491 "dhcp4_parser.cc"
    break;

  case 846: // $@126: %empty
#line 2890 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4501 "dhcp4_parser.cc"
    break;

  case 847: // basic_auth: "{" $@126 clients_params "}"
#line 2894 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4509 "dhcp4_parser.cc"
    break;

  case 850: // clients_params: clients_params ","
#line 2900 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4517 "dhcp4_parser.cc"
    break;

  case 858: // $@127: %empty
#line 2914 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4526 "dhcp4_parser.cc"
    break;

  case 859: // user_file: "user-file" $@127 ":" "constant string"
#line 2917 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4536 "dhcp4_parser.cc"
    break;

  case 860: // $@128: %empty
#line 2925 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4548 "dhcp4_parser.cc"
    break;

  case 861: // dhcp_queue_control: "dhcp-queue-control" $@128 ":" "{" queue_control_params "}"
#line 2931 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 864: // queue_control_params: queue_control_params ","
#line 2940 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4567 "dhcp4_parser.cc"
    break;

  case 871: // enable_queue: "enable-queue" ":" "boolean"
#line 2953 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4577 "dhcp4_parser.cc"
    break;

  case 872: // $@129: %empty
#line 2959 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4586 "dhcp4_parser.cc"
    break;

  case 873: // queue_type: "queue-type" $@129 ":" "constant string"
#line 2962 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4596 "dhcp4_parser.cc"
    break;

  case 874: // capacity: "capacity" ":" "integer"
#line 2968 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4606 "dhcp4_parser.cc"
    break;

  case 875: // $@130: %empty
#line 2974 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4615 "dhcp4_parser.cc"
    break;

  case 876: // arbitrary_map_entry: "constant string" $@130 ":" value
#line 2977 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4624 "dhcp4_parser.cc"
    break;

  case 877: // $@131: %empty
#line 2984 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4636 "dhcp4_parser.cc"
    break;

  case 878: // dhcp_ddns: "dhcp-ddns" $@131 ":" "{" dhcp_ddns_params "}"
#line 2990 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 879: // $@132: %empty
#line 2997 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4657 "dhcp4_parser.cc"
    break;

  case 880: // sub_dhcp_ddns: "{" $@132 dhcp_ddns_params "}"
#line 3001 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4667 "dhcp4_parser.cc"
    break;

  case 883: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3009 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4675 "dhcp4_parser.cc"
    break;

  case 895: // enable_updates: "enable-updates" ":" "boolean"
#line 3027 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4685 "dhcp4_parser.cc"
    break;

  case 896: // $@133: %empty
#line 3033 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4694 "dhcp4_parser.cc"
    break;

  case 897: // server_ip: "server-ip" $@133 ":" "constant string"
#line 3036 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4704 "dhcp4_parser.cc"
    break;

  case 898: // server_port: "server-port" ":" "integer"
#line 3042 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4714 "dhcp4_parser.cc"
    break;

  case 899: // $@134: %empty
#line 3048 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4723 "dhcp4_parser.cc"
    break;

  case 900: // sender_ip: "sender-ip" $@134 ":" "constant string"
#line 3051 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4733 "dhcp4_parser.cc"
    break;

  case 901: // sender_port: "sender-port" ":" "integer"
#line 3057 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4743 "dhcp4_parser.cc"
    break;

  case 902: // max_queue_size: "max-queue-size" ":" "integer"
#line 3063 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4753 "dhcp4_parser.cc"
    break;

  case 903: // $@135: %empty
#line 3069 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4762 "dhcp4_parser.cc"
    break;

  case 904: // ncr_protocol: "ncr-protocol" $@135 ":" ncr_protocol_value
#line 3072 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4771 "dhcp4_parser.cc"
    break;

  case 905: // ncr_protocol_value: "udp"
#line 3078 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4777 "dhcp4_parser.cc"
    break;

  case 906: // ncr_protocol_value: "tcp"
#line 3079 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4783 "dhcp4_parser.cc"
    break;

  case 907: // $@136: %empty
#line 3082 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4792 "dhcp4_parser.cc"
    break;

  case 908: // ncr_format: "ncr-format" $@136 ":" "JSON"
#line 3085 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4802 "dhcp4_parser.cc"
    break;

  case 909: // $@137: %empty
#line 3093 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4814 "dhcp4_parser.cc"
    break;

  case 910: // config_control: "config-control" $@137 ":" "{" config_control_params "}"
#line 3099 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4824 "dhcp4_parser.cc"
    break;

  case 911: // $@138: %empty
#line 3105 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4834 "dhcp4_parser.cc"
    break;

  case 912: // sub_config_control: "{" $@138 config_control_params "}"
#line 3109 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4843 "dhcp4_parser.cc"
    break;

  case 915: // config_control_params: config_control_params ","
#line 3117 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4851 "dhcp4_parser.cc"
    break;

  case 918: // $@139: %empty
#line 3127 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4863 "dhcp4_parser.cc"
    break;

  case 919: // config_databases: "config-databases" $@139 ":" "[" database_list "]"
#line 3133 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4872 "dhcp4_parser.cc"
    break;

  case 920: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3138 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4882 "dhcp4_parser.cc"
    break;

  case 921: // $@140: %empty
#line 3146 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4894 "dhcp4_parser.cc"
    break;

  case 922: // loggers: "loggers" $@140 ":" "[" loggers_entries "]"
#line 3152 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4903 "dhcp4_parser.cc"
    break;

  case 925: // loggers_entries: loggers_entries ","
#line 3161 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4911 "dhcp4_parser.cc"
    break;

  case 926: // $@141: %empty
#line 3167 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4921 "dhcp4_parser.cc"
    break;

  case 927: // logger_entry: "{" $@141 logger_params "}"
#line 3171 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4929 "dhcp4_parser.cc"
    break;

  case 930: // logger_params: logger_params ","
#line 3177 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4937 "dhcp4_parser.cc"
    break;

  case 938: // debuglevel: "debuglevel" ":" "integer"
#line 3191 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4947 "dhcp4_parser.cc"
    break;

  case 939: // $@142: %empty
#line 3197 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4956 "dhcp4_parser.cc"
    break;

  case 940: // severity: "severity" $@142 ":" "constant string"
#line 3200 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4966 "dhcp4_parser.cc"
    break;

  case 941: // $@143: %empty
#line 3206 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4978 "dhcp4_parser.cc"
    break;

  case 942: // output_options_list: "output-options" $@143 ":" "[" output_options_list_content "]"
#line 3212 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4987 "dhcp4_parser.cc"
    break;

  case 945: // output_options_list_content: output_options_list_content ","
#line 3219 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4995 "dhcp4_parser.cc"
    break;

  case 946: // $@144: %empty
#line 3224 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5005 "dhcp4_parser.cc"
    break;

  case 947: // output_entry: "{" $@144 output_params_list "}"
#line 3228 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5013 "dhcp4_parser.cc"
    break;

  case 950: // output_params_list: output_params_list ","
#line 3234 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5021 "dhcp4_parser.cc"
    break;

  case 956: // $@145: %empty
#line 3246 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5030 "dhcp4_parser.cc"
    break;

  case 957: // output: "output" $@145 ":" "constant string"
#line 3249 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5040 "dhcp4_parser.cc"
    break;

  case 958: // flush: "flush" ":" "boolean"
#line 3255 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5050 "dhcp4_parser.cc"
    break;

  case 959: // maxsize: "maxsize" ":" "integer"
#line 3261 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5060 "dhcp4_parser.cc"
    break;

  case 960: // maxver: "maxver" ":" "integer"
#line 3267 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5070 "dhcp4_parser.cc"
    break;

  case 961: // $@146: %empty
#line 3273 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5079 "dhcp4_parser.cc"
    break;

  case 962: // pattern: "pattern" $@146 ":" "constant string"
#line 3276 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5089 "dhcp4_parser.cc"
    break;

  case 963: // $@147: %empty
#line 3282 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5101 "dhcp4_parser.cc"
    break;

  case 964: // compatibility: "compatibility" $@147 ":" "{" compatibility_params "}"
#line 3288 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5110 "dhcp4_parser.cc"
    break;

  case 967: // compatibility_params: compatibility_params ","
#line 3295 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5118 "dhcp4_parser.cc"
    break;

  case 973: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3307 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5128 "dhcp4_parser.cc"
    break;

  case 974: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3313 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5138 "dhcp4_parser.cc"
    break;

  case 975: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3319 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5148 "dhcp4_parser.cc"
    break;

  case 976: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3325 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5158 "dhcp4_parser.cc"
    break;


#line 5162 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1423;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     612, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423,    36,    52,    64,    69,    71,    76,
      96,   106,   119,   129,   181,   207,   218,   233, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423,    52,  -151,   254,   248,   170,   676,
    1360,    73,    -5,   123,   466,  -115,   662,   134, -1423,    84,
     264,   269,   267,   289, -1423,    40, -1423, -1423, -1423, -1423,
     311,   354,   356, -1423, -1423, -1423,   370,   391, -1423, -1423,
   -1423,   393,   394,   401,   412,   413,   418,   419,   423,   426,
     427,   428,   430, -1423,   431,   432,   440,   441,   458, -1423,
   -1423, -1423,   459,   460,   461,   464,   465,   468,   471, -1423,
   -1423, -1423,   473, -1423, -1423, -1423, -1423, -1423,   474,   475,
     476, -1423, -1423, -1423, -1423, -1423,   477, -1423, -1423, -1423,
   -1423, -1423, -1423,   479,   481,   482, -1423, -1423,   483, -1423,
      50, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,   484,   485,   487,   489,
   -1423,    72, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   491, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,    79, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423,   494, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423,    83, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
     305,   346, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423,   462, -1423, -1423,   495, -1423, -1423,
   -1423,   496, -1423, -1423,   493,   406, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   500,
     503,   504, -1423, -1423, -1423, -1423, -1423,   501,   508, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423,   111, -1423, -1423, -1423,   509, -1423,   510,
   -1423,   512,   515, -1423, -1423, -1423, -1423, -1423,   112, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   516,
     162, -1423, -1423, -1423, -1423,    52,    52, -1423,   276,   519,
   -1423, -1423,   520,   523,   524,   291,   293,   295,   536,   538,
     540,   310,   306,   542,   545,   546,   317,   318,   319,   323,
     324,   320,   325,   326,   328,   330,   339,   342,   558,   349,
     350,   355,   357,   362,   577,   579,   589,   363,   364,   359,
     368,   369,   372,   374,   591,   603,   607,   386,   614,   624,
     626,   629,   630,   399,   403,   407,   631,   636,   649,   652,
     654,   422,   657,   658,   659,   660,   664,   665,   434,   435,
     436,   666,   667, -1423,   248, -1423,   672,   673,   674,   442,
     444,   429,   448,   170, -1423,   682,   684,   686,   687,   689,
     690,   463,   691,   692,   693,   695,   697,   676, -1423,   699,
     467,  1360, -1423,   701,   708,   709,   710,   711,   712,   714,
     715, -1423,    73, -1423,   717,   718,   486,   721,   722,   723,
     490, -1423,   123,   724,   492,   498,   499,   726, -1423,   466,
     728,   730,    51, -1423,   502,   735,   505,   736,   506,   507,
     753,   754,   662, -1423,   755,   537,   134, -1423, -1423, -1423,
     756,   771,   774,   777,   778, -1423, -1423, -1423,   552,   553,
     554, -1423, -1423,   786,   787,   790, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   560, -1423,
   -1423, -1423, -1423, -1423,  -108,   561,   563, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423,   803,   807,   808, -1423,   578,   331,
     810,   812,   581, -1423, -1423, -1423,   815,   816,   817,   818,
     820, -1423,   821,   819,   841,   842,   615,   625, -1423, -1423,
   -1423,   845,   853, -1423,   857,   215,   347, -1423, -1423, -1423,
   -1423, -1423,   627,   628,   632,   860,   646,   647, -1423,   857,
     857,   857,   663,   859, -1423,   668, -1423, -1423,   857,   669,
     670,   671,   675,   677,   680,   681, -1423,   683,   685, -1423,
     700,   702,   704, -1423, -1423,   705, -1423, -1423, -1423,   857,
   -1423,   706,   812, -1423, -1423,   707, -1423,   716, -1423, -1423,
      13,   719, -1423,   862, -1423, -1423,    52,   248,   134,   170,
     348, -1423, -1423, -1423,  1174,  1174,   893, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,   894,   901,   902, -1423,
   -1423, -1423, -1423, -1423, -1423,   903, -1423, -1423, -1423,   152,
     913,   915,   918,   282,   -23,   920,   -78,   662, -1423, -1423,
     924,   -12, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423,   928, -1423, -1423, -1423, -1423, -1423, -1423,
     793, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423,   893, -1423,   165,   172,   175,
   -1423, -1423,   220, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
     933,   941,   942,   943,   944,   946,   947,   949,   950,   951,
   -1423,   952,   953, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423,   223, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423,   238, -1423,   954,   822, -1423, -1423,   955,   956, -1423,
   -1423,   957,   959, -1423, -1423,   958,   962, -1423, -1423,   960,
     964, -1423, -1423, -1423, -1423, -1423, -1423,   168, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423,   963,   965, -1423, -1423,   966,
     967, -1423, -1423,   968,   970, -1423,   971,   972,   973,   974,
     975,   977,   255, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
     978,   980,   981, -1423,   257, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423,   982,   984, -1423,   986, -1423,   989, -1423, -1423,
   -1423,   258, -1423, -1423, -1423, -1423, -1423,   302, -1423,   184,
   -1423,   991,  1007,  1016,  1019, -1423,   308, -1423, -1423, -1423,
   -1423, -1423,   788, -1423,  1023,  1031, -1423, -1423,  1029, -1423,
    1039, -1423, -1423, -1423,  1044,  1047,   348, -1423,  1054,  1058,
    1059,  1061,   734,   827,   830,   832,   838,   839,   844,   847,
     851,   858,  1093,   867,   861,  1104,  1109,  1114,  1116,  1119,
    1121,  1174, -1423, -1423,  1174, -1423,   893,   676, -1423,   894,
     123, -1423,   901,   466, -1423,   902,   799, -1423,   903,   152,
   -1423,   322, -1423,   913,    73, -1423,   915,  -115, -1423,   918,
     891,   895,   896,   898,   904,   930,   282, -1423,   922,   935,
     939,   -23, -1423,   246, -1423,   920,   945,  1126,   961,  1177,
     -78, -1423, -1423,   261,   924, -1423,   969,   990,   992,  1006,
     -12, -1423, -1423,  1176,  1186,  1360, -1423,   928,  1187, -1423,
   -1423,   994,  1011, -1423,  1012,  1013,  1014,  1018, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   247, -1423,
   -1423,  1021,  1022,  1026,   186,  1028,  1030, -1423,   309, -1423,
     344, -1423,  1182, -1423,  1185, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   345, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423,  1190,  1192, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,  1189,  1196, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423,  1193, -1423,   358, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423,  1198, -1423,  1199, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423,   379, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423,  1033, -1423,    52, -1423, -1423,  1200,
   -1423, -1423, -1423, -1423, -1423,   380, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423,  1034,   381, -1423,
     857, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423,   799, -1423,  1201,  1202,  1020,  1032, -1423,   322, -1423,
   -1423,  1203,  1205,  1206,   976,  1207,  1035,  1248,   246, -1423,
   -1423, -1423,  1251,  1036,  1261,   261, -1423, -1423, -1423, -1423,
   -1423,  1045,  1046, -1423, -1423, -1423,   -16,  1049,  1051, -1423,
    1273, -1423,  1195, -1423,  1283, -1423,  1053, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,    78,  1285,  1286, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423,   388, -1423, -1423,
   -1423, -1423, -1423, -1423,  1284,  1291, -1423, -1423,   209, -1423,
    1292,  1293,  1296,  1297,    78, -1423,   -36, -1423,  1285,    28,
    1286, -1423,   782,  1066,  1067,  1290, -1423, -1423, -1423, -1423,
   -1423, -1423,   396, -1423, -1423, -1423, -1423,  1300,  1301,  1302,
   -1423,   404, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423,  1303,  1304,   -36, -1423,  1305,  1073,  1076,
    1079,  1313,    28, -1423, -1423,  1314,  1318, -1423,  1086, -1423,
    1089, -1423, -1423, -1423,  1092, -1423,    57, -1423,  1303, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   405,
   -1423, -1423, -1423,  1328,    57, -1423,  1097, -1423, -1423
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   215,     9,   403,    11,   632,    13,
     677,    15,   547,    17,   556,    19,   595,    21,   365,    23,
     879,    25,   911,    27,    46,    39,     0,     0,     0,     0,
       0,   679,     0,   558,   597,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   909,   200,   233,
       0,     0,     0,   699,   701,   703,     0,     0,   231,   244,
     246,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,     0,     0,     0,     0,     0,   165,
     172,   174,     0,     0,     0,     0,     0,     0,     0,   394,
     545,   586,     0,   157,   178,   484,   664,   666,     0,     0,
       0,   327,   726,   668,   356,   377,     0,   342,   765,   860,
     877,   188,   190,     0,     0,     0,   921,   963,     0,   141,
       0,    67,    70,    71,    72,    73,    74,   107,   108,   109,
     110,   111,   112,    75,   103,   137,   138,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   114,   115,   129,   130,   131,   133,   134,
     135,   139,   140,    78,    79,   100,    80,    81,    82,   132,
      86,    87,    76,   104,   105,   106,    77,    84,    85,    98,
      99,   101,    95,    96,    97,    83,    88,    89,    90,    91,
     102,   113,   136,   217,   219,   223,     0,     0,     0,     0,
     214,     0,   202,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   464,   466,   468,   623,   462,   470,     0,   474,
     476,   478,   472,   721,   461,   408,   409,   410,   411,   412,
     437,   438,   439,   440,   441,   442,   459,   427,   428,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   460,     0,   405,   415,   432,
     433,   434,   416,   418,   419,   420,   421,   423,   424,   425,
     417,   413,   414,   435,   436,   422,   429,   430,   431,   426,
     661,     0,   660,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   640,   641,   642,
     643,   639,     0,   634,   637,   638,   658,   659,   719,   705,
     707,   709,   713,   711,   717,   715,   698,   692,   696,   697,
       0,   680,   681,   693,   694,   695,   689,   684,   690,   686,
     687,   688,   691,   685,     0,   576,   294,     0,   580,   578,
     583,     0,   572,   573,     0,   559,   560,   563,   575,   564,
     565,   566,   582,   567,   568,   569,   570,   571,   614,     0,
       0,     0,   621,   612,   613,   616,   617,     0,   598,   599,
     602,   603,   604,   605,   606,   607,   608,   611,   609,   610,
     373,   375,   370,     0,   367,   371,   372,     0,   896,     0,
     899,     0,     0,   903,   907,   894,   892,   893,     0,   881,
     884,   885,   886,   887,   888,   889,   890,   891,   918,     0,
       0,   913,   916,   917,    45,    50,     0,    37,    43,     0,
      64,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    69,    66,     0,     0,     0,     0,
       0,     0,     0,   204,   216,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   407,   404,     0,
       0,   636,   633,     0,     0,     0,     0,     0,     0,     0,
       0,   678,   683,   548,     0,     0,     0,     0,     0,     0,
       0,   557,   562,     0,     0,     0,     0,     0,   596,   601,
       0,     0,   369,   366,     0,     0,     0,     0,     0,     0,
       0,     0,   883,   880,     0,     0,   915,   912,    49,    41,
       0,     0,     0,     0,     0,   159,   160,   161,     0,     0,
       0,   198,   199,     0,     0,     0,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,     0,   193,
     194,   162,   163,   164,     0,     0,     0,   176,   177,   184,
     185,   186,   187,   192,     0,     0,     0,   156,     0,     0,
       0,     0,     0,   480,   481,   482,     0,     0,     0,     0,
       0,   764,     0,     0,     0,     0,     0,     0,   195,   196,
     197,     0,     0,    68,     0,     0,     0,   227,   228,   229,
     230,   203,     0,     0,     0,     0,     0,     0,   483,     0,
       0,     0,     0,     0,   406,     0,   663,   635,     0,     0,
       0,     0,     0,     0,     0,     0,   682,     0,     0,   574,
       0,     0,     0,   585,   561,     0,   618,   619,   620,     0,
     600,     0,     0,   368,   895,     0,   898,     0,   901,   902,
       0,     0,   882,     0,   920,   914,     0,     0,     0,     0,
       0,   700,   702,   704,     0,     0,   248,   155,   167,   168,
     169,   170,   171,   166,   173,   175,   396,   549,   588,   158,
     180,   181,   182,   183,   179,   486,    38,   665,   667,     0,
     728,   670,   358,     0,     0,   767,     0,     0,   189,   191,
       0,     0,    51,   218,   221,   222,   220,   225,   226,   224,
     465,   467,   469,   625,   463,   471,   475,   477,   479,   473,
       0,   662,   720,   706,   708,   710,   714,   712,   718,   716,
     577,   295,   581,   579,   584,   615,   622,   374,   376,   897,
     900,   905,   906,   904,   908,   248,    42,     0,     0,     0,
     240,   242,     0,   235,   238,   239,   283,   285,   287,   291,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     305,     0,     0,   312,   314,   316,   318,   320,   321,   322,
     323,   324,   325,   289,   282,     0,   255,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,     0,   253,     0,   249,   250,   401,     0,   397,   398,
     554,     0,   550,   551,   593,     0,   589,   590,   491,     0,
     487,   488,   337,   338,   339,   340,   341,     0,   329,   332,
     333,   334,   335,   336,   733,     0,   729,   730,   675,     0,
     671,   672,   363,     0,   359,   360,     0,     0,     0,     0,
       0,     0,     0,   379,   382,   383,   384,   385,   386,   387,
       0,     0,     0,   352,     0,   344,   347,   348,   349,   350,
     351,   772,     0,   768,   769,     0,   872,     0,   875,   868,
     869,     0,   862,   865,   866,   867,   870,     0,   926,     0,
     923,     0,     0,     0,     0,   972,     0,   965,   968,   969,
     970,   971,    53,   630,     0,   626,   627,   724,     0,   723,
       0,    62,   910,   201,     0,     0,   237,   234,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   257,   232,   245,     0,   247,   252,     0,   395,   400,
     558,   546,   553,   597,   587,   592,     0,   485,   490,   331,
     328,   735,   727,   732,   679,   669,   674,     0,   357,   362,
       0,     0,     0,     0,     0,     0,   381,   378,     0,     0,
       0,   346,   343,     0,   766,   771,     0,     0,     0,     0,
     864,   861,   878,     0,   925,   922,     0,     0,     0,     0,
     967,   964,    55,     0,    54,     0,   624,   629,     0,   722,
     919,     0,     0,   236,     0,     0,     0,     0,   293,   296,
     297,   298,   299,   300,   301,   302,   303,   304,     0,   310,
     311,     0,     0,     0,     0,     0,     0,   256,     0,   251,
       0,   399,     0,   552,     0,   591,   544,   515,   516,   517,
     499,   500,   520,   521,   522,   523,   524,   525,   542,   502,
     503,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   543,   496,   497,
     498,   511,   512,   513,   514,   508,   509,   510,     0,   493,
     501,   518,   519,   504,   505,   506,   507,   489,   330,   758,
     760,     0,     0,   752,   753,   754,   755,   756,   757,   745,
     746,   750,   751,   747,   748,   749,     0,   736,   737,   740,
     741,   742,   743,   744,   731,     0,   673,     0,   361,   388,
     389,   390,   391,   392,   393,   380,   353,   354,   355,   345,
     790,   795,   797,     0,   820,     0,   801,   789,   782,   783,
     784,   787,   788,     0,   774,   777,   778,   779,   780,   785,
     786,   781,   770,   871,     0,   874,     0,   863,   941,     0,
     939,   937,   931,   935,   936,     0,   928,   933,   934,   932,
     924,   973,   974,   975,   976,   966,    52,    57,     0,   628,
       0,   241,   243,   284,   286,   288,   292,   307,   308,   309,
     306,   313,   315,   317,   319,   326,   290,   254,   402,   555,
     594,   495,   492,     0,     0,     0,     0,   734,   739,   676,
     364,     0,     0,     0,     0,     0,     0,     0,   776,   773,
     873,   876,     0,     0,     0,   930,   927,    56,   631,   725,
     494,     0,     0,   762,   763,   738,     0,     0,     0,   799,
       0,   800,     0,   775,     0,   938,     0,   929,   759,   761,
     792,   793,   794,   791,   796,   798,     0,   803,     0,   940,
     832,   835,   837,   839,   831,   830,   829,     0,   822,   825,
     826,   827,   828,   808,     0,   804,   805,   946,     0,   943,
       0,     0,     0,     0,   824,   821,     0,   802,   807,     0,
     945,   942,     0,     0,     0,     0,   823,   818,   817,   813,
     815,   816,     0,   810,   814,   806,   956,     0,     0,     0,
     961,     0,   948,   951,   952,   953,   954,   955,   944,   834,
     833,   836,   838,   841,     0,   812,   809,     0,     0,     0,
       0,     0,   950,   947,   846,     0,   842,   843,     0,   811,
       0,   958,   959,   960,     0,   949,     0,   840,   845,   819,
     957,   962,   858,   857,   851,   853,   854,   855,   856,     0,
     848,   852,   844,     0,   850,   847,     0,   849,   859
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423,   -54, -1423,  -621, -1423,   602,
   -1423, -1423, -1423, -1423, -1423, -1423,  -645, -1423, -1423, -1423,
     -67, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   590,   802,
      12,    31,    35,   -28,    27,    92,    93,    95,    97,    98,
     100, -1423, -1423, -1423, -1423,   103, -1423, -1423,   108,   110,
      47,    53,    55,    58, -1423, -1423,    60, -1423,    63, -1423,
      65,   115,    68, -1423, -1423,    70,    75,    80,    82,    87,
   -1423,    90, -1423,   122, -1423, -1423, -1423, -1423, -1423,    43,
   -1423, -1423, -1423,   592,   796, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423,   332, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423,   517, -1423,   294, -1423,  -744,   303, -1423,
   -1423, -1422, -1423, -1414, -1423, -1412, -1423, -1423, -1423, -1423,
       0, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1059, -1423, -1057, -1423,
   -1056, -1423,   213, -1423, -1423, -1423, -1423, -1423, -1423,   292,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   275, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,   281, -1423, -1423, -1423,
     290,   767, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   284,
   -1423, -1423, -1423, -1423, -1423, -1423, -1043, -1423, -1423, -1423,
     314, -1423, -1423, -1423,   333,   813, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1041, -1423,   -65, -1423,   -58, -1423,
     -35, -1423,   -25, -1423,   127,   130,   132, -1423, -1423, -1423,
   -1423, -1423,   307, -1423, -1423,    56,   -43, -1423, -1423, -1423,
   -1423, -1423,   321, -1423, -1423, -1423,   327, -1423,   800, -1423,
     -46, -1423, -1423, -1423, -1423, -1423,   -41, -1423, -1423, -1423,
   -1423, -1423,   -20, -1423, -1423, -1423,   340, -1423, -1423, -1423,
     334, -1423,   783, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423,   268, -1423, -1423,
   -1423,   273,   824, -1423, -1423, -1423,   -51, -1423,    -4, -1423,
     -32, -1423, -1423, -1423,   336, -1423, -1423, -1423,   335, -1423,
     811,   -55, -1423,   -39, -1423,     8, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1035, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423,   337, -1423, -1423, -1423,    94, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   312,
   -1423, -1423,    66, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,   -10, -1423, -1423,   -22,
   -1423, -1423, -1423, -1423, -1423,    21, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423,   -42, -1423, -1423,
     -57, -1423, -1423, -1423, -1423, -1423,   338, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423,   633,   823, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423,   679,   826, -1423, -1423,
   -1423, -1423, -1423, -1423,   343, -1423, -1423,    89, -1423, -1423,
   -1423, -1423, -1423, -1423,    18, -1423, -1423,   -13, -1423, -1423,
   -1423, -1423, -1423, -1423, -1423, -1423, -1423, -1423,   360, -1423,
   -1423, -1423, -1423
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   777,
      82,    83,    39,    64,    79,    80,   793,  1002,  1103,  1104,
     874,    41,    66,    85,   459,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   488,   175,   176,   508,   177,   178,   179,
     180,   181,   182,   183,   494,   763,   184,   495,   185,   496,
     186,   187,   188,   509,   774,   189,   190,   191,   192,   193,
     526,   194,   527,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   463,   241,   242,    45,    68,   243,   536,   244,
     537,   796,   245,   538,   799,   246,   247,   248,   249,   204,
     473,   205,   464,   842,   843,   844,  1014,   845,  1015,   206,
     474,   207,   475,   903,   904,   905,  1044,   875,   876,   877,
    1018,   878,  1019,   879,  1020,   880,  1040,   881,  1021,   882,
     883,   575,   884,   885,   886,   887,   888,   889,   890,   891,
     892,   893,  1032,  1300,   894,   895,   896,  1035,   897,  1036,
     898,  1037,   899,  1038,   900,  1039,   208,   516,   927,   928,
     929,   930,   931,   932,   933,   209,   522,   964,   965,   966,
     967,   968,   210,   519,   943,   944,   945,  1067,    59,    75,
     423,   424,   425,   590,   426,   591,   211,   520,   952,   953,
     954,   955,   956,   957,   958,   959,   212,   504,   907,   908,
     909,  1047,    47,    69,   296,   297,   298,   549,   299,   545,
     300,   546,   301,   547,   302,   550,   303,   555,   304,   552,
     305,   553,   306,   554,   213,   214,   215,   310,   216,   510,
     919,   920,   921,  1056,  1188,  1189,   217,   505,    53,    72,
     911,   912,   913,  1050,    55,    73,   384,   385,   386,   387,
     388,   389,   390,   574,   391,   578,   392,   577,   393,   394,
     579,   395,   218,   506,   915,   916,   917,  1053,    57,    74,
     407,   408,   409,   410,   411,   583,   412,   413,   414,   415,
     416,   417,   587,   312,   548,  1004,  1005,  1006,  1105,    49,
      70,   342,   343,   344,   559,   345,   219,   511,   220,   512,
     221,   518,   939,   940,   941,  1064,    51,    71,   360,   361,
     362,   222,   468,   223,   469,   224,   470,   366,   564,   367,
     565,   368,   566,   369,   568,   370,   567,   371,   570,   372,
     569,   373,   563,   319,   556,  1008,  1009,  1108,   225,   517,
     935,   936,   937,  1061,  1216,  1217,  1218,  1219,  1220,  1313,
    1221,  1314,  1222,  1223,   226,   227,   523,   972,   973,   974,
    1083,  1253,  1254,  1255,  1321,  1363,  1256,  1322,  1257,  1323,
    1258,  1259,  1260,  1327,  1384,  1385,  1386,  1396,  1412,  1413,
    1414,  1434,  1261,  1325,  1377,  1378,  1379,  1390,  1430,  1380,
    1391,  1381,  1392,  1382,  1393,  1445,  1446,  1447,  1456,  1469,
    1470,  1471,  1473,   228,   524,   981,   982,   983,   984,  1087,
     985,   986,  1089,   229,   525,    61,    76,   438,   439,   440,
     441,   595,   442,   443,   597,   444,   445,   446,   600,   833,
     447,   601,   230,   462,    63,    77,   450,   451,   452,   604,
     453,   231,   531,   989,   990,  1093,  1275,  1276,  1277,  1278,
    1334,  1279,  1332,  1388,  1389,  1399,  1421,  1422,  1423,  1437,
    1424,  1425,  1426,  1427,  1441,   232,   532,   996,   997,   998,
     999,  1000,  1001
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   322,   356,   337,   382,   403,   422,   435,
      78,   901,   338,  1179,   316,  1180,   363,   250,   313,   346,
     358,  1196,   396,   418,  1248,   436,  1249,  1250,   405,   374,
     317,   831,   364,   406,  1464,   339,    28,   315,   420,   421,
     776,   268,  1465,   460,  1466,   340,   136,   137,   461,   311,
     341,   357,  1464,   534,   806,   807,   808,    29,   535,    30,
    1465,    31,  1466,   812,   251,   314,   347,   359,   376,   397,
     419,    40,   437,   383,   404,   543,    42,   318,    44,   365,
     544,   265,   557,    46,   826,    81,   561,   558,   136,   137,
     454,   562,   758,   759,   760,   761,   269,   130,   847,   848,
     266,   136,   137,    48,   267,    93,    94,    95,   975,   976,
     977,   776,   295,    50,   592,   602,   279,   323,  1370,   593,
     603,   158,   280,   324,   281,   325,    52,   282,   326,   283,
     327,   762,   284,   328,   285,   329,    54,   287,   330,   288,
     331,   960,   961,   962,   289,   332,   448,   449,  1407,   290,
     333,   291,   334,  1360,  1361,  1362,   292,   335,   978,   293,
     336,   270,   271,   375,   272,   606,   273,   274,   534,   275,
     607,  1059,   276,  1011,  1060,   606,   131,   277,   543,   278,
    1012,   136,   137,  1013,   286,   233,   234,  1094,    56,   235,
    1095,   294,   236,   237,   238,   239,   307,   136,   137,   308,
     158,   309,   136,   137,   420,   421,   348,   991,   992,   993,
     994,   832,  1400,   158,    58,  1401,   349,   350,   351,   352,
     353,   354,   355,  1016,   158,    60,  1041,   376,  1017,   377,
     378,  1042,   794,   795,   379,   380,   381,  1462,   873,  1416,
      62,  1041,  1417,  1418,  1419,  1420,  1043,   136,   137,   866,
     867,   868,   869,   870,   871,  1371,  1372,  1373,  1076,    87,
    1081,  1090,    88,  1077,    84,  1082,  1091,   455,  1179,  1248,
    1180,  1249,  1250,   456,    89,   457,  1196,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    32,    33,
      34,    35,   458,   158,   136,   137,   922,   923,   924,   925,
    1138,   926,  1297,  1298,  1299,   602,   863,   864,   865,   158,
    1092,  1100,  1041,   571,   158,   465,  1101,  1307,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   557,  1311,   572,
     130,   131,  1308,  1312,    93,    94,    95,    96,   466,   158,
     467,   592,   132,   133,   134,   376,  1320,   797,   798,   135,
     136,   137,   136,   137,   471,   840,   841,   138,   139,   140,
     141,   142,  1328,  1335,   561,   136,   137,  1329,  1336,  1338,
     143,  1394,   101,   102,   103,   472,  1395,   476,   477,  1435,
     144,   608,   609,   145,  1436,   478,   158,  1442,  1474,   582,
     146,   147,  1443,  1475,  1240,   148,   479,   480,  1241,  1242,
    1243,  1244,   481,   482,   130,   131,   376,   483,  1245,  1246,
     484,   485,   486,   149,   487,   489,   490,   150,   946,   947,
     948,   949,   950,   951,   491,   492,   136,   137,   770,   771,
     772,   773,   151,   152,   153,   154,   155,   156,  1199,  1200,
    1201,  1202,   493,   497,   498,   499,   157,   159,   500,   501,
     573,  1268,   502,  1269,  1270,   503,   240,   507,   513,   514,
     515,   521,   158,   528,   158,   529,   530,   533,   539,   540,
     264,   541,   250,   542,   322,   551,   337,   158,   560,   576,
     580,   581,   316,   338,   584,   356,   313,   585,   586,   588,
     346,   589,   610,   594,   596,   382,   598,   363,   317,   599,
     605,   358,   403,   611,   612,   315,   339,   613,   614,   268,
     615,   396,   616,   364,   617,   435,   340,   311,   418,   251,
     618,   341,   619,   405,   620,   622,   623,   621,   406,   624,
     625,   436,   357,   314,   626,   627,   628,   347,   158,   631,
     629,   630,   638,   632,   633,   318,   634,   635,   359,   265,
     376,   398,   377,   378,   399,   400,   401,   636,   397,   637,
     365,   644,   383,   645,   269,   419,   639,   640,   266,   404,
     136,   137,   267,   646,   641,   654,   642,   649,   437,   402,
     295,   643,   647,   648,   279,   650,   651,   655,   323,   652,
     280,   656,   281,   653,   324,   282,   325,   283,   658,   326,
     284,   327,   285,   657,   328,   287,   329,   288,   659,   330,
     660,   331,   289,   661,   662,   666,   332,   290,   663,   291,
     667,   333,   664,   334,   292,  1339,   665,   293,   335,   270,
     271,   336,   272,   668,   273,   274,   669,   275,   670,   671,
     276,   672,   673,   674,   675,   277,   689,   278,   676,   677,
     681,   682,   286,   678,   679,   680,   684,   685,   686,   294,
     159,   687,   240,   688,   307,   690,   692,   308,   693,   309,
     694,   695,   836,   696,   697,   699,   700,   701,   250,   702,
     698,   703,   158,   705,   706,   708,    91,    92,    93,    94,
      95,    96,   709,   710,   711,   712,   713,   963,   714,   715,
     435,   717,   718,   719,   995,   720,   721,   722,   725,   723,
     729,   726,   731,   969,   732,   979,   436,   727,   728,   735,
     737,   734,   736,   738,   739,   251,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   740,   741,   743,
     746,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   744,   252,   253,   254,   747,   131,
     970,   748,   980,   437,   749,   750,   136,   137,   751,   752,
     753,   133,   134,   754,   755,   756,   757,   764,   255,   765,
     136,   137,   256,   257,   258,   138,   139,   140,   766,   259,
     260,   261,   767,   768,   769,   775,   262,   778,   143,    30,
     779,   780,   781,   782,   785,  1046,   263,   783,   784,    91,
      92,    93,    94,    95,    96,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   786,   787,
     790,   788,   427,   428,   429,   430,   431,   432,   433,   434,
     791,   789,   792,   800,   801,   803,   810,   835,   802,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     151,   152,   804,   805,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   158,   809,
     902,   906,   131,   376,   811,   813,   814,   815,   910,   914,
     918,   816,   158,   817,   133,   134,   818,   819,   834,   820,
     934,   821,   938,   136,   137,   942,   257,   971,   138,   139,
     140,   988,   259,   260,   261,  1003,   822,  1022,   823,   262,
     824,   825,   827,   829,  1007,  1023,  1024,  1025,  1026,   263,
    1027,  1028,   830,  1029,  1030,  1031,  1033,  1034,  1429,  1049,
    1045,  1048,  1052,  1051,  1054,  1055,  1057,  1058,  1063,  1062,
    1066,  1118,  1065,  1069,  1068,  1070,  1071,  1072,  1073,  1074,
     264,  1075,  1078,   382,  1079,  1080,   403,  1085,  1084,  1146,
    1086,  1181,   316,  1088,  1203,  1096,   313,   356,  1182,   396,
     422,  1193,   418,   151,   152,  1191,  1213,   405,   317,   363,
    1211,  1097,   406,   358,   963,   315,  1247,  1194,  1209,   268,
    1098,  1183,  1214,  1099,  1102,   364,  1271,   311,  1150,  1106,
     969,  1184,  1251,   995,  1107,   158,  1190,  1109,   322,   979,
     337,  1210,  1273,   314,   357,  1110,   397,   338,  1111,   419,
     383,  1112,  1192,   404,   346,   318,  1178,  1212,  1114,   265,
     359,  1208,  1115,  1116,  1195,  1117,  1119,  1120,  1147,  1215,
     339,  1121,   365,  1204,   269,  1122,  1123,   970,   266,  1252,
     340,  1124,   267,  1151,  1125,   341,   980,  1148,  1126,  1274,
     295,  1149,  1205,  1272,   279,  1127,  1206,  1128,  1130,  1177,
     280,   347,   281,  1161,  1207,   282,  1129,   283,  1131,  1162,
     284,  1163,   285,  1132,  1164,   287,  1165,   288,  1133,  1166,
    1134,  1167,   289,  1135,  1169,  1136,  1170,   290,  1229,   291,
    1264,  1171,  1230,  1231,   292,  1232,  1172,   293,  1173,   270,
     271,  1233,   272,  1174,   273,   274,  1175,   275,  1152,  1153,
     276,  1154,   323,  1155,  1156,   277,  1157,   278,   324,  1158,
     325,  1236,   286,   326,  1159,   327,  1160,  1234,   328,   294,
     329,  1168,  1237,   330,   307,   331,  1238,   308,  1176,   309,
     332,  1266,  1286,  1185,  1263,   333,  1186,   334,  1187,  1287,
    1309,  1290,   335,  1310,  1315,   336,  1316,  1317,  1265,  1318,
    1367,  1319,  1324,  1326,  1333,  1341,  1342,  1346,  1281,  1347,
    1348,  1350,  1331,  1349,   846,   847,   848,   849,   850,   851,
     852,   853,   854,   855,   856,   857,   858,   859,   860,  1282,
    1291,  1283,   861,   862,   863,   864,   865,   866,   867,   868,
     869,   870,   871,   872,  1146,  1284,  1181,  1292,  1293,  1294,
    1295,  1203,  1352,  1182,  1296,  1354,  1193,  1301,  1302,  1343,
    1191,  1247,  1303,  1213,  1305,  1356,  1306,  1211,  1271,  1330,
    1337,  1344,  1194,  1355,  1351,  1209,  1183,  1251,   376,  1214,
    1366,  1358,  1359,  1150,  1273,  1364,  1184,  1365,  1368,  1369,
    1397,  1190,  1383,  1387,  1398,  1433,  1402,  1403,  1210,  1374,
    1404,  1405,  1431,  1432,  1438,  1439,  1440,  1192,  1448,  1450,
    1444,  1178,  1451,  1452,  1212,  1375,  1453,  1454,  1208,  1195,
    1457,  1458,  1459,  1147,  1252,  1460,  1215,  1374,  1461,  1408,
    1204,  1274,  1476,  1478,   828,  1272,   683,   837,  1151,   691,
    1139,   839,  1148,  1375,  1137,  1410,  1149,  1304,  1113,  1205,
    1228,  1198,  1010,  1206,  1177,   873,  1239,  1227,  1161,   733,
    1235,  1207,  1376,  1141,  1162,  1197,  1163,  1340,  1408,  1164,
     704,  1165,   730,  1143,  1166,  1289,  1167,  1142,  1288,  1169,
    1140,  1170,   724,   716,  1410,   707,  1171,  1144,  1415,  1463,
    1376,  1172,  1411,  1173,  1353,  1145,  1409,  1262,  1174,  1225,
    1224,  1175,  1226,  1152,  1153,  1467,  1154,  1463,  1155,  1156,
     158,  1157,  1345,  1449,  1158,  1406,  1472,  1477,  1428,  1159,
     987,  1160,     0,  1467,  1357,   742,  1168,   838,  1267,  1455,
       0,  1411,   745,  1176,     0,  1409,     0,  1280,  1185,     0,
       0,  1186,     0,  1187,     0,   116,   117,   118,   119,   120,
     121,   122,  1468,   124,   125,   126,   127,     0,     0,     0,
    1285,     0,     0,   131,     0,     0,     0,     0,     0,     0,
    1468,     0,     0,     0,     0,     0,   134,     0,     0,     0,
       0,     0,     0,   320,   136,   137,     0,     0,     0,     0,
       0,     0,     0,   259,   260,   261,     0,     0,     0,     0,
     262,   321,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   151,   152,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,   755,    70,  1056,    69,  1056,    71,    68,    69,    70,
      71,  1056,    73,    74,  1083,    76,  1083,  1083,    74,    72,
      69,    18,    71,    74,  1456,    70,     0,    69,   153,   154,
     661,    69,  1456,     3,  1456,    70,   124,   125,     8,    69,
      70,    71,  1474,     3,   699,   700,   701,     5,     8,     7,
    1474,     9,  1474,   708,    68,    69,    70,    71,   104,    73,
      74,     7,    76,    73,    74,     3,     7,    69,     7,    71,
       8,    69,     3,     7,   729,   236,     3,     8,   124,   125,
       6,     8,   200,   201,   202,   203,    69,   102,    41,    42,
      69,   124,   125,     7,    69,    32,    33,    34,   186,   187,
     188,   732,    69,     7,     3,     3,    69,    70,    40,     8,
       8,   236,    69,    70,    69,    70,     7,    69,    70,    69,
      70,   239,    69,    70,    69,    70,     7,    69,    70,    69,
      70,   164,   165,   166,    69,    70,    12,    13,   184,    69,
      70,    69,    70,   169,   170,   171,    69,    70,   236,    69,
      70,    69,    69,    40,    69,     3,    69,    69,     3,    69,
       8,     3,    69,     8,     6,     3,   103,    69,     3,    69,
       8,   124,   125,     8,    69,    15,    16,     3,     7,    19,
       6,    69,    22,    23,    24,    25,    69,   124,   125,    69,
     236,    69,   124,   125,   153,   154,   133,   219,   220,   221,
     222,   198,     3,   236,     7,     6,   143,   144,   145,   146,
     147,   148,   149,     3,   236,     7,     3,   104,     8,   106,
     107,     8,    17,    18,   111,   112,   113,   180,   181,   211,
       7,     3,   214,   215,   216,   217,     8,   124,   125,    63,
      64,    65,    66,    67,    68,   177,   178,   179,     3,    11,
       3,     3,    14,     8,    10,     8,     8,     3,  1311,  1328,
    1311,  1328,  1328,     4,    26,     8,  1311,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   236,   237,
     238,   239,     3,   236,   124,   125,   144,   145,   146,   147,
    1044,   149,    55,    56,    57,     3,    60,    61,    62,   236,
       8,     3,     3,     8,   236,     4,     8,     8,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     3,     3,     3,
     102,   103,     8,     8,    32,    33,    34,    35,     4,   236,
       4,     3,   114,   115,   116,   104,     8,    20,    21,   121,
     124,   125,   124,   125,     4,    27,    28,   129,   130,   131,
     132,   133,     3,     3,     3,   124,   125,     8,     8,     8,
     142,     3,    70,    71,    72,     4,     8,     4,     4,     3,
     152,   455,   456,   155,     8,     4,   236,     3,     3,     3,
     162,   163,     8,     8,   168,   167,     4,     4,   172,   173,
     174,   175,     4,     4,   102,   103,   104,     4,   182,   183,
       4,     4,     4,   185,     4,     4,     4,   189,   156,   157,
     158,   159,   160,   161,     4,     4,   124,   125,   117,   118,
     119,   120,   204,   205,   206,   207,   208,   209,   136,   137,
     138,   139,     4,     4,     4,     4,   218,   534,     4,     4,
       8,   210,     4,   212,   213,     4,   543,     4,     4,     4,
       4,     4,   236,     4,   236,     4,     4,     4,     4,     4,
     557,     4,   543,     4,   561,     4,   561,   236,     4,     4,
       4,     8,   557,   561,     4,   572,   557,     4,     4,     8,
     561,     3,   236,     4,     4,   582,     4,   572,   557,     4,
       4,   572,   589,     4,     4,   557,   561,     4,     4,   557,
     239,   582,   239,   572,   239,   602,   561,   557,   589,   543,
       4,   561,     4,   589,     4,   239,     4,   237,   589,     4,
       4,   602,   572,   557,   237,   237,   237,   561,   236,   239,
     237,   237,     4,   238,   238,   557,   238,   237,   572,   557,
     104,   105,   106,   107,   108,   109,   110,   238,   582,   237,
     572,     4,   582,     4,   557,   589,   237,   237,   557,   589,
     124,   125,   557,     4,   239,     4,   239,   238,   602,   133,
     557,   239,   239,   239,   557,   237,   237,     4,   561,   237,
     557,     4,   557,   239,   561,   557,   561,   557,     4,   561,
     557,   561,   557,   237,   561,   557,   561,   557,     4,   561,
       4,   561,   557,     4,     4,     4,   561,   557,   239,   557,
       4,   561,   239,   561,   557,  1290,   239,   557,   561,   557,
     557,   561,   557,     4,   557,   557,     4,   557,     4,   237,
     557,     4,     4,     4,     4,   557,   237,   557,     4,     4,
       4,     4,   557,   239,   239,   239,     4,     4,     4,   557,
     747,   239,   749,   239,   557,   237,     4,   557,     4,   557,
       4,     4,   746,     4,     4,     4,     4,     4,   749,     4,
     237,     4,   236,     4,   237,     4,    30,    31,    32,    33,
      34,    35,     4,     4,     4,     4,     4,   784,     4,     4,
     787,     4,     4,   237,   791,     4,     4,     4,     4,   239,
       4,   239,     4,   784,     4,   786,   787,   239,   239,     4,
       4,   239,   237,   237,   237,   749,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     4,     4,     4,
       4,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   237,    99,   100,   101,     7,   103,
     784,     7,   786,   787,     7,     7,   124,   125,   236,   236,
     236,   115,   116,     7,     7,     5,   236,   236,   122,   236,
     124,   125,   126,   127,   128,   129,   130,   131,     5,   133,
     134,   135,     5,     5,   236,     5,   140,   236,   142,     7,
       5,     5,     5,     5,     5,     3,   150,     7,     7,    30,
      31,    32,    33,    34,    35,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,     7,     7,
       5,   236,   190,   191,   192,   193,   194,   195,   196,   197,
       7,   236,     5,   236,   236,     5,     7,     5,   236,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
     204,   205,   236,   236,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   236,   236,
       7,     7,   103,   104,   236,   236,   236,   236,     7,     7,
       7,   236,   236,   236,   115,   116,   236,   236,   199,   236,
       7,   236,     7,   124,   125,     7,   127,     7,   129,   130,
     131,     7,   133,   134,   135,     7,   236,     4,   236,   140,
     236,   236,   236,   236,   151,     4,     4,     4,     4,   150,
       4,     4,   236,     4,     4,     4,     4,     4,   176,     3,
       6,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   237,     6,     3,     6,     4,     4,     4,     4,     4,
    1047,     4,     4,  1050,     4,     4,  1053,     3,     6,  1056,
       4,  1056,  1047,     4,  1061,     4,  1047,  1064,  1056,  1050,
    1067,  1056,  1053,   204,   205,  1056,  1061,  1053,  1047,  1064,
    1061,     4,  1053,  1064,  1081,  1047,  1083,  1056,  1061,  1047,
       4,  1056,  1061,     4,   236,  1064,  1093,  1047,  1056,     6,
    1081,  1056,  1083,  1100,     3,   236,  1056,     8,  1105,  1090,
    1105,  1061,  1093,  1047,  1064,     6,  1050,  1105,     4,  1053,
    1050,     4,  1056,  1053,  1105,  1047,  1056,  1061,     4,  1047,
    1064,  1061,     4,     4,  1056,     4,   239,   237,  1056,  1061,
    1105,   239,  1064,  1061,  1047,   237,   237,  1081,  1047,  1083,
    1105,   237,  1047,  1056,   237,  1105,  1090,  1056,   237,  1093,
    1047,  1056,  1061,  1093,  1047,   237,  1061,     4,   237,  1056,
    1047,  1105,  1047,  1056,  1061,  1047,   239,  1047,     4,  1056,
    1047,  1056,  1047,     4,  1056,  1047,  1056,  1047,     4,  1056,
       4,  1056,  1047,     4,  1056,     4,  1056,  1047,   237,  1047,
       4,  1056,   237,   237,  1047,   237,  1056,  1047,  1056,  1047,
    1047,   237,  1047,  1056,  1047,  1047,  1056,  1047,  1056,  1056,
    1047,  1056,  1105,  1056,  1056,  1047,  1056,  1047,  1105,  1056,
    1105,   239,  1047,  1105,  1056,  1105,  1056,   237,  1105,  1047,
    1105,  1056,   237,  1105,  1047,  1105,   237,  1047,  1056,  1047,
    1105,     4,     6,  1056,   239,  1105,  1056,  1105,  1056,     3,
       8,     4,  1105,     8,     4,  1105,     4,     8,   237,     3,
       5,     8,     4,     4,     4,     4,     4,     4,   239,     4,
       4,     4,  1266,   237,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   239,
     236,   239,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,  1311,   239,  1311,   236,   236,   236,
     236,  1318,     4,  1311,   236,     4,  1311,   236,   236,   239,
    1311,  1328,   236,  1318,   236,     4,   236,  1318,  1335,   236,
     236,   239,  1311,   237,   239,  1318,  1311,  1328,   104,  1318,
       7,   236,   236,  1311,  1335,   236,  1311,   236,     5,   236,
       6,  1311,     7,     7,     3,     5,     4,     4,  1318,  1366,
       4,     4,   236,   236,     4,     4,     4,  1311,     4,     4,
       7,  1311,   239,   237,  1318,  1366,   237,     4,  1318,  1311,
       6,     3,   236,  1311,  1328,   236,  1318,  1394,   236,  1396,
    1318,  1335,     4,   236,   732,  1335,   534,   747,  1311,   543,
    1046,   749,  1311,  1394,  1041,  1396,  1311,  1134,  1016,  1318,
    1069,  1059,   835,  1318,  1311,   181,  1081,  1067,  1311,   592,
    1076,  1318,  1366,  1049,  1311,  1058,  1311,  1311,  1435,  1311,
     557,  1311,   589,  1052,  1311,  1107,  1311,  1050,  1105,  1311,
    1047,  1311,   582,   572,  1435,   561,  1311,  1053,  1398,  1456,
    1394,  1311,  1396,  1311,  1328,  1055,  1396,  1085,  1311,  1064,
    1063,  1311,  1066,  1311,  1311,  1456,  1311,  1474,  1311,  1311,
     236,  1311,  1318,  1435,  1311,  1394,  1458,  1474,  1400,  1311,
     787,  1311,    -1,  1474,  1335,   602,  1311,   748,  1090,  1442,
      -1,  1435,   606,  1311,    -1,  1435,    -1,  1094,  1311,    -1,
      -1,  1311,    -1,  1311,    -1,    85,    86,    87,    88,    89,
      90,    91,  1456,    93,    94,    95,    96,    -1,    -1,    -1,
    1100,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,
    1474,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,   123,   124,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   133,   134,   135,    -1,    -1,    -1,    -1,
     140,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   204,   205,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   236
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,     5,
       7,     9,   236,   237,   238,   239,   255,   256,   257,   262,
       7,   271,     7,   276,     7,   335,     7,   452,     7,   539,
       7,   556,     7,   488,     7,   494,     7,   518,     7,   428,
       7,   665,     7,   684,   263,   258,   272,   277,   336,   453,
     540,   557,   489,   495,   519,   429,   666,   685,   255,   264,
     265,   236,   260,   261,    10,   273,   275,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     102,   103,   114,   115,   116,   121,   124,   125,   129,   130,
     131,   132,   133,   142,   152,   155,   162,   163,   167,   185,
     189,   204,   205,   206,   207,   208,   209,   218,   236,   270,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   294,   295,   297,   298,   299,
     300,   301,   302,   303,   306,   308,   310,   311,   312,   315,
     316,   317,   318,   319,   321,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   349,   351,   359,   361,   406,   415,
     422,   436,   446,   474,   475,   476,   478,   486,   512,   546,
     548,   550,   561,   563,   565,   588,   604,   605,   653,   663,
     682,   691,   715,    15,    16,    19,    22,    23,    24,    25,
     270,   333,   334,   337,   339,   342,   345,   346,   347,   348,
     546,   548,    99,   100,   101,   122,   126,   127,   128,   133,
     134,   135,   140,   150,   270,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   295,   298,   299,   300,
     301,   302,   303,   306,   308,   310,   311,   312,   315,   316,
     317,   318,   319,   321,   323,   329,   454,   455,   456,   458,
     460,   462,   464,   466,   468,   470,   472,   474,   475,   476,
     477,   512,   533,   546,   548,   550,   561,   563,   565,   583,
     123,   141,   270,   300,   301,   302,   303,   306,   308,   310,
     312,   315,   316,   317,   318,   319,   321,   466,   468,   470,
     472,   512,   541,   542,   543,   545,   546,   548,   133,   143,
     144,   145,   146,   147,   148,   149,   270,   512,   546,   548,
     558,   559,   560,   561,   563,   565,   567,   569,   571,   573,
     575,   577,   579,   581,   486,    40,   104,   106,   107,   111,
     112,   113,   270,   380,   496,   497,   498,   499,   500,   501,
     502,   504,   506,   508,   509,   511,   546,   548,   105,   108,
     109,   110,   133,   270,   380,   500,   506,   520,   521,   522,
     523,   524,   526,   527,   528,   529,   530,   531,   546,   548,
     153,   154,   270,   430,   431,   432,   434,   190,   191,   192,
     193,   194,   195,   196,   197,   270,   546,   548,   667,   668,
     669,   670,   672,   673,   675,   676,   677,   680,    12,    13,
     686,   687,   688,   690,     6,     3,     4,     8,     3,   274,
       3,     8,   683,   332,   352,     4,     4,     4,   562,   564,
     566,     4,     4,   350,   360,   362,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   293,     4,
       4,     4,     4,     4,   304,   307,   309,     4,     4,     4,
       4,     4,     4,     4,   447,   487,   513,     4,   296,   313,
     479,   547,   549,     4,     4,     4,   407,   589,   551,   423,
     437,     4,   416,   606,   654,   664,   320,   322,     4,     4,
       4,   692,   716,     4,     3,     8,   338,   340,   343,     4,
       4,     4,     4,     3,     8,   459,   461,   463,   534,   457,
     465,     4,   469,   471,   473,   467,   584,     3,     8,   544,
       4,     3,     8,   582,   568,   570,   572,   576,   574,   580,
     578,     8,     3,     8,   503,   381,     4,   507,   505,   510,
       4,     8,     3,   525,     4,     4,     4,   532,     8,     3,
     433,   435,     3,     8,     4,   671,     4,   674,     4,     4,
     678,   681,     3,     8,   689,     4,     3,     8,   255,   255,
     236,     4,     4,     4,     4,   239,   239,   239,     4,     4,
       4,   237,   239,     4,     4,     4,   237,   237,   237,   237,
     237,   239,   238,   238,   238,   237,   238,   237,     4,   237,
     237,   239,   239,   239,     4,     4,     4,   239,   239,   238,
     237,   237,   237,   239,     4,     4,     4,   237,     4,     4,
       4,     4,     4,   239,   239,   239,     4,     4,     4,     4,
       4,   237,     4,     4,     4,     4,     4,     4,   239,   239,
     239,     4,     4,   279,     4,     4,     4,   239,   239,   237,
     237,   334,     4,     4,     4,     4,     4,     4,   237,     4,
       4,     4,     4,     4,   455,     4,   237,   542,     4,     4,
       4,     4,     4,     4,     4,     4,   560,     4,     4,   237,
       4,     4,     4,   239,   498,     4,   239,   239,   239,     4,
     522,     4,     4,   431,   239,     4,   237,     4,   237,   237,
       4,     4,   668,     4,   237,   687,     4,     7,     7,     7,
       7,   236,   236,   236,     7,     7,     5,   236,   200,   201,
     202,   203,   239,   305,   236,   236,     5,     5,     5,   236,
     117,   118,   119,   120,   314,     5,   257,   259,   236,     5,
       5,     5,     5,     7,     7,     5,     7,     7,   236,   236,
       5,     7,     5,   266,    17,    18,   341,    20,    21,   344,
     236,   236,   236,     5,   236,   236,   266,   266,   266,   236,
       7,   236,   266,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   266,   236,   259,   236,
     236,    18,   198,   679,   199,     5,   255,   278,   686,   333,
      27,    28,   353,   354,   355,   357,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,   181,   270,   367,   368,   369,   371,   373,
     375,   377,   379,   380,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   394,   395,   396,   398,   400,   402,
     404,   367,     7,   363,   364,   365,     7,   448,   449,   450,
       7,   490,   491,   492,     7,   514,   515,   516,     7,   480,
     481,   482,   144,   145,   146,   147,   149,   408,   409,   410,
     411,   412,   413,   414,     7,   590,   591,   592,     7,   552,
     553,   554,     7,   424,   425,   426,   156,   157,   158,   159,
     160,   161,   438,   439,   440,   441,   442,   443,   444,   445,
     164,   165,   166,   270,   417,   418,   419,   420,   421,   546,
     548,     7,   607,   608,   609,   186,   187,   188,   236,   546,
     548,   655,   656,   657,   658,   660,   661,   667,     7,   693,
     694,   219,   220,   221,   222,   270,   717,   718,   719,   720,
     721,   722,   267,     7,   535,   536,   537,   151,   585,   586,
     363,     8,     8,     8,   356,   358,     3,     8,   370,   372,
     374,   378,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   392,     4,     4,   397,   399,   401,   403,   405,
     376,     3,     8,     8,   366,     6,     3,   451,     6,     3,
     493,     6,     3,   517,     6,     3,   483,     6,     3,     3,
       6,   593,     6,     3,   555,     6,     3,   427,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   610,     6,     3,     4,   659,     4,   662,
       3,     8,     8,   695,     3,     6,     4,     4,     4,     4,
       3,     8,   236,   268,   269,   538,     6,     3,   587,     8,
       6,     4,     4,   354,     4,     4,     4,     4,   237,   239,
     237,   239,   237,   237,   237,   237,   237,   237,     4,   239,
     237,     4,     4,     4,     4,     4,     4,   368,   367,   365,
     454,   450,   496,   492,   520,   516,   270,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   295,   298,
     299,   300,   301,   302,   303,   306,   308,   310,   311,   312,
     315,   316,   317,   318,   319,   321,   323,   329,   380,   446,
     464,   466,   468,   470,   472,   474,   475,   476,   484,   485,
     512,   546,   548,   561,   563,   565,   583,   482,   409,   136,
     137,   138,   139,   270,   280,   281,   282,   329,   380,   486,
     512,   546,   548,   561,   563,   565,   594,   595,   596,   597,
     598,   600,   602,   603,   592,   558,   554,   430,   426,   237,
     237,   237,   237,   237,   237,   439,   239,   237,   237,   418,
     168,   172,   173,   174,   175,   182,   183,   270,   396,   398,
     400,   546,   548,   611,   612,   613,   616,   618,   620,   621,
     622,   632,   609,   239,     4,   237,     4,   656,   210,   212,
     213,   270,   380,   546,   548,   696,   697,   698,   699,   701,
     694,   239,   239,   239,   239,   718,     6,     3,   541,   537,
       4,   236,   236,   236,   236,   236,   236,    55,    56,    57,
     393,   236,   236,   236,   402,   236,   236,     8,     8,     8,
       8,     3,     8,   599,   601,     4,     4,     8,     3,     8,
       8,   614,   617,   619,     4,   633,     4,   623,     3,     8,
     236,   255,   702,     4,   700,     3,     8,   236,     8,   266,
     485,     4,     4,   239,   239,   596,     4,     4,     4,   237,
       4,   239,     4,   612,     4,   237,     4,   697,   236,   236,
     169,   170,   171,   615,   236,   236,     7,     5,     5,   236,
      40,   177,   178,   179,   270,   546,   548,   634,   635,   636,
     639,   641,   643,     7,   624,   625,   626,     7,   703,   704,
     637,   640,   642,   644,     3,     8,   627,     6,     3,   705,
       3,     6,     4,     4,     4,     4,   635,   184,   270,   380,
     546,   548,   628,   629,   630,   626,   211,   214,   215,   216,
     217,   706,   707,   708,   710,   711,   712,   713,   704,   176,
     638,   236,   236,     5,   631,     3,     8,   709,     4,     4,
       4,   714,     3,     8,     7,   645,   646,   647,     4,   629,
       4,   239,   237,   237,     4,   707,   648,     6,     3,   236,
     236,   236,   180,   270,   371,   373,   375,   546,   548,   649,
     650,   651,   647,   652,     3,     8,     4,   650,   236
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   240,   242,   241,   243,   241,   244,   241,   245,   241,
     246,   241,   247,   241,   248,   241,   249,   241,   250,   241,
     251,   241,   252,   241,   253,   241,   254,   241,   255,   255,
     255,   255,   255,   255,   255,   256,   258,   257,   259,   260,
     260,   261,   261,   261,   263,   262,   264,   264,   265,   265,
     265,   267,   266,   268,   268,   269,   269,   269,   270,   272,
     271,   274,   273,   273,   275,   277,   276,   278,   278,   278,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   293,   292,   294,   296,   295,   297,
     298,   299,   300,   301,   302,   304,   303,   305,   305,   305,
     305,   305,   307,   306,   309,   308,   310,   311,   313,   312,
     314,   314,   314,   314,   315,   316,   317,   318,   320,   319,
     322,   321,   323,   324,   325,   326,   327,   328,   329,   330,
     332,   331,   333,   333,   333,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   336,   335,   338,   337,   340,
     339,   341,   341,   343,   342,   344,   344,   345,   346,   347,
     348,   350,   349,   352,   351,   353,   353,   353,   354,   354,
     356,   355,   358,   357,   360,   359,   362,   361,   363,   363,
     364,   364,   364,   366,   365,   367,   367,   367,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   370,   369,   372,   371,   374,   373,   376,
     375,   378,   377,   379,   381,   380,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   392,   391,   393,   393,   393,
     394,   395,   397,   396,   399,   398,   401,   400,   403,   402,
     402,   402,   402,   402,   402,   405,   404,   407,   406,   408,
     408,   408,   409,   409,   409,   409,   409,   410,   411,   412,
     413,   414,   416,   415,   417,   417,   417,   418,   418,   418,
     418,   418,   418,   419,   420,   421,   423,   422,   424,   424,
     425,   425,   425,   427,   426,   429,   428,   430,   430,   430,
     430,   431,   431,   433,   432,   435,   434,   437,   436,   438,
     438,   438,   439,   439,   439,   439,   439,   439,   440,   441,
     442,   443,   444,   445,   447,   446,   448,   448,   449,   449,
     449,   451,   450,   453,   452,   454,   454,   454,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   457,   456,   459,   458,   461,   460,   463,   462,
     465,   464,   467,   466,   469,   468,   471,   470,   473,   472,
     474,   475,   476,   477,   479,   478,   480,   480,   481,   481,
     481,   483,   482,   484,   484,   484,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   487,   486,   489,   488,   490,
     490,   491,   491,   491,   493,   492,   495,   494,   496,   496,
     497,   497,   497,   498,   498,   498,   498,   498,   498,   498,
     498,   498,   498,   499,   500,   501,   503,   502,   505,   504,
     507,   506,   508,   510,   509,   511,   513,   512,   514,   514,
     515,   515,   515,   517,   516,   519,   518,   520,   520,   521,
     521,   521,   522,   522,   522,   522,   522,   522,   522,   522,
     522,   522,   522,   523,   525,   524,   526,   527,   528,   529,
     530,   532,   531,   534,   533,   535,   535,   536,   536,   536,
     538,   537,   540,   539,   541,   541,   541,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     542,   544,   543,   545,   547,   546,   549,   548,   551,   550,
     552,   552,   553,   553,   553,   555,   554,   557,   556,   558,
     558,   559,   559,   559,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   562,
     561,   564,   563,   566,   565,   568,   567,   570,   569,   572,
     571,   574,   573,   576,   575,   578,   577,   580,   579,   582,
     581,   584,   583,   585,   587,   586,   589,   588,   590,   590,
     591,   591,   591,   593,   592,   594,   594,   595,   595,   595,
     596,   596,   596,   596,   596,   596,   596,   596,   596,   596,
     596,   596,   596,   596,   596,   596,   596,   597,   599,   598,
     601,   600,   602,   603,   604,   606,   605,   607,   607,   608,
     608,   608,   610,   609,   611,   611,   611,   612,   612,   612,
     612,   612,   612,   612,   612,   612,   612,   612,   612,   612,
     614,   613,   615,   615,   615,   617,   616,   619,   618,   620,
     621,   623,   622,   624,   624,   625,   625,   625,   627,   626,
     628,   628,   628,   629,   629,   629,   629,   629,   631,   630,
     633,   632,   634,   634,   634,   635,   635,   635,   635,   635,
     635,   635,   637,   636,   638,   640,   639,   642,   641,   644,
     643,   645,   645,   646,   646,   646,   648,   647,   649,   649,
     649,   650,   650,   650,   650,   650,   650,   650,   652,   651,
     654,   653,   655,   655,   655,   656,   656,   656,   656,   656,
     656,   657,   659,   658,   660,   662,   661,   664,   663,   666,
     665,   667,   667,   667,   668,   668,   668,   668,   668,   668,
     668,   668,   668,   668,   668,   669,   671,   670,   672,   674,
     673,   675,   676,   678,   677,   679,   679,   681,   680,   683,
     682,   685,   684,   686,   686,   686,   687,   687,   689,   688,
     690,   692,   691,   693,   693,   693,   695,   694,   696,   696,
     696,   697,   697,   697,   697,   697,   697,   697,   698,   700,
     699,   702,   701,   703,   703,   703,   705,   704,   706,   706,
     706,   707,   707,   707,   707,   707,   709,   708,   710,   711,
     712,   714,   713,   716,   715,   717,   717,   717,   718,   718,
     718,   718,   718,   719,   720,   721,   722
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
       3,     3,     3,     3,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     3,     3,     3,     3,     0,     4,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     3,     3,
       3,     0,     6,     0,     6,     1,     3,     2,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     1,     3,     2,     1,     1,     1,
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     3,     3,     3,     3
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
  "\"ddns-qualifying-suffix\"", "\"ddns-update-on-renew\"",
  "\"ddns-use-conflict-resolution\"", "\"ddns-ttl-percent\"",
  "\"ddns-ttl\"", "\"ddns-ttl-min\"", "\"ddns-ttl-max\"",
  "\"store-extended-info\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"never-send\"",
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
  "ddns_qualifying_suffix", "$@24", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "ddns_conflict_resolution_mode", "$@25",
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
  "database_type", "$@40", "user", "$@41", "password", "$@42",
  "password_file", "$@43", "host", "$@44", "port", "name", "$@45",
  "persist", "lfc_interval", "readonly", "connect_timeout", "read_timeout",
  "write_timeout", "tcp_user_timeout", "max_reconnect_tries",
  "reconnect_wait_time", "on_fail", "$@46", "on_fail_mode",
  "retry_on_startup", "max_row_errors", "trust_anchor", "$@47",
  "cert_file", "$@48", "key_file", "$@49", "ssl_mode", "$@50",
  "cipher_list", "$@51", "host_reservation_identifiers", "$@52",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@53", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@54", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@55",
  "sub_hooks_library", "$@56", "hooks_params", "hooks_param", "library",
  "$@57", "parameters", "$@58", "expired_leases_processing", "$@59",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@60",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@61",
  "sub_subnet4", "$@62", "subnet4_params", "subnet4_param", "subnet",
  "$@63", "subnet_4o6_interface", "$@64", "subnet_4o6_interface_id",
  "$@65", "subnet_4o6_subnet", "$@66", "interface", "$@67", "client_class",
  "$@68", "network_client_classes", "$@69", "require_client_classes",
  "$@70", "evaluate_additional_classes", "$@71", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "shared_networks", "$@72", "shared_networks_content",
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
  "sub_pool4", "$@89", "pool_params", "pool_param", "pool_entry", "$@90",
  "pool_id", "user_context", "$@91", "comment", "$@92", "reservations",
  "$@93", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@94", "sub_reservation", "$@95", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@96", "server_hostname", "$@97", "boot_file_name", "$@98",
  "ip_address", "$@99", "duid", "$@100", "hw_address", "$@101",
  "client_id_value", "$@102", "circuit_id_value", "$@103", "flex_id_value",
  "$@104", "hostname", "$@105", "reservation_client_classes", "$@106",
  "relay", "$@107", "relay_map", "ip_addresses", "$@108", "client_classes",
  "$@109", "client_classes_list", "not_empty_classes_list",
  "client_class_entry", "$@110", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@111",
  "client_class_template_test", "$@112", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_sockets", "$@113",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@114", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@115",
  "control_socket_type_value", "control_socket_name", "$@116",
  "control_socket_address", "$@117", "control_socket_port",
  "cert_required", "http_headers", "$@118", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@119",
  "http_header_params", "http_header_param", "header_value", "$@120",
  "authentication", "$@121", "auth_params", "auth_param", "auth_type",
  "$@122", "auth_type_value", "realm", "$@123", "directory", "$@124",
  "clients", "$@125", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@126", "clients_params", "clients_param", "user_file",
  "$@127", "dhcp_queue_control", "$@128", "queue_control_params",
  "queue_control_param", "enable_queue", "queue_type", "$@129", "capacity",
  "arbitrary_map_entry", "$@130", "dhcp_ddns", "$@131", "sub_dhcp_ddns",
  "$@132", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "server_ip", "$@133", "server_port", "sender_ip", "$@134", "sender_port",
  "max_queue_size", "ncr_protocol", "$@135", "ncr_protocol_value",
  "ncr_format", "$@136", "config_control", "$@137", "sub_config_control",
  "$@138", "config_control_params", "config_control_param",
  "config_databases", "$@139", "config_fetch_wait_time", "loggers",
  "$@140", "loggers_entries", "logger_entry", "$@141", "logger_params",
  "logger_param", "debuglevel", "severity", "$@142", "output_options_list",
  "$@143", "output_options_list_content", "output_entry", "$@144",
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
       0,   336,   336,   336,   337,   337,   338,   338,   339,   339,
     340,   340,   341,   341,   342,   342,   343,   343,   344,   344,
     345,   345,   346,   346,   347,   347,   348,   348,   356,   357,
     358,   359,   360,   361,   362,   365,   370,   370,   381,   384,
     385,   388,   393,   399,   404,   404,   411,   412,   415,   419,
     423,   429,   429,   436,   437,   440,   444,   448,   458,   467,
     467,   482,   482,   496,   499,   505,   505,   514,   515,   516,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   597,   603,   609,   615,   621,   627,   633,   639,
     645,   651,   657,   663,   669,   669,   678,   684,   684,   693,
     699,   705,   711,   717,   723,   729,   729,   738,   741,   744,
     747,   750,   756,   756,   765,   765,   774,   783,   793,   793,
     802,   805,   808,   811,   816,   822,   828,   834,   840,   840,
     849,   849,   858,   864,   870,   876,   882,   888,   894,   900,
     906,   906,   918,   919,   920,   925,   926,   927,   928,   929,
     930,   931,   932,   933,   934,   937,   937,   946,   946,   957,
     957,   965,   966,   969,   969,   977,   979,   983,   989,   995,
    1001,  1007,  1007,  1020,  1020,  1031,  1032,  1033,  1038,  1039,
    1042,  1042,  1061,  1061,  1079,  1079,  1092,  1092,  1103,  1104,
    1107,  1108,  1109,  1114,  1114,  1124,  1125,  1126,  1131,  1132,
    1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,
    1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,
    1153,  1154,  1155,  1158,  1158,  1167,  1167,  1176,  1176,  1185,
    1185,  1194,  1194,  1203,  1209,  1209,  1218,  1224,  1230,  1236,
    1242,  1248,  1254,  1260,  1266,  1272,  1272,  1280,  1281,  1282,
    1285,  1291,  1297,  1297,  1306,  1306,  1315,  1315,  1324,  1324,
    1332,  1335,  1338,  1341,  1344,  1349,  1349,  1358,  1358,  1369,
    1370,  1371,  1376,  1377,  1378,  1379,  1380,  1383,  1388,  1393,
    1398,  1403,  1410,  1410,  1423,  1424,  1425,  1430,  1431,  1432,
    1433,  1434,  1435,  1438,  1444,  1450,  1456,  1456,  1467,  1468,
    1471,  1472,  1473,  1478,  1478,  1488,  1488,  1498,  1499,  1500,
    1503,  1506,  1507,  1510,  1510,  1519,  1519,  1528,  1528,  1540,
    1541,  1542,  1547,  1548,  1549,  1550,  1551,  1552,  1555,  1561,
    1567,  1573,  1579,  1585,  1594,  1594,  1608,  1609,  1612,  1613,
    1614,  1623,  1623,  1649,  1649,  1660,  1661,  1662,  1668,  1669,
    1670,  1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,
    1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,
    1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,
    1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,
    1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,
    1720,  1721,  1724,  1724,  1733,  1733,  1742,  1742,  1751,  1751,
    1760,  1760,  1769,  1769,  1779,  1779,  1791,  1791,  1802,  1802,
    1813,  1819,  1825,  1831,  1839,  1839,  1851,  1852,  1856,  1857,
    1858,  1863,  1863,  1871,  1872,  1873,  1878,  1879,  1880,  1881,
    1882,  1883,  1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,
    1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,
    1902,  1903,  1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,
    1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,  1920,  1921,
    1922,  1923,  1924,  1925,  1926,  1933,  1933,  1947,  1947,  1956,
    1957,  1960,  1961,  1962,  1969,  1969,  1984,  1984,  1998,  1999,
    2002,  2003,  2004,  2009,  2010,  2011,  2012,  2013,  2014,  2015,
    2016,  2017,  2018,  2021,  2023,  2029,  2031,  2031,  2040,  2040,
    2049,  2049,  2058,  2060,  2060,  2069,  2079,  2079,  2092,  2093,
    2098,  2099,  2100,  2107,  2107,  2119,  2119,  2131,  2132,  2137,
    2138,  2139,  2146,  2147,  2148,  2149,  2150,  2151,  2152,  2153,
    2154,  2155,  2156,  2159,  2161,  2161,  2170,  2172,  2174,  2180,
    2186,  2192,  2192,  2206,  2206,  2219,  2220,  2223,  2224,  2225,
    2230,  2230,  2240,  2240,  2250,  2251,  2252,  2257,  2258,  2259,
    2260,  2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,
    2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,
    2280,  2283,  2283,  2292,  2298,  2298,  2323,  2323,  2353,  2353,
    2364,  2365,  2368,  2369,  2370,  2375,  2375,  2384,  2384,  2393,
    2394,  2397,  2398,  2399,  2405,  2406,  2407,  2408,  2409,  2410,
    2411,  2412,  2413,  2414,  2415,  2416,  2417,  2418,  2419,  2422,
    2422,  2431,  2431,  2440,  2440,  2449,  2449,  2458,  2458,  2467,
    2467,  2476,  2476,  2485,  2485,  2494,  2494,  2503,  2503,  2512,
    2512,  2526,  2526,  2537,  2540,  2540,  2554,  2554,  2565,  2566,
    2569,  2570,  2571,  2576,  2576,  2586,  2587,  2590,  2591,  2592,
    2597,  2598,  2599,  2600,  2601,  2602,  2603,  2604,  2605,  2606,
    2607,  2608,  2609,  2610,  2611,  2612,  2613,  2616,  2618,  2618,
    2627,  2627,  2637,  2643,  2651,  2659,  2659,  2670,  2671,  2674,
    2675,  2676,  2681,  2681,  2689,  2690,  2691,  2696,  2697,  2698,
    2699,  2700,  2701,  2702,  2703,  2704,  2705,  2706,  2707,  2708,
    2711,  2711,  2720,  2721,  2722,  2725,  2725,  2734,  2734,  2743,
    2749,  2755,  2755,  2766,  2767,  2770,  2771,  2772,  2777,  2777,
    2785,  2786,  2787,  2792,  2793,  2794,  2795,  2796,  2799,  2799,
    2810,  2810,  2823,  2824,  2825,  2830,  2831,  2832,  2833,  2834,
    2835,  2836,  2839,  2839,  2847,  2850,  2850,  2859,  2859,  2868,
    2868,  2879,  2880,  2883,  2884,  2885,  2890,  2890,  2898,  2899,
    2900,  2905,  2906,  2907,  2908,  2909,  2910,  2911,  2914,  2914,
    2925,  2925,  2938,  2939,  2940,  2945,  2946,  2947,  2948,  2949,
    2950,  2953,  2959,  2959,  2968,  2974,  2974,  2984,  2984,  2997,
    2997,  3007,  3008,  3009,  3014,  3015,  3016,  3017,  3018,  3019,
    3020,  3021,  3022,  3023,  3024,  3027,  3033,  3033,  3042,  3048,
    3048,  3057,  3063,  3069,  3069,  3078,  3079,  3082,  3082,  3093,
    3093,  3105,  3105,  3115,  3116,  3117,  3123,  3124,  3127,  3127,
    3138,  3146,  3146,  3159,  3160,  3161,  3167,  3167,  3175,  3176,
    3177,  3182,  3183,  3184,  3185,  3186,  3187,  3188,  3191,  3197,
    3197,  3206,  3206,  3217,  3218,  3219,  3224,  3224,  3232,  3233,
    3234,  3239,  3240,  3241,  3242,  3243,  3246,  3246,  3255,  3261,
    3267,  3273,  3273,  3282,  3282,  3293,  3294,  3295,  3300,  3301,
    3302,  3303,  3304,  3307,  3313,  3319,  3325
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
#line 6969 "dhcp4_parser.cc"

#line 3331 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
