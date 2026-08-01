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

  case 282: // $@40: %empty
#line 1157 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 283: // database_type: "type" $@40 ":" "constant string"
#line 1160 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2087 "dhcp4_parser.cc"
    break;

  case 284: // $@41: %empty
#line 1166 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 285: // user: "user" $@41 ":" "constant string"
#line 1169 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 286: // $@42: %empty
#line 1175 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 287: // password: "password" $@42 ":" "constant string"
#line 1178 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 288: // $@43: %empty
#line 1184 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 289: // host: "host" $@43 ":" "constant string"
#line 1187 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 290: // port: "port" ":" "integer"
#line 1193 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 291: // $@44: %empty
#line 1199 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 292: // name: "name" $@44 ":" "constant string"
#line 1202 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 293: // persist: "persist" ":" "boolean"
#line 1208 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 294: // lfc_interval: "lfc-interval" ":" "integer"
#line 1214 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2193 "dhcp4_parser.cc"
    break;

  case 295: // readonly: "readonly" ":" "boolean"
#line 1220 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 296: // connect_timeout: "connect-timeout" ":" "integer"
#line 1226 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 297: // read_timeout: "read-timeout" ":" "integer"
#line 1232 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 298: // write_timeout: "write-timeout" ":" "integer"
#line 1238 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2233 "dhcp4_parser.cc"
    break;

  case 299: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1244 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2243 "dhcp4_parser.cc"
    break;

  case 300: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1250 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2253 "dhcp4_parser.cc"
    break;

  case 301: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1256 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2263 "dhcp4_parser.cc"
    break;

  case 302: // $@45: %empty
#line 1262 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 303: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1265 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 304: // on_fail_mode: "stop-retry-exit"
#line 1270 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2287 "dhcp4_parser.cc"
    break;

  case 305: // on_fail_mode: "serve-retry-exit"
#line 1271 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2293 "dhcp4_parser.cc"
    break;

  case 306: // on_fail_mode: "serve-retry-continue"
#line 1272 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2299 "dhcp4_parser.cc"
    break;

  case 307: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1275 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 308: // max_row_errors: "max-row-errors" ":" "integer"
#line 1281 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2319 "dhcp4_parser.cc"
    break;

  case 309: // $@46: %empty
#line 1287 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 310: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1290 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc"
    break;

  case 311: // $@47: %empty
#line 1296 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 312: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1299 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 313: // $@48: %empty
#line 1305 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 314: // key_file: "key-file" $@48 ":" "constant string"
#line 1308 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 315: // $@49: %empty
#line 1314 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 316: // ssl_mode: "ssl-mode" $@49 ":" ssl_mode
#line 1317 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2394 "dhcp4_parser.cc"
    break;

  case 317: // ssl_mode: "disable"
#line 1322 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2402 "dhcp4_parser.cc"
    break;

  case 318: // ssl_mode: "prefer"
#line 1325 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2410 "dhcp4_parser.cc"
    break;

  case 319: // ssl_mode: "require"
#line 1328 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2418 "dhcp4_parser.cc"
    break;

  case 320: // ssl_mode: "verify-ca"
#line 1331 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2426 "dhcp4_parser.cc"
    break;

  case 321: // ssl_mode: "verify-full"
#line 1334 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2434 "dhcp4_parser.cc"
    break;

  case 322: // $@50: %empty
#line 1339 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc"
    break;

  case 323: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1342 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1348 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 325: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1354 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2474 "dhcp4_parser.cc"
    break;

  case 328: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1361 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2482 "dhcp4_parser.cc"
    break;

  case 334: // duid_id: "duid"
#line 1373 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 335: // hw_address_id: "hw-address"
#line 1378 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 336: // circuit_id: "circuit-id"
#line 1383 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2509 "dhcp4_parser.cc"
    break;

  case 337: // client_id: "client-id"
#line 1388 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 338: // flex_id: "flex-id"
#line 1393 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2527 "dhcp4_parser.cc"
    break;

  case 339: // $@52: %empty
#line 1400 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 340: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1406 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 343: // multi_threading_params: multi_threading_params ","
#line 1415 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2558 "dhcp4_parser.cc"
    break;

  case 350: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1428 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 351: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1434 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2578 "dhcp4_parser.cc"
    break;

  case 352: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1440 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 353: // $@53: %empty
#line 1446 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2600 "dhcp4_parser.cc"
    break;

  case 354: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1452 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp4_parser.cc"
    break;

  case 359: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1463 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2617 "dhcp4_parser.cc"
    break;

  case 360: // $@54: %empty
#line 1468 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2627 "dhcp4_parser.cc"
    break;

  case 361: // hooks_library: "{" $@54 hooks_params "}"
#line 1472 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 362: // $@55: %empty
#line 1478 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 363: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1482 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2657 "dhcp4_parser.cc"
    break;

  case 366: // hooks_params: hooks_params ","
#line 1490 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2665 "dhcp4_parser.cc"
    break;

  case 370: // $@56: %empty
#line 1500 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp4_parser.cc"
    break;

  case 371: // library: "library" $@56 ":" "constant string"
#line 1503 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2684 "dhcp4_parser.cc"
    break;

  case 372: // $@57: %empty
#line 1509 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 373: // parameters: "parameters" $@57 ":" map_value
#line 1512 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 374: // $@58: %empty
#line 1518 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2714 "dhcp4_parser.cc"
    break;

  case 375: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1524 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc"
    break;

  case 378: // expired_leases_params: expired_leases_params ","
#line 1532 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2732 "dhcp4_parser.cc"
    break;

  case 385: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1545 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 386: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1551 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 387: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1557 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 388: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1563 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 389: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1569 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 390: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1575 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 391: // $@59: %empty
#line 1584 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 392: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1590 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc"
    break;

  case 397: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1604 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2821 "dhcp4_parser.cc"
    break;

  case 398: // $@60: %empty
#line 1613 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 399: // subnet4: "{" $@60 subnet4_params "}"
#line 1617 "dhcp4_parser.yy"
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
#line 2857 "dhcp4_parser.cc"
    break;

  case 400: // $@61: %empty
#line 1639 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2867 "dhcp4_parser.cc"
    break;

  case 401: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1643 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2877 "dhcp4_parser.cc"
    break;

  case 404: // subnet4_params: subnet4_params ","
#line 1652 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2885 "dhcp4_parser.cc"
    break;

  case 459: // $@62: %empty
#line 1714 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2894 "dhcp4_parser.cc"
    break;

  case 460: // subnet: "subnet" $@62 ":" "constant string"
#line 1717 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2904 "dhcp4_parser.cc"
    break;

  case 461: // $@63: %empty
#line 1723 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2913 "dhcp4_parser.cc"
    break;

  case 462: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1726 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 463: // $@64: %empty
#line 1732 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 464: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1735 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 465: // $@65: %empty
#line 1741 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 466: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1744 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 467: // $@66: %empty
#line 1750 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 468: // interface: "interface" $@66 ":" "constant string"
#line 1753 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 469: // $@67: %empty
#line 1759 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 470: // client_class: "client-class" $@67 ":" "constant string"
#line 1762 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 471: // $@68: %empty
#line 1769 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 472: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1775 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3020 "dhcp4_parser.cc"
    break;

  case 473: // $@69: %empty
#line 1781 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp4_parser.cc"
    break;

  case 474: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1787 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3041 "dhcp4_parser.cc"
    break;

  case 475: // $@70: %empty
#line 1792 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 476: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1798 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 477: // reservations_global: "reservations-global" ":" "boolean"
#line 1803 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 478: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1809 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 479: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1815 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 480: // id: "id" ":" "integer"
#line 1821 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 481: // $@71: %empty
#line 1829 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 482: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1835 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3123 "dhcp4_parser.cc"
    break;

  case 487: // shared_networks_list: shared_networks_list ","
#line 1848 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3131 "dhcp4_parser.cc"
    break;

  case 488: // $@72: %empty
#line 1853 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3141 "dhcp4_parser.cc"
    break;

  case 489: // shared_network: "{" $@72 shared_network_params "}"
#line 1857 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 492: // shared_network_params: shared_network_params ","
#line 1863 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3157 "dhcp4_parser.cc"
    break;

  case 542: // $@73: %empty
#line 1923 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 543: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1929 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 544: // $@74: %empty
#line 1937 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 545: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1940 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3195 "dhcp4_parser.cc"
    break;

  case 550: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1952 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3203 "dhcp4_parser.cc"
    break;

  case 551: // $@75: %empty
#line 1959 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3213 "dhcp4_parser.cc"
    break;

  case 552: // option_def_entry: "{" $@75 option_def_params "}"
#line 1963 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 553: // $@76: %empty
#line 1974 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 554: // sub_option_def: "{" $@76 option_def_params "}"
#line 1978 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3247 "dhcp4_parser.cc"
    break;

  case 559: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1994 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3255 "dhcp4_parser.cc"
    break;

  case 571: // code: "code" ":" "integer"
#line 2013 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3265 "dhcp4_parser.cc"
    break;

  case 573: // $@77: %empty
#line 2021 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp4_parser.cc"
    break;

  case 574: // option_def_type: "type" $@77 ":" "constant string"
#line 2024 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 575: // $@78: %empty
#line 2030 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 576: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 2033 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 577: // $@79: %empty
#line 2039 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 578: // space: "space" $@79 ":" "constant string"
#line 2042 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 580: // $@80: %empty
#line 2050 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc"
    break;

  case 581: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2053 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 582: // option_def_array: "array" ":" "boolean"
#line 2059 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 583: // $@81: %empty
#line 2069 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 584: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2075 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3372 "dhcp4_parser.cc"
    break;

  case 589: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2090 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3380 "dhcp4_parser.cc"
    break;

  case 590: // $@82: %empty
#line 2097 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3390 "dhcp4_parser.cc"
    break;

  case 591: // option_data_entry: "{" $@82 option_data_params "}"
#line 2101 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3399 "dhcp4_parser.cc"
    break;

  case 592: // $@83: %empty
#line 2109 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3409 "dhcp4_parser.cc"
    break;

  case 593: // sub_option_data: "{" $@83 option_data_params "}"
#line 2113 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 598: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2129 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3426 "dhcp4_parser.cc"
    break;

  case 611: // $@84: %empty
#line 2151 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 612: // option_data_data: "data" $@84 ":" "constant string"
#line 2154 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3445 "dhcp4_parser.cc"
    break;

  case 615: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2164 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3455 "dhcp4_parser.cc"
    break;

  case 616: // option_data_always_send: "always-send" ":" "boolean"
#line 2170 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3465 "dhcp4_parser.cc"
    break;

  case 617: // option_data_never_send: "never-send" ":" "boolean"
#line 2176 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3475 "dhcp4_parser.cc"
    break;

  case 618: // $@85: %empty
#line 2182 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 619: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2188 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3496 "dhcp4_parser.cc"
    break;

  case 620: // $@86: %empty
#line 2196 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3508 "dhcp4_parser.cc"
    break;

  case 621: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2202 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3517 "dhcp4_parser.cc"
    break;

  case 626: // not_empty_pools_list: not_empty_pools_list ","
#line 2215 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3525 "dhcp4_parser.cc"
    break;

  case 627: // $@87: %empty
#line 2220 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 628: // pool_list_entry: "{" $@87 pool_params "}"
#line 2224 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 629: // $@88: %empty
#line 2230 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 630: // sub_pool4: "{" $@88 pool_params "}"
#line 2234 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 633: // pool_params: pool_params ","
#line 2242 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3573 "dhcp4_parser.cc"
    break;

  case 658: // $@89: %empty
#line 2273 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 659: // pool_entry: "pool" $@89 ":" "constant string"
#line 2276 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 660: // pool_id: "pool-id" ":" "integer"
#line 2282 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 661: // $@90: %empty
#line 2288 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3610 "dhcp4_parser.cc"
    break;

  case 662: // user_context: "user-context" $@90 ":" map_value
#line 2290 "dhcp4_parser.yy"
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
#line 3637 "dhcp4_parser.cc"
    break;

  case 663: // $@91: %empty
#line 2313 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 664: // comment: "comment" $@91 ":" "constant string"
#line 2315 "dhcp4_parser.yy"
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
#line 3674 "dhcp4_parser.cc"
    break;

  case 665: // $@92: %empty
#line 2343 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3686 "dhcp4_parser.cc"
    break;

  case 666: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2349 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3695 "dhcp4_parser.cc"
    break;

  case 671: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2360 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3703 "dhcp4_parser.cc"
    break;

  case 672: // $@93: %empty
#line 2365 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3713 "dhcp4_parser.cc"
    break;

  case 673: // reservation: "{" $@93 reservation_params "}"
#line 2369 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 674: // $@94: %empty
#line 2374 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 675: // sub_reservation: "{" $@94 reservation_params "}"
#line 2378 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 680: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2389 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3749 "dhcp4_parser.cc"
    break;

  case 696: // $@95: %empty
#line 2412 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 697: // next_server: "next-server" $@95 ":" "constant string"
#line 2415 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 698: // $@96: %empty
#line 2421 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 699: // server_hostname: "server-hostname" $@96 ":" "constant string"
#line 2424 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3787 "dhcp4_parser.cc"
    break;

  case 700: // $@97: %empty
#line 2430 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 701: // boot_file_name: "boot-file-name" $@97 ":" "constant string"
#line 2433 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 702: // $@98: %empty
#line 2439 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 703: // ip_address: "ip-address" $@98 ":" "constant string"
#line 2442 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 704: // $@99: %empty
#line 2448 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 705: // duid: "duid" $@99 ":" "constant string"
#line 2451 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 706: // $@100: %empty
#line 2457 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 707: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2460 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 708: // $@101: %empty
#line 2466 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 709: // client_id_value: "client-id" $@101 ":" "constant string"
#line 2469 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 710: // $@102: %empty
#line 2475 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 711: // circuit_id_value: "circuit-id" $@102 ":" "constant string"
#line 2478 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 712: // $@103: %empty
#line 2484 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 713: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2487 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3920 "dhcp4_parser.cc"
    break;

  case 714: // $@104: %empty
#line 2493 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 715: // hostname: "hostname" $@104 ":" "constant string"
#line 2496 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3939 "dhcp4_parser.cc"
    break;

  case 716: // $@105: %empty
#line 2502 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3951 "dhcp4_parser.cc"
    break;

  case 717: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2508 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3960 "dhcp4_parser.cc"
    break;

  case 718: // $@106: %empty
#line 2516 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3972 "dhcp4_parser.cc"
    break;

  case 719: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2522 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3981 "dhcp4_parser.cc"
    break;

  case 721: // $@107: %empty
#line 2530 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3993 "dhcp4_parser.cc"
    break;

  case 722: // ip_addresses: "ip-addresses" $@107 ":" list_strings
#line 2536 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4002 "dhcp4_parser.cc"
    break;

  case 723: // $@108: %empty
#line 2544 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4014 "dhcp4_parser.cc"
    break;

  case 724: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2550 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4023 "dhcp4_parser.cc"
    break;

  case 729: // not_empty_classes_list: not_empty_classes_list ","
#line 2561 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4031 "dhcp4_parser.cc"
    break;

  case 730: // $@109: %empty
#line 2566 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 731: // client_class_entry: "{" $@109 client_class_params "}"
#line 2570 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 736: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2582 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4059 "dhcp4_parser.cc"
    break;

  case 755: // $@110: %empty
#line 2608 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4068 "dhcp4_parser.cc"
    break;

  case 756: // client_class_test: "test" $@110 ":" "constant string"
#line 2611 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4078 "dhcp4_parser.cc"
    break;

  case 757: // $@111: %empty
#line 2617 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 758: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2620 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 759: // only_if_required: "only-if-required" ":" "boolean"
#line 2627 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4107 "dhcp4_parser.cc"
    break;

  case 760: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2633 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4117 "dhcp4_parser.cc"
    break;

  case 761: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2641 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4127 "dhcp4_parser.cc"
    break;

  case 762: // $@112: %empty
#line 2649 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 763: // control_sockets: "control-sockets" $@112 ":" "[" control_socket_list "]"
#line 2655 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 768: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2666 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4156 "dhcp4_parser.cc"
    break;

  case 769: // $@113: %empty
#line 2671 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4166 "dhcp4_parser.cc"
    break;

  case 770: // control_socket_entry: "{" $@113 control_socket_params "}"
#line 2675 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4174 "dhcp4_parser.cc"
    break;

  case 773: // control_socket_params: control_socket_params ","
#line 2681 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4182 "dhcp4_parser.cc"
    break;

  case 787: // $@114: %empty
#line 2701 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4191 "dhcp4_parser.cc"
    break;

  case 788: // control_socket_type: "socket-type" $@114 ":" control_socket_type_value
#line 2704 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4200 "dhcp4_parser.cc"
    break;

  case 789: // control_socket_type_value: "unix"
#line 2710 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4206 "dhcp4_parser.cc"
    break;

  case 790: // control_socket_type_value: "http"
#line 2711 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4212 "dhcp4_parser.cc"
    break;

  case 791: // control_socket_type_value: "https"
#line 2712 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4218 "dhcp4_parser.cc"
    break;

  case 792: // $@115: %empty
#line 2715 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4227 "dhcp4_parser.cc"
    break;

  case 793: // control_socket_name: "socket-name" $@115 ":" "constant string"
#line 2718 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4237 "dhcp4_parser.cc"
    break;

  case 794: // $@116: %empty
#line 2724 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 795: // control_socket_address: "socket-address" $@116 ":" "constant string"
#line 2727 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 796: // control_socket_port: "socket-port" ":" "integer"
#line 2733 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4266 "dhcp4_parser.cc"
    break;

  case 797: // cert_required: "cert-required" ":" "boolean"
#line 2739 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4276 "dhcp4_parser.cc"
    break;

  case 798: // $@117: %empty
#line 2745 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4288 "dhcp4_parser.cc"
    break;

  case 799: // http_headers: "http-headers" $@117 ":" "[" http_header_list "]"
#line 2751 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4297 "dhcp4_parser.cc"
    break;

  case 804: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2762 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4305 "dhcp4_parser.cc"
    break;

  case 805: // $@118: %empty
#line 2767 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4315 "dhcp4_parser.cc"
    break;

  case 806: // http_header: "{" $@118 http_header_params "}"
#line 2771 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4323 "dhcp4_parser.cc"
    break;

  case 809: // http_header_params: http_header_params ","
#line 2777 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4331 "dhcp4_parser.cc"
    break;

  case 815: // $@119: %empty
#line 2789 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4340 "dhcp4_parser.cc"
    break;

  case 816: // header_value: "value" $@119 ":" "constant string"
#line 2792 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4350 "dhcp4_parser.cc"
    break;

  case 817: // $@120: %empty
#line 2800 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4362 "dhcp4_parser.cc"
    break;

  case 818: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2806 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4373 "dhcp4_parser.cc"
    break;

  case 821: // auth_params: auth_params ","
#line 2815 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4381 "dhcp4_parser.cc"
    break;

  case 829: // $@121: %empty
#line 2829 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4390 "dhcp4_parser.cc"
    break;

  case 830: // auth_type: "type" $@121 ":" auth_type_value
#line 2832 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4399 "dhcp4_parser.cc"
    break;

  case 831: // auth_type_value: "basic"
#line 2837 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4405 "dhcp4_parser.cc"
    break;

  case 832: // $@122: %empty
#line 2840 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4414 "dhcp4_parser.cc"
    break;

  case 833: // realm: "realm" $@122 ":" "constant string"
#line 2843 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4424 "dhcp4_parser.cc"
    break;

  case 834: // $@123: %empty
#line 2849 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4433 "dhcp4_parser.cc"
    break;

  case 835: // directory: "directory" $@123 ":" "constant string"
#line 2852 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4443 "dhcp4_parser.cc"
    break;

  case 836: // $@124: %empty
#line 2858 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4455 "dhcp4_parser.cc"
    break;

  case 837: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2864 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4464 "dhcp4_parser.cc"
    break;

  case 842: // not_empty_clients_list: not_empty_clients_list ","
#line 2875 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4472 "dhcp4_parser.cc"
    break;

  case 843: // $@125: %empty
#line 2880 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 844: // basic_auth: "{" $@125 clients_params "}"
#line 2884 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4490 "dhcp4_parser.cc"
    break;

  case 847: // clients_params: clients_params ","
#line 2890 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4498 "dhcp4_parser.cc"
    break;

  case 855: // $@126: %empty
#line 2904 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4507 "dhcp4_parser.cc"
    break;

  case 856: // user_file: "user-file" $@126 ":" "constant string"
#line 2907 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4517 "dhcp4_parser.cc"
    break;

  case 857: // $@127: %empty
#line 2913 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4526 "dhcp4_parser.cc"
    break;

  case 858: // password_file: "password-file" $@127 ":" "constant string"
#line 2916 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4536 "dhcp4_parser.cc"
    break;

  case 859: // $@128: %empty
#line 2924 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4548 "dhcp4_parser.cc"
    break;

  case 860: // dhcp_queue_control: "dhcp-queue-control" $@128 ":" "{" queue_control_params "}"
#line 2930 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 863: // queue_control_params: queue_control_params ","
#line 2939 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4567 "dhcp4_parser.cc"
    break;

  case 870: // enable_queue: "enable-queue" ":" "boolean"
#line 2952 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4577 "dhcp4_parser.cc"
    break;

  case 871: // $@129: %empty
#line 2958 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4586 "dhcp4_parser.cc"
    break;

  case 872: // queue_type: "queue-type" $@129 ":" "constant string"
#line 2961 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4596 "dhcp4_parser.cc"
    break;

  case 873: // capacity: "capacity" ":" "integer"
#line 2967 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4606 "dhcp4_parser.cc"
    break;

  case 874: // $@130: %empty
#line 2973 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4615 "dhcp4_parser.cc"
    break;

  case 875: // arbitrary_map_entry: "constant string" $@130 ":" value
#line 2976 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4624 "dhcp4_parser.cc"
    break;

  case 876: // $@131: %empty
#line 2983 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4636 "dhcp4_parser.cc"
    break;

  case 877: // dhcp_ddns: "dhcp-ddns" $@131 ":" "{" dhcp_ddns_params "}"
#line 2989 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 878: // $@132: %empty
#line 2996 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4657 "dhcp4_parser.cc"
    break;

  case 879: // sub_dhcp_ddns: "{" $@132 dhcp_ddns_params "}"
#line 3000 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4667 "dhcp4_parser.cc"
    break;

  case 882: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3008 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4675 "dhcp4_parser.cc"
    break;

  case 894: // enable_updates: "enable-updates" ":" "boolean"
#line 3026 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4685 "dhcp4_parser.cc"
    break;

  case 895: // $@133: %empty
#line 3032 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4694 "dhcp4_parser.cc"
    break;

  case 896: // server_ip: "server-ip" $@133 ":" "constant string"
#line 3035 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4704 "dhcp4_parser.cc"
    break;

  case 897: // server_port: "server-port" ":" "integer"
#line 3041 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4714 "dhcp4_parser.cc"
    break;

  case 898: // $@134: %empty
#line 3047 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4723 "dhcp4_parser.cc"
    break;

  case 899: // sender_ip: "sender-ip" $@134 ":" "constant string"
#line 3050 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4733 "dhcp4_parser.cc"
    break;

  case 900: // sender_port: "sender-port" ":" "integer"
#line 3056 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4743 "dhcp4_parser.cc"
    break;

  case 901: // max_queue_size: "max-queue-size" ":" "integer"
#line 3062 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4753 "dhcp4_parser.cc"
    break;

  case 902: // $@135: %empty
#line 3068 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4762 "dhcp4_parser.cc"
    break;

  case 903: // ncr_protocol: "ncr-protocol" $@135 ":" ncr_protocol_value
#line 3071 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4771 "dhcp4_parser.cc"
    break;

  case 904: // ncr_protocol_value: "udp"
#line 3077 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4777 "dhcp4_parser.cc"
    break;

  case 905: // ncr_protocol_value: "tcp"
#line 3078 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4783 "dhcp4_parser.cc"
    break;

  case 906: // $@136: %empty
#line 3081 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4792 "dhcp4_parser.cc"
    break;

  case 907: // ncr_format: "ncr-format" $@136 ":" "JSON"
#line 3084 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4802 "dhcp4_parser.cc"
    break;

  case 908: // $@137: %empty
#line 3092 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4814 "dhcp4_parser.cc"
    break;

  case 909: // config_control: "config-control" $@137 ":" "{" config_control_params "}"
#line 3098 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4824 "dhcp4_parser.cc"
    break;

  case 910: // $@138: %empty
#line 3104 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4834 "dhcp4_parser.cc"
    break;

  case 911: // sub_config_control: "{" $@138 config_control_params "}"
#line 3108 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4843 "dhcp4_parser.cc"
    break;

  case 914: // config_control_params: config_control_params ","
#line 3116 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4851 "dhcp4_parser.cc"
    break;

  case 917: // $@139: %empty
#line 3126 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4863 "dhcp4_parser.cc"
    break;

  case 918: // config_databases: "config-databases" $@139 ":" "[" database_list "]"
#line 3132 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4872 "dhcp4_parser.cc"
    break;

  case 919: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3137 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4882 "dhcp4_parser.cc"
    break;

  case 920: // $@140: %empty
#line 3145 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4894 "dhcp4_parser.cc"
    break;

  case 921: // loggers: "loggers" $@140 ":" "[" loggers_entries "]"
#line 3151 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4903 "dhcp4_parser.cc"
    break;

  case 924: // loggers_entries: loggers_entries ","
#line 3160 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4911 "dhcp4_parser.cc"
    break;

  case 925: // $@141: %empty
#line 3166 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4921 "dhcp4_parser.cc"
    break;

  case 926: // logger_entry: "{" $@141 logger_params "}"
#line 3170 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4929 "dhcp4_parser.cc"
    break;

  case 929: // logger_params: logger_params ","
#line 3176 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4937 "dhcp4_parser.cc"
    break;

  case 937: // debuglevel: "debuglevel" ":" "integer"
#line 3190 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4947 "dhcp4_parser.cc"
    break;

  case 938: // $@142: %empty
#line 3196 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4956 "dhcp4_parser.cc"
    break;

  case 939: // severity: "severity" $@142 ":" "constant string"
#line 3199 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4966 "dhcp4_parser.cc"
    break;

  case 940: // $@143: %empty
#line 3205 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4978 "dhcp4_parser.cc"
    break;

  case 941: // output_options_list: "output-options" $@143 ":" "[" output_options_list_content "]"
#line 3211 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4987 "dhcp4_parser.cc"
    break;

  case 944: // output_options_list_content: output_options_list_content ","
#line 3218 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4995 "dhcp4_parser.cc"
    break;

  case 945: // $@144: %empty
#line 3223 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5005 "dhcp4_parser.cc"
    break;

  case 946: // output_entry: "{" $@144 output_params_list "}"
#line 3227 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5013 "dhcp4_parser.cc"
    break;

  case 949: // output_params_list: output_params_list ","
#line 3233 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5021 "dhcp4_parser.cc"
    break;

  case 955: // $@145: %empty
#line 3245 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5030 "dhcp4_parser.cc"
    break;

  case 956: // output: "output" $@145 ":" "constant string"
#line 3248 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5040 "dhcp4_parser.cc"
    break;

  case 957: // flush: "flush" ":" "boolean"
#line 3254 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5050 "dhcp4_parser.cc"
    break;

  case 958: // maxsize: "maxsize" ":" "integer"
#line 3260 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5060 "dhcp4_parser.cc"
    break;

  case 959: // maxver: "maxver" ":" "integer"
#line 3266 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5070 "dhcp4_parser.cc"
    break;

  case 960: // $@146: %empty
#line 3272 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5079 "dhcp4_parser.cc"
    break;

  case 961: // pattern: "pattern" $@146 ":" "constant string"
#line 3275 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5089 "dhcp4_parser.cc"
    break;

  case 962: // $@147: %empty
#line 3281 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5101 "dhcp4_parser.cc"
    break;

  case 963: // compatibility: "compatibility" $@147 ":" "{" compatibility_params "}"
#line 3287 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5110 "dhcp4_parser.cc"
    break;

  case 966: // compatibility_params: compatibility_params ","
#line 3294 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5118 "dhcp4_parser.cc"
    break;

  case 972: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3306 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5128 "dhcp4_parser.cc"
    break;

  case 973: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3312 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5138 "dhcp4_parser.cc"
    break;

  case 974: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3318 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5148 "dhcp4_parser.cc"
    break;

  case 975: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3324 "dhcp4_parser.yy"
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


  const short Dhcp4Parser::yypact_ninf_ = -1392;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     476, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,    34,    49,    37,    50,    52,    61,
      64,    88,   111,   182,   208,   264,   266,   274, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,    49,  -194,   136,   717,    69,   245,
    1469,    73,   -12,   341,   284,  -115,   232,    40, -1392,   186,
     164,   279,   204,   281, -1392,    28, -1392, -1392, -1392, -1392,
     296,   300,   306, -1392, -1392, -1392,   307,   310, -1392, -1392,
   -1392,   339,   343,   354,   364,   382,   399,   400,   409,   436,
     447,   460,   469, -1392,   470,   478,   479,   480,   481, -1392,
   -1392, -1392,   482,   483,   484,   485,   487,   489,   493, -1392,
   -1392, -1392,   494, -1392, -1392, -1392, -1392, -1392,   495,   496,
     497, -1392, -1392, -1392, -1392, -1392,   500, -1392, -1392, -1392,
   -1392, -1392, -1392,   503,   504,   505, -1392, -1392,   508, -1392,
      79, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,   509,   510,   512,   515,
   -1392,   105, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   519, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,   106, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392,   520, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392,   107, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
     347,   289, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   408, -1392, -1392,   523, -1392, -1392,
   -1392,   524, -1392, -1392,   526,   529, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   536,
     538,   540, -1392, -1392, -1392, -1392, -1392,   537,   543, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392,   123, -1392, -1392, -1392,   545, -1392,   546,
   -1392,   550,   551, -1392, -1392, -1392, -1392, -1392,   133, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   552,
     139, -1392, -1392, -1392, -1392,    49,    49, -1392,   311,   554,
   -1392, -1392,   555,   556,   557,   323,   324,   325,   562,   563,
     566,   334,   333,   569,   570,   571,   342,   344,   346,   349,
     350,   337,   352,   353,   355,   357,   358,   362,   591,   365,
     366,   367,   368,   370,   593,   597,   601,   372,   379,   375,
     386,   391,   393,   395,   631,   634,   636,   405,   641,   642,
     649,   651,   652,   419,   420,   422,   658,   659,   660,   662,
     664,   432,   666,   667,   669,   670,   671,   672,   438,   439,
     442,   679,   681, -1392,   717, -1392,   682,   684,   686,   454,
     455,   458,   459,    69, -1392,   693,   708,   712,   714,   715,
     718,   486,   721,   722,   723,   725,   726,   245, -1392,   728,
     501,  1469, -1392,   730,   733,   735,   736,   737,   738,   740,
     753, -1392,    73, -1392,   754,   755,   525,   756,   757,   759,
     527, -1392,   341,   760,   528,   530,   531,   761, -1392,   284,
     764,   767,   -34, -1392,   533,   769,   539,   770,   542,   544,
     771,   780,   232, -1392,   781,   549,    40, -1392, -1392, -1392,
     812,   810,   811,   815,   816, -1392, -1392, -1392,   588,   594,
     598, -1392, -1392,   822,   830,   716, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   603, -1392,
   -1392, -1392, -1392, -1392,   -15,   604,   607, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   839,   840,   846, -1392,   616,   360,
     848,   847,   619, -1392, -1392, -1392,   851,   852,   853,   855,
     854, -1392,   856,   857,   858,   859,   628,   632, -1392, -1392,
   -1392,   862,   863, -1392,   866,   137,   161, -1392, -1392, -1392,
   -1392, -1392,   637,   638,   639,   871,   645,   646, -1392,   866,
     866,   866,   647,   870, -1392,   650, -1392, -1392,   866,   654,
     655,   656,   657,   661,   663,   665, -1392,   668,   673, -1392,
     674,   675,   676, -1392, -1392,   677, -1392, -1392, -1392,   866,
   -1392,   678,   847, -1392, -1392,   680, -1392,   683, -1392, -1392,
      25,   688, -1392,   873, -1392, -1392,    49,   717,    40,    69,
     233, -1392, -1392, -1392,   185,   185,   878, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,   881,   887,   888, -1392,
   -1392, -1392, -1392, -1392, -1392,   889, -1392, -1392, -1392,   297,
     891,   893,   896,   278,   -63,   898,   275,   232, -1392, -1392,
     900,    36, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392,   901, -1392, -1392, -1392, -1392, -1392, -1392,
     766, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392,   878, -1392,   140,   150,   160,
   -1392, -1392,   162, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
     911,   914,   916,   923,   924,   925,   926,   927,   928,   929,
   -1392,   930,   932, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   172, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   175,
   -1392,   931,   935, -1392, -1392,   933,   937, -1392, -1392,   936,
     938, -1392, -1392,   939,   940, -1392, -1392,   941,   943, -1392,
   -1392, -1392, -1392, -1392, -1392,    72, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392,   942,   946, -1392, -1392,   944,   948, -1392,
   -1392,   949,   951, -1392,   952,   953,   954,   955,   956,   957,
     187, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   958,   959,
     960, -1392,   197, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
     961,   962, -1392,   964, -1392,   965, -1392, -1392, -1392,   199,
   -1392, -1392, -1392, -1392, -1392,   201, -1392,    83, -1392,   966,
     967,   968,   969, -1392,   205, -1392, -1392, -1392, -1392, -1392,
     739, -1392,   970,   963, -1392, -1392,   971, -1392,   972, -1392,
   -1392, -1392,   977,   978,   233, -1392,   980,   981,   983,   986,
     707,   713,   763,   762,   783,   784,   789,   794,   795,   797,
     988,   778,   805,  1004,  1041,  1044,  1051,  1055,   185, -1392,
   -1392,   185, -1392,   878,   245, -1392,   881,   341, -1392,   887,
     284, -1392,   888,  1411, -1392,   889,   297, -1392,   294, -1392,
     891,    73, -1392,   893,  -115, -1392,   896,   823,   825,   826,
     827,   831,   835,   278, -1392,   834,   841,   844,   -63, -1392,
     653, -1392,   898,   864,  1081,   868,  1088,   275, -1392, -1392,
     259,   900, -1392,   876,   883,   886,   890,    36, -1392, -1392,
    1089,  1091,  1469, -1392,   901,  1106, -1392, -1392,   884,   894,
   -1392,   902,   906,   915,   922, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392,    42, -1392, -1392,   945,   950,
     973,   392,   974, -1392,   287, -1392,   288, -1392,  1109, -1392,
    1119, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   298, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392,  1128,  1160, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392,  1161,  1170, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392,  1171, -1392,   304, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,  1184,
   -1392,  1186, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   305,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
     975, -1392,    49, -1392, -1392,  1187, -1392, -1392, -1392, -1392,
   -1392,   351, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392,   976,   374, -1392,   866, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,  1411, -1392,  1189,  1190,
     979,   982, -1392,   294, -1392, -1392,  1191,  1192,  1193,   985,
    1194,   984,  1195,   653, -1392, -1392, -1392,  1196,   987,  1197,
     259, -1392, -1392, -1392, -1392, -1392,   989,   990, -1392, -1392,
   -1392,    71,   991,   992, -1392,  1198, -1392,  1199, -1392,  1201,
   -1392,   993, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392,   174,  1200,  1206, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392,   403, -1392, -1392, -1392, -1392, -1392, -1392,  1208,
    1212, -1392, -1392,   168, -1392,  1213,  1215,  1216,  1226,   174,
   -1392,   178, -1392,  1200,    48,  1206, -1392,   798,   995,   996,
    1211, -1392, -1392, -1392, -1392, -1392, -1392,   404, -1392, -1392,
   -1392, -1392,  1229,  1230,  1231, -1392,   412, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,  1233,  1232,
     178, -1392,  1234,   998,  1005,  1006,  1240,    48, -1392, -1392,
    1239,  1244, -1392,  1013, -1392,  1014, -1392, -1392, -1392,  1016,
   -1392,   169, -1392,  1233, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   467, -1392, -1392, -1392, -1392,  1249,
    1250,   169, -1392,  1021,  1023, -1392, -1392, -1392
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   215,     9,   400,    11,   629,    13,
     674,    15,   544,    17,   553,    19,   592,    21,   362,    23,
     878,    25,   910,    27,    46,    39,     0,     0,     0,     0,
       0,   676,     0,   555,   594,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   908,   200,   233,
       0,     0,     0,   696,   698,   700,     0,     0,   231,   244,
     246,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,     0,     0,     0,     0,     0,   165,
     172,   174,     0,     0,     0,     0,     0,     0,     0,   391,
     542,   583,     0,   157,   178,   481,   661,   663,     0,     0,
       0,   324,   723,   665,   353,   374,     0,   339,   762,   859,
     876,   188,   190,     0,     0,     0,   920,   962,     0,   141,
       0,    67,    70,    71,    72,    73,    74,   107,   108,   109,
     110,   111,   112,    75,   103,   137,   138,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   114,   115,   129,   130,   131,   133,   134,
     135,   139,   140,    78,    79,   100,    80,    81,    82,   132,
      86,    87,    76,   104,   105,   106,    77,    84,    85,    98,
      99,   101,    95,    96,    97,    83,    88,    89,    90,    91,
     102,   113,   136,   217,   219,   223,     0,     0,     0,     0,
     214,     0,   202,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   461,   463,   465,   620,   459,   467,     0,   471,
     473,   475,   469,   718,   458,   405,   406,   407,   408,   409,
     434,   435,   436,   437,   438,   439,   456,   424,   425,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   457,     0,   402,   412,   429,
     430,   431,   413,   415,   416,   417,   418,   420,   421,   422,
     414,   410,   411,   432,   433,   419,   426,   427,   428,   423,
     658,     0,   657,   641,   642,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   637,   638,   639,
     640,   636,     0,   631,   634,   635,   655,   656,   716,   702,
     704,   706,   710,   708,   714,   712,   695,   689,   693,   694,
       0,   677,   678,   690,   691,   692,   686,   681,   687,   683,
     684,   685,   688,   682,     0,   573,   291,     0,   577,   575,
     580,     0,   569,   570,     0,   556,   557,   560,   572,   561,
     562,   563,   579,   564,   565,   566,   567,   568,   611,     0,
       0,     0,   618,   609,   610,   613,   614,     0,   595,   596,
     599,   600,   601,   602,   603,   604,   605,   608,   606,   607,
     370,   372,   367,     0,   364,   368,   369,     0,   895,     0,
     898,     0,     0,   902,   906,   893,   891,   892,     0,   880,
     883,   884,   885,   886,   887,   888,   889,   890,   917,     0,
       0,   912,   915,   916,    45,    50,     0,    37,    43,     0,
      64,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    69,    66,     0,     0,     0,     0,
       0,     0,     0,   204,   216,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   404,   401,     0,
       0,   633,   630,     0,     0,     0,     0,     0,     0,     0,
       0,   675,   680,   545,     0,     0,     0,     0,     0,     0,
       0,   554,   559,     0,     0,     0,     0,     0,   593,   598,
       0,     0,   366,   363,     0,     0,     0,     0,     0,     0,
       0,     0,   882,   879,     0,     0,   914,   911,    49,    41,
       0,     0,     0,     0,     0,   159,   160,   161,     0,     0,
       0,   198,   199,     0,     0,     0,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,     0,   193,
     194,   162,   163,   164,     0,     0,     0,   176,   177,   184,
     185,   186,   187,   192,     0,     0,     0,   156,     0,     0,
       0,     0,     0,   477,   478,   479,     0,     0,     0,     0,
       0,   761,     0,     0,     0,     0,     0,     0,   195,   196,
     197,     0,     0,    68,     0,     0,     0,   227,   228,   229,
     230,   203,     0,     0,     0,     0,     0,     0,   480,     0,
       0,     0,     0,     0,   403,     0,   660,   632,     0,     0,
       0,     0,     0,     0,     0,     0,   679,     0,     0,   571,
       0,     0,     0,   582,   558,     0,   615,   616,   617,     0,
     597,     0,     0,   365,   894,     0,   897,     0,   900,   901,
       0,     0,   881,     0,   919,   913,     0,     0,     0,     0,
       0,   697,   699,   701,     0,     0,   248,   155,   167,   168,
     169,   170,   171,   166,   173,   175,   393,   546,   585,   158,
     180,   181,   182,   183,   179,   483,    38,   662,   664,     0,
     725,   667,   355,     0,     0,   764,     0,     0,   189,   191,
       0,     0,    51,   218,   221,   222,   220,   225,   226,   224,
     462,   464,   466,   622,   460,   468,   472,   474,   476,   470,
       0,   659,   717,   703,   705,   707,   711,   709,   715,   713,
     574,   292,   578,   576,   581,   612,   619,   371,   373,   896,
     899,   904,   905,   903,   907,   248,    42,     0,     0,     0,
     240,   242,     0,   235,   238,   239,   282,   284,   286,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     302,     0,     0,   309,   311,   313,   315,   317,   318,   319,
     320,   321,   322,   281,     0,   255,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,     0,
     253,     0,   249,   250,   398,     0,   394,   395,   551,     0,
     547,   548,   590,     0,   586,   587,   488,     0,   484,   485,
     334,   335,   336,   337,   338,     0,   326,   329,   330,   331,
     332,   333,   730,     0,   726,   727,   672,     0,   668,   669,
     360,     0,   356,   357,     0,     0,     0,     0,     0,     0,
       0,   376,   379,   380,   381,   382,   383,   384,     0,     0,
       0,   349,     0,   341,   344,   345,   346,   347,   348,   769,
       0,   765,   766,     0,   871,     0,   874,   867,   868,     0,
     861,   864,   865,   866,   869,     0,   925,     0,   922,     0,
       0,     0,     0,   971,     0,   964,   967,   968,   969,   970,
      53,   627,     0,   623,   624,   721,     0,   720,     0,    62,
     909,   201,     0,     0,   237,   234,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   257,   232,
     245,     0,   247,   252,     0,   392,   397,   555,   543,   550,
     594,   584,   589,     0,   482,   487,   328,   325,   732,   724,
     729,   676,   666,   671,     0,   354,   359,     0,     0,     0,
       0,     0,     0,   378,   375,     0,     0,     0,   343,   340,
       0,   763,   768,     0,     0,     0,     0,   863,   860,   877,
       0,   924,   921,     0,     0,     0,     0,   966,   963,    55,
       0,    54,     0,   621,   626,     0,   719,   918,     0,     0,
     236,     0,     0,     0,     0,   290,   293,   294,   295,   296,
     297,   298,   299,   300,   301,     0,   307,   308,     0,     0,
       0,     0,     0,   256,     0,   251,     0,   396,     0,   549,
       0,   588,   541,   512,   513,   514,   496,   497,   517,   518,
     519,   520,   521,   522,   539,   499,   500,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   540,   493,   494,   495,   508,   509,   510,
     511,   505,   506,   507,     0,   490,   498,   515,   516,   501,
     502,   503,   504,   486,   327,   755,   757,     0,     0,   749,
     750,   751,   752,   753,   754,   742,   743,   747,   748,   744,
     745,   746,     0,   733,   734,   737,   738,   739,   740,   741,
     728,     0,   670,     0,   358,   385,   386,   387,   388,   389,
     390,   377,   350,   351,   352,   342,   787,   792,   794,     0,
     817,     0,   798,   786,   779,   780,   781,   784,   785,     0,
     771,   774,   775,   776,   777,   782,   783,   778,   767,   870,
       0,   873,     0,   862,   940,     0,   938,   936,   930,   934,
     935,     0,   927,   932,   933,   931,   923,   972,   973,   974,
     975,   965,    52,    57,     0,   625,     0,   241,   243,   283,
     285,   287,   289,   304,   305,   306,   303,   310,   312,   314,
     316,   323,   254,   399,   552,   591,   492,   489,     0,     0,
       0,     0,   731,   736,   673,   361,     0,     0,     0,     0,
       0,     0,     0,   773,   770,   872,   875,     0,     0,     0,
     929,   926,    56,   628,   722,   491,     0,     0,   759,   760,
     735,     0,     0,     0,   796,     0,   797,     0,   772,     0,
     937,     0,   928,   756,   758,   789,   790,   791,   788,   793,
     795,     0,   800,     0,   939,   829,   832,   834,   836,   828,
     827,   826,     0,   819,   822,   823,   824,   825,   805,     0,
     801,   802,   945,     0,   942,     0,     0,     0,     0,   821,
     818,     0,   799,   804,     0,   944,   941,     0,     0,     0,
       0,   820,   815,   814,   810,   812,   813,     0,   807,   811,
     803,   955,     0,     0,     0,   960,     0,   947,   950,   951,
     952,   953,   954,   943,   831,   830,   833,   835,   838,     0,
     809,   806,     0,     0,     0,     0,     0,   949,   946,   843,
       0,   839,   840,     0,   808,     0,   957,   958,   959,     0,
     948,     0,   837,   842,   816,   956,   961,   855,   857,   854,
     848,   850,   852,   853,     0,   845,   849,   851,   841,     0,
       0,   847,   844,     0,     0,   846,   856,   858
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392,   -54, -1392,  -621, -1392,   471,
   -1392, -1392, -1392, -1392, -1392, -1392,  -653, -1392, -1392, -1392,
     -67, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   513,   727,
      12,    31,    35,   -28,    27,    92,    93,    95,    97,   100,
     103, -1392, -1392, -1392, -1392,   108, -1392, -1392,   110,   115,
      47,    53,    55,    58, -1392, -1392,    60, -1392,    63, -1392,
      65,   122,    68, -1392, -1392,    70,    75,    80,    82,    87,
   -1392,    90, -1392,   127, -1392, -1392, -1392, -1392, -1392,    43,
   -1392, -1392, -1392,   453,   732, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   250, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392,   430, -1392,   223, -1392,  -744,   230, -1392,
   -1392, -1391, -1392, -1388, -1392, -1392, -1392, -1392,     0, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1056, -1392, -1054, -1392, -1053, -1392,
     138, -1392, -1392, -1392, -1392, -1392, -1392,   217, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,   198, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   211, -1392, -1392, -1392,   216,   690,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392,   210, -1392, -1392,
   -1392, -1392, -1392, -1392, -1040, -1392, -1392, -1392,   238, -1392,
   -1392, -1392,   241,   731, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1038, -1392,   -65, -1392,   -58, -1392,   -35, -1392,
     -25, -1392,   130,   132,   134, -1392, -1392, -1392, -1392, -1392,
     234, -1392, -1392,   -19,   -43, -1392, -1392, -1392, -1392, -1392,
     242, -1392, -1392, -1392,   243, -1392,   710, -1392,   -46, -1392,
   -1392, -1392, -1392, -1392,   -41, -1392, -1392, -1392, -1392, -1392,
     -20, -1392, -1392, -1392,   244, -1392, -1392, -1392,   247, -1392,
     706, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392,   194, -1392, -1392, -1392,   202,
     742, -1392, -1392, -1392,   -51, -1392,    -4, -1392,   -32, -1392,
   -1392, -1392,   236, -1392, -1392, -1392,   239, -1392,   729,   -55,
   -1392,   -39, -1392,     8, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1032, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
     248, -1392, -1392, -1392,    -8, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392,   225, -1392, -1392,
     -11, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392,   -82, -1392, -1392,  -114, -1392, -1392,
   -1392, -1392, -1392,   -74, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392,  -136, -1392, -1392,  -151, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,   240, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392,   541,   734, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392,   575,   741, -1392, -1392,
   -1392, -1392, -1392, -1392,   251, -1392, -1392,    -1, -1392, -1392,
   -1392, -1392, -1392, -1392,   -64, -1392, -1392,  -105, -1392, -1392,
   -1392, -1392, -1392, -1392, -1392, -1392, -1392, -1392,   237, -1392,
   -1392, -1392, -1392
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   777,
      82,    83,    39,    64,    79,    80,   793,  1000,  1100,  1101,
     873,    41,    66,    85,   459,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   488,   175,   176,   508,   177,   178,   179,
     180,   181,   182,   183,   494,   763,   184,   495,   185,   496,
     186,   187,   188,   509,   774,   189,   190,   191,   192,   193,
     526,   194,   527,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   463,   241,   242,    45,    68,   243,   536,   244,
     537,   796,   245,   538,   799,   246,   247,   248,   249,   204,
     473,   205,   464,   842,   843,   844,  1012,   845,  1013,   206,
     474,   207,   475,   901,   902,   903,  1041,   874,   875,   876,
    1016,   877,  1017,   878,  1018,   879,  1019,   880,   881,   575,
     882,   883,   884,   885,   886,   887,   888,   889,   890,   891,
    1030,  1296,   892,   893,   894,  1033,   895,  1034,   896,  1035,
     897,  1036,   898,  1037,   208,   516,   925,   926,   927,   928,
     929,   930,   931,   209,   522,   962,   963,   964,   965,   966,
     210,   519,   941,   942,   943,  1064,    59,    75,   423,   424,
     425,   590,   426,   591,   211,   520,   950,   951,   952,   953,
     954,   955,   956,   957,   212,   504,   905,   906,   907,  1044,
      47,    69,   296,   297,   298,   549,   299,   545,   300,   546,
     301,   547,   302,   550,   303,   555,   304,   552,   305,   553,
     306,   554,   213,   214,   215,   310,   216,   510,   917,   918,
     919,  1053,  1184,  1185,   217,   505,    53,    72,   909,   910,
     911,  1047,    55,    73,   384,   385,   386,   387,   388,   389,
     390,   574,   391,   578,   392,   577,   393,   394,   579,   395,
     218,   506,   913,   914,   915,  1050,    57,    74,   407,   408,
     409,   410,   411,   583,   412,   413,   414,   415,   416,   417,
     587,   312,   548,  1002,  1003,  1004,  1102,    49,    70,   342,
     343,   344,   559,   345,   219,   511,   220,   512,   221,   518,
     937,   938,   939,  1061,    51,    71,   360,   361,   362,   222,
     468,   223,   469,   224,   470,   366,   564,   367,   565,   368,
     566,   369,   568,   370,   567,   371,   570,   372,   569,   373,
     563,   319,   556,  1006,  1007,  1105,   225,   517,   933,   934,
     935,  1058,  1212,  1213,  1214,  1215,  1216,  1308,  1217,  1309,
    1218,  1219,   226,   227,   523,   970,   971,   972,  1080,  1249,
    1250,  1251,  1316,  1358,  1252,  1317,  1253,  1318,  1254,  1255,
    1256,  1322,  1379,  1380,  1381,  1391,  1407,  1408,  1409,  1429,
    1257,  1320,  1372,  1373,  1374,  1385,  1425,  1375,  1386,  1376,
    1387,  1377,  1388,  1440,  1441,  1442,  1451,  1464,  1465,  1466,
    1469,  1467,  1470,   228,   524,   979,   980,   981,   982,  1084,
     983,   984,  1086,   229,   525,    61,    76,   438,   439,   440,
     441,   595,   442,   443,   597,   444,   445,   446,   600,   833,
     447,   601,   230,   462,    63,    77,   450,   451,   452,   604,
     453,   231,   531,   987,   988,  1090,  1271,  1272,  1273,  1274,
    1329,  1275,  1327,  1383,  1384,  1394,  1416,  1417,  1418,  1432,
    1419,  1420,  1421,  1422,  1436,   232,   532,   994,   995,   996,
     997,   998,   999
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   322,   356,   337,   382,   403,   422,   435,
      78,   899,   338,  1175,   316,  1176,   363,   250,   313,   346,
     358,  1192,   396,   418,  1244,   436,  1245,  1246,   405,   374,
     317,   460,   364,   406,    28,   339,   461,   315,   420,   421,
     776,   268,    81,   831,    40,   340,   806,   807,   808,   311,
     341,   357,   448,   449,    29,   812,    30,    42,    31,    44,
    1460,   136,   137,  1461,   251,   314,   347,   359,    46,   397,
     419,    48,   437,   383,   404,  1056,   826,   318,  1057,   365,
    1460,   265,   534,  1461,   233,   234,  1091,   535,   235,  1092,
     130,   236,   237,   238,   239,    50,   269,  1293,  1294,  1295,
     266,   958,   959,   960,   267,    93,    94,    95,   543,   557,
     561,   776,   295,   544,   558,   562,   279,   323,    52,   420,
     421,   158,   280,   324,   281,   325,   592,   282,   326,   283,
     327,   593,   284,   328,   285,   329,   602,   287,   330,   288,
     331,   603,   606,   534,   289,   332,    84,   607,  1009,   290,
     333,   291,   334,   606,   794,   795,   292,   335,  1010,   293,
     336,   270,   271,   543,   272,  1014,   273,   455,  1011,   274,
    1015,  1395,   275,   158,  1396,  1038,   131,   276,  1038,   277,
    1039,   797,   798,  1040,   278,   758,   759,   760,   761,    54,
    1073,   286,   454,   136,   137,  1074,   294,   136,   137,   307,
    1078,   308,  1087,   309,   602,  1079,   348,  1088,  1097,  1089,
     847,   848,   457,  1098,  1365,    56,   349,   350,   351,   352,
     353,   354,   355,   832,   762,   846,   847,   848,   849,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
    1355,  1356,  1357,   861,   862,   863,   864,   865,   866,   867,
     868,   869,   870,   871,   872,   989,   990,   991,   992,  1411,
     840,   841,  1412,  1413,  1414,  1415,  1175,  1244,  1176,  1245,
    1246,    58,   158,    60,  1192,    91,    92,    93,    94,    95,
      96,    62,   376,   456,   458,    32,    33,    34,    35,   376,
    1038,   557,   572,   136,   137,  1302,  1303,  1134,   136,   137,
     465,  1306,   136,   137,   466,   158,  1307,   592,  1323,   158,
     467,   471,  1315,  1324,   472,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,    93,    94,    95,    96,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   476,   252,   253,   254,   477,   131,  1457,
    1458,  1366,  1367,  1368,  1330,   571,   136,   137,   478,  1331,
     133,   134,  1402,   376,   101,   102,   103,   255,   479,   136,
     137,   256,   257,   258,   138,   139,   140,   561,   259,   260,
     261,   375,  1333,   136,   137,   262,   480,   143,   376,   398,
     377,   378,   399,   400,   401,   263,   130,   131,   376,   136,
     137,   608,   609,   481,   482,   158,  1389,  1430,   136,   137,
     158,  1390,  1431,   483,   158,  1437,   573,   402,   136,   137,
    1438,   158,   427,   428,   429,   430,   431,   432,   433,   434,
    1195,  1196,  1197,  1198,   944,   945,   946,   947,   948,   949,
     484,   920,   921,   922,   923,   376,   924,   377,   378,   151,
     152,   485,   379,   380,   381,   866,   867,   868,   869,   870,
     871,   973,   974,   975,   486,   136,   137,   159,   158,  1264,
    1471,  1265,  1266,   487,   489,  1472,   240,   770,   771,   772,
     773,   158,   490,   491,   492,   493,   497,   498,   499,   500,
     264,   501,   250,   502,   322,   158,   337,   503,   507,   513,
     514,   515,   316,   338,   521,   356,   313,   528,   529,   530,
     346,   976,   533,   539,   540,   382,   541,   363,   317,   542,
     158,   358,   403,   551,   560,   315,   339,   576,   580,   268,
     158,   396,   582,   364,   581,   435,   340,   311,   418,   251,
     584,   341,   585,   405,   586,   588,   589,   610,   406,   594,
     596,   436,   357,   314,   598,   599,   605,   347,   611,   612,
     613,   614,   615,   616,   617,   318,   618,   619,   359,   265,
     620,   621,   622,   623,   624,   625,   631,   158,   397,   626,
     365,   627,   383,   628,   269,   419,   629,   630,   266,   404,
     632,   633,   267,   634,   635,   638,   636,   644,   437,   637,
     295,   645,   639,   640,   279,   646,   641,   642,   323,   643,
     280,   647,   281,   649,   324,   282,   325,   283,   648,   326,
     284,   327,   285,   650,   328,   287,   329,   288,   651,   330,
     652,   331,   289,  1334,   653,   654,   332,   290,   655,   291,
     656,   333,   657,   334,   292,   658,   659,   293,   335,   270,
     271,   336,   272,   660,   273,   661,   662,   274,   663,   664,
     275,   665,   666,   667,   668,   276,   669,   277,   670,   671,
     672,   673,   278,   674,   675,   676,   677,   678,   679,   286,
     159,   680,   240,   681,   294,   682,   684,   307,   685,   308,
     686,   309,   836,   687,   688,   689,   690,   692,   250,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   693,   863,   864,   865,   694,   961,   695,   696,
     435,   756,   697,   698,   993,   699,   700,   701,    87,   702,
     703,    88,   705,   967,   708,   977,   436,   709,   706,   710,
     711,   712,   713,    89,   714,   251,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   715,   717,   718,
     720,   721,   719,   722,   725,   729,   723,   726,   731,   727,
     728,   732,   734,   735,   737,   740,   736,   136,   137,   738,
     968,   739,   978,   437,   741,   743,   744,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   746,   747,   748,   130,
     131,  1236,   749,   750,   751,  1237,  1238,  1239,  1240,   754,
     752,   132,   133,   134,   753,  1241,  1242,   755,   135,   757,
     764,   136,   137,   765,   766,   767,   138,   139,   140,   141,
     142,   768,   769,   775,    30,   778,   779,   780,   781,   143,
     782,   783,   785,   784,   788,   786,   787,   790,   789,   144,
     791,   792,   145,   800,   801,   802,   803,   810,   835,   146,
     147,   804,   805,   809,   148,   900,   811,   834,   904,   158,
     813,   814,   815,   816,   908,   912,   916,   817,   932,   818,
     936,   819,   149,   940,   820,   969,   150,   986,  1001,   821,
     822,   823,   824,   825,   827,  1020,   829,  1005,  1021,   830,
    1022,   151,   152,   153,   154,   155,   156,  1023,  1024,  1025,
    1026,  1027,  1028,  1029,  1031,   157,  1032,  1042,  1043,  1045,
    1046,  1049,  1048,  1052,  1115,  1051,  1055,  1054,  1059,  1060,
    1062,  1063,  1116,   158,  1066,  1065,  1067,  1068,  1069,  1070,
    1071,  1072,  1075,  1076,  1077,  1082,  1104,  1081,  1083,  1085,
    1093,  1094,  1095,  1096,  1424,  1099,  1103,   264,  1107,  1106,
     382,  1108,  1109,   403,  1111,  1112,  1142,  1113,  1177,   316,
    1114,  1199,  1125,   313,   356,  1178,   396,   422,  1189,   418,
    1117,  1118,  1187,  1209,   405,   317,   363,  1207,  1128,   406,
     358,   961,   315,  1243,  1190,  1205,   268,  1126,  1179,  1210,
    1119,  1120,   364,  1267,   311,  1146,  1121,   967,  1180,  1247,
     993,  1122,  1123,  1186,  1124,   322,   977,   337,  1206,  1269,
     314,   357,  1127,   397,   338,  1129,   419,   383,  1130,  1188,
     404,   346,   318,  1174,  1208,  1131,   265,   359,  1204,  1132,
    1225,  1191,  1226,  1227,  1228,  1143,  1211,   339,  1229,   365,
    1200,   269,  1230,  1232,   968,   266,  1248,   340,  1233,   267,
    1147,  1234,   341,   978,  1144,  1260,  1270,   295,  1145,  1201,
    1268,   279,  1262,  1202,  1283,  1282,  1173,   280,   347,   281,
    1157,  1203,   282,  1259,   283,  1261,  1158,   284,  1159,   285,
    1286,  1160,   287,  1161,   288,  1277,  1162,  1304,  1163,   289,
    1287,  1165,  1278,  1166,   290,  1279,   291,  1305,  1167,  1280,
    1288,   292,  1310,  1168,   293,  1169,   270,   271,  1289,   272,
    1170,   273,  1290,  1171,   274,  1148,  1149,   275,  1150,   323,
    1151,  1291,   276,  1152,   277,   324,  1153,   325,  1292,   278,
     326,  1154,   327,  1155,  1311,   328,   286,   329,  1156,  1312,
     330,   294,   331,  1313,   307,  1164,   308,   332,   309,  1314,
    1172,  1297,   333,  1181,   334,  1182,  1298,  1183,  1319,   335,
    1321,  1328,   336,  1336,  1337,  1341,  1342,  1343,  1345,  1347,
    1349,  1351,   839,   828,  1362,  1361,  1363,  1378,  1326,  1299,
    1301,  1325,  1332,  1382,  1392,  1393,  1428,  1397,  1338,  1398,
    1399,  1339,  1344,  1346,  1350,  1353,  1354,  1359,  1360,  1364,
    1400,  1426,  1427,  1433,  1434,  1435,  1443,  1446,  1445,  1142,
    1439,  1177,  1447,  1448,  1449,  1452,  1199,  1453,  1178,  1454,
    1455,  1189,  1456,  1473,  1474,  1187,  1243,  1476,  1209,  1477,
     837,   683,  1207,  1267,  1110,  1008,  1135,  1190,  1133,  1300,
    1205,  1179,  1247,  1194,  1210,   691,  1235,  1224,  1146,  1269,
    1223,  1180,   733,  1231,  1137,  1136,  1186,  1335,   704,  1193,
    1138,  1139,   724,  1206,  1369,   730,  1141,  1140,  1285,  1222,
    1221,   716,  1188,   707,  1284,  1340,  1174,  1258,  1220,  1208,
    1370,  1410,  1348,  1204,  1191,  1401,  1444,  1468,  1143,  1248,
    1475,  1211,  1369,   838,  1403,  1200,  1270,  1263,   985,  1352,
    1268,  1423,  1450,  1147,  1281,     0,   742,  1144,  1370,     0,
    1405,  1145,  1276,     0,  1201,     0,     0,   745,  1202,  1173,
       0,     0,     0,  1157,     0,     0,  1203,  1371,     0,  1158,
       0,  1159,     0,  1403,  1160,     0,  1161,     0,     0,  1162,
       0,  1163,     0,     0,  1165,     0,  1166,     0,     0,  1405,
       0,  1167,     0,     0,  1459,  1371,  1168,  1406,  1169,     0,
       0,  1404,     0,  1170,     0,     0,  1171,     0,  1148,  1149,
    1462,  1150,     0,  1151,  1459,     0,  1152,     0,     0,  1153,
       0,     0,     0,     0,  1154,     0,  1155,     0,     0,     0,
    1462,  1156,     0,     0,     0,     0,  1406,     0,  1164,     0,
    1404,     0,     0,  1172,     0,     0,  1181,     0,  1182,     0,
    1183,    91,    92,    93,    94,    95,    96,  1463,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1463,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       0,     0,     0,     0,   131,   376,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   134,     0,     0,
       0,     0,     0,     0,     0,   136,   137,     0,   257,     0,
     138,   139,   140,     0,   259,   260,   261,     0,     0,     0,
       0,   262,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   263,   124,   125,   126,   127,     0,     0,     0,     0,
       0,     0,   131,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   134,     0,     0,     0,     0,
       0,     0,   320,   136,   137,     0,     0,     0,     0,     0,
       0,     0,   259,   260,   261,     0,     0,     0,     0,   262,
     321,     0,     0,     0,     0,   151,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   158
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,   755,    70,  1053,    69,  1053,    71,    68,    69,    70,
      71,  1053,    73,    74,  1080,    76,  1080,  1080,    74,    72,
      69,     3,    71,    74,     0,    70,     8,    69,   153,   154,
     661,    69,   236,    18,     7,    70,   699,   700,   701,    69,
      70,    71,    12,    13,     5,   708,     7,     7,     9,     7,
    1451,   124,   125,  1451,    68,    69,    70,    71,     7,    73,
      74,     7,    76,    73,    74,     3,   729,    69,     6,    71,
    1471,    69,     3,  1471,    15,    16,     3,     8,    19,     6,
     102,    22,    23,    24,    25,     7,    69,    55,    56,    57,
      69,   164,   165,   166,    69,    32,    33,    34,     3,     3,
       3,   732,    69,     8,     8,     8,    69,    70,     7,   153,
     154,   236,    69,    70,    69,    70,     3,    69,    70,    69,
      70,     8,    69,    70,    69,    70,     3,    69,    70,    69,
      70,     8,     3,     3,    69,    70,    10,     8,     8,    69,
      70,    69,    70,     3,    17,    18,    69,    70,     8,    69,
      70,    69,    69,     3,    69,     3,    69,     3,     8,    69,
       8,     3,    69,   236,     6,     3,   103,    69,     3,    69,
       8,    20,    21,     8,    69,   200,   201,   202,   203,     7,
       3,    69,     6,   124,   125,     8,    69,   124,   125,    69,
       3,    69,     3,    69,     3,     8,   133,     8,     3,     8,
      41,    42,     8,     8,    40,     7,   143,   144,   145,   146,
     147,   148,   149,   198,   239,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     169,   170,   171,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   219,   220,   221,   222,   211,
      27,    28,   214,   215,   216,   217,  1306,  1323,  1306,  1323,
    1323,     7,   236,     7,  1306,    30,    31,    32,    33,    34,
      35,     7,   104,     4,     3,   236,   237,   238,   239,   104,
       3,     3,     3,   124,   125,     8,     8,  1041,   124,   125,
       4,     3,   124,   125,     4,   236,     8,     3,     3,   236,
       4,     4,     8,     8,     4,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    32,    33,    34,    35,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     4,    99,   100,   101,     4,   103,   180,
     181,   177,   178,   179,     3,     8,   124,   125,     4,     8,
     115,   116,   184,   104,    70,    71,    72,   122,     4,   124,
     125,   126,   127,   128,   129,   130,   131,     3,   133,   134,
     135,    40,     8,   124,   125,   140,     4,   142,   104,   105,
     106,   107,   108,   109,   110,   150,   102,   103,   104,   124,
     125,   455,   456,     4,     4,   236,     3,     3,   124,   125,
     236,     8,     8,     4,   236,     3,     8,   133,   124,   125,
       8,   236,   190,   191,   192,   193,   194,   195,   196,   197,
     136,   137,   138,   139,   156,   157,   158,   159,   160,   161,
       4,   144,   145,   146,   147,   104,   149,   106,   107,   204,
     205,     4,   111,   112,   113,    63,    64,    65,    66,    67,
      68,   186,   187,   188,     4,   124,   125,   534,   236,   210,
       3,   212,   213,     4,     4,     8,   543,   117,   118,   119,
     120,   236,     4,     4,     4,     4,     4,     4,     4,     4,
     557,     4,   543,     4,   561,   236,   561,     4,     4,     4,
       4,     4,   557,   561,     4,   572,   557,     4,     4,     4,
     561,   236,     4,     4,     4,   582,     4,   572,   557,     4,
     236,   572,   589,     4,     4,   557,   561,     4,     4,   557,
     236,   582,     3,   572,     8,   602,   561,   557,   589,   543,
       4,   561,     4,   589,     4,     8,     3,   236,   589,     4,
       4,   602,   572,   557,     4,     4,     4,   561,     4,     4,
       4,     4,   239,   239,   239,   557,     4,     4,   572,   557,
       4,   237,   239,     4,     4,     4,   239,   236,   582,   237,
     572,   237,   582,   237,   557,   589,   237,   237,   557,   589,
     238,   238,   557,   238,   237,     4,   238,     4,   602,   237,
     557,     4,   237,   237,   557,     4,   239,   239,   561,   239,
     557,   239,   557,   238,   561,   557,   561,   557,   239,   561,
     557,   561,   557,   237,   561,   557,   561,   557,   237,   561,
     237,   561,   557,  1286,   239,     4,   561,   557,     4,   557,
       4,   561,   237,   561,   557,     4,     4,   557,   561,   557,
     557,   561,   557,     4,   557,     4,     4,   557,   239,   239,
     557,   239,     4,     4,     4,   557,     4,   557,     4,   237,
       4,     4,   557,     4,     4,     4,     4,   239,   239,   557,
     747,   239,   749,     4,   557,     4,     4,   557,     4,   557,
       4,   557,   746,   239,   239,   237,   237,     4,   749,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,     4,    60,    61,    62,     4,   784,     4,     4,
     787,     5,     4,   237,   791,     4,     4,     4,    11,     4,
       4,    14,     4,   784,     4,   786,   787,     4,   237,     4,
       4,     4,     4,    26,     4,   749,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     4,     4,     4,
       4,     4,   237,     4,     4,     4,   239,   239,     4,   239,
     239,     4,   239,     4,     4,     4,   237,   124,   125,   237,
     784,   237,   786,   787,     4,     4,   237,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     4,     7,     7,   102,
     103,   168,     7,     7,   236,   172,   173,   174,   175,     7,
     236,   114,   115,   116,   236,   182,   183,     7,   121,   236,
     236,   124,   125,   236,     5,     5,   129,   130,   131,   132,
     133,     5,   236,     5,     7,   236,     5,     5,     5,   142,
       5,     7,     5,     7,   236,     7,     7,     5,   236,   152,
       7,     5,   155,   236,   236,   236,     5,     7,     5,   162,
     163,   236,   236,   236,   167,     7,   236,   199,     7,   236,
     236,   236,   236,   236,     7,     7,     7,   236,     7,   236,
       7,   236,   185,     7,   236,     7,   189,     7,     7,   236,
     236,   236,   236,   236,   236,     4,   236,   151,     4,   236,
       4,   204,   205,   206,   207,   208,   209,     4,     4,     4,
       4,     4,     4,     4,     4,   218,     4,     6,     3,     6,
       3,     3,     6,     3,   237,     6,     3,     6,     6,     3,
       6,     3,   239,   236,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     6,     4,     4,
       4,     4,     4,     4,   176,   236,     6,  1044,     6,     8,
    1047,     4,     4,  1050,     4,     4,  1053,     4,  1053,  1044,
       4,  1058,     4,  1044,  1061,  1053,  1047,  1064,  1053,  1050,
     237,   239,  1053,  1058,  1050,  1044,  1061,  1058,     4,  1050,
    1061,  1078,  1044,  1080,  1053,  1058,  1044,   239,  1053,  1058,
     237,   237,  1061,  1090,  1044,  1053,   237,  1078,  1053,  1080,
    1097,   237,   237,  1053,   237,  1102,  1087,  1102,  1058,  1090,
    1044,  1061,   237,  1047,  1102,     4,  1050,  1047,     4,  1053,
    1050,  1102,  1044,  1053,  1058,     4,  1044,  1061,  1058,     4,
     237,  1053,   237,   237,   237,  1053,  1058,  1102,   237,  1061,
    1058,  1044,   237,   239,  1078,  1044,  1080,  1102,   237,  1044,
    1053,   237,  1102,  1087,  1053,     4,  1090,  1044,  1053,  1058,
    1090,  1044,     4,  1058,     3,     6,  1053,  1044,  1102,  1044,
    1053,  1058,  1044,   239,  1044,   237,  1053,  1044,  1053,  1044,
       4,  1053,  1044,  1053,  1044,   239,  1053,     8,  1053,  1044,
     236,  1053,   239,  1053,  1044,   239,  1044,     8,  1053,   239,
     236,  1044,     4,  1053,  1044,  1053,  1044,  1044,   236,  1044,
    1053,  1044,   236,  1053,  1044,  1053,  1053,  1044,  1053,  1102,
    1053,   236,  1044,  1053,  1044,  1102,  1053,  1102,   236,  1044,
    1102,  1053,  1102,  1053,     4,  1102,  1044,  1102,  1053,     8,
    1102,  1044,  1102,     3,  1044,  1053,  1044,  1102,  1044,     8,
    1053,   236,  1102,  1053,  1102,  1053,   236,  1053,     4,  1102,
       4,     4,  1102,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   749,   732,     5,     7,     5,     7,  1262,   236,
     236,   236,   236,     7,     6,     3,     5,     4,   239,     4,
       4,   239,   237,   239,   237,   236,   236,   236,   236,   236,
       4,   236,   236,     4,     4,     4,     4,   239,     4,  1306,
       7,  1306,   237,   237,     4,     6,  1313,     3,  1306,   236,
     236,  1306,   236,     4,     4,  1306,  1323,   236,  1313,   236,
     747,   534,  1313,  1330,  1014,   835,  1043,  1306,  1038,  1131,
    1313,  1306,  1323,  1056,  1313,   543,  1078,  1066,  1306,  1330,
    1064,  1306,   592,  1073,  1046,  1044,  1306,  1306,   557,  1055,
    1047,  1049,   582,  1313,  1361,   589,  1052,  1050,  1104,  1063,
    1061,   572,  1306,   561,  1102,  1313,  1306,  1082,  1060,  1313,
    1361,  1393,  1323,  1313,  1306,  1389,  1430,  1453,  1306,  1323,
    1471,  1313,  1389,   748,  1391,  1313,  1330,  1087,   787,  1330,
    1330,  1395,  1437,  1306,  1097,    -1,   602,  1306,  1389,    -1,
    1391,  1306,  1091,    -1,  1313,    -1,    -1,   606,  1313,  1306,
      -1,    -1,    -1,  1306,    -1,    -1,  1313,  1361,    -1,  1306,
      -1,  1306,    -1,  1430,  1306,    -1,  1306,    -1,    -1,  1306,
      -1,  1306,    -1,    -1,  1306,    -1,  1306,    -1,    -1,  1430,
      -1,  1306,    -1,    -1,  1451,  1389,  1306,  1391,  1306,    -1,
      -1,  1391,    -1,  1306,    -1,    -1,  1306,    -1,  1306,  1306,
    1451,  1306,    -1,  1306,  1471,    -1,  1306,    -1,    -1,  1306,
      -1,    -1,    -1,    -1,  1306,    -1,  1306,    -1,    -1,    -1,
    1471,  1306,    -1,    -1,    -1,    -1,  1430,    -1,  1306,    -1,
    1430,    -1,    -1,  1306,    -1,    -1,  1306,    -1,  1306,    -1,
    1306,    30,    31,    32,    33,    34,    35,  1451,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1471,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,   103,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,
     129,   130,   131,    -1,   133,   134,   135,    -1,    -1,    -1,
      -1,   140,    -1,    -1,    85,    86,    87,    88,    89,    90,
      91,   150,    93,    94,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   133,   134,   135,    -1,    -1,    -1,    -1,   140,
     141,    -1,    -1,    -1,    -1,   204,   205,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   236,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   204,   205,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   236
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,     5,
       7,     9,   236,   237,   238,   239,   255,   256,   257,   262,
       7,   271,     7,   276,     7,   335,     7,   450,     7,   537,
       7,   554,     7,   486,     7,   492,     7,   516,     7,   426,
       7,   665,     7,   684,   263,   258,   272,   277,   336,   451,
     538,   555,   487,   493,   517,   427,   666,   685,   255,   264,
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
     328,   329,   330,   331,   349,   351,   359,   361,   404,   413,
     420,   434,   444,   472,   473,   474,   476,   484,   510,   544,
     546,   548,   559,   561,   563,   586,   602,   603,   653,   663,
     682,   691,   715,    15,    16,    19,    22,    23,    24,    25,
     270,   333,   334,   337,   339,   342,   345,   346,   347,   348,
     544,   546,    99,   100,   101,   122,   126,   127,   128,   133,
     134,   135,   140,   150,   270,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   295,   298,   299,   300,
     301,   302,   303,   306,   308,   310,   311,   312,   315,   316,
     317,   318,   319,   321,   323,   329,   452,   453,   454,   456,
     458,   460,   462,   464,   466,   468,   470,   472,   473,   474,
     475,   510,   531,   544,   546,   548,   559,   561,   563,   581,
     123,   141,   270,   300,   301,   302,   303,   306,   308,   310,
     312,   315,   316,   317,   318,   319,   321,   464,   466,   468,
     470,   510,   539,   540,   541,   543,   544,   546,   133,   143,
     144,   145,   146,   147,   148,   149,   270,   510,   544,   546,
     556,   557,   558,   559,   561,   563,   565,   567,   569,   571,
     573,   575,   577,   579,   484,    40,   104,   106,   107,   111,
     112,   113,   270,   378,   494,   495,   496,   497,   498,   499,
     500,   502,   504,   506,   507,   509,   544,   546,   105,   108,
     109,   110,   133,   270,   378,   498,   504,   518,   519,   520,
     521,   522,   524,   525,   526,   527,   528,   529,   544,   546,
     153,   154,   270,   428,   429,   430,   432,   190,   191,   192,
     193,   194,   195,   196,   197,   270,   544,   546,   667,   668,
     669,   670,   672,   673,   675,   676,   677,   680,    12,    13,
     686,   687,   688,   690,     6,     3,     4,     8,     3,   274,
       3,     8,   683,   332,   352,     4,     4,     4,   560,   562,
     564,     4,     4,   350,   360,   362,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   293,     4,
       4,     4,     4,     4,   304,   307,   309,     4,     4,     4,
       4,     4,     4,     4,   445,   485,   511,     4,   296,   313,
     477,   545,   547,     4,     4,     4,   405,   587,   549,   421,
     435,     4,   414,   604,   654,   664,   320,   322,     4,     4,
       4,   692,   716,     4,     3,     8,   338,   340,   343,     4,
       4,     4,     4,     3,     8,   457,   459,   461,   532,   455,
     463,     4,   467,   469,   471,   465,   582,     3,     8,   542,
       4,     3,     8,   580,   566,   568,   570,   574,   572,   578,
     576,     8,     3,     8,   501,   379,     4,   505,   503,   508,
       4,     8,     3,   523,     4,     4,     4,   530,     8,     3,
     431,   433,     3,     8,     4,   671,     4,   674,     4,     4,
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
       4,     4,     4,     4,   453,     4,   237,   540,     4,     4,
       4,     4,     4,     4,     4,     4,   558,     4,     4,   237,
       4,     4,     4,   239,   496,     4,   239,   239,   239,     4,
     520,     4,     4,   429,   239,     4,   237,     4,   237,   237,
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
      67,    68,    69,   270,   367,   368,   369,   371,   373,   375,
     377,   378,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   392,   393,   394,   396,   398,   400,   402,   367,
       7,   363,   364,   365,     7,   446,   447,   448,     7,   488,
     489,   490,     7,   512,   513,   514,     7,   478,   479,   480,
     144,   145,   146,   147,   149,   406,   407,   408,   409,   410,
     411,   412,     7,   588,   589,   590,     7,   550,   551,   552,
       7,   422,   423,   424,   156,   157,   158,   159,   160,   161,
     436,   437,   438,   439,   440,   441,   442,   443,   164,   165,
     166,   270,   415,   416,   417,   418,   419,   544,   546,     7,
     605,   606,   607,   186,   187,   188,   236,   544,   546,   655,
     656,   657,   658,   660,   661,   667,     7,   693,   694,   219,
     220,   221,   222,   270,   717,   718,   719,   720,   721,   722,
     267,     7,   533,   534,   535,   151,   583,   584,   363,     8,
       8,     8,   356,   358,     3,     8,   370,   372,   374,   376,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     390,     4,     4,   395,   397,   399,   401,   403,     3,     8,
       8,   366,     6,     3,   449,     6,     3,   491,     6,     3,
     515,     6,     3,   481,     6,     3,     3,     6,   591,     6,
       3,   553,     6,     3,   425,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     608,     6,     3,     4,   659,     4,   662,     3,     8,     8,
     695,     3,     6,     4,     4,     4,     4,     3,     8,   236,
     268,   269,   536,     6,     3,   585,     8,     6,     4,     4,
     354,     4,     4,     4,     4,   237,   239,   237,   239,   237,
     237,   237,   237,   237,   237,     4,   239,   237,     4,     4,
       4,     4,     4,   368,   367,   365,   452,   448,   494,   490,
     518,   514,   270,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   295,   298,   299,   300,   301,   302,
     303,   306,   308,   310,   311,   312,   315,   316,   317,   318,
     319,   321,   323,   329,   378,   444,   462,   464,   466,   468,
     470,   472,   473,   474,   482,   483,   510,   544,   546,   559,
     561,   563,   581,   480,   407,   136,   137,   138,   139,   270,
     280,   281,   282,   329,   378,   484,   510,   544,   546,   559,
     561,   563,   592,   593,   594,   595,   596,   598,   600,   601,
     590,   556,   552,   428,   424,   237,   237,   237,   237,   237,
     237,   437,   239,   237,   237,   416,   168,   172,   173,   174,
     175,   182,   183,   270,   394,   396,   398,   544,   546,   609,
     610,   611,   614,   616,   618,   619,   620,   630,   607,   239,
       4,   237,     4,   656,   210,   212,   213,   270,   378,   544,
     546,   696,   697,   698,   699,   701,   694,   239,   239,   239,
     239,   718,     6,     3,   539,   535,     4,   236,   236,   236,
     236,   236,   236,    55,    56,    57,   391,   236,   236,   236,
     400,   236,     8,     8,     8,     8,     3,     8,   597,   599,
       4,     4,     8,     3,     8,     8,   612,   615,   617,     4,
     631,     4,   621,     3,     8,   236,   255,   702,     4,   700,
       3,     8,   236,     8,   266,   483,     4,     4,   239,   239,
     594,     4,     4,     4,   237,     4,   239,     4,   610,     4,
     237,     4,   697,   236,   236,   169,   170,   171,   613,   236,
     236,     7,     5,     5,   236,    40,   177,   178,   179,   270,
     544,   546,   632,   633,   634,   637,   639,   641,     7,   622,
     623,   624,     7,   703,   704,   635,   638,   640,   642,     3,
       8,   625,     6,     3,   705,     3,     6,     4,     4,     4,
       4,   633,   184,   270,   378,   544,   546,   626,   627,   628,
     624,   211,   214,   215,   216,   217,   706,   707,   708,   710,
     711,   712,   713,   704,   176,   636,   236,   236,     5,   629,
       3,     8,   709,     4,     4,     4,   714,     3,     8,     7,
     643,   644,   645,     4,   627,     4,   239,   237,   237,     4,
     707,   646,     6,     3,   236,   236,   236,   180,   181,   270,
     371,   373,   544,   546,   647,   648,   649,   651,   645,   650,
     652,     3,     8,     4,     4,   648,   236,   236
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
     368,   368,   370,   369,   372,   371,   374,   373,   376,   375,
     377,   379,   378,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   390,   389,   391,   391,   391,   392,   393,   395,
     394,   397,   396,   399,   398,   401,   400,   400,   400,   400,
     400,   400,   403,   402,   405,   404,   406,   406,   406,   407,
     407,   407,   407,   407,   408,   409,   410,   411,   412,   414,
     413,   415,   415,   415,   416,   416,   416,   416,   416,   416,
     417,   418,   419,   421,   420,   422,   422,   423,   423,   423,
     425,   424,   427,   426,   428,   428,   428,   428,   429,   429,
     431,   430,   433,   432,   435,   434,   436,   436,   436,   437,
     437,   437,   437,   437,   437,   438,   439,   440,   441,   442,
     443,   445,   444,   446,   446,   447,   447,   447,   449,   448,
     451,   450,   452,   452,   452,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   455,
     454,   457,   456,   459,   458,   461,   460,   463,   462,   465,
     464,   467,   466,   469,   468,   471,   470,   472,   473,   474,
     475,   477,   476,   478,   478,   479,   479,   479,   481,   480,
     482,   482,   482,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   485,   484,   487,   486,   488,   488,   489,   489,
     489,   491,   490,   493,   492,   494,   494,   495,   495,   495,
     496,   496,   496,   496,   496,   496,   496,   496,   496,   496,
     497,   498,   499,   501,   500,   503,   502,   505,   504,   506,
     508,   507,   509,   511,   510,   512,   512,   513,   513,   513,
     515,   514,   517,   516,   518,   518,   519,   519,   519,   520,
     520,   520,   520,   520,   520,   520,   520,   520,   520,   520,
     521,   523,   522,   524,   525,   526,   527,   528,   530,   529,
     532,   531,   533,   533,   534,   534,   534,   536,   535,   538,
     537,   539,   539,   539,   540,   540,   540,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   540,   540,   542,   541,
     543,   545,   544,   547,   546,   549,   548,   550,   550,   551,
     551,   551,   553,   552,   555,   554,   556,   556,   557,   557,
     557,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   560,   559,   562,   561,
     564,   563,   566,   565,   568,   567,   570,   569,   572,   571,
     574,   573,   576,   575,   578,   577,   580,   579,   582,   581,
     583,   585,   584,   587,   586,   588,   588,   589,   589,   589,
     591,   590,   592,   592,   593,   593,   593,   594,   594,   594,
     594,   594,   594,   594,   594,   594,   594,   594,   594,   594,
     594,   594,   594,   594,   595,   597,   596,   599,   598,   600,
     601,   602,   604,   603,   605,   605,   606,   606,   606,   608,
     607,   609,   609,   609,   610,   610,   610,   610,   610,   610,
     610,   610,   610,   610,   610,   610,   610,   612,   611,   613,
     613,   613,   615,   614,   617,   616,   618,   619,   621,   620,
     622,   622,   623,   623,   623,   625,   624,   626,   626,   626,
     627,   627,   627,   627,   627,   629,   628,   631,   630,   632,
     632,   632,   633,   633,   633,   633,   633,   633,   633,   635,
     634,   636,   638,   637,   640,   639,   642,   641,   643,   643,
     644,   644,   644,   646,   645,   647,   647,   647,   648,   648,
     648,   648,   648,   648,   648,   650,   649,   652,   651,   654,
     653,   655,   655,   655,   656,   656,   656,   656,   656,   656,
     657,   659,   658,   660,   662,   661,   664,   663,   666,   665,
     667,   667,   667,   668,   668,   668,   668,   668,   668,   668,
     668,   668,   668,   668,   669,   671,   670,   672,   674,   673,
     675,   676,   678,   677,   679,   679,   681,   680,   683,   682,
     685,   684,   686,   686,   686,   687,   687,   689,   688,   690,
     692,   691,   693,   693,   693,   695,   694,   696,   696,   696,
     697,   697,   697,   697,   697,   697,   697,   698,   700,   699,
     702,   701,   703,   703,   703,   705,   704,   706,   706,   706,
     707,   707,   707,   707,   707,   709,   708,   710,   711,   712,
     714,   713,   716,   715,   717,   717,   717,   718,   718,   718,
     718,   718,   719,   720,   721,   722
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
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
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     3
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
  "$@108", "client_classes_list", "not_empty_classes_list",
  "client_class_entry", "$@109", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@110",
  "client_class_template_test", "$@111", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_sockets", "$@112",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@113", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@114",
  "control_socket_type_value", "control_socket_name", "$@115",
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
    1153,  1154,  1157,  1157,  1166,  1166,  1175,  1175,  1184,  1184,
    1193,  1199,  1199,  1208,  1214,  1220,  1226,  1232,  1238,  1244,
    1250,  1256,  1262,  1262,  1270,  1271,  1272,  1275,  1281,  1287,
    1287,  1296,  1296,  1305,  1305,  1314,  1314,  1322,  1325,  1328,
    1331,  1334,  1339,  1339,  1348,  1348,  1359,  1360,  1361,  1366,
    1367,  1368,  1369,  1370,  1373,  1378,  1383,  1388,  1393,  1400,
    1400,  1413,  1414,  1415,  1420,  1421,  1422,  1423,  1424,  1425,
    1428,  1434,  1440,  1446,  1446,  1457,  1458,  1461,  1462,  1463,
    1468,  1468,  1478,  1478,  1488,  1489,  1490,  1493,  1496,  1497,
    1500,  1500,  1509,  1509,  1518,  1518,  1530,  1531,  1532,  1537,
    1538,  1539,  1540,  1541,  1542,  1545,  1551,  1557,  1563,  1569,
    1575,  1584,  1584,  1598,  1599,  1602,  1603,  1604,  1613,  1613,
    1639,  1639,  1650,  1651,  1652,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,
    1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,  1682,
    1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,
    1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,
    1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,  1711,  1714,
    1714,  1723,  1723,  1732,  1732,  1741,  1741,  1750,  1750,  1759,
    1759,  1769,  1769,  1781,  1781,  1792,  1792,  1803,  1809,  1815,
    1821,  1829,  1829,  1841,  1842,  1846,  1847,  1848,  1853,  1853,
    1861,  1862,  1863,  1868,  1869,  1870,  1871,  1872,  1873,  1874,
    1875,  1876,  1877,  1878,  1879,  1880,  1881,  1882,  1883,  1884,
    1885,  1886,  1887,  1888,  1889,  1890,  1891,  1892,  1893,  1894,
    1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,  1904,
    1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,  1914,
    1915,  1916,  1923,  1923,  1937,  1937,  1946,  1947,  1950,  1951,
    1952,  1959,  1959,  1974,  1974,  1988,  1989,  1992,  1993,  1994,
    1999,  2000,  2001,  2002,  2003,  2004,  2005,  2006,  2007,  2008,
    2011,  2013,  2019,  2021,  2021,  2030,  2030,  2039,  2039,  2048,
    2050,  2050,  2059,  2069,  2069,  2082,  2083,  2088,  2089,  2090,
    2097,  2097,  2109,  2109,  2121,  2122,  2127,  2128,  2129,  2136,
    2137,  2138,  2139,  2140,  2141,  2142,  2143,  2144,  2145,  2146,
    2149,  2151,  2151,  2160,  2162,  2164,  2170,  2176,  2182,  2182,
    2196,  2196,  2209,  2210,  2213,  2214,  2215,  2220,  2220,  2230,
    2230,  2240,  2241,  2242,  2247,  2248,  2249,  2250,  2251,  2252,
    2253,  2254,  2255,  2256,  2257,  2258,  2259,  2260,  2261,  2262,
    2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,  2273,  2273,
    2282,  2288,  2288,  2313,  2313,  2343,  2343,  2354,  2355,  2358,
    2359,  2360,  2365,  2365,  2374,  2374,  2383,  2384,  2387,  2388,
    2389,  2395,  2396,  2397,  2398,  2399,  2400,  2401,  2402,  2403,
    2404,  2405,  2406,  2407,  2408,  2409,  2412,  2412,  2421,  2421,
    2430,  2430,  2439,  2439,  2448,  2448,  2457,  2457,  2466,  2466,
    2475,  2475,  2484,  2484,  2493,  2493,  2502,  2502,  2516,  2516,
    2527,  2530,  2530,  2544,  2544,  2555,  2556,  2559,  2560,  2561,
    2566,  2566,  2576,  2577,  2580,  2581,  2582,  2587,  2588,  2589,
    2590,  2591,  2592,  2593,  2594,  2595,  2596,  2597,  2598,  2599,
    2600,  2601,  2602,  2603,  2606,  2608,  2608,  2617,  2617,  2627,
    2633,  2641,  2649,  2649,  2660,  2661,  2664,  2665,  2666,  2671,
    2671,  2679,  2680,  2681,  2686,  2687,  2688,  2689,  2690,  2691,
    2692,  2693,  2694,  2695,  2696,  2697,  2698,  2701,  2701,  2710,
    2711,  2712,  2715,  2715,  2724,  2724,  2733,  2739,  2745,  2745,
    2756,  2757,  2760,  2761,  2762,  2767,  2767,  2775,  2776,  2777,
    2782,  2783,  2784,  2785,  2786,  2789,  2789,  2800,  2800,  2813,
    2814,  2815,  2820,  2821,  2822,  2823,  2824,  2825,  2826,  2829,
    2829,  2837,  2840,  2840,  2849,  2849,  2858,  2858,  2869,  2870,
    2873,  2874,  2875,  2880,  2880,  2888,  2889,  2890,  2895,  2896,
    2897,  2898,  2899,  2900,  2901,  2904,  2904,  2913,  2913,  2924,
    2924,  2937,  2938,  2939,  2944,  2945,  2946,  2947,  2948,  2949,
    2952,  2958,  2958,  2967,  2973,  2973,  2983,  2983,  2996,  2996,
    3006,  3007,  3008,  3013,  3014,  3015,  3016,  3017,  3018,  3019,
    3020,  3021,  3022,  3023,  3026,  3032,  3032,  3041,  3047,  3047,
    3056,  3062,  3068,  3068,  3077,  3078,  3081,  3081,  3092,  3092,
    3104,  3104,  3114,  3115,  3116,  3122,  3123,  3126,  3126,  3137,
    3145,  3145,  3158,  3159,  3160,  3166,  3166,  3174,  3175,  3176,
    3181,  3182,  3183,  3184,  3185,  3186,  3187,  3190,  3196,  3196,
    3205,  3205,  3216,  3217,  3218,  3223,  3223,  3231,  3232,  3233,
    3238,  3239,  3240,  3241,  3242,  3245,  3245,  3254,  3260,  3266,
    3272,  3272,  3281,  3281,  3292,  3293,  3294,  3299,  3300,  3301,
    3302,  3303,  3306,  3312,  3318,  3324
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
#line 6991 "dhcp4_parser.cc"

#line 3330 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
