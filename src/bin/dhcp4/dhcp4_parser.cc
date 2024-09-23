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
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 313 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp4_parser.cc"
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
#line 322 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 323 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 324 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 325 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 326 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 327 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 328 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 329 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 330 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 331 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 332 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 333 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 334 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 342 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 343 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 344 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 345 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 346 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 347 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 348 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 351 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 356 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 361 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 367 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 374 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 379 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 385 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 390 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 393 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 401 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 405 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 409 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 415 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 417 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 426 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 430 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 434 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 444 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 453 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 458 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1077 "dhcp4_parser.cc"
    break;

  case 61: // $@18: %empty
#line 468 "dhcp4_parser.yy"
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
#line 1092 "dhcp4_parser.cc"
    break;

  case 62: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 477 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 485 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 491 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 495 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 502 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 139: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 580 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 140: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 586 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 141: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 592 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 142: // renew_timer: "renew-timer" ":" "integer"
#line 598 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 143: // rebind_timer: "rebind-timer" ":" "integer"
#line 604 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 144: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 610 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 145: // t1_percent: "t1-percent" ":" "floating point"
#line 616 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 146: // t2_percent: "t2-percent" ":" "floating point"
#line 622 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 147: // cache_threshold: "cache-threshold" ":" "floating point"
#line 628 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 148: // cache_max_age: "cache-max-age" ":" "integer"
#line 634 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 149: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 640 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 150: // $@20: %empty
#line 646 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 151: // server_tag: "server-tag" $@20 ":" "constant string"
#line 649 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 152: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 655 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 661 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 154: // allocator: "allocator" $@21 ":" "constant string"
#line 664 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 155: // echo_client_id: "echo-client-id" ":" "boolean"
#line 670 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 156: // match_client_id: "match-client-id" ":" "boolean"
#line 676 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 157: // authoritative: "authoritative" ":" "boolean"
#line 682 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 158: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 688 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 694 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 160: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 700 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 706 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 709 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-present"
#line 715 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "never"
#line 718 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "always"
#line 721 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-not-present"
#line 724 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "boolean"
#line 727 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 168: // $@23: %empty
#line 733 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 169: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 736 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 170: // $@24: %empty
#line 742 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 171: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 745 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 172: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 751 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 173: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 760 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1476 "dhcp4_parser.cc"
    break;

  case 174: // $@25: %empty
#line 770 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 773 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 779 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 782 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 785 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 788 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 180: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 793 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 799 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 802 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 183: // $@27: %empty
#line 808 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 184: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 811 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 185: // store_extended_info: "store-extended-info" ":" "boolean"
#line 817 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 823 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 187: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 829 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 188: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 835 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 189: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 841 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 847 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 191: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 853 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 192: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 859 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 865 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 194: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 871 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 197: // interfaces_config_params: interfaces_config_params ","
#line 879 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1684 "dhcp4_parser.cc"
    break;

  case 208: // $@29: %empty
#line 896 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 209: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 900 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1703 "dhcp4_parser.cc"
    break;

  case 210: // $@30: %empty
#line 905 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1715 "dhcp4_parser.cc"
    break;

  case 211: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 911 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 212: // $@31: %empty
#line 916 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 213: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 919 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1742 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "raw"
#line 924 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp4_parser.cc"
    break;

  case 215: // socket_type: "udp"
#line 925 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp4_parser.cc"
    break;

  case 216: // $@32: %empty
#line 928 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 931 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "same-as-inbound"
#line 936 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 219: // outbound_interface_value: "use-routing"
#line 938 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1788 "dhcp4_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 942 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 948 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 954 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 960 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 224: // $@33: %empty
#line 966 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1840 "dhcp4_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 972 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 226: // $@34: %empty
#line 979 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1863 "dhcp4_parser.cc"
    break;

  case 227: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 985 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 230: // sanity_checks_params: sanity_checks_params ","
#line 992 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1880 "dhcp4_parser.cc"
    break;

  case 233: // $@35: %empty
#line 1001 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp4_parser.cc"
    break;

  case 234: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1004 "dhcp4_parser.yy"
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
#line 1909 "dhcp4_parser.cc"
    break;

  case 235: // $@36: %empty
#line 1020 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp4_parser.cc"
    break;

  case 236: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1023 "dhcp4_parser.yy"
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
#line 1937 "dhcp4_parser.cc"
    break;

  case 237: // $@37: %empty
#line 1038 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1949 "dhcp4_parser.cc"
    break;

  case 238: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1044 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 239: // $@38: %empty
#line 1051 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 240: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1057 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 245: // not_empty_database_list: not_empty_database_list ","
#line 1068 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1989 "dhcp4_parser.cc"
    break;

  case 246: // $@39: %empty
#line 1073 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 247: // database: "{" $@39 database_map_params "}"
#line 1077 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2009 "dhcp4_parser.cc"
    break;

  case 250: // database_map_params: database_map_params ","
#line 1085 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2017 "dhcp4_parser.cc"
    break;

  case 274: // $@40: %empty
#line 1115 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2026 "dhcp4_parser.cc"
    break;

  case 275: // database_type: "type" $@40 ":" "constant string"
#line 1118 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2036 "dhcp4_parser.cc"
    break;

  case 276: // $@41: %empty
#line 1124 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc"
    break;

  case 277: // user: "user" $@41 ":" "constant string"
#line 1127 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc"
    break;

  case 278: // $@42: %empty
#line 1133 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 279: // password: "password" $@42 ":" "constant string"
#line 1136 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 280: // $@43: %empty
#line 1142 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp4_parser.cc"
    break;

  case 281: // host: "host" $@43 ":" "constant string"
#line 1145 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2093 "dhcp4_parser.cc"
    break;

  case 282: // port: "port" ":" "integer"
#line 1151 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2103 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1157 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp4_parser.cc"
    break;

  case 284: // name: "name" $@44 ":" "constant string"
#line 1160 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2122 "dhcp4_parser.cc"
    break;

  case 285: // persist: "persist" ":" "boolean"
#line 1166 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 286: // lfc_interval: "lfc-interval" ":" "integer"
#line 1172 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 287: // readonly: "readonly" ":" "boolean"
#line 1178 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 288: // connect_timeout: "connect-timeout" ":" "integer"
#line 1184 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2162 "dhcp4_parser.cc"
    break;

  case 289: // read_timeout: "read-timeout" ":" "integer"
#line 1190 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 290: // write_timeout: "write-timeout" ":" "integer"
#line 1196 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 291: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1202 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 292: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1208 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 293: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1214 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1220 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 295: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1223 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 296: // on_fail_mode: "stop-retry-exit"
#line 1228 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2236 "dhcp4_parser.cc"
    break;

  case 297: // on_fail_mode: "serve-retry-exit"
#line 1229 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2242 "dhcp4_parser.cc"
    break;

  case 298: // on_fail_mode: "serve-retry-continue"
#line 1230 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2248 "dhcp4_parser.cc"
    break;

  case 299: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1233 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 300: // max_row_errors: "max-row-errors" ":" "integer"
#line 1239 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2268 "dhcp4_parser.cc"
    break;

  case 301: // $@46: %empty
#line 1245 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 302: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1248 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc"
    break;

  case 303: // $@47: %empty
#line 1254 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc"
    break;

  case 304: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1257 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2306 "dhcp4_parser.cc"
    break;

  case 305: // $@48: %empty
#line 1263 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp4_parser.cc"
    break;

  case 306: // key_file: "key-file" $@48 ":" "constant string"
#line 1266 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 307: // $@49: %empty
#line 1272 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc"
    break;

  case 308: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1275 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 309: // $@50: %empty
#line 1281 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2356 "dhcp4_parser.cc"
    break;

  case 310: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1287 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2365 "dhcp4_parser.cc"
    break;

  case 313: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1294 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2373 "dhcp4_parser.cc"
    break;

  case 319: // duid_id: "duid"
#line 1306 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2382 "dhcp4_parser.cc"
    break;

  case 320: // hw_address_id: "hw-address"
#line 1311 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2391 "dhcp4_parser.cc"
    break;

  case 321: // circuit_id: "circuit-id"
#line 1316 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2400 "dhcp4_parser.cc"
    break;

  case 322: // client_id: "client-id"
#line 1321 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2409 "dhcp4_parser.cc"
    break;

  case 323: // flex_id: "flex-id"
#line 1326 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1333 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 325: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1339 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2441 "dhcp4_parser.cc"
    break;

  case 328: // multi_threading_params: multi_threading_params ","
#line 1348 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2449 "dhcp4_parser.cc"
    break;

  case 335: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1361 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2459 "dhcp4_parser.cc"
    break;

  case 336: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1367 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 337: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1373 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2479 "dhcp4_parser.cc"
    break;

  case 338: // $@52: %empty
#line 1379 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 339: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1385 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 344: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1396 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2508 "dhcp4_parser.cc"
    break;

  case 345: // $@53: %empty
#line 1401 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 346: // hooks_library: "{" $@53 hooks_params "}"
#line 1405 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 347: // $@54: %empty
#line 1411 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 348: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1415 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 351: // hooks_params: hooks_params ","
#line 1423 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2556 "dhcp4_parser.cc"
    break;

  case 355: // $@55: %empty
#line 1433 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 356: // library: "library" $@55 ":" "constant string"
#line 1436 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 357: // $@56: %empty
#line 1442 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2584 "dhcp4_parser.cc"
    break;

  case 358: // parameters: "parameters" $@56 ":" map_value
#line 1445 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2593 "dhcp4_parser.cc"
    break;

  case 359: // $@57: %empty
#line 1451 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 360: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1457 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 363: // expired_leases_params: expired_leases_params ","
#line 1465 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2623 "dhcp4_parser.cc"
    break;

  case 370: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1478 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2633 "dhcp4_parser.cc"
    break;

  case 371: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1484 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 372: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1490 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 373: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1496 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 374: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1502 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 375: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1508 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 376: // $@58: %empty
#line 1517 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 377: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1523 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2704 "dhcp4_parser.cc"
    break;

  case 382: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1537 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2712 "dhcp4_parser.cc"
    break;

  case 383: // $@59: %empty
#line 1546 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 384: // subnet4: "{" $@59 subnet4_params "}"
#line 1550 "dhcp4_parser.yy"
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
#line 2748 "dhcp4_parser.cc"
    break;

  case 385: // $@60: %empty
#line 1572 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 386: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1576 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 389: // subnet4_params: subnet4_params ","
#line 1585 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2776 "dhcp4_parser.cc"
    break;

  case 438: // $@61: %empty
#line 1641 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 439: // subnet: "subnet" $@61 ":" "constant string"
#line 1644 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc"
    break;

  case 440: // $@62: %empty
#line 1650 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 441: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1653 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2814 "dhcp4_parser.cc"
    break;

  case 442: // $@63: %empty
#line 1659 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 443: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1662 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 444: // $@64: %empty
#line 1668 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1671 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 446: // $@65: %empty
#line 1677 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 447: // interface: "interface" $@65 ":" "constant string"
#line 1680 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 448: // $@66: %empty
#line 1686 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc"
    break;

  case 449: // client_class: "client-class" $@66 ":" "constant string"
#line 1689 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 450: // $@67: %empty
#line 1695 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp4_parser.cc"
    break;

  case 451: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1701 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2911 "dhcp4_parser.cc"
    break;

  case 452: // reservations_global: "reservations-global" ":" "boolean"
#line 1706 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2921 "dhcp4_parser.cc"
    break;

  case 453: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1712 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2931 "dhcp4_parser.cc"
    break;

  case 454: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1718 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 455: // id: "id" ":" "integer"
#line 1724 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 456: // $@68: %empty
#line 1732 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2963 "dhcp4_parser.cc"
    break;

  case 457: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1738 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2972 "dhcp4_parser.cc"
    break;

  case 462: // shared_networks_list: shared_networks_list ","
#line 1751 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2980 "dhcp4_parser.cc"
    break;

  case 463: // $@69: %empty
#line 1756 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 464: // shared_network: "{" $@69 shared_network_params "}"
#line 1760 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2998 "dhcp4_parser.cc"
    break;

  case 467: // shared_network_params: shared_network_params ","
#line 1766 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3006 "dhcp4_parser.cc"
    break;

  case 511: // $@70: %empty
#line 1820 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 512: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1826 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 513: // $@71: %empty
#line 1834 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3036 "dhcp4_parser.cc"
    break;

  case 514: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1837 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 519: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1849 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3052 "dhcp4_parser.cc"
    break;

  case 520: // $@72: %empty
#line 1856 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 521: // option_def_entry: "{" $@72 option_def_params "}"
#line 1860 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3074 "dhcp4_parser.cc"
    break;

  case 522: // $@73: %empty
#line 1871 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3084 "dhcp4_parser.cc"
    break;

  case 523: // sub_option_def: "{" $@73 option_def_params "}"
#line 1875 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3096 "dhcp4_parser.cc"
    break;

  case 528: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1891 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3104 "dhcp4_parser.cc"
    break;

  case 540: // code: "code" ":" "integer"
#line 1910 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 542: // $@74: %empty
#line 1918 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3123 "dhcp4_parser.cc"
    break;

  case 543: // option_def_type: "type" $@74 ":" "constant string"
#line 1921 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3133 "dhcp4_parser.cc"
    break;

  case 544: // $@75: %empty
#line 1927 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 545: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1930 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3152 "dhcp4_parser.cc"
    break;

  case 546: // $@76: %empty
#line 1936 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3161 "dhcp4_parser.cc"
    break;

  case 547: // space: "space" $@76 ":" "constant string"
#line 1939 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3171 "dhcp4_parser.cc"
    break;

  case 549: // $@77: %empty
#line 1947 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3180 "dhcp4_parser.cc"
    break;

  case 550: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1950 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3190 "dhcp4_parser.cc"
    break;

  case 551: // option_def_array: "array" ":" "boolean"
#line 1956 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3200 "dhcp4_parser.cc"
    break;

  case 552: // $@78: %empty
#line 1966 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3212 "dhcp4_parser.cc"
    break;

  case 553: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1972 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3221 "dhcp4_parser.cc"
    break;

  case 558: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1987 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3229 "dhcp4_parser.cc"
    break;

  case 559: // $@79: %empty
#line 1994 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3239 "dhcp4_parser.cc"
    break;

  case 560: // option_data_entry: "{" $@79 option_data_params "}"
#line 1998 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3248 "dhcp4_parser.cc"
    break;

  case 561: // $@80: %empty
#line 2006 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 562: // sub_option_data: "{" $@80 option_data_params "}"
#line 2010 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3267 "dhcp4_parser.cc"
    break;

  case 567: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2026 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3275 "dhcp4_parser.cc"
    break;

  case 580: // $@81: %empty
#line 2048 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 581: // option_data_data: "data" $@81 ":" "constant string"
#line 2051 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 584: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2061 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 585: // option_data_always_send: "always-send" ":" "boolean"
#line 2067 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 586: // option_data_never_send: "never-send" ":" "boolean"
#line 2073 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3324 "dhcp4_parser.cc"
    break;

  case 587: // $@82: %empty
#line 2079 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3336 "dhcp4_parser.cc"
    break;

  case 588: // option_data_client_classes: "client-classes" $@82 ":" list_strings
#line 2085 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3345 "dhcp4_parser.cc"
    break;

  case 589: // $@83: %empty
#line 2093 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3357 "dhcp4_parser.cc"
    break;

  case 590: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2099 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 595: // not_empty_pools_list: not_empty_pools_list ","
#line 2112 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3374 "dhcp4_parser.cc"
    break;

  case 596: // $@84: %empty
#line 2117 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp4_parser.cc"
    break;

  case 597: // pool_list_entry: "{" $@84 pool_params "}"
#line 2121 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 598: // $@85: %empty
#line 2127 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3404 "dhcp4_parser.cc"
    break;

  case 599: // sub_pool4: "{" $@85 pool_params "}"
#line 2131 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3414 "dhcp4_parser.cc"
    break;

  case 602: // pool_params: pool_params ","
#line 2139 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3422 "dhcp4_parser.cc"
    break;

  case 611: // $@86: %empty
#line 2154 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3431 "dhcp4_parser.cc"
    break;

  case 612: // pool_entry: "pool" $@86 ":" "constant string"
#line 2157 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3441 "dhcp4_parser.cc"
    break;

  case 613: // pool_id: "pool-id" ":" "integer"
#line 2163 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3451 "dhcp4_parser.cc"
    break;

  case 614: // $@87: %empty
#line 2169 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 615: // user_context: "user-context" $@87 ":" map_value
#line 2171 "dhcp4_parser.yy"
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
#line 3486 "dhcp4_parser.cc"
    break;

  case 616: // $@88: %empty
#line 2194 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 617: // comment: "comment" $@88 ":" "constant string"
#line 2196 "dhcp4_parser.yy"
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
#line 3523 "dhcp4_parser.cc"
    break;

  case 618: // $@89: %empty
#line 2224 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 619: // reservations: "reservations" $@89 ":" "[" reservations_list "]"
#line 2230 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 624: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2241 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3552 "dhcp4_parser.cc"
    break;

  case 625: // $@90: %empty
#line 2246 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3562 "dhcp4_parser.cc"
    break;

  case 626: // reservation: "{" $@90 reservation_params "}"
#line 2250 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3571 "dhcp4_parser.cc"
    break;

  case 627: // $@91: %empty
#line 2255 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3581 "dhcp4_parser.cc"
    break;

  case 628: // sub_reservation: "{" $@91 reservation_params "}"
#line 2259 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3590 "dhcp4_parser.cc"
    break;

  case 633: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2270 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3598 "dhcp4_parser.cc"
    break;

  case 649: // $@92: %empty
#line 2293 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 650: // next_server: "next-server" $@92 ":" "constant string"
#line 2296 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3617 "dhcp4_parser.cc"
    break;

  case 651: // $@93: %empty
#line 2302 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3626 "dhcp4_parser.cc"
    break;

  case 652: // server_hostname: "server-hostname" $@93 ":" "constant string"
#line 2305 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3636 "dhcp4_parser.cc"
    break;

  case 653: // $@94: %empty
#line 2311 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 654: // boot_file_name: "boot-file-name" $@94 ":" "constant string"
#line 2314 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 655: // $@95: %empty
#line 2320 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 656: // ip_address: "ip-address" $@95 ":" "constant string"
#line 2323 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 657: // $@96: %empty
#line 2329 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 658: // duid: "duid" $@96 ":" "constant string"
#line 2332 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 659: // $@97: %empty
#line 2338 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 660: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2341 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 661: // $@98: %empty
#line 2347 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 662: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2350 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 663: // $@99: %empty
#line 2356 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3740 "dhcp4_parser.cc"
    break;

  case 664: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2359 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3750 "dhcp4_parser.cc"
    break;

  case 665: // $@100: %empty
#line 2365 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 666: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2368 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 667: // $@101: %empty
#line 2374 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 668: // hostname: "hostname" $@101 ":" "constant string"
#line 2377 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 669: // $@102: %empty
#line 2383 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 670: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2389 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 671: // $@103: %empty
#line 2397 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 672: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2403 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 674: // $@104: %empty
#line 2411 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 675: // ip_addresses: "ip-addresses" $@104 ":" list_strings
#line 2417 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3851 "dhcp4_parser.cc"
    break;

  case 676: // $@105: %empty
#line 2425 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 677: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2431 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 680: // client_classes_list: client_classes_list ","
#line 2438 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3880 "dhcp4_parser.cc"
    break;

  case 681: // $@106: %empty
#line 2443 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3890 "dhcp4_parser.cc"
    break;

  case 682: // client_class_entry: "{" $@106 client_class_params "}"
#line 2447 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3900 "dhcp4_parser.cc"
    break;

  case 687: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2459 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3908 "dhcp4_parser.cc"
    break;

  case 705: // $@107: %empty
#line 2484 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3917 "dhcp4_parser.cc"
    break;

  case 706: // client_class_test: "test" $@107 ":" "constant string"
#line 2487 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3927 "dhcp4_parser.cc"
    break;

  case 707: // $@108: %empty
#line 2493 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3936 "dhcp4_parser.cc"
    break;

  case 708: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2496 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3946 "dhcp4_parser.cc"
    break;

  case 709: // only_if_required: "only-if-required" ":" "boolean"
#line 2502 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3956 "dhcp4_parser.cc"
    break;

  case 710: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2510 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3966 "dhcp4_parser.cc"
    break;

  case 711: // $@109: %empty
#line 2518 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3979 "dhcp4_parser.cc"
    break;

  case 712: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2525 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3988 "dhcp4_parser.cc"
    break;

  case 713: // $@110: %empty
#line 2530 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4001 "dhcp4_parser.cc"
    break;

  case 714: // control_sockets: "control-sockets" $@110 ":" "[" control_socket_list "]"
#line 2537 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4010 "dhcp4_parser.cc"
    break;

  case 719: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2548 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4018 "dhcp4_parser.cc"
    break;

  case 720: // $@111: %empty
#line 2553 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4028 "dhcp4_parser.cc"
    break;

  case 721: // control_socket_entry: "{" $@111 control_socket_params "}"
#line 2557 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4036 "dhcp4_parser.cc"
    break;

  case 724: // control_socket_params: control_socket_params ","
#line 2563 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4044 "dhcp4_parser.cc"
    break;

  case 737: // $@112: %empty
#line 2582 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4053 "dhcp4_parser.cc"
    break;

  case 738: // control_socket_type: "socket-type" $@112 ":" control_socket_type_value
#line 2585 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 739: // control_socket_type_value: "unix"
#line 2591 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4068 "dhcp4_parser.cc"
    break;

  case 740: // control_socket_type_value: "http"
#line 2592 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4074 "dhcp4_parser.cc"
    break;

  case 741: // control_socket_type_value: "https"
#line 2593 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4080 "dhcp4_parser.cc"
    break;

  case 742: // $@113: %empty
#line 2596 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4090 "dhcp4_parser.cc"
    break;

  case 743: // control_socket_name: "socket-name" $@113 ":" "constant string"
#line 2600 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4100 "dhcp4_parser.cc"
    break;

  case 744: // $@114: %empty
#line 2606 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4110 "dhcp4_parser.cc"
    break;

  case 745: // control_socket_address: "socket-address" $@114 ":" "constant string"
#line 2610 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4120 "dhcp4_parser.cc"
    break;

  case 746: // control_socket_port: "socket-port" ":" "integer"
#line 2616 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4130 "dhcp4_parser.cc"
    break;

  case 747: // cert_required: "cert-required" ":" "boolean"
#line 2622 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4140 "dhcp4_parser.cc"
    break;

  case 748: // $@115: %empty
#line 2630 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4152 "dhcp4_parser.cc"
    break;

  case 749: // authentication: "authentication" $@115 ":" "{" auth_params "}"
#line 2636 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4163 "dhcp4_parser.cc"
    break;

  case 752: // auth_params: auth_params ","
#line 2645 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4171 "dhcp4_parser.cc"
    break;

  case 760: // $@116: %empty
#line 2659 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4180 "dhcp4_parser.cc"
    break;

  case 761: // auth_type: "type" $@116 ":" auth_type_value
#line 2662 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4189 "dhcp4_parser.cc"
    break;

  case 762: // auth_type_value: "basic"
#line 2667 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4195 "dhcp4_parser.cc"
    break;

  case 763: // $@117: %empty
#line 2670 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4204 "dhcp4_parser.cc"
    break;

  case 764: // realm: "realm" $@117 ":" "constant string"
#line 2673 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4214 "dhcp4_parser.cc"
    break;

  case 765: // $@118: %empty
#line 2679 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4223 "dhcp4_parser.cc"
    break;

  case 766: // directory: "directory" $@118 ":" "constant string"
#line 2682 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4233 "dhcp4_parser.cc"
    break;

  case 767: // $@119: %empty
#line 2688 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4245 "dhcp4_parser.cc"
    break;

  case 768: // clients: "clients" $@119 ":" "[" clients_list "]"
#line 2694 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4254 "dhcp4_parser.cc"
    break;

  case 773: // not_empty_clients_list: not_empty_clients_list ","
#line 2705 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4262 "dhcp4_parser.cc"
    break;

  case 774: // $@120: %empty
#line 2710 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4272 "dhcp4_parser.cc"
    break;

  case 775: // basic_auth: "{" $@120 clients_params "}"
#line 2714 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4280 "dhcp4_parser.cc"
    break;

  case 778: // clients_params: clients_params ","
#line 2720 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4288 "dhcp4_parser.cc"
    break;

  case 786: // $@121: %empty
#line 2734 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4297 "dhcp4_parser.cc"
    break;

  case 787: // user_file: "user-file" $@121 ":" "constant string"
#line 2737 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4307 "dhcp4_parser.cc"
    break;

  case 788: // $@122: %empty
#line 2743 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4316 "dhcp4_parser.cc"
    break;

  case 789: // password_file: "password-file" $@122 ":" "constant string"
#line 2746 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4326 "dhcp4_parser.cc"
    break;

  case 790: // $@123: %empty
#line 2754 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 791: // dhcp_queue_control: "dhcp-queue-control" $@123 ":" "{" queue_control_params "}"
#line 2760 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4349 "dhcp4_parser.cc"
    break;

  case 794: // queue_control_params: queue_control_params ","
#line 2769 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4357 "dhcp4_parser.cc"
    break;

  case 801: // enable_queue: "enable-queue" ":" "boolean"
#line 2782 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4367 "dhcp4_parser.cc"
    break;

  case 802: // $@124: %empty
#line 2788 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4376 "dhcp4_parser.cc"
    break;

  case 803: // queue_type: "queue-type" $@124 ":" "constant string"
#line 2791 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4386 "dhcp4_parser.cc"
    break;

  case 804: // capacity: "capacity" ":" "integer"
#line 2797 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4396 "dhcp4_parser.cc"
    break;

  case 805: // $@125: %empty
#line 2803 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4405 "dhcp4_parser.cc"
    break;

  case 806: // arbitrary_map_entry: "constant string" $@125 ":" value
#line 2806 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4414 "dhcp4_parser.cc"
    break;

  case 807: // $@126: %empty
#line 2813 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4426 "dhcp4_parser.cc"
    break;

  case 808: // dhcp_ddns: "dhcp-ddns" $@126 ":" "{" dhcp_ddns_params "}"
#line 2819 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4437 "dhcp4_parser.cc"
    break;

  case 809: // $@127: %empty
#line 2826 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4447 "dhcp4_parser.cc"
    break;

  case 810: // sub_dhcp_ddns: "{" $@127 dhcp_ddns_params "}"
#line 2830 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4457 "dhcp4_parser.cc"
    break;

  case 813: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2838 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4465 "dhcp4_parser.cc"
    break;

  case 825: // enable_updates: "enable-updates" ":" "boolean"
#line 2856 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4475 "dhcp4_parser.cc"
    break;

  case 826: // $@128: %empty
#line 2862 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4484 "dhcp4_parser.cc"
    break;

  case 827: // server_ip: "server-ip" $@128 ":" "constant string"
#line 2865 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4494 "dhcp4_parser.cc"
    break;

  case 828: // server_port: "server-port" ":" "integer"
#line 2871 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4504 "dhcp4_parser.cc"
    break;

  case 829: // $@129: %empty
#line 2877 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4513 "dhcp4_parser.cc"
    break;

  case 830: // sender_ip: "sender-ip" $@129 ":" "constant string"
#line 2880 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4523 "dhcp4_parser.cc"
    break;

  case 831: // sender_port: "sender-port" ":" "integer"
#line 2886 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4533 "dhcp4_parser.cc"
    break;

  case 832: // max_queue_size: "max-queue-size" ":" "integer"
#line 2892 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4543 "dhcp4_parser.cc"
    break;

  case 833: // $@130: %empty
#line 2898 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 834: // ncr_protocol: "ncr-protocol" $@130 ":" ncr_protocol_value
#line 2901 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 835: // ncr_protocol_value: "udp"
#line 2907 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4567 "dhcp4_parser.cc"
    break;

  case 836: // ncr_protocol_value: "tcp"
#line 2908 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4573 "dhcp4_parser.cc"
    break;

  case 837: // $@131: %empty
#line 2911 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4582 "dhcp4_parser.cc"
    break;

  case 838: // ncr_format: "ncr-format" $@131 ":" "JSON"
#line 2914 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4592 "dhcp4_parser.cc"
    break;

  case 839: // $@132: %empty
#line 2922 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4604 "dhcp4_parser.cc"
    break;

  case 840: // config_control: "config-control" $@132 ":" "{" config_control_params "}"
#line 2928 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4614 "dhcp4_parser.cc"
    break;

  case 841: // $@133: %empty
#line 2934 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4624 "dhcp4_parser.cc"
    break;

  case 842: // sub_config_control: "{" $@133 config_control_params "}"
#line 2938 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4633 "dhcp4_parser.cc"
    break;

  case 845: // config_control_params: config_control_params ","
#line 2946 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4641 "dhcp4_parser.cc"
    break;

  case 848: // $@134: %empty
#line 2956 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4653 "dhcp4_parser.cc"
    break;

  case 849: // config_databases: "config-databases" $@134 ":" "[" database_list "]"
#line 2962 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4662 "dhcp4_parser.cc"
    break;

  case 850: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2967 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4672 "dhcp4_parser.cc"
    break;

  case 851: // $@135: %empty
#line 2975 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4684 "dhcp4_parser.cc"
    break;

  case 852: // loggers: "loggers" $@135 ":" "[" loggers_entries "]"
#line 2981 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4693 "dhcp4_parser.cc"
    break;

  case 855: // loggers_entries: loggers_entries ","
#line 2990 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4701 "dhcp4_parser.cc"
    break;

  case 856: // $@136: %empty
#line 2996 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4711 "dhcp4_parser.cc"
    break;

  case 857: // logger_entry: "{" $@136 logger_params "}"
#line 3000 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4719 "dhcp4_parser.cc"
    break;

  case 860: // logger_params: logger_params ","
#line 3006 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4727 "dhcp4_parser.cc"
    break;

  case 868: // debuglevel: "debuglevel" ":" "integer"
#line 3020 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4737 "dhcp4_parser.cc"
    break;

  case 869: // $@137: %empty
#line 3026 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4746 "dhcp4_parser.cc"
    break;

  case 870: // severity: "severity" $@137 ":" "constant string"
#line 3029 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4756 "dhcp4_parser.cc"
    break;

  case 871: // $@138: %empty
#line 3035 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4768 "dhcp4_parser.cc"
    break;

  case 872: // output_options_list: "output-options" $@138 ":" "[" output_options_list_content "]"
#line 3041 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 875: // output_options_list_content: output_options_list_content ","
#line 3048 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4785 "dhcp4_parser.cc"
    break;

  case 876: // $@139: %empty
#line 3053 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4795 "dhcp4_parser.cc"
    break;

  case 877: // output_entry: "{" $@139 output_params_list "}"
#line 3057 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4803 "dhcp4_parser.cc"
    break;

  case 880: // output_params_list: output_params_list ","
#line 3063 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4811 "dhcp4_parser.cc"
    break;

  case 886: // $@140: %empty
#line 3075 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4820 "dhcp4_parser.cc"
    break;

  case 887: // output: "output" $@140 ":" "constant string"
#line 3078 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4830 "dhcp4_parser.cc"
    break;

  case 888: // flush: "flush" ":" "boolean"
#line 3084 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4840 "dhcp4_parser.cc"
    break;

  case 889: // maxsize: "maxsize" ":" "integer"
#line 3090 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4850 "dhcp4_parser.cc"
    break;

  case 890: // maxver: "maxver" ":" "integer"
#line 3096 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4860 "dhcp4_parser.cc"
    break;

  case 891: // $@141: %empty
#line 3102 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4869 "dhcp4_parser.cc"
    break;

  case 892: // pattern: "pattern" $@141 ":" "constant string"
#line 3105 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4879 "dhcp4_parser.cc"
    break;

  case 893: // $@142: %empty
#line 3111 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4891 "dhcp4_parser.cc"
    break;

  case 894: // compatibility: "compatibility" $@142 ":" "{" compatibility_params "}"
#line 3117 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4900 "dhcp4_parser.cc"
    break;

  case 897: // compatibility_params: compatibility_params ","
#line 3124 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4908 "dhcp4_parser.cc"
    break;

  case 903: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3136 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4918 "dhcp4_parser.cc"
    break;

  case 904: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3142 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4928 "dhcp4_parser.cc"
    break;

  case 905: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3148 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4938 "dhcp4_parser.cc"
    break;

  case 906: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3154 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4948 "dhcp4_parser.cc"
    break;


#line 4952 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1300;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     415, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300,    35,    51,    30,    41,    48,    50,
      62,    65,    77,    81,    83,    99,   101,   116, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300,    51,  -142,    84,   683,    95,   167,
      91,   278,    -6,     1,   322,   -96,   440,    87, -1300,   126,
     135,   138,   142,   153, -1300,    44, -1300, -1300, -1300, -1300,
     154,   207,   237, -1300, -1300, -1300,   239,   251, -1300, -1300,
   -1300,   255,   257,   259,   274,   276,   288,   294,   296,   311,
     319,   325, -1300,   332,   334,   335,   342,   344, -1300, -1300,
   -1300,   353,   364,   374,   375, -1300, -1300, -1300,   378, -1300,
   -1300, -1300, -1300, -1300,   393,   395,   402, -1300, -1300, -1300,
   -1300, -1300,   403, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
     404,   434,   437, -1300, -1300,   444, -1300,    93, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
     450,   452,   462,   474, -1300,   131, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300,   478, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300,   149, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300,   482, -1300, -1300,
   -1300, -1300,   182, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
     178,   306, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300,   309, -1300, -1300,   485, -1300, -1300,
   -1300,   486, -1300, -1300,   348,   428, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   490,
     493,   495, -1300, -1300, -1300, -1300, -1300,   373,   472, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300,   204, -1300, -1300, -1300,   509, -1300,   510,
   -1300,   512,   516, -1300, -1300, -1300, -1300, -1300,   205, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   517,
     215, -1300, -1300, -1300, -1300,    51,    51, -1300,   217,   518,
   -1300, -1300,   521,   522,   523,   302,   303,   304,   529,   532,
     533,   315,   314,   537,   539,   543,   324,   326,   328,   337,
     341,   330,   338,   343,   345,   347,   349,   555,   350,   356,
     340,   346,   351,   563,   565,   572,   355,   358,   360,   363,
     583,   584,   587,   368,   591,   595,   598,   599,   601,   381,
     383,   384,   607,   609,   610,   611,   612,   414,   635,   637,
     639,   640,   641,   642,   644,   423,   426,   429,   646,   647,
   -1300,   683, -1300,   649,   650,   652,   431,   432,   435,   438,
      95, -1300,   657,   660,   661,   662,   663,   664,   445,   666,
     667,   668,   167, -1300,   669,   451,    91, -1300,   670,   672,
     675,   676,   678,   679,   680,   682, -1300,   278, -1300,   684,
     685,   463,   686,   687,   688,   467, -1300,     1,   696,   475,
     476,   477,   700, -1300,   322,   701,   703,   -78, -1300,   484,
     704,   487,   719,   500,   501,   722,   723,   440, -1300,   724,
     505,    87, -1300, -1300, -1300,   726,   725,   727,   728,   729,
   -1300, -1300, -1300,   508,   514,   515, -1300, -1300,   732,   733,
     738, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300,   549, -1300, -1300, -1300, -1300, -1300,  -113,   550,
     551, -1300, -1300, -1300, -1300,   741,   772,   773, -1300,   556,
     401,   775,   774,   559, -1300, -1300, -1300,   778,   779,   780,
     781,   783, -1300,   784,   785,   788,   789,   792,   577,   578,
   -1300, -1300, -1300,   790,   800, -1300,   803,   212,   201, -1300,
   -1300, -1300, -1300, -1300,   586,   588,   589,   805,   592,   593,
   -1300,   803,   594,   807, -1300,   596, -1300, -1300,   803,   597,
     602,   604,   605,   606,   608,   613, -1300,   614,   617, -1300,
     618,   619,   620, -1300, -1300,   621, -1300, -1300, -1300,   803,
   -1300,   622,   774, -1300, -1300,   623, -1300,   624, -1300, -1300,
      18,   547, -1300,   813, -1300, -1300,    51,   683,    87,    95,
     279, -1300, -1300, -1300,   120,   120,   814, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300,   815,   817,   823, -1300,
   -1300, -1300, -1300, -1300, -1300,   825, -1300, -1300, -1300,   254,
     828,   841,   842,   228,    39,   289,   843,   179,   440, -1300,
   -1300,   844,    19, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300,   845, -1300, -1300, -1300, -1300,   714,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300,   814, -1300,   305,   313,   323, -1300,
   -1300,   329, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   850,
     852,   853,   854,   856,   857,   858,   859,   860,   861, -1300,
     862,   863, -1300, -1300, -1300, -1300, -1300,   339, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300,   352, -1300,   864,   865, -1300, -1300,   866,   868, -1300,
   -1300,   867,   877, -1300, -1300,   875,   879, -1300, -1300,   878,
     880, -1300, -1300, -1300, -1300, -1300, -1300,   118, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,   125, -1300, -1300,   881,   882,
   -1300, -1300,   883,   887, -1300,   888,   889,   890,   891,   892,
     893,   361, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   894,
     895,   896, -1300,   362, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300,   897, -1300,   898, -1300, -1300, -1300, -1300,
   -1300, -1300,   377, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300,   885,   900, -1300,   901, -1300,   903, -1300, -1300, -1300,
     397, -1300, -1300, -1300, -1300, -1300,   421, -1300,   143, -1300,
     904,   905,   906,   907, -1300,   424, -1300, -1300, -1300, -1300,
   -1300,   681, -1300,   908,   909, -1300, -1300,   910, -1300,   911,
   -1300, -1300, -1300,   912,   915,   279, -1300,   916,   917,   918,
     919,   645,   689,   702,   698,   705,   706,   707,   708,   709,
     710,   921,   711,   712,   923,   924,   931,   934,   120, -1300,
   -1300,   120, -1300,   814,   167, -1300,   815,     1, -1300,   817,
     322, -1300,   823,  1321, -1300,   825,   254, -1300,   269,   828,
   -1300,   278, -1300,   841,   -96, -1300,   842,   715,   716,   717,
     718,   720,   721,   228, -1300,   744,   730,   731,    39, -1300,
     939,   942,   944,   734,   945,   747,   289, -1300,   289, -1300,
     843,   752,   947,   756,   948,   179, -1300, -1300,   226,   844,
   -1300,   762,   776,   795,   796,    19, -1300, -1300,  1000,  1007,
      91, -1300,   845,  1011, -1300, -1300,   690,   806, -1300,   812,
     818,   819,   833, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300,   139, -1300, -1300,   834,   835,   837,   849,
   -1300,   425, -1300,   427, -1300,  1010, -1300,  1018, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,   436, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,  1069, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300,  1098,  1104, -1300, -1300, -1300, -1300, -1300, -1300,
    1100, -1300,   439, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,    17,   899,   902, -1300,  1103,
   -1300, -1300,   454, -1300, -1300,   913, -1300,    51, -1300, -1300,
    1107, -1300, -1300, -1300, -1300, -1300,   455, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   914,   461,
   -1300,   803, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
    1321, -1300,  1108,  1110,   920, -1300,   269, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,    21, -1300, -1300, -1300,  1111,
     925,  1112,   226, -1300, -1300, -1300, -1300, -1300,   922,   927,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   464,
   -1300, -1300, -1300, -1300, -1300,  1113, -1300,   928, -1300, -1300,
   -1300,  1115,  1116,  1117,  1119,    21, -1300,  1120, -1300,   952,
     929,   930,  1121, -1300, -1300,   293, -1300, -1300, -1300, -1300,
   -1300,  1122,    66,  1120, -1300, -1300,  1118,  1125, -1300, -1300,
    1126,  1127,  1128, -1300,   471, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300,   175, -1300,  1122,  1129,   933,   932,   936,  1130,
      66, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   473,
   -1300, -1300, -1300, -1300,   938, -1300, -1300, -1300,   940, -1300,
    1131,  1134,   175, -1300, -1300, -1300,   941,   943, -1300, -1300,
   -1300
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   208,     9,   385,    11,   598,    13,
     627,    15,   513,    17,   522,    19,   561,    21,   347,    23,
     809,    25,   841,    27,    46,    39,     0,     0,     0,     0,
       0,   629,     0,   524,   563,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   839,   193,   226,
       0,     0,     0,   649,   651,   653,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   376,   511,   552,     0,   153,
     174,   456,   614,   616,     0,     0,     0,   309,   676,   618,
     338,   359,     0,   324,   711,   713,   790,   807,   181,   183,
       0,     0,     0,   851,   893,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     104,   134,   135,    93,    94,    95,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   101,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,    77,
      84,    85,    99,   100,   102,    96,    97,    98,    83,    88,
      89,    90,    91,    92,   103,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   440,   442,   444,   589,
     438,   446,     0,   450,   448,   671,   437,   390,   391,   392,
     393,   394,   417,   418,   419,   420,   421,   435,   407,   408,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   436,     0,   387,   397,   412,   413,   414,
     398,   400,   401,   403,   404,   405,   399,   395,   396,   415,
     416,   402,   409,   410,   411,   406,   611,     0,   610,   606,
     607,   605,     0,   600,   603,   604,   608,   609,   669,   655,
     657,   659,   663,   661,   667,   665,   648,   642,   646,   647,
       0,   630,   631,   643,   644,   645,   639,   634,   640,   636,
     637,   638,   641,   635,     0,   542,   283,     0,   546,   544,
     549,     0,   538,   539,     0,   525,   526,   529,   541,   530,
     531,   532,   548,   533,   534,   535,   536,   537,   580,     0,
       0,     0,   587,   578,   579,   582,   583,     0,   564,   565,
     568,   569,   570,   571,   572,   573,   574,   577,   575,   576,
     355,   357,   352,     0,   349,   353,   354,     0,   826,     0,
     829,     0,     0,   833,   837,   824,   822,   823,     0,   811,
     814,   815,   816,   817,   818,   819,   820,   821,   848,     0,
       0,   843,   846,   847,    45,    50,     0,    37,    43,     0,
      64,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    69,    66,     0,     0,     0,     0,     0,     0,     0,
     197,   209,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   389,   386,     0,     0,   602,   599,     0,     0,
       0,     0,     0,     0,     0,     0,   628,   633,   514,     0,
       0,     0,     0,     0,     0,     0,   523,   528,     0,     0,
       0,     0,     0,   562,   567,     0,     0,   351,   348,     0,
       0,     0,     0,     0,     0,     0,     0,   813,   810,     0,
       0,   845,   842,    49,    41,     0,     0,     0,     0,     0,
     155,   156,   157,     0,     0,     0,   191,   192,     0,     0,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,     0,   186,   187,   158,   159,   160,     0,     0,
       0,   172,   173,   180,   185,     0,     0,     0,   152,     0,
       0,     0,     0,     0,   452,   453,   454,     0,     0,     0,
       0,     0,   710,     0,     0,     0,     0,     0,     0,     0,
     188,   189,   190,     0,     0,    68,     0,     0,     0,   220,
     221,   222,   223,   196,     0,     0,     0,     0,     0,     0,
     455,     0,     0,     0,   388,     0,   613,   601,     0,     0,
       0,     0,     0,     0,     0,     0,   632,     0,     0,   540,
       0,     0,     0,   551,   527,     0,   584,   585,   586,     0,
     566,     0,     0,   350,   825,     0,   828,     0,   831,   832,
       0,     0,   812,     0,   850,   844,     0,     0,     0,     0,
       0,   650,   652,   654,     0,     0,   241,   151,   163,   164,
     165,   166,   167,   162,   169,   171,   378,   515,   554,   154,
     176,   177,   178,   179,   175,   458,    38,   615,   617,     0,
       0,   620,   340,     0,     0,     0,   715,     0,     0,   182,
     184,     0,     0,    51,   211,   214,   215,   213,   218,   219,
     217,   441,   443,   445,   591,   439,   447,   451,   449,     0,
     612,   670,   656,   658,   660,   664,   662,   668,   666,   543,
     284,   547,   545,   550,   581,   588,   356,   358,   827,   830,
     835,   836,   834,   838,   241,    42,     0,     0,     0,   233,
     235,     0,   228,   231,   232,   274,   276,   278,   280,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   294,
       0,     0,   301,   303,   305,   307,   273,     0,   248,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,     0,   246,     0,   242,   243,   383,     0,   379,   380,
     520,     0,   516,   517,   559,     0,   555,   556,   463,     0,
     459,   460,   319,   320,   321,   322,   323,     0,   311,   314,
     315,   316,   317,   318,   681,     0,   678,   625,     0,   621,
     622,   345,     0,   341,   342,     0,     0,     0,     0,     0,
       0,     0,   361,   364,   365,   366,   367,   368,   369,     0,
       0,     0,   334,     0,   326,   329,   330,   331,   332,   333,
     737,   742,   744,     0,   748,     0,   736,   730,   731,   732,
     734,   735,     0,   722,   725,   726,   727,   728,   733,   729,
     720,     0,   716,   717,     0,   802,     0,   805,   798,   799,
       0,   792,   795,   796,   797,   800,     0,   856,     0,   853,
       0,     0,     0,     0,   902,     0,   895,   898,   899,   900,
     901,    53,   596,     0,   592,   593,   674,     0,   673,     0,
      62,   840,   194,     0,     0,   230,   227,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   250,   225,
     238,     0,   240,   245,     0,   377,   382,   524,   512,   519,
     563,   553,   558,     0,   457,   462,   313,   310,   683,   680,
     677,   629,   619,   624,     0,   339,   344,     0,     0,     0,
       0,     0,     0,   363,   360,     0,     0,     0,   328,   325,
       0,     0,     0,     0,     0,     0,   724,   712,     0,   714,
     719,     0,     0,     0,     0,   794,   791,   808,     0,   855,
     852,     0,     0,     0,     0,   897,   894,    55,     0,    54,
       0,   590,   595,     0,   672,   849,     0,     0,   229,     0,
       0,     0,     0,   282,   285,   286,   287,   288,   289,   290,
     291,   292,   293,     0,   299,   300,     0,     0,     0,     0,
     249,     0,   244,     0,   381,     0,   518,     0,   557,   510,
     485,   486,   487,   471,   472,   490,   491,   492,   493,   494,
     508,   474,   475,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   509,   468,   469,   470,
     483,   484,   480,   481,   482,     0,   465,   473,   488,   489,
     476,   477,   478,   479,   461,   312,   705,   707,     0,   699,
     700,   701,   702,   703,   704,   692,   693,   697,   698,   694,
     695,   696,     0,   684,   685,   688,   689,   690,   691,   679,
       0,   623,     0,   343,   370,   371,   372,   373,   374,   375,
     362,   335,   336,   337,   327,     0,     0,     0,   746,     0,
     747,   723,     0,   718,   801,     0,   804,     0,   793,   871,
       0,   869,   867,   861,   865,   866,     0,   858,   863,   864,
     862,   854,   903,   904,   905,   906,   896,    52,    57,     0,
     594,     0,   234,   236,   275,   277,   279,   281,   296,   297,
     298,   295,   302,   304,   306,   308,   247,   384,   521,   560,
     467,   464,     0,     0,     0,   682,   687,   626,   346,   739,
     740,   741,   738,   743,   745,     0,   721,   803,   806,     0,
       0,     0,   860,   857,    56,   597,   675,   466,     0,     0,
     709,   686,   760,   763,   765,   767,   759,   758,   757,     0,
     750,   753,   754,   755,   756,     0,   868,     0,   859,   706,
     708,     0,     0,     0,     0,   752,   749,     0,   870,     0,
       0,     0,     0,   751,   876,     0,   873,   762,   761,   764,
     766,   769,     0,   875,   872,   774,     0,   770,   771,   886,
       0,     0,     0,   891,     0,   878,   881,   882,   883,   884,
     885,   874,     0,   768,   773,     0,     0,     0,     0,     0,
     880,   877,   786,   788,   785,   779,   781,   783,   784,     0,
     776,   780,   782,   772,     0,   888,   889,   890,     0,   879,
       0,     0,   778,   775,   887,   892,     0,     0,   777,   787,
     789
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,   -59, -1300,  -580, -1300,   194,
   -1300, -1300, -1300, -1300, -1300, -1300,  -635, -1300, -1300, -1300,
     -67, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   433,   638,
      36,    38,    40,   -54,   -51,   -39,   -38,   -37,   -20,   -19,
   -1300, -1300, -1300, -1300,   -18, -1300, -1300,    10,    13,    56,
      57,    60,    61, -1300, -1300,    64, -1300,    68, -1300,    71,
      72,    74, -1300, -1300,    75,    76, -1300,    78, -1300,    79,
   -1300, -1300, -1300, -1300, -1300,    53, -1300, -1300, -1300,   446,
     631, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
     157, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   354,
   -1300,   130, -1300,  -692,   136, -1300, -1300, -1299, -1300, -1290,
   -1300, -1300, -1300, -1300,   -30, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
    -734, -1300,  -731, -1300,  -728, -1300, -1300, -1300, -1300, -1300,
   -1300,   121, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
     106, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   129, -1300,
   -1300, -1300,   123,   615, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300,   119, -1300, -1300, -1300, -1300, -1300, -1300,  -995, -1300,
   -1300, -1300,   151, -1300, -1300, -1300,   155,   648, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300,  -994, -1300,   -11, -1300,
      23, -1300,    82,    86,    90, -1300, -1300, -1300, -1300, -1300,
     146, -1300, -1300,   -92,   -62, -1300, -1300, -1300, -1300, -1300,
     156, -1300, -1300, -1300,   159, -1300,   626, -1300,   -61, -1300,
   -1300, -1300, -1300, -1300,   -58, -1300, -1300, -1300, -1300, -1300,
     -31, -1300, -1300, -1300,   152, -1300, -1300, -1300,   158, -1300,
     625, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,    98, -1300, -1300, -1300,    97,
     655, -1300, -1300, -1300,   -49, -1300,    -3, -1300,   -57, -1300,
   -1300, -1300,   150, -1300, -1300, -1300,   160, -1300,   651,     9,
   -1300,    16, -1300,    20, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300,  -989, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   161,
   -1300, -1300, -1300,   -84, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300,   124, -1300,   127,
     133, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300,  -129, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300,  -167, -1300, -1300,  -190, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300,   132, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300,   447,   627, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300,   488,   629, -1300, -1300,
   -1300, -1300, -1300, -1300,   134, -1300, -1300,   -81, -1300, -1300,
   -1300, -1300, -1300, -1300,  -135, -1300, -1300,  -158, -1300, -1300,
   -1300, -1300, -1300, -1300, -1300, -1300, -1300, -1300,   137, -1300,
   -1300, -1300, -1300
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   737,
      82,    83,    39,    64,    79,    80,   754,   971,  1078,  1079,
     826,    41,    66,    85,   429,    86,    43,    67,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   457,   171,   172,   474,   173,   174,   175,   176,
     177,   178,   179,   463,   723,   180,   464,   181,   465,   182,
     183,   184,   475,   734,   185,   186,   493,   187,   494,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   433,   235,
     236,    45,    68,   237,   503,   238,   504,   757,   239,   505,
     760,   240,   241,   242,   243,   197,   443,   198,   434,   801,
     802,   803,   983,   804,   984,   199,   444,   200,   445,   853,
     854,   855,  1011,   827,   828,   829,   987,   830,   988,   831,
     989,   832,   990,   833,   834,   540,   835,   836,   837,   838,
     839,   840,   841,   842,   843,   844,  1001,  1251,   845,   846,
     847,  1004,   848,  1005,   849,  1006,   850,  1007,   201,   482,
     877,   878,   879,   880,   881,   882,   883,   202,   488,   913,
     914,   915,   916,   917,   203,   485,   892,   893,   894,  1034,
      59,    75,   393,   394,   395,   555,   396,   556,   204,   486,
     901,   902,   903,   904,   905,   906,   907,   908,   205,   470,
     857,   858,   859,  1014,    47,    69,   284,   285,   286,   516,
     287,   512,   288,   513,   289,   514,   290,   517,   291,   520,
     292,   519,   206,   207,   208,   296,   209,   476,   869,   870,
     871,  1023,  1155,  1156,   210,   471,    53,    72,   861,   862,
     863,  1017,    55,    73,   354,   355,   356,   357,   358,   359,
     360,   539,   361,   543,   362,   542,   363,   364,   544,   365,
     211,   472,   865,   866,   867,  1020,    57,    74,   377,   378,
     379,   380,   381,   548,   382,   383,   384,   385,   386,   387,
     552,   298,   515,   973,   974,   975,  1080,    49,    70,   312,
     313,   314,   524,   315,   212,   477,   213,   478,   214,   484,
     888,   889,   890,  1031,    51,    71,   330,   331,   332,   215,
     438,   216,   439,   217,   440,   336,   529,   337,   530,   338,
     531,   339,   533,   340,   532,   341,   535,   342,   534,   343,
     528,   305,   521,   977,   978,  1083,   218,   483,   885,   886,
    1028,  1182,  1183,  1184,  1185,  1186,  1262,  1187,  1263,  1188,
     219,   220,   489,   221,   490,   941,   942,   943,  1058,   932,
     933,   934,  1050,  1272,   935,  1051,   936,  1052,   937,   938,
     939,  1054,  1299,  1300,  1301,  1311,  1328,  1302,  1312,  1303,
    1313,  1304,  1314,  1336,  1337,  1338,  1352,  1369,  1370,  1371,
    1380,  1372,  1381,   222,   491,   950,   951,   952,   953,  1062,
     954,   955,  1064,   223,   492,    61,    76,   408,   409,   410,
     411,   560,   412,   413,   562,   414,   415,   416,   565,   792,
     417,   566,   224,   432,    63,    77,   420,   421,   422,   569,
     423,   225,   498,   958,   959,  1068,  1226,  1227,  1228,  1229,
    1281,  1230,  1279,  1325,  1326,  1332,  1344,  1345,  1346,  1355,
    1347,  1348,  1349,  1350,  1359,   226,   499,   965,   966,   967,
     968,   969,   970
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   256,   308,   326,    78,   352,   373,   392,   405,
     344,   927,   301,   375,   928,   260,   376,   929,   261,   244,
     299,   316,   328,   851,   366,   388,   767,   406,  1148,  1149,
     262,   263,   264,   771,  1163,    28,   790,    40,   297,   311,
     327,   345,   736,   353,   374,   390,   391,   430,    42,   265,
     266,   267,   431,  1365,   785,    44,    29,    46,    30,   309,
      31,  1292,  1366,   390,   391,   245,   300,   317,   329,    48,
     367,   389,    50,   407,   718,   719,   720,   721,   302,   268,
     333,    81,   269,  1365,    52,   303,   126,   334,    54,   304,
      56,   335,  1366,   310,    84,   346,   501,   347,   348,   418,
     419,   502,   349,   350,   351,   257,    58,   258,    60,   259,
     227,   228,   736,   722,   229,   132,   133,   230,   231,   232,
     233,  1026,   283,    62,  1027,   270,   271,   155,  1029,   272,
     273,  1030,   424,   274,   510,   132,   133,   275,   425,   511,
     276,   277,   426,   278,   279,   280,  1069,   281,   282,  1070,
     427,   293,   522,   132,   133,   294,   428,   523,   435,   295,
     805,   806,   807,   808,   809,   810,   811,   812,   813,   814,
     815,   816,   817,   818,   819,  1269,  1270,  1271,   820,   821,
     822,   823,   824,   825,   127,   526,   536,  1293,  1294,  1295,
     527,   909,   910,   911,  1248,  1249,  1250,    91,    92,    93,
      94,    95,    96,   791,   306,   132,   133,   557,   567,   132,
     133,   436,   558,   568,   346,   253,   806,   807,   571,   254,
     307,   758,   759,   572,   155,   960,   961,   962,   963,   755,
     756,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   437,   155,   441,   155,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   442,   246,   247,   248,   446,
     127,   447,   155,   448,  1339,  1148,  1149,  1340,  1341,  1342,
    1343,  1163,   129,   130,    32,    33,    34,    35,   449,   249,
     450,   132,   133,   250,   251,   252,   134,   135,   136,   132,
     133,   253,   451,   132,   133,   254,  1333,   139,   452,  1334,
     453,    93,    94,    95,    96,   255,   799,   800,   501,   537,
      93,    94,    95,   980,   155,   454,   571,   538,   155,  1111,
     346,   981,   927,   455,   927,   928,   510,   928,   929,   456,
     929,   982,   985,   101,   102,   103,   458,   986,   459,   460,
     132,   133,  1008,   155,  1362,  1363,   461,  1009,   462,   822,
     823,   824,   944,   945,   946,  1008,   546,   466,   148,   149,
    1010,   126,   127,   346,  1043,  1048,   573,   574,   467,  1044,
    1049,   127,   895,   896,   897,   898,   899,   900,   468,   469,
    1056,   553,   473,   132,   133,  1057,   872,   873,   874,   875,
     155,   876,   132,   133,  1166,  1167,  1168,   479,   155,   480,
    1065,   318,   947,   132,   133,  1066,   481,   487,   495,   319,
     320,   321,   322,   323,   324,   325,   346,   368,   347,   348,
     369,   370,   371,  1219,   567,  1220,  1221,  1075,  1008,  1067,
     522,   547,  1076,  1256,   156,  1257,   132,   133,   496,  1260,
     575,   497,   557,   234,  1261,   372,   920,  1268,   500,   155,
     921,   922,   923,   924,   506,   256,   507,  1056,  1282,   308,
     925,   244,  1276,  1283,   526,   301,   508,  1315,   260,  1285,
     326,   261,  1316,   299,  1360,   554,  1382,   316,   509,  1361,
     352,  1383,   518,   262,   263,   264,   525,   373,   328,   541,
     545,   297,   155,   375,   549,   311,   376,   550,   366,   551,
     405,   155,   265,   266,   267,   388,   327,   245,   730,   731,
     732,   733,   155,   559,   561,   309,   563,   353,   406,   300,
     564,   570,   576,   317,   374,   577,   578,   579,   580,   581,
     582,   302,   268,   583,   329,   269,   584,   585,   303,   586,
     587,   588,   304,   589,   367,   155,   333,   590,   591,   310,
     592,   389,   593,   334,   132,   133,   596,   335,   257,   602,
     258,   594,   259,   597,   407,   595,   605,   608,   598,   609,
     599,   600,   606,   601,   603,   283,   610,   607,   270,   271,
     604,   611,   272,   273,   612,   613,   274,   615,   616,   614,
     275,   617,   618,   276,   277,   619,   278,   279,   280,   620,
     281,   282,   621,   622,   293,   623,  1286,   624,   294,   625,
     626,   627,   295,   628,   629,   630,   631,   397,   398,   399,
     400,   401,   402,   403,   404,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   632,   633,
     156,   634,   234,   635,   636,   637,   638,   795,   639,   640,
     643,   644,   641,   646,   647,   642,   648,   649,   650,   651,
     244,   654,   652,   155,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   665,   668,   666,   669,   912,   926,   670,
     671,   405,   672,   673,   674,   964,   675,   679,   677,   678,
     680,   681,   682,   683,    87,   918,   930,    88,   948,   406,
     685,   686,   687,   688,   689,   691,   245,   692,   695,    89,
     694,   696,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   697,   698,   699,   700,   701,   703,   704,
     706,   711,   707,   793,   708,   709,   710,   712,   713,   714,
     715,   919,   931,   716,   949,   407,   726,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   717,   724,   725,   126,   127,   727,   728,   729,
     735,    30,   738,   739,   740,   741,   742,   128,   129,   130,
     743,   744,   745,   746,   131,   751,   747,   132,   133,   748,
     749,   750,   134,   135,   136,   137,   138,   752,   753,   761,
     764,   762,   763,   139,   769,   765,   766,   768,   794,   770,
     772,   852,   856,   140,   860,   773,   141,   774,   775,   776,
     864,   777,   868,   142,   143,   884,   778,   779,   144,   145,
     780,   781,   782,   783,   784,   786,   788,   789,   887,   891,
     940,   957,   972,   976,   991,   146,   992,   993,   994,   147,
     995,   996,   997,   998,   999,  1000,  1002,  1003,  1013,  1093,
    1012,  1016,  1015,  1018,   148,   149,   150,   151,   152,   153,
    1019,  1021,  1022,  1025,  1024,  1033,   787,  1032,   154,  1035,
    1036,  1059,  1037,  1038,  1039,  1040,  1041,  1042,  1045,  1046,
    1047,  1053,  1055,  1060,  1077,  1061,   155,  1063,  1071,  1072,
    1073,  1074,  1082,  1242,  1081,  1094,  1086,  1085,  1084,  1087,
    1089,  1090,  1091,  1092,  1096,  1103,  1095,  1106,  1107,  1097,
    1098,  1099,  1100,  1101,  1102,  1108,  1105,  1104,  1109,  1194,
    1195,  1196,  1197,  1205,  1198,  1199,  1206,   256,  1207,  1209,
     352,  1215,  1217,   373,  1202,  1203,  1119,   301,  1208,   375,
     260,  1169,   376,   261,   326,   299,  1175,   392,   366,  1123,
    1201,   388,  1124,  1210,  1158,   262,   263,   264,  1214,  1177,
    1216,   912,   328,   297,  1125,  1126,  1127,   353,  1232,   926,
     374,   926,  1157,  1147,   265,   266,   267,  1176,  1174,   918,
     327,  1222,  1233,  1128,  1129,  1130,  1237,   930,   964,   930,
    1238,   300,  1150,   308,   367,  1241,   948,   389,  1258,  1224,
    1159,  1234,  1235,   302,   268,  1178,  1259,   269,   329,  1243,
     303,   316,  1160,  1131,   304,  1244,  1132,  1179,  1223,  1161,
     333,  1245,  1246,  1162,  1180,   919,  1151,   334,  1181,   311,
     257,   335,   258,   931,   259,   931,  1247,  1252,  1253,  1120,
    1254,  1121,   949,  1122,  1170,  1225,  1171,   283,  1172,   309,
     270,   271,  1255,  1264,   272,   273,  1146,   317,   274,  1133,
    1134,  1173,   275,  1135,  1136,   276,   277,  1137,   278,   279,
     280,  1138,   281,   282,  1139,  1140,   293,  1141,  1142,  1143,
     294,  1144,  1145,   310,   295,  1152,  1265,  1266,  1267,  1153,
    1275,  1280,  1288,  1154,  1289,  1305,  1307,  1327,  1317,  1319,
    1320,  1321,  1273,  1322,  1353,  1274,  1331,  1324,  1354,  1335,
    1356,  1357,  1358,  1374,  1378,  1386,  1277,  1284,  1387,   645,
     796,   653,  1088,  1112,  1110,  1309,  1290,  1165,   979,  1306,
    1310,  1318,  1329,  1330,  1204,   798,  1376,  1192,  1278,  1375,
    1377,  1384,  1200,  1385,  1389,  1193,  1390,  1114,  1287,  1113,
     664,  1164,   693,   684,  1118,  1116,  1115,  1239,  1117,   690,
    1240,   667,  1291,  1191,  1213,  1212,  1323,  1373,   676,  1211,
    1189,  1190,  1388,  1119,   702,   956,   797,  1218,  1351,  1169,
     705,  1308,  1379,  1231,  1175,     0,  1123,     0,  1296,  1124,
       0,  1158,  1236,     0,     0,  1222,     0,  1177,     0,     0,
       0,  1125,  1126,  1127,     0,     0,  1297,     0,     0,  1157,
    1147,     0,     0,  1224,     0,  1176,  1174,     0,     0,     0,
    1128,  1129,  1130,     0,     0,     0,     0,     0,  1296,  1150,
       0,     0,  1223,     0,     0,     0,     0,  1159,     0,     0,
       0,     0,     0,  1178,     0,     0,  1297,     0,     0,  1160,
    1131,     0,  1298,  1132,     0,  1179,  1161,     0,     0,  1225,
    1162,     0,  1180,  1151,     0,  1364,  1181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1120,     0,  1121,     0,
    1122,     0,  1170,  1367,  1171,     0,  1172,     0,     0,     0,
       0,     0,  1298,  1146,     0,  1364,  1133,  1134,     0,  1173,
    1135,  1136,     0,     0,  1137,     0,     0,     0,  1138,     0,
       0,  1139,  1140,  1367,  1141,  1142,  1143,     0,  1144,  1145,
       0,     0,  1152,     0,     0,     0,  1153,     0,     0,  1368,
    1154,    91,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1368,
       0,     0,     0,     0,     0,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,   127,   346,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   130,     0,     0,
       0,     0,     0,     0,     0,   132,   133,     0,   251,     0,
     134,   135,   136,     0,     0,   253,     0,     0,     0,   254,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   255,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   148,   149,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   155
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,   745,    69,    74,   745,    69,    74,   745,    69,    68,
      69,    70,    71,   715,    73,    74,   661,    76,  1023,  1023,
      69,    69,    69,   668,  1023,     0,    18,     7,    69,    70,
      71,    40,   622,    73,    74,   141,   142,     3,     7,    69,
      69,    69,     8,  1352,   689,     7,     5,     7,     7,    70,
       9,    40,  1352,   141,   142,    68,    69,    70,    71,     7,
      73,    74,     7,    76,   187,   188,   189,   190,    69,    69,
      71,   223,    69,  1382,     7,    69,    92,    71,     7,    69,
       7,    71,  1382,    70,    10,    94,     3,    96,    97,    12,
      13,     8,   101,   102,   103,    69,     7,    69,     7,    69,
      15,    16,   692,   226,    19,   114,   115,    22,    23,    24,
      25,     3,    69,     7,     6,    69,    69,   223,     3,    69,
      69,     6,     6,    69,     3,   114,   115,    69,     3,     8,
      69,    69,     4,    69,    69,    69,     3,    69,    69,     6,
       8,    69,     3,   114,   115,    69,     3,     8,     4,    69,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   158,   159,   160,    58,    59,
      60,    61,    62,    63,    93,     3,     8,   166,   167,   168,
       8,   152,   153,   154,    55,    56,    57,    30,    31,    32,
      33,    34,    35,   185,   113,   114,   115,     3,     3,   114,
     115,     4,     8,     8,    94,   124,    41,    42,     3,   128,
     129,    20,    21,     8,   223,   206,   207,   208,   209,    17,
      18,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     4,   223,     4,   223,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     4,    89,    90,    91,     4,
      93,     4,   223,     4,   198,  1260,  1260,   201,   202,   203,
     204,  1260,   105,   106,   223,   224,   225,   226,     4,   112,
       4,   114,   115,   116,   117,   118,   119,   120,   121,   114,
     115,   124,     4,   114,   115,   128,     3,   130,     4,     6,
       4,    32,    33,    34,    35,   138,    27,    28,     3,     3,
      32,    33,    34,     8,   223,     4,     3,     8,   223,  1011,
      94,     8,  1056,     4,  1058,  1056,     3,  1058,  1056,     4,
    1058,     8,     3,    64,    65,    66,     4,     8,     4,     4,
     114,   115,     3,   223,   169,   170,     4,     8,     4,    60,
      61,    62,   173,   174,   175,     3,     8,     4,   191,   192,
       8,    92,    93,    94,     3,     3,   425,   426,     4,     8,
       8,    93,   144,   145,   146,   147,   148,   149,     4,     4,
       3,     8,     4,   114,   115,     8,   132,   133,   134,   135,
     223,   137,   114,   115,   125,   126,   127,     4,   223,     4,
       3,   123,   223,   114,   115,     8,     4,     4,     4,   131,
     132,   133,   134,   135,   136,   137,    94,    95,    96,    97,
      98,    99,   100,   197,     3,   199,   200,     3,     3,     8,
       3,     3,     8,     8,   501,     8,   114,   115,     4,     3,
     223,     4,     3,   510,     8,   123,   157,     8,     4,   223,
     161,   162,   163,   164,     4,   522,     4,     3,     3,   526,
     171,   510,     8,     8,     3,   522,     4,     3,   522,     8,
     537,   522,     8,   522,     3,     3,     3,   526,     4,     8,
     547,     8,     4,   522,   522,   522,     4,   554,   537,     4,
       4,   522,   223,   554,     4,   526,   554,     4,   547,     4,
     567,   223,   522,   522,   522,   554,   537,   510,   107,   108,
     109,   110,   223,     4,     4,   526,     4,   547,   567,   522,
       4,     4,     4,   526,   554,     4,     4,     4,   226,   226,
     226,   522,   522,     4,   537,   522,     4,     4,   522,   224,
     226,     4,   522,     4,   547,   223,   537,     4,   224,   526,
     224,   554,   224,   537,   114,   115,   226,   537,   522,     4,
     522,   224,   522,   225,   567,   224,   226,     4,   225,     4,
     225,   224,   226,   224,   224,   522,     4,   226,   522,   522,
     224,   226,   522,   522,   226,   225,   522,     4,     4,   226,
     522,     4,   224,   522,   522,     4,   522,   522,   522,     4,
     522,   522,     4,     4,   522,     4,  1241,   226,   522,   226,
     226,     4,   522,     4,     4,     4,     4,   177,   178,   179,
     180,   181,   182,   183,   184,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   224,     4,
     707,     4,   709,     4,     4,     4,     4,   706,     4,   226,
       4,     4,   226,     4,     4,   226,     4,   226,   226,   224,
     709,     4,   224,   223,     4,     4,     4,     4,     4,   224,
       4,     4,     4,     4,     4,   224,     4,   744,   745,     4,
       4,   748,     4,     4,     4,   752,     4,   224,     4,     4,
       4,     4,     4,   226,    11,   744,   745,    14,   747,   748,
       4,   226,   226,   226,     4,     4,   709,     4,     4,    26,
     226,   224,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     4,   224,   224,     4,     4,     4,   224,
       4,   223,     7,   186,     7,     7,     7,   223,   223,     7,
       7,   744,   745,     5,   747,   748,     5,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   223,   223,   223,    92,    93,     5,     5,   223,
       5,     7,   223,     5,     5,     5,     5,   104,   105,   106,
       7,     7,     7,     5,   111,     5,     7,   114,   115,     7,
     223,   223,   119,   120,   121,   122,   123,     7,     5,   223,
       5,   223,   223,   130,     7,   223,   223,   223,     5,   223,
     223,     7,     7,   140,     7,   223,   143,   223,   223,   223,
       7,   223,     7,   150,   151,     7,   223,   223,   155,   156,
     223,   223,   223,   223,   223,   223,   223,   223,     7,     7,
       7,     7,     7,   139,     4,   172,     4,     4,     4,   176,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   224,
       6,     3,     6,     6,   191,   192,   193,   194,   195,   196,
       3,     6,     3,     3,     6,     3,   692,     6,   205,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   223,     4,   223,     4,     4,     4,
       4,     4,     3,   223,     6,   226,     4,     6,     8,     4,
       4,     4,     4,     4,   226,     4,   224,     4,     4,   224,
     224,   224,   224,   224,   224,     4,   224,   226,     4,   224,
     224,   224,   224,     4,   224,   224,     4,  1014,     4,     4,
    1017,     4,     4,  1020,   224,   224,  1023,  1014,   224,  1020,
    1014,  1028,  1020,  1014,  1031,  1014,  1028,  1034,  1017,  1023,
     226,  1020,  1023,   226,  1023,  1014,  1014,  1014,   226,  1028,
     224,  1048,  1031,  1014,  1023,  1023,  1023,  1017,   226,  1056,
    1020,  1058,  1023,  1023,  1014,  1014,  1014,  1028,  1028,  1048,
    1031,  1068,   226,  1023,  1023,  1023,     6,  1056,  1075,  1058,
       3,  1014,  1023,  1080,  1017,     4,  1065,  1020,     8,  1068,
    1023,   226,   226,  1014,  1014,  1028,     8,  1014,  1031,   223,
    1014,  1080,  1023,  1023,  1014,   223,  1023,  1028,  1068,  1023,
    1031,   223,   223,  1023,  1028,  1048,  1023,  1031,  1028,  1080,
    1014,  1031,  1014,  1056,  1014,  1058,   223,   223,   223,  1023,
     223,  1023,  1065,  1023,  1028,  1068,  1028,  1014,  1028,  1080,
    1014,  1014,   223,     4,  1014,  1014,  1023,  1080,  1014,  1023,
    1023,  1028,  1014,  1023,  1023,  1014,  1014,  1023,  1014,  1014,
    1014,  1023,  1014,  1014,  1023,  1023,  1014,  1023,  1023,  1023,
    1014,  1023,  1023,  1080,  1014,  1023,     8,     3,     8,  1023,
       7,     4,     4,  1023,     4,     4,     4,   165,     5,     4,
       4,     4,   223,     4,     6,   223,     5,     7,     3,     7,
       4,     4,     4,     4,     4,     4,   223,   223,     4,   501,
     707,   510,   985,  1013,  1008,   223,   226,  1026,   794,   224,
     223,   223,   223,   223,  1048,   709,   224,  1034,  1217,   226,
     224,   223,  1043,   223,   223,  1036,   223,  1016,  1260,  1014,
     522,  1025,   557,   547,  1022,  1019,  1017,  1080,  1020,   554,
    1082,   526,  1266,  1033,  1060,  1058,  1315,  1354,   537,  1056,
    1029,  1031,  1382,  1260,   567,   748,   708,  1065,  1333,  1266,
     571,  1282,  1360,  1069,  1266,    -1,  1260,    -1,  1275,  1260,
      -1,  1260,  1075,    -1,    -1,  1282,    -1,  1266,    -1,    -1,
      -1,  1260,  1260,  1260,    -1,    -1,  1275,    -1,    -1,  1260,
    1260,    -1,    -1,  1282,    -1,  1266,  1266,    -1,    -1,    -1,
    1260,  1260,  1260,    -1,    -1,    -1,    -1,    -1,  1315,  1260,
      -1,    -1,  1282,    -1,    -1,    -1,    -1,  1260,    -1,    -1,
      -1,    -1,    -1,  1266,    -1,    -1,  1315,    -1,    -1,  1260,
    1260,    -1,  1275,  1260,    -1,  1266,  1260,    -1,    -1,  1282,
    1260,    -1,  1266,  1260,    -1,  1352,  1266,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1260,    -1,  1260,    -1,
    1260,    -1,  1266,  1352,  1266,    -1,  1266,    -1,    -1,    -1,
      -1,    -1,  1315,  1260,    -1,  1382,  1260,  1260,    -1,  1266,
    1260,  1260,    -1,    -1,  1260,    -1,    -1,    -1,  1260,    -1,
      -1,  1260,  1260,  1382,  1260,  1260,  1260,    -1,  1260,  1260,
      -1,    -1,  1260,    -1,    -1,    -1,  1260,    -1,    -1,  1352,
    1260,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1382,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,   115,    -1,   117,    -1,
     119,   120,   121,    -1,    -1,   124,    -1,    -1,    -1,   128,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   223
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,     0,     5,
       7,     9,   223,   224,   225,   226,   242,   243,   244,   249,
       7,   258,     7,   263,     7,   318,     7,   431,     7,   514,
       7,   531,     7,   463,     7,   469,     7,   493,     7,   407,
       7,   632,     7,   651,   250,   245,   259,   264,   319,   432,
     515,   532,   464,   470,   494,   408,   633,   652,   242,   251,
     252,   223,   247,   248,    10,   260,   262,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    92,    93,   104,   105,
     106,   111,   114,   115,   119,   120,   121,   122,   123,   130,
     140,   143,   150,   151,   155,   156,   172,   176,   191,   192,
     193,   194,   195,   196,   205,   223,   257,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   280,   281,   283,   284,   285,   286,   287,   288,   289,
     292,   294,   296,   297,   298,   301,   302,   304,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   332,   334,   342,
     344,   385,   394,   401,   415,   425,   449,   450,   451,   453,
     461,   487,   521,   523,   525,   536,   538,   540,   563,   577,
     578,   580,   620,   630,   649,   658,   682,    15,    16,    19,
      22,    23,    24,    25,   257,   316,   317,   320,   322,   325,
     328,   329,   330,   331,   521,   523,    89,    90,    91,   112,
     116,   117,   118,   124,   128,   138,   257,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   281,   284,   285,
     286,   287,   288,   289,   292,   294,   296,   297,   298,   301,
     302,   304,   306,   312,   433,   434,   435,   437,   439,   441,
     443,   445,   447,   449,   450,   451,   452,   487,   508,   521,
     523,   525,   536,   538,   540,   558,   113,   129,   257,   445,
     447,   487,   516,   517,   518,   520,   521,   523,   123,   131,
     132,   133,   134,   135,   136,   137,   257,   487,   521,   523,
     533,   534,   535,   536,   538,   540,   542,   544,   546,   548,
     550,   552,   554,   556,   461,    40,    94,    96,    97,   101,
     102,   103,   257,   361,   471,   472,   473,   474,   475,   476,
     477,   479,   481,   483,   484,   486,   521,   523,    95,    98,
      99,   100,   123,   257,   361,   475,   481,   495,   496,   497,
     498,   499,   501,   502,   503,   504,   505,   506,   521,   523,
     141,   142,   257,   409,   410,   411,   413,   177,   178,   179,
     180,   181,   182,   183,   184,   257,   521,   523,   634,   635,
     636,   637,   639,   640,   642,   643,   644,   647,    12,    13,
     653,   654,   655,   657,     6,     3,     4,     8,     3,   261,
       3,     8,   650,   315,   335,     4,     4,     4,   537,   539,
     541,     4,     4,   333,   343,   345,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   279,     4,     4,
       4,     4,     4,   290,   293,   295,     4,     4,     4,     4,
     426,   462,   488,     4,   282,   299,   454,   522,   524,     4,
       4,     4,   386,   564,   526,   402,   416,     4,   395,   579,
     581,   621,   631,   303,   305,     4,     4,     4,   659,   683,
       4,     3,     8,   321,   323,   326,     4,     4,     4,     4,
       3,     8,   438,   440,   442,   509,   436,   444,     4,   448,
     446,   559,     3,     8,   519,     4,     3,     8,   557,   543,
     545,   547,   551,   549,   555,   553,     8,     3,     8,   478,
     362,     4,   482,   480,   485,     4,     8,     3,   500,     4,
       4,     4,   507,     8,     3,   412,   414,     3,     8,     4,
     638,     4,   641,     4,     4,   645,   648,     3,     8,   656,
       4,     3,     8,   242,   242,   223,     4,     4,     4,     4,
     226,   226,   226,     4,     4,     4,   224,   226,     4,     4,
       4,   224,   224,   224,   224,   224,   226,   225,   225,   225,
     224,   224,     4,   224,   224,   226,   226,   226,     4,     4,
       4,   226,   226,   225,   226,     4,     4,     4,   224,     4,
       4,     4,     4,     4,   226,   226,   226,     4,     4,     4,
       4,     4,   224,     4,     4,     4,     4,     4,     4,     4,
     226,   226,   226,     4,     4,   266,     4,     4,     4,   226,
     226,   224,   224,   317,     4,     4,     4,     4,     4,     4,
     224,     4,     4,     4,   434,     4,   224,   517,     4,     4,
       4,     4,     4,     4,     4,     4,   535,     4,     4,   224,
       4,     4,     4,   226,   473,     4,   226,   226,   226,     4,
     497,     4,     4,   410,   226,     4,   224,     4,   224,   224,
       4,     4,   635,     4,   224,   654,     4,     7,     7,     7,
       7,   223,   223,   223,     7,     7,     5,   223,   187,   188,
     189,   190,   226,   291,   223,   223,     5,     5,     5,   223,
     107,   108,   109,   110,   300,     5,   244,   246,   223,     5,
       5,     5,     5,     7,     7,     7,     5,     7,     7,   223,
     223,     5,     7,     5,   253,    17,    18,   324,    20,    21,
     327,   223,   223,   223,     5,   223,   223,   253,   223,     7,
     223,   253,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   253,   223,   246,   223,   223,
      18,   185,   646,   186,     5,   242,   265,   653,   316,    27,
      28,   336,   337,   338,   340,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      58,    59,    60,    61,    62,    63,   257,   350,   351,   352,
     354,   356,   358,   360,   361,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   375,   376,   377,   379,   381,
     383,   350,     7,   346,   347,   348,     7,   427,   428,   429,
       7,   465,   466,   467,     7,   489,   490,   491,     7,   455,
     456,   457,   132,   133,   134,   135,   137,   387,   388,   389,
     390,   391,   392,   393,     7,   565,   566,     7,   527,   528,
     529,     7,   403,   404,   405,   144,   145,   146,   147,   148,
     149,   417,   418,   419,   420,   421,   422,   423,   424,   152,
     153,   154,   257,   396,   397,   398,   399,   400,   521,   523,
     157,   161,   162,   163,   164,   171,   257,   377,   379,   381,
     521,   523,   586,   587,   588,   591,   593,   595,   596,   597,
       7,   582,   583,   584,   173,   174,   175,   223,   521,   523,
     622,   623,   624,   625,   627,   628,   634,     7,   660,   661,
     206,   207,   208,   209,   257,   684,   685,   686,   687,   688,
     689,   254,     7,   510,   511,   512,   139,   560,   561,   346,
       8,     8,     8,   339,   341,     3,     8,   353,   355,   357,
     359,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   373,     4,     4,   378,   380,   382,   384,     3,     8,
       8,   349,     6,     3,   430,     6,     3,   468,     6,     3,
     492,     6,     3,   458,     6,     3,     3,     6,   567,     3,
       6,   530,     6,     3,   406,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     589,   592,   594,     4,   598,     4,     3,     8,   585,     6,
       3,     4,   626,     4,   629,     3,     8,     8,   662,     3,
       6,     4,     4,     4,     4,     3,     8,   223,   255,   256,
     513,     6,     3,   562,     8,     6,     4,     4,   337,     4,
       4,     4,     4,   224,   226,   224,   226,   224,   224,   224,
     224,   224,   224,     4,   226,   224,     4,     4,     4,     4,
     351,   350,   348,   433,   429,   471,   467,   495,   491,   257,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     281,   284,   285,   286,   287,   288,   289,   292,   294,   296,
     297,   298,   301,   302,   304,   306,   312,   361,   425,   443,
     445,   447,   449,   450,   451,   459,   460,   487,   521,   523,
     536,   538,   540,   558,   457,   388,   125,   126,   127,   257,
     267,   268,   269,   312,   361,   461,   487,   521,   523,   536,
     538,   540,   568,   569,   570,   571,   572,   574,   576,   566,
     533,   529,   409,   405,   224,   224,   224,   224,   224,   224,
     418,   226,   224,   224,   397,     4,     4,     4,   224,     4,
     226,   587,   586,   584,   226,     4,   224,     4,   623,   197,
     199,   200,   257,   361,   521,   523,   663,   664,   665,   666,
     668,   661,   226,   226,   226,   226,   685,     6,     3,   516,
     512,     4,   223,   223,   223,   223,   223,   223,    55,    56,
      57,   374,   223,   223,   223,   223,     8,     8,     8,     8,
       3,     8,   573,   575,     4,     8,     3,     8,     8,   158,
     159,   160,   590,   223,   223,     7,     8,   223,   242,   669,
       4,   667,     3,     8,   223,     8,   253,   460,     4,     4,
     226,   570,    40,   166,   167,   168,   257,   521,   523,   599,
     600,   601,   604,   606,   608,     4,   224,     4,   664,   223,
     223,   602,   605,   607,   609,     3,     8,     5,   223,     4,
       4,     4,     4,   600,     7,   670,   671,   165,   603,   223,
     223,     5,   672,     3,     6,     7,   610,   611,   612,   198,
     201,   202,   203,   204,   673,   674,   675,   677,   678,   679,
     680,   671,   613,     6,     3,   676,     4,     4,     4,   681,
       3,     8,   169,   170,   257,   354,   356,   521,   523,   614,
     615,   616,   618,   612,     4,   226,   224,   224,     4,   674,
     617,   619,     3,     8,   223,   223,     4,     4,   615,   223,
     223
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   227,   229,   228,   230,   228,   231,   228,   232,   228,
     233,   228,   234,   228,   235,   228,   236,   228,   237,   228,
     238,   228,   239,   228,   240,   228,   241,   228,   242,   242,
     242,   242,   242,   242,   242,   243,   245,   244,   246,   247,
     247,   248,   248,   248,   250,   249,   251,   251,   252,   252,
     252,   254,   253,   255,   255,   256,   256,   256,   257,   259,
     258,   261,   260,   260,   262,   264,   263,   265,   265,   265,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     279,   278,   280,   282,   281,   283,   284,   285,   286,   287,
     288,   290,   289,   291,   291,   291,   291,   291,   293,   292,
     295,   294,   296,   297,   299,   298,   300,   300,   300,   300,
     301,   303,   302,   305,   304,   306,   307,   308,   309,   310,
     311,   312,   313,   315,   314,   316,   316,   316,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   319,   318,
     321,   320,   323,   322,   324,   324,   326,   325,   327,   327,
     328,   329,   330,   331,   333,   332,   335,   334,   336,   336,
     336,   337,   337,   339,   338,   341,   340,   343,   342,   345,
     344,   346,   346,   347,   347,   347,   349,   348,   350,   350,
     350,   351,   351,   351,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   351,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   351,   353,   352,   355,   354,   357,   356,
     359,   358,   360,   362,   361,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   373,   372,   374,   374,   374,   375,
     376,   378,   377,   380,   379,   382,   381,   384,   383,   386,
     385,   387,   387,   387,   388,   388,   388,   388,   388,   389,
     390,   391,   392,   393,   395,   394,   396,   396,   396,   397,
     397,   397,   397,   397,   397,   398,   399,   400,   402,   401,
     403,   403,   404,   404,   404,   406,   405,   408,   407,   409,
     409,   409,   409,   410,   410,   412,   411,   414,   413,   416,
     415,   417,   417,   417,   418,   418,   418,   418,   418,   418,
     419,   420,   421,   422,   423,   424,   426,   425,   427,   427,
     428,   428,   428,   430,   429,   432,   431,   433,   433,   433,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   436,   435,
     438,   437,   440,   439,   442,   441,   444,   443,   446,   445,
     448,   447,   449,   450,   451,   452,   454,   453,   455,   455,
     456,   456,   456,   458,   457,   459,   459,   459,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   462,   461,   464,   463,   465,   465,   466,   466,   466,
     468,   467,   470,   469,   471,   471,   472,   472,   472,   473,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   474,
     475,   476,   478,   477,   480,   479,   482,   481,   483,   485,
     484,   486,   488,   487,   489,   489,   490,   490,   490,   492,
     491,   494,   493,   495,   495,   496,   496,   496,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   498,
     500,   499,   501,   502,   503,   504,   505,   507,   506,   509,
     508,   510,   510,   511,   511,   511,   513,   512,   515,   514,
     516,   516,   516,   517,   517,   517,   517,   517,   517,   517,
     517,   519,   518,   520,   522,   521,   524,   523,   526,   525,
     527,   527,   528,   528,   528,   530,   529,   532,   531,   533,
     533,   534,   534,   534,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   537,
     536,   539,   538,   541,   540,   543,   542,   545,   544,   547,
     546,   549,   548,   551,   550,   553,   552,   555,   554,   557,
     556,   559,   558,   560,   562,   561,   564,   563,   565,   565,
     565,   567,   566,   568,   568,   569,   569,   569,   570,   570,
     570,   570,   570,   570,   570,   570,   570,   570,   570,   570,
     570,   570,   570,   570,   571,   573,   572,   575,   574,   576,
     577,   579,   578,   581,   580,   582,   582,   583,   583,   583,
     585,   584,   586,   586,   586,   587,   587,   587,   587,   587,
     587,   587,   587,   587,   587,   587,   587,   589,   588,   590,
     590,   590,   592,   591,   594,   593,   595,   596,   598,   597,
     599,   599,   599,   600,   600,   600,   600,   600,   600,   600,
     602,   601,   603,   605,   604,   607,   606,   609,   608,   610,
     610,   611,   611,   611,   613,   612,   614,   614,   614,   615,
     615,   615,   615,   615,   615,   615,   617,   616,   619,   618,
     621,   620,   622,   622,   622,   623,   623,   623,   623,   623,
     623,   624,   626,   625,   627,   629,   628,   631,   630,   633,
     632,   634,   634,   634,   635,   635,   635,   635,   635,   635,
     635,   635,   635,   635,   635,   636,   638,   637,   639,   641,
     640,   642,   643,   645,   644,   646,   646,   648,   647,   650,
     649,   652,   651,   653,   653,   653,   654,   654,   656,   655,
     657,   659,   658,   660,   660,   660,   662,   661,   663,   663,
     663,   664,   664,   664,   664,   664,   664,   664,   665,   667,
     666,   669,   668,   670,   670,   670,   672,   671,   673,   673,
     673,   674,   674,   674,   674,   674,   676,   675,   677,   678,
     679,   681,   680,   683,   682,   684,   684,   684,   685,   685,
     685,   685,   685,   686,   687,   688,   689
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     3,     0,     4,     0,
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
  "\"hosts-databases\"", "\"type\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"read-timeout\"",
  "\"write-timeout\"", "\"tcp-user-timeout\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"on-fail\"", "\"stop-retry-exit\"",
  "\"serve-retry-exit\"", "\"serve-retry-continue\"",
  "\"retry-on-startup\"", "\"max-row-errors\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cipher-list\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
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
  "database_type", "$@40", "user", "$@41", "password", "$@42", "host",
  "$@43", "port", "name", "$@44", "persist", "lfc_interval", "readonly",
  "connect_timeout", "read_timeout", "write_timeout", "tcp_user_timeout",
  "max_reconnect_tries", "reconnect_wait_time", "on_fail", "$@45",
  "on_fail_mode", "retry_on_startup", "max_row_errors", "trust_anchor",
  "$@46", "cert_file", "$@47", "key_file", "$@48", "cipher_list", "$@49",
  "host_reservation_identifiers", "$@50",
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
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@82", "pools_list", "$@83",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@84",
  "sub_pool4", "$@85", "pool_params", "pool_param", "pool_entry", "$@86",
  "pool_id", "user_context", "$@87", "comment", "$@88", "reservations",
  "$@89", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@90", "sub_reservation", "$@91", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@92", "server_hostname", "$@93", "boot_file_name", "$@94",
  "ip_address", "$@95", "duid", "$@96", "hw_address", "$@97",
  "client_id_value", "$@98", "circuit_id_value", "$@99", "flex_id_value",
  "$@100", "hostname", "$@101", "reservation_client_classes", "$@102",
  "relay", "$@103", "relay_map", "ip_addresses", "$@104", "client_classes",
  "$@105", "client_classes_list", "client_class_entry", "$@106",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@107",
  "client_class_template_test", "$@108", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@109", "control_sockets", "$@110",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@111", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@112",
  "control_socket_type_value", "control_socket_name", "$@113",
  "control_socket_address", "$@114", "control_socket_port",
  "cert_required", "authentication", "$@115", "auth_params", "auth_param",
  "auth_type", "$@116", "auth_type_value", "realm", "$@117", "directory",
  "$@118", "clients", "$@119", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@120", "clients_params", "clients_param", "user_file",
  "$@121", "password_file", "$@122", "dhcp_queue_control", "$@123",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@124", "capacity", "arbitrary_map_entry", "$@125",
  "dhcp_ddns", "$@126", "sub_dhcp_ddns", "$@127", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@128", "server_port",
  "sender_ip", "$@129", "sender_port", "max_queue_size", "ncr_protocol",
  "$@130", "ncr_protocol_value", "ncr_format", "$@131", "config_control",
  "$@132", "sub_config_control", "$@133", "config_control_params",
  "config_control_param", "config_databases", "$@134",
  "config_fetch_wait_time", "loggers", "$@135", "loggers_entries",
  "logger_entry", "$@136", "logger_params", "logger_param", "debuglevel",
  "severity", "$@137", "output_options_list", "$@138",
  "output_options_list_content", "output_entry", "$@139",
  "output_params_list", "output_params", "output", "$@140", "flush",
  "maxsize", "maxver", "pattern", "$@141", "compatibility", "$@142",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   322,   322,   322,   323,   323,   324,   324,   325,   325,
     326,   326,   327,   327,   328,   328,   329,   329,   330,   330,
     331,   331,   332,   332,   333,   333,   334,   334,   342,   343,
     344,   345,   346,   347,   348,   351,   356,   356,   367,   370,
     371,   374,   379,   385,   390,   390,   397,   398,   401,   405,
     409,   415,   415,   422,   423,   426,   430,   434,   444,   453,
     453,   468,   468,   482,   485,   491,   491,   500,   501,   502,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   580,
     586,   592,   598,   604,   610,   616,   622,   628,   634,   640,
     646,   646,   655,   661,   661,   670,   676,   682,   688,   694,
     700,   706,   706,   715,   718,   721,   724,   727,   733,   733,
     742,   742,   751,   760,   770,   770,   779,   782,   785,   788,
     793,   799,   799,   808,   808,   817,   823,   829,   835,   841,
     847,   853,   859,   865,   865,   877,   878,   879,   884,   885,
     886,   887,   888,   889,   890,   891,   892,   893,   896,   896,
     905,   905,   916,   916,   924,   925,   928,   928,   936,   938,
     942,   948,   954,   960,   966,   966,   979,   979,   990,   991,
     992,   997,   998,  1001,  1001,  1020,  1020,  1038,  1038,  1051,
    1051,  1062,  1063,  1066,  1067,  1068,  1073,  1073,  1083,  1084,
    1085,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,  1098,
    1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,  1108,
    1109,  1110,  1111,  1112,  1115,  1115,  1124,  1124,  1133,  1133,
    1142,  1142,  1151,  1157,  1157,  1166,  1172,  1178,  1184,  1190,
    1196,  1202,  1208,  1214,  1220,  1220,  1228,  1229,  1230,  1233,
    1239,  1245,  1245,  1254,  1254,  1263,  1263,  1272,  1272,  1281,
    1281,  1292,  1293,  1294,  1299,  1300,  1301,  1302,  1303,  1306,
    1311,  1316,  1321,  1326,  1333,  1333,  1346,  1347,  1348,  1353,
    1354,  1355,  1356,  1357,  1358,  1361,  1367,  1373,  1379,  1379,
    1390,  1391,  1394,  1395,  1396,  1401,  1401,  1411,  1411,  1421,
    1422,  1423,  1426,  1429,  1430,  1433,  1433,  1442,  1442,  1451,
    1451,  1463,  1464,  1465,  1470,  1471,  1472,  1473,  1474,  1475,
    1478,  1484,  1490,  1496,  1502,  1508,  1517,  1517,  1531,  1532,
    1535,  1536,  1537,  1546,  1546,  1572,  1572,  1583,  1584,  1585,
    1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,
    1601,  1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,
    1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,
    1621,  1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1637,  1638,  1641,  1641,
    1650,  1650,  1659,  1659,  1668,  1668,  1677,  1677,  1686,  1686,
    1695,  1695,  1706,  1712,  1718,  1724,  1732,  1732,  1744,  1745,
    1749,  1750,  1751,  1756,  1756,  1764,  1765,  1766,  1771,  1772,
    1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,
    1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,
    1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,
    1803,  1804,  1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,
    1813,  1820,  1820,  1834,  1834,  1843,  1844,  1847,  1848,  1849,
    1856,  1856,  1871,  1871,  1885,  1886,  1889,  1890,  1891,  1896,
    1897,  1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1908,
    1910,  1916,  1918,  1918,  1927,  1927,  1936,  1936,  1945,  1947,
    1947,  1956,  1966,  1966,  1979,  1980,  1985,  1986,  1987,  1994,
    1994,  2006,  2006,  2018,  2019,  2024,  2025,  2026,  2033,  2034,
    2035,  2036,  2037,  2038,  2039,  2040,  2041,  2042,  2043,  2046,
    2048,  2048,  2057,  2059,  2061,  2067,  2073,  2079,  2079,  2093,
    2093,  2106,  2107,  2110,  2111,  2112,  2117,  2117,  2127,  2127,
    2137,  2138,  2139,  2144,  2145,  2146,  2147,  2148,  2149,  2150,
    2151,  2154,  2154,  2163,  2169,  2169,  2194,  2194,  2224,  2224,
    2235,  2236,  2239,  2240,  2241,  2246,  2246,  2255,  2255,  2264,
    2265,  2268,  2269,  2270,  2276,  2277,  2278,  2279,  2280,  2281,
    2282,  2283,  2284,  2285,  2286,  2287,  2288,  2289,  2290,  2293,
    2293,  2302,  2302,  2311,  2311,  2320,  2320,  2329,  2329,  2338,
    2338,  2347,  2347,  2356,  2356,  2365,  2365,  2374,  2374,  2383,
    2383,  2397,  2397,  2408,  2411,  2411,  2425,  2425,  2436,  2437,
    2438,  2443,  2443,  2453,  2454,  2457,  2458,  2459,  2464,  2465,
    2466,  2467,  2468,  2469,  2470,  2471,  2472,  2473,  2474,  2475,
    2476,  2477,  2478,  2479,  2482,  2484,  2484,  2493,  2493,  2502,
    2510,  2518,  2518,  2530,  2530,  2542,  2543,  2546,  2547,  2548,
    2553,  2553,  2561,  2562,  2563,  2568,  2569,  2570,  2571,  2572,
    2573,  2574,  2575,  2576,  2577,  2578,  2579,  2582,  2582,  2591,
    2592,  2593,  2596,  2596,  2606,  2606,  2616,  2622,  2630,  2630,
    2643,  2644,  2645,  2650,  2651,  2652,  2653,  2654,  2655,  2656,
    2659,  2659,  2667,  2670,  2670,  2679,  2679,  2688,  2688,  2699,
    2700,  2703,  2704,  2705,  2710,  2710,  2718,  2719,  2720,  2725,
    2726,  2727,  2728,  2729,  2730,  2731,  2734,  2734,  2743,  2743,
    2754,  2754,  2767,  2768,  2769,  2774,  2775,  2776,  2777,  2778,
    2779,  2782,  2788,  2788,  2797,  2803,  2803,  2813,  2813,  2826,
    2826,  2836,  2837,  2838,  2843,  2844,  2845,  2846,  2847,  2848,
    2849,  2850,  2851,  2852,  2853,  2856,  2862,  2862,  2871,  2877,
    2877,  2886,  2892,  2898,  2898,  2907,  2908,  2911,  2911,  2922,
    2922,  2934,  2934,  2944,  2945,  2946,  2952,  2953,  2956,  2956,
    2967,  2975,  2975,  2988,  2989,  2990,  2996,  2996,  3004,  3005,
    3006,  3011,  3012,  3013,  3014,  3015,  3016,  3017,  3020,  3026,
    3026,  3035,  3035,  3046,  3047,  3048,  3053,  3053,  3061,  3062,
    3063,  3068,  3069,  3070,  3071,  3072,  3075,  3075,  3084,  3090,
    3096,  3102,  3102,  3111,  3111,  3122,  3123,  3124,  3129,  3130,
    3131,  3132,  3133,  3136,  3142,  3148,  3154
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
#line 6690 "dhcp4_parser.cc"

#line 3160 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
