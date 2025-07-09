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

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 657 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 153: // $@20: %empty
#line 663 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp4_parser.cc"
    break;

  case 154: // server_tag: "server-tag" $@20 ":" "constant string"
#line 666 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 155: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 672 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 156: // $@21: %empty
#line 678 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc"
    break;

  case 157: // allocator: "allocator" $@21 ":" "constant string"
#line 681 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 158: // echo_client_id: "echo-client-id" ":" "boolean"
#line 687 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 159: // match_client_id: "match-client-id" ":" "boolean"
#line 693 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 160: // authoritative: "authoritative" ":" "boolean"
#line 699 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 161: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 705 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 162: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 711 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 163: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 717 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 164: // $@22: %empty
#line 723 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 726 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1384 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-present"
#line 732 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1392 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "never"
#line 735 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1400 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "always"
#line 738 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1408 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "when-not-present"
#line 741 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1416 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "boolean"
#line 744 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1425 "dhcp4_parser.cc"
    break;

  case 171: // $@23: %empty
#line 750 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 172: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 753 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 173: // $@24: %empty
#line 759 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp4_parser.cc"
    break;

  case 174: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 762 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 175: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 768 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 176: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 777 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1487 "dhcp4_parser.cc"
    break;

  case 177: // $@25: %empty
#line 787 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 790 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 796 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1513 "dhcp4_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 799 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1521 "dhcp4_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 802 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1529 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 805 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1537 "dhcp4_parser.cc"
    break;

  case 183: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 810 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 184: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 816 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 185: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 822 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1567 "dhcp4_parser.cc"
    break;

  case 186: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 828 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 187: // $@26: %empty
#line 834 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 188: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 837 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 189: // $@27: %empty
#line 843 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 190: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 846 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 191: // store_extended_info: "store-extended-info" ":" "boolean"
#line 852 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 192: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 858 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1635 "dhcp4_parser.cc"
    break;

  case 193: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 864 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 870 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 876 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 882 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 197: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 888 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1685 "dhcp4_parser.cc"
    break;

  case 198: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 894 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1695 "dhcp4_parser.cc"
    break;

  case 199: // $@28: %empty
#line 900 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 200: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 906 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 914 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1725 "dhcp4_parser.cc"
    break;

  case 214: // $@29: %empty
#line 931 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 215: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 935 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1744 "dhcp4_parser.cc"
    break;

  case 216: // $@30: %empty
#line 940 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 217: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 946 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 218: // $@31: %empty
#line 951 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 219: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 954 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 220: // socket_type: "raw"
#line 959 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1789 "dhcp4_parser.cc"
    break;

  case 221: // socket_type: "udp"
#line 960 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1795 "dhcp4_parser.cc"
    break;

  case 222: // $@32: %empty
#line 963 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1804 "dhcp4_parser.cc"
    break;

  case 223: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 966 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1813 "dhcp4_parser.cc"
    break;

  case 224: // outbound_interface_value: "same-as-inbound"
#line 971 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1821 "dhcp4_parser.cc"
    break;

  case 225: // outbound_interface_value: "use-routing"
#line 973 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1829 "dhcp4_parser.cc"
    break;

  case 226: // re_detect: "re-detect" ":" "boolean"
#line 977 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1839 "dhcp4_parser.cc"
    break;

  case 227: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 983 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1849 "dhcp4_parser.cc"
    break;

  case 228: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 989 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1859 "dhcp4_parser.cc"
    break;

  case 229: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 995 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 230: // $@33: %empty
#line 1001 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 231: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 1007 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1892 "dhcp4_parser.cc"
    break;

  case 232: // $@34: %empty
#line 1014 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1904 "dhcp4_parser.cc"
    break;

  case 233: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 1020 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1913 "dhcp4_parser.cc"
    break;

  case 236: // sanity_checks_params: sanity_checks_params ","
#line 1027 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1921 "dhcp4_parser.cc"
    break;

  case 239: // $@35: %empty
#line 1036 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1930 "dhcp4_parser.cc"
    break;

  case 240: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1039 "dhcp4_parser.yy"
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
#line 1950 "dhcp4_parser.cc"
    break;

  case 241: // $@36: %empty
#line 1055 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc"
    break;

  case 242: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1058 "dhcp4_parser.yy"
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
#line 1978 "dhcp4_parser.cc"
    break;

  case 243: // $@37: %empty
#line 1073 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1990 "dhcp4_parser.cc"
    break;

  case 244: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1079 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 245: // $@38: %empty
#line 1086 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2013 "dhcp4_parser.cc"
    break;

  case 246: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1092 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 251: // not_empty_database_list: not_empty_database_list ","
#line 1103 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2030 "dhcp4_parser.cc"
    break;

  case 252: // $@39: %empty
#line 1108 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 253: // database: "{" $@39 database_map_params "}"
#line 1112 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 256: // database_map_params: database_map_params ","
#line 1120 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2058 "dhcp4_parser.cc"
    break;

  case 281: // $@40: %empty
#line 1151 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc"
    break;

  case 282: // database_type: "type" $@40 ":" "constant string"
#line 1154 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 283: // $@41: %empty
#line 1160 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2086 "dhcp4_parser.cc"
    break;

  case 284: // user: "user" $@41 ":" "constant string"
#line 1163 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 285: // $@42: %empty
#line 1169 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp4_parser.cc"
    break;

  case 286: // password: "password" $@42 ":" "constant string"
#line 1172 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 287: // $@43: %empty
#line 1178 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp4_parser.cc"
    break;

  case 288: // host: "host" $@43 ":" "constant string"
#line 1181 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 289: // port: "port" ":" "integer"
#line 1187 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 290: // $@44: %empty
#line 1193 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2153 "dhcp4_parser.cc"
    break;

  case 291: // name: "name" $@44 ":" "constant string"
#line 1196 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 292: // persist: "persist" ":" "boolean"
#line 1202 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 293: // lfc_interval: "lfc-interval" ":" "integer"
#line 1208 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 294: // readonly: "readonly" ":" "boolean"
#line 1214 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2193 "dhcp4_parser.cc"
    break;

  case 295: // connect_timeout: "connect-timeout" ":" "integer"
#line 1220 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 296: // read_timeout: "read-timeout" ":" "integer"
#line 1226 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 297: // write_timeout: "write-timeout" ":" "integer"
#line 1232 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 298: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1238 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2233 "dhcp4_parser.cc"
    break;

  case 299: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1244 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2243 "dhcp4_parser.cc"
    break;

  case 300: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1250 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2253 "dhcp4_parser.cc"
    break;

  case 301: // $@45: %empty
#line 1256 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2262 "dhcp4_parser.cc"
    break;

  case 302: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1259 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 303: // on_fail_mode: "stop-retry-exit"
#line 1264 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2277 "dhcp4_parser.cc"
    break;

  case 304: // on_fail_mode: "serve-retry-exit"
#line 1265 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2283 "dhcp4_parser.cc"
    break;

  case 305: // on_fail_mode: "serve-retry-continue"
#line 1266 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2289 "dhcp4_parser.cc"
    break;

  case 306: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1269 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 307: // max_row_errors: "max-row-errors" ":" "integer"
#line 1275 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 308: // $@46: %empty
#line 1281 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2318 "dhcp4_parser.cc"
    break;

  case 309: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1284 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 310: // $@47: %empty
#line 1290 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 311: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1293 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 312: // $@48: %empty
#line 1299 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc"
    break;

  case 313: // key_file: "key-file" $@48 ":" "constant string"
#line 1302 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 314: // $@49: %empty
#line 1308 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2375 "dhcp4_parser.cc"
    break;

  case 315: // ssl_mode: "ssl-mode" $@49 ":" ssl_mode
#line 1311 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2384 "dhcp4_parser.cc"
    break;

  case 316: // ssl_mode: "disable"
#line 1316 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2392 "dhcp4_parser.cc"
    break;

  case 317: // ssl_mode: "prefer"
#line 1319 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2400 "dhcp4_parser.cc"
    break;

  case 318: // ssl_mode: "require"
#line 1322 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2408 "dhcp4_parser.cc"
    break;

  case 319: // ssl_mode: "verify-ca"
#line 1325 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2416 "dhcp4_parser.cc"
    break;

  case 320: // ssl_mode: "verify-full"
#line 1328 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2424 "dhcp4_parser.cc"
    break;

  case 321: // $@50: %empty
#line 1333 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2433 "dhcp4_parser.cc"
    break;

  case 322: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1336 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2443 "dhcp4_parser.cc"
    break;

  case 323: // $@51: %empty
#line 1342 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 324: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1348 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 327: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1355 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2472 "dhcp4_parser.cc"
    break;

  case 333: // duid_id: "duid"
#line 1367 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2481 "dhcp4_parser.cc"
    break;

  case 334: // hw_address_id: "hw-address"
#line 1372 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2490 "dhcp4_parser.cc"
    break;

  case 335: // circuit_id: "circuit-id"
#line 1377 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2499 "dhcp4_parser.cc"
    break;

  case 336: // client_id: "client-id"
#line 1382 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2508 "dhcp4_parser.cc"
    break;

  case 337: // flex_id: "flex-id"
#line 1387 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2517 "dhcp4_parser.cc"
    break;

  case 338: // $@52: %empty
#line 1394 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2529 "dhcp4_parser.cc"
    break;

  case 339: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1400 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 342: // multi_threading_params: multi_threading_params ","
#line 1409 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2548 "dhcp4_parser.cc"
    break;

  case 349: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1422 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 350: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1428 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 351: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1434 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2578 "dhcp4_parser.cc"
    break;

  case 352: // $@53: %empty
#line 1440 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 353: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1446 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 358: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1457 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2607 "dhcp4_parser.cc"
    break;

  case 359: // $@54: %empty
#line 1462 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2617 "dhcp4_parser.cc"
    break;

  case 360: // hooks_library: "{" $@54 hooks_params "}"
#line 1466 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2627 "dhcp4_parser.cc"
    break;

  case 361: // $@55: %empty
#line 1472 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 362: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1476 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 365: // hooks_params: hooks_params ","
#line 1484 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2655 "dhcp4_parser.cc"
    break;

  case 369: // $@56: %empty
#line 1494 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2664 "dhcp4_parser.cc"
    break;

  case 370: // library: "library" $@56 ":" "constant string"
#line 1497 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2674 "dhcp4_parser.cc"
    break;

  case 371: // $@57: %empty
#line 1503 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 372: // parameters: "parameters" $@57 ":" map_value
#line 1506 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 373: // $@58: %empty
#line 1512 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2704 "dhcp4_parser.cc"
    break;

  case 374: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1518 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2714 "dhcp4_parser.cc"
    break;

  case 377: // expired_leases_params: expired_leases_params ","
#line 1526 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2722 "dhcp4_parser.cc"
    break;

  case 384: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1539 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 385: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1545 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 386: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1551 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 387: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1557 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 388: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1563 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 389: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1569 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 390: // $@59: %empty
#line 1578 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2794 "dhcp4_parser.cc"
    break;

  case 391: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1584 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2803 "dhcp4_parser.cc"
    break;

  case 396: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1598 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2811 "dhcp4_parser.cc"
    break;

  case 397: // $@60: %empty
#line 1607 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 398: // subnet4: "{" $@60 subnet4_params "}"
#line 1611 "dhcp4_parser.yy"
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
#line 2847 "dhcp4_parser.cc"
    break;

  case 399: // $@61: %empty
#line 1633 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2857 "dhcp4_parser.cc"
    break;

  case 400: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1637 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2867 "dhcp4_parser.cc"
    break;

  case 403: // subnet4_params: subnet4_params ","
#line 1646 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2875 "dhcp4_parser.cc"
    break;

  case 457: // $@62: %empty
#line 1707 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp4_parser.cc"
    break;

  case 458: // subnet: "subnet" $@62 ":" "constant string"
#line 1710 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2894 "dhcp4_parser.cc"
    break;

  case 459: // $@63: %empty
#line 1716 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2903 "dhcp4_parser.cc"
    break;

  case 460: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1719 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2913 "dhcp4_parser.cc"
    break;

  case 461: // $@64: %empty
#line 1725 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp4_parser.cc"
    break;

  case 462: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1728 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 463: // $@65: %empty
#line 1734 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 464: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1737 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 465: // $@66: %empty
#line 1743 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 466: // interface: "interface" $@66 ":" "constant string"
#line 1746 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 467: // $@67: %empty
#line 1752 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2979 "dhcp4_parser.cc"
    break;

  case 468: // client_class: "client-class" $@67 ":" "constant string"
#line 1755 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 469: // $@68: %empty
#line 1762 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3001 "dhcp4_parser.cc"
    break;

  case 470: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1768 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3010 "dhcp4_parser.cc"
    break;

  case 471: // $@69: %empty
#line 1774 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3022 "dhcp4_parser.cc"
    break;

  case 472: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1780 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3031 "dhcp4_parser.cc"
    break;

  case 473: // $@70: %empty
#line 1785 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 474: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1791 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 475: // reservations_global: "reservations-global" ":" "boolean"
#line 1796 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 476: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1802 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 477: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1808 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 478: // id: "id" ":" "integer"
#line 1814 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 479: // $@71: %empty
#line 1822 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3104 "dhcp4_parser.cc"
    break;

  case 480: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1828 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3113 "dhcp4_parser.cc"
    break;

  case 485: // shared_networks_list: shared_networks_list ","
#line 1841 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3121 "dhcp4_parser.cc"
    break;

  case 486: // $@72: %empty
#line 1846 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3131 "dhcp4_parser.cc"
    break;

  case 487: // shared_network: "{" $@72 shared_network_params "}"
#line 1850 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 490: // shared_network_params: shared_network_params ","
#line 1856 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3147 "dhcp4_parser.cc"
    break;

  case 539: // $@73: %empty
#line 1915 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 540: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1921 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3168 "dhcp4_parser.cc"
    break;

  case 541: // $@74: %empty
#line 1929 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 542: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1932 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3185 "dhcp4_parser.cc"
    break;

  case 547: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1944 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3193 "dhcp4_parser.cc"
    break;

  case 548: // $@75: %empty
#line 1951 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3203 "dhcp4_parser.cc"
    break;

  case 549: // option_def_entry: "{" $@75 option_def_params "}"
#line 1955 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3215 "dhcp4_parser.cc"
    break;

  case 550: // $@76: %empty
#line 1966 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 551: // sub_option_def: "{" $@76 option_def_params "}"
#line 1970 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3237 "dhcp4_parser.cc"
    break;

  case 556: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1986 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3245 "dhcp4_parser.cc"
    break;

  case 568: // code: "code" ":" "integer"
#line 2005 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3255 "dhcp4_parser.cc"
    break;

  case 570: // $@77: %empty
#line 2013 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3264 "dhcp4_parser.cc"
    break;

  case 571: // option_def_type: "type" $@77 ":" "constant string"
#line 2016 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3274 "dhcp4_parser.cc"
    break;

  case 572: // $@78: %empty
#line 2022 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 573: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 2025 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 574: // $@79: %empty
#line 2031 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 575: // space: "space" $@79 ":" "constant string"
#line 2034 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 577: // $@80: %empty
#line 2042 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3321 "dhcp4_parser.cc"
    break;

  case 578: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2045 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3331 "dhcp4_parser.cc"
    break;

  case 579: // option_def_array: "array" ":" "boolean"
#line 2051 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 580: // $@81: %empty
#line 2061 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 581: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2067 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3362 "dhcp4_parser.cc"
    break;

  case 586: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2082 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3370 "dhcp4_parser.cc"
    break;

  case 587: // $@82: %empty
#line 2089 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3380 "dhcp4_parser.cc"
    break;

  case 588: // option_data_entry: "{" $@82 option_data_params "}"
#line 2093 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 589: // $@83: %empty
#line 2101 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3399 "dhcp4_parser.cc"
    break;

  case 590: // sub_option_data: "{" $@83 option_data_params "}"
#line 2105 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 595: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2121 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3416 "dhcp4_parser.cc"
    break;

  case 608: // $@84: %empty
#line 2143 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp4_parser.cc"
    break;

  case 609: // option_data_data: "data" $@84 ":" "constant string"
#line 2146 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 612: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2156 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3445 "dhcp4_parser.cc"
    break;

  case 613: // option_data_always_send: "always-send" ":" "boolean"
#line 2162 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3455 "dhcp4_parser.cc"
    break;

  case 614: // option_data_never_send: "never-send" ":" "boolean"
#line 2168 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3465 "dhcp4_parser.cc"
    break;

  case 615: // $@85: %empty
#line 2174 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc"
    break;

  case 616: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2180 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3486 "dhcp4_parser.cc"
    break;

  case 617: // $@86: %empty
#line 2188 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3498 "dhcp4_parser.cc"
    break;

  case 618: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2194 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp4_parser.cc"
    break;

  case 623: // not_empty_pools_list: not_empty_pools_list ","
#line 2207 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3515 "dhcp4_parser.cc"
    break;

  case 624: // $@87: %empty
#line 2212 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 625: // pool_list_entry: "{" $@87 pool_params "}"
#line 2216 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 626: // $@88: %empty
#line 2222 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 627: // sub_pool4: "{" $@88 pool_params "}"
#line 2226 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 630: // pool_params: pool_params ","
#line 2234 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3563 "dhcp4_parser.cc"
    break;

  case 655: // $@89: %empty
#line 2265 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 656: // pool_entry: "pool" $@89 ":" "constant string"
#line 2268 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 657: // pool_id: "pool-id" ":" "integer"
#line 2274 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 658: // $@90: %empty
#line 2280 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3600 "dhcp4_parser.cc"
    break;

  case 659: // user_context: "user-context" $@90 ":" map_value
#line 2282 "dhcp4_parser.yy"
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
#line 3627 "dhcp4_parser.cc"
    break;

  case 660: // $@91: %empty
#line 2305 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 661: // comment: "comment" $@91 ":" "constant string"
#line 2307 "dhcp4_parser.yy"
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
#line 3664 "dhcp4_parser.cc"
    break;

  case 662: // $@92: %empty
#line 2335 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3676 "dhcp4_parser.cc"
    break;

  case 663: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2341 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3685 "dhcp4_parser.cc"
    break;

  case 668: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2352 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3693 "dhcp4_parser.cc"
    break;

  case 669: // $@93: %empty
#line 2357 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 670: // reservation: "{" $@93 reservation_params "}"
#line 2361 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 671: // $@94: %empty
#line 2366 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 672: // sub_reservation: "{" $@94 reservation_params "}"
#line 2370 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 677: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2381 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3739 "dhcp4_parser.cc"
    break;

  case 693: // $@95: %empty
#line 2404 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3748 "dhcp4_parser.cc"
    break;

  case 694: // next_server: "next-server" $@95 ":" "constant string"
#line 2407 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 695: // $@96: %empty
#line 2413 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3767 "dhcp4_parser.cc"
    break;

  case 696: // server_hostname: "server-hostname" $@96 ":" "constant string"
#line 2416 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 697: // $@97: %empty
#line 2422 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 698: // boot_file_name: "boot-file-name" $@97 ":" "constant string"
#line 2425 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 699: // $@98: %empty
#line 2431 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3805 "dhcp4_parser.cc"
    break;

  case 700: // ip_address: "ip-address" $@98 ":" "constant string"
#line 2434 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 701: // $@99: %empty
#line 2440 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3824 "dhcp4_parser.cc"
    break;

  case 702: // duid: "duid" $@99 ":" "constant string"
#line 2443 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 703: // $@100: %empty
#line 2449 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3843 "dhcp4_parser.cc"
    break;

  case 704: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2452 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 705: // $@101: %empty
#line 2458 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3862 "dhcp4_parser.cc"
    break;

  case 706: // client_id_value: "client-id" $@101 ":" "constant string"
#line 2461 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 707: // $@102: %empty
#line 2467 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 708: // circuit_id_value: "circuit-id" $@102 ":" "constant string"
#line 2470 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 709: // $@103: %empty
#line 2476 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3900 "dhcp4_parser.cc"
    break;

  case 710: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2479 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 711: // $@104: %empty
#line 2485 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 712: // hostname: "hostname" $@104 ":" "constant string"
#line 2488 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 713: // $@105: %empty
#line 2494 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3941 "dhcp4_parser.cc"
    break;

  case 714: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2500 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3950 "dhcp4_parser.cc"
    break;

  case 715: // $@106: %empty
#line 2508 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3962 "dhcp4_parser.cc"
    break;

  case 716: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2514 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3971 "dhcp4_parser.cc"
    break;

  case 718: // $@107: %empty
#line 2522 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3983 "dhcp4_parser.cc"
    break;

  case 719: // ip_addresses: "ip-addresses" $@107 ":" list_strings
#line 2528 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3992 "dhcp4_parser.cc"
    break;

  case 720: // $@108: %empty
#line 2536 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4004 "dhcp4_parser.cc"
    break;

  case 721: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2542 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4013 "dhcp4_parser.cc"
    break;

  case 724: // client_classes_list: client_classes_list ","
#line 2549 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4021 "dhcp4_parser.cc"
    break;

  case 725: // $@109: %empty
#line 2554 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 726: // client_class_entry: "{" $@109 client_class_params "}"
#line 2558 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 731: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2570 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4049 "dhcp4_parser.cc"
    break;

  case 750: // $@110: %empty
#line 2596 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4058 "dhcp4_parser.cc"
    break;

  case 751: // client_class_test: "test" $@110 ":" "constant string"
#line 2599 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4068 "dhcp4_parser.cc"
    break;

  case 752: // $@111: %empty
#line 2605 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4077 "dhcp4_parser.cc"
    break;

  case 753: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2608 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 754: // only_if_required: "only-if-required" ":" "boolean"
#line 2615 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 755: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2621 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4107 "dhcp4_parser.cc"
    break;

  case 756: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2629 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4117 "dhcp4_parser.cc"
    break;

  case 757: // $@112: %empty
#line 2637 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4130 "dhcp4_parser.cc"
    break;

  case 758: // control_socket: "control-socket" $@112 ":" "{" control_socket_params "}"
#line 2644 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 759: // $@113: %empty
#line 2649 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4152 "dhcp4_parser.cc"
    break;

  case 760: // control_sockets: "control-sockets" $@113 ":" "[" control_socket_list "]"
#line 2656 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 765: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2667 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4169 "dhcp4_parser.cc"
    break;

  case 766: // $@114: %empty
#line 2672 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4179 "dhcp4_parser.cc"
    break;

  case 767: // control_socket_entry: "{" $@114 control_socket_params "}"
#line 2676 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4187 "dhcp4_parser.cc"
    break;

  case 770: // control_socket_params: control_socket_params ","
#line 2682 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4195 "dhcp4_parser.cc"
    break;

  case 784: // $@115: %empty
#line 2702 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4204 "dhcp4_parser.cc"
    break;

  case 785: // control_socket_type: "socket-type" $@115 ":" control_socket_type_value
#line 2705 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4213 "dhcp4_parser.cc"
    break;

  case 786: // control_socket_type_value: "unix"
#line 2711 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4219 "dhcp4_parser.cc"
    break;

  case 787: // control_socket_type_value: "http"
#line 2712 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4225 "dhcp4_parser.cc"
    break;

  case 788: // control_socket_type_value: "https"
#line 2713 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4231 "dhcp4_parser.cc"
    break;

  case 789: // $@116: %empty
#line 2716 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4241 "dhcp4_parser.cc"
    break;

  case 790: // control_socket_name: "socket-name" $@116 ":" "constant string"
#line 2720 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4251 "dhcp4_parser.cc"
    break;

  case 791: // $@117: %empty
#line 2726 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4261 "dhcp4_parser.cc"
    break;

  case 792: // control_socket_address: "socket-address" $@117 ":" "constant string"
#line 2730 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4271 "dhcp4_parser.cc"
    break;

  case 793: // control_socket_port: "socket-port" ":" "integer"
#line 2736 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4281 "dhcp4_parser.cc"
    break;

  case 794: // cert_required: "cert-required" ":" "boolean"
#line 2742 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4291 "dhcp4_parser.cc"
    break;

  case 795: // $@118: %empty
#line 2748 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 796: // http_headers: "http-headers" $@118 ":" "[" http_header_list "]"
#line 2754 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4312 "dhcp4_parser.cc"
    break;

  case 801: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2765 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4320 "dhcp4_parser.cc"
    break;

  case 802: // $@119: %empty
#line 2770 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4330 "dhcp4_parser.cc"
    break;

  case 803: // http_header: "{" $@119 http_header_params "}"
#line 2774 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 806: // http_header_params: http_header_params ","
#line 2780 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4346 "dhcp4_parser.cc"
    break;

  case 812: // $@120: %empty
#line 2792 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4355 "dhcp4_parser.cc"
    break;

  case 813: // header_value: "value" $@120 ":" "constant string"
#line 2795 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4365 "dhcp4_parser.cc"
    break;

  case 814: // $@121: %empty
#line 2803 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4377 "dhcp4_parser.cc"
    break;

  case 815: // authentication: "authentication" $@121 ":" "{" auth_params "}"
#line 2809 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4388 "dhcp4_parser.cc"
    break;

  case 818: // auth_params: auth_params ","
#line 2818 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4396 "dhcp4_parser.cc"
    break;

  case 826: // $@122: %empty
#line 2832 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4405 "dhcp4_parser.cc"
    break;

  case 827: // auth_type: "type" $@122 ":" auth_type_value
#line 2835 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4414 "dhcp4_parser.cc"
    break;

  case 828: // auth_type_value: "basic"
#line 2840 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4420 "dhcp4_parser.cc"
    break;

  case 829: // $@123: %empty
#line 2843 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4429 "dhcp4_parser.cc"
    break;

  case 830: // realm: "realm" $@123 ":" "constant string"
#line 2846 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4439 "dhcp4_parser.cc"
    break;

  case 831: // $@124: %empty
#line 2852 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4448 "dhcp4_parser.cc"
    break;

  case 832: // directory: "directory" $@124 ":" "constant string"
#line 2855 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4458 "dhcp4_parser.cc"
    break;

  case 833: // $@125: %empty
#line 2861 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4470 "dhcp4_parser.cc"
    break;

  case 834: // clients: "clients" $@125 ":" "[" clients_list "]"
#line 2867 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4479 "dhcp4_parser.cc"
    break;

  case 839: // not_empty_clients_list: not_empty_clients_list ","
#line 2878 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4487 "dhcp4_parser.cc"
    break;

  case 840: // $@126: %empty
#line 2883 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4497 "dhcp4_parser.cc"
    break;

  case 841: // basic_auth: "{" $@126 clients_params "}"
#line 2887 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 844: // clients_params: clients_params ","
#line 2893 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4513 "dhcp4_parser.cc"
    break;

  case 852: // $@127: %empty
#line 2907 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4522 "dhcp4_parser.cc"
    break;

  case 853: // user_file: "user-file" $@127 ":" "constant string"
#line 2910 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 854: // $@128: %empty
#line 2916 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4541 "dhcp4_parser.cc"
    break;

  case 855: // password_file: "password-file" $@128 ":" "constant string"
#line 2919 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4551 "dhcp4_parser.cc"
    break;

  case 856: // $@129: %empty
#line 2927 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4563 "dhcp4_parser.cc"
    break;

  case 857: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2933 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4574 "dhcp4_parser.cc"
    break;

  case 860: // queue_control_params: queue_control_params ","
#line 2942 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4582 "dhcp4_parser.cc"
    break;

  case 867: // enable_queue: "enable-queue" ":" "boolean"
#line 2955 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4592 "dhcp4_parser.cc"
    break;

  case 868: // $@130: %empty
#line 2961 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4601 "dhcp4_parser.cc"
    break;

  case 869: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2964 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4611 "dhcp4_parser.cc"
    break;

  case 870: // capacity: "capacity" ":" "integer"
#line 2970 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4621 "dhcp4_parser.cc"
    break;

  case 871: // $@131: %empty
#line 2976 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4630 "dhcp4_parser.cc"
    break;

  case 872: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2979 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4639 "dhcp4_parser.cc"
    break;

  case 873: // $@132: %empty
#line 2986 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4651 "dhcp4_parser.cc"
    break;

  case 874: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 2992 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4662 "dhcp4_parser.cc"
    break;

  case 875: // $@133: %empty
#line 2999 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4672 "dhcp4_parser.cc"
    break;

  case 876: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 3003 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4682 "dhcp4_parser.cc"
    break;

  case 879: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3011 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4690 "dhcp4_parser.cc"
    break;

  case 891: // enable_updates: "enable-updates" ":" "boolean"
#line 3029 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4700 "dhcp4_parser.cc"
    break;

  case 892: // $@134: %empty
#line 3035 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4709 "dhcp4_parser.cc"
    break;

  case 893: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3038 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4719 "dhcp4_parser.cc"
    break;

  case 894: // server_port: "server-port" ":" "integer"
#line 3044 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4729 "dhcp4_parser.cc"
    break;

  case 895: // $@135: %empty
#line 3050 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4738 "dhcp4_parser.cc"
    break;

  case 896: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3053 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4748 "dhcp4_parser.cc"
    break;

  case 897: // sender_port: "sender-port" ":" "integer"
#line 3059 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4758 "dhcp4_parser.cc"
    break;

  case 898: // max_queue_size: "max-queue-size" ":" "integer"
#line 3065 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4768 "dhcp4_parser.cc"
    break;

  case 899: // $@136: %empty
#line 3071 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 900: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3074 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4786 "dhcp4_parser.cc"
    break;

  case 901: // ncr_protocol_value: "udp"
#line 3080 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4792 "dhcp4_parser.cc"
    break;

  case 902: // ncr_protocol_value: "tcp"
#line 3081 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4798 "dhcp4_parser.cc"
    break;

  case 903: // $@137: %empty
#line 3084 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4807 "dhcp4_parser.cc"
    break;

  case 904: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3087 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4817 "dhcp4_parser.cc"
    break;

  case 905: // $@138: %empty
#line 3095 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4829 "dhcp4_parser.cc"
    break;

  case 906: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3101 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4839 "dhcp4_parser.cc"
    break;

  case 907: // $@139: %empty
#line 3107 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4849 "dhcp4_parser.cc"
    break;

  case 908: // sub_config_control: "{" $@139 config_control_params "}"
#line 3111 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4858 "dhcp4_parser.cc"
    break;

  case 911: // config_control_params: config_control_params ","
#line 3119 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4866 "dhcp4_parser.cc"
    break;

  case 914: // $@140: %empty
#line 3129 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4878 "dhcp4_parser.cc"
    break;

  case 915: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3135 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4887 "dhcp4_parser.cc"
    break;

  case 916: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3140 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4897 "dhcp4_parser.cc"
    break;

  case 917: // $@141: %empty
#line 3148 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4909 "dhcp4_parser.cc"
    break;

  case 918: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3154 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4918 "dhcp4_parser.cc"
    break;

  case 921: // loggers_entries: loggers_entries ","
#line 3163 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4926 "dhcp4_parser.cc"
    break;

  case 922: // $@142: %empty
#line 3169 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4936 "dhcp4_parser.cc"
    break;

  case 923: // logger_entry: "{" $@142 logger_params "}"
#line 3173 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4944 "dhcp4_parser.cc"
    break;

  case 926: // logger_params: logger_params ","
#line 3179 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4952 "dhcp4_parser.cc"
    break;

  case 934: // debuglevel: "debuglevel" ":" "integer"
#line 3193 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4962 "dhcp4_parser.cc"
    break;

  case 935: // $@143: %empty
#line 3199 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4971 "dhcp4_parser.cc"
    break;

  case 936: // severity: "severity" $@143 ":" "constant string"
#line 3202 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4981 "dhcp4_parser.cc"
    break;

  case 937: // $@144: %empty
#line 3208 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4993 "dhcp4_parser.cc"
    break;

  case 938: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3214 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5002 "dhcp4_parser.cc"
    break;

  case 941: // output_options_list_content: output_options_list_content ","
#line 3221 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5010 "dhcp4_parser.cc"
    break;

  case 942: // $@145: %empty
#line 3226 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5020 "dhcp4_parser.cc"
    break;

  case 943: // output_entry: "{" $@145 output_params_list "}"
#line 3230 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5028 "dhcp4_parser.cc"
    break;

  case 946: // output_params_list: output_params_list ","
#line 3236 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5036 "dhcp4_parser.cc"
    break;

  case 952: // $@146: %empty
#line 3248 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5045 "dhcp4_parser.cc"
    break;

  case 953: // output: "output" $@146 ":" "constant string"
#line 3251 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5055 "dhcp4_parser.cc"
    break;

  case 954: // flush: "flush" ":" "boolean"
#line 3257 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5065 "dhcp4_parser.cc"
    break;

  case 955: // maxsize: "maxsize" ":" "integer"
#line 3263 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5075 "dhcp4_parser.cc"
    break;

  case 956: // maxver: "maxver" ":" "integer"
#line 3269 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5085 "dhcp4_parser.cc"
    break;

  case 957: // $@147: %empty
#line 3275 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5094 "dhcp4_parser.cc"
    break;

  case 958: // pattern: "pattern" $@147 ":" "constant string"
#line 3278 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5104 "dhcp4_parser.cc"
    break;

  case 959: // $@148: %empty
#line 3284 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5116 "dhcp4_parser.cc"
    break;

  case 960: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3290 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5125 "dhcp4_parser.cc"
    break;

  case 963: // compatibility_params: compatibility_params ","
#line 3297 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5133 "dhcp4_parser.cc"
    break;

  case 969: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3309 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5143 "dhcp4_parser.cc"
    break;

  case 970: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3315 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5153 "dhcp4_parser.cc"
    break;

  case 971: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3321 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5163 "dhcp4_parser.cc"
    break;

  case 972: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3327 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5173 "dhcp4_parser.cc"
    break;


#line 5177 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1405;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     464, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405,    28,    37,    38,    44,    80,    90,
     106,   109,   140,   171,   175,   188,   196,   228, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405,    37,  -173,    60,   279,   168,   722,
    1463,    62,    -8,   346,   154,   -84,   479,    23, -1405,   124,
     225,   239,   248,   261, -1405,    45, -1405, -1405, -1405, -1405,
     262,   268,   283, -1405, -1405, -1405,   299,   300, -1405, -1405,
   -1405,   303,   315,   327,   328,   329,   341,   342,   343,   381,
     383,   384, -1405,   385,   387,   393,   394,   402, -1405, -1405,
   -1405,   424,   430,   440,   458,   459,   463,   467, -1405, -1405,
   -1405,   468, -1405, -1405, -1405, -1405, -1405,   469,   470,   472,
   -1405, -1405, -1405, -1405, -1405,   473, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   474,   475,   476, -1405, -1405,   477, -1405,
     134, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,   478,   486,   487,   488,
   -1405,   169, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   490, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,   172, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
     491, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405,   193, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   275,
     318, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   417, -1405, -1405,   492, -1405, -1405, -1405,
     495, -1405, -1405,   453,   498, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   499,   501,
     502, -1405, -1405, -1405, -1405, -1405,   494,   504, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405,   209, -1405, -1405, -1405,   505, -1405,   506, -1405,
     507,   509, -1405, -1405, -1405, -1405, -1405,   221, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   513,   242,
   -1405, -1405, -1405, -1405,    37,    37, -1405,   284,   515, -1405,
   -1405,   518,   522,   525,   293,   294,   296,   532,   534,   536,
     304,   307,   544,   546,   547,   316,   321,   323,   325,   330,
     313,   332,   337,   338,   331,   344,   551,   348,   351,   339,
     353,   354,   562,   573,   575,   355,   356,   345,   359,   361,
     363,   366,   576,   586,   602,   371,   606,   610,   613,   614,
     617,   388,   389,   392,   619,   629,   634,   640,   642,   412,
     647,   648,   650,   655,   660,   661,   663,   438,   441,   443,
     674,   679, -1405,   279, -1405,   680,   681,   696,   462,   466,
     465,   471,   168, -1405,   699,   702,   703,   705,   706,   707,
     484,   708,   709,   710,   718,   719,   722, -1405,   721,   489,
    1463, -1405,   723,   724,   725,   726,   727,   728,   729,   730,
   -1405,    62, -1405,   731,   732,   500,   734,   737,   740,   508,
   -1405,   346,   741,   510,   511,   519,   742, -1405,   154,   744,
     755,   -72, -1405,   521,   757,   527,   758,   528,   529,   767,
     768,   479, -1405,   769,   537,    23, -1405, -1405, -1405,   771,
     772,   773,   774,   775, -1405, -1405, -1405,   540,   548,   549,
   -1405, -1405,   776,   781,   786, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,   566, -1405, -1405, -1405,
   -1405, -1405,    -3,   567,   568, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405,   800,   814,   818, -1405,   589,   136,   821,   820,
     592, -1405, -1405, -1405,   824,   825,   827,   828,   831, -1405,
     832,   834,   829,   835,   837,   599,   604, -1405, -1405, -1405,
     848,   850, -1405,   853,   123,   205, -1405, -1405, -1405, -1405,
   -1405,   623,   624,   626,   859,   630,   631, -1405,   853,   853,
     853,   632,   858, -1405,   633, -1405, -1405,   853,   636,   652,
     653,   654,   667,   668,   669, -1405,   670,   671, -1405,   672,
     673,   675, -1405, -1405,   676, -1405, -1405, -1405,   853, -1405,
     677,   820, -1405, -1405,   678, -1405,   682, -1405, -1405,     4,
     711, -1405,   865, -1405, -1405,    37,   279,    23,   168,   254,
   -1405, -1405, -1405,   833,   833,   908, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,   909,   910,   912, -1405, -1405,
   -1405, -1405, -1405, -1405,   913, -1405, -1405, -1405,   103,   914,
     915,   916,    63,   165,   595,   917,   -69,   479, -1405, -1405,
     918,    -6, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   921, -1405, -1405, -1405, -1405, -1405, -1405,
     779, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,   908, -1405,   276,   277,   291,
   -1405, -1405,   317, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
     926,   927,   928,   929,   930,   931,   933,   934,   935,   936,
   -1405,   937,   938, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405,   340, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   374,
   -1405,   939,   940, -1405, -1405,   941,   943, -1405, -1405,   942,
     946, -1405, -1405,   944,   948, -1405, -1405,   947,   949, -1405,
   -1405, -1405, -1405, -1405, -1405,    98, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   121, -1405, -1405,   950,   951, -1405, -1405,
     953,   952, -1405,   956,   957,   958,   959,   960,   961,   375,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405,   962,   963,   964,
   -1405,   376, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405,   965, -1405,   966, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405,   397, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405,   967,   954, -1405,   968, -1405,   970, -1405, -1405, -1405,
     409, -1405, -1405, -1405, -1405, -1405,   411, -1405,   151, -1405,
     971,   972,   973,   974, -1405,   415, -1405, -1405, -1405, -1405,
   -1405,   735, -1405,   975,   976, -1405, -1405,   977, -1405,   978,
   -1405, -1405, -1405,   979,   982,   254, -1405,   983,   984,   985,
     986,   743,   752,   745,   753,   756,   759,   760,   762,   763,
     765,   990,   764,   777,   991,  1002,  1006,  1009,  1016,   833,
   -1405, -1405,   833, -1405,   908,   722, -1405,   909,   346, -1405,
     910,   154, -1405,   912,  1405, -1405,   913,   103, -1405,   199,
     914, -1405,    62, -1405,   915,   -84, -1405,   916,   785,   788,
     791,   792,   799,   803,    63, -1405,   784,   809,   812,   165,
   -1405,  1047,  1050,  1055,   826,  1058,   844,  1080,   595, -1405,
     595, -1405,   917,   847,  1087,   855,  1089,   -69, -1405, -1405,
     203,   918, -1405,   860,   862,   870,   887,    -6, -1405, -1405,
    1098,  1129,  1463, -1405,   921,  1132, -1405, -1405,   906,   911,
   -1405,   969,   980,   981,   987, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,    34, -1405, -1405,   988,   989,
     992,   174,   993, -1405,   418, -1405,   419, -1405,  1156, -1405,
    1166, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   421, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,  1176,  1178, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405,  1179,  1186, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
    1182, -1405,   428, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,   126,   994,   995, -1405,  1185,
   -1405,  1188, -1405,   429, -1405, -1405,   996, -1405,    37, -1405,
   -1405,  1190, -1405, -1405, -1405, -1405, -1405,   435, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   997,
     439, -1405,   853, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405,  1405, -1405,  1191,  1193,   998,   999, -1405,   199,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,    -9,  1192,
   -1405, -1405, -1405,  1196,  1003,  1198,   203, -1405, -1405, -1405,
   -1405, -1405,  1000,  1005, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405,   445, -1405, -1405, -1405, -1405, -1405,
   -1405,  1197,  1201, -1405,  1202, -1405,  1007, -1405, -1405, -1405,
    1205,  1206,  1208,  1210,    -9, -1405,   -25, -1405,  1192,  1211,
   -1405,  1039,  1008,  1010,  1215, -1405, -1405, -1405, -1405, -1405,
   -1405,   447, -1405, -1405, -1405, -1405,   159, -1405, -1405, -1405,
   -1405, -1405,  1214,  1218,   -25, -1405,  -108,  1211, -1405, -1405,
    1220,  1224, -1405,  1011, -1405, -1405,  1230,  1231,  1235, -1405,
     451, -1405, -1405, -1405, -1405, -1405, -1405, -1405,     8, -1405,
    1214, -1405,  1238,  1012,  1013,  1015,  1241,  -108, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,   457, -1405, -1405, -1405,
   -1405,  1017, -1405, -1405, -1405,  1018, -1405,  1244,  1245,     8,
   -1405, -1405, -1405,  1020,  1021, -1405, -1405, -1405
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   214,     9,   399,    11,   626,    13,
     671,    15,   541,    17,   550,    19,   589,    21,   361,    23,
     875,    25,   907,    27,    46,    39,     0,     0,     0,     0,
       0,   673,     0,   552,   591,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   905,   199,   232,
       0,     0,     0,   693,   695,   697,     0,     0,   230,   243,
     245,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,   164,   171,
     173,     0,     0,     0,     0,     0,     0,     0,   390,   539,
     580,     0,   156,   177,   479,   658,   660,     0,     0,     0,
     323,   720,   662,   352,   373,     0,   338,   757,   759,   856,
     873,   187,   189,     0,     0,     0,   917,   959,     0,   141,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   104,   137,   138,    93,    94,    95,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   114,   115,   129,   130,   131,   133,   134,   135,
     139,   140,    78,    79,   101,    80,    81,    82,   132,    86,
      87,    76,   105,   106,   107,    77,    84,    85,    99,   100,
     102,    96,    97,    98,    83,    88,    89,    90,    91,    92,
     103,   113,   136,   216,   218,   222,     0,     0,     0,     0,
     213,     0,   201,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   459,   461,   463,   617,   457,   465,     0,   469,
     471,   473,   467,   715,   456,   404,   405,   406,   407,   408,
     433,   434,   435,   436,   437,   454,   423,   424,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   455,     0,   401,   411,   428,   429,
     430,   412,   414,   415,   416,   417,   419,   420,   421,   413,
     409,   410,   431,   432,   418,   425,   426,   427,   422,   655,
       0,   654,   638,   639,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   649,   650,   651,   634,   635,   636,   637,
     633,     0,   628,   631,   632,   652,   653,   713,   699,   701,
     703,   707,   705,   711,   709,   692,   686,   690,   691,     0,
     674,   675,   687,   688,   689,   683,   678,   684,   680,   681,
     682,   685,   679,     0,   570,   290,     0,   574,   572,   577,
       0,   566,   567,     0,   553,   554,   557,   569,   558,   559,
     560,   576,   561,   562,   563,   564,   565,   608,     0,     0,
       0,   615,   606,   607,   610,   611,     0,   592,   593,   596,
     597,   598,   599,   600,   601,   602,   605,   603,   604,   369,
     371,   366,     0,   363,   367,   368,     0,   892,     0,   895,
       0,     0,   899,   903,   890,   888,   889,     0,   877,   880,
     881,   882,   883,   884,   885,   886,   887,   914,     0,     0,
     909,   912,   913,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    69,    66,     0,     0,     0,     0,     0,
       0,     0,   203,   215,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   403,   400,     0,     0,
     630,   627,     0,     0,     0,     0,     0,     0,     0,     0,
     672,   677,   542,     0,     0,     0,     0,     0,     0,     0,
     551,   556,     0,     0,     0,     0,     0,   590,   595,     0,
       0,   365,   362,     0,     0,     0,     0,     0,     0,     0,
       0,   879,   876,     0,     0,   911,   908,    49,    41,     0,
       0,     0,     0,     0,   158,   159,   160,     0,     0,     0,
     197,   198,     0,     0,     0,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     0,   192,   193,   161,
     162,   163,     0,     0,     0,   175,   176,   183,   184,   185,
     186,   191,     0,     0,     0,   155,     0,     0,     0,     0,
       0,   475,   476,   477,     0,     0,     0,     0,     0,   756,
       0,     0,     0,     0,     0,     0,     0,   194,   195,   196,
       0,     0,    68,     0,     0,     0,   226,   227,   228,   229,
     202,     0,     0,     0,     0,     0,     0,   478,     0,     0,
       0,     0,     0,   402,     0,   657,   629,     0,     0,     0,
       0,     0,     0,     0,     0,   676,     0,     0,   568,     0,
       0,     0,   579,   555,     0,   612,   613,   614,     0,   594,
       0,     0,   364,   891,     0,   894,     0,   897,   898,     0,
       0,   878,     0,   916,   910,     0,     0,     0,     0,     0,
     694,   696,   698,     0,     0,   247,   154,   166,   167,   168,
     169,   170,   165,   172,   174,   392,   543,   582,   157,   179,
     180,   181,   182,   178,   481,    38,   659,   661,     0,     0,
     664,   354,     0,     0,     0,   761,     0,     0,   188,   190,
       0,     0,    51,   217,   220,   221,   219,   224,   225,   223,
     460,   462,   464,   619,   458,   466,   470,   472,   474,   468,
       0,   656,   714,   700,   702,   704,   708,   706,   712,   710,
     571,   291,   575,   573,   578,   609,   616,   370,   372,   893,
     896,   901,   902,   900,   904,   247,    42,     0,     0,     0,
     239,   241,     0,   234,   237,   238,   281,   283,   285,   287,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,   308,   310,   312,   314,   316,   317,   318,
     319,   320,   321,   280,     0,   254,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,     0,
     252,     0,   248,   249,   397,     0,   393,   394,   548,     0,
     544,   545,   587,     0,   583,   584,   486,     0,   482,   483,
     333,   334,   335,   336,   337,     0,   325,   328,   329,   330,
     331,   332,   725,     0,   722,   669,     0,   665,   666,   359,
       0,   355,   356,     0,     0,     0,     0,     0,     0,     0,
     375,   378,   379,   380,   381,   382,   383,     0,     0,     0,
     348,     0,   340,   343,   344,   345,   346,   347,   784,   789,
     791,     0,   814,     0,   795,   783,   776,   777,   778,   781,
     782,     0,   768,   771,   772,   773,   774,   779,   780,   775,
     766,     0,   762,   763,     0,   868,     0,   871,   864,   865,
       0,   858,   861,   862,   863,   866,     0,   922,     0,   919,
       0,     0,     0,     0,   968,     0,   961,   964,   965,   966,
     967,    53,   624,     0,   620,   621,   718,     0,   717,     0,
      62,   906,   200,     0,     0,   236,   233,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   256,
     231,   244,     0,   246,   251,     0,   391,   396,   552,   540,
     547,   591,   581,   586,     0,   480,   485,   327,   324,   727,
     724,   721,   673,   663,   668,     0,   353,   358,     0,     0,
       0,     0,     0,     0,   377,   374,     0,     0,     0,   342,
     339,     0,     0,     0,     0,     0,     0,     0,   770,   758,
       0,   760,   765,     0,     0,     0,     0,   860,   857,   874,
       0,   921,   918,     0,     0,     0,     0,   963,   960,    55,
       0,    54,     0,   618,   623,     0,   716,   915,     0,     0,
     235,     0,     0,     0,     0,   289,   292,   293,   294,   295,
     296,   297,   298,   299,   300,     0,   306,   307,     0,     0,
       0,     0,     0,   255,     0,   250,     0,   395,     0,   546,
       0,   585,   538,   510,   511,   512,   494,   495,   515,   516,
     517,   518,   519,   536,   497,   498,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   537,   491,   492,   493,   506,   507,   508,   509,
     503,   504,   505,     0,   488,   496,   513,   514,   499,   500,
     501,   502,   484,   326,   750,   752,     0,     0,   744,   745,
     746,   747,   748,   749,   737,   738,   742,   743,   739,   740,
     741,     0,   728,   729,   732,   733,   734,   735,   736,   723,
       0,   667,     0,   357,   384,   385,   386,   387,   388,   389,
     376,   349,   350,   351,   341,     0,     0,     0,   793,     0,
     794,     0,   769,     0,   764,   867,     0,   870,     0,   859,
     937,     0,   935,   933,   927,   931,   932,     0,   924,   929,
     930,   928,   920,   969,   970,   971,   972,   962,    52,    57,
       0,   622,     0,   240,   242,   282,   284,   286,   288,   303,
     304,   305,   302,   309,   311,   313,   315,   322,   253,   398,
     549,   588,   490,   487,     0,     0,     0,     0,   726,   731,
     670,   360,   786,   787,   788,   785,   790,   792,     0,   797,
     767,   869,   872,     0,     0,     0,   926,   923,    56,   625,
     719,   489,     0,     0,   754,   755,   730,   826,   829,   831,
     833,   825,   824,   823,     0,   816,   819,   820,   821,   822,
     802,     0,   798,   799,     0,   934,     0,   925,   751,   753,
       0,     0,     0,     0,   818,   815,     0,   796,   801,     0,
     936,     0,     0,     0,     0,   817,   812,   811,   807,   809,
     810,     0,   804,   808,   800,   942,     0,   939,   828,   827,
     830,   832,   835,     0,   806,   803,     0,   941,   938,   840,
       0,   836,   837,     0,   805,   952,     0,     0,     0,   957,
       0,   944,   947,   948,   949,   950,   951,   940,     0,   834,
     839,   813,     0,     0,     0,     0,     0,   946,   943,   852,
     854,   851,   845,   847,   849,   850,     0,   842,   846,   848,
     838,     0,   954,   955,   956,     0,   945,     0,     0,   844,
     841,   953,   958,     0,     0,   843,   853,   855
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,   -59, -1405,  -626, -1405,   213,
   -1405, -1405, -1405, -1405, -1405, -1405,  -640, -1405, -1405, -1405,
     -67, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   512,   739,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
   -1405, -1405, -1405, -1405,    94, -1405, -1405,    97,   102,   -13,
      13,    41,    51, -1405, -1405,    53, -1405,    56, -1405,    59,
     104,    64, -1405, -1405,    66,    69,    74,    76,    79, -1405,
      81, -1405,   105, -1405, -1405, -1405, -1405, -1405,    43, -1405,
   -1405, -1405,   516,   733, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   226, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405,   425, -1405,   201, -1405,  -738,   204, -1405, -1405,
   -1404, -1405, -1377, -1405, -1405, -1405, -1405,   -63, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,  -770, -1405,  -769, -1405,  -766, -1405,   115,
   -1405, -1405, -1405, -1405, -1405, -1405,   190, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,   178, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405,   181, -1405, -1405, -1405,   185,   689, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,   179, -1405, -1405, -1405,
   -1405, -1405, -1405, -1057, -1405, -1405, -1405,   215, -1405, -1405,
   -1405,   219,   736, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1055, -1405,   -29, -1405,   -18, -1405,    -4, -1405,     5,
   -1405,   107,   110,   112, -1405, -1405, -1405, -1405, -1405,   210,
   -1405, -1405,   -35,   -60, -1405, -1405, -1405, -1405, -1405,   218,
   -1405, -1405, -1405,   223, -1405,   714, -1405,   -34, -1405, -1405,
   -1405, -1405, -1405,   -27, -1405, -1405, -1405, -1405, -1405,   -32,
   -1405, -1405, -1405,   216, -1405, -1405, -1405,   227, -1405,   712,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405,   167, -1405, -1405, -1405,   173,   746,
   -1405, -1405, -1405,   -44, -1405,     3, -1405,   -56, -1405, -1405,
   -1405,   224, -1405, -1405, -1405,   217, -1405,   749,   -48, -1405,
      -7, -1405,    15, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1054, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   230, -1405,
   -1405, -1405,   -22, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405,   191, -1405,   202,
     206, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405,   -77, -1405, -1405,  -101, -1405, -1405,
   -1405, -1405, -1405,   -68, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405,  -119, -1405, -1405,  -145, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,   211, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405,   539,   738, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405,   582,   747, -1405, -1405,
   -1405, -1405, -1405, -1405,   212, -1405, -1405,   -16, -1405, -1405,
   -1405, -1405, -1405, -1405,   -86, -1405, -1405,  -113, -1405, -1405,
   -1405, -1405, -1405, -1405, -1405, -1405, -1405, -1405,   229, -1405,
   -1405, -1405, -1405
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   776,
      82,    83,    39,    64,    79,    80,   793,  1021,  1130,  1131,
     873,    41,    66,    85,   458,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   486,   174,   175,   506,   176,   177,   178,   179,
     180,   181,   182,   492,   762,   183,   493,   184,   494,   185,
     186,   187,   507,   773,   188,   189,   190,   191,   192,   525,
     193,   526,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   462,   241,   242,    45,    68,   243,   535,   244,   536,
     796,   245,   537,   799,   246,   247,   248,   249,   203,   472,
     204,   463,   842,   843,   844,  1033,   845,  1034,   205,   473,
     206,   474,   901,   902,   903,  1062,   874,   875,   876,  1037,
     877,  1038,   878,  1039,   879,  1040,   880,   881,   574,   882,
     883,   884,   885,   886,   887,   888,   889,   890,   891,  1051,
    1312,   892,   893,   894,  1054,   895,  1055,   896,  1056,   897,
    1057,   898,  1058,   207,   514,   925,   926,   927,   928,   929,
     930,   931,   208,   520,   961,   962,   963,   964,   965,   209,
     517,   940,   941,   942,  1085,    59,    75,   422,   423,   424,
     589,   425,   590,   210,   518,   949,   950,   951,   952,   953,
     954,   955,   956,   211,   502,   905,   906,   907,  1065,    47,
      69,   295,   296,   297,   548,   298,   544,   299,   545,   300,
     546,   301,   549,   302,   554,   303,   551,   304,   552,   305,
     553,   212,   213,   214,   309,   215,   508,   917,   918,   919,
    1074,  1213,  1214,   216,   503,    53,    72,   909,   910,   911,
    1068,    55,    73,   383,   384,   385,   386,   387,   388,   389,
     573,   390,   577,   391,   576,   392,   393,   578,   394,   217,
     504,   913,   914,   915,  1071,    57,    74,   406,   407,   408,
     409,   410,   582,   411,   412,   413,   414,   415,   416,   586,
     311,   547,  1023,  1024,  1025,  1132,    49,    70,   341,   342,
     343,   558,   344,   218,   509,   219,   510,   220,   516,   936,
     937,   938,  1082,    51,    71,   359,   360,   361,   221,   467,
     222,   468,   223,   469,   365,   563,   366,   564,   367,   565,
     368,   567,   369,   566,   370,   569,   371,   568,   372,   562,
     318,   555,  1027,  1028,  1135,   224,   515,   933,   934,  1079,
    1241,  1242,  1243,  1244,  1245,  1324,  1246,  1325,  1247,  1248,
     225,   226,   521,   227,   522,   991,   992,   993,  1110,   981,
     982,   983,  1101,  1335,   984,  1102,   985,  1103,   986,   987,
     988,  1107,  1371,  1372,  1373,  1386,  1401,  1402,  1403,  1413,
     989,  1105,  1364,  1365,  1366,  1380,  1409,  1367,  1381,  1368,
    1382,  1369,  1383,  1420,  1421,  1422,  1438,  1456,  1457,  1458,
    1467,  1459,  1468,   228,   523,  1000,  1001,  1002,  1003,  1114,
    1004,  1005,  1116,   229,   524,    61,    76,   437,   438,   439,
     440,   594,   441,   442,   596,   443,   444,   445,   599,   833,
     446,   600,   230,   461,    63,    77,   449,   450,   451,   603,
     452,   231,   530,  1008,  1009,  1120,  1287,  1288,  1289,  1290,
    1345,  1291,  1343,  1406,  1407,  1416,  1430,  1431,  1432,  1442,
    1433,  1434,  1435,  1436,  1446,   232,   531,  1015,  1016,  1017,
    1018,  1019,  1020
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   321,   355,    78,   381,   402,   421,   434,
     382,   403,   373,   314,   976,   977,   899,  1204,   978,  1205,
    1221,   315,   831,   362,   250,   312,   345,   357,    28,   395,
     417,  1357,   435,   775,  1452,   447,   448,   310,   340,   356,
     404,   336,    29,   268,    30,    40,    31,   405,   459,   847,
     848,    42,   337,   460,   135,   136,   278,   322,   806,   807,
     808,  1453,   316,    81,   363,  1452,   338,   812,   419,   420,
      84,   251,   313,   346,   358,   339,   396,   418,   375,   436,
     419,   420,   279,   323,   317,   265,   364,    44,   826,  1309,
    1310,  1311,  1453,   129,    93,    94,    95,    46,   135,   136,
     266,  1077,   267,  1425,  1078,   775,  1426,  1427,  1428,  1429,
     280,   324,   294,    48,   135,   136,    50,   994,   995,   996,
     281,   325,   282,   326,  1080,   283,   327,  1081,   284,   328,
     453,   135,   136,   286,   329,   287,   330,   533,   288,   331,
     794,   795,   534,   289,   332,   290,   333,    52,   291,   334,
     292,   335,   158,   269,  1121,   270,   271,  1122,   272,  1396,
     273,   274,  1417,   275,   130,  1418,   276,   997,  1358,  1359,
    1360,   277,   542,   285,   293,   556,   306,   543,    54,   307,
     557,   308,    56,   233,   234,   135,   136,   235,  1449,  1450,
     236,   237,   238,   239,   347,    58,   560,   757,   758,   759,
     760,   561,   832,    60,   348,   349,   350,   351,   352,   353,
     354,   158,   591,  1010,  1011,  1012,  1013,   592,   943,   944,
     945,   946,   947,   948,   601,   797,   798,   158,   454,   602,
     158,    93,    94,    95,    96,    62,   761,   866,   867,   868,
     869,   870,   871,   455,   158,   605,   920,   921,   922,   923,
     606,   924,   769,   770,   771,   772,   456,   375,   397,   376,
     377,   398,   399,   400,   457,  1204,   464,  1205,  1221,   101,
     102,   103,   465,    32,    33,    34,    35,   135,   136,   533,
     605,   840,   841,   570,  1030,  1031,   401,   466,   135,   136,
      87,   135,   136,    88,   542,  1332,  1333,  1334,   158,  1032,
     129,   130,   375,   470,   471,    89,   375,   475,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   476,
    1035,   571,   135,   136,  1164,  1036,   135,   136,   957,   958,
     959,   477,   478,   479,  1224,  1225,  1226,  1227,   976,   977,
     976,   977,   978,  1059,   978,   480,   481,   482,  1060,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,  1059,  1094,  1099,
     129,   130,  1061,  1095,  1100,   483,   374,   484,   485,   487,
     158,   488,   131,   132,   133,   607,   608,   489,   490,   134,
    1108,   158,   135,   136,   158,  1109,   491,   137,   138,   139,
     140,   141,  1117,  1280,   601,  1281,  1282,  1118,  1127,  1119,
     142,  1059,   556,  1128,  1322,   572,  1318,  1319,   495,  1323,
     143,   591,  1108,   144,   496,   158,  1331,  1340,  1346,   158,
     145,   146,   560,  1347,   497,   147,   148,  1349,  1384,   375,
    1414,   376,   377,  1385,  1447,  1415,   378,   379,   380,  1448,
    1469,   580,   498,   499,   149,  1470,   159,   500,   150,   135,
     136,   501,   505,   511,   512,   240,   513,   519,   527,   528,
     529,   532,   538,   151,   152,   153,   154,   155,   156,   264,
     539,   540,   541,   321,   550,   559,   575,   157,   250,   579,
     314,   581,   587,   583,   355,   584,   585,   588,   315,   593,
     595,   597,   312,   598,   381,   158,   345,   604,   382,   610,
     609,   402,   611,   362,   310,   403,   612,   357,   340,   613,
     268,   336,   614,   615,   434,   616,   617,   395,   618,   356,
     619,   620,   337,   278,   417,   251,   621,   322,   622,   316,
     623,   624,   630,   625,   404,   636,   338,   435,   626,   313,
     627,   405,   628,   346,   363,   339,   642,   629,   634,   279,
     631,   317,   265,   323,   358,   632,   633,   643,   639,   644,
     652,   635,   158,   647,   396,   637,   364,   266,   638,   267,
     653,   418,   640,   641,   645,   646,   648,   280,   649,   294,
     650,   324,   135,   136,   436,   651,   654,   281,   655,   282,
     656,   325,   283,   326,   657,   284,   327,   658,   659,   328,
     286,   660,   287,   664,   329,   288,   330,   661,   662,   331,
     289,   663,   290,   665,   332,   291,   333,   292,   666,   334,
     269,   335,   270,   271,   667,   272,   668,   273,   274,   669,
     275,   670,   671,   276,   672,   863,   864,   865,   277,   673,
     285,   293,  1350,   306,   674,   675,   307,   676,   308,   426,
     427,   428,   429,   430,   431,   432,   433,   677,   680,   159,
     678,   240,   679,   681,   683,   684,   836,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     685,   686,   688,   691,   250,   687,   692,   693,   689,   694,
     695,   696,   698,   699,   700,   158,   960,   975,   135,   136,
     434,   697,   701,   702,  1014,   704,   705,   707,   708,   709,
     710,   711,   712,   713,   714,   716,   717,   718,   719,   966,
     979,   720,   998,   435,   721,   724,   728,   722,   730,   725,
     726,   251,    91,    92,    93,    94,    95,    96,   727,   731,
     733,   734,   736,   968,   735,   737,   738,   969,   970,   971,
     972,   739,   740,   742,   743,   745,   750,   973,   974,   746,
     747,   748,   749,   753,   751,   752,   967,   980,   754,   999,
     436,   755,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   756,   763,   764,   765,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   766,
     252,   253,   254,   767,   130,   768,   774,    30,   777,   778,
     779,   158,   780,   781,   785,   788,   132,   133,   782,   783,
     789,   784,   786,   255,   787,   135,   136,   256,   257,   258,
     137,   138,   139,   790,   259,   260,   261,   791,   792,   800,
     801,   262,   802,   142,   803,   810,   804,   805,   809,   811,
     835,   263,   813,   846,   847,   848,   849,   850,   851,   852,
     853,   854,   855,   856,   857,   858,   859,   860,   814,   815,
     816,   861,   862,   863,   864,   865,   866,   867,   868,   869,
     870,   871,   872,   817,   818,   819,   820,   821,   822,   823,
     834,   824,   825,   827,   829,   900,   904,   908,   830,   912,
     916,   932,   935,   939,   990,  1007,   151,   152,  1022,  1026,
    1041,  1042,  1043,  1044,  1045,  1046,   375,  1047,  1048,  1049,
    1050,  1052,  1053,  1064,   828,  1063,  1067,  1066,  1069,  1070,
    1072,  1073,  1076,  1075,  1084,  1087,  1083,  1112,   158,  1086,
    1088,  1089,  1090,  1091,  1092,  1093,  1096,  1097,  1098,  1104,
    1106,  1129,  1113,  1111,  1115,  1123,  1124,  1125,  1126,  1134,
    1145,  1133,  1147,  1138,  1137,  1136,  1139,  1141,  1142,  1143,
    1144,  1146,  1148,  1149,  1155,  1158,  1150,  1151,   264,  1152,
    1153,   381,  1154,  1156,   402,   382,  1159,  1172,   403,   314,
    1160,  1203,  1228,  1161,  1157,   355,  1233,   315,   421,  1234,
    1162,   312,  1254,  1261,   395,  1255,  1218,   417,  1256,  1257,
    1216,  1238,   960,   310,   362,  1236,  1258,   404,   357,   268,
    1259,   975,  1215,   975,   405,  1206,  1262,  1235,  1176,  1263,
     356,  1265,   278,  1283,  1266,   966,  1207,  1284,   316,  1267,
    1014,  1186,  1269,  1268,   979,   321,   979,  1219,   313,   158,
    1208,   396,  1239,   998,   418,   363,  1285,  1217,   279,  1209,
     317,   265,  1237,  1270,  1271,   358,  1275,  1187,   345,  1220,
    1173,  1276,  1277,  1278,  1240,  1229,   266,   364,   267,  1293,
     340,  1294,   967,   336,  1298,  1174,   280,  1175,   294,  1295,
    1230,   980,  1231,   980,   337,  1188,   281,  1202,   282,   322,
     999,   283,  1232,  1286,   284,  1189,  1296,  1190,   338,   286,
    1191,   287,  1299,  1192,   288,   346,  1302,   339,  1194,   289,
    1195,   290,  1303,  1196,   291,   323,   292,  1304,  1197,   269,
    1198,   270,   271,  1199,   272,  1200,   273,   274,  1177,   275,
    1178,  1179,   276,  1180,  1320,  1181,  1182,   277,  1183,   285,
     293,  1184,   306,   324,  1321,   307,  1185,   308,  1193,  1201,
    1326,  1210,  1327,   325,  1211,   326,  1212,  1328,   327,  1329,
    1330,   328,  1338,  1339,  1344,  1352,   329,  1353,   330,  1370,
    1374,   331,  1376,  1387,  1388,  1305,   332,  1389,   333,  1391,
    1392,   334,  1393,   335,  1394,  1408,  1306,  1307,  1405,  1342,
    1412,  1419,  1423,  1308,  1313,  1314,  1439,  1440,  1315,  1317,
    1336,  1337,  1341,  1348,  1443,  1444,  1378,  1354,  1355,  1445,
    1375,  1379,  1461,  1390,  1410,  1465,  1411,  1441,  1473,  1474,
    1463,  1462,  1464,  1471,  1472,  1172,  1476,  1477,   837,  1203,
    1029,  1140,  1228,  1163,   839,  1165,  1233,  1223,  1253,  1234,
    1252,  1361,   682,  1260,  1218,   690,  1316,  1264,  1216,  1283,
     732,  1238,  1167,  1284,  1166,  1236,  1222,  1351,  1169,  1171,
    1215,  1168,   703,  1206,  1362,   723,  1176,  1235,  1170,  1250,
     729,  1301,  1285,  1274,  1207,  1300,   706,  1356,  1251,  1186,
    1249,  1404,  1273,  1424,  1272,  1219,  1395,  1361,  1208,  1397,
     715,  1460,  1239,  1398,  1475,  1217,  1006,  1209,  1279,   838,
    1377,  1437,  1237,  1292,  1466,  1187,     0,  1220,  1173,   741,
    1362,  1363,  1399,     0,  1240,  1229,     0,  1397,     0,  1286,
       0,  1398,   744,  1174,     0,  1175,  1297,     0,     0,     0,
    1230,     0,  1231,  1188,     0,  1202,     0,     0,     0,     0,
    1399,  1451,  1232,  1189,     0,  1190,     0,     0,  1191,     0,
       0,  1192,     0,     0,     0,     0,  1194,  1363,  1195,  1400,
       0,  1196,     0,     0,  1454,     0,  1197,     0,  1198,     0,
       0,  1199,  1451,  1200,     0,     0,  1177,     0,  1178,  1179,
       0,  1180,     0,  1181,  1182,     0,  1183,  1400,     0,  1184,
       0,     0,     0,     0,  1185,  1454,  1193,  1201,     0,  1210,
       0,     0,  1211,     0,  1212,    91,    92,    93,    94,    95,
      96,  1455,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1455,     0,     0,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,   130,   375,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
     133,     0,     0,     0,     0,     0,     0,     0,   135,   136,
       0,   257,     0,   137,   138,   139,     0,   259,   260,   261,
       0,     0,     0,     0,   262,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   263,   123,   124,   125,   126,     0,
       0,     0,     0,     0,     0,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   133,     0,
       0,     0,     0,     0,     0,   319,   135,   136,     0,     0,
       0,     0,     0,     0,     0,   259,   260,   261,     0,     0,
       0,     0,   262,   320,     0,     0,     0,     0,     0,   151,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   784,   784,   754,  1074,   784,  1074,
    1074,    69,    18,    71,    68,    69,    70,    71,     0,    73,
      74,    40,    76,   659,  1438,    12,    13,    69,    70,    71,
      74,    70,     5,    69,     7,     7,     9,    74,     3,    41,
      42,     7,    70,     8,   123,   124,    69,    70,   698,   699,
     700,  1438,    69,   236,    71,  1469,    70,   707,   152,   153,
      10,    68,    69,    70,    71,    70,    73,    74,   103,    76,
     152,   153,    69,    70,    69,    69,    71,     7,   728,    55,
      56,    57,  1469,   101,    32,    33,    34,     7,   123,   124,
      69,     3,    69,   211,     6,   731,   214,   215,   216,   217,
      69,    70,    69,     7,   123,   124,     7,   186,   187,   188,
      69,    70,    69,    70,     3,    69,    70,     6,    69,    70,
       6,   123,   124,    69,    70,    69,    70,     3,    69,    70,
      17,    18,     8,    69,    70,    69,    70,     7,    69,    70,
      69,    70,   236,    69,     3,    69,    69,     6,    69,   184,
      69,    69,     3,    69,   102,     6,    69,   236,   177,   178,
     179,    69,     3,    69,    69,     3,    69,     8,     7,    69,
       8,    69,     7,    15,    16,   123,   124,    19,   180,   181,
      22,    23,    24,    25,   132,     7,     3,   200,   201,   202,
     203,     8,   198,     7,   142,   143,   144,   145,   146,   147,
     148,   236,     3,   219,   220,   221,   222,     8,   155,   156,
     157,   158,   159,   160,     3,    20,    21,   236,     3,     8,
     236,    32,    33,    34,    35,     7,   239,    63,    64,    65,
      66,    67,    68,     4,   236,     3,   143,   144,   145,   146,
       8,   148,   116,   117,   118,   119,     8,   103,   104,   105,
     106,   107,   108,   109,     3,  1322,     4,  1322,  1322,    70,
      71,    72,     4,   236,   237,   238,   239,   123,   124,     3,
       3,    27,    28,     8,     8,     8,   132,     4,   123,   124,
      11,   123,   124,    14,     3,   169,   170,   171,   236,     8,
     101,   102,   103,     4,     4,    26,   103,     4,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     4,
       3,     3,   123,   124,  1062,     8,   123,   124,   163,   164,
     165,     4,     4,     4,   135,   136,   137,   138,  1108,  1108,
    1110,  1110,  1108,     3,  1110,     4,     4,     4,     8,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     3,     3,     3,
     101,   102,     8,     8,     8,     4,    40,     4,     4,     4,
     236,     4,   113,   114,   115,   454,   455,     4,     4,   120,
       3,   236,   123,   124,   236,     8,     4,   128,   129,   130,
     131,   132,     3,   210,     3,   212,   213,     8,     3,     8,
     141,     3,     3,     8,     3,     8,     8,     8,     4,     8,
     151,     3,     3,   154,     4,   236,     8,     8,     3,   236,
     161,   162,     3,     8,     4,   166,   167,     8,     3,   103,
       3,   105,   106,     8,     3,     8,   110,   111,   112,     8,
       3,     8,     4,     4,   185,     8,   533,     4,   189,   123,
     124,     4,     4,     4,     4,   542,     4,     4,     4,     4,
       4,     4,     4,   204,   205,   206,   207,   208,   209,   556,
       4,     4,     4,   560,     4,     4,     4,   218,   542,     4,
     556,     3,     8,     4,   571,     4,     4,     3,   556,     4,
       4,     4,   556,     4,   581,   236,   560,     4,   581,     4,
     236,   588,     4,   571,   556,   588,     4,   571,   560,     4,
     556,   560,   239,   239,   601,   239,     4,   581,     4,   571,
       4,   237,   560,   556,   588,   542,   239,   560,     4,   556,
       4,     4,   239,   237,   588,     4,   560,   601,   237,   556,
     237,   588,   237,   560,   571,   560,     4,   237,   237,   556,
     238,   556,   556,   560,   571,   238,   238,     4,   239,     4,
       4,   237,   236,   238,   581,   237,   571,   556,   237,   556,
       4,   588,   239,   239,   239,   239,   237,   556,   237,   556,
     237,   560,   123,   124,   601,   239,     4,   556,   237,   556,
       4,   560,   556,   560,     4,   556,   560,     4,     4,   560,
     556,     4,   556,     4,   560,   556,   560,   239,   239,   560,
     556,   239,   556,     4,   560,   556,   560,   556,     4,   560,
     556,   560,   556,   556,     4,   556,     4,   556,   556,   237,
     556,     4,     4,   556,     4,    60,    61,    62,   556,     4,
     556,   556,  1302,   556,     4,     4,   556,     4,   556,   190,
     191,   192,   193,   194,   195,   196,   197,   239,     4,   746,
     239,   748,   239,     4,     4,     4,   745,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
       4,   239,   237,     4,   748,   239,     4,     4,   237,     4,
       4,     4,     4,     4,     4,   236,   783,   784,   123,   124,
     787,   237,     4,     4,   791,     4,   237,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   237,     4,   783,
     784,     4,   786,   787,     4,     4,     4,   239,     4,   239,
     239,   748,    30,    31,    32,    33,    34,    35,   239,     4,
     239,     4,     4,   168,   237,   237,   237,   172,   173,   174,
     175,     4,     4,     4,   237,     4,   236,   182,   183,     7,
       7,     7,     7,     7,   236,   236,   783,   784,     7,   786,
     787,     5,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,   236,   236,   236,     5,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     5,
      98,    99,   100,     5,   102,   236,     5,     7,   236,     5,
       5,   236,     5,     5,     5,   236,   114,   115,     7,     7,
     236,     7,     7,   121,     7,   123,   124,   125,   126,   127,
     128,   129,   130,     5,   132,   133,   134,     7,     5,   236,
     236,   139,   236,   141,     5,     7,   236,   236,   236,   236,
       5,   149,   236,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,   236,   236,
     236,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,   236,   236,   236,   236,   236,   236,   236,
     199,   236,   236,   236,   236,     7,     7,     7,   236,     7,
       7,     7,     7,     7,     7,     7,   204,   205,     7,   150,
       4,     4,     4,     4,     4,     4,   103,     4,     4,     4,
       4,     4,     4,     3,   731,     6,     3,     6,     6,     3,
       6,     3,     3,     6,     3,     3,     6,     3,   236,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   236,     4,     6,     4,     4,     4,     4,     4,     3,
     237,     6,   237,     4,     6,     8,     4,     4,     4,     4,
       4,   239,   239,   237,     4,     4,   237,   237,  1065,   237,
     237,  1068,   237,   239,  1071,  1068,     4,  1074,  1071,  1065,
       4,  1074,  1079,     4,   237,  1082,  1079,  1065,  1085,  1079,
       4,  1065,   237,   239,  1068,   237,  1074,  1071,   237,   237,
    1074,  1079,  1099,  1065,  1082,  1079,   237,  1071,  1082,  1065,
     237,  1108,  1074,  1110,  1071,  1074,   237,  1079,  1074,   237,
    1082,     4,  1065,  1120,     4,  1099,  1074,  1120,  1065,     4,
    1127,  1074,     4,   237,  1108,  1132,  1110,  1074,  1065,   236,
    1074,  1068,  1079,  1117,  1071,  1082,  1120,  1074,  1065,  1074,
    1065,  1065,  1079,   239,     4,  1082,   239,  1074,  1132,  1074,
    1074,     4,   237,     4,  1079,  1079,  1065,  1082,  1065,   239,
    1132,   239,  1099,  1132,     6,  1074,  1065,  1074,  1065,   239,
    1079,  1108,  1079,  1110,  1132,  1074,  1065,  1074,  1065,  1132,
    1117,  1065,  1079,  1120,  1065,  1074,   239,  1074,  1132,  1065,
    1074,  1065,     3,  1074,  1065,  1132,     4,  1132,  1074,  1065,
    1074,  1065,   236,  1074,  1065,  1132,  1065,   236,  1074,  1065,
    1074,  1065,  1065,  1074,  1065,  1074,  1065,  1065,  1074,  1065,
    1074,  1074,  1065,  1074,     8,  1074,  1074,  1065,  1074,  1065,
    1065,  1074,  1065,  1132,     8,  1065,  1074,  1065,  1074,  1074,
       4,  1074,     4,  1132,  1074,  1132,  1074,     8,  1132,     3,
       8,  1132,     7,     5,     4,     4,  1132,     4,  1132,     7,
       4,  1132,     4,     6,     3,   236,  1132,     5,  1132,     4,
       4,  1132,     4,  1132,     4,   176,   236,   236,     7,  1278,
       5,     7,     4,   236,   236,   236,     6,     3,   236,   236,
     236,   236,   236,   236,     4,     4,   236,   239,   239,     4,
     237,   236,     4,   236,   236,     4,   236,   236,     4,     4,
     237,   239,   237,   236,   236,  1322,   236,   236,   746,  1322,
     835,  1035,  1329,  1059,   748,  1064,  1329,  1077,  1087,  1329,
    1085,  1338,   533,  1094,  1322,   542,  1161,  1099,  1322,  1346,
     591,  1329,  1067,  1346,  1065,  1329,  1076,  1322,  1070,  1073,
    1322,  1068,   556,  1322,  1338,   581,  1322,  1329,  1071,  1082,
     588,  1134,  1346,  1112,  1322,  1132,   560,  1329,  1084,  1322,
    1080,  1388,  1110,  1414,  1108,  1322,  1384,  1384,  1322,  1386,
     571,  1440,  1329,  1386,  1469,  1322,   787,  1322,  1117,   747,
    1346,  1417,  1329,  1121,  1447,  1322,    -1,  1322,  1322,   601,
    1384,  1338,  1386,    -1,  1329,  1329,    -1,  1414,    -1,  1346,
      -1,  1414,   605,  1322,    -1,  1322,  1127,    -1,    -1,    -1,
    1329,    -1,  1329,  1322,    -1,  1322,    -1,    -1,    -1,    -1,
    1414,  1438,  1329,  1322,    -1,  1322,    -1,    -1,  1322,    -1,
      -1,  1322,    -1,    -1,    -1,    -1,  1322,  1384,  1322,  1386,
      -1,  1322,    -1,    -1,  1438,    -1,  1322,    -1,  1322,    -1,
      -1,  1322,  1469,  1322,    -1,    -1,  1322,    -1,  1322,  1322,
      -1,  1322,    -1,  1322,  1322,    -1,  1322,  1414,    -1,  1322,
      -1,    -1,    -1,    -1,  1322,  1469,  1322,  1322,    -1,  1322,
      -1,    -1,  1322,    -1,  1322,    30,    31,    32,    33,    34,
      35,  1438,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1469,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    -1,    -1,    -1,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,   124,
      -1,   126,    -1,   128,   129,   130,    -1,   132,   133,   134,
      -1,    -1,    -1,    -1,   139,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,   149,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,
      -1,    -1,    -1,    -1,    -1,   122,   123,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   132,   133,   134,    -1,    -1,
      -1,    -1,   139,   140,    -1,    -1,    -1,    -1,    -1,   204,
     205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   236,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   204,   205,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   236
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,     5,
       7,     9,   236,   237,   238,   239,   255,   256,   257,   262,
       7,   271,     7,   276,     7,   334,     7,   449,     7,   536,
       7,   553,     7,   485,     7,   491,     7,   515,     7,   425,
       7,   665,     7,   684,   263,   258,   272,   277,   335,   450,
     537,   554,   486,   492,   516,   426,   666,   685,   255,   264,
     265,   236,   260,   261,    10,   273,   275,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,   101,
     102,   113,   114,   115,   120,   123,   124,   128,   129,   130,
     131,   132,   141,   151,   154,   161,   162,   166,   167,   185,
     189,   204,   205,   206,   207,   208,   209,   218,   236,   270,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   293,   294,   296,   297,   298,   299,
     300,   301,   302,   305,   307,   309,   310,   311,   314,   315,
     316,   317,   318,   320,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   348,   350,   358,   360,   403,   412,   419,
     433,   443,   471,   472,   473,   475,   483,   509,   543,   545,
     547,   558,   560,   562,   585,   600,   601,   603,   653,   663,
     682,   691,   715,    15,    16,    19,    22,    23,    24,    25,
     270,   332,   333,   336,   338,   341,   344,   345,   346,   347,
     543,   545,    98,    99,   100,   121,   125,   126,   127,   132,
     133,   134,   139,   149,   270,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   294,   297,   298,   299,   300,
     301,   302,   305,   307,   309,   310,   311,   314,   315,   316,
     317,   318,   320,   322,   328,   451,   452,   453,   455,   457,
     459,   461,   463,   465,   467,   469,   471,   472,   473,   474,
     509,   530,   543,   545,   547,   558,   560,   562,   580,   122,
     140,   270,   299,   300,   301,   302,   305,   307,   309,   311,
     314,   315,   316,   317,   318,   320,   463,   465,   467,   469,
     509,   538,   539,   540,   542,   543,   545,   132,   142,   143,
     144,   145,   146,   147,   148,   270,   509,   543,   545,   555,
     556,   557,   558,   560,   562,   564,   566,   568,   570,   572,
     574,   576,   578,   483,    40,   103,   105,   106,   110,   111,
     112,   270,   377,   493,   494,   495,   496,   497,   498,   499,
     501,   503,   505,   506,   508,   543,   545,   104,   107,   108,
     109,   132,   270,   377,   497,   503,   517,   518,   519,   520,
     521,   523,   524,   525,   526,   527,   528,   543,   545,   152,
     153,   270,   427,   428,   429,   431,   190,   191,   192,   193,
     194,   195,   196,   197,   270,   543,   545,   667,   668,   669,
     670,   672,   673,   675,   676,   677,   680,    12,    13,   686,
     687,   688,   690,     6,     3,     4,     8,     3,   274,     3,
       8,   683,   331,   351,     4,     4,     4,   559,   561,   563,
       4,     4,   349,   359,   361,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   292,     4,     4,     4,
       4,     4,   303,   306,   308,     4,     4,     4,     4,     4,
       4,     4,   444,   484,   510,     4,   295,   312,   476,   544,
     546,     4,     4,     4,   404,   586,   548,   420,   434,     4,
     413,   602,   604,   654,   664,   319,   321,     4,     4,     4,
     692,   716,     4,     3,     8,   337,   339,   342,     4,     4,
       4,     4,     3,     8,   456,   458,   460,   531,   454,   462,
       4,   466,   468,   470,   464,   581,     3,     8,   541,     4,
       3,     8,   579,   565,   567,   569,   573,   571,   577,   575,
       8,     3,     8,   500,   378,     4,   504,   502,   507,     4,
       8,     3,   522,     4,     4,     4,   529,     8,     3,   430,
     432,     3,     8,     4,   671,     4,   674,     4,     4,   678,
     681,     3,     8,   689,     4,     3,     8,   255,   255,   236,
       4,     4,     4,     4,   239,   239,   239,     4,     4,     4,
     237,   239,     4,     4,     4,   237,   237,   237,   237,   237,
     239,   238,   238,   238,   237,   237,     4,   237,   237,   239,
     239,   239,     4,     4,     4,   239,   239,   238,   237,   237,
     237,   239,     4,     4,     4,   237,     4,     4,     4,     4,
       4,   239,   239,   239,     4,     4,     4,     4,     4,   237,
       4,     4,     4,     4,     4,     4,     4,   239,   239,   239,
       4,     4,   279,     4,     4,     4,   239,   239,   237,   237,
     333,     4,     4,     4,     4,     4,     4,   237,     4,     4,
       4,     4,     4,   452,     4,   237,   539,     4,     4,     4,
       4,     4,     4,     4,     4,   557,     4,     4,   237,     4,
       4,     4,   239,   495,     4,   239,   239,   239,     4,   519,
       4,     4,   428,   239,     4,   237,     4,   237,   237,     4,
       4,   668,     4,   237,   687,     4,     7,     7,     7,     7,
     236,   236,   236,     7,     7,     5,   236,   200,   201,   202,
     203,   239,   304,   236,   236,     5,     5,     5,   236,   116,
     117,   118,   119,   313,     5,   257,   259,   236,     5,     5,
       5,     5,     7,     7,     7,     5,     7,     7,   236,   236,
       5,     7,     5,   266,    17,    18,   340,    20,    21,   343,
     236,   236,   236,     5,   236,   236,   266,   266,   266,   236,
       7,   236,   266,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   266,   236,   259,   236,
     236,    18,   198,   679,   199,     5,   255,   278,   686,   332,
      27,    28,   352,   353,   354,   356,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,   270,   366,   367,   368,   370,   372,   374,
     376,   377,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   391,   392,   393,   395,   397,   399,   401,   366,
       7,   362,   363,   364,     7,   445,   446,   447,     7,   487,
     488,   489,     7,   511,   512,   513,     7,   477,   478,   479,
     143,   144,   145,   146,   148,   405,   406,   407,   408,   409,
     410,   411,     7,   587,   588,     7,   549,   550,   551,     7,
     421,   422,   423,   155,   156,   157,   158,   159,   160,   435,
     436,   437,   438,   439,   440,   441,   442,   163,   164,   165,
     270,   414,   415,   416,   417,   418,   543,   545,   168,   172,
     173,   174,   175,   182,   183,   270,   393,   395,   397,   543,
     545,   609,   610,   611,   614,   616,   618,   619,   620,   630,
       7,   605,   606,   607,   186,   187,   188,   236,   543,   545,
     655,   656,   657,   658,   660,   661,   667,     7,   693,   694,
     219,   220,   221,   222,   270,   717,   718,   719,   720,   721,
     722,   267,     7,   532,   533,   534,   150,   582,   583,   362,
       8,     8,     8,   355,   357,     3,     8,   369,   371,   373,
     375,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   389,     4,     4,   394,   396,   398,   400,   402,     3,
       8,     8,   365,     6,     3,   448,     6,     3,   490,     6,
       3,   514,     6,     3,   480,     6,     3,     3,     6,   589,
       3,     6,   552,     6,     3,   424,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   612,   615,   617,     4,   631,     4,   621,     3,     8,
     608,     6,     3,     4,   659,     4,   662,     3,     8,     8,
     695,     3,     6,     4,     4,     4,     4,     3,     8,   236,
     268,   269,   535,     6,     3,   584,     8,     6,     4,     4,
     353,     4,     4,     4,     4,   237,   239,   237,   239,   237,
     237,   237,   237,   237,   237,     4,   239,   237,     4,     4,
       4,     4,     4,   367,   366,   364,   451,   447,   493,   489,
     517,   513,   270,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   294,   297,   298,   299,   300,   301,   302,
     305,   307,   309,   310,   311,   314,   315,   316,   317,   318,
     320,   322,   328,   377,   443,   461,   463,   465,   467,   469,
     471,   472,   473,   481,   482,   509,   543,   545,   558,   560,
     562,   580,   479,   406,   135,   136,   137,   138,   270,   280,
     281,   282,   328,   377,   483,   509,   543,   545,   558,   560,
     562,   590,   591,   592,   593,   594,   596,   598,   599,   588,
     555,   551,   427,   423,   237,   237,   237,   237,   237,   237,
     436,   239,   237,   237,   415,     4,     4,     4,   237,     4,
     239,     4,   610,   609,   607,   239,     4,   237,     4,   656,
     210,   212,   213,   270,   377,   543,   545,   696,   697,   698,
     699,   701,   694,   239,   239,   239,   239,   718,     6,     3,
     538,   534,     4,   236,   236,   236,   236,   236,   236,    55,
      56,    57,   390,   236,   236,   236,   399,   236,     8,     8,
       8,     8,     3,     8,   595,   597,     4,     4,     8,     3,
       8,     8,   169,   170,   171,   613,   236,   236,     7,     5,
       8,   236,   255,   702,     4,   700,     3,     8,   236,     8,
     266,   482,     4,     4,   239,   239,   592,    40,   177,   178,
     179,   270,   543,   545,   632,   633,   634,   637,   639,   641,
       7,   622,   623,   624,     4,   237,     4,   697,   236,   236,
     635,   638,   640,   642,     3,     8,   625,     6,     3,     5,
     236,     4,     4,     4,     4,   633,   184,   270,   377,   543,
     545,   626,   627,   628,   624,     7,   703,   704,   176,   636,
     236,   236,     5,   629,     3,     8,   705,     3,     6,     7,
     643,   644,   645,     4,   627,   211,   214,   215,   216,   217,
     706,   707,   708,   710,   711,   712,   713,   704,   646,     6,
       3,   236,   709,     4,     4,     4,   714,     3,     8,   180,
     181,   270,   370,   372,   543,   545,   647,   648,   649,   651,
     645,     4,   239,   237,   237,     4,   707,   650,   652,     3,
       8,   236,   236,     4,     4,   648,   236,   236
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
     288,   289,   290,   292,   291,   293,   295,   294,   296,   297,
     298,   299,   300,   301,   303,   302,   304,   304,   304,   304,
     304,   306,   305,   308,   307,   309,   310,   312,   311,   313,
     313,   313,   313,   314,   315,   316,   317,   319,   318,   321,
     320,   322,   323,   324,   325,   326,   327,   328,   329,   331,
     330,   332,   332,   332,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   335,   334,   337,   336,   339,   338,
     340,   340,   342,   341,   343,   343,   344,   345,   346,   347,
     349,   348,   351,   350,   352,   352,   352,   353,   353,   355,
     354,   357,   356,   359,   358,   361,   360,   362,   362,   363,
     363,   363,   365,   364,   366,   366,   366,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   367,   367,
     367,   369,   368,   371,   370,   373,   372,   375,   374,   376,
     378,   377,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   389,   388,   390,   390,   390,   391,   392,   394,   393,
     396,   395,   398,   397,   400,   399,   399,   399,   399,   399,
     399,   402,   401,   404,   403,   405,   405,   405,   406,   406,
     406,   406,   406,   407,   408,   409,   410,   411,   413,   412,
     414,   414,   414,   415,   415,   415,   415,   415,   415,   416,
     417,   418,   420,   419,   421,   421,   422,   422,   422,   424,
     423,   426,   425,   427,   427,   427,   427,   428,   428,   430,
     429,   432,   431,   434,   433,   435,   435,   435,   436,   436,
     436,   436,   436,   436,   437,   438,   439,   440,   441,   442,
     444,   443,   445,   445,   446,   446,   446,   448,   447,   450,
     449,   451,   451,   451,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   454,   453,   456,
     455,   458,   457,   460,   459,   462,   461,   464,   463,   466,
     465,   468,   467,   470,   469,   471,   472,   473,   474,   476,
     475,   477,   477,   478,   478,   478,   480,   479,   481,   481,
     481,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   484,
     483,   486,   485,   487,   487,   488,   488,   488,   490,   489,
     492,   491,   493,   493,   494,   494,   494,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   496,   497,   498,
     500,   499,   502,   501,   504,   503,   505,   507,   506,   508,
     510,   509,   511,   511,   512,   512,   512,   514,   513,   516,
     515,   517,   517,   518,   518,   518,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   520,   522,   521,
     523,   524,   525,   526,   527,   529,   528,   531,   530,   532,
     532,   533,   533,   533,   535,   534,   537,   536,   538,   538,
     538,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   541,   540,   542,   544,   543,
     546,   545,   548,   547,   549,   549,   550,   550,   550,   552,
     551,   554,   553,   555,   555,   556,   556,   556,   557,   557,
     557,   557,   557,   557,   557,   557,   557,   557,   557,   557,
     557,   557,   557,   559,   558,   561,   560,   563,   562,   565,
     564,   567,   566,   569,   568,   571,   570,   573,   572,   575,
     574,   577,   576,   579,   578,   581,   580,   582,   584,   583,
     586,   585,   587,   587,   587,   589,   588,   590,   590,   591,
     591,   591,   592,   592,   592,   592,   592,   592,   592,   592,
     592,   592,   592,   592,   592,   592,   592,   592,   592,   593,
     595,   594,   597,   596,   598,   599,   600,   602,   601,   604,
     603,   605,   605,   606,   606,   606,   608,   607,   609,   609,
     609,   610,   610,   610,   610,   610,   610,   610,   610,   610,
     610,   610,   610,   610,   612,   611,   613,   613,   613,   615,
     614,   617,   616,   618,   619,   621,   620,   622,   622,   623,
     623,   623,   625,   624,   626,   626,   626,   627,   627,   627,
     627,   627,   629,   628,   631,   630,   632,   632,   632,   633,
     633,   633,   633,   633,   633,   633,   635,   634,   636,   638,
     637,   640,   639,   642,   641,   643,   643,   644,   644,   644,
     646,   645,   647,   647,   647,   648,   648,   648,   648,   648,
     648,   648,   650,   649,   652,   651,   654,   653,   655,   655,
     655,   656,   656,   656,   656,   656,   656,   657,   659,   658,
     660,   662,   661,   664,   663,   666,   665,   667,   667,   667,
     668,   668,   668,   668,   668,   668,   668,   668,   668,   668,
     668,   669,   671,   670,   672,   674,   673,   675,   676,   678,
     677,   679,   679,   681,   680,   683,   682,   685,   684,   686,
     686,   686,   687,   687,   689,   688,   690,   692,   691,   693,
     693,   693,   695,   694,   696,   696,   696,   697,   697,   697,
     697,   697,   697,   697,   698,   700,   699,   702,   701,   703,
     703,   703,   705,   704,   706,   706,   706,   707,   707,   707,
     707,   707,   709,   708,   710,   711,   712,   714,   713,   716,
     715,   717,   717,   717,   718,   718,   718,   718,   718,   719,
     720,   721,   722
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
       0,     4,     0,     4,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     3,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     3,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     2,     1,
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
       6,     1,     3,     2,     1,     1,     1,     1,     1,     3,
       3,     3,     3
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
  "$@46", "cert_file", "$@47", "key_file", "$@48", "ssl_mode", "$@49",
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
     645,   651,   657,   663,   663,   672,   678,   678,   687,   693,
     699,   705,   711,   717,   723,   723,   732,   735,   738,   741,
     744,   750,   750,   759,   759,   768,   777,   787,   787,   796,
     799,   802,   805,   810,   816,   822,   828,   834,   834,   843,
     843,   852,   858,   864,   870,   876,   882,   888,   894,   900,
     900,   912,   913,   914,   919,   920,   921,   922,   923,   924,
     925,   926,   927,   928,   931,   931,   940,   940,   951,   951,
     959,   960,   963,   963,   971,   973,   977,   983,   989,   995,
    1001,  1001,  1014,  1014,  1025,  1026,  1027,  1032,  1033,  1036,
    1036,  1055,  1055,  1073,  1073,  1086,  1086,  1097,  1098,  1101,
    1102,  1103,  1108,  1108,  1118,  1119,  1120,  1125,  1126,  1127,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,
    1148,  1151,  1151,  1160,  1160,  1169,  1169,  1178,  1178,  1187,
    1193,  1193,  1202,  1208,  1214,  1220,  1226,  1232,  1238,  1244,
    1250,  1256,  1256,  1264,  1265,  1266,  1269,  1275,  1281,  1281,
    1290,  1290,  1299,  1299,  1308,  1308,  1316,  1319,  1322,  1325,
    1328,  1333,  1333,  1342,  1342,  1353,  1354,  1355,  1360,  1361,
    1362,  1363,  1364,  1367,  1372,  1377,  1382,  1387,  1394,  1394,
    1407,  1408,  1409,  1414,  1415,  1416,  1417,  1418,  1419,  1422,
    1428,  1434,  1440,  1440,  1451,  1452,  1455,  1456,  1457,  1462,
    1462,  1472,  1472,  1482,  1483,  1484,  1487,  1490,  1491,  1494,
    1494,  1503,  1503,  1512,  1512,  1524,  1525,  1526,  1531,  1532,
    1533,  1534,  1535,  1536,  1539,  1545,  1551,  1557,  1563,  1569,
    1578,  1578,  1592,  1593,  1596,  1597,  1598,  1607,  1607,  1633,
    1633,  1644,  1645,  1646,  1652,  1653,  1654,  1655,  1656,  1657,
    1658,  1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,
    1668,  1669,  1670,  1671,  1672,  1673,  1674,  1675,  1676,  1677,
    1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,
    1698,  1699,  1700,  1701,  1702,  1703,  1704,  1707,  1707,  1716,
    1716,  1725,  1725,  1734,  1734,  1743,  1743,  1752,  1752,  1762,
    1762,  1774,  1774,  1785,  1785,  1796,  1802,  1808,  1814,  1822,
    1822,  1834,  1835,  1839,  1840,  1841,  1846,  1846,  1854,  1855,
    1856,  1861,  1862,  1863,  1864,  1865,  1866,  1867,  1868,  1869,
    1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,  1878,  1879,
    1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,  1888,  1889,
    1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,
    1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,  1908,  1915,
    1915,  1929,  1929,  1938,  1939,  1942,  1943,  1944,  1951,  1951,
    1966,  1966,  1980,  1981,  1984,  1985,  1986,  1991,  1992,  1993,
    1994,  1995,  1996,  1997,  1998,  1999,  2000,  2003,  2005,  2011,
    2013,  2013,  2022,  2022,  2031,  2031,  2040,  2042,  2042,  2051,
    2061,  2061,  2074,  2075,  2080,  2081,  2082,  2089,  2089,  2101,
    2101,  2113,  2114,  2119,  2120,  2121,  2128,  2129,  2130,  2131,
    2132,  2133,  2134,  2135,  2136,  2137,  2138,  2141,  2143,  2143,
    2152,  2154,  2156,  2162,  2168,  2174,  2174,  2188,  2188,  2201,
    2202,  2205,  2206,  2207,  2212,  2212,  2222,  2222,  2232,  2233,
    2234,  2239,  2240,  2241,  2242,  2243,  2244,  2245,  2246,  2247,
    2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,  2256,  2257,
    2258,  2259,  2260,  2261,  2262,  2265,  2265,  2274,  2280,  2280,
    2305,  2305,  2335,  2335,  2346,  2347,  2350,  2351,  2352,  2357,
    2357,  2366,  2366,  2375,  2376,  2379,  2380,  2381,  2387,  2388,
    2389,  2390,  2391,  2392,  2393,  2394,  2395,  2396,  2397,  2398,
    2399,  2400,  2401,  2404,  2404,  2413,  2413,  2422,  2422,  2431,
    2431,  2440,  2440,  2449,  2449,  2458,  2458,  2467,  2467,  2476,
    2476,  2485,  2485,  2494,  2494,  2508,  2508,  2519,  2522,  2522,
    2536,  2536,  2547,  2548,  2549,  2554,  2554,  2564,  2565,  2568,
    2569,  2570,  2575,  2576,  2577,  2578,  2579,  2580,  2581,  2582,
    2583,  2584,  2585,  2586,  2587,  2588,  2589,  2590,  2591,  2594,
    2596,  2596,  2605,  2605,  2615,  2621,  2629,  2637,  2637,  2649,
    2649,  2661,  2662,  2665,  2666,  2667,  2672,  2672,  2680,  2681,
    2682,  2687,  2688,  2689,  2690,  2691,  2692,  2693,  2694,  2695,
    2696,  2697,  2698,  2699,  2702,  2702,  2711,  2712,  2713,  2716,
    2716,  2726,  2726,  2736,  2742,  2748,  2748,  2759,  2760,  2763,
    2764,  2765,  2770,  2770,  2778,  2779,  2780,  2785,  2786,  2787,
    2788,  2789,  2792,  2792,  2803,  2803,  2816,  2817,  2818,  2823,
    2824,  2825,  2826,  2827,  2828,  2829,  2832,  2832,  2840,  2843,
    2843,  2852,  2852,  2861,  2861,  2872,  2873,  2876,  2877,  2878,
    2883,  2883,  2891,  2892,  2893,  2898,  2899,  2900,  2901,  2902,
    2903,  2904,  2907,  2907,  2916,  2916,  2927,  2927,  2940,  2941,
    2942,  2947,  2948,  2949,  2950,  2951,  2952,  2955,  2961,  2961,
    2970,  2976,  2976,  2986,  2986,  2999,  2999,  3009,  3010,  3011,
    3016,  3017,  3018,  3019,  3020,  3021,  3022,  3023,  3024,  3025,
    3026,  3029,  3035,  3035,  3044,  3050,  3050,  3059,  3065,  3071,
    3071,  3080,  3081,  3084,  3084,  3095,  3095,  3107,  3107,  3117,
    3118,  3119,  3125,  3126,  3129,  3129,  3140,  3148,  3148,  3161,
    3162,  3163,  3169,  3169,  3177,  3178,  3179,  3184,  3185,  3186,
    3187,  3188,  3189,  3190,  3193,  3199,  3199,  3208,  3208,  3219,
    3220,  3221,  3226,  3226,  3234,  3235,  3236,  3241,  3242,  3243,
    3244,  3245,  3248,  3248,  3257,  3263,  3269,  3275,  3275,  3284,
    3284,  3295,  3296,  3297,  3302,  3303,  3304,  3305,  3306,  3309,
    3315,  3321,  3327
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
#line 7002 "dhcp4_parser.cc"

#line 3333 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
