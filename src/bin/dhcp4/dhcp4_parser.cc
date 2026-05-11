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

  case 730: // not_empty_classes_list: not_empty_classes_list ","
#line 2563 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4031 "dhcp4_parser.cc"
    break;

  case 731: // $@109: %empty
#line 2568 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 732: // client_class_entry: "{" $@109 client_class_params "}"
#line 2572 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 737: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2584 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4059 "dhcp4_parser.cc"
    break;

  case 756: // $@110: %empty
#line 2610 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4068 "dhcp4_parser.cc"
    break;

  case 757: // client_class_test: "test" $@110 ":" "constant string"
#line 2613 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4078 "dhcp4_parser.cc"
    break;

  case 758: // $@111: %empty
#line 2619 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 759: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2622 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 760: // only_if_required: "only-if-required" ":" "boolean"
#line 2629 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4107 "dhcp4_parser.cc"
    break;

  case 761: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2635 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4117 "dhcp4_parser.cc"
    break;

  case 762: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2643 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4127 "dhcp4_parser.cc"
    break;

  case 763: // $@112: %empty
#line 2651 "dhcp4_parser.yy"
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

  case 764: // control_socket: "control-socket" $@112 ":" "{" control_socket_params "}"
#line 2658 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4149 "dhcp4_parser.cc"
    break;

  case 765: // $@113: %empty
#line 2663 "dhcp4_parser.yy"
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

  case 766: // control_sockets: "control-sockets" $@113 ":" "[" control_socket_list "]"
#line 2670 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 771: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2681 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4179 "dhcp4_parser.cc"
    break;

  case 772: // $@114: %empty
#line 2686 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4189 "dhcp4_parser.cc"
    break;

  case 773: // control_socket_entry: "{" $@114 control_socket_params "}"
#line 2690 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 776: // control_socket_params: control_socket_params ","
#line 2696 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4205 "dhcp4_parser.cc"
    break;

  case 790: // $@115: %empty
#line 2716 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4214 "dhcp4_parser.cc"
    break;

  case 791: // control_socket_type: "socket-type" $@115 ":" control_socket_type_value
#line 2719 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4223 "dhcp4_parser.cc"
    break;

  case 792: // control_socket_type_value: "unix"
#line 2725 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4229 "dhcp4_parser.cc"
    break;

  case 793: // control_socket_type_value: "http"
#line 2726 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4235 "dhcp4_parser.cc"
    break;

  case 794: // control_socket_type_value: "https"
#line 2727 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4241 "dhcp4_parser.cc"
    break;

  case 795: // $@116: %empty
#line 2730 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4250 "dhcp4_parser.cc"
    break;

  case 796: // control_socket_name: "socket-name" $@116 ":" "constant string"
#line 2733 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4260 "dhcp4_parser.cc"
    break;

  case 797: // $@117: %empty
#line 2739 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4269 "dhcp4_parser.cc"
    break;

  case 798: // control_socket_address: "socket-address" $@117 ":" "constant string"
#line 2742 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4279 "dhcp4_parser.cc"
    break;

  case 799: // control_socket_port: "socket-port" ":" "integer"
#line 2748 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4289 "dhcp4_parser.cc"
    break;

  case 800: // cert_required: "cert-required" ":" "boolean"
#line 2754 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4299 "dhcp4_parser.cc"
    break;

  case 801: // $@118: %empty
#line 2760 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4311 "dhcp4_parser.cc"
    break;

  case 802: // http_headers: "http-headers" $@118 ":" "[" http_header_list "]"
#line 2766 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4320 "dhcp4_parser.cc"
    break;

  case 807: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2777 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4328 "dhcp4_parser.cc"
    break;

  case 808: // $@119: %empty
#line 2782 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 809: // http_header: "{" $@119 http_header_params "}"
#line 2786 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4346 "dhcp4_parser.cc"
    break;

  case 812: // http_header_params: http_header_params ","
#line 2792 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4354 "dhcp4_parser.cc"
    break;

  case 818: // $@120: %empty
#line 2804 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4363 "dhcp4_parser.cc"
    break;

  case 819: // header_value: "value" $@120 ":" "constant string"
#line 2807 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4373 "dhcp4_parser.cc"
    break;

  case 820: // $@121: %empty
#line 2815 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4385 "dhcp4_parser.cc"
    break;

  case 821: // authentication: "authentication" $@121 ":" "{" auth_params "}"
#line 2821 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4396 "dhcp4_parser.cc"
    break;

  case 824: // auth_params: auth_params ","
#line 2830 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4404 "dhcp4_parser.cc"
    break;

  case 832: // $@122: %empty
#line 2844 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4413 "dhcp4_parser.cc"
    break;

  case 833: // auth_type: "type" $@122 ":" auth_type_value
#line 2847 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 834: // auth_type_value: "basic"
#line 2852 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4428 "dhcp4_parser.cc"
    break;

  case 835: // $@123: %empty
#line 2855 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4437 "dhcp4_parser.cc"
    break;

  case 836: // realm: "realm" $@123 ":" "constant string"
#line 2858 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4447 "dhcp4_parser.cc"
    break;

  case 837: // $@124: %empty
#line 2864 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4456 "dhcp4_parser.cc"
    break;

  case 838: // directory: "directory" $@124 ":" "constant string"
#line 2867 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4466 "dhcp4_parser.cc"
    break;

  case 839: // $@125: %empty
#line 2873 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4478 "dhcp4_parser.cc"
    break;

  case 840: // clients: "clients" $@125 ":" "[" clients_list "]"
#line 2879 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4487 "dhcp4_parser.cc"
    break;

  case 845: // not_empty_clients_list: not_empty_clients_list ","
#line 2890 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4495 "dhcp4_parser.cc"
    break;

  case 846: // $@126: %empty
#line 2895 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 847: // basic_auth: "{" $@126 clients_params "}"
#line 2899 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4513 "dhcp4_parser.cc"
    break;

  case 850: // clients_params: clients_params ","
#line 2905 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4521 "dhcp4_parser.cc"
    break;

  case 858: // $@127: %empty
#line 2919 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4530 "dhcp4_parser.cc"
    break;

  case 859: // user_file: "user-file" $@127 ":" "constant string"
#line 2922 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4540 "dhcp4_parser.cc"
    break;

  case 860: // $@128: %empty
#line 2928 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4549 "dhcp4_parser.cc"
    break;

  case 861: // password_file: "password-file" $@128 ":" "constant string"
#line 2931 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 862: // $@129: %empty
#line 2939 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4571 "dhcp4_parser.cc"
    break;

  case 863: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2945 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4582 "dhcp4_parser.cc"
    break;

  case 866: // queue_control_params: queue_control_params ","
#line 2954 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4590 "dhcp4_parser.cc"
    break;

  case 873: // enable_queue: "enable-queue" ":" "boolean"
#line 2967 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4600 "dhcp4_parser.cc"
    break;

  case 874: // $@130: %empty
#line 2973 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4609 "dhcp4_parser.cc"
    break;

  case 875: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2976 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4619 "dhcp4_parser.cc"
    break;

  case 876: // capacity: "capacity" ":" "integer"
#line 2982 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4629 "dhcp4_parser.cc"
    break;

  case 877: // $@131: %empty
#line 2988 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4638 "dhcp4_parser.cc"
    break;

  case 878: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2991 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 879: // $@132: %empty
#line 2998 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4659 "dhcp4_parser.cc"
    break;

  case 880: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 3004 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4670 "dhcp4_parser.cc"
    break;

  case 881: // $@133: %empty
#line 3011 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4680 "dhcp4_parser.cc"
    break;

  case 882: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 3015 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4690 "dhcp4_parser.cc"
    break;

  case 885: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3023 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4698 "dhcp4_parser.cc"
    break;

  case 897: // enable_updates: "enable-updates" ":" "boolean"
#line 3041 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 898: // $@134: %empty
#line 3047 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4717 "dhcp4_parser.cc"
    break;

  case 899: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3050 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4727 "dhcp4_parser.cc"
    break;

  case 900: // server_port: "server-port" ":" "integer"
#line 3056 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4737 "dhcp4_parser.cc"
    break;

  case 901: // $@135: %empty
#line 3062 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4746 "dhcp4_parser.cc"
    break;

  case 902: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3065 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4756 "dhcp4_parser.cc"
    break;

  case 903: // sender_port: "sender-port" ":" "integer"
#line 3071 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4766 "dhcp4_parser.cc"
    break;

  case 904: // max_queue_size: "max-queue-size" ":" "integer"
#line 3077 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4776 "dhcp4_parser.cc"
    break;

  case 905: // $@136: %empty
#line 3083 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4785 "dhcp4_parser.cc"
    break;

  case 906: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3086 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4794 "dhcp4_parser.cc"
    break;

  case 907: // ncr_protocol_value: "udp"
#line 3092 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4800 "dhcp4_parser.cc"
    break;

  case 908: // ncr_protocol_value: "tcp"
#line 3093 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4806 "dhcp4_parser.cc"
    break;

  case 909: // $@137: %empty
#line 3096 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4815 "dhcp4_parser.cc"
    break;

  case 910: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3099 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4825 "dhcp4_parser.cc"
    break;

  case 911: // $@138: %empty
#line 3107 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4837 "dhcp4_parser.cc"
    break;

  case 912: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3113 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4847 "dhcp4_parser.cc"
    break;

  case 913: // $@139: %empty
#line 3119 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4857 "dhcp4_parser.cc"
    break;

  case 914: // sub_config_control: "{" $@139 config_control_params "}"
#line 3123 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4866 "dhcp4_parser.cc"
    break;

  case 917: // config_control_params: config_control_params ","
#line 3131 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4874 "dhcp4_parser.cc"
    break;

  case 920: // $@140: %empty
#line 3141 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4886 "dhcp4_parser.cc"
    break;

  case 921: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3147 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4895 "dhcp4_parser.cc"
    break;

  case 922: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3152 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4905 "dhcp4_parser.cc"
    break;

  case 923: // $@141: %empty
#line 3160 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4917 "dhcp4_parser.cc"
    break;

  case 924: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3166 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4926 "dhcp4_parser.cc"
    break;

  case 927: // loggers_entries: loggers_entries ","
#line 3175 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4934 "dhcp4_parser.cc"
    break;

  case 928: // $@142: %empty
#line 3181 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4944 "dhcp4_parser.cc"
    break;

  case 929: // logger_entry: "{" $@142 logger_params "}"
#line 3185 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4952 "dhcp4_parser.cc"
    break;

  case 932: // logger_params: logger_params ","
#line 3191 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4960 "dhcp4_parser.cc"
    break;

  case 940: // debuglevel: "debuglevel" ":" "integer"
#line 3205 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4970 "dhcp4_parser.cc"
    break;

  case 941: // $@143: %empty
#line 3211 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4979 "dhcp4_parser.cc"
    break;

  case 942: // severity: "severity" $@143 ":" "constant string"
#line 3214 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4989 "dhcp4_parser.cc"
    break;

  case 943: // $@144: %empty
#line 3220 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5001 "dhcp4_parser.cc"
    break;

  case 944: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3226 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5010 "dhcp4_parser.cc"
    break;

  case 947: // output_options_list_content: output_options_list_content ","
#line 3233 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5018 "dhcp4_parser.cc"
    break;

  case 948: // $@145: %empty
#line 3238 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5028 "dhcp4_parser.cc"
    break;

  case 949: // output_entry: "{" $@145 output_params_list "}"
#line 3242 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5036 "dhcp4_parser.cc"
    break;

  case 952: // output_params_list: output_params_list ","
#line 3248 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5044 "dhcp4_parser.cc"
    break;

  case 958: // $@146: %empty
#line 3260 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5053 "dhcp4_parser.cc"
    break;

  case 959: // output: "output" $@146 ":" "constant string"
#line 3263 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5063 "dhcp4_parser.cc"
    break;

  case 960: // flush: "flush" ":" "boolean"
#line 3269 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5073 "dhcp4_parser.cc"
    break;

  case 961: // maxsize: "maxsize" ":" "integer"
#line 3275 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5083 "dhcp4_parser.cc"
    break;

  case 962: // maxver: "maxver" ":" "integer"
#line 3281 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5093 "dhcp4_parser.cc"
    break;

  case 963: // $@147: %empty
#line 3287 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5102 "dhcp4_parser.cc"
    break;

  case 964: // pattern: "pattern" $@147 ":" "constant string"
#line 3290 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5112 "dhcp4_parser.cc"
    break;

  case 965: // $@148: %empty
#line 3296 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5124 "dhcp4_parser.cc"
    break;

  case 966: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3302 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5133 "dhcp4_parser.cc"
    break;

  case 969: // compatibility_params: compatibility_params ","
#line 3309 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5141 "dhcp4_parser.cc"
    break;

  case 975: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3321 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5151 "dhcp4_parser.cc"
    break;

  case 976: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3327 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5161 "dhcp4_parser.cc"
    break;

  case 977: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3333 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5171 "dhcp4_parser.cc"
    break;

  case 978: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3339 "dhcp4_parser.yy"
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


  const short Dhcp4Parser::yypact_ninf_ = -1397;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     470, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,    67,    37,    44,    46,    54,    71,
      83,    88,   109,   111,   161,   168,   173,   176, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,    37,  -138,   103,   276,    82,   727,
    1477,    98,   100,   343,   367,  -118,   544,   287, -1397,   187,
     193,   204,   213,   209, -1397,    25, -1397, -1397, -1397, -1397,
     226,   251,   257, -1397, -1397, -1397,   260,   263, -1397, -1397,
   -1397,   267,   275,   285,   293,   316,   330,   334,   376,   390,
     391,   392,   398, -1397,   399,   400,   428,   429,   430, -1397,
   -1397, -1397,   432,   433,   436,   437,   438,   441,   442, -1397,
   -1397, -1397,   444, -1397, -1397, -1397, -1397, -1397,   447,   448,
     449, -1397, -1397, -1397, -1397, -1397,   457, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,   459,   460,   461, -1397, -1397,   465,
   -1397,    57, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   474,   476,
     483,   484, -1397,    60, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
     485, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   106, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397,   486, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,   144, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397,   245,   341, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397,   405, -1397, -1397,   490,
   -1397, -1397, -1397,   492, -1397, -1397,   415,   495, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397,   497,   499,   501, -1397, -1397, -1397, -1397, -1397,   491,
     503, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397,   151, -1397, -1397, -1397,   505,
   -1397,   506, -1397,   507,   510, -1397, -1397, -1397, -1397, -1397,
     154, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397,   511,   169, -1397, -1397, -1397, -1397,    37,    37, -1397,
     280,   515, -1397, -1397,   517,   519,   520,   286,   290,   296,
     529,   533,   535,   269,   300,   538,   540,   541,   312,   314,
     317,   319,   324,   326,   315,   320,   325,   332,   333,   336,
     552,   344,   345,   331,   339,   346,   577,   580,   581,   347,
     349,   353,   356,   358,   359,   360,   594,   595,   598,   368,
     603,   605,   606,   608,   610,   378,   381,   382,   621,   623,
     627,   628,   631,   404,   633,   644,   646,   649,   651,   652,
     654,   423,   426,   431,   669,   670, -1397,   276, -1397,   672,
     673,   674,   439,   440,   443,   445,    82, -1397,   678,   681,
     683,   684,   685,   686,   454,   703,   704,   706,   707,   708,
     727, -1397,   709,   477,  1477, -1397,   710,   712,   713,   714,
     715,   716,   722,   723, -1397,    98, -1397,   724,   726,   493,
     728,   729,   730,   509, -1397,   343,   739,   512,   513,   514,
     742, -1397,   367,   746,   747,   -84, -1397,   523,   751,   526,
     761,   528,   531,   763,   766,   544, -1397,   767,   539,   287,
   -1397, -1397, -1397,   772,   771,   773,   777,   778, -1397, -1397,
   -1397,   542,   549,   550, -1397, -1397,   781,   782,   785, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397,   556, -1397, -1397, -1397, -1397, -1397,    32,   559,   571,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,   804,   805,   806,
   -1397,   588,   340,   824,   825,   596, -1397, -1397, -1397,   826,
     829,   830,   832,   831, -1397,   833,   834,   839,   840,   841,
     602,   609, -1397, -1397, -1397,   845,   852, -1397,   858,   147,
     184, -1397, -1397, -1397, -1397, -1397,   629,   634,   635,   859,
     636,   637, -1397,   858,   858,   858,   638,   861, -1397,   639,
   -1397, -1397,   858,   656,   657,   658,   671,   675,   676,   677,
   -1397,   679,   680, -1397,   682,   687,   688, -1397, -1397,   689,
   -1397, -1397, -1397,   858, -1397,   690,   825, -1397, -1397,   691,
   -1397,   692, -1397, -1397,     4,   645, -1397,   860, -1397, -1397,
      37,   276,   287,    82,   309, -1397, -1397, -1397,   838,   838,
     863, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
     902,   903,   904, -1397, -1397, -1397, -1397, -1397, -1397,   908,
   -1397, -1397, -1397,   139,   911,   913,   914,   172,    45,   599,
     915,    61,   544, -1397, -1397,   916,  -129, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   923, -1397,
   -1397, -1397, -1397, -1397, -1397,   780, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
     863, -1397,   179,   189,   192, -1397, -1397,   217, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397,   930,   931,   932,   933,   934,
     935,   936,   937,   939,   940, -1397,   941,   942, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   221,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,   229, -1397,   943,   944, -1397, -1397,
     945,   947, -1397, -1397,   946,   950, -1397, -1397,   948,   952,
   -1397, -1397,   951,   953, -1397, -1397, -1397, -1397, -1397, -1397,
      42, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   954,   955,
   -1397, -1397,   956,   958, -1397, -1397,   957,   962, -1397,   963,
     964,   965,   966,   967,   968,   248, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397,   969,   970,   971, -1397,   249, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,   972, -1397,   973,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,   262, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,   960,   975, -1397,
     976, -1397,   977, -1397, -1397, -1397,   270, -1397, -1397, -1397,
   -1397, -1397,   288, -1397,   121, -1397,   978,   979,   980,   981,
   -1397,   318, -1397, -1397, -1397, -1397, -1397,   711, -1397,   982,
     983, -1397, -1397,   984, -1397,   985, -1397, -1397, -1397,   986,
     989,   309, -1397,   990,   991,   992,   993,   721,   749,   741,
     758,   762,   764,   765,   768,   770,   774,   995,   769,   788,
     997,  1001,  1012,  1015,  1016,   838, -1397, -1397,   838, -1397,
     863,   727, -1397,   902,   343, -1397,   903,   367, -1397,   904,
    1419, -1397,   908,   139, -1397,   156, -1397,   911,    98, -1397,
     913,  -118, -1397,   914,   790,   791,   793,   796,   797,   808,
     172, -1397,   802,   814,   817,    45, -1397,  1053,  1056,  1061,
     851,  1064,   850,  1065,   599, -1397,   599, -1397,   915,   857,
    1088,   867,  1094,    61, -1397, -1397,    90,   916, -1397,   870,
     875,   892,   898,  -129, -1397, -1397,  1093,  1104,  1477, -1397,
     923,  1138, -1397, -1397,   750,   959, -1397,   961,   974,   987,
     988, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397,   183, -1397, -1397,   994,   996,   998,   321,   999, -1397,
     373, -1397,   374, -1397,  1140, -1397,  1145, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
     407, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397,  1166,  1176, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,  1180,  1190,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,  1191, -1397,   408,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397,   152,  1000,  1002, -1397,  1193, -1397,  1196, -1397,
     409, -1397, -1397,  1003, -1397,    37, -1397, -1397,  1199, -1397,
   -1397, -1397, -1397, -1397,   411, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397,  1004,   417, -1397,   858,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,  1419,
   -1397,  1201,  1202,  1005,  1006, -1397,   156, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397,   138,  1203, -1397, -1397, -1397,
    1204,  1009,  1205,    90, -1397, -1397, -1397, -1397, -1397,  1007,
    1011, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397,   418, -1397, -1397, -1397, -1397, -1397, -1397,  1207,  1212,
   -1397,  1211, -1397,  1013, -1397, -1397, -1397,  1214,  1216,  1217,
    1218,   138, -1397,   -70, -1397,  1203,  1220, -1397,  1046,  1014,
    1017,  1223, -1397, -1397, -1397, -1397, -1397, -1397,   419, -1397,
   -1397, -1397, -1397,   134, -1397, -1397, -1397, -1397, -1397,  1222,
    1226,   -70, -1397,     1,  1220, -1397, -1397,  1228,  1229, -1397,
    1018, -1397, -1397,  1234,  1238,  1239, -1397,   421, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397,    17, -1397,  1222, -1397,  1245,
    1019,  1020,  1022,  1248,     1, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397,   427, -1397, -1397, -1397, -1397,  1024, -1397,
   -1397, -1397,  1026, -1397,  1249,  1252,    17, -1397, -1397, -1397,
    1027,  1028, -1397, -1397, -1397
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
     881,    25,   913,    27,    46,    39,     0,     0,     0,     0,
       0,   677,     0,   556,   595,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   911,   201,   234,
       0,     0,     0,   697,   699,   701,     0,     0,   232,   245,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,     0,   166,
     173,   175,     0,     0,     0,     0,     0,     0,     0,   392,
     543,   584,     0,   158,   179,   482,   662,   664,     0,     0,
       0,   325,   724,   666,   354,   375,     0,   340,   763,   765,
     862,   879,   189,   191,     0,     0,     0,   923,   965,     0,
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
     898,     0,   901,     0,     0,   905,   909,   896,   894,   895,
       0,   883,   886,   887,   888,   889,   890,   891,   892,   893,
     920,     0,     0,   915,   918,   919,    45,    50,     0,    37,
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
       0,     0,     0,     0,     0,   885,   882,     0,     0,   917,
     914,    49,    41,     0,     0,     0,     0,     0,   160,   161,
     162,     0,     0,     0,   199,   200,     0,     0,     0,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,   194,   195,   163,   164,   165,     0,     0,     0,
     177,   178,   185,   186,   187,   188,   193,     0,     0,     0,
     157,     0,     0,     0,     0,     0,   478,   479,   480,     0,
       0,     0,     0,     0,   762,     0,     0,     0,     0,     0,
       0,     0,   196,   197,   198,     0,     0,    68,     0,     0,
       0,   228,   229,   230,   231,   204,     0,     0,     0,     0,
       0,     0,   481,     0,     0,     0,     0,     0,   404,     0,
     661,   633,     0,     0,     0,     0,     0,     0,     0,     0,
     680,     0,     0,   572,     0,     0,     0,   583,   559,     0,
     616,   617,   618,     0,   598,     0,     0,   366,   897,     0,
     900,     0,   903,   904,     0,     0,   884,     0,   922,   916,
       0,     0,     0,     0,     0,   698,   700,   702,     0,     0,
     249,   156,   168,   169,   170,   171,   172,   167,   174,   176,
     394,   547,   586,   159,   181,   182,   183,   184,   180,   484,
      38,   663,   665,     0,   726,   668,   356,     0,     0,     0,
     767,     0,     0,   190,   192,     0,     0,    51,   219,   222,
     223,   221,   226,   227,   225,   463,   465,   467,   623,   461,
     469,   473,   475,   477,   471,     0,   660,   718,   704,   706,
     708,   712,   710,   716,   714,   575,   293,   579,   577,   582,
     613,   620,   372,   374,   899,   902,   907,   908,   906,   910,
     249,    42,     0,     0,     0,   241,   243,     0,   236,   239,
     240,   283,   285,   287,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   303,     0,     0,   310,   312,
     314,   316,   318,   319,   320,   321,   322,   323,   282,     0,
     256,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,     0,   254,     0,   250,   251,   399,
       0,   395,   396,   552,     0,   548,   549,   591,     0,   587,
     588,   489,     0,   485,   486,   335,   336,   337,   338,   339,
       0,   327,   330,   331,   332,   333,   334,   731,     0,   727,
     728,   673,     0,   669,   670,   361,     0,   357,   358,     0,
       0,     0,     0,     0,     0,     0,   377,   380,   381,   382,
     383,   384,   385,     0,     0,     0,   350,     0,   342,   345,
     346,   347,   348,   349,   790,   795,   797,     0,   820,     0,
     801,   789,   782,   783,   784,   787,   788,     0,   774,   777,
     778,   779,   780,   785,   786,   781,   772,     0,   768,   769,
       0,   874,     0,   877,   870,   871,     0,   864,   867,   868,
     869,   872,     0,   928,     0,   925,     0,     0,     0,     0,
     974,     0,   967,   970,   971,   972,   973,    53,   628,     0,
     624,   625,   722,     0,   721,     0,    62,   912,   202,     0,
       0,   238,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   258,   233,   246,     0,   248,
     253,     0,   393,   398,   556,   544,   551,   595,   585,   590,
       0,   483,   488,   329,   326,   733,   725,   730,   677,   667,
     672,     0,   355,   360,     0,     0,     0,     0,     0,     0,
     379,   376,     0,     0,     0,   344,   341,     0,     0,     0,
       0,     0,     0,     0,   776,   764,     0,   766,   771,     0,
       0,     0,     0,   866,   863,   880,     0,   927,   924,     0,
       0,     0,     0,   969,   966,    55,     0,    54,     0,   622,
     627,     0,   720,   921,     0,     0,   237,     0,     0,     0,
       0,   291,   294,   295,   296,   297,   298,   299,   300,   301,
     302,     0,   308,   309,     0,     0,     0,     0,     0,   257,
       0,   252,     0,   397,     0,   550,     0,   589,   542,   513,
     514,   515,   497,   498,   518,   519,   520,   521,   522,   523,
     540,   500,   501,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   541,
     494,   495,   496,   509,   510,   511,   512,   506,   507,   508,
       0,   491,   499,   516,   517,   502,   503,   504,   505,   487,
     328,   756,   758,     0,     0,   750,   751,   752,   753,   754,
     755,   743,   744,   748,   749,   745,   746,   747,     0,   734,
     735,   738,   739,   740,   741,   742,   729,     0,   671,     0,
     359,   386,   387,   388,   389,   390,   391,   378,   351,   352,
     353,   343,     0,     0,     0,   799,     0,   800,     0,   775,
       0,   770,   873,     0,   876,     0,   865,   943,     0,   941,
     939,   933,   937,   938,     0,   930,   935,   936,   934,   926,
     975,   976,   977,   978,   968,    52,    57,     0,   626,     0,
     242,   244,   284,   286,   288,   290,   305,   306,   307,   304,
     311,   313,   315,   317,   324,   255,   400,   553,   592,   493,
     490,     0,     0,     0,     0,   732,   737,   674,   362,   792,
     793,   794,   791,   796,   798,     0,   803,   773,   875,   878,
       0,     0,     0,   932,   929,    56,   629,   723,   492,     0,
       0,   760,   761,   736,   832,   835,   837,   839,   831,   830,
     829,     0,   822,   825,   826,   827,   828,   808,     0,   804,
     805,     0,   940,     0,   931,   757,   759,     0,     0,     0,
       0,   824,   821,     0,   802,   807,     0,   942,     0,     0,
       0,     0,   823,   818,   817,   813,   815,   816,     0,   810,
     814,   806,   948,     0,   945,   834,   833,   836,   838,   841,
       0,   812,   809,     0,   947,   944,   846,     0,   842,   843,
       0,   811,   958,     0,     0,     0,   963,     0,   950,   953,
     954,   955,   956,   957,   946,     0,   840,   845,   819,     0,
       0,     0,     0,     0,   952,   949,   858,   860,   857,   851,
     853,   855,   856,     0,   848,   852,   854,   844,     0,   960,
     961,   962,     0,   951,     0,     0,   850,   847,   959,   964,
       0,     0,   849,   859,   861
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397,   -59, -1397,  -633, -1397,   521,
   -1397, -1397, -1397, -1397, -1397, -1397,  -616, -1397, -1397, -1397,
     -67, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   516,   731,
      16,    31,    33,   -26,    84,    86,    87,    89,    91,    92,
      94, -1397, -1397, -1397, -1397,    97, -1397, -1397,   102,   104,
     -13,    13,    41,    51, -1397, -1397,    53, -1397,    56, -1397,
      59,   105,    64, -1397, -1397,    66,    69,    74,    76,    79,
   -1397,    81, -1397,   107, -1397, -1397, -1397, -1397, -1397,    43,
   -1397, -1397, -1397,   518,   733, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,   231, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397,   434, -1397,   200, -1397,  -743,   210, -1397,
   -1397, -1396, -1397, -1395, -1397, -1397, -1397, -1397,   -63, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,  -775, -1397,  -774, -1397,  -771, -1397,
     113, -1397, -1397, -1397, -1397, -1397, -1397,   194, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397,   177, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397,   190, -1397, -1397, -1397,   196,   694,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,   191, -1397, -1397,
   -1397, -1397, -1397, -1397, -1063, -1397, -1397, -1397,   211, -1397,
   -1397, -1397,   222,   734, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1061, -1397,   -29, -1397,   -18, -1397,    -4, -1397,
       5, -1397,   110,   112,   115, -1397, -1397, -1397, -1397, -1397,
     214, -1397, -1397,   -31,   -60, -1397, -1397, -1397, -1397, -1397,
     219, -1397, -1397, -1397,   225, -1397,   717, -1397,   -34, -1397,
   -1397, -1397, -1397, -1397,   -27, -1397, -1397, -1397, -1397, -1397,
     -32, -1397, -1397, -1397,   227, -1397, -1397, -1397,   228, -1397,
     718, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397,   167, -1397, -1397, -1397,   170,
     748, -1397, -1397, -1397,   -44, -1397,     3, -1397,   -56, -1397,
   -1397, -1397,   223, -1397, -1397, -1397,   230, -1397,   740,   -48,
   -1397,    -7, -1397,    15, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1060, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
     232, -1397, -1397, -1397,   -22, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   199,
   -1397,   205,   206, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397,   -72, -1397, -1397,   -94,
   -1397, -1397, -1397, -1397, -1397,   -58, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397,  -119, -1397, -1397,
    -145, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   212, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   545,
     735, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,   584,   732,
   -1397, -1397, -1397, -1397, -1397, -1397,   216, -1397, -1397,   -15,
   -1397, -1397, -1397, -1397, -1397, -1397,   -78, -1397, -1397,  -104,
   -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397, -1397,
     220, -1397, -1397, -1397, -1397
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   781,
      82,    83,    39,    64,    79,    80,   798,  1027,  1136,  1137,
     878,    41,    66,    85,   461,    86,    43,    67,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   490,   176,   177,   510,   178,   179,   180,
     181,   182,   183,   184,   496,   767,   185,   497,   186,   498,
     187,   188,   189,   511,   778,   190,   191,   192,   193,   194,
     529,   195,   530,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   465,   243,   244,    45,    68,   245,   539,   246,
     540,   801,   247,   541,   804,   248,   249,   250,   251,   205,
     475,   206,   466,   847,   848,   849,  1039,   850,  1040,   207,
     476,   208,   477,   906,   907,   908,  1068,   879,   880,   881,
    1043,   882,  1044,   883,  1045,   884,  1046,   885,   886,   578,
     887,   888,   889,   890,   891,   892,   893,   894,   895,   896,
    1057,  1319,   897,   898,   899,  1060,   900,  1061,   901,  1062,
     902,  1063,   903,  1064,   209,   518,   930,   931,   932,   933,
     934,   935,   936,   210,   524,   967,   968,   969,   970,   971,
     211,   521,   946,   947,   948,  1091,    59,    75,   425,   426,
     427,   593,   428,   594,   212,   522,   955,   956,   957,   958,
     959,   960,   961,   962,   213,   506,   910,   911,   912,  1071,
      47,    69,   298,   299,   300,   552,   301,   548,   302,   549,
     303,   550,   304,   553,   305,   558,   306,   555,   307,   556,
     308,   557,   214,   215,   216,   312,   217,   512,   922,   923,
     924,  1080,  1220,  1221,   218,   507,    53,    72,   914,   915,
     916,  1074,    55,    73,   386,   387,   388,   389,   390,   391,
     392,   577,   393,   581,   394,   580,   395,   396,   582,   397,
     219,   508,   918,   919,   920,  1077,    57,    74,   409,   410,
     411,   412,   413,   586,   414,   415,   416,   417,   418,   419,
     590,   314,   551,  1029,  1030,  1031,  1138,    49,    70,   344,
     345,   346,   562,   347,   220,   513,   221,   514,   222,   520,
     942,   943,   944,  1088,    51,    71,   362,   363,   364,   223,
     470,   224,   471,   225,   472,   368,   567,   369,   568,   370,
     569,   371,   571,   372,   570,   373,   573,   374,   572,   375,
     566,   321,   559,  1033,  1034,  1141,   226,   519,   938,   939,
     940,  1085,  1248,  1249,  1250,  1251,  1252,  1331,  1253,  1332,
    1254,  1255,   227,   228,   525,   229,   526,   997,   998,   999,
    1116,   987,   988,   989,  1107,  1342,   990,  1108,   991,  1109,
     992,   993,   994,  1113,  1378,  1379,  1380,  1393,  1408,  1409,
    1410,  1420,   995,  1111,  1371,  1372,  1373,  1387,  1416,  1374,
    1388,  1375,  1389,  1376,  1390,  1427,  1428,  1429,  1445,  1463,
    1464,  1465,  1474,  1466,  1475,   230,   527,  1006,  1007,  1008,
    1009,  1120,  1010,  1011,  1122,   231,   528,    61,    76,   440,
     441,   442,   443,   598,   444,   445,   600,   446,   447,   448,
     603,   838,   449,   604,   232,   464,    63,    77,   452,   453,
     454,   607,   455,   233,   534,  1014,  1015,  1126,  1294,  1295,
    1296,  1297,  1352,  1298,  1350,  1413,  1414,  1423,  1437,  1438,
    1439,  1449,  1440,  1441,  1442,  1443,  1453,   234,   535,  1021,
    1022,  1023,  1024,  1025,  1026
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     160,   242,   266,   324,   358,    78,   384,   405,   424,   437,
     385,   406,   376,   317,   982,   983,   904,  1211,   984,  1212,
    1228,   318,   836,   365,   252,   315,   348,   360,   462,   398,
     420,   780,   438,   463,   378,   422,   423,   313,   343,   359,
     407,   339,    29,   270,    30,  1083,    31,   408,  1084,  1459,
    1460,    40,   340,    42,   136,   137,   281,   325,   852,   853,
     537,    44,   319,   546,   366,   538,   341,    28,   547,   422,
     423,   253,   316,   349,   361,   342,   399,   421,    46,   439,
    1459,  1460,   282,   326,   320,   267,   367,   811,   812,   813,
      48,  1016,  1017,  1018,  1019,    50,   817,   235,   236,    81,
     268,   237,   269,   780,   238,   239,   240,   241,   159,   560,
     283,   327,   297,    84,   561,  1403,    52,   831,    54,   159,
     284,   328,   285,   329,  1127,   286,   330,  1128,   287,   331,
      93,    94,    95,   289,   332,   290,   333,  1424,   291,   334,
    1425,   136,   137,   292,   335,   293,   336,   564,   294,   337,
     295,   338,   565,   271,   595,   272,   273,   605,   274,   596,
     275,   276,   606,   277,   799,   800,   278,   159,    56,   136,
     137,   279,   609,   280,   288,    58,   296,   610,  1364,   309,
      60,   310,   537,    62,   311,   136,   137,  1036,    93,    94,
      95,    96,   609,   456,   378,   546,   457,  1037,  1456,  1457,
    1038,   131,   130,   837,   802,   803,   136,   137,   458,   963,
     964,   965,   460,  1432,   136,   137,  1433,  1434,  1435,  1436,
    1041,   459,   136,   137,  1065,  1042,   101,   102,   103,  1066,
     467,   350,  1065,   762,   763,   764,   765,  1067,  1316,  1317,
    1318,   351,   352,   353,   354,   355,   356,   357,  1000,  1001,
    1002,  1100,  1105,   574,   159,   468,  1101,  1106,   130,   131,
     378,   469,   136,   137,   473,  1114,  1211,   474,  1212,  1228,
    1115,   478,   766,  1123,    32,    33,    34,    35,  1124,   479,
     136,   137,   159,   925,   926,   927,   928,    87,   929,   480,
      88,   605,  1231,  1232,  1233,  1234,  1125,   481,  1003,   450,
     451,  1287,    89,  1288,  1289,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,  1365,  1366,  1367,   159,
     482,  1133,  1339,  1340,  1341,  1170,  1134,   159,   949,   950,
     951,   952,   953,   954,   483,   159,   845,   846,   484,   982,
     983,   982,   983,   984,   575,   984,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   159,  1065,   560,   130,   131,
     485,  1325,  1326,   377,   871,   872,   873,   874,   875,   876,
     132,   133,   134,   159,   486,   487,   488,   135,   611,   612,
     136,   137,   489,   491,   492,   138,   139,   140,   141,   142,
    1329,   595,  1114,   576,  1353,  1330,  1338,  1347,   143,  1354,
     564,  1391,  1421,   584,  1454,  1356,  1392,  1422,   144,  1455,
    1476,   145,   493,   494,   495,  1477,   499,   500,   146,   147,
     501,   502,   503,   148,   149,   504,   505,   378,   509,   379,
     380,   515,   516,   517,   381,   382,   383,   774,   775,   776,
     777,   523,   150,   531,   532,   533,   151,   136,   137,   536,
     160,   378,   400,   379,   380,   401,   402,   403,   542,   242,
     543,   152,   153,   154,   155,   156,   157,   544,   545,   554,
     563,   136,   137,   266,   579,   158,   583,   324,   585,   591,
     404,   587,   252,   588,   317,   589,   592,   624,   358,   597,
     599,   601,   318,   159,   602,   608,   315,   613,   384,   614,
     348,   615,   385,   616,   617,   405,   618,   365,   313,   406,
     619,   360,   343,   621,   270,   339,   620,   622,   437,   623,
     625,   398,   626,   359,   627,   628,   340,   281,   420,   253,
     629,   325,   630,   319,   635,   631,   641,   632,   407,   636,
     341,   438,   633,   316,   637,   408,   634,   349,   366,   342,
     638,   644,   639,   282,   640,   320,   267,   326,   361,   645,
     159,   647,   642,   643,   648,   649,   646,   650,   399,   651,
     367,   268,   652,   269,   653,   421,   654,   655,   657,   658,
     656,   283,   659,   297,   159,   327,   660,   661,   439,   662,
     663,   284,   664,   285,   665,   328,   286,   329,   666,   287,
     330,   667,   668,   331,   289,   669,   290,   670,   332,   291,
     333,   671,   672,   334,   292,   673,   293,   675,   335,   294,
     336,   295,   674,   337,   271,   338,   272,   273,   676,   274,
     677,   275,   276,   678,   277,   679,   680,   278,   681,   868,
     869,   870,   279,   682,   280,   288,   683,   296,   136,   137,
     309,   684,   310,   685,   686,   311,   688,   689,   690,   691,
     692,   693,   696,   694,   160,   697,   242,   698,   699,   700,
     701,   841,   702,  1357,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   703,   704,   252,
     705,   706,   707,   709,   712,   710,   713,   714,   715,   716,
     717,   966,   981,   136,   137,   437,   718,   719,   721,  1020,
     722,   723,   724,   725,   726,   429,   430,   431,   432,   433,
     434,   435,   436,   729,   972,   985,   733,  1004,   438,   727,
     735,   736,   730,   731,   732,   739,   253,    91,    92,    93,
      94,    95,    96,   738,   740,   741,   742,   744,   974,   743,
     745,   747,   975,   976,   977,   978,   750,   748,   751,   755,
     752,   159,   979,   980,   753,   754,   756,   757,   758,   759,
     760,   973,   986,   761,  1005,   439,   768,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   769,   770,
     771,   772,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   773,   254,   255,   256,   779,
     131,   783,    30,   782,   784,   785,   159,   786,   787,   793,
     788,   789,   133,   134,   790,   839,   794,   791,   792,   257,
     795,   136,   137,   258,   259,   260,   138,   139,   140,   796,
     261,   262,   263,   797,   808,   840,   805,   264,   815,   143,
     905,   806,   807,   809,   810,   814,   816,   265,   851,   852,
     853,   854,   855,   856,   857,   858,   859,   860,   861,   862,
     863,   864,   865,   818,   819,   820,   866,   867,   868,   869,
     870,   871,   872,   873,   874,   875,   876,   877,   821,   909,
     913,   917,   822,   823,   824,   921,   825,   826,   937,   827,
     941,   945,   996,  1013,   828,   829,   830,   832,   834,   835,
    1028,  1032,   152,   153,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,  1054,   378,  1055,  1056,  1058,  1059,  1070,  1135,  1069,
    1073,  1072,  1075,  1076,  1078,  1079,  1082,  1081,  1087,  1151,
    1086,  1090,  1089,  1092,   159,  1093,  1117,  1094,  1095,  1096,
    1097,  1098,  1099,  1102,  1103,  1104,  1110,  1112,  1118,  1153,
    1119,  1121,  1129,  1130,  1131,  1132,  1140,  1310,  1139,  1152,
    1144,  1143,  1142,  1145,  1147,  1148,  1149,  1150,  1154,  1161,
    1155,  1164,  1156,  1157,   266,  1165,  1158,   384,  1159,  1162,
     405,   385,  1160,  1178,   406,   317,  1166,  1210,  1235,  1167,
    1168,   358,  1240,   318,   424,  1241,  1163,   315,  1261,  1262,
     398,  1263,  1225,   420,  1264,  1265,  1223,  1245,   966,   313,
     365,  1243,  1268,   407,   360,   270,  1266,   981,  1222,   981,
     408,  1213,  1269,  1242,  1182,  1270,   359,  1272,   281,  1290,
    1273,   972,  1214,  1291,   319,  1274,  1020,  1193,  1276,  1278,
     985,   324,   985,  1226,   316,   159,  1215,   399,  1246,  1004,
     421,   366,  1292,  1224,   282,  1216,   320,   267,  1244,  1275,
    1277,   361,  1283,  1194,   348,  1227,  1179,  1282,  1285,  1305,
    1247,  1236,   268,   367,   269,  1284,   343,  1306,   973,   339,
    1300,  1180,   283,  1181,   297,  1301,  1237,   986,  1238,   986,
     340,  1195,   284,  1209,   285,   325,  1005,   286,  1239,  1293,
     287,  1196,  1302,  1197,   341,   289,  1198,   290,  1303,  1199,
     291,   349,  1309,   342,  1201,   292,  1202,   293,  1327,  1203,
     294,   326,   295,  1328,  1204,   271,  1205,   272,   273,  1206,
     274,  1207,   275,   276,  1183,   277,  1184,  1185,   278,  1186,
    1333,  1187,  1188,   279,  1189,   280,   288,  1190,   296,   327,
    1334,   309,  1191,   310,  1192,  1200,   311,  1208,  1335,   328,
    1217,   329,  1218,  1336,   330,  1219,  1311,   331,  1312,  1337,
    1345,  1346,   332,  1351,   333,  1359,  1360,   334,  1381,  1383,
    1377,  1313,   335,  1394,   336,  1395,  1396,   337,  1398,   338,
    1399,  1400,  1401,  1415,  1314,  1315,  1349,  1412,  1419,  1426,
    1430,  1320,  1447,  1321,  1446,  1322,  1324,  1343,  1450,  1344,
    1348,  1355,  1451,  1452,  1385,  1361,  1362,  1382,  1386,  1468,
    1397,  1417,  1472,  1480,  1418,  1448,  1481,   833,  1470,  1469,
    1471,  1478,  1178,  1479,  1483,  1484,  1210,   842,   687,  1235,
    1171,   844,  1146,  1240,  1035,  1169,  1241,  1230,  1368,   695,
    1323,  1225,  1271,  1260,  1173,  1223,  1290,  1259,  1245,   737,
    1291,  1267,  1243,  1172,   708,  1175,  1229,  1222,  1358,  1174,
    1213,  1369,   728,  1182,  1242,  1176,  1177,  1308,  1307,  1292,
     734,  1214,   711,  1258,  1363,   720,  1193,  1281,  1257,  1256,
    1279,  1280,  1226,  1411,  1368,  1215,  1404,  1431,  1467,  1246,
    1405,  1482,  1224,  1402,  1216,  1286,   843,  1012,  1384,  1244,
     746,   749,  1194,  1299,  1227,  1179,  1444,  1369,  1370,  1406,
    1473,  1247,  1236,  1304,  1404,     0,  1293,     0,  1405,     0,
    1180,     0,  1181,     0,     0,     0,     0,  1237,     0,  1238,
    1195,     0,  1209,     0,     0,     0,     0,  1406,  1458,  1239,
    1196,     0,  1197,     0,     0,  1198,     0,     0,  1199,     0,
       0,     0,     0,  1201,  1370,  1202,  1407,     0,  1203,     0,
       0,  1461,     0,  1204,     0,  1205,     0,     0,  1206,  1458,
    1207,     0,     0,  1183,     0,  1184,  1185,     0,  1186,     0,
    1187,  1188,     0,  1189,  1407,     0,  1190,     0,     0,     0,
       0,  1191,  1461,  1192,  1200,     0,  1208,     0,     0,  1217,
       0,  1218,     0,     0,  1219,     0,     0,     0,  1462,    91,
      92,    93,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1462,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,     0,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     0,     0,
       0,     0,   131,   378,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,     0,     0,     0,     0,
       0,     0,     0,   136,   137,     0,   259,     0,   138,   139,
     140,     0,   261,   262,   263,     0,     0,     0,     0,   264,
       0,     0,   116,   117,   118,   119,   120,   121,   122,   265,
     124,   125,   126,   127,     0,     0,     0,     0,     0,     0,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
     322,   136,   137,     0,     0,     0,     0,     0,     0,     0,
     261,   262,   263,     0,     0,     0,     0,   264,   323,     0,
       0,     0,     0,     0,   152,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   152,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   789,   789,   759,  1080,   789,  1080,
    1080,    69,    18,    71,    68,    69,    70,    71,     3,    73,
      74,   664,    76,     8,   104,   153,   154,    69,    70,    71,
      74,    70,     5,    69,     7,     3,     9,    74,     6,  1445,
    1445,     7,    70,     7,   124,   125,    69,    70,    41,    42,
       3,     7,    69,     3,    71,     8,    70,     0,     8,   153,
     154,    68,    69,    70,    71,    70,    73,    74,     7,    76,
    1476,  1476,    69,    70,    69,    69,    71,   703,   704,   705,
       7,   220,   221,   222,   223,     7,   712,    15,    16,   237,
      69,    19,    69,   736,    22,    23,    24,    25,   237,     3,
      69,    70,    69,    10,     8,   185,     7,   733,     7,   237,
      69,    70,    69,    70,     3,    69,    70,     6,    69,    70,
      32,    33,    34,    69,    70,    69,    70,     3,    69,    70,
       6,   124,   125,    69,    70,    69,    70,     3,    69,    70,
      69,    70,     8,    69,     3,    69,    69,     3,    69,     8,
      69,    69,     8,    69,    17,    18,    69,   237,     7,   124,
     125,    69,     3,    69,    69,     7,    69,     8,    40,    69,
       7,    69,     3,     7,    69,   124,   125,     8,    32,    33,
      34,    35,     3,     6,   104,     3,     3,     8,   181,   182,
       8,   103,   102,   199,    20,    21,   124,   125,     4,   164,
     165,   166,     3,   212,   124,   125,   215,   216,   217,   218,
       3,     8,   124,   125,     3,     8,    70,    71,    72,     8,
       4,   133,     3,   201,   202,   203,   204,     8,    55,    56,
      57,   143,   144,   145,   146,   147,   148,   149,   187,   188,
     189,     3,     3,     8,   237,     4,     8,     8,   102,   103,
     104,     4,   124,   125,     4,     3,  1329,     4,  1329,  1329,
       8,     4,   240,     3,   237,   238,   239,   240,     8,     4,
     124,   125,   237,   144,   145,   146,   147,    11,   149,     4,
      14,     3,   136,   137,   138,   139,     8,     4,   237,    12,
      13,   211,    26,   213,   214,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,   178,   179,   180,   237,
       4,     3,   170,   171,   172,  1068,     8,   237,   156,   157,
     158,   159,   160,   161,     4,   237,    27,    28,     4,  1114,
    1114,  1116,  1116,  1114,     3,  1116,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   237,     3,     3,   102,   103,
       4,     8,     8,    40,    63,    64,    65,    66,    67,    68,
     114,   115,   116,   237,     4,     4,     4,   121,   457,   458,
     124,   125,     4,     4,     4,   129,   130,   131,   132,   133,
       3,     3,     3,     8,     3,     8,     8,     8,   142,     8,
       3,     3,     3,     8,     3,     8,     8,     8,   152,     8,
       3,   155,     4,     4,     4,     8,     4,     4,   162,   163,
       4,     4,     4,   167,   168,     4,     4,   104,     4,   106,
     107,     4,     4,     4,   111,   112,   113,   117,   118,   119,
     120,     4,   186,     4,     4,     4,   190,   124,   125,     4,
     537,   104,   105,   106,   107,   108,   109,   110,     4,   546,
       4,   205,   206,   207,   208,   209,   210,     4,     4,     4,
       4,   124,   125,   560,     4,   219,     4,   564,     3,     8,
     133,     4,   546,     4,   560,     4,     3,   238,   575,     4,
       4,     4,   560,   237,     4,     4,   560,   237,   585,     4,
     564,     4,   585,     4,     4,   592,   240,   575,   560,   592,
     240,   575,   564,     4,   560,   564,   240,     4,   605,     4,
     240,   585,     4,   575,     4,     4,   564,   560,   592,   546,
     238,   564,   238,   560,   239,   238,     4,   238,   592,   239,
     564,   605,   238,   560,   239,   592,   240,   564,   575,   564,
     238,   240,   239,   560,   238,   560,   560,   564,   575,   240,
     237,     4,   238,   238,     4,     4,   240,   240,   585,   240,
     575,   560,   239,   560,   238,   592,   238,   238,     4,     4,
     240,   560,     4,   560,   237,   564,   238,     4,   605,     4,
       4,   560,     4,   560,     4,   564,   560,   564,   240,   560,
     564,   240,   240,   564,   560,     4,   560,     4,   564,   560,
     564,     4,     4,   564,   560,     4,   560,     4,   564,   560,
     564,   560,   238,   564,   560,   564,   560,   560,     4,   560,
       4,   560,   560,     4,   560,     4,     4,   560,     4,    60,
      61,    62,   560,   240,   560,   560,   240,   560,   124,   125,
     560,   240,   560,     4,     4,   560,     4,     4,     4,   240,
     240,   238,     4,   238,   751,     4,   753,     4,     4,     4,
       4,   750,   238,  1309,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,     4,     4,   753,
       4,     4,     4,     4,     4,   238,     4,     4,     4,     4,
       4,   788,   789,   124,   125,   792,     4,     4,     4,   796,
       4,   238,     4,     4,     4,   191,   192,   193,   194,   195,
     196,   197,   198,     4,   788,   789,     4,   791,   792,   240,
       4,     4,   240,   240,   240,     4,   753,    30,    31,    32,
      33,    34,    35,   240,   238,     4,   238,     4,   169,   238,
       4,     4,   173,   174,   175,   176,     4,   238,     7,   237,
       7,   237,   183,   184,     7,     7,   237,   237,     7,     7,
       5,   788,   789,   237,   791,   792,   237,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   237,     5,
       5,     5,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,   237,    99,   100,   101,     5,
     103,     5,     7,   237,     5,     5,   237,     5,     7,   237,
       7,     7,   115,   116,     5,   200,   237,     7,     7,   122,
       5,   124,   125,   126,   127,   128,   129,   130,   131,     7,
     133,   134,   135,     5,     5,     5,   237,   140,     7,   142,
       7,   237,   237,   237,   237,   237,   237,   150,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,   237,   237,   237,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   237,     7,
       7,     7,   237,   237,   237,     7,   237,   237,     7,   237,
       7,     7,     7,     7,   237,   237,   237,   237,   237,   237,
       7,   151,   205,   206,     4,     4,     4,     4,     4,     4,
       4,     4,   104,     4,     4,     4,     4,     3,   237,     6,
       3,     6,     6,     3,     6,     3,     3,     6,     3,   238,
       6,     3,     6,     6,   237,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   238,
       4,     4,     4,     4,     4,     4,     3,   237,     6,   240,
       4,     6,     8,     4,     4,     4,     4,     4,   240,     4,
     238,     4,   238,   238,  1071,     4,   238,  1074,   238,   240,
    1077,  1074,   238,  1080,  1077,  1071,     4,  1080,  1085,     4,
       4,  1088,  1085,  1071,  1091,  1085,   238,  1071,   238,   238,
    1074,   238,  1080,  1077,   238,   238,  1080,  1085,  1105,  1071,
    1088,  1085,   240,  1077,  1088,  1071,   238,  1114,  1080,  1116,
    1077,  1080,   238,  1085,  1080,   238,  1088,     4,  1071,  1126,
       4,  1105,  1080,  1126,  1071,     4,  1133,  1080,     4,     4,
    1114,  1138,  1116,  1080,  1071,   237,  1080,  1074,  1085,  1123,
    1077,  1088,  1126,  1080,  1071,  1080,  1071,  1071,  1085,   238,
     240,  1088,     4,  1080,  1138,  1080,  1080,   240,     4,     6,
    1085,  1085,  1071,  1088,  1071,   238,  1138,     3,  1105,  1138,
     240,  1080,  1071,  1080,  1071,   240,  1085,  1114,  1085,  1116,
    1138,  1080,  1071,  1080,  1071,  1138,  1123,  1071,  1085,  1126,
    1071,  1080,   240,  1080,  1138,  1071,  1080,  1071,   240,  1080,
    1071,  1138,     4,  1138,  1080,  1071,  1080,  1071,     8,  1080,
    1071,  1138,  1071,     8,  1080,  1071,  1080,  1071,  1071,  1080,
    1071,  1080,  1071,  1071,  1080,  1071,  1080,  1080,  1071,  1080,
       4,  1080,  1080,  1071,  1080,  1071,  1071,  1080,  1071,  1138,
       4,  1071,  1080,  1071,  1080,  1080,  1071,  1080,     8,  1138,
    1080,  1138,  1080,     3,  1138,  1080,   237,  1138,   237,     8,
       7,     5,  1138,     4,  1138,     4,     4,  1138,     4,     4,
       7,   237,  1138,     6,  1138,     3,     5,  1138,     4,  1138,
       4,     4,     4,   177,   237,   237,  1285,     7,     5,     7,
       4,   237,     3,   237,     6,   237,   237,   237,     4,   237,
     237,   237,     4,     4,   237,   240,   240,   238,   237,     4,
     237,   237,     4,     4,   237,   237,     4,   736,   238,   240,
     238,   237,  1329,   237,   237,   237,  1329,   751,   537,  1336,
    1070,   753,  1041,  1336,   840,  1065,  1336,  1083,  1345,   546,
    1167,  1329,  1105,  1093,  1073,  1329,  1353,  1091,  1336,   595,
    1353,  1100,  1336,  1071,   560,  1076,  1082,  1329,  1329,  1074,
    1329,  1345,   585,  1329,  1336,  1077,  1079,  1140,  1138,  1353,
     592,  1329,   564,  1090,  1336,   575,  1329,  1118,  1088,  1087,
    1114,  1116,  1329,  1395,  1391,  1329,  1393,  1421,  1447,  1336,
    1393,  1476,  1329,  1391,  1329,  1123,   752,   792,  1353,  1336,
     605,   609,  1329,  1127,  1329,  1329,  1424,  1391,  1345,  1393,
    1454,  1336,  1336,  1133,  1421,    -1,  1353,    -1,  1421,    -1,
    1329,    -1,  1329,    -1,    -1,    -1,    -1,  1336,    -1,  1336,
    1329,    -1,  1329,    -1,    -1,    -1,    -1,  1421,  1445,  1336,
    1329,    -1,  1329,    -1,    -1,  1329,    -1,    -1,  1329,    -1,
      -1,    -1,    -1,  1329,  1391,  1329,  1393,    -1,  1329,    -1,
      -1,  1445,    -1,  1329,    -1,  1329,    -1,    -1,  1329,  1476,
    1329,    -1,    -1,  1329,    -1,  1329,  1329,    -1,  1329,    -1,
    1329,  1329,    -1,  1329,  1421,    -1,  1329,    -1,    -1,    -1,
      -1,  1329,  1476,  1329,  1329,    -1,  1329,    -1,    -1,  1329,
      -1,  1329,    -1,    -1,  1329,    -1,    -1,    -1,  1445,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1476,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,   125,    -1,   127,    -1,   129,   130,
     131,    -1,   133,   134,   135,    -1,    -1,    -1,    -1,   140,
      -1,    -1,    85,    86,    87,    88,    89,    90,    91,   150,
      93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,
     123,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     133,   134,   135,    -1,    -1,    -1,    -1,   140,   141,    -1,
      -1,    -1,    -1,    -1,   205,   206,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   205,   206,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   237
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
       7,   668,     7,   687,   264,   259,   273,   278,   337,   452,
     539,   556,   488,   494,   518,   428,   669,   688,   256,   265,
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
     545,   547,   549,   560,   562,   564,   587,   603,   604,   606,
     656,   666,   685,   694,   718,    15,    16,    19,    22,    23,
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
     670,   671,   672,   673,   675,   676,   678,   679,   680,   683,
      12,    13,   689,   690,   691,   693,     6,     3,     4,     8,
       3,   275,     3,     8,   686,   333,   353,     4,     4,     4,
     561,   563,   565,     4,     4,   351,   361,   363,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     294,     4,     4,     4,     4,     4,   305,   308,   310,     4,
       4,     4,     4,     4,     4,     4,   446,   486,   512,     4,
     297,   314,   478,   546,   548,     4,     4,     4,   406,   588,
     550,   422,   436,     4,   415,   605,   607,   657,   667,   321,
     323,     4,     4,     4,   695,   719,     4,     3,     8,   339,
     341,   344,     4,     4,     4,     4,     3,     8,   458,   460,
     462,   533,   456,   464,     4,   468,   470,   472,   466,   583,
       3,     8,   543,     4,     3,     8,   581,   567,   569,   571,
     575,   573,   579,   577,     8,     3,     8,   502,   380,     4,
     506,   504,   509,     4,     8,     3,   524,     4,     4,     4,
     531,     8,     3,   432,   434,     3,     8,     4,   674,     4,
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
       4,     4,   238,     4,     4,     4,     4,     4,   454,     4,
     238,   541,     4,     4,     4,     4,     4,     4,     4,     4,
     559,     4,     4,   238,     4,     4,     4,   240,   497,     4,
     240,   240,   240,     4,   521,     4,     4,   430,   240,     4,
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
      62,    63,    64,    65,    66,    67,    68,    69,   271,   368,
     369,   370,   372,   374,   376,   378,   379,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   393,   394,   395,
     397,   399,   401,   403,   368,     7,   364,   365,   366,     7,
     447,   448,   449,     7,   489,   490,   491,     7,   513,   514,
     515,     7,   479,   480,   481,   144,   145,   146,   147,   149,
     407,   408,   409,   410,   411,   412,   413,     7,   589,   590,
     591,     7,   551,   552,   553,     7,   423,   424,   425,   156,
     157,   158,   159,   160,   161,   437,   438,   439,   440,   441,
     442,   443,   444,   164,   165,   166,   271,   416,   417,   418,
     419,   420,   545,   547,   169,   173,   174,   175,   176,   183,
     184,   271,   395,   397,   399,   545,   547,   612,   613,   614,
     617,   619,   621,   622,   623,   633,     7,   608,   609,   610,
     187,   188,   189,   237,   545,   547,   658,   659,   660,   661,
     663,   664,   670,     7,   696,   697,   220,   221,   222,   223,
     271,   720,   721,   722,   723,   724,   725,   268,     7,   534,
     535,   536,   151,   584,   585,   364,     8,     8,     8,   357,
     359,     3,     8,   371,   373,   375,   377,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   391,     4,     4,
     396,   398,   400,   402,   404,     3,     8,     8,   367,     6,
       3,   450,     6,     3,   492,     6,     3,   516,     6,     3,
     482,     6,     3,     3,     6,   592,     6,     3,   554,     6,
       3,   426,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,     4,     4,     4,     3,     8,   615,   618,   620,
       4,   634,     4,   624,     3,     8,   611,     6,     3,     4,
     662,     4,   665,     3,     8,     8,   698,     3,     6,     4,
       4,     4,     4,     3,     8,   237,   269,   270,   537,     6,
       3,   586,     8,     6,     4,     4,   355,     4,     4,     4,
       4,   238,   240,   238,   240,   238,   238,   238,   238,   238,
     238,     4,   240,   238,     4,     4,     4,     4,     4,   369,
     368,   366,   453,   449,   495,   491,   519,   515,   271,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     296,   299,   300,   301,   302,   303,   304,   307,   309,   311,
     312,   313,   316,   317,   318,   319,   320,   322,   324,   330,
     379,   445,   463,   465,   467,   469,   471,   473,   474,   475,
     483,   484,   511,   545,   547,   560,   562,   564,   582,   481,
     408,   136,   137,   138,   139,   271,   281,   282,   283,   330,
     379,   485,   511,   545,   547,   560,   562,   564,   593,   594,
     595,   596,   597,   599,   601,   602,   591,   557,   553,   429,
     425,   238,   238,   238,   238,   238,   238,   438,   240,   238,
     238,   417,     4,     4,     4,   238,     4,   240,     4,   613,
     612,   610,   240,     4,   238,     4,   659,   211,   213,   214,
     271,   379,   545,   547,   699,   700,   701,   702,   704,   697,
     240,   240,   240,   240,   721,     6,     3,   540,   536,     4,
     237,   237,   237,   237,   237,   237,    55,    56,    57,   392,
     237,   237,   237,   401,   237,     8,     8,     8,     8,     3,
       8,   598,   600,     4,     4,     8,     3,     8,     8,   170,
     171,   172,   616,   237,   237,     7,     5,     8,   237,   256,
     705,     4,   703,     3,     8,   237,     8,   267,   484,     4,
       4,   240,   240,   595,    40,   178,   179,   180,   271,   545,
     547,   635,   636,   637,   640,   642,   644,     7,   625,   626,
     627,     4,   238,     4,   700,   237,   237,   638,   641,   643,
     645,     3,     8,   628,     6,     3,     5,   237,     4,     4,
       4,     4,   636,   185,   271,   379,   545,   547,   629,   630,
     631,   627,     7,   706,   707,   177,   639,   237,   237,     5,
     632,     3,     8,   708,     3,     6,     7,   646,   647,   648,
       4,   630,   212,   215,   216,   217,   218,   709,   710,   711,
     713,   714,   715,   716,   707,   649,     6,     3,   237,   712,
       4,     4,     4,   717,     3,     8,   181,   182,   271,   372,
     374,   545,   547,   650,   651,   652,   654,   648,     4,   240,
     238,   238,     4,   710,   653,   655,     3,     8,   237,   237,
       4,     4,   651,   237,   237
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
     582,   584,   586,   585,   588,   587,   589,   589,   590,   590,
     590,   592,   591,   593,   593,   594,   594,   594,   595,   595,
     595,   595,   595,   595,   595,   595,   595,   595,   595,   595,
     595,   595,   595,   595,   595,   596,   598,   597,   600,   599,
     601,   602,   603,   605,   604,   607,   606,   608,   608,   609,
     609,   609,   611,   610,   612,   612,   612,   613,   613,   613,
     613,   613,   613,   613,   613,   613,   613,   613,   613,   613,
     615,   614,   616,   616,   616,   618,   617,   620,   619,   621,
     622,   624,   623,   625,   625,   626,   626,   626,   628,   627,
     629,   629,   629,   630,   630,   630,   630,   630,   632,   631,
     634,   633,   635,   635,   635,   636,   636,   636,   636,   636,
     636,   636,   638,   637,   639,   641,   640,   643,   642,   645,
     644,   646,   646,   647,   647,   647,   649,   648,   650,   650,
     650,   651,   651,   651,   651,   651,   651,   651,   653,   652,
     655,   654,   657,   656,   658,   658,   658,   659,   659,   659,
     659,   659,   659,   660,   662,   661,   663,   665,   664,   667,
     666,   669,   668,   670,   670,   670,   671,   671,   671,   671,
     671,   671,   671,   671,   671,   671,   671,   672,   674,   673,
     675,   677,   676,   678,   679,   681,   680,   682,   682,   684,
     683,   686,   685,   688,   687,   689,   689,   689,   690,   690,
     692,   691,   693,   695,   694,   696,   696,   696,   698,   697,
     699,   699,   699,   700,   700,   700,   700,   700,   700,   700,
     701,   703,   702,   705,   704,   706,   706,   706,   708,   707,
     709,   709,   709,   710,   710,   710,   710,   710,   712,   711,
     713,   714,   715,   717,   716,   719,   718,   720,   720,   720,
     721,   721,   721,   721,   721,   722,   723,   724,   725
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
       6,     1,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     3,     3,     0,     6,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     3,     3,     3,     3
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
    2518,  2529,  2532,  2532,  2546,  2546,  2557,  2558,  2561,  2562,
    2563,  2568,  2568,  2578,  2579,  2582,  2583,  2584,  2589,  2590,
    2591,  2592,  2593,  2594,  2595,  2596,  2597,  2598,  2599,  2600,
    2601,  2602,  2603,  2604,  2605,  2608,  2610,  2610,  2619,  2619,
    2629,  2635,  2643,  2651,  2651,  2663,  2663,  2675,  2676,  2679,
    2680,  2681,  2686,  2686,  2694,  2695,  2696,  2701,  2702,  2703,
    2704,  2705,  2706,  2707,  2708,  2709,  2710,  2711,  2712,  2713,
    2716,  2716,  2725,  2726,  2727,  2730,  2730,  2739,  2739,  2748,
    2754,  2760,  2760,  2771,  2772,  2775,  2776,  2777,  2782,  2782,
    2790,  2791,  2792,  2797,  2798,  2799,  2800,  2801,  2804,  2804,
    2815,  2815,  2828,  2829,  2830,  2835,  2836,  2837,  2838,  2839,
    2840,  2841,  2844,  2844,  2852,  2855,  2855,  2864,  2864,  2873,
    2873,  2884,  2885,  2888,  2889,  2890,  2895,  2895,  2903,  2904,
    2905,  2910,  2911,  2912,  2913,  2914,  2915,  2916,  2919,  2919,
    2928,  2928,  2939,  2939,  2952,  2953,  2954,  2959,  2960,  2961,
    2962,  2963,  2964,  2967,  2973,  2973,  2982,  2988,  2988,  2998,
    2998,  3011,  3011,  3021,  3022,  3023,  3028,  3029,  3030,  3031,
    3032,  3033,  3034,  3035,  3036,  3037,  3038,  3041,  3047,  3047,
    3056,  3062,  3062,  3071,  3077,  3083,  3083,  3092,  3093,  3096,
    3096,  3107,  3107,  3119,  3119,  3129,  3130,  3131,  3137,  3138,
    3141,  3141,  3152,  3160,  3160,  3173,  3174,  3175,  3181,  3181,
    3189,  3190,  3191,  3196,  3197,  3198,  3199,  3200,  3201,  3202,
    3205,  3211,  3211,  3220,  3220,  3231,  3232,  3233,  3238,  3238,
    3246,  3247,  3248,  3253,  3254,  3255,  3256,  3257,  3260,  3260,
    3269,  3275,  3281,  3287,  3287,  3296,  3296,  3307,  3308,  3309,
    3314,  3315,  3316,  3317,  3318,  3321,  3327,  3333,  3339
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
#line 7019 "dhcp4_parser.cc"

#line 3345 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
