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

  case 579: // $@81: %empty
#line 2047 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 580: // option_data_data: "data" $@81 ":" "constant string"
#line 2050 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 583: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2060 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 584: // option_data_always_send: "always-send" ":" "boolean"
#line 2066 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 585: // option_data_never_send: "never-send" ":" "boolean"
#line 2072 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3324 "dhcp4_parser.cc"
    break;

  case 586: // $@82: %empty
#line 2081 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3336 "dhcp4_parser.cc"
    break;

  case 587: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2087 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3345 "dhcp4_parser.cc"
    break;

  case 592: // not_empty_pools_list: not_empty_pools_list ","
#line 2100 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3353 "dhcp4_parser.cc"
    break;

  case 593: // $@83: %empty
#line 2105 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 594: // pool_list_entry: "{" $@83 pool_params "}"
#line 2109 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 595: // $@84: %empty
#line 2115 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3383 "dhcp4_parser.cc"
    break;

  case 596: // sub_pool4: "{" $@84 pool_params "}"
#line 2119 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3393 "dhcp4_parser.cc"
    break;

  case 599: // pool_params: pool_params ","
#line 2127 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3401 "dhcp4_parser.cc"
    break;

  case 608: // $@85: %empty
#line 2142 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3410 "dhcp4_parser.cc"
    break;

  case 609: // pool_entry: "pool" $@85 ":" "constant string"
#line 2145 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3420 "dhcp4_parser.cc"
    break;

  case 610: // pool_id: "pool-id" ":" "integer"
#line 2151 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3430 "dhcp4_parser.cc"
    break;

  case 611: // $@86: %empty
#line 2157 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3438 "dhcp4_parser.cc"
    break;

  case 612: // user_context: "user-context" $@86 ":" map_value
#line 2159 "dhcp4_parser.yy"
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
#line 3465 "dhcp4_parser.cc"
    break;

  case 613: // $@87: %empty
#line 2182 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 614: // comment: "comment" $@87 ":" "constant string"
#line 2184 "dhcp4_parser.yy"
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
#line 3502 "dhcp4_parser.cc"
    break;

  case 615: // $@88: %empty
#line 2212 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 616: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2218 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 621: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2229 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3531 "dhcp4_parser.cc"
    break;

  case 622: // $@89: %empty
#line 2234 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3541 "dhcp4_parser.cc"
    break;

  case 623: // reservation: "{" $@89 reservation_params "}"
#line 2238 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3550 "dhcp4_parser.cc"
    break;

  case 624: // $@90: %empty
#line 2243 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3560 "dhcp4_parser.cc"
    break;

  case 625: // sub_reservation: "{" $@90 reservation_params "}"
#line 2247 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3569 "dhcp4_parser.cc"
    break;

  case 630: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2258 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3577 "dhcp4_parser.cc"
    break;

  case 646: // $@91: %empty
#line 2281 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3586 "dhcp4_parser.cc"
    break;

  case 647: // next_server: "next-server" $@91 ":" "constant string"
#line 2284 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3596 "dhcp4_parser.cc"
    break;

  case 648: // $@92: %empty
#line 2290 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3605 "dhcp4_parser.cc"
    break;

  case 649: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2293 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3615 "dhcp4_parser.cc"
    break;

  case 650: // $@93: %empty
#line 2299 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 651: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2302 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3634 "dhcp4_parser.cc"
    break;

  case 652: // $@94: %empty
#line 2308 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 653: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2311 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 654: // $@95: %empty
#line 2317 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3662 "dhcp4_parser.cc"
    break;

  case 655: // duid: "duid" $@95 ":" "constant string"
#line 2320 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3672 "dhcp4_parser.cc"
    break;

  case 656: // $@96: %empty
#line 2326 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 657: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2329 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3691 "dhcp4_parser.cc"
    break;

  case 658: // $@97: %empty
#line 2335 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3700 "dhcp4_parser.cc"
    break;

  case 659: // client_id_value: "client-id" $@97 ":" "constant string"
#line 2338 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3710 "dhcp4_parser.cc"
    break;

  case 660: // $@98: %empty
#line 2344 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3719 "dhcp4_parser.cc"
    break;

  case 661: // circuit_id_value: "circuit-id" $@98 ":" "constant string"
#line 2347 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3729 "dhcp4_parser.cc"
    break;

  case 662: // $@99: %empty
#line 2353 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3738 "dhcp4_parser.cc"
    break;

  case 663: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2356 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3748 "dhcp4_parser.cc"
    break;

  case 664: // $@100: %empty
#line 2362 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3757 "dhcp4_parser.cc"
    break;

  case 665: // hostname: "hostname" $@100 ":" "constant string"
#line 2365 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3767 "dhcp4_parser.cc"
    break;

  case 666: // $@101: %empty
#line 2371 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3779 "dhcp4_parser.cc"
    break;

  case 667: // reservation_client_classes: "client-classes" $@101 ":" list_strings
#line 2377 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 668: // $@102: %empty
#line 2385 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 669: // relay: "relay" $@102 ":" "{" relay_map "}"
#line 2391 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 671: // $@103: %empty
#line 2399 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 672: // ip_addresses: "ip-addresses" $@103 ":" list_strings
#line 2405 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 673: // $@104: %empty
#line 2413 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 674: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2419 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3851 "dhcp4_parser.cc"
    break;

  case 677: // client_classes_list: client_classes_list ","
#line 2426 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3859 "dhcp4_parser.cc"
    break;

  case 678: // $@105: %empty
#line 2431 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3869 "dhcp4_parser.cc"
    break;

  case 679: // client_class_entry: "{" $@105 client_class_params "}"
#line 2435 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3879 "dhcp4_parser.cc"
    break;

  case 684: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2447 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3887 "dhcp4_parser.cc"
    break;

  case 702: // $@106: %empty
#line 2472 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 703: // client_class_test: "test" $@106 ":" "constant string"
#line 2475 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3906 "dhcp4_parser.cc"
    break;

  case 704: // $@107: %empty
#line 2481 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 705: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2484 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3925 "dhcp4_parser.cc"
    break;

  case 706: // only_if_required: "only-if-required" ":" "boolean"
#line 2490 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3935 "dhcp4_parser.cc"
    break;

  case 707: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2498 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3945 "dhcp4_parser.cc"
    break;

  case 708: // $@108: %empty
#line 2506 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 709: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2513 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 710: // $@109: %empty
#line 2518 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3980 "dhcp4_parser.cc"
    break;

  case 711: // control_sockets: "control-sockets" $@109 ":" "[" control_socket_list "]"
#line 2525 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 716: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2536 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 3997 "dhcp4_parser.cc"
    break;

  case 717: // $@110: %empty
#line 2541 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4007 "dhcp4_parser.cc"
    break;

  case 718: // control_socket_entry: "{" $@110 control_socket_params "}"
#line 2545 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4015 "dhcp4_parser.cc"
    break;

  case 721: // control_socket_params: control_socket_params ","
#line 2551 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4023 "dhcp4_parser.cc"
    break;

  case 734: // $@111: %empty
#line 2570 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 735: // control_socket_type: "socket-type" $@111 ":" control_socket_type_value
#line 2573 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 736: // control_socket_type_value: "unix"
#line 2579 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4047 "dhcp4_parser.cc"
    break;

  case 737: // control_socket_type_value: "http"
#line 2580 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4053 "dhcp4_parser.cc"
    break;

  case 738: // control_socket_type_value: "https"
#line 2581 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4059 "dhcp4_parser.cc"
    break;

  case 739: // $@112: %empty
#line 2584 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4069 "dhcp4_parser.cc"
    break;

  case 740: // control_socket_name: "socket-name" $@112 ":" "constant string"
#line 2588 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4079 "dhcp4_parser.cc"
    break;

  case 741: // $@113: %empty
#line 2594 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4089 "dhcp4_parser.cc"
    break;

  case 742: // control_socket_address: "socket-address" $@113 ":" "constant string"
#line 2598 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4099 "dhcp4_parser.cc"
    break;

  case 743: // control_socket_port: "socket-port" ":" "integer"
#line 2604 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4109 "dhcp4_parser.cc"
    break;

  case 744: // cert_required: "cert-required" ":" "boolean"
#line 2610 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4119 "dhcp4_parser.cc"
    break;

  case 745: // $@114: %empty
#line 2618 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 746: // authentication: "authentication" $@114 ":" "{" auth_params "}"
#line 2624 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4142 "dhcp4_parser.cc"
    break;

  case 749: // auth_params: auth_params ","
#line 2633 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4150 "dhcp4_parser.cc"
    break;

  case 757: // $@115: %empty
#line 2647 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4159 "dhcp4_parser.cc"
    break;

  case 758: // auth_type: "type" $@115 ":" auth_type_value
#line 2650 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 759: // auth_type_value: "basic"
#line 2655 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4174 "dhcp4_parser.cc"
    break;

  case 760: // $@116: %empty
#line 2658 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4183 "dhcp4_parser.cc"
    break;

  case 761: // realm: "realm" $@116 ":" "constant string"
#line 2661 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4193 "dhcp4_parser.cc"
    break;

  case 762: // $@117: %empty
#line 2667 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 763: // directory: "directory" $@117 ":" "constant string"
#line 2670 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 764: // $@118: %empty
#line 2676 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4224 "dhcp4_parser.cc"
    break;

  case 765: // clients: "clients" $@118 ":" "[" clients_list "]"
#line 2682 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4233 "dhcp4_parser.cc"
    break;

  case 770: // not_empty_clients_list: not_empty_clients_list ","
#line 2693 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4241 "dhcp4_parser.cc"
    break;

  case 771: // $@119: %empty
#line 2698 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4251 "dhcp4_parser.cc"
    break;

  case 772: // basic_auth: "{" $@119 clients_params "}"
#line 2702 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4259 "dhcp4_parser.cc"
    break;

  case 775: // clients_params: clients_params ","
#line 2708 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4267 "dhcp4_parser.cc"
    break;

  case 783: // $@120: %empty
#line 2722 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4276 "dhcp4_parser.cc"
    break;

  case 784: // user_file: "user-file" $@120 ":" "constant string"
#line 2725 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4286 "dhcp4_parser.cc"
    break;

  case 785: // $@121: %empty
#line 2731 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4295 "dhcp4_parser.cc"
    break;

  case 786: // password_file: "password-file" $@121 ":" "constant string"
#line 2734 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4305 "dhcp4_parser.cc"
    break;

  case 787: // $@122: %empty
#line 2742 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4317 "dhcp4_parser.cc"
    break;

  case 788: // dhcp_queue_control: "dhcp-queue-control" $@122 ":" "{" queue_control_params "}"
#line 2748 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4328 "dhcp4_parser.cc"
    break;

  case 791: // queue_control_params: queue_control_params ","
#line 2757 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4336 "dhcp4_parser.cc"
    break;

  case 798: // enable_queue: "enable-queue" ":" "boolean"
#line 2770 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4346 "dhcp4_parser.cc"
    break;

  case 799: // $@123: %empty
#line 2776 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4355 "dhcp4_parser.cc"
    break;

  case 800: // queue_type: "queue-type" $@123 ":" "constant string"
#line 2779 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4365 "dhcp4_parser.cc"
    break;

  case 801: // capacity: "capacity" ":" "integer"
#line 2785 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4375 "dhcp4_parser.cc"
    break;

  case 802: // $@124: %empty
#line 2791 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4384 "dhcp4_parser.cc"
    break;

  case 803: // arbitrary_map_entry: "constant string" $@124 ":" value
#line 2794 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4393 "dhcp4_parser.cc"
    break;

  case 804: // $@125: %empty
#line 2801 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4405 "dhcp4_parser.cc"
    break;

  case 805: // dhcp_ddns: "dhcp-ddns" $@125 ":" "{" dhcp_ddns_params "}"
#line 2807 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4416 "dhcp4_parser.cc"
    break;

  case 806: // $@126: %empty
#line 2814 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4426 "dhcp4_parser.cc"
    break;

  case 807: // sub_dhcp_ddns: "{" $@126 dhcp_ddns_params "}"
#line 2818 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 810: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2826 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4444 "dhcp4_parser.cc"
    break;

  case 822: // enable_updates: "enable-updates" ":" "boolean"
#line 2844 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4454 "dhcp4_parser.cc"
    break;

  case 823: // $@127: %empty
#line 2850 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 824: // server_ip: "server-ip" $@127 ":" "constant string"
#line 2853 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4473 "dhcp4_parser.cc"
    break;

  case 825: // server_port: "server-port" ":" "integer"
#line 2859 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 826: // $@128: %empty
#line 2865 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4492 "dhcp4_parser.cc"
    break;

  case 827: // sender_ip: "sender-ip" $@128 ":" "constant string"
#line 2868 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4502 "dhcp4_parser.cc"
    break;

  case 828: // sender_port: "sender-port" ":" "integer"
#line 2874 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4512 "dhcp4_parser.cc"
    break;

  case 829: // max_queue_size: "max-queue-size" ":" "integer"
#line 2880 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4522 "dhcp4_parser.cc"
    break;

  case 830: // $@129: %empty
#line 2886 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4531 "dhcp4_parser.cc"
    break;

  case 831: // ncr_protocol: "ncr-protocol" $@129 ":" ncr_protocol_value
#line 2889 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4540 "dhcp4_parser.cc"
    break;

  case 832: // ncr_protocol_value: "udp"
#line 2895 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4546 "dhcp4_parser.cc"
    break;

  case 833: // ncr_protocol_value: "tcp"
#line 2896 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4552 "dhcp4_parser.cc"
    break;

  case 834: // $@130: %empty
#line 2899 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 835: // ncr_format: "ncr-format" $@130 ":" "JSON"
#line 2902 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4571 "dhcp4_parser.cc"
    break;

  case 836: // $@131: %empty
#line 2910 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4583 "dhcp4_parser.cc"
    break;

  case 837: // config_control: "config-control" $@131 ":" "{" config_control_params "}"
#line 2916 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4593 "dhcp4_parser.cc"
    break;

  case 838: // $@132: %empty
#line 2922 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4603 "dhcp4_parser.cc"
    break;

  case 839: // sub_config_control: "{" $@132 config_control_params "}"
#line 2926 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4612 "dhcp4_parser.cc"
    break;

  case 842: // config_control_params: config_control_params ","
#line 2934 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4620 "dhcp4_parser.cc"
    break;

  case 845: // $@133: %empty
#line 2944 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4632 "dhcp4_parser.cc"
    break;

  case 846: // config_databases: "config-databases" $@133 ":" "[" database_list "]"
#line 2950 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4641 "dhcp4_parser.cc"
    break;

  case 847: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2955 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4651 "dhcp4_parser.cc"
    break;

  case 848: // $@134: %empty
#line 2963 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4663 "dhcp4_parser.cc"
    break;

  case 849: // loggers: "loggers" $@134 ":" "[" loggers_entries "]"
#line 2969 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4672 "dhcp4_parser.cc"
    break;

  case 852: // loggers_entries: loggers_entries ","
#line 2978 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4680 "dhcp4_parser.cc"
    break;

  case 853: // $@135: %empty
#line 2984 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4690 "dhcp4_parser.cc"
    break;

  case 854: // logger_entry: "{" $@135 logger_params "}"
#line 2988 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4698 "dhcp4_parser.cc"
    break;

  case 857: // logger_params: logger_params ","
#line 2994 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4706 "dhcp4_parser.cc"
    break;

  case 865: // debuglevel: "debuglevel" ":" "integer"
#line 3008 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4716 "dhcp4_parser.cc"
    break;

  case 866: // $@136: %empty
#line 3014 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4725 "dhcp4_parser.cc"
    break;

  case 867: // severity: "severity" $@136 ":" "constant string"
#line 3017 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4735 "dhcp4_parser.cc"
    break;

  case 868: // $@137: %empty
#line 3023 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4747 "dhcp4_parser.cc"
    break;

  case 869: // output_options_list: "output-options" $@137 ":" "[" output_options_list_content "]"
#line 3029 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4756 "dhcp4_parser.cc"
    break;

  case 872: // output_options_list_content: output_options_list_content ","
#line 3036 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4764 "dhcp4_parser.cc"
    break;

  case 873: // $@138: %empty
#line 3041 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4774 "dhcp4_parser.cc"
    break;

  case 874: // output_entry: "{" $@138 output_params_list "}"
#line 3045 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4782 "dhcp4_parser.cc"
    break;

  case 877: // output_params_list: output_params_list ","
#line 3051 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4790 "dhcp4_parser.cc"
    break;

  case 883: // $@139: %empty
#line 3063 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4799 "dhcp4_parser.cc"
    break;

  case 884: // output: "output" $@139 ":" "constant string"
#line 3066 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4809 "dhcp4_parser.cc"
    break;

  case 885: // flush: "flush" ":" "boolean"
#line 3072 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4819 "dhcp4_parser.cc"
    break;

  case 886: // maxsize: "maxsize" ":" "integer"
#line 3078 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4829 "dhcp4_parser.cc"
    break;

  case 887: // maxver: "maxver" ":" "integer"
#line 3084 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4839 "dhcp4_parser.cc"
    break;

  case 888: // $@140: %empty
#line 3090 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4848 "dhcp4_parser.cc"
    break;

  case 889: // pattern: "pattern" $@140 ":" "constant string"
#line 3093 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4858 "dhcp4_parser.cc"
    break;

  case 890: // $@141: %empty
#line 3099 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4870 "dhcp4_parser.cc"
    break;

  case 891: // compatibility: "compatibility" $@141 ":" "{" compatibility_params "}"
#line 3105 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4879 "dhcp4_parser.cc"
    break;

  case 894: // compatibility_params: compatibility_params ","
#line 3112 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4887 "dhcp4_parser.cc"
    break;

  case 900: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3124 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4897 "dhcp4_parser.cc"
    break;

  case 901: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3130 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4907 "dhcp4_parser.cc"
    break;

  case 902: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3136 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4917 "dhcp4_parser.cc"
    break;

  case 903: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3142 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4927 "dhcp4_parser.cc"
    break;


#line 4931 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1294;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     398, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,    41,    48,    81,    93,    97,   116,
     135,   142,   162,   169,   185,   195,   230,   244, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,    48,  -172,    50,   679,    95,   163,
     -16,   287,    -9,   341,    85,  -107,   268,   155, -1294,    86,
      99,   251,   250,   262, -1294,    44, -1294, -1294, -1294, -1294,
     263,   272,   288, -1294, -1294, -1294,   290,   313, -1294, -1294,
   -1294,   321,   333,   356,   372,   373,   374,   407,   427,   429,
     430,   432, -1294,   435,   436,   450,   456,   457, -1294, -1294,
   -1294,   463,   466,   469,   470, -1294, -1294, -1294,   472, -1294,
   -1294, -1294, -1294, -1294,   473,   476,   481, -1294, -1294, -1294,
   -1294, -1294,   483, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     488,   490,   491, -1294, -1294,   494, -1294,    98, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     502,   503,   504,   505, -1294,   200, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294,   507, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   210, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294,   509, -1294, -1294,
   -1294, -1294,   216, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     315,   293, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   381, -1294, -1294,   510, -1294, -1294,
   -1294,   512, -1294, -1294,   392,   336, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   514,
     515,   516, -1294, -1294, -1294, -1294,   517,   519, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294,   217, -1294, -1294, -1294,   522, -1294,   523, -1294,   524,
     526, -1294, -1294, -1294, -1294, -1294,   254, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294,   527,   256, -1294,
   -1294, -1294, -1294,    48,    48, -1294,   300,   530, -1294, -1294,
     531,   533,   534,   317,   323,   324,   535,   537,   541,   330,
     327,   543,   555,   558,   339,   342,   343,   344,   346,   357,
     340,   347,   350,   358,   361,   565,   362,   364,   375,   377,
     379,   567,   570,   583,   380,   397,   365,   399,   585,   589,
     596,   400,   617,   618,   622,   623,   624,   403,   404,   408,
     627,   628,   629,   631,   633,   415,   636,   637,   638,   640,
     641,   642,   643,   423,   424,   425,   644,   648, -1294,   679,
   -1294,   649,   650,   651,   431,   433,   434,   437,    95, -1294,
     656,   658,   659,   660,   661,   662,   443,   664,   665,   666,
     163, -1294,   667,   448,   -16, -1294,   671,   672,   674,   675,
     676,   678,   680,   681, -1294,   287, -1294,   682,   683,   459,
     684,   685,   692,   471, -1294,   341,   694,   474,   475,   477,
   -1294,    85,   695,   700,    70, -1294,   480,   703,   495,   716,
     497,   498,   719,   720,   268, -1294,   721,   506,   155, -1294,
   -1294, -1294,   722,   724,   725,   726,   727, -1294, -1294, -1294,
     513,   545,   546, -1294, -1294,   728,   732,   723, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   547,
   -1294, -1294, -1294, -1294, -1294,  -145,   550,   551, -1294, -1294,
   -1294, -1294,   737,   770,   771, -1294,   554,   319,   773,   772,
     557, -1294, -1294, -1294,   776,   777,   781,   782,   784, -1294,
     785,   788,   783,   789,   790,   566,   580, -1294, -1294, -1294,
     799,   798, -1294,   801,   285,   329, -1294, -1294, -1294, -1294,
   -1294,   584,   587,   588,   803,   590,   591, -1294,   801,   592,
     805, -1294,   593, -1294, -1294,   801,   594,   595,   597,   598,
     600,   601,   602, -1294,   603,   604, -1294,   605,   608,   609,
   -1294, -1294,   610, -1294, -1294, -1294, -1294,   613,   772, -1294,
   -1294,   614, -1294,   615, -1294, -1294,    19,   653, -1294,   835,
   -1294, -1294,    48,   679,   155,    95,   331, -1294, -1294, -1294,
     112,   112,   834, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294,   836,   837,   838, -1294, -1294, -1294, -1294, -1294,
   -1294,   839, -1294, -1294, -1294,   199,   840,   841,   842,   -10,
      63,   301,   843,   124,   268, -1294, -1294,   845,   -18, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     846, -1294, -1294, -1294, -1294,   715, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   834,
   -1294,   258,   282,   292, -1294, -1294,   302, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   852,   853,   854,   855,   856,   857,
     858,   859,   860,   861, -1294,   862,   863, -1294, -1294, -1294,
   -1294, -1294,   308, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294,   335, -1294,   870,   865,
   -1294, -1294,   871,   866, -1294, -1294,   872,   876, -1294, -1294,
     874,   878, -1294, -1294,   877,   879, -1294, -1294, -1294, -1294,
   -1294, -1294,    66, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
      73, -1294, -1294,   880,   882, -1294, -1294,   881,   885, -1294,
     886,   887,   888,   889,   890,   891,   345, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   892,   893,   894, -1294,   348, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   895, -1294,
     896, -1294, -1294, -1294, -1294, -1294, -1294,   349, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294,   883,   898, -1294,   899,
   -1294,   900, -1294, -1294, -1294,   363, -1294, -1294, -1294, -1294,
   -1294,   367, -1294,   118, -1294,   901,   902,   903,   904, -1294,
     376, -1294, -1294, -1294, -1294, -1294,   619, -1294,   905,   906,
   -1294, -1294,   907, -1294,   908, -1294, -1294, -1294,   909,   912,
     331, -1294,   913,   914,   915,   916,   686,   501,   688,   696,
     697,   699,   701,   702,   704,   705,   920,   706,   707,   923,
     926,   929,   930,   112, -1294, -1294,   112, -1294,   834,   163,
   -1294,   836,   341, -1294,   837,    85, -1294,   838,  1315, -1294,
     839,   199, -1294,   280,   840, -1294,   287, -1294,   841,  -107,
   -1294,   842,   711,   712,   713,   714,   717,   729,   -10, -1294,
     718,   733,   741,    63, -1294,   935,   936,   939,   749,   942,
     756,   301, -1294,   301, -1294,   843,   757,   943,   751,   945,
     124, -1294, -1294,   107,   845, -1294,   765,   767,   774,   779,
     -18, -1294, -1294,   944,  1004,   -16, -1294,   846,  1013, -1294,
   -1294,   807,   810, -1294,   813,   814,   818,   829, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,     7, -1294,
   -1294,   830,   832,   884,   897, -1294,   382, -1294,   384, -1294,
    1020, -1294,  1091, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     385, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294,  1017, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294,  1093,  1099, -1294,
   -1294, -1294, -1294, -1294, -1294,  1095, -1294,   388, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     209,   910,   911, -1294,  1097, -1294, -1294,   395, -1294, -1294,
     917, -1294,    48, -1294, -1294,  1101, -1294, -1294, -1294, -1294,
   -1294,   396, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294,   918,   405, -1294,   801, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294,  1315, -1294,  1102,  1105,   919,
   -1294,   280, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     174, -1294, -1294, -1294,  1106,   922,  1107,   107, -1294, -1294,
   -1294, -1294, -1294,   921,   924, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   406, -1294, -1294, -1294, -1294, -1294,
    1108, -1294,   925, -1294, -1294, -1294,  1110,  1111,  1112,  1113,
     174, -1294,  1114, -1294,   564,   927,   928,  1117, -1294, -1294,
     220, -1294, -1294, -1294, -1294, -1294,  1116,  -108,  1114, -1294,
   -1294,  1118,  1109, -1294, -1294,  1115,  1121,  1122, -1294,   409,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294,    17, -1294,  1116,
    1123,   931,   932,   934,  1124,  -108, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   422, -1294, -1294, -1294, -1294,   937,
   -1294, -1294, -1294,   938, -1294,  1125,  1126,    17, -1294, -1294,
   -1294,   940,   941, -1294, -1294, -1294
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   208,     9,   385,    11,   595,    13,
     624,    15,   513,    17,   522,    19,   561,    21,   347,    23,
     806,    25,   838,    27,    46,    39,     0,     0,     0,     0,
       0,   626,     0,   524,   563,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   836,   193,   226,
       0,     0,     0,   646,   648,   650,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   376,   511,   552,     0,   153,
     174,   456,   611,   613,     0,     0,     0,   309,   673,   615,
     338,   359,     0,   324,   708,   710,   787,   804,   181,   183,
       0,     0,     0,   848,   890,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     104,   134,   135,    93,    94,    95,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   101,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,    77,
      84,    85,    99,   100,   102,    96,    97,    98,    83,    88,
      89,    90,    91,    92,   103,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   440,   442,   444,   586,
     438,   446,     0,   450,   448,   668,   437,   390,   391,   392,
     393,   394,   417,   418,   419,   420,   421,   435,   407,   408,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   436,     0,   387,   397,   412,   413,   414,
     398,   400,   401,   403,   404,   405,   399,   395,   396,   415,
     416,   402,   409,   410,   411,   406,   608,     0,   607,   603,
     604,   602,     0,   597,   600,   601,   605,   606,   666,   652,
     654,   656,   660,   658,   664,   662,   645,   639,   643,   644,
       0,   627,   628,   640,   641,   642,   636,   631,   637,   633,
     634,   635,   638,   632,     0,   542,   283,     0,   546,   544,
     549,     0,   538,   539,     0,   525,   526,   529,   541,   530,
     531,   532,   548,   533,   534,   535,   536,   537,   579,     0,
       0,     0,   577,   578,   581,   582,     0,   564,   565,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   355,   357,
     352,     0,   349,   353,   354,     0,   823,     0,   826,     0,
       0,   830,   834,   821,   819,   820,     0,   808,   811,   812,
     813,   814,   815,   816,   817,   818,   845,     0,     0,   840,
     843,   844,    45,    50,     0,    37,    43,     0,    64,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    69,
      66,     0,     0,     0,     0,     0,     0,     0,   197,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     389,   386,     0,     0,   599,   596,     0,     0,     0,     0,
       0,     0,     0,     0,   625,   630,   514,     0,     0,     0,
       0,     0,     0,     0,   523,   528,     0,     0,     0,     0,
     562,   567,     0,     0,   351,   348,     0,     0,     0,     0,
       0,     0,     0,     0,   810,   807,     0,     0,   842,   839,
      49,    41,     0,     0,     0,     0,     0,   155,   156,   157,
       0,     0,     0,   191,   192,     0,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,     0,
     186,   187,   158,   159,   160,     0,     0,     0,   172,   173,
     180,   185,     0,     0,     0,   152,     0,     0,     0,     0,
       0,   452,   453,   454,     0,     0,     0,     0,     0,   707,
       0,     0,     0,     0,     0,     0,     0,   188,   189,   190,
       0,     0,    68,     0,     0,     0,   220,   221,   222,   223,
     196,     0,     0,     0,     0,     0,     0,   455,     0,     0,
       0,   388,     0,   610,   598,     0,     0,     0,     0,     0,
       0,     0,     0,   629,     0,     0,   540,     0,     0,     0,
     551,   527,     0,   583,   584,   585,   566,     0,     0,   350,
     822,     0,   825,     0,   828,   829,     0,     0,   809,     0,
     847,   841,     0,     0,     0,     0,     0,   647,   649,   651,
       0,     0,   241,   151,   163,   164,   165,   166,   167,   162,
     169,   171,   378,   515,   554,   154,   176,   177,   178,   179,
     175,   458,    38,   612,   614,     0,     0,   617,   340,     0,
       0,     0,   712,     0,     0,   182,   184,     0,     0,    51,
     211,   214,   215,   213,   218,   219,   217,   441,   443,   445,
     588,   439,   447,   451,   449,     0,   609,   667,   653,   655,
     657,   661,   659,   665,   663,   543,   284,   547,   545,   550,
     580,   356,   358,   824,   827,   832,   833,   831,   835,   241,
      42,     0,     0,     0,   233,   235,     0,   228,   231,   232,
     274,   276,   278,   280,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   294,     0,     0,   301,   303,   305,
     307,   273,     0,   248,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,     0,   246,     0,   242,
     243,   383,     0,   379,   380,   520,     0,   516,   517,   559,
       0,   555,   556,   463,     0,   459,   460,   319,   320,   321,
     322,   323,     0,   311,   314,   315,   316,   317,   318,   678,
       0,   675,   622,     0,   618,   619,   345,     0,   341,   342,
       0,     0,     0,     0,     0,     0,     0,   361,   364,   365,
     366,   367,   368,   369,     0,     0,     0,   334,     0,   326,
     329,   330,   331,   332,   333,   734,   739,   741,     0,   745,
       0,   733,   727,   728,   729,   731,   732,     0,   719,   722,
     723,   724,   725,   730,   726,   717,     0,   713,   714,     0,
     799,     0,   802,   795,   796,     0,   789,   792,   793,   794,
     797,     0,   853,     0,   850,     0,     0,     0,     0,   899,
       0,   892,   895,   896,   897,   898,    53,   593,     0,   589,
     590,   671,     0,   670,     0,    62,   837,   194,     0,     0,
     230,   227,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   225,   238,     0,   240,   245,     0,
     377,   382,   524,   512,   519,   563,   553,   558,     0,   457,
     462,   313,   310,   680,   677,   674,   626,   616,   621,     0,
     339,   344,     0,     0,     0,     0,     0,     0,   363,   360,
       0,     0,     0,   328,   325,     0,     0,     0,     0,     0,
       0,   721,   709,     0,   711,   716,     0,     0,     0,     0,
     791,   788,   805,     0,   852,   849,     0,     0,     0,     0,
     894,   891,    55,     0,    54,     0,   587,   592,     0,   669,
     846,     0,     0,   229,     0,     0,     0,     0,   282,   285,
     286,   287,   288,   289,   290,   291,   292,   293,     0,   299,
     300,     0,     0,     0,     0,   249,     0,   244,     0,   381,
       0,   518,     0,   557,   510,   485,   486,   487,   471,   472,
     490,   491,   492,   493,   494,   508,   474,   475,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   509,   468,   469,   470,   483,   484,   480,   481,   482,
       0,   465,   473,   488,   489,   476,   477,   478,   479,   461,
     312,   702,   704,     0,   696,   697,   698,   699,   700,   701,
     689,   690,   694,   695,   691,   692,   693,     0,   681,   682,
     685,   686,   687,   688,   676,     0,   620,     0,   343,   370,
     371,   372,   373,   374,   375,   362,   335,   336,   337,   327,
       0,     0,     0,   743,     0,   744,   720,     0,   715,   798,
       0,   801,     0,   790,   868,     0,   866,   864,   858,   862,
     863,     0,   855,   860,   861,   859,   851,   900,   901,   902,
     903,   893,    52,    57,     0,   591,     0,   234,   236,   275,
     277,   279,   281,   296,   297,   298,   295,   302,   304,   306,
     308,   247,   384,   521,   560,   467,   464,     0,     0,     0,
     679,   684,   623,   346,   736,   737,   738,   735,   740,   742,
       0,   718,   800,   803,     0,     0,     0,   857,   854,    56,
     594,   672,   466,     0,     0,   706,   683,   757,   760,   762,
     764,   756,   755,   754,     0,   747,   750,   751,   752,   753,
       0,   865,     0,   856,   703,   705,     0,     0,     0,     0,
     749,   746,     0,   867,     0,     0,     0,     0,   748,   873,
       0,   870,   759,   758,   761,   763,   766,     0,   872,   869,
     771,     0,   767,   768,   883,     0,     0,     0,   888,     0,
     875,   878,   879,   880,   881,   882,   871,     0,   765,   770,
       0,     0,     0,     0,     0,   877,   874,   783,   785,   782,
     776,   778,   780,   781,     0,   773,   777,   779,   769,     0,
     885,   886,   887,     0,   876,     0,     0,   775,   772,   884,
     889,     0,     0,   774,   784,   786
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294,   -59, -1294,  -573, -1294,   444,
   -1294, -1294, -1294, -1294, -1294, -1294,  -629, -1294, -1294, -1294,
     -67, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   428,   639,
     -38,    36,    38,   -54,   -51,   -39,   -37,   -21,   -20,   -19,
   -1294, -1294, -1294, -1294,    -8, -1294, -1294,    13,    53,    56,
      57,    58,    59, -1294, -1294,    60, -1294,    61, -1294,    64,
      71,    72, -1294, -1294,    74,    75, -1294,    76, -1294,    77,
   -1294, -1294, -1294, -1294, -1294,    40, -1294, -1294, -1294,   413,
     634, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
     156, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   354,
   -1294,   127, -1294,  -697,   134, -1294, -1294, -1293, -1294, -1291,
   -1294, -1294, -1294, -1294,     1, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
    -729, -1294,  -725, -1294,  -724, -1294, -1294, -1294, -1294, -1294,
   -1294,   128, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
      96, -1294, -1294, -1294, -1294, -1294, -1294, -1294,   121, -1294,
   -1294, -1294,   125,   611, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294,   129, -1294, -1294, -1294, -1294, -1294, -1294,  -995, -1294,
   -1294, -1294,   148, -1294, -1294, -1294,   153,   646, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294,  -992, -1294,    33, -1294,
      80, -1294,    78,    79,    82, -1294, -1294, -1294, -1294, -1294,
     149, -1294, -1294,   -87,   -62, -1294, -1294, -1294, -1294, -1294,
     157, -1294, -1294, -1294,   158, -1294,   630, -1294,   -63, -1294,
   -1294, -1294, -1294, -1294,   -61, -1294, -1294, -1294, -1294, -1294,
     -31, -1294, -1294, -1294,   159, -1294, -1294, -1294,   164, -1294,
     621, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294,   100, -1294, -1294, -1294,   103,   657, -1294,
   -1294, -1294,   -49, -1294,    -3, -1294,   -41, -1294, -1294, -1294,
     145, -1294, -1294, -1294,   154, -1294,   647,     9, -1294,    16,
   -1294,    20, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,  -985,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294,   150, -1294, -1294,
   -1294,   -78, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294,   130, -1294,   131,   136, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294,  -124, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294,  -160, -1294, -1294,  -187, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   132, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294,   447,   632, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294,   489,   645, -1294, -1294, -1294, -1294,
   -1294, -1294,   133, -1294, -1294,   -82, -1294, -1294, -1294, -1294,
   -1294, -1294,  -130, -1294, -1294,  -155, -1294, -1294, -1294, -1294,
   -1294, -1294, -1294, -1294, -1294, -1294,   137, -1294, -1294, -1294,
   -1294
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
     849,   850,  1006,   822,   823,   824,   982,   825,   983,   826,
     984,   827,   985,   828,   829,   538,   830,   831,   832,   833,
     834,   835,   836,   837,   838,   839,   996,  1246,   840,   841,
     842,   999,   843,  1000,   844,  1001,   845,  1002,   201,   480,
     872,   873,   874,   875,   876,   877,   878,   202,   486,   908,
     909,   910,   911,   912,   203,   483,   887,   888,   889,  1029,
      59,    75,   391,   392,   393,   552,   394,   553,   204,   484,
     896,   897,   898,   899,   900,   901,   902,   903,   205,   468,
     852,   853,   854,  1009,    47,    69,   284,   285,   286,   514,
     287,   510,   288,   511,   289,   512,   290,   515,   291,   518,
     292,   517,   206,   207,   208,   296,   209,   474,   864,   865,
     866,  1018,  1150,  1151,   210,   469,    53,    72,   856,   857,
     858,  1012,    55,    73,   354,   355,   356,   357,   358,   359,
     360,   537,   361,   541,   362,   540,   363,   364,   542,   365,
     211,   470,   860,   861,   862,  1015,    57,    74,   376,   377,
     378,   379,   380,   546,   381,   382,   383,   384,   385,   298,
     513,   968,   969,   970,  1075,    49,    70,   312,   313,   314,
     522,   315,   212,   475,   213,   476,   214,   482,   883,   884,
     885,  1026,    51,    71,   330,   331,   332,   215,   436,   216,
     437,   217,   438,   336,   527,   337,   528,   338,   529,   339,
     531,   340,   530,   341,   533,   342,   532,   343,   526,   305,
     519,   972,   973,  1078,   218,   481,   880,   881,  1023,  1177,
    1178,  1179,  1180,  1181,  1257,  1182,  1258,  1183,   219,   220,
     487,   221,   488,   936,   937,   938,  1053,   927,   928,   929,
    1045,  1267,   930,  1046,   931,  1047,   932,   933,   934,  1049,
    1294,  1295,  1296,  1306,  1323,  1297,  1307,  1298,  1308,  1299,
    1309,  1331,  1332,  1333,  1347,  1364,  1365,  1366,  1375,  1367,
    1376,   222,   489,   945,   946,   947,   948,  1057,   949,   950,
    1059,   223,   490,    61,    76,   406,   407,   408,   409,   557,
     410,   411,   559,   412,   413,   414,   562,   787,   415,   563,
     224,   430,    63,    77,   418,   419,   420,   566,   421,   225,
     496,   953,   954,  1063,  1221,  1222,  1223,  1224,  1276,  1225,
    1274,  1320,  1321,  1327,  1339,  1340,  1341,  1350,  1342,  1343,
    1344,  1345,  1354,   226,   497,   960,   961,   962,   963,   964,
     965
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   256,   308,   326,    78,   352,   372,   390,   403,
     344,   374,   922,   375,   846,   260,   923,   924,   261,   244,
     299,   316,   328,  1143,   366,   386,  1144,   404,   301,   763,
     262,   257,   263,  1158,   388,   389,   767,   785,   297,   311,
     327,    28,   714,   715,   716,   717,   732,   428,   264,   265,
     266,    81,   429,    29,  1360,    30,  1361,    31,   801,   802,
      84,   267,  1243,  1244,  1245,   245,   300,   317,   329,  1021,
     367,   387,  1022,   405,   353,   373,  1024,   127,   302,  1025,
     333,   718,   268,   126,  1360,   303,  1361,   334,    40,   304,
    1334,   335,   422,  1335,  1336,  1337,  1338,   306,   132,   133,
      42,   499,   423,   309,    44,   258,   500,   259,   253,   283,
     227,   228,   254,   307,   229,   732,   155,   230,   231,   232,
     233,  1064,   269,    46,  1065,   270,   271,   272,   273,   274,
     275,   132,   133,   276,   890,   891,   892,   893,   894,   895,
     277,   278,    48,   279,   280,   281,   282,   293,   294,    50,
     310,   295,   800,   801,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   416,   417,    52,
     815,   816,   817,   818,   819,   820,    54,   132,   133,   346,
     368,   347,   348,   369,   370,   371,  1357,  1358,   955,   956,
     957,   958,    56,    91,    92,    93,    94,    95,    96,   132,
     133,   346,    58,   508,   786,   155,   346,   155,   509,   132,
     133,   388,   389,   520,  1287,   904,   905,   906,   521,   524,
     554,   132,   133,  1328,   525,   555,  1329,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    60,   132,   133,
     155,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    62,   246,   247,   248,   424,   127,   564,   425,   568,
    1143,   499,   565,  1144,   569,   426,   975,   433,   129,   130,
    1158,    32,    33,    34,    35,   249,   434,   132,   133,   250,
     251,   252,   134,   135,   136,   568,   155,   253,   132,   133,
     976,   254,   435,   139,   439,   508,   535,   939,   940,   941,
     977,   255,   751,   752,  1214,   980,  1215,  1216,   155,  1106,
     981,  1003,    93,    94,    95,    96,  1004,   440,   155,    93,
      94,    95,   922,   534,   922,   444,   923,   924,   923,   924,
     155,   867,   868,   869,   870,   155,   871,   445,  1003,   545,
    1288,  1289,  1290,  1005,   101,   102,   103,   942,  1038,   754,
     755,  1043,  1051,  1039,   148,   149,  1044,  1052,   794,   795,
     446,   817,   818,   819,   570,   571,  1060,  1264,  1265,  1266,
     564,  1061,   126,   127,   346,  1062,   447,   448,   449,  1070,
     127,   345,   132,   133,  1071,  1003,   155,   520,  1255,   536,
    1251,   554,  1252,  1256,   132,   133,  1263,   155,  1051,  1277,
     544,   132,   133,  1271,  1278,  1161,  1162,  1163,   524,  1310,
     318,   450,  1355,  1280,  1311,   132,   133,  1356,   319,   320,
     321,   322,   323,   324,   325,  1377,   726,   727,   728,   729,
    1378,   451,   156,   452,   453,   346,   454,   347,   348,   456,
     457,   234,   349,   350,   351,   395,   396,   397,   398,   399,
     400,   401,   402,   256,   458,   132,   133,   308,   915,   244,
     459,   460,   916,   917,   918,   919,   260,   464,   326,   261,
     465,   299,   920,   466,   467,   316,   471,   477,   352,   301,
     478,   262,   257,   263,   372,   479,   328,   485,   374,   297,
     375,   155,   493,   311,   494,   495,   366,   403,   498,   264,
     265,   266,   386,   155,   327,   245,   504,   505,   506,   507,
     155,   516,   267,   523,   539,   404,   543,   300,   547,   548,
     549,   317,   551,   572,   155,   550,   556,   558,   560,   302,
     561,   567,   329,   268,   573,   574,   303,   575,   576,   580,
     304,   581,   367,   577,   333,   582,   353,   585,   387,   578,
     579,   334,   373,   584,   583,   335,   258,   309,   259,   586,
     283,   405,   587,   588,   155,   594,   589,   590,   591,   599,
     592,   605,   595,   269,   606,   596,   270,   271,   272,   273,
     274,   275,   597,   593,   276,   598,   600,   607,   601,   612,
     610,   277,   278,   613,   279,   280,   281,   282,   293,   294,
     614,   602,   295,   603,   310,   604,   608,  1281,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   616,   617,   609,   615,   611,   618,   619,   620,   621,
     622,   624,   625,   626,   623,   627,   156,   628,   234,   629,
     630,   631,   632,   790,   633,   634,   635,   636,   640,   637,
     638,   639,   641,   643,   644,   645,   244,   646,   648,   647,
     651,   649,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   662,   663,   907,   921,   665,   666,   403,   667,   668,
     669,   959,   670,   676,   671,   672,   674,   675,   677,   678,
      87,   913,   925,    88,   943,   404,   679,   680,   682,   687,
     683,   684,   245,   685,   688,    89,   690,   691,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   692,
     693,   694,   695,   696,   697,   699,   702,  1089,   712,  1322,
     700,   703,   704,   705,   706,   710,   707,   914,   926,   711,
     944,   405,   722,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   708,   709,
     713,   126,   127,   720,   721,   723,   724,   725,   731,    30,
     734,   735,   736,   128,   129,   130,   737,   738,   742,   745,
     131,   739,   740,   132,   133,   741,   743,   744,   134,   135,
     136,   137,   138,   746,   747,   748,   749,   757,   760,   139,
     758,   759,   765,   761,   762,   764,   766,   768,   769,   140,
     770,   771,   141,   772,   773,   774,   775,   776,   777,   142,
     143,   778,   779,   780,   144,   145,   781,   783,   784,   788,
     789,   847,  1072,   851,   855,   859,   863,   879,   882,   886,
     935,   146,   952,   967,   971,   147,   986,   987,   988,   989,
     990,   991,   992,   993,   994,   995,   997,   998,  1008,  1011,
     148,   149,   150,   151,   152,   153,  1007,  1010,  1013,  1014,
    1016,  1017,  1020,  1019,   154,  1028,  1027,  1030,  1031,  1054,
    1032,  1033,  1034,  1035,  1036,  1037,  1040,  1041,  1042,  1048,
    1050,  1055,   155,  1056,  1058,  1066,  1067,  1068,  1069,  1077,
    1088,  1076,  1090,  1081,  1080,  1079,  1082,  1084,  1085,  1086,
    1087,  1092,  1091,  1093,  1098,  1094,  1095,  1101,  1096,  1097,
    1102,  1100,  1099,  1103,  1104,  1189,  1190,  1191,  1192,  1200,
    1201,  1193,   256,  1202,  1196,   352,  1204,  1210,   372,  1212,
    1232,  1114,   374,  1194,   375,   260,  1164,  1197,   261,   326,
     299,  1170,   390,   366,  1118,  1198,   386,  1119,   301,  1153,
     262,   257,   263,  1203,  1172,  1211,   907,   328,   297,  1120,
    1115,  1121,  1205,  1209,   921,  1165,   921,  1152,   264,   265,
     266,  1227,  1171,  1228,   913,   327,  1217,  1122,  1123,  1124,
    1229,   267,   925,   959,   925,  1230,   300,  1233,   308,   367,
    1125,   943,   387,   353,  1219,  1154,   373,  1236,   302,  1142,
    1173,  1259,   268,   329,  1169,   303,   316,  1155,  1253,   304,
    1237,  1126,  1174,  1238,  1156,   333,  1239,  1240,  1157,  1175,
     914,  1241,   334,  1176,   311,   258,   335,   259,   926,   283,
     926,  1145,  1242,  1247,  1116,  1248,  1117,   944,  1141,  1166,
    1220,  1167,   269,  1168,  1218,   270,   271,   272,   273,   274,
     275,  1127,   317,   276,  1128,  1129,  1130,  1131,  1132,  1133,
     277,   278,  1134,   279,   280,   281,   282,   293,   294,  1135,
    1136,   295,  1137,  1138,  1139,  1140,  1147,  1148,  1146,  1254,
    1149,  1260,  1261,  1262,  1270,  1275,  1283,  1249,   309,  1284,
    1300,  1302,  1349,  1312,  1314,  1315,  1316,  1317,   793,  1351,
    1250,  1319,  1326,  1330,  1348,  1352,  1353,  1369,  1373,  1381,
    1382,   791,   782,  1268,  1269,  1107,  1083,  1105,   642,  1199,
    1272,  1279,   650,   974,  1304,  1285,  1301,  1305,  1313,  1160,
    1324,  1325,  1188,  1273,  1187,   310,  1371,  1370,  1372,  1109,
    1379,  1380,  1108,  1384,  1385,   689,   661,  1195,  1282,  1159,
    1110,  1111,   686,  1186,  1184,   681,  1113,  1235,  1234,  1112,
    1185,   664,   673,  1286,  1207,  1208,  1318,  1206,  1114,  1368,
    1383,   951,  1213,   792,  1164,  1303,   698,  1226,  1346,  1170,
    1374,  1118,     0,  1291,  1119,     0,  1153,  1231,     0,     0,
    1217,     0,  1172,   701,     0,     0,  1120,  1115,  1121,     0,
       0,  1292,     0,  1165,  1152,     0,     0,     0,  1219,     0,
    1171,     0,     0,     0,  1122,  1123,  1124,     0,     0,     0,
       0,     0,     0,  1291,     0,     0,     0,  1125,     0,     0,
       0,     0,  1154,     0,     0,     0,  1142,     0,  1173,     0,
       0,  1292,  1169,     0,  1155,     0,     0,  1293,  1126,     0,
    1174,  1156,     0,     0,  1220,  1157,     0,  1175,  1218,     0,
    1359,  1176,     0,     0,     0,     0,     0,     0,  1145,     0,
       0,  1116,     0,  1117,     0,  1141,     0,  1166,  1362,  1167,
       0,  1168,     0,     0,     0,     0,     0,  1293,  1127,     0,
    1359,  1128,  1129,  1130,  1131,  1132,  1133,     0,     0,  1134,
       0,     0,     0,     0,     0,     0,  1135,  1136,  1362,  1137,
    1138,  1139,  1140,  1147,  1148,  1146,     0,  1149,     0,     0,
       0,     0,     0,     0,  1363,    91,    92,    93,    94,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1363,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,   127,   346,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,     0,     0,     0,     0,     0,     0,     0,   132,
     133,     0,   251,     0,   134,   135,   136,     0,     0,   253,
       0,     0,     0,   254,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   255,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   741,    74,   711,    69,   741,   741,    69,    68,
      69,    70,    71,  1018,    73,    74,  1018,    76,    69,   658,
      69,    69,    69,  1018,   141,   142,   665,    18,    69,    70,
      71,     0,   187,   188,   189,   190,   619,     3,    69,    69,
      69,   223,     8,     5,  1347,     7,  1347,     9,    41,    42,
      10,    69,    55,    56,    57,    68,    69,    70,    71,     3,
      73,    74,     6,    76,    73,    74,     3,    93,    69,     6,
      71,   226,    69,    92,  1377,    69,  1377,    71,     7,    69,
     198,    71,     6,   201,   202,   203,   204,   113,   114,   115,
       7,     3,     3,    70,     7,    69,     8,    69,   124,    69,
      15,    16,   128,   129,    19,   688,   223,    22,    23,    24,
      25,     3,    69,     7,     6,    69,    69,    69,    69,    69,
      69,   114,   115,    69,   144,   145,   146,   147,   148,   149,
      69,    69,     7,    69,    69,    69,    69,    69,    69,     7,
      70,    69,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    12,    13,     7,
      58,    59,    60,    61,    62,    63,     7,   114,   115,    94,
      95,    96,    97,    98,    99,   100,   169,   170,   206,   207,
     208,   209,     7,    30,    31,    32,    33,    34,    35,   114,
     115,    94,     7,     3,   185,   223,    94,   223,     8,   114,
     115,   141,   142,     3,    40,   152,   153,   154,     8,     3,
       3,   114,   115,     3,     8,     8,     6,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,     7,   114,   115,
     223,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     7,    89,    90,    91,     4,    93,     3,     8,     3,
    1255,     3,     8,  1255,     8,     3,     8,     4,   105,   106,
    1255,   223,   224,   225,   226,   112,     4,   114,   115,   116,
     117,   118,   119,   120,   121,     3,   223,   124,   114,   115,
       8,   128,     4,   130,     4,     3,     3,   173,   174,   175,
       8,   138,    17,    18,   197,     3,   199,   200,   223,  1006,
       8,     3,    32,    33,    34,    35,     8,     4,   223,    32,
      33,    34,  1051,     8,  1053,     4,  1051,  1051,  1053,  1053,
     223,   132,   133,   134,   135,   223,   137,     4,     3,     3,
     166,   167,   168,     8,    64,    65,    66,   223,     3,    20,
      21,     3,     3,     8,   191,   192,     8,     8,    27,    28,
       4,    60,    61,    62,   423,   424,     3,   158,   159,   160,
       3,     8,    92,    93,    94,     8,     4,     4,     4,     3,
      93,    40,   114,   115,     8,     3,   223,     3,     3,     8,
       8,     3,     8,     8,   114,   115,     8,   223,     3,     3,
       8,   114,   115,     8,     8,   125,   126,   127,     3,     3,
     123,     4,     3,     8,     8,   114,   115,     8,   131,   132,
     133,   134,   135,   136,   137,     3,   107,   108,   109,   110,
       8,     4,   499,     4,     4,    94,     4,    96,    97,     4,
       4,   508,   101,   102,   103,   177,   178,   179,   180,   181,
     182,   183,   184,   520,     4,   114,   115,   524,   157,   508,
       4,     4,   161,   162,   163,   164,   520,     4,   535,   520,
       4,   520,   171,     4,     4,   524,     4,     4,   545,   520,
       4,   520,   520,   520,   551,     4,   535,     4,   551,   520,
     551,   223,     4,   524,     4,     4,   545,   564,     4,   520,
     520,   520,   551,   223,   535,   508,     4,     4,     4,     4,
     223,     4,   520,     4,     4,   564,     4,   520,     4,     4,
       4,   524,     3,   223,   223,     8,     4,     4,     4,   520,
       4,     4,   535,   520,     4,     4,   520,     4,     4,     4,
     520,     4,   545,   226,   535,     4,   545,     4,   551,   226,
     226,   535,   551,   226,   224,   535,   520,   524,   520,     4,
     520,   564,     4,   224,   223,   225,   224,   224,   224,     4,
     224,     4,   225,   520,     4,   225,   520,   520,   520,   520,
     520,   520,   224,   226,   520,   224,   224,     4,   224,     4,
     225,   520,   520,     4,   520,   520,   520,   520,   520,   520,
       4,   226,   520,   226,   524,   226,   226,  1236,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,     4,     4,   226,   224,   226,     4,     4,     4,   226,
     226,     4,     4,     4,   226,     4,   703,     4,   705,   224,
       4,     4,     4,   702,     4,     4,     4,     4,     4,   226,
     226,   226,     4,     4,     4,     4,   705,   226,   224,   226,
       4,   224,     4,     4,     4,     4,     4,   224,     4,     4,
       4,     4,   224,   740,   741,     4,     4,   744,     4,     4,
       4,   748,     4,   224,     4,     4,     4,     4,     4,     4,
      11,   740,   741,    14,   743,   744,     4,   226,     4,     4,
     226,   226,   705,   226,     4,    26,   226,     4,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,   224,
       4,   224,   224,     4,     4,     4,     4,   226,     5,   165,
     224,     7,     7,     7,     7,     7,   223,   740,   741,     7,
     743,   744,     5,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,   223,   223,
     223,    92,    93,   223,   223,     5,     5,   223,     5,     7,
     223,     5,     5,   104,   105,   106,     5,     5,     5,   223,
     111,     7,     7,   114,   115,     7,     7,     7,   119,   120,
     121,   122,   123,   223,     5,     7,     5,   223,     5,   130,
     223,   223,     7,   223,   223,   223,   223,   223,   223,   140,
     223,   223,   143,   223,   223,   223,   223,   223,   223,   150,
     151,   223,   223,   223,   155,   156,   223,   223,   223,   186,
       5,     7,   223,     7,     7,     7,     7,     7,     7,     7,
       7,   172,     7,     7,   139,   176,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
     191,   192,   193,   194,   195,   196,     6,     6,     6,     3,
       6,     3,     3,     6,   205,     3,     6,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   223,     4,     4,     4,     4,     4,     4,     3,
     224,     6,   224,     4,     6,     8,     4,     4,     4,     4,
       4,   224,   226,   224,     4,   224,   224,     4,   224,   224,
       4,   224,   226,     4,     4,   224,   224,   224,   224,     4,
       4,   224,  1009,     4,   226,  1012,     4,     4,  1015,     4,
       6,  1018,  1015,   224,  1015,  1009,  1023,   224,  1009,  1026,
    1009,  1023,  1029,  1012,  1018,   224,  1015,  1018,  1009,  1018,
    1009,  1009,  1009,   224,  1023,   224,  1043,  1026,  1009,  1018,
    1018,  1018,   226,   226,  1051,  1023,  1053,  1018,  1009,  1009,
    1009,   226,  1023,   226,  1043,  1026,  1063,  1018,  1018,  1018,
     226,  1009,  1051,  1070,  1053,   226,  1009,     3,  1075,  1012,
    1018,  1060,  1015,  1012,  1063,  1018,  1015,     4,  1009,  1018,
    1023,     4,  1009,  1026,  1023,  1009,  1075,  1018,     8,  1009,
     223,  1018,  1023,   223,  1018,  1026,   223,   223,  1018,  1023,
    1043,   223,  1026,  1023,  1075,  1009,  1026,  1009,  1051,  1009,
    1053,  1018,   223,   223,  1018,   223,  1018,  1060,  1018,  1023,
    1063,  1023,  1009,  1023,  1063,  1009,  1009,  1009,  1009,  1009,
    1009,  1018,  1075,  1009,  1018,  1018,  1018,  1018,  1018,  1018,
    1009,  1009,  1018,  1009,  1009,  1009,  1009,  1009,  1009,  1018,
    1018,  1009,  1018,  1018,  1018,  1018,  1018,  1018,  1018,     8,
    1018,     8,     3,     8,     7,     4,     4,   223,  1075,     4,
       4,     4,     3,     5,     4,     4,     4,     4,   705,     4,
     223,     7,     5,     7,     6,     4,     4,     4,     4,     4,
       4,   703,   688,   223,   223,  1008,   980,  1003,   499,  1043,
     223,   223,   508,   789,   223,   226,   224,   223,   223,  1021,
     223,   223,  1031,  1212,  1029,  1075,   224,   226,   224,  1011,
     223,   223,  1009,   223,   223,   554,   520,  1038,  1255,  1020,
    1012,  1014,   551,  1028,  1024,   545,  1017,  1077,  1075,  1015,
    1026,   524,   535,  1261,  1053,  1055,  1310,  1051,  1255,  1349,
    1377,   744,  1060,   704,  1261,  1277,   564,  1064,  1328,  1261,
    1355,  1255,    -1,  1270,  1255,    -1,  1255,  1070,    -1,    -1,
    1277,    -1,  1261,   568,    -1,    -1,  1255,  1255,  1255,    -1,
      -1,  1270,    -1,  1261,  1255,    -1,    -1,    -1,  1277,    -1,
    1261,    -1,    -1,    -1,  1255,  1255,  1255,    -1,    -1,    -1,
      -1,    -1,    -1,  1310,    -1,    -1,    -1,  1255,    -1,    -1,
      -1,    -1,  1255,    -1,    -1,    -1,  1255,    -1,  1261,    -1,
      -1,  1310,  1261,    -1,  1255,    -1,    -1,  1270,  1255,    -1,
    1261,  1255,    -1,    -1,  1277,  1255,    -1,  1261,  1277,    -1,
    1347,  1261,    -1,    -1,    -1,    -1,    -1,    -1,  1255,    -1,
      -1,  1255,    -1,  1255,    -1,  1255,    -1,  1261,  1347,  1261,
      -1,  1261,    -1,    -1,    -1,    -1,    -1,  1310,  1255,    -1,
    1377,  1255,  1255,  1255,  1255,  1255,  1255,    -1,    -1,  1255,
      -1,    -1,    -1,    -1,    -1,    -1,  1255,  1255,  1377,  1255,
    1255,  1255,  1255,  1255,  1255,  1255,    -1,  1255,    -1,    -1,
      -1,    -1,    -1,    -1,  1347,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1377,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,    93,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
     115,    -1,   117,    -1,   119,   120,   121,    -1,    -1,   124,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   191,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   223
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,     0,     5,
       7,     9,   223,   224,   225,   226,   242,   243,   244,   249,
       7,   258,     7,   263,     7,   318,     7,   431,     7,   512,
       7,   529,     7,   463,     7,   469,     7,   493,     7,   407,
       7,   630,     7,   649,   250,   245,   259,   264,   319,   432,
     513,   530,   464,   470,   494,   408,   631,   650,   242,   251,
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
     461,   487,   519,   521,   523,   534,   536,   538,   561,   575,
     576,   578,   618,   628,   647,   656,   680,    15,    16,    19,
      22,    23,    24,    25,   257,   316,   317,   320,   322,   325,
     328,   329,   330,   331,   519,   521,    89,    90,    91,   112,
     116,   117,   118,   124,   128,   138,   257,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   281,   284,   285,
     286,   287,   288,   289,   292,   294,   296,   297,   298,   301,
     302,   304,   306,   312,   433,   434,   435,   437,   439,   441,
     443,   445,   447,   449,   450,   451,   452,   487,   506,   519,
     521,   523,   534,   536,   538,   556,   113,   129,   257,   445,
     447,   487,   514,   515,   516,   518,   519,   521,   123,   131,
     132,   133,   134,   135,   136,   137,   257,   487,   519,   521,
     531,   532,   533,   534,   536,   538,   540,   542,   544,   546,
     548,   550,   552,   554,   461,    40,    94,    96,    97,   101,
     102,   103,   257,   361,   471,   472,   473,   474,   475,   476,
     477,   479,   481,   483,   484,   486,   519,   521,    95,    98,
      99,   100,   257,   361,   475,   481,   495,   496,   497,   498,
     499,   501,   502,   503,   504,   505,   519,   521,   141,   142,
     257,   409,   410,   411,   413,   177,   178,   179,   180,   181,
     182,   183,   184,   257,   519,   521,   632,   633,   634,   635,
     637,   638,   640,   641,   642,   645,    12,    13,   651,   652,
     653,   655,     6,     3,     4,     8,     3,   261,     3,     8,
     648,   315,   335,     4,     4,     4,   535,   537,   539,     4,
       4,   333,   343,   345,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   279,     4,     4,     4,     4,
       4,   290,   293,   295,     4,     4,     4,     4,   426,   462,
     488,     4,   282,   299,   454,   520,   522,     4,     4,     4,
     386,   562,   524,   402,   416,     4,   395,   577,   579,   619,
     629,   303,   305,     4,     4,     4,   657,   681,     4,     3,
       8,   321,   323,   326,     4,     4,     4,     4,     3,     8,
     438,   440,   442,   507,   436,   444,     4,   448,   446,   557,
       3,     8,   517,     4,     3,     8,   555,   541,   543,   545,
     549,   547,   553,   551,     8,     3,     8,   478,   362,     4,
     482,   480,   485,     4,     8,     3,   500,     4,     4,     4,
       8,     3,   412,   414,     3,     8,     4,   636,     4,   639,
       4,     4,   643,   646,     3,     8,   654,     4,     3,     8,
     242,   242,   223,     4,     4,     4,     4,   226,   226,   226,
       4,     4,     4,   224,   226,     4,     4,     4,   224,   224,
     224,   224,   224,   226,   225,   225,   225,   224,   224,     4,
     224,   224,   226,   226,   226,     4,     4,     4,   226,   226,
     225,   226,     4,     4,     4,   224,     4,     4,     4,     4,
       4,   226,   226,   226,     4,     4,     4,     4,     4,   224,
       4,     4,     4,     4,     4,     4,     4,   226,   226,   226,
       4,     4,   266,     4,     4,     4,   226,   226,   224,   224,
     317,     4,     4,     4,     4,     4,     4,   224,     4,     4,
       4,   434,     4,   224,   515,     4,     4,     4,     4,     4,
       4,     4,     4,   533,     4,     4,   224,     4,     4,     4,
     226,   473,     4,   226,   226,   226,   497,     4,     4,   410,
     226,     4,   224,     4,   224,   224,     4,     4,   633,     4,
     224,   652,     4,     7,     7,     7,     7,   223,   223,   223,
       7,     7,     5,   223,   187,   188,   189,   190,   226,   291,
     223,   223,     5,     5,     5,   223,   107,   108,   109,   110,
     300,     5,   244,   246,   223,     5,     5,     5,     5,     7,
       7,     7,     5,     7,     7,   223,   223,     5,     7,     5,
     253,    17,    18,   324,    20,    21,   327,   223,   223,   223,
       5,   223,   223,   253,   223,     7,   223,   253,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   246,   223,   223,    18,   185,   644,   186,     5,
     242,   265,   651,   316,    27,    28,   336,   337,   338,   340,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    58,    59,    60,    61,    62,
      63,   257,   350,   351,   352,   354,   356,   358,   360,   361,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     375,   376,   377,   379,   381,   383,   350,     7,   346,   347,
     348,     7,   427,   428,   429,     7,   465,   466,   467,     7,
     489,   490,   491,     7,   455,   456,   457,   132,   133,   134,
     135,   137,   387,   388,   389,   390,   391,   392,   393,     7,
     563,   564,     7,   525,   526,   527,     7,   403,   404,   405,
     144,   145,   146,   147,   148,   149,   417,   418,   419,   420,
     421,   422,   423,   424,   152,   153,   154,   257,   396,   397,
     398,   399,   400,   519,   521,   157,   161,   162,   163,   164,
     171,   257,   377,   379,   381,   519,   521,   584,   585,   586,
     589,   591,   593,   594,   595,     7,   580,   581,   582,   173,
     174,   175,   223,   519,   521,   620,   621,   622,   623,   625,
     626,   632,     7,   658,   659,   206,   207,   208,   209,   257,
     682,   683,   684,   685,   686,   687,   254,     7,   508,   509,
     510,   139,   558,   559,   346,     8,     8,     8,   339,   341,
       3,     8,   353,   355,   357,   359,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   373,     4,     4,   378,
     380,   382,   384,     3,     8,     8,   349,     6,     3,   430,
       6,     3,   468,     6,     3,   492,     6,     3,   458,     6,
       3,     3,     6,   565,     3,     6,   528,     6,     3,   406,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   587,   590,   592,     4,   596,
       4,     3,     8,   583,     6,     3,     4,   624,     4,   627,
       3,     8,     8,   660,     3,     6,     4,     4,     4,     4,
       3,     8,   223,   255,   256,   511,     6,     3,   560,     8,
       6,     4,     4,   337,     4,     4,     4,     4,   224,   226,
     224,   226,   224,   224,   224,   224,   224,   224,     4,   226,
     224,     4,     4,     4,     4,   351,   350,   348,   433,   429,
     471,   467,   495,   491,   257,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   281,   284,   285,   286,   287,
     288,   289,   292,   294,   296,   297,   298,   301,   302,   304,
     306,   312,   361,   425,   443,   445,   447,   449,   450,   451,
     459,   460,   487,   519,   521,   534,   536,   538,   556,   457,
     388,   125,   126,   127,   257,   267,   268,   269,   312,   361,
     461,   487,   519,   521,   534,   536,   538,   566,   567,   568,
     569,   570,   572,   574,   564,   531,   527,   409,   405,   224,
     224,   224,   224,   224,   224,   418,   226,   224,   224,   397,
       4,     4,     4,   224,     4,   226,   585,   584,   582,   226,
       4,   224,     4,   621,   197,   199,   200,   257,   361,   519,
     521,   661,   662,   663,   664,   666,   659,   226,   226,   226,
     226,   683,     6,     3,   514,   510,     4,   223,   223,   223,
     223,   223,   223,    55,    56,    57,   374,   223,   223,   223,
     223,     8,     8,     8,     8,     3,     8,   571,   573,     4,
       8,     3,     8,     8,   158,   159,   160,   588,   223,   223,
       7,     8,   223,   242,   667,     4,   665,     3,     8,   223,
       8,   253,   460,     4,     4,   226,   568,    40,   166,   167,
     168,   257,   519,   521,   597,   598,   599,   602,   604,   606,
       4,   224,     4,   662,   223,   223,   600,   603,   605,   607,
       3,     8,     5,   223,     4,     4,     4,     4,   598,     7,
     668,   669,   165,   601,   223,   223,     5,   670,     3,     6,
       7,   608,   609,   610,   198,   201,   202,   203,   204,   671,
     672,   673,   675,   676,   677,   678,   669,   611,     6,     3,
     674,     4,     4,     4,   679,     3,     8,   169,   170,   257,
     354,   356,   519,   521,   612,   613,   614,   616,   610,     4,
     226,   224,   224,     4,   672,   615,   617,     3,     8,   223,
     223,     4,     4,   613,   223,   223
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
     497,   497,   497,   497,   497,   497,   497,   497,   498,   500,
     499,   501,   502,   503,   504,   505,   507,   506,   508,   508,
     509,   509,   509,   511,   510,   513,   512,   514,   514,   514,
     515,   515,   515,   515,   515,   515,   515,   515,   517,   516,
     518,   520,   519,   522,   521,   524,   523,   525,   525,   526,
     526,   526,   528,   527,   530,   529,   531,   531,   532,   532,
     532,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   535,   534,   537,   536,
     539,   538,   541,   540,   543,   542,   545,   544,   547,   546,
     549,   548,   551,   550,   553,   552,   555,   554,   557,   556,
     558,   560,   559,   562,   561,   563,   563,   563,   565,   564,
     566,   566,   567,   567,   567,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   568,   568,   568,   568,   568,   568,
     568,   569,   571,   570,   573,   572,   574,   575,   577,   576,
     579,   578,   580,   580,   581,   581,   581,   583,   582,   584,
     584,   584,   585,   585,   585,   585,   585,   585,   585,   585,
     585,   585,   585,   585,   587,   586,   588,   588,   588,   590,
     589,   592,   591,   593,   594,   596,   595,   597,   597,   597,
     598,   598,   598,   598,   598,   598,   598,   600,   599,   601,
     603,   602,   605,   604,   607,   606,   608,   608,   609,   609,
     609,   611,   610,   612,   612,   612,   613,   613,   613,   613,
     613,   613,   613,   615,   614,   617,   616,   619,   618,   620,
     620,   620,   621,   621,   621,   621,   621,   621,   622,   624,
     623,   625,   627,   626,   629,   628,   631,   630,   632,   632,
     632,   633,   633,   633,   633,   633,   633,   633,   633,   633,
     633,   633,   634,   636,   635,   637,   639,   638,   640,   641,
     643,   642,   644,   644,   646,   645,   648,   647,   650,   649,
     651,   651,   651,   652,   652,   654,   653,   655,   657,   656,
     658,   658,   658,   660,   659,   661,   661,   661,   662,   662,
     662,   662,   662,   662,   662,   663,   665,   664,   667,   666,
     668,   668,   668,   670,   669,   671,   671,   671,   672,   672,
     672,   672,   672,   674,   673,   675,   676,   677,   679,   678,
     681,   680,   682,   682,   682,   683,   683,   683,   683,   683,
     684,   685,   686,   687
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
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
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     0,     6,     3,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     3
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
    2035,  2036,  2037,  2038,  2039,  2040,  2041,  2042,  2045,  2047,
    2047,  2056,  2058,  2060,  2066,  2072,  2081,  2081,  2094,  2095,
    2098,  2099,  2100,  2105,  2105,  2115,  2115,  2125,  2126,  2127,
    2132,  2133,  2134,  2135,  2136,  2137,  2138,  2139,  2142,  2142,
    2151,  2157,  2157,  2182,  2182,  2212,  2212,  2223,  2224,  2227,
    2228,  2229,  2234,  2234,  2243,  2243,  2252,  2253,  2256,  2257,
    2258,  2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,  2272,
    2273,  2274,  2275,  2276,  2277,  2278,  2281,  2281,  2290,  2290,
    2299,  2299,  2308,  2308,  2317,  2317,  2326,  2326,  2335,  2335,
    2344,  2344,  2353,  2353,  2362,  2362,  2371,  2371,  2385,  2385,
    2396,  2399,  2399,  2413,  2413,  2424,  2425,  2426,  2431,  2431,
    2441,  2442,  2445,  2446,  2447,  2452,  2453,  2454,  2455,  2456,
    2457,  2458,  2459,  2460,  2461,  2462,  2463,  2464,  2465,  2466,
    2467,  2470,  2472,  2472,  2481,  2481,  2490,  2498,  2506,  2506,
    2518,  2518,  2530,  2531,  2534,  2535,  2536,  2541,  2541,  2549,
    2550,  2551,  2556,  2557,  2558,  2559,  2560,  2561,  2562,  2563,
    2564,  2565,  2566,  2567,  2570,  2570,  2579,  2580,  2581,  2584,
    2584,  2594,  2594,  2604,  2610,  2618,  2618,  2631,  2632,  2633,
    2638,  2639,  2640,  2641,  2642,  2643,  2644,  2647,  2647,  2655,
    2658,  2658,  2667,  2667,  2676,  2676,  2687,  2688,  2691,  2692,
    2693,  2698,  2698,  2706,  2707,  2708,  2713,  2714,  2715,  2716,
    2717,  2718,  2719,  2722,  2722,  2731,  2731,  2742,  2742,  2755,
    2756,  2757,  2762,  2763,  2764,  2765,  2766,  2767,  2770,  2776,
    2776,  2785,  2791,  2791,  2801,  2801,  2814,  2814,  2824,  2825,
    2826,  2831,  2832,  2833,  2834,  2835,  2836,  2837,  2838,  2839,
    2840,  2841,  2844,  2850,  2850,  2859,  2865,  2865,  2874,  2880,
    2886,  2886,  2895,  2896,  2899,  2899,  2910,  2910,  2922,  2922,
    2932,  2933,  2934,  2940,  2941,  2944,  2944,  2955,  2963,  2963,
    2976,  2977,  2978,  2984,  2984,  2992,  2993,  2994,  2999,  3000,
    3001,  3002,  3003,  3004,  3005,  3008,  3014,  3014,  3023,  3023,
    3034,  3035,  3036,  3041,  3041,  3049,  3050,  3051,  3056,  3057,
    3058,  3059,  3060,  3063,  3063,  3072,  3078,  3084,  3090,  3090,
    3099,  3099,  3110,  3111,  3112,  3117,  3118,  3119,  3120,  3121,
    3124,  3130,  3136,  3142
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
#line 6664 "dhcp4_parser.cc"

#line 3148 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
