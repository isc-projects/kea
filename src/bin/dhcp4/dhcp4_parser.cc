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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 421 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 427 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 433 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 439 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 481 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 487 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 493 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 499 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 317 "dhcp4_parser.yy"
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
#line 326 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 788 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 327 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 794 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 328 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 800 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 329 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 806 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 330 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 812 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 331 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 818 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 332 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 824 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 333 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 830 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 334 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 836 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 335 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 842 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 336 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 848 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 337 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 854 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 338 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 860 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 346 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 347 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 348 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 349 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 350 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 890 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 351 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 352 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 902 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 355 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 911 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 360 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 365 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 932 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 371 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 938 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 378 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 383 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 959 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 389 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 967 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 394 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 976 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 397 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 984 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 405 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 993 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 409 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1002 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 413 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1010 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 419 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1018 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 421 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1027 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 430 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1036 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 434 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1045 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 438 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1053 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 448 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 457 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1075 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 462 "dhcp4_parser.yy"
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
#line 472 "dhcp4_parser.yy"
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
#line 481 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 489 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 495 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 499 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 506 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1148 "dhcp4_parser.cc"
    break;

  case 139: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 584 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1158 "dhcp4_parser.cc"
    break;

  case 140: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 590 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 141: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 596 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1178 "dhcp4_parser.cc"
    break;

  case 142: // renew_timer: "renew-timer" ":" "integer"
#line 602 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1188 "dhcp4_parser.cc"
    break;

  case 143: // rebind_timer: "rebind-timer" ":" "integer"
#line 608 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 144: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 614 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1208 "dhcp4_parser.cc"
    break;

  case 145: // t1_percent: "t1-percent" ":" "floating point"
#line 620 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1218 "dhcp4_parser.cc"
    break;

  case 146: // t2_percent: "t2-percent" ":" "floating point"
#line 626 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1228 "dhcp4_parser.cc"
    break;

  case 147: // cache_threshold: "cache-threshold" ":" "floating point"
#line 632 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 148: // cache_max_age: "cache-max-age" ":" "integer"
#line 638 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1248 "dhcp4_parser.cc"
    break;

  case 149: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 644 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 150: // $@20: %empty
#line 650 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1267 "dhcp4_parser.cc"
    break;

  case 151: // server_tag: "server-tag" $@20 ":" "constant string"
#line 653 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 152: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 659 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 665 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp4_parser.cc"
    break;

  case 154: // allocator: "allocator" $@21 ":" "constant string"
#line 668 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1306 "dhcp4_parser.cc"
    break;

  case 155: // echo_client_id: "echo-client-id" ":" "boolean"
#line 674 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1316 "dhcp4_parser.cc"
    break;

  case 156: // match_client_id: "match-client-id" ":" "boolean"
#line 680 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1326 "dhcp4_parser.cc"
    break;

  case 157: // authoritative: "authoritative" ":" "boolean"
#line 686 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1336 "dhcp4_parser.cc"
    break;

  case 158: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 692 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 698 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 160: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 704 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 710 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 713 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1384 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-present"
#line 719 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1392 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "never"
#line 722 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1400 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "always"
#line 725 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1408 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-not-present"
#line 728 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1416 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "boolean"
#line 731 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1425 "dhcp4_parser.cc"
    break;

  case 168: // $@23: %empty
#line 737 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 169: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 740 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 170: // $@24: %empty
#line 746 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1453 "dhcp4_parser.cc"
    break;

  case 171: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 749 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 172: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 755 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 173: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 764 "dhcp4_parser.yy"
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

  case 174: // $@25: %empty
#line 774 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 777 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 783 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1513 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 786 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1521 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 789 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1529 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 792 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1537 "dhcp4_parser.cc"
    break;

  case 180: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 797 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 803 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 182: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 806 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 183: // $@27: %empty
#line 812 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 184: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 815 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 185: // store_extended_info: "store-extended-info" ":" "boolean"
#line 821 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1595 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 827 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 187: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 833 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 188: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 839 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 189: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 845 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1635 "dhcp4_parser.cc"
    break;

  case 190: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 851 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 191: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 857 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 192: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 863 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 869 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1677 "dhcp4_parser.cc"
    break;

  case 194: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 875 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1687 "dhcp4_parser.cc"
    break;

  case 197: // interfaces_config_params: interfaces_config_params ","
#line 883 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1695 "dhcp4_parser.cc"
    break;

  case 208: // $@29: %empty
#line 900 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1705 "dhcp4_parser.cc"
    break;

  case 209: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 904 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 210: // $@30: %empty
#line 909 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "dhcp4_parser.cc"
    break;

  case 211: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 915 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 212: // $@31: %empty
#line 920 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1744 "dhcp4_parser.cc"
    break;

  case 213: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 923 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "raw"
#line 928 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1759 "dhcp4_parser.cc"
    break;

  case 215: // socket_type: "udp"
#line 929 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1765 "dhcp4_parser.cc"
    break;

  case 216: // $@32: %empty
#line 932 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 935 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "same-as-inbound"
#line 940 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1791 "dhcp4_parser.cc"
    break;

  case 219: // outbound_interface_value: "use-routing"
#line 942 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1799 "dhcp4_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 946 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1809 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 952 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1819 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 958 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1829 "dhcp4_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 964 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1839 "dhcp4_parser.cc"
    break;

  case 224: // $@33: %empty
#line 970 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 976 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 226: // $@34: %empty
#line 983 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1874 "dhcp4_parser.cc"
    break;

  case 227: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 989 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1883 "dhcp4_parser.cc"
    break;

  case 230: // sanity_checks_params: sanity_checks_params ","
#line 996 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1891 "dhcp4_parser.cc"
    break;

  case 233: // $@35: %empty
#line 1005 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp4_parser.cc"
    break;

  case 234: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1008 "dhcp4_parser.yy"
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
#line 1920 "dhcp4_parser.cc"
    break;

  case 235: // $@36: %empty
#line 1024 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 236: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1027 "dhcp4_parser.yy"
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
#line 1948 "dhcp4_parser.cc"
    break;

  case 237: // $@37: %empty
#line 1042 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 238: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1048 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 239: // $@38: %empty
#line 1055 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1983 "dhcp4_parser.cc"
    break;

  case 240: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1061 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 245: // not_empty_database_list: not_empty_database_list ","
#line 1072 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 2000 "dhcp4_parser.cc"
    break;

  case 246: // $@39: %empty
#line 1077 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 247: // database: "{" $@39 database_map_params "}"
#line 1081 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 250: // database_map_params: database_map_params ","
#line 1089 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2028 "dhcp4_parser.cc"
    break;

  case 274: // $@40: %empty
#line 1119 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 2037 "dhcp4_parser.cc"
    break;

  case 275: // database_type: "type" $@40 ":" db_type
#line 1122 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 276: // db_type: "memfile"
#line 1127 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 2052 "dhcp4_parser.cc"
    break;

  case 277: // db_type: "mysql"
#line 1128 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 2058 "dhcp4_parser.cc"
    break;

  case 278: // db_type: "postgresql"
#line 1129 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 2064 "dhcp4_parser.cc"
    break;

  case 279: // $@41: %empty
#line 1132 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc"
    break;

  case 280: // user: "user" $@41 ":" "constant string"
#line 1135 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2083 "dhcp4_parser.cc"
    break;

  case 281: // $@42: %empty
#line 1141 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2092 "dhcp4_parser.cc"
    break;

  case 282: // password: "password" $@42 ":" "constant string"
#line 1144 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2102 "dhcp4_parser.cc"
    break;

  case 283: // $@43: %empty
#line 1150 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2111 "dhcp4_parser.cc"
    break;

  case 284: // host: "host" $@43 ":" "constant string"
#line 1153 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2121 "dhcp4_parser.cc"
    break;

  case 285: // port: "port" ":" "integer"
#line 1159 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2131 "dhcp4_parser.cc"
    break;

  case 286: // $@44: %empty
#line 1165 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp4_parser.cc"
    break;

  case 287: // name: "name" $@44 ":" "constant string"
#line 1168 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2150 "dhcp4_parser.cc"
    break;

  case 288: // persist: "persist" ":" "boolean"
#line 1174 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2160 "dhcp4_parser.cc"
    break;

  case 289: // lfc_interval: "lfc-interval" ":" "integer"
#line 1180 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2170 "dhcp4_parser.cc"
    break;

  case 290: // readonly: "readonly" ":" "boolean"
#line 1186 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2180 "dhcp4_parser.cc"
    break;

  case 291: // connect_timeout: "connect-timeout" ":" "integer"
#line 1192 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2190 "dhcp4_parser.cc"
    break;

  case 292: // read_timeout: "read-timeout" ":" "integer"
#line 1198 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2200 "dhcp4_parser.cc"
    break;

  case 293: // write_timeout: "write-timeout" ":" "integer"
#line 1204 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2210 "dhcp4_parser.cc"
    break;

  case 294: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1210 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 295: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1216 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 296: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1222 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 297: // $@45: %empty
#line 1228 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2249 "dhcp4_parser.cc"
    break;

  case 298: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1231 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 299: // on_fail_mode: "stop-retry-exit"
#line 1236 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2264 "dhcp4_parser.cc"
    break;

  case 300: // on_fail_mode: "serve-retry-exit"
#line 1237 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2270 "dhcp4_parser.cc"
    break;

  case 301: // on_fail_mode: "serve-retry-continue"
#line 1238 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2276 "dhcp4_parser.cc"
    break;

  case 302: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1241 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2286 "dhcp4_parser.cc"
    break;

  case 303: // max_row_errors: "max-row-errors" ":" "integer"
#line 1247 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2296 "dhcp4_parser.cc"
    break;

  case 304: // $@46: %empty
#line 1253 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2305 "dhcp4_parser.cc"
    break;

  case 305: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1256 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2315 "dhcp4_parser.cc"
    break;

  case 306: // $@47: %empty
#line 1262 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2324 "dhcp4_parser.cc"
    break;

  case 307: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1265 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2334 "dhcp4_parser.cc"
    break;

  case 308: // $@48: %empty
#line 1271 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2343 "dhcp4_parser.cc"
    break;

  case 309: // key_file: "key-file" $@48 ":" "constant string"
#line 1274 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2353 "dhcp4_parser.cc"
    break;

  case 310: // $@49: %empty
#line 1280 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 311: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1283 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2372 "dhcp4_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1289 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2384 "dhcp4_parser.cc"
    break;

  case 313: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1295 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2393 "dhcp4_parser.cc"
    break;

  case 316: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1302 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2401 "dhcp4_parser.cc"
    break;

  case 322: // duid_id: "duid"
#line 1314 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2410 "dhcp4_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1319 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2419 "dhcp4_parser.cc"
    break;

  case 324: // circuit_id: "circuit-id"
#line 1324 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2428 "dhcp4_parser.cc"
    break;

  case 325: // client_id: "client-id"
#line 1329 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2437 "dhcp4_parser.cc"
    break;

  case 326: // flex_id: "flex-id"
#line 1334 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2446 "dhcp4_parser.cc"
    break;

  case 327: // $@51: %empty
#line 1341 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2458 "dhcp4_parser.cc"
    break;

  case 328: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1347 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1356 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2477 "dhcp4_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1369 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2487 "dhcp4_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1375 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2497 "dhcp4_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1381 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 341: // $@52: %empty
#line 1387 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 342: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1393 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1404 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2536 "dhcp4_parser.cc"
    break;

  case 348: // $@53: %empty
#line 1409 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2546 "dhcp4_parser.cc"
    break;

  case 349: // hooks_library: "{" $@53 hooks_params "}"
#line 1413 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2556 "dhcp4_parser.cc"
    break;

  case 350: // $@54: %empty
#line 1419 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2566 "dhcp4_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1423 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2576 "dhcp4_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1431 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2584 "dhcp4_parser.cc"
    break;

  case 358: // $@55: %empty
#line 1441 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2593 "dhcp4_parser.cc"
    break;

  case 359: // library: "library" $@55 ":" "constant string"
#line 1444 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2603 "dhcp4_parser.cc"
    break;

  case 360: // $@56: %empty
#line 1450 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2612 "dhcp4_parser.cc"
    break;

  case 361: // parameters: "parameters" $@56 ":" map_value
#line 1453 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1459 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2633 "dhcp4_parser.cc"
    break;

  case 363: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1465 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1473 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2651 "dhcp4_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1486 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2661 "dhcp4_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1492 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2671 "dhcp4_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1498 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2681 "dhcp4_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1504 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2691 "dhcp4_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1510 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1516 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 379: // $@58: %empty
#line 1525 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2723 "dhcp4_parser.cc"
    break;

  case 380: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1531 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 385: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1545 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2740 "dhcp4_parser.cc"
    break;

  case 386: // $@59: %empty
#line 1554 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 387: // subnet4: "{" $@59 subnet4_params "}"
#line 1558 "dhcp4_parser.yy"
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
#line 2776 "dhcp4_parser.cc"
    break;

  case 388: // $@60: %empty
#line 1580 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp4_parser.cc"
    break;

  case 389: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1584 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2796 "dhcp4_parser.cc"
    break;

  case 392: // subnet4_params: subnet4_params ","
#line 1593 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2804 "dhcp4_parser.cc"
    break;

  case 441: // $@61: %empty
#line 1649 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp4_parser.cc"
    break;

  case 442: // subnet: "subnet" $@61 ":" "constant string"
#line 1652 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 443: // $@62: %empty
#line 1658 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp4_parser.cc"
    break;

  case 444: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1661 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 445: // $@63: %empty
#line 1667 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 446: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1670 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 447: // $@64: %empty
#line 1676 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2870 "dhcp4_parser.cc"
    break;

  case 448: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1679 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2880 "dhcp4_parser.cc"
    break;

  case 449: // $@65: %empty
#line 1685 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2889 "dhcp4_parser.cc"
    break;

  case 450: // interface: "interface" $@65 ":" "constant string"
#line 1688 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 451: // $@66: %empty
#line 1694 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 452: // client_class: "client-class" $@66 ":" "constant string"
#line 1697 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2918 "dhcp4_parser.cc"
    break;

  case 453: // $@67: %empty
#line 1703 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp4_parser.cc"
    break;

  case 454: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1709 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 455: // reservations_global: "reservations-global" ":" "boolean"
#line 1714 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2949 "dhcp4_parser.cc"
    break;

  case 456: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1720 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2959 "dhcp4_parser.cc"
    break;

  case 457: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1726 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 458: // id: "id" ":" "integer"
#line 1732 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2979 "dhcp4_parser.cc"
    break;

  case 459: // $@68: %empty
#line 1740 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2991 "dhcp4_parser.cc"
    break;

  case 460: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1746 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 465: // shared_networks_list: shared_networks_list ","
#line 1759 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3008 "dhcp4_parser.cc"
    break;

  case 466: // $@69: %empty
#line 1764 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 467: // shared_network: "{" $@69 shared_network_params "}"
#line 1768 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3026 "dhcp4_parser.cc"
    break;

  case 470: // shared_network_params: shared_network_params ","
#line 1774 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3034 "dhcp4_parser.cc"
    break;

  case 514: // $@70: %empty
#line 1828 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3046 "dhcp4_parser.cc"
    break;

  case 515: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1834 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3055 "dhcp4_parser.cc"
    break;

  case 516: // $@71: %empty
#line 1842 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3064 "dhcp4_parser.cc"
    break;

  case 517: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1845 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 522: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1857 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3080 "dhcp4_parser.cc"
    break;

  case 523: // $@72: %empty
#line 1864 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 524: // option_def_entry: "{" $@72 option_def_params "}"
#line 1868 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 525: // $@73: %empty
#line 1879 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 526: // sub_option_def: "{" $@73 option_def_params "}"
#line 1883 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3124 "dhcp4_parser.cc"
    break;

  case 531: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1899 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3132 "dhcp4_parser.cc"
    break;

  case 543: // code: "code" ":" "integer"
#line 1918 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 545: // $@74: %empty
#line 1926 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3151 "dhcp4_parser.cc"
    break;

  case 546: // option_def_type: "type" $@74 ":" "constant string"
#line 1929 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3161 "dhcp4_parser.cc"
    break;

  case 547: // $@75: %empty
#line 1935 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3170 "dhcp4_parser.cc"
    break;

  case 548: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1938 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3180 "dhcp4_parser.cc"
    break;

  case 549: // $@76: %empty
#line 1944 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3189 "dhcp4_parser.cc"
    break;

  case 550: // space: "space" $@76 ":" "constant string"
#line 1947 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3199 "dhcp4_parser.cc"
    break;

  case 552: // $@77: %empty
#line 1955 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3208 "dhcp4_parser.cc"
    break;

  case 553: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1958 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3218 "dhcp4_parser.cc"
    break;

  case 554: // option_def_array: "array" ":" "boolean"
#line 1964 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3228 "dhcp4_parser.cc"
    break;

  case 555: // $@78: %empty
#line 1974 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3240 "dhcp4_parser.cc"
    break;

  case 556: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1980 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 561: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1995 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3257 "dhcp4_parser.cc"
    break;

  case 562: // $@79: %empty
#line 2002 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3267 "dhcp4_parser.cc"
    break;

  case 563: // option_data_entry: "{" $@79 option_data_params "}"
#line 2006 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3276 "dhcp4_parser.cc"
    break;

  case 564: // $@80: %empty
#line 2014 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3286 "dhcp4_parser.cc"
    break;

  case 565: // sub_option_data: "{" $@80 option_data_params "}"
#line 2018 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3295 "dhcp4_parser.cc"
    break;

  case 570: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2034 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3303 "dhcp4_parser.cc"
    break;

  case 582: // $@81: %empty
#line 2055 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 583: // option_data_data: "data" $@81 ":" "constant string"
#line 2058 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 586: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2068 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 587: // option_data_always_send: "always-send" ":" "boolean"
#line 2074 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 588: // option_data_never_send: "never-send" ":" "boolean"
#line 2080 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3352 "dhcp4_parser.cc"
    break;

  case 589: // $@82: %empty
#line 2089 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3364 "dhcp4_parser.cc"
    break;

  case 590: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2095 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 595: // not_empty_pools_list: not_empty_pools_list ","
#line 2108 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3381 "dhcp4_parser.cc"
    break;

  case 596: // $@83: %empty
#line 2113 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3391 "dhcp4_parser.cc"
    break;

  case 597: // pool_list_entry: "{" $@83 pool_params "}"
#line 2117 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3401 "dhcp4_parser.cc"
    break;

  case 598: // $@84: %empty
#line 2123 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3411 "dhcp4_parser.cc"
    break;

  case 599: // sub_pool4: "{" $@84 pool_params "}"
#line 2127 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3421 "dhcp4_parser.cc"
    break;

  case 602: // pool_params: pool_params ","
#line 2135 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3429 "dhcp4_parser.cc"
    break;

  case 611: // $@85: %empty
#line 2150 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3438 "dhcp4_parser.cc"
    break;

  case 612: // pool_entry: "pool" $@85 ":" "constant string"
#line 2153 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3448 "dhcp4_parser.cc"
    break;

  case 613: // pool_id: "pool-id" ":" "integer"
#line 2159 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3458 "dhcp4_parser.cc"
    break;

  case 614: // $@86: %empty
#line 2165 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp4_parser.cc"
    break;

  case 615: // user_context: "user-context" $@86 ":" map_value
#line 2167 "dhcp4_parser.yy"
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
#line 3493 "dhcp4_parser.cc"
    break;

  case 616: // $@87: %empty
#line 2190 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3501 "dhcp4_parser.cc"
    break;

  case 617: // comment: "comment" $@87 ":" "constant string"
#line 2192 "dhcp4_parser.yy"
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
#line 3530 "dhcp4_parser.cc"
    break;

  case 618: // $@88: %empty
#line 2220 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 619: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2226 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3551 "dhcp4_parser.cc"
    break;

  case 624: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2237 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3559 "dhcp4_parser.cc"
    break;

  case 625: // $@89: %empty
#line 2242 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3569 "dhcp4_parser.cc"
    break;

  case 626: // reservation: "{" $@89 reservation_params "}"
#line 2246 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3578 "dhcp4_parser.cc"
    break;

  case 627: // $@90: %empty
#line 2251 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3588 "dhcp4_parser.cc"
    break;

  case 628: // sub_reservation: "{" $@90 reservation_params "}"
#line 2255 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3597 "dhcp4_parser.cc"
    break;

  case 633: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2266 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3605 "dhcp4_parser.cc"
    break;

  case 649: // $@91: %empty
#line 2289 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3614 "dhcp4_parser.cc"
    break;

  case 650: // next_server: "next-server" $@91 ":" "constant string"
#line 2292 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 651: // $@92: %empty
#line 2298 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3633 "dhcp4_parser.cc"
    break;

  case 652: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2301 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 653: // $@93: %empty
#line 2307 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3652 "dhcp4_parser.cc"
    break;

  case 654: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2310 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3662 "dhcp4_parser.cc"
    break;

  case 655: // $@94: %empty
#line 2316 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3671 "dhcp4_parser.cc"
    break;

  case 656: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2319 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 657: // $@95: %empty
#line 2325 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3690 "dhcp4_parser.cc"
    break;

  case 658: // duid: "duid" $@95 ":" "constant string"
#line 2328 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3700 "dhcp4_parser.cc"
    break;

  case 659: // $@96: %empty
#line 2334 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3709 "dhcp4_parser.cc"
    break;

  case 660: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2337 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3719 "dhcp4_parser.cc"
    break;

  case 661: // $@97: %empty
#line 2343 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3728 "dhcp4_parser.cc"
    break;

  case 662: // client_id_value: "client-id" $@97 ":" "constant string"
#line 2346 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3738 "dhcp4_parser.cc"
    break;

  case 663: // $@98: %empty
#line 2352 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3747 "dhcp4_parser.cc"
    break;

  case 664: // circuit_id_value: "circuit-id" $@98 ":" "constant string"
#line 2355 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3757 "dhcp4_parser.cc"
    break;

  case 665: // $@99: %empty
#line 2361 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp4_parser.cc"
    break;

  case 666: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2364 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 667: // $@100: %empty
#line 2370 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3785 "dhcp4_parser.cc"
    break;

  case 668: // hostname: "hostname" $@100 ":" "constant string"
#line 2373 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3795 "dhcp4_parser.cc"
    break;

  case 669: // $@101: %empty
#line 2379 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3807 "dhcp4_parser.cc"
    break;

  case 670: // reservation_client_classes: "client-classes" $@101 ":" list_strings
#line 2385 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3816 "dhcp4_parser.cc"
    break;

  case 671: // $@102: %empty
#line 2393 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 672: // relay: "relay" $@102 ":" "{" relay_map "}"
#line 2399 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 674: // $@103: %empty
#line 2407 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3849 "dhcp4_parser.cc"
    break;

  case 675: // ip_addresses: "ip-addresses" $@103 ":" list_strings
#line 2413 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 676: // $@104: %empty
#line 2421 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3870 "dhcp4_parser.cc"
    break;

  case 677: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2427 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3879 "dhcp4_parser.cc"
    break;

  case 680: // client_classes_list: client_classes_list ","
#line 2434 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3887 "dhcp4_parser.cc"
    break;

  case 681: // $@105: %empty
#line 2439 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3897 "dhcp4_parser.cc"
    break;

  case 682: // client_class_entry: "{" $@105 client_class_params "}"
#line 2443 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3907 "dhcp4_parser.cc"
    break;

  case 687: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2455 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3915 "dhcp4_parser.cc"
    break;

  case 705: // $@106: %empty
#line 2480 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3924 "dhcp4_parser.cc"
    break;

  case 706: // client_class_test: "test" $@106 ":" "constant string"
#line 2483 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 707: // $@107: %empty
#line 2489 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3943 "dhcp4_parser.cc"
    break;

  case 708: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2492 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3953 "dhcp4_parser.cc"
    break;

  case 709: // only_if_required: "only-if-required" ":" "boolean"
#line 2498 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 710: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2506 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3973 "dhcp4_parser.cc"
    break;

  case 711: // $@108: %empty
#line 2514 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3985 "dhcp4_parser.cc"
    break;

  case 712: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2520 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 713: // $@109: %empty
#line 2525 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 714: // control_sockets: "control-sockets" $@109 ":" "[" control_socket_list "]"
#line 2531 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4015 "dhcp4_parser.cc"
    break;

  case 719: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2542 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4023 "dhcp4_parser.cc"
    break;

  case 720: // $@110: %empty
#line 2547 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4033 "dhcp4_parser.cc"
    break;

  case 721: // control_socket_entry: "{" $@110 control_socket_params "}"
#line 2551 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 724: // control_socket_params: control_socket_params ","
#line 2558 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4050 "dhcp4_parser.cc"
    break;

  case 737: // $@111: %empty
#line 2577 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4059 "dhcp4_parser.cc"
    break;

  case 738: // control_socket_type: "socket-type" $@111 ":" control_socket_type_value
#line 2580 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4068 "dhcp4_parser.cc"
    break;

  case 739: // control_socket_type_value: "unix"
#line 2586 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4074 "dhcp4_parser.cc"
    break;

  case 740: // control_socket_type_value: "http"
#line 2587 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4080 "dhcp4_parser.cc"
    break;

  case 741: // control_socket_type_value: "https"
#line 2588 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4086 "dhcp4_parser.cc"
    break;

  case 742: // $@112: %empty
#line 2591 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4095 "dhcp4_parser.cc"
    break;

  case 743: // control_socket_name: "socket-name" $@112 ":" "constant string"
#line 2594 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 744: // $@113: %empty
#line 2600 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 745: // control_socket_address: "socket-address" $@113 ":" "constant string"
#line 2603 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 746: // control_socket_port: "socket-port" ":" "integer"
#line 2609 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4134 "dhcp4_parser.cc"
    break;

  case 747: // cert_required: "cert-required" ":" "boolean"
#line 2615 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4144 "dhcp4_parser.cc"
    break;

  case 748: // $@114: %empty
#line 2623 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4156 "dhcp4_parser.cc"
    break;

  case 749: // authentication: "authentication" $@114 ":" "{" auth_params "}"
#line 2629 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 752: // auth_params: auth_params ","
#line 2638 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4175 "dhcp4_parser.cc"
    break;

  case 760: // $@115: %empty
#line 2652 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4184 "dhcp4_parser.cc"
    break;

  case 761: // auth_type: "type" $@115 ":" auth_type_value
#line 2655 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4193 "dhcp4_parser.cc"
    break;

  case 762: // auth_type_value: "basic"
#line 2660 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4199 "dhcp4_parser.cc"
    break;

  case 763: // $@116: %empty
#line 2663 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4208 "dhcp4_parser.cc"
    break;

  case 764: // realm: "realm" $@116 ":" "constant string"
#line 2666 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4218 "dhcp4_parser.cc"
    break;

  case 765: // $@117: %empty
#line 2672 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4227 "dhcp4_parser.cc"
    break;

  case 766: // directory: "directory" $@117 ":" "constant string"
#line 2675 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4237 "dhcp4_parser.cc"
    break;

  case 767: // $@118: %empty
#line 2681 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4249 "dhcp4_parser.cc"
    break;

  case 768: // clients: "clients" $@118 ":" "[" clients_list "]"
#line 2687 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 773: // not_empty_clients_list: not_empty_clients_list ","
#line 2698 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4266 "dhcp4_parser.cc"
    break;

  case 774: // $@119: %empty
#line 2703 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4276 "dhcp4_parser.cc"
    break;

  case 775: // basic_auth: "{" $@119 clients_params "}"
#line 2707 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 778: // clients_params: clients_params ","
#line 2713 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4292 "dhcp4_parser.cc"
    break;

  case 786: // $@120: %empty
#line 2727 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4301 "dhcp4_parser.cc"
    break;

  case 787: // user_file: "user-file" $@120 ":" "constant string"
#line 2730 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4311 "dhcp4_parser.cc"
    break;

  case 788: // $@121: %empty
#line 2736 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4320 "dhcp4_parser.cc"
    break;

  case 789: // password_file: "password-file" $@121 ":" "constant string"
#line 2739 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4330 "dhcp4_parser.cc"
    break;

  case 790: // $@122: %empty
#line 2747 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4342 "dhcp4_parser.cc"
    break;

  case 791: // dhcp_queue_control: "dhcp-queue-control" $@122 ":" "{" queue_control_params "}"
#line 2753 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 794: // queue_control_params: queue_control_params ","
#line 2762 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4361 "dhcp4_parser.cc"
    break;

  case 801: // enable_queue: "enable-queue" ":" "boolean"
#line 2775 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4371 "dhcp4_parser.cc"
    break;

  case 802: // $@123: %empty
#line 2781 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4380 "dhcp4_parser.cc"
    break;

  case 803: // queue_type: "queue-type" $@123 ":" "constant string"
#line 2784 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4390 "dhcp4_parser.cc"
    break;

  case 804: // capacity: "capacity" ":" "integer"
#line 2790 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4400 "dhcp4_parser.cc"
    break;

  case 805: // $@124: %empty
#line 2796 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4409 "dhcp4_parser.cc"
    break;

  case 806: // arbitrary_map_entry: "constant string" $@124 ":" value
#line 2799 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4418 "dhcp4_parser.cc"
    break;

  case 807: // $@125: %empty
#line 2806 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4430 "dhcp4_parser.cc"
    break;

  case 808: // dhcp_ddns: "dhcp-ddns" $@125 ":" "{" dhcp_ddns_params "}"
#line 2812 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4441 "dhcp4_parser.cc"
    break;

  case 809: // $@126: %empty
#line 2819 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4451 "dhcp4_parser.cc"
    break;

  case 810: // sub_dhcp_ddns: "{" $@126 dhcp_ddns_params "}"
#line 2823 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4461 "dhcp4_parser.cc"
    break;

  case 813: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2831 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4469 "dhcp4_parser.cc"
    break;

  case 825: // enable_updates: "enable-updates" ":" "boolean"
#line 2849 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4479 "dhcp4_parser.cc"
    break;

  case 826: // $@127: %empty
#line 2855 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4488 "dhcp4_parser.cc"
    break;

  case 827: // server_ip: "server-ip" $@127 ":" "constant string"
#line 2858 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4498 "dhcp4_parser.cc"
    break;

  case 828: // server_port: "server-port" ":" "integer"
#line 2864 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4508 "dhcp4_parser.cc"
    break;

  case 829: // $@128: %empty
#line 2870 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4517 "dhcp4_parser.cc"
    break;

  case 830: // sender_ip: "sender-ip" $@128 ":" "constant string"
#line 2873 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4527 "dhcp4_parser.cc"
    break;

  case 831: // sender_port: "sender-port" ":" "integer"
#line 2879 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4537 "dhcp4_parser.cc"
    break;

  case 832: // max_queue_size: "max-queue-size" ":" "integer"
#line 2885 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4547 "dhcp4_parser.cc"
    break;

  case 833: // $@129: %empty
#line 2891 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4556 "dhcp4_parser.cc"
    break;

  case 834: // ncr_protocol: "ncr-protocol" $@129 ":" ncr_protocol_value
#line 2894 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4565 "dhcp4_parser.cc"
    break;

  case 835: // ncr_protocol_value: "udp"
#line 2900 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4571 "dhcp4_parser.cc"
    break;

  case 836: // ncr_protocol_value: "tcp"
#line 2901 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4577 "dhcp4_parser.cc"
    break;

  case 837: // $@130: %empty
#line 2904 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4586 "dhcp4_parser.cc"
    break;

  case 838: // ncr_format: "ncr-format" $@130 ":" "JSON"
#line 2907 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4596 "dhcp4_parser.cc"
    break;

  case 839: // $@131: %empty
#line 2915 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4608 "dhcp4_parser.cc"
    break;

  case 840: // config_control: "config-control" $@131 ":" "{" config_control_params "}"
#line 2921 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4618 "dhcp4_parser.cc"
    break;

  case 841: // $@132: %empty
#line 2927 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4628 "dhcp4_parser.cc"
    break;

  case 842: // sub_config_control: "{" $@132 config_control_params "}"
#line 2931 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4637 "dhcp4_parser.cc"
    break;

  case 845: // config_control_params: config_control_params ","
#line 2939 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4645 "dhcp4_parser.cc"
    break;

  case 848: // $@133: %empty
#line 2949 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4657 "dhcp4_parser.cc"
    break;

  case 849: // config_databases: "config-databases" $@133 ":" "[" database_list "]"
#line 2955 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4666 "dhcp4_parser.cc"
    break;

  case 850: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2960 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4676 "dhcp4_parser.cc"
    break;

  case 851: // $@134: %empty
#line 2968 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4688 "dhcp4_parser.cc"
    break;

  case 852: // loggers: "loggers" $@134 ":" "[" loggers_entries "]"
#line 2974 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4697 "dhcp4_parser.cc"
    break;

  case 855: // loggers_entries: loggers_entries ","
#line 2983 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4705 "dhcp4_parser.cc"
    break;

  case 856: // $@135: %empty
#line 2989 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4715 "dhcp4_parser.cc"
    break;

  case 857: // logger_entry: "{" $@135 logger_params "}"
#line 2993 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4723 "dhcp4_parser.cc"
    break;

  case 860: // logger_params: logger_params ","
#line 2999 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4731 "dhcp4_parser.cc"
    break;

  case 868: // debuglevel: "debuglevel" ":" "integer"
#line 3013 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4741 "dhcp4_parser.cc"
    break;

  case 869: // $@136: %empty
#line 3019 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4750 "dhcp4_parser.cc"
    break;

  case 870: // severity: "severity" $@136 ":" "constant string"
#line 3022 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4760 "dhcp4_parser.cc"
    break;

  case 871: // $@137: %empty
#line 3028 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4772 "dhcp4_parser.cc"
    break;

  case 872: // output_options_list: "output-options" $@137 ":" "[" output_options_list_content "]"
#line 3034 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4781 "dhcp4_parser.cc"
    break;

  case 875: // output_options_list_content: output_options_list_content ","
#line 3041 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4789 "dhcp4_parser.cc"
    break;

  case 876: // $@138: %empty
#line 3046 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4799 "dhcp4_parser.cc"
    break;

  case 877: // output_entry: "{" $@138 output_params_list "}"
#line 3050 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4807 "dhcp4_parser.cc"
    break;

  case 880: // output_params_list: output_params_list ","
#line 3056 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4815 "dhcp4_parser.cc"
    break;

  case 886: // $@139: %empty
#line 3068 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4824 "dhcp4_parser.cc"
    break;

  case 887: // output: "output" $@139 ":" "constant string"
#line 3071 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4834 "dhcp4_parser.cc"
    break;

  case 888: // flush: "flush" ":" "boolean"
#line 3077 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4844 "dhcp4_parser.cc"
    break;

  case 889: // maxsize: "maxsize" ":" "integer"
#line 3083 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4854 "dhcp4_parser.cc"
    break;

  case 890: // maxver: "maxver" ":" "integer"
#line 3089 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4864 "dhcp4_parser.cc"
    break;

  case 891: // $@140: %empty
#line 3095 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4873 "dhcp4_parser.cc"
    break;

  case 892: // pattern: "pattern" $@140 ":" "constant string"
#line 3098 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4883 "dhcp4_parser.cc"
    break;

  case 893: // $@141: %empty
#line 3104 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4895 "dhcp4_parser.cc"
    break;

  case 894: // compatibility: "compatibility" $@141 ":" "{" compatibility_params "}"
#line 3110 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4904 "dhcp4_parser.cc"
    break;

  case 897: // compatibility_params: compatibility_params ","
#line 3117 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4912 "dhcp4_parser.cc"
    break;

  case 903: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3129 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4922 "dhcp4_parser.cc"
    break;

  case 904: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3135 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4932 "dhcp4_parser.cc"
    break;

  case 905: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3141 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4942 "dhcp4_parser.cc"
    break;

  case 906: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3147 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4952 "dhcp4_parser.cc"
    break;


#line 4956 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1317;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     395, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,    62,    48,    49,    81,    83,    97,
      99,   101,   117,   135,   149,   151,   174,   201, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,    48,  -166,    69,   675,    95,   163,
     220,    65,    -9,   280,   302,  -103,    42,    39, -1317,    94,
     187,    98,   130,   189, -1317,    51, -1317, -1317, -1317, -1317,
     254,   275,   291, -1317, -1317, -1317,   297,   307, -1317, -1317,
   -1317,   315,   319,   327,   331,   344,   346,   355,   359,   386,
     402,   445, -1317,   448,   454,   460,   461,   463, -1317, -1317,
   -1317,   466,   468,   469,   470, -1317, -1317, -1317,   473, -1317,
   -1317, -1317, -1317, -1317,   476,   481,   483, -1317, -1317, -1317,
   -1317, -1317,   488, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     490,   491,   494, -1317, -1317,   499, -1317,    55, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     503,   504,   509,   510, -1317,    73, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317,   512, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,    93, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,   514, -1317, -1317,
   -1317, -1317,   113, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     246,   371, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,   380, -1317, -1317,   515, -1317, -1317,
   -1317,   516, -1317, -1317,   401,   436, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   518,
     519,   520, -1317, -1317, -1317, -1317,   517,   523, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317,   131, -1317, -1317, -1317,   526, -1317,   527, -1317,   530,
     531, -1317, -1317, -1317, -1317, -1317,   154, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,   533,   203, -1317,
   -1317, -1317, -1317,    48,    48, -1317,   301,   534, -1317, -1317,
     535,   537,   539,   316,   318,   320,   546,   549,   550,   335,
     334,   560,   561,   562,   340,   341,   342,   343,   345,   353,
     347,   357,   358,   356,   360,   567,   361,   362,   364,   372,
     374,   570,   586,   596,   376,   377,   393,   394,   618,   620,
     621,   399,   623,   624,   625,   626,   627,   403,   406,   408,
     629,   630,   635,   636,   637,   417,   638,   641,   642,   643,
     644,   645,   646,   423,   424,   429,   647,   650, -1317,   675,
   -1317,   651,   653,   655,   431,   433,   437,   438,    95, -1317,
     657,   659,   662,   663,   664,   665,   443,   667,   668,   671,
     163, -1317,   672,   451,   220, -1317,   676,   678,   679,   680,
     681,   683,   684,   686, -1317,    65, -1317,   689,   692,   452,
     693,   694,   695,   471, -1317,   280,   699,   486,   487,   489,
   -1317,   302,   713,   715,   125, -1317,   492,   716,   495,   719,
     497,   498,   722,   723,    42, -1317,   724,   502,    39, -1317,
   -1317, -1317,   726,   725,   727,   728,   729, -1317, -1317, -1317,
     505,   507,   513, -1317, -1317,   760,   761,   764, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   547,
   -1317, -1317, -1317, -1317, -1317,   -98,   548,   551, -1317, -1317,
   -1317, -1317,   767,   770,   771, -1317,   552,   350,   774,   773,
     555, -1317, -1317, -1317,   780,   781,   782,   783,   784, -1317,
     787,   788,   785,   789,   795,   577,   578, -1317, -1317, -1317,
     800,   799, -1317,   802,   427,    63, -1317, -1317, -1317, -1317,
   -1317,   583,   584,   585,   807,   587,   588, -1317,   802,   589,
     809, -1317,   591, -1317, -1317,   802,   593,   594,   597,   598,
     599,   600,   601, -1317,   604,   605, -1317,   606,   609,   610,
   -1317, -1317,   611, -1317, -1317, -1317, -1317,   612,   773, -1317,
   -1317,   613, -1317,   614, -1317, -1317,    19,   633, -1317,   836,
   -1317, -1317,    48,   675,    39,    95,   420, -1317, -1317, -1317,
     123,   123,   835, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317,   837,   838,   839, -1317, -1317, -1317, -1317, -1317,
   -1317,   840, -1317, -1317, -1317,   170,   841,   842,   844,    67,
     185,   250,   845,   333,    42, -1317, -1317,   846,   144, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     848, -1317, -1317, -1317, -1317,   701, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   835,
   -1317,   259,   285,   309, -1317, -1317,   322, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,   852,   853,   854,   855,   856,   857,
     858,   859,   860,   861, -1317,   862,   863, -1317, -1317, -1317,
   -1317, -1317,   336, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317,   363, -1317,   869,   865,
   -1317, -1317,   870,   874, -1317, -1317,   872,   876, -1317, -1317,
     875,   877, -1317, -1317,   878,   879, -1317, -1317, -1317, -1317,
   -1317, -1317,    66, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     129, -1317, -1317,   880,   882, -1317, -1317,   881,   885, -1317,
     886,   887,   888,   889,   890,   891,   370, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,   892,   893,   894, -1317,   373, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   895, -1317,
     896, -1317, -1317, -1317, -1317, -1317, -1317,   384, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317,   883,   899, -1317,   900,
   -1317,   901, -1317, -1317, -1317,   388, -1317, -1317, -1317, -1317,
   -1317,   404, -1317,   286, -1317,   902,   903,   904,   905, -1317,
     405, -1317, -1317, -1317, -1317, -1317,   677, -1317,   906,   907,
   -1317, -1317,   908, -1317,   909, -1317, -1317, -1317,   910,   913,
     420, -1317,   914,   915,   916,   917,   696,   682,   697,   698,
     702,   703,   704,   705,   706,   707,   918,   708,   709,   921,
     922,   924,   931,   123, -1317, -1317,   123, -1317,   835,   163,
   -1317,   837,   280, -1317,   838,   302, -1317,   839,  1311, -1317,
     840,   170, -1317,   265,   841, -1317,    65, -1317,   842,  -103,
   -1317,   844,   711,   712,   714,   717,   720,   730,    67, -1317,
     721,   738,   746,   185, -1317,   936,   939,   942,   748,   945,
     753,   250, -1317,   250, -1317,   845,   754,   949,   766,   987,
     333, -1317, -1317,   143,   846, -1317,   776,   778,   792,   801,
     144, -1317, -1317,   994,  1014,   220, -1317,   848,  1024, -1317,
   -1317,   687,   810, -1317,     2,   811,   815,   826, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   183, -1317,
   -1317,   827,   829,   873,   884, -1317,   415, -1317,   418, -1317,
    1025, -1317,  1093, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     419, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317,  1098, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,  1095,  1101, -1317,
   -1317, -1317, -1317, -1317, -1317,  1097, -1317,   422, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     293,   897,   898, -1317,  1099, -1317, -1317,   425, -1317, -1317,
     911, -1317,    48, -1317, -1317,  1103, -1317, -1317, -1317, -1317,
   -1317,   426, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317,   912,   428, -1317,   802, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,  1311, -1317,
    1105,  1107,   919, -1317,   265, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317,    -5, -1317, -1317, -1317,  1108,   920,  1109,
     143, -1317, -1317, -1317, -1317, -1317,   923,   925, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,   432, -1317, -1317,
   -1317, -1317, -1317,  1110, -1317,   926, -1317, -1317, -1317,  1112,
    1113,  1114,  1115,    -5, -1317,  1118, -1317,   946,   928,   930,
    1116, -1317, -1317,   369, -1317, -1317, -1317, -1317, -1317,  1119,
     -52,  1118, -1317, -1317,  1121,  1117, -1317, -1317,  1124,  1125,
    1126, -1317,   434, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
      92, -1317,  1119,  1127,   929,   932,   933,  1128,   -52, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,   435, -1317, -1317,
   -1317, -1317,   935, -1317, -1317, -1317,   937, -1317,  1129,  1130,
      92, -1317, -1317, -1317,   938,   940, -1317, -1317, -1317
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   208,     9,   388,    11,   598,    13,
     627,    15,   516,    17,   525,    19,   564,    21,   350,    23,
     809,    25,   841,    27,    46,    39,     0,     0,     0,     0,
       0,   629,     0,   527,   566,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   839,   193,   226,
       0,     0,     0,   649,   651,   653,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   379,   514,   555,     0,   153,
     174,   459,   614,   616,     0,     0,     0,   312,   676,   618,
     341,   362,     0,   327,   711,   713,   790,   807,   181,   183,
       0,     0,     0,   851,   893,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     104,   134,   135,    93,    94,    95,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   101,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,    77,
      84,    85,    99,   100,   102,    96,    97,    98,    83,    88,
      89,    90,    91,    92,   103,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   443,   445,   447,   589,
     441,   449,     0,   453,   451,   671,   440,   393,   394,   395,
     396,   397,   420,   421,   422,   423,   424,   438,   410,   411,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   439,     0,   390,   400,   415,   416,   417,
     401,   403,   404,   406,   407,   408,   402,   398,   399,   418,
     419,   405,   412,   413,   414,   409,   611,     0,   610,   606,
     607,   605,     0,   600,   603,   604,   608,   609,   669,   655,
     657,   659,   663,   661,   667,   665,   648,   642,   646,   647,
       0,   630,   631,   643,   644,   645,   639,   634,   640,   636,
     637,   638,   641,   635,     0,   545,   286,     0,   549,   547,
     552,     0,   541,   542,     0,   528,   529,   532,   544,   533,
     534,   535,   551,   536,   537,   538,   539,   540,   582,     0,
       0,     0,   580,   581,   584,   585,     0,   567,   568,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   358,   360,
     355,     0,   352,   356,   357,     0,   826,     0,   829,     0,
       0,   833,   837,   824,   822,   823,     0,   811,   814,   815,
     816,   817,   818,   819,   820,   821,   848,     0,     0,   843,
     846,   847,    45,    50,     0,    37,    43,     0,    64,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    69,
      66,     0,     0,     0,     0,     0,     0,     0,   197,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     392,   389,     0,     0,   602,   599,     0,     0,     0,     0,
       0,     0,     0,     0,   628,   633,   517,     0,     0,     0,
       0,     0,     0,     0,   526,   531,     0,     0,     0,     0,
     565,   570,     0,     0,   354,   351,     0,     0,     0,     0,
       0,     0,     0,     0,   813,   810,     0,     0,   845,   842,
      49,    41,     0,     0,     0,     0,     0,   155,   156,   157,
       0,     0,     0,   191,   192,     0,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,     0,
     186,   187,   158,   159,   160,     0,     0,     0,   172,   173,
     180,   185,     0,     0,     0,   152,     0,     0,     0,     0,
       0,   455,   456,   457,     0,     0,     0,     0,     0,   710,
       0,     0,     0,     0,     0,     0,     0,   188,   189,   190,
       0,     0,    68,     0,     0,     0,   220,   221,   222,   223,
     196,     0,     0,     0,     0,     0,     0,   458,     0,     0,
       0,   391,     0,   613,   601,     0,     0,     0,     0,     0,
       0,     0,     0,   632,     0,     0,   543,     0,     0,     0,
     554,   530,     0,   586,   587,   588,   569,     0,     0,   353,
     825,     0,   828,     0,   831,   832,     0,     0,   812,     0,
     850,   844,     0,     0,     0,     0,     0,   650,   652,   654,
       0,     0,   241,   151,   163,   164,   165,   166,   167,   162,
     169,   171,   381,   518,   557,   154,   176,   177,   178,   179,
     175,   461,    38,   615,   617,     0,     0,   620,   343,     0,
       0,     0,   715,     0,     0,   182,   184,     0,     0,    51,
     211,   214,   215,   213,   218,   219,   217,   444,   446,   448,
     591,   442,   450,   454,   452,     0,   612,   670,   656,   658,
     660,   664,   662,   668,   666,   546,   287,   550,   548,   553,
     583,   359,   361,   827,   830,   835,   836,   834,   838,   241,
      42,     0,     0,     0,   233,   235,     0,   228,   231,   232,
     274,   279,   281,   283,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   297,     0,     0,   304,   306,   308,
     310,   273,     0,   248,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,     0,   246,     0,   242,
     243,   386,     0,   382,   383,   523,     0,   519,   520,   562,
       0,   558,   559,   466,     0,   462,   463,   322,   323,   324,
     325,   326,     0,   314,   317,   318,   319,   320,   321,   681,
       0,   678,   625,     0,   621,   622,   348,     0,   344,   345,
       0,     0,     0,     0,     0,     0,     0,   364,   367,   368,
     369,   370,   371,   372,     0,     0,     0,   337,     0,   329,
     332,   333,   334,   335,   336,   737,   742,   744,     0,   748,
       0,   736,   730,   731,   732,   734,   735,     0,   722,   725,
     726,   727,   728,   733,   729,   720,     0,   716,   717,     0,
     802,     0,   805,   798,   799,     0,   792,   795,   796,   797,
     800,     0,   856,     0,   853,     0,     0,     0,     0,   902,
       0,   895,   898,   899,   900,   901,    53,   596,     0,   592,
     593,   674,     0,   673,     0,    62,   840,   194,     0,     0,
     230,   227,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   225,   238,     0,   240,   245,     0,
     380,   385,   527,   515,   522,   566,   556,   561,     0,   460,
     465,   316,   313,   683,   680,   677,   629,   619,   624,     0,
     342,   347,     0,     0,     0,     0,     0,     0,   366,   363,
       0,     0,     0,   331,   328,     0,     0,     0,     0,     0,
       0,   724,   712,     0,   714,   719,     0,     0,     0,     0,
     794,   791,   808,     0,   855,   852,     0,     0,     0,     0,
     897,   894,    55,     0,    54,     0,   590,   595,     0,   672,
     849,     0,     0,   229,     0,     0,     0,     0,   285,   288,
     289,   290,   291,   292,   293,   294,   295,   296,     0,   302,
     303,     0,     0,     0,     0,   249,     0,   244,     0,   384,
       0,   521,     0,   560,   513,   488,   489,   490,   474,   475,
     493,   494,   495,   496,   497,   511,   477,   478,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   512,   471,   472,   473,   486,   487,   483,   484,   485,
       0,   468,   476,   491,   492,   479,   480,   481,   482,   464,
     315,   705,   707,     0,   699,   700,   701,   702,   703,   704,
     692,   693,   697,   698,   694,   695,   696,     0,   684,   685,
     688,   689,   690,   691,   679,     0,   623,     0,   346,   373,
     374,   375,   376,   377,   378,   365,   338,   339,   340,   330,
       0,     0,     0,   746,     0,   747,   723,     0,   718,   801,
       0,   804,     0,   793,   871,     0,   869,   867,   861,   865,
     866,     0,   858,   863,   864,   862,   854,   903,   904,   905,
     906,   896,    52,    57,     0,   594,     0,   234,   236,   276,
     277,   278,   275,   280,   282,   284,   299,   300,   301,   298,
     305,   307,   309,   311,   247,   387,   524,   563,   470,   467,
       0,     0,     0,   682,   687,   626,   349,   739,   740,   741,
     738,   743,   745,     0,   721,   803,   806,     0,     0,     0,
     860,   857,    56,   597,   675,   469,     0,     0,   709,   686,
     760,   763,   765,   767,   759,   758,   757,     0,   750,   753,
     754,   755,   756,     0,   868,     0,   859,   706,   708,     0,
       0,     0,     0,   752,   749,     0,   870,     0,     0,     0,
       0,   751,   876,     0,   873,   762,   761,   764,   766,   769,
       0,   875,   872,   774,     0,   770,   771,   886,     0,     0,
       0,   891,     0,   878,   881,   882,   883,   884,   885,   874,
       0,   768,   773,     0,     0,     0,     0,     0,   880,   877,
     786,   788,   785,   779,   781,   783,   784,     0,   776,   780,
     782,   772,     0,   888,   889,   890,     0,   879,     0,     0,
     778,   775,   887,   892,     0,     0,   777,   787,   789
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317,   -59, -1317,  -573, -1317,   447,
   -1317, -1317, -1317, -1317, -1317, -1317,  -629, -1317, -1317, -1317,
     -67, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   439,   640,
     -38,    36,    38,   -54,   -51,   -39,   -37,   -21,   -20,   -19,
   -1317, -1317, -1317, -1317,    -8, -1317, -1317,    13,    53,    56,
      57,    58,    59, -1317, -1317,    60, -1317,    61, -1317,    64,
      71,    72, -1317, -1317,    74,    75, -1317,    76, -1317,    77,
   -1317, -1317, -1317, -1317, -1317,    40, -1317, -1317, -1317,   440,
     628, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
     142, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   351,
   -1317,   133, -1317,  -697,   140, -1317, -1317, -1317, -1316, -1317,
   -1303, -1317, -1317, -1317, -1317,     1, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317,  -729, -1317,  -725, -1317,  -724, -1317, -1317, -1317, -1317,
   -1317, -1317,   136, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317,   103, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   119,
   -1317, -1317, -1317,   115,   608, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317,   127, -1317, -1317, -1317, -1317, -1317, -1317,  -995,
   -1317, -1317, -1317,   156, -1317, -1317, -1317,   159,   649, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,  -992, -1317,    33,
   -1317,    80, -1317,    78,    79,    82, -1317, -1317, -1317, -1317,
   -1317,   150, -1317, -1317,   -87,   -62, -1317, -1317, -1317, -1317,
   -1317,   158, -1317, -1317, -1317,   161, -1317,   631, -1317,   -63,
   -1317, -1317, -1317, -1317, -1317,   -61, -1317, -1317, -1317, -1317,
   -1317,   -31, -1317, -1317, -1317,   157, -1317, -1317, -1317,   160,
   -1317,   632, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,   100, -1317, -1317, -1317,   104,   654,
   -1317, -1317, -1317,   -49, -1317,    -3, -1317,   -41, -1317, -1317,
   -1317,   152, -1317, -1317, -1317,   155, -1317,   652,     9, -1317,
      16, -1317,    20, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
    -985, -1317, -1317, -1317, -1317, -1317, -1317, -1317,   162, -1317,
   -1317, -1317,   -82, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317,   134, -1317,   132,   137,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317,  -129, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317,  -162, -1317, -1317,  -188, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317,   138, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317,   449,   639, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317,   496,   648, -1317, -1317, -1317,
   -1317, -1317, -1317,   141, -1317, -1317,   -86, -1317, -1317, -1317,
   -1317, -1317, -1317,  -136, -1317, -1317,  -159, -1317, -1317, -1317,
   -1317, -1317, -1317, -1317, -1317, -1317, -1317,   126, -1317, -1317,
   -1317, -1317
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   733,
      82,    83,    39,    64,    79,    80,   750,   966,  1073,  1074,
     821,    41,    66,    85,   427,    86,    43,    67,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   455,   171,   172,   472,   173,   174,   175,   176,
     177,   178,   179,   461,   719,   180,   462,   181,   463,   182,
     183,   184,   473,   730,   185,   186,   491,   187,   492,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   431,   235,
     236,    45,    68,   237,   501,   238,   502,   753,   239,   503,
     756,   240,   241,   242,   243,   197,   441,   198,   432,   796,
     797,   798,   978,   799,   979,   199,   442,   200,   443,   848,
     849,   850,  1006,   822,   823,   824,   982,  1242,   825,   983,
     826,   984,   827,   985,   828,   829,   538,   830,   831,   832,
     833,   834,   835,   836,   837,   838,   839,   996,  1249,   840,
     841,   842,   999,   843,  1000,   844,  1001,   845,  1002,   201,
     480,   872,   873,   874,   875,   876,   877,   878,   202,   486,
     908,   909,   910,   911,   912,   203,   483,   887,   888,   889,
    1029,    59,    75,   391,   392,   393,   552,   394,   553,   204,
     484,   896,   897,   898,   899,   900,   901,   902,   903,   205,
     468,   852,   853,   854,  1009,    47,    69,   284,   285,   286,
     514,   287,   510,   288,   511,   289,   512,   290,   515,   291,
     518,   292,   517,   206,   207,   208,   296,   209,   474,   864,
     865,   866,  1018,  1150,  1151,   210,   469,    53,    72,   856,
     857,   858,  1012,    55,    73,   354,   355,   356,   357,   358,
     359,   360,   537,   361,   541,   362,   540,   363,   364,   542,
     365,   211,   470,   860,   861,   862,  1015,    57,    74,   376,
     377,   378,   379,   380,   546,   381,   382,   383,   384,   385,
     298,   513,   968,   969,   970,  1075,    49,    70,   312,   313,
     314,   522,   315,   212,   475,   213,   476,   214,   482,   883,
     884,   885,  1026,    51,    71,   330,   331,   332,   215,   436,
     216,   437,   217,   438,   336,   527,   337,   528,   338,   529,
     339,   531,   340,   530,   341,   533,   342,   532,   343,   526,
     305,   519,   972,   973,  1078,   218,   481,   880,   881,  1023,
    1177,  1178,  1179,  1180,  1181,  1260,  1182,  1261,  1183,   219,
     220,   487,   221,   488,   936,   937,   938,  1053,   927,   928,
     929,  1045,  1270,   930,  1046,   931,  1047,   932,   933,   934,
    1049,  1297,  1298,  1299,  1309,  1326,  1300,  1310,  1301,  1311,
    1302,  1312,  1334,  1335,  1336,  1350,  1367,  1368,  1369,  1378,
    1370,  1379,   222,   489,   945,   946,   947,   948,  1057,   949,
     950,  1059,   223,   490,    61,    76,   406,   407,   408,   409,
     557,   410,   411,   559,   412,   413,   414,   562,   787,   415,
     563,   224,   430,    63,    77,   418,   419,   420,   566,   421,
     225,   496,   953,   954,  1063,  1221,  1222,  1223,  1224,  1279,
    1225,  1277,  1323,  1324,  1330,  1342,  1343,  1344,  1353,  1345,
    1346,  1347,  1348,  1357,   226,   497,   960,   961,   962,   963,
     964,   965
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   256,   308,   326,    78,   352,   372,   390,   403,
     344,   374,   922,   375,   846,   260,   923,   924,   261,   244,
     299,   316,   328,  1143,   366,   386,  1144,   404,   301,   763,
     262,   257,   263,  1158,  1363,  1290,   767,   785,   297,   311,
     327,   388,   389,  1239,  1240,  1241,   732,  1364,   264,   265,
     266,   416,   417,    29,   428,    30,    40,    31,   499,   429,
      81,   267,    28,   500,  1363,   245,   300,   317,   329,  1021,
     367,   387,  1022,   405,   353,   373,   508,  1364,   302,    84,
     333,   509,   268,   754,   755,   303,   126,   334,    42,   304,
      44,   335,   714,   715,   716,   717,   520,    93,    94,    95,
     422,   521,   424,   309,    46,   258,    48,   259,    50,   283,
     227,   228,   132,   133,   229,   732,   524,   230,   231,   232,
     233,   525,   269,   155,    52,   270,   271,   272,   273,   274,
     275,   718,  1024,   276,   554,  1025,   801,   802,   425,   555,
     277,   278,    54,   279,   280,   281,   282,   293,   294,  1337,
     310,   295,  1338,  1339,  1340,  1341,    56,   564,    58,   132,
     133,   127,   565,   800,  1291,  1292,  1293,   801,   802,   803,
     804,   805,   806,   807,   808,   809,   810,   811,   812,   813,
     814,    60,   132,   133,   815,   816,   817,   818,   819,   820,
     423,   318,   426,    91,    92,    93,    94,    95,    96,   319,
     320,   321,   322,   323,   324,   325,   568,   786,    62,   132,
     133,   569,   132,   133,   890,   891,   892,   893,   894,   895,
     346,   155,   395,   396,   397,   398,   399,   400,   401,   402,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     346,  1246,  1247,  1248,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   534,   246,   247,   248,   433,   127,
     132,   133,   499,  1143,  1360,  1361,  1144,   975,   155,   388,
     389,   129,   130,  1158,    32,    33,    34,    35,   249,   434,
     132,   133,   250,   251,   252,   134,   135,   136,   568,  1064,
     253,   155,  1065,   976,   254,   435,   139,    93,    94,    95,
      96,   439,   132,   133,   255,   867,   868,   869,   870,  1106,
     871,   440,   508,   817,   818,   819,   127,   977,   155,   444,
     345,   155,   922,   445,   922,   980,   923,   924,   923,   924,
     981,   446,   101,   102,   103,   447,   306,   132,   133,  1003,
     904,   905,   906,  1214,  1004,  1215,  1216,   253,   448,   155,
     449,   254,   307,   955,   956,   957,   958,   148,   149,   450,
     126,   127,   346,   451,   570,   571,  1003,   132,   133,   155,
     155,  1005,  1331,  1038,   535,  1332,  1043,   346,  1039,   347,
     348,  1044,   132,   133,   349,   350,   351,  1051,   536,   155,
     452,  1060,  1052,  1161,  1162,  1163,  1061,   132,   133,   346,
     368,   347,   348,   369,   370,   371,   453,   564,  1070,   544,
     915,   155,  1062,  1071,   916,   917,   918,   919,  1003,   132,
     133,   520,  1258,  1254,   920,   554,  1255,  1259,  1051,  1280,
    1266,   524,   156,  1274,  1281,  1313,  1283,  1358,  1380,   545,
    1314,   234,  1359,  1381,   751,   752,   155,   794,   795,   454,
     132,   133,   456,   256,  1267,  1268,  1269,   308,   457,   244,
     726,   727,   728,   729,   458,   459,   260,   460,   326,   261,
     464,   299,   465,   466,   467,   316,   155,   471,   352,   301,
     477,   262,   257,   263,   372,   478,   328,   479,   374,   297,
     375,   155,   485,   311,   493,   494,   366,   403,   495,   264,
     265,   266,   386,   498,   327,   245,   155,   504,   505,   939,
     940,   941,   267,   506,   507,   404,   516,   300,   523,   539,
     543,   317,   547,   548,   549,   550,   551,   572,   155,   302,
     556,   558,   329,   268,   560,   561,   303,   567,   573,   574,
     304,   575,   367,   576,   333,   577,   353,   578,   387,   579,
     580,   334,   373,   581,   582,   335,   258,   309,   259,   942,
     283,   405,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   599,   592,   269,   605,   594,   270,   271,   272,   273,
     274,   275,   593,   597,   276,   595,   596,   598,   600,   601,
     606,   277,   278,   602,   279,   280,   281,   282,   293,   294,
     607,   603,   295,   604,   310,   608,   609,  1284,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   610,   612,   611,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   624,   625,   622,   156,   623,   234,   626,
     627,   628,   630,   790,   629,   631,   632,   633,   634,   635,
     636,   640,   637,   638,   641,   643,   244,   644,   639,   645,
     646,   651,   647,   652,   648,   649,   653,   654,   655,   656,
     657,   658,   659,   907,   921,   660,   662,   403,   663,   676,
     665,   959,   666,   667,   668,   669,    87,   670,   671,    88,
     672,   913,   925,   674,   943,   404,   675,   677,   678,   679,
     680,    89,   245,   682,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   683,   684,   687,   685,   688,
     691,   690,   692,   693,   694,   695,   696,   697,   699,   700,
     702,   707,   703,   708,   704,   705,   706,   914,   926,   709,
     944,   405,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   710,   711,   712,
     126,   127,   722,   713,   720,   723,   724,   721,   725,   731,
      30,   734,   128,   129,   130,   735,   736,   737,   738,   131,
     742,   739,   132,   133,   740,   741,   743,   134,   135,   136,
     137,   138,   744,   745,   746,   747,   748,   749,   139,   757,
     758,   759,   760,   761,   762,   764,   765,   766,   140,   768,
     769,   141,   788,   770,   771,   772,   773,   774,   142,   143,
     775,   776,   777,   144,   145,   778,   779,   780,   781,   783,
     784,   789,   847,   971,   851,   855,   859,   863,   879,   882,
     146,   886,   935,   952,   147,   967,   986,   987,   988,   989,
     990,   991,   992,   993,   994,   995,   997,   998,  1008,   148,
     149,   150,   151,   152,   153,  1007,  1010,  1011,  1013,  1014,
    1017,  1016,  1020,   154,  1019,  1028,  1027,  1030,  1031,  1054,
    1032,  1033,  1034,  1035,  1036,  1037,  1040,  1041,  1042,  1048,
    1050,   155,  1055,  1072,  1056,  1058,  1066,  1067,  1068,  1069,
    1077,  1089,  1076,  1237,  1081,  1080,  1079,  1082,  1084,  1085,
    1086,  1087,  1098,  1088,  1090,  1101,  1102,  1091,  1103,  1092,
    1093,  1094,  1095,  1096,  1097,  1104,  1100,  1099,  1189,  1190,
    1200,  1191,   256,  1201,  1192,   352,  1202,  1193,   372,  1204,
    1196,  1114,   374,  1210,   375,   260,  1164,  1194,   261,   326,
     299,  1170,   390,   366,  1118,  1197,   386,  1119,   301,  1153,
     262,   257,   263,  1198,  1172,  1203,   907,   328,   297,  1120,
    1115,  1121,  1205,  1209,   921,  1165,   921,  1152,   264,   265,
     266,  1212,  1171,  1211,   913,   327,  1217,  1122,  1123,  1124,
    1232,   267,   925,   959,   925,  1227,   300,  1228,   308,   367,
    1125,   943,   387,   353,  1219,  1154,   373,  1233,   302,  1142,
    1173,  1229,   268,   329,  1169,   303,   316,  1155,  1236,   304,
    1230,  1126,  1174,  1256,  1156,   333,  1238,  1243,  1157,  1175,
     914,  1244,   334,  1176,   311,   258,   335,   259,   926,   283,
     926,  1145,  1245,  1250,  1116,  1251,  1117,   944,  1141,  1166,
    1220,  1167,   269,  1168,  1218,   270,   271,   272,   273,   274,
     275,  1127,   317,   276,  1128,  1129,  1130,  1131,  1132,  1133,
     277,   278,  1134,   279,   280,   281,   282,   293,   294,  1135,
    1136,   295,  1137,  1138,  1139,  1140,  1147,  1148,  1146,  1252,
    1149,  1257,  1262,  1263,  1264,  1265,  1273,  1278,   309,  1286,
    1253,  1287,  1303,  1305,  1325,  1315,  1317,  1318,  1319,  1320,
    1352,  1329,  1083,  1271,  1272,  1322,  1333,  1351,  1354,  1355,
    1356,  1372,  1376,  1384,  1385,   782,   650,  1275,  1282,   642,
     974,  1107,   791,  1105,  1187,   793,  1199,  1304,  1288,  1307,
    1188,  1308,  1316,  1276,  1327,   310,  1328,  1160,  1373,  1374,
    1375,  1382,   689,  1383,  1387,  1195,  1388,  1109,  1108,   661,
    1159,  1285,  1111,  1110,  1113,  1112,   681,  1235,   664,  1234,
    1186,  1185,  1289,   686,  1321,  1207,  1184,   673,  1206,  1208,
    1371,  1114,  1386,   951,  1306,  1349,  1231,  1164,  1213,  1377,
     792,     0,  1170,   698,  1118,  1226,  1294,  1119,     0,  1153,
       0,     0,     0,  1217,     0,  1172,   701,     0,     0,  1120,
    1115,  1121,     0,     0,  1295,     0,  1165,  1152,     0,     0,
       0,  1219,     0,  1171,     0,     0,     0,  1122,  1123,  1124,
       0,     0,     0,     0,     0,     0,  1294,     0,     0,     0,
    1125,     0,     0,     0,     0,  1154,     0,     0,     0,  1142,
       0,  1173,     0,     0,  1295,  1169,     0,  1155,     0,     0,
    1296,  1126,     0,  1174,  1156,     0,     0,  1220,  1157,     0,
    1175,  1218,     0,  1362,  1176,     0,     0,     0,     0,     0,
       0,  1145,     0,     0,  1116,     0,  1117,     0,  1141,     0,
    1166,  1365,  1167,     0,  1168,     0,     0,     0,     0,     0,
    1296,  1127,     0,  1362,  1128,  1129,  1130,  1131,  1132,  1133,
       0,     0,  1134,     0,     0,     0,     0,     0,     0,  1135,
    1136,  1365,  1137,  1138,  1139,  1140,  1147,  1148,  1146,     0,
    1149,    91,    92,    93,    94,    95,    96,  1366,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1366,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,   127,   346,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
     130,     0,     0,     0,     0,     0,     0,     0,   132,   133,
       0,   251,     0,   134,   135,   136,     0,     0,   253,     0,
       0,     0,   254,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   255,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148,   149,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   155
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   741,    74,   711,    69,   741,   741,    69,    68,
      69,    70,    71,  1018,    73,    74,  1018,    76,    69,   658,
      69,    69,    69,  1018,  1350,    40,   665,    18,    69,    70,
      71,   144,   145,    41,    42,    43,   619,  1350,    69,    69,
      69,    12,    13,     5,     3,     7,     7,     9,     3,     8,
     226,    69,     0,     8,  1380,    68,    69,    70,    71,     3,
      73,    74,     6,    76,    73,    74,     3,  1380,    69,    10,
      71,     8,    69,    20,    21,    69,    95,    71,     7,    69,
       7,    71,   190,   191,   192,   193,     3,    32,    33,    34,
       6,     8,     4,    70,     7,    69,     7,    69,     7,    69,
      15,    16,   117,   118,    19,   688,     3,    22,    23,    24,
      25,     8,    69,   226,     7,    69,    69,    69,    69,    69,
      69,   229,     3,    69,     3,     6,    44,    45,     8,     8,
      69,    69,     7,    69,    69,    69,    69,    69,    69,   201,
      70,    69,   204,   205,   206,   207,     7,     3,     7,   117,
     118,    96,     8,    40,   169,   170,   171,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,     7,   117,   118,    61,    62,    63,    64,    65,    66,
       3,   126,     3,    30,    31,    32,    33,    34,    35,   134,
     135,   136,   137,   138,   139,   140,     3,   188,     7,   117,
     118,     8,   117,   118,   147,   148,   149,   150,   151,   152,
      97,   226,   180,   181,   182,   183,   184,   185,   186,   187,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      97,    58,    59,    60,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     8,    92,    93,    94,     4,    96,
     117,   118,     3,  1258,   172,   173,  1258,     8,   226,   144,
     145,   108,   109,  1258,   226,   227,   228,   229,   115,     4,
     117,   118,   119,   120,   121,   122,   123,   124,     3,     3,
     127,   226,     6,     8,   131,     4,   133,    32,    33,    34,
      35,     4,   117,   118,   141,   135,   136,   137,   138,  1006,
     140,     4,     3,    63,    64,    65,    96,     8,   226,     4,
      40,   226,  1051,     4,  1053,     3,  1051,  1051,  1053,  1053,
       8,     4,    67,    68,    69,     4,   116,   117,   118,     3,
     155,   156,   157,   200,     8,   202,   203,   127,     4,   226,
       4,   131,   132,   209,   210,   211,   212,   194,   195,     4,
      95,    96,    97,     4,   423,   424,     3,   117,   118,   226,
     226,     8,     3,     3,     3,     6,     3,    97,     8,    99,
     100,     8,   117,   118,   104,   105,   106,     3,     8,   226,
       4,     3,     8,   128,   129,   130,     8,   117,   118,    97,
      98,    99,   100,   101,   102,   103,     4,     3,     3,     8,
     160,   226,     8,     8,   164,   165,   166,   167,     3,   117,
     118,     3,     3,     8,   174,     3,     8,     8,     3,     3,
       8,     3,   499,     8,     8,     3,     8,     3,     3,     3,
       8,   508,     8,     8,    17,    18,   226,    27,    28,     4,
     117,   118,     4,   520,   161,   162,   163,   524,     4,   508,
     110,   111,   112,   113,     4,     4,   520,     4,   535,   520,
       4,   520,     4,     4,     4,   524,   226,     4,   545,   520,
       4,   520,   520,   520,   551,     4,   535,     4,   551,   520,
     551,   226,     4,   524,     4,     4,   545,   564,     4,   520,
     520,   520,   551,     4,   535,   508,   226,     4,     4,   176,
     177,   178,   520,     4,     4,   564,     4,   520,     4,     4,
       4,   524,     4,     4,     4,     8,     3,   226,   226,   520,
       4,     4,   535,   520,     4,     4,   520,     4,     4,     4,
     520,     4,   545,     4,   535,   229,   545,   229,   551,   229,
       4,   535,   551,     4,     4,   535,   520,   524,   520,   226,
     520,   564,   227,   229,     4,     4,     4,   227,   227,   227,
     227,     4,   227,   520,     4,   228,   520,   520,   520,   520,
     520,   520,   229,   227,   520,   228,   228,   227,   227,   227,
       4,   520,   520,   229,   520,   520,   520,   520,   520,   520,
       4,   229,   520,   229,   524,   229,   229,  1236,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   228,     4,   229,     4,     4,   227,     4,     4,     4,
       4,     4,   229,     4,     4,   229,   703,   229,   705,     4,
       4,     4,     4,   702,   227,     4,     4,     4,     4,     4,
       4,     4,   229,   229,     4,     4,   705,     4,   229,     4,
     229,     4,   229,     4,   227,   227,     4,     4,     4,     4,
     227,     4,     4,   740,   741,     4,     4,   744,   227,   227,
       4,   748,     4,     4,     4,     4,    11,     4,     4,    14,
       4,   740,   741,     4,   743,   744,     4,     4,     4,     4,
     229,    26,   705,     4,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,   229,   229,     4,   229,     4,
       4,   229,   227,     4,   227,   227,     4,     4,     4,   227,
       4,   226,     7,   226,     7,     7,     7,   740,   741,   226,
     743,   744,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,     7,     7,     5,
      95,    96,     5,   226,   226,     5,     5,   226,   226,     5,
       7,   226,   107,   108,   109,     5,     5,     5,     5,   114,
       5,     7,   117,   118,     7,     7,     7,   122,   123,   124,
     125,   126,     7,   226,   226,     5,     7,     5,   133,   226,
     226,   226,     5,   226,   226,   226,     7,   226,   143,   226,
     226,   146,   189,   226,   226,   226,   226,   226,   153,   154,
     226,   226,   226,   158,   159,   226,   226,   226,   226,   226,
     226,     5,     7,   142,     7,     7,     7,     7,     7,     7,
     175,     7,     7,     7,   179,     7,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   194,
     195,   196,   197,   198,   199,     6,     6,     3,     6,     3,
       3,     6,     3,   208,     6,     3,     6,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   226,     3,   226,     4,     4,     4,     4,     4,     4,
       3,   229,     6,   226,     4,     6,     8,     4,     4,     4,
       4,     4,     4,   227,   227,     4,     4,   229,     4,   227,
     227,   227,   227,   227,   227,     4,   227,   229,   227,   227,
       4,   227,  1009,     4,   227,  1012,     4,   227,  1015,     4,
     229,  1018,  1015,     4,  1015,  1009,  1023,   227,  1009,  1026,
    1009,  1023,  1029,  1012,  1018,   227,  1015,  1018,  1009,  1018,
    1009,  1009,  1009,   227,  1023,   227,  1043,  1026,  1009,  1018,
    1018,  1018,   229,   229,  1051,  1023,  1053,  1018,  1009,  1009,
    1009,     4,  1023,   227,  1043,  1026,  1063,  1018,  1018,  1018,
       6,  1009,  1051,  1070,  1053,   229,  1009,   229,  1075,  1012,
    1018,  1060,  1015,  1012,  1063,  1018,  1015,     3,  1009,  1018,
    1023,   229,  1009,  1026,  1023,  1009,  1075,  1018,     4,  1009,
     229,  1018,  1023,     8,  1018,  1026,   226,   226,  1018,  1023,
    1043,   226,  1026,  1023,  1075,  1009,  1026,  1009,  1051,  1009,
    1053,  1018,   226,   226,  1018,   226,  1018,  1060,  1018,  1023,
    1063,  1023,  1009,  1023,  1063,  1009,  1009,  1009,  1009,  1009,
    1009,  1018,  1075,  1009,  1018,  1018,  1018,  1018,  1018,  1018,
    1009,  1009,  1018,  1009,  1009,  1009,  1009,  1009,  1009,  1018,
    1018,  1009,  1018,  1018,  1018,  1018,  1018,  1018,  1018,   226,
    1018,     8,     4,     8,     3,     8,     7,     4,  1075,     4,
     226,     4,     4,     4,   168,     5,     4,     4,     4,     4,
       3,     5,   980,   226,   226,     7,     7,     6,     4,     4,
       4,     4,     4,     4,     4,   688,   508,   226,   226,   499,
     789,  1008,   703,  1003,  1029,   705,  1043,   227,   229,   226,
    1031,   226,   226,  1212,   226,  1075,   226,  1021,   229,   227,
     227,   226,   554,   226,   226,  1038,   226,  1011,  1009,   520,
    1020,  1258,  1014,  1012,  1017,  1015,   545,  1077,   524,  1075,
    1028,  1026,  1264,   551,  1313,  1053,  1024,   535,  1051,  1055,
    1352,  1258,  1380,   744,  1280,  1331,  1070,  1264,  1060,  1358,
     704,    -1,  1264,   564,  1258,  1064,  1273,  1258,    -1,  1258,
      -1,    -1,    -1,  1280,    -1,  1264,   568,    -1,    -1,  1258,
    1258,  1258,    -1,    -1,  1273,    -1,  1264,  1258,    -1,    -1,
      -1,  1280,    -1,  1264,    -1,    -1,    -1,  1258,  1258,  1258,
      -1,    -1,    -1,    -1,    -1,    -1,  1313,    -1,    -1,    -1,
    1258,    -1,    -1,    -1,    -1,  1258,    -1,    -1,    -1,  1258,
      -1,  1264,    -1,    -1,  1313,  1264,    -1,  1258,    -1,    -1,
    1273,  1258,    -1,  1264,  1258,    -1,    -1,  1280,  1258,    -1,
    1264,  1280,    -1,  1350,  1264,    -1,    -1,    -1,    -1,    -1,
      -1,  1258,    -1,    -1,  1258,    -1,  1258,    -1,  1258,    -1,
    1264,  1350,  1264,    -1,  1264,    -1,    -1,    -1,    -1,    -1,
    1313,  1258,    -1,  1380,  1258,  1258,  1258,  1258,  1258,  1258,
      -1,    -1,  1258,    -1,    -1,    -1,    -1,    -1,    -1,  1258,
    1258,  1380,  1258,  1258,  1258,  1258,  1258,  1258,  1258,    -1,
    1258,    30,    31,    32,    33,    34,    35,  1350,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1380,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    -1,    -1,    -1,    96,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
      -1,   120,    -1,   122,   123,   124,    -1,    -1,   127,    -1,
      -1,    -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   194,   195,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   226
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,     0,     5,
       7,     9,   226,   227,   228,   229,   245,   246,   247,   252,
       7,   261,     7,   266,     7,   321,     7,   435,     7,   516,
       7,   533,     7,   467,     7,   473,     7,   497,     7,   411,
       7,   634,     7,   653,   253,   248,   262,   267,   322,   436,
     517,   534,   468,   474,   498,   412,   635,   654,   245,   254,
     255,   226,   250,   251,    10,   263,   265,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    95,    96,   107,   108,
     109,   114,   117,   118,   122,   123,   124,   125,   126,   133,
     143,   146,   153,   154,   158,   159,   175,   179,   194,   195,
     196,   197,   198,   199,   208,   226,   260,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   283,   284,   286,   287,   288,   289,   290,   291,   292,
     295,   297,   299,   300,   301,   304,   305,   307,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   335,   337,   345,
     347,   389,   398,   405,   419,   429,   453,   454,   455,   457,
     465,   491,   523,   525,   527,   538,   540,   542,   565,   579,
     580,   582,   622,   632,   651,   660,   684,    15,    16,    19,
      22,    23,    24,    25,   260,   319,   320,   323,   325,   328,
     331,   332,   333,   334,   523,   525,    92,    93,    94,   115,
     119,   120,   121,   127,   131,   141,   260,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   284,   287,   288,
     289,   290,   291,   292,   295,   297,   299,   300,   301,   304,
     305,   307,   309,   315,   437,   438,   439,   441,   443,   445,
     447,   449,   451,   453,   454,   455,   456,   491,   510,   523,
     525,   527,   538,   540,   542,   560,   116,   132,   260,   449,
     451,   491,   518,   519,   520,   522,   523,   525,   126,   134,
     135,   136,   137,   138,   139,   140,   260,   491,   523,   525,
     535,   536,   537,   538,   540,   542,   544,   546,   548,   550,
     552,   554,   556,   558,   465,    40,    97,    99,   100,   104,
     105,   106,   260,   365,   475,   476,   477,   478,   479,   480,
     481,   483,   485,   487,   488,   490,   523,   525,    98,   101,
     102,   103,   260,   365,   479,   485,   499,   500,   501,   502,
     503,   505,   506,   507,   508,   509,   523,   525,   144,   145,
     260,   413,   414,   415,   417,   180,   181,   182,   183,   184,
     185,   186,   187,   260,   523,   525,   636,   637,   638,   639,
     641,   642,   644,   645,   646,   649,    12,    13,   655,   656,
     657,   659,     6,     3,     4,     8,     3,   264,     3,     8,
     652,   318,   338,     4,     4,     4,   539,   541,   543,     4,
       4,   336,   346,   348,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   282,     4,     4,     4,     4,
       4,   293,   296,   298,     4,     4,     4,     4,   430,   466,
     492,     4,   285,   302,   458,   524,   526,     4,     4,     4,
     390,   566,   528,   406,   420,     4,   399,   581,   583,   623,
     633,   306,   308,     4,     4,     4,   661,   685,     4,     3,
       8,   324,   326,   329,     4,     4,     4,     4,     3,     8,
     442,   444,   446,   511,   440,   448,     4,   452,   450,   561,
       3,     8,   521,     4,     3,     8,   559,   545,   547,   549,
     553,   551,   557,   555,     8,     3,     8,   482,   366,     4,
     486,   484,   489,     4,     8,     3,   504,     4,     4,     4,
       8,     3,   416,   418,     3,     8,     4,   640,     4,   643,
       4,     4,   647,   650,     3,     8,   658,     4,     3,     8,
     245,   245,   226,     4,     4,     4,     4,   229,   229,   229,
       4,     4,     4,   227,   229,     4,     4,     4,   227,   227,
     227,   227,   227,   229,   228,   228,   228,   227,   227,     4,
     227,   227,   229,   229,   229,     4,     4,     4,   229,   229,
     228,   229,     4,     4,     4,   227,     4,     4,     4,     4,
       4,   229,   229,   229,     4,     4,     4,     4,     4,   227,
       4,     4,     4,     4,     4,     4,     4,   229,   229,   229,
       4,     4,   269,     4,     4,     4,   229,   229,   227,   227,
     320,     4,     4,     4,     4,     4,     4,   227,     4,     4,
       4,   438,     4,   227,   519,     4,     4,     4,     4,     4,
       4,     4,     4,   537,     4,     4,   227,     4,     4,     4,
     229,   477,     4,   229,   229,   229,   501,     4,     4,   414,
     229,     4,   227,     4,   227,   227,     4,     4,   637,     4,
     227,   656,     4,     7,     7,     7,     7,   226,   226,   226,
       7,     7,     5,   226,   190,   191,   192,   193,   229,   294,
     226,   226,     5,     5,     5,   226,   110,   111,   112,   113,
     303,     5,   247,   249,   226,     5,     5,     5,     5,     7,
       7,     7,     5,     7,     7,   226,   226,     5,     7,     5,
     256,    17,    18,   327,    20,    21,   330,   226,   226,   226,
       5,   226,   226,   256,   226,     7,   226,   256,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   249,   226,   226,    18,   188,   648,   189,     5,
     245,   268,   655,   319,    27,    28,   339,   340,   341,   343,
      40,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    61,    62,    63,    64,    65,
      66,   260,   353,   354,   355,   358,   360,   362,   364,   365,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     379,   380,   381,   383,   385,   387,   353,     7,   349,   350,
     351,     7,   431,   432,   433,     7,   469,   470,   471,     7,
     493,   494,   495,     7,   459,   460,   461,   135,   136,   137,
     138,   140,   391,   392,   393,   394,   395,   396,   397,     7,
     567,   568,     7,   529,   530,   531,     7,   407,   408,   409,
     147,   148,   149,   150,   151,   152,   421,   422,   423,   424,
     425,   426,   427,   428,   155,   156,   157,   260,   400,   401,
     402,   403,   404,   523,   525,   160,   164,   165,   166,   167,
     174,   260,   381,   383,   385,   523,   525,   588,   589,   590,
     593,   595,   597,   598,   599,     7,   584,   585,   586,   176,
     177,   178,   226,   523,   525,   624,   625,   626,   627,   629,
     630,   636,     7,   662,   663,   209,   210,   211,   212,   260,
     686,   687,   688,   689,   690,   691,   257,     7,   512,   513,
     514,   142,   562,   563,   349,     8,     8,     8,   342,   344,
       3,     8,   356,   359,   361,   363,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   377,     4,     4,   382,
     384,   386,   388,     3,     8,     8,   352,     6,     3,   434,
       6,     3,   472,     6,     3,   496,     6,     3,   462,     6,
       3,     3,     6,   569,     3,     6,   532,     6,     3,   410,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   591,   594,   596,     4,   600,
       4,     3,     8,   587,     6,     3,     4,   628,     4,   631,
       3,     8,     8,   664,     3,     6,     4,     4,     4,     4,
       3,     8,   226,   258,   259,   515,     6,     3,   564,     8,
       6,     4,     4,   340,     4,     4,     4,     4,   227,   229,
     227,   229,   227,   227,   227,   227,   227,   227,     4,   229,
     227,     4,     4,     4,     4,   354,   353,   351,   437,   433,
     475,   471,   499,   495,   260,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   284,   287,   288,   289,   290,
     291,   292,   295,   297,   299,   300,   301,   304,   305,   307,
     309,   315,   365,   429,   447,   449,   451,   453,   454,   455,
     463,   464,   491,   523,   525,   538,   540,   542,   560,   461,
     392,   128,   129,   130,   260,   270,   271,   272,   315,   365,
     465,   491,   523,   525,   538,   540,   542,   570,   571,   572,
     573,   574,   576,   578,   568,   535,   531,   413,   409,   227,
     227,   227,   227,   227,   227,   422,   229,   227,   227,   401,
       4,     4,     4,   227,     4,   229,   589,   588,   586,   229,
       4,   227,     4,   625,   200,   202,   203,   260,   365,   523,
     525,   665,   666,   667,   668,   670,   663,   229,   229,   229,
     229,   687,     6,     3,   518,   514,     4,   226,   226,    41,
      42,    43,   357,   226,   226,   226,    58,    59,    60,   378,
     226,   226,   226,   226,     8,     8,     8,     8,     3,     8,
     575,   577,     4,     8,     3,     8,     8,   161,   162,   163,
     592,   226,   226,     7,     8,   226,   245,   671,     4,   669,
       3,     8,   226,     8,   256,   464,     4,     4,   229,   572,
      40,   169,   170,   171,   260,   523,   525,   601,   602,   603,
     606,   608,   610,     4,   227,     4,   666,   226,   226,   604,
     607,   609,   611,     3,     8,     5,   226,     4,     4,     4,
       4,   602,     7,   672,   673,   168,   605,   226,   226,     5,
     674,     3,     6,     7,   612,   613,   614,   201,   204,   205,
     206,   207,   675,   676,   677,   679,   680,   681,   682,   673,
     615,     6,     3,   678,     4,     4,     4,   683,     3,     8,
     172,   173,   260,   358,   360,   523,   525,   616,   617,   618,
     620,   614,     4,   229,   227,   227,     4,   676,   619,   621,
       3,     8,   226,   226,     4,     4,   617,   226,   226
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   230,   232,   231,   233,   231,   234,   231,   235,   231,
     236,   231,   237,   231,   238,   231,   239,   231,   240,   231,
     241,   231,   242,   231,   243,   231,   244,   231,   245,   245,
     245,   245,   245,   245,   245,   246,   248,   247,   249,   250,
     250,   251,   251,   251,   253,   252,   254,   254,   255,   255,
     255,   257,   256,   258,   258,   259,   259,   259,   260,   262,
     261,   264,   263,   263,   265,   267,   266,   268,   268,   268,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     282,   281,   283,   285,   284,   286,   287,   288,   289,   290,
     291,   293,   292,   294,   294,   294,   294,   294,   296,   295,
     298,   297,   299,   300,   302,   301,   303,   303,   303,   303,
     304,   306,   305,   308,   307,   309,   310,   311,   312,   313,
     314,   315,   316,   318,   317,   319,   319,   319,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   322,   321,
     324,   323,   326,   325,   327,   327,   329,   328,   330,   330,
     331,   332,   333,   334,   336,   335,   338,   337,   339,   339,
     339,   340,   340,   342,   341,   344,   343,   346,   345,   348,
     347,   349,   349,   350,   350,   350,   352,   351,   353,   353,
     353,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     354,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     354,   354,   354,   354,   356,   355,   357,   357,   357,   359,
     358,   361,   360,   363,   362,   364,   366,   365,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   377,   376,   378,
     378,   378,   379,   380,   382,   381,   384,   383,   386,   385,
     388,   387,   390,   389,   391,   391,   391,   392,   392,   392,
     392,   392,   393,   394,   395,   396,   397,   399,   398,   400,
     400,   400,   401,   401,   401,   401,   401,   401,   402,   403,
     404,   406,   405,   407,   407,   408,   408,   408,   410,   409,
     412,   411,   413,   413,   413,   413,   414,   414,   416,   415,
     418,   417,   420,   419,   421,   421,   421,   422,   422,   422,
     422,   422,   422,   423,   424,   425,   426,   427,   428,   430,
     429,   431,   431,   432,   432,   432,   434,   433,   436,   435,
     437,   437,   437,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   440,   439,   442,   441,   444,   443,   446,   445,   448,
     447,   450,   449,   452,   451,   453,   454,   455,   456,   458,
     457,   459,   459,   460,   460,   460,   462,   461,   463,   463,
     463,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   466,   465,   468,   467,   469,   469,
     470,   470,   470,   472,   471,   474,   473,   475,   475,   476,
     476,   476,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   478,   479,   480,   482,   481,   484,   483,   486,
     485,   487,   489,   488,   490,   492,   491,   493,   493,   494,
     494,   494,   496,   495,   498,   497,   499,   499,   500,   500,
     500,   501,   501,   501,   501,   501,   501,   501,   501,   501,
     501,   502,   504,   503,   505,   506,   507,   508,   509,   511,
     510,   512,   512,   513,   513,   513,   515,   514,   517,   516,
     518,   518,   518,   519,   519,   519,   519,   519,   519,   519,
     519,   521,   520,   522,   524,   523,   526,   525,   528,   527,
     529,   529,   530,   530,   530,   532,   531,   534,   533,   535,
     535,   536,   536,   536,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   539,
     538,   541,   540,   543,   542,   545,   544,   547,   546,   549,
     548,   551,   550,   553,   552,   555,   554,   557,   556,   559,
     558,   561,   560,   562,   564,   563,   566,   565,   567,   567,
     567,   569,   568,   570,   570,   571,   571,   571,   572,   572,
     572,   572,   572,   572,   572,   572,   572,   572,   572,   572,
     572,   572,   572,   572,   573,   575,   574,   577,   576,   578,
     579,   581,   580,   583,   582,   584,   584,   585,   585,   585,
     587,   586,   588,   588,   588,   589,   589,   589,   589,   589,
     589,   589,   589,   589,   589,   589,   589,   591,   590,   592,
     592,   592,   594,   593,   596,   595,   597,   598,   600,   599,
     601,   601,   601,   602,   602,   602,   602,   602,   602,   602,
     604,   603,   605,   607,   606,   609,   608,   611,   610,   612,
     612,   613,   613,   613,   615,   614,   616,   616,   616,   617,
     617,   617,   617,   617,   617,   617,   619,   618,   621,   620,
     623,   622,   624,   624,   624,   625,   625,   625,   625,   625,
     625,   626,   628,   627,   629,   631,   630,   633,   632,   635,
     634,   636,   636,   636,   637,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   638,   640,   639,   641,   643,
     642,   644,   645,   647,   646,   648,   648,   650,   649,   652,
     651,   654,   653,   655,   655,   655,   656,   656,   658,   657,
     659,   661,   660,   662,   662,   662,   664,   663,   665,   665,
     665,   666,   666,   666,   666,   666,   666,   666,   667,   669,
     668,   671,   670,   672,   672,   672,   674,   673,   675,   675,
     675,   676,   676,   676,   676,   676,   678,   677,   679,   680,
     681,   683,   682,   685,   684,   686,   686,   686,   687,   687,
     687,   687,   687,   688,   689,   690,   691
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     3,     3,     3,     0,     6,     0,     6,     1,     3,
       2,     1,     1,     0,     4,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     3,     3,     0,     4,     0,     4,     0,     4,
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
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     0,     4,     1,     1,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     0,     4,     0,     6,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
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
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"", "\"port\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"retry-on-startup\"", "\"max-row-errors\"",
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"ddns-ttl-percent\"", "\"store-extended-info\"", "\"subnet4\"",
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
  "\"require-client-classes\"", "\"test\"", "\"template-test\"",
  "\"only-if-required\"", "\"client-class\"", "\"pool-id\"",
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
  "\"dhcp-queue-control\"", "\"enable-queue\"", "\"queue-type\"",
  "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"", "\"tcp\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"early-global-reservations-lookup\"",
  "\"ip-reservations-unique\"", "\"reservations-lookup-first\"",
  "\"loggers\"", "\"output-options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"compatibility\"", "\"lenient-option-parsing\"",
  "\"ignore-dhcp-server-identifier\"", "\"ignore-rai-link-selection\"",
  "\"exclude-first-last-24\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
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
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first", "offer_lifetime",
  "stash_agent_options", "interfaces_config", "$@28",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@29", "interfaces_list", "$@30", "dhcp_socket_type", "$@31",
  "socket_type", "outbound_interface", "$@32", "outbound_interface_value",
  "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@33", "sanity_checks", "$@34",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@35",
  "extended_info_checks", "$@36", "hosts_database", "$@37",
  "hosts_databases", "$@38", "database_list", "not_empty_database_list",
  "database", "$@39", "database_map_params", "database_map_param",
  "database_type", "$@40", "db_type", "user", "$@41", "password", "$@42",
  "host", "$@43", "port", "name", "$@44", "persist", "lfc_interval",
  "readonly", "connect_timeout", "read_timeout", "write_timeout",
  "tcp_user_timeout", "max_reconnect_tries", "reconnect_wait_time",
  "on_fail", "$@45", "on_fail_mode", "retry_on_startup", "max_row_errors",
  "trust_anchor", "$@46", "cert_file", "$@47", "key_file", "$@48",
  "cipher_list", "$@49", "host_reservation_identifiers", "$@50",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@51", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@52", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@53",
  "sub_hooks_library", "$@54", "hooks_params", "hooks_param", "library",
  "$@55", "parameters", "$@56", "expired_leases_processing", "$@57",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@58",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@59",
  "sub_subnet4", "$@60", "subnet4_params", "subnet4_param", "subnet",
  "$@61", "subnet_4o6_interface", "$@62", "subnet_4o6_interface_id",
  "$@63", "subnet_4o6_subnet", "$@64", "interface", "$@65", "client_class",
  "$@66", "require_client_classes", "$@67", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "shared_networks", "$@68", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@69",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@70", "sub_option_def_list", "$@71", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@72",
  "sub_option_def", "$@73", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@74",
  "option_def_record_types", "$@75", "space", "$@76", "option_def_space",
  "option_def_encapsulate", "$@77", "option_def_array", "option_data_list",
  "$@78", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@79", "sub_option_data", "$@80",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@81",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@82", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@83", "sub_pool4", "$@84", "pool_params", "pool_param", "pool_entry",
  "$@85", "pool_id", "user_context", "$@86", "comment", "$@87",
  "reservations", "$@88", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@89", "sub_reservation",
  "$@90", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@91", "server_hostname", "$@92",
  "boot_file_name", "$@93", "ip_address", "$@94", "duid", "$@95",
  "hw_address", "$@96", "client_id_value", "$@97", "circuit_id_value",
  "$@98", "flex_id_value", "$@99", "hostname", "$@100",
  "reservation_client_classes", "$@101", "relay", "$@102", "relay_map",
  "ip_addresses", "$@103", "client_classes", "$@104",
  "client_classes_list", "client_class_entry", "$@105",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@106",
  "client_class_template_test", "$@107", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@108", "control_sockets", "$@109",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@110", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@111",
  "control_socket_type_value", "control_socket_name", "$@112",
  "control_socket_address", "$@113", "control_socket_port",
  "cert_required", "authentication", "$@114", "auth_params", "auth_param",
  "auth_type", "$@115", "auth_type_value", "realm", "$@116", "directory",
  "$@117", "clients", "$@118", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@119", "clients_params", "clients_param", "user_file",
  "$@120", "password_file", "$@121", "dhcp_queue_control", "$@122",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@123", "capacity", "arbitrary_map_entry", "$@124",
  "dhcp_ddns", "$@125", "sub_dhcp_ddns", "$@126", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@127", "server_port",
  "sender_ip", "$@128", "sender_port", "max_queue_size", "ncr_protocol",
  "$@129", "ncr_protocol_value", "ncr_format", "$@130", "config_control",
  "$@131", "sub_config_control", "$@132", "config_control_params",
  "config_control_param", "config_databases", "$@133",
  "config_fetch_wait_time", "loggers", "$@134", "loggers_entries",
  "logger_entry", "$@135", "logger_params", "logger_param", "debuglevel",
  "severity", "$@136", "output_options_list", "$@137",
  "output_options_list_content", "output_entry", "$@138",
  "output_params_list", "output_params", "output", "$@139", "flush",
  "maxsize", "maxver", "pattern", "$@140", "compatibility", "$@141",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   326,   326,   326,   327,   327,   328,   328,   329,   329,
     330,   330,   331,   331,   332,   332,   333,   333,   334,   334,
     335,   335,   336,   336,   337,   337,   338,   338,   346,   347,
     348,   349,   350,   351,   352,   355,   360,   360,   371,   374,
     375,   378,   383,   389,   394,   394,   401,   402,   405,   409,
     413,   419,   419,   426,   427,   430,   434,   438,   448,   457,
     457,   472,   472,   486,   489,   495,   495,   504,   505,   506,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   581,   584,
     590,   596,   602,   608,   614,   620,   626,   632,   638,   644,
     650,   650,   659,   665,   665,   674,   680,   686,   692,   698,
     704,   710,   710,   719,   722,   725,   728,   731,   737,   737,
     746,   746,   755,   764,   774,   774,   783,   786,   789,   792,
     797,   803,   803,   812,   812,   821,   827,   833,   839,   845,
     851,   857,   863,   869,   869,   881,   882,   883,   888,   889,
     890,   891,   892,   893,   894,   895,   896,   897,   900,   900,
     909,   909,   920,   920,   928,   929,   932,   932,   940,   942,
     946,   952,   958,   964,   970,   970,   983,   983,   994,   995,
     996,  1001,  1002,  1005,  1005,  1024,  1024,  1042,  1042,  1055,
    1055,  1066,  1067,  1070,  1071,  1072,  1077,  1077,  1087,  1088,
    1089,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1119,  1119,  1127,  1128,  1129,  1132,
    1132,  1141,  1141,  1150,  1150,  1159,  1165,  1165,  1174,  1180,
    1186,  1192,  1198,  1204,  1210,  1216,  1222,  1228,  1228,  1236,
    1237,  1238,  1241,  1247,  1253,  1253,  1262,  1262,  1271,  1271,
    1280,  1280,  1289,  1289,  1300,  1301,  1302,  1307,  1308,  1309,
    1310,  1311,  1314,  1319,  1324,  1329,  1334,  1341,  1341,  1354,
    1355,  1356,  1361,  1362,  1363,  1364,  1365,  1366,  1369,  1375,
    1381,  1387,  1387,  1398,  1399,  1402,  1403,  1404,  1409,  1409,
    1419,  1419,  1429,  1430,  1431,  1434,  1437,  1438,  1441,  1441,
    1450,  1450,  1459,  1459,  1471,  1472,  1473,  1478,  1479,  1480,
    1481,  1482,  1483,  1486,  1492,  1498,  1504,  1510,  1516,  1525,
    1525,  1539,  1540,  1543,  1544,  1545,  1554,  1554,  1580,  1580,
    1591,  1592,  1593,  1599,  1600,  1601,  1602,  1603,  1604,  1605,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,  1645,
    1646,  1649,  1649,  1658,  1658,  1667,  1667,  1676,  1676,  1685,
    1685,  1694,  1694,  1703,  1703,  1714,  1720,  1726,  1732,  1740,
    1740,  1752,  1753,  1757,  1758,  1759,  1764,  1764,  1772,  1773,
    1774,  1779,  1780,  1781,  1782,  1783,  1784,  1785,  1786,  1787,
    1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,
    1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,
    1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,  1817,
    1818,  1819,  1820,  1821,  1828,  1828,  1842,  1842,  1851,  1852,
    1855,  1856,  1857,  1864,  1864,  1879,  1879,  1893,  1894,  1897,
    1898,  1899,  1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,
    1912,  1913,  1916,  1918,  1924,  1926,  1926,  1935,  1935,  1944,
    1944,  1953,  1955,  1955,  1964,  1974,  1974,  1987,  1988,  1993,
    1994,  1995,  2002,  2002,  2014,  2014,  2026,  2027,  2032,  2033,
    2034,  2041,  2042,  2043,  2044,  2045,  2046,  2047,  2048,  2049,
    2050,  2053,  2055,  2055,  2064,  2066,  2068,  2074,  2080,  2089,
    2089,  2102,  2103,  2106,  2107,  2108,  2113,  2113,  2123,  2123,
    2133,  2134,  2135,  2140,  2141,  2142,  2143,  2144,  2145,  2146,
    2147,  2150,  2150,  2159,  2165,  2165,  2190,  2190,  2220,  2220,
    2231,  2232,  2235,  2236,  2237,  2242,  2242,  2251,  2251,  2260,
    2261,  2264,  2265,  2266,  2272,  2273,  2274,  2275,  2276,  2277,
    2278,  2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2289,
    2289,  2298,  2298,  2307,  2307,  2316,  2316,  2325,  2325,  2334,
    2334,  2343,  2343,  2352,  2352,  2361,  2361,  2370,  2370,  2379,
    2379,  2393,  2393,  2404,  2407,  2407,  2421,  2421,  2432,  2433,
    2434,  2439,  2439,  2449,  2450,  2453,  2454,  2455,  2460,  2461,
    2462,  2463,  2464,  2465,  2466,  2467,  2468,  2469,  2470,  2471,
    2472,  2473,  2474,  2475,  2478,  2480,  2480,  2489,  2489,  2498,
    2506,  2514,  2514,  2525,  2525,  2536,  2537,  2540,  2541,  2542,
    2547,  2547,  2556,  2557,  2558,  2563,  2564,  2565,  2566,  2567,
    2568,  2569,  2570,  2571,  2572,  2573,  2574,  2577,  2577,  2586,
    2587,  2588,  2591,  2591,  2600,  2600,  2609,  2615,  2623,  2623,
    2636,  2637,  2638,  2643,  2644,  2645,  2646,  2647,  2648,  2649,
    2652,  2652,  2660,  2663,  2663,  2672,  2672,  2681,  2681,  2692,
    2693,  2696,  2697,  2698,  2703,  2703,  2711,  2712,  2713,  2718,
    2719,  2720,  2721,  2722,  2723,  2724,  2727,  2727,  2736,  2736,
    2747,  2747,  2760,  2761,  2762,  2767,  2768,  2769,  2770,  2771,
    2772,  2775,  2781,  2781,  2790,  2796,  2796,  2806,  2806,  2819,
    2819,  2829,  2830,  2831,  2836,  2837,  2838,  2839,  2840,  2841,
    2842,  2843,  2844,  2845,  2846,  2849,  2855,  2855,  2864,  2870,
    2870,  2879,  2885,  2891,  2891,  2900,  2901,  2904,  2904,  2915,
    2915,  2927,  2927,  2937,  2938,  2939,  2945,  2946,  2949,  2949,
    2960,  2968,  2968,  2981,  2982,  2983,  2989,  2989,  2997,  2998,
    2999,  3004,  3005,  3006,  3007,  3008,  3009,  3010,  3013,  3019,
    3019,  3028,  3028,  3039,  3040,  3041,  3046,  3046,  3054,  3055,
    3056,  3061,  3062,  3063,  3064,  3065,  3068,  3068,  3077,  3083,
    3089,  3095,  3095,  3104,  3104,  3115,  3116,  3117,  3122,  3123,
    3124,  3125,  3126,  3129,  3135,  3141,  3147
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
#line 6689 "dhcp4_parser.cc"

#line 3153 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
