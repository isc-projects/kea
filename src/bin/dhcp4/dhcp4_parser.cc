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
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 421 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 427 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 433 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 439 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 481 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 487 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 493 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 328 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 499 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 328 "dhcp4_parser.yy"
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
#line 337 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 788 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 338 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 794 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 339 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 800 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 340 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 806 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 341 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 812 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 342 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 818 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 343 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 824 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 344 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 830 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 345 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 836 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 346 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 842 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 347 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 848 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 348 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 854 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 349 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 860 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 357 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 358 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 359 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 360 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 361 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 890 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 362 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 363 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 902 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 366 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 911 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 371 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 376 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 932 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 382 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 938 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 389 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 394 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 959 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 400 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 967 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 405 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 976 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 408 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 984 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 416 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 993 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 420 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1002 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 424 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1010 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 430 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1018 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 432 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1027 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 441 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1036 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 445 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1045 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 449 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1053 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 459 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 468 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 473 "dhcp4_parser.yy"
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
#line 483 "dhcp4_parser.yy"
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
#line 492 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 500 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 506 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 510 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 517 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1148 "dhcp4_parser.cc"
    break;

  case 143: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 599 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1158 "dhcp4_parser.cc"
    break;

  case 144: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 605 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 145: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 611 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1178 "dhcp4_parser.cc"
    break;

  case 146: // renew_timer: "renew-timer" ":" "integer"
#line 617 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 147: // rebind_timer: "rebind-timer" ":" "integer"
#line 623 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 148: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 629 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 149: // t1_percent: "t1-percent" ":" "floating point"
#line 635 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1218 "dhcp4_parser.cc"
    break;

  case 150: // t2_percent: "t2-percent" ":" "floating point"
#line 641 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1228 "dhcp4_parser.cc"
    break;

  case 151: // cache_threshold: "cache-threshold" ":" "floating point"
#line 647 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 152: // cache_max_age: "cache-max-age" ":" "integer"
#line 653 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 153: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 659 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 154: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 665 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 155: // $@20: %empty
#line 671 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 156: // server_tag: "server-tag" $@20 ":" "constant string"
#line 674 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 157: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 680 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 158: // $@21: %empty
#line 686 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 159: // allocator: "allocator" $@21 ":" "constant string"
#line 689 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 160: // echo_client_id: "echo-client-id" ":" "boolean"
#line 695 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 161: // match_client_id: "match-client-id" ":" "boolean"
#line 701 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 162: // authoritative: "authoritative" ":" "boolean"
#line 707 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 163: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 713 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 164: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 719 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 165: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 725 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 166: // $@22: %empty
#line 731 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 734 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-present"
#line 740 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1402 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "never"
#line 743 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1410 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "always"
#line 746 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1418 "dhcp4_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "when-not-present"
#line 749 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1426 "dhcp4_parser.cc"
    break;

  case 172: // ddns_replace_client_name_value: "boolean"
#line 752 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1435 "dhcp4_parser.cc"
    break;

  case 173: // $@23: %empty
#line 758 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 174: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 761 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1454 "dhcp4_parser.cc"
    break;

  case 175: // $@24: %empty
#line 767 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 176: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 770 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 177: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 776 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1483 "dhcp4_parser.cc"
    break;

  case 178: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 785 "dhcp4_parser.yy"
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

  case 179: // $@25: %empty
#line 795 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 798 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 804 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1523 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 807 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1531 "dhcp4_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 810 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1539 "dhcp4_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 813 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1547 "dhcp4_parser.cc"
    break;

  case 185: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 818 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 186: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 824 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1567 "dhcp4_parser.cc"
    break;

  case 187: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 830 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 188: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 836 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1587 "dhcp4_parser.cc"
    break;

  case 189: // $@26: %empty
#line 842 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 190: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 845 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 191: // $@27: %empty
#line 851 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 192: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 854 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 193: // store_extended_info: "store-extended-info" ":" "boolean"
#line 860 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1635 "dhcp4_parser.cc"
    break;

  case 194: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 866 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 195: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 872 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 196: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 878 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 197: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 884 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 198: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 890 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1685 "dhcp4_parser.cc"
    break;

  case 199: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 896 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1695 "dhcp4_parser.cc"
    break;

  case 200: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 902 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1705 "dhcp4_parser.cc"
    break;

  case 201: // $@28: %empty
#line 908 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 202: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 914 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 205: // interfaces_config_params: interfaces_config_params ","
#line 922 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1735 "dhcp4_parser.cc"
    break;

  case 216: // $@29: %empty
#line 939 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 217: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 943 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1754 "dhcp4_parser.cc"
    break;

  case 218: // $@30: %empty
#line 948 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1766 "dhcp4_parser.cc"
    break;

  case 219: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 954 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1775 "dhcp4_parser.cc"
    break;

  case 220: // $@31: %empty
#line 959 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1784 "dhcp4_parser.cc"
    break;

  case 221: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 962 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc"
    break;

  case 222: // socket_type: "raw"
#line 967 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1799 "dhcp4_parser.cc"
    break;

  case 223: // socket_type: "udp"
#line 968 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1805 "dhcp4_parser.cc"
    break;

  case 224: // $@32: %empty
#line 971 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1814 "dhcp4_parser.cc"
    break;

  case 225: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 974 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1823 "dhcp4_parser.cc"
    break;

  case 226: // outbound_interface_value: "same-as-inbound"
#line 979 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1831 "dhcp4_parser.cc"
    break;

  case 227: // outbound_interface_value: "use-routing"
#line 981 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1839 "dhcp4_parser.cc"
    break;

  case 228: // re_detect: "re-detect" ":" "boolean"
#line 985 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1849 "dhcp4_parser.cc"
    break;

  case 229: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 991 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1859 "dhcp4_parser.cc"
    break;

  case 230: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 997 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 231: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1003 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 232: // $@33: %empty
#line 1009 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1891 "dhcp4_parser.cc"
    break;

  case 233: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 1015 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1902 "dhcp4_parser.cc"
    break;

  case 234: // $@34: %empty
#line 1022 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1914 "dhcp4_parser.cc"
    break;

  case 235: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 1028 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1923 "dhcp4_parser.cc"
    break;

  case 238: // sanity_checks_params: sanity_checks_params ","
#line 1035 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1931 "dhcp4_parser.cc"
    break;

  case 241: // $@35: %empty
#line 1044 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1940 "dhcp4_parser.cc"
    break;

  case 242: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1047 "dhcp4_parser.yy"
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

  case 243: // $@36: %empty
#line 1063 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp4_parser.cc"
    break;

  case 244: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1066 "dhcp4_parser.yy"
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

  case 245: // $@37: %empty
#line 1081 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 246: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1087 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 247: // $@38: %empty
#line 1094 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 2023 "dhcp4_parser.cc"
    break;

  case 248: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1100 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 253: // not_empty_database_list: not_empty_database_list ","
#line 1111 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2040 "dhcp4_parser.cc"
    break;

  case 254: // $@39: %empty
#line 1116 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 255: // database: "{" $@39 database_map_params "}"
#line 1120 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 258: // database_map_params: database_map_params ","
#line 1128 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2068 "dhcp4_parser.cc"
    break;

  case 283: // $@40: %empty
#line 1159 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 284: // database_type: "type" $@40 ":" "constant string"
#line 1162 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2087 "dhcp4_parser.cc"
    break;

  case 285: // $@41: %empty
#line 1168 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 286: // user: "user" $@41 ":" "constant string"
#line 1171 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 287: // $@42: %empty
#line 1177 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 288: // password: "password" $@42 ":" "constant string"
#line 1180 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 289: // $@43: %empty
#line 1186 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 290: // host: "host" $@43 ":" "constant string"
#line 1189 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 291: // port: "port" ":" "integer"
#line 1195 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 292: // $@44: %empty
#line 1201 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 293: // name: "name" $@44 ":" "constant string"
#line 1204 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 294: // persist: "persist" ":" "boolean"
#line 1210 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 295: // lfc_interval: "lfc-interval" ":" "integer"
#line 1216 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2193 "dhcp4_parser.cc"
    break;

  case 296: // readonly: "readonly" ":" "boolean"
#line 1222 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 297: // connect_timeout: "connect-timeout" ":" "integer"
#line 1228 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 298: // read_timeout: "read-timeout" ":" "integer"
#line 1234 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 299: // write_timeout: "write-timeout" ":" "integer"
#line 1240 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2233 "dhcp4_parser.cc"
    break;

  case 300: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1246 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2243 "dhcp4_parser.cc"
    break;

  case 301: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1252 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2253 "dhcp4_parser.cc"
    break;

  case 302: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1258 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2263 "dhcp4_parser.cc"
    break;

  case 303: // $@45: %empty
#line 1264 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 304: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1267 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 305: // on_fail_mode: "stop-retry-exit"
#line 1272 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2287 "dhcp4_parser.cc"
    break;

  case 306: // on_fail_mode: "serve-retry-exit"
#line 1273 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2293 "dhcp4_parser.cc"
    break;

  case 307: // on_fail_mode: "serve-retry-continue"
#line 1274 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2299 "dhcp4_parser.cc"
    break;

  case 308: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1277 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 309: // max_row_errors: "max-row-errors" ":" "integer"
#line 1283 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2319 "dhcp4_parser.cc"
    break;

  case 310: // $@46: %empty
#line 1289 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 311: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1292 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc"
    break;

  case 312: // $@47: %empty
#line 1298 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 313: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1301 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 314: // $@48: %empty
#line 1307 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 315: // key_file: "key-file" $@48 ":" "constant string"
#line 1310 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 316: // $@49: %empty
#line 1316 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 317: // ssl_mode: "ssl-mode" $@49 ":" ssl_mode
#line 1319 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2394 "dhcp4_parser.cc"
    break;

  case 318: // ssl_mode: "disable"
#line 1324 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2402 "dhcp4_parser.cc"
    break;

  case 319: // ssl_mode: "prefer"
#line 1327 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2410 "dhcp4_parser.cc"
    break;

  case 320: // ssl_mode: "require"
#line 1330 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2418 "dhcp4_parser.cc"
    break;

  case 321: // ssl_mode: "verify-ca"
#line 1333 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2426 "dhcp4_parser.cc"
    break;

  case 322: // ssl_mode: "verify-full"
#line 1336 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2434 "dhcp4_parser.cc"
    break;

  case 323: // $@50: %empty
#line 1341 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp4_parser.cc"
    break;

  case 324: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1344 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc"
    break;

  case 325: // $@51: %empty
#line 1350 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 326: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1356 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2474 "dhcp4_parser.cc"
    break;

  case 329: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1363 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2482 "dhcp4_parser.cc"
    break;

  case 335: // duid_id: "duid"
#line 1375 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 336: // hw_address_id: "hw-address"
#line 1380 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 337: // circuit_id: "circuit-id"
#line 1385 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2509 "dhcp4_parser.cc"
    break;

  case 338: // client_id: "client-id"
#line 1390 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 339: // flex_id: "flex-id"
#line 1395 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2527 "dhcp4_parser.cc"
    break;

  case 340: // $@52: %empty
#line 1402 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 341: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1408 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 344: // multi_threading_params: multi_threading_params ","
#line 1417 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2558 "dhcp4_parser.cc"
    break;

  case 351: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1430 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 352: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1436 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2578 "dhcp4_parser.cc"
    break;

  case 353: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1442 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 354: // $@53: %empty
#line 1448 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2600 "dhcp4_parser.cc"
    break;

  case 355: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1454 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2609 "dhcp4_parser.cc"
    break;

  case 360: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1465 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2617 "dhcp4_parser.cc"
    break;

  case 361: // $@54: %empty
#line 1470 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2627 "dhcp4_parser.cc"
    break;

  case 362: // hooks_library: "{" $@54 hooks_params "}"
#line 1474 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 363: // $@55: %empty
#line 1480 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 364: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1484 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2657 "dhcp4_parser.cc"
    break;

  case 367: // hooks_params: hooks_params ","
#line 1492 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2665 "dhcp4_parser.cc"
    break;

  case 371: // $@56: %empty
#line 1502 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp4_parser.cc"
    break;

  case 372: // library: "library" $@56 ":" "constant string"
#line 1505 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2684 "dhcp4_parser.cc"
    break;

  case 373: // $@57: %empty
#line 1511 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 374: // parameters: "parameters" $@57 ":" map_value
#line 1514 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 375: // $@58: %empty
#line 1520 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2714 "dhcp4_parser.cc"
    break;

  case 376: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1526 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc"
    break;

  case 379: // expired_leases_params: expired_leases_params ","
#line 1534 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2732 "dhcp4_parser.cc"
    break;

  case 386: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1547 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 387: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1553 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 388: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1559 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 389: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1565 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 390: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1571 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 391: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1577 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 392: // $@59: %empty
#line 1586 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 393: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1592 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc"
    break;

  case 398: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1606 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2821 "dhcp4_parser.cc"
    break;

  case 399: // $@60: %empty
#line 1615 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 400: // subnet4: "{" $@60 subnet4_params "}"
#line 1619 "dhcp4_parser.yy"
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

  case 401: // $@61: %empty
#line 1641 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2867 "dhcp4_parser.cc"
    break;

  case 402: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1645 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2877 "dhcp4_parser.cc"
    break;

  case 405: // subnet4_params: subnet4_params ","
#line 1654 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2885 "dhcp4_parser.cc"
    break;

  case 460: // $@62: %empty
#line 1716 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2894 "dhcp4_parser.cc"
    break;

  case 461: // subnet: "subnet" $@62 ":" "constant string"
#line 1719 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2904 "dhcp4_parser.cc"
    break;

  case 462: // $@63: %empty
#line 1725 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2913 "dhcp4_parser.cc"
    break;

  case 463: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1728 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 464: // $@64: %empty
#line 1734 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 465: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1737 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 466: // $@65: %empty
#line 1743 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 467: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1746 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 468: // $@66: %empty
#line 1752 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 469: // interface: "interface" $@66 ":" "constant string"
#line 1755 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 470: // $@67: %empty
#line 1761 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 471: // client_class: "client-class" $@67 ":" "constant string"
#line 1764 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 472: // $@68: %empty
#line 1771 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 473: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1777 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3020 "dhcp4_parser.cc"
    break;

  case 474: // $@69: %empty
#line 1783 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3032 "dhcp4_parser.cc"
    break;

  case 475: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1789 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3041 "dhcp4_parser.cc"
    break;

  case 476: // $@70: %empty
#line 1794 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 477: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1800 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 478: // reservations_global: "reservations-global" ":" "boolean"
#line 1805 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 479: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1811 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 480: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1817 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 481: // id: "id" ":" "integer"
#line 1823 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 482: // $@71: %empty
#line 1831 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 483: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1837 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3123 "dhcp4_parser.cc"
    break;

  case 488: // shared_networks_list: shared_networks_list ","
#line 1850 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3131 "dhcp4_parser.cc"
    break;

  case 489: // $@72: %empty
#line 1855 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3141 "dhcp4_parser.cc"
    break;

  case 490: // shared_network: "{" $@72 shared_network_params "}"
#line 1859 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 493: // shared_network_params: shared_network_params ","
#line 1865 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3157 "dhcp4_parser.cc"
    break;

  case 543: // $@73: %empty
#line 1925 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 544: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1931 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 545: // $@74: %empty
#line 1939 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 546: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1942 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3195 "dhcp4_parser.cc"
    break;

  case 551: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1954 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3203 "dhcp4_parser.cc"
    break;

  case 552: // $@75: %empty
#line 1961 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3213 "dhcp4_parser.cc"
    break;

  case 553: // option_def_entry: "{" $@75 option_def_params "}"
#line 1965 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 554: // $@76: %empty
#line 1976 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 555: // sub_option_def: "{" $@76 option_def_params "}"
#line 1980 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3247 "dhcp4_parser.cc"
    break;

  case 560: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1996 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3255 "dhcp4_parser.cc"
    break;

  case 572: // code: "code" ":" "integer"
#line 2015 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3265 "dhcp4_parser.cc"
    break;

  case 574: // $@77: %empty
#line 2023 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp4_parser.cc"
    break;

  case 575: // option_def_type: "type" $@77 ":" "constant string"
#line 2026 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 576: // $@78: %empty
#line 2032 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 577: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 2035 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 578: // $@79: %empty
#line 2041 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 579: // space: "space" $@79 ":" "constant string"
#line 2044 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 581: // $@80: %empty
#line 2052 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc"
    break;

  case 582: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2055 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 583: // option_def_array: "array" ":" "boolean"
#line 2061 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 584: // $@81: %empty
#line 2071 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 585: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2077 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3372 "dhcp4_parser.cc"
    break;

  case 590: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2092 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3380 "dhcp4_parser.cc"
    break;

  case 591: // $@82: %empty
#line 2099 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3390 "dhcp4_parser.cc"
    break;

  case 592: // option_data_entry: "{" $@82 option_data_params "}"
#line 2103 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3399 "dhcp4_parser.cc"
    break;

  case 593: // $@83: %empty
#line 2111 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3409 "dhcp4_parser.cc"
    break;

  case 594: // sub_option_data: "{" $@83 option_data_params "}"
#line 2115 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 599: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2131 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3426 "dhcp4_parser.cc"
    break;

  case 612: // $@84: %empty
#line 2153 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 613: // option_data_data: "data" $@84 ":" "constant string"
#line 2156 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3445 "dhcp4_parser.cc"
    break;

  case 616: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2166 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3455 "dhcp4_parser.cc"
    break;

  case 617: // option_data_always_send: "always-send" ":" "boolean"
#line 2172 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3465 "dhcp4_parser.cc"
    break;

  case 618: // option_data_never_send: "never-send" ":" "boolean"
#line 2178 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3475 "dhcp4_parser.cc"
    break;

  case 619: // $@85: %empty
#line 2184 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 620: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2190 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3496 "dhcp4_parser.cc"
    break;

  case 621: // $@86: %empty
#line 2198 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3508 "dhcp4_parser.cc"
    break;

  case 622: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2204 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3517 "dhcp4_parser.cc"
    break;

  case 627: // not_empty_pools_list: not_empty_pools_list ","
#line 2217 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3525 "dhcp4_parser.cc"
    break;

  case 628: // $@87: %empty
#line 2222 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 629: // pool_list_entry: "{" $@87 pool_params "}"
#line 2226 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 630: // $@88: %empty
#line 2232 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 631: // sub_pool4: "{" $@88 pool_params "}"
#line 2236 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 634: // pool_params: pool_params ","
#line 2244 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3573 "dhcp4_parser.cc"
    break;

  case 659: // $@89: %empty
#line 2275 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 660: // pool_entry: "pool" $@89 ":" "constant string"
#line 2278 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 661: // pool_id: "pool-id" ":" "integer"
#line 2284 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 662: // $@90: %empty
#line 2290 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3610 "dhcp4_parser.cc"
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
#line 3637 "dhcp4_parser.cc"
    break;

  case 664: // $@91: %empty
#line 2315 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp4_parser.cc"
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
#line 3674 "dhcp4_parser.cc"
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
#line 3686 "dhcp4_parser.cc"
    break;

  case 667: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2351 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3695 "dhcp4_parser.cc"
    break;

  case 672: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2362 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3703 "dhcp4_parser.cc"
    break;

  case 673: // $@93: %empty
#line 2367 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3713 "dhcp4_parser.cc"
    break;

  case 674: // reservation: "{" $@93 reservation_params "}"
#line 2371 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 675: // $@94: %empty
#line 2376 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 676: // sub_reservation: "{" $@94 reservation_params "}"
#line 2380 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 681: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2391 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3749 "dhcp4_parser.cc"
    break;

  case 697: // $@95: %empty
#line 2414 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 698: // next_server: "next-server" $@95 ":" "constant string"
#line 2417 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 699: // $@96: %empty
#line 2423 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 700: // server_hostname: "server-hostname" $@96 ":" "constant string"
#line 2426 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3787 "dhcp4_parser.cc"
    break;

  case 701: // $@97: %empty
#line 2432 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 702: // boot_file_name: "boot-file-name" $@97 ":" "constant string"
#line 2435 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 703: // $@98: %empty
#line 2441 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 704: // ip_address: "ip-address" $@98 ":" "constant string"
#line 2444 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 705: // $@99: %empty
#line 2450 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 706: // duid: "duid" $@99 ":" "constant string"
#line 2453 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 707: // $@100: %empty
#line 2459 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 708: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2462 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 709: // $@101: %empty
#line 2468 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 710: // client_id_value: "client-id" $@101 ":" "constant string"
#line 2471 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 711: // $@102: %empty
#line 2477 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 712: // circuit_id_value: "circuit-id" $@102 ":" "constant string"
#line 2480 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 713: // $@103: %empty
#line 2486 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 714: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2489 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3920 "dhcp4_parser.cc"
    break;

  case 715: // $@104: %empty
#line 2495 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 716: // hostname: "hostname" $@104 ":" "constant string"
#line 2498 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3939 "dhcp4_parser.cc"
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
#line 3951 "dhcp4_parser.cc"
    break;

  case 718: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2510 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3960 "dhcp4_parser.cc"
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
#line 3972 "dhcp4_parser.cc"
    break;

  case 720: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2524 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3981 "dhcp4_parser.cc"
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
#line 3993 "dhcp4_parser.cc"
    break;

  case 723: // ip_addresses: "ip-addresses" $@107 ":" list_strings
#line 2538 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4002 "dhcp4_parser.cc"
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
#line 4014 "dhcp4_parser.cc"
    break;

  case 725: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2552 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4023 "dhcp4_parser.cc"
    break;

  case 728: // client_classes_list: client_classes_list ","
#line 2559 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4031 "dhcp4_parser.cc"
    break;

  case 729: // $@109: %empty
#line 2564 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 730: // client_class_entry: "{" $@109 client_class_params "}"
#line 2568 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 735: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2580 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4059 "dhcp4_parser.cc"
    break;

  case 754: // $@110: %empty
#line 2606 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4068 "dhcp4_parser.cc"
    break;

  case 755: // client_class_test: "test" $@110 ":" "constant string"
#line 2609 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4078 "dhcp4_parser.cc"
    break;

  case 756: // $@111: %empty
#line 2615 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 757: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2618 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 758: // only_if_required: "only-if-required" ":" "boolean"
#line 2625 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4107 "dhcp4_parser.cc"
    break;

  case 759: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2631 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4117 "dhcp4_parser.cc"
    break;

  case 760: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2639 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4127 "dhcp4_parser.cc"
    break;

  case 761: // $@112: %empty
#line 2647 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4140 "dhcp4_parser.cc"
    break;

  case 762: // control_socket: "control-socket" $@112 ":" "{" control_socket_params "}"
#line 2654 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4149 "dhcp4_parser.cc"
    break;

  case 763: // $@113: %empty
#line 2659 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4162 "dhcp4_parser.cc"
    break;

  case 764: // control_sockets: "control-sockets" $@113 ":" "[" control_socket_list "]"
#line 2666 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 769: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2677 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4179 "dhcp4_parser.cc"
    break;

  case 770: // $@114: %empty
#line 2682 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4189 "dhcp4_parser.cc"
    break;

  case 771: // control_socket_entry: "{" $@114 control_socket_params "}"
#line 2686 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 774: // control_socket_params: control_socket_params ","
#line 2692 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4205 "dhcp4_parser.cc"
    break;

  case 788: // $@115: %empty
#line 2712 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4214 "dhcp4_parser.cc"
    break;

  case 789: // control_socket_type: "socket-type" $@115 ":" control_socket_type_value
#line 2715 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4223 "dhcp4_parser.cc"
    break;

  case 790: // control_socket_type_value: "unix"
#line 2721 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4229 "dhcp4_parser.cc"
    break;

  case 791: // control_socket_type_value: "http"
#line 2722 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4235 "dhcp4_parser.cc"
    break;

  case 792: // control_socket_type_value: "https"
#line 2723 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4241 "dhcp4_parser.cc"
    break;

  case 793: // $@116: %empty
#line 2726 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4251 "dhcp4_parser.cc"
    break;

  case 794: // control_socket_name: "socket-name" $@116 ":" "constant string"
#line 2730 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4261 "dhcp4_parser.cc"
    break;

  case 795: // $@117: %empty
#line 2736 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4271 "dhcp4_parser.cc"
    break;

  case 796: // control_socket_address: "socket-address" $@117 ":" "constant string"
#line 2740 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4281 "dhcp4_parser.cc"
    break;

  case 797: // control_socket_port: "socket-port" ":" "integer"
#line 2746 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4291 "dhcp4_parser.cc"
    break;

  case 798: // cert_required: "cert-required" ":" "boolean"
#line 2752 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4301 "dhcp4_parser.cc"
    break;

  case 799: // $@118: %empty
#line 2758 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4313 "dhcp4_parser.cc"
    break;

  case 800: // http_headers: "http-headers" $@118 ":" "[" http_header_list "]"
#line 2764 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4322 "dhcp4_parser.cc"
    break;

  case 805: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2775 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4330 "dhcp4_parser.cc"
    break;

  case 806: // $@119: %empty
#line 2780 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4340 "dhcp4_parser.cc"
    break;

  case 807: // http_header: "{" $@119 http_header_params "}"
#line 2784 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4348 "dhcp4_parser.cc"
    break;

  case 810: // http_header_params: http_header_params ","
#line 2790 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4356 "dhcp4_parser.cc"
    break;

  case 816: // $@120: %empty
#line 2802 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4365 "dhcp4_parser.cc"
    break;

  case 817: // header_value: "value" $@120 ":" "constant string"
#line 2805 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4375 "dhcp4_parser.cc"
    break;

  case 818: // $@121: %empty
#line 2813 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4387 "dhcp4_parser.cc"
    break;

  case 819: // authentication: "authentication" $@121 ":" "{" auth_params "}"
#line 2819 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 822: // auth_params: auth_params ","
#line 2828 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4406 "dhcp4_parser.cc"
    break;

  case 830: // $@122: %empty
#line 2842 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4415 "dhcp4_parser.cc"
    break;

  case 831: // auth_type: "type" $@122 ":" auth_type_value
#line 2845 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4424 "dhcp4_parser.cc"
    break;

  case 832: // auth_type_value: "basic"
#line 2850 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4430 "dhcp4_parser.cc"
    break;

  case 833: // $@123: %empty
#line 2853 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4439 "dhcp4_parser.cc"
    break;

  case 834: // realm: "realm" $@123 ":" "constant string"
#line 2856 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4449 "dhcp4_parser.cc"
    break;

  case 835: // $@124: %empty
#line 2862 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4458 "dhcp4_parser.cc"
    break;

  case 836: // directory: "directory" $@124 ":" "constant string"
#line 2865 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4468 "dhcp4_parser.cc"
    break;

  case 837: // $@125: %empty
#line 2871 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4480 "dhcp4_parser.cc"
    break;

  case 838: // clients: "clients" $@125 ":" "[" clients_list "]"
#line 2877 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4489 "dhcp4_parser.cc"
    break;

  case 843: // not_empty_clients_list: not_empty_clients_list ","
#line 2888 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4497 "dhcp4_parser.cc"
    break;

  case 844: // $@126: %empty
#line 2893 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4507 "dhcp4_parser.cc"
    break;

  case 845: // basic_auth: "{" $@126 clients_params "}"
#line 2897 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4515 "dhcp4_parser.cc"
    break;

  case 848: // clients_params: clients_params ","
#line 2903 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4523 "dhcp4_parser.cc"
    break;

  case 856: // $@127: %empty
#line 2917 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 857: // user_file: "user-file" $@127 ":" "constant string"
#line 2920 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 858: // $@128: %empty
#line 2926 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4551 "dhcp4_parser.cc"
    break;

  case 859: // password_file: "password-file" $@128 ":" "constant string"
#line 2929 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 860: // $@129: %empty
#line 2937 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4573 "dhcp4_parser.cc"
    break;

  case 861: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2943 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4584 "dhcp4_parser.cc"
    break;

  case 864: // queue_control_params: queue_control_params ","
#line 2952 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4592 "dhcp4_parser.cc"
    break;

  case 871: // enable_queue: "enable-queue" ":" "boolean"
#line 2965 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4602 "dhcp4_parser.cc"
    break;

  case 872: // $@130: %empty
#line 2971 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4611 "dhcp4_parser.cc"
    break;

  case 873: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2974 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4621 "dhcp4_parser.cc"
    break;

  case 874: // capacity: "capacity" ":" "integer"
#line 2980 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4631 "dhcp4_parser.cc"
    break;

  case 875: // $@131: %empty
#line 2986 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4640 "dhcp4_parser.cc"
    break;

  case 876: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2989 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4649 "dhcp4_parser.cc"
    break;

  case 877: // $@132: %empty
#line 2996 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4661 "dhcp4_parser.cc"
    break;

  case 878: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 3002 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4672 "dhcp4_parser.cc"
    break;

  case 879: // $@133: %empty
#line 3009 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4682 "dhcp4_parser.cc"
    break;

  case 880: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 3013 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4692 "dhcp4_parser.cc"
    break;

  case 883: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3021 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4700 "dhcp4_parser.cc"
    break;

  case 895: // enable_updates: "enable-updates" ":" "boolean"
#line 3039 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4710 "dhcp4_parser.cc"
    break;

  case 896: // $@134: %empty
#line 3045 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4719 "dhcp4_parser.cc"
    break;

  case 897: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3048 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4729 "dhcp4_parser.cc"
    break;

  case 898: // server_port: "server-port" ":" "integer"
#line 3054 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4739 "dhcp4_parser.cc"
    break;

  case 899: // $@135: %empty
#line 3060 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4748 "dhcp4_parser.cc"
    break;

  case 900: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3063 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4758 "dhcp4_parser.cc"
    break;

  case 901: // sender_port: "sender-port" ":" "integer"
#line 3069 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4768 "dhcp4_parser.cc"
    break;

  case 902: // max_queue_size: "max-queue-size" ":" "integer"
#line 3075 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4778 "dhcp4_parser.cc"
    break;

  case 903: // $@136: %empty
#line 3081 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4787 "dhcp4_parser.cc"
    break;

  case 904: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3084 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4796 "dhcp4_parser.cc"
    break;

  case 905: // ncr_protocol_value: "udp"
#line 3090 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4802 "dhcp4_parser.cc"
    break;

  case 906: // ncr_protocol_value: "tcp"
#line 3091 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4808 "dhcp4_parser.cc"
    break;

  case 907: // $@137: %empty
#line 3094 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4817 "dhcp4_parser.cc"
    break;

  case 908: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3097 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4827 "dhcp4_parser.cc"
    break;

  case 909: // $@138: %empty
#line 3105 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4839 "dhcp4_parser.cc"
    break;

  case 910: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3111 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4849 "dhcp4_parser.cc"
    break;

  case 911: // $@139: %empty
#line 3117 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4859 "dhcp4_parser.cc"
    break;

  case 912: // sub_config_control: "{" $@139 config_control_params "}"
#line 3121 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4868 "dhcp4_parser.cc"
    break;

  case 915: // config_control_params: config_control_params ","
#line 3129 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4876 "dhcp4_parser.cc"
    break;

  case 918: // $@140: %empty
#line 3139 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4888 "dhcp4_parser.cc"
    break;

  case 919: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3145 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4897 "dhcp4_parser.cc"
    break;

  case 920: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3150 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4907 "dhcp4_parser.cc"
    break;

  case 921: // $@141: %empty
#line 3158 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4919 "dhcp4_parser.cc"
    break;

  case 922: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3164 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4928 "dhcp4_parser.cc"
    break;

  case 925: // loggers_entries: loggers_entries ","
#line 3173 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4936 "dhcp4_parser.cc"
    break;

  case 926: // $@142: %empty
#line 3179 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4946 "dhcp4_parser.cc"
    break;

  case 927: // logger_entry: "{" $@142 logger_params "}"
#line 3183 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4954 "dhcp4_parser.cc"
    break;

  case 930: // logger_params: logger_params ","
#line 3189 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4962 "dhcp4_parser.cc"
    break;

  case 938: // debuglevel: "debuglevel" ":" "integer"
#line 3203 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4972 "dhcp4_parser.cc"
    break;

  case 939: // $@143: %empty
#line 3209 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4981 "dhcp4_parser.cc"
    break;

  case 940: // severity: "severity" $@143 ":" "constant string"
#line 3212 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4991 "dhcp4_parser.cc"
    break;

  case 941: // $@144: %empty
#line 3218 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5003 "dhcp4_parser.cc"
    break;

  case 942: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3224 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5012 "dhcp4_parser.cc"
    break;

  case 945: // output_options_list_content: output_options_list_content ","
#line 3231 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5020 "dhcp4_parser.cc"
    break;

  case 946: // $@145: %empty
#line 3236 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5030 "dhcp4_parser.cc"
    break;

  case 947: // output_entry: "{" $@145 output_params_list "}"
#line 3240 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5038 "dhcp4_parser.cc"
    break;

  case 950: // output_params_list: output_params_list ","
#line 3246 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5046 "dhcp4_parser.cc"
    break;

  case 956: // $@146: %empty
#line 3258 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5055 "dhcp4_parser.cc"
    break;

  case 957: // output: "output" $@146 ":" "constant string"
#line 3261 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5065 "dhcp4_parser.cc"
    break;

  case 958: // flush: "flush" ":" "boolean"
#line 3267 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5075 "dhcp4_parser.cc"
    break;

  case 959: // maxsize: "maxsize" ":" "integer"
#line 3273 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5085 "dhcp4_parser.cc"
    break;

  case 960: // maxver: "maxver" ":" "integer"
#line 3279 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5095 "dhcp4_parser.cc"
    break;

  case 961: // $@147: %empty
#line 3285 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5104 "dhcp4_parser.cc"
    break;

  case 962: // pattern: "pattern" $@147 ":" "constant string"
#line 3288 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5114 "dhcp4_parser.cc"
    break;

  case 963: // $@148: %empty
#line 3294 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5126 "dhcp4_parser.cc"
    break;

  case 964: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3300 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5135 "dhcp4_parser.cc"
    break;

  case 967: // compatibility_params: compatibility_params ","
#line 3307 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5143 "dhcp4_parser.cc"
    break;

  case 973: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3319 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5153 "dhcp4_parser.cc"
    break;

  case 974: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3325 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5163 "dhcp4_parser.cc"
    break;

  case 975: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3331 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5173 "dhcp4_parser.cc"
    break;

  case 976: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3337 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5183 "dhcp4_parser.cc"
    break;


#line 5187 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1384;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     468, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,    80,    37,    44,    46,   109,   117,
     120,   150,   161,   168,   176,   195,   213,   223, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,    37,  -150,    85,   276,    82,   727,
    1476,    98,    -3,   343,    88,  -118,   544,    96, -1384,   180,
     254,   114,   256,   262, -1384,    25, -1384, -1384, -1384, -1384,
     275,   296,   299, -1384, -1384, -1384,   300,   330, -1384, -1384,
   -1384,   332,   341,   376,   382,   408,   409,   430,   438,   442,
     444,   447,   448, -1384,   449,   453,   454,   455,   456, -1384,
   -1384, -1384,   457,   459,   460,   461,   465,   467,   469, -1384,
   -1384, -1384,   470, -1384, -1384, -1384, -1384, -1384,   471,   472,
     473, -1384, -1384, -1384, -1384, -1384,   474, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   476,   483,   484, -1384, -1384,   485,
   -1384,    62, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   486,   487,
     488,   490, -1384,   134, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
     492, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   144, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384,   494, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   151, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384,   277,   294, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,   325, -1384, -1384,   497,
   -1384, -1384, -1384,   499, -1384, -1384,   335,   420, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384,   501,   502,   503, -1384, -1384, -1384, -1384, -1384,   425,
     506, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384,   169, -1384, -1384, -1384,   507,
   -1384,   510, -1384,   511,   513, -1384, -1384, -1384, -1384, -1384,
     177, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384,   515,   179, -1384, -1384, -1384, -1384,    37,    37, -1384,
    -124,   517, -1384, -1384,   519,   520,   522,   270,   290,   297,
     529,   532,   535,   234,   302,   536,   540,   541,   312,   314,
     316,   317,   321,   322,   327,   331,   333,   326,   340,   336,
     567,   344,   345,   346,   347,   349,   577,   580,   581,   352,
     354,   357,   359,   360,   361,   362,   596,   600,   602,   369,
     605,   606,   610,   614,   617,   385,   387,   391,   618,   628,
     631,   633,   638,   410,   646,   649,   651,   652,   654,   662,
     667,   434,   436,   439,   669,   673, -1384,   276, -1384,   674,
     676,   677,   443,   445,   450,   451,    82, -1384,   678,   683,
     686,   701,   702,   703,   475,   704,   706,   707,   708,   710,
     727, -1384,   711,   478,  1476, -1384,   713,   714,   715,   716,
     722,   723,   724,   726, -1384,    98, -1384,   728,   729,   493,
     730,   739,   742,   509, -1384,   343,   746,   512,   514,   523,
     747, -1384,    88,   749,   751,   -85, -1384,   524,   761,   528,
     763,   531,   533,   766,   772,   544, -1384,   773,   542,    96,
   -1384, -1384, -1384,   774,   777,   778,   779,   780, -1384, -1384,
   -1384,   551,   552,   553, -1384, -1384,   786,   789,   803, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384,   572, -1384, -1384, -1384, -1384, -1384,    14,   573,   574,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384,   820,   824,   826,
   -1384,   595,   203,   828,   827,   598, -1384, -1384, -1384,   832,
     833,   834,   835,   837, -1384,   838,   839,   836,   840,   841,
     613,   622, -1384, -1384, -1384,   858,   857, -1384,   860,   123,
     228, -1384, -1384, -1384, -1384, -1384,   629,   634,   635,   863,
     636,   637, -1384,   860,   860,   860,   639,   868, -1384,   641,
   -1384, -1384,   860,   642,   643,   644,   645,   647,   648,   650,
   -1384,   653,   670, -1384,   671,   684,   685, -1384, -1384,   687,
   -1384, -1384, -1384,   860, -1384,   688,   827, -1384, -1384,   689,
   -1384,   690, -1384, -1384,     4,   579, -1384,   865, -1384, -1384,
      37,   276,    96,    82,   137, -1384, -1384, -1384,   851,   851,
     876, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
     879,   881,   882, -1384, -1384, -1384, -1384, -1384, -1384,   899,
   -1384, -1384, -1384,   106,   916,   921,   922,   170,   -75,   599,
     923,    45,   544, -1384, -1384,   924,   -12, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   927, -1384,
   -1384, -1384, -1384, -1384, -1384,   784, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
     876, -1384,   196,   197,   211, -1384, -1384,   221, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941, -1384,   942,   943, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   253,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   280, -1384,   944,   945, -1384, -1384,
     946,   948, -1384, -1384,   947,   951, -1384, -1384,   950,   954,
   -1384, -1384,   952,   956, -1384, -1384, -1384, -1384, -1384, -1384,
      42, -1384, -1384, -1384, -1384, -1384, -1384, -1384,    75, -1384,
   -1384,   955,   957, -1384, -1384,   959,   960, -1384,   958,   962,
     963,   964,   965,   966,   281, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384,   967,   968,   969, -1384,   283, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,   970, -1384,   971, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,   293, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,   972,   973, -1384,   975,
   -1384,   976, -1384, -1384, -1384,   329, -1384, -1384, -1384, -1384,
   -1384,   373, -1384,    90, -1384,   977,   978,   979,   980, -1384,
     374, -1384, -1384, -1384, -1384, -1384,   712, -1384,   981,   974,
   -1384, -1384,   982, -1384,   983, -1384, -1384, -1384,   984,   987,
     137, -1384,   988,   989,   990,   991,   748,   745,   758,   757,
     760,   762,   764,   767,   769,   770,   995,   771,   781,   997,
    1000,  1011,  1014,  1021,   851, -1384, -1384,   851, -1384,   876,
     727, -1384,   879,   343, -1384,   881,    88, -1384,   882,  1418,
   -1384,   899,   106, -1384,   156,   916, -1384,    98, -1384,   921,
    -118, -1384,   922,   790,   792,   795,   796,   807,   813,   170,
   -1384,   787,   816,   818,   -75, -1384,  1037,  1055,  1060,   829,
    1064,   849,  1070,   599, -1384,   599, -1384,   923,   856,  1087,
     859,  1094,    45, -1384, -1384,   174,   924, -1384,   864,   866,
     869,   874,   -12, -1384, -1384,  1125,  1134,  1476, -1384,   927,
    1137, -1384, -1384,   910,   915, -1384,   961,   985,   986,   992,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
     339, -1384, -1384,   993,   994,   996,   172,   998, -1384,   381,
   -1384,   407, -1384,  1161, -1384,  1171, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   411,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384,  1183,  1188, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384,  1187,  1194, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,  1191, -1384,   417, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384,   232,   999,  1001, -1384,  1193, -1384,  1197, -1384,   418,
   -1384, -1384,  1002, -1384,    37, -1384, -1384,  1200, -1384, -1384,
   -1384, -1384, -1384,   419, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384,  1003,   421, -1384,   860, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,  1418, -1384,
    1201,  1203,  1004,  1005, -1384,   156, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   138,  1202, -1384, -1384, -1384,  1204,
    1008,  1206,   174, -1384, -1384, -1384, -1384, -1384,  1006,  1010,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
     427, -1384, -1384, -1384, -1384, -1384, -1384,  1208,  1209, -1384,
    1210, -1384,  1012, -1384, -1384, -1384,  1213,  1215,  1216,  1217,
     138, -1384,   -70, -1384,  1202,  1219, -1384,  1047,  1013,  1015,
    1222, -1384, -1384, -1384, -1384, -1384, -1384,   429, -1384, -1384,
   -1384, -1384,   111, -1384, -1384, -1384, -1384, -1384,  1221,  1228,
     -70, -1384,    55,  1219, -1384, -1384,  1231,  1238, -1384,  1016,
   -1384, -1384,  1230,  1244,  1247, -1384,   433, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   375, -1384,  1221, -1384,  1250,  1017,
    1018,  1020,  1251,    55, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384,   437, -1384, -1384, -1384, -1384,  1022, -1384, -1384,
   -1384,  1023, -1384,  1258,  1259,   375, -1384, -1384, -1384,  1027,
    1029, -1384, -1384, -1384
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   216,     9,   401,    11,   630,    13,
     675,    15,   545,    17,   554,    19,   593,    21,   363,    23,
     879,    25,   911,    27,    46,    39,     0,     0,     0,     0,
       0,   677,     0,   556,   595,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   909,   201,   234,
       0,     0,     0,   697,   699,   701,     0,     0,   232,   245,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,     0,   166,
     173,   175,     0,     0,     0,     0,     0,     0,     0,   392,
     543,   584,     0,   158,   179,   482,   662,   664,     0,     0,
       0,   325,   724,   666,   354,   375,     0,   340,   761,   763,
     860,   877,   189,   191,     0,     0,     0,   921,   963,     0,
     142,     0,    67,    70,    71,    72,    73,    74,   108,   109,
     110,   111,   112,   113,    75,   104,   138,   139,    93,    94,
      95,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   115,   116,   130,   131,   132,   134,
     135,   136,   140,   141,    78,    79,   101,    80,    81,    82,
     133,    86,    87,    76,   105,   106,   107,    77,    84,    85,
      99,   100,   102,    96,    97,    98,    83,    88,    89,    90,
      91,    92,   103,   114,   137,   218,   220,   224,     0,     0,
       0,     0,   215,     0,   203,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   462,   464,   466,   621,   460,   468,
       0,   472,   474,   476,   470,   719,   459,   406,   407,   408,
     409,   410,   435,   436,   437,   438,   439,   440,   457,   425,
     426,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   458,     0,   403,
     413,   430,   431,   432,   414,   416,   417,   418,   419,   421,
     422,   423,   415,   411,   412,   433,   434,   420,   427,   428,
     429,   424,   659,     0,   658,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   638,
     639,   640,   641,   637,     0,   632,   635,   636,   656,   657,
     717,   703,   705,   707,   711,   709,   715,   713,   696,   690,
     694,   695,     0,   678,   679,   691,   692,   693,   687,   682,
     688,   684,   685,   686,   689,   683,     0,   574,   292,     0,
     578,   576,   581,     0,   570,   571,     0,   557,   558,   561,
     573,   562,   563,   564,   580,   565,   566,   567,   568,   569,
     612,     0,     0,     0,   619,   610,   611,   614,   615,     0,
     596,   597,   600,   601,   602,   603,   604,   605,   606,   609,
     607,   608,   371,   373,   368,     0,   365,   369,   370,     0,
     896,     0,   899,     0,     0,   903,   907,   894,   892,   893,
       0,   881,   884,   885,   886,   887,   888,   889,   890,   891,
     918,     0,     0,   913,   916,   917,    45,    50,     0,    37,
      43,     0,    64,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    69,    66,     0,
       0,     0,     0,     0,     0,     0,   205,   217,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     405,   402,     0,     0,   634,   631,     0,     0,     0,     0,
       0,     0,     0,     0,   676,   681,   546,     0,     0,     0,
       0,     0,     0,     0,   555,   560,     0,     0,     0,     0,
       0,   594,   599,     0,     0,   367,   364,     0,     0,     0,
       0,     0,     0,     0,     0,   883,   880,     0,     0,   915,
     912,    49,    41,     0,     0,     0,     0,     0,   160,   161,
     162,     0,     0,     0,   199,   200,     0,     0,     0,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,   194,   195,   163,   164,   165,     0,     0,     0,
     177,   178,   185,   186,   187,   188,   193,     0,     0,     0,
     157,     0,     0,     0,     0,     0,   478,   479,   480,     0,
       0,     0,     0,     0,   760,     0,     0,     0,     0,     0,
       0,     0,   196,   197,   198,     0,     0,    68,     0,     0,
       0,   228,   229,   230,   231,   204,     0,     0,     0,     0,
       0,     0,   481,     0,     0,     0,     0,     0,   404,     0,
     661,   633,     0,     0,     0,     0,     0,     0,     0,     0,
     680,     0,     0,   572,     0,     0,     0,   583,   559,     0,
     616,   617,   618,     0,   598,     0,     0,   366,   895,     0,
     898,     0,   901,   902,     0,     0,   882,     0,   920,   914,
       0,     0,     0,     0,     0,   698,   700,   702,     0,     0,
     249,   156,   168,   169,   170,   171,   172,   167,   174,   176,
     394,   547,   586,   159,   181,   182,   183,   184,   180,   484,
      38,   663,   665,     0,     0,   668,   356,     0,     0,     0,
     765,     0,     0,   190,   192,     0,     0,    51,   219,   222,
     223,   221,   226,   227,   225,   463,   465,   467,   623,   461,
     469,   473,   475,   477,   471,     0,   660,   718,   704,   706,
     708,   712,   710,   716,   714,   575,   293,   579,   577,   582,
     613,   620,   372,   374,   897,   900,   905,   906,   904,   908,
     249,    42,     0,     0,     0,   241,   243,     0,   236,   239,
     240,   283,   285,   287,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   303,     0,     0,   310,   312,
     314,   316,   318,   319,   320,   321,   322,   323,   282,     0,
     256,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,     0,   254,     0,   250,   251,   399,
       0,   395,   396,   552,     0,   548,   549,   591,     0,   587,
     588,   489,     0,   485,   486,   335,   336,   337,   338,   339,
       0,   327,   330,   331,   332,   333,   334,   729,     0,   726,
     673,     0,   669,   670,   361,     0,   357,   358,     0,     0,
       0,     0,     0,     0,     0,   377,   380,   381,   382,   383,
     384,   385,     0,     0,     0,   350,     0,   342,   345,   346,
     347,   348,   349,   788,   793,   795,     0,   818,     0,   799,
     787,   780,   781,   782,   785,   786,     0,   772,   775,   776,
     777,   778,   783,   784,   779,   770,     0,   766,   767,     0,
     872,     0,   875,   868,   869,     0,   862,   865,   866,   867,
     870,     0,   926,     0,   923,     0,     0,     0,     0,   972,
       0,   965,   968,   969,   970,   971,    53,   628,     0,   624,
     625,   722,     0,   721,     0,    62,   910,   202,     0,     0,
     238,   235,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   258,   233,   246,     0,   248,   253,
       0,   393,   398,   556,   544,   551,   595,   585,   590,     0,
     483,   488,   329,   326,   731,   728,   725,   677,   667,   672,
       0,   355,   360,     0,     0,     0,     0,     0,     0,   379,
     376,     0,     0,     0,   344,   341,     0,     0,     0,     0,
       0,     0,     0,   774,   762,     0,   764,   769,     0,     0,
       0,     0,   864,   861,   878,     0,   925,   922,     0,     0,
       0,     0,   967,   964,    55,     0,    54,     0,   622,   627,
       0,   720,   919,     0,     0,   237,     0,     0,     0,     0,
     291,   294,   295,   296,   297,   298,   299,   300,   301,   302,
       0,   308,   309,     0,     0,     0,     0,     0,   257,     0,
     252,     0,   397,     0,   550,     0,   589,   542,   513,   514,
     515,   497,   498,   518,   519,   520,   521,   522,   523,   540,
     500,   501,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   541,   494,
     495,   496,   509,   510,   511,   512,   506,   507,   508,     0,
     491,   499,   516,   517,   502,   503,   504,   505,   487,   328,
     754,   756,     0,     0,   748,   749,   750,   751,   752,   753,
     741,   742,   746,   747,   743,   744,   745,     0,   732,   733,
     736,   737,   738,   739,   740,   727,     0,   671,     0,   359,
     386,   387,   388,   389,   390,   391,   378,   351,   352,   353,
     343,     0,     0,     0,   797,     0,   798,     0,   773,     0,
     768,   871,     0,   874,     0,   863,   941,     0,   939,   937,
     931,   935,   936,     0,   928,   933,   934,   932,   924,   973,
     974,   975,   976,   966,    52,    57,     0,   626,     0,   242,
     244,   284,   286,   288,   290,   305,   306,   307,   304,   311,
     313,   315,   317,   324,   255,   400,   553,   592,   493,   490,
       0,     0,     0,     0,   730,   735,   674,   362,   790,   791,
     792,   789,   794,   796,     0,   801,   771,   873,   876,     0,
       0,     0,   930,   927,    56,   629,   723,   492,     0,     0,
     758,   759,   734,   830,   833,   835,   837,   829,   828,   827,
       0,   820,   823,   824,   825,   826,   806,     0,   802,   803,
       0,   938,     0,   929,   755,   757,     0,     0,     0,     0,
     822,   819,     0,   800,   805,     0,   940,     0,     0,     0,
       0,   821,   816,   815,   811,   813,   814,     0,   808,   812,
     804,   946,     0,   943,   832,   831,   834,   836,   839,     0,
     810,   807,     0,   945,   942,   844,     0,   840,   841,     0,
     809,   956,     0,     0,     0,   961,     0,   948,   951,   952,
     953,   954,   955,   944,     0,   838,   843,   817,     0,     0,
       0,     0,     0,   950,   947,   856,   858,   855,   849,   851,
     853,   854,     0,   846,   850,   852,   842,     0,   958,   959,
     960,     0,   949,     0,     0,   848,   845,   957,   962,     0,
       0,   847,   857,   859
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384,   -59, -1384,  -633, -1384,   534,
   -1384, -1384, -1384, -1384, -1384, -1384,  -645, -1384, -1384, -1384,
     -67, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   491,   732,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
      94, -1384, -1384, -1384, -1384,    97, -1384, -1384,   102,   104,
     -13,    13,    41,    51, -1384, -1384,    53, -1384,    56, -1384,
      59,   105,    64, -1384, -1384,    66,    69,    74,    76,    79,
   -1384,    81, -1384,   107, -1384, -1384, -1384, -1384, -1384,    43,
   -1384, -1384, -1384,   518,   721, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   233, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384,   441, -1384,   205, -1384,  -743,   212, -1384,
   -1384, -1383, -1384, -1381, -1384, -1384, -1384, -1384,   -63, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,  -775, -1384,  -774, -1384,  -771, -1384,
     113, -1384, -1384, -1384, -1384, -1384, -1384,   200, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,   182, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384,   186, -1384, -1384, -1384,   193,   693,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384,   191, -1384, -1384,
   -1384, -1384, -1384, -1384, -1062, -1384, -1384, -1384,   220, -1384,
   -1384, -1384,   224,   733, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1060, -1384,   -29, -1384,   -18, -1384,    -4, -1384,
       5, -1384,   110,   112,   115, -1384, -1384, -1384, -1384, -1384,
     214, -1384, -1384,   -31,   -60, -1384, -1384, -1384, -1384, -1384,
     226, -1384, -1384, -1384,   225, -1384,   719, -1384,   -34, -1384,
   -1384, -1384, -1384, -1384,   -27, -1384, -1384, -1384, -1384, -1384,
     -32, -1384, -1384, -1384,   227, -1384, -1384, -1384,   230, -1384,
     717, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384,   173, -1384, -1384, -1384,   181,
     743, -1384, -1384, -1384,   -44, -1384,     3, -1384,   -56, -1384,
   -1384, -1384,   222, -1384, -1384, -1384,   229, -1384,   738,   -48,
   -1384,    -7, -1384,    15, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1059, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   235,
   -1384, -1384, -1384,   -21, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   202, -1384,
     207,   204, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384,   -68, -1384, -1384,   -93, -1384,
   -1384, -1384, -1384, -1384,   -58, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384,  -116, -1384, -1384,  -141,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384,   215, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   543,   731,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384,   587,   736, -1384,
   -1384, -1384, -1384, -1384, -1384,   216, -1384, -1384,     0, -1384,
   -1384, -1384, -1384, -1384, -1384,   -83, -1384, -1384,  -104, -1384,
   -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384, -1384,   231,
   -1384, -1384, -1384, -1384
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   781,
      82,    83,    39,    64,    79,    80,   798,  1026,  1135,  1136,
     878,    41,    66,    85,   461,    86,    43,    67,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   490,   176,   177,   510,   178,   179,   180,
     181,   182,   183,   184,   496,   767,   185,   497,   186,   498,
     187,   188,   189,   511,   778,   190,   191,   192,   193,   194,
     529,   195,   530,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   465,   243,   244,    45,    68,   245,   539,   246,
     540,   801,   247,   541,   804,   248,   249,   250,   251,   205,
     475,   206,   466,   847,   848,   849,  1038,   850,  1039,   207,
     476,   208,   477,   906,   907,   908,  1067,   879,   880,   881,
    1042,   882,  1043,   883,  1044,   884,  1045,   885,   886,   578,
     887,   888,   889,   890,   891,   892,   893,   894,   895,   896,
    1056,  1318,   897,   898,   899,  1059,   900,  1060,   901,  1061,
     902,  1062,   903,  1063,   209,   518,   930,   931,   932,   933,
     934,   935,   936,   210,   524,   966,   967,   968,   969,   970,
     211,   521,   945,   946,   947,  1090,    59,    75,   425,   426,
     427,   593,   428,   594,   212,   522,   954,   955,   956,   957,
     958,   959,   960,   961,   213,   506,   910,   911,   912,  1070,
      47,    69,   298,   299,   300,   552,   301,   548,   302,   549,
     303,   550,   304,   553,   305,   558,   306,   555,   307,   556,
     308,   557,   214,   215,   216,   312,   217,   512,   922,   923,
     924,  1079,  1219,  1220,   218,   507,    53,    72,   914,   915,
     916,  1073,    55,    73,   386,   387,   388,   389,   390,   391,
     392,   577,   393,   581,   394,   580,   395,   396,   582,   397,
     219,   508,   918,   919,   920,  1076,    57,    74,   409,   410,
     411,   412,   413,   586,   414,   415,   416,   417,   418,   419,
     590,   314,   551,  1028,  1029,  1030,  1137,    49,    70,   344,
     345,   346,   562,   347,   220,   513,   221,   514,   222,   520,
     941,   942,   943,  1087,    51,    71,   362,   363,   364,   223,
     470,   224,   471,   225,   472,   368,   567,   369,   568,   370,
     569,   371,   571,   372,   570,   373,   573,   374,   572,   375,
     566,   321,   559,  1032,  1033,  1140,   226,   519,   938,   939,
    1084,  1247,  1248,  1249,  1250,  1251,  1330,  1252,  1331,  1253,
    1254,   227,   228,   525,   229,   526,   996,   997,   998,  1115,
     986,   987,   988,  1106,  1341,   989,  1107,   990,  1108,   991,
     992,   993,  1112,  1377,  1378,  1379,  1392,  1407,  1408,  1409,
    1419,   994,  1110,  1370,  1371,  1372,  1386,  1415,  1373,  1387,
    1374,  1388,  1375,  1389,  1426,  1427,  1428,  1444,  1462,  1463,
    1464,  1473,  1465,  1474,   230,   527,  1005,  1006,  1007,  1008,
    1119,  1009,  1010,  1121,   231,   528,    61,    76,   440,   441,
     442,   443,   598,   444,   445,   600,   446,   447,   448,   603,
     838,   449,   604,   232,   464,    63,    77,   452,   453,   454,
     607,   455,   233,   534,  1013,  1014,  1125,  1293,  1294,  1295,
    1296,  1351,  1297,  1349,  1412,  1413,  1422,  1436,  1437,  1438,
    1448,  1439,  1440,  1441,  1442,  1452,   234,   535,  1020,  1021,
    1022,  1023,  1024,  1025
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     160,   242,   266,   324,   358,    78,   384,   405,   424,   437,
     385,   406,   376,   317,   981,   982,   904,  1210,   983,  1211,
    1227,   318,   836,   365,   252,   315,   348,   360,   462,   398,
     420,   780,   438,   463,   378,   422,   423,   313,   343,   359,
     407,   339,    29,   270,    30,  1082,    31,   408,  1083,   136,
     137,    40,   340,    42,   136,   137,   281,   325,   811,   812,
     813,  1458,   319,  1459,   366,   537,   341,   817,   422,   423,
     538,   253,   316,   349,   361,   342,   399,   421,  1085,   439,
      28,  1086,   282,   326,   320,   267,   367,    81,   831,   962,
     963,   964,  1458,  1126,  1459,    84,  1127,   235,   236,   130,
     268,   237,   269,   780,   238,   239,   240,   241,   450,   451,
     283,   327,   297,   613,  1423,  1402,    44,  1424,   458,   159,
     284,   328,   285,   329,    46,   286,   330,    48,   287,   331,
      93,    94,    95,   289,   332,   290,   333,   546,   291,   334,
     799,   800,   547,   292,   335,   293,   336,   560,   294,   337,
     295,   338,   561,   271,   564,   272,   273,    50,   274,   565,
     275,   276,   159,   277,   845,   846,   278,   159,    52,   136,
     137,   279,   595,   280,   288,    54,   296,   596,  1363,   309,
     605,   310,   609,    56,   311,   606,   456,   610,    93,    94,
      95,    96,   378,   400,   379,   380,   401,   402,   403,   537,
     609,   131,    58,   837,  1035,  1036,   136,   137,  1015,  1016,
    1017,  1018,   136,   137,   546,   762,   763,   764,   765,  1037,
      60,   404,   136,   137,  1040,   159,   101,   102,   103,  1041,
      62,   350,   999,  1000,  1001,   871,   872,   873,   874,   875,
     876,   351,   352,   353,   354,   355,   356,   357,   802,   803,
     925,   926,   927,   928,   766,   929,  1064,   457,   130,   131,
     378,  1065,   136,   137,   459,   460,  1210,  1431,  1211,  1227,
    1432,  1433,  1434,  1435,    32,    33,    34,    35,   378,   467,
     136,   137,  1002,  1064,  1099,   574,  1104,    87,  1066,  1100,
      88,  1105,  1230,  1231,  1232,  1233,  1113,   575,   136,   137,
     468,  1114,    89,   469,   473,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,  1364,  1365,  1366,   159,
     774,   775,   776,   777,  1169,   159,   948,   949,   950,   951,
     952,   953,  1122,   576,   474,   159,   478,  1123,   981,   982,
     981,   982,   983,   584,   983,   479,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   159,   605,  1132,   130,   131,
     480,  1124,  1133,   377,  1064,  1286,   481,  1287,  1288,  1324,
     132,   133,   134,   159,  1315,  1316,  1317,   135,   611,   612,
     136,   137,  1338,  1339,  1340,   138,   139,   140,   141,   142,
     560,   159,   482,   483,  1328,  1325,   852,   853,   143,  1329,
     595,  1113,  1352,   585,   564,  1337,  1346,  1353,   144,  1355,
    1390,   145,  1420,   591,   484,  1391,  1453,  1421,   146,   147,
    1475,  1454,   485,   148,   149,  1476,   486,   378,   487,   379,
     380,   488,   489,   491,   381,   382,   383,   492,   493,   494,
     495,   499,   150,   500,   501,   502,   151,   136,   137,   503,
     160,   504,   624,   505,   509,   515,   516,   517,   523,   242,
     531,   152,   153,   154,   155,   156,   157,   532,   533,   536,
     542,   543,   544,   266,   545,   158,   554,   324,   563,   136,
     137,   579,   252,   583,   317,   587,   588,   589,   358,   592,
     618,   597,   318,   159,   599,   601,   315,   602,   384,   608,
     348,   614,   385,   615,   616,   405,   617,   365,   313,   406,
     619,   360,   343,   621,   270,   339,   622,   620,   437,   623,
     626,   398,   625,   359,   627,   628,   340,   281,   420,   253,
     629,   325,   630,   319,   631,   632,  1455,  1456,   407,   633,
     341,   438,   634,   316,   638,   408,   635,   349,   366,   342,
     636,   641,   637,   282,   640,   320,   267,   326,   361,   639,
     159,   647,   642,   643,   648,   649,   644,   645,   399,   646,
     367,   268,   650,   269,   651,   421,   652,   653,   654,   655,
     657,   283,   656,   297,   658,   327,   659,   660,   439,   661,
     662,   284,   159,   285,   663,   328,   286,   329,   664,   287,
     330,   665,   669,   331,   289,   666,   290,   667,   332,   291,
     333,   668,   670,   334,   292,   671,   293,   672,   335,   294,
     336,   295,   673,   337,   271,   338,   272,   273,   674,   274,
     675,   275,   276,   676,   277,   677,   678,   278,   679,   868,
     869,   870,   279,  1356,   280,   288,   680,   296,   136,   137,
     309,   681,   310,   685,   682,   311,   683,   686,   688,   684,
     689,   690,   696,   691,   160,   692,   242,   697,   693,   694,
     698,   841,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   699,   700,   701,   703,   252,
     704,   705,   706,   702,   707,   709,   710,   712,   713,   714,
     715,   965,   980,   136,   137,   437,   716,   717,   718,  1019,
     719,   723,   721,   722,   724,   429,   430,   431,   432,   433,
     434,   435,   436,   725,   971,   984,   726,  1003,   438,   727,
     729,   733,   730,   735,   731,   736,   253,    91,    92,    93,
      94,    95,    96,   732,   738,   739,   740,   741,   973,   742,
     744,   743,   974,   975,   976,   977,   745,   747,   750,   839,
     748,   159,   978,   979,   751,   752,   753,   754,   755,   756,
     757,   972,   985,   758,  1004,   439,   759,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   760,   761,
     768,   769,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   770,   254,   255,   256,   771,
     131,   772,   773,   779,    30,   782,   159,   783,   784,   785,
     786,   790,   133,   134,   787,   788,   789,   791,   792,   257,
     793,   136,   137,   258,   259,   260,   138,   139,   140,   794,
     261,   262,   263,   795,   796,   797,   805,   264,   808,   143,
     840,   806,   807,   809,   810,   815,   814,   265,   816,   818,
     819,   820,   821,   905,   822,   823,   909,   824,   913,   917,
     825,   851,   852,   853,   854,   855,   856,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   921,   826,   827,   866,
     867,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     877,   828,   829,   937,   830,   832,   834,   835,   940,   944,
     995,  1012,   152,   153,  1027,  1031,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1054,  1055,  1057,  1058,  1069,  1134,
    1068,  1072,  1071,  1074,  1075,   378,  1077,  1078,  1080,  1081,
    1089,  1088,  1093,  1092,   159,  1091,  1094,  1095,  1096,  1097,
    1098,  1101,  1102,  1103,  1109,  1111,  1117,  1139,  1116,  1118,
    1120,  1128,  1129,  1130,  1131,  1151,  1150,  1138,  1143,  1142,
    1141,  1144,  1146,  1147,  1148,  1149,  1152,  1153,  1154,  1160,
    1155,  1163,  1156,   266,  1164,  1157,   384,  1158,  1159,   405,
     385,  1161,  1177,   406,   317,  1165,  1209,  1234,  1166,  1162,
     358,  1239,   318,   424,  1240,  1167,   315,  1267,  1260,   398,
    1261,  1224,   420,  1262,  1263,  1222,  1244,   965,   313,   365,
    1242,  1271,   407,   360,   270,  1264,   980,  1221,   980,   408,
    1212,  1265,  1241,  1181,  1268,   359,  1269,   281,  1289,  1272,
     971,  1213,  1290,   319,  1273,  1019,  1192,  1274,  1275,   984,
     324,   984,  1225,   316,  1277,  1214,   399,  1245,  1003,   421,
     366,  1291,  1223,   282,  1215,   320,   267,  1243,   159,  1276,
     361,  1282,  1193,   348,  1226,  1178,  1281,  1283,  1284,  1246,
    1235,   268,   367,   269,  1299,   343,  1300,   972,   339,  1301,
    1179,   283,  1180,   297,  1302,  1236,   985,  1237,   985,   340,
    1194,   284,  1208,   285,   325,  1004,   286,  1238,  1292,   287,
    1195,  1304,  1196,   341,   289,  1197,   290,  1305,  1198,   291,
     349,  1308,   342,  1200,   292,  1201,   293,  1309,  1202,   294,
     326,   295,  1310,  1203,   271,  1204,   272,   273,  1205,   274,
    1206,   275,   276,  1182,   277,  1183,  1184,   278,  1185,  1326,
    1186,  1187,   279,  1188,   280,   288,  1189,   296,   327,  1327,
     309,  1190,   310,  1191,  1199,   311,  1207,  1332,   328,  1216,
     329,  1217,  1333,   330,  1218,  1334,   331,  1335,  1311,  1336,
    1344,   332,  1345,   333,  1350,  1358,   334,  1359,  1380,  1376,
    1382,   335,  1394,   336,  1393,  1395,   337,  1397,   338,  1398,
    1399,  1400,  1312,  1313,  1414,  1348,  1411,  1418,  1425,  1314,
    1319,  1320,  1429,  1321,  1449,  1323,  1342,  1445,  1343,  1347,
    1354,  1446,   842,  1384,  1360,  1361,  1381,  1385,  1450,  1396,
    1416,  1451,  1417,  1447,  1467,  1471,  1469,  1468,  1470,  1477,
    1478,  1177,  1479,  1480,  1482,  1209,  1483,   695,  1234,   687,
     833,   844,  1239,  1145,  1170,  1240,  1168,  1367,  1259,  1322,
    1224,  1034,  1229,  1258,  1222,  1289,  1270,  1244,   737,  1290,
    1266,  1242,  1172,   708,  1171,  1228,  1221,  1357,  1173,  1212,
    1368,  1174,  1181,  1241,   728,  1176,  1175,   711,  1291,   734,
    1213,  1257,  1307,   720,  1362,  1192,  1256,  1278,  1306,  1280,
    1255,  1225,  1279,  1367,  1214,  1403,  1410,  1430,  1245,  1404,
    1466,  1223,  1401,  1215,  1481,  1011,   746,  1285,  1243,   843,
    1443,  1193,  1298,  1226,  1178,   749,  1368,  1369,  1405,  1472,
    1246,  1235,  1383,  1403,     0,  1292,     0,  1404,     0,  1179,
       0,  1180,     0,  1303,     0,     0,  1236,     0,  1237,  1194,
       0,  1208,     0,     0,     0,     0,  1405,  1457,  1238,  1195,
       0,  1196,     0,     0,  1197,     0,     0,  1198,     0,     0,
       0,     0,  1200,  1369,  1201,  1406,     0,  1202,     0,     0,
    1460,     0,  1203,     0,  1204,     0,     0,  1205,  1457,  1206,
       0,     0,  1182,     0,  1183,  1184,     0,  1185,     0,  1186,
    1187,     0,  1188,  1406,     0,  1189,     0,     0,     0,     0,
    1190,  1460,  1191,  1199,     0,  1207,     0,     0,  1216,     0,
    1217,     0,     0,  1218,     0,     0,     0,  1461,    91,    92,
      93,    94,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1461,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
       0,     0,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,     0,     0,     0,
       0,   131,   378,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,     0,     0,     0,     0,     0,
       0,     0,   136,   137,     0,   259,     0,   138,   139,   140,
       0,   261,   262,   263,     0,     0,     0,     0,   264,     0,
       0,   116,   117,   118,   119,   120,   121,   122,   265,   124,
     125,   126,   127,     0,     0,     0,     0,     0,     0,   131,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,     0,     0,     0,     0,     0,     0,   322,
     136,   137,     0,     0,     0,     0,     0,     0,     0,   261,
     262,   263,     0,     0,     0,     0,   264,   323,     0,     0,
       0,     0,     0,   152,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   159,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   152,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   789,   789,   759,  1079,   789,  1079,
    1079,    69,    18,    71,    68,    69,    70,    71,     3,    73,
      74,   664,    76,     8,   104,   153,   154,    69,    70,    71,
      74,    70,     5,    69,     7,     3,     9,    74,     6,   124,
     125,     7,    70,     7,   124,   125,    69,    70,   703,   704,
     705,  1444,    69,  1444,    71,     3,    70,   712,   153,   154,
       8,    68,    69,    70,    71,    70,    73,    74,     3,    76,
       0,     6,    69,    70,    69,    69,    71,   237,   733,   164,
     165,   166,  1475,     3,  1475,    10,     6,    15,    16,   102,
      69,    19,    69,   736,    22,    23,    24,    25,    12,    13,
      69,    70,    69,   237,     3,   185,     7,     6,     4,   237,
      69,    70,    69,    70,     7,    69,    70,     7,    69,    70,
      32,    33,    34,    69,    70,    69,    70,     3,    69,    70,
      17,    18,     8,    69,    70,    69,    70,     3,    69,    70,
      69,    70,     8,    69,     3,    69,    69,     7,    69,     8,
      69,    69,   237,    69,    27,    28,    69,   237,     7,   124,
     125,    69,     3,    69,    69,     7,    69,     8,    40,    69,
       3,    69,     3,     7,    69,     8,     6,     8,    32,    33,
      34,    35,   104,   105,   106,   107,   108,   109,   110,     3,
       3,   103,     7,   199,     8,     8,   124,   125,   220,   221,
     222,   223,   124,   125,     3,   201,   202,   203,   204,     8,
       7,   133,   124,   125,     3,   237,    70,    71,    72,     8,
       7,   133,   187,   188,   189,    63,    64,    65,    66,    67,
      68,   143,   144,   145,   146,   147,   148,   149,    20,    21,
     144,   145,   146,   147,   240,   149,     3,     3,   102,   103,
     104,     8,   124,   125,     8,     3,  1328,   212,  1328,  1328,
     215,   216,   217,   218,   237,   238,   239,   240,   104,     4,
     124,   125,   237,     3,     3,     8,     3,    11,     8,     8,
      14,     8,   136,   137,   138,   139,     3,     3,   124,   125,
       4,     8,    26,     4,     4,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,   178,   179,   180,   237,
     117,   118,   119,   120,  1067,   237,   156,   157,   158,   159,
     160,   161,     3,     8,     4,   237,     4,     8,  1113,  1113,
    1115,  1115,  1113,     8,  1115,     4,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   237,     3,     3,   102,   103,
       4,     8,     8,    40,     3,   211,     4,   213,   214,     8,
     114,   115,   116,   237,    55,    56,    57,   121,   457,   458,
     124,   125,   170,   171,   172,   129,   130,   131,   132,   133,
       3,   237,     4,     4,     3,     8,    41,    42,   142,     8,
       3,     3,     3,     3,     3,     8,     8,     8,   152,     8,
       3,   155,     3,     8,     4,     8,     3,     8,   162,   163,
       3,     8,     4,   167,   168,     8,     4,   104,     4,   106,
     107,     4,     4,     4,   111,   112,   113,     4,     4,     4,
       4,     4,   186,     4,     4,     4,   190,   124,   125,     4,
     537,     4,   238,     4,     4,     4,     4,     4,     4,   546,
       4,   205,   206,   207,   208,   209,   210,     4,     4,     4,
       4,     4,     4,   560,     4,   219,     4,   564,     4,   124,
     125,     4,   546,     4,   560,     4,     4,     4,   575,     3,
     240,     4,   560,   237,     4,     4,   560,     4,   585,     4,
     564,     4,   585,     4,     4,   592,     4,   575,   560,   592,
     240,   575,   564,     4,   560,   564,     4,   240,   605,     4,
       4,   585,   240,   575,     4,     4,   564,   560,   592,   546,
     238,   564,   238,   560,   238,   238,   181,   182,   592,   238,
     564,   605,   240,   560,   238,   592,   239,   564,   575,   564,
     239,     4,   239,   560,   238,   560,   560,   564,   575,   239,
     237,     4,   238,   238,     4,     4,   240,   240,   585,   240,
     575,   560,   240,   560,   240,   592,   239,   238,   238,   238,
       4,   560,   240,   560,     4,   564,     4,   238,   605,     4,
       4,   560,   237,   560,     4,   564,   560,   564,     4,   560,
     564,     4,     4,   564,   560,   240,   560,   240,   564,   560,
     564,   240,     4,   564,   560,     4,   560,     4,   564,   560,
     564,   560,     4,   564,   560,   564,   560,   560,   238,   560,
       4,   560,   560,     4,   560,     4,     4,   560,     4,    60,
      61,    62,   560,  1308,   560,   560,     4,   560,   124,   125,
     560,     4,   560,     4,   240,   560,   240,     4,     4,   240,
       4,     4,     4,   240,   751,   240,   753,     4,   238,   238,
       4,   750,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,     4,     4,     4,     4,   753,
       4,     4,     4,   238,     4,     4,   238,     4,     4,     4,
       4,   788,   789,   124,   125,   792,     4,     4,     4,   796,
       4,   238,     4,     4,     4,   191,   192,   193,   194,   195,
     196,   197,   198,     4,   788,   789,     4,   791,   792,   240,
       4,     4,   240,     4,   240,     4,   753,    30,    31,    32,
      33,    34,    35,   240,   240,     4,   238,     4,   169,   238,
       4,   238,   173,   174,   175,   176,     4,     4,     4,   200,
     238,   237,   183,   184,     7,     7,     7,     7,   237,   237,
     237,   788,   789,     7,   791,   792,     7,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     5,   237,
     237,   237,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     5,    99,   100,   101,     5,
     103,     5,   237,     5,     7,   237,   237,     5,     5,     5,
       5,     5,   115,   116,     7,     7,     7,     7,     7,   122,
     237,   124,   125,   126,   127,   128,   129,   130,   131,   237,
     133,   134,   135,     5,     7,     5,   237,   140,     5,   142,
       5,   237,   237,   237,   237,     7,   237,   150,   237,   237,
     237,   237,   237,     7,   237,   237,     7,   237,     7,     7,
     237,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     7,   237,   237,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,   237,   237,     7,   237,   237,   237,   237,     7,     7,
       7,     7,   205,   206,     7,   151,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   237,
       6,     3,     6,     6,     3,   104,     6,     3,     6,     3,
       3,     6,     4,     3,   237,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     6,     4,
       4,     4,     4,     4,     4,   240,   238,     6,     4,     6,
       8,     4,     4,     4,     4,     4,   238,   240,   238,     4,
     238,     4,   238,  1070,     4,   238,  1073,   238,   238,  1076,
    1073,   240,  1079,  1076,  1070,     4,  1079,  1084,     4,   238,
    1087,  1084,  1070,  1090,  1084,     4,  1070,   240,   238,  1073,
     238,  1079,  1076,   238,   238,  1079,  1084,  1104,  1070,  1087,
    1084,     4,  1076,  1087,  1070,   238,  1113,  1079,  1115,  1076,
    1079,   238,  1084,  1079,   238,  1087,   238,  1070,  1125,     4,
    1104,  1079,  1125,  1070,     4,  1132,  1079,   238,     4,  1113,
    1137,  1115,  1079,  1070,     4,  1079,  1073,  1084,  1122,  1076,
    1087,  1125,  1079,  1070,  1079,  1070,  1070,  1084,   237,   240,
    1087,     4,  1079,  1137,  1079,  1079,   240,   238,     4,  1084,
    1084,  1070,  1087,  1070,   240,  1137,   240,  1104,  1137,   240,
    1079,  1070,  1079,  1070,   240,  1084,  1113,  1084,  1115,  1137,
    1079,  1070,  1079,  1070,  1137,  1122,  1070,  1084,  1125,  1070,
    1079,     6,  1079,  1137,  1070,  1079,  1070,     3,  1079,  1070,
    1137,     4,  1137,  1079,  1070,  1079,  1070,   237,  1079,  1070,
    1137,  1070,   237,  1079,  1070,  1079,  1070,  1070,  1079,  1070,
    1079,  1070,  1070,  1079,  1070,  1079,  1079,  1070,  1079,     8,
    1079,  1079,  1070,  1079,  1070,  1070,  1079,  1070,  1137,     8,
    1070,  1079,  1070,  1079,  1079,  1070,  1079,     4,  1137,  1079,
    1137,  1079,     4,  1137,  1079,     8,  1137,     3,   237,     8,
       7,  1137,     5,  1137,     4,     4,  1137,     4,     4,     7,
       4,  1137,     3,  1137,     6,     5,  1137,     4,  1137,     4,
       4,     4,   237,   237,   177,  1284,     7,     5,     7,   237,
     237,   237,     4,   237,     4,   237,   237,     6,   237,   237,
     237,     3,   751,   237,   240,   240,   238,   237,     4,   237,
     237,     4,   237,   237,     4,     4,   238,   240,   238,   237,
     237,  1328,     4,     4,   237,  1328,   237,   546,  1335,   537,
     736,   753,  1335,  1040,  1069,  1335,  1064,  1344,  1092,  1166,
    1328,   840,  1082,  1090,  1328,  1352,  1104,  1335,   595,  1352,
    1099,  1335,  1072,   560,  1070,  1081,  1328,  1328,  1073,  1328,
    1344,  1075,  1328,  1335,   585,  1078,  1076,   564,  1352,   592,
    1328,  1089,  1139,   575,  1335,  1328,  1087,  1113,  1137,  1117,
    1085,  1328,  1115,  1390,  1328,  1392,  1394,  1420,  1335,  1392,
    1446,  1328,  1390,  1328,  1475,   792,   605,  1122,  1335,   752,
    1423,  1328,  1126,  1328,  1328,   609,  1390,  1344,  1392,  1453,
    1335,  1335,  1352,  1420,    -1,  1352,    -1,  1420,    -1,  1328,
      -1,  1328,    -1,  1132,    -1,    -1,  1335,    -1,  1335,  1328,
      -1,  1328,    -1,    -1,    -1,    -1,  1420,  1444,  1335,  1328,
      -1,  1328,    -1,    -1,  1328,    -1,    -1,  1328,    -1,    -1,
      -1,    -1,  1328,  1390,  1328,  1392,    -1,  1328,    -1,    -1,
    1444,    -1,  1328,    -1,  1328,    -1,    -1,  1328,  1475,  1328,
      -1,    -1,  1328,    -1,  1328,  1328,    -1,  1328,    -1,  1328,
    1328,    -1,  1328,  1420,    -1,  1328,    -1,    -1,    -1,    -1,
    1328,  1475,  1328,  1328,    -1,  1328,    -1,    -1,  1328,    -1,
    1328,    -1,    -1,  1328,    -1,    -1,    -1,  1444,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1475,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,    -1,   127,    -1,   129,   130,   131,
      -1,   133,   134,   135,    -1,    -1,    -1,    -1,   140,    -1,
      -1,    85,    86,    87,    88,    89,    90,    91,   150,    93,
      94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,   123,
     124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,
     134,   135,    -1,    -1,    -1,    -1,   140,   141,    -1,    -1,
      -1,    -1,    -1,   205,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   205,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   237
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,     0,     5,
       7,     9,   237,   238,   239,   240,   256,   257,   258,   263,
       7,   272,     7,   277,     7,   336,     7,   451,     7,   538,
       7,   555,     7,   487,     7,   493,     7,   517,     7,   427,
       7,   667,     7,   686,   264,   259,   273,   278,   337,   452,
     539,   556,   488,   494,   518,   428,   668,   687,   256,   265,
     266,   237,   261,   262,    10,   274,   276,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     102,   103,   114,   115,   116,   121,   124,   125,   129,   130,
     131,   132,   133,   142,   152,   155,   162,   163,   167,   168,
     186,   190,   205,   206,   207,   208,   209,   210,   219,   237,
     271,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   295,   296,   298,   299,
     300,   301,   302,   303,   304,   307,   309,   311,   312,   313,
     316,   317,   318,   319,   320,   322,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   350,   352,   360,   362,   405,
     414,   421,   435,   445,   473,   474,   475,   477,   485,   511,
     545,   547,   549,   560,   562,   564,   587,   602,   603,   605,
     655,   665,   684,   693,   717,    15,    16,    19,    22,    23,
      24,    25,   271,   334,   335,   338,   340,   343,   346,   347,
     348,   349,   545,   547,    99,   100,   101,   122,   126,   127,
     128,   133,   134,   135,   140,   150,   271,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   296,   299,
     300,   301,   302,   303,   304,   307,   309,   311,   312,   313,
     316,   317,   318,   319,   320,   322,   324,   330,   453,   454,
     455,   457,   459,   461,   463,   465,   467,   469,   471,   473,
     474,   475,   476,   511,   532,   545,   547,   549,   560,   562,
     564,   582,   123,   141,   271,   301,   302,   303,   304,   307,
     309,   311,   313,   316,   317,   318,   319,   320,   322,   465,
     467,   469,   471,   511,   540,   541,   542,   544,   545,   547,
     133,   143,   144,   145,   146,   147,   148,   149,   271,   511,
     545,   547,   557,   558,   559,   560,   562,   564,   566,   568,
     570,   572,   574,   576,   578,   580,   485,    40,   104,   106,
     107,   111,   112,   113,   271,   379,   495,   496,   497,   498,
     499,   500,   501,   503,   505,   507,   508,   510,   545,   547,
     105,   108,   109,   110,   133,   271,   379,   499,   505,   519,
     520,   521,   522,   523,   525,   526,   527,   528,   529,   530,
     545,   547,   153,   154,   271,   429,   430,   431,   433,   191,
     192,   193,   194,   195,   196,   197,   198,   271,   545,   547,
     669,   670,   671,   672,   674,   675,   677,   678,   679,   682,
      12,    13,   688,   689,   690,   692,     6,     3,     4,     8,
       3,   275,     3,     8,   685,   333,   353,     4,     4,     4,
     561,   563,   565,     4,     4,   351,   361,   363,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     294,     4,     4,     4,     4,     4,   305,   308,   310,     4,
       4,     4,     4,     4,     4,     4,   446,   486,   512,     4,
     297,   314,   478,   546,   548,     4,     4,     4,   406,   588,
     550,   422,   436,     4,   415,   604,   606,   656,   666,   321,
     323,     4,     4,     4,   694,   718,     4,     3,     8,   339,
     341,   344,     4,     4,     4,     4,     3,     8,   458,   460,
     462,   533,   456,   464,     4,   468,   470,   472,   466,   583,
       3,     8,   543,     4,     3,     8,   581,   567,   569,   571,
     575,   573,   579,   577,     8,     3,     8,   502,   380,     4,
     506,   504,   509,     4,     8,     3,   524,     4,     4,     4,
     531,     8,     3,   432,   434,     3,     8,     4,   673,     4,
     676,     4,     4,   680,   683,     3,     8,   691,     4,     3,
       8,   256,   256,   237,     4,     4,     4,     4,   240,   240,
     240,     4,     4,     4,   238,   240,     4,     4,     4,   238,
     238,   238,   238,   238,   240,   239,   239,   239,   238,   239,
     238,     4,   238,   238,   240,   240,   240,     4,     4,     4,
     240,   240,   239,   238,   238,   238,   240,     4,     4,     4,
     238,     4,     4,     4,     4,     4,   240,   240,   240,     4,
       4,     4,     4,     4,   238,     4,     4,     4,     4,     4,
       4,     4,   240,   240,   240,     4,     4,   280,     4,     4,
       4,   240,   240,   238,   238,   335,     4,     4,     4,     4,
       4,     4,   238,     4,     4,     4,     4,     4,   454,     4,
     238,   541,     4,     4,     4,     4,     4,     4,     4,     4,
     559,     4,     4,   238,     4,     4,     4,   240,   497,     4,
     240,   240,   240,     4,   521,     4,     4,   430,   240,     4,
     238,     4,   238,   238,     4,     4,   670,     4,   238,   689,
       4,     7,     7,     7,     7,   237,   237,   237,     7,     7,
       5,   237,   201,   202,   203,   204,   240,   306,   237,   237,
       5,     5,     5,   237,   117,   118,   119,   120,   315,     5,
     258,   260,   237,     5,     5,     5,     5,     7,     7,     7,
       5,     7,     7,   237,   237,     5,     7,     5,   267,    17,
      18,   342,    20,    21,   345,   237,   237,   237,     5,   237,
     237,   267,   267,   267,   237,     7,   237,   267,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   267,   237,   260,   237,   237,    18,   199,   681,   200,
       5,   256,   279,   688,   334,    27,    28,   354,   355,   356,
     358,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   271,   368,
     369,   370,   372,   374,   376,   378,   379,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   393,   394,   395,
     397,   399,   401,   403,   368,     7,   364,   365,   366,     7,
     447,   448,   449,     7,   489,   490,   491,     7,   513,   514,
     515,     7,   479,   480,   481,   144,   145,   146,   147,   149,
     407,   408,   409,   410,   411,   412,   413,     7,   589,   590,
       7,   551,   552,   553,     7,   423,   424,   425,   156,   157,
     158,   159,   160,   161,   437,   438,   439,   440,   441,   442,
     443,   444,   164,   165,   166,   271,   416,   417,   418,   419,
     420,   545,   547,   169,   173,   174,   175,   176,   183,   184,
     271,   395,   397,   399,   545,   547,   611,   612,   613,   616,
     618,   620,   621,   622,   632,     7,   607,   608,   609,   187,
     188,   189,   237,   545,   547,   657,   658,   659,   660,   662,
     663,   669,     7,   695,   696,   220,   221,   222,   223,   271,
     719,   720,   721,   722,   723,   724,   268,     7,   534,   535,
     536,   151,   584,   585,   364,     8,     8,     8,   357,   359,
       3,     8,   371,   373,   375,   377,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   391,     4,     4,   396,
     398,   400,   402,   404,     3,     8,     8,   367,     6,     3,
     450,     6,     3,   492,     6,     3,   516,     6,     3,   482,
       6,     3,     3,     6,   591,     3,     6,   554,     6,     3,
     426,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   614,   617,   619,     4,
     633,     4,   623,     3,     8,   610,     6,     3,     4,   661,
       4,   664,     3,     8,     8,   697,     3,     6,     4,     4,
       4,     4,     3,     8,   237,   269,   270,   537,     6,     3,
     586,     8,     6,     4,     4,   355,     4,     4,     4,     4,
     238,   240,   238,   240,   238,   238,   238,   238,   238,   238,
       4,   240,   238,     4,     4,     4,     4,     4,   369,   368,
     366,   453,   449,   495,   491,   519,   515,   271,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   296,
     299,   300,   301,   302,   303,   304,   307,   309,   311,   312,
     313,   316,   317,   318,   319,   320,   322,   324,   330,   379,
     445,   463,   465,   467,   469,   471,   473,   474,   475,   483,
     484,   511,   545,   547,   560,   562,   564,   582,   481,   408,
     136,   137,   138,   139,   271,   281,   282,   283,   330,   379,
     485,   511,   545,   547,   560,   562,   564,   592,   593,   594,
     595,   596,   598,   600,   601,   590,   557,   553,   429,   425,
     238,   238,   238,   238,   238,   238,   438,   240,   238,   238,
     417,     4,     4,     4,   238,     4,   240,     4,   612,   611,
     609,   240,     4,   238,     4,   658,   211,   213,   214,   271,
     379,   545,   547,   698,   699,   700,   701,   703,   696,   240,
     240,   240,   240,   720,     6,     3,   540,   536,     4,   237,
     237,   237,   237,   237,   237,    55,    56,    57,   392,   237,
     237,   237,   401,   237,     8,     8,     8,     8,     3,     8,
     597,   599,     4,     4,     8,     3,     8,     8,   170,   171,
     172,   615,   237,   237,     7,     5,     8,   237,   256,   704,
       4,   702,     3,     8,   237,     8,   267,   484,     4,     4,
     240,   240,   594,    40,   178,   179,   180,   271,   545,   547,
     634,   635,   636,   639,   641,   643,     7,   624,   625,   626,
       4,   238,     4,   699,   237,   237,   637,   640,   642,   644,
       3,     8,   627,     6,     3,     5,   237,     4,     4,     4,
       4,   635,   185,   271,   379,   545,   547,   628,   629,   630,
     626,     7,   705,   706,   177,   638,   237,   237,     5,   631,
       3,     8,   707,     3,     6,     7,   645,   646,   647,     4,
     629,   212,   215,   216,   217,   218,   708,   709,   710,   712,
     713,   714,   715,   706,   648,     6,     3,   237,   711,     4,
       4,     4,   716,     3,     8,   181,   182,   271,   372,   374,
     545,   547,   649,   650,   651,   653,   647,     4,   240,   238,
     238,     4,   709,   652,   654,     3,     8,   237,   237,     4,
       4,   650,   237,   237
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   241,   243,   242,   244,   242,   245,   242,   246,   242,
     247,   242,   248,   242,   249,   242,   250,   242,   251,   242,
     252,   242,   253,   242,   254,   242,   255,   242,   256,   256,
     256,   256,   256,   256,   256,   257,   259,   258,   260,   261,
     261,   262,   262,   262,   264,   263,   265,   265,   266,   266,
     266,   268,   267,   269,   269,   270,   270,   270,   271,   273,
     272,   275,   274,   274,   276,   278,   277,   279,   279,   279,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   294,   293,   295,   297,   296,
     298,   299,   300,   301,   302,   303,   305,   304,   306,   306,
     306,   306,   306,   308,   307,   310,   309,   311,   312,   314,
     313,   315,   315,   315,   315,   316,   317,   318,   319,   321,
     320,   323,   322,   324,   325,   326,   327,   328,   329,   330,
     331,   333,   332,   334,   334,   334,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   337,   336,   339,   338,
     341,   340,   342,   342,   344,   343,   345,   345,   346,   347,
     348,   349,   351,   350,   353,   352,   354,   354,   354,   355,
     355,   357,   356,   359,   358,   361,   360,   363,   362,   364,
     364,   365,   365,   365,   367,   366,   368,   368,   368,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   371,   370,   373,   372,   375,   374,   377,
     376,   378,   380,   379,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   391,   390,   392,   392,   392,   393,   394,
     396,   395,   398,   397,   400,   399,   402,   401,   401,   401,
     401,   401,   401,   404,   403,   406,   405,   407,   407,   407,
     408,   408,   408,   408,   408,   409,   410,   411,   412,   413,
     415,   414,   416,   416,   416,   417,   417,   417,   417,   417,
     417,   418,   419,   420,   422,   421,   423,   423,   424,   424,
     424,   426,   425,   428,   427,   429,   429,   429,   429,   430,
     430,   432,   431,   434,   433,   436,   435,   437,   437,   437,
     438,   438,   438,   438,   438,   438,   439,   440,   441,   442,
     443,   444,   446,   445,   447,   447,   448,   448,   448,   450,
     449,   452,   451,   453,   453,   453,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     454,   454,   454,   454,   454,   454,   454,   454,   454,   454,
     456,   455,   458,   457,   460,   459,   462,   461,   464,   463,
     466,   465,   468,   467,   470,   469,   472,   471,   473,   474,
     475,   476,   478,   477,   479,   479,   480,   480,   480,   482,
     481,   483,   483,   483,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   484,   486,   485,   488,   487,   489,   489,   490,
     490,   490,   492,   491,   494,   493,   495,   495,   496,   496,
     496,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   498,   499,   500,   502,   501,   504,   503,   506,   505,
     507,   509,   508,   510,   512,   511,   513,   513,   514,   514,
     514,   516,   515,   518,   517,   519,   519,   520,   520,   520,
     521,   521,   521,   521,   521,   521,   521,   521,   521,   521,
     521,   522,   524,   523,   525,   526,   527,   528,   529,   531,
     530,   533,   532,   534,   534,   535,   535,   535,   537,   536,
     539,   538,   540,   540,   540,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   543,
     542,   544,   546,   545,   548,   547,   550,   549,   551,   551,
     552,   552,   552,   554,   553,   556,   555,   557,   557,   558,
     558,   558,   559,   559,   559,   559,   559,   559,   559,   559,
     559,   559,   559,   559,   559,   559,   559,   561,   560,   563,
     562,   565,   564,   567,   566,   569,   568,   571,   570,   573,
     572,   575,   574,   577,   576,   579,   578,   581,   580,   583,
     582,   584,   586,   585,   588,   587,   589,   589,   589,   591,
     590,   592,   592,   593,   593,   593,   594,   594,   594,   594,
     594,   594,   594,   594,   594,   594,   594,   594,   594,   594,
     594,   594,   594,   595,   597,   596,   599,   598,   600,   601,
     602,   604,   603,   606,   605,   607,   607,   608,   608,   608,
     610,   609,   611,   611,   611,   612,   612,   612,   612,   612,
     612,   612,   612,   612,   612,   612,   612,   612,   614,   613,
     615,   615,   615,   617,   616,   619,   618,   620,   621,   623,
     622,   624,   624,   625,   625,   625,   627,   626,   628,   628,
     628,   629,   629,   629,   629,   629,   631,   630,   633,   632,
     634,   634,   634,   635,   635,   635,   635,   635,   635,   635,
     637,   636,   638,   640,   639,   642,   641,   644,   643,   645,
     645,   646,   646,   646,   648,   647,   649,   649,   649,   650,
     650,   650,   650,   650,   650,   650,   652,   651,   654,   653,
     656,   655,   657,   657,   657,   658,   658,   658,   658,   658,
     658,   659,   661,   660,   662,   664,   663,   666,   665,   668,
     667,   669,   669,   669,   670,   670,   670,   670,   670,   670,
     670,   670,   670,   670,   670,   671,   673,   672,   674,   676,
     675,   677,   678,   680,   679,   681,   681,   683,   682,   685,
     684,   687,   686,   688,   688,   688,   689,   689,   691,   690,
     692,   694,   693,   695,   695,   695,   697,   696,   698,   698,
     698,   699,   699,   699,   699,   699,   699,   699,   700,   702,
     701,   704,   703,   705,   705,   705,   707,   706,   708,   708,
     708,   709,   709,   709,   709,   709,   711,   710,   712,   713,
     714,   716,   715,   718,   717,   719,   719,   719,   720,   720,
     720,   720,   720,   721,   722,   723,   724
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
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     3,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     3,
       3,     3,     0,     6,     0,     6,     1,     3,     2,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     2,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     3,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       3,     0,     6,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
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
  "\"ddns-ttl\"", "\"ddns-ttl-min\"", "\"ddns-ttl-mix\"",
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
       0,   337,   337,   337,   338,   338,   339,   339,   340,   340,
     341,   341,   342,   342,   343,   343,   344,   344,   345,   345,
     346,   346,   347,   347,   348,   348,   349,   349,   357,   358,
     359,   360,   361,   362,   363,   366,   371,   371,   382,   385,
     386,   389,   394,   400,   405,   405,   412,   413,   416,   420,
     424,   430,   430,   437,   438,   441,   445,   449,   459,   468,
     468,   483,   483,   497,   500,   506,   506,   515,   516,   517,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   599,   605,   611,   617,   623,   629,   635,
     641,   647,   653,   659,   665,   671,   671,   680,   686,   686,
     695,   701,   707,   713,   719,   725,   731,   731,   740,   743,
     746,   749,   752,   758,   758,   767,   767,   776,   785,   795,
     795,   804,   807,   810,   813,   818,   824,   830,   836,   842,
     842,   851,   851,   860,   866,   872,   878,   884,   890,   896,
     902,   908,   908,   920,   921,   922,   927,   928,   929,   930,
     931,   932,   933,   934,   935,   936,   939,   939,   948,   948,
     959,   959,   967,   968,   971,   971,   979,   981,   985,   991,
     997,  1003,  1009,  1009,  1022,  1022,  1033,  1034,  1035,  1040,
    1041,  1044,  1044,  1063,  1063,  1081,  1081,  1094,  1094,  1105,
    1106,  1109,  1110,  1111,  1116,  1116,  1126,  1127,  1128,  1133,
    1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,
    1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,  1153,
    1154,  1155,  1156,  1159,  1159,  1168,  1168,  1177,  1177,  1186,
    1186,  1195,  1201,  1201,  1210,  1216,  1222,  1228,  1234,  1240,
    1246,  1252,  1258,  1264,  1264,  1272,  1273,  1274,  1277,  1283,
    1289,  1289,  1298,  1298,  1307,  1307,  1316,  1316,  1324,  1327,
    1330,  1333,  1336,  1341,  1341,  1350,  1350,  1361,  1362,  1363,
    1368,  1369,  1370,  1371,  1372,  1375,  1380,  1385,  1390,  1395,
    1402,  1402,  1415,  1416,  1417,  1422,  1423,  1424,  1425,  1426,
    1427,  1430,  1436,  1442,  1448,  1448,  1459,  1460,  1463,  1464,
    1465,  1470,  1470,  1480,  1480,  1490,  1491,  1492,  1495,  1498,
    1499,  1502,  1502,  1511,  1511,  1520,  1520,  1532,  1533,  1534,
    1539,  1540,  1541,  1542,  1543,  1544,  1547,  1553,  1559,  1565,
    1571,  1577,  1586,  1586,  1600,  1601,  1604,  1605,  1606,  1615,
    1615,  1641,  1641,  1652,  1653,  1654,  1660,  1661,  1662,  1663,
    1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,
    1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,
    1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,
    1694,  1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,
    1704,  1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,
    1716,  1716,  1725,  1725,  1734,  1734,  1743,  1743,  1752,  1752,
    1761,  1761,  1771,  1771,  1783,  1783,  1794,  1794,  1805,  1811,
    1817,  1823,  1831,  1831,  1843,  1844,  1848,  1849,  1850,  1855,
    1855,  1863,  1864,  1865,  1870,  1871,  1872,  1873,  1874,  1875,
    1876,  1877,  1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,
    1886,  1887,  1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,
    1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,
    1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,
    1916,  1917,  1918,  1925,  1925,  1939,  1939,  1948,  1949,  1952,
    1953,  1954,  1961,  1961,  1976,  1976,  1990,  1991,  1994,  1995,
    1996,  2001,  2002,  2003,  2004,  2005,  2006,  2007,  2008,  2009,
    2010,  2013,  2015,  2021,  2023,  2023,  2032,  2032,  2041,  2041,
    2050,  2052,  2052,  2061,  2071,  2071,  2084,  2085,  2090,  2091,
    2092,  2099,  2099,  2111,  2111,  2123,  2124,  2129,  2130,  2131,
    2138,  2139,  2140,  2141,  2142,  2143,  2144,  2145,  2146,  2147,
    2148,  2151,  2153,  2153,  2162,  2164,  2166,  2172,  2178,  2184,
    2184,  2198,  2198,  2211,  2212,  2215,  2216,  2217,  2222,  2222,
    2232,  2232,  2242,  2243,  2244,  2249,  2250,  2251,  2252,  2253,
    2254,  2255,  2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,
    2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,  2272,  2275,
    2275,  2284,  2290,  2290,  2315,  2315,  2345,  2345,  2356,  2357,
    2360,  2361,  2362,  2367,  2367,  2376,  2376,  2385,  2386,  2389,
    2390,  2391,  2397,  2398,  2399,  2400,  2401,  2402,  2403,  2404,
    2405,  2406,  2407,  2408,  2409,  2410,  2411,  2414,  2414,  2423,
    2423,  2432,  2432,  2441,  2441,  2450,  2450,  2459,  2459,  2468,
    2468,  2477,  2477,  2486,  2486,  2495,  2495,  2504,  2504,  2518,
    2518,  2529,  2532,  2532,  2546,  2546,  2557,  2558,  2559,  2564,
    2564,  2574,  2575,  2578,  2579,  2580,  2585,  2586,  2587,  2588,
    2589,  2590,  2591,  2592,  2593,  2594,  2595,  2596,  2597,  2598,
    2599,  2600,  2601,  2604,  2606,  2606,  2615,  2615,  2625,  2631,
    2639,  2647,  2647,  2659,  2659,  2671,  2672,  2675,  2676,  2677,
    2682,  2682,  2690,  2691,  2692,  2697,  2698,  2699,  2700,  2701,
    2702,  2703,  2704,  2705,  2706,  2707,  2708,  2709,  2712,  2712,
    2721,  2722,  2723,  2726,  2726,  2736,  2736,  2746,  2752,  2758,
    2758,  2769,  2770,  2773,  2774,  2775,  2780,  2780,  2788,  2789,
    2790,  2795,  2796,  2797,  2798,  2799,  2802,  2802,  2813,  2813,
    2826,  2827,  2828,  2833,  2834,  2835,  2836,  2837,  2838,  2839,
    2842,  2842,  2850,  2853,  2853,  2862,  2862,  2871,  2871,  2882,
    2883,  2886,  2887,  2888,  2893,  2893,  2901,  2902,  2903,  2908,
    2909,  2910,  2911,  2912,  2913,  2914,  2917,  2917,  2926,  2926,
    2937,  2937,  2950,  2951,  2952,  2957,  2958,  2959,  2960,  2961,
    2962,  2965,  2971,  2971,  2980,  2986,  2986,  2996,  2996,  3009,
    3009,  3019,  3020,  3021,  3026,  3027,  3028,  3029,  3030,  3031,
    3032,  3033,  3034,  3035,  3036,  3039,  3045,  3045,  3054,  3060,
    3060,  3069,  3075,  3081,  3081,  3090,  3091,  3094,  3094,  3105,
    3105,  3117,  3117,  3127,  3128,  3129,  3135,  3136,  3139,  3139,
    3150,  3158,  3158,  3171,  3172,  3173,  3179,  3179,  3187,  3188,
    3189,  3194,  3195,  3196,  3197,  3198,  3199,  3200,  3203,  3209,
    3209,  3218,  3218,  3229,  3230,  3231,  3236,  3236,  3244,  3245,
    3246,  3251,  3252,  3253,  3254,  3255,  3258,  3258,  3267,  3273,
    3279,  3285,  3285,  3294,  3294,  3305,  3306,  3307,  3312,  3313,
    3314,  3315,  3316,  3319,  3325,  3331,  3337
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
#line 7020 "dhcp4_parser.cc"

#line 3343 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
