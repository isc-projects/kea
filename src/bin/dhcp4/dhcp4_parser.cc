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

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 598 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1158 "dhcp4_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 604 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 610 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1178 "dhcp4_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 616 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 622 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 628 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 634 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1218 "dhcp4_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 640 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1228 "dhcp4_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 646 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 652 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 658 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 153: // $@20: %empty
#line 664 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp4_parser.cc"
    break;

  case 154: // server_tag: "server-tag" $@20 ":" "constant string"
#line 667 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 155: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 673 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 156: // $@21: %empty
#line 679 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc"
    break;

  case 157: // allocator: "allocator" $@21 ":" "constant string"
#line 682 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 158: // echo_client_id: "echo-client-id" ":" "boolean"
#line 688 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 159: // match_client_id: "match-client-id" ":" "boolean"
#line 694 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 160: // authoritative: "authoritative" ":" "boolean"
#line 700 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 161: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 706 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 162: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 712 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 163: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 718 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 164: // $@22: %empty
#line 724 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 727 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1384 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-present"
#line 733 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1392 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "never"
#line 736 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1400 "dhcp4_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "always"
#line 739 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1408 "dhcp4_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "when-not-present"
#line 742 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1416 "dhcp4_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "boolean"
#line 745 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1425 "dhcp4_parser.cc"
    break;

  case 171: // $@23: %empty
#line 751 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 172: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 754 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 173: // $@24: %empty
#line 760 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp4_parser.cc"
    break;

  case 174: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 763 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 175: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 769 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 176: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 778 "dhcp4_parser.yy"
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
#line 788 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 791 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 797 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1513 "dhcp4_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 800 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1521 "dhcp4_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 803 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1529 "dhcp4_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 806 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1537 "dhcp4_parser.cc"
    break;

  case 183: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 811 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 184: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 817 "dhcp4_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 185: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 823 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1567 "dhcp4_parser.cc"
    break;

  case 186: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 829 "dhcp4_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 187: // $@26: %empty
#line 835 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 188: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 838 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 189: // $@27: %empty
#line 844 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 190: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 847 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 191: // store_extended_info: "store-extended-info" ":" "boolean"
#line 853 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 192: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 859 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1635 "dhcp4_parser.cc"
    break;

  case 193: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 865 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 871 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 877 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 883 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 197: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 889 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1685 "dhcp4_parser.cc"
    break;

  case 198: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 895 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1695 "dhcp4_parser.cc"
    break;

  case 199: // $@28: %empty
#line 901 "dhcp4_parser.yy"
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
#line 907 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 915 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1725 "dhcp4_parser.cc"
    break;

  case 214: // $@29: %empty
#line 932 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 215: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 936 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1744 "dhcp4_parser.cc"
    break;

  case 216: // $@30: %empty
#line 941 "dhcp4_parser.yy"
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
#line 947 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 218: // $@31: %empty
#line 952 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 219: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 955 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 220: // socket_type: "raw"
#line 960 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1789 "dhcp4_parser.cc"
    break;

  case 221: // socket_type: "udp"
#line 961 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1795 "dhcp4_parser.cc"
    break;

  case 222: // $@32: %empty
#line 964 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1804 "dhcp4_parser.cc"
    break;

  case 223: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 967 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1813 "dhcp4_parser.cc"
    break;

  case 224: // outbound_interface_value: "same-as-inbound"
#line 972 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1821 "dhcp4_parser.cc"
    break;

  case 225: // outbound_interface_value: "use-routing"
#line 974 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1829 "dhcp4_parser.cc"
    break;

  case 226: // re_detect: "re-detect" ":" "boolean"
#line 978 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1839 "dhcp4_parser.cc"
    break;

  case 227: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 984 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1849 "dhcp4_parser.cc"
    break;

  case 228: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 990 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1859 "dhcp4_parser.cc"
    break;

  case 229: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 996 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 230: // $@33: %empty
#line 1002 "dhcp4_parser.yy"
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
#line 1008 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1892 "dhcp4_parser.cc"
    break;

  case 232: // $@34: %empty
#line 1015 "dhcp4_parser.yy"
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
#line 1021 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1913 "dhcp4_parser.cc"
    break;

  case 236: // sanity_checks_params: sanity_checks_params ","
#line 1028 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1921 "dhcp4_parser.cc"
    break;

  case 239: // $@35: %empty
#line 1037 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1930 "dhcp4_parser.cc"
    break;

  case 240: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1040 "dhcp4_parser.yy"
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
#line 1056 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1959 "dhcp4_parser.cc"
    break;

  case 242: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1059 "dhcp4_parser.yy"
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
#line 1074 "dhcp4_parser.yy"
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
#line 1080 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 245: // $@38: %empty
#line 1087 "dhcp4_parser.yy"
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
#line 1093 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 251: // not_empty_database_list: not_empty_database_list ","
#line 1104 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2030 "dhcp4_parser.cc"
    break;

  case 252: // $@39: %empty
#line 1109 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 253: // database: "{" $@39 database_map_params "}"
#line 1113 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 256: // database_map_params: database_map_params ","
#line 1121 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2058 "dhcp4_parser.cc"
    break;

  case 282: // $@40: %empty
#line 1153 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp4_parser.cc"
    break;

  case 283: // database_type: "type" $@40 ":" "constant string"
#line 1156 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 284: // $@41: %empty
#line 1162 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2086 "dhcp4_parser.cc"
    break;

  case 285: // user: "user" $@41 ":" "constant string"
#line 1165 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 286: // $@42: %empty
#line 1171 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp4_parser.cc"
    break;

  case 287: // password: "password" $@42 ":" "constant string"
#line 1174 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 288: // $@43: %empty
#line 1180 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp4_parser.cc"
    break;

  case 289: // host: "host" $@43 ":" "constant string"
#line 1183 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 290: // port: "port" ":" "integer"
#line 1189 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 291: // $@44: %empty
#line 1195 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2153 "dhcp4_parser.cc"
    break;

  case 292: // name: "name" $@44 ":" "constant string"
#line 1198 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 293: // persist: "persist" ":" "boolean"
#line 1204 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 294: // lfc_interval: "lfc-interval" ":" "integer"
#line 1210 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 295: // readonly: "readonly" ":" "boolean"
#line 1216 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2193 "dhcp4_parser.cc"
    break;

  case 296: // connect_timeout: "connect-timeout" ":" "integer"
#line 1222 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 297: // read_timeout: "read-timeout" ":" "integer"
#line 1228 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 298: // write_timeout: "write-timeout" ":" "integer"
#line 1234 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 299: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1240 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2233 "dhcp4_parser.cc"
    break;

  case 300: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1246 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2243 "dhcp4_parser.cc"
    break;

  case 301: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1252 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2253 "dhcp4_parser.cc"
    break;

  case 302: // $@45: %empty
#line 1258 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2262 "dhcp4_parser.cc"
    break;

  case 303: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1261 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 304: // on_fail_mode: "stop-retry-exit"
#line 1266 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2277 "dhcp4_parser.cc"
    break;

  case 305: // on_fail_mode: "serve-retry-exit"
#line 1267 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2283 "dhcp4_parser.cc"
    break;

  case 306: // on_fail_mode: "serve-retry-continue"
#line 1268 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2289 "dhcp4_parser.cc"
    break;

  case 307: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1271 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 308: // max_row_errors: "max-row-errors" ":" "integer"
#line 1277 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 309: // $@46: %empty
#line 1283 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2318 "dhcp4_parser.cc"
    break;

  case 310: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1286 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 311: // $@47: %empty
#line 1292 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 312: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1295 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 313: // $@48: %empty
#line 1301 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp4_parser.cc"
    break;

  case 314: // key_file: "key-file" $@48 ":" "constant string"
#line 1304 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 315: // $@49: %empty
#line 1310 "dhcp4_parser.yy"
                           {
    ctx.unique("key-password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2375 "dhcp4_parser.cc"
    break;

  case 316: // key_password: "key-password" $@49 ":" "constant string"
#line 1313 "dhcp4_parser.yy"
               {
    ElementPtr key_pass(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-password", key_pass);
    ctx.leave();
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 317: // $@50: %empty
#line 1319 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2394 "dhcp4_parser.cc"
    break;

  case 318: // ssl_mode: "ssl-mode" $@50 ":" ssl_mode
#line 1322 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2403 "dhcp4_parser.cc"
    break;

  case 319: // ssl_mode: "disable"
#line 1327 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location))); }
#line 2409 "dhcp4_parser.cc"
    break;

  case 320: // ssl_mode: "prefer"
#line 1328 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location))); }
#line 2415 "dhcp4_parser.cc"
    break;

  case 321: // ssl_mode: "require"
#line 1329 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location))); }
#line 2421 "dhcp4_parser.cc"
    break;

  case 322: // ssl_mode: "verify-ca"
#line 1330 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location))); }
#line 2427 "dhcp4_parser.cc"
    break;

  case 323: // ssl_mode: "verify-full"
#line 1331 "dhcp4_parser.yy"
                      { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location))); }
#line 2433 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1334 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 325: // cipher_list: "cipher-list" $@51 ":" "constant string"
#line 1337 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2452 "dhcp4_parser.cc"
    break;

  case 326: // $@52: %empty
#line 1343 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 327: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1349 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 330: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1356 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2481 "dhcp4_parser.cc"
    break;

  case 336: // duid_id: "duid"
#line 1368 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2490 "dhcp4_parser.cc"
    break;

  case 337: // hw_address_id: "hw-address"
#line 1373 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2499 "dhcp4_parser.cc"
    break;

  case 338: // circuit_id: "circuit-id"
#line 1378 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2508 "dhcp4_parser.cc"
    break;

  case 339: // client_id: "client-id"
#line 1383 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2517 "dhcp4_parser.cc"
    break;

  case 340: // flex_id: "flex-id"
#line 1388 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2526 "dhcp4_parser.cc"
    break;

  case 341: // $@53: %empty
#line 1395 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 342: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1401 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 345: // multi_threading_params: multi_threading_params ","
#line 1410 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2557 "dhcp4_parser.cc"
    break;

  case 352: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1423 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2567 "dhcp4_parser.cc"
    break;

  case 353: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1429 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2577 "dhcp4_parser.cc"
    break;

  case 354: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1435 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 355: // $@54: %empty
#line 1441 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 356: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1447 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc"
    break;

  case 361: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1458 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2616 "dhcp4_parser.cc"
    break;

  case 362: // $@55: %empty
#line 1463 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 363: // hooks_library: "{" $@55 hooks_params "}"
#line 1467 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2636 "dhcp4_parser.cc"
    break;

  case 364: // $@56: %empty
#line 1473 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2646 "dhcp4_parser.cc"
    break;

  case 365: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1477 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2656 "dhcp4_parser.cc"
    break;

  case 368: // hooks_params: hooks_params ","
#line 1485 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2664 "dhcp4_parser.cc"
    break;

  case 372: // $@57: %empty
#line 1495 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 373: // library: "library" $@57 ":" "constant string"
#line 1498 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 374: // $@58: %empty
#line 1504 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 375: // parameters: "parameters" $@58 ":" map_value
#line 1507 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 376: // $@59: %empty
#line 1513 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2713 "dhcp4_parser.cc"
    break;

  case 377: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1519 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2723 "dhcp4_parser.cc"
    break;

  case 380: // expired_leases_params: expired_leases_params ","
#line 1527 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2731 "dhcp4_parser.cc"
    break;

  case 387: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1540 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 388: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1546 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2751 "dhcp4_parser.cc"
    break;

  case 389: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1552 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2761 "dhcp4_parser.cc"
    break;

  case 390: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1558 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 391: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1564 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 392: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1570 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 393: // $@60: %empty
#line 1579 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2803 "dhcp4_parser.cc"
    break;

  case 394: // subnet4_list: "subnet4" $@60 ":" "[" subnet4_list_content "]"
#line 1585 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 399: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1599 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2820 "dhcp4_parser.cc"
    break;

  case 400: // $@61: %empty
#line 1608 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 401: // subnet4: "{" $@61 subnet4_params "}"
#line 1612 "dhcp4_parser.yy"
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
#line 2856 "dhcp4_parser.cc"
    break;

  case 402: // $@62: %empty
#line 1634 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2866 "dhcp4_parser.cc"
    break;

  case 403: // sub_subnet4: "{" $@62 subnet4_params "}"
#line 1638 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2876 "dhcp4_parser.cc"
    break;

  case 406: // subnet4_params: subnet4_params ","
#line 1647 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2884 "dhcp4_parser.cc"
    break;

  case 460: // $@63: %empty
#line 1708 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2893 "dhcp4_parser.cc"
    break;

  case 461: // subnet: "subnet" $@63 ":" "constant string"
#line 1711 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2903 "dhcp4_parser.cc"
    break;

  case 462: // $@64: %empty
#line 1717 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2912 "dhcp4_parser.cc"
    break;

  case 463: // subnet_4o6_interface: "4o6-interface" $@64 ":" "constant string"
#line 1720 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc"
    break;

  case 464: // $@65: %empty
#line 1726 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2931 "dhcp4_parser.cc"
    break;

  case 465: // subnet_4o6_interface_id: "4o6-interface-id" $@65 ":" "constant string"
#line 1729 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 466: // $@66: %empty
#line 1735 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2950 "dhcp4_parser.cc"
    break;

  case 467: // subnet_4o6_subnet: "4o6-subnet" $@66 ":" "constant string"
#line 1738 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 468: // $@67: %empty
#line 1744 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 469: // interface: "interface" $@67 ":" "constant string"
#line 1747 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2979 "dhcp4_parser.cc"
    break;

  case 470: // $@68: %empty
#line 1753 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2988 "dhcp4_parser.cc"
    break;

  case 471: // client_class: "client-class" $@68 ":" "constant string"
#line 1756 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2998 "dhcp4_parser.cc"
    break;

  case 472: // $@69: %empty
#line 1763 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3010 "dhcp4_parser.cc"
    break;

  case 473: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1769 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3019 "dhcp4_parser.cc"
    break;

  case 474: // $@70: %empty
#line 1775 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3031 "dhcp4_parser.cc"
    break;

  case 475: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1781 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3040 "dhcp4_parser.cc"
    break;

  case 476: // $@71: %empty
#line 1786 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 477: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1792 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 478: // reservations_global: "reservations-global" ":" "boolean"
#line 1797 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 479: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1803 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 480: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1809 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 481: // id: "id" ":" "integer"
#line 1815 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 482: // $@72: %empty
#line 1823 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3113 "dhcp4_parser.cc"
    break;

  case 483: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1829 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3122 "dhcp4_parser.cc"
    break;

  case 488: // shared_networks_list: shared_networks_list ","
#line 1842 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3130 "dhcp4_parser.cc"
    break;

  case 489: // $@73: %empty
#line 1847 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 490: // shared_network: "{" $@73 shared_network_params "}"
#line 1851 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3148 "dhcp4_parser.cc"
    break;

  case 493: // shared_network_params: shared_network_params ","
#line 1857 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3156 "dhcp4_parser.cc"
    break;

  case 542: // $@74: %empty
#line 1916 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3168 "dhcp4_parser.cc"
    break;

  case 543: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1922 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 544: // $@75: %empty
#line 1930 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 545: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1933 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3194 "dhcp4_parser.cc"
    break;

  case 550: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1945 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3202 "dhcp4_parser.cc"
    break;

  case 551: // $@76: %empty
#line 1952 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3212 "dhcp4_parser.cc"
    break;

  case 552: // option_def_entry: "{" $@76 option_def_params "}"
#line 1956 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3224 "dhcp4_parser.cc"
    break;

  case 553: // $@77: %empty
#line 1967 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3234 "dhcp4_parser.cc"
    break;

  case 554: // sub_option_def: "{" $@77 option_def_params "}"
#line 1971 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3246 "dhcp4_parser.cc"
    break;

  case 559: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1987 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3254 "dhcp4_parser.cc"
    break;

  case 571: // code: "code" ":" "integer"
#line 2006 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3264 "dhcp4_parser.cc"
    break;

  case 573: // $@78: %empty
#line 2014 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 574: // option_def_type: "type" $@78 ":" "constant string"
#line 2017 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 575: // $@79: %empty
#line 2023 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3292 "dhcp4_parser.cc"
    break;

  case 576: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2026 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 577: // $@80: %empty
#line 2032 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 578: // space: "space" $@80 ":" "constant string"
#line 2035 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3321 "dhcp4_parser.cc"
    break;

  case 580: // $@81: %empty
#line 2043 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 581: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2046 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3340 "dhcp4_parser.cc"
    break;

  case 582: // option_def_array: "array" ":" "boolean"
#line 2052 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 583: // $@82: %empty
#line 2062 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3362 "dhcp4_parser.cc"
    break;

  case 584: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2068 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3371 "dhcp4_parser.cc"
    break;

  case 589: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2083 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3379 "dhcp4_parser.cc"
    break;

  case 590: // $@83: %empty
#line 2090 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 591: // option_data_entry: "{" $@83 option_data_params "}"
#line 2094 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3398 "dhcp4_parser.cc"
    break;

  case 592: // $@84: %empty
#line 2102 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 593: // sub_option_data: "{" $@84 option_data_params "}"
#line 2106 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3417 "dhcp4_parser.cc"
    break;

  case 598: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2122 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3425 "dhcp4_parser.cc"
    break;

  case 611: // $@85: %empty
#line 2144 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3434 "dhcp4_parser.cc"
    break;

  case 612: // option_data_data: "data" $@85 ":" "constant string"
#line 2147 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 615: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2157 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 616: // option_data_always_send: "always-send" ":" "boolean"
#line 2163 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3464 "dhcp4_parser.cc"
    break;

  case 617: // option_data_never_send: "never-send" ":" "boolean"
#line 2169 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3474 "dhcp4_parser.cc"
    break;

  case 618: // $@86: %empty
#line 2175 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3486 "dhcp4_parser.cc"
    break;

  case 619: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2181 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 620: // $@87: %empty
#line 2189 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3507 "dhcp4_parser.cc"
    break;

  case 621: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2195 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3516 "dhcp4_parser.cc"
    break;

  case 626: // not_empty_pools_list: not_empty_pools_list ","
#line 2208 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3524 "dhcp4_parser.cc"
    break;

  case 627: // $@88: %empty
#line 2213 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 628: // pool_list_entry: "{" $@88 pool_params "}"
#line 2217 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 629: // $@89: %empty
#line 2223 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 630: // sub_pool4: "{" $@89 pool_params "}"
#line 2227 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 633: // pool_params: pool_params ","
#line 2235 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3572 "dhcp4_parser.cc"
    break;

  case 658: // $@90: %empty
#line 2266 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3581 "dhcp4_parser.cc"
    break;

  case 659: // pool_entry: "pool" $@90 ":" "constant string"
#line 2269 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3591 "dhcp4_parser.cc"
    break;

  case 660: // pool_id: "pool-id" ":" "integer"
#line 2275 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 661: // $@91: %empty
#line 2281 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3609 "dhcp4_parser.cc"
    break;

  case 662: // user_context: "user-context" $@91 ":" map_value
#line 2283 "dhcp4_parser.yy"
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
#line 3636 "dhcp4_parser.cc"
    break;

  case 663: // $@92: %empty
#line 2306 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3644 "dhcp4_parser.cc"
    break;

  case 664: // comment: "comment" $@92 ":" "constant string"
#line 2308 "dhcp4_parser.yy"
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
#line 3673 "dhcp4_parser.cc"
    break;

  case 665: // $@93: %empty
#line 2336 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3685 "dhcp4_parser.cc"
    break;

  case 666: // reservations: "reservations" $@93 ":" "[" reservations_list "]"
#line 2342 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3694 "dhcp4_parser.cc"
    break;

  case 671: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2353 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3702 "dhcp4_parser.cc"
    break;

  case 672: // $@94: %empty
#line 2358 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 673: // reservation: "{" $@94 reservation_params "}"
#line 2362 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 674: // $@95: %empty
#line 2367 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 675: // sub_reservation: "{" $@95 reservation_params "}"
#line 2371 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3740 "dhcp4_parser.cc"
    break;

  case 680: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2382 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3748 "dhcp4_parser.cc"
    break;

  case 696: // $@96: %empty
#line 2405 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3757 "dhcp4_parser.cc"
    break;

  case 697: // next_server: "next-server" $@96 ":" "constant string"
#line 2408 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3767 "dhcp4_parser.cc"
    break;

  case 698: // $@97: %empty
#line 2414 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 699: // server_hostname: "server-hostname" $@97 ":" "constant string"
#line 2417 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 700: // $@98: %empty
#line 2423 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3795 "dhcp4_parser.cc"
    break;

  case 701: // boot_file_name: "boot-file-name" $@98 ":" "constant string"
#line 2426 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3805 "dhcp4_parser.cc"
    break;

  case 702: // $@99: %empty
#line 2432 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3814 "dhcp4_parser.cc"
    break;

  case 703: // ip_address: "ip-address" $@99 ":" "constant string"
#line 2435 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3824 "dhcp4_parser.cc"
    break;

  case 704: // $@100: %empty
#line 2441 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3833 "dhcp4_parser.cc"
    break;

  case 705: // duid: "duid" $@100 ":" "constant string"
#line 2444 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3843 "dhcp4_parser.cc"
    break;

  case 706: // $@101: %empty
#line 2450 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3852 "dhcp4_parser.cc"
    break;

  case 707: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2453 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3862 "dhcp4_parser.cc"
    break;

  case 708: // $@102: %empty
#line 2459 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3871 "dhcp4_parser.cc"
    break;

  case 709: // client_id_value: "client-id" $@102 ":" "constant string"
#line 2462 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 710: // $@103: %empty
#line 2468 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3890 "dhcp4_parser.cc"
    break;

  case 711: // circuit_id_value: "circuit-id" $@103 ":" "constant string"
#line 2471 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3900 "dhcp4_parser.cc"
    break;

  case 712: // $@104: %empty
#line 2477 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3909 "dhcp4_parser.cc"
    break;

  case 713: // flex_id_value: "flex-id" $@104 ":" "constant string"
#line 2480 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 714: // $@105: %empty
#line 2486 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 715: // hostname: "hostname" $@105 ":" "constant string"
#line 2489 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 716: // $@106: %empty
#line 2495 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3950 "dhcp4_parser.cc"
    break;

  case 717: // reservation_client_classes: "client-classes" $@106 ":" list_strings
#line 2501 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3959 "dhcp4_parser.cc"
    break;

  case 718: // $@107: %empty
#line 2509 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3971 "dhcp4_parser.cc"
    break;

  case 719: // relay: "relay" $@107 ":" "{" relay_map "}"
#line 2515 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3980 "dhcp4_parser.cc"
    break;

  case 721: // $@108: %empty
#line 2523 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3992 "dhcp4_parser.cc"
    break;

  case 722: // ip_addresses: "ip-addresses" $@108 ":" list_strings
#line 2529 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4001 "dhcp4_parser.cc"
    break;

  case 723: // $@109: %empty
#line 2537 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4013 "dhcp4_parser.cc"
    break;

  case 724: // client_classes: "client-classes" $@109 ":" "[" client_classes_list "]"
#line 2543 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4022 "dhcp4_parser.cc"
    break;

  case 727: // client_classes_list: client_classes_list ","
#line 2550 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4030 "dhcp4_parser.cc"
    break;

  case 728: // $@110: %empty
#line 2555 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4040 "dhcp4_parser.cc"
    break;

  case 729: // client_class_entry: "{" $@110 client_class_params "}"
#line 2559 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4050 "dhcp4_parser.cc"
    break;

  case 734: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2571 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4058 "dhcp4_parser.cc"
    break;

  case 753: // $@111: %empty
#line 2597 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4067 "dhcp4_parser.cc"
    break;

  case 754: // client_class_test: "test" $@111 ":" "constant string"
#line 2600 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4077 "dhcp4_parser.cc"
    break;

  case 755: // $@112: %empty
#line 2606 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4086 "dhcp4_parser.cc"
    break;

  case 756: // client_class_template_test: "template-test" $@112 ":" "constant string"
#line 2609 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4096 "dhcp4_parser.cc"
    break;

  case 757: // only_if_required: "only-if-required" ":" "boolean"
#line 2616 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4106 "dhcp4_parser.cc"
    break;

  case 758: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2622 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4116 "dhcp4_parser.cc"
    break;

  case 759: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2630 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4126 "dhcp4_parser.cc"
    break;

  case 760: // $@113: %empty
#line 2638 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 761: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2645 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 762: // $@114: %empty
#line 2650 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 763: // control_sockets: "control-sockets" $@114 ":" "[" control_socket_list "]"
#line 2657 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4170 "dhcp4_parser.cc"
    break;

  case 768: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2668 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4178 "dhcp4_parser.cc"
    break;

  case 769: // $@115: %empty
#line 2673 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4188 "dhcp4_parser.cc"
    break;

  case 770: // control_socket_entry: "{" $@115 control_socket_params "}"
#line 2677 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 773: // control_socket_params: control_socket_params ","
#line 2683 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4204 "dhcp4_parser.cc"
    break;

  case 787: // $@116: %empty
#line 2703 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4213 "dhcp4_parser.cc"
    break;

  case 788: // control_socket_type: "socket-type" $@116 ":" control_socket_type_value
#line 2706 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4222 "dhcp4_parser.cc"
    break;

  case 789: // control_socket_type_value: "unix"
#line 2712 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4228 "dhcp4_parser.cc"
    break;

  case 790: // control_socket_type_value: "http"
#line 2713 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4234 "dhcp4_parser.cc"
    break;

  case 791: // control_socket_type_value: "https"
#line 2714 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4240 "dhcp4_parser.cc"
    break;

  case 792: // $@117: %empty
#line 2717 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4250 "dhcp4_parser.cc"
    break;

  case 793: // control_socket_name: "socket-name" $@117 ":" "constant string"
#line 2721 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4260 "dhcp4_parser.cc"
    break;

  case 794: // $@118: %empty
#line 2727 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4270 "dhcp4_parser.cc"
    break;

  case 795: // control_socket_address: "socket-address" $@118 ":" "constant string"
#line 2731 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4280 "dhcp4_parser.cc"
    break;

  case 796: // control_socket_port: "socket-port" ":" "integer"
#line 2737 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4290 "dhcp4_parser.cc"
    break;

  case 797: // cert_required: "cert-required" ":" "boolean"
#line 2743 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4300 "dhcp4_parser.cc"
    break;

  case 798: // $@119: %empty
#line 2749 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4312 "dhcp4_parser.cc"
    break;

  case 799: // http_headers: "http-headers" $@119 ":" "[" http_header_list "]"
#line 2755 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4321 "dhcp4_parser.cc"
    break;

  case 804: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2766 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4329 "dhcp4_parser.cc"
    break;

  case 805: // $@120: %empty
#line 2771 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4339 "dhcp4_parser.cc"
    break;

  case 806: // http_header: "{" $@120 http_header_params "}"
#line 2775 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4347 "dhcp4_parser.cc"
    break;

  case 809: // http_header_params: http_header_params ","
#line 2781 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4355 "dhcp4_parser.cc"
    break;

  case 815: // $@121: %empty
#line 2793 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4364 "dhcp4_parser.cc"
    break;

  case 816: // header_value: "value" $@121 ":" "constant string"
#line 2796 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4374 "dhcp4_parser.cc"
    break;

  case 817: // $@122: %empty
#line 2804 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4386 "dhcp4_parser.cc"
    break;

  case 818: // authentication: "authentication" $@122 ":" "{" auth_params "}"
#line 2810 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4397 "dhcp4_parser.cc"
    break;

  case 821: // auth_params: auth_params ","
#line 2819 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4405 "dhcp4_parser.cc"
    break;

  case 829: // $@123: %empty
#line 2833 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4414 "dhcp4_parser.cc"
    break;

  case 830: // auth_type: "type" $@123 ":" auth_type_value
#line 2836 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4423 "dhcp4_parser.cc"
    break;

  case 831: // auth_type_value: "basic"
#line 2841 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4429 "dhcp4_parser.cc"
    break;

  case 832: // $@124: %empty
#line 2844 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4438 "dhcp4_parser.cc"
    break;

  case 833: // realm: "realm" $@124 ":" "constant string"
#line 2847 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4448 "dhcp4_parser.cc"
    break;

  case 834: // $@125: %empty
#line 2853 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4457 "dhcp4_parser.cc"
    break;

  case 835: // directory: "directory" $@125 ":" "constant string"
#line 2856 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4467 "dhcp4_parser.cc"
    break;

  case 836: // $@126: %empty
#line 2862 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4479 "dhcp4_parser.cc"
    break;

  case 837: // clients: "clients" $@126 ":" "[" clients_list "]"
#line 2868 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4488 "dhcp4_parser.cc"
    break;

  case 842: // not_empty_clients_list: not_empty_clients_list ","
#line 2879 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4496 "dhcp4_parser.cc"
    break;

  case 843: // $@127: %empty
#line 2884 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4506 "dhcp4_parser.cc"
    break;

  case 844: // basic_auth: "{" $@127 clients_params "}"
#line 2888 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4514 "dhcp4_parser.cc"
    break;

  case 847: // clients_params: clients_params ","
#line 2894 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4522 "dhcp4_parser.cc"
    break;

  case 855: // $@128: %empty
#line 2908 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4531 "dhcp4_parser.cc"
    break;

  case 856: // user_file: "user-file" $@128 ":" "constant string"
#line 2911 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4541 "dhcp4_parser.cc"
    break;

  case 857: // $@129: %empty
#line 2917 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4550 "dhcp4_parser.cc"
    break;

  case 858: // password_file: "password-file" $@129 ":" "constant string"
#line 2920 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4560 "dhcp4_parser.cc"
    break;

  case 859: // $@130: %empty
#line 2928 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4572 "dhcp4_parser.cc"
    break;

  case 860: // dhcp_queue_control: "dhcp-queue-control" $@130 ":" "{" queue_control_params "}"
#line 2934 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4583 "dhcp4_parser.cc"
    break;

  case 863: // queue_control_params: queue_control_params ","
#line 2943 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4591 "dhcp4_parser.cc"
    break;

  case 870: // enable_queue: "enable-queue" ":" "boolean"
#line 2956 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4601 "dhcp4_parser.cc"
    break;

  case 871: // $@131: %empty
#line 2962 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4610 "dhcp4_parser.cc"
    break;

  case 872: // queue_type: "queue-type" $@131 ":" "constant string"
#line 2965 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4620 "dhcp4_parser.cc"
    break;

  case 873: // capacity: "capacity" ":" "integer"
#line 2971 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4630 "dhcp4_parser.cc"
    break;

  case 874: // $@132: %empty
#line 2977 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4639 "dhcp4_parser.cc"
    break;

  case 875: // arbitrary_map_entry: "constant string" $@132 ":" value
#line 2980 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4648 "dhcp4_parser.cc"
    break;

  case 876: // $@133: %empty
#line 2987 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4660 "dhcp4_parser.cc"
    break;

  case 877: // dhcp_ddns: "dhcp-ddns" $@133 ":" "{" dhcp_ddns_params "}"
#line 2993 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4671 "dhcp4_parser.cc"
    break;

  case 878: // $@134: %empty
#line 3000 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4681 "dhcp4_parser.cc"
    break;

  case 879: // sub_dhcp_ddns: "{" $@134 dhcp_ddns_params "}"
#line 3004 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4691 "dhcp4_parser.cc"
    break;

  case 882: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3012 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4699 "dhcp4_parser.cc"
    break;

  case 894: // enable_updates: "enable-updates" ":" "boolean"
#line 3030 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4709 "dhcp4_parser.cc"
    break;

  case 895: // $@135: %empty
#line 3036 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4718 "dhcp4_parser.cc"
    break;

  case 896: // server_ip: "server-ip" $@135 ":" "constant string"
#line 3039 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4728 "dhcp4_parser.cc"
    break;

  case 897: // server_port: "server-port" ":" "integer"
#line 3045 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4738 "dhcp4_parser.cc"
    break;

  case 898: // $@136: %empty
#line 3051 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4747 "dhcp4_parser.cc"
    break;

  case 899: // sender_ip: "sender-ip" $@136 ":" "constant string"
#line 3054 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4757 "dhcp4_parser.cc"
    break;

  case 900: // sender_port: "sender-port" ":" "integer"
#line 3060 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4767 "dhcp4_parser.cc"
    break;

  case 901: // max_queue_size: "max-queue-size" ":" "integer"
#line 3066 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 902: // $@137: %empty
#line 3072 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4786 "dhcp4_parser.cc"
    break;

  case 903: // ncr_protocol: "ncr-protocol" $@137 ":" ncr_protocol_value
#line 3075 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4795 "dhcp4_parser.cc"
    break;

  case 904: // ncr_protocol_value: "udp"
#line 3081 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4801 "dhcp4_parser.cc"
    break;

  case 905: // ncr_protocol_value: "tcp"
#line 3082 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4807 "dhcp4_parser.cc"
    break;

  case 906: // $@138: %empty
#line 3085 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4816 "dhcp4_parser.cc"
    break;

  case 907: // ncr_format: "ncr-format" $@138 ":" "JSON"
#line 3088 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4826 "dhcp4_parser.cc"
    break;

  case 908: // $@139: %empty
#line 3096 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4838 "dhcp4_parser.cc"
    break;

  case 909: // config_control: "config-control" $@139 ":" "{" config_control_params "}"
#line 3102 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4848 "dhcp4_parser.cc"
    break;

  case 910: // $@140: %empty
#line 3108 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4858 "dhcp4_parser.cc"
    break;

  case 911: // sub_config_control: "{" $@140 config_control_params "}"
#line 3112 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4867 "dhcp4_parser.cc"
    break;

  case 914: // config_control_params: config_control_params ","
#line 3120 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4875 "dhcp4_parser.cc"
    break;

  case 917: // $@141: %empty
#line 3130 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4887 "dhcp4_parser.cc"
    break;

  case 918: // config_databases: "config-databases" $@141 ":" "[" database_list "]"
#line 3136 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4896 "dhcp4_parser.cc"
    break;

  case 919: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3141 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4906 "dhcp4_parser.cc"
    break;

  case 920: // $@142: %empty
#line 3149 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4918 "dhcp4_parser.cc"
    break;

  case 921: // loggers: "loggers" $@142 ":" "[" loggers_entries "]"
#line 3155 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4927 "dhcp4_parser.cc"
    break;

  case 924: // loggers_entries: loggers_entries ","
#line 3164 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4935 "dhcp4_parser.cc"
    break;

  case 925: // $@143: %empty
#line 3170 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4945 "dhcp4_parser.cc"
    break;

  case 926: // logger_entry: "{" $@143 logger_params "}"
#line 3174 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4953 "dhcp4_parser.cc"
    break;

  case 929: // logger_params: logger_params ","
#line 3180 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4961 "dhcp4_parser.cc"
    break;

  case 937: // debuglevel: "debuglevel" ":" "integer"
#line 3194 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4971 "dhcp4_parser.cc"
    break;

  case 938: // $@144: %empty
#line 3200 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4980 "dhcp4_parser.cc"
    break;

  case 939: // severity: "severity" $@144 ":" "constant string"
#line 3203 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4990 "dhcp4_parser.cc"
    break;

  case 940: // $@145: %empty
#line 3209 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5002 "dhcp4_parser.cc"
    break;

  case 941: // output_options_list: "output-options" $@145 ":" "[" output_options_list_content "]"
#line 3215 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5011 "dhcp4_parser.cc"
    break;

  case 944: // output_options_list_content: output_options_list_content ","
#line 3222 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5019 "dhcp4_parser.cc"
    break;

  case 945: // $@146: %empty
#line 3227 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5029 "dhcp4_parser.cc"
    break;

  case 946: // output_entry: "{" $@146 output_params_list "}"
#line 3231 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5037 "dhcp4_parser.cc"
    break;

  case 949: // output_params_list: output_params_list ","
#line 3237 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5045 "dhcp4_parser.cc"
    break;

  case 955: // $@147: %empty
#line 3249 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5054 "dhcp4_parser.cc"
    break;

  case 956: // output: "output" $@147 ":" "constant string"
#line 3252 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5064 "dhcp4_parser.cc"
    break;

  case 957: // flush: "flush" ":" "boolean"
#line 3258 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5074 "dhcp4_parser.cc"
    break;

  case 958: // maxsize: "maxsize" ":" "integer"
#line 3264 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5084 "dhcp4_parser.cc"
    break;

  case 959: // maxver: "maxver" ":" "integer"
#line 3270 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5094 "dhcp4_parser.cc"
    break;

  case 960: // $@148: %empty
#line 3276 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5103 "dhcp4_parser.cc"
    break;

  case 961: // pattern: "pattern" $@148 ":" "constant string"
#line 3279 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5113 "dhcp4_parser.cc"
    break;

  case 962: // $@149: %empty
#line 3285 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5125 "dhcp4_parser.cc"
    break;

  case 963: // compatibility: "compatibility" $@149 ":" "{" compatibility_params "}"
#line 3291 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5134 "dhcp4_parser.cc"
    break;

  case 966: // compatibility_params: compatibility_params ","
#line 3298 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5142 "dhcp4_parser.cc"
    break;

  case 972: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3310 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5152 "dhcp4_parser.cc"
    break;

  case 973: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3316 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5162 "dhcp4_parser.cc"
    break;

  case 974: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3322 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5172 "dhcp4_parser.cc"
    break;

  case 975: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3328 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5182 "dhcp4_parser.cc"
    break;


#line 5186 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1377;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     463, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377,    28,    26,    35,    37,    39,    44,
      58,    62,    71,    83,   123,   171,   191,   193, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377,    26,  -174,   192,   204,    72,   722,
    1468,   736,    -3,   101,   353,   -73,   276,    80, -1377,   211,
     201,   244,   221,   249, -1377,    42, -1377, -1377, -1377, -1377,
     268,   313,   335, -1377, -1377, -1377,   336,   344, -1377, -1377,
   -1377,   354,   357,   364,   373,   375,   383,   387,   402,   404,
     411,   418, -1377,   435,   436,   451,   452,   460, -1377, -1377,
   -1377,   461,   475,   476,   490,   495,   497,   498, -1377, -1377,
   -1377,   499, -1377, -1377, -1377, -1377, -1377,   501,   502,   503,
   -1377, -1377, -1377, -1377, -1377,   505, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   506,   507,   511, -1377, -1377,   515, -1377,
      50, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377,   516,   518,   522,   525,
   -1377,   106, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   528, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   144, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
     531, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377,   151, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   349,
     378, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   381, -1377, -1377,   532, -1377, -1377, -1377,
     534, -1377, -1377,   391,   537, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   542,   544,
     551, -1377, -1377, -1377, -1377, -1377,   533,   555, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377,   154, -1377, -1377, -1377,   556, -1377,   558, -1377,
     562,   563, -1377, -1377, -1377, -1377, -1377,   162, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   564,   169,
   -1377, -1377, -1377, -1377,    26,    26, -1377,   333,   571, -1377,
   -1377,   572,   573,   574,   339,   340,   341,   578,   579,   581,
     350,   352,   589,   590,   591,   358,   360,   365,   367,   368,
     370,   363,   369,   379,   376,   390,   596,   393,   400,   406,
     409,   412,   613,   619,   623,   414,   415,   394,   413,   419,
     421,   416,   640,   658,   660,   427,   665,   666,   667,   668,
     669,   434,   437,   438,   671,   672,   676,   678,   679,   446,
     681,   696,   697,   698,   699,   701,   702,   467,   468,   469,
     706,   707, -1377,   204, -1377,   708,   709,   710,   478,   481,
     477,   484,    72, -1377,   715,   719,   721,   723,   724,   725,
     492,   727,   728,   729,   730,   731,   722, -1377,   732,   500,
    1468, -1377,   733,   737,   740,   741,   742,   743,   744,   745,
   -1377,   736, -1377,   746,   754,   521,   756,   757,   758,   486,
   -1377,   101,   759,   524,   526,   527,   761, -1377,   353,   767,
     768,    40, -1377,   535,   769,   536,   772,   543,   545,   776,
     778,   276, -1377,   780,   547,    80, -1377, -1377, -1377,   784,
     785,   796,   797,   798, -1377, -1377, -1377,   554,   569,   583,
   -1377, -1377,   817,   819,   822, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377,   592, -1377, -1377, -1377,
   -1377, -1377,   -98,   593,   594, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377,   823,   827,   828, -1377,   597,   433,   830,   829,
     603, -1377, -1377, -1377,   838,   840,   849,   853,   852, -1377,
     856,   858,   861,   860,   863,   631,   634, -1377, -1377, -1377,
     868,   867, -1377,   870,   306,   148, -1377, -1377, -1377, -1377,
   -1377,   639,   641,   650,   872,   651,   652, -1377,   870,   870,
     870,   657,   888, -1377,   659, -1377, -1377,   870,   661,   662,
     670,   673,   674,   675,   677, -1377,   680,   682, -1377,   683,
     684,   685, -1377, -1377,   686, -1377, -1377, -1377,   870, -1377,
     687,   829, -1377, -1377,   688, -1377,   689, -1377, -1377,     4,
     703, -1377,   892, -1377, -1377,    26,   204,    80,    72,   159,
   -1377, -1377, -1377,   384,   384,   895, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   897,   898,   899, -1377, -1377,
   -1377, -1377, -1377, -1377,   901, -1377, -1377, -1377,   229,   902,
     906,   908,    63,    85,   717,   909,   296,   276, -1377, -1377,
     911,   -38, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   922, -1377, -1377, -1377, -1377, -1377, -1377,
     779, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   895, -1377,   172,   187,   198,
   -1377, -1377,   208, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
     927,   928,   929,   930,   931,   932,   933,   934,   935,   936,
   -1377,   937,   938, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   224, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377,   300, -1377,   939,   940, -1377, -1377,   941,   943, -1377,
   -1377,   942,   946, -1377, -1377,   944,   948, -1377, -1377,   947,
     949, -1377, -1377, -1377, -1377, -1377, -1377,   121, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   134, -1377, -1377,   950,   952,
   -1377, -1377,   951,   955, -1377,   956,   957,   958,   959,   960,
     961,   302, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   962,
     963,   964, -1377,   308, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   965, -1377,   966, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   318, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   968,   969, -1377,   967, -1377,   971, -1377,
   -1377, -1377,   346, -1377, -1377, -1377, -1377, -1377,   347, -1377,
     225, -1377,   972,   973,   974,   975, -1377,   361, -1377, -1377,
   -1377, -1377, -1377,   747, -1377,   976,   977, -1377, -1377,   978,
   -1377,   979, -1377, -1377, -1377,   983,   984,   159, -1377,   985,
     986,   987,   988,   755,   704,   760,   762,   765,   771,   775,
     787,   788,   790,   990,   766,   793,   991,   992,   993,   995,
     996,  1001,   384, -1377, -1377,   384, -1377,   895,   722, -1377,
     897,   101, -1377,   898,   353, -1377,   899,  1410, -1377,   901,
     229, -1377,   280,   902, -1377,   736, -1377,   906,   -73, -1377,
     908,   794,   801,   805,   811,   814,   816,    63, -1377,   777,
     824,   834,    85, -1377,  1012,  1019,  1053,   848,  1061,   826,
    1083,   717, -1377,   717, -1377,   909,   854,  1085,   857,  1092,
     296, -1377, -1377,   149,   911, -1377,   862,   864,   889,   905,
     -38, -1377, -1377,  1101,   980,  1468, -1377,   922,  1108, -1377,
   -1377,   913,   953, -1377,   970,   981,   982,   989, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   205, -1377,
   -1377,   994,   997,   998,   999,   190,  1000, -1377,   362, -1377,
     377, -1377,  1127, -1377,  1131, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377,   385, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
    1163,  1173, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,  1175,  1182, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377,  1184, -1377,   389, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   160,
    1002,  1003, -1377,  1186, -1377,  1190, -1377,   395, -1377, -1377,
    1004, -1377,    26, -1377, -1377,  1192, -1377, -1377, -1377, -1377,
   -1377,   399, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,  1005,   473, -1377,   870, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377,  1410, -1377,  1193,
    1194,  1006,  1007, -1377,   280, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,    67,  1195, -1377, -1377, -1377,  1196,  1010,
    1199,   149, -1377, -1377, -1377, -1377, -1377,  1008,  1013, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   479,
   -1377, -1377, -1377, -1377, -1377, -1377,  1200,  1202, -1377,  1203,
   -1377,  1014, -1377, -1377, -1377,  1206,  1208,  1209,  1211,    67,
   -1377,   -70, -1377,  1195,  1210, -1377,   804,  1015,  1016,  1215,
   -1377, -1377, -1377, -1377, -1377, -1377,   487, -1377, -1377, -1377,
   -1377,   265, -1377, -1377, -1377, -1377, -1377,  1214,  1218,   -70,
   -1377,   -99,  1210, -1377, -1377,  1219,  1221, -1377,  1017, -1377,
   -1377,  1223,  1224,  1225, -1377,   488, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,     7, -1377,  1214, -1377,  1226,  1009,  1018,
    1020,  1228,   -99, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377,   489, -1377, -1377, -1377, -1377,  1022, -1377, -1377, -1377,
    1024, -1377,  1229,  1234,     7, -1377, -1377, -1377,  1025,  1026,
   -1377, -1377, -1377
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   214,     9,   402,    11,   629,    13,
     674,    15,   544,    17,   553,    19,   592,    21,   364,    23,
     878,    25,   910,    27,    46,    39,     0,     0,     0,     0,
       0,   676,     0,   555,   594,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   908,   199,   232,
       0,     0,     0,   696,   698,   700,     0,     0,   230,   243,
     245,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,     0,   164,   171,
     173,     0,     0,     0,     0,     0,     0,     0,   393,   542,
     583,     0,   156,   177,   482,   661,   663,     0,     0,     0,
     326,   723,   665,   355,   376,     0,   341,   760,   762,   859,
     876,   187,   189,     0,     0,     0,   920,   962,     0,   141,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   104,   137,   138,    93,    94,    95,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   114,   115,   129,   130,   131,   133,   134,   135,
     139,   140,    78,    79,   101,    80,    81,    82,   132,    86,
      87,    76,   105,   106,   107,    77,    84,    85,    99,   100,
     102,    96,    97,    98,    83,    88,    89,    90,    91,    92,
     103,   113,   136,   216,   218,   222,     0,     0,     0,     0,
     213,     0,   201,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   462,   464,   466,   620,   460,   468,     0,   472,
     474,   476,   470,   718,   459,   407,   408,   409,   410,   411,
     436,   437,   438,   439,   440,   457,   426,   427,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   458,     0,   404,   414,   431,   432,
     433,   415,   417,   418,   419,   420,   422,   423,   424,   416,
     412,   413,   434,   435,   421,   428,   429,   430,   425,   658,
       0,   657,   641,   642,   643,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   637,   638,   639,   640,
     636,     0,   631,   634,   635,   655,   656,   716,   702,   704,
     706,   710,   708,   714,   712,   695,   689,   693,   694,     0,
     677,   678,   690,   691,   692,   686,   681,   687,   683,   684,
     685,   688,   682,     0,   573,   291,     0,   577,   575,   580,
       0,   569,   570,     0,   556,   557,   560,   572,   561,   562,
     563,   579,   564,   565,   566,   567,   568,   611,     0,     0,
       0,   618,   609,   610,   613,   614,     0,   595,   596,   599,
     600,   601,   602,   603,   604,   605,   608,   606,   607,   372,
     374,   369,     0,   366,   370,   371,     0,   895,     0,   898,
       0,     0,   902,   906,   893,   891,   892,     0,   880,   883,
     884,   885,   886,   887,   888,   889,   890,   917,     0,     0,
     912,   915,   916,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    69,    66,     0,     0,     0,     0,     0,
       0,     0,   203,   215,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   406,   403,     0,     0,
     633,   630,     0,     0,     0,     0,     0,     0,     0,     0,
     675,   680,   545,     0,     0,     0,     0,     0,     0,     0,
     554,   559,     0,     0,     0,     0,     0,   593,   598,     0,
       0,   368,   365,     0,     0,     0,     0,     0,     0,     0,
       0,   882,   879,     0,     0,   914,   911,    49,    41,     0,
       0,     0,     0,     0,   158,   159,   160,     0,     0,     0,
     197,   198,     0,     0,     0,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,     0,   192,   193,   161,
     162,   163,     0,     0,     0,   175,   176,   183,   184,   185,
     186,   191,     0,     0,     0,   155,     0,     0,     0,     0,
       0,   478,   479,   480,     0,     0,     0,     0,     0,   759,
       0,     0,     0,     0,     0,     0,     0,   194,   195,   196,
       0,     0,    68,     0,     0,     0,   226,   227,   228,   229,
     202,     0,     0,     0,     0,     0,     0,   481,     0,     0,
       0,     0,     0,   405,     0,   660,   632,     0,     0,     0,
       0,     0,     0,     0,     0,   679,     0,     0,   571,     0,
       0,     0,   582,   558,     0,   615,   616,   617,     0,   597,
       0,     0,   367,   894,     0,   897,     0,   900,   901,     0,
       0,   881,     0,   919,   913,     0,     0,     0,     0,     0,
     697,   699,   701,     0,     0,   247,   154,   166,   167,   168,
     169,   170,   165,   172,   174,   395,   546,   585,   157,   179,
     180,   181,   182,   178,   484,    38,   662,   664,     0,     0,
     667,   357,     0,     0,     0,   764,     0,     0,   188,   190,
       0,     0,    51,   217,   220,   221,   219,   224,   225,   223,
     463,   465,   467,   622,   461,   469,   473,   475,   477,   471,
       0,   659,   717,   703,   705,   707,   711,   709,   715,   713,
     574,   292,   578,   576,   581,   612,   619,   373,   375,   896,
     899,   904,   905,   903,   907,   247,    42,     0,     0,     0,
     239,   241,     0,   234,   237,   238,   282,   284,   286,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     302,     0,     0,   309,   311,   313,   315,   317,   319,   320,
     321,   322,   323,   324,   281,     0,   254,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,   252,     0,   248,   249,   400,     0,   396,   397,
     551,     0,   547,   548,   590,     0,   586,   587,   489,     0,
     485,   486,   336,   337,   338,   339,   340,     0,   328,   331,
     332,   333,   334,   335,   728,     0,   725,   672,     0,   668,
     669,   362,     0,   358,   359,     0,     0,     0,     0,     0,
       0,     0,   378,   381,   382,   383,   384,   385,   386,     0,
       0,     0,   351,     0,   343,   346,   347,   348,   349,   350,
     787,   792,   794,     0,   817,     0,   798,   786,   779,   780,
     781,   784,   785,     0,   771,   774,   775,   776,   777,   782,
     783,   778,   769,     0,   765,   766,     0,   871,     0,   874,
     867,   868,     0,   861,   864,   865,   866,   869,     0,   925,
       0,   922,     0,     0,     0,     0,   971,     0,   964,   967,
     968,   969,   970,    53,   627,     0,   623,   624,   721,     0,
     720,     0,    62,   909,   200,     0,     0,   236,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   256,   231,   244,     0,   246,   251,     0,   394,
     399,   555,   543,   550,   594,   584,   589,     0,   483,   488,
     330,   327,   730,   727,   724,   676,   666,   671,     0,   356,
     361,     0,     0,     0,     0,     0,     0,   380,   377,     0,
       0,     0,   345,   342,     0,     0,     0,     0,     0,     0,
       0,   773,   761,     0,   763,   768,     0,     0,     0,     0,
     863,   860,   877,     0,   924,   921,     0,     0,     0,     0,
     966,   963,    55,     0,    54,     0,   621,   626,     0,   719,
     918,     0,     0,   235,     0,     0,     0,     0,   290,   293,
     294,   295,   296,   297,   298,   299,   300,   301,     0,   307,
     308,     0,     0,     0,     0,     0,     0,   255,     0,   250,
       0,   398,     0,   549,     0,   588,   541,   513,   514,   515,
     497,   498,   518,   519,   520,   521,   522,   539,   500,   501,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   540,   494,   495,   496,
     509,   510,   511,   512,   506,   507,   508,     0,   491,   499,
     516,   517,   502,   503,   504,   505,   487,   329,   753,   755,
       0,     0,   747,   748,   749,   750,   751,   752,   740,   741,
     745,   746,   742,   743,   744,     0,   731,   732,   735,   736,
     737,   738,   739,   726,     0,   670,     0,   360,   387,   388,
     389,   390,   391,   392,   379,   352,   353,   354,   344,     0,
       0,     0,   796,     0,   797,     0,   772,     0,   767,   870,
       0,   873,     0,   862,   940,     0,   938,   936,   930,   934,
     935,     0,   927,   932,   933,   931,   923,   972,   973,   974,
     975,   965,    52,    57,     0,   625,     0,   240,   242,   283,
     285,   287,   289,   304,   305,   306,   303,   310,   312,   314,
     316,   318,   325,   253,   401,   552,   591,   493,   490,     0,
       0,     0,     0,   729,   734,   673,   363,   789,   790,   791,
     788,   793,   795,     0,   800,   770,   872,   875,     0,     0,
       0,   929,   926,    56,   628,   722,   492,     0,     0,   757,
     758,   733,   829,   832,   834,   836,   828,   827,   826,     0,
     819,   822,   823,   824,   825,   805,     0,   801,   802,     0,
     937,     0,   928,   754,   756,     0,     0,     0,     0,   821,
     818,     0,   799,   804,     0,   939,     0,     0,     0,     0,
     820,   815,   814,   810,   812,   813,     0,   807,   811,   803,
     945,     0,   942,   831,   830,   833,   835,   838,     0,   809,
     806,     0,   944,   941,   843,     0,   839,   840,     0,   808,
     955,     0,     0,     0,   960,     0,   947,   950,   951,   952,
     953,   954,   943,     0,   837,   842,   816,     0,     0,     0,
       0,     0,   949,   946,   855,   857,   854,   848,   850,   852,
     853,     0,   845,   849,   851,   841,     0,   957,   958,   959,
       0,   948,     0,     0,   847,   844,   956,   961,     0,     0,
     846,   856,   858
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   -59, -1377,  -623, -1377,   512,
   -1377, -1377, -1377, -1377, -1377, -1377,  -639, -1377, -1377, -1377,
     -67, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   509,   711,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
   -1377, -1377, -1377, -1377,    94, -1377, -1377,    97,   102,   -13,
      13,    41,    51, -1377, -1377,    53, -1377,    56, -1377,    59,
     104,    64, -1377, -1377,    66,    69,    74,    76,    79, -1377,
      81, -1377,   105, -1377, -1377, -1377, -1377, -1377,    43, -1377,
   -1377, -1377,   517,   726, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,   220, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377,   431, -1377,   202, -1377,  -738,   210, -1377, -1377,
   -1376, -1377, -1373, -1377, -1377, -1377, -1377,   -63, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377,  -770, -1377,  -769, -1377,  -766, -1377, -1377,
   -1377,   108, -1377, -1377, -1377, -1377, -1377, -1377,   195, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377,   168, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377,   188, -1377, -1377, -1377,   189,
     690, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   183, -1377,
   -1377, -1377, -1377, -1377, -1377, -1060, -1377, -1377, -1377,   212,
   -1377, -1377, -1377,   217,   735, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1058, -1377,   -29, -1377,   -18, -1377,    -4,
   -1377,     5, -1377,   107,   110,   112, -1377, -1377, -1377, -1377,
   -1377,   213, -1377, -1377,   -40,   -60, -1377, -1377, -1377, -1377,
   -1377,   216, -1377, -1377, -1377,   222, -1377,   713, -1377,   -34,
   -1377, -1377, -1377, -1377, -1377,   -27, -1377, -1377, -1377, -1377,
   -1377,   -32, -1377, -1377, -1377,   227, -1377, -1377, -1377,   223,
   -1377,   712, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377,   167, -1377, -1377, -1377,
     161,   748, -1377, -1377, -1377,   -44, -1377,     3, -1377,   -56,
   -1377, -1377, -1377,   218, -1377, -1377, -1377,   226, -1377,   739,
     -48, -1377,    -7, -1377,    15, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1057, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
     230, -1377, -1377, -1377,   -28, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   197,
   -1377,   203,   206, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377,   -78, -1377, -1377,  -101,
   -1377, -1377, -1377, -1377, -1377,   -68, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377,  -126, -1377, -1377,
    -149, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   209, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   539,
     734, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,   584,   750,
   -1377, -1377, -1377, -1377, -1377, -1377,   214, -1377, -1377,   -17,
   -1377, -1377, -1377, -1377, -1377, -1377,   -89, -1377, -1377,  -116,
   -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377, -1377,
     231, -1377, -1377, -1377, -1377
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   776,
      82,    83,    39,    64,    79,    80,   793,  1023,  1133,  1134,
     874,    41,    66,    85,   458,    86,    43,    67,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   486,   174,   175,   506,   176,   177,   178,   179,
     180,   181,   182,   492,   762,   183,   493,   184,   494,   185,
     186,   187,   507,   773,   188,   189,   190,   191,   192,   525,
     193,   526,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   462,   241,   242,    45,    68,   243,   535,   244,   536,
     796,   245,   537,   799,   246,   247,   248,   249,   203,   472,
     204,   463,   842,   843,   844,  1035,   845,  1036,   205,   473,
     206,   474,   903,   904,   905,  1065,   875,   876,   877,  1039,
     878,  1040,   879,  1041,   880,  1042,   881,   882,   574,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,  1053,
    1316,   893,   894,   895,  1056,   896,  1057,   897,  1058,   898,
    1059,   899,  1060,   900,  1061,   207,   514,   927,   928,   929,
     930,   931,   932,   933,   208,   520,   963,   964,   965,   966,
     967,   209,   517,   942,   943,   944,  1088,    59,    75,   422,
     423,   424,   589,   425,   590,   210,   518,   951,   952,   953,
     954,   955,   956,   957,   958,   211,   502,   907,   908,   909,
    1068,    47,    69,   295,   296,   297,   548,   298,   544,   299,
     545,   300,   546,   301,   549,   302,   554,   303,   551,   304,
     552,   305,   553,   212,   213,   214,   309,   215,   508,   919,
     920,   921,  1077,  1217,  1218,   216,   503,    53,    72,   911,
     912,   913,  1071,    55,    73,   383,   384,   385,   386,   387,
     388,   389,   573,   390,   577,   391,   576,   392,   393,   578,
     394,   217,   504,   915,   916,   917,  1074,    57,    74,   406,
     407,   408,   409,   410,   582,   411,   412,   413,   414,   415,
     416,   586,   311,   547,  1025,  1026,  1027,  1135,    49,    70,
     341,   342,   343,   558,   344,   218,   509,   219,   510,   220,
     516,   938,   939,   940,  1085,    51,    71,   359,   360,   361,
     221,   467,   222,   468,   223,   469,   365,   563,   366,   564,
     367,   565,   368,   567,   369,   566,   370,   569,   371,   568,
     372,   562,   318,   555,  1029,  1030,  1138,   224,   515,   935,
     936,  1082,  1245,  1246,  1247,  1248,  1249,  1329,  1250,  1330,
    1251,  1252,   225,   226,   521,   227,   522,   993,   994,   995,
    1113,   983,   984,   985,  1104,  1340,   986,  1105,   987,  1106,
     988,   989,   990,  1110,  1376,  1377,  1378,  1391,  1406,  1407,
    1408,  1418,   991,  1108,  1369,  1370,  1371,  1385,  1414,  1372,
    1386,  1373,  1387,  1374,  1388,  1425,  1426,  1427,  1443,  1461,
    1462,  1463,  1472,  1464,  1473,   228,   523,  1002,  1003,  1004,
    1005,  1117,  1006,  1007,  1119,   229,   524,    61,    76,   437,
     438,   439,   440,   594,   441,   442,   596,   443,   444,   445,
     599,   833,   446,   600,   230,   461,    63,    77,   449,   450,
     451,   603,   452,   231,   530,  1010,  1011,  1123,  1291,  1292,
    1293,  1294,  1350,  1295,  1348,  1411,  1412,  1421,  1435,  1436,
    1437,  1447,  1438,  1439,  1440,  1441,  1451,   232,   531,  1017,
    1018,  1019,  1020,  1021,  1022
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   240,   264,   321,   355,    78,   381,   402,   421,   434,
     382,   403,   373,   314,   978,   979,   901,  1208,   980,  1209,
    1225,   315,   831,   362,   250,   312,   345,   357,    28,   395,
     417,    29,   435,    30,   375,    31,   775,   310,   340,   356,
     404,   336,    40,   268,    42,   459,    44,   405,   847,   848,
     460,    46,   337,   533,   135,   136,   278,   322,   534,   806,
     807,   808,   316,    81,   363,    48,   338,  1457,   812,    50,
    1458,   251,   313,   346,   358,   339,   396,   418,    52,   436,
     419,   420,   279,   323,   317,   265,   364,   233,   234,   826,
      54,   235,   447,   448,   236,   237,   238,   239,  1457,   129,
     266,  1458,   267,   757,   758,   759,   760,  1362,   775,   542,
     280,   324,   294,  1430,   543,  1401,  1431,  1432,  1433,  1434,
     281,   325,   282,   326,  1080,   283,   327,  1081,   284,   328,
      56,   135,   136,   286,   329,   287,   330,  1083,   288,   331,
    1084,   374,   761,   289,   332,   290,   333,   556,   291,   334,
     292,   335,   557,   269,   560,   270,   271,   591,   272,   561,
     273,   274,   592,   275,   158,   601,   276,   158,   797,   798,
     602,   277,   605,   285,   293,   533,   306,   606,    58,   307,
    1032,   308,  1012,  1013,  1014,  1015,   840,   841,  1454,  1455,
     605,   135,   136,   419,   420,  1033,   135,   136,    60,   158,
      62,   542,    84,   832,   454,   375,  1034,   376,   377,   135,
     136,  1037,   378,   379,   380,    87,  1038,   453,    88,   945,
     946,   947,   948,   949,   950,   135,   136,  1062,  1124,   456,
      89,  1125,  1063,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   158,  1363,  1364,  1365,   455,   959,
     960,   961,   457,   375,   867,   868,   869,   870,   871,   872,
    1313,  1314,  1315,    32,    33,    34,    35,  1208,  1422,  1209,
    1225,  1423,   464,   135,   136,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,  1062,   158,  1097,   129,   130,  1064,   158,
    1098,  1102,    93,    94,    95,    96,  1103,   465,   131,   132,
     133,  1111,   158,   794,   795,   134,  1112,  1168,   135,   136,
    1337,  1338,  1339,   137,   138,   139,   140,   141,   158,   466,
     470,   978,   979,   978,   979,   980,   142,   980,   471,  1120,
     601,   101,   102,   103,  1121,  1122,   143,   570,   475,   144,
    1284,   476,  1285,  1286,  1130,  1062,   145,   146,   477,  1131,
    1323,   147,   148,   922,   923,   924,   925,   478,   926,   479,
     556,   571,   129,   130,   375,  1324,   158,   480,  1327,   572,
     149,   481,   591,  1328,   150,   607,   608,  1336,  1111,   580,
     135,   136,  1351,  1345,   135,   136,   482,  1352,   483,   151,
     152,   153,   154,   155,   156,   484,  1228,  1229,  1230,  1231,
     135,   136,   485,   157,   846,   847,   848,   849,   850,   851,
     852,   853,   854,   855,   856,   857,   858,   859,   860,   487,
     488,   158,   861,   862,   863,   864,   865,   866,   867,   868,
     869,   870,   871,   872,   873,   489,   490,   375,   397,   376,
     377,   398,   399,   400,   491,   495,   159,   426,   427,   428,
     429,   430,   431,   432,   433,   240,   560,   135,   136,   496,
     497,  1354,  1389,   996,   997,   998,   401,  1390,   375,   264,
    1419,  1452,  1474,   321,   498,  1420,  1453,  1475,   250,   499,
     314,   500,   501,   505,   355,   511,   512,   513,   315,   519,
     527,   528,   312,   158,   381,   529,   345,   158,   382,   532,
     538,   402,   539,   362,   310,   403,   540,   357,   340,   541,
     268,   336,   550,   999,   434,   559,   575,   395,   579,   356,
     581,   587,   337,   278,   417,   251,   583,   322,   584,   316,
     769,   770,   771,   772,   404,   585,   338,   435,   588,   313,
     593,   405,   595,   346,   363,   339,   597,   598,   604,   279,
     609,   317,   265,   323,   358,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   396,   619,   364,   266,   620,   267,
     158,   418,   621,   622,   623,   624,   625,   280,   626,   294,
     636,   324,   631,   627,   436,   628,   629,   281,   632,   282,
     630,   325,   283,   326,   634,   284,   327,   642,   633,   328,
     286,   158,   287,   643,   329,   288,   330,   644,   635,   331,
     289,   637,   290,   647,   332,   291,   333,   292,   638,   334,
     269,   335,   270,   271,   652,   272,   639,   273,   274,   640,
     275,   648,   641,   276,   645,   646,   651,   649,   277,   650,
     285,   293,   653,   306,   654,   655,   307,  1355,   308,   656,
     657,   658,   659,   660,   661,   664,   665,   662,   663,   159,
     666,   240,   667,   668,   669,   670,   836,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     671,   672,   673,   674,   250,   675,   676,   677,   678,   679,
     680,   681,   683,   684,   685,   688,   962,   977,   686,   691,
     434,   687,   689,   692,  1016,   693,   722,   694,   695,   696,
     697,   698,   699,   700,   701,   702,   704,   707,   705,   968,
     981,   708,  1000,   435,   709,   710,   711,   712,   713,   714,
     716,   251,    91,    92,    93,    94,    95,    96,   717,   718,
     719,   720,   721,   724,   725,   728,   726,   727,    93,    94,
      95,   730,   731,   734,   735,   733,   736,   863,   864,   865,
     739,   737,   740,   738,   742,   743,   969,   982,   745,  1001,
     436,   750,   746,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   747,   748,   749,   751,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     752,   252,   253,   254,   753,   130,   754,   755,   765,   756,
     763,   764,   766,   767,   768,   774,    30,   132,   133,   130,
     777,   135,   136,   778,   255,   779,   135,   136,   256,   257,
     258,   137,   138,   139,   780,   259,   260,   261,   781,   782,
     135,   136,   262,   783,   142,   784,   785,   786,   788,   347,
     787,   789,   263,   790,   791,   792,   800,   803,   801,   348,
     349,   350,   351,   352,   353,   354,   970,   802,   804,   805,
     971,   972,   973,   974,   809,   810,   811,   835,   813,   814,
     975,   976,   902,   834,   906,   910,   914,   815,   918,   934,
     816,   817,   818,   937,   819,   941,   992,   820,  1009,   821,
     822,   823,   824,   825,   827,   829,   830,   151,   152,  1024,
    1028,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,
    1052,  1054,  1055,  1067,  1149,  1066,  1070,  1069,  1072,  1073,
    1075,  1076,  1079,  1078,   158,  1087,  1086,  1089,  1090,   158,
    1091,  1092,  1093,  1094,  1095,  1096,  1099,  1100,  1101,  1107,
    1109,  1116,  1115,   158,  1114,  1118,  1126,  1127,  1128,  1129,
    1137,  1413,  1136,  1303,  1132,  1140,  1139,  1141,  1142,  1144,
    1145,  1146,  1147,  1148,  1158,  1161,  1162,  1163,  1150,  1164,
    1165,   264,  1151,  1152,   381,  1166,  1159,   402,   382,  1153,
    1176,   403,   314,  1154,  1207,  1232,  1269,  1265,   355,  1237,
     315,   421,  1238,  1270,   312,  1155,  1156,   395,  1157,  1222,
     417,  1160,  1258,  1220,  1242,   962,   310,   362,  1240,  1259,
     404,   357,   268,  1260,   977,  1219,   977,   405,  1210,  1261,
    1239,  1180,  1262,   356,  1263,   278,  1287,  1271,   968,  1211,
    1288,   316,  1266,  1016,  1190,  1273,  1274,   981,   321,   981,
    1223,   313,  1267,  1212,   396,  1243,  1000,   418,   363,  1289,
    1221,   279,  1213,   317,   265,  1241,  1272,  1275,   358,  1280,
    1191,   345,  1224,  1177,  1279,  1281,  1282,  1244,  1233,   266,
     364,   267,  1297,   340,  1298,   969,   336,  1302,  1178,   280,
    1179,   294,  1306,  1234,   982,  1235,   982,   337,  1192,   281,
    1206,   282,   322,  1001,   283,  1236,  1290,   284,  1193,  1299,
    1194,   338,   286,  1195,   287,  1325,  1196,   288,   346,  1326,
     339,  1198,   289,  1199,   290,  1300,  1200,   291,   323,   292,
    1307,  1201,   269,  1202,   270,   271,  1203,   272,  1204,   273,
     274,  1181,   275,  1182,  1183,   276,  1184,  1331,  1185,  1186,
     277,  1187,   285,   293,  1188,   306,   324,  1332,   307,  1189,
     308,  1197,  1205,  1333,  1214,  1334,   325,  1215,   326,  1216,
    1308,   327,  1335,  1343,   328,  1344,  1349,  1357,  1358,   329,
    1379,   330,  1375,  1381,   331,  1393,  1392,  1309,  1394,   332,
    1396,   333,  1397,  1398,   334,  1399,   335,  1410,  1310,  1311,
    1417,  1424,  1428,  1347,  1445,  1444,  1312,  1448,  1449,  1450,
    1466,  1317,  1470,  1478,  1318,  1319,  1320,  1322,  1479,  1341,
    1342,  1346,  1353,   828,   682,  1383,  1359,  1360,  1380,  1467,
    1384,  1395,  1415,  1416,  1446,   837,  1468,  1143,  1469,  1476,
    1176,  1477,  1481,  1482,  1207,   839,  1031,  1232,   690,  1169,
    1268,  1237,  1167,  1321,  1238,  1227,  1366,  1256,  1257,  1222,
    1264,   732,  1171,  1220,  1287,  1170,  1242,  1356,  1288,  1173,
    1240,   703,  1226,  1172,   723,  1219,  1304,  1174,  1210,  1367,
     729,  1180,  1239,  1175,  1305,  1255,  1361,  1289,   706,  1211,
     715,  1254,  1278,  1253,  1190,  1409,  1277,  1276,  1429,  1465,
    1223,  1400,  1366,  1212,  1402,  1480,  1008,  1243,  1403,  1283,
    1221,   838,  1213,  1442,  1382,   741,  1471,  1241,  1296,     0,
    1191,     0,  1224,  1177,     0,  1367,  1368,  1404,     0,  1244,
    1233,     0,  1402,     0,  1290,   744,  1403,     0,  1178,     0,
    1179,  1301,     0,     0,     0,  1234,     0,  1235,  1192,     0,
    1206,     0,     0,     0,     0,  1404,  1456,  1236,  1193,     0,
    1194,     0,     0,  1195,     0,     0,  1196,     0,     0,     0,
       0,  1198,  1368,  1199,  1405,     0,  1200,     0,     0,  1459,
       0,  1201,     0,  1202,     0,     0,  1203,  1456,  1204,     0,
       0,  1181,     0,  1182,  1183,     0,  1184,     0,  1185,  1186,
       0,  1187,  1405,     0,  1188,     0,     0,     0,     0,  1189,
    1459,  1197,  1205,     0,  1214,     0,     0,  1215,     0,  1216,
      91,    92,    93,    94,    95,    96,  1460,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1460,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   130,   375,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   132,   133,     0,     0,     0,
       0,     0,     0,     0,   135,   136,     0,   257,     0,   137,
     138,   139,     0,   259,   260,   261,     0,     0,     0,     0,
     262,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     263,   123,   124,   125,   126,     0,     0,     0,     0,     0,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,     0,     0,
       0,   319,   135,   136,     0,     0,     0,     0,     0,     0,
       0,   259,   260,   261,     0,     0,     0,     0,   262,   320,
       0,     0,     0,     0,     0,   151,   152,     0,     0,     0,
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
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   784,   784,   754,  1077,   784,  1077,
    1077,    69,    18,    71,    68,    69,    70,    71,     0,    73,
      74,     5,    76,     7,   104,     9,   659,    69,    70,    71,
      74,    70,     7,    69,     7,     3,     7,    74,    41,    42,
       8,     7,    70,     3,   124,   125,    69,    70,     8,   698,
     699,   700,    69,   237,    71,     7,    70,  1443,   707,     7,
    1443,    68,    69,    70,    71,    70,    73,    74,     7,    76,
     153,   154,    69,    70,    69,    69,    71,    15,    16,   728,
       7,    19,    12,    13,    22,    23,    24,    25,  1474,   102,
      69,  1474,    69,   201,   202,   203,   204,    40,   731,     3,
      69,    70,    69,   212,     8,   185,   215,   216,   217,   218,
      69,    70,    69,    70,     3,    69,    70,     6,    69,    70,
       7,   124,   125,    69,    70,    69,    70,     3,    69,    70,
       6,    40,   240,    69,    70,    69,    70,     3,    69,    70,
      69,    70,     8,    69,     3,    69,    69,     3,    69,     8,
      69,    69,     8,    69,   237,     3,    69,   237,    20,    21,
       8,    69,     3,    69,    69,     3,    69,     8,     7,    69,
       8,    69,   220,   221,   222,   223,    27,    28,   181,   182,
       3,   124,   125,   153,   154,     8,   124,   125,     7,   237,
       7,     3,    10,   199,     3,   104,     8,   106,   107,   124,
     125,     3,   111,   112,   113,    11,     8,     6,    14,   156,
     157,   158,   159,   160,   161,   124,   125,     3,     3,     8,
      26,     6,     8,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,   237,   178,   179,   180,     4,   164,
     165,   166,     3,   104,    64,    65,    66,    67,    68,    69,
      55,    56,    57,   237,   238,   239,   240,  1327,     3,  1327,
    1327,     6,     4,   124,   125,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     3,   237,     3,   102,   103,     8,   237,
       8,     3,    32,    33,    34,    35,     8,     4,   114,   115,
     116,     3,   237,    17,    18,   121,     8,  1065,   124,   125,
     170,   171,   172,   129,   130,   131,   132,   133,   237,     4,
       4,  1111,  1111,  1113,  1113,  1111,   142,  1113,     4,     3,
       3,    71,    72,    73,     8,     8,   152,     8,     4,   155,
     211,     4,   213,   214,     3,     3,   162,   163,     4,     8,
       8,   167,   168,   144,   145,   146,   147,     4,   149,     4,
       3,     3,   102,   103,   104,     8,   237,     4,     3,     8,
     186,     4,     3,     8,   190,   454,   455,     8,     3,     8,
     124,   125,     3,     8,   124,   125,     4,     8,     4,   205,
     206,   207,   208,   209,   210,     4,   136,   137,   138,   139,
     124,   125,     4,   219,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     4,
       4,   237,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,     4,     4,   104,   105,   106,
     107,   108,   109,   110,     4,     4,   533,   191,   192,   193,
     194,   195,   196,   197,   198,   542,     3,   124,   125,     4,
       4,     8,     3,   187,   188,   189,   133,     8,   104,   556,
       3,     3,     3,   560,     4,     8,     8,     8,   542,     4,
     556,     4,     4,     4,   571,     4,     4,     4,   556,     4,
       4,     4,   556,   237,   581,     4,   560,   237,   581,     4,
       4,   588,     4,   571,   556,   588,     4,   571,   560,     4,
     556,   560,     4,   237,   601,     4,     4,   581,     4,   571,
       3,     8,   560,   556,   588,   542,     4,   560,     4,   556,
     117,   118,   119,   120,   588,     4,   560,   601,     3,   556,
       4,   588,     4,   560,   571,   560,     4,     4,     4,   556,
     237,   556,   556,   560,   571,     4,     4,     4,     4,   240,
     240,   240,     4,     4,   581,     4,   571,   556,   238,   556,
     237,   588,   240,     4,     4,     4,   238,   556,   238,   556,
       4,   560,   239,   238,   601,   238,   238,   556,   239,   556,
     240,   560,   556,   560,   238,   556,   560,     4,   239,   560,
     556,   237,   556,     4,   560,   556,   560,     4,   238,   560,
     556,   238,   556,   239,   560,   556,   560,   556,   238,   560,
     556,   560,   556,   556,     4,   556,   240,   556,   556,   240,
     556,   238,   240,   556,   240,   240,   240,   238,   556,   238,
     556,   556,     4,   556,     4,   238,   556,  1306,   556,     4,
       4,     4,     4,     4,   240,     4,     4,   240,   240,   746,
       4,   748,     4,     4,   238,     4,   745,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
       4,     4,     4,     4,   748,     4,     4,   240,   240,   240,
       4,     4,     4,     4,     4,   238,   783,   784,   240,     4,
     787,   240,   238,     4,   791,     4,   240,     4,     4,     4,
     238,     4,     4,     4,     4,     4,     4,     4,   238,   783,
     784,     4,   786,   787,     4,     4,     4,     4,     4,     4,
       4,   748,    30,    31,    32,    33,    34,    35,     4,   238,
       4,     4,     4,     4,   240,     4,   240,   240,    32,    33,
      34,     4,     4,     4,   238,   240,     4,    60,    61,    62,
       4,   238,     4,   238,     4,   238,   783,   784,     4,   786,
     787,   237,     7,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     7,     7,     7,   237,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
     237,    99,   100,   101,     7,   103,     7,     5,     5,   237,
     237,   237,     5,     5,   237,     5,     7,   115,   116,   103,
     237,   124,   125,     5,   122,     5,   124,   125,   126,   127,
     128,   129,   130,   131,     5,   133,   134,   135,     5,     7,
     124,   125,   140,     7,   142,     7,     5,     7,   237,   133,
       7,   237,   150,     5,     7,     5,   237,     5,   237,   143,
     144,   145,   146,   147,   148,   149,   169,   237,   237,   237,
     173,   174,   175,   176,   237,     7,   237,     5,   237,   237,
     183,   184,     7,   200,     7,     7,     7,   237,     7,     7,
     237,   237,   237,     7,   237,     7,     7,   237,     7,   237,
     237,   237,   237,   237,   237,   237,   237,   205,   206,     7,
     151,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   240,     6,     3,     6,     6,     3,
       6,     3,     3,     6,   237,     3,     6,     6,     3,   237,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   237,     6,     4,     4,     4,     4,     4,
       3,   177,     6,     3,   237,     6,     8,     4,     4,     4,
       4,     4,     4,   238,     4,     4,     4,     4,   238,     4,
       4,  1068,   240,   238,  1071,     4,   240,  1074,  1071,   238,
    1077,  1074,  1068,   238,  1077,  1082,     4,   240,  1085,  1082,
    1068,  1088,  1082,     4,  1068,   238,   238,  1071,   238,  1077,
    1074,   238,   238,  1077,  1082,  1102,  1068,  1085,  1082,   238,
    1074,  1085,  1068,   238,  1111,  1077,  1113,  1074,  1077,   238,
    1082,  1077,   238,  1085,   238,  1068,  1123,     4,  1102,  1077,
    1123,  1068,   238,  1130,  1077,     4,   240,  1111,  1135,  1113,
    1077,  1068,   238,  1077,  1071,  1082,  1120,  1074,  1085,  1123,
    1077,  1068,  1077,  1068,  1068,  1082,   238,     4,  1085,     4,
    1077,  1135,  1077,  1077,   240,   238,     4,  1082,  1082,  1068,
    1085,  1068,   240,  1135,   240,  1102,  1135,     6,  1077,  1068,
    1077,  1068,     4,  1082,  1111,  1082,  1113,  1135,  1077,  1068,
    1077,  1068,  1135,  1120,  1068,  1082,  1123,  1068,  1077,   240,
    1077,  1135,  1068,  1077,  1068,     8,  1077,  1068,  1135,     8,
    1135,  1077,  1068,  1077,  1068,   240,  1077,  1068,  1135,  1068,
     237,  1077,  1068,  1077,  1068,  1068,  1077,  1068,  1077,  1068,
    1068,  1077,  1068,  1077,  1077,  1068,  1077,     4,  1077,  1077,
    1068,  1077,  1068,  1068,  1077,  1068,  1135,     4,  1068,  1077,
    1068,  1077,  1077,     8,  1077,     3,  1135,  1077,  1135,  1077,
     237,  1135,     8,     7,  1135,     5,     4,     4,     4,  1135,
       4,  1135,     7,     4,  1135,     3,     6,   237,     5,  1135,
       4,  1135,     4,     4,  1135,     4,  1135,     7,   237,   237,
       5,     7,     4,  1282,     3,     6,   237,     4,     4,     4,
       4,   237,     4,     4,   237,   237,   237,   237,     4,   237,
     237,   237,   237,   731,   533,   237,   240,   240,   238,   240,
     237,   237,   237,   237,   237,   746,   238,  1037,   238,   237,
    1327,   237,   237,   237,  1327,   748,   835,  1334,   542,  1067,
    1102,  1334,  1062,  1165,  1334,  1080,  1343,  1088,  1090,  1327,
    1097,   591,  1070,  1327,  1351,  1068,  1334,  1327,  1351,  1073,
    1334,   556,  1079,  1071,   581,  1327,  1135,  1074,  1327,  1343,
     588,  1327,  1334,  1076,  1137,  1087,  1334,  1351,   560,  1327,
     571,  1085,  1115,  1083,  1327,  1393,  1113,  1111,  1419,  1445,
    1327,  1389,  1389,  1327,  1391,  1474,   787,  1334,  1391,  1120,
    1327,   747,  1327,  1422,  1351,   601,  1452,  1334,  1124,    -1,
    1327,    -1,  1327,  1327,    -1,  1389,  1343,  1391,    -1,  1334,
    1334,    -1,  1419,    -1,  1351,   605,  1419,    -1,  1327,    -1,
    1327,  1130,    -1,    -1,    -1,  1334,    -1,  1334,  1327,    -1,
    1327,    -1,    -1,    -1,    -1,  1419,  1443,  1334,  1327,    -1,
    1327,    -1,    -1,  1327,    -1,    -1,  1327,    -1,    -1,    -1,
      -1,  1327,  1389,  1327,  1391,    -1,  1327,    -1,    -1,  1443,
      -1,  1327,    -1,  1327,    -1,    -1,  1327,  1474,  1327,    -1,
      -1,  1327,    -1,  1327,  1327,    -1,  1327,    -1,  1327,  1327,
      -1,  1327,  1419,    -1,  1327,    -1,    -1,    -1,    -1,  1327,
    1474,  1327,  1327,    -1,  1327,    -1,    -1,  1327,    -1,  1327,
      30,    31,    32,    33,    34,    35,  1443,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1474,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,   103,   104,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,   129,
     130,   131,    -1,   133,   134,   135,    -1,    -1,    -1,    -1,
     140,    -1,    -1,    85,    86,    87,    88,    89,    90,    91,
     150,    93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,   123,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   133,   134,   135,    -1,    -1,    -1,    -1,   140,   141,
      -1,    -1,    -1,    -1,    -1,   205,   206,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   205,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   237
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,     0,     5,
       7,     9,   237,   238,   239,   240,   256,   257,   258,   263,
       7,   272,     7,   277,     7,   335,     7,   452,     7,   539,
       7,   556,     7,   488,     7,   494,     7,   518,     7,   428,
       7,   668,     7,   687,   264,   259,   273,   278,   336,   453,
     540,   557,   489,   495,   519,   429,   669,   688,   256,   265,
     266,   237,   261,   262,    10,   274,   276,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,   102,
     103,   114,   115,   116,   121,   124,   125,   129,   130,   131,
     132,   133,   142,   152,   155,   162,   163,   167,   168,   186,
     190,   205,   206,   207,   208,   209,   210,   219,   237,   271,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   294,   295,   297,   298,   299,   300,
     301,   302,   303,   306,   308,   310,   311,   312,   315,   316,
     317,   318,   319,   321,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   349,   351,   359,   361,   406,   415,   422,
     436,   446,   474,   475,   476,   478,   486,   512,   546,   548,
     550,   561,   563,   565,   588,   603,   604,   606,   656,   666,
     685,   694,   718,    15,    16,    19,    22,    23,    24,    25,
     271,   333,   334,   337,   339,   342,   345,   346,   347,   348,
     546,   548,    99,   100,   101,   122,   126,   127,   128,   133,
     134,   135,   140,   150,   271,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   295,   298,   299,   300,   301,
     302,   303,   306,   308,   310,   311,   312,   315,   316,   317,
     318,   319,   321,   323,   329,   454,   455,   456,   458,   460,
     462,   464,   466,   468,   470,   472,   474,   475,   476,   477,
     512,   533,   546,   548,   550,   561,   563,   565,   583,   123,
     141,   271,   300,   301,   302,   303,   306,   308,   310,   312,
     315,   316,   317,   318,   319,   321,   466,   468,   470,   472,
     512,   541,   542,   543,   545,   546,   548,   133,   143,   144,
     145,   146,   147,   148,   149,   271,   512,   546,   548,   558,
     559,   560,   561,   563,   565,   567,   569,   571,   573,   575,
     577,   579,   581,   486,    40,   104,   106,   107,   111,   112,
     113,   271,   378,   496,   497,   498,   499,   500,   501,   502,
     504,   506,   508,   509,   511,   546,   548,   105,   108,   109,
     110,   133,   271,   378,   500,   506,   520,   521,   522,   523,
     524,   526,   527,   528,   529,   530,   531,   546,   548,   153,
     154,   271,   430,   431,   432,   434,   191,   192,   193,   194,
     195,   196,   197,   198,   271,   546,   548,   670,   671,   672,
     673,   675,   676,   678,   679,   680,   683,    12,    13,   689,
     690,   691,   693,     6,     3,     4,     8,     3,   275,     3,
       8,   686,   332,   352,     4,     4,     4,   562,   564,   566,
       4,     4,   350,   360,   362,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   293,     4,     4,     4,
       4,     4,   304,   307,   309,     4,     4,     4,     4,     4,
       4,     4,   447,   487,   513,     4,   296,   313,   479,   547,
     549,     4,     4,     4,   407,   589,   551,   423,   437,     4,
     416,   605,   607,   657,   667,   320,   322,     4,     4,     4,
     695,   719,     4,     3,     8,   338,   340,   343,     4,     4,
       4,     4,     3,     8,   459,   461,   463,   534,   457,   465,
       4,   469,   471,   473,   467,   584,     3,     8,   544,     4,
       3,     8,   582,   568,   570,   572,   576,   574,   580,   578,
       8,     3,     8,   503,   379,     4,   507,   505,   510,     4,
       8,     3,   525,     4,     4,     4,   532,     8,     3,   433,
     435,     3,     8,     4,   674,     4,   677,     4,     4,   681,
     684,     3,     8,   692,     4,     3,     8,   256,   256,   237,
       4,     4,     4,     4,   240,   240,   240,     4,     4,     4,
     238,   240,     4,     4,     4,   238,   238,   238,   238,   238,
     240,   239,   239,   239,   238,   238,     4,   238,   238,   240,
     240,   240,     4,     4,     4,   240,   240,   239,   238,   238,
     238,   240,     4,     4,     4,   238,     4,     4,     4,     4,
       4,   240,   240,   240,     4,     4,     4,     4,     4,   238,
       4,     4,     4,     4,     4,     4,     4,   240,   240,   240,
       4,     4,   280,     4,     4,     4,   240,   240,   238,   238,
     334,     4,     4,     4,     4,     4,     4,   238,     4,     4,
       4,     4,     4,   455,     4,   238,   542,     4,     4,     4,
       4,     4,     4,     4,     4,   560,     4,     4,   238,     4,
       4,     4,   240,   498,     4,   240,   240,   240,     4,   522,
       4,     4,   431,   240,     4,   238,     4,   238,   238,     4,
       4,   671,     4,   238,   690,     4,     7,     7,     7,     7,
     237,   237,   237,     7,     7,     5,   237,   201,   202,   203,
     204,   240,   305,   237,   237,     5,     5,     5,   237,   117,
     118,   119,   120,   314,     5,   258,   260,   237,     5,     5,
       5,     5,     7,     7,     7,     5,     7,     7,   237,   237,
       5,     7,     5,   267,    17,    18,   341,    20,    21,   344,
     237,   237,   237,     5,   237,   237,   267,   267,   267,   237,
       7,   237,   267,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   267,   237,   260,   237,
     237,    18,   199,   682,   200,     5,   256,   279,   689,   333,
      27,    28,   353,   354,   355,   357,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,   271,   367,   368,   369,   371,   373,
     375,   377,   378,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   392,   393,   394,   396,   398,   400,   402,
     404,   367,     7,   363,   364,   365,     7,   448,   449,   450,
       7,   490,   491,   492,     7,   514,   515,   516,     7,   480,
     481,   482,   144,   145,   146,   147,   149,   408,   409,   410,
     411,   412,   413,   414,     7,   590,   591,     7,   552,   553,
     554,     7,   424,   425,   426,   156,   157,   158,   159,   160,
     161,   438,   439,   440,   441,   442,   443,   444,   445,   164,
     165,   166,   271,   417,   418,   419,   420,   421,   546,   548,
     169,   173,   174,   175,   176,   183,   184,   271,   394,   396,
     398,   546,   548,   612,   613,   614,   617,   619,   621,   622,
     623,   633,     7,   608,   609,   610,   187,   188,   189,   237,
     546,   548,   658,   659,   660,   661,   663,   664,   670,     7,
     696,   697,   220,   221,   222,   223,   271,   720,   721,   722,
     723,   724,   725,   268,     7,   535,   536,   537,   151,   585,
     586,   363,     8,     8,     8,   356,   358,     3,     8,   370,
     372,   374,   376,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   390,     4,     4,   395,   397,   399,   401,
     403,   405,     3,     8,     8,   366,     6,     3,   451,     6,
       3,   493,     6,     3,   517,     6,     3,   483,     6,     3,
       3,     6,   592,     3,     6,   555,     6,     3,   427,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,     4,
       4,     4,     3,     8,   615,   618,   620,     4,   634,     4,
     624,     3,     8,   611,     6,     3,     4,   662,     4,   665,
       3,     8,     8,   698,     3,     6,     4,     4,     4,     4,
       3,     8,   237,   269,   270,   538,     6,     3,   587,     8,
       6,     4,     4,   354,     4,     4,     4,     4,   238,   240,
     238,   240,   238,   238,   238,   238,   238,   238,     4,   240,
     238,     4,     4,     4,     4,     4,     4,   368,   367,   365,
     454,   450,   496,   492,   520,   516,   271,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   295,   298,   299,
     300,   301,   302,   303,   306,   308,   310,   311,   312,   315,
     316,   317,   318,   319,   321,   323,   329,   378,   446,   464,
     466,   468,   470,   472,   474,   475,   476,   484,   485,   512,
     546,   548,   561,   563,   565,   583,   482,   409,   136,   137,
     138,   139,   271,   281,   282,   283,   329,   378,   486,   512,
     546,   548,   561,   563,   565,   593,   594,   595,   596,   597,
     599,   601,   602,   591,   558,   554,   430,   426,   238,   238,
     238,   238,   238,   238,   439,   240,   238,   238,   418,     4,
       4,     4,   238,     4,   240,     4,   613,   612,   610,   240,
       4,   238,     4,   659,   211,   213,   214,   271,   378,   546,
     548,   699,   700,   701,   702,   704,   697,   240,   240,   240,
     240,   721,     6,     3,   541,   537,     4,   237,   237,   237,
     237,   237,   237,    55,    56,    57,   391,   237,   237,   237,
     237,   402,   237,     8,     8,     8,     8,     3,     8,   598,
     600,     4,     4,     8,     3,     8,     8,   170,   171,   172,
     616,   237,   237,     7,     5,     8,   237,   256,   705,     4,
     703,     3,     8,   237,     8,   267,   485,     4,     4,   240,
     240,   595,    40,   178,   179,   180,   271,   546,   548,   635,
     636,   637,   640,   642,   644,     7,   625,   626,   627,     4,
     238,     4,   700,   237,   237,   638,   641,   643,   645,     3,
       8,   628,     6,     3,     5,   237,     4,     4,     4,     4,
     636,   185,   271,   378,   546,   548,   629,   630,   631,   627,
       7,   706,   707,   177,   639,   237,   237,     5,   632,     3,
       8,   708,     3,     6,     7,   646,   647,   648,     4,   630,
     212,   215,   216,   217,   218,   709,   710,   711,   713,   714,
     715,   716,   707,   649,     6,     3,   237,   712,     4,     4,
       4,   717,     3,     8,   181,   182,   271,   371,   373,   546,
     548,   650,   651,   652,   654,   648,     4,   240,   238,   238,
       4,   710,   653,   655,     3,     8,   237,   237,     4,     4,
     651,   237,   237
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
     280,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   293,   292,   294,   296,   295,   297,   298,
     299,   300,   301,   302,   304,   303,   305,   305,   305,   305,
     305,   307,   306,   309,   308,   310,   311,   313,   312,   314,
     314,   314,   314,   315,   316,   317,   318,   320,   319,   322,
     321,   323,   324,   325,   326,   327,   328,   329,   330,   332,
     331,   333,   333,   333,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   336,   335,   338,   337,   340,   339,
     341,   341,   343,   342,   344,   344,   345,   346,   347,   348,
     350,   349,   352,   351,   353,   353,   353,   354,   354,   356,
     355,   358,   357,   360,   359,   362,   361,   363,   363,   364,
     364,   364,   366,   365,   367,   367,   367,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   370,   369,   372,   371,   374,   373,   376,   375,
     377,   379,   378,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   390,   389,   391,   391,   391,   392,   393,   395,
     394,   397,   396,   399,   398,   401,   400,   403,   402,   402,
     402,   402,   402,   402,   405,   404,   407,   406,   408,   408,
     408,   409,   409,   409,   409,   409,   410,   411,   412,   413,
     414,   416,   415,   417,   417,   417,   418,   418,   418,   418,
     418,   418,   419,   420,   421,   423,   422,   424,   424,   425,
     425,   425,   427,   426,   429,   428,   430,   430,   430,   430,
     431,   431,   433,   432,   435,   434,   437,   436,   438,   438,
     438,   439,   439,   439,   439,   439,   439,   440,   441,   442,
     443,   444,   445,   447,   446,   448,   448,   449,   449,   449,
     451,   450,   453,   452,   454,   454,   454,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     457,   456,   459,   458,   461,   460,   463,   462,   465,   464,
     467,   466,   469,   468,   471,   470,   473,   472,   474,   475,
     476,   477,   479,   478,   480,   480,   481,   481,   481,   483,
     482,   484,   484,   484,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   487,   486,   489,   488,   490,   490,   491,   491,
     491,   493,   492,   495,   494,   496,   496,   497,   497,   497,
     498,   498,   498,   498,   498,   498,   498,   498,   498,   498,
     499,   500,   501,   503,   502,   505,   504,   507,   506,   508,
     510,   509,   511,   513,   512,   514,   514,   515,   515,   515,
     517,   516,   519,   518,   520,   520,   521,   521,   521,   522,
     522,   522,   522,   522,   522,   522,   522,   522,   522,   522,
     523,   525,   524,   526,   527,   528,   529,   530,   532,   531,
     534,   533,   535,   535,   536,   536,   536,   538,   537,   540,
     539,   541,   541,   541,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   542,   544,   543,
     545,   547,   546,   549,   548,   551,   550,   552,   552,   553,
     553,   553,   555,   554,   557,   556,   558,   558,   559,   559,
     559,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   562,   561,   564,   563,
     566,   565,   568,   567,   570,   569,   572,   571,   574,   573,
     576,   575,   578,   577,   580,   579,   582,   581,   584,   583,
     585,   587,   586,   589,   588,   590,   590,   590,   592,   591,
     593,   593,   594,   594,   594,   595,   595,   595,   595,   595,
     595,   595,   595,   595,   595,   595,   595,   595,   595,   595,
     595,   595,   596,   598,   597,   600,   599,   601,   602,   603,
     605,   604,   607,   606,   608,   608,   609,   609,   609,   611,
     610,   612,   612,   612,   613,   613,   613,   613,   613,   613,
     613,   613,   613,   613,   613,   613,   613,   615,   614,   616,
     616,   616,   618,   617,   620,   619,   621,   622,   624,   623,
     625,   625,   626,   626,   626,   628,   627,   629,   629,   629,
     630,   630,   630,   630,   630,   632,   631,   634,   633,   635,
     635,   635,   636,   636,   636,   636,   636,   636,   636,   638,
     637,   639,   641,   640,   643,   642,   645,   644,   646,   646,
     647,   647,   647,   649,   648,   650,   650,   650,   651,   651,
     651,   651,   651,   651,   651,   653,   652,   655,   654,   657,
     656,   658,   658,   658,   659,   659,   659,   659,   659,   659,
     660,   662,   661,   663,   665,   664,   667,   666,   669,   668,
     670,   670,   670,   671,   671,   671,   671,   671,   671,   671,
     671,   671,   671,   671,   672,   674,   673,   675,   677,   676,
     678,   679,   681,   680,   682,   682,   684,   683,   686,   685,
     688,   687,   689,   689,   689,   690,   690,   692,   691,   693,
     695,   694,   696,   696,   696,   698,   697,   699,   699,   699,
     700,   700,   700,   700,   700,   700,   700,   701,   703,   702,
     705,   704,   706,   706,   706,   708,   707,   709,   709,   709,
     710,   710,   710,   710,   710,   712,   711,   713,   714,   715,
     717,   716,   719,   718,   720,   720,   720,   721,   721,   721,
     721,   721,   722,   723,   724,   725
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
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
       1,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
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
  "\"cert-file\"", "\"key-file\"", "\"key-password\"", "\"ssl-mode\"",
  "\"disable\"", "\"prefer\"", "\"require\"", "\"verify-ca\"",
  "\"verify-full\"", "\"cipher-list\"", "\"valid-lifetime\"",
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
  "$@46", "cert_file", "$@47", "key_file", "$@48", "key_password", "$@49",
  "ssl_mode", "$@50", "cipher_list", "$@51",
  "host_reservation_identifiers", "$@52",
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
  "$@109", "client_classes_list", "client_class_entry", "$@110",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@111",
  "client_class_template_test", "$@112", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_socket", "$@113",
  "control_sockets", "$@114", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@115",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@116", "control_socket_type_value", "control_socket_name", "$@117",
  "control_socket_address", "$@118", "control_socket_port",
  "cert_required", "http_headers", "$@119", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@120",
  "http_header_params", "http_header_param", "header_value", "$@121",
  "authentication", "$@122", "auth_params", "auth_param", "auth_type",
  "$@123", "auth_type_value", "realm", "$@124", "directory", "$@125",
  "clients", "$@126", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@127", "clients_params", "clients_param", "user_file",
  "$@128", "password_file", "$@129", "dhcp_queue_control", "$@130",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@131", "capacity", "arbitrary_map_entry", "$@132",
  "dhcp_ddns", "$@133", "sub_dhcp_ddns", "$@134", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@135", "server_port",
  "sender_ip", "$@136", "sender_port", "max_queue_size", "ncr_protocol",
  "$@137", "ncr_protocol_value", "ncr_format", "$@138", "config_control",
  "$@139", "sub_config_control", "$@140", "config_control_params",
  "config_control_param", "config_databases", "$@141",
  "config_fetch_wait_time", "loggers", "$@142", "loggers_entries",
  "logger_entry", "$@143", "logger_params", "logger_param", "debuglevel",
  "severity", "$@144", "output_options_list", "$@145",
  "output_options_list_content", "output_entry", "$@146",
  "output_params_list", "output_params", "output", "$@147", "flush",
  "maxsize", "maxver", "pattern", "$@148", "compatibility", "$@149",
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
     594,   595,   598,   604,   610,   616,   622,   628,   634,   640,
     646,   652,   658,   664,   664,   673,   679,   679,   688,   694,
     700,   706,   712,   718,   724,   724,   733,   736,   739,   742,
     745,   751,   751,   760,   760,   769,   778,   788,   788,   797,
     800,   803,   806,   811,   817,   823,   829,   835,   835,   844,
     844,   853,   859,   865,   871,   877,   883,   889,   895,   901,
     901,   913,   914,   915,   920,   921,   922,   923,   924,   925,
     926,   927,   928,   929,   932,   932,   941,   941,   952,   952,
     960,   961,   964,   964,   972,   974,   978,   984,   990,   996,
    1002,  1002,  1015,  1015,  1026,  1027,  1028,  1033,  1034,  1037,
    1037,  1056,  1056,  1074,  1074,  1087,  1087,  1098,  1099,  1102,
    1103,  1104,  1109,  1109,  1119,  1120,  1121,  1126,  1127,  1128,
    1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,
    1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1150,  1153,  1153,  1162,  1162,  1171,  1171,  1180,  1180,
    1189,  1195,  1195,  1204,  1210,  1216,  1222,  1228,  1234,  1240,
    1246,  1252,  1258,  1258,  1266,  1267,  1268,  1271,  1277,  1283,
    1283,  1292,  1292,  1301,  1301,  1310,  1310,  1319,  1319,  1327,
    1328,  1329,  1330,  1331,  1334,  1334,  1343,  1343,  1354,  1355,
    1356,  1361,  1362,  1363,  1364,  1365,  1368,  1373,  1378,  1383,
    1388,  1395,  1395,  1408,  1409,  1410,  1415,  1416,  1417,  1418,
    1419,  1420,  1423,  1429,  1435,  1441,  1441,  1452,  1453,  1456,
    1457,  1458,  1463,  1463,  1473,  1473,  1483,  1484,  1485,  1488,
    1491,  1492,  1495,  1495,  1504,  1504,  1513,  1513,  1525,  1526,
    1527,  1532,  1533,  1534,  1535,  1536,  1537,  1540,  1546,  1552,
    1558,  1564,  1570,  1579,  1579,  1593,  1594,  1597,  1598,  1599,
    1608,  1608,  1634,  1634,  1645,  1646,  1647,  1653,  1654,  1655,
    1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,  1664,  1665,
    1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,  1674,  1675,
    1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,
    1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,
    1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,
    1708,  1708,  1717,  1717,  1726,  1726,  1735,  1735,  1744,  1744,
    1753,  1753,  1763,  1763,  1775,  1775,  1786,  1786,  1797,  1803,
    1809,  1815,  1823,  1823,  1835,  1836,  1840,  1841,  1842,  1847,
    1847,  1855,  1856,  1857,  1862,  1863,  1864,  1865,  1866,  1867,
    1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,
    1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,
    1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,
    1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,
    1908,  1909,  1916,  1916,  1930,  1930,  1939,  1940,  1943,  1944,
    1945,  1952,  1952,  1967,  1967,  1981,  1982,  1985,  1986,  1987,
    1992,  1993,  1994,  1995,  1996,  1997,  1998,  1999,  2000,  2001,
    2004,  2006,  2012,  2014,  2014,  2023,  2023,  2032,  2032,  2041,
    2043,  2043,  2052,  2062,  2062,  2075,  2076,  2081,  2082,  2083,
    2090,  2090,  2102,  2102,  2114,  2115,  2120,  2121,  2122,  2129,
    2130,  2131,  2132,  2133,  2134,  2135,  2136,  2137,  2138,  2139,
    2142,  2144,  2144,  2153,  2155,  2157,  2163,  2169,  2175,  2175,
    2189,  2189,  2202,  2203,  2206,  2207,  2208,  2213,  2213,  2223,
    2223,  2233,  2234,  2235,  2240,  2241,  2242,  2243,  2244,  2245,
    2246,  2247,  2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,
    2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,  2266,  2266,
    2275,  2281,  2281,  2306,  2306,  2336,  2336,  2347,  2348,  2351,
    2352,  2353,  2358,  2358,  2367,  2367,  2376,  2377,  2380,  2381,
    2382,  2388,  2389,  2390,  2391,  2392,  2393,  2394,  2395,  2396,
    2397,  2398,  2399,  2400,  2401,  2402,  2405,  2405,  2414,  2414,
    2423,  2423,  2432,  2432,  2441,  2441,  2450,  2450,  2459,  2459,
    2468,  2468,  2477,  2477,  2486,  2486,  2495,  2495,  2509,  2509,
    2520,  2523,  2523,  2537,  2537,  2548,  2549,  2550,  2555,  2555,
    2565,  2566,  2569,  2570,  2571,  2576,  2577,  2578,  2579,  2580,
    2581,  2582,  2583,  2584,  2585,  2586,  2587,  2588,  2589,  2590,
    2591,  2592,  2595,  2597,  2597,  2606,  2606,  2616,  2622,  2630,
    2638,  2638,  2650,  2650,  2662,  2663,  2666,  2667,  2668,  2673,
    2673,  2681,  2682,  2683,  2688,  2689,  2690,  2691,  2692,  2693,
    2694,  2695,  2696,  2697,  2698,  2699,  2700,  2703,  2703,  2712,
    2713,  2714,  2717,  2717,  2727,  2727,  2737,  2743,  2749,  2749,
    2760,  2761,  2764,  2765,  2766,  2771,  2771,  2779,  2780,  2781,
    2786,  2787,  2788,  2789,  2790,  2793,  2793,  2804,  2804,  2817,
    2818,  2819,  2824,  2825,  2826,  2827,  2828,  2829,  2830,  2833,
    2833,  2841,  2844,  2844,  2853,  2853,  2862,  2862,  2873,  2874,
    2877,  2878,  2879,  2884,  2884,  2892,  2893,  2894,  2899,  2900,
    2901,  2902,  2903,  2904,  2905,  2908,  2908,  2917,  2917,  2928,
    2928,  2941,  2942,  2943,  2948,  2949,  2950,  2951,  2952,  2953,
    2956,  2962,  2962,  2971,  2977,  2977,  2987,  2987,  3000,  3000,
    3010,  3011,  3012,  3017,  3018,  3019,  3020,  3021,  3022,  3023,
    3024,  3025,  3026,  3027,  3030,  3036,  3036,  3045,  3051,  3051,
    3060,  3066,  3072,  3072,  3081,  3082,  3085,  3085,  3096,  3096,
    3108,  3108,  3118,  3119,  3120,  3126,  3127,  3130,  3130,  3141,
    3149,  3149,  3162,  3163,  3164,  3170,  3170,  3178,  3179,  3180,
    3185,  3186,  3187,  3188,  3189,  3190,  3191,  3194,  3200,  3200,
    3209,  3209,  3220,  3221,  3222,  3227,  3227,  3235,  3236,  3237,
    3242,  3243,  3244,  3245,  3246,  3249,  3249,  3258,  3264,  3270,
    3276,  3276,  3285,  3285,  3296,  3297,  3298,  3303,  3304,  3305,
    3306,  3307,  3310,  3316,  3322,  3328
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
#line 7017 "dhcp4_parser.cc"

#line 3334 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
