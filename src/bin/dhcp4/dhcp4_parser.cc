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
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 317 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 317 "dhcp4_parser.yy"
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
#line 326 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 327 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 328 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 329 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 330 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 331 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 332 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 333 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 334 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 335 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 336 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 337 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 338 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 346 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 347 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 348 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 349 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 350 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 351 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 352 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 355 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 360 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 365 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 371 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 378 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 383 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 389 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 394 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 397 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 405 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 409 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 413 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 419 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 421 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 430 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 434 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 438 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 448 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 457 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
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
#line 1077 "dhcp4_parser.cc"
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
#line 1092 "dhcp4_parser.cc"
    break;

  case 62: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 481 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 489 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 495 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 499 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 506 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 139: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 584 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 140: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 590 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 141: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 596 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 142: // renew_timer: "renew-timer" ":" "integer"
#line 602 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 143: // rebind_timer: "rebind-timer" ":" "integer"
#line 608 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 144: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 614 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 145: // t1_percent: "t1-percent" ":" "floating point"
#line 620 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 146: // t2_percent: "t2-percent" ":" "floating point"
#line 626 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 147: // cache_threshold: "cache-threshold" ":" "floating point"
#line 632 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 148: // cache_max_age: "cache-max-age" ":" "integer"
#line 638 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 149: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 644 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 150: // $@20: %empty
#line 650 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 151: // server_tag: "server-tag" $@20 ":" "constant string"
#line 653 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 152: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 659 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 665 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 154: // allocator: "allocator" $@21 ":" "constant string"
#line 668 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 155: // echo_client_id: "echo-client-id" ":" "boolean"
#line 674 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 156: // match_client_id: "match-client-id" ":" "boolean"
#line 680 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 157: // authoritative: "authoritative" ":" "boolean"
#line 686 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 158: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 692 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 698 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 160: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 704 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 710 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 713 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-present"
#line 719 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "never"
#line 722 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "always"
#line 725 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-not-present"
#line 728 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "boolean"
#line 731 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 168: // $@23: %empty
#line 737 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 169: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 740 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 170: // $@24: %empty
#line 746 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 171: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 749 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 172: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 755 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
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
#line 1476 "dhcp4_parser.cc"
    break;

  case 174: // $@25: %empty
#line 774 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 777 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 783 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 786 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 789 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 792 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 180: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 797 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 803 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 806 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 183: // $@27: %empty
#line 812 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 184: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 815 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 185: // store_extended_info: "store-extended-info" ":" "boolean"
#line 821 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 827 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 187: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 833 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 188: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 839 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 189: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 845 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 851 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 191: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 857 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 192: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 863 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1654 "dhcp4_parser.cc"
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
#line 1666 "dhcp4_parser.cc"
    break;

  case 194: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 875 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 197: // interfaces_config_params: interfaces_config_params ","
#line 883 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1684 "dhcp4_parser.cc"
    break;

  case 208: // $@29: %empty
#line 900 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 209: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 904 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1703 "dhcp4_parser.cc"
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
#line 1715 "dhcp4_parser.cc"
    break;

  case 211: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 915 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 212: // $@31: %empty
#line 920 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 213: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 923 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1742 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "raw"
#line 928 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp4_parser.cc"
    break;

  case 215: // socket_type: "udp"
#line 929 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp4_parser.cc"
    break;

  case 216: // $@32: %empty
#line 932 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 935 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "same-as-inbound"
#line 940 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 219: // outbound_interface_value: "use-routing"
#line 942 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1788 "dhcp4_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 946 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 952 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 958 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 964 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1828 "dhcp4_parser.cc"
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
#line 1840 "dhcp4_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 976 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc"
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
#line 1863 "dhcp4_parser.cc"
    break;

  case 227: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 989 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 230: // sanity_checks_params: sanity_checks_params ","
#line 996 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1880 "dhcp4_parser.cc"
    break;

  case 233: // $@35: %empty
#line 1005 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp4_parser.cc"
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
#line 1909 "dhcp4_parser.cc"
    break;

  case 235: // $@36: %empty
#line 1024 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp4_parser.cc"
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
#line 1937 "dhcp4_parser.cc"
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
#line 1949 "dhcp4_parser.cc"
    break;

  case 238: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1048 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1960 "dhcp4_parser.cc"
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
#line 1972 "dhcp4_parser.cc"
    break;

  case 240: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1061 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 245: // not_empty_database_list: not_empty_database_list ","
#line 1072 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1989 "dhcp4_parser.cc"
    break;

  case 246: // $@39: %empty
#line 1077 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 247: // database: "{" $@39 database_map_params "}"
#line 1081 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2009 "dhcp4_parser.cc"
    break;

  case 250: // database_map_params: database_map_params ","
#line 1089 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2017 "dhcp4_parser.cc"
    break;

  case 274: // $@40: %empty
#line 1119 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2026 "dhcp4_parser.cc"
    break;

  case 275: // database_type: "type" $@40 ":" "constant string"
#line 1122 "dhcp4_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 2036 "dhcp4_parser.cc"
    break;

  case 276: // $@41: %empty
#line 1128 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc"
    break;

  case 277: // user: "user" $@41 ":" "constant string"
#line 1131 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc"
    break;

  case 278: // $@42: %empty
#line 1137 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 279: // password: "password" $@42 ":" "constant string"
#line 1140 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 280: // $@43: %empty
#line 1146 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp4_parser.cc"
    break;

  case 281: // host: "host" $@43 ":" "constant string"
#line 1149 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2093 "dhcp4_parser.cc"
    break;

  case 282: // port: "port" ":" "integer"
#line 1155 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2103 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1161 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp4_parser.cc"
    break;

  case 284: // name: "name" $@44 ":" "constant string"
#line 1164 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2122 "dhcp4_parser.cc"
    break;

  case 285: // persist: "persist" ":" "boolean"
#line 1170 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 286: // lfc_interval: "lfc-interval" ":" "integer"
#line 1176 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 287: // readonly: "readonly" ":" "boolean"
#line 1182 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 288: // connect_timeout: "connect-timeout" ":" "integer"
#line 1188 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2162 "dhcp4_parser.cc"
    break;

  case 289: // read_timeout: "read-timeout" ":" "integer"
#line 1194 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 290: // write_timeout: "write-timeout" ":" "integer"
#line 1200 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 291: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1206 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 292: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1212 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 293: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1218 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1224 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 295: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1227 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 296: // on_fail_mode: "stop-retry-exit"
#line 1232 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2236 "dhcp4_parser.cc"
    break;

  case 297: // on_fail_mode: "serve-retry-exit"
#line 1233 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2242 "dhcp4_parser.cc"
    break;

  case 298: // on_fail_mode: "serve-retry-continue"
#line 1234 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2248 "dhcp4_parser.cc"
    break;

  case 299: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1237 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 300: // max_row_errors: "max-row-errors" ":" "integer"
#line 1243 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2268 "dhcp4_parser.cc"
    break;

  case 301: // $@46: %empty
#line 1249 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 302: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1252 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc"
    break;

  case 303: // $@47: %empty
#line 1258 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc"
    break;

  case 304: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1261 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2306 "dhcp4_parser.cc"
    break;

  case 305: // $@48: %empty
#line 1267 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp4_parser.cc"
    break;

  case 306: // key_file: "key-file" $@48 ":" "constant string"
#line 1270 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 307: // $@49: %empty
#line 1276 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2334 "dhcp4_parser.cc"
    break;

  case 308: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1279 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 309: // $@50: %empty
#line 1285 "dhcp4_parser.yy"
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
#line 1291 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2365 "dhcp4_parser.cc"
    break;

  case 313: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1298 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2373 "dhcp4_parser.cc"
    break;

  case 319: // duid_id: "duid"
#line 1310 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2382 "dhcp4_parser.cc"
    break;

  case 320: // hw_address_id: "hw-address"
#line 1315 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2391 "dhcp4_parser.cc"
    break;

  case 321: // circuit_id: "circuit-id"
#line 1320 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2400 "dhcp4_parser.cc"
    break;

  case 322: // client_id: "client-id"
#line 1325 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2409 "dhcp4_parser.cc"
    break;

  case 323: // flex_id: "flex-id"
#line 1330 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1337 "dhcp4_parser.yy"
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
#line 1343 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2441 "dhcp4_parser.cc"
    break;

  case 328: // multi_threading_params: multi_threading_params ","
#line 1352 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2449 "dhcp4_parser.cc"
    break;

  case 335: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1365 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2459 "dhcp4_parser.cc"
    break;

  case 336: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1371 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 337: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1377 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2479 "dhcp4_parser.cc"
    break;

  case 338: // $@52: %empty
#line 1383 "dhcp4_parser.yy"
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
#line 1389 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 344: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1400 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2508 "dhcp4_parser.cc"
    break;

  case 345: // $@53: %empty
#line 1405 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 346: // hooks_library: "{" $@53 hooks_params "}"
#line 1409 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 347: // $@54: %empty
#line 1415 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 348: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1419 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 351: // hooks_params: hooks_params ","
#line 1427 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2556 "dhcp4_parser.cc"
    break;

  case 355: // $@55: %empty
#line 1437 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 356: // library: "library" $@55 ":" "constant string"
#line 1440 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 357: // $@56: %empty
#line 1446 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2584 "dhcp4_parser.cc"
    break;

  case 358: // parameters: "parameters" $@56 ":" map_value
#line 1449 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2593 "dhcp4_parser.cc"
    break;

  case 359: // $@57: %empty
#line 1455 "dhcp4_parser.yy"
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
#line 1461 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 363: // expired_leases_params: expired_leases_params ","
#line 1469 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2623 "dhcp4_parser.cc"
    break;

  case 370: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1482 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2633 "dhcp4_parser.cc"
    break;

  case 371: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1488 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 372: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1494 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 373: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1500 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 374: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1506 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 375: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1512 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 376: // $@58: %empty
#line 1521 "dhcp4_parser.yy"
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
#line 1527 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2704 "dhcp4_parser.cc"
    break;

  case 382: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1541 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2712 "dhcp4_parser.cc"
    break;

  case 383: // $@59: %empty
#line 1550 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 384: // subnet4: "{" $@59 subnet4_params "}"
#line 1554 "dhcp4_parser.yy"
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
#line 1576 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 386: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1580 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 389: // subnet4_params: subnet4_params ","
#line 1589 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2776 "dhcp4_parser.cc"
    break;

  case 440: // $@61: %empty
#line 1647 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 441: // subnet: "subnet" $@61 ":" "constant string"
#line 1650 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc"
    break;

  case 442: // $@62: %empty
#line 1656 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 443: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1659 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2814 "dhcp4_parser.cc"
    break;

  case 444: // $@63: %empty
#line 1665 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1668 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 446: // $@64: %empty
#line 1674 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 447: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1677 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 448: // $@65: %empty
#line 1683 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 449: // interface: "interface" $@65 ":" "constant string"
#line 1686 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 450: // $@66: %empty
#line 1692 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc"
    break;

  case 451: // client_class: "client-class" $@66 ":" "constant string"
#line 1695 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 452: // $@67: %empty
#line 1702 "dhcp4_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp4_parser.cc"
    break;

  case 453: // network_client_classes: "client-classes" $@67 ":" list_strings
#line 1708 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2911 "dhcp4_parser.cc"
    break;

  case 454: // $@68: %empty
#line 1714 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 455: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1720 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 456: // $@69: %empty
#line 1725 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2944 "dhcp4_parser.cc"
    break;

  case 457: // evaluate_additional_classes: "evaluate-additional-classes" $@69 ":" list_strings
#line 1731 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2953 "dhcp4_parser.cc"
    break;

  case 458: // reservations_global: "reservations-global" ":" "boolean"
#line 1736 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2963 "dhcp4_parser.cc"
    break;

  case 459: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1742 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2973 "dhcp4_parser.cc"
    break;

  case 460: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1748 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2983 "dhcp4_parser.cc"
    break;

  case 461: // id: "id" ":" "integer"
#line 1754 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 462: // $@70: %empty
#line 1762 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3005 "dhcp4_parser.cc"
    break;

  case 463: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1768 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3014 "dhcp4_parser.cc"
    break;

  case 468: // shared_networks_list: shared_networks_list ","
#line 1781 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3022 "dhcp4_parser.cc"
    break;

  case 469: // $@71: %empty
#line 1786 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3032 "dhcp4_parser.cc"
    break;

  case 470: // shared_network: "{" $@71 shared_network_params "}"
#line 1790 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3040 "dhcp4_parser.cc"
    break;

  case 473: // shared_network_params: shared_network_params ","
#line 1796 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3048 "dhcp4_parser.cc"
    break;

  case 519: // $@72: %empty
#line 1852 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3060 "dhcp4_parser.cc"
    break;

  case 520: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1858 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3069 "dhcp4_parser.cc"
    break;

  case 521: // $@73: %empty
#line 1866 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3078 "dhcp4_parser.cc"
    break;

  case 522: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1869 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3086 "dhcp4_parser.cc"
    break;

  case 527: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1881 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3094 "dhcp4_parser.cc"
    break;

  case 528: // $@74: %empty
#line 1888 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3104 "dhcp4_parser.cc"
    break;

  case 529: // option_def_entry: "{" $@74 option_def_params "}"
#line 1892 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3116 "dhcp4_parser.cc"
    break;

  case 530: // $@75: %empty
#line 1903 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3126 "dhcp4_parser.cc"
    break;

  case 531: // sub_option_def: "{" $@75 option_def_params "}"
#line 1907 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3138 "dhcp4_parser.cc"
    break;

  case 536: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1923 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3146 "dhcp4_parser.cc"
    break;

  case 548: // code: "code" ":" "integer"
#line 1942 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 550: // $@76: %empty
#line 1950 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3165 "dhcp4_parser.cc"
    break;

  case 551: // option_def_type: "type" $@76 ":" "constant string"
#line 1953 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3175 "dhcp4_parser.cc"
    break;

  case 552: // $@77: %empty
#line 1959 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp4_parser.cc"
    break;

  case 553: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1962 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3194 "dhcp4_parser.cc"
    break;

  case 554: // $@78: %empty
#line 1968 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc"
    break;

  case 555: // space: "space" $@78 ":" "constant string"
#line 1971 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc"
    break;

  case 557: // $@79: %empty
#line 1979 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp4_parser.cc"
    break;

  case 558: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1982 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3232 "dhcp4_parser.cc"
    break;

  case 559: // option_def_array: "array" ":" "boolean"
#line 1988 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3242 "dhcp4_parser.cc"
    break;

  case 560: // $@80: %empty
#line 1998 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 561: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 2004 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 566: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2019 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3271 "dhcp4_parser.cc"
    break;

  case 567: // $@81: %empty
#line 2026 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3281 "dhcp4_parser.cc"
    break;

  case 568: // option_data_entry: "{" $@81 option_data_params "}"
#line 2030 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3290 "dhcp4_parser.cc"
    break;

  case 569: // $@82: %empty
#line 2038 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3300 "dhcp4_parser.cc"
    break;

  case 570: // sub_option_data: "{" $@82 option_data_params "}"
#line 2042 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3309 "dhcp4_parser.cc"
    break;

  case 575: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2058 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3317 "dhcp4_parser.cc"
    break;

  case 588: // $@83: %empty
#line 2080 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3326 "dhcp4_parser.cc"
    break;

  case 589: // option_data_data: "data" $@83 ":" "constant string"
#line 2083 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3336 "dhcp4_parser.cc"
    break;

  case 592: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2093 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3346 "dhcp4_parser.cc"
    break;

  case 593: // option_data_always_send: "always-send" ":" "boolean"
#line 2099 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3356 "dhcp4_parser.cc"
    break;

  case 594: // option_data_never_send: "never-send" ":" "boolean"
#line 2105 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 595: // $@84: %empty
#line 2111 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp4_parser.cc"
    break;

  case 596: // option_data_client_classes: "client-classes" $@84 ":" list_strings
#line 2117 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3387 "dhcp4_parser.cc"
    break;

  case 597: // $@85: %empty
#line 2125 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3399 "dhcp4_parser.cc"
    break;

  case 598: // pools_list: "pools" $@85 ":" "[" pools_list_content "]"
#line 2131 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 603: // not_empty_pools_list: not_empty_pools_list ","
#line 2144 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3416 "dhcp4_parser.cc"
    break;

  case 604: // $@86: %empty
#line 2149 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 605: // pool_list_entry: "{" $@86 pool_params "}"
#line 2153 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 606: // $@87: %empty
#line 2159 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3446 "dhcp4_parser.cc"
    break;

  case 607: // sub_pool4: "{" $@87 pool_params "}"
#line 2163 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3456 "dhcp4_parser.cc"
    break;

  case 610: // pool_params: pool_params ","
#line 2171 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3464 "dhcp4_parser.cc"
    break;

  case 621: // $@88: %empty
#line 2188 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 622: // pool_entry: "pool" $@88 ":" "constant string"
#line 2191 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 623: // pool_id: "pool-id" ":" "integer"
#line 2197 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3493 "dhcp4_parser.cc"
    break;

  case 624: // $@89: %empty
#line 2203 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3501 "dhcp4_parser.cc"
    break;

  case 625: // user_context: "user-context" $@89 ":" map_value
#line 2205 "dhcp4_parser.yy"
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
#line 3528 "dhcp4_parser.cc"
    break;

  case 626: // $@90: %empty
#line 2228 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3536 "dhcp4_parser.cc"
    break;

  case 627: // comment: "comment" $@90 ":" "constant string"
#line 2230 "dhcp4_parser.yy"
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
#line 3565 "dhcp4_parser.cc"
    break;

  case 628: // $@91: %empty
#line 2258 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3577 "dhcp4_parser.cc"
    break;

  case 629: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2264 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3586 "dhcp4_parser.cc"
    break;

  case 634: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2275 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3594 "dhcp4_parser.cc"
    break;

  case 635: // $@92: %empty
#line 2280 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 636: // reservation: "{" $@92 reservation_params "}"
#line 2284 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3613 "dhcp4_parser.cc"
    break;

  case 637: // $@93: %empty
#line 2289 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3623 "dhcp4_parser.cc"
    break;

  case 638: // sub_reservation: "{" $@93 reservation_params "}"
#line 2293 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 643: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2304 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3640 "dhcp4_parser.cc"
    break;

  case 659: // $@94: %empty
#line 2327 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3649 "dhcp4_parser.cc"
    break;

  case 660: // next_server: "next-server" $@94 ":" "constant string"
#line 2330 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 661: // $@95: %empty
#line 2336 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 662: // server_hostname: "server-hostname" $@95 ":" "constant string"
#line 2339 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3678 "dhcp4_parser.cc"
    break;

  case 663: // $@96: %empty
#line 2345 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3687 "dhcp4_parser.cc"
    break;

  case 664: // boot_file_name: "boot-file-name" $@96 ":" "constant string"
#line 2348 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3697 "dhcp4_parser.cc"
    break;

  case 665: // $@97: %empty
#line 2354 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3706 "dhcp4_parser.cc"
    break;

  case 666: // ip_address: "ip-address" $@97 ":" "constant string"
#line 2357 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3716 "dhcp4_parser.cc"
    break;

  case 667: // $@98: %empty
#line 2363 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3725 "dhcp4_parser.cc"
    break;

  case 668: // duid: "duid" $@98 ":" "constant string"
#line 2366 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3735 "dhcp4_parser.cc"
    break;

  case 669: // $@99: %empty
#line 2372 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3744 "dhcp4_parser.cc"
    break;

  case 670: // hw_address: "hw-address" $@99 ":" "constant string"
#line 2375 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3754 "dhcp4_parser.cc"
    break;

  case 671: // $@100: %empty
#line 2381 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3763 "dhcp4_parser.cc"
    break;

  case 672: // client_id_value: "client-id" $@100 ":" "constant string"
#line 2384 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3773 "dhcp4_parser.cc"
    break;

  case 673: // $@101: %empty
#line 2390 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3782 "dhcp4_parser.cc"
    break;

  case 674: // circuit_id_value: "circuit-id" $@101 ":" "constant string"
#line 2393 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3792 "dhcp4_parser.cc"
    break;

  case 675: // $@102: %empty
#line 2399 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3801 "dhcp4_parser.cc"
    break;

  case 676: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2402 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3811 "dhcp4_parser.cc"
    break;

  case 677: // $@103: %empty
#line 2408 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3820 "dhcp4_parser.cc"
    break;

  case 678: // hostname: "hostname" $@103 ":" "constant string"
#line 2411 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 679: // $@104: %empty
#line 2417 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 680: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2423 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3851 "dhcp4_parser.cc"
    break;

  case 681: // $@105: %empty
#line 2431 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 682: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2437 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 684: // $@106: %empty
#line 2445 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 685: // ip_addresses: "ip-addresses" $@106 ":" list_strings
#line 2451 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 686: // $@107: %empty
#line 2459 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3905 "dhcp4_parser.cc"
    break;

  case 687: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2465 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3914 "dhcp4_parser.cc"
    break;

  case 690: // client_classes_list: client_classes_list ","
#line 2472 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3922 "dhcp4_parser.cc"
    break;

  case 691: // $@108: %empty
#line 2477 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3932 "dhcp4_parser.cc"
    break;

  case 692: // client_class_entry: "{" $@108 client_class_params "}"
#line 2481 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 697: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2493 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3950 "dhcp4_parser.cc"
    break;

  case 716: // $@109: %empty
#line 2519 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3959 "dhcp4_parser.cc"
    break;

  case 717: // client_class_test: "test" $@109 ":" "constant string"
#line 2522 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3969 "dhcp4_parser.cc"
    break;

  case 718: // $@110: %empty
#line 2528 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3978 "dhcp4_parser.cc"
    break;

  case 719: // client_class_template_test: "template-test" $@110 ":" "constant string"
#line 2531 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3988 "dhcp4_parser.cc"
    break;

  case 720: // only_if_required: "only-if-required" ":" "boolean"
#line 2538 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3998 "dhcp4_parser.cc"
    break;

  case 721: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2544 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4008 "dhcp4_parser.cc"
    break;

  case 722: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2552 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 723: // $@111: %empty
#line 2560 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 724: // control_socket: "control-socket" $@111 ":" "{" control_socket_params "}"
#line 2567 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4040 "dhcp4_parser.cc"
    break;

  case 725: // $@112: %empty
#line 2572 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4053 "dhcp4_parser.cc"
    break;

  case 726: // control_sockets: "control-sockets" $@112 ":" "[" control_socket_list "]"
#line 2579 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 731: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2590 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4070 "dhcp4_parser.cc"
    break;

  case 732: // $@113: %empty
#line 2595 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4080 "dhcp4_parser.cc"
    break;

  case 733: // control_socket_entry: "{" $@113 control_socket_params "}"
#line 2599 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4088 "dhcp4_parser.cc"
    break;

  case 736: // control_socket_params: control_socket_params ","
#line 2605 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4096 "dhcp4_parser.cc"
    break;

  case 750: // $@114: %empty
#line 2625 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 751: // control_socket_type: "socket-type" $@114 ":" control_socket_type_value
#line 2628 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 752: // control_socket_type_value: "unix"
#line 2634 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4120 "dhcp4_parser.cc"
    break;

  case 753: // control_socket_type_value: "http"
#line 2635 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4126 "dhcp4_parser.cc"
    break;

  case 754: // control_socket_type_value: "https"
#line 2636 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4132 "dhcp4_parser.cc"
    break;

  case 755: // $@115: %empty
#line 2639 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4142 "dhcp4_parser.cc"
    break;

  case 756: // control_socket_name: "socket-name" $@115 ":" "constant string"
#line 2643 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4152 "dhcp4_parser.cc"
    break;

  case 757: // $@116: %empty
#line 2649 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4162 "dhcp4_parser.cc"
    break;

  case 758: // control_socket_address: "socket-address" $@116 ":" "constant string"
#line 2653 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4172 "dhcp4_parser.cc"
    break;

  case 759: // control_socket_port: "socket-port" ":" "integer"
#line 2659 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 760: // cert_required: "cert-required" ":" "boolean"
#line 2665 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 761: // $@117: %empty
#line 2671 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4204 "dhcp4_parser.cc"
    break;

  case 762: // http_headers: "http-headers" $@117 ":" "[" http_header_list "]"
#line 2677 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4213 "dhcp4_parser.cc"
    break;

  case 767: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2688 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4221 "dhcp4_parser.cc"
    break;

  case 768: // $@118: %empty
#line 2693 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4231 "dhcp4_parser.cc"
    break;

  case 769: // http_header: "{" $@118 http_header_params "}"
#line 2697 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4239 "dhcp4_parser.cc"
    break;

  case 772: // http_header_params: http_header_params ","
#line 2703 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4247 "dhcp4_parser.cc"
    break;

  case 778: // $@119: %empty
#line 2715 "dhcp4_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 779: // header_value: "value" $@119 ":" "constant string"
#line 2718 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4266 "dhcp4_parser.cc"
    break;

  case 780: // $@120: %empty
#line 2726 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4278 "dhcp4_parser.cc"
    break;

  case 781: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2732 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4289 "dhcp4_parser.cc"
    break;

  case 784: // auth_params: auth_params ","
#line 2741 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4297 "dhcp4_parser.cc"
    break;

  case 792: // $@121: %empty
#line 2755 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4306 "dhcp4_parser.cc"
    break;

  case 793: // auth_type: "type" $@121 ":" auth_type_value
#line 2758 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4315 "dhcp4_parser.cc"
    break;

  case 794: // auth_type_value: "basic"
#line 2763 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4321 "dhcp4_parser.cc"
    break;

  case 795: // $@122: %empty
#line 2766 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4330 "dhcp4_parser.cc"
    break;

  case 796: // realm: "realm" $@122 ":" "constant string"
#line 2769 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4340 "dhcp4_parser.cc"
    break;

  case 797: // $@123: %empty
#line 2775 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4349 "dhcp4_parser.cc"
    break;

  case 798: // directory: "directory" $@123 ":" "constant string"
#line 2778 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4359 "dhcp4_parser.cc"
    break;

  case 799: // $@124: %empty
#line 2784 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4371 "dhcp4_parser.cc"
    break;

  case 800: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2790 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4380 "dhcp4_parser.cc"
    break;

  case 805: // not_empty_clients_list: not_empty_clients_list ","
#line 2801 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4388 "dhcp4_parser.cc"
    break;

  case 806: // $@125: %empty
#line 2806 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 807: // basic_auth: "{" $@125 clients_params "}"
#line 2810 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4406 "dhcp4_parser.cc"
    break;

  case 810: // clients_params: clients_params ","
#line 2816 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4414 "dhcp4_parser.cc"
    break;

  case 818: // $@126: %empty
#line 2830 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4423 "dhcp4_parser.cc"
    break;

  case 819: // user_file: "user-file" $@126 ":" "constant string"
#line 2833 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4433 "dhcp4_parser.cc"
    break;

  case 820: // $@127: %empty
#line 2839 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4442 "dhcp4_parser.cc"
    break;

  case 821: // password_file: "password-file" $@127 ":" "constant string"
#line 2842 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4452 "dhcp4_parser.cc"
    break;

  case 822: // $@128: %empty
#line 2850 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4464 "dhcp4_parser.cc"
    break;

  case 823: // dhcp_queue_control: "dhcp-queue-control" $@128 ":" "{" queue_control_params "}"
#line 2856 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4475 "dhcp4_parser.cc"
    break;

  case 826: // queue_control_params: queue_control_params ","
#line 2865 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4483 "dhcp4_parser.cc"
    break;

  case 833: // enable_queue: "enable-queue" ":" "boolean"
#line 2878 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4493 "dhcp4_parser.cc"
    break;

  case 834: // $@129: %empty
#line 2884 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4502 "dhcp4_parser.cc"
    break;

  case 835: // queue_type: "queue-type" $@129 ":" "constant string"
#line 2887 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4512 "dhcp4_parser.cc"
    break;

  case 836: // capacity: "capacity" ":" "integer"
#line 2893 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4522 "dhcp4_parser.cc"
    break;

  case 837: // $@130: %empty
#line 2899 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4531 "dhcp4_parser.cc"
    break;

  case 838: // arbitrary_map_entry: "constant string" $@130 ":" value
#line 2902 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4540 "dhcp4_parser.cc"
    break;

  case 839: // $@131: %empty
#line 2909 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 840: // dhcp_ddns: "dhcp-ddns" $@131 ":" "{" dhcp_ddns_params "}"
#line 2915 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4563 "dhcp4_parser.cc"
    break;

  case 841: // $@132: %empty
#line 2922 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4573 "dhcp4_parser.cc"
    break;

  case 842: // sub_dhcp_ddns: "{" $@132 dhcp_ddns_params "}"
#line 2926 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4583 "dhcp4_parser.cc"
    break;

  case 845: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2934 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4591 "dhcp4_parser.cc"
    break;

  case 857: // enable_updates: "enable-updates" ":" "boolean"
#line 2952 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4601 "dhcp4_parser.cc"
    break;

  case 858: // $@133: %empty
#line 2958 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4610 "dhcp4_parser.cc"
    break;

  case 859: // server_ip: "server-ip" $@133 ":" "constant string"
#line 2961 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4620 "dhcp4_parser.cc"
    break;

  case 860: // server_port: "server-port" ":" "integer"
#line 2967 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4630 "dhcp4_parser.cc"
    break;

  case 861: // $@134: %empty
#line 2973 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4639 "dhcp4_parser.cc"
    break;

  case 862: // sender_ip: "sender-ip" $@134 ":" "constant string"
#line 2976 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4649 "dhcp4_parser.cc"
    break;

  case 863: // sender_port: "sender-port" ":" "integer"
#line 2982 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4659 "dhcp4_parser.cc"
    break;

  case 864: // max_queue_size: "max-queue-size" ":" "integer"
#line 2988 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4669 "dhcp4_parser.cc"
    break;

  case 865: // $@135: %empty
#line 2994 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4678 "dhcp4_parser.cc"
    break;

  case 866: // ncr_protocol: "ncr-protocol" $@135 ":" ncr_protocol_value
#line 2997 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4687 "dhcp4_parser.cc"
    break;

  case 867: // ncr_protocol_value: "udp"
#line 3003 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4693 "dhcp4_parser.cc"
    break;

  case 868: // ncr_protocol_value: "tcp"
#line 3004 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4699 "dhcp4_parser.cc"
    break;

  case 869: // $@136: %empty
#line 3007 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 870: // ncr_format: "ncr-format" $@136 ":" "JSON"
#line 3010 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4718 "dhcp4_parser.cc"
    break;

  case 871: // $@137: %empty
#line 3018 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4730 "dhcp4_parser.cc"
    break;

  case 872: // config_control: "config-control" $@137 ":" "{" config_control_params "}"
#line 3024 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4740 "dhcp4_parser.cc"
    break;

  case 873: // $@138: %empty
#line 3030 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4750 "dhcp4_parser.cc"
    break;

  case 874: // sub_config_control: "{" $@138 config_control_params "}"
#line 3034 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4759 "dhcp4_parser.cc"
    break;

  case 877: // config_control_params: config_control_params ","
#line 3042 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4767 "dhcp4_parser.cc"
    break;

  case 880: // $@139: %empty
#line 3052 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4779 "dhcp4_parser.cc"
    break;

  case 881: // config_databases: "config-databases" $@139 ":" "[" database_list "]"
#line 3058 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4788 "dhcp4_parser.cc"
    break;

  case 882: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3063 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4798 "dhcp4_parser.cc"
    break;

  case 883: // $@140: %empty
#line 3071 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4810 "dhcp4_parser.cc"
    break;

  case 884: // loggers: "loggers" $@140 ":" "[" loggers_entries "]"
#line 3077 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4819 "dhcp4_parser.cc"
    break;

  case 887: // loggers_entries: loggers_entries ","
#line 3086 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4827 "dhcp4_parser.cc"
    break;

  case 888: // $@141: %empty
#line 3092 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4837 "dhcp4_parser.cc"
    break;

  case 889: // logger_entry: "{" $@141 logger_params "}"
#line 3096 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4845 "dhcp4_parser.cc"
    break;

  case 892: // logger_params: logger_params ","
#line 3102 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4853 "dhcp4_parser.cc"
    break;

  case 900: // debuglevel: "debuglevel" ":" "integer"
#line 3116 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4863 "dhcp4_parser.cc"
    break;

  case 901: // $@142: %empty
#line 3122 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4872 "dhcp4_parser.cc"
    break;

  case 902: // severity: "severity" $@142 ":" "constant string"
#line 3125 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4882 "dhcp4_parser.cc"
    break;

  case 903: // $@143: %empty
#line 3131 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4894 "dhcp4_parser.cc"
    break;

  case 904: // output_options_list: "output-options" $@143 ":" "[" output_options_list_content "]"
#line 3137 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4903 "dhcp4_parser.cc"
    break;

  case 907: // output_options_list_content: output_options_list_content ","
#line 3144 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4911 "dhcp4_parser.cc"
    break;

  case 908: // $@144: %empty
#line 3149 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4921 "dhcp4_parser.cc"
    break;

  case 909: // output_entry: "{" $@144 output_params_list "}"
#line 3153 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4929 "dhcp4_parser.cc"
    break;

  case 912: // output_params_list: output_params_list ","
#line 3159 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4937 "dhcp4_parser.cc"
    break;

  case 918: // $@145: %empty
#line 3171 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4946 "dhcp4_parser.cc"
    break;

  case 919: // output: "output" $@145 ":" "constant string"
#line 3174 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4956 "dhcp4_parser.cc"
    break;

  case 920: // flush: "flush" ":" "boolean"
#line 3180 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4966 "dhcp4_parser.cc"
    break;

  case 921: // maxsize: "maxsize" ":" "integer"
#line 3186 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4976 "dhcp4_parser.cc"
    break;

  case 922: // maxver: "maxver" ":" "integer"
#line 3192 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4986 "dhcp4_parser.cc"
    break;

  case 923: // $@146: %empty
#line 3198 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4995 "dhcp4_parser.cc"
    break;

  case 924: // pattern: "pattern" $@146 ":" "constant string"
#line 3201 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5005 "dhcp4_parser.cc"
    break;

  case 925: // $@147: %empty
#line 3207 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5017 "dhcp4_parser.cc"
    break;

  case 926: // compatibility: "compatibility" $@147 ":" "{" compatibility_params "}"
#line 3213 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5026 "dhcp4_parser.cc"
    break;

  case 929: // compatibility_params: compatibility_params ","
#line 3220 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5034 "dhcp4_parser.cc"
    break;

  case 935: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3232 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5044 "dhcp4_parser.cc"
    break;

  case 936: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3238 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5054 "dhcp4_parser.cc"
    break;

  case 937: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3244 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5064 "dhcp4_parser.cc"
    break;

  case 938: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3250 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5074 "dhcp4_parser.cc"
    break;


#line 5078 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1369;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     632, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,    36,    39,    47,    83,    98,   100,
     104,   123,   129,   133,   140,   142,   160,   168, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,    39,  -170,    68,   166,    72,   698,
     285,   288,   -31,   112,   337,   -93,   516,   252, -1369,    95,
      78,   117,   176,    80, -1369,    50, -1369, -1369, -1369, -1369,
     206,   253,   257, -1369, -1369, -1369,   299,   310, -1369, -1369,
   -1369,   313,   321,   325,   341,   353,   363,   375,   376,   382,
     390,   391, -1369,   413,   416,   424,   425,   426, -1369, -1369,
   -1369,   441,   444,   446,   449, -1369, -1369, -1369,   450, -1369,
   -1369, -1369, -1369, -1369,   451,   453,   454, -1369, -1369, -1369,
   -1369, -1369,   455, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     457,   458,   460, -1369, -1369,   461, -1369,    52, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     462,   464,   465,   466, -1369,    90, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   467, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,    96, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   469, -1369, -1369, -1369, -1369, -1369, -1369,   111, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   210,   472, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     468, -1369, -1369,   473, -1369, -1369, -1369,   475, -1369, -1369,
     476,   477, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   479,   481,   483, -1369, -1369,
   -1369, -1369, -1369,   485,   478, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   119,
   -1369, -1369, -1369,   487, -1369,   490, -1369,   492,   496, -1369,
   -1369, -1369, -1369, -1369,   121, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   499,   134, -1369, -1369, -1369,
   -1369,    39,    39, -1369,   279,   503, -1369, -1369,   505,   506,
     510,   290,   291,   292,   520,   521,   522,   301,   297,   526,
     528,   530,   308,   312,   314,   316,   319,   311,   322,   323,
     324,   326,   327,   545,   328,   329,   336,   338,   340,   546,
     555,   558,   342,   345,   347,   349,   563,   565,   573,   352,
     578,   579,   581,   583,   584,   360,   361,   365,   589,   593,
     594,   596,   597,   374,   599,   604,   606,   609,   611,   612,
     614,   396,   398,   402,   616,   617, -1369,   166, -1369,   619,
     629,   630,   408,   409,   412,   414,    72, -1369,   637,   639,
     640,   641,   642,   643,   420,   645,   647,   649,   650,   651,
     698, -1369,   652,   445,   285, -1369,   670,   678,   679,   680,
     681,   682,   688,   689, -1369,   288, -1369,   690,   692,   480,
     701,   702,   703,   486, -1369,   112,   705,   488,   489,   491,
     711, -1369,   337,   713,   716,   157, -1369,   493,   720,   497,
     722,   507,   508,   723,   733,   516, -1369,   738,   517,   252,
   -1369, -1369, -1369,   740,   739,   743,   744,   745, -1369, -1369,
   -1369,   527,   529,   532, -1369, -1369,   746,   748,   742, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     547, -1369, -1369, -1369, -1369, -1369,  -124,   548,   559, -1369,
   -1369, -1369, -1369,   767,   768,   785, -1369,   566,   183,   787,
     788,   567, -1369, -1369, -1369,   791,   792,   793,   794,   798,
   -1369,   799,   800,   795,   801,   802,   574,   598, -1369, -1369,
   -1369,   806,   813, -1369,   819,   320,   339, -1369, -1369, -1369,
   -1369, -1369,   600,   602,   605,   821,   607,   608, -1369,   819,
     819,   819,   610,   824, -1369,   613, -1369, -1369,   819,   615,
     633,   634,   635,   636,   638,   644, -1369,   646,   648, -1369,
     653,   654,   655, -1369, -1369,   656, -1369, -1369, -1369,   819,
   -1369,   657,   788, -1369, -1369,   658, -1369,   659, -1369, -1369,
       4,   669, -1369,   828, -1369, -1369,    39,   166,   252,    72,
     343, -1369, -1369, -1369,   618,   618,   829, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   832,   834,   836, -1369,
   -1369, -1369, -1369, -1369, -1369,   837, -1369, -1369, -1369,   170,
     857,   859,   860,   201,   229,   575,   861,    -6,   516, -1369,
   -1369,   862,   -95, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,   863, -1369, -1369, -1369, -1369, -1369,
   -1369,   731, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   829, -1369,   136,   152,
     154, -1369, -1369,   156, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   870,   872,   873,   874,   875,   883,   884,   885,   886,
     887, -1369,   888,   891, -1369, -1369, -1369, -1369, -1369,   162,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   171, -1369,   890,   894, -1369, -1369,   892,
     896, -1369, -1369,   895,   897, -1369, -1369,   898,   899, -1369,
   -1369,   900,   902, -1369, -1369, -1369, -1369, -1369, -1369,    86,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369,   182, -1369, -1369,
     901,   905, -1369, -1369,   903,   907, -1369,   908,   909,   910,
     911,   912,   913,   173, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   914,   915,   916, -1369,   204, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   917, -1369,   918, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   208, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   920,   921, -1369,   919, -1369,
     923, -1369, -1369, -1369,   307, -1369, -1369, -1369, -1369, -1369,
     332, -1369,   188, -1369,   924,   925,   926,   927, -1369,   350,
   -1369, -1369, -1369, -1369, -1369,   676, -1369,   928,   929, -1369,
   -1369,   930, -1369,   931, -1369, -1369, -1369,   932,   935,   343,
   -1369,   936,   937,   938,   939,   683,   714,   707,   715,   718,
     719,   721,   724,   725,   726,   944,   727,   728,   946,   947,
     951,   954,   618, -1369, -1369,   618, -1369,   829,   698, -1369,
     832,   112, -1369,   834,   337, -1369,   836,  1354, -1369,   837,
     170, -1369,   262,   857, -1369,   288, -1369,   859,   -93, -1369,
     860,   732,   734,   735,   737,   741,   749,   201, -1369,   729,
     755,   757,   229, -1369,   962,   969,   972,   758,   984,   761,
     988,   575, -1369,   575, -1369,   861,   769,   999,   781,  1008,
      -6, -1369, -1369,    75,   862, -1369,   784,   796,   803,   816,
     -95, -1369, -1369,  1011,  1019,   285, -1369,   863,  1021, -1369,
   -1369,   706,   805, -1369,   820,   822,   827,   835, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   218, -1369,
   -1369,   840,   868,   906,   922, -1369,   366, -1369,   379, -1369,
    1047, -1369,  1048, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   389, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,  1060,  1085, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
    1115,  1125, -1369, -1369, -1369, -1369, -1369, -1369, -1369,  1122,
   -1369,   393, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,   244,   933,   934, -1369,  1128, -1369,
    1127, -1369,   404, -1369, -1369,   940, -1369,    39, -1369, -1369,
    1133, -1369, -1369, -1369, -1369, -1369,   410, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   941,   411,
   -1369,   819, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
    1354, -1369,  1134,  1135,   942,   943, -1369,   262, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   114,  1136, -1369, -1369,
   -1369,  1137,   948,  1138,    75, -1369, -1369, -1369, -1369, -1369,
     950,   952, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   435, -1369, -1369, -1369, -1369, -1369, -1369,  1139,
    1141, -1369,  1142, -1369,   953, -1369, -1369, -1369,  1144,  1146,
    1147,  1148,   114, -1369,   -49, -1369,  1136,  1149, -1369,   973,
     955,   956,  1150, -1369, -1369, -1369, -1369, -1369, -1369,   436,
   -1369, -1369, -1369, -1369,   214, -1369, -1369, -1369, -1369, -1369,
    1151,  1153,   -49, -1369,    17,  1149, -1369, -1369,  1140,  1156,
   -1369,   957, -1369, -1369,  1158,  1159,  1160, -1369,   438, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369,   141, -1369,  1151, -1369,
    1161,   945,   958,   959,  1165,    17, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369,   439, -1369, -1369, -1369, -1369,   961,
   -1369, -1369, -1369,   963, -1369,  1166,  1167,   141, -1369, -1369,
   -1369,   964,   965, -1369, -1369, -1369
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   208,     9,   385,    11,   606,    13,
     637,    15,   521,    17,   530,    19,   569,    21,   347,    23,
     841,    25,   873,    27,    46,    39,     0,     0,     0,     0,
       0,   639,     0,   532,   571,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   871,   193,   226,
       0,     0,     0,   659,   661,   663,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   376,   519,   560,     0,   153,
     174,   462,   624,   626,     0,     0,     0,   309,   686,   628,
     338,   359,     0,   324,   723,   725,   822,   839,   181,   183,
       0,     0,     0,   883,   925,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     104,   134,   135,    93,    94,    95,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   101,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,    77,
      84,    85,    99,   100,   102,    96,    97,    98,    83,    88,
      89,    90,    91,    92,   103,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   442,   444,   446,   597,
     440,   448,     0,   452,   454,   456,   450,   681,   439,   390,
     391,   392,   393,   394,   419,   420,   421,   422,   423,   437,
     409,   410,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   438,     0,   387,   397,   414,
     415,   416,   398,   400,   401,   402,   403,   405,   406,   407,
     399,   395,   396,   417,   418,   404,   411,   412,   413,   408,
     621,     0,   620,   614,   615,   616,   617,   613,     0,   608,
     611,   612,   618,   619,   679,   665,   667,   669,   673,   671,
     677,   675,   658,   652,   656,   657,     0,   640,   641,   653,
     654,   655,   649,   644,   650,   646,   647,   648,   651,   645,
       0,   550,   283,     0,   554,   552,   557,     0,   546,   547,
       0,   533,   534,   537,   549,   538,   539,   540,   556,   541,
     542,   543,   544,   545,   588,     0,     0,     0,   595,   586,
     587,   590,   591,     0,   572,   573,   576,   577,   578,   579,
     580,   581,   582,   585,   583,   584,   355,   357,   352,     0,
     349,   353,   354,     0,   858,     0,   861,     0,     0,   865,
     869,   856,   854,   855,     0,   843,   846,   847,   848,   849,
     850,   851,   852,   853,   880,     0,     0,   875,   878,   879,
      45,    50,     0,    37,    43,     0,    64,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    69,    66,     0,
       0,     0,     0,     0,     0,     0,   197,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     389,   386,     0,     0,   610,   607,     0,     0,     0,     0,
       0,     0,     0,     0,   638,   643,   522,     0,     0,     0,
       0,     0,     0,     0,   531,   536,     0,     0,     0,     0,
       0,   570,   575,     0,     0,   351,   348,     0,     0,     0,
       0,     0,     0,     0,     0,   845,   842,     0,     0,   877,
     874,    49,    41,     0,     0,     0,     0,     0,   155,   156,
     157,     0,     0,     0,   191,   192,     0,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
       0,   186,   187,   158,   159,   160,     0,     0,     0,   172,
     173,   180,   185,     0,     0,     0,   152,     0,     0,     0,
       0,     0,   458,   459,   460,     0,     0,     0,     0,     0,
     722,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,     0,     0,    68,     0,     0,     0,   220,   221,   222,
     223,   196,     0,     0,     0,     0,     0,     0,   461,     0,
       0,     0,     0,     0,   388,     0,   623,   609,     0,     0,
       0,     0,     0,     0,     0,     0,   642,     0,     0,   548,
       0,     0,     0,   559,   535,     0,   592,   593,   594,     0,
     574,     0,     0,   350,   857,     0,   860,     0,   863,   864,
       0,     0,   844,     0,   882,   876,     0,     0,     0,     0,
       0,   660,   662,   664,     0,     0,   241,   151,   163,   164,
     165,   166,   167,   162,   169,   171,   378,   523,   562,   154,
     176,   177,   178,   179,   175,   464,    38,   625,   627,     0,
       0,   630,   340,     0,     0,     0,   727,     0,     0,   182,
     184,     0,     0,    51,   211,   214,   215,   213,   218,   219,
     217,   443,   445,   447,   599,   441,   449,   453,   455,   457,
     451,     0,   622,   680,   666,   668,   670,   674,   672,   678,
     676,   551,   284,   555,   553,   558,   589,   596,   356,   358,
     859,   862,   867,   868,   866,   870,   241,    42,     0,     0,
       0,   233,   235,     0,   228,   231,   232,   274,   276,   278,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   294,     0,     0,   301,   303,   305,   307,   273,     0,
     248,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,     0,   246,     0,   242,   243,   383,     0,
     379,   380,   528,     0,   524,   525,   567,     0,   563,   564,
     469,     0,   465,   466,   319,   320,   321,   322,   323,     0,
     311,   314,   315,   316,   317,   318,   691,     0,   688,   635,
       0,   631,   632,   345,     0,   341,   342,     0,     0,     0,
       0,     0,     0,     0,   361,   364,   365,   366,   367,   368,
     369,     0,     0,     0,   334,     0,   326,   329,   330,   331,
     332,   333,   750,   755,   757,     0,   780,     0,   761,   749,
     742,   743,   744,   747,   748,     0,   734,   737,   738,   739,
     740,   745,   746,   741,   732,     0,   728,   729,     0,   834,
       0,   837,   830,   831,     0,   824,   827,   828,   829,   832,
       0,   888,     0,   885,     0,     0,     0,     0,   934,     0,
     927,   930,   931,   932,   933,    53,   604,     0,   600,   601,
     684,     0,   683,     0,    62,   872,   194,     0,     0,   230,
     227,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   250,   225,   238,     0,   240,   245,     0,   377,
     382,   532,   520,   527,   571,   561,   566,     0,   463,   468,
     313,   310,   693,   690,   687,   639,   629,   634,     0,   339,
     344,     0,     0,     0,     0,     0,     0,   363,   360,     0,
       0,     0,   328,   325,     0,     0,     0,     0,     0,     0,
       0,   736,   724,     0,   726,   731,     0,     0,     0,     0,
     826,   823,   840,     0,   887,   884,     0,     0,     0,     0,
     929,   926,    55,     0,    54,     0,   598,   603,     0,   682,
     881,     0,     0,   229,     0,     0,     0,     0,   282,   285,
     286,   287,   288,   289,   290,   291,   292,   293,     0,   299,
     300,     0,     0,     0,     0,   249,     0,   244,     0,   381,
       0,   526,     0,   565,   518,   493,   494,   495,   477,   478,
     498,   499,   500,   501,   502,   516,   480,   481,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   517,   474,   475,   476,   489,   490,   491,   492,   486,
     487,   488,     0,   471,   479,   496,   497,   482,   483,   484,
     485,   467,   312,   716,   718,     0,     0,   710,   711,   712,
     713,   714,   715,   703,   704,   708,   709,   705,   706,   707,
       0,   694,   695,   698,   699,   700,   701,   702,   689,     0,
     633,     0,   343,   370,   371,   372,   373,   374,   375,   362,
     335,   336,   337,   327,     0,     0,     0,   759,     0,   760,
       0,   735,     0,   730,   833,     0,   836,     0,   825,   903,
       0,   901,   899,   893,   897,   898,     0,   890,   895,   896,
     894,   886,   935,   936,   937,   938,   928,    52,    57,     0,
     602,     0,   234,   236,   275,   277,   279,   281,   296,   297,
     298,   295,   302,   304,   306,   308,   247,   384,   529,   568,
     473,   470,     0,     0,     0,     0,   692,   697,   636,   346,
     752,   753,   754,   751,   756,   758,     0,   763,   733,   835,
     838,     0,     0,     0,   892,   889,    56,   605,   685,   472,
       0,     0,   720,   721,   696,   792,   795,   797,   799,   791,
     790,   789,     0,   782,   785,   786,   787,   788,   768,     0,
     764,   765,     0,   900,     0,   891,   717,   719,     0,     0,
       0,     0,   784,   781,     0,   762,   767,     0,   902,     0,
       0,     0,     0,   783,   778,   777,   773,   775,   776,     0,
     770,   774,   766,   908,     0,   905,   794,   793,   796,   798,
     801,     0,   772,   769,     0,   907,   904,   806,     0,   802,
     803,     0,   771,   918,     0,     0,     0,   923,     0,   910,
     913,   914,   915,   916,   917,   906,     0,   800,   805,   779,
       0,     0,     0,     0,     0,   912,   909,   818,   820,   817,
     811,   813,   815,   816,     0,   808,   812,   814,   804,     0,
     920,   921,   922,     0,   911,     0,     0,   810,   807,   919,
     924,     0,     0,   809,   819,   821
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369,   -59, -1369,  -599, -1369,   452,
   -1369, -1369, -1369, -1369, -1369, -1369,  -636, -1369, -1369, -1369,
     -67, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   482,   667,
      16,    31,    33,   -26,   -13,    13,    41,    44,    51,    54,
   -1369, -1369, -1369, -1369,    56, -1369, -1369,    59,    62,    64,
      66,    69,    74, -1369, -1369,    76, -1369,    77, -1369,    79,
      81,    82, -1369, -1369,    84,    87, -1369,    89, -1369,    92,
   -1369, -1369, -1369, -1369, -1369,    43, -1369, -1369, -1369,   434,
     665, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     186, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   383,
   -1369,   167, -1369,  -709,   174, -1369, -1369, -1368, -1369, -1347,
   -1369, -1369, -1369, -1369,   -63, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
    -741, -1369,  -740, -1369,  -737, -1369, -1369, -1369, -1369, -1369,
   -1369,   153, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
     135, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   145, -1369,
   -1369, -1369,   150,   660, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   143, -1369, -1369, -1369, -1369, -1369, -1369, -1020, -1369,
   -1369, -1369,   172, -1369, -1369, -1369,   175,   671, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1018, -1369,   -29, -1369,
     -18, -1369,     5, -1369,    71, -1369,    94,    97,    99, -1369,
   -1369, -1369, -1369, -1369,   165, -1369, -1369,   -75,   -60, -1369,
   -1369, -1369, -1369, -1369,   177, -1369, -1369, -1369,   178, -1369,
     661, -1369,   -34, -1369, -1369, -1369, -1369, -1369,   -27, -1369,
   -1369, -1369, -1369, -1369,   -32, -1369, -1369, -1369,   179, -1369,
   -1369, -1369,   180, -1369,   664, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,   109,
   -1369, -1369, -1369,   113,   673, -1369, -1369, -1369,   -44, -1369,
       3, -1369,   -56, -1369, -1369, -1369,   164, -1369, -1369, -1369,
     185, -1369,   674,   -48, -1369,    -7, -1369,    15, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1017, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   169, -1369, -1369, -1369,   -69, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   146, -1369,   149,   163, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,  -123,
   -1369, -1369,  -144, -1369, -1369, -1369, -1369, -1369,  -111, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
    -165, -1369, -1369,  -192, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   158, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369,   484,   672, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369,   531,   666, -1369, -1369, -1369, -1369, -1369, -1369,   181,
   -1369, -1369,   -64, -1369, -1369, -1369, -1369, -1369, -1369,  -131,
   -1369, -1369,  -159, -1369, -1369, -1369, -1369, -1369, -1369, -1369,
   -1369, -1369, -1369,   184, -1369, -1369, -1369, -1369
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   747,
      82,    83,    39,    64,    79,    80,   764,   985,  1093,  1094,
     838,    41,    66,    85,   435,    86,    43,    67,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   463,   171,   172,   480,   173,   174,   175,   176,
     177,   178,   179,   469,   733,   180,   470,   181,   471,   182,
     183,   184,   481,   744,   185,   186,   499,   187,   500,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   439,   235,
     236,    45,    68,   237,   509,   238,   510,   767,   239,   511,
     770,   240,   241,   242,   243,   197,   449,   198,   440,   813,
     814,   815,   997,   816,   998,   199,   450,   200,   451,   865,
     866,   867,  1025,   839,   840,   841,  1001,   842,  1002,   843,
    1003,   844,  1004,   845,   846,   548,   847,   848,   849,   850,
     851,   852,   853,   854,   855,   856,  1015,  1271,   857,   858,
     859,  1018,   860,  1019,   861,  1020,   862,  1021,   201,   488,
     889,   890,   891,   892,   893,   894,   895,   202,   494,   925,
     926,   927,   928,   929,   203,   491,   904,   905,   906,  1048,
      59,    75,   399,   400,   401,   563,   402,   564,   204,   492,
     913,   914,   915,   916,   917,   918,   919,   920,   205,   476,
     869,   870,   871,  1028,    47,    69,   286,   287,   288,   522,
     289,   518,   290,   519,   291,   520,   292,   523,   293,   528,
     294,   525,   295,   526,   296,   527,   206,   207,   208,   300,
     209,   482,   881,   882,   883,  1037,  1172,  1173,   210,   477,
      53,    72,   873,   874,   875,  1031,    55,    73,   360,   361,
     362,   363,   364,   365,   366,   547,   367,   551,   368,   550,
     369,   370,   552,   371,   211,   478,   877,   878,   879,  1034,
      57,    74,   383,   384,   385,   386,   387,   556,   388,   389,
     390,   391,   392,   393,   560,   302,   521,   987,   988,   989,
    1095,    49,    70,   318,   319,   320,   532,   321,   212,   483,
     213,   484,   214,   490,   900,   901,   902,  1045,    51,    71,
     336,   337,   338,   215,   444,   216,   445,   217,   446,   342,
     537,   343,   538,   344,   539,   345,   541,   346,   540,   347,
     543,   348,   542,   349,   536,   309,   529,   991,   992,  1098,
     218,   489,   897,   898,  1042,  1200,  1201,  1202,  1203,  1204,
    1282,  1205,  1283,  1206,  1207,   219,   220,   495,   221,   496,
     955,   956,   957,  1073,   945,   946,   947,  1064,  1293,   948,
    1065,   949,  1066,   950,   951,   952,  1070,  1329,  1330,  1331,
    1344,  1359,  1360,  1361,  1371,   953,  1068,  1322,  1323,  1324,
    1338,  1367,  1325,  1339,  1326,  1340,  1327,  1341,  1378,  1379,
    1380,  1396,  1414,  1415,  1416,  1425,  1417,  1426,   222,   497,
     964,   965,   966,   967,  1077,   968,   969,  1079,   223,   498,
      61,    76,   414,   415,   416,   417,   568,   418,   419,   570,
     420,   421,   422,   573,   804,   423,   574,   224,   438,    63,
      77,   426,   427,   428,   577,   429,   225,   504,   972,   973,
    1083,  1246,  1247,  1248,  1249,  1303,  1250,  1301,  1364,  1365,
    1374,  1388,  1389,  1390,  1400,  1391,  1392,  1393,  1394,  1404,
     226,   505,   979,   980,   981,   982,   983,   984
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   258,   312,   332,    78,   358,   379,   398,   411,
     359,   380,   350,   305,   940,   941,   863,  1163,   942,  1164,
    1180,   306,   802,   339,   244,   303,   322,   334,  1410,   372,
     394,   746,   412,   777,   778,   779,    28,   301,   317,   333,
     381,   313,   783,   262,    29,   352,    30,   382,    31,  1411,
     396,   397,   314,   436,    40,   507,   263,    81,   437,  1410,
     508,   126,   307,   797,   340,   132,   133,   728,   729,   730,
     731,   245,   304,   323,   335,   315,   373,   395,    84,   413,
    1411,   431,   264,   434,   308,   259,   341,   227,   228,  1040,
      42,   229,  1041,   516,   230,   231,   232,   233,   517,   530,
     260,   430,   261,   746,   531,    44,   732,    46,   132,   133,
     265,    48,   285,   266,   534,   974,   975,   976,   977,   535,
     267,   432,   565,   268,   575,   269,  1354,   566,   270,   576,
      50,   271,   155,   272,   155,   273,    52,   579,   274,   507,
      54,   316,   580,   275,   994,   276,   277,    56,   278,    58,
     279,   280,   351,   281,  1315,   579,   282,   516,   283,   999,
     995,   284,   996,   297,  1000,  1022,   298,    60,   299,   352,
    1023,   958,   959,   960,  1022,    62,  1057,    87,   155,  1024,
      88,  1058,   818,   819,   433,  1043,   132,   133,  1044,   132,
     133,  1084,    89,   803,  1085,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   352,  1062,   353,   354,
     441,  1071,  1063,   355,   356,   357,  1072,  1375,   544,  1383,
    1376,   961,  1384,  1385,  1386,  1387,   132,   133,   132,   133,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   132,   133,   442,   126,   127,
    1163,   443,  1164,  1180,   424,   425,    32,    33,    34,    35,
     128,   129,   130,  1268,  1269,  1270,  1239,   131,  1240,  1241,
     132,   133,  1316,  1317,  1318,   134,   135,   136,   137,   138,
     740,   741,   742,   743,    93,    94,    95,    96,   139,   155,
     396,   397,   155,   447,   884,   885,   886,   887,   140,   888,
    1080,   141,  1407,  1408,   448,  1081,  1126,   452,   142,   143,
      93,    94,    95,   144,   145,   453,   101,   102,   103,   454,
     940,   941,   940,   941,   942,   575,   942,   765,   766,   155,
    1082,   155,   146,   132,   133,   455,   147,   907,   908,   909,
     910,   911,   912,  1090,   126,   127,   352,   456,  1091,   768,
     769,   148,   149,   150,   151,   152,   153,   457,   155,  1022,
     811,   812,   581,   582,  1276,   154,   132,   133,   127,   458,
     459,   127,   530,   921,   922,   923,   460,  1277,  1183,  1184,
    1185,  1186,  1280,   155,   461,   462,   565,  1281,   310,   132,
     133,  1289,   132,   133,  1290,  1291,  1292,  1071,   253,   254,
     255,   324,  1298,  1304,   534,   256,   311,   464,  1305,  1307,
     465,   325,   326,   327,   328,   329,   330,   331,   466,   467,
     468,   352,   374,   353,   354,   375,   376,   377,  1342,  1372,
     156,  1405,  1427,  1343,  1373,   472,  1406,  1428,   473,   234,
     474,   132,   133,   475,   479,   485,   155,   486,   487,   493,
     378,   501,   502,   258,   503,   506,   512,   312,   513,   514,
     515,   524,   244,   533,   305,   545,   546,   549,   332,   553,
     555,   562,   306,   557,   554,   558,   303,   559,   358,   155,
     322,   567,   359,   561,   569,   379,   571,   339,   301,   380,
     572,   334,   317,   578,   262,   313,   583,   584,   411,   585,
     586,   372,   155,   333,   587,   155,   314,   263,   394,   245,
     588,   589,   590,   307,   591,   592,   593,   595,   381,   594,
     596,   412,   597,   304,   598,   382,   599,   323,   340,   315,
     600,   604,   601,   264,   602,   308,   259,   603,   335,   610,
     616,   605,   606,   607,   608,   609,   611,   612,   373,   617,
     341,   260,   618,   261,   155,   395,   613,   623,   614,   624,
     615,   265,   619,   285,   266,   620,   621,   625,   413,   622,
     626,   267,   627,   628,   268,   629,   269,   630,   631,   270,
     632,   633,   271,   635,   272,   634,   273,   636,   637,   274,
     638,   639,   640,   641,   275,   316,   276,   277,   642,   278,
     643,   279,   280,   644,   281,   645,   646,   282,   647,   283,
     651,   652,   284,   654,   297,  1308,   648,   298,   649,   299,
     132,   133,   650,   655,   656,   834,   835,   836,   657,   658,
     659,   662,   660,   663,   664,   665,   666,   667,   668,   669,
     156,   670,   234,   671,   672,   673,   675,   807,   817,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   827,   828,
     829,   830,   831,   676,   678,   244,   832,   833,   834,   835,
     836,   837,   679,   680,   681,   682,   683,   924,   939,   132,
     133,   411,   684,   685,   687,   978,   688,   403,   404,   405,
     406,   407,   408,   409,   410,   690,   691,   692,   689,   695,
     930,   943,   352,   962,   412,   699,   693,   701,   696,   697,
     702,   698,   245,   704,   705,   706,   707,   710,    91,    92,
      93,    94,    95,    96,   932,   708,   709,   711,   933,   934,
     935,   936,   713,   155,   716,   714,   717,   726,   937,   938,
     718,   719,   720,   724,   721,   725,   722,   931,   944,   723,
     963,   413,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   736,   737,   727,   734,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   735,   246,   247,   248,
     738,   127,   745,   739,   748,    30,   749,   750,   751,   752,
     756,   759,   155,   129,   130,   753,   754,   755,   757,   758,
     249,   761,   132,   133,   250,   251,   252,   134,   135,   136,
     762,   253,   254,   255,   763,   760,   774,   771,   256,   772,
     139,   781,   773,   806,   775,   776,   864,   780,   257,   868,
     782,   872,   784,   876,   880,   155,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   805,
     785,   786,   787,   788,   896,   789,   899,   903,   954,   971,
     986,   790,   990,   791,  1005,   792,  1006,  1007,  1008,  1009,
     793,   794,   795,   796,   798,   800,   801,  1010,  1011,  1012,
    1013,  1014,  1016,   148,   149,  1017,  1026,  1027,  1029,  1030,
    1033,  1032,  1036,  1092,  1035,  1039,  1038,  1046,  1047,  1049,
    1050,  1108,  1051,  1052,  1053,  1054,  1055,  1056,  1059,  1060,
    1061,  1067,  1069,  1076,  1075,   155,  1074,  1078,  1086,  1087,
    1088,  1089,  1097,  1262,  1096,  1110,  1101,  1100,  1099,  1102,
    1104,  1105,  1106,  1107,  1109,  1111,  1112,  1113,  1118,  1114,
    1121,  1122,  1115,  1116,  1117,  1123,  1120,  1119,  1124,  1220,
    1213,   258,  1214,  1215,   358,  1216,  1224,   379,   359,  1217,
    1134,   380,   305,  1225,  1162,  1187,  1226,  1218,   332,  1192,
     306,   398,  1193,  1221,   303,  1222,  1227,   372,  1228,  1177,
     394,  1229,  1230,  1175,  1197,   924,   301,   339,  1195,  1234,
     381,   334,   262,  1235,   939,  1174,   939,   382,  1165,  1236,
    1194,  1138,  1237,   333,  1252,   263,  1242,  1257,   930,  1166,
    1243,   307,  1258,   978,  1139,  1261,  1253,   943,   312,   943,
    1178,   304,  1263,  1254,   373,  1198,   962,   395,   340,  1244,
    1176,   264,  1167,   308,   259,  1196,  1255,  1264,   335,  1265,
    1140,   322,  1179,  1135,  1266,  1278,  1279,  1199,  1188,   260,
     341,   261,  1267,   317,  1284,   931,   313,  1272,  1136,   265,
    1137,   285,   266,  1189,   944,  1190,   944,   314,  1141,   267,
    1161,  1142,   268,   963,   269,  1191,  1245,   270,  1143,  1285,
     271,  1144,   272,  1145,   273,  1273,  1146,   274,   323,  1147,
     315,  1148,   275,  1149,   276,   277,  1150,   278,  1168,   279,
     280,  1151,   281,  1152,  1153,   282,  1154,   283,  1155,  1156,
     284,  1157,   297,  1286,  1158,   298,  1159,   299,  1287,  1160,
    1288,  1169,  1297,  1274,  1170,  1296,  1171,  1302,  1310,  1311,
    1366,  1332,  1334,  1328,  1346,  1345,  1397,  1347,  1349,  1275,
    1350,  1351,  1352,   810,   799,  1370,  1363,  1381,  1377,  1398,
    1294,  1295,  1401,  1402,  1403,  1419,   316,  1299,  1306,  1423,
    1431,  1432,  1312,  1313,   653,  1420,  1333,  1336,  1300,  1337,
    1348,   661,  1368,  1369,  1399,  1103,  1421,  1422,  1429,   993,
    1430,  1434,  1435,  1182,  1127,  1212,  1125,  1223,  1211,   808,
    1219,   674,  1129,  1128,  1181,  1309,  1260,   677,  1259,  1130,
    1131,  1210,  1208,  1134,  1132,  1133,   694,  1162,  1314,   686,
    1187,  1233,  1232,  1362,  1192,   703,   700,  1193,  1382,  1319,
    1209,  1353,  1177,  1418,  1231,  1433,  1175,  1242,  1238,  1197,
    1335,  1243,   970,  1195,  1395,   715,  1424,   712,  1174,   809,
       0,  1165,  1320,     0,  1138,  1194,     0,     0,     0,     0,
    1244,     0,  1166,     0,     0,  1251,     0,  1139,     0,     0,
       0,     0,     0,  1178,  1256,  1319,     0,  1355,     0,     0,
    1198,  1356,     0,  1176,     0,  1167,     0,     0,     0,     0,
    1196,     0,     0,  1140,     0,  1179,  1135,     0,  1320,  1321,
    1357,     0,  1199,  1188,     0,  1355,     0,  1245,     0,  1356,
       0,  1136,     0,  1137,     0,     0,     0,     0,  1189,     0,
    1190,  1141,     0,  1161,  1142,     0,     0,     0,  1357,  1409,
    1191,  1143,     0,     0,  1144,     0,  1145,     0,     0,  1146,
       0,     0,  1147,     0,  1148,  1321,  1149,  1358,     0,  1150,
       0,  1168,  1412,     0,  1151,     0,  1152,  1153,     0,  1154,
    1409,  1155,  1156,     0,  1157,     0,     0,  1158,     0,  1159,
       0,     0,  1160,     0,  1169,  1358,     0,  1170,     0,  1171,
       0,     0,     0,  1412,    91,    92,    93,    94,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1413,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
    1413,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,   127,   352,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
     130,     0,     0,     0,     0,     0,     0,     0,   132,   133,
       0,   251,     0,   134,   135,   136,     0,   253,   254,   255,
       0,     0,     0,     0,   256,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   257,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      73,    74,    72,    69,   755,   755,   725,  1037,   755,  1037,
    1037,    69,    18,    71,    68,    69,    70,    71,  1396,    73,
      74,   630,    76,   669,   670,   671,     0,    69,    70,    71,
      74,    70,   678,    69,     5,    94,     7,    74,     9,  1396,
     143,   144,    70,     3,     7,     3,    69,   227,     8,  1427,
       8,    92,    69,   699,    71,   114,   115,   191,   192,   193,
     194,    68,    69,    70,    71,    70,    73,    74,    10,    76,
    1427,     3,    69,     3,    69,    69,    71,    15,    16,     3,
       7,    19,     6,     3,    22,    23,    24,    25,     8,     3,
      69,     6,    69,   702,     8,     7,   230,     7,   114,   115,
      69,     7,    69,    69,     3,   210,   211,   212,   213,     8,
      69,     4,     3,    69,     3,    69,   175,     8,    69,     8,
       7,    69,   227,    69,   227,    69,     7,     3,    69,     3,
       7,    70,     8,    69,     8,    69,    69,     7,    69,     7,
      69,    69,    40,    69,    40,     3,    69,     3,    69,     3,
       8,    69,     8,    69,     8,     3,    69,     7,    69,    94,
       8,   177,   178,   179,     3,     7,     3,    11,   227,     8,
      14,     8,    41,    42,     8,     3,   114,   115,     6,   114,
     115,     3,    26,   189,     6,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    94,     3,    96,    97,
       4,     3,     8,   101,   102,   103,     8,     3,     8,   202,
       6,   227,   205,   206,   207,   208,   114,   115,   114,   115,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   114,   115,     4,    92,    93,
    1280,     4,  1280,  1280,    12,    13,   227,   228,   229,   230,
     104,   105,   106,    55,    56,    57,   201,   111,   203,   204,
     114,   115,   168,   169,   170,   119,   120,   121,   122,   123,
     107,   108,   109,   110,    32,    33,    34,    35,   132,   227,
     143,   144,   227,     4,   134,   135,   136,   137,   142,   139,
       3,   145,   171,   172,     4,     8,  1025,     4,   152,   153,
      32,    33,    34,   157,   158,     4,    64,    65,    66,     4,
    1071,  1071,  1073,  1073,  1071,     3,  1073,    17,    18,   227,
       8,   227,   176,   114,   115,     4,   180,   146,   147,   148,
     149,   150,   151,     3,    92,    93,    94,     4,     8,    20,
      21,   195,   196,   197,   198,   199,   200,     4,   227,     3,
      27,    28,   431,   432,     8,   209,   114,   115,    93,     4,
       4,    93,     3,   154,   155,   156,     4,     8,   126,   127,
     128,   129,     3,   227,     4,     4,     3,     8,   113,   114,
     115,     8,   114,   115,   160,   161,   162,     3,   123,   124,
     125,   123,     8,     3,     3,   130,   131,     4,     8,     8,
       4,   133,   134,   135,   136,   137,   138,   139,     4,     4,
       4,    94,    95,    96,    97,    98,    99,   100,     3,     3,
     507,     3,     3,     8,     8,     4,     8,     8,     4,   516,
       4,   114,   115,     4,     4,     4,   227,     4,     4,     4,
     123,     4,     4,   530,     4,     4,     4,   534,     4,     4,
       4,     4,   516,     4,   530,     3,     8,     4,   545,     4,
       3,     3,   530,     4,     8,     4,   530,     4,   555,   227,
     534,     4,   555,     8,     4,   562,     4,   545,   530,   562,
       4,   545,   534,     4,   530,   534,   227,     4,   575,     4,
       4,   555,   227,   545,     4,   227,   534,   530,   562,   516,
     230,   230,   230,   530,     4,     4,     4,   230,   562,   228,
       4,   575,     4,   530,     4,   562,   228,   534,   545,   534,
     228,   230,   228,   530,   228,   530,   530,   228,   545,     4,
       4,   229,   229,   229,   228,   228,   228,   228,   555,     4,
     545,   530,     4,   530,   227,   562,   230,     4,   230,     4,
     230,   530,   230,   530,   530,   230,   229,     4,   575,   230,
     228,   530,     4,     4,   530,     4,   530,     4,     4,   530,
     230,   230,   530,     4,   530,   230,   530,     4,     4,   530,
       4,     4,   228,     4,   530,   534,   530,   530,     4,   530,
       4,   530,   530,     4,   530,     4,     4,   530,     4,   530,
       4,     4,   530,     4,   530,  1261,   230,   530,   230,   530,
     114,   115,   230,     4,     4,    60,    61,    62,   230,   230,
     228,     4,   228,     4,     4,     4,     4,     4,   228,     4,
     717,     4,   719,     4,     4,     4,     4,   716,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,   228,     4,   719,    58,    59,    60,    61,
      62,    63,     4,     4,     4,     4,     4,   754,   755,   114,
     115,   758,     4,     4,     4,   762,     4,   181,   182,   183,
     184,   185,   186,   187,   188,     4,     4,     4,   228,     4,
     754,   755,    94,   757,   758,     4,   230,     4,   230,   230,
       4,   230,   719,   230,     4,   228,     4,     4,    30,    31,
      32,    33,    34,    35,   159,   228,   228,     4,   163,   164,
     165,   166,     4,   227,     4,   228,     7,     5,   173,   174,
       7,     7,     7,     7,   227,     7,   227,   754,   755,   227,
     757,   758,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     5,     5,   227,   227,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   227,    89,    90,    91,
       5,    93,     5,   227,   227,     7,     5,     5,     5,     5,
       5,   227,   227,   105,   106,     7,     7,     7,     7,     7,
     112,     5,   114,   115,   116,   117,   118,   119,   120,   121,
       7,   123,   124,   125,     5,   227,     5,   227,   130,   227,
     132,     7,   227,     5,   227,   227,     7,   227,   140,     7,
     227,     7,   227,     7,     7,   227,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   190,
     227,   227,   227,   227,     7,   227,     7,     7,     7,     7,
       7,   227,   141,   227,     4,   227,     4,     4,     4,     4,
     227,   227,   227,   227,   227,   227,   227,     4,     4,     4,
       4,     4,     4,   195,   196,     4,     6,     3,     6,     3,
       3,     6,     3,   227,     6,     3,     6,     6,     3,     6,
       3,   228,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   227,     6,     4,     4,     4,
       4,     4,     3,   227,     6,   228,     4,     6,     8,     4,
       4,     4,     4,     4,   230,   230,   228,   228,     4,   228,
       4,     4,   228,   228,   228,     4,   228,   230,     4,   230,
     228,  1028,   228,   228,  1031,   228,     4,  1034,  1031,   228,
    1037,  1034,  1028,     4,  1037,  1042,     4,   228,  1045,  1042,
    1028,  1048,  1042,   228,  1028,   228,   228,  1031,     4,  1037,
    1034,   230,     4,  1037,  1042,  1062,  1028,  1045,  1042,   230,
    1034,  1045,  1028,     4,  1071,  1037,  1073,  1034,  1037,   228,
    1042,  1037,     4,  1045,   230,  1028,  1083,     6,  1062,  1037,
    1083,  1028,     3,  1090,  1037,     4,   230,  1071,  1095,  1073,
    1037,  1028,   227,   230,  1031,  1042,  1080,  1034,  1045,  1083,
    1037,  1028,  1037,  1028,  1028,  1042,   230,   227,  1045,   227,
    1037,  1095,  1037,  1037,   227,     8,     8,  1042,  1042,  1028,
    1045,  1028,   227,  1095,     4,  1062,  1095,   227,  1037,  1028,
    1037,  1028,  1028,  1042,  1071,  1042,  1073,  1095,  1037,  1028,
    1037,  1037,  1028,  1080,  1028,  1042,  1083,  1028,  1037,     4,
    1028,  1037,  1028,  1037,  1028,   227,  1037,  1028,  1095,  1037,
    1095,  1037,  1028,  1037,  1028,  1028,  1037,  1028,  1037,  1028,
    1028,  1037,  1028,  1037,  1037,  1028,  1037,  1028,  1037,  1037,
    1028,  1037,  1028,     8,  1037,  1028,  1037,  1028,     3,  1037,
       8,  1037,     5,   227,  1037,     7,  1037,     4,     4,     4,
     167,     4,     4,     7,     3,     6,     6,     5,     4,   227,
       4,     4,     4,   719,   702,     5,     7,     4,     7,     3,
     227,   227,     4,     4,     4,     4,  1095,   227,   227,     4,
       4,     4,   230,   230,   507,   230,   228,   227,  1237,   227,
     227,   516,   227,   227,   227,   999,   228,   228,   227,   806,
     227,   227,   227,  1040,  1027,  1050,  1022,  1062,  1048,   717,
    1057,   530,  1030,  1028,  1039,  1280,  1097,   534,  1095,  1031,
    1033,  1047,  1043,  1280,  1034,  1036,   555,  1280,  1287,   545,
    1287,  1075,  1073,  1346,  1287,   565,   562,  1287,  1372,  1296,
    1045,  1342,  1280,  1398,  1071,  1427,  1280,  1304,  1080,  1287,
    1304,  1304,   758,  1287,  1375,   579,  1405,   575,  1280,   718,
      -1,  1280,  1296,    -1,  1280,  1287,    -1,    -1,    -1,    -1,
    1304,    -1,  1280,    -1,    -1,  1084,    -1,  1280,    -1,    -1,
      -1,    -1,    -1,  1280,  1090,  1342,    -1,  1344,    -1,    -1,
    1287,  1344,    -1,  1280,    -1,  1280,    -1,    -1,    -1,    -1,
    1287,    -1,    -1,  1280,    -1,  1280,  1280,    -1,  1342,  1296,
    1344,    -1,  1287,  1287,    -1,  1372,    -1,  1304,    -1,  1372,
      -1,  1280,    -1,  1280,    -1,    -1,    -1,    -1,  1287,    -1,
    1287,  1280,    -1,  1280,  1280,    -1,    -1,    -1,  1372,  1396,
    1287,  1280,    -1,    -1,  1280,    -1,  1280,    -1,    -1,  1280,
      -1,    -1,  1280,    -1,  1280,  1342,  1280,  1344,    -1,  1280,
      -1,  1280,  1396,    -1,  1280,    -1,  1280,  1280,    -1,  1280,
    1427,  1280,  1280,    -1,  1280,    -1,    -1,  1280,    -1,  1280,
      -1,    -1,  1280,    -1,  1280,  1372,    -1,  1280,    -1,  1280,
      -1,    -1,    -1,  1427,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1396,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
    1427,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    93,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,
      -1,   117,    -1,   119,   120,   121,    -1,   123,   124,   125,
      -1,    -1,    -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,
     196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,     0,     5,
       7,     9,   227,   228,   229,   230,   246,   247,   248,   253,
       7,   262,     7,   267,     7,   322,     7,   435,     7,   522,
       7,   539,     7,   471,     7,   477,     7,   501,     7,   411,
       7,   651,     7,   670,   254,   249,   263,   268,   323,   436,
     523,   540,   472,   478,   502,   412,   652,   671,   246,   255,
     256,   227,   251,   252,    10,   264,   266,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    92,    93,   104,   105,
     106,   111,   114,   115,   119,   120,   121,   122,   123,   132,
     142,   145,   152,   153,   157,   158,   176,   180,   195,   196,
     197,   198,   199,   200,   209,   227,   261,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   284,   285,   287,   288,   289,   290,   291,   292,   293,
     296,   298,   300,   301,   302,   305,   306,   308,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   336,   338,   346,
     348,   389,   398,   405,   419,   429,   457,   458,   459,   461,
     469,   495,   529,   531,   533,   544,   546,   548,   571,   586,
     587,   589,   639,   649,   668,   677,   701,    15,    16,    19,
      22,    23,    24,    25,   261,   320,   321,   324,   326,   329,
     332,   333,   334,   335,   529,   531,    89,    90,    91,   112,
     116,   117,   118,   123,   124,   125,   130,   140,   261,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   285,
     288,   289,   290,   291,   292,   293,   296,   298,   300,   301,
     302,   305,   306,   308,   310,   316,   437,   438,   439,   441,
     443,   445,   447,   449,   451,   453,   455,   457,   458,   459,
     460,   495,   516,   529,   531,   533,   544,   546,   548,   566,
     113,   131,   261,   449,   451,   453,   455,   495,   524,   525,
     526,   528,   529,   531,   123,   133,   134,   135,   136,   137,
     138,   139,   261,   495,   529,   531,   541,   542,   543,   544,
     546,   548,   550,   552,   554,   556,   558,   560,   562,   564,
     469,    40,    94,    96,    97,   101,   102,   103,   261,   365,
     479,   480,   481,   482,   483,   484,   485,   487,   489,   491,
     492,   494,   529,   531,    95,    98,    99,   100,   123,   261,
     365,   483,   489,   503,   504,   505,   506,   507,   509,   510,
     511,   512,   513,   514,   529,   531,   143,   144,   261,   413,
     414,   415,   417,   181,   182,   183,   184,   185,   186,   187,
     188,   261,   529,   531,   653,   654,   655,   656,   658,   659,
     661,   662,   663,   666,    12,    13,   672,   673,   674,   676,
       6,     3,     4,     8,     3,   265,     3,     8,   669,   319,
     339,     4,     4,     4,   545,   547,   549,     4,     4,   337,
     347,   349,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   283,     4,     4,     4,     4,     4,   294,
     297,   299,     4,     4,     4,     4,   430,   470,   496,     4,
     286,   303,   462,   530,   532,     4,     4,     4,   390,   572,
     534,   406,   420,     4,   399,   588,   590,   640,   650,   307,
     309,     4,     4,     4,   678,   702,     4,     3,     8,   325,
     327,   330,     4,     4,     4,     4,     3,     8,   442,   444,
     446,   517,   440,   448,     4,   452,   454,   456,   450,   567,
       3,     8,   527,     4,     3,     8,   565,   551,   553,   555,
     559,   557,   563,   561,     8,     3,     8,   486,   366,     4,
     490,   488,   493,     4,     8,     3,   508,     4,     4,     4,
     515,     8,     3,   416,   418,     3,     8,     4,   657,     4,
     660,     4,     4,   664,   667,     3,     8,   675,     4,     3,
       8,   246,   246,   227,     4,     4,     4,     4,   230,   230,
     230,     4,     4,     4,   228,   230,     4,     4,     4,   228,
     228,   228,   228,   228,   230,   229,   229,   229,   228,   228,
       4,   228,   228,   230,   230,   230,     4,     4,     4,   230,
     230,   229,   230,     4,     4,     4,   228,     4,     4,     4,
       4,     4,   230,   230,   230,     4,     4,     4,     4,     4,
     228,     4,     4,     4,     4,     4,     4,     4,   230,   230,
     230,     4,     4,   270,     4,     4,     4,   230,   230,   228,
     228,   321,     4,     4,     4,     4,     4,     4,   228,     4,
       4,     4,     4,     4,   438,     4,   228,   525,     4,     4,
       4,     4,     4,     4,     4,     4,   543,     4,     4,   228,
       4,     4,     4,   230,   481,     4,   230,   230,   230,     4,
     505,     4,     4,   414,   230,     4,   228,     4,   228,   228,
       4,     4,   654,     4,   228,   673,     4,     7,     7,     7,
       7,   227,   227,   227,     7,     7,     5,   227,   191,   192,
     193,   194,   230,   295,   227,   227,     5,     5,     5,   227,
     107,   108,   109,   110,   304,     5,   248,   250,   227,     5,
       5,     5,     5,     7,     7,     7,     5,     7,     7,   227,
     227,     5,     7,     5,   257,    17,    18,   328,    20,    21,
     331,   227,   227,   227,     5,   227,   227,   257,   257,   257,
     227,     7,   227,   257,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   257,   227,   250,
     227,   227,    18,   189,   665,   190,     5,   246,   269,   672,
     320,    27,    28,   340,   341,   342,   344,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    58,    59,    60,    61,    62,    63,   261,   354,
     355,   356,   358,   360,   362,   364,   365,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   379,   380,   381,
     383,   385,   387,   354,     7,   350,   351,   352,     7,   431,
     432,   433,     7,   473,   474,   475,     7,   497,   498,   499,
       7,   463,   464,   465,   134,   135,   136,   137,   139,   391,
     392,   393,   394,   395,   396,   397,     7,   573,   574,     7,
     535,   536,   537,     7,   407,   408,   409,   146,   147,   148,
     149,   150,   151,   421,   422,   423,   424,   425,   426,   427,
     428,   154,   155,   156,   261,   400,   401,   402,   403,   404,
     529,   531,   159,   163,   164,   165,   166,   173,   174,   261,
     381,   383,   385,   529,   531,   595,   596,   597,   600,   602,
     604,   605,   606,   616,     7,   591,   592,   593,   177,   178,
     179,   227,   529,   531,   641,   642,   643,   644,   646,   647,
     653,     7,   679,   680,   210,   211,   212,   213,   261,   703,
     704,   705,   706,   707,   708,   258,     7,   518,   519,   520,
     141,   568,   569,   350,     8,     8,     8,   343,   345,     3,
       8,   357,   359,   361,   363,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   377,     4,     4,   382,   384,
     386,   388,     3,     8,     8,   353,     6,     3,   434,     6,
       3,   476,     6,     3,   500,     6,     3,   466,     6,     3,
       3,     6,   575,     3,     6,   538,     6,     3,   410,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,     4,
       4,     4,     3,     8,   598,   601,   603,     4,   617,     4,
     607,     3,     8,   594,     6,     3,     4,   645,     4,   648,
       3,     8,     8,   681,     3,     6,     4,     4,     4,     4,
       3,     8,   227,   259,   260,   521,     6,     3,   570,     8,
       6,     4,     4,   341,     4,     4,     4,     4,   228,   230,
     228,   230,   228,   228,   228,   228,   228,   228,     4,   230,
     228,     4,     4,     4,     4,   355,   354,   352,   437,   433,
     479,   475,   503,   499,   261,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   285,   288,   289,   290,   291,
     292,   293,   296,   298,   300,   301,   302,   305,   306,   308,
     310,   316,   365,   429,   447,   449,   451,   453,   455,   457,
     458,   459,   467,   468,   495,   529,   531,   544,   546,   548,
     566,   465,   392,   126,   127,   128,   129,   261,   271,   272,
     273,   316,   365,   469,   495,   529,   531,   544,   546,   548,
     576,   577,   578,   579,   580,   582,   584,   585,   574,   541,
     537,   413,   409,   228,   228,   228,   228,   228,   228,   422,
     230,   228,   228,   401,     4,     4,     4,   228,     4,   230,
       4,   596,   595,   593,   230,     4,   228,     4,   642,   201,
     203,   204,   261,   365,   529,   531,   682,   683,   684,   685,
     687,   680,   230,   230,   230,   230,   704,     6,     3,   524,
     520,     4,   227,   227,   227,   227,   227,   227,    55,    56,
      57,   378,   227,   227,   227,   227,     8,     8,     8,     8,
       3,     8,   581,   583,     4,     4,     8,     3,     8,     8,
     160,   161,   162,   599,   227,   227,     7,     5,     8,   227,
     246,   688,     4,   686,     3,     8,   227,     8,   257,   468,
       4,     4,   230,   230,   578,    40,   168,   169,   170,   261,
     529,   531,   618,   619,   620,   623,   625,   627,     7,   608,
     609,   610,     4,   228,     4,   683,   227,   227,   621,   624,
     626,   628,     3,     8,   611,     6,     3,     5,   227,     4,
       4,     4,     4,   619,   175,   261,   365,   529,   531,   612,
     613,   614,   610,     7,   689,   690,   167,   622,   227,   227,
       5,   615,     3,     8,   691,     3,     6,     7,   629,   630,
     631,     4,   613,   202,   205,   206,   207,   208,   692,   693,
     694,   696,   697,   698,   699,   690,   632,     6,     3,   227,
     695,     4,     4,     4,   700,     3,     8,   171,   172,   261,
     358,   360,   529,   531,   633,   634,   635,   637,   631,     4,
     230,   228,   228,     4,   693,   636,   638,     3,     8,   227,
     227,     4,     4,   634,   227,   227
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   231,   233,   232,   234,   232,   235,   232,   236,   232,
     237,   232,   238,   232,   239,   232,   240,   232,   241,   232,
     242,   232,   243,   232,   244,   232,   245,   232,   246,   246,
     246,   246,   246,   246,   246,   247,   249,   248,   250,   251,
     251,   252,   252,   252,   254,   253,   255,   255,   256,   256,
     256,   258,   257,   259,   259,   260,   260,   260,   261,   263,
     262,   265,   264,   264,   266,   268,   267,   269,   269,   269,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     283,   282,   284,   286,   285,   287,   288,   289,   290,   291,
     292,   294,   293,   295,   295,   295,   295,   295,   297,   296,
     299,   298,   300,   301,   303,   302,   304,   304,   304,   304,
     305,   307,   306,   309,   308,   310,   311,   312,   313,   314,
     315,   316,   317,   319,   318,   320,   320,   320,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   323,   322,
     325,   324,   327,   326,   328,   328,   330,   329,   331,   331,
     332,   333,   334,   335,   337,   336,   339,   338,   340,   340,
     340,   341,   341,   343,   342,   345,   344,   347,   346,   349,
     348,   350,   350,   351,   351,   351,   353,   352,   354,   354,
     354,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   357,   356,   359,   358,   361,   360,
     363,   362,   364,   366,   365,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   377,   376,   378,   378,   378,   379,
     380,   382,   381,   384,   383,   386,   385,   388,   387,   390,
     389,   391,   391,   391,   392,   392,   392,   392,   392,   393,
     394,   395,   396,   397,   399,   398,   400,   400,   400,   401,
     401,   401,   401,   401,   401,   402,   403,   404,   406,   405,
     407,   407,   408,   408,   408,   410,   409,   412,   411,   413,
     413,   413,   413,   414,   414,   416,   415,   418,   417,   420,
     419,   421,   421,   421,   422,   422,   422,   422,   422,   422,
     423,   424,   425,   426,   427,   428,   430,   429,   431,   431,
     432,   432,   432,   434,   433,   436,   435,   437,   437,   437,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     440,   439,   442,   441,   444,   443,   446,   445,   448,   447,
     450,   449,   452,   451,   454,   453,   456,   455,   457,   458,
     459,   460,   462,   461,   463,   463,   464,   464,   464,   466,
     465,   467,   467,   467,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   468,   468,   468,   468,   468,   470,
     469,   472,   471,   473,   473,   474,   474,   474,   476,   475,
     478,   477,   479,   479,   480,   480,   480,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   482,   483,   484,
     486,   485,   488,   487,   490,   489,   491,   493,   492,   494,
     496,   495,   497,   497,   498,   498,   498,   500,   499,   502,
     501,   503,   503,   504,   504,   504,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   505,   505,   506,   508,   507,
     509,   510,   511,   512,   513,   515,   514,   517,   516,   518,
     518,   519,   519,   519,   521,   520,   523,   522,   524,   524,
     524,   525,   525,   525,   525,   525,   525,   525,   525,   525,
     525,   527,   526,   528,   530,   529,   532,   531,   534,   533,
     535,   535,   536,   536,   536,   538,   537,   540,   539,   541,
     541,   542,   542,   542,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   545,
     544,   547,   546,   549,   548,   551,   550,   553,   552,   555,
     554,   557,   556,   559,   558,   561,   560,   563,   562,   565,
     564,   567,   566,   568,   570,   569,   572,   571,   573,   573,
     573,   575,   574,   576,   576,   577,   577,   577,   578,   578,
     578,   578,   578,   578,   578,   578,   578,   578,   578,   578,
     578,   578,   578,   578,   578,   579,   581,   580,   583,   582,
     584,   585,   586,   588,   587,   590,   589,   591,   591,   592,
     592,   592,   594,   593,   595,   595,   595,   596,   596,   596,
     596,   596,   596,   596,   596,   596,   596,   596,   596,   596,
     598,   597,   599,   599,   599,   601,   600,   603,   602,   604,
     605,   607,   606,   608,   608,   609,   609,   609,   611,   610,
     612,   612,   612,   613,   613,   613,   613,   613,   615,   614,
     617,   616,   618,   618,   618,   619,   619,   619,   619,   619,
     619,   619,   621,   620,   622,   624,   623,   626,   625,   628,
     627,   629,   629,   630,   630,   630,   632,   631,   633,   633,
     633,   634,   634,   634,   634,   634,   634,   634,   636,   635,
     638,   637,   640,   639,   641,   641,   641,   642,   642,   642,
     642,   642,   642,   643,   645,   644,   646,   648,   647,   650,
     649,   652,   651,   653,   653,   653,   654,   654,   654,   654,
     654,   654,   654,   654,   654,   654,   654,   655,   657,   656,
     658,   660,   659,   661,   662,   664,   663,   665,   665,   667,
     666,   669,   668,   671,   670,   672,   672,   672,   673,   673,
     675,   674,   676,   678,   677,   679,   679,   679,   681,   680,
     682,   682,   682,   683,   683,   683,   683,   683,   683,   683,
     684,   686,   685,   688,   687,   689,   689,   689,   691,   690,
     692,   692,   692,   693,   693,   693,   693,   693,   695,   694,
     696,   697,   698,   700,   699,   702,   701,   703,   703,   703,
     704,   704,   704,   704,   704,   705,   706,   707,   708
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     3,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     0,     4,     0,     6,     1,     3,
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
  "$@66", "network_client_classes", "$@67", "require_client_classes",
  "$@68", "evaluate_additional_classes", "$@69", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "shared_networks", "$@70", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@71",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@72", "sub_option_def_list", "$@73", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@74",
  "sub_option_def", "$@75", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@76",
  "option_def_record_types", "$@77", "space", "$@78", "option_def_space",
  "option_def_encapsulate", "$@79", "option_def_array", "option_data_list",
  "$@80", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@81", "sub_option_data", "$@82",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@83",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@84", "pools_list", "$@85",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@86",
  "sub_pool4", "$@87", "pool_params", "pool_param", "pool_entry", "$@88",
  "pool_id", "user_context", "$@89", "comment", "$@90", "reservations",
  "$@91", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@92", "sub_reservation", "$@93", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@94", "server_hostname", "$@95", "boot_file_name", "$@96",
  "ip_address", "$@97", "duid", "$@98", "hw_address", "$@99",
  "client_id_value", "$@100", "circuit_id_value", "$@101", "flex_id_value",
  "$@102", "hostname", "$@103", "reservation_client_classes", "$@104",
  "relay", "$@105", "relay_map", "ip_addresses", "$@106", "client_classes",
  "$@107", "client_classes_list", "client_class_entry", "$@108",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@109",
  "client_class_template_test", "$@110", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_socket", "$@111",
  "control_sockets", "$@112", "control_socket_list",
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
    1113,  1114,  1115,  1116,  1119,  1119,  1128,  1128,  1137,  1137,
    1146,  1146,  1155,  1161,  1161,  1170,  1176,  1182,  1188,  1194,
    1200,  1206,  1212,  1218,  1224,  1224,  1232,  1233,  1234,  1237,
    1243,  1249,  1249,  1258,  1258,  1267,  1267,  1276,  1276,  1285,
    1285,  1296,  1297,  1298,  1303,  1304,  1305,  1306,  1307,  1310,
    1315,  1320,  1325,  1330,  1337,  1337,  1350,  1351,  1352,  1357,
    1358,  1359,  1360,  1361,  1362,  1365,  1371,  1377,  1383,  1383,
    1394,  1395,  1398,  1399,  1400,  1405,  1405,  1415,  1415,  1425,
    1426,  1427,  1430,  1433,  1434,  1437,  1437,  1446,  1446,  1455,
    1455,  1467,  1468,  1469,  1474,  1475,  1476,  1477,  1478,  1479,
    1482,  1488,  1494,  1500,  1506,  1512,  1521,  1521,  1535,  1536,
    1539,  1540,  1541,  1550,  1550,  1576,  1576,  1587,  1588,  1589,
    1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,  1604,
    1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,
    1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,
    1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,
    1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,
    1647,  1647,  1656,  1656,  1665,  1665,  1674,  1674,  1683,  1683,
    1692,  1692,  1702,  1702,  1714,  1714,  1725,  1725,  1736,  1742,
    1748,  1754,  1762,  1762,  1774,  1775,  1779,  1780,  1781,  1786,
    1786,  1794,  1795,  1796,  1801,  1802,  1803,  1804,  1805,  1806,
    1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,  1826,
    1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,  1835,  1836,
    1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,  1845,  1852,
    1852,  1866,  1866,  1875,  1876,  1879,  1880,  1881,  1888,  1888,
    1903,  1903,  1917,  1918,  1921,  1922,  1923,  1928,  1929,  1930,
    1931,  1932,  1933,  1934,  1935,  1936,  1937,  1940,  1942,  1948,
    1950,  1950,  1959,  1959,  1968,  1968,  1977,  1979,  1979,  1988,
    1998,  1998,  2011,  2012,  2017,  2018,  2019,  2026,  2026,  2038,
    2038,  2050,  2051,  2056,  2057,  2058,  2065,  2066,  2067,  2068,
    2069,  2070,  2071,  2072,  2073,  2074,  2075,  2078,  2080,  2080,
    2089,  2091,  2093,  2099,  2105,  2111,  2111,  2125,  2125,  2138,
    2139,  2142,  2143,  2144,  2149,  2149,  2159,  2159,  2169,  2170,
    2171,  2176,  2177,  2178,  2179,  2180,  2181,  2182,  2183,  2184,
    2185,  2188,  2188,  2197,  2203,  2203,  2228,  2228,  2258,  2258,
    2269,  2270,  2273,  2274,  2275,  2280,  2280,  2289,  2289,  2298,
    2299,  2302,  2303,  2304,  2310,  2311,  2312,  2313,  2314,  2315,
    2316,  2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,  2327,
    2327,  2336,  2336,  2345,  2345,  2354,  2354,  2363,  2363,  2372,
    2372,  2381,  2381,  2390,  2390,  2399,  2399,  2408,  2408,  2417,
    2417,  2431,  2431,  2442,  2445,  2445,  2459,  2459,  2470,  2471,
    2472,  2477,  2477,  2487,  2488,  2491,  2492,  2493,  2498,  2499,
    2500,  2501,  2502,  2503,  2504,  2505,  2506,  2507,  2508,  2509,
    2510,  2511,  2512,  2513,  2514,  2517,  2519,  2519,  2528,  2528,
    2538,  2544,  2552,  2560,  2560,  2572,  2572,  2584,  2585,  2588,
    2589,  2590,  2595,  2595,  2603,  2604,  2605,  2610,  2611,  2612,
    2613,  2614,  2615,  2616,  2617,  2618,  2619,  2620,  2621,  2622,
    2625,  2625,  2634,  2635,  2636,  2639,  2639,  2649,  2649,  2659,
    2665,  2671,  2671,  2682,  2683,  2686,  2687,  2688,  2693,  2693,
    2701,  2702,  2703,  2708,  2709,  2710,  2711,  2712,  2715,  2715,
    2726,  2726,  2739,  2740,  2741,  2746,  2747,  2748,  2749,  2750,
    2751,  2752,  2755,  2755,  2763,  2766,  2766,  2775,  2775,  2784,
    2784,  2795,  2796,  2799,  2800,  2801,  2806,  2806,  2814,  2815,
    2816,  2821,  2822,  2823,  2824,  2825,  2826,  2827,  2830,  2830,
    2839,  2839,  2850,  2850,  2863,  2864,  2865,  2870,  2871,  2872,
    2873,  2874,  2875,  2878,  2884,  2884,  2893,  2899,  2899,  2909,
    2909,  2922,  2922,  2932,  2933,  2934,  2939,  2940,  2941,  2942,
    2943,  2944,  2945,  2946,  2947,  2948,  2949,  2952,  2958,  2958,
    2967,  2973,  2973,  2982,  2988,  2994,  2994,  3003,  3004,  3007,
    3007,  3018,  3018,  3030,  3030,  3040,  3041,  3042,  3048,  3049,
    3052,  3052,  3063,  3071,  3071,  3084,  3085,  3086,  3092,  3092,
    3100,  3101,  3102,  3107,  3108,  3109,  3110,  3111,  3112,  3113,
    3116,  3122,  3122,  3131,  3131,  3142,  3143,  3144,  3149,  3149,
    3157,  3158,  3159,  3164,  3165,  3166,  3167,  3168,  3171,  3171,
    3180,  3186,  3192,  3198,  3198,  3207,  3207,  3218,  3219,  3220,
    3225,  3226,  3227,  3228,  3229,  3232,  3238,  3244,  3250
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
#line 6852 "dhcp4_parser.cc"

#line 3256 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
