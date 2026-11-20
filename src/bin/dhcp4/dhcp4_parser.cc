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
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 421 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 427 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 433 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 439 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 481 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 487 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 493 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 326 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 499 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 326 "dhcp4_parser.yy"
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
#line 335 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 788 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 336 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 794 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 337 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 800 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 338 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 806 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 339 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 812 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 340 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 818 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 341 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 824 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 342 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 830 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 343 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 836 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 344 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 842 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 345 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 848 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 346 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 854 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 347 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 860 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 355 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 356 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 357 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 358 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 359 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 890 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 360 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 361 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 902 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 364 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 911 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 369 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 374 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 932 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 380 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 938 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 387 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 392 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 959 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 398 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 967 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 403 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 976 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 406 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 984 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 414 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 993 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 418 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1002 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 422 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1010 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 428 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1018 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 430 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1027 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 439 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1036 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 443 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1045 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 447 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1053 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 457 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 466 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 471 "dhcp4_parser.yy"
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
#line 481 "dhcp4_parser.yy"
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
#line 490 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 498 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 504 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 508 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 515 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1148 "dhcp4_parser.cc"
    break;

  case 143: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 597 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1158 "dhcp4_parser.cc"
    break;

  case 144: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 603 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 145: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 609 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1178 "dhcp4_parser.cc"
    break;

  case 146: // renew_timer: "renew-timer" ":" "integer"
#line 615 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 147: // rebind_timer: "rebind-timer" ":" "integer"
#line 621 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 148: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 627 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 149: // t1_percent: "t1-percent" ":" "floating point"
#line 633 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1218 "dhcp4_parser.cc"
    break;

  case 150: // t2_percent: "t2-percent" ":" "floating point"
#line 639 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1228 "dhcp4_parser.cc"
    break;

  case 151: // cache_threshold: "cache-threshold" ":" "floating point"
#line 645 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 152: // cache_max_age: "cache-max-age" ":" "integer"
#line 651 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 153: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 657 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 154: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 663 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 155: // $@20: %empty
#line 669 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 156: // server_tag: "server-tag" $@20 ":" "constant string"
#line 672 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 157: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 678 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 158: // $@21: %empty
#line 684 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 159: // allocator: "allocator" $@21 ":" "constant string"
#line 687 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 160: // echo_client_id: "echo-client-id" ":" "boolean"
#line 693 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 161: // match_client_id: "match-client-id" ":" "boolean"
#line 699 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 162: // authoritative: "authoritative" ":" "boolean"
#line 705 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 163: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 711 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 164: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 717 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 165: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 723 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 166: // $@22: %empty
#line 729 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 732 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-present"
#line 738 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1402 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "never"
#line 741 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1410 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "always"
#line 744 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1418 "dhcp4_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "when-not-present"
#line 747 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1426 "dhcp4_parser.cc"
    break;

  case 172: // ddns_replace_client_name_value: "boolean"
#line 750 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1435 "dhcp4_parser.cc"
    break;

  case 173: // $@23: %empty
#line 756 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 174: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 759 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc"
    break;

  case 175: // $@24: %empty
#line 765 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 176: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 768 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 177: // $@25: %empty
#line 774 "dhcp4_parser.yy"
                                     {
    ctx.unique("ddns-reverse-zone", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc"
    break;

  case 178: // ddns_reverse_zone: "ddns-reverse-zone" $@25 ":" "constant string"
#line 777 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-reverse-zone", s);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc"
    break;

  case 179: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 783 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1502 "dhcp4_parser.cc"
    break;

  case 180: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 792 "dhcp4_parser.yy"
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
#line 802 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@26 ":" ddns_conflict_resolution_mode_value
#line 805 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 811 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1542 "dhcp4_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 814 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1550 "dhcp4_parser.cc"
    break;

  case 185: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 817 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1558 "dhcp4_parser.cc"
    break;

  case 186: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 820 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1566 "dhcp4_parser.cc"
    break;

  case 187: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 825 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 188: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 831 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 189: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 837 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 190: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 843 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 191: // $@27: %empty
#line 849 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 192: // hostname_char_set: "hostname-char-set" $@27 ":" "constant string"
#line 852 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 858 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 194: // hostname_char_replacement: "hostname-char-replacement" $@28 ":" "constant string"
#line 861 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 195: // store_extended_info: "store-extended-info" ":" "boolean"
#line 867 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 196: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 873 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 197: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 879 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1674 "dhcp4_parser.cc"
    break;

  case 198: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 885 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 199: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 891 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 200: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 897 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1704 "dhcp4_parser.cc"
    break;

  case 201: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 903 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 202: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 909 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 203: // $@29: %empty
#line 915 "dhcp4_parser.yy"
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
#line 921 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc"
    break;

  case 207: // interfaces_config_params: interfaces_config_params ","
#line 929 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1754 "dhcp4_parser.cc"
    break;

  case 219: // $@30: %empty
#line 947 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1764 "dhcp4_parser.cc"
    break;

  case 220: // sub_interfaces4: "{" $@30 interfaces_config_params "}"
#line 951 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 221: // $@31: %empty
#line 956 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1785 "dhcp4_parser.cc"
    break;

  case 222: // interfaces_list: "interfaces" $@31 ":" list_strings
#line 962 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc"
    break;

  case 223: // $@32: %empty
#line 967 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1803 "dhcp4_parser.cc"
    break;

  case 224: // dhcp_socket_type: "dhcp-socket-type" $@32 ":" socket_type
#line 970 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 225: // socket_type: "raw"
#line 975 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1818 "dhcp4_parser.cc"
    break;

  case 226: // socket_type: "udp"
#line 976 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1824 "dhcp4_parser.cc"
    break;

  case 227: // use_fallbacks: "use-fallbacks" ":" "boolean"
#line 979 "dhcp4_parser.yy"
                                           {
    ctx.unique("use-fallbacks", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("use-fallbacks", b);
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 228: // $@33: %empty
#line 985 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1843 "dhcp4_parser.cc"
    break;

  case 229: // outbound_interface: "outbound-interface" $@33 ":" outbound_interface_value
#line 988 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 230: // outbound_interface_value: "same-as-inbound"
#line 993 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 231: // outbound_interface_value: "use-routing"
#line 995 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1868 "dhcp4_parser.cc"
    break;

  case 232: // re_detect: "re-detect" ":" "boolean"
#line 999 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 233: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 1005 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 234: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 1011 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1898 "dhcp4_parser.cc"
    break;

  case 235: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1017 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 236: // $@34: %empty
#line 1023 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1920 "dhcp4_parser.cc"
    break;

  case 237: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 1029 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1931 "dhcp4_parser.cc"
    break;

  case 238: // $@35: %empty
#line 1036 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1943 "dhcp4_parser.cc"
    break;

  case 239: // sanity_checks: "sanity-checks" $@35 ":" "{" sanity_checks_params "}"
#line 1042 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1952 "dhcp4_parser.cc"
    break;

  case 242: // sanity_checks_params: sanity_checks_params ","
#line 1049 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1960 "dhcp4_parser.cc"
    break;

  case 245: // $@36: %empty
#line 1058 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp4_parser.cc"
    break;

  case 246: // lease_checks: "lease-checks" $@36 ":" "constant string"
#line 1061 "dhcp4_parser.yy"
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
#line 1989 "dhcp4_parser.cc"
    break;

  case 247: // $@37: %empty
#line 1077 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 248: // extended_info_checks: "extended-info-checks" $@37 ":" "constant string"
#line 1080 "dhcp4_parser.yy"
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
#line 2017 "dhcp4_parser.cc"
    break;

  case 249: // $@38: %empty
#line 1095 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 250: // hosts_database: "hosts-database" $@38 ":" "{" database_map_params "}"
#line 1101 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 251: // $@39: %empty
#line 1108 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2052 "dhcp4_parser.cc"
    break;

  case 252: // hosts_databases: "hosts-databases" $@39 ":" "[" database_list "]"
#line 1114 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2061 "dhcp4_parser.cc"
    break;

  case 257: // not_empty_database_list: not_empty_database_list ","
#line 1125 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2069 "dhcp4_parser.cc"
    break;

  case 258: // $@40: %empty
#line 1130 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 259: // database: "{" $@40 database_map_params "}"
#line 1134 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 262: // database_map_params: database_map_params ","
#line 1142 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2097 "dhcp4_parser.cc"
    break;

  case 288: // $@41: %empty
#line 1174 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 289: // database_type: "type" $@41 ":" "constant string"
#line 1177 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2116 "dhcp4_parser.cc"
    break;

  case 290: // $@42: %empty
#line 1183 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 291: // user: "user" $@42 ":" "constant string"
#line 1186 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2135 "dhcp4_parser.cc"
    break;

  case 292: // $@43: %empty
#line 1192 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 293: // password: "password" $@43 ":" "constant string"
#line 1195 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 294: // $@44: %empty
#line 1201 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 295: // password_file: "password-file" $@44 ":" "constant string"
#line 1204 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 296: // $@45: %empty
#line 1210 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 297: // host: "host" $@45 ":" "constant string"
#line 1213 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 298: // port: "port" ":" "integer"
#line 1219 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 299: // $@46: %empty
#line 1225 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc"
    break;

  case 300: // name: "name" $@46 ":" "constant string"
#line 1228 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 301: // persist: "persist" ":" "boolean"
#line 1234 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2231 "dhcp4_parser.cc"
    break;

  case 302: // lfc_interval: "lfc-interval" ":" "integer"
#line 1240 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2241 "dhcp4_parser.cc"
    break;

  case 303: // readonly: "readonly" ":" "boolean"
#line 1246 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 304: // connect_timeout: "connect-timeout" ":" "integer"
#line 1252 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 305: // read_timeout: "read-timeout" ":" "integer"
#line 1258 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 306: // write_timeout: "write-timeout" ":" "integer"
#line 1264 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 307: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1270 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 308: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1276 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 309: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1282 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2311 "dhcp4_parser.cc"
    break;

  case 310: // $@47: %empty
#line 1288 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 311: // on_fail: "on-fail" $@47 ":" on_fail_mode
#line 1291 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2329 "dhcp4_parser.cc"
    break;

  case 312: // on_fail_mode: "stop-retry-exit"
#line 1296 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2335 "dhcp4_parser.cc"
    break;

  case 313: // on_fail_mode: "serve-retry-exit"
#line 1297 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2341 "dhcp4_parser.cc"
    break;

  case 314: // on_fail_mode: "serve-retry-continue"
#line 1298 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2347 "dhcp4_parser.cc"
    break;

  case 315: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1301 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 316: // max_row_errors: "max-row-errors" ":" "integer"
#line 1307 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2367 "dhcp4_parser.cc"
    break;

  case 317: // $@48: %empty
#line 1313 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 318: // trust_anchor: "trust-anchor" $@48 ":" "constant string"
#line 1316 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 319: // $@49: %empty
#line 1322 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 320: // cert_file: "cert-file" $@49 ":" "constant string"
#line 1325 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc"
    break;

  case 321: // $@50: %empty
#line 1331 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp4_parser.cc"
    break;

  case 322: // key_file: "key-file" $@50 ":" "constant string"
#line 1334 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc"
    break;

  case 323: // $@51: %empty
#line 1340 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2433 "dhcp4_parser.cc"
    break;

  case 324: // ssl_mode: "ssl-mode" $@51 ":" ssl_mode
#line 1343 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 325: // ssl_mode: "disable"
#line 1348 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2450 "dhcp4_parser.cc"
    break;

  case 326: // ssl_mode: "prefer"
#line 1351 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2458 "dhcp4_parser.cc"
    break;

  case 327: // ssl_mode: "require"
#line 1354 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2466 "dhcp4_parser.cc"
    break;

  case 328: // ssl_mode: "verify-ca"
#line 1357 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2474 "dhcp4_parser.cc"
    break;

  case 329: // ssl_mode: "verify-full"
#line 1360 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2482 "dhcp4_parser.cc"
    break;

  case 330: // $@52: %empty
#line 1365 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 331: // cipher_list: "cipher-list" $@52 ":" "constant string"
#line 1368 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 332: // $@53: %empty
#line 1374 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2513 "dhcp4_parser.cc"
    break;

  case 333: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1380 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2522 "dhcp4_parser.cc"
    break;

  case 336: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1387 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2530 "dhcp4_parser.cc"
    break;

  case 342: // duid_id: "duid"
#line 1399 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 343: // hw_address_id: "hw-address"
#line 1404 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 344: // circuit_id: "circuit-id"
#line 1409 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2557 "dhcp4_parser.cc"
    break;

  case 345: // client_id: "client-id"
#line 1414 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2566 "dhcp4_parser.cc"
    break;

  case 346: // flex_id: "flex-id"
#line 1419 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 347: // $@54: %empty
#line 1426 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 348: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1432 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2598 "dhcp4_parser.cc"
    break;

  case 351: // multi_threading_params: multi_threading_params ","
#line 1441 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2606 "dhcp4_parser.cc"
    break;

  case 358: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1454 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 359: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1460 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 360: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1466 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2636 "dhcp4_parser.cc"
    break;

  case 361: // $@55: %empty
#line 1472 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2648 "dhcp4_parser.cc"
    break;

  case 362: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1478 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2657 "dhcp4_parser.cc"
    break;

  case 367: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1489 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2665 "dhcp4_parser.cc"
    break;

  case 368: // $@56: %empty
#line 1494 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 369: // hooks_library: "{" $@56 hooks_params "}"
#line 1498 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 370: // $@57: %empty
#line 1504 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 371: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1508 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2705 "dhcp4_parser.cc"
    break;

  case 374: // hooks_params: hooks_params ","
#line 1516 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2713 "dhcp4_parser.cc"
    break;

  case 378: // $@58: %empty
#line 1526 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 379: // library: "library" $@58 ":" "constant string"
#line 1529 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 380: // $@59: %empty
#line 1535 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 381: // parameters: "parameters" $@59 ":" map_value
#line 1538 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 382: // $@60: %empty
#line 1544 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 383: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1550 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 386: // expired_leases_params: expired_leases_params ","
#line 1558 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2780 "dhcp4_parser.cc"
    break;

  case 393: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1571 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2790 "dhcp4_parser.cc"
    break;

  case 394: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1577 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2800 "dhcp4_parser.cc"
    break;

  case 395: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1583 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 396: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1589 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 397: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1595 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 398: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1601 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 399: // $@61: %empty
#line 1610 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 400: // subnet4_list: "subnet4" $@61 ":" "[" subnet4_list_content "]"
#line 1616 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 405: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1630 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2869 "dhcp4_parser.cc"
    break;

  case 406: // $@62: %empty
#line 1639 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2879 "dhcp4_parser.cc"
    break;

  case 407: // subnet4: "{" $@62 subnet4_params "}"
#line 1643 "dhcp4_parser.yy"
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
#line 2905 "dhcp4_parser.cc"
    break;

  case 408: // $@63: %empty
#line 1665 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2915 "dhcp4_parser.cc"
    break;

  case 409: // sub_subnet4: "{" $@63 subnet4_params "}"
#line 1669 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2925 "dhcp4_parser.cc"
    break;

  case 412: // subnet4_params: subnet4_params ","
#line 1678 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2933 "dhcp4_parser.cc"
    break;

  case 466: // $@64: %empty
#line 1739 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 467: // subnet: "subnet" $@64 ":" "constant string"
#line 1742 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 468: // $@65: %empty
#line 1748 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 469: // subnet_4o6_interface: "4o6-interface" $@65 ":" "constant string"
#line 1751 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2971 "dhcp4_parser.cc"
    break;

  case 470: // $@66: %empty
#line 1757 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 471: // subnet_4o6_interface_id: "4o6-interface-id" $@66 ":" "constant string"
#line 1760 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 472: // $@67: %empty
#line 1766 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 473: // subnet_4o6_subnet: "4o6-subnet" $@67 ":" "constant string"
#line 1769 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 3009 "dhcp4_parser.cc"
    break;

  case 474: // $@68: %empty
#line 1775 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 475: // interface: "interface" $@68 ":" "constant string"
#line 1778 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 3028 "dhcp4_parser.cc"
    break;

  case 476: // $@69: %empty
#line 1785 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3040 "dhcp4_parser.cc"
    break;

  case 477: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1791 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3049 "dhcp4_parser.cc"
    break;

  case 478: // $@70: %empty
#line 1796 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 479: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1802 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 480: // reservations_global: "reservations-global" ":" "boolean"
#line 1807 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 481: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1813 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 482: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1819 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3100 "dhcp4_parser.cc"
    break;

  case 483: // id: "id" ":" "integer"
#line 1825 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 484: // $@71: %empty
#line 1833 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3122 "dhcp4_parser.cc"
    break;

  case 485: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1839 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3131 "dhcp4_parser.cc"
    break;

  case 490: // shared_networks_list: shared_networks_list ","
#line 1852 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3139 "dhcp4_parser.cc"
    break;

  case 491: // $@72: %empty
#line 1857 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 492: // shared_network: "{" $@72 shared_network_params "}"
#line 1861 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3157 "dhcp4_parser.cc"
    break;

  case 495: // shared_network_params: shared_network_params ","
#line 1867 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3165 "dhcp4_parser.cc"
    break;

  case 544: // $@73: %empty
#line 1926 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 545: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1932 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 546: // $@74: %empty
#line 1940 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3195 "dhcp4_parser.cc"
    break;

  case 547: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1943 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3203 "dhcp4_parser.cc"
    break;

  case 552: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1955 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3211 "dhcp4_parser.cc"
    break;

  case 553: // $@75: %empty
#line 1962 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3221 "dhcp4_parser.cc"
    break;

  case 554: // option_def_entry: "{" $@75 option_def_params "}"
#line 1966 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 555: // $@76: %empty
#line 1977 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 556: // sub_option_def: "{" $@76 option_def_params "}"
#line 1981 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3255 "dhcp4_parser.cc"
    break;

  case 561: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1997 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3263 "dhcp4_parser.cc"
    break;

  case 573: // code: "code" ":" "integer"
#line 2016 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 575: // $@77: %empty
#line 2024 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 576: // option_def_type: "type" $@77 ":" "constant string"
#line 2027 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3292 "dhcp4_parser.cc"
    break;

  case 577: // $@78: %empty
#line 2033 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 578: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 2036 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 579: // $@79: %empty
#line 2042 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 580: // space: "space" $@79 ":" "constant string"
#line 2045 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 582: // $@80: %empty
#line 2053 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3339 "dhcp4_parser.cc"
    break;

  case 583: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2056 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3349 "dhcp4_parser.cc"
    break;

  case 584: // option_def_array: "array" ":" "boolean"
#line 2062 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 585: // $@81: %empty
#line 2072 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3371 "dhcp4_parser.cc"
    break;

  case 586: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2078 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3380 "dhcp4_parser.cc"
    break;

  case 591: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2093 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3388 "dhcp4_parser.cc"
    break;

  case 592: // $@82: %empty
#line 2100 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3398 "dhcp4_parser.cc"
    break;

  case 593: // option_data_entry: "{" $@82 option_data_params "}"
#line 2104 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3407 "dhcp4_parser.cc"
    break;

  case 594: // $@83: %empty
#line 2112 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3417 "dhcp4_parser.cc"
    break;

  case 595: // sub_option_data: "{" $@83 option_data_params "}"
#line 2116 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 600: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2132 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3434 "dhcp4_parser.cc"
    break;

  case 613: // $@84: %empty
#line 2154 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 614: // option_data_data: "data" $@84 ":" "constant string"
#line 2157 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 617: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2167 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 618: // option_data_always_send: "always-send" ":" "boolean"
#line 2173 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 619: // option_data_never_send: "never-send" ":" "boolean"
#line 2179 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 620: // $@85: %empty
#line 2185 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 621: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2191 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 622: // $@86: %empty
#line 2199 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3516 "dhcp4_parser.cc"
    break;

  case 623: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2205 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 628: // not_empty_pools_list: not_empty_pools_list ","
#line 2218 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3533 "dhcp4_parser.cc"
    break;

  case 629: // $@87: %empty
#line 2223 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3543 "dhcp4_parser.cc"
    break;

  case 630: // pool_list_entry: "{" $@87 pool_params "}"
#line 2227 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3553 "dhcp4_parser.cc"
    break;

  case 631: // $@88: %empty
#line 2233 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 632: // sub_pool4: "{" $@88 pool_params "}"
#line 2237 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 635: // pool_params: pool_params ","
#line 2245 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3581 "dhcp4_parser.cc"
    break;

  case 659: // $@89: %empty
#line 2275 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3590 "dhcp4_parser.cc"
    break;

  case 660: // pool_entry: "pool" $@89 ":" "constant string"
#line 2278 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3600 "dhcp4_parser.cc"
    break;

  case 661: // pool_id: "pool-id" ":" "integer"
#line 2284 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3610 "dhcp4_parser.cc"
    break;

  case 662: // $@90: %empty
#line 2290 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3618 "dhcp4_parser.cc"
    break;

  case 663: // user_context: "user-context" $@90 ":" map_value
#line 2292 "dhcp4_parser.yy"
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
#line 3645 "dhcp4_parser.cc"
    break;

  case 664: // $@91: %empty
#line 2315 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 665: // comment: "comment" $@91 ":" "constant string"
#line 2317 "dhcp4_parser.yy"
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
#line 3682 "dhcp4_parser.cc"
    break;

  case 666: // $@92: %empty
#line 2345 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3694 "dhcp4_parser.cc"
    break;

  case 667: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2351 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 672: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2362 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3711 "dhcp4_parser.cc"
    break;

  case 673: // $@93: %empty
#line 2367 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 674: // reservation: "{" $@93 reservation_params "}"
#line 2371 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3730 "dhcp4_parser.cc"
    break;

  case 675: // $@94: %empty
#line 2376 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3740 "dhcp4_parser.cc"
    break;

  case 676: // sub_reservation: "{" $@94 reservation_params "}"
#line 2380 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 681: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2391 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3757 "dhcp4_parser.cc"
    break;

  case 697: // $@95: %empty
#line 2414 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp4_parser.cc"
    break;

  case 698: // next_server: "next-server" $@95 ":" "constant string"
#line 2417 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 699: // $@96: %empty
#line 2423 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3785 "dhcp4_parser.cc"
    break;

  case 700: // server_hostname: "server-hostname" $@96 ":" "constant string"
#line 2426 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3795 "dhcp4_parser.cc"
    break;

  case 701: // $@97: %empty
#line 2432 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3804 "dhcp4_parser.cc"
    break;

  case 702: // boot_file_name: "boot-file-name" $@97 ":" "constant string"
#line 2435 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3814 "dhcp4_parser.cc"
    break;

  case 703: // $@98: %empty
#line 2441 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3823 "dhcp4_parser.cc"
    break;

  case 704: // ip_address: "ip-address" $@98 ":" "constant string"
#line 2444 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3833 "dhcp4_parser.cc"
    break;

  case 705: // $@99: %empty
#line 2450 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 706: // duid: "duid" $@99 ":" "constant string"
#line 2453 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3852 "dhcp4_parser.cc"
    break;

  case 707: // $@100: %empty
#line 2459 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3861 "dhcp4_parser.cc"
    break;

  case 708: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2462 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3871 "dhcp4_parser.cc"
    break;

  case 709: // $@101: %empty
#line 2468 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3880 "dhcp4_parser.cc"
    break;

  case 710: // client_id_value: "client-id" $@101 ":" "constant string"
#line 2471 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3890 "dhcp4_parser.cc"
    break;

  case 711: // $@102: %empty
#line 2477 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3899 "dhcp4_parser.cc"
    break;

  case 712: // circuit_id_value: "circuit-id" $@102 ":" "constant string"
#line 2480 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3909 "dhcp4_parser.cc"
    break;

  case 713: // $@103: %empty
#line 2486 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 714: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2489 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 715: // $@104: %empty
#line 2495 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3937 "dhcp4_parser.cc"
    break;

  case 716: // hostname: "hostname" $@104 ":" "constant string"
#line 2498 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3947 "dhcp4_parser.cc"
    break;

  case 717: // $@105: %empty
#line 2504 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3959 "dhcp4_parser.cc"
    break;

  case 718: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2510 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3968 "dhcp4_parser.cc"
    break;

  case 719: // $@106: %empty
#line 2518 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3980 "dhcp4_parser.cc"
    break;

  case 720: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2524 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 722: // $@107: %empty
#line 2532 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4001 "dhcp4_parser.cc"
    break;

  case 723: // ip_addresses: "ip-addresses" $@107 ":" list_strings
#line 2538 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4010 "dhcp4_parser.cc"
    break;

  case 724: // $@108: %empty
#line 2546 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4022 "dhcp4_parser.cc"
    break;

  case 725: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2552 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 730: // not_empty_classes_list: not_empty_classes_list ","
#line 2563 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4039 "dhcp4_parser.cc"
    break;

  case 731: // $@109: %empty
#line 2568 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4049 "dhcp4_parser.cc"
    break;

  case 732: // client_class_entry: "{" $@109 client_class_params "}"
#line 2572 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4059 "dhcp4_parser.cc"
    break;

  case 737: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2584 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4067 "dhcp4_parser.cc"
    break;

  case 755: // $@110: %empty
#line 2609 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4076 "dhcp4_parser.cc"
    break;

  case 756: // client_class_test: "test" $@110 ":" "constant string"
#line 2612 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4086 "dhcp4_parser.cc"
    break;

  case 757: // $@111: %empty
#line 2618 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4095 "dhcp4_parser.cc"
    break;

  case 758: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2621 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 759: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2627 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4115 "dhcp4_parser.cc"
    break;

  case 760: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2635 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4125 "dhcp4_parser.cc"
    break;

  case 761: // $@112: %empty
#line 2643 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4137 "dhcp4_parser.cc"
    break;

  case 762: // control_sockets: "control-sockets" $@112 ":" "[" control_socket_list "]"
#line 2649 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4146 "dhcp4_parser.cc"
    break;

  case 767: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2660 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4154 "dhcp4_parser.cc"
    break;

  case 768: // $@113: %empty
#line 2665 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4164 "dhcp4_parser.cc"
    break;

  case 769: // control_socket_entry: "{" $@113 control_socket_params "}"
#line 2669 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4172 "dhcp4_parser.cc"
    break;

  case 772: // control_socket_params: control_socket_params ","
#line 2675 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4180 "dhcp4_parser.cc"
    break;

  case 786: // $@114: %empty
#line 2695 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4189 "dhcp4_parser.cc"
    break;

  case 787: // control_socket_type: "socket-type" $@114 ":" control_socket_type_value
#line 2698 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4198 "dhcp4_parser.cc"
    break;

  case 788: // control_socket_type_value: "unix"
#line 2704 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4204 "dhcp4_parser.cc"
    break;

  case 789: // control_socket_type_value: "http"
#line 2705 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4210 "dhcp4_parser.cc"
    break;

  case 790: // control_socket_type_value: "https"
#line 2706 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4216 "dhcp4_parser.cc"
    break;

  case 791: // $@115: %empty
#line 2709 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4225 "dhcp4_parser.cc"
    break;

  case 792: // control_socket_name: "socket-name" $@115 ":" "constant string"
#line 2712 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4235 "dhcp4_parser.cc"
    break;

  case 793: // $@116: %empty
#line 2718 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4244 "dhcp4_parser.cc"
    break;

  case 794: // control_socket_address: "socket-address" $@116 ":" "constant string"
#line 2721 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4254 "dhcp4_parser.cc"
    break;

  case 795: // control_socket_port: "socket-port" ":" "integer"
#line 2727 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4264 "dhcp4_parser.cc"
    break;

  case 796: // cert_required: "cert-required" ":" "boolean"
#line 2733 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4274 "dhcp4_parser.cc"
    break;

  case 797: // $@117: %empty
#line 2739 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4286 "dhcp4_parser.cc"
    break;

  case 798: // http_headers: "http-headers" $@117 ":" "[" http_header_list "]"
#line 2745 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4295 "dhcp4_parser.cc"
    break;

  case 803: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2756 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4303 "dhcp4_parser.cc"
    break;

  case 804: // $@118: %empty
#line 2761 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4313 "dhcp4_parser.cc"
    break;

  case 805: // http_header: "{" $@118 http_header_params "}"
#line 2765 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4321 "dhcp4_parser.cc"
    break;

  case 808: // http_header_params: http_header_params ","
#line 2771 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4329 "dhcp4_parser.cc"
    break;

  case 814: // $@119: %empty
#line 2783 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 815: // header_value: "value" $@119 ":" "constant string"
#line 2786 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4348 "dhcp4_parser.cc"
    break;

  case 816: // $@120: %empty
#line 2794 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4360 "dhcp4_parser.cc"
    break;

  case 817: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2800 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4371 "dhcp4_parser.cc"
    break;

  case 820: // auth_params: auth_params ","
#line 2809 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4379 "dhcp4_parser.cc"
    break;

  case 828: // $@121: %empty
#line 2823 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4388 "dhcp4_parser.cc"
    break;

  case 829: // auth_type: "type" $@121 ":" auth_type_value
#line 2826 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4397 "dhcp4_parser.cc"
    break;

  case 830: // auth_type_value: "basic"
#line 2831 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4403 "dhcp4_parser.cc"
    break;

  case 831: // $@122: %empty
#line 2834 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4412 "dhcp4_parser.cc"
    break;

  case 832: // realm: "realm" $@122 ":" "constant string"
#line 2837 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 833: // $@123: %empty
#line 2843 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4431 "dhcp4_parser.cc"
    break;

  case 834: // directory: "directory" $@123 ":" "constant string"
#line 2846 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4441 "dhcp4_parser.cc"
    break;

  case 835: // $@124: %empty
#line 2852 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 836: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2858 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4462 "dhcp4_parser.cc"
    break;

  case 841: // not_empty_clients_list: not_empty_clients_list ","
#line 2869 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4470 "dhcp4_parser.cc"
    break;

  case 842: // $@125: %empty
#line 2874 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4480 "dhcp4_parser.cc"
    break;

  case 843: // basic_auth: "{" $@125 clients_params "}"
#line 2878 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4488 "dhcp4_parser.cc"
    break;

  case 846: // clients_params: clients_params ","
#line 2884 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4496 "dhcp4_parser.cc"
    break;

  case 854: // $@126: %empty
#line 2898 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 855: // user_file: "user-file" $@126 ":" "constant string"
#line 2901 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4515 "dhcp4_parser.cc"
    break;

  case 856: // $@127: %empty
#line 2909 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4527 "dhcp4_parser.cc"
    break;

  case 857: // dhcp_queue_control: "dhcp-queue-control" $@127 ":" "{" queue_control_params "}"
#line 2915 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4538 "dhcp4_parser.cc"
    break;

  case 860: // queue_control_params: queue_control_params ","
#line 2924 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4546 "dhcp4_parser.cc"
    break;

  case 867: // enable_queue: "enable-queue" ":" "boolean"
#line 2937 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4556 "dhcp4_parser.cc"
    break;

  case 868: // $@128: %empty
#line 2943 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4565 "dhcp4_parser.cc"
    break;

  case 869: // queue_type: "queue-type" $@128 ":" "constant string"
#line 2946 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4575 "dhcp4_parser.cc"
    break;

  case 870: // capacity: "capacity" ":" "integer"
#line 2952 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4585 "dhcp4_parser.cc"
    break;

  case 871: // $@129: %empty
#line 2958 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4594 "dhcp4_parser.cc"
    break;

  case 872: // arbitrary_map_entry: "constant string" $@129 ":" value
#line 2961 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4603 "dhcp4_parser.cc"
    break;

  case 873: // $@130: %empty
#line 2968 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4615 "dhcp4_parser.cc"
    break;

  case 874: // dhcp_ddns: "dhcp-ddns" $@130 ":" "{" dhcp_ddns_params "}"
#line 2974 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4626 "dhcp4_parser.cc"
    break;

  case 875: // $@131: %empty
#line 2981 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4636 "dhcp4_parser.cc"
    break;

  case 876: // sub_dhcp_ddns: "{" $@131 dhcp_ddns_params "}"
#line 2985 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4646 "dhcp4_parser.cc"
    break;

  case 879: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2993 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4654 "dhcp4_parser.cc"
    break;

  case 891: // enable_updates: "enable-updates" ":" "boolean"
#line 3011 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4664 "dhcp4_parser.cc"
    break;

  case 892: // $@132: %empty
#line 3017 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4673 "dhcp4_parser.cc"
    break;

  case 893: // server_ip: "server-ip" $@132 ":" "constant string"
#line 3020 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4683 "dhcp4_parser.cc"
    break;

  case 894: // server_port: "server-port" ":" "integer"
#line 3026 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4693 "dhcp4_parser.cc"
    break;

  case 895: // $@133: %empty
#line 3032 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4702 "dhcp4_parser.cc"
    break;

  case 896: // sender_ip: "sender-ip" $@133 ":" "constant string"
#line 3035 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4712 "dhcp4_parser.cc"
    break;

  case 897: // sender_port: "sender-port" ":" "integer"
#line 3041 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4722 "dhcp4_parser.cc"
    break;

  case 898: // max_queue_size: "max-queue-size" ":" "integer"
#line 3047 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4732 "dhcp4_parser.cc"
    break;

  case 899: // $@134: %empty
#line 3053 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4741 "dhcp4_parser.cc"
    break;

  case 900: // ncr_protocol: "ncr-protocol" $@134 ":" ncr_protocol_value
#line 3056 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4750 "dhcp4_parser.cc"
    break;

  case 901: // ncr_protocol_value: "udp"
#line 3062 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4756 "dhcp4_parser.cc"
    break;

  case 902: // ncr_protocol_value: "tcp"
#line 3063 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4762 "dhcp4_parser.cc"
    break;

  case 903: // $@135: %empty
#line 3066 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4771 "dhcp4_parser.cc"
    break;

  case 904: // ncr_format: "ncr-format" $@135 ":" "JSON"
#line 3069 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4781 "dhcp4_parser.cc"
    break;

  case 905: // $@136: %empty
#line 3077 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4793 "dhcp4_parser.cc"
    break;

  case 906: // config_control: "config-control" $@136 ":" "{" config_control_params "}"
#line 3083 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4803 "dhcp4_parser.cc"
    break;

  case 907: // $@137: %empty
#line 3089 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4813 "dhcp4_parser.cc"
    break;

  case 908: // sub_config_control: "{" $@137 config_control_params "}"
#line 3093 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4822 "dhcp4_parser.cc"
    break;

  case 911: // config_control_params: config_control_params ","
#line 3101 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4830 "dhcp4_parser.cc"
    break;

  case 914: // $@138: %empty
#line 3111 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4842 "dhcp4_parser.cc"
    break;

  case 915: // config_databases: "config-databases" $@138 ":" "[" database_list "]"
#line 3117 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4851 "dhcp4_parser.cc"
    break;

  case 916: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3122 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4861 "dhcp4_parser.cc"
    break;

  case 917: // $@139: %empty
#line 3130 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4873 "dhcp4_parser.cc"
    break;

  case 918: // loggers: "loggers" $@139 ":" "[" loggers_entries "]"
#line 3136 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4882 "dhcp4_parser.cc"
    break;

  case 921: // loggers_entries: loggers_entries ","
#line 3145 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4890 "dhcp4_parser.cc"
    break;

  case 922: // $@140: %empty
#line 3151 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4900 "dhcp4_parser.cc"
    break;

  case 923: // logger_entry: "{" $@140 logger_params "}"
#line 3155 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4908 "dhcp4_parser.cc"
    break;

  case 926: // logger_params: logger_params ","
#line 3161 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4916 "dhcp4_parser.cc"
    break;

  case 934: // debuglevel: "debuglevel" ":" "integer"
#line 3175 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4926 "dhcp4_parser.cc"
    break;

  case 935: // $@141: %empty
#line 3181 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4935 "dhcp4_parser.cc"
    break;

  case 936: // severity: "severity" $@141 ":" "constant string"
#line 3184 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4945 "dhcp4_parser.cc"
    break;

  case 937: // $@142: %empty
#line 3190 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4957 "dhcp4_parser.cc"
    break;

  case 938: // output_options_list: "output-options" $@142 ":" "[" output_options_list_content "]"
#line 3196 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4966 "dhcp4_parser.cc"
    break;

  case 941: // output_options_list_content: output_options_list_content ","
#line 3203 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4974 "dhcp4_parser.cc"
    break;

  case 942: // $@143: %empty
#line 3208 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4984 "dhcp4_parser.cc"
    break;

  case 943: // output_entry: "{" $@143 output_params_list "}"
#line 3212 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4992 "dhcp4_parser.cc"
    break;

  case 946: // output_params_list: output_params_list ","
#line 3218 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5000 "dhcp4_parser.cc"
    break;

  case 952: // $@144: %empty
#line 3230 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5009 "dhcp4_parser.cc"
    break;

  case 953: // output: "output" $@144 ":" "constant string"
#line 3233 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5019 "dhcp4_parser.cc"
    break;

  case 954: // flush: "flush" ":" "boolean"
#line 3239 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5029 "dhcp4_parser.cc"
    break;

  case 955: // maxsize: "maxsize" ":" "integer"
#line 3245 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5039 "dhcp4_parser.cc"
    break;

  case 956: // maxver: "maxver" ":" "integer"
#line 3251 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5049 "dhcp4_parser.cc"
    break;

  case 957: // $@145: %empty
#line 3257 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5058 "dhcp4_parser.cc"
    break;

  case 958: // pattern: "pattern" $@145 ":" "constant string"
#line 3260 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5068 "dhcp4_parser.cc"
    break;

  case 959: // $@146: %empty
#line 3266 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5080 "dhcp4_parser.cc"
    break;

  case 960: // compatibility: "compatibility" $@146 ":" "{" compatibility_params "}"
#line 3272 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5089 "dhcp4_parser.cc"
    break;

  case 963: // compatibility_params: compatibility_params ","
#line 3279 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5097 "dhcp4_parser.cc"
    break;

  case 969: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3291 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5107 "dhcp4_parser.cc"
    break;

  case 970: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3297 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5117 "dhcp4_parser.cc"
    break;

  case 971: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3303 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5127 "dhcp4_parser.cc"
    break;

  case 972: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3309 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5137 "dhcp4_parser.cc"
    break;


#line 5141 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1415;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     526, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,    49,    39,    52,    64,    67,    79,
      81,   117,   179,   191,   199,   255,   283,   290, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,    39,  -190,    43,   268,    77,   697,
    1452,   189,    -9,   134,   353,   -72,   510,    99, -1415,   172,
      74,    87,   309,   316, -1415,    58, -1415, -1415, -1415, -1415,
     319,   326,   334, -1415, -1415, -1415,   376,   386, -1415, -1415,
   -1415,   404,   412,   413,   416,   417,   419,   427,   428,   431,
     432,   437,   438, -1415,   439,   440,   441,   442,   445, -1415,
   -1415, -1415, -1415,   446,   447,   449,   450,   451,   453,   454,
   -1415, -1415, -1415,   462, -1415, -1415, -1415, -1415, -1415,   463,
     465,   466, -1415, -1415, -1415, -1415, -1415,   473, -1415, -1415,
   -1415, -1415, -1415, -1415,   477,   478,   479, -1415, -1415,   480,
   -1415,    76, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   483, -1415,   485,
     487,   488,   489, -1415,    82, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,   491, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,    96,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,   492, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,   119, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     490,   494, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   500, -1415, -1415,   495, -1415, -1415,
   -1415,   496, -1415, -1415,   502,   508, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   509,
     513,   514, -1415, -1415, -1415, -1415, -1415,   506,   518, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415,   120, -1415, -1415, -1415,   519, -1415,   520,
   -1415,   521,   523, -1415, -1415, -1415, -1415, -1415,   131, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   529,
     141, -1415, -1415, -1415, -1415,    39,    39, -1415,   295,   532,
   -1415, -1415,   533,   538,   541,   311,   312,   314,   543,   549,
     550,   320,   322,   553,   554,   558,   329,   332,   333,   335,
     336,   339,   330,   337,   341,   344,   347,   345,   566,   350,
     351,   355,   356,   359,   569,   581,   596,   602,   370,   372,
     374,   383,   385,   390,   393,   608,   610,   612,   397,   634,
     637,   639,   644,   648,   415,   418,   421,   650,   657,   658,
     659,   660,   430,   663,   665,   667,   668,   669,   670,   443,
     448,   455,   672,   673, -1415,   268, -1415,   674,   675,   456,
     679,   458,   459,   452,   471,    77, -1415,   680,   685,   687,
     688,   694,   705,   474,   707,   708,   709,   697, -1415,   710,
     481,  1452, -1415,   711,   712,   715,   716,   718,   719,   720,
     722, -1415,   189, -1415,   723,   730,   499,   732,   733,   734,
     501, -1415,   134,   736,   503,   504,   524,   757, -1415,   353,
     759,   760,   230, -1415,   527,   762,   531,   776,   561,   565,
     799,   800,   510, -1415,   801,   570,    99, -1415, -1415, -1415,
     803,   802,   804,   805,   806, -1415, -1415, -1415,   573,   575,
     582, -1415, -1415,   809,   811,   814, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   585, -1415,
   -1415, -1415, -1415, -1415,    -7,   587,   599,   600, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   826,   831,   832, -1415,   604,
     306,   835,   834,   607, -1415, -1415, -1415,   838,   839,   840,
     842,   841, -1415,   843,   844,   859,   860,   633,   646, -1415,
   -1415, -1415,   877,   876, -1415,   879,   220, -1415,   349, -1415,
   -1415, -1415, -1415, -1415,   651,   652,   653,   880,   654,   655,
   -1415,   879,   879,   884, -1415,   661, -1415, -1415,   879,   662,
     664,   671,   676,   677,   678,   682, -1415,   683,   684, -1415,
     686,   689,   690, -1415, -1415,   691, -1415, -1415, -1415,   879,
   -1415,   692,   834, -1415, -1415,   693, -1415,   695, -1415, -1415,
      16,   696, -1415,   887, -1415, -1415,    39,   268,    99,    77,
     378, -1415, -1415, -1415,   810,   810,   886, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   888,   891,   895,
   -1415, -1415, -1415, -1415, -1415, -1415,   896, -1415, -1415, -1415,
      84,   897,   898,   900,   219,   -44,   901,   -21,   510, -1415,
   -1415,   902,   -10, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   903, -1415, -1415, -1415, -1415,   764,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   886, -1415,   142,   143,   153, -1415,
   -1415,   165, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   911,
     916,   918,   919,   925,   927,   929,   930,   931,   932, -1415,
     933,   934, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   168, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     171, -1415,   935,   936, -1415, -1415,   937,   939, -1415, -1415,
     938,   942, -1415, -1415,   940,   944, -1415, -1415,   943,   945,
   -1415, -1415, -1415, -1415, -1415, -1415,    54, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   946,   947, -1415, -1415,   948,   950,
   -1415, -1415,   949,   953, -1415,   954,   955,   956,   957,   958,
     959,   182, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   960,
     961,   962, -1415,   193, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   951,   964, -1415,   965, -1415,   966, -1415, -1415, -1415,
     197, -1415, -1415, -1415, -1415, -1415,   204, -1415,   275, -1415,
     967,   968,   969,   970, -1415,   212, -1415, -1415, -1415, -1415,
   -1415,   740, -1415,   971,   973, -1415, -1415,   972, -1415,   975,
   -1415, -1415, -1415,   974,   979,   378, -1415,   980,   983,   990,
     991,   704,   713,   766,   768,   780,   782,   784,   785,   788,
     794,  1000,   797,   808,  1034,  1051,  1052,  1054,  1055,  1056,
     810, -1415, -1415,   810, -1415,   886,   697, -1415,   888,   134,
   -1415,   891,   353, -1415,   895,  1397, -1415,   896,    84, -1415,
     183, -1415,   897,   189, -1415,   898,   -72, -1415,   900,   829,
     830,   833,   846,   852,   853,   219, -1415,   857,   861,   870,
     -44, -1415,   266, -1415,   901,   872,  1064,   889,  1075,   -21,
   -1415, -1415,   380,   902, -1415,   875,   882,   892,   894,   -10,
   -1415, -1415,  1102,  1112,  1452, -1415,   903,  1118, -1415, -1415,
     906,   926, -1415,   963,   977,   978,   981, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   331, -1415, -1415,
     982,   984,   985,   346,   986,   987, -1415,   218, -1415,   233,
   -1415,  1119, -1415,  1127, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   236, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,  1133,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415,  1143,  1159, -1415, -1415, -1415, -1415, -1415,
   -1415,  1161, -1415,   242, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,  1167,
   -1415,  1174, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   243,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     988, -1415,    39, -1415, -1415,  1176, -1415, -1415, -1415, -1415,
   -1415,   249, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415,   989,   250, -1415,   879, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,  1397, -1415,  1177,
    1180,   952, -1415,   183, -1415, -1415,  1182,  1187,  1189,   992,
    1191,   976,  1192,   266, -1415, -1415, -1415,  1193,   993,  1195,
     380, -1415, -1415, -1415, -1415, -1415,   995,   996, -1415, -1415,
     228,   997,   998, -1415,  1194, -1415,  1197, -1415,  1198, -1415,
     999, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
      57,  1199,  1200, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   262, -1415, -1415, -1415, -1415, -1415, -1415,  1202,  1201,
   -1415, -1415,   308, -1415,  1196,  1205,  1206,  1211,    57, -1415,
     -54, -1415,  1199,    70,  1200, -1415,   793,  1001,  1002,  1213,
   -1415, -1415, -1415, -1415, -1415, -1415,   263, -1415, -1415, -1415,
   -1415,  1221,  1222,  1223, -1415,   288, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,  1228,  1234,   -54,
   -1415,  1235,  1003,  1006,  1007,  1241,    70, -1415, -1415,  1242,
    1244, -1415,  1014, -1415,  1016, -1415, -1415, -1415,  1017, -1415,
     146, -1415,  1228, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415,   310, -1415, -1415, -1415,  1250,   146, -1415,
    1020, -1415, -1415
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   219,     9,   408,    11,   631,    13,
     675,    15,   546,    17,   555,    19,   594,    21,   370,    23,
     875,    25,   907,    27,    46,    39,     0,     0,     0,     0,
       0,   677,     0,   557,   596,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   905,   203,   238,
       0,     0,     0,   697,   699,   701,     0,     0,   236,   249,
     251,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,     0,   166,
     173,   175,   177,     0,     0,     0,     0,     0,     0,     0,
     399,   544,   585,     0,   158,   181,   484,   662,   664,     0,
       0,     0,   332,   724,   666,   361,   382,     0,   347,   761,
     856,   873,   191,   193,     0,     0,     0,   917,   959,     0,
     142,     0,    67,    70,    71,    72,    73,    74,   107,   108,
     109,   110,   111,   112,    75,   103,   138,   139,    92,    93,
      94,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   114,   115,   130,   131,   132,
     134,   135,   136,   140,   141,    78,    79,   100,    80,    81,
      82,   133,    86,    87,    76,   104,   105,   106,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   113,   137,   221,   223,     0,   228,     0,
       0,     0,     0,   218,     0,   205,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   468,   470,   472,   622,
     466,   474,     0,   476,   478,   719,   465,   413,   414,   415,
     416,   417,   440,   441,   442,   443,   444,   445,   463,   430,
     431,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   464,     0,
     410,   420,   435,   436,   437,   421,   423,   424,   426,   427,
     428,   422,   418,   419,   438,   439,   425,   432,   433,   434,
     429,   659,     0,   658,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   639,
     640,   638,     0,   633,   636,   637,   656,   657,   717,   703,
     705,   707,   711,   709,   715,   713,   696,   690,   694,   695,
       0,   678,   679,   691,   692,   693,   687,   682,   688,   684,
     685,   686,   689,   683,     0,   575,   299,     0,   579,   577,
     582,     0,   571,   572,     0,   558,   559,   562,   574,   563,
     564,   565,   581,   566,   567,   568,   569,   570,   613,     0,
       0,     0,   620,   611,   612,   615,   616,     0,   597,   598,
     601,   602,   603,   604,   605,   606,   607,   610,   608,   609,
     378,   380,   375,     0,   372,   376,   377,     0,   892,     0,
     895,     0,     0,   899,   903,   890,   888,   889,     0,   877,
     880,   881,   882,   883,   884,   885,   886,   887,   914,     0,
       0,   909,   912,   913,    45,    50,     0,    37,    43,     0,
      64,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    69,    66,     0,     0,     0,
       0,     0,     0,     0,     0,   207,   220,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   412,   409,     0,
       0,   635,   632,     0,     0,     0,     0,     0,     0,     0,
       0,   676,   681,   547,     0,     0,     0,     0,     0,     0,
       0,   556,   561,     0,     0,     0,     0,     0,   595,   600,
       0,     0,   374,   371,     0,     0,     0,     0,     0,     0,
       0,     0,   879,   876,     0,     0,   911,   908,    49,    41,
       0,     0,     0,     0,     0,   160,   161,   162,     0,     0,
       0,   201,   202,     0,     0,     0,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,     0,   196,
     197,   163,   164,   165,     0,     0,     0,     0,   179,   180,
     187,   188,   189,   190,   195,     0,     0,     0,   157,     0,
       0,     0,     0,     0,   480,   481,   482,     0,     0,     0,
       0,     0,   760,     0,     0,     0,     0,     0,     0,   198,
     199,   200,     0,     0,    68,     0,     0,   227,     0,   232,
     233,   234,   235,   206,     0,     0,     0,     0,     0,     0,
     483,     0,     0,     0,   411,     0,   661,   634,     0,     0,
       0,     0,     0,     0,     0,     0,   680,     0,     0,   573,
       0,     0,     0,   584,   560,     0,   617,   618,   619,     0,
     599,     0,     0,   373,   891,     0,   894,     0,   897,   898,
       0,     0,   878,     0,   916,   910,     0,     0,     0,     0,
       0,   698,   700,   702,     0,     0,   253,   156,   168,   169,
     170,   171,   172,   167,   174,   176,   178,   401,   548,   587,
     159,   183,   184,   185,   186,   182,   486,    38,   663,   665,
       0,   726,   668,   363,     0,     0,   763,     0,     0,   192,
     194,     0,     0,    51,   222,   225,   226,   224,   230,   231,
     229,   469,   471,   473,   624,   467,   475,   477,   479,     0,
     660,   718,   704,   706,   708,   712,   710,   716,   714,   576,
     300,   580,   578,   583,   614,   621,   379,   381,   893,   896,
     901,   902,   900,   904,   253,    42,     0,     0,     0,   245,
     247,     0,   240,   243,   244,   288,   290,   292,   296,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   310,
       0,     0,   317,   319,   321,   323,   325,   326,   327,   328,
     329,   330,   294,   287,     0,   260,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
       0,   258,     0,   254,   255,   406,     0,   402,   403,   553,
       0,   549,   550,   592,     0,   588,   589,   491,     0,   487,
     488,   342,   343,   344,   345,   346,     0,   334,   337,   338,
     339,   340,   341,   731,     0,   727,   728,   673,     0,   669,
     670,   368,     0,   364,   365,     0,     0,     0,     0,     0,
       0,     0,   384,   387,   388,   389,   390,   391,   392,     0,
       0,     0,   357,     0,   349,   352,   353,   354,   355,   356,
     768,     0,   764,   765,     0,   868,     0,   871,   864,   865,
       0,   858,   861,   862,   863,   866,     0,   922,     0,   919,
       0,     0,     0,     0,   968,     0,   961,   964,   965,   966,
     967,    53,   629,     0,   625,   626,   722,     0,   721,     0,
      62,   906,   204,     0,     0,   242,   239,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     262,   237,   250,     0,   252,   257,     0,   400,   405,   557,
     545,   552,   596,   586,   591,     0,   485,   490,   336,   333,
     733,   725,   730,   677,   667,   672,     0,   362,   367,     0,
       0,     0,     0,     0,     0,   386,   383,     0,     0,     0,
     351,   348,     0,   762,   767,     0,     0,     0,     0,   860,
     857,   874,     0,   921,   918,     0,     0,     0,     0,   963,
     960,    55,     0,    54,     0,   623,   628,     0,   720,   915,
       0,     0,   241,     0,     0,     0,     0,   298,   301,   302,
     303,   304,   305,   306,   307,   308,   309,     0,   315,   316,
       0,     0,     0,     0,     0,     0,   261,     0,   256,     0,
     404,     0,   551,     0,   590,   543,   513,   514,   515,   499,
     500,   518,   519,   520,   521,   522,   523,   541,   502,   503,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   542,   496,   497,
     498,   511,   512,   508,   509,   510,     0,   493,   501,   516,
     517,   504,   505,   506,   507,   489,   335,   755,   757,     0,
     749,   750,   751,   752,   753,   754,   742,   743,   747,   748,
     744,   745,   746,     0,   734,   735,   738,   739,   740,   741,
     729,     0,   671,     0,   366,   393,   394,   395,   396,   397,
     398,   385,   358,   359,   360,   350,   786,   791,   793,     0,
     816,     0,   797,   785,   778,   779,   780,   783,   784,     0,
     770,   773,   774,   775,   776,   781,   782,   777,   766,   867,
       0,   870,     0,   859,   937,     0,   935,   933,   927,   931,
     932,     0,   924,   929,   930,   928,   920,   969,   970,   971,
     972,   962,    52,    57,     0,   627,     0,   246,   248,   289,
     291,   293,   297,   312,   313,   314,   311,   318,   320,   322,
     324,   331,   295,   259,   407,   554,   593,   495,   492,     0,
       0,     0,   732,   737,   674,   369,     0,     0,     0,     0,
       0,     0,     0,   772,   769,   869,   872,     0,     0,     0,
     926,   923,    56,   630,   723,   494,     0,     0,   759,   736,
       0,     0,     0,   795,     0,   796,     0,   771,     0,   934,
       0,   925,   756,   758,   788,   789,   790,   787,   792,   794,
       0,   799,     0,   936,   828,   831,   833,   835,   827,   826,
     825,     0,   818,   821,   822,   823,   824,   804,     0,   800,
     801,   942,     0,   939,     0,     0,     0,     0,   820,   817,
       0,   798,   803,     0,   941,   938,     0,     0,     0,     0,
     819,   814,   813,   809,   811,   812,     0,   806,   810,   802,
     952,     0,     0,     0,   957,     0,   944,   947,   948,   949,
     950,   951,   940,   830,   829,   832,   834,   837,     0,   808,
     805,     0,     0,     0,     0,     0,   946,   943,   842,     0,
     838,   839,     0,   807,     0,   954,   955,   956,     0,   945,
       0,   836,   841,   815,   953,   958,   854,   853,   847,   849,
     850,   851,   852,     0,   844,   848,   840,     0,   846,   843,
       0,   845,   855
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   -51, -1415,  -623, -1415,   525,
   -1415, -1415, -1415, -1415, -1415, -1415,  -682, -1415, -1415, -1415,
     -67, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   511,   725,
     -48,    25,    44,   -45,   -19,     6,    41,    93,    98,   100,
     101, -1415, -1415, -1415, -1415,   103, -1415, -1415,   108,   111,
      38,    46,    48,    56, -1415, -1415,    61, -1415,    63, -1415,
      66, -1415,    68,   113,    71, -1415, -1415,    73,    78,    83,
      85,    88, -1415,    90, -1415,   118, -1415, -1415, -1415, -1415,
   -1415,    45, -1415, -1415, -1415,   512,   724, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   190, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   434, -1415,   225, -1415,
    -750,   224, -1415, -1415, -1414, -1415, -1413, -1415, -1399, -1415,
   -1415, -1415, -1415,   -63, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1064,
   -1415, -1060, -1415, -1059, -1415,   138, -1415, -1415, -1415, -1415,
   -1415, -1415,   215, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   194, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   208,
   -1415, -1415, -1415,   211,   698, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,   206, -1415, -1415, -1415, -1415, -1415, -1415, -1040,
   -1415, -1415, -1415,   231, -1415, -1415, -1415,   237,   728, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1039, -1415,   -32,
   -1415,   -27, -1415,   128,   130,   133, -1415, -1415, -1415, -1415,
   -1415,   229, -1415, -1415,   -20,   -60, -1415, -1415, -1415, -1415,
   -1415,   240, -1415, -1415, -1415,   246, -1415,   714, -1415,   -49,
   -1415, -1415, -1415, -1415, -1415,   -43, -1415, -1415, -1415, -1415,
   -1415,   -29, -1415, -1415, -1415,   238, -1415, -1415, -1415,   245,
   -1415,   717, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   192, -1415, -1415, -1415,
     195,   741, -1415, -1415, -1415,   -41, -1415,    -6, -1415,   -55,
   -1415, -1415, -1415,   239, -1415, -1415, -1415,   247, -1415,   731,
     -13, -1415,     7, -1415,    18, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1038, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   253, -1415, -1415, -1415,    -8, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   227, -1415, -1415,
     -15, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   -83, -1415, -1415,  -117, -1415, -1415,
   -1415, -1415, -1415,   -70, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,  -136, -1415, -1415,  -146, -1415,
   -1415, -1415, -1415, -1415,   241, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   540,   727, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   578,   729, -1415, -1415, -1415, -1415,
   -1415, -1415,   244, -1415, -1415,     3, -1415, -1415, -1415, -1415,
   -1415, -1415,   -58, -1415, -1415,  -102, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   251, -1415, -1415, -1415,
   -1415
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   778,
      82,    83,    39,    64,    79,    80,   794,  1001,  1102,  1103,
     873,    41,    66,    85,   459,    86,    43,    67,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   488,   176,   177,   509,   178,   179,   180,
     181,   182,   183,   184,   494,   763,   185,   495,   186,   496,
     187,   497,   188,   189,   190,   510,   775,   191,   192,   193,
     194,   195,   527,   196,   528,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   463,   244,   245,    45,    68,   246,
     537,   247,   538,   797,   248,   249,   540,   800,   250,   251,
     252,   253,   206,   473,   207,   464,   841,   842,   843,  1013,
     844,  1014,   208,   474,   209,   475,   902,   903,   904,  1043,
     874,   875,   876,  1017,   877,  1018,   878,  1019,   879,  1039,
     880,  1020,   881,   882,   575,   883,   884,   885,   886,   887,
     888,   889,   890,   891,   892,  1031,  1296,   893,   894,   895,
    1034,   896,  1035,   897,  1036,   898,  1037,   899,  1038,   210,
     517,   926,   927,   928,   929,   930,   931,   932,   211,   523,
     963,   964,   965,   966,   967,   212,   520,   942,   943,   944,
    1066,    59,    75,   423,   424,   425,   590,   426,   591,   213,
     521,   951,   952,   953,   954,   955,   956,   957,   958,   214,
     505,   906,   907,   908,  1046,    47,    69,   299,   300,   301,
     551,   302,   547,   303,   548,   304,   549,   305,   552,   306,
     554,   307,   555,   215,   216,   217,   311,   218,   511,   918,
     919,   920,  1055,  1186,  1187,   219,   506,    53,    72,   910,
     911,   912,  1049,    55,    73,   384,   385,   386,   387,   388,
     389,   390,   574,   391,   578,   392,   577,   393,   394,   579,
     395,   220,   507,   914,   915,   916,  1052,    57,    74,   407,
     408,   409,   410,   411,   583,   412,   413,   414,   415,   416,
     417,   587,   313,   550,  1003,  1004,  1005,  1104,    49,    70,
     342,   343,   344,   559,   345,   221,   512,   222,   513,   223,
     519,   938,   939,   940,  1063,    51,    71,   360,   361,   362,
     224,   468,   225,   469,   226,   470,   366,   564,   367,   565,
     368,   566,   369,   568,   370,   567,   371,   570,   372,   569,
     373,   563,   320,   556,  1007,  1008,  1107,   227,   518,   934,
     935,   936,  1060,  1213,  1214,  1215,  1216,  1217,  1309,  1218,
    1310,  1219,   228,   229,   524,   971,   972,   973,  1082,  1249,
    1250,  1251,  1316,  1357,  1252,  1317,  1253,  1318,  1254,  1255,
    1256,  1322,  1378,  1379,  1380,  1390,  1406,  1407,  1408,  1428,
    1257,  1320,  1371,  1372,  1373,  1384,  1424,  1374,  1385,  1375,
    1386,  1376,  1387,  1439,  1440,  1441,  1450,  1463,  1464,  1465,
    1467,   230,   525,   980,   981,   982,   983,  1086,   984,   985,
    1088,   231,   526,    61,    76,   438,   439,   440,   441,   595,
     442,   443,   597,   444,   445,   446,   600,   832,   447,   601,
     232,   462,    63,    77,   450,   451,   452,   604,   453,   233,
     532,   988,   989,  1092,  1271,  1272,  1273,  1274,  1329,  1275,
    1327,  1382,  1383,  1393,  1415,  1416,  1417,  1431,  1418,  1419,
    1420,  1421,  1435,   234,   533,   995,   996,   997,   998,   999,
    1000
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     160,   243,   266,   323,   356,   900,   382,   403,   422,   435,
     383,   404,   374,    78,   316,  1179,  1180,  1194,  1244,   807,
     808,   267,  1245,  1246,   270,   405,   811,   254,   314,   346,
     358,   406,   396,   418,   830,   436,  1458,  1459,   339,   777,
     312,   341,   357,   340,    29,    81,    30,   825,    31,    28,
     271,  1460,   376,    84,  1458,  1459,   317,  1058,   363,    40,
    1059,   460,   255,   315,   347,   359,   461,   397,   419,  1460,
     437,    42,   137,   138,    44,   272,   318,   455,   364,   535,
     420,   421,   137,   138,   536,   545,    46,   319,    48,   365,
     546,   456,   235,   236,   268,   131,   237,   238,  1364,   557,
     239,   240,   241,   242,   558,   137,   138,   281,   324,   777,
     273,   448,   449,   269,   298,   282,   325,   283,   326,   959,
     960,   961,   561,   592,    50,   284,   327,   562,   593,  1401,
     285,   328,   286,   329,   602,   287,   330,   288,   331,   603,
     290,   332,   291,   333,   606,   535,   606,   292,   334,   607,
    1010,  1011,   293,   335,   294,   336,   545,   295,   337,   296,
     338,  1012,   274,   159,   974,   975,   976,   275,  1015,   276,
     277,  1040,   278,  1016,  1040,   375,  1041,   279,   454,  1042,
     280,   159,   289,   137,   138,  1075,    52,   297,   846,   847,
    1076,   159,   758,   759,   760,   761,  1080,   308,    54,   309,
    1089,  1081,   310,   137,   138,  1090,    56,   602,   990,   991,
     992,   993,  1091,   831,   977,  1099,    93,    94,    95,    96,
    1100,  1040,    93,    94,    95,   159,  1303,   921,   922,   923,
     924,   762,   925,  1365,  1366,  1367,   557,   795,   796,  1307,
     376,  1304,   377,   378,  1308,   592,  1323,   379,   380,   381,
    1315,  1324,  1330,   561,   101,   102,   103,  1331,  1333,  1244,
     137,   138,    58,  1245,  1246,  1388,  1429,  1179,  1180,  1194,
    1389,  1430,   137,   138,    32,    33,    34,    35,  1093,    87,
    1410,  1094,    88,  1411,  1412,  1413,  1414,   131,   132,   376,
      60,  1436,   159,  1137,   132,    89,  1437,    62,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   137,
     138,  1394,   159,  1468,  1395,   137,   138,   457,  1469,   458,
    1197,  1198,  1199,   465,   348,  1456,   872,   862,   863,   864,
     466,   349,   350,   351,   352,   353,   354,   355,   467,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   159,
     798,   799,   131,   132,   945,   946,   947,   948,   949,   950,
     471,   159,   420,   421,   133,   134,   135,  1293,  1294,  1295,
     472,   136,   137,   138,   137,   138,  1354,  1355,  1356,   139,
     140,   141,   142,   143,   608,   609,   839,   840,   476,   144,
     865,   866,   867,   868,   869,   870,   477,   478,   159,   145,
     479,   480,   146,   481,   159,   771,   772,   773,   774,   147,
     148,   482,   483,  1236,   149,   484,   485,  1237,  1238,  1239,
    1240,   486,   487,   489,   490,   491,   492,  1241,  1242,   493,
     498,   499,   150,   500,   501,   502,   151,   503,   504,   376,
     398,   377,   378,   399,   400,   401,   508,   514,   160,   515,
     516,   152,   153,   154,   155,   156,   157,   522,   243,   137,
     138,   529,   530,   531,   534,   158,   376,   539,   402,   541,
     266,   542,   543,   544,   323,   553,   560,   572,   571,   576,
     580,   159,   316,   159,   254,   356,   137,   138,   573,   267,
     581,   582,   270,   584,   588,   382,   314,   585,   586,   383,
     346,   589,   403,   594,   596,   598,   404,   599,   312,   339,
     610,   358,   341,   605,   340,   435,   611,   612,   271,   255,
     405,   396,   613,   357,   317,   614,   406,   618,   418,   615,
     616,   315,   617,   619,   620,   347,   621,   623,   624,   363,
     622,   436,   625,   272,   318,   626,   359,   632,   627,   628,
     638,   629,   630,   644,   633,   319,   397,   631,   634,   364,
     635,   637,   268,   419,   636,   645,   639,   640,   159,  1264,
     365,  1265,  1266,   641,   642,   281,   437,   643,   273,   324,
     646,   269,   298,   282,  1334,   283,   647,   325,   648,   326,
     649,   650,   655,   284,   656,   159,   657,   327,   285,   651,
     286,   652,   328,   287,   329,   288,   653,   330,   290,   331,
     291,   654,   332,   658,   333,   292,   137,   138,   659,   334,
     293,   660,   294,   661,   335,   295,   336,   296,   662,   337,
     274,   338,   663,   664,   667,   275,   665,   276,   277,   666,
     278,   668,   669,   670,   671,   279,   672,   673,   280,   674,
     289,   675,   676,   677,   678,   297,   682,   683,   685,   686,
     160,   679,   243,   688,   694,   308,   680,   309,   691,   695,
     310,   696,   697,   681,   687,   835,   689,   690,   698,   427,
     428,   429,   430,   431,   432,   433,   434,   692,   254,   699,
     700,   701,   702,   703,   705,   708,   709,   706,   962,   710,
     711,   435,   712,   713,   714,   994,   715,   717,    91,    92,
      93,    94,    95,    96,   718,   719,   720,   721,   722,   723,
     725,   726,   727,   255,   968,   159,   978,   436,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   729,   728,   731,   732,   734,   735,   736,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   969,
     737,   979,   437,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   738,   256,   257,
     258,   739,   132,   740,   741,   743,   744,   746,   751,   747,
     752,   748,   749,   750,   134,   135,   754,   753,   755,   756,
     757,   259,   764,   137,   138,   260,   261,   262,   139,   140,
     141,   767,   263,   264,   765,   766,   768,   769,   144,   770,
     776,    30,   779,   780,   781,   782,   265,   783,   784,   786,
     785,   845,   846,   847,   848,   849,   850,   851,   852,   853,
     854,   855,   856,   857,   858,   859,   787,   788,   789,   860,
     861,   862,   863,   864,   865,   866,   867,   868,   869,   870,
     871,   790,   791,   792,   793,   804,   801,   802,   803,   805,
     806,   809,   834,   901,   833,   905,   810,   812,   909,   813,
     152,   153,   913,   917,   933,   937,   814,   941,   970,   987,
    1002,   815,   816,   817,  1006,  1021,   376,   818,   819,   820,
    1022,   821,  1023,  1024,   822,   823,   824,   826,   828,  1025,
     829,  1026,   159,  1027,  1028,  1029,  1030,  1032,  1033,  1045,
    1117,  1044,  1048,  1047,  1050,  1051,  1053,  1054,  1057,  1056,
    1062,  1118,  1061,  1065,  1064,  1067,  1068,  1083,  1069,  1070,
    1071,  1072,  1073,  1074,  1077,  1078,  1079,  1084,  1423,  1085,
    1087,  1095,  1096,  1097,  1098,  1101,  1106,  1105,  1110,   266,
    1108,  1109,   382,  1111,  1113,   403,   383,  1114,  1145,   404,
     872,   316,  1178,  1200,  1115,  1116,   356,  1205,   267,   422,
    1206,   270,  1119,   405,  1127,   314,  1120,  1146,   396,   406,
    1149,   418,  1201,   962,  1189,  1243,  1121,   312,  1122,  1208,
    1123,  1124,   358,  1181,  1125,  1267,  1188,   271,  1182,  1268,
    1126,  1207,   994,   317,   357,  1128,  1150,   323,  1130,   968,
     315,  1247,  1191,   397,  1129,   159,   419,  1210,   978,  1190,
     363,  1269,   272,   318,  1209,  1131,  1132,   359,  1133,  1134,
    1135,  1151,  1192,   346,   319,  1225,  1226,  1211,  1260,  1227,
     364,   268,   339,  1193,   969,   341,  1248,   340,  1212,  1262,
    1147,   365,  1228,   979,   281,  1202,  1270,   273,  1229,  1230,
     269,   298,   282,  1160,   283,  1232,  1152,  1233,   347,  1148,
    1177,  1161,   284,  1162,  1203,  1204,  1234,   285,  1282,   286,
    1259,  1163,   287,  1277,   288,  1283,  1164,   290,  1165,   291,
    1278,  1166,  1286,  1167,   292,  1261,  1169,  1305,  1170,   293,
    1279,   294,  1280,  1171,   295,  1306,   296,  1311,  1172,   274,
    1173,  1287,   324,  1174,   275,  1175,   276,   277,  1153,   278,
     325,  1312,   326,  1154,   279,  1155,  1156,   280,  1157,   289,
     327,  1288,  1313,  1158,   297,   328,  1159,   329,  1168,  1314,
     330,  1319,   331,  1176,   308,   332,   309,   333,  1321,   310,
    1328,  1336,   334,  1183,  1337,  1184,  1340,   335,  1185,   336,
    1338,  1341,   337,  1342,   338,  1344,  1346,  1348,  1289,  1350,
    1396,  1360,  1361,  1362,  1392,  1112,  1377,  1381,  1391,  1397,
    1398,  1326,  1290,  1291,  1345,  1399,  1292,  1297,  1427,  1298,
    1299,  1301,  1302,  1325,  1332,  1432,  1433,  1434,  1343,  1349,
    1352,  1353,  1358,  1359,  1363,  1438,  1425,  1426,  1442,  1444,
    1145,  1445,  1446,  1447,  1178,  1448,  1200,  1452,  1451,  1453,
    1205,  1454,  1455,  1206,  1470,  1472,  1243,   827,   836,  1146,
     684,   838,  1149,  1267,  1136,  1201,  1189,  1268,  1009,   693,
    1138,  1300,  1208,  1196,  1235,  1181,  1224,  1223,  1188,  1140,
    1182,  1231,  1247,  1139,  1207,   704,  1195,  1335,  1150,  1269,
     733,  1142,  1144,  1368,  1191,  1141,   724,  1143,  1285,  1284,
    1210,  1190,   707,   716,  1222,  1339,   730,  1209,  1347,  1409,
    1221,  1258,  1443,  1151,  1192,  1220,  1466,  1248,  1400,  1369,
    1211,  1368,  1471,  1402,  1270,  1193,   837,  1403,   986,   742,
    1263,  1212,  1147,  1351,  1449,   745,  1422,  1276,  1202,     0,
       0,     0,     0,     0,     0,  1160,     0,  1369,  1152,  1404,
    1281,  1148,  1177,  1161,  1370,  1162,     0,  1203,  1204,     0,
       0,     0,  1402,  1163,     0,     0,  1403,     0,  1164,     0,
    1165,     0,     0,  1166,     0,  1167,     0,     0,  1169,     0,
    1170,     0,  1370,  1457,  1405,  1171,     0,     0,  1404,     0,
    1172,     0,  1173,     0,     0,  1174,     0,  1175,     0,     0,
    1153,  1457,     0,     0,     0,  1154,     0,  1155,  1156,  1461,
    1157,     0,     0,     0,     0,  1158,     0,     0,  1159,     0,
    1168,     0,     0,  1405,     0,  1176,     0,  1461,    91,    92,
      93,    94,    95,    96,     0,  1183,     0,  1184,     0,     0,
    1185,     0,     0,     0,  1462,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1462,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
       0,     0,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     0,     0,
       0,     0,   132,   376,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,     0,     0,     0,     0,
       0,     0,     0,   137,   138,     0,   261,     0,   139,   140,
     141,     0,   263,   264,     0,     0,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   265,   125,   126,   127,
     128,     0,     0,     0,     0,     0,     0,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,     0,     0,     0,     0,     0,     0,   321,   137,   138,
       0,     0,     0,     0,     0,     0,     0,   263,   264,     0,
       0,     0,   322,     0,     0,     0,     0,     0,     0,     0,
     152,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   159
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,   755,    73,    74,    75,    76,
      73,    74,    72,    64,    69,  1055,  1055,  1055,  1082,   701,
     702,    69,  1082,  1082,    69,    74,   708,    68,    69,    70,
      71,    74,    73,    74,    18,    76,  1450,  1450,    70,   662,
      69,    70,    71,    70,     5,   235,     7,   729,     9,     0,
      69,  1450,   106,    10,  1468,  1468,    69,     3,    71,     7,
       6,     3,    68,    69,    70,    71,     8,    73,    74,  1468,
      76,     7,   126,   127,     7,    69,    69,     3,    71,     3,
     152,   153,   126,   127,     8,     3,     7,    69,     7,    71,
       8,     4,    15,    16,    69,   104,    19,    20,    41,     3,
      23,    24,    25,    26,     8,   126,   127,    69,    70,   732,
      69,    12,    13,    69,    69,    69,    70,    69,    70,   163,
     164,   165,     3,     3,     7,    69,    70,     8,     8,   183,
      69,    70,    69,    70,     3,    69,    70,    69,    70,     8,
      69,    70,    69,    70,     3,     3,     3,    69,    70,     8,
       8,     8,    69,    70,    69,    70,     3,    69,    70,    69,
      70,     8,    69,   235,   185,   186,   187,    69,     3,    69,
      69,     3,    69,     8,     3,    41,     8,    69,     6,     8,
      69,   235,    69,   126,   127,     3,     7,    69,    42,    43,
       8,   235,   199,   200,   201,   202,     3,    69,     7,    69,
       3,     8,    69,   126,   127,     8,     7,     3,   218,   219,
     220,   221,     8,   197,   235,     3,    33,    34,    35,    36,
       8,     3,    33,    34,    35,   235,     8,   143,   144,   145,
     146,   238,   148,   176,   177,   178,     3,    17,    18,     3,
     106,     8,   108,   109,     8,     3,     3,   113,   114,   115,
       8,     8,     3,     3,    71,    72,    73,     8,     8,  1323,
     126,   127,     7,  1323,  1323,     3,     3,  1307,  1307,  1307,
       8,     8,   126,   127,   235,   236,   237,   238,     3,    11,
     210,     6,    14,   213,   214,   215,   216,   104,   105,   106,
       7,     3,   235,  1043,   105,    27,     8,     7,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   126,
     127,     3,   235,     3,     6,   126,   127,     8,     8,     3,
     137,   138,   139,     4,   135,   179,   180,    61,    62,    63,
       4,   142,   143,   144,   145,   146,   147,   148,     4,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   235,
      21,    22,   104,   105,   155,   156,   157,   158,   159,   160,
       4,   235,   152,   153,   116,   117,   118,    56,    57,    58,
       4,   123,   126,   127,   126,   127,   168,   169,   170,   131,
     132,   133,   134,   135,   455,   456,    28,    29,     4,   141,
      64,    65,    66,    67,    68,    69,     4,     4,   235,   151,
       4,     4,   154,     4,   235,   119,   120,   121,   122,   161,
     162,     4,     4,   167,   166,     4,     4,   171,   172,   173,
     174,     4,     4,     4,     4,     4,     4,   181,   182,     4,
       4,     4,   184,     4,     4,     4,   188,     4,     4,   106,
     107,   108,   109,   110,   111,   112,     4,     4,   535,     4,
       4,   203,   204,   205,   206,   207,   208,     4,   545,   126,
     127,     4,     4,     4,     4,   217,   106,     4,   135,     4,
     557,     4,     4,     4,   561,     4,     4,     3,     8,     4,
       4,   235,   557,   235,   545,   572,   126,   127,     8,   557,
       8,     3,   557,     4,     8,   582,   557,     4,     4,   582,
     561,     3,   589,     4,     4,     4,   589,     4,   557,   561,
     235,   572,   561,     4,   561,   602,     4,     4,   557,   545,
     589,   582,     4,   572,   557,     4,   589,     4,   589,   238,
     238,   557,   238,     4,     4,   561,   236,     4,     4,   572,
     238,   602,     4,   557,   557,   236,   572,   237,   236,   236,
       4,   236,   236,     4,   237,   557,   582,   238,   237,   572,
     236,   236,   557,   589,   237,     4,   236,   236,   235,   209,
     572,   211,   212,   238,   238,   557,   602,   238,   557,   561,
       4,   557,   557,   557,  1286,   557,     4,   561,   238,   561,
     238,   237,     4,   557,     4,   235,     4,   561,   557,   236,
     557,   236,   561,   557,   561,   557,   236,   561,   557,   561,
     557,   238,   561,   236,   561,   557,   126,   127,     4,   561,
     557,     4,   557,     4,   561,   557,   561,   557,     4,   561,
     557,   561,     4,   238,     4,   557,   238,   557,   557,   238,
     557,     4,     4,     4,     4,   557,   236,     4,   557,     4,
     557,     4,     4,     4,     4,   557,     4,     4,     4,     4,
     747,   238,   749,     4,     4,   557,   238,   557,   236,     4,
     557,     4,     4,   238,   238,   746,   238,   238,     4,   189,
     190,   191,   192,   193,   194,   195,   196,   236,   749,     4,
     236,     4,     4,     4,     4,     4,     4,   236,   785,     4,
       4,   788,     4,     4,     4,   792,     4,     4,    31,    32,
      33,    34,    35,    36,     4,   236,     4,     4,     4,   238,
       4,   238,   238,   749,   785,   235,   787,   788,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,     4,   238,     4,     4,   238,     4,   236,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,   785,
       4,   787,   788,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   236,   101,   102,
     103,   236,   105,     4,     4,     4,   236,     4,   235,     7,
     235,     7,     7,     7,   117,   118,     7,   235,     7,     5,
     235,   124,   235,   126,   127,   128,   129,   130,   131,   132,
     133,     5,   135,   136,   235,   235,     5,     5,   141,   235,
       5,     7,   235,     5,     5,     5,   149,     5,     7,     5,
       7,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     7,     7,   235,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,   235,     5,     7,     5,     5,   235,   235,   235,   235,
     235,     7,     5,     7,   198,     7,   235,   235,     7,   235,
     203,   204,     7,     7,     7,     7,   235,     7,     7,     7,
       7,   235,   235,   235,   150,     4,   106,   235,   235,   235,
       4,   235,     4,     4,   235,   235,   235,   235,   235,     4,
     235,     4,   235,     4,     4,     4,     4,     4,     4,     3,
     236,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   238,     6,     3,     6,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   175,     4,
       4,     4,     4,     4,     4,   235,     3,     6,     4,  1046,
       8,     6,  1049,     4,     4,  1052,  1049,     4,  1055,  1052,
     180,  1046,  1055,  1060,     4,     4,  1063,  1060,  1046,  1066,
    1060,  1046,   236,  1052,     4,  1046,   238,  1055,  1049,  1052,
    1055,  1052,  1060,  1080,  1055,  1082,   236,  1046,   236,  1060,
     236,   236,  1063,  1055,   236,  1092,  1055,  1046,  1055,  1092,
     236,  1060,  1099,  1046,  1063,   238,  1055,  1104,     4,  1080,
    1046,  1082,  1055,  1049,   236,   235,  1052,  1060,  1089,  1055,
    1063,  1092,  1046,  1046,  1060,     4,     4,  1063,     4,     4,
       4,  1055,  1055,  1104,  1046,   236,   236,  1060,     4,   236,
    1063,  1046,  1104,  1055,  1080,  1104,  1082,  1104,  1060,     4,
    1055,  1063,   236,  1089,  1046,  1060,  1092,  1046,   236,   236,
    1046,  1046,  1046,  1055,  1046,   238,  1055,   236,  1104,  1055,
    1055,  1055,  1046,  1055,  1060,  1060,   236,  1046,     6,  1046,
     238,  1055,  1046,   238,  1046,     3,  1055,  1046,  1055,  1046,
     238,  1055,     4,  1055,  1046,   236,  1055,     8,  1055,  1046,
     238,  1046,   238,  1055,  1046,     8,  1046,     4,  1055,  1046,
    1055,   235,  1104,  1055,  1046,  1055,  1046,  1046,  1055,  1046,
    1104,     8,  1104,  1055,  1046,  1055,  1055,  1046,  1055,  1046,
    1104,   235,     3,  1055,  1046,  1104,  1055,  1104,  1055,     8,
    1104,     4,  1104,  1055,  1046,  1104,  1046,  1104,     4,  1046,
       4,     4,  1104,  1055,     4,  1055,     4,  1104,  1055,  1104,
     238,     4,  1104,     4,  1104,     4,     4,     4,   235,     4,
       4,     7,     5,     5,     3,  1015,     7,     7,     6,     4,
       4,  1262,   235,   235,   238,     4,   235,   235,     5,   235,
     235,   235,   235,   235,   235,     4,     4,     4,   236,   236,
     235,   235,   235,   235,   235,     7,   235,   235,     4,     4,
    1307,   238,   236,   236,  1307,     4,  1313,     3,     6,   235,
    1313,   235,   235,  1313,     4,   235,  1323,   732,   747,  1307,
     535,   749,  1307,  1330,  1040,  1313,  1307,  1330,   834,   545,
    1045,  1133,  1313,  1058,  1080,  1307,  1068,  1066,  1307,  1048,
    1307,  1075,  1323,  1046,  1313,   557,  1057,  1307,  1307,  1330,
     592,  1051,  1054,  1360,  1307,  1049,   582,  1052,  1106,  1104,
    1313,  1307,   561,   572,  1065,  1313,   589,  1313,  1323,  1392,
    1063,  1084,  1429,  1307,  1307,  1062,  1452,  1323,  1388,  1360,
    1313,  1388,  1468,  1390,  1330,  1307,   748,  1390,   788,   602,
    1089,  1313,  1307,  1330,  1436,   606,  1394,  1093,  1313,    -1,
      -1,    -1,    -1,    -1,    -1,  1307,    -1,  1388,  1307,  1390,
    1099,  1307,  1307,  1307,  1360,  1307,    -1,  1313,  1313,    -1,
      -1,    -1,  1429,  1307,    -1,    -1,  1429,    -1,  1307,    -1,
    1307,    -1,    -1,  1307,    -1,  1307,    -1,    -1,  1307,    -1,
    1307,    -1,  1388,  1450,  1390,  1307,    -1,    -1,  1429,    -1,
    1307,    -1,  1307,    -1,    -1,  1307,    -1,  1307,    -1,    -1,
    1307,  1468,    -1,    -1,    -1,  1307,    -1,  1307,  1307,  1450,
    1307,    -1,    -1,    -1,    -1,  1307,    -1,    -1,  1307,    -1,
    1307,    -1,    -1,  1429,    -1,  1307,    -1,  1468,    31,    32,
      33,    34,    35,    36,    -1,  1307,    -1,  1307,    -1,    -1,
    1307,    -1,    -1,    -1,  1450,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1468,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,    -1,   129,    -1,   131,   132,
     133,    -1,   135,   136,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,    93,   149,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,   136,    -1,
      -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     203,   204,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   235,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   203,   204,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   235
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,     0,     5,
       7,     9,   235,   236,   237,   238,   254,   255,   256,   261,
       7,   270,     7,   275,     7,   336,     7,   454,     7,   537,
       7,   554,     7,   486,     7,   492,     7,   516,     7,   430,
       7,   662,     7,   681,   262,   257,   271,   276,   337,   455,
     538,   555,   487,   493,   517,   431,   663,   682,   254,   263,
     264,   235,   259,   260,    10,   272,   274,    11,    14,    27,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   104,   105,   116,   117,   118,   123,   126,   127,   131,
     132,   133,   134,   135,   141,   151,   154,   161,   162,   166,
     184,   188,   203,   204,   205,   206,   207,   208,   217,   235,
     269,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   293,   294,   296,   297,
     298,   299,   300,   301,   302,   305,   307,   309,   311,   312,
     313,   316,   317,   318,   319,   320,   322,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   351,   353,   361,   363,
     408,   417,   424,   438,   448,   472,   473,   474,   476,   484,
     510,   544,   546,   548,   559,   561,   563,   586,   601,   602,
     650,   660,   679,   688,   712,    15,    16,    19,    20,    23,
      24,    25,    26,   269,   334,   335,   338,   340,   343,   344,
     347,   348,   349,   350,   544,   546,   101,   102,   103,   124,
     128,   129,   130,   135,   136,   149,   269,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   294,   297,
     298,   299,   300,   301,   302,   305,   307,   309,   311,   312,
     313,   316,   317,   318,   319,   320,   322,   324,   330,   456,
     457,   458,   460,   462,   464,   466,   468,   470,   472,   473,
     474,   475,   510,   531,   544,   546,   548,   559,   561,   563,
     581,   125,   140,   269,   299,   300,   301,   302,   305,   307,
     309,   311,   313,   316,   317,   318,   319,   320,   322,   468,
     470,   510,   539,   540,   541,   543,   544,   546,   135,   142,
     143,   144,   145,   146,   147,   148,   269,   510,   544,   546,
     556,   557,   558,   559,   561,   563,   565,   567,   569,   571,
     573,   575,   577,   579,   484,    41,   106,   108,   109,   113,
     114,   115,   269,   382,   494,   495,   496,   497,   498,   499,
     500,   502,   504,   506,   507,   509,   544,   546,   107,   110,
     111,   112,   135,   269,   382,   498,   504,   518,   519,   520,
     521,   522,   524,   525,   526,   527,   528,   529,   544,   546,
     152,   153,   269,   432,   433,   434,   436,   189,   190,   191,
     192,   193,   194,   195,   196,   269,   544,   546,   664,   665,
     666,   667,   669,   670,   672,   673,   674,   677,    12,    13,
     683,   684,   685,   687,     6,     3,     4,     8,     3,   273,
       3,     8,   680,   333,   354,     4,     4,     4,   560,   562,
     564,     4,     4,   352,   362,   364,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   292,     4,
       4,     4,     4,     4,   303,   306,   308,   310,     4,     4,
       4,     4,     4,     4,     4,   449,   485,   511,     4,   295,
     314,   477,   545,   547,     4,     4,     4,   409,   587,   549,
     425,   439,     4,   418,   603,   651,   661,   321,   323,     4,
       4,     4,   689,   713,     4,     3,     8,   339,   341,     4,
     345,     4,     4,     4,     4,     3,     8,   461,   463,   465,
     532,   459,   467,     4,   469,   471,   582,     3,     8,   542,
       4,     3,     8,   580,   566,   568,   570,   574,   572,   578,
     576,     8,     3,     8,   501,   383,     4,   505,   503,   508,
       4,     8,     3,   523,     4,     4,     4,   530,     8,     3,
     435,   437,     3,     8,     4,   668,     4,   671,     4,     4,
     675,   678,     3,     8,   686,     4,     3,     8,   254,   254,
     235,     4,     4,     4,     4,   238,   238,   238,     4,     4,
       4,   236,   238,     4,     4,     4,   236,   236,   236,   236,
     236,   238,   237,   237,   237,   236,   237,   236,     4,   236,
     236,   238,   238,   238,     4,     4,     4,     4,   238,   238,
     237,   236,   236,   236,   238,     4,     4,     4,   236,     4,
       4,     4,     4,     4,   238,   238,   238,     4,     4,     4,
       4,     4,   236,     4,     4,     4,     4,     4,     4,   238,
     238,   238,     4,     4,   278,     4,     4,   238,     4,   238,
     238,   236,   236,   335,     4,     4,     4,     4,     4,     4,
     236,     4,     4,     4,   457,     4,   236,   540,     4,     4,
       4,     4,     4,     4,     4,     4,   558,     4,     4,   236,
       4,     4,     4,   238,   496,     4,   238,   238,   238,     4,
     520,     4,     4,   433,   238,     4,   236,     4,   236,   236,
       4,     4,   665,     4,   236,   684,     4,     7,     7,     7,
       7,   235,   235,   235,     7,     7,     5,   235,   199,   200,
     201,   202,   238,   304,   235,   235,   235,     5,     5,     5,
     235,   119,   120,   121,   122,   315,     5,   256,   258,   235,
       5,     5,     5,     5,     7,     7,     5,     7,     7,   235,
     235,     5,     7,     5,   265,    17,    18,   342,    21,    22,
     346,   235,   235,   235,     5,   235,   235,   265,   265,     7,
     235,   265,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   265,   235,   258,   235,   235,
      18,   197,   676,   198,     5,   254,   277,   683,   334,    28,
      29,   355,   356,   357,   359,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,   180,   269,   369,   370,   371,   373,   375,   377,
     379,   381,   382,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   396,   397,   398,   400,   402,   404,   406,
     369,     7,   365,   366,   367,     7,   450,   451,   452,     7,
     488,   489,   490,     7,   512,   513,   514,     7,   478,   479,
     480,   143,   144,   145,   146,   148,   410,   411,   412,   413,
     414,   415,   416,     7,   588,   589,   590,     7,   550,   551,
     552,     7,   426,   427,   428,   155,   156,   157,   158,   159,
     160,   440,   441,   442,   443,   444,   445,   446,   447,   163,
     164,   165,   269,   419,   420,   421,   422,   423,   544,   546,
       7,   604,   605,   606,   185,   186,   187,   235,   544,   546,
     652,   653,   654,   655,   657,   658,   664,     7,   690,   691,
     218,   219,   220,   221,   269,   714,   715,   716,   717,   718,
     719,   266,     7,   533,   534,   535,   150,   583,   584,   365,
       8,     8,     8,   358,   360,     3,     8,   372,   374,   376,
     380,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   394,     4,     4,   399,   401,   403,   405,   407,   378,
       3,     8,     8,   368,     6,     3,   453,     6,     3,   491,
       6,     3,   515,     6,     3,   481,     6,     3,     3,     6,
     591,     6,     3,   553,     6,     3,   429,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   607,     6,     3,     4,   656,     4,   659,     3,
       8,     8,   692,     3,     6,     4,     4,     4,     4,     3,
       8,   235,   267,   268,   536,     6,     3,   585,     8,     6,
       4,     4,   356,     4,     4,     4,     4,   236,   238,   236,
     238,   236,   236,   236,   236,   236,   236,     4,   238,   236,
       4,     4,     4,     4,     4,     4,   370,   369,   367,   456,
     452,   494,   490,   518,   514,   269,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   294,   297,   298,
     299,   300,   301,   302,   305,   307,   309,   311,   312,   313,
     316,   317,   318,   319,   320,   322,   324,   330,   382,   448,
     466,   468,   470,   472,   473,   474,   482,   483,   510,   544,
     546,   559,   561,   563,   581,   480,   411,   137,   138,   139,
     269,   279,   280,   281,   330,   382,   484,   510,   544,   546,
     559,   561,   563,   592,   593,   594,   595,   596,   598,   600,
     590,   556,   552,   432,   428,   236,   236,   236,   236,   236,
     236,   441,   238,   236,   236,   420,   167,   171,   172,   173,
     174,   181,   182,   269,   398,   400,   402,   544,   546,   608,
     609,   610,   613,   615,   617,   618,   619,   629,   606,   238,
       4,   236,     4,   653,   209,   211,   212,   269,   382,   544,
     546,   693,   694,   695,   696,   698,   691,   238,   238,   238,
     238,   715,     6,     3,   539,   535,     4,   235,   235,   235,
     235,   235,   235,    56,    57,    58,   395,   235,   235,   235,
     404,   235,   235,     8,     8,     8,     8,     3,     8,   597,
     599,     4,     8,     3,     8,     8,   611,   614,   616,     4,
     630,     4,   620,     3,     8,   235,   254,   699,     4,   697,
       3,     8,   235,     8,   265,   483,     4,     4,   238,   594,
       4,     4,     4,   236,     4,   238,     4,   609,     4,   236,
       4,   694,   235,   235,   168,   169,   170,   612,   235,   235,
       7,     5,     5,   235,    41,   176,   177,   178,   269,   544,
     546,   631,   632,   633,   636,   638,   640,     7,   621,   622,
     623,     7,   700,   701,   634,   637,   639,   641,     3,     8,
     624,     6,     3,   702,     3,     6,     4,     4,     4,     4,
     632,   183,   269,   382,   544,   546,   625,   626,   627,   623,
     210,   213,   214,   215,   216,   703,   704,   705,   707,   708,
     709,   710,   701,   175,   635,   235,   235,     5,   628,     3,
       8,   706,     4,     4,     4,   711,     3,     8,     7,   642,
     643,   644,     4,   626,     4,   238,   236,   236,     4,   704,
     645,     6,     3,   235,   235,   235,   179,   269,   373,   375,
     377,   544,   546,   646,   647,   648,   644,   649,     3,     8,
       4,   647,   235
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   239,   241,   240,   242,   240,   243,   240,   244,   240,
     245,   240,   246,   240,   247,   240,   248,   240,   249,   240,
     250,   240,   251,   240,   252,   240,   253,   240,   254,   254,
     254,   254,   254,   254,   254,   255,   257,   256,   258,   259,
     259,   260,   260,   260,   262,   261,   263,   263,   264,   264,
     264,   266,   265,   267,   267,   268,   268,   268,   269,   271,
     270,   273,   272,   272,   274,   276,   275,   277,   277,   277,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   292,   291,   293,   295,   294,
     296,   297,   298,   299,   300,   301,   303,   302,   304,   304,
     304,   304,   304,   306,   305,   308,   307,   310,   309,   311,
     312,   314,   313,   315,   315,   315,   315,   316,   317,   318,
     319,   321,   320,   323,   322,   324,   325,   326,   327,   328,
     329,   330,   331,   333,   332,   334,   334,   334,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   337,
     336,   339,   338,   341,   340,   342,   342,   343,   345,   344,
     346,   346,   347,   348,   349,   350,   352,   351,   354,   353,
     355,   355,   355,   356,   356,   358,   357,   360,   359,   362,
     361,   364,   363,   365,   365,   366,   366,   366,   368,   367,
     369,   369,   369,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   372,   371,
     374,   373,   376,   375,   378,   377,   380,   379,   381,   383,
     382,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     394,   393,   395,   395,   395,   396,   397,   399,   398,   401,
     400,   403,   402,   405,   404,   404,   404,   404,   404,   404,
     407,   406,   409,   408,   410,   410,   410,   411,   411,   411,
     411,   411,   412,   413,   414,   415,   416,   418,   417,   419,
     419,   419,   420,   420,   420,   420,   420,   420,   421,   422,
     423,   425,   424,   426,   426,   427,   427,   427,   429,   428,
     431,   430,   432,   432,   432,   432,   433,   433,   435,   434,
     437,   436,   439,   438,   440,   440,   440,   441,   441,   441,
     441,   441,   441,   442,   443,   444,   445,   446,   447,   449,
     448,   450,   450,   451,   451,   451,   453,   452,   455,   454,
     456,   456,   456,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   459,   458,   461,   460,
     463,   462,   465,   464,   467,   466,   469,   468,   471,   470,
     472,   473,   474,   475,   477,   476,   478,   478,   479,   479,
     479,   481,   480,   482,   482,   482,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   485,   484,   487,   486,   488,   488,
     489,   489,   489,   491,   490,   493,   492,   494,   494,   495,
     495,   495,   496,   496,   496,   496,   496,   496,   496,   496,
     496,   496,   497,   498,   499,   501,   500,   503,   502,   505,
     504,   506,   508,   507,   509,   511,   510,   512,   512,   513,
     513,   513,   515,   514,   517,   516,   518,   518,   519,   519,
     519,   520,   520,   520,   520,   520,   520,   520,   520,   520,
     520,   520,   521,   523,   522,   524,   525,   526,   527,   528,
     530,   529,   532,   531,   533,   533,   534,   534,   534,   536,
     535,   538,   537,   539,   539,   539,   540,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   542,
     541,   543,   545,   544,   547,   546,   549,   548,   550,   550,
     551,   551,   551,   553,   552,   555,   554,   556,   556,   557,
     557,   557,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   560,   559,   562,
     561,   564,   563,   566,   565,   568,   567,   570,   569,   572,
     571,   574,   573,   576,   575,   578,   577,   580,   579,   582,
     581,   583,   585,   584,   587,   586,   588,   588,   589,   589,
     589,   591,   590,   592,   592,   593,   593,   593,   594,   594,
     594,   594,   594,   594,   594,   594,   594,   594,   594,   594,
     594,   594,   594,   594,   595,   597,   596,   599,   598,   600,
     601,   603,   602,   604,   604,   605,   605,   605,   607,   606,
     608,   608,   608,   609,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   609,   609,   609,   611,   610,   612,   612,
     612,   614,   613,   616,   615,   617,   618,   620,   619,   621,
     621,   622,   622,   622,   624,   623,   625,   625,   625,   626,
     626,   626,   626,   626,   628,   627,   630,   629,   631,   631,
     631,   632,   632,   632,   632,   632,   632,   632,   634,   633,
     635,   637,   636,   639,   638,   641,   640,   642,   642,   643,
     643,   643,   645,   644,   646,   646,   646,   647,   647,   647,
     647,   647,   647,   647,   649,   648,   651,   650,   652,   652,
     652,   653,   653,   653,   653,   653,   653,   654,   656,   655,
     657,   659,   658,   661,   660,   663,   662,   664,   664,   664,
     665,   665,   665,   665,   665,   665,   665,   665,   665,   665,
     665,   666,   668,   667,   669,   671,   670,   672,   673,   675,
     674,   676,   676,   678,   677,   680,   679,   682,   681,   683,
     683,   683,   684,   684,   686,   685,   687,   689,   688,   690,
     690,   690,   692,   691,   693,   693,   693,   694,   694,   694,
     694,   694,   694,   694,   695,   697,   696,   699,   698,   700,
     700,   700,   702,   701,   703,   703,   703,   704,   704,   704,
     704,   704,   706,   705,   707,   708,   709,   711,   710,   713,
     712,   714,   714,   714,   715,   715,   715,   715,   715,   716,
     717,   718,   719
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     3,     0,     4,
       1,     1,     3,     3,     3,     3,     0,     6,     0,     6,
       1,     3,     2,     1,     1,     0,     4,     0,     4,     0,
       6,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
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
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"use-fallbacks\"",
  "\"outbound-interface\"", "\"same-as-inbound\"", "\"use-routing\"",
  "\"re-detect\"", "\"service-sockets-require-all\"",
  "\"service-sockets-retry-wait-time\"", "\"service-sockets-max-retries\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"extended-info-checks\"",
  "\"echo-client-id\"", "\"match-client-id\"", "\"authoritative\"",
  "\"next-server\"", "\"server-hostname\"", "\"boot-file-name\"",
  "\"offer-lifetime\"", "\"stash-agent-options\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"retry-on-startup\"", "\"max-row-errors\"",
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"ssl-mode\"",
  "\"disable\"", "\"prefer\"", "\"require\"", "\"verify-ca\"",
  "\"verify-full\"", "\"cipher-list\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
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
  "$@31", "dhcp_socket_type", "$@32", "socket_type", "use_fallbacks",
  "outbound_interface", "$@33", "outbound_interface_value", "re_detect",
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
       0,   335,   335,   335,   336,   336,   337,   337,   338,   338,
     339,   339,   340,   340,   341,   341,   342,   342,   343,   343,
     344,   344,   345,   345,   346,   346,   347,   347,   355,   356,
     357,   358,   359,   360,   361,   364,   369,   369,   380,   383,
     384,   387,   392,   398,   403,   403,   410,   411,   414,   418,
     422,   428,   428,   435,   436,   439,   443,   447,   457,   466,
     466,   481,   481,   495,   498,   504,   504,   513,   514,   515,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   597,   603,   609,   615,   621,   627,   633,
     639,   645,   651,   657,   663,   669,   669,   678,   684,   684,
     693,   699,   705,   711,   717,   723,   729,   729,   738,   741,
     744,   747,   750,   756,   756,   765,   765,   774,   774,   783,
     792,   802,   802,   811,   814,   817,   820,   825,   831,   837,
     843,   849,   849,   858,   858,   867,   873,   879,   885,   891,
     897,   903,   909,   915,   915,   927,   928,   929,   934,   935,
     936,   937,   938,   939,   940,   941,   942,   943,   944,   947,
     947,   956,   956,   967,   967,   975,   976,   979,   985,   985,
     993,   995,   999,  1005,  1011,  1017,  1023,  1023,  1036,  1036,
    1047,  1048,  1049,  1054,  1055,  1058,  1058,  1077,  1077,  1095,
    1095,  1108,  1108,  1119,  1120,  1123,  1124,  1125,  1130,  1130,
    1140,  1141,  1142,  1147,  1148,  1149,  1150,  1151,  1152,  1153,
    1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,  1163,
    1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1174,  1174,
    1183,  1183,  1192,  1192,  1201,  1201,  1210,  1210,  1219,  1225,
    1225,  1234,  1240,  1246,  1252,  1258,  1264,  1270,  1276,  1282,
    1288,  1288,  1296,  1297,  1298,  1301,  1307,  1313,  1313,  1322,
    1322,  1331,  1331,  1340,  1340,  1348,  1351,  1354,  1357,  1360,
    1365,  1365,  1374,  1374,  1385,  1386,  1387,  1392,  1393,  1394,
    1395,  1396,  1399,  1404,  1409,  1414,  1419,  1426,  1426,  1439,
    1440,  1441,  1446,  1447,  1448,  1449,  1450,  1451,  1454,  1460,
    1466,  1472,  1472,  1483,  1484,  1487,  1488,  1489,  1494,  1494,
    1504,  1504,  1514,  1515,  1516,  1519,  1522,  1523,  1526,  1526,
    1535,  1535,  1544,  1544,  1556,  1557,  1558,  1563,  1564,  1565,
    1566,  1567,  1568,  1571,  1577,  1583,  1589,  1595,  1601,  1610,
    1610,  1624,  1625,  1628,  1629,  1630,  1639,  1639,  1665,  1665,
    1676,  1677,  1678,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,
    1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,
    1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,
    1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,
    1731,  1732,  1733,  1734,  1735,  1736,  1739,  1739,  1748,  1748,
    1757,  1757,  1766,  1766,  1775,  1775,  1785,  1785,  1796,  1796,
    1807,  1813,  1819,  1825,  1833,  1833,  1845,  1846,  1850,  1851,
    1852,  1857,  1857,  1865,  1866,  1867,  1872,  1873,  1874,  1875,
    1876,  1877,  1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,
    1886,  1887,  1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,
    1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,
    1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,
    1916,  1917,  1918,  1919,  1926,  1926,  1940,  1940,  1949,  1950,
    1953,  1954,  1955,  1962,  1962,  1977,  1977,  1991,  1992,  1995,
    1996,  1997,  2002,  2003,  2004,  2005,  2006,  2007,  2008,  2009,
    2010,  2011,  2014,  2016,  2022,  2024,  2024,  2033,  2033,  2042,
    2042,  2051,  2053,  2053,  2062,  2072,  2072,  2085,  2086,  2091,
    2092,  2093,  2100,  2100,  2112,  2112,  2124,  2125,  2130,  2131,
    2132,  2139,  2140,  2141,  2142,  2143,  2144,  2145,  2146,  2147,
    2148,  2149,  2152,  2154,  2154,  2163,  2165,  2167,  2173,  2179,
    2185,  2185,  2199,  2199,  2212,  2213,  2216,  2217,  2218,  2223,
    2223,  2233,  2233,  2243,  2244,  2245,  2250,  2251,  2252,  2253,
    2254,  2255,  2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,
    2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,  2272,  2275,
    2275,  2284,  2290,  2290,  2315,  2315,  2345,  2345,  2356,  2357,
    2360,  2361,  2362,  2367,  2367,  2376,  2376,  2385,  2386,  2389,
    2390,  2391,  2397,  2398,  2399,  2400,  2401,  2402,  2403,  2404,
    2405,  2406,  2407,  2408,  2409,  2410,  2411,  2414,  2414,  2423,
    2423,  2432,  2432,  2441,  2441,  2450,  2450,  2459,  2459,  2468,
    2468,  2477,  2477,  2486,  2486,  2495,  2495,  2504,  2504,  2518,
    2518,  2529,  2532,  2532,  2546,  2546,  2557,  2558,  2561,  2562,
    2563,  2568,  2568,  2578,  2579,  2582,  2583,  2584,  2589,  2590,
    2591,  2592,  2593,  2594,  2595,  2596,  2597,  2598,  2599,  2600,
    2601,  2602,  2603,  2604,  2607,  2609,  2609,  2618,  2618,  2627,
    2635,  2643,  2643,  2654,  2655,  2658,  2659,  2660,  2665,  2665,
    2673,  2674,  2675,  2680,  2681,  2682,  2683,  2684,  2685,  2686,
    2687,  2688,  2689,  2690,  2691,  2692,  2695,  2695,  2704,  2705,
    2706,  2709,  2709,  2718,  2718,  2727,  2733,  2739,  2739,  2750,
    2751,  2754,  2755,  2756,  2761,  2761,  2769,  2770,  2771,  2776,
    2777,  2778,  2779,  2780,  2783,  2783,  2794,  2794,  2807,  2808,
    2809,  2814,  2815,  2816,  2817,  2818,  2819,  2820,  2823,  2823,
    2831,  2834,  2834,  2843,  2843,  2852,  2852,  2863,  2864,  2867,
    2868,  2869,  2874,  2874,  2882,  2883,  2884,  2889,  2890,  2891,
    2892,  2893,  2894,  2895,  2898,  2898,  2909,  2909,  2922,  2923,
    2924,  2929,  2930,  2931,  2932,  2933,  2934,  2937,  2943,  2943,
    2952,  2958,  2958,  2968,  2968,  2981,  2981,  2991,  2992,  2993,
    2998,  2999,  3000,  3001,  3002,  3003,  3004,  3005,  3006,  3007,
    3008,  3011,  3017,  3017,  3026,  3032,  3032,  3041,  3047,  3053,
    3053,  3062,  3063,  3066,  3066,  3077,  3077,  3089,  3089,  3099,
    3100,  3101,  3107,  3108,  3111,  3111,  3122,  3130,  3130,  3143,
    3144,  3145,  3151,  3151,  3159,  3160,  3161,  3166,  3167,  3168,
    3169,  3170,  3171,  3172,  3175,  3181,  3181,  3190,  3190,  3201,
    3202,  3203,  3208,  3208,  3216,  3217,  3218,  3223,  3224,  3225,
    3226,  3227,  3230,  3230,  3239,  3245,  3251,  3257,  3257,  3266,
    3266,  3277,  3278,  3279,  3284,  3285,  3286,  3287,  3288,  3291,
    3297,  3303,  3309
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
#line 6964 "dhcp4_parser.cc"

#line 3315 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
