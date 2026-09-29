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

  case 177: // $@25: %empty
#line 776 "dhcp4_parser.yy"
                                     {
    ctx.unique("ddns-reverse-zone", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc"
    break;

  case 178: // ddns_reverse_zone: "ddns-reverse-zone" $@25 ":" "constant string"
#line 779 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-reverse-zone", s);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc"
    break;

  case 179: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 785 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1502 "dhcp4_parser.cc"
    break;

  case 180: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 794 "dhcp4_parser.yy"
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
#line 804 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@26 ":" ddns_conflict_resolution_mode_value
#line 807 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 813 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1542 "dhcp4_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 816 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1550 "dhcp4_parser.cc"
    break;

  case 185: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 819 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1558 "dhcp4_parser.cc"
    break;

  case 186: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 822 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1566 "dhcp4_parser.cc"
    break;

  case 187: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 827 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 188: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 833 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 189: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 839 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 190: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 845 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 191: // $@27: %empty
#line 851 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 192: // hostname_char_set: "hostname-char-set" $@27 ":" "constant string"
#line 854 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 860 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 194: // hostname_char_replacement: "hostname-char-replacement" $@28 ":" "constant string"
#line 863 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 195: // store_extended_info: "store-extended-info" ":" "boolean"
#line 869 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 196: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 875 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 197: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 881 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1674 "dhcp4_parser.cc"
    break;

  case 198: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 887 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 199: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 893 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 200: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 899 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1704 "dhcp4_parser.cc"
    break;

  case 201: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 905 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 202: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 911 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 203: // $@29: %empty
#line 917 "dhcp4_parser.yy"
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
#line 923 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1746 "dhcp4_parser.cc"
    break;

  case 207: // interfaces_config_params: interfaces_config_params ","
#line 931 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1754 "dhcp4_parser.cc"
    break;

  case 218: // $@30: %empty
#line 948 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1764 "dhcp4_parser.cc"
    break;

  case 219: // sub_interfaces4: "{" $@30 interfaces_config_params "}"
#line 952 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 220: // $@31: %empty
#line 957 "dhcp4_parser.yy"
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
#line 963 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc"
    break;

  case 222: // $@32: %empty
#line 968 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1803 "dhcp4_parser.cc"
    break;

  case 223: // dhcp_socket_type: "dhcp-socket-type" $@32 ":" socket_type
#line 971 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 224: // socket_type: "raw"
#line 976 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1818 "dhcp4_parser.cc"
    break;

  case 225: // socket_type: "udp"
#line 977 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1824 "dhcp4_parser.cc"
    break;

  case 226: // $@33: %empty
#line 980 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1833 "dhcp4_parser.cc"
    break;

  case 227: // outbound_interface: "outbound-interface" $@33 ":" outbound_interface_value
#line 983 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1842 "dhcp4_parser.cc"
    break;

  case 228: // outbound_interface_value: "same-as-inbound"
#line 988 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1850 "dhcp4_parser.cc"
    break;

  case 229: // outbound_interface_value: "use-routing"
#line 990 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1858 "dhcp4_parser.cc"
    break;

  case 230: // re_detect: "re-detect" ":" "boolean"
#line 994 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1868 "dhcp4_parser.cc"
    break;

  case 231: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 1000 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 232: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 1006 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 233: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1012 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1898 "dhcp4_parser.cc"
    break;

  case 234: // $@34: %empty
#line 1018 "dhcp4_parser.yy"
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
#line 1024 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1921 "dhcp4_parser.cc"
    break;

  case 236: // $@35: %empty
#line 1031 "dhcp4_parser.yy"
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
#line 1037 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1942 "dhcp4_parser.cc"
    break;

  case 240: // sanity_checks_params: sanity_checks_params ","
#line 1044 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1950 "dhcp4_parser.cc"
    break;

  case 243: // $@36: %empty
#line 1053 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc"
    break;

  case 244: // lease_checks: "lease-checks" $@36 ":" "constant string"
#line 1056 "dhcp4_parser.yy"
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
#line 1072 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 246: // extended_info_checks: "extended-info-checks" $@37 ":" "constant string"
#line 1075 "dhcp4_parser.yy"
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
#line 1090 "dhcp4_parser.yy"
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
#line 1096 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 249: // $@39: %empty
#line 1103 "dhcp4_parser.yy"
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
#line 1109 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2051 "dhcp4_parser.cc"
    break;

  case 255: // not_empty_database_list: not_empty_database_list ","
#line 1120 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2059 "dhcp4_parser.cc"
    break;

  case 256: // $@40: %empty
#line 1125 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 257: // database: "{" $@40 database_map_params "}"
#line 1129 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 260: // database_map_params: database_map_params ","
#line 1137 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2087 "dhcp4_parser.cc"
    break;

  case 286: // $@41: %empty
#line 1169 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 287: // database_type: "type" $@41 ":" "constant string"
#line 1172 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 288: // $@42: %empty
#line 1178 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 289: // user: "user" $@42 ":" "constant string"
#line 1181 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 290: // $@43: %empty
#line 1187 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 291: // password: "password" $@43 ":" "constant string"
#line 1190 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 292: // $@44: %empty
#line 1196 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2153 "dhcp4_parser.cc"
    break;

  case 293: // password_file: "password-file" $@44 ":" "constant string"
#line 1199 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1205 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 295: // host: "host" $@45 ":" "constant string"
#line 1208 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 296: // port: "port" ":" "integer"
#line 1214 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 297: // $@46: %empty
#line 1220 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 298: // name: "name" $@46 ":" "constant string"
#line 1223 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2211 "dhcp4_parser.cc"
    break;

  case 299: // persist: "persist" ":" "boolean"
#line 1229 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 300: // lfc_interval: "lfc-interval" ":" "integer"
#line 1235 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2231 "dhcp4_parser.cc"
    break;

  case 301: // readonly: "readonly" ":" "boolean"
#line 1241 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2241 "dhcp4_parser.cc"
    break;

  case 302: // connect_timeout: "connect-timeout" ":" "integer"
#line 1247 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 303: // read_timeout: "read-timeout" ":" "integer"
#line 1253 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 304: // write_timeout: "write-timeout" ":" "integer"
#line 1259 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 305: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1265 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 306: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1271 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 307: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1277 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 308: // $@47: %empty
#line 1283 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 309: // on_fail: "on-fail" $@47 ":" on_fail_mode
#line 1286 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2319 "dhcp4_parser.cc"
    break;

  case 310: // on_fail_mode: "stop-retry-exit"
#line 1291 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2325 "dhcp4_parser.cc"
    break;

  case 311: // on_fail_mode: "serve-retry-exit"
#line 1292 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2331 "dhcp4_parser.cc"
    break;

  case 312: // on_fail_mode: "serve-retry-continue"
#line 1293 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2337 "dhcp4_parser.cc"
    break;

  case 313: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1296 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 314: // max_row_errors: "max-row-errors" ":" "integer"
#line 1302 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 315: // $@48: %empty
#line 1308 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 316: // trust_anchor: "trust-anchor" $@48 ":" "constant string"
#line 1311 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 317: // $@49: %empty
#line 1317 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 318: // cert_file: "cert-file" $@49 ":" "constant string"
#line 1320 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 319: // $@50: %empty
#line 1326 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2404 "dhcp4_parser.cc"
    break;

  case 320: // key_file: "key-file" $@50 ":" "constant string"
#line 1329 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2414 "dhcp4_parser.cc"
    break;

  case 321: // $@51: %empty
#line 1335 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2423 "dhcp4_parser.cc"
    break;

  case 322: // ssl_mode: "ssl-mode" $@51 ":" ssl_mode
#line 1338 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2432 "dhcp4_parser.cc"
    break;

  case 323: // ssl_mode: "disable"
#line 1343 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2440 "dhcp4_parser.cc"
    break;

  case 324: // ssl_mode: "prefer"
#line 1346 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2448 "dhcp4_parser.cc"
    break;

  case 325: // ssl_mode: "require"
#line 1349 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2456 "dhcp4_parser.cc"
    break;

  case 326: // ssl_mode: "verify-ca"
#line 1352 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2464 "dhcp4_parser.cc"
    break;

  case 327: // ssl_mode: "verify-full"
#line 1355 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2472 "dhcp4_parser.cc"
    break;

  case 328: // $@52: %empty
#line 1360 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2481 "dhcp4_parser.cc"
    break;

  case 329: // cipher_list: "cipher-list" $@52 ":" "constant string"
#line 1363 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 330: // $@53: %empty
#line 1369 "dhcp4_parser.yy"
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
#line 1375 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2512 "dhcp4_parser.cc"
    break;

  case 334: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1382 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2520 "dhcp4_parser.cc"
    break;

  case 340: // duid_id: "duid"
#line 1394 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2529 "dhcp4_parser.cc"
    break;

  case 341: // hw_address_id: "hw-address"
#line 1399 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 342: // circuit_id: "circuit-id"
#line 1404 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2547 "dhcp4_parser.cc"
    break;

  case 343: // client_id: "client-id"
#line 1409 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2556 "dhcp4_parser.cc"
    break;

  case 344: // flex_id: "flex-id"
#line 1414 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 345: // $@54: %empty
#line 1421 "dhcp4_parser.yy"
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
#line 1427 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 349: // multi_threading_params: multi_threading_params ","
#line 1436 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2596 "dhcp4_parser.cc"
    break;

  case 356: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1449 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2606 "dhcp4_parser.cc"
    break;

  case 357: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1455 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 358: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1461 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 359: // $@55: %empty
#line 1467 "dhcp4_parser.yy"
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
#line 1473 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 365: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1484 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2655 "dhcp4_parser.cc"
    break;

  case 366: // $@56: %empty
#line 1489 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 367: // hooks_library: "{" $@56 hooks_params "}"
#line 1493 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 368: // $@57: %empty
#line 1499 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 369: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1503 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 372: // hooks_params: hooks_params ","
#line 1511 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2703 "dhcp4_parser.cc"
    break;

  case 376: // $@58: %empty
#line 1521 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 377: // library: "library" $@58 ":" "constant string"
#line 1524 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 378: // $@59: %empty
#line 1530 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 379: // parameters: "parameters" $@59 ":" map_value
#line 1533 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 380: // $@60: %empty
#line 1539 "dhcp4_parser.yy"
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
#line 1545 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 384: // expired_leases_params: expired_leases_params ","
#line 1553 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2770 "dhcp4_parser.cc"
    break;

  case 391: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1566 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 392: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1572 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2790 "dhcp4_parser.cc"
    break;

  case 393: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1578 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2800 "dhcp4_parser.cc"
    break;

  case 394: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1584 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 395: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1590 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 396: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1596 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 397: // $@61: %empty
#line 1605 "dhcp4_parser.yy"
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
#line 1611 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 403: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1625 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2859 "dhcp4_parser.cc"
    break;

  case 404: // $@62: %empty
#line 1634 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 405: // subnet4: "{" $@62 subnet4_params "}"
#line 1638 "dhcp4_parser.yy"
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
#line 1660 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2905 "dhcp4_parser.cc"
    break;

  case 407: // sub_subnet4: "{" $@63 subnet4_params "}"
#line 1664 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2915 "dhcp4_parser.cc"
    break;

  case 410: // subnet4_params: subnet4_params ","
#line 1673 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2923 "dhcp4_parser.cc"
    break;

  case 466: // $@64: %empty
#line 1736 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 467: // subnet: "subnet" $@64 ":" "constant string"
#line 1739 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 468: // $@65: %empty
#line 1745 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 469: // subnet_4o6_interface: "4o6-interface" $@65 ":" "constant string"
#line 1748 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 470: // $@66: %empty
#line 1754 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 471: // subnet_4o6_interface_id: "4o6-interface-id" $@66 ":" "constant string"
#line 1757 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 472: // $@67: %empty
#line 1763 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 473: // subnet_4o6_subnet: "4o6-subnet" $@67 ":" "constant string"
#line 1766 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 474: // $@68: %empty
#line 1772 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 475: // interface: "interface" $@68 ":" "constant string"
#line 1775 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 476: // $@69: %empty
#line 1781 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 477: // client_class: "client-class" $@69 ":" "constant string"
#line 1784 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 3037 "dhcp4_parser.cc"
    break;

  case 478: // $@70: %empty
#line 1791 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3049 "dhcp4_parser.cc"
    break;

  case 479: // network_client_classes: "client-classes" $@70 ":" list_strings
#line 1797 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3058 "dhcp4_parser.cc"
    break;

  case 480: // $@71: %empty
#line 1803 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 481: // require_client_classes: "require-client-classes" $@71 ":" list_strings
#line 1809 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3079 "dhcp4_parser.cc"
    break;

  case 482: // $@72: %empty
#line 1814 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 483: // evaluate_additional_classes: "evaluate-additional-classes" $@72 ":" list_strings
#line 1820 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3100 "dhcp4_parser.cc"
    break;

  case 484: // reservations_global: "reservations-global" ":" "boolean"
#line 1825 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 485: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1831 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 486: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1837 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 487: // id: "id" ":" "integer"
#line 1843 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 488: // $@73: %empty
#line 1851 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3152 "dhcp4_parser.cc"
    break;

  case 489: // shared_networks: "shared-networks" $@73 ":" "[" shared_networks_content "]"
#line 1857 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3161 "dhcp4_parser.cc"
    break;

  case 494: // shared_networks_list: shared_networks_list ","
#line 1870 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3169 "dhcp4_parser.cc"
    break;

  case 495: // $@74: %empty
#line 1875 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3179 "dhcp4_parser.cc"
    break;

  case 496: // shared_network: "{" $@74 shared_network_params "}"
#line 1879 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 499: // shared_network_params: shared_network_params ","
#line 1885 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3195 "dhcp4_parser.cc"
    break;

  case 550: // $@75: %empty
#line 1946 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 551: // option_def_list: "option-def" $@75 ":" "[" option_def_list_content "]"
#line 1952 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 552: // $@76: %empty
#line 1960 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 553: // sub_option_def_list: "{" $@76 option_def_list "}"
#line 1963 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 558: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1975 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3241 "dhcp4_parser.cc"
    break;

  case 559: // $@77: %empty
#line 1982 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3251 "dhcp4_parser.cc"
    break;

  case 560: // option_def_entry: "{" $@77 option_def_params "}"
#line 1986 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 561: // $@78: %empty
#line 1997 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 562: // sub_option_def: "{" $@78 option_def_params "}"
#line 2001 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 567: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2017 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3293 "dhcp4_parser.cc"
    break;

  case 579: // code: "code" ":" "integer"
#line 2036 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 581: // $@79: %empty
#line 2044 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 582: // option_def_type: "type" $@79 ":" "constant string"
#line 2047 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 583: // $@80: %empty
#line 2053 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc"
    break;

  case 584: // option_def_record_types: "record-types" $@80 ":" "constant string"
#line 2056 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 585: // $@81: %empty
#line 2062 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 586: // space: "space" $@81 ":" "constant string"
#line 2065 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3360 "dhcp4_parser.cc"
    break;

  case 588: // $@82: %empty
#line 2073 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3369 "dhcp4_parser.cc"
    break;

  case 589: // option_def_encapsulate: "encapsulate" $@82 ":" "constant string"
#line 2076 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 590: // option_def_array: "array" ":" "boolean"
#line 2082 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 591: // $@83: %empty
#line 2092 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3401 "dhcp4_parser.cc"
    break;

  case 592: // option_data_list: "option-data" $@83 ":" "[" option_data_list_content "]"
#line 2098 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3410 "dhcp4_parser.cc"
    break;

  case 597: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2113 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3418 "dhcp4_parser.cc"
    break;

  case 598: // $@84: %empty
#line 2120 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3428 "dhcp4_parser.cc"
    break;

  case 599: // option_data_entry: "{" $@84 option_data_params "}"
#line 2124 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3437 "dhcp4_parser.cc"
    break;

  case 600: // $@85: %empty
#line 2132 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3447 "dhcp4_parser.cc"
    break;

  case 601: // sub_option_data: "{" $@85 option_data_params "}"
#line 2136 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3456 "dhcp4_parser.cc"
    break;

  case 606: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2152 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3464 "dhcp4_parser.cc"
    break;

  case 619: // $@86: %empty
#line 2174 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 620: // option_data_data: "data" $@86 ":" "constant string"
#line 2177 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 623: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2187 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3493 "dhcp4_parser.cc"
    break;

  case 624: // option_data_always_send: "always-send" ":" "boolean"
#line 2193 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 625: // option_data_never_send: "never-send" ":" "boolean"
#line 2199 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3513 "dhcp4_parser.cc"
    break;

  case 626: // $@87: %empty
#line 2205 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 627: // option_data_client_classes: "client-classes" $@87 ":" list_strings
#line 2211 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 628: // $@88: %empty
#line 2219 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3546 "dhcp4_parser.cc"
    break;

  case 629: // pools_list: "pools" $@88 ":" "[" pools_list_content "]"
#line 2225 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 634: // not_empty_pools_list: not_empty_pools_list ","
#line 2238 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3563 "dhcp4_parser.cc"
    break;

  case 635: // $@89: %empty
#line 2243 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 636: // pool_list_entry: "{" $@89 pool_params "}"
#line 2247 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 637: // $@90: %empty
#line 2253 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3593 "dhcp4_parser.cc"
    break;

  case 638: // sub_pool4: "{" $@90 pool_params "}"
#line 2257 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 641: // pool_params: pool_params ","
#line 2265 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3611 "dhcp4_parser.cc"
    break;

  case 667: // $@91: %empty
#line 2297 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3620 "dhcp4_parser.cc"
    break;

  case 668: // pool_entry: "pool" $@91 ":" "constant string"
#line 2300 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 669: // pool_id: "pool-id" ":" "integer"
#line 2306 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3640 "dhcp4_parser.cc"
    break;

  case 670: // $@92: %empty
#line 2312 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3648 "dhcp4_parser.cc"
    break;

  case 671: // user_context: "user-context" $@92 ":" map_value
#line 2314 "dhcp4_parser.yy"
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
#line 3675 "dhcp4_parser.cc"
    break;

  case 672: // $@93: %empty
#line 2337 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 673: // comment: "comment" $@93 ":" "constant string"
#line 2339 "dhcp4_parser.yy"
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
#line 3712 "dhcp4_parser.cc"
    break;

  case 674: // $@94: %empty
#line 2367 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 675: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2373 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 680: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2384 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3741 "dhcp4_parser.cc"
    break;

  case 681: // $@95: %empty
#line 2389 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 682: // reservation: "{" $@95 reservation_params "}"
#line 2393 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 683: // $@96: %empty
#line 2398 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 684: // sub_reservation: "{" $@96 reservation_params "}"
#line 2402 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3779 "dhcp4_parser.cc"
    break;

  case 689: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2413 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3787 "dhcp4_parser.cc"
    break;

  case 705: // $@97: %empty
#line 2436 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 706: // next_server: "next-server" $@97 ":" "constant string"
#line 2439 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 707: // $@98: %empty
#line 2445 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 708: // server_hostname: "server-hostname" $@98 ":" "constant string"
#line 2448 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 709: // $@99: %empty
#line 2454 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 710: // boot_file_name: "boot-file-name" $@99 ":" "constant string"
#line 2457 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 711: // $@100: %empty
#line 2463 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 712: // ip_address: "ip-address" $@100 ":" "constant string"
#line 2466 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 713: // $@101: %empty
#line 2472 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 714: // duid: "duid" $@101 ":" "constant string"
#line 2475 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 715: // $@102: %empty
#line 2481 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 716: // hw_address: "hw-address" $@102 ":" "constant string"
#line 2484 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 717: // $@103: %empty
#line 2490 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 718: // client_id_value: "client-id" $@103 ":" "constant string"
#line 2493 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3920 "dhcp4_parser.cc"
    break;

  case 719: // $@104: %empty
#line 2499 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 720: // circuit_id_value: "circuit-id" $@104 ":" "constant string"
#line 2502 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3939 "dhcp4_parser.cc"
    break;

  case 721: // $@105: %empty
#line 2508 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3948 "dhcp4_parser.cc"
    break;

  case 722: // flex_id_value: "flex-id" $@105 ":" "constant string"
#line 2511 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 723: // $@106: %empty
#line 2517 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 724: // hostname: "hostname" $@106 ":" "constant string"
#line 2520 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 725: // $@107: %empty
#line 2526 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 726: // reservation_client_classes: "client-classes" $@107 ":" list_strings
#line 2532 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3998 "dhcp4_parser.cc"
    break;

  case 727: // $@108: %empty
#line 2540 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4010 "dhcp4_parser.cc"
    break;

  case 728: // relay: "relay" $@108 ":" "{" relay_map "}"
#line 2546 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4019 "dhcp4_parser.cc"
    break;

  case 730: // $@109: %empty
#line 2554 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 731: // ip_addresses: "ip-addresses" $@109 ":" list_strings
#line 2560 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4040 "dhcp4_parser.cc"
    break;

  case 732: // $@110: %empty
#line 2568 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4052 "dhcp4_parser.cc"
    break;

  case 733: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2574 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4061 "dhcp4_parser.cc"
    break;

  case 738: // not_empty_classes_list: not_empty_classes_list ","
#line 2585 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4069 "dhcp4_parser.cc"
    break;

  case 739: // $@111: %empty
#line 2590 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4079 "dhcp4_parser.cc"
    break;

  case 740: // client_class_entry: "{" $@111 client_class_params "}"
#line 2594 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4089 "dhcp4_parser.cc"
    break;

  case 745: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2606 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4097 "dhcp4_parser.cc"
    break;

  case 764: // $@112: %empty
#line 2632 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4106 "dhcp4_parser.cc"
    break;

  case 765: // client_class_test: "test" $@112 ":" "constant string"
#line 2635 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4116 "dhcp4_parser.cc"
    break;

  case 766: // $@113: %empty
#line 2641 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4125 "dhcp4_parser.cc"
    break;

  case 767: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2644 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4135 "dhcp4_parser.cc"
    break;

  case 768: // only_if_required: "only-if-required" ":" "boolean"
#line 2651 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4145 "dhcp4_parser.cc"
    break;

  case 769: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2657 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4155 "dhcp4_parser.cc"
    break;

  case 770: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2665 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4165 "dhcp4_parser.cc"
    break;

  case 771: // $@114: %empty
#line 2673 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4177 "dhcp4_parser.cc"
    break;

  case 772: // control_sockets: "control-sockets" $@114 ":" "[" control_socket_list "]"
#line 2679 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4186 "dhcp4_parser.cc"
    break;

  case 777: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2690 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4194 "dhcp4_parser.cc"
    break;

  case 778: // $@115: %empty
#line 2695 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4204 "dhcp4_parser.cc"
    break;

  case 779: // control_socket_entry: "{" $@115 control_socket_params "}"
#line 2699 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 782: // control_socket_params: control_socket_params ","
#line 2705 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4220 "dhcp4_parser.cc"
    break;

  case 796: // $@116: %empty
#line 2725 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4229 "dhcp4_parser.cc"
    break;

  case 797: // control_socket_type: "socket-type" $@116 ":" control_socket_type_value
#line 2728 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4238 "dhcp4_parser.cc"
    break;

  case 798: // control_socket_type_value: "unix"
#line 2734 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4244 "dhcp4_parser.cc"
    break;

  case 799: // control_socket_type_value: "http"
#line 2735 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4250 "dhcp4_parser.cc"
    break;

  case 800: // control_socket_type_value: "https"
#line 2736 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4256 "dhcp4_parser.cc"
    break;

  case 801: // $@117: %empty
#line 2739 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4265 "dhcp4_parser.cc"
    break;

  case 802: // control_socket_name: "socket-name" $@117 ":" "constant string"
#line 2742 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4275 "dhcp4_parser.cc"
    break;

  case 803: // $@118: %empty
#line 2748 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 804: // control_socket_address: "socket-address" $@118 ":" "constant string"
#line 2751 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4294 "dhcp4_parser.cc"
    break;

  case 805: // control_socket_port: "socket-port" ":" "integer"
#line 2757 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4304 "dhcp4_parser.cc"
    break;

  case 806: // cert_required: "cert-required" ":" "boolean"
#line 2763 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4314 "dhcp4_parser.cc"
    break;

  case 807: // $@119: %empty
#line 2769 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4326 "dhcp4_parser.cc"
    break;

  case 808: // http_headers: "http-headers" $@119 ":" "[" http_header_list "]"
#line 2775 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4335 "dhcp4_parser.cc"
    break;

  case 813: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2786 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4343 "dhcp4_parser.cc"
    break;

  case 814: // $@120: %empty
#line 2791 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 815: // http_header: "{" $@120 http_header_params "}"
#line 2795 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4361 "dhcp4_parser.cc"
    break;

  case 818: // http_header_params: http_header_params ","
#line 2801 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4369 "dhcp4_parser.cc"
    break;

  case 824: // $@121: %empty
#line 2813 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4378 "dhcp4_parser.cc"
    break;

  case 825: // header_value: "value" $@121 ":" "constant string"
#line 2816 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4388 "dhcp4_parser.cc"
    break;

  case 826: // $@122: %empty
#line 2824 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4400 "dhcp4_parser.cc"
    break;

  case 827: // authentication: "authentication" $@122 ":" "{" auth_params "}"
#line 2830 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 830: // auth_params: auth_params ","
#line 2839 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4419 "dhcp4_parser.cc"
    break;

  case 838: // $@123: %empty
#line 2853 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4428 "dhcp4_parser.cc"
    break;

  case 839: // auth_type: "type" $@123 ":" auth_type_value
#line 2856 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4437 "dhcp4_parser.cc"
    break;

  case 840: // auth_type_value: "basic"
#line 2861 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4443 "dhcp4_parser.cc"
    break;

  case 841: // $@124: %empty
#line 2864 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4452 "dhcp4_parser.cc"
    break;

  case 842: // realm: "realm" $@124 ":" "constant string"
#line 2867 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4462 "dhcp4_parser.cc"
    break;

  case 843: // $@125: %empty
#line 2873 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4471 "dhcp4_parser.cc"
    break;

  case 844: // directory: "directory" $@125 ":" "constant string"
#line 2876 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4481 "dhcp4_parser.cc"
    break;

  case 845: // $@126: %empty
#line 2882 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4493 "dhcp4_parser.cc"
    break;

  case 846: // clients: "clients" $@126 ":" "[" clients_list "]"
#line 2888 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4502 "dhcp4_parser.cc"
    break;

  case 851: // not_empty_clients_list: not_empty_clients_list ","
#line 2899 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4510 "dhcp4_parser.cc"
    break;

  case 852: // $@127: %empty
#line 2904 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4520 "dhcp4_parser.cc"
    break;

  case 853: // basic_auth: "{" $@127 clients_params "}"
#line 2908 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4528 "dhcp4_parser.cc"
    break;

  case 856: // clients_params: clients_params ","
#line 2914 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4536 "dhcp4_parser.cc"
    break;

  case 864: // $@128: %empty
#line 2928 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4545 "dhcp4_parser.cc"
    break;

  case 865: // user_file: "user-file" $@128 ":" "constant string"
#line 2931 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4555 "dhcp4_parser.cc"
    break;

  case 866: // $@129: %empty
#line 2939 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4567 "dhcp4_parser.cc"
    break;

  case 867: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2945 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4578 "dhcp4_parser.cc"
    break;

  case 870: // queue_control_params: queue_control_params ","
#line 2954 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4586 "dhcp4_parser.cc"
    break;

  case 877: // enable_queue: "enable-queue" ":" "boolean"
#line 2967 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4596 "dhcp4_parser.cc"
    break;

  case 878: // $@130: %empty
#line 2973 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4605 "dhcp4_parser.cc"
    break;

  case 879: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2976 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4615 "dhcp4_parser.cc"
    break;

  case 880: // capacity: "capacity" ":" "integer"
#line 2982 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4625 "dhcp4_parser.cc"
    break;

  case 881: // $@131: %empty
#line 2988 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4634 "dhcp4_parser.cc"
    break;

  case 882: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2991 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4643 "dhcp4_parser.cc"
    break;

  case 883: // $@132: %empty
#line 2998 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4655 "dhcp4_parser.cc"
    break;

  case 884: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 3004 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4666 "dhcp4_parser.cc"
    break;

  case 885: // $@133: %empty
#line 3011 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4676 "dhcp4_parser.cc"
    break;

  case 886: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 3015 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4686 "dhcp4_parser.cc"
    break;

  case 889: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3023 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4694 "dhcp4_parser.cc"
    break;

  case 901: // enable_updates: "enable-updates" ":" "boolean"
#line 3041 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4704 "dhcp4_parser.cc"
    break;

  case 902: // $@134: %empty
#line 3047 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4713 "dhcp4_parser.cc"
    break;

  case 903: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3050 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4723 "dhcp4_parser.cc"
    break;

  case 904: // server_port: "server-port" ":" "integer"
#line 3056 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4733 "dhcp4_parser.cc"
    break;

  case 905: // $@135: %empty
#line 3062 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4742 "dhcp4_parser.cc"
    break;

  case 906: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3065 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4752 "dhcp4_parser.cc"
    break;

  case 907: // sender_port: "sender-port" ":" "integer"
#line 3071 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4762 "dhcp4_parser.cc"
    break;

  case 908: // max_queue_size: "max-queue-size" ":" "integer"
#line 3077 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4772 "dhcp4_parser.cc"
    break;

  case 909: // $@136: %empty
#line 3083 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4781 "dhcp4_parser.cc"
    break;

  case 910: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3086 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4790 "dhcp4_parser.cc"
    break;

  case 911: // ncr_protocol_value: "udp"
#line 3092 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4796 "dhcp4_parser.cc"
    break;

  case 912: // ncr_protocol_value: "tcp"
#line 3093 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4802 "dhcp4_parser.cc"
    break;

  case 913: // $@137: %empty
#line 3096 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4811 "dhcp4_parser.cc"
    break;

  case 914: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3099 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4821 "dhcp4_parser.cc"
    break;

  case 915: // $@138: %empty
#line 3107 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4833 "dhcp4_parser.cc"
    break;

  case 916: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3113 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4843 "dhcp4_parser.cc"
    break;

  case 917: // $@139: %empty
#line 3119 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4853 "dhcp4_parser.cc"
    break;

  case 918: // sub_config_control: "{" $@139 config_control_params "}"
#line 3123 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4862 "dhcp4_parser.cc"
    break;

  case 921: // config_control_params: config_control_params ","
#line 3131 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4870 "dhcp4_parser.cc"
    break;

  case 924: // $@140: %empty
#line 3141 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4882 "dhcp4_parser.cc"
    break;

  case 925: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3147 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4891 "dhcp4_parser.cc"
    break;

  case 926: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3152 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4901 "dhcp4_parser.cc"
    break;

  case 927: // $@141: %empty
#line 3160 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4913 "dhcp4_parser.cc"
    break;

  case 928: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3166 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4922 "dhcp4_parser.cc"
    break;

  case 931: // loggers_entries: loggers_entries ","
#line 3175 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4930 "dhcp4_parser.cc"
    break;

  case 932: // $@142: %empty
#line 3181 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4940 "dhcp4_parser.cc"
    break;

  case 933: // logger_entry: "{" $@142 logger_params "}"
#line 3185 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4948 "dhcp4_parser.cc"
    break;

  case 936: // logger_params: logger_params ","
#line 3191 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4956 "dhcp4_parser.cc"
    break;

  case 944: // debuglevel: "debuglevel" ":" "integer"
#line 3205 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4966 "dhcp4_parser.cc"
    break;

  case 945: // $@143: %empty
#line 3211 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4975 "dhcp4_parser.cc"
    break;

  case 946: // severity: "severity" $@143 ":" "constant string"
#line 3214 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4985 "dhcp4_parser.cc"
    break;

  case 947: // $@144: %empty
#line 3220 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4997 "dhcp4_parser.cc"
    break;

  case 948: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3226 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5006 "dhcp4_parser.cc"
    break;

  case 951: // output_options_list_content: output_options_list_content ","
#line 3233 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5014 "dhcp4_parser.cc"
    break;

  case 952: // $@145: %empty
#line 3238 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5024 "dhcp4_parser.cc"
    break;

  case 953: // output_entry: "{" $@145 output_params_list "}"
#line 3242 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5032 "dhcp4_parser.cc"
    break;

  case 956: // output_params_list: output_params_list ","
#line 3248 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5040 "dhcp4_parser.cc"
    break;

  case 962: // $@146: %empty
#line 3260 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5049 "dhcp4_parser.cc"
    break;

  case 963: // output: "output" $@146 ":" "constant string"
#line 3263 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5059 "dhcp4_parser.cc"
    break;

  case 964: // flush: "flush" ":" "boolean"
#line 3269 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5069 "dhcp4_parser.cc"
    break;

  case 965: // maxsize: "maxsize" ":" "integer"
#line 3275 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5079 "dhcp4_parser.cc"
    break;

  case 966: // maxver: "maxver" ":" "integer"
#line 3281 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5089 "dhcp4_parser.cc"
    break;

  case 967: // $@147: %empty
#line 3287 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5098 "dhcp4_parser.cc"
    break;

  case 968: // pattern: "pattern" $@147 ":" "constant string"
#line 3290 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5108 "dhcp4_parser.cc"
    break;

  case 969: // $@148: %empty
#line 3296 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5120 "dhcp4_parser.cc"
    break;

  case 970: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3302 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5129 "dhcp4_parser.cc"
    break;

  case 973: // compatibility_params: compatibility_params ","
#line 3309 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5137 "dhcp4_parser.cc"
    break;

  case 979: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3321 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5147 "dhcp4_parser.cc"
    break;

  case 980: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3327 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5157 "dhcp4_parser.cc"
    break;

  case 981: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3333 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5167 "dhcp4_parser.cc"
    break;

  case 982: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3339 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5177 "dhcp4_parser.cc"
    break;


#line 5181 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1427;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     538, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,    39,    57,    67,    96,   132,   150,
     220,   232,   249,   256,   273,   275,   282,   291, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,    57,  -191,    53,   279,    63,   714,
     792,    88,   -33,   153,   627,  -110,   521,   172, -1427,    70,
      92,   297,   294,   320, -1427,    40, -1427, -1427, -1427, -1427,
     344,   387,   394, -1427, -1427, -1427,   395,   396, -1427, -1427,
   -1427,   404,   419,   423,   432,   433,   436,   437,   440,   441,
     444,   445,   451, -1427,   452,   453,   454,   455,   458, -1427,
   -1427, -1427, -1427,   459,   460,   462,   463,   464,   466,   467,
   -1427, -1427, -1427,   469, -1427, -1427, -1427, -1427, -1427,   470,
     471,   472, -1427, -1427, -1427, -1427, -1427,   473, -1427, -1427,
   -1427, -1427, -1427, -1427,   474,   475,   476, -1427, -1427,   478,
   -1427,    93, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   479,   486,
     487,   488, -1427,    94, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
     489, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   111,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,   490, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427,   129, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,   372,   386, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   426, -1427,
   -1427,   492, -1427, -1427, -1427,   496, -1427, -1427,   493,   499,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427,   500,   501,   502, -1427, -1427, -1427, -1427,
   -1427,   504,   506, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427,   139, -1427, -1427,
   -1427,   509, -1427,   514, -1427,   515,   517, -1427, -1427, -1427,
   -1427, -1427,   151, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427,   519,   160, -1427, -1427, -1427, -1427,    57,
      57, -1427,   287,   524, -1427, -1427,   525,   527,   529,   295,
     298,   299,   530,   533,   537,   307,   308,   543,   545,   547,
     314,   315,   321,   322,   325,   326,   328,   330,   331,   327,
     336,   334,   550,   338,   342,   341,   343,   346,   578,   580,
     584,   585,   350,   352,   355,   357,   358,   360,   359,   596,
     598,   600,   368,   607,   609,   611,   613,   615,   391,   399,
     410,   625,   631,   648,   649,   650,   420,   651,   652,   653,
     655,   656,   657,   425,   427,   428,   659,   662, -1427,   279,
   -1427,   666,   667,   668,   434,   435,   438,   439,    63, -1427,
     669,   674,   675,   677,   678,   680,   447,   683,   685,   686,
     687,   688,   714, -1427,   690,   465,   792, -1427,   692,   697,
     698,   701,   702,   703,   704,   705, -1427,    88, -1427,   706,
     707,   482,   717,   718,   719,   485, -1427,   153,   722,   510,
     511,   516,   724, -1427,   627,   725,   726,   -48, -1427,   520,
     737,   541,   750,   542,   544,   751,   753,   521, -1427,   755,
     557,   172, -1427, -1427, -1427,   772,   774,   776,   789,   790,
   -1427, -1427, -1427,   561,   576,   582, -1427, -1427,   810,   813,
     816, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427,   586, -1427, -1427, -1427, -1427, -1427,   -37,
     587,   588,   589, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
     817,   822,   823, -1427,   592,   226,   827,   826,   597, -1427,
   -1427, -1427,   830,   831,   833,   842,   844, -1427,   845,   848,
     847,   849,   621,   622, -1427, -1427, -1427,   855,   854, -1427,
     857,   274,   210, -1427, -1427, -1427, -1427, -1427,   626,   629,
     630,   863,   632,   633, -1427,   857,   857,   857,   634,   865,
   -1427,   636, -1427, -1427,   857,   637,   638,   639,   654,   658,
     660,   661, -1427,   663,   664, -1427,   665,   670,   671, -1427,
   -1427,   673, -1427, -1427, -1427,   857, -1427,   676,   826, -1427,
   -1427,   684, -1427,   693, -1427, -1427,    18,   694, -1427,   880,
   -1427, -1427,    57,   279,   172,    63,   293, -1427, -1427, -1427,
    1523,  1523,   883, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427,   885,   886,   892, -1427, -1427, -1427, -1427,
   -1427, -1427,   896, -1427, -1427, -1427,    51,   897,   898,   899,
      84,   103,   904,   -27,   521, -1427, -1427,   905,     3, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
     907, -1427, -1427, -1427, -1427, -1427, -1427,   763, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427,   883, -1427,   167,   169,   170, -1427, -1427,   171,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427,   918,   919,   920,
     921,   925,   927,   928,   931,   932,   933, -1427,   934,   935,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427,   183, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   203, -1427,
     936,   937, -1427, -1427,   938,   940, -1427, -1427,   939,   943,
   -1427, -1427,   941,   945, -1427, -1427,   944,   946, -1427, -1427,
   -1427, -1427, -1427, -1427,    44, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427,   947,   949, -1427, -1427,   948,   952, -1427, -1427,
     950,   954, -1427,   955,   956,   957,   958,   959,   960,   213,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427,   961,   962,   963,
   -1427,   247, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   964,
     965, -1427,   967, -1427,   968, -1427, -1427, -1427,   251, -1427,
   -1427, -1427, -1427, -1427,   254, -1427,    77, -1427,   969,   970,
     971,   972, -1427,   269, -1427, -1427, -1427, -1427, -1427,   721,
   -1427,   973,   966, -1427, -1427,   974, -1427,   975, -1427, -1427,
   -1427,   976,   979,   293, -1427,   980,   981,   982,   984,   739,
     738,   754,   749,   756,   762,   764,   773,   777,   780,  1015,
     784,   788,  1026,  1028,  1031,  1038,  1049,  1053,  1523, -1427,
   -1427,  1523, -1427,   883,   714, -1427,   885,   153, -1427,   886,
     627, -1427,   892,  1411, -1427,   896,    51, -1427,   148, -1427,
     897,    88, -1427,   898,  -110, -1427,   899,   820,   824,   852,
     867,   869,   874,    84, -1427,   853,   878,   888,   103, -1427,
     277, -1427,   904,   861,  1056,   894,  1067,   -27, -1427, -1427,
     217,   905, -1427,   881,   906,   908,   911,     3, -1427, -1427,
    1076,  1084,   792, -1427,   907,  1088, -1427, -1427,   866,   901,
   -1427,   922,   930,   942,   977, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427,    34, -1427, -1427,   978,   983,
     985,   351,   986,   987, -1427,   296, -1427,   316, -1427,  1115,
   -1427,  1149, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427,   333, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,  1158,
    1160, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,  1161,  1171, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427,  1169, -1427,   376, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427,  1178, -1427,  1189, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427,   378, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427,   988, -1427,    57, -1427, -1427,  1191, -1427, -1427,
   -1427, -1427, -1427,   385, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427,   989,   389, -1427,   857, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,  1411,
   -1427,  1193,  1196,   990,   991, -1427,   148, -1427, -1427,  1198,
    1199,  1200,   994,  1201,   993,  1202,   277, -1427, -1427, -1427,
    1203,   996,  1204,   217, -1427, -1427, -1427, -1427, -1427,   992,
     998, -1427, -1427, -1427,   163,   999,  1000, -1427,  1205, -1427,
    1206, -1427,  1208, -1427,  1001, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,    69,  1209,  1210, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427,   417, -1427, -1427, -1427, -1427,
   -1427, -1427,  1212,  1207, -1427, -1427,   209, -1427,  1215,  1223,
    1224,  1235,    69, -1427,   202, -1427,  1209,   114,  1210, -1427,
    1032,  1003,  1004,  1237, -1427, -1427, -1427, -1427, -1427, -1427,
     418, -1427, -1427, -1427, -1427,  1239,  1240,  1241, -1427,   421,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427,  1242,  1243,   202, -1427,  1244,  1006,  1012,  1013,  1249,
     114, -1427, -1427,  1248,  1252, -1427,  1019, -1427,  1020, -1427,
   -1427, -1427,  1021, -1427,    27, -1427,  1242, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427,   430, -1427, -1427,
   -1427,  1256,    27, -1427,  1025, -1427, -1427
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   218,     9,   406,    11,   637,    13,
     683,    15,   552,    17,   561,    19,   600,    21,   368,    23,
     885,    25,   917,    27,    46,    39,     0,     0,     0,     0,
       0,   685,     0,   563,   602,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   915,   203,   236,
       0,     0,     0,   705,   707,   709,     0,     0,   234,   247,
     249,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,     0,   166,
     173,   175,   177,     0,     0,     0,     0,     0,     0,     0,
     397,   550,   591,     0,   158,   181,   488,   670,   672,     0,
       0,     0,   330,   732,   674,   359,   380,     0,   345,   771,
     866,   883,   191,   193,     0,     0,     0,   927,   969,     0,
     142,     0,    67,    70,    71,    72,    73,    74,   107,   108,
     109,   110,   111,   112,    75,   103,   138,   139,    92,    93,
      94,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   114,   115,   130,   131,   132,
     134,   135,   136,   140,   141,    78,    79,   100,    80,    81,
      82,   133,    86,    87,    76,   104,   105,   106,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   113,   137,   220,   222,   226,     0,     0,
       0,     0,   217,     0,   205,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   468,   470,   472,   628,   466,   474,
       0,   478,   480,   482,   476,   727,   465,   411,   412,   413,
     414,   415,   440,   441,   442,   443,   444,   445,   463,   430,
     431,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   464,     0,
     408,   418,   435,   436,   437,   419,   421,   422,   423,   424,
     426,   427,   428,   420,   416,   417,   438,   439,   425,   432,
     433,   434,   429,   667,     0,   666,   649,   650,   651,   652,
     653,   654,   655,   656,   657,   658,   659,   660,   661,   662,
     663,   645,   646,   647,   648,   644,     0,   639,   642,   643,
     664,   665,   725,   711,   713,   715,   719,   717,   723,   721,
     704,   698,   702,   703,     0,   686,   687,   699,   700,   701,
     695,   690,   696,   692,   693,   694,   697,   691,     0,   581,
     297,     0,   585,   583,   588,     0,   577,   578,     0,   564,
     565,   568,   580,   569,   570,   571,   587,   572,   573,   574,
     575,   576,   619,     0,     0,     0,   626,   617,   618,   621,
     622,     0,   603,   604,   607,   608,   609,   610,   611,   612,
     613,   616,   614,   615,   376,   378,   373,     0,   370,   374,
     375,     0,   902,     0,   905,     0,     0,   909,   913,   900,
     898,   899,     0,   887,   890,   891,   892,   893,   894,   895,
     896,   897,   924,     0,     0,   919,   922,   923,    45,    50,
       0,    37,    43,     0,    64,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    69,
      66,     0,     0,     0,     0,     0,     0,     0,   207,   219,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   410,   407,     0,     0,   641,   638,     0,     0,
       0,     0,     0,     0,     0,     0,   684,   689,   553,     0,
       0,     0,     0,     0,     0,     0,   562,   567,     0,     0,
       0,     0,     0,   601,   606,     0,     0,   372,   369,     0,
       0,     0,     0,     0,     0,     0,     0,   889,   886,     0,
       0,   921,   918,    49,    41,     0,     0,     0,     0,     0,
     160,   161,   162,     0,     0,     0,   201,   202,     0,     0,
       0,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,     0,   196,   197,   163,   164,   165,     0,
       0,     0,     0,   179,   180,   187,   188,   189,   190,   195,
       0,     0,     0,   157,     0,     0,     0,     0,     0,   484,
     485,   486,     0,     0,     0,     0,     0,   770,     0,     0,
       0,     0,     0,     0,   198,   199,   200,     0,     0,    68,
       0,     0,     0,   230,   231,   232,   233,   206,     0,     0,
       0,     0,     0,     0,   487,     0,     0,     0,     0,     0,
     409,     0,   669,   640,     0,     0,     0,     0,     0,     0,
       0,     0,   688,     0,     0,   579,     0,     0,     0,   590,
     566,     0,   623,   624,   625,     0,   605,     0,     0,   371,
     901,     0,   904,     0,   907,   908,     0,     0,   888,     0,
     926,   920,     0,     0,     0,     0,     0,   706,   708,   710,
       0,     0,   251,   156,   168,   169,   170,   171,   172,   167,
     174,   176,   178,   399,   554,   593,   159,   183,   184,   185,
     186,   182,   490,    38,   671,   673,     0,   734,   676,   361,
       0,     0,   773,     0,     0,   192,   194,     0,     0,    51,
     221,   224,   225,   223,   228,   229,   227,   469,   471,   473,
     630,   467,   475,   479,   481,   483,   477,     0,   668,   726,
     712,   714,   716,   720,   718,   724,   722,   582,   298,   586,
     584,   589,   620,   627,   377,   379,   903,   906,   911,   912,
     910,   914,   251,    42,     0,     0,     0,   243,   245,     0,
     238,   241,   242,   286,   288,   290,   294,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   308,     0,     0,
     315,   317,   319,   321,   323,   324,   325,   326,   327,   328,
     292,   285,     0,   258,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,     0,   256,
       0,   252,   253,   404,     0,   400,   401,   559,     0,   555,
     556,   598,     0,   594,   595,   495,     0,   491,   492,   340,
     341,   342,   343,   344,     0,   332,   335,   336,   337,   338,
     339,   739,     0,   735,   736,   681,     0,   677,   678,   366,
       0,   362,   363,     0,     0,     0,     0,     0,     0,     0,
     382,   385,   386,   387,   388,   389,   390,     0,     0,     0,
     355,     0,   347,   350,   351,   352,   353,   354,   778,     0,
     774,   775,     0,   878,     0,   881,   874,   875,     0,   868,
     871,   872,   873,   876,     0,   932,     0,   929,     0,     0,
       0,     0,   978,     0,   971,   974,   975,   976,   977,    53,
     635,     0,   631,   632,   730,     0,   729,     0,    62,   916,
     204,     0,     0,   240,   237,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   260,   235,
     248,     0,   250,   255,     0,   398,   403,   563,   551,   558,
     602,   592,   597,     0,   489,   494,   334,   331,   741,   733,
     738,   685,   675,   680,     0,   360,   365,     0,     0,     0,
       0,     0,     0,   384,   381,     0,     0,     0,   349,   346,
       0,   772,   777,     0,     0,     0,     0,   870,   867,   884,
       0,   931,   928,     0,     0,     0,     0,   973,   970,    55,
       0,    54,     0,   629,   634,     0,   728,   925,     0,     0,
     239,     0,     0,     0,     0,   296,   299,   300,   301,   302,
     303,   304,   305,   306,   307,     0,   313,   314,     0,     0,
       0,     0,     0,     0,   259,     0,   254,     0,   402,     0,
     557,     0,   596,   549,   519,   520,   521,   503,   504,   524,
     525,   526,   527,   528,   529,   547,   506,   507,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   548,   500,   501,   502,   515,
     516,   517,   518,   512,   513,   514,     0,   497,   505,   522,
     523,   508,   509,   510,   511,   493,   333,   764,   766,     0,
       0,   758,   759,   760,   761,   762,   763,   751,   752,   756,
     757,   753,   754,   755,     0,   742,   743,   746,   747,   748,
     749,   750,   737,     0,   679,     0,   364,   391,   392,   393,
     394,   395,   396,   383,   356,   357,   358,   348,   796,   801,
     803,     0,   826,     0,   807,   795,   788,   789,   790,   793,
     794,     0,   780,   783,   784,   785,   786,   791,   792,   787,
     776,   877,     0,   880,     0,   869,   947,     0,   945,   943,
     937,   941,   942,     0,   934,   939,   940,   938,   930,   979,
     980,   981,   982,   972,    52,    57,     0,   633,     0,   244,
     246,   287,   289,   291,   295,   310,   311,   312,   309,   316,
     318,   320,   322,   329,   293,   257,   405,   560,   599,   499,
     496,     0,     0,     0,     0,   740,   745,   682,   367,     0,
       0,     0,     0,     0,     0,     0,   782,   779,   879,   882,
       0,     0,     0,   936,   933,    56,   636,   731,   498,     0,
       0,   768,   769,   744,     0,     0,     0,   805,     0,   806,
       0,   781,     0,   944,     0,   935,   765,   767,   798,   799,
     800,   797,   802,   804,     0,   809,     0,   946,   838,   841,
     843,   845,   837,   836,   835,     0,   828,   831,   832,   833,
     834,   814,     0,   810,   811,   952,     0,   949,     0,     0,
       0,     0,   830,   827,     0,   808,   813,     0,   951,   948,
       0,     0,     0,     0,   829,   824,   823,   819,   821,   822,
       0,   816,   820,   812,   962,     0,     0,     0,   967,     0,
     954,   957,   958,   959,   960,   961,   950,   840,   839,   842,
     844,   847,     0,   818,   815,     0,     0,     0,     0,     0,
     956,   953,   852,     0,   848,   849,     0,   817,     0,   964,
     965,   966,     0,   955,     0,   846,   851,   825,   963,   968,
     864,   863,   857,   859,   860,   861,   862,     0,   854,   858,
     850,     0,   856,   853,     0,   855,   865
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427,   -53, -1427,  -630, -1427,   528,
   -1427, -1427, -1427, -1427, -1427, -1427,  -674, -1427, -1427, -1427,
     -67, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   188,   728,
      12,    15,    23,    25,    81,    82,    86,    87,    89,   100,
     102, -1427, -1427, -1427, -1427,   107, -1427, -1427,   118,   121,
      35,    41,    43,    46, -1427, -1427,    48, -1427,    54, -1427,
      56, -1427,    59,   131,    61, -1427, -1427,    64,    66,    71,
      74,    76, -1427,    79, -1427,   133, -1427, -1427, -1427, -1427,
   -1427,    31, -1427, -1427, -1427,   508,   729, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427,   242, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427,   431, -1427,   219, -1427,  -748,
     230, -1427, -1427, -1426, -1427, -1405, -1427, -1389, -1427, -1427,
   -1427, -1427,   -32, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1061, -1427,
   -1060, -1427, -1055, -1427,   140, -1427, -1427, -1427, -1427, -1427,
   -1427,   208, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
     191, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   206, -1427,
   -1427, -1427,   212,   691, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427,   201, -1427, -1427, -1427, -1427, -1427, -1427, -1048, -1427,
   -1427, -1427,   233, -1427, -1427, -1427,   236,   731, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1036, -1427,   -58, -1427,
     -49, -1427,   -36, -1427,    68, -1427,   135,   136,   138, -1427,
   -1427, -1427, -1427, -1427,   231, -1427, -1427,   -28,   -46, -1427,
   -1427, -1427, -1427, -1427,   238, -1427, -1427, -1427,   241, -1427,
     708, -1427,   -69, -1427, -1427, -1427, -1427, -1427,   -50, -1427,
   -1427, -1427, -1427, -1427,     2, -1427, -1427, -1427,   239, -1427,
   -1427, -1427,   240, -1427,   710, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   194,
   -1427, -1427, -1427,   190,   743, -1427, -1427, -1427,   -51, -1427,
     -16, -1427,   -59, -1427, -1427, -1427,   243, -1427, -1427, -1427,
     234, -1427,   735,   -55, -1427,   -20, -1427,    -4, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1035, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427,   244, -1427, -1427, -1427,   -13, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427,   225, -1427, -1427,   -18, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   -87, -1427,
   -1427,  -119, -1427, -1427, -1427, -1427, -1427,   -77, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,  -140,
   -1427, -1427,  -153, -1427, -1427, -1427, -1427, -1427,   235, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   536,
     732, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,   579,   734,
   -1427, -1427, -1427, -1427, -1427, -1427,   245, -1427, -1427,    -7,
   -1427, -1427, -1427, -1427, -1427, -1427,   -68, -1427, -1427,  -107,
   -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427, -1427,
     248, -1427, -1427, -1427, -1427
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   784,
      82,    83,    39,    64,    79,    80,   800,  1009,  1110,  1111,
     881,    41,    66,    85,   463,    86,    43,    67,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   492,   176,   177,   513,   178,   179,   180,
     181,   182,   183,   184,   498,   769,   185,   499,   186,   500,
     187,   501,   188,   189,   190,   514,   781,   191,   192,   193,
     194,   195,   531,   196,   532,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   467,   243,   244,    45,    68,   245,
     541,   246,   542,   803,   247,   543,   806,   248,   249,   250,
     251,   206,   477,   207,   468,   849,   850,   851,  1021,   852,
    1022,   208,   478,   209,   479,   910,   911,   912,  1051,   882,
     883,   884,  1025,   885,  1026,   886,  1027,   887,  1047,   888,
    1028,   889,   890,   580,   891,   892,   893,   894,   895,   896,
     897,   898,   899,   900,  1039,  1308,   901,   902,   903,  1042,
     904,  1043,   905,  1044,   906,  1045,   907,  1046,   210,   521,
     934,   935,   936,   937,   938,   939,   940,   211,   527,   971,
     972,   973,   974,   975,   212,   524,   950,   951,   952,  1074,
      59,    75,   427,   428,   429,   595,   430,   596,   213,   525,
     959,   960,   961,   962,   963,   964,   965,   966,   214,   509,
     914,   915,   916,  1054,    47,    69,   299,   300,   301,   554,
     302,   550,   303,   551,   304,   552,   305,   555,   306,   560,
     307,   557,   308,   558,   309,   559,   215,   216,   217,   313,
     218,   515,   926,   927,   928,  1063,  1196,  1197,   219,   510,
      53,    72,   918,   919,   920,  1057,    55,    73,   388,   389,
     390,   391,   392,   393,   394,   579,   395,   583,   396,   582,
     397,   398,   584,   399,   220,   511,   922,   923,   924,  1060,
      57,    74,   411,   412,   413,   414,   415,   588,   416,   417,
     418,   419,   420,   421,   592,   315,   553,  1011,  1012,  1013,
    1112,    49,    70,   346,   347,   348,   564,   349,   221,   516,
     222,   517,   223,   523,   946,   947,   948,  1071,    51,    71,
     364,   365,   366,   224,   472,   225,   473,   226,   474,   370,
     569,   371,   570,   372,   571,   373,   573,   374,   572,   375,
     575,   376,   574,   377,   568,   322,   561,  1015,  1016,  1115,
     227,   522,   942,   943,   944,  1068,  1224,  1225,  1226,  1227,
    1228,  1321,  1229,  1322,  1230,  1231,   228,   229,   528,   979,
     980,   981,  1090,  1261,  1262,  1263,  1329,  1371,  1264,  1330,
    1265,  1331,  1266,  1267,  1268,  1335,  1392,  1393,  1394,  1404,
    1420,  1421,  1422,  1442,  1269,  1333,  1385,  1386,  1387,  1398,
    1438,  1388,  1399,  1389,  1400,  1390,  1401,  1453,  1454,  1455,
    1464,  1477,  1478,  1479,  1481,   230,   529,   988,   989,   990,
     991,  1094,   992,   993,  1096,   231,   530,    61,    76,   442,
     443,   444,   445,   600,   446,   447,   602,   448,   449,   450,
     605,   840,   451,   606,   232,   466,    63,    77,   454,   455,
     456,   609,   457,   233,   536,   996,   997,  1100,  1283,  1284,
    1285,  1286,  1342,  1287,  1340,  1396,  1397,  1407,  1429,  1430,
    1431,  1445,  1432,  1433,  1434,  1435,  1449,   234,   537,  1003,
    1004,  1005,  1006,  1007,  1008
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     160,   242,   266,   325,   360,   409,   386,   407,   426,   439,
     318,    78,   341,   908,   319,  1187,   367,   252,   316,   350,
     362,   342,   400,   422,   410,   440,   378,  1188,  1204,  1256,
    1257,   813,   814,   815,   343,  1258,   838,   783,  1472,    28,
     819,   387,   408,   464,   424,   425,    81,  1066,   465,   320,
    1067,   368,   253,   317,   351,   363,  1472,   401,   423,  1473,
     441,   833,    29,    84,    30,   321,    31,   369,   854,   855,
     131,   314,   345,   361,    40,  1474,   458,  1473,   235,   236,
    1101,   267,   237,  1102,   268,   238,   239,   240,   241,  1305,
    1306,  1307,   269,  1474,   270,   459,   539,   548,   137,   138,
     298,   540,   549,    42,   281,   326,   424,   425,   783,  1378,
     282,   327,   283,   328,   562,   284,   329,   285,   330,   563,
      93,    94,    95,   286,   331,   287,   332,   159,   288,   333,
     290,   334,   566,   291,   335,   292,   336,   567,   344,    44,
     293,   337,   597,   294,   338,   295,   339,   598,   296,   340,
     271,   272,   137,   138,   607,   273,   274,    46,   275,   608,
     982,   983,   984,   611,   764,   765,   766,   767,   612,   276,
     539,   277,   611,   548,  1023,  1018,   278,  1019,  1020,  1024,
      93,    94,    95,    96,   452,   453,  1048,   279,   137,   138,
     280,  1049,   132,   379,   137,   138,   929,   930,   931,   932,
     289,   933,   297,   768,   310,   311,  1048,   312,  1470,   880,
     985,  1050,  1408,   137,   138,  1409,  1083,   839,   101,   102,
     103,  1084,   352,   998,   999,  1000,  1001,    48,   137,   138,
     804,   805,   353,   354,   355,   356,   357,   358,   359,    50,
     159,   953,   954,   955,   956,   957,   958,  1379,  1380,  1381,
    1088,   131,   132,   380,  1097,  1089,    52,   607,   380,  1098,
     381,   382,  1099,    54,   159,   383,   384,   385,   967,   968,
     969,  1187,  1107,   137,   138,  1256,  1257,  1108,   137,   138,
      56,  1258,    58,  1188,  1204,  1207,  1208,  1209,  1210,    60,
      87,   801,   802,    88,    32,    33,    34,    35,    62,  1048,
     159,   460,   461,  1145,  1315,    89,   159,   380,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   562,
     847,   848,   380,   462,  1316,   159,  1424,   137,   138,  1425,
    1426,  1427,  1428,  1368,  1369,  1370,  1319,   870,   871,   872,
     159,  1320,   137,   138,   777,   778,   779,   780,   469,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   597,
     576,  1336,   131,   132,  1328,   159,  1337,  1415,  1343,   577,
     159,   470,   566,  1344,   133,   134,   135,  1346,   471,   475,
     476,   136,   137,   138,   137,   138,   613,   614,   480,   139,
     140,   141,   142,   143,   873,   874,   875,   876,   877,   878,
    1402,  1443,   144,   481,  1450,  1403,  1444,   482,  1276,  1451,
    1277,  1278,   145,  1482,   578,   146,   483,   484,  1483,   159,
     485,   486,   147,   148,   487,   488,  1248,   149,   489,   490,
    1249,  1250,  1251,  1252,   159,   491,   493,   494,   495,   496,
    1253,  1254,   497,   502,   503,   150,   504,   505,   506,   151,
     507,   508,   160,   512,   518,   519,   520,   526,   533,   534,
     535,   242,   538,   544,   152,   153,   154,   155,   156,   157,
     545,   546,   547,   556,   565,   266,   581,   252,   158,   325,
     585,   586,   587,   318,   589,   590,   591,   319,   341,   594,
     360,   316,   593,   599,   159,   350,   159,   342,   601,   603,
     386,   604,   367,   610,   615,   409,   362,   407,   616,   617,
     343,   618,   253,   619,   623,   620,   400,   624,   621,   622,
     439,   625,   320,   422,   410,   626,   317,   628,   627,   629,
     351,   630,   631,   632,   643,   387,   440,   368,   321,   633,
     634,   363,   408,   635,   314,   640,   636,   637,   345,   638,
     639,   401,   642,   369,   267,   641,   644,   268,   423,   361,
     645,   646,   649,   647,   650,   269,   648,   270,   651,   652,
     653,   441,   654,   298,   655,   656,   657,   281,   658,   659,
     660,   326,   661,   282,   662,   283,   663,   327,   284,   328,
     285,   664,   329,   665,   330,   666,   286,   667,   287,   668,
     331,   288,   332,   290,  1347,   333,   291,   334,   292,   672,
     335,   669,   336,   293,   344,   673,   294,   337,   295,   670,
     338,   296,   339,   271,   272,   340,   137,   138,   273,   274,
     671,   275,   674,   675,   676,   678,   679,   680,   677,   681,
     682,   683,   276,   687,   277,   684,   688,   685,   686,   278,
     690,   691,   692,   698,   693,   694,   695,   696,   699,   700,
     279,   701,   702,   280,   703,   704,   160,   705,   242,   706,
     707,   708,   709,   289,   711,   297,   714,   310,   311,   843,
     312,   715,   716,   712,   252,   717,   718,   719,   720,   721,
     723,   724,   431,   432,   433,   434,   435,   436,   437,   438,
     725,   726,   727,   728,   970,   729,   731,   439,   735,   737,
     738,  1002,   380,   402,   381,   382,   403,   404,   405,   253,
     976,   741,   986,   440,    91,    92,    93,    94,    95,    96,
     732,   733,   137,   138,   743,   746,   734,   747,   159,   749,
     740,   406,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   977,   752,   987,   441,   742,
     744,   753,   745,   754,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   750,   755,   756,   757,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   758,   254,   255,   256,   760,   132,   759,
     761,   762,   773,   763,   770,   771,   772,   774,   775,   776,
     134,   135,   782,    30,   785,   786,   787,   257,   788,   137,
     138,   258,   259,   260,   139,   140,   141,   789,   261,   262,
     263,   790,   791,   792,   793,   264,   794,   144,   795,   796,
     797,   798,   799,   807,   159,   265,   808,   809,   810,   811,
     812,   816,   817,   818,   820,   821,   822,   116,   117,   118,
     119,   120,   121,   122,   123,   842,   125,   126,   127,   128,
     909,   823,   913,   917,   841,   824,   132,   825,   826,   921,
     827,   828,   829,   925,   941,   945,   949,   830,   831,   135,
     832,   978,   995,   834,  1010,  1014,   323,   137,   138,   152,
     153,   836,  1029,  1030,  1031,  1032,   261,   262,   263,  1033,
     837,  1034,  1035,   264,   324,  1036,  1037,  1038,  1040,  1041,
    1053,   844,  1052,  1056,  1055,  1058,  1059,  1061,  1062,  1065,
    1064,   159,  1070,  1069,  1072,  1073,  1075,  1076,  1109,  1077,
    1078,  1079,  1080,  1081,  1082,  1085,  1086,  1087,  1092,  1114,
    1091,  1093,  1095,  1103,  1104,  1105,  1106,  1125,  1126,  1113,
    1118,  1117,  1116,  1119,  1121,  1122,  1123,   266,  1124,  1128,
     386,   409,  1127,   407,  1129,   318,  1153,   152,   153,   319,
    1130,  1211,  1131,   316,   360,  1189,   400,   426,  1201,   422,
     410,  1132,  1199,  1221,  1190,  1133,   367,  1219,  1134,  1135,
     362,   970,  1217,  1255,  1136,   387,  1137,  1191,   408,   159,
    1138,  1186,  1139,  1279,   320,  1140,  1216,   976,   317,  1259,
    1002,   401,  1141,  1202,   423,   325,   986,  1200,  1222,  1281,
     321,   368,  1220,  1142,   341,   363,   314,  1143,  1237,  1203,
    1272,   350,  1238,   342,  1223,  1198,   267,   369,  1280,   268,
    1218,  1274,   977,   361,  1260,  1154,   343,   269,  1155,   270,
    1212,   987,  1294,  1213,  1282,   298,  1156,  1295,  1157,   281,
    1239,  1214,  1298,  1244,  1185,   282,   351,   283,  1168,  1215,
     284,  1271,   285,  1299,  1169,  1240,  1170,  1241,   286,  1171,
     287,  1172,  1242,   288,   345,   290,  1245,  1173,   291,  1174,
     292,  1289,  1175,  1317,  1177,   293,  1246,  1178,   294,  1179,
     295,  1192,  1273,   296,  1180,   271,   272,  1181,  1300,  1182,
     273,   274,  1183,   275,  1158,  1159,  1290,   326,  1291,  1160,
    1161,  1292,  1162,   327,   276,   328,   277,  1318,   329,  1301,
     330,   278,  1323,  1163,  1324,  1164,   331,  1302,   332,  1325,
    1165,   333,   279,   334,  1326,   280,   335,  1327,   336,  1303,
     344,  1166,  1332,   337,  1167,   289,   338,   297,   339,   310,
     311,   340,   312,  1334,  1176,  1341,  1184,  1349,  1193,  1194,
    1350,  1195,  1354,  1355,  1356,  1358,  1360,  1362,  1364,  1437,
    1406,  1375,  1374,  1376,  1304,  1309,  1391,  1395,  1405,  1410,
    1310,  1339,  1311,  1313,  1314,  1338,  1345,  1411,  1412,  1366,
    1351,  1352,  1357,  1359,  1363,  1367,  1372,  1373,  1377,  1413,
    1439,  1440,  1441,  1446,  1447,  1448,  1459,  1456,  1458,  1452,
    1460,  1461,  1153,  1462,  1465,  1466,  1467,  1468,  1469,  1211,
    1484,  1189,  1486,   846,  1201,  1120,   835,   689,  1199,  1255,
    1190,  1221,  1146,  1017,  1206,  1219,  1279,   697,  1144,  1247,
    1217,  1312,  1236,  1191,  1243,  1259,  1235,  1186,   739,  1148,
    1147,  1348,  1281,   710,  1216,   730,  1205,  1150,  1149,  1202,
    1151,  1152,  1296,  1200,   736,  1233,  1222,  1382,  1297,   713,
    1220,  1280,   722,  1353,  1232,  1203,  1234,  1270,  1361,  1423,
    1260,  1198,  1223,  1383,  1457,  1414,  1480,  1282,  1218,  1485,
     994,  1154,  1275,   845,  1155,  1382,  1365,  1416,  1212,   748,
    1436,  1213,  1156,  1463,  1157,   751,  1288,     0,     0,  1214,
    1185,  1383,     0,  1418,  1168,  1293,     0,  1215,  1384,     0,
    1169,     0,  1170,     0,     0,  1171,     0,  1172,     0,     0,
       0,     0,  1417,  1173,     0,  1174,  1416,     0,  1175,     0,
    1177,     0,     0,  1178,     0,  1179,  1384,  1192,  1419,     0,
    1180,     0,  1418,  1181,     0,  1182,     0,  1471,  1183,     0,
    1158,  1159,     0,     0,     0,  1160,  1161,     0,  1162,     0,
       0,  1417,     0,  1475,     0,  1471,     0,     0,     0,  1163,
       0,  1164,     0,     0,     0,     0,  1165,  1419,     0,     0,
       0,  1475,     0,     0,     0,     0,     0,  1166,     0,     0,
    1167,    91,    92,    93,    94,    95,    96,     0,  1476,     0,
    1176,     0,  1184,     0,  1193,  1194,     0,  1195,     0,     0,
       0,     0,     0,     0,     0,     0,  1476,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     0,     0,     0,     0,   132,   380,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,   135,     0,
       0,     0,     0,     0,     0,     0,   137,   138,     0,   259,
       0,   139,   140,   141,     0,   261,   262,   263,     0,     0,
       0,     0,   264,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   265,   853,   854,   855,   856,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   866,   867,     0,     0,
       0,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     877,   878,   879,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,   153,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   380,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   880,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    74,    73,    74,    75,    76,
      69,    64,    70,   761,    69,  1063,    71,    68,    69,    70,
      71,    70,    73,    74,    74,    76,    72,  1063,  1063,  1090,
    1090,   705,   706,   707,    70,  1090,    18,   667,  1464,     0,
     714,    73,    74,     3,   154,   155,   237,     3,     8,    69,
       6,    71,    68,    69,    70,    71,  1482,    73,    74,  1464,
      76,   735,     5,    10,     7,    69,     9,    71,    41,    42,
     103,    69,    70,    71,     7,  1464,     6,  1482,    15,    16,
       3,    69,    19,     6,    69,    22,    23,    24,    25,    55,
      56,    57,    69,  1482,    69,     3,     3,     3,   125,   126,
      69,     8,     8,     7,    69,    70,   154,   155,   738,    40,
      69,    70,    69,    70,     3,    69,    70,    69,    70,     8,
      32,    33,    34,    69,    70,    69,    70,   237,    69,    70,
      69,    70,     3,    69,    70,    69,    70,     8,    70,     7,
      69,    70,     3,    69,    70,    69,    70,     8,    69,    70,
      69,    69,   125,   126,     3,    69,    69,     7,    69,     8,
     187,   188,   189,     3,   201,   202,   203,   204,     8,    69,
       3,    69,     3,     3,     3,     8,    69,     8,     8,     8,
      32,    33,    34,    35,    12,    13,     3,    69,   125,   126,
      69,     8,   104,    40,   125,   126,   145,   146,   147,   148,
      69,   150,    69,   240,    69,    69,     3,    69,   181,   182,
     237,     8,     3,   125,   126,     6,     3,   199,    70,    71,
      72,     8,   134,   220,   221,   222,   223,     7,   125,   126,
      20,    21,   144,   145,   146,   147,   148,   149,   150,     7,
     237,   157,   158,   159,   160,   161,   162,   178,   179,   180,
       3,   103,   104,   105,     3,     8,     7,     3,   105,     8,
     107,   108,     8,     7,   237,   112,   113,   114,   165,   166,
     167,  1319,     3,   125,   126,  1336,  1336,     8,   125,   126,
       7,  1336,     7,  1319,  1319,   137,   138,   139,   140,     7,
      11,    17,    18,    14,   237,   238,   239,   240,     7,     3,
     237,     4,     8,  1051,     8,    26,   237,   105,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     3,
      27,    28,   105,     3,     8,   237,   212,   125,   126,   215,
     216,   217,   218,   170,   171,   172,     3,    60,    61,    62,
     237,     8,   125,   126,   118,   119,   120,   121,     4,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,     3,
       8,     3,   103,   104,     8,   237,     8,   185,     3,     3,
     237,     4,     3,     8,   115,   116,   117,     8,     4,     4,
       4,   122,   125,   126,   125,   126,   459,   460,     4,   130,
     131,   132,   133,   134,    63,    64,    65,    66,    67,    68,
       3,     3,   143,     4,     3,     8,     8,     4,   211,     8,
     213,   214,   153,     3,     8,   156,     4,     4,     8,   237,
       4,     4,   163,   164,     4,     4,   169,   168,     4,     4,
     173,   174,   175,   176,   237,     4,     4,     4,     4,     4,
     183,   184,     4,     4,     4,   186,     4,     4,     4,   190,
       4,     4,   539,     4,     4,     4,     4,     4,     4,     4,
       4,   548,     4,     4,   205,   206,   207,   208,   209,   210,
       4,     4,     4,     4,     4,   562,     4,   548,   219,   566,
       4,     8,     3,   562,     4,     4,     4,   562,   566,     3,
     577,   562,     8,     4,   237,   566,   237,   566,     4,     4,
     587,     4,   577,     4,   237,   594,   577,   594,     4,     4,
     566,     4,   548,     4,     4,   240,   587,     4,   240,   240,
     607,     4,   562,   594,   594,   238,   562,     4,   240,     4,
     566,     4,   238,   238,     4,   587,   607,   577,   562,   238,
     238,   577,   594,   238,   562,   238,   240,   239,   566,   239,
     239,   587,   238,   577,   562,   239,   238,   562,   594,   577,
     238,   240,     4,   240,     4,   562,   240,   562,     4,     4,
     240,   607,   240,   562,   239,   238,   238,   562,   238,   240,
       4,   566,     4,   562,     4,   562,   238,   566,   562,   566,
     562,     4,   566,     4,   566,     4,   562,     4,   562,     4,
     566,   562,   566,   562,  1298,   566,   562,   566,   562,     4,
     566,   240,   566,   562,   566,     4,   562,   566,   562,   240,
     566,   562,   566,   562,   562,   566,   125,   126,   562,   562,
     240,   562,     4,     4,     4,     4,     4,     4,   238,     4,
       4,     4,   562,     4,   562,   240,     4,   240,   240,   562,
       4,     4,     4,     4,   240,   240,   238,   238,     4,     4,
     562,     4,     4,   562,     4,   238,   753,     4,   755,     4,
       4,     4,     4,   562,     4,   562,     4,   562,   562,   752,
     562,     4,     4,   238,   755,     4,     4,     4,     4,     4,
       4,     4,   191,   192,   193,   194,   195,   196,   197,   198,
     238,     4,     4,     4,   791,   240,     4,   794,     4,     4,
       4,   798,   105,   106,   107,   108,   109,   110,   111,   755,
     791,     4,   793,   794,    30,    31,    32,    33,    34,    35,
     240,   240,   125,   126,     4,     4,   240,     4,   237,     4,
     240,   134,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   791,     4,   793,   794,   238,
     238,     7,   238,     7,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,   238,     7,     7,   237,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,   237,   100,   101,   102,     7,   104,   237,
       7,     5,     5,   237,   237,   237,   237,     5,     5,   237,
     116,   117,     5,     7,   237,     5,     5,   123,     5,   125,
     126,   127,   128,   129,   130,   131,   132,     5,   134,   135,
     136,     7,     7,     5,     7,   141,     7,   143,   237,   237,
       5,     7,     5,   237,   237,   151,   237,   237,     5,   237,
     237,   237,     7,   237,   237,   237,   237,    85,    86,    87,
      88,    89,    90,    91,    92,     5,    94,    95,    96,    97,
       7,   237,     7,     7,   200,   237,   104,   237,   237,     7,
     237,   237,   237,     7,     7,     7,     7,   237,   237,   117,
     237,     7,     7,   237,     7,   152,   124,   125,   126,   205,
     206,   237,     4,     4,     4,     4,   134,   135,   136,     4,
     237,     4,     4,   141,   142,     4,     4,     4,     4,     4,
       3,   753,     6,     3,     6,     6,     3,     6,     3,     3,
       6,   237,     3,     6,     6,     3,     6,     3,   237,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       6,     4,     4,     4,     4,     4,     4,   238,   240,     6,
       4,     6,     8,     4,     4,     4,     4,  1054,     4,   240,
    1057,  1060,   238,  1060,   238,  1054,  1063,   205,   206,  1054,
     238,  1068,   238,  1054,  1071,  1063,  1057,  1074,  1063,  1060,
    1060,   238,  1063,  1068,  1063,   238,  1071,  1068,   238,     4,
    1071,  1088,  1068,  1090,   240,  1057,   238,  1063,  1060,   237,
       4,  1063,     4,  1100,  1054,     4,  1068,  1088,  1054,  1090,
    1107,  1057,     4,  1063,  1060,  1112,  1097,  1063,  1068,  1100,
    1054,  1071,  1068,     4,  1112,  1071,  1054,     4,   238,  1063,
       4,  1112,   238,  1112,  1068,  1063,  1054,  1071,  1100,  1054,
    1068,     4,  1088,  1071,  1090,  1063,  1112,  1054,  1063,  1054,
    1068,  1097,     6,  1068,  1100,  1054,  1063,     3,  1063,  1054,
     238,  1068,     4,   240,  1063,  1054,  1112,  1054,  1063,  1068,
    1054,   240,  1054,   237,  1063,   238,  1063,   238,  1054,  1063,
    1054,  1063,   238,  1054,  1112,  1054,   238,  1063,  1054,  1063,
    1054,   240,  1063,     8,  1063,  1054,   238,  1063,  1054,  1063,
    1054,  1063,   238,  1054,  1063,  1054,  1054,  1063,   237,  1063,
    1054,  1054,  1063,  1054,  1063,  1063,   240,  1112,   240,  1063,
    1063,   240,  1063,  1112,  1054,  1112,  1054,     8,  1112,   237,
    1112,  1054,     4,  1063,     4,  1063,  1112,   237,  1112,     8,
    1063,  1112,  1054,  1112,     3,  1054,  1112,     8,  1112,   237,
    1112,  1063,     4,  1112,  1063,  1054,  1112,  1054,  1112,  1054,
    1054,  1112,  1054,     4,  1063,     4,  1063,     4,  1063,  1063,
       4,  1063,     4,     4,     4,     4,     4,     4,     4,   177,
       3,     5,     7,     5,   237,   237,     7,     7,     6,     4,
     237,  1274,   237,   237,   237,   237,   237,     4,     4,   237,
     240,   240,   238,   240,   238,   237,   237,   237,   237,     4,
     237,   237,     5,     4,     4,     4,   240,     4,     4,     7,
     238,   238,  1319,     4,     6,     3,   237,   237,   237,  1326,
       4,  1319,   237,   755,  1319,  1023,   738,   539,  1319,  1336,
    1319,  1326,  1053,   842,  1066,  1326,  1343,   548,  1048,  1088,
    1326,  1141,  1076,  1319,  1083,  1336,  1074,  1319,   597,  1056,
    1054,  1319,  1343,   562,  1326,   587,  1065,  1059,  1057,  1319,
    1060,  1062,  1112,  1319,   594,  1071,  1326,  1374,  1114,   566,
    1326,  1343,   577,  1326,  1070,  1319,  1073,  1092,  1336,  1406,
    1336,  1319,  1326,  1374,  1443,  1402,  1466,  1343,  1326,  1482,
     794,  1319,  1097,   754,  1319,  1402,  1343,  1404,  1326,   607,
    1408,  1326,  1319,  1450,  1319,   611,  1101,    -1,    -1,  1326,
    1319,  1402,    -1,  1404,  1319,  1107,    -1,  1326,  1374,    -1,
    1319,    -1,  1319,    -1,    -1,  1319,    -1,  1319,    -1,    -1,
      -1,    -1,  1404,  1319,    -1,  1319,  1443,    -1,  1319,    -1,
    1319,    -1,    -1,  1319,    -1,  1319,  1402,  1319,  1404,    -1,
    1319,    -1,  1443,  1319,    -1,  1319,    -1,  1464,  1319,    -1,
    1319,  1319,    -1,    -1,    -1,  1319,  1319,    -1,  1319,    -1,
      -1,  1443,    -1,  1464,    -1,  1482,    -1,    -1,    -1,  1319,
      -1,  1319,    -1,    -1,    -1,    -1,  1319,  1443,    -1,    -1,
      -1,  1482,    -1,    -1,    -1,    -1,    -1,  1319,    -1,    -1,
    1319,    30,    31,    32,    33,    34,    35,    -1,  1464,    -1,
    1319,    -1,  1319,    -1,  1319,  1319,    -1,  1319,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1482,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    -1,    -1,    -1,    -1,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   125,   126,    -1,   128,
      -1,   130,   131,   132,    -1,   134,   135,   136,    -1,    -1,
      -1,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   205,   206,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,     0,     5,
       7,     9,   237,   238,   239,   240,   256,   257,   258,   263,
       7,   272,     7,   277,     7,   338,     7,   455,     7,   542,
       7,   559,     7,   491,     7,   497,     7,   521,     7,   431,
       7,   668,     7,   687,   264,   259,   273,   278,   339,   456,
     543,   560,   492,   498,   522,   432,   669,   688,   256,   265,
     266,   237,   261,   262,    10,   274,   276,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   103,   104,   115,   116,   117,   122,   125,   126,   130,
     131,   132,   133,   134,   143,   153,   156,   163,   164,   168,
     186,   190,   205,   206,   207,   208,   209,   210,   219,   237,
     271,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   295,   296,   298,   299,
     300,   301,   302,   303,   304,   307,   309,   311,   313,   314,
     315,   318,   319,   320,   321,   322,   324,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   352,   354,   362,   364,
     409,   418,   425,   439,   449,   477,   478,   479,   481,   489,
     515,   549,   551,   553,   564,   566,   568,   591,   607,   608,
     656,   666,   685,   694,   718,    15,    16,    19,    22,    23,
      24,    25,   271,   336,   337,   340,   342,   345,   348,   349,
     350,   351,   549,   551,   100,   101,   102,   123,   127,   128,
     129,   134,   135,   136,   141,   151,   271,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   296,   299,
     300,   301,   302,   303,   304,   307,   309,   311,   313,   314,
     315,   318,   319,   320,   321,   322,   324,   326,   332,   457,
     458,   459,   461,   463,   465,   467,   469,   471,   473,   475,
     477,   478,   479,   480,   515,   536,   549,   551,   553,   564,
     566,   568,   586,   124,   142,   271,   301,   302,   303,   304,
     307,   309,   311,   313,   315,   318,   319,   320,   321,   322,
     324,   469,   471,   473,   475,   515,   544,   545,   546,   548,
     549,   551,   134,   144,   145,   146,   147,   148,   149,   150,
     271,   515,   549,   551,   561,   562,   563,   564,   566,   568,
     570,   572,   574,   576,   578,   580,   582,   584,   489,    40,
     105,   107,   108,   112,   113,   114,   271,   383,   499,   500,
     501,   502,   503,   504,   505,   507,   509,   511,   512,   514,
     549,   551,   106,   109,   110,   111,   134,   271,   383,   503,
     509,   523,   524,   525,   526,   527,   529,   530,   531,   532,
     533,   534,   549,   551,   154,   155,   271,   433,   434,   435,
     437,   191,   192,   193,   194,   195,   196,   197,   198,   271,
     549,   551,   670,   671,   672,   673,   675,   676,   678,   679,
     680,   683,    12,    13,   689,   690,   691,   693,     6,     3,
       4,     8,     3,   275,     3,     8,   686,   335,   355,     4,
       4,     4,   565,   567,   569,     4,     4,   353,   363,   365,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   294,     4,     4,     4,     4,     4,   305,   308,
     310,   312,     4,     4,     4,     4,     4,     4,     4,   450,
     490,   516,     4,   297,   316,   482,   550,   552,     4,     4,
       4,   410,   592,   554,   426,   440,     4,   419,   609,   657,
     667,   323,   325,     4,     4,     4,   695,   719,     4,     3,
       8,   341,   343,   346,     4,     4,     4,     4,     3,     8,
     462,   464,   466,   537,   460,   468,     4,   472,   474,   476,
     470,   587,     3,     8,   547,     4,     3,     8,   585,   571,
     573,   575,   579,   577,   583,   581,     8,     3,     8,   506,
     384,     4,   510,   508,   513,     4,     8,     3,   528,     4,
       4,     4,   535,     8,     3,   436,   438,     3,     8,     4,
     674,     4,   677,     4,     4,   681,   684,     3,     8,   692,
       4,     3,     8,   256,   256,   237,     4,     4,     4,     4,
     240,   240,   240,     4,     4,     4,   238,   240,     4,     4,
       4,   238,   238,   238,   238,   238,   240,   239,   239,   239,
     238,   239,   238,     4,   238,   238,   240,   240,   240,     4,
       4,     4,     4,   240,   240,   239,   238,   238,   238,   240,
       4,     4,     4,   238,     4,     4,     4,     4,     4,   240,
     240,   240,     4,     4,     4,     4,     4,   238,     4,     4,
       4,     4,     4,     4,   240,   240,   240,     4,     4,   280,
       4,     4,     4,   240,   240,   238,   238,   337,     4,     4,
       4,     4,     4,     4,   238,     4,     4,     4,     4,     4,
     458,     4,   238,   545,     4,     4,     4,     4,     4,     4,
       4,     4,   563,     4,     4,   238,     4,     4,     4,   240,
     501,     4,   240,   240,   240,     4,   525,     4,     4,   434,
     240,     4,   238,     4,   238,   238,     4,     4,   671,     4,
     238,   690,     4,     7,     7,     7,     7,   237,   237,   237,
       7,     7,     5,   237,   201,   202,   203,   204,   240,   306,
     237,   237,   237,     5,     5,     5,   237,   118,   119,   120,
     121,   317,     5,   258,   260,   237,     5,     5,     5,     5,
       7,     7,     5,     7,     7,   237,   237,     5,     7,     5,
     267,    17,    18,   344,    20,    21,   347,   237,   237,   237,
       5,   237,   237,   267,   267,   267,   237,     7,   237,   267,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   267,   237,   260,   237,   237,    18,   199,
     682,   200,     5,   256,   279,   689,   336,    27,    28,   356,
     357,   358,   360,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
     182,   271,   370,   371,   372,   374,   376,   378,   380,   382,
     383,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   397,   398,   399,   401,   403,   405,   407,   370,     7,
     366,   367,   368,     7,   451,   452,   453,     7,   493,   494,
     495,     7,   517,   518,   519,     7,   483,   484,   485,   145,
     146,   147,   148,   150,   411,   412,   413,   414,   415,   416,
     417,     7,   593,   594,   595,     7,   555,   556,   557,     7,
     427,   428,   429,   157,   158,   159,   160,   161,   162,   441,
     442,   443,   444,   445,   446,   447,   448,   165,   166,   167,
     271,   420,   421,   422,   423,   424,   549,   551,     7,   610,
     611,   612,   187,   188,   189,   237,   549,   551,   658,   659,
     660,   661,   663,   664,   670,     7,   696,   697,   220,   221,
     222,   223,   271,   720,   721,   722,   723,   724,   725,   268,
       7,   538,   539,   540,   152,   588,   589,   366,     8,     8,
       8,   359,   361,     3,     8,   373,   375,   377,   381,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   395,
       4,     4,   400,   402,   404,   406,   408,   379,     3,     8,
       8,   369,     6,     3,   454,     6,     3,   496,     6,     3,
     520,     6,     3,   486,     6,     3,     3,     6,   596,     6,
       3,   558,     6,     3,   430,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     613,     6,     3,     4,   662,     4,   665,     3,     8,     8,
     698,     3,     6,     4,     4,     4,     4,     3,     8,   237,
     269,   270,   541,     6,     3,   590,     8,     6,     4,     4,
     357,     4,     4,     4,     4,   238,   240,   238,   240,   238,
     238,   238,   238,   238,   238,     4,   240,   238,     4,     4,
       4,     4,     4,     4,   371,   370,   368,   457,   453,   499,
     495,   523,   519,   271,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   296,   299,   300,   301,   302,
     303,   304,   307,   309,   311,   313,   314,   315,   318,   319,
     320,   321,   322,   324,   326,   332,   383,   449,   467,   469,
     471,   473,   475,   477,   478,   479,   487,   488,   515,   549,
     551,   564,   566,   568,   586,   485,   412,   137,   138,   139,
     140,   271,   281,   282,   283,   332,   383,   489,   515,   549,
     551,   564,   566,   568,   597,   598,   599,   600,   601,   603,
     605,   606,   595,   561,   557,   433,   429,   238,   238,   238,
     238,   238,   238,   442,   240,   238,   238,   421,   169,   173,
     174,   175,   176,   183,   184,   271,   399,   401,   403,   549,
     551,   614,   615,   616,   619,   621,   623,   624,   625,   635,
     612,   240,     4,   238,     4,   659,   211,   213,   214,   271,
     383,   549,   551,   699,   700,   701,   702,   704,   697,   240,
     240,   240,   240,   721,     6,     3,   544,   540,     4,   237,
     237,   237,   237,   237,   237,    55,    56,    57,   396,   237,
     237,   237,   405,   237,   237,     8,     8,     8,     8,     3,
       8,   602,   604,     4,     4,     8,     3,     8,     8,   617,
     620,   622,     4,   636,     4,   626,     3,     8,   237,   256,
     705,     4,   703,     3,     8,   237,     8,   267,   488,     4,
       4,   240,   240,   599,     4,     4,     4,   238,     4,   240,
       4,   615,     4,   238,     4,   700,   237,   237,   170,   171,
     172,   618,   237,   237,     7,     5,     5,   237,    40,   178,
     179,   180,   271,   549,   551,   637,   638,   639,   642,   644,
     646,     7,   627,   628,   629,     7,   706,   707,   640,   643,
     645,   647,     3,     8,   630,     6,     3,   708,     3,     6,
       4,     4,     4,     4,   638,   185,   271,   383,   549,   551,
     631,   632,   633,   629,   212,   215,   216,   217,   218,   709,
     710,   711,   713,   714,   715,   716,   707,   177,   641,   237,
     237,     5,   634,     3,     8,   712,     4,     4,     4,   717,
       3,     8,     7,   648,   649,   650,     4,   632,     4,   240,
     238,   238,     4,   710,   651,     6,     3,   237,   237,   237,
     181,   271,   374,   376,   378,   549,   551,   652,   653,   654,
     650,   655,     3,     8,     4,   653,   237
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
     306,   306,   306,   308,   307,   310,   309,   312,   311,   313,
     314,   316,   315,   317,   317,   317,   317,   318,   319,   320,
     321,   323,   322,   325,   324,   326,   327,   328,   329,   330,
     331,   332,   333,   335,   334,   336,   336,   336,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   339,   338,
     341,   340,   343,   342,   344,   344,   346,   345,   347,   347,
     348,   349,   350,   351,   353,   352,   355,   354,   356,   356,
     356,   357,   357,   359,   358,   361,   360,   363,   362,   365,
     364,   366,   366,   367,   367,   367,   369,   368,   370,   370,
     370,   371,   371,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   373,   372,   375,   374,
     377,   376,   379,   378,   381,   380,   382,   384,   383,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   395,   394,
     396,   396,   396,   397,   398,   400,   399,   402,   401,   404,
     403,   406,   405,   405,   405,   405,   405,   405,   408,   407,
     410,   409,   411,   411,   411,   412,   412,   412,   412,   412,
     413,   414,   415,   416,   417,   419,   418,   420,   420,   420,
     421,   421,   421,   421,   421,   421,   422,   423,   424,   426,
     425,   427,   427,   428,   428,   428,   430,   429,   432,   431,
     433,   433,   433,   433,   434,   434,   436,   435,   438,   437,
     440,   439,   441,   441,   441,   442,   442,   442,   442,   442,
     442,   443,   444,   445,   446,   447,   448,   450,   449,   451,
     451,   452,   452,   452,   454,   453,   456,   455,   457,   457,
     457,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   460,   459,   462,   461,
     464,   463,   466,   465,   468,   467,   470,   469,   472,   471,
     474,   473,   476,   475,   477,   478,   479,   480,   482,   481,
     483,   483,   484,   484,   484,   486,   485,   487,   487,   487,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     490,   489,   492,   491,   493,   493,   494,   494,   494,   496,
     495,   498,   497,   499,   499,   500,   500,   500,   501,   501,
     501,   501,   501,   501,   501,   501,   501,   501,   502,   503,
     504,   506,   505,   508,   507,   510,   509,   511,   513,   512,
     514,   516,   515,   517,   517,   518,   518,   518,   520,   519,
     522,   521,   523,   523,   524,   524,   524,   525,   525,   525,
     525,   525,   525,   525,   525,   525,   525,   525,   526,   528,
     527,   529,   530,   531,   532,   533,   535,   534,   537,   536,
     538,   538,   539,   539,   539,   541,   540,   543,   542,   544,
     544,   544,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   545,   545,   545,   545,   547,   546,   548,
     550,   549,   552,   551,   554,   553,   555,   555,   556,   556,
     556,   558,   557,   560,   559,   561,   561,   562,   562,   562,
     563,   563,   563,   563,   563,   563,   563,   563,   563,   563,
     563,   563,   563,   563,   563,   565,   564,   567,   566,   569,
     568,   571,   570,   573,   572,   575,   574,   577,   576,   579,
     578,   581,   580,   583,   582,   585,   584,   587,   586,   588,
     590,   589,   592,   591,   593,   593,   594,   594,   594,   596,
     595,   597,   597,   598,   598,   598,   599,   599,   599,   599,
     599,   599,   599,   599,   599,   599,   599,   599,   599,   599,
     599,   599,   599,   600,   602,   601,   604,   603,   605,   606,
     607,   609,   608,   610,   610,   611,   611,   611,   613,   612,
     614,   614,   614,   615,   615,   615,   615,   615,   615,   615,
     615,   615,   615,   615,   615,   615,   617,   616,   618,   618,
     618,   620,   619,   622,   621,   623,   624,   626,   625,   627,
     627,   628,   628,   628,   630,   629,   631,   631,   631,   632,
     632,   632,   632,   632,   634,   633,   636,   635,   637,   637,
     637,   638,   638,   638,   638,   638,   638,   638,   640,   639,
     641,   643,   642,   645,   644,   647,   646,   648,   648,   649,
     649,   649,   651,   650,   652,   652,   652,   653,   653,   653,
     653,   653,   653,   653,   655,   654,   657,   656,   658,   658,
     658,   659,   659,   659,   659,   659,   659,   660,   662,   661,
     663,   665,   664,   667,   666,   669,   668,   670,   670,   670,
     671,   671,   671,   671,   671,   671,   671,   671,   671,   671,
     671,   672,   674,   673,   675,   677,   676,   678,   679,   681,
     680,   682,   682,   684,   683,   686,   685,   688,   687,   689,
     689,   689,   690,   690,   692,   691,   693,   695,   694,   696,
     696,   696,   698,   697,   699,   699,   699,   700,   700,   700,
     700,   700,   700,   700,   701,   703,   702,   705,   704,   706,
     706,   706,   708,   707,   709,   709,   709,   710,   710,   710,
     710,   710,   712,   711,   713,   714,   715,   717,   716,   719,
     718,   720,   720,   720,   721,   721,   721,   721,   721,   722,
     723,   724,   725
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
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     3,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
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
  "$@66", "subnet_4o6_subnet", "$@67", "interface", "$@68", "client_class",
  "$@69", "network_client_classes", "$@70", "require_client_classes",
  "$@71", "evaluate_additional_classes", "$@72", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "shared_networks", "$@73", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@74",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@75", "sub_option_def_list", "$@76", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@77",
  "sub_option_def", "$@78", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@79",
  "option_def_record_types", "$@80", "space", "$@81", "option_def_space",
  "option_def_encapsulate", "$@82", "option_def_array", "option_data_list",
  "$@83", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@84", "sub_option_data", "$@85",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@86",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@87", "pools_list", "$@88",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@89",
  "sub_pool4", "$@90", "pool_params", "pool_param", "pool_entry", "$@91",
  "pool_id", "user_context", "$@92", "comment", "$@93", "reservations",
  "$@94", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@95", "sub_reservation", "$@96", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@97", "server_hostname", "$@98", "boot_file_name", "$@99",
  "ip_address", "$@100", "duid", "$@101", "hw_address", "$@102",
  "client_id_value", "$@103", "circuit_id_value", "$@104", "flex_id_value",
  "$@105", "hostname", "$@106", "reservation_client_classes", "$@107",
  "relay", "$@108", "relay_map", "ip_addresses", "$@109", "client_classes",
  "$@110", "client_classes_list", "not_empty_classes_list",
  "client_class_entry", "$@111", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@112",
  "client_class_template_test", "$@113", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_sockets", "$@114",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@115", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@116",
  "control_socket_type_value", "control_socket_name", "$@117",
  "control_socket_address", "$@118", "control_socket_port",
  "cert_required", "http_headers", "$@119", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@120",
  "http_header_params", "http_header_param", "header_value", "$@121",
  "authentication", "$@122", "auth_params", "auth_param", "auth_type",
  "$@123", "auth_type_value", "realm", "$@124", "directory", "$@125",
  "clients", "$@126", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@127", "clients_params", "clients_param", "user_file",
  "$@128", "dhcp_queue_control", "$@129", "queue_control_params",
  "queue_control_param", "enable_queue", "queue_type", "$@130", "capacity",
  "arbitrary_map_entry", "$@131", "dhcp_ddns", "$@132", "sub_dhcp_ddns",
  "$@133", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "server_ip", "$@134", "server_port", "sender_ip", "$@135", "sender_port",
  "max_queue_size", "ncr_protocol", "$@136", "ncr_protocol_value",
  "ncr_format", "$@137", "config_control", "$@138", "sub_config_control",
  "$@139", "config_control_params", "config_control_param",
  "config_databases", "$@140", "config_fetch_wait_time", "loggers",
  "$@141", "loggers_entries", "logger_entry", "$@142", "logger_params",
  "logger_param", "debuglevel", "severity", "$@143", "output_options_list",
  "$@144", "output_options_list_content", "output_entry", "$@145",
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
     746,   749,   752,   758,   758,   767,   767,   776,   776,   785,
     794,   804,   804,   813,   816,   819,   822,   827,   833,   839,
     845,   851,   851,   860,   860,   869,   875,   881,   887,   893,
     899,   905,   911,   917,   917,   929,   930,   931,   936,   937,
     938,   939,   940,   941,   942,   943,   944,   945,   948,   948,
     957,   957,   968,   968,   976,   977,   980,   980,   988,   990,
     994,  1000,  1006,  1012,  1018,  1018,  1031,  1031,  1042,  1043,
    1044,  1049,  1050,  1053,  1053,  1072,  1072,  1090,  1090,  1103,
    1103,  1114,  1115,  1118,  1119,  1120,  1125,  1125,  1135,  1136,
    1137,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,
    1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,
    1161,  1162,  1163,  1164,  1165,  1166,  1169,  1169,  1178,  1178,
    1187,  1187,  1196,  1196,  1205,  1205,  1214,  1220,  1220,  1229,
    1235,  1241,  1247,  1253,  1259,  1265,  1271,  1277,  1283,  1283,
    1291,  1292,  1293,  1296,  1302,  1308,  1308,  1317,  1317,  1326,
    1326,  1335,  1335,  1343,  1346,  1349,  1352,  1355,  1360,  1360,
    1369,  1369,  1380,  1381,  1382,  1387,  1388,  1389,  1390,  1391,
    1394,  1399,  1404,  1409,  1414,  1421,  1421,  1434,  1435,  1436,
    1441,  1442,  1443,  1444,  1445,  1446,  1449,  1455,  1461,  1467,
    1467,  1478,  1479,  1482,  1483,  1484,  1489,  1489,  1499,  1499,
    1509,  1510,  1511,  1514,  1517,  1518,  1521,  1521,  1530,  1530,
    1539,  1539,  1551,  1552,  1553,  1558,  1559,  1560,  1561,  1562,
    1563,  1566,  1572,  1578,  1584,  1590,  1596,  1605,  1605,  1619,
    1620,  1623,  1624,  1625,  1634,  1634,  1660,  1660,  1671,  1672,
    1673,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,
    1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,
    1708,  1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,
    1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,
    1728,  1729,  1730,  1731,  1732,  1733,  1736,  1736,  1745,  1745,
    1754,  1754,  1763,  1763,  1772,  1772,  1781,  1781,  1791,  1791,
    1803,  1803,  1814,  1814,  1825,  1831,  1837,  1843,  1851,  1851,
    1863,  1864,  1868,  1869,  1870,  1875,  1875,  1883,  1884,  1885,
    1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,
    1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,  1908,  1909,
    1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,
    1920,  1921,  1922,  1923,  1924,  1925,  1926,  1927,  1928,  1929,
    1930,  1931,  1932,  1933,  1934,  1935,  1936,  1937,  1938,  1939,
    1946,  1946,  1960,  1960,  1969,  1970,  1973,  1974,  1975,  1982,
    1982,  1997,  1997,  2011,  2012,  2015,  2016,  2017,  2022,  2023,
    2024,  2025,  2026,  2027,  2028,  2029,  2030,  2031,  2034,  2036,
    2042,  2044,  2044,  2053,  2053,  2062,  2062,  2071,  2073,  2073,
    2082,  2092,  2092,  2105,  2106,  2111,  2112,  2113,  2120,  2120,
    2132,  2132,  2144,  2145,  2150,  2151,  2152,  2159,  2160,  2161,
    2162,  2163,  2164,  2165,  2166,  2167,  2168,  2169,  2172,  2174,
    2174,  2183,  2185,  2187,  2193,  2199,  2205,  2205,  2219,  2219,
    2232,  2233,  2236,  2237,  2238,  2243,  2243,  2253,  2253,  2263,
    2264,  2265,  2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,
    2278,  2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2287,
    2288,  2289,  2290,  2291,  2292,  2293,  2294,  2297,  2297,  2306,
    2312,  2312,  2337,  2337,  2367,  2367,  2378,  2379,  2382,  2383,
    2384,  2389,  2389,  2398,  2398,  2407,  2408,  2411,  2412,  2413,
    2419,  2420,  2421,  2422,  2423,  2424,  2425,  2426,  2427,  2428,
    2429,  2430,  2431,  2432,  2433,  2436,  2436,  2445,  2445,  2454,
    2454,  2463,  2463,  2472,  2472,  2481,  2481,  2490,  2490,  2499,
    2499,  2508,  2508,  2517,  2517,  2526,  2526,  2540,  2540,  2551,
    2554,  2554,  2568,  2568,  2579,  2580,  2583,  2584,  2585,  2590,
    2590,  2600,  2601,  2604,  2605,  2606,  2611,  2612,  2613,  2614,
    2615,  2616,  2617,  2618,  2619,  2620,  2621,  2622,  2623,  2624,
    2625,  2626,  2627,  2630,  2632,  2632,  2641,  2641,  2651,  2657,
    2665,  2673,  2673,  2684,  2685,  2688,  2689,  2690,  2695,  2695,
    2703,  2704,  2705,  2710,  2711,  2712,  2713,  2714,  2715,  2716,
    2717,  2718,  2719,  2720,  2721,  2722,  2725,  2725,  2734,  2735,
    2736,  2739,  2739,  2748,  2748,  2757,  2763,  2769,  2769,  2780,
    2781,  2784,  2785,  2786,  2791,  2791,  2799,  2800,  2801,  2806,
    2807,  2808,  2809,  2810,  2813,  2813,  2824,  2824,  2837,  2838,
    2839,  2844,  2845,  2846,  2847,  2848,  2849,  2850,  2853,  2853,
    2861,  2864,  2864,  2873,  2873,  2882,  2882,  2893,  2894,  2897,
    2898,  2899,  2904,  2904,  2912,  2913,  2914,  2919,  2920,  2921,
    2922,  2923,  2924,  2925,  2928,  2928,  2939,  2939,  2952,  2953,
    2954,  2959,  2960,  2961,  2962,  2963,  2964,  2967,  2973,  2973,
    2982,  2988,  2988,  2998,  2998,  3011,  3011,  3021,  3022,  3023,
    3028,  3029,  3030,  3031,  3032,  3033,  3034,  3035,  3036,  3037,
    3038,  3041,  3047,  3047,  3056,  3062,  3062,  3071,  3077,  3083,
    3083,  3092,  3093,  3096,  3096,  3107,  3107,  3119,  3119,  3129,
    3130,  3131,  3137,  3138,  3141,  3141,  3152,  3160,  3160,  3173,
    3174,  3175,  3181,  3181,  3189,  3190,  3191,  3196,  3197,  3198,
    3199,  3200,  3201,  3202,  3205,  3211,  3211,  3220,  3220,  3231,
    3232,  3233,  3238,  3238,  3246,  3247,  3248,  3253,  3254,  3255,
    3256,  3257,  3260,  3260,  3269,  3275,  3281,  3287,  3287,  3296,
    3296,  3307,  3308,  3309,  3314,  3315,  3316,  3317,  3318,  3321,
    3327,  3333,  3339
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
#line 7029 "dhcp4_parser.cc"

#line 3345 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
