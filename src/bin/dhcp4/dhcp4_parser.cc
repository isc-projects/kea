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

  case 188: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
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

  case 284: // $@40: %empty
#line 1160 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 285: // database_type: "type" $@40 ":" "constant string"
#line 1163 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2087 "dhcp4_parser.cc"
    break;

  case 286: // $@41: %empty
#line 1169 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp4_parser.cc"
    break;

  case 287: // user: "user" $@41 ":" "constant string"
#line 1172 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2106 "dhcp4_parser.cc"
    break;

  case 288: // $@42: %empty
#line 1178 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp4_parser.cc"
    break;

  case 289: // password: "password" $@42 ":" "constant string"
#line 1181 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 290: // $@43: %empty
#line 1187 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 291: // password_file: "password-file" $@43 ":" "constant string"
#line 1190 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 292: // $@44: %empty
#line 1196 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2153 "dhcp4_parser.cc"
    break;

  case 293: // host: "host" $@44 ":" "constant string"
#line 1199 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2163 "dhcp4_parser.cc"
    break;

  case 294: // port: "port" ":" "integer"
#line 1205 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 295: // $@45: %empty
#line 1211 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 296: // name: "name" $@45 ":" "constant string"
#line 1214 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 297: // persist: "persist" ":" "boolean"
#line 1220 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 298: // lfc_interval: "lfc-interval" ":" "integer"
#line 1226 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 299: // readonly: "readonly" ":" "boolean"
#line 1232 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 300: // connect_timeout: "connect-timeout" ":" "integer"
#line 1238 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 301: // read_timeout: "read-timeout" ":" "integer"
#line 1244 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 302: // write_timeout: "write-timeout" ":" "integer"
#line 1250 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2252 "dhcp4_parser.cc"
    break;

  case 303: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1256 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2262 "dhcp4_parser.cc"
    break;

  case 304: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1262 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 305: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1268 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2282 "dhcp4_parser.cc"
    break;

  case 306: // $@46: %empty
#line 1274 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 307: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1277 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 308: // on_fail_mode: "stop-retry-exit"
#line 1282 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2306 "dhcp4_parser.cc"
    break;

  case 309: // on_fail_mode: "serve-retry-exit"
#line 1283 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2312 "dhcp4_parser.cc"
    break;

  case 310: // on_fail_mode: "serve-retry-continue"
#line 1284 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2318 "dhcp4_parser.cc"
    break;

  case 311: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1287 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 312: // max_row_errors: "max-row-errors" ":" "integer"
#line 1293 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2338 "dhcp4_parser.cc"
    break;

  case 313: // $@47: %empty
#line 1299 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 314: // trust_anchor: "trust-anchor" $@47 ":" "constant string"
#line 1302 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 315: // $@48: %empty
#line 1308 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 316: // cert_file: "cert-file" $@48 ":" "constant string"
#line 1311 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 317: // $@49: %empty
#line 1317 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 318: // key_file: "key-file" $@49 ":" "constant string"
#line 1320 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 319: // $@50: %empty
#line 1326 "dhcp4_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2404 "dhcp4_parser.cc"
    break;

  case 320: // ssl_mode: "ssl-mode" $@50 ":" ssl_mode
#line 1329 "dhcp4_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2413 "dhcp4_parser.cc"
    break;

  case 321: // ssl_mode: "disable"
#line 1334 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2421 "dhcp4_parser.cc"
    break;

  case 322: // ssl_mode: "prefer"
#line 1337 "dhcp4_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2429 "dhcp4_parser.cc"
    break;

  case 323: // ssl_mode: "require"
#line 1340 "dhcp4_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2437 "dhcp4_parser.cc"
    break;

  case 324: // ssl_mode: "verify-ca"
#line 1343 "dhcp4_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2445 "dhcp4_parser.cc"
    break;

  case 325: // ssl_mode: "verify-full"
#line 1346 "dhcp4_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2453 "dhcp4_parser.cc"
    break;

  case 326: // $@51: %empty
#line 1351 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2462 "dhcp4_parser.cc"
    break;

  case 327: // cipher_list: "cipher-list" $@51 ":" "constant string"
#line 1354 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 328: // $@52: %empty
#line 1360 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2484 "dhcp4_parser.cc"
    break;

  case 329: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1366 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2493 "dhcp4_parser.cc"
    break;

  case 332: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1373 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2501 "dhcp4_parser.cc"
    break;

  case 338: // duid_id: "duid"
#line 1385 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 339: // hw_address_id: "hw-address"
#line 1390 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 340: // circuit_id: "circuit-id"
#line 1395 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 341: // client_id: "client-id"
#line 1400 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2537 "dhcp4_parser.cc"
    break;

  case 342: // flex_id: "flex-id"
#line 1405 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2546 "dhcp4_parser.cc"
    break;

  case 343: // $@53: %empty
#line 1412 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 344: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1418 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 347: // multi_threading_params: multi_threading_params ","
#line 1427 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2577 "dhcp4_parser.cc"
    break;

  case 354: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1440 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 355: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1446 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 356: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1452 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2607 "dhcp4_parser.cc"
    break;

  case 357: // $@54: %empty
#line 1458 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2619 "dhcp4_parser.cc"
    break;

  case 358: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1464 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2628 "dhcp4_parser.cc"
    break;

  case 363: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1475 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2636 "dhcp4_parser.cc"
    break;

  case 364: // $@55: %empty
#line 1480 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2646 "dhcp4_parser.cc"
    break;

  case 365: // hooks_library: "{" $@55 hooks_params "}"
#line 1484 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2656 "dhcp4_parser.cc"
    break;

  case 366: // $@56: %empty
#line 1490 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2666 "dhcp4_parser.cc"
    break;

  case 367: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1494 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2676 "dhcp4_parser.cc"
    break;

  case 370: // hooks_params: hooks_params ","
#line 1502 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2684 "dhcp4_parser.cc"
    break;

  case 374: // $@57: %empty
#line 1512 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 375: // library: "library" $@57 ":" "constant string"
#line 1515 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2703 "dhcp4_parser.cc"
    break;

  case 376: // $@58: %empty
#line 1521 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 377: // parameters: "parameters" $@58 ":" map_value
#line 1524 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 378: // $@59: %empty
#line 1530 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2733 "dhcp4_parser.cc"
    break;

  case 379: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1536 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2743 "dhcp4_parser.cc"
    break;

  case 382: // expired_leases_params: expired_leases_params ","
#line 1544 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2751 "dhcp4_parser.cc"
    break;

  case 389: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1557 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2761 "dhcp4_parser.cc"
    break;

  case 390: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1563 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 391: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1569 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 392: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1575 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 393: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1581 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 394: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1587 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 395: // $@60: %empty
#line 1596 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 396: // subnet4_list: "subnet4" $@60 ":" "[" subnet4_list_content "]"
#line 1602 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2832 "dhcp4_parser.cc"
    break;

  case 401: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1616 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2840 "dhcp4_parser.cc"
    break;

  case 402: // $@61: %empty
#line 1625 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2850 "dhcp4_parser.cc"
    break;

  case 403: // subnet4: "{" $@61 subnet4_params "}"
#line 1629 "dhcp4_parser.yy"
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

  case 404: // $@62: %empty
#line 1651 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2886 "dhcp4_parser.cc"
    break;

  case 405: // sub_subnet4: "{" $@62 subnet4_params "}"
#line 1655 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2896 "dhcp4_parser.cc"
    break;

  case 408: // subnet4_params: subnet4_params ","
#line 1664 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2904 "dhcp4_parser.cc"
    break;

  case 463: // $@63: %empty
#line 1726 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2913 "dhcp4_parser.cc"
    break;

  case 464: // subnet: "subnet" $@63 ":" "constant string"
#line 1729 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 465: // $@64: %empty
#line 1735 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 466: // subnet_4o6_interface: "4o6-interface" $@64 ":" "constant string"
#line 1738 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 467: // $@65: %empty
#line 1744 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 468: // subnet_4o6_interface_id: "4o6-interface-id" $@65 ":" "constant string"
#line 1747 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 469: // $@66: %empty
#line 1753 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 470: // subnet_4o6_subnet: "4o6-subnet" $@66 ":" "constant string"
#line 1756 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 471: // $@67: %empty
#line 1762 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp4_parser.cc"
    break;

  case 472: // interface: "interface" $@67 ":" "constant string"
#line 1765 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2999 "dhcp4_parser.cc"
    break;

  case 473: // $@68: %empty
#line 1771 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 474: // client_class: "client-class" $@68 ":" "constant string"
#line 1774 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 475: // $@69: %empty
#line 1781 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3030 "dhcp4_parser.cc"
    break;

  case 476: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1787 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3039 "dhcp4_parser.cc"
    break;

  case 477: // $@70: %empty
#line 1793 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3051 "dhcp4_parser.cc"
    break;

  case 478: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1799 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3060 "dhcp4_parser.cc"
    break;

  case 479: // $@71: %empty
#line 1804 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 480: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1810 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 481: // reservations_global: "reservations-global" ":" "boolean"
#line 1815 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 482: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1821 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 483: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1827 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 484: // id: "id" ":" "integer"
#line 1833 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 485: // $@72: %empty
#line 1841 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3133 "dhcp4_parser.cc"
    break;

  case 486: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1847 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 491: // shared_networks_list: shared_networks_list ","
#line 1860 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3150 "dhcp4_parser.cc"
    break;

  case 492: // $@73: %empty
#line 1865 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 493: // shared_network: "{" $@73 shared_network_params "}"
#line 1869 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3168 "dhcp4_parser.cc"
    break;

  case 496: // shared_network_params: shared_network_params ","
#line 1875 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3176 "dhcp4_parser.cc"
    break;

  case 546: // $@74: %empty
#line 1935 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 547: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1941 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 548: // $@75: %empty
#line 1949 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 549: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1952 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 554: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1964 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3222 "dhcp4_parser.cc"
    break;

  case 555: // $@76: %empty
#line 1971 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3232 "dhcp4_parser.cc"
    break;

  case 556: // option_def_entry: "{" $@76 option_def_params "}"
#line 1975 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 557: // $@77: %empty
#line 1986 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 558: // sub_option_def: "{" $@77 option_def_params "}"
#line 1990 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3266 "dhcp4_parser.cc"
    break;

  case 563: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2006 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3274 "dhcp4_parser.cc"
    break;

  case 575: // code: "code" ":" "integer"
#line 2025 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 577: // $@78: %empty
#line 2033 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 578: // option_def_type: "type" $@78 ":" "constant string"
#line 2036 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 579: // $@79: %empty
#line 2042 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 580: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2045 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 581: // $@80: %empty
#line 2051 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp4_parser.cc"
    break;

  case 582: // space: "space" $@80 ":" "constant string"
#line 2054 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 584: // $@81: %empty
#line 2062 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 585: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2065 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3360 "dhcp4_parser.cc"
    break;

  case 586: // option_def_array: "array" ":" "boolean"
#line 2071 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3370 "dhcp4_parser.cc"
    break;

  case 587: // $@82: %empty
#line 2081 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3382 "dhcp4_parser.cc"
    break;

  case 588: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2087 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3391 "dhcp4_parser.cc"
    break;

  case 593: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2102 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3399 "dhcp4_parser.cc"
    break;

  case 594: // $@83: %empty
#line 2109 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3409 "dhcp4_parser.cc"
    break;

  case 595: // option_data_entry: "{" $@83 option_data_params "}"
#line 2113 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 596: // $@84: %empty
#line 2121 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3428 "dhcp4_parser.cc"
    break;

  case 597: // sub_option_data: "{" $@84 option_data_params "}"
#line 2125 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3437 "dhcp4_parser.cc"
    break;

  case 602: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2141 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3445 "dhcp4_parser.cc"
    break;

  case 615: // $@85: %empty
#line 2163 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 616: // option_data_data: "data" $@85 ":" "constant string"
#line 2166 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3464 "dhcp4_parser.cc"
    break;

  case 619: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2176 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3474 "dhcp4_parser.cc"
    break;

  case 620: // option_data_always_send: "always-send" ":" "boolean"
#line 2182 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3484 "dhcp4_parser.cc"
    break;

  case 621: // option_data_never_send: "never-send" ":" "boolean"
#line 2188 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 622: // $@86: %empty
#line 2194 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 623: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2200 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 624: // $@87: %empty
#line 2208 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3527 "dhcp4_parser.cc"
    break;

  case 625: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2214 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3536 "dhcp4_parser.cc"
    break;

  case 630: // not_empty_pools_list: not_empty_pools_list ","
#line 2227 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3544 "dhcp4_parser.cc"
    break;

  case 631: // $@88: %empty
#line 2232 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 632: // pool_list_entry: "{" $@88 pool_params "}"
#line 2236 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 633: // $@89: %empty
#line 2242 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 634: // sub_pool4: "{" $@89 pool_params "}"
#line 2246 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 637: // pool_params: pool_params ","
#line 2254 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3592 "dhcp4_parser.cc"
    break;

  case 662: // $@90: %empty
#line 2285 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 663: // pool_entry: "pool" $@90 ":" "constant string"
#line 2288 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 664: // pool_id: "pool-id" ":" "integer"
#line 2294 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 665: // $@91: %empty
#line 2300 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3629 "dhcp4_parser.cc"
    break;

  case 666: // user_context: "user-context" $@91 ":" map_value
#line 2302 "dhcp4_parser.yy"
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

  case 667: // $@92: %empty
#line 2325 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 668: // comment: "comment" $@92 ":" "constant string"
#line 2327 "dhcp4_parser.yy"
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

  case 669: // $@93: %empty
#line 2355 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3705 "dhcp4_parser.cc"
    break;

  case 670: // reservations: "reservations" $@93 ":" "[" reservations_list "]"
#line 2361 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 675: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2372 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3722 "dhcp4_parser.cc"
    break;

  case 676: // $@94: %empty
#line 2377 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 677: // reservation: "{" $@94 reservation_params "}"
#line 2381 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 678: // $@95: %empty
#line 2386 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 679: // sub_reservation: "{" $@95 reservation_params "}"
#line 2390 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 684: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2401 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3768 "dhcp4_parser.cc"
    break;

  case 700: // $@96: %empty
#line 2424 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 701: // next_server: "next-server" $@96 ":" "constant string"
#line 2427 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3787 "dhcp4_parser.cc"
    break;

  case 702: // $@97: %empty
#line 2433 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 703: // server_hostname: "server-hostname" $@97 ":" "constant string"
#line 2436 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 704: // $@98: %empty
#line 2442 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 705: // boot_file_name: "boot-file-name" $@98 ":" "constant string"
#line 2445 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 706: // $@99: %empty
#line 2451 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 707: // ip_address: "ip-address" $@99 ":" "constant string"
#line 2454 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 708: // $@100: %empty
#line 2460 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 709: // duid: "duid" $@100 ":" "constant string"
#line 2463 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 710: // $@101: %empty
#line 2469 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 711: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2472 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 712: // $@102: %empty
#line 2478 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 713: // client_id_value: "client-id" $@102 ":" "constant string"
#line 2481 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 714: // $@103: %empty
#line 2487 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 715: // circuit_id_value: "circuit-id" $@103 ":" "constant string"
#line 2490 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3920 "dhcp4_parser.cc"
    break;

  case 716: // $@104: %empty
#line 2496 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 717: // flex_id_value: "flex-id" $@104 ":" "constant string"
#line 2499 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3939 "dhcp4_parser.cc"
    break;

  case 718: // $@105: %empty
#line 2505 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3948 "dhcp4_parser.cc"
    break;

  case 719: // hostname: "hostname" $@105 ":" "constant string"
#line 2508 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 720: // $@106: %empty
#line 2514 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3970 "dhcp4_parser.cc"
    break;

  case 721: // reservation_client_classes: "client-classes" $@106 ":" list_strings
#line 2520 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3979 "dhcp4_parser.cc"
    break;

  case 722: // $@107: %empty
#line 2528 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3991 "dhcp4_parser.cc"
    break;

  case 723: // relay: "relay" $@107 ":" "{" relay_map "}"
#line 2534 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4000 "dhcp4_parser.cc"
    break;

  case 725: // $@108: %empty
#line 2542 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4012 "dhcp4_parser.cc"
    break;

  case 726: // ip_addresses: "ip-addresses" $@108 ":" list_strings
#line 2548 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 727: // $@109: %empty
#line 2556 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4033 "dhcp4_parser.cc"
    break;

  case 728: // client_classes: "client-classes" $@109 ":" "[" client_classes_list "]"
#line 2562 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 733: // not_empty_classes_list: not_empty_classes_list ","
#line 2573 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4050 "dhcp4_parser.cc"
    break;

  case 734: // $@110: %empty
#line 2578 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4060 "dhcp4_parser.cc"
    break;

  case 735: // client_class_entry: "{" $@110 client_class_params "}"
#line 2582 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4070 "dhcp4_parser.cc"
    break;

  case 740: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2594 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4078 "dhcp4_parser.cc"
    break;

  case 759: // $@111: %empty
#line 2620 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 760: // client_class_test: "test" $@111 ":" "constant string"
#line 2623 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 761: // $@112: %empty
#line 2629 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4106 "dhcp4_parser.cc"
    break;

  case 762: // client_class_template_test: "template-test" $@112 ":" "constant string"
#line 2632 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4116 "dhcp4_parser.cc"
    break;

  case 763: // only_if_required: "only-if-required" ":" "boolean"
#line 2639 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4126 "dhcp4_parser.cc"
    break;

  case 764: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2645 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4136 "dhcp4_parser.cc"
    break;

  case 765: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2653 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4146 "dhcp4_parser.cc"
    break;

  case 766: // $@113: %empty
#line 2661 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4159 "dhcp4_parser.cc"
    break;

  case 767: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2668 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 768: // $@114: %empty
#line 2673 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4181 "dhcp4_parser.cc"
    break;

  case 769: // control_sockets: "control-sockets" $@114 ":" "[" control_socket_list "]"
#line 2680 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4190 "dhcp4_parser.cc"
    break;

  case 774: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2691 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4198 "dhcp4_parser.cc"
    break;

  case 775: // $@115: %empty
#line 2696 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4208 "dhcp4_parser.cc"
    break;

  case 776: // control_socket_entry: "{" $@115 control_socket_params "}"
#line 2700 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4216 "dhcp4_parser.cc"
    break;

  case 779: // control_socket_params: control_socket_params ","
#line 2706 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4224 "dhcp4_parser.cc"
    break;

  case 793: // $@116: %empty
#line 2726 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4233 "dhcp4_parser.cc"
    break;

  case 794: // control_socket_type: "socket-type" $@116 ":" control_socket_type_value
#line 2729 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4242 "dhcp4_parser.cc"
    break;

  case 795: // control_socket_type_value: "unix"
#line 2735 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4248 "dhcp4_parser.cc"
    break;

  case 796: // control_socket_type_value: "http"
#line 2736 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4254 "dhcp4_parser.cc"
    break;

  case 797: // control_socket_type_value: "https"
#line 2737 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4260 "dhcp4_parser.cc"
    break;

  case 798: // $@117: %empty
#line 2740 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4269 "dhcp4_parser.cc"
    break;

  case 799: // control_socket_name: "socket-name" $@117 ":" "constant string"
#line 2743 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4279 "dhcp4_parser.cc"
    break;

  case 800: // $@118: %empty
#line 2749 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4288 "dhcp4_parser.cc"
    break;

  case 801: // control_socket_address: "socket-address" $@118 ":" "constant string"
#line 2752 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4298 "dhcp4_parser.cc"
    break;

  case 802: // control_socket_port: "socket-port" ":" "integer"
#line 2758 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4308 "dhcp4_parser.cc"
    break;

  case 803: // cert_required: "cert-required" ":" "boolean"
#line 2764 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4318 "dhcp4_parser.cc"
    break;

  case 804: // $@119: %empty
#line 2770 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4330 "dhcp4_parser.cc"
    break;

  case 805: // http_headers: "http-headers" $@119 ":" "[" http_header_list "]"
#line 2776 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4339 "dhcp4_parser.cc"
    break;

  case 810: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2787 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4347 "dhcp4_parser.cc"
    break;

  case 811: // $@120: %empty
#line 2792 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4357 "dhcp4_parser.cc"
    break;

  case 812: // http_header: "{" $@120 http_header_params "}"
#line 2796 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4365 "dhcp4_parser.cc"
    break;

  case 815: // http_header_params: http_header_params ","
#line 2802 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4373 "dhcp4_parser.cc"
    break;

  case 821: // $@121: %empty
#line 2814 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4382 "dhcp4_parser.cc"
    break;

  case 822: // header_value: "value" $@121 ":" "constant string"
#line 2817 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4392 "dhcp4_parser.cc"
    break;

  case 823: // $@122: %empty
#line 2825 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4404 "dhcp4_parser.cc"
    break;

  case 824: // authentication: "authentication" $@122 ":" "{" auth_params "}"
#line 2831 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4415 "dhcp4_parser.cc"
    break;

  case 827: // auth_params: auth_params ","
#line 2840 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4423 "dhcp4_parser.cc"
    break;

  case 835: // $@123: %empty
#line 2854 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4432 "dhcp4_parser.cc"
    break;

  case 836: // auth_type: "type" $@123 ":" auth_type_value
#line 2857 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4441 "dhcp4_parser.cc"
    break;

  case 837: // auth_type_value: "basic"
#line 2862 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4447 "dhcp4_parser.cc"
    break;

  case 838: // $@124: %empty
#line 2865 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4456 "dhcp4_parser.cc"
    break;

  case 839: // realm: "realm" $@124 ":" "constant string"
#line 2868 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4466 "dhcp4_parser.cc"
    break;

  case 840: // $@125: %empty
#line 2874 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4475 "dhcp4_parser.cc"
    break;

  case 841: // directory: "directory" $@125 ":" "constant string"
#line 2877 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4485 "dhcp4_parser.cc"
    break;

  case 842: // $@126: %empty
#line 2883 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4497 "dhcp4_parser.cc"
    break;

  case 843: // clients: "clients" $@126 ":" "[" clients_list "]"
#line 2889 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4506 "dhcp4_parser.cc"
    break;

  case 848: // not_empty_clients_list: not_empty_clients_list ","
#line 2900 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4514 "dhcp4_parser.cc"
    break;

  case 849: // $@127: %empty
#line 2905 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4524 "dhcp4_parser.cc"
    break;

  case 850: // basic_auth: "{" $@127 clients_params "}"
#line 2909 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 853: // clients_params: clients_params ","
#line 2915 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4540 "dhcp4_parser.cc"
    break;

  case 861: // $@128: %empty
#line 2929 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4549 "dhcp4_parser.cc"
    break;

  case 862: // user_file: "user-file" $@128 ":" "constant string"
#line 2932 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 863: // $@129: %empty
#line 2940 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4571 "dhcp4_parser.cc"
    break;

  case 864: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2946 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4582 "dhcp4_parser.cc"
    break;

  case 867: // queue_control_params: queue_control_params ","
#line 2955 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4590 "dhcp4_parser.cc"
    break;

  case 874: // enable_queue: "enable-queue" ":" "boolean"
#line 2968 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4600 "dhcp4_parser.cc"
    break;

  case 875: // $@130: %empty
#line 2974 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4609 "dhcp4_parser.cc"
    break;

  case 876: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2977 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4619 "dhcp4_parser.cc"
    break;

  case 877: // capacity: "capacity" ":" "integer"
#line 2983 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4629 "dhcp4_parser.cc"
    break;

  case 878: // $@131: %empty
#line 2989 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4638 "dhcp4_parser.cc"
    break;

  case 879: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2992 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 880: // $@132: %empty
#line 2999 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4659 "dhcp4_parser.cc"
    break;

  case 881: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 3005 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4670 "dhcp4_parser.cc"
    break;

  case 882: // $@133: %empty
#line 3012 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4680 "dhcp4_parser.cc"
    break;

  case 883: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 3016 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4690 "dhcp4_parser.cc"
    break;

  case 886: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3024 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4698 "dhcp4_parser.cc"
    break;

  case 898: // enable_updates: "enable-updates" ":" "boolean"
#line 3042 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 899: // $@134: %empty
#line 3048 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4717 "dhcp4_parser.cc"
    break;

  case 900: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3051 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4727 "dhcp4_parser.cc"
    break;

  case 901: // server_port: "server-port" ":" "integer"
#line 3057 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4737 "dhcp4_parser.cc"
    break;

  case 902: // $@135: %empty
#line 3063 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4746 "dhcp4_parser.cc"
    break;

  case 903: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3066 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4756 "dhcp4_parser.cc"
    break;

  case 904: // sender_port: "sender-port" ":" "integer"
#line 3072 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4766 "dhcp4_parser.cc"
    break;

  case 905: // max_queue_size: "max-queue-size" ":" "integer"
#line 3078 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4776 "dhcp4_parser.cc"
    break;

  case 906: // $@136: %empty
#line 3084 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4785 "dhcp4_parser.cc"
    break;

  case 907: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3087 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4794 "dhcp4_parser.cc"
    break;

  case 908: // ncr_protocol_value: "udp"
#line 3093 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4800 "dhcp4_parser.cc"
    break;

  case 909: // ncr_protocol_value: "tcp"
#line 3094 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4806 "dhcp4_parser.cc"
    break;

  case 910: // $@137: %empty
#line 3097 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4815 "dhcp4_parser.cc"
    break;

  case 911: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3100 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4825 "dhcp4_parser.cc"
    break;

  case 912: // $@138: %empty
#line 3108 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4837 "dhcp4_parser.cc"
    break;

  case 913: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3114 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4847 "dhcp4_parser.cc"
    break;

  case 914: // $@139: %empty
#line 3120 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4857 "dhcp4_parser.cc"
    break;

  case 915: // sub_config_control: "{" $@139 config_control_params "}"
#line 3124 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4866 "dhcp4_parser.cc"
    break;

  case 918: // config_control_params: config_control_params ","
#line 3132 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4874 "dhcp4_parser.cc"
    break;

  case 921: // $@140: %empty
#line 3142 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4886 "dhcp4_parser.cc"
    break;

  case 922: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3148 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4895 "dhcp4_parser.cc"
    break;

  case 923: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3153 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4905 "dhcp4_parser.cc"
    break;

  case 924: // $@141: %empty
#line 3161 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4917 "dhcp4_parser.cc"
    break;

  case 925: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3167 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4926 "dhcp4_parser.cc"
    break;

  case 928: // loggers_entries: loggers_entries ","
#line 3176 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4934 "dhcp4_parser.cc"
    break;

  case 929: // $@142: %empty
#line 3182 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4944 "dhcp4_parser.cc"
    break;

  case 930: // logger_entry: "{" $@142 logger_params "}"
#line 3186 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4952 "dhcp4_parser.cc"
    break;

  case 933: // logger_params: logger_params ","
#line 3192 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4960 "dhcp4_parser.cc"
    break;

  case 941: // debuglevel: "debuglevel" ":" "integer"
#line 3206 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4970 "dhcp4_parser.cc"
    break;

  case 942: // $@143: %empty
#line 3212 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4979 "dhcp4_parser.cc"
    break;

  case 943: // severity: "severity" $@143 ":" "constant string"
#line 3215 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4989 "dhcp4_parser.cc"
    break;

  case 944: // $@144: %empty
#line 3221 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5001 "dhcp4_parser.cc"
    break;

  case 945: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3227 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5010 "dhcp4_parser.cc"
    break;

  case 948: // output_options_list_content: output_options_list_content ","
#line 3234 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5018 "dhcp4_parser.cc"
    break;

  case 949: // $@145: %empty
#line 3239 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5028 "dhcp4_parser.cc"
    break;

  case 950: // output_entry: "{" $@145 output_params_list "}"
#line 3243 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5036 "dhcp4_parser.cc"
    break;

  case 953: // output_params_list: output_params_list ","
#line 3249 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5044 "dhcp4_parser.cc"
    break;

  case 959: // $@146: %empty
#line 3261 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5053 "dhcp4_parser.cc"
    break;

  case 960: // output: "output" $@146 ":" "constant string"
#line 3264 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5063 "dhcp4_parser.cc"
    break;

  case 961: // flush: "flush" ":" "boolean"
#line 3270 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5073 "dhcp4_parser.cc"
    break;

  case 962: // maxsize: "maxsize" ":" "integer"
#line 3276 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5083 "dhcp4_parser.cc"
    break;

  case 963: // maxver: "maxver" ":" "integer"
#line 3282 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5093 "dhcp4_parser.cc"
    break;

  case 964: // $@147: %empty
#line 3288 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5102 "dhcp4_parser.cc"
    break;

  case 965: // pattern: "pattern" $@147 ":" "constant string"
#line 3291 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5112 "dhcp4_parser.cc"
    break;

  case 966: // $@148: %empty
#line 3297 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5124 "dhcp4_parser.cc"
    break;

  case 967: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3303 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5133 "dhcp4_parser.cc"
    break;

  case 970: // compatibility_params: compatibility_params ","
#line 3310 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5141 "dhcp4_parser.cc"
    break;

  case 976: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3322 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5151 "dhcp4_parser.cc"
    break;

  case 977: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3328 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5161 "dhcp4_parser.cc"
    break;

  case 978: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3334 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5171 "dhcp4_parser.cc"
    break;

  case 979: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3340 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5181 "dhcp4_parser.cc"
    break;


#line 5185 "dhcp4_parser.cc"

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
     256, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,    42,    26,    39,    63,    80,    88,
     117,   140,   219,   251,   302,   317,   318,   324, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,    26,  -176,   131,   205,   180,   727,
     826,   329,    -1,   334,   272,   -85,   800,   118, -1415,   267,
     165,   255,   186,   330, -1415,    45, -1415, -1415, -1415, -1415,
     328,   335,   336, -1415, -1415, -1415,   337,   345, -1415, -1415,
   -1415,   354,   361,   371,   412,   418,   419,   426,   427,   429,
     430,   431,   432, -1415,   433,   435,   439,   440,   444, -1415,
   -1415, -1415,   445,   446,   447,   448,   451,   452,   453, -1415,
   -1415, -1415,   456, -1415, -1415, -1415, -1415, -1415,   457,   459,
     461, -1415, -1415, -1415, -1415, -1415,   462, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   463,   464,   465, -1415, -1415,   467,
   -1415,   111, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   490,   491,
     492,   494, -1415,   124, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     495, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   151, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415,   496, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   161, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,   493,   500, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   497, -1415, -1415,   502,
   -1415, -1415, -1415,   503, -1415, -1415,   505,   507, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   510,   511,   513, -1415, -1415, -1415, -1415, -1415,   515,
     508, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   162, -1415, -1415, -1415,   517,
   -1415,   520, -1415,   522,   526, -1415, -1415, -1415, -1415, -1415,
     169, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   529,   172, -1415, -1415, -1415, -1415,    26,    26, -1415,
     227,   532, -1415, -1415,   533,   535,   536,   304,   305,   310,
     538,   548,   550,   321,   316,   551,   553,   558,   332,   341,
     342,   343,   344,   346,   333,   350,   353,   349,   355,   358,
     570,   359,   360,   362,   364,   366,   579,   595,   596,   367,
     369,   373,   372,   376,   383,   378,   618,   621,   623,   393,
     628,   631,   633,   638,   644,   410,   413,   415,   652,   654,
     659,   662,   665,   438,   673,   674,   675,   676,   677,   678,
     679,   449,   450,   454,   681,   683, -1415,   205, -1415,   684,
     688,   689,   455,   458,   466,   468,   180, -1415,   692,   695,
     696,   697,   698,   699,   469,   701,   704,   706,   707,   708,
     727, -1415,   709,   476,   826, -1415,   711,   712,   713,   714,
     715,   716,   722,   723, -1415,   329, -1415,   724,   726,   498,
     728,   729,   730,   499, -1415,   334,   731,   501,   506,   509,
     733, -1415,   272,   734,   736,    32, -1415,   512,   738,   516,
     739,   525,   527,   746,   747,   800, -1415,   749,   528,   118,
   -1415, -1415, -1415,   751,   757,   760,   762,   763, -1415, -1415,
   -1415,   534,   539,   540, -1415, -1415,   771,   772,   775, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   544, -1415, -1415, -1415, -1415, -1415,   -98,   547,   549,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   780,   782,   783,
   -1415,   552,   309,   785,   786,   559, -1415, -1415, -1415,   803,
     804,   805,   806,   818, -1415,   822,   824,   827,   828,   830,
     597,   601, -1415, -1415, -1415,   834,   833, -1415,   836,   183,
     187, -1415, -1415, -1415, -1415, -1415,   607,   608,   609,   842,
     611,   613, -1415,   836,   836,   836,   622,   856, -1415,   627,
   -1415, -1415,   836,   629,   634,   635,   636,   637,   639,   641,
   -1415,   642,   643, -1415,   660,   661,   686, -1415, -1415,   690,
   -1415, -1415, -1415,   836, -1415,   691,   786, -1415, -1415,   693,
   -1415,   694, -1415, -1415,    10,   531, -1415,   860, -1415, -1415,
      26,   205,   118,   180,   190, -1415, -1415, -1415,   841,   841,
     861, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     863,   868,   889, -1415, -1415, -1415, -1415, -1415, -1415,   911,
   -1415, -1415, -1415,   101,   919,   927,   928,    54,   -75,   599,
     929,   -80,   800, -1415, -1415,   930,   -31, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   931, -1415,
   -1415, -1415, -1415, -1415, -1415,   682, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     861, -1415,   175,   179,   185, -1415, -1415,   224, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   935,   936,   937,   939,   940,
     942,   943,   944,   948,   949, -1415,   950,   951, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     225, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   246, -1415,   952,   953,
   -1415, -1415,   956,   954, -1415, -1415,   957,   962, -1415, -1415,
     963,   965, -1415, -1415,   964,   968, -1415, -1415, -1415, -1415,
   -1415, -1415,    75, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     966,   970, -1415, -1415,   969,   971, -1415, -1415,   972,   973,
   -1415,   975,   976,   977,   978,   979,   980,   252, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   981,   982,   983, -1415,   253,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   984,
   -1415,   985, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   254,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   993,
     974, -1415,   986, -1415,   996, -1415, -1415, -1415,   264, -1415,
   -1415, -1415, -1415, -1415,   266, -1415,   134, -1415,   997,   998,
     999,  1000, -1415,   303, -1415, -1415, -1415, -1415, -1415,   768,
   -1415,  1002,  1003, -1415, -1415,  1001, -1415,  1005, -1415, -1415,
   -1415,  1008,  1011,   190, -1415,  1015,  1018,  1025,  1030,   807,
     798,   811,   815,   820,   854,   855,   857,   862,   864,  1056,
     831,   870,  1064,  1068,  1097,  1106,  1109,  1114,   841, -1415,
   -1415,   841, -1415,   861,   727, -1415,   863,   334, -1415,   868,
     272, -1415,   889,  1424, -1415,   911,   101, -1415,   282, -1415,
     919,   329, -1415,   927,   -85, -1415,   928,   897,   903,   907,
     913,   918,   945,    54, -1415,   933,   958,   961,   -75, -1415,
    1187,  1197,  1198,   987,  1199,   988,  1200,   599, -1415,   599,
   -1415,   929,   989,  1202,   994,  1204,   -80, -1415, -1415,   460,
     930, -1415,   991,   995,  1004,  1006,   -31, -1415, -1415,  1203,
    1208,   826, -1415,   931,  1209, -1415, -1415,   990,  1010, -1415,
    1012,  1013,  1014,  1016, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,    61, -1415, -1415,  1017,  1019,  1020,
     157,  1021,  1022, -1415,   315, -1415,   319, -1415,  1206, -1415,
    1210, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   347, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,  1212,  1215, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,  1213,  1220, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,  1216, -1415,   348, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   230,  1023,  1024, -1415,
    1205, -1415,  1221, -1415,   356, -1415, -1415,  1026, -1415,    26,
   -1415, -1415,  1229, -1415, -1415, -1415, -1415, -1415,   363, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
    1027,   380, -1415,   836, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,  1424, -1415,  1230,  1232,  1028,  1029,
   -1415,   282, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
      73,  1231, -1415, -1415, -1415,  1233,  1007,  1235,   460, -1415,
   -1415, -1415, -1415, -1415,  1033,  1035, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   384, -1415, -1415, -1415,
   -1415, -1415, -1415,  1234,  1238, -1415,  1237, -1415,  1036, -1415,
   -1415, -1415,  1239,  1244,  1248,  1251,    73, -1415,   -70, -1415,
    1231,  1255, -1415,  1088,  1038,  1039,  1261, -1415, -1415, -1415,
   -1415, -1415, -1415,   386, -1415, -1415, -1415, -1415,   387, -1415,
   -1415, -1415, -1415, -1415,  1270,  1275,   -70, -1415,  -119,  1255,
   -1415, -1415,  1274,  1279, -1415,  1047, -1415, -1415,  1281,  1283,
    1284, -1415,   400, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     188, -1415,  1270, -1415,  1285,  1052,  1058,  1060,  1290,  -119,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   401, -1415,
   -1415, -1415,  1062, -1415, -1415, -1415,  1063, -1415,  1297,   188,
   -1415, -1415, -1415,  1066, -1415, -1415
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   216,     9,   404,    11,   633,    13,
     678,    15,   548,    17,   557,    19,   596,    21,   366,    23,
     882,    25,   914,    27,    46,    39,     0,     0,     0,     0,
       0,   680,     0,   559,   598,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   912,   201,   234,
       0,     0,     0,   700,   702,   704,     0,     0,   232,   245,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,     0,   166,
     173,   175,     0,     0,     0,     0,     0,     0,     0,   395,
     546,   587,     0,   158,   179,   485,   665,   667,     0,     0,
       0,   328,   727,   669,   357,   378,     0,   343,   766,   768,
     863,   880,   189,   191,     0,     0,     0,   924,   966,     0,
     142,     0,    67,    70,    71,    72,    73,    74,   108,   109,
     110,   111,   112,   113,    75,   104,   138,   139,    93,    94,
      95,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   115,   116,   130,   131,   132,   134,
     135,   136,   140,   141,    78,    79,   101,    80,    81,    82,
     133,    86,    87,    76,   105,   106,   107,    77,    84,    85,
      99,   100,   102,    96,    97,    98,    83,    88,    89,    90,
      91,    92,   103,   114,   137,   218,   220,   224,     0,     0,
       0,     0,   215,     0,   203,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   465,   467,   469,   624,   463,   471,
       0,   475,   477,   479,   473,   722,   462,   409,   410,   411,
     412,   413,   438,   439,   440,   441,   442,   443,   460,   428,
     429,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   461,     0,   406,
     416,   433,   434,   435,   417,   419,   420,   421,   422,   424,
     425,   426,   418,   414,   415,   436,   437,   423,   430,   431,
     432,   427,   662,     0,   661,   645,   646,   647,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   641,
     642,   643,   644,   640,     0,   635,   638,   639,   659,   660,
     720,   706,   708,   710,   714,   712,   718,   716,   699,   693,
     697,   698,     0,   681,   682,   694,   695,   696,   690,   685,
     691,   687,   688,   689,   692,   686,     0,   577,   295,     0,
     581,   579,   584,     0,   573,   574,     0,   560,   561,   564,
     576,   565,   566,   567,   583,   568,   569,   570,   571,   572,
     615,     0,     0,     0,   622,   613,   614,   617,   618,     0,
     599,   600,   603,   604,   605,   606,   607,   608,   609,   612,
     610,   611,   374,   376,   371,     0,   368,   372,   373,     0,
     899,     0,   902,     0,     0,   906,   910,   897,   895,   896,
       0,   884,   887,   888,   889,   890,   891,   892,   893,   894,
     921,     0,     0,   916,   919,   920,    45,    50,     0,    37,
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
     408,   405,     0,     0,   637,   634,     0,     0,     0,     0,
       0,     0,     0,     0,   679,   684,   549,     0,     0,     0,
       0,     0,     0,     0,   558,   563,     0,     0,     0,     0,
       0,   597,   602,     0,     0,   370,   367,     0,     0,     0,
       0,     0,     0,     0,     0,   886,   883,     0,     0,   918,
     915,    49,    41,     0,     0,     0,     0,     0,   160,   161,
     162,     0,     0,     0,   199,   200,     0,     0,     0,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,   194,   195,   163,   164,   165,     0,     0,     0,
     177,   178,   185,   186,   187,   188,   193,     0,     0,     0,
     157,     0,     0,     0,     0,     0,   481,   482,   483,     0,
       0,     0,     0,     0,   765,     0,     0,     0,     0,     0,
       0,     0,   196,   197,   198,     0,     0,    68,     0,     0,
       0,   228,   229,   230,   231,   204,     0,     0,     0,     0,
       0,     0,   484,     0,     0,     0,     0,     0,   407,     0,
     664,   636,     0,     0,     0,     0,     0,     0,     0,     0,
     683,     0,     0,   575,     0,     0,     0,   586,   562,     0,
     619,   620,   621,     0,   601,     0,     0,   369,   898,     0,
     901,     0,   904,   905,     0,     0,   885,     0,   923,   917,
       0,     0,     0,     0,     0,   701,   703,   705,     0,     0,
     249,   156,   168,   169,   170,   171,   172,   167,   174,   176,
     397,   550,   589,   159,   181,   182,   183,   184,   180,   487,
      38,   666,   668,     0,   729,   671,   359,     0,     0,     0,
     770,     0,     0,   190,   192,     0,     0,    51,   219,   222,
     223,   221,   226,   227,   225,   466,   468,   470,   626,   464,
     472,   476,   478,   480,   474,     0,   663,   721,   707,   709,
     711,   715,   713,   719,   717,   578,   296,   582,   580,   585,
     616,   623,   375,   377,   900,   903,   908,   909,   907,   911,
     249,    42,     0,     0,     0,   241,   243,     0,   236,   239,
     240,   284,   286,   288,   292,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   306,     0,     0,   313,   315,
     317,   319,   321,   322,   323,   324,   325,   326,   290,   283,
       0,   256,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,     0,   254,     0,   250,
     251,   402,     0,   398,   399,   555,     0,   551,   552,   594,
       0,   590,   591,   492,     0,   488,   489,   338,   339,   340,
     341,   342,     0,   330,   333,   334,   335,   336,   337,   734,
       0,   730,   731,   676,     0,   672,   673,   364,     0,   360,
     361,     0,     0,     0,     0,     0,     0,     0,   380,   383,
     384,   385,   386,   387,   388,     0,     0,     0,   353,     0,
     345,   348,   349,   350,   351,   352,   793,   798,   800,     0,
     823,     0,   804,   792,   785,   786,   787,   790,   791,     0,
     777,   780,   781,   782,   783,   788,   789,   784,   775,     0,
     771,   772,     0,   875,     0,   878,   871,   872,     0,   865,
     868,   869,   870,   873,     0,   929,     0,   926,     0,     0,
       0,     0,   975,     0,   968,   971,   972,   973,   974,    53,
     631,     0,   627,   628,   725,     0,   724,     0,    62,   913,
     202,     0,     0,   238,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   258,   233,
     246,     0,   248,   253,     0,   396,   401,   559,   547,   554,
     598,   588,   593,     0,   486,   491,   332,   329,   736,   728,
     733,   680,   670,   675,     0,   358,   363,     0,     0,     0,
       0,     0,     0,   382,   379,     0,     0,     0,   347,   344,
       0,     0,     0,     0,     0,     0,     0,   779,   767,     0,
     769,   774,     0,     0,     0,     0,   867,   864,   881,     0,
     928,   925,     0,     0,     0,     0,   970,   967,    55,     0,
      54,     0,   625,   630,     0,   723,   922,     0,     0,   237,
       0,     0,     0,     0,   294,   297,   298,   299,   300,   301,
     302,   303,   304,   305,     0,   311,   312,     0,     0,     0,
       0,     0,     0,   257,     0,   252,     0,   400,     0,   553,
       0,   592,   545,   516,   517,   518,   500,   501,   521,   522,
     523,   524,   525,   526,   543,   503,   504,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   544,   497,   498,   499,   512,   513,   514,
     515,   509,   510,   511,     0,   494,   502,   519,   520,   505,
     506,   507,   508,   490,   331,   759,   761,     0,     0,   753,
     754,   755,   756,   757,   758,   746,   747,   751,   752,   748,
     749,   750,     0,   737,   738,   741,   742,   743,   744,   745,
     732,     0,   674,     0,   362,   389,   390,   391,   392,   393,
     394,   381,   354,   355,   356,   346,     0,     0,     0,   802,
       0,   803,     0,   778,     0,   773,   874,     0,   877,     0,
     866,   944,     0,   942,   940,   934,   938,   939,     0,   931,
     936,   937,   935,   927,   976,   977,   978,   979,   969,    52,
      57,     0,   629,     0,   242,   244,   285,   287,   289,   293,
     308,   309,   310,   307,   314,   316,   318,   320,   327,   291,
     255,   403,   556,   595,   496,   493,     0,     0,     0,     0,
     735,   740,   677,   365,   795,   796,   797,   794,   799,   801,
       0,   806,   776,   876,   879,     0,     0,     0,   933,   930,
      56,   632,   726,   495,     0,     0,   763,   764,   739,   835,
     838,   840,   842,   834,   833,   832,     0,   825,   828,   829,
     830,   831,   811,     0,   807,   808,     0,   941,     0,   932,
     760,   762,     0,     0,     0,     0,   827,   824,     0,   805,
     810,     0,   943,     0,     0,     0,     0,   826,   821,   820,
     816,   818,   819,     0,   813,   817,   809,   949,     0,   946,
     837,   836,   839,   841,   844,     0,   815,   812,     0,   948,
     945,   849,     0,   845,   846,     0,   814,   959,     0,     0,
       0,   964,     0,   951,   954,   955,   956,   957,   958,   947,
       0,   843,   848,   822,     0,     0,     0,     0,     0,   953,
     950,   861,   860,   854,   856,   857,   858,   859,     0,   851,
     855,   847,     0,   961,   962,   963,     0,   952,     0,   853,
     850,   960,   965,     0,   852,   862
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415,   -59, -1415,  -642, -1415,   568,
   -1415, -1415, -1415, -1415, -1415, -1415,  -645, -1415, -1415, -1415,
     -67, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   556,   773,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
      94, -1415, -1415, -1415, -1415,    97, -1415, -1415,   102,   104,
     -13,    13,    41,    51, -1415, -1415,    53, -1415,    56, -1415,
      59,   105,    64, -1415, -1415,    66,    69,    74,    76,    79,
   -1415,    81, -1415,   107, -1415, -1415, -1415, -1415, -1415,    43,
   -1415, -1415, -1415,   560,   765, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415,   269, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415,   475, -1415,   244, -1415,  -743,   250, -1415,
   -1415, -1414, -1415, -1399, -1415, -1387, -1415, -1415, -1415, -1415,
     -63, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,  -775, -1415,  -774, -1415,
    -771, -1415,   149, -1415, -1415, -1415, -1415, -1415, -1415,   234,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   214, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415,   228, -1415, -1415, -1415,
     229,   737, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   222,
   -1415, -1415, -1415, -1415, -1415, -1415, -1066, -1415, -1415, -1415,
     257, -1415, -1415, -1415,   262,   766, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1064, -1415,   -29, -1415,   -18, -1415,
      -4, -1415,     5, -1415,   110,   112,   115, -1415, -1415, -1415,
   -1415, -1415,   243, -1415, -1415,     4,   -60, -1415, -1415, -1415,
   -1415, -1415,   261, -1415, -1415, -1415,   265, -1415,   756, -1415,
     -34, -1415, -1415, -1415, -1415, -1415,   -27, -1415, -1415, -1415,
   -1415, -1415,   -32, -1415, -1415, -1415,   263, -1415, -1415, -1415,
     268, -1415,   754, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415,   200, -1415, -1415,
   -1415,   210,   791, -1415, -1415, -1415,   -44, -1415,     3, -1415,
     -56, -1415, -1415, -1415,   271, -1415, -1415, -1415,   275, -1415,
     787,   -48, -1415,    -7, -1415,    15, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1063, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415,   270, -1415, -1415, -1415,    17, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415,   247, -1415,   259,   274, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   -30, -1415,
   -1415,   -57, -1415, -1415, -1415, -1415, -1415,   -25, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   -79,
   -1415, -1415,  -103, -1415, -1415, -1415, -1415, -1415,   260, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   587,
     776, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,   640,   779,
   -1415, -1415, -1415, -1415, -1415, -1415,   277, -1415, -1415,    22,
   -1415, -1415, -1415, -1415, -1415, -1415,   -40, -1415, -1415,   -65,
   -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415, -1415,
     273, -1415, -1415, -1415, -1415
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   781,
      82,    83,    39,    64,    79,    80,   798,  1029,  1139,  1140,
     879,    41,    66,    85,   461,    86,    43,    67,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   490,   176,   177,   510,   178,   179,   180,
     181,   182,   183,   184,   496,   767,   185,   497,   186,   498,
     187,   188,   189,   511,   778,   190,   191,   192,   193,   194,
     529,   195,   530,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   465,   243,   244,    45,    68,   245,   539,   246,
     540,   801,   247,   541,   804,   248,   249,   250,   251,   205,
     475,   206,   466,   847,   848,   849,  1041,   850,  1042,   207,
     476,   208,   477,   908,   909,   910,  1071,   880,   881,   882,
    1045,   883,  1046,   884,  1047,   885,  1067,   886,  1048,   887,
     888,   578,   889,   890,   891,   892,   893,   894,   895,   896,
     897,   898,  1059,  1323,   899,   900,   901,  1062,   902,  1063,
     903,  1064,   904,  1065,   905,  1066,   209,   518,   932,   933,
     934,   935,   936,   937,   938,   210,   524,   969,   970,   971,
     972,   973,   211,   521,   948,   949,   950,  1094,    59,    75,
     425,   426,   427,   593,   428,   594,   212,   522,   957,   958,
     959,   960,   961,   962,   963,   964,   213,   506,   912,   913,
     914,  1074,    47,    69,   298,   299,   300,   552,   301,   548,
     302,   549,   303,   550,   304,   553,   305,   558,   306,   555,
     307,   556,   308,   557,   214,   215,   216,   312,   217,   512,
     924,   925,   926,  1083,  1224,  1225,   218,   507,    53,    72,
     916,   917,   918,  1077,    55,    73,   386,   387,   388,   389,
     390,   391,   392,   577,   393,   581,   394,   580,   395,   396,
     582,   397,   219,   508,   920,   921,   922,  1080,    57,    74,
     409,   410,   411,   412,   413,   586,   414,   415,   416,   417,
     418,   419,   590,   314,   551,  1031,  1032,  1033,  1141,    49,
      70,   344,   345,   346,   562,   347,   220,   513,   221,   514,
     222,   520,   944,   945,   946,  1091,    51,    71,   362,   363,
     364,   223,   470,   224,   471,   225,   472,   368,   567,   369,
     568,   370,   569,   371,   571,   372,   570,   373,   573,   374,
     572,   375,   566,   321,   559,  1035,  1036,  1144,   226,   519,
     940,   941,   942,  1088,  1252,  1253,  1254,  1255,  1256,  1336,
    1257,  1337,  1258,  1259,   227,   228,   525,   229,   526,   999,
    1000,  1001,  1119,   989,   990,   991,  1110,  1347,   992,  1111,
     993,  1112,   994,   995,   996,  1116,  1383,  1384,  1385,  1398,
    1413,  1414,  1415,  1425,   997,  1114,  1376,  1377,  1378,  1392,
    1421,  1379,  1393,  1380,  1394,  1381,  1395,  1432,  1433,  1434,
    1450,  1468,  1469,  1470,  1478,   230,   527,  1008,  1009,  1010,
    1011,  1123,  1012,  1013,  1125,   231,   528,    61,    76,   440,
     441,   442,   443,   598,   444,   445,   600,   446,   447,   448,
     603,   838,   449,   604,   232,   464,    63,    77,   452,   453,
     454,   607,   455,   233,   534,  1016,  1017,  1129,  1298,  1299,
    1300,  1301,  1357,  1302,  1355,  1418,  1419,  1428,  1442,  1443,
    1444,  1454,  1445,  1446,  1447,  1448,  1458,   234,   535,  1023,
    1024,  1025,  1026,  1027,  1028
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     160,   242,   266,   324,   358,    78,   384,   405,   424,   437,
     385,   406,   376,   317,   984,   985,   906,  1215,   986,  1216,
    1232,   318,   780,   365,   252,   315,   348,   360,   836,   398,
     420,    29,   438,    30,   378,    31,  1463,   313,   343,   359,
     407,   339,    28,   270,   136,   137,    40,   408,   462,   136,
     137,  1464,   340,   463,   136,   137,   281,   325,   811,   812,
     813,    81,   319,  1465,   366,  1463,   341,   817,   422,   423,
      42,   253,   316,   349,   361,   342,   399,   421,  1086,   439,
    1464,  1087,   282,   326,   320,   267,   367,    44,   831,   965,
     966,   967,  1465,  1437,   780,    46,  1438,  1439,  1440,  1441,
     268,   130,   269,   762,   763,   764,   765,  1002,  1003,  1004,
     283,   327,   297,  1369,   537,  1408,  1320,  1321,  1322,   538,
     284,   328,   285,   329,    48,   286,   330,   546,   287,   331,
     450,   451,   547,   289,   332,   290,   333,  1130,   291,   334,
    1131,    84,   766,   292,   335,   293,   336,    50,   294,   337,
     295,   338,   159,   271,   560,   272,   273,  1005,   274,   561,
     275,   276,   159,   277,   564,   595,   278,   159,   457,   565,
     596,   279,   605,   280,   288,   609,   296,   606,   537,   309,
     610,   310,   609,  1038,   311,   422,   423,  1039,   546,  1018,
    1019,  1020,  1021,  1040,   459,   235,   236,   136,   137,   237,
     799,   800,   238,   239,   240,   241,   159,   802,   803,   837,
     951,   952,   953,   954,   955,   956,    87,   845,   846,    88,
     871,   872,   873,   874,   875,   876,    52,  1043,  1068,   852,
     853,    89,  1044,  1069,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   927,   928,   929,   930,  1068,
     931,  1370,  1371,  1372,  1070,  1103,  1108,  1117,    54,   458,
    1104,  1109,  1118,    32,    33,    34,    35,  1126,  1215,   605,
    1216,  1232,  1127,   456,  1128,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   136,   137,  1136,   130,   131,    56,
     159,  1137,   136,   137,    93,    94,    95,    96,  1068,   132,
     133,   134,   560,  1330,    58,    60,   135,  1331,  1174,   136,
     137,    62,   467,   460,   138,   139,   140,   141,   142,   468,
     469,   473,   984,   985,   984,   985,   986,   143,   986,   474,
    1334,   595,   101,   102,   103,  1335,  1343,   144,   478,  1117,
     145,    93,    94,    95,  1352,   479,  1358,   146,   147,  1461,
     878,  1359,   148,   149,   377,   480,   378,   400,   379,   380,
     401,   402,   403,   564,   130,   131,   378,  1396,  1361,  1426,
    1429,   150,  1397,  1430,  1427,   151,   136,   137,   611,   612,
    1344,  1345,  1346,  1459,  1479,   404,   136,   137,  1460,  1480,
     152,   153,   154,   155,   156,   157,   481,   159,  1235,  1236,
    1237,  1238,   482,   483,   158,   159,   774,   775,   776,   777,
     484,   485,   131,   486,   487,   488,   489,   491,   378,   492,
     379,   380,   159,   493,   494,   381,   382,   383,   495,   499,
     500,   501,   502,   136,   137,   503,   504,   505,   136,   137,
     509,   515,   350,   516,   613,   517,   523,   531,   532,   533,
     160,   536,   351,   352,   353,   354,   355,   356,   357,   242,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   266,   542,   543,   544,   324,   545,   554,
     563,   574,   252,   575,   317,   576,   579,   583,   358,   159,
     585,   592,   318,   584,   587,   588,   315,   589,   384,   159,
     348,   597,   385,   591,   599,   405,   601,   365,   313,   406,
     602,   360,   343,   608,   270,   339,   614,   615,   437,   616,
     617,   398,   621,   359,   618,   619,   340,   281,   420,   253,
     620,   325,   622,   319,   623,   626,   625,   627,   407,   624,
     341,   438,   628,   316,   378,   408,   159,   349,   366,   342,
     629,   159,   635,   282,   641,   320,   267,   326,   361,   630,
     631,   632,   633,   647,   136,   137,   634,   638,   399,   636,
     367,   268,   637,   269,   639,   421,   640,   642,   643,   648,
     649,   283,   644,   297,   645,   327,   646,   650,   439,   651,
     653,   284,   652,   285,   654,   328,   286,   329,   656,   287,
     330,   655,   657,   331,   289,   658,   290,   659,   332,   291,
     333,   660,   661,   334,   292,   662,   293,   663,   335,   294,
     336,   295,   664,   337,   271,   338,   272,   273,   665,   274,
     666,   275,   276,   667,   277,   668,   669,   278,   670,   868,
     869,   870,   279,   671,   280,   288,   672,   296,  1362,   673,
     309,  1291,   310,  1292,  1293,   311,   674,   675,   676,   677,
     678,   679,   680,   681,   160,   685,   242,   686,   688,   682,
     683,   841,   689,   690,   684,   691,   696,   159,   692,   697,
     698,   699,   700,   701,   693,   703,   694,   702,   704,   252,
     705,   706,   707,   709,   710,   712,   713,   714,   715,   716,
     717,   968,   983,   136,   137,   437,   718,   719,   721,  1022,
     722,   839,   724,   725,   726,   729,   723,   733,   735,   727,
     736,   730,   739,   741,   974,   987,   731,  1006,   438,   732,
     744,   745,   738,   747,   740,   750,   253,    91,    92,    93,
      94,    95,    96,   742,   751,   743,   748,   752,   976,   753,
     754,   755,   977,   978,   979,   980,   756,   757,   758,   759,
     760,   761,   981,   982,   768,   770,   769,   771,   772,   773,
     779,   975,   988,    30,  1007,   439,   782,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   783,   784,
     785,   786,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   787,   254,   255,   256,   788,
     131,   789,   790,  1034,   793,   791,   159,   792,   794,   795,
     796,   797,   133,   134,   805,   806,   807,   808,   809,   257,
     810,   136,   137,   258,   259,   260,   138,   139,   140,   814,
     261,   262,   263,   815,   816,   840,   818,   264,   907,   143,
     911,   819,   820,   821,   822,   915,   823,   265,   824,   825,
     826,   851,   852,   853,   854,   855,   856,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   919,   827,   828,   866,
     867,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     877,   116,   117,   118,   119,   120,   121,   122,   923,   124,
     125,   126,   127,   829,   136,   137,   939,   830,   832,   131,
     834,   835,   152,   153,   943,   947,   998,  1015,  1030,  1049,
    1050,  1051,   134,  1052,  1053,   378,  1054,  1055,  1056,   322,
     136,   137,  1057,  1058,  1060,  1061,  1073,  1076,  1072,   261,
     262,   263,  1075,  1078,   159,  1079,   264,   323,  1082,  1081,
    1084,  1085,  1089,  1090,  1093,  1092,  1096,  1121,  1095,  1097,
    1098,  1099,  1100,  1101,  1102,  1105,  1106,  1107,  1113,  1115,
    1122,   429,   430,   431,   432,   433,   434,   435,   436,  1120,
    1124,  1132,  1133,  1134,  1135,  1138,  1143,   266,  1142,  1145,
     384,  1146,  1147,   405,   385,  1148,  1182,   406,   317,  1150,
    1214,  1239,  1151,   878,   358,  1244,   318,   424,  1245,  1152,
     315,   152,   153,   398,  1153,  1229,   420,   159,  1155,  1227,
    1249,   968,   313,   365,  1247,  1154,   407,   360,   270,  1156,
     983,  1226,   983,   408,  1217,  1157,  1246,  1186,  1158,   359,
    1164,   281,  1294,   159,   974,  1218,  1295,   319,  1167,  1022,
    1197,  1165,  1168,   987,   324,   987,  1230,   316,   159,  1219,
     399,  1250,  1006,   421,   366,  1296,  1228,   282,  1220,   320,
     267,  1248,  1159,  1160,   361,  1161,  1198,   348,  1231,  1183,
    1162,  1169,  1163,  1251,  1240,   268,   367,   269,  1166,   343,
    1170,   975,   339,  1171,  1184,   283,  1185,   297,  1172,  1241,
     988,  1242,   988,   340,  1199,   284,  1213,   285,   325,  1007,
     286,  1243,  1297,   287,  1200,  1265,  1201,   341,   289,  1202,
     290,  1266,  1203,   291,   349,  1267,   342,  1205,   292,  1206,
     293,  1268,  1207,   294,   326,   295,  1269,  1208,   271,  1209,
     272,   273,  1210,   274,  1211,   275,   276,  1187,   277,  1188,
    1189,   278,  1190,  1272,  1191,  1192,   279,  1193,   280,   288,
    1194,   296,   327,  1270,   309,  1195,   310,  1196,  1204,   311,
    1212,  1276,   328,  1221,   329,  1222,  1273,   330,  1223,  1274,
     331,  1277,  1278,  1280,  1282,   332,  1287,   333,  1289,  1309,
     334,  1310,  1350,  1313,  1332,   335,  1338,   336,  1333,  1339,
     337,  1340,   338,  1341,  1342,  1279,  1351,  1314,  1281,  1286,
    1354,  1304,  1288,  1356,  1364,  1305,  1365,  1386,  1382,  1388,
    1399,  1400,  1401,  1403,  1306,  1387,  1307,  1315,  1404,  1316,
    1317,  1318,  1405,  1319,  1324,  1406,  1325,  1326,  1328,  1329,
    1348,  1349,  1417,  1353,  1360,  1420,  1424,  1182,  1366,  1367,
    1390,  1214,  1391,  1402,  1239,  1422,  1423,  1431,  1244,  1435,
    1451,  1245,  1452,  1373,  1453,  1455,  1229,  1456,  1457,  1472,
    1227,  1294,  1473,  1249,  1476,  1295,  1474,  1247,  1475,  1481,
    1482,  1483,  1226,  1485,   833,  1217,  1374,   842,  1186,  1246,
     687,   695,  1149,   844,  1296,  1037,  1218,  1175,  1173,  1327,
    1234,  1197,  1275,  1263,  1264,  1271,   708,  1230,  1233,  1373,
    1219,  1409,   737,  1177,  1250,  1410,  1176,  1228,  1363,  1220,
    1179,   728,  1178,  1312,  1248,  1181,   734,  1198,  1180,  1231,
    1183,  1311,  1374,  1375,  1411,   711,  1251,  1240,  1368,  1409,
    1260,  1297,   720,  1410,  1262,  1184,  1261,  1185,  1285,  1436,
    1416,  1407,  1241,  1471,  1242,  1199,  1484,  1213,  1284,  1014,
    1389,   746,  1411,  1462,  1243,  1200,  1290,  1201,   749,  1449,
    1202,  1283,   843,  1203,  1477,     0,     0,     0,  1205,  1375,
    1206,  1412,     0,  1207,     0,     0,  1466,  1303,  1208,  1308,
    1209,     0,  1462,  1210,     0,  1211,     0,     0,  1187,     0,
    1188,  1189,     0,  1190,     0,  1191,  1192,     0,  1193,  1412,
       0,  1194,     0,     0,     0,  1466,  1195,     0,  1196,  1204,
       0,  1212,     0,     0,  1221,     0,  1222,     0,     0,  1223,
       0,     0,     0,  1467,    91,    92,    93,    94,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1467,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     0,     0,     0,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,     0,     0,     0,     0,   131,   378,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,     0,     0,     0,     0,     0,     0,     0,   136,   137,
       0,   259,     0,   138,   139,   140,     0,   261,   262,   263,
       0,     0,     0,     0,   264,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   265,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
      73,    74,    72,    69,   789,   789,   759,  1083,   789,  1083,
    1083,    69,   664,    71,    68,    69,    70,    71,    18,    73,
      74,     5,    76,     7,   104,     9,  1450,    69,    70,    71,
      74,    70,     0,    69,   124,   125,     7,    74,     3,   124,
     125,  1450,    70,     8,   124,   125,    69,    70,   703,   704,
     705,   237,    69,  1450,    71,  1479,    70,   712,   153,   154,
       7,    68,    69,    70,    71,    70,    73,    74,     3,    76,
    1479,     6,    69,    70,    69,    69,    71,     7,   733,   164,
     165,   166,  1479,   212,   736,     7,   215,   216,   217,   218,
      69,   102,    69,   201,   202,   203,   204,   187,   188,   189,
      69,    70,    69,    40,     3,   185,    55,    56,    57,     8,
      69,    70,    69,    70,     7,    69,    70,     3,    69,    70,
      12,    13,     8,    69,    70,    69,    70,     3,    69,    70,
       6,    10,   240,    69,    70,    69,    70,     7,    69,    70,
      69,    70,   237,    69,     3,    69,    69,   237,    69,     8,
      69,    69,   237,    69,     3,     3,    69,   237,     3,     8,
       8,    69,     3,    69,    69,     3,    69,     8,     3,    69,
       8,    69,     3,     8,    69,   153,   154,     8,     3,   220,
     221,   222,   223,     8,     8,    15,    16,   124,   125,    19,
      17,    18,    22,    23,    24,    25,   237,    20,    21,   199,
     156,   157,   158,   159,   160,   161,    11,    27,    28,    14,
      63,    64,    65,    66,    67,    68,     7,     3,     3,    41,
      42,    26,     8,     8,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,   144,   145,   146,   147,     3,
     149,   178,   179,   180,     8,     3,     3,     3,     7,     4,
       8,     8,     8,   237,   238,   239,   240,     3,  1334,     3,
    1334,  1334,     8,     6,     8,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,   124,   125,     3,   102,   103,     7,
     237,     8,   124,   125,    32,    33,    34,    35,     3,   114,
     115,   116,     3,     8,     7,     7,   121,     8,  1071,   124,
     125,     7,     4,     3,   129,   130,   131,   132,   133,     4,
       4,     4,  1117,  1117,  1119,  1119,  1117,   142,  1119,     4,
       3,     3,    70,    71,    72,     8,     8,   152,     4,     3,
     155,    32,    33,    34,     8,     4,     3,   162,   163,   181,
     182,     8,   167,   168,    40,     4,   104,   105,   106,   107,
     108,   109,   110,     3,   102,   103,   104,     3,     8,     3,
       3,   186,     8,     6,     8,   190,   124,   125,   457,   458,
     170,   171,   172,     3,     3,   133,   124,   125,     8,     8,
     205,   206,   207,   208,   209,   210,     4,   237,   136,   137,
     138,   139,     4,     4,   219,   237,   117,   118,   119,   120,
       4,     4,   103,     4,     4,     4,     4,     4,   104,     4,
     106,   107,   237,     4,     4,   111,   112,   113,     4,     4,
       4,     4,     4,   124,   125,     4,     4,     4,   124,   125,
       4,     4,   133,     4,   237,     4,     4,     4,     4,     4,
     537,     4,   143,   144,   145,   146,   147,   148,   149,   546,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   560,     4,     4,     4,   564,     4,     4,
       4,     8,   546,     3,   560,     8,     4,     4,   575,   237,
       3,     3,   560,     8,     4,     4,   560,     4,   585,   237,
     564,     4,   585,     8,     4,   592,     4,   575,   560,   592,
       4,   575,   564,     4,   560,   564,     4,     4,   605,     4,
       4,   585,     4,   575,   240,   240,   564,   560,   592,   546,
     240,   564,     4,   560,     4,     4,   240,     4,   592,   238,
     564,   605,     4,   560,   104,   592,   237,   564,   575,   564,
     238,   237,   239,   560,     4,   560,   560,   564,   575,   238,
     238,   238,   238,     4,   124,   125,   240,   238,   585,   239,
     575,   560,   239,   560,   239,   592,   238,   238,   238,     4,
       4,   560,   240,   560,   240,   564,   240,   240,   605,   240,
     238,   560,   239,   560,   238,   564,   560,   564,   240,   560,
     564,   238,     4,   564,   560,     4,   560,     4,   564,   560,
     564,   238,     4,   564,   560,     4,   560,     4,   564,   560,
     564,   560,     4,   564,   560,   564,   560,   560,     4,   560,
     240,   560,   560,   240,   560,   240,     4,   560,     4,    60,
      61,    62,   560,     4,   560,   560,     4,   560,  1313,     4,
     560,   211,   560,   213,   214,   560,   238,     4,     4,     4,
       4,     4,     4,     4,   751,     4,   753,     4,     4,   240,
     240,   750,     4,     4,   240,   240,     4,   237,   240,     4,
       4,     4,     4,     4,   238,     4,   238,   238,     4,   753,
       4,     4,     4,     4,   238,     4,     4,     4,     4,     4,
       4,   788,   789,   124,   125,   792,     4,     4,     4,   796,
       4,   200,     4,     4,     4,     4,   238,     4,     4,   240,
       4,   240,     4,     4,   788,   789,   240,   791,   792,   240,
       4,     4,   240,     4,   238,     4,   753,    30,    31,    32,
      33,    34,    35,   238,     7,   238,   238,     7,   169,     7,
       7,   237,   173,   174,   175,   176,   237,   237,     7,     7,
       5,   237,   183,   184,   237,     5,   237,     5,     5,   237,
       5,   788,   789,     7,   791,   792,   237,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     5,     5,
       5,     5,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     7,    99,   100,   101,     7,
     103,     7,     5,   151,   237,     7,   237,     7,   237,     5,
       7,     5,   115,   116,   237,   237,   237,     5,   237,   122,
     237,   124,   125,   126,   127,   128,   129,   130,   131,   237,
     133,   134,   135,     7,   237,     5,   237,   140,     7,   142,
       7,   237,   237,   237,   237,     7,   237,   150,   237,   237,
     237,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     7,   237,   237,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    85,    86,    87,    88,    89,    90,    91,     7,    93,
      94,    95,    96,   237,   124,   125,     7,   237,   237,   103,
     237,   237,   205,   206,     7,     7,     7,     7,     7,     4,
       4,     4,   116,     4,     4,   104,     4,     4,     4,   123,
     124,   125,     4,     4,     4,     4,     3,     3,     6,   133,
     134,   135,     6,     6,   237,     3,   140,   141,     3,     6,
       6,     3,     6,     3,     3,     6,     3,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   191,   192,   193,   194,   195,   196,   197,   198,     6,
       4,     4,     4,     4,     4,   237,     3,  1074,     6,     8,
    1077,     6,     4,  1080,  1077,     4,  1083,  1080,  1074,     4,
    1083,  1088,     4,   182,  1091,  1088,  1074,  1094,  1088,     4,
    1074,   205,   206,  1077,     4,  1083,  1080,   237,   240,  1083,
    1088,  1108,  1074,  1091,  1088,   238,  1080,  1091,  1074,   238,
    1117,  1083,  1119,  1080,  1083,   240,  1088,  1083,   238,  1091,
       4,  1074,  1129,   237,  1108,  1083,  1129,  1074,     4,  1136,
    1083,   240,     4,  1117,  1141,  1119,  1083,  1074,   237,  1083,
    1077,  1088,  1126,  1080,  1091,  1129,  1083,  1074,  1083,  1074,
    1074,  1088,   238,   238,  1091,   238,  1083,  1141,  1083,  1083,
     238,     4,   238,  1088,  1088,  1074,  1091,  1074,   238,  1141,
       4,  1108,  1141,     4,  1083,  1074,  1083,  1074,     4,  1088,
    1117,  1088,  1119,  1141,  1083,  1074,  1083,  1074,  1141,  1126,
    1074,  1088,  1129,  1074,  1083,   238,  1083,  1141,  1074,  1083,
    1074,   238,  1083,  1074,  1141,   238,  1141,  1083,  1074,  1083,
    1074,   238,  1083,  1074,  1141,  1074,   238,  1083,  1074,  1083,
    1074,  1074,  1083,  1074,  1083,  1074,  1074,  1083,  1074,  1083,
    1083,  1074,  1083,   240,  1083,  1083,  1074,  1083,  1074,  1074,
    1083,  1074,  1141,   238,  1074,  1083,  1074,  1083,  1083,  1074,
    1083,     4,  1141,  1083,  1141,  1083,   238,  1141,  1083,   238,
    1141,     4,     4,     4,     4,  1141,     4,  1141,     4,     6,
    1141,     3,     7,     4,     8,  1141,     4,  1141,     8,     4,
    1141,     8,  1141,     3,     8,   238,     5,   237,   240,   240,
    1289,   240,   238,     4,     4,   240,     4,     4,     7,     4,
       6,     3,     5,     4,   240,   238,   240,   237,     4,   237,
     237,   237,     4,   237,   237,     4,   237,   237,   237,   237,
     237,   237,     7,   237,   237,   177,     5,  1334,   240,   240,
     237,  1334,   237,   237,  1341,   237,   237,     7,  1341,     4,
       6,  1341,     3,  1350,   237,     4,  1334,     4,     4,     4,
    1334,  1358,   240,  1341,     4,  1358,   238,  1341,   238,   237,
     237,     4,  1334,   237,   736,  1334,  1350,   751,  1334,  1341,
     537,   546,  1043,   753,  1358,   840,  1334,  1073,  1068,  1170,
    1086,  1334,  1108,  1094,  1096,  1103,   560,  1334,  1085,  1396,
    1334,  1398,   595,  1076,  1341,  1398,  1074,  1334,  1334,  1334,
    1079,   585,  1077,  1143,  1341,  1082,   592,  1334,  1080,  1334,
    1334,  1141,  1396,  1350,  1398,   564,  1341,  1341,  1341,  1426,
    1090,  1358,   575,  1426,  1093,  1334,  1091,  1334,  1121,  1426,
    1400,  1396,  1341,  1452,  1341,  1334,  1479,  1334,  1119,   792,
    1358,   605,  1426,  1450,  1341,  1334,  1126,  1334,   609,  1429,
    1334,  1117,   752,  1334,  1459,    -1,    -1,    -1,  1334,  1396,
    1334,  1398,    -1,  1334,    -1,    -1,  1450,  1130,  1334,  1136,
    1334,    -1,  1479,  1334,    -1,  1334,    -1,    -1,  1334,    -1,
    1334,  1334,    -1,  1334,    -1,  1334,  1334,    -1,  1334,  1426,
      -1,  1334,    -1,    -1,    -1,  1479,  1334,    -1,  1334,  1334,
      -1,  1334,    -1,    -1,  1334,    -1,  1334,    -1,    -1,  1334,
      -1,    -1,    -1,  1450,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1479,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,   103,   104,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,
     116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
      -1,   127,    -1,   129,   130,   131,    -1,   133,   134,   135,
      -1,    -1,    -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   205,
     206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   237
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,     0,     5,
       7,     9,   237,   238,   239,   240,   256,   257,   258,   263,
       7,   272,     7,   277,     7,   336,     7,   453,     7,   540,
       7,   557,     7,   489,     7,   495,     7,   519,     7,   429,
       7,   668,     7,   687,   264,   259,   273,   278,   337,   454,
     541,   558,   490,   496,   520,   430,   669,   688,   256,   265,
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
     328,   329,   330,   331,   332,   350,   352,   360,   362,   407,
     416,   423,   437,   447,   475,   476,   477,   479,   487,   513,
     547,   549,   551,   562,   564,   566,   589,   605,   606,   608,
     656,   666,   685,   694,   718,    15,    16,    19,    22,    23,
      24,    25,   271,   334,   335,   338,   340,   343,   346,   347,
     348,   349,   547,   549,    99,   100,   101,   122,   126,   127,
     128,   133,   134,   135,   140,   150,   271,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   296,   299,
     300,   301,   302,   303,   304,   307,   309,   311,   312,   313,
     316,   317,   318,   319,   320,   322,   324,   330,   455,   456,
     457,   459,   461,   463,   465,   467,   469,   471,   473,   475,
     476,   477,   478,   513,   534,   547,   549,   551,   562,   564,
     566,   584,   123,   141,   271,   301,   302,   303,   304,   307,
     309,   311,   313,   316,   317,   318,   319,   320,   322,   467,
     469,   471,   473,   513,   542,   543,   544,   546,   547,   549,
     133,   143,   144,   145,   146,   147,   148,   149,   271,   513,
     547,   549,   559,   560,   561,   562,   564,   566,   568,   570,
     572,   574,   576,   578,   580,   582,   487,    40,   104,   106,
     107,   111,   112,   113,   271,   381,   497,   498,   499,   500,
     501,   502,   503,   505,   507,   509,   510,   512,   547,   549,
     105,   108,   109,   110,   133,   271,   381,   501,   507,   521,
     522,   523,   524,   525,   527,   528,   529,   530,   531,   532,
     547,   549,   153,   154,   271,   431,   432,   433,   435,   191,
     192,   193,   194,   195,   196,   197,   198,   271,   547,   549,
     670,   671,   672,   673,   675,   676,   678,   679,   680,   683,
      12,    13,   689,   690,   691,   693,     6,     3,     4,     8,
       3,   275,     3,     8,   686,   333,   353,     4,     4,     4,
     563,   565,   567,     4,     4,   351,   361,   363,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     294,     4,     4,     4,     4,     4,   305,   308,   310,     4,
       4,     4,     4,     4,     4,     4,   448,   488,   514,     4,
     297,   314,   480,   548,   550,     4,     4,     4,   408,   590,
     552,   424,   438,     4,   417,   607,   609,   657,   667,   321,
     323,     4,     4,     4,   695,   719,     4,     3,     8,   339,
     341,   344,     4,     4,     4,     4,     3,     8,   460,   462,
     464,   535,   458,   466,     4,   470,   472,   474,   468,   585,
       3,     8,   545,     4,     3,     8,   583,   569,   571,   573,
     577,   575,   581,   579,     8,     3,     8,   504,   382,     4,
     508,   506,   511,     4,     8,     3,   526,     4,     4,     4,
     533,     8,     3,   434,   436,     3,     8,     4,   674,     4,
     677,     4,     4,   681,   684,     3,     8,   692,     4,     3,
       8,   256,   256,   237,     4,     4,     4,     4,   240,   240,
     240,     4,     4,     4,   238,   240,     4,     4,     4,   238,
     238,   238,   238,   238,   240,   239,   239,   239,   238,   239,
     238,     4,   238,   238,   240,   240,   240,     4,     4,     4,
     240,   240,   239,   238,   238,   238,   240,     4,     4,     4,
     238,     4,     4,     4,     4,     4,   240,   240,   240,     4,
       4,     4,     4,     4,   238,     4,     4,     4,     4,     4,
       4,     4,   240,   240,   240,     4,     4,   280,     4,     4,
       4,   240,   240,   238,   238,   335,     4,     4,     4,     4,
       4,     4,   238,     4,     4,     4,     4,     4,   456,     4,
     238,   543,     4,     4,     4,     4,     4,     4,     4,     4,
     561,     4,     4,   238,     4,     4,     4,   240,   499,     4,
     240,   240,   240,     4,   523,     4,     4,   432,   240,     4,
     238,     4,   238,   238,     4,     4,   671,     4,   238,   690,
       4,     7,     7,     7,     7,   237,   237,   237,     7,     7,
       5,   237,   201,   202,   203,   204,   240,   306,   237,   237,
       5,     5,     5,   237,   117,   118,   119,   120,   315,     5,
     258,   260,   237,     5,     5,     5,     5,     7,     7,     7,
       5,     7,     7,   237,   237,     5,     7,     5,   267,    17,
      18,   342,    20,    21,   345,   237,   237,   237,     5,   237,
     237,   267,   267,   267,   237,     7,   237,   267,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   267,   237,   260,   237,   237,    18,   199,   682,   200,
       5,   256,   279,   689,   334,    27,    28,   354,   355,   356,
     358,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   182,   271,
     368,   369,   370,   372,   374,   376,   378,   380,   381,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   395,
     396,   397,   399,   401,   403,   405,   368,     7,   364,   365,
     366,     7,   449,   450,   451,     7,   491,   492,   493,     7,
     515,   516,   517,     7,   481,   482,   483,   144,   145,   146,
     147,   149,   409,   410,   411,   412,   413,   414,   415,     7,
     591,   592,   593,     7,   553,   554,   555,     7,   425,   426,
     427,   156,   157,   158,   159,   160,   161,   439,   440,   441,
     442,   443,   444,   445,   446,   164,   165,   166,   271,   418,
     419,   420,   421,   422,   547,   549,   169,   173,   174,   175,
     176,   183,   184,   271,   397,   399,   401,   547,   549,   614,
     615,   616,   619,   621,   623,   624,   625,   635,     7,   610,
     611,   612,   187,   188,   189,   237,   547,   549,   658,   659,
     660,   661,   663,   664,   670,     7,   696,   697,   220,   221,
     222,   223,   271,   720,   721,   722,   723,   724,   725,   268,
       7,   536,   537,   538,   151,   586,   587,   364,     8,     8,
       8,   357,   359,     3,     8,   371,   373,   375,   379,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   393,
       4,     4,   398,   400,   402,   404,   406,   377,     3,     8,
       8,   367,     6,     3,   452,     6,     3,   494,     6,     3,
     518,     6,     3,   484,     6,     3,     3,     6,   594,     6,
       3,   556,     6,     3,   428,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     617,   620,   622,     4,   636,     4,   626,     3,     8,   613,
       6,     3,     4,   662,     4,   665,     3,     8,     8,   698,
       3,     6,     4,     4,     4,     4,     3,     8,   237,   269,
     270,   539,     6,     3,   588,     8,     6,     4,     4,   355,
       4,     4,     4,     4,   238,   240,   238,   240,   238,   238,
     238,   238,   238,   238,     4,   240,   238,     4,     4,     4,
       4,     4,     4,   369,   368,   366,   455,   451,   497,   493,
     521,   517,   271,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   296,   299,   300,   301,   302,   303,
     304,   307,   309,   311,   312,   313,   316,   317,   318,   319,
     320,   322,   324,   330,   381,   447,   465,   467,   469,   471,
     473,   475,   476,   477,   485,   486,   513,   547,   549,   562,
     564,   566,   584,   483,   410,   136,   137,   138,   139,   271,
     281,   282,   283,   330,   381,   487,   513,   547,   549,   562,
     564,   566,   595,   596,   597,   598,   599,   601,   603,   604,
     593,   559,   555,   431,   427,   238,   238,   238,   238,   238,
     238,   440,   240,   238,   238,   419,     4,     4,     4,   238,
       4,   240,     4,   615,   614,   612,   240,     4,   238,     4,
     659,   211,   213,   214,   271,   381,   547,   549,   699,   700,
     701,   702,   704,   697,   240,   240,   240,   240,   721,     6,
       3,   542,   538,     4,   237,   237,   237,   237,   237,   237,
      55,    56,    57,   394,   237,   237,   237,   403,   237,   237,
       8,     8,     8,     8,     3,     8,   600,   602,     4,     4,
       8,     3,     8,     8,   170,   171,   172,   618,   237,   237,
       7,     5,     8,   237,   256,   705,     4,   703,     3,     8,
     237,     8,   267,   486,     4,     4,   240,   240,   597,    40,
     178,   179,   180,   271,   547,   549,   637,   638,   639,   642,
     644,   646,     7,   627,   628,   629,     4,   238,     4,   700,
     237,   237,   640,   643,   645,   647,     3,     8,   630,     6,
       3,     5,   237,     4,     4,     4,     4,   638,   185,   271,
     381,   547,   549,   631,   632,   633,   629,     7,   706,   707,
     177,   641,   237,   237,     5,   634,     3,     8,   708,     3,
       6,     7,   648,   649,   650,     4,   632,   212,   215,   216,
     217,   218,   709,   710,   711,   713,   714,   715,   716,   707,
     651,     6,     3,   237,   712,     4,     4,     4,   717,     3,
       8,   181,   271,   372,   374,   376,   547,   549,   652,   653,
     654,   650,     4,   240,   238,   238,     4,   710,   655,     3,
       8,   237,   237,     4,   653,   237
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
     369,   369,   369,   369,   371,   370,   373,   372,   375,   374,
     377,   376,   379,   378,   380,   382,   381,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   393,   392,   394,   394,
     394,   395,   396,   398,   397,   400,   399,   402,   401,   404,
     403,   403,   403,   403,   403,   403,   406,   405,   408,   407,
     409,   409,   409,   410,   410,   410,   410,   410,   411,   412,
     413,   414,   415,   417,   416,   418,   418,   418,   419,   419,
     419,   419,   419,   419,   420,   421,   422,   424,   423,   425,
     425,   426,   426,   426,   428,   427,   430,   429,   431,   431,
     431,   431,   432,   432,   434,   433,   436,   435,   438,   437,
     439,   439,   439,   440,   440,   440,   440,   440,   440,   441,
     442,   443,   444,   445,   446,   448,   447,   449,   449,   450,
     450,   450,   452,   451,   454,   453,   455,   455,   455,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   458,   457,   460,   459,   462,   461,   464,
     463,   466,   465,   468,   467,   470,   469,   472,   471,   474,
     473,   475,   476,   477,   478,   480,   479,   481,   481,   482,
     482,   482,   484,   483,   485,   485,   485,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   488,   487,   490,   489,
     491,   491,   492,   492,   492,   494,   493,   496,   495,   497,
     497,   498,   498,   498,   499,   499,   499,   499,   499,   499,
     499,   499,   499,   499,   500,   501,   502,   504,   503,   506,
     505,   508,   507,   509,   511,   510,   512,   514,   513,   515,
     515,   516,   516,   516,   518,   517,   520,   519,   521,   521,
     522,   522,   522,   523,   523,   523,   523,   523,   523,   523,
     523,   523,   523,   523,   524,   526,   525,   527,   528,   529,
     530,   531,   533,   532,   535,   534,   536,   536,   537,   537,
     537,   539,   538,   541,   540,   542,   542,   542,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   545,   544,   546,   548,   547,   550,   549,   552,
     551,   553,   553,   554,   554,   554,   556,   555,   558,   557,
     559,   559,   560,   560,   560,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     563,   562,   565,   564,   567,   566,   569,   568,   571,   570,
     573,   572,   575,   574,   577,   576,   579,   578,   581,   580,
     583,   582,   585,   584,   586,   588,   587,   590,   589,   591,
     591,   592,   592,   592,   594,   593,   595,   595,   596,   596,
     596,   597,   597,   597,   597,   597,   597,   597,   597,   597,
     597,   597,   597,   597,   597,   597,   597,   597,   598,   600,
     599,   602,   601,   603,   604,   605,   607,   606,   609,   608,
     610,   610,   611,   611,   611,   613,   612,   614,   614,   614,
     615,   615,   615,   615,   615,   615,   615,   615,   615,   615,
     615,   615,   615,   617,   616,   618,   618,   618,   620,   619,
     622,   621,   623,   624,   626,   625,   627,   627,   628,   628,
     628,   630,   629,   631,   631,   631,   632,   632,   632,   632,
     632,   634,   633,   636,   635,   637,   637,   637,   638,   638,
     638,   638,   638,   638,   638,   640,   639,   641,   643,   642,
     645,   644,   647,   646,   648,   648,   649,   649,   649,   651,
     650,   652,   652,   652,   653,   653,   653,   653,   653,   653,
     653,   655,   654,   657,   656,   658,   658,   658,   659,   659,
     659,   659,   659,   659,   660,   662,   661,   663,   665,   664,
     667,   666,   669,   668,   670,   670,   670,   671,   671,   671,
     671,   671,   671,   671,   671,   671,   671,   671,   672,   674,
     673,   675,   677,   676,   678,   679,   681,   680,   682,   682,
     684,   683,   686,   685,   688,   687,   689,   689,   689,   690,
     690,   692,   691,   693,   695,   694,   696,   696,   696,   698,
     697,   699,   699,   699,   700,   700,   700,   700,   700,   700,
     700,   701,   703,   702,   705,   704,   706,   706,   706,   708,
     707,   709,   709,   709,   710,   710,   710,   710,   710,   712,
     711,   713,   714,   715,   717,   716,   719,   718,   720,   720,
     720,   721,   721,   721,   721,   721,   722,   723,   724,   725
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     6,
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
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     3,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     3,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     0,     6,     3,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     3
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
    1154,  1155,  1156,  1157,  1160,  1160,  1169,  1169,  1178,  1178,
    1187,  1187,  1196,  1196,  1205,  1211,  1211,  1220,  1226,  1232,
    1238,  1244,  1250,  1256,  1262,  1268,  1274,  1274,  1282,  1283,
    1284,  1287,  1293,  1299,  1299,  1308,  1308,  1317,  1317,  1326,
    1326,  1334,  1337,  1340,  1343,  1346,  1351,  1351,  1360,  1360,
    1371,  1372,  1373,  1378,  1379,  1380,  1381,  1382,  1385,  1390,
    1395,  1400,  1405,  1412,  1412,  1425,  1426,  1427,  1432,  1433,
    1434,  1435,  1436,  1437,  1440,  1446,  1452,  1458,  1458,  1469,
    1470,  1473,  1474,  1475,  1480,  1480,  1490,  1490,  1500,  1501,
    1502,  1505,  1508,  1509,  1512,  1512,  1521,  1521,  1530,  1530,
    1542,  1543,  1544,  1549,  1550,  1551,  1552,  1553,  1554,  1557,
    1563,  1569,  1575,  1581,  1587,  1596,  1596,  1610,  1611,  1614,
    1615,  1616,  1625,  1625,  1651,  1651,  1662,  1663,  1664,  1670,
    1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,
    1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,
    1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,
    1721,  1722,  1723,  1726,  1726,  1735,  1735,  1744,  1744,  1753,
    1753,  1762,  1762,  1771,  1771,  1781,  1781,  1793,  1793,  1804,
    1804,  1815,  1821,  1827,  1833,  1841,  1841,  1853,  1854,  1858,
    1859,  1860,  1865,  1865,  1873,  1874,  1875,  1880,  1881,  1882,
    1883,  1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,  1892,
    1893,  1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,
    1903,  1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,
    1913,  1914,  1915,  1916,  1917,  1918,  1919,  1920,  1921,  1922,
    1923,  1924,  1925,  1926,  1927,  1928,  1935,  1935,  1949,  1949,
    1958,  1959,  1962,  1963,  1964,  1971,  1971,  1986,  1986,  2000,
    2001,  2004,  2005,  2006,  2011,  2012,  2013,  2014,  2015,  2016,
    2017,  2018,  2019,  2020,  2023,  2025,  2031,  2033,  2033,  2042,
    2042,  2051,  2051,  2060,  2062,  2062,  2071,  2081,  2081,  2094,
    2095,  2100,  2101,  2102,  2109,  2109,  2121,  2121,  2133,  2134,
    2139,  2140,  2141,  2148,  2149,  2150,  2151,  2152,  2153,  2154,
    2155,  2156,  2157,  2158,  2161,  2163,  2163,  2172,  2174,  2176,
    2182,  2188,  2194,  2194,  2208,  2208,  2221,  2222,  2225,  2226,
    2227,  2232,  2232,  2242,  2242,  2252,  2253,  2254,  2259,  2260,
    2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,
    2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,  2280,
    2281,  2282,  2285,  2285,  2294,  2300,  2300,  2325,  2325,  2355,
    2355,  2366,  2367,  2370,  2371,  2372,  2377,  2377,  2386,  2386,
    2395,  2396,  2399,  2400,  2401,  2407,  2408,  2409,  2410,  2411,
    2412,  2413,  2414,  2415,  2416,  2417,  2418,  2419,  2420,  2421,
    2424,  2424,  2433,  2433,  2442,  2442,  2451,  2451,  2460,  2460,
    2469,  2469,  2478,  2478,  2487,  2487,  2496,  2496,  2505,  2505,
    2514,  2514,  2528,  2528,  2539,  2542,  2542,  2556,  2556,  2567,
    2568,  2571,  2572,  2573,  2578,  2578,  2588,  2589,  2592,  2593,
    2594,  2599,  2600,  2601,  2602,  2603,  2604,  2605,  2606,  2607,
    2608,  2609,  2610,  2611,  2612,  2613,  2614,  2615,  2618,  2620,
    2620,  2629,  2629,  2639,  2645,  2653,  2661,  2661,  2673,  2673,
    2685,  2686,  2689,  2690,  2691,  2696,  2696,  2704,  2705,  2706,
    2711,  2712,  2713,  2714,  2715,  2716,  2717,  2718,  2719,  2720,
    2721,  2722,  2723,  2726,  2726,  2735,  2736,  2737,  2740,  2740,
    2749,  2749,  2758,  2764,  2770,  2770,  2781,  2782,  2785,  2786,
    2787,  2792,  2792,  2800,  2801,  2802,  2807,  2808,  2809,  2810,
    2811,  2814,  2814,  2825,  2825,  2838,  2839,  2840,  2845,  2846,
    2847,  2848,  2849,  2850,  2851,  2854,  2854,  2862,  2865,  2865,
    2874,  2874,  2883,  2883,  2894,  2895,  2898,  2899,  2900,  2905,
    2905,  2913,  2914,  2915,  2920,  2921,  2922,  2923,  2924,  2925,
    2926,  2929,  2929,  2940,  2940,  2953,  2954,  2955,  2960,  2961,
    2962,  2963,  2964,  2965,  2968,  2974,  2974,  2983,  2989,  2989,
    2999,  2999,  3012,  3012,  3022,  3023,  3024,  3029,  3030,  3031,
    3032,  3033,  3034,  3035,  3036,  3037,  3038,  3039,  3042,  3048,
    3048,  3057,  3063,  3063,  3072,  3078,  3084,  3084,  3093,  3094,
    3097,  3097,  3108,  3108,  3120,  3120,  3130,  3131,  3132,  3138,
    3139,  3142,  3142,  3153,  3161,  3161,  3174,  3175,  3176,  3182,
    3182,  3190,  3191,  3192,  3197,  3198,  3199,  3200,  3201,  3202,
    3203,  3206,  3212,  3212,  3221,  3221,  3232,  3233,  3234,  3239,
    3239,  3247,  3248,  3249,  3254,  3255,  3256,  3257,  3258,  3261,
    3261,  3270,  3276,  3282,  3288,  3288,  3297,  3297,  3308,  3309,
    3310,  3315,  3316,  3317,  3318,  3319,  3322,  3328,  3334,  3340
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
#line 7009 "dhcp4_parser.cc"

#line 3346 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
