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

  case 439: // $@61: %empty
#line 1646 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 440: // subnet: "subnet" $@61 ":" "constant string"
#line 1649 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2795 "dhcp4_parser.cc"
    break;

  case 441: // $@62: %empty
#line 1655 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 442: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1658 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2814 "dhcp4_parser.cc"
    break;

  case 443: // $@63: %empty
#line 1664 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 444: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1667 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 445: // $@64: %empty
#line 1673 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 446: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1676 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 447: // $@65: %empty
#line 1682 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 448: // interface: "interface" $@65 ":" "constant string"
#line 1685 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 449: // $@66: %empty
#line 1691 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc"
    break;

  case 450: // client_class: "client-class" $@66 ":" "constant string"
#line 1694 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 451: // $@67: %empty
#line 1701 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp4_parser.cc"
    break;

  case 452: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1707 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2911 "dhcp4_parser.cc"
    break;

  case 453: // $@68: %empty
#line 1712 "dhcp4_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 454: // evaluate_additional_classes: "evaluate-additional-classes" $@68 ":" list_strings
#line 1718 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 455: // reservations_global: "reservations-global" ":" "boolean"
#line 1723 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 456: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1729 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 457: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1735 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 458: // id: "id" ":" "integer"
#line 1741 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2972 "dhcp4_parser.cc"
    break;

  case 459: // $@69: %empty
#line 1749 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2984 "dhcp4_parser.cc"
    break;

  case 460: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1755 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 465: // shared_networks_list: shared_networks_list ","
#line 1768 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3001 "dhcp4_parser.cc"
    break;

  case 466: // $@70: %empty
#line 1773 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 467: // shared_network: "{" $@70 shared_network_params "}"
#line 1777 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3019 "dhcp4_parser.cc"
    break;

  case 470: // shared_network_params: shared_network_params ","
#line 1783 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3027 "dhcp4_parser.cc"
    break;

  case 515: // $@71: %empty
#line 1838 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3039 "dhcp4_parser.cc"
    break;

  case 516: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1844 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc"
    break;

  case 517: // $@72: %empty
#line 1852 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 518: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1855 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3065 "dhcp4_parser.cc"
    break;

  case 523: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1867 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3073 "dhcp4_parser.cc"
    break;

  case 524: // $@73: %empty
#line 1874 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3083 "dhcp4_parser.cc"
    break;

  case 525: // option_def_entry: "{" $@73 option_def_params "}"
#line 1878 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3095 "dhcp4_parser.cc"
    break;

  case 526: // $@74: %empty
#line 1889 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3105 "dhcp4_parser.cc"
    break;

  case 527: // sub_option_def: "{" $@74 option_def_params "}"
#line 1893 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3117 "dhcp4_parser.cc"
    break;

  case 532: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1909 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3125 "dhcp4_parser.cc"
    break;

  case 544: // code: "code" ":" "integer"
#line 1928 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3135 "dhcp4_parser.cc"
    break;

  case 546: // $@75: %empty
#line 1936 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp4_parser.cc"
    break;

  case 547: // option_def_type: "type" $@75 ":" "constant string"
#line 1939 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3154 "dhcp4_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1945 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp4_parser.cc"
    break;

  case 549: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1948 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1954 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 551: // space: "space" $@77 ":" "constant string"
#line 1957 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3192 "dhcp4_parser.cc"
    break;

  case 553: // $@78: %empty
#line 1965 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp4_parser.cc"
    break;

  case 554: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1968 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 555: // option_def_array: "array" ":" "boolean"
#line 1974 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3221 "dhcp4_parser.cc"
    break;

  case 556: // $@79: %empty
#line 1984 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 557: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1990 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp4_parser.cc"
    break;

  case 562: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2005 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3250 "dhcp4_parser.cc"
    break;

  case 563: // $@80: %empty
#line 2012 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3260 "dhcp4_parser.cc"
    break;

  case 564: // option_data_entry: "{" $@80 option_data_params "}"
#line 2016 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3269 "dhcp4_parser.cc"
    break;

  case 565: // $@81: %empty
#line 2024 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp4_parser.cc"
    break;

  case 566: // sub_option_data: "{" $@81 option_data_params "}"
#line 2028 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3288 "dhcp4_parser.cc"
    break;

  case 571: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2044 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3296 "dhcp4_parser.cc"
    break;

  case 584: // $@82: %empty
#line 2066 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp4_parser.cc"
    break;

  case 585: // option_data_data: "data" $@82 ":" "constant string"
#line 2069 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3315 "dhcp4_parser.cc"
    break;

  case 588: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2079 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3325 "dhcp4_parser.cc"
    break;

  case 589: // option_data_always_send: "always-send" ":" "boolean"
#line 2085 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3335 "dhcp4_parser.cc"
    break;

  case 590: // option_data_never_send: "never-send" ":" "boolean"
#line 2091 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3345 "dhcp4_parser.cc"
    break;

  case 591: // $@83: %empty
#line 2097 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp4_parser.cc"
    break;

  case 592: // option_data_client_classes: "client-classes" $@83 ":" list_strings
#line 2103 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 593: // $@84: %empty
#line 2111 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3378 "dhcp4_parser.cc"
    break;

  case 594: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2117 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3387 "dhcp4_parser.cc"
    break;

  case 599: // not_empty_pools_list: not_empty_pools_list ","
#line 2130 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3395 "dhcp4_parser.cc"
    break;

  case 600: // $@85: %empty
#line 2135 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3405 "dhcp4_parser.cc"
    break;

  case 601: // pool_list_entry: "{" $@85 pool_params "}"
#line 2139 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 602: // $@86: %empty
#line 2145 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3425 "dhcp4_parser.cc"
    break;

  case 603: // sub_pool4: "{" $@86 pool_params "}"
#line 2149 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 606: // pool_params: pool_params ","
#line 2157 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3443 "dhcp4_parser.cc"
    break;

  case 616: // $@87: %empty
#line 2173 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 617: // pool_entry: "pool" $@87 ":" "constant string"
#line 2176 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 618: // pool_id: "pool-id" ":" "integer"
#line 2182 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 619: // $@88: %empty
#line 2188 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3480 "dhcp4_parser.cc"
    break;

  case 620: // user_context: "user-context" $@88 ":" map_value
#line 2190 "dhcp4_parser.yy"
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
#line 3507 "dhcp4_parser.cc"
    break;

  case 621: // $@89: %empty
#line 2213 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 622: // comment: "comment" $@89 ":" "constant string"
#line 2215 "dhcp4_parser.yy"
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
#line 3544 "dhcp4_parser.cc"
    break;

  case 623: // $@90: %empty
#line 2243 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 624: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2249 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 629: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2260 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3573 "dhcp4_parser.cc"
    break;

  case 630: // $@91: %empty
#line 2265 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 631: // reservation: "{" $@91 reservation_params "}"
#line 2269 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 632: // $@92: %empty
#line 2274 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 633: // sub_reservation: "{" $@92 reservation_params "}"
#line 2278 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 638: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2289 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3619 "dhcp4_parser.cc"
    break;

  case 654: // $@93: %empty
#line 2312 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3628 "dhcp4_parser.cc"
    break;

  case 655: // next_server: "next-server" $@93 ":" "constant string"
#line 2315 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3638 "dhcp4_parser.cc"
    break;

  case 656: // $@94: %empty
#line 2321 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp4_parser.cc"
    break;

  case 657: // server_hostname: "server-hostname" $@94 ":" "constant string"
#line 2324 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3657 "dhcp4_parser.cc"
    break;

  case 658: // $@95: %empty
#line 2330 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3666 "dhcp4_parser.cc"
    break;

  case 659: // boot_file_name: "boot-file-name" $@95 ":" "constant string"
#line 2333 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3676 "dhcp4_parser.cc"
    break;

  case 660: // $@96: %empty
#line 2339 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3685 "dhcp4_parser.cc"
    break;

  case 661: // ip_address: "ip-address" $@96 ":" "constant string"
#line 2342 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3695 "dhcp4_parser.cc"
    break;

  case 662: // $@97: %empty
#line 2348 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3704 "dhcp4_parser.cc"
    break;

  case 663: // duid: "duid" $@97 ":" "constant string"
#line 2351 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 664: // $@98: %empty
#line 2357 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 665: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2360 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 666: // $@99: %empty
#line 2366 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 667: // client_id_value: "client-id" $@99 ":" "constant string"
#line 2369 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3752 "dhcp4_parser.cc"
    break;

  case 668: // $@100: %empty
#line 2375 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 669: // circuit_id_value: "circuit-id" $@100 ":" "constant string"
#line 2378 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 670: // $@101: %empty
#line 2384 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 671: // flex_id_value: "flex-id" $@101 ":" "constant string"
#line 2387 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 672: // $@102: %empty
#line 2393 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 673: // hostname: "hostname" $@102 ":" "constant string"
#line 2396 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 674: // $@103: %empty
#line 2402 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 675: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2408 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 676: // $@104: %empty
#line 2416 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3842 "dhcp4_parser.cc"
    break;

  case 677: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2422 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3851 "dhcp4_parser.cc"
    break;

  case 679: // $@105: %empty
#line 2430 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 680: // ip_addresses: "ip-addresses" $@105 ":" list_strings
#line 2436 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 681: // $@106: %empty
#line 2444 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 682: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2450 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 685: // client_classes_list: client_classes_list ","
#line 2457 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3901 "dhcp4_parser.cc"
    break;

  case 686: // $@107: %empty
#line 2462 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3911 "dhcp4_parser.cc"
    break;

  case 687: // client_class_entry: "{" $@107 client_class_params "}"
#line 2466 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3921 "dhcp4_parser.cc"
    break;

  case 692: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2478 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3929 "dhcp4_parser.cc"
    break;

  case 711: // $@108: %empty
#line 2504 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 712: // client_class_test: "test" $@108 ":" "constant string"
#line 2507 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3948 "dhcp4_parser.cc"
    break;

  case 713: // $@109: %empty
#line 2513 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3957 "dhcp4_parser.cc"
    break;

  case 714: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2516 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 715: // only_if_required: "only-if-required" ":" "boolean"
#line 2523 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 716: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2529 "dhcp4_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 3987 "dhcp4_parser.cc"
    break;

  case 717: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2537 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3997 "dhcp4_parser.cc"
    break;

  case 718: // $@110: %empty
#line 2545 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4010 "dhcp4_parser.cc"
    break;

  case 719: // control_socket: "control-socket" $@110 ":" "{" control_socket_params "}"
#line 2552 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4019 "dhcp4_parser.cc"
    break;

  case 720: // $@111: %empty
#line 2557 "dhcp4_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 721: // control_sockets: "control-sockets" $@111 ":" "[" control_socket_list "]"
#line 2564 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 726: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2575 "dhcp4_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4049 "dhcp4_parser.cc"
    break;

  case 727: // $@112: %empty
#line 2580 "dhcp4_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4059 "dhcp4_parser.cc"
    break;

  case 728: // control_socket_entry: "{" $@112 control_socket_params "}"
#line 2584 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4067 "dhcp4_parser.cc"
    break;

  case 731: // control_socket_params: control_socket_params ","
#line 2590 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4075 "dhcp4_parser.cc"
    break;

  case 745: // $@113: %empty
#line 2610 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 746: // control_socket_type: "socket-type" $@113 ":" control_socket_type_value
#line 2613 "dhcp4_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4093 "dhcp4_parser.cc"
    break;

  case 747: // control_socket_type_value: "unix"
#line 2619 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4099 "dhcp4_parser.cc"
    break;

  case 748: // control_socket_type_value: "http"
#line 2620 "dhcp4_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4105 "dhcp4_parser.cc"
    break;

  case 749: // control_socket_type_value: "https"
#line 2621 "dhcp4_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4111 "dhcp4_parser.cc"
    break;

  case 750: // $@114: %empty
#line 2624 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 751: // control_socket_name: "socket-name" $@114 ":" "constant string"
#line 2628 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 752: // $@115: %empty
#line 2634 "dhcp4_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 753: // control_socket_address: "socket-address" $@115 ":" "constant string"
#line 2638 "dhcp4_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 754: // control_socket_port: "socket-port" ":" "integer"
#line 2644 "dhcp4_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 755: // cert_required: "cert-required" ":" "boolean"
#line 2650 "dhcp4_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 756: // $@116: %empty
#line 2656 "dhcp4_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 757: // http_headers: "http-headers" $@116 ":" "[" http_header_list "]"
#line 2661 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4191 "dhcp4_parser.cc"
    break;

  case 762: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2672 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4199 "dhcp4_parser.cc"
    break;

  case 763: // $@117: %empty
#line 2677 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4209 "dhcp4_parser.cc"
    break;

  case 764: // http_header: "{" $@117 http_header_params "}"
#line 2681 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4217 "dhcp4_parser.cc"
    break;

  case 767: // http_header_params: http_header_params ","
#line 2687 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4225 "dhcp4_parser.cc"
    break;

  case 773: // $@118: %empty
#line 2699 "dhcp4_parser.yy"
             {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 774: // value: "value" $@118 ":" "constant string"
#line 2702 "dhcp4_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4244 "dhcp4_parser.cc"
    break;

  case 775: // $@119: %empty
#line 2710 "dhcp4_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 776: // authentication: "authentication" $@119 ":" "{" auth_params "}"
#line 2716 "dhcp4_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4267 "dhcp4_parser.cc"
    break;

  case 779: // auth_params: auth_params ","
#line 2725 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4275 "dhcp4_parser.cc"
    break;

  case 787: // $@120: %empty
#line 2739 "dhcp4_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 788: // auth_type: "type" $@120 ":" auth_type_value
#line 2742 "dhcp4_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4293 "dhcp4_parser.cc"
    break;

  case 789: // auth_type_value: "basic"
#line 2747 "dhcp4_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4299 "dhcp4_parser.cc"
    break;

  case 790: // $@121: %empty
#line 2750 "dhcp4_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4308 "dhcp4_parser.cc"
    break;

  case 791: // realm: "realm" $@121 ":" "constant string"
#line 2753 "dhcp4_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4318 "dhcp4_parser.cc"
    break;

  case 792: // $@122: %empty
#line 2759 "dhcp4_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4327 "dhcp4_parser.cc"
    break;

  case 793: // directory: "directory" $@122 ":" "constant string"
#line 2762 "dhcp4_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4337 "dhcp4_parser.cc"
    break;

  case 794: // $@123: %empty
#line 2768 "dhcp4_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4349 "dhcp4_parser.cc"
    break;

  case 795: // clients: "clients" $@123 ":" "[" clients_list "]"
#line 2774 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4358 "dhcp4_parser.cc"
    break;

  case 800: // not_empty_clients_list: not_empty_clients_list ","
#line 2785 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4366 "dhcp4_parser.cc"
    break;

  case 801: // $@124: %empty
#line 2790 "dhcp4_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4376 "dhcp4_parser.cc"
    break;

  case 802: // basic_auth: "{" $@124 clients_params "}"
#line 2794 "dhcp4_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4384 "dhcp4_parser.cc"
    break;

  case 805: // clients_params: clients_params ","
#line 2800 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4392 "dhcp4_parser.cc"
    break;

  case 813: // $@125: %empty
#line 2814 "dhcp4_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 814: // user_file: "user-file" $@125 ":" "constant string"
#line 2817 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 815: // $@126: %empty
#line 2823 "dhcp4_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4420 "dhcp4_parser.cc"
    break;

  case 816: // password_file: "password-file" $@126 ":" "constant string"
#line 2826 "dhcp4_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4430 "dhcp4_parser.cc"
    break;

  case 817: // $@127: %empty
#line 2834 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4442 "dhcp4_parser.cc"
    break;

  case 818: // dhcp_queue_control: "dhcp-queue-control" $@127 ":" "{" queue_control_params "}"
#line 2840 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 821: // queue_control_params: queue_control_params ","
#line 2849 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4461 "dhcp4_parser.cc"
    break;

  case 828: // enable_queue: "enable-queue" ":" "boolean"
#line 2862 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4471 "dhcp4_parser.cc"
    break;

  case 829: // $@128: %empty
#line 2868 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4480 "dhcp4_parser.cc"
    break;

  case 830: // queue_type: "queue-type" $@128 ":" "constant string"
#line 2871 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4490 "dhcp4_parser.cc"
    break;

  case 831: // capacity: "capacity" ":" "integer"
#line 2877 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4500 "dhcp4_parser.cc"
    break;

  case 832: // $@129: %empty
#line 2883 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4509 "dhcp4_parser.cc"
    break;

  case 833: // arbitrary_map_entry: "constant string" $@129 ":" value
#line 2886 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4518 "dhcp4_parser.cc"
    break;

  case 834: // $@130: %empty
#line 2893 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4530 "dhcp4_parser.cc"
    break;

  case 835: // dhcp_ddns: "dhcp-ddns" $@130 ":" "{" dhcp_ddns_params "}"
#line 2899 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4541 "dhcp4_parser.cc"
    break;

  case 836: // $@131: %empty
#line 2906 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4551 "dhcp4_parser.cc"
    break;

  case 837: // sub_dhcp_ddns: "{" $@131 dhcp_ddns_params "}"
#line 2910 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 840: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2918 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4569 "dhcp4_parser.cc"
    break;

  case 852: // enable_updates: "enable-updates" ":" "boolean"
#line 2936 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 853: // $@132: %empty
#line 2942 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4588 "dhcp4_parser.cc"
    break;

  case 854: // server_ip: "server-ip" $@132 ":" "constant string"
#line 2945 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4598 "dhcp4_parser.cc"
    break;

  case 855: // server_port: "server-port" ":" "integer"
#line 2951 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4608 "dhcp4_parser.cc"
    break;

  case 856: // $@133: %empty
#line 2957 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4617 "dhcp4_parser.cc"
    break;

  case 857: // sender_ip: "sender-ip" $@133 ":" "constant string"
#line 2960 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4627 "dhcp4_parser.cc"
    break;

  case 858: // sender_port: "sender-port" ":" "integer"
#line 2966 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4637 "dhcp4_parser.cc"
    break;

  case 859: // max_queue_size: "max-queue-size" ":" "integer"
#line 2972 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 860: // $@134: %empty
#line 2978 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4656 "dhcp4_parser.cc"
    break;

  case 861: // ncr_protocol: "ncr-protocol" $@134 ":" ncr_protocol_value
#line 2981 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4665 "dhcp4_parser.cc"
    break;

  case 862: // ncr_protocol_value: "udp"
#line 2987 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4671 "dhcp4_parser.cc"
    break;

  case 863: // ncr_protocol_value: "tcp"
#line 2988 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4677 "dhcp4_parser.cc"
    break;

  case 864: // $@135: %empty
#line 2991 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4686 "dhcp4_parser.cc"
    break;

  case 865: // ncr_format: "ncr-format" $@135 ":" "JSON"
#line 2994 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4696 "dhcp4_parser.cc"
    break;

  case 866: // $@136: %empty
#line 3002 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 867: // config_control: "config-control" $@136 ":" "{" config_control_params "}"
#line 3008 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4718 "dhcp4_parser.cc"
    break;

  case 868: // $@137: %empty
#line 3014 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4728 "dhcp4_parser.cc"
    break;

  case 869: // sub_config_control: "{" $@137 config_control_params "}"
#line 3018 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4737 "dhcp4_parser.cc"
    break;

  case 872: // config_control_params: config_control_params ","
#line 3026 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4745 "dhcp4_parser.cc"
    break;

  case 875: // $@138: %empty
#line 3036 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4757 "dhcp4_parser.cc"
    break;

  case 876: // config_databases: "config-databases" $@138 ":" "[" database_list "]"
#line 3042 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4766 "dhcp4_parser.cc"
    break;

  case 877: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3047 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4776 "dhcp4_parser.cc"
    break;

  case 878: // $@139: %empty
#line 3055 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4788 "dhcp4_parser.cc"
    break;

  case 879: // loggers: "loggers" $@139 ":" "[" loggers_entries "]"
#line 3061 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4797 "dhcp4_parser.cc"
    break;

  case 882: // loggers_entries: loggers_entries ","
#line 3070 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4805 "dhcp4_parser.cc"
    break;

  case 883: // $@140: %empty
#line 3076 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4815 "dhcp4_parser.cc"
    break;

  case 884: // logger_entry: "{" $@140 logger_params "}"
#line 3080 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4823 "dhcp4_parser.cc"
    break;

  case 887: // logger_params: logger_params ","
#line 3086 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4831 "dhcp4_parser.cc"
    break;

  case 895: // debuglevel: "debuglevel" ":" "integer"
#line 3100 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4841 "dhcp4_parser.cc"
    break;

  case 896: // $@141: %empty
#line 3106 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4850 "dhcp4_parser.cc"
    break;

  case 897: // severity: "severity" $@141 ":" "constant string"
#line 3109 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4860 "dhcp4_parser.cc"
    break;

  case 898: // $@142: %empty
#line 3115 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4872 "dhcp4_parser.cc"
    break;

  case 899: // output_options_list: "output-options" $@142 ":" "[" output_options_list_content "]"
#line 3121 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4881 "dhcp4_parser.cc"
    break;

  case 902: // output_options_list_content: output_options_list_content ","
#line 3128 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4889 "dhcp4_parser.cc"
    break;

  case 903: // $@143: %empty
#line 3133 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4899 "dhcp4_parser.cc"
    break;

  case 904: // output_entry: "{" $@143 output_params_list "}"
#line 3137 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4907 "dhcp4_parser.cc"
    break;

  case 907: // output_params_list: output_params_list ","
#line 3143 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4915 "dhcp4_parser.cc"
    break;

  case 913: // $@144: %empty
#line 3155 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4924 "dhcp4_parser.cc"
    break;

  case 914: // output: "output" $@144 ":" "constant string"
#line 3158 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4934 "dhcp4_parser.cc"
    break;

  case 915: // flush: "flush" ":" "boolean"
#line 3164 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4944 "dhcp4_parser.cc"
    break;

  case 916: // maxsize: "maxsize" ":" "integer"
#line 3170 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4954 "dhcp4_parser.cc"
    break;

  case 917: // maxver: "maxver" ":" "integer"
#line 3176 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4964 "dhcp4_parser.cc"
    break;

  case 918: // $@145: %empty
#line 3182 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4973 "dhcp4_parser.cc"
    break;

  case 919: // pattern: "pattern" $@145 ":" "constant string"
#line 3185 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4983 "dhcp4_parser.cc"
    break;

  case 920: // $@146: %empty
#line 3191 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4995 "dhcp4_parser.cc"
    break;

  case 921: // compatibility: "compatibility" $@146 ":" "{" compatibility_params "}"
#line 3197 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5004 "dhcp4_parser.cc"
    break;

  case 924: // compatibility_params: compatibility_params ","
#line 3204 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5012 "dhcp4_parser.cc"
    break;

  case 930: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3216 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5022 "dhcp4_parser.cc"
    break;

  case 931: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3222 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 5032 "dhcp4_parser.cc"
    break;

  case 932: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3228 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 5042 "dhcp4_parser.cc"
    break;

  case 933: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3234 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 5052 "dhcp4_parser.cc"
    break;


#line 5056 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1343;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     436, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343,    41,    43,    48,    50,    54,    63,
      66,    68,    78,    86,   116,   124,   161,   169, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,    43,  -136,   103,   164,   690,
      97,  1358,   110,   168,    23,    94,   287,   -98,   452,   137,
   -1343,   140,   175,   160,   181,   201,   -21, -1343,    73, -1343,
   -1343, -1343, -1343,   206,   209,   235, -1343, -1343, -1343,   238,
     270, -1343, -1343, -1343,   280,   296,   327,   335,   363,   366,
     373,   385,   386,   396,   399, -1343,   410,   411,   413,   414,
     415, -1343, -1343, -1343,   421,   424,   425,   428, -1343, -1343,
   -1343,   429, -1343, -1343, -1343, -1343, -1343,   430,   431,   432,
   -1343, -1343, -1343, -1343, -1343,   433, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,   434,   437,   438, -1343, -1343,   439, -1343,
      75, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,   440,   441,   442,   443, -1343,   101, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,   445, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   102, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343,   446, -1343, -1343, -1343, -1343, -1343,   129, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343,   244,   260, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
     315, -1343, -1343,   447, -1343, -1343, -1343,   448, -1343, -1343,
     333,   450, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,   451,   453,   454, -1343, -1343,
   -1343, -1343, -1343,   361,   456, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   144,
   -1343, -1343, -1343,   458, -1343,   459, -1343,   460,   464, -1343,
   -1343, -1343, -1343, -1343,   154, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,   465,   155, -1343, -1343, -1343,
   -1343,    43,    43, -1343,   213, -1343,   466, -1343, -1343,   468,
     469,   470,   224,   226,   230,   471,   474,   476,   253,   252,
     481,   483,   484,   262,   264,   267,   268,   269,   273,   281,
     288,   289,   279,   291,   485,   293,   294,   295,   297,   298,
     494,   519,   527,   303,   304,   308,   310,   528,   531,   534,
     314,   539,   540,   541,   542,   543,   318,   320,   322,   549,
     552,   553,   555,   556,   334,   559,   564,   565,   566,   568,
     569,   570,   345,   348,   349,   577,   578, -1343,   690, -1343,
     579,   580,   581,   356,   358,   362,   368,    97, -1343,   587,
     589,   594,   597,   599,   600,   377,   602,   604,   605,   607,
    1358, -1343,   612,   389,   110, -1343,   617,   618,   619,   620,
     623,   625,   627,   628, -1343,   168, -1343,   637,   638,   416,
     639,   641,   642,   418, -1343,    94,   659,   435,   444,   457,
     660, -1343,   287,   662,   664,   105, -1343,   461,   665,   449,
     666,   455,   462,   667,   668,   452, -1343,   669,   467,   137,
   -1343, -1343, -1343,   671,   673,   674,   675,   679, -1343, -1343,
   -1343,   472,   473,   480, -1343, -1343,   682,   686,   689, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
     482, -1343, -1343, -1343, -1343, -1343,  -129,   486,   488, -1343,
   -1343, -1343, -1343,   691,   692,   693, -1343,   490,   189,   703,
     704,   491, -1343, -1343, -1343,   707,   725,   726,   727,   728,
   -1343,   729,   730,   733,   732,   734,   506,   507, -1343, -1343,
   -1343,   735,   736, -1343,   737,   203,   337, -1343, -1343, -1343,
   -1343, -1343,   517,   518,   520,   741,   521,   524, -1343,   737,
     737,   554,   772, -1343,   557, -1343, -1343,   737,   558,   560,
     561,   562,   563,   571,   572, -1343,   573,   575, -1343,   576,
     588,   590, -1343, -1343,   591, -1343, -1343, -1343,   737, -1343,
     592,   704, -1343, -1343,   593, -1343,   596, -1343, -1343,    18,
     601, -1343,   775, -1343, -1343,    43,   690,   137,    97,   352,
   -1343, -1343, -1343,   302,   302,   779, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,   785,   786,   790, -1343, -1343,
   -1343, -1343, -1343, -1343,   799, -1343, -1343, -1343,   153,   800,
     801,   807,   258,   139,   257,   809,   197,   452, -1343, -1343,
     814,  -124, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,   817, -1343, -1343, -1343, -1343, -1343,   535,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343,   779, -1343,   157,   167,   174, -1343,
   -1343,   184, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   821,
     822,   823,   824,   825,   826,   827,   829,   830,   832, -1343,
     833,   834, -1343, -1343, -1343, -1343, -1343,   190, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343,   191, -1343,   672,   836, -1343, -1343,   835,   837, -1343,
   -1343,   838,   842, -1343, -1343,   840,   846, -1343, -1343,   844,
     848, -1343, -1343, -1343, -1343, -1343, -1343,    91, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,    92, -1343, -1343,   847,   849,
   -1343, -1343,   850,   851, -1343,   853,   854,   855,   856,   857,
     858,   211, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   859,
     860,   861, -1343,   219, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,   863, -1343,   864, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,   225, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,   865,   852, -1343,   868, -1343,   869, -1343,
   -1343, -1343,   228, -1343, -1343, -1343, -1343, -1343,   229, -1343,
     108, -1343,   870,   871,   872,   873, -1343,   247, -1343, -1343,
   -1343, -1343, -1343,   651, -1343,   874,   866, -1343, -1343,   875,
   -1343,   876, -1343, -1343, -1343,   877,   880,   352, -1343,   887,
     888,   889,   890,   670,   649,   676,   677,   678,   680,   681,
     683,   684,   685,   891,   688,   687,   892,   893,   896,   897,
     302, -1343, -1343,   302, -1343,   779,  1358, -1343,   785,    94,
   -1343,   786,   287, -1343,   790,  1462, -1343,   799,   153, -1343,
     151,   800, -1343,   168, -1343,   801,   -98, -1343,   807,   694,
     695,   696,   697,   698,   699,   258, -1343,   700,   701,   705,
     139, -1343,   898,   899,   901,   706,   906,   702,   910,   257,
   -1343,   257, -1343,   809,   708,   912,   709,   915,   197, -1343,
   -1343,   132,   814, -1343,   710,   711,   712,   713,  -124, -1343,
   -1343,   914,   918,   110, -1343,   817,   924, -1343, -1343,   717,
     718, -1343,   719,   720,   721,   722, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343,   342, -1343, -1343,   723,
     724,   731,   738, -1343,   248, -1343,   259, -1343,   923, -1343,
     927, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   261,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343,   932,   935, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343,   944,   950, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343,   946, -1343,   278, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343,   251,   742,   753, -1343,   948, -1343,   951, -1343,   305,
   -1343, -1343,   756, -1343,    43, -1343, -1343,   955, -1343, -1343,
   -1343, -1343, -1343,   306, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,   759,   307, -1343,   737, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343,  1462, -1343,   957,
     958,   760,   764, -1343,   151, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343,    11,   991, -1343, -1343, -1343,   960,   771,
     999,   132, -1343, -1343, -1343, -1343, -1343,   778,   780, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   317,
   -1343, -1343, -1343, -1343, -1343, -1343,  1007,  1012, -1343,  1011,
   -1343,   796, -1343, -1343, -1343,  1025,  1029,  1033,  1034,    11,
   -1343,    30, -1343,   991,  1036, -1343,   879,   813,   820,  1043,
   -1343,   439, -1343, -1343, -1343, -1343, -1343,   319, -1343, -1343,
   -1343,   136, -1343, -1343, -1343, -1343, -1343,  1046,    30, -1343,
     186,  1036, -1343, -1343,  1044,  1052, -1343, -1343, -1343,  1054,
    1059,  1065, -1343,   326, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343,    58, -1343,  1046,  1072,   883,   900,   904,  1076,   186,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   365, -1343,
   -1343, -1343, -1343,   902, -1343, -1343, -1343,   907, -1343,  1080,
    1097,    58, -1343, -1343, -1343,   909,   911, -1343, -1343, -1343
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,   773,    31,    28,    29,    30,    35,     3,    33,
      34,    59,     5,    65,     7,   208,     9,   385,    11,   602,
      13,   632,    15,   517,    17,   526,    19,   565,    21,   347,
      23,   836,    25,   868,    27,    46,    39,     0,     0,     0,
       0,     0,     0,   634,     0,   528,   567,     0,     0,     0,
      48,     0,    47,     0,     0,    40,     0,    61,     0,    63,
     866,   193,   226,     0,     0,     0,   654,   656,   658,     0,
       0,   224,   237,   239,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,     0,     0,     0,     0,
       0,   161,   168,   170,     0,     0,     0,     0,   376,   515,
     556,     0,   153,   174,   459,   619,   621,     0,     0,     0,
     309,   681,   623,   338,   359,     0,   324,   718,   720,   817,
     834,   181,   183,     0,     0,     0,   878,   920,     0,   138,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   104,   134,   135,    93,    94,    95,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   114,
     115,   126,   127,   128,   130,   131,   132,   136,   137,    78,
      79,   101,    80,    81,    82,   129,    86,    87,    76,   105,
     106,   107,    77,    84,    85,    99,   100,   102,    96,    97,
      98,    83,    88,    89,    90,    91,    92,   103,   113,   133,
     210,   212,   216,     0,     0,     0,     0,   207,     0,   195,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   441,
     443,   445,   593,   439,   447,     0,   451,   453,   449,   676,
     438,   390,   391,   392,   393,   394,   418,   419,   420,   421,
     422,   436,   408,   409,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   437,     0,   387,
     397,   413,   414,   415,   398,   400,   401,   402,   404,   405,
     406,   399,   395,   396,   416,   417,   403,   410,   411,   412,
     407,   616,     0,   615,   610,   611,   612,   609,     0,   604,
     607,   608,   613,   614,   674,   660,   662,   664,   668,   666,
     672,   670,   653,   647,   651,   652,     0,   635,   636,   648,
     649,   650,   644,   639,   645,   641,   642,   643,   646,   640,
       0,   546,   283,     0,   550,   548,   553,     0,   542,   543,
       0,   529,   530,   533,   545,   534,   535,   536,   552,   537,
     538,   539,   540,   541,   584,     0,     0,     0,   591,   582,
     583,   586,   587,     0,   568,   569,   572,   573,   574,   575,
     576,   577,   578,   581,   579,   580,   355,   357,   352,     0,
     349,   353,   354,     0,   853,     0,   856,     0,     0,   860,
     864,   851,   849,   850,     0,   838,   841,   842,   843,   844,
     845,   846,   847,   848,   875,     0,     0,   870,   873,   874,
      45,    50,     0,    37,    43,   774,     0,    64,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    69,    66,
       0,     0,     0,     0,     0,     0,     0,   197,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     389,   386,     0,     0,   606,   603,     0,     0,     0,     0,
       0,     0,     0,     0,   633,   638,   518,     0,     0,     0,
       0,     0,     0,     0,   527,   532,     0,     0,     0,     0,
       0,   566,   571,     0,     0,   351,   348,     0,     0,     0,
       0,     0,     0,     0,     0,   840,   837,     0,     0,   872,
     869,    49,    41,     0,     0,     0,     0,     0,   155,   156,
     157,     0,     0,     0,   191,   192,     0,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
       0,   186,   187,   158,   159,   160,     0,     0,     0,   172,
     173,   180,   185,     0,     0,     0,   152,     0,     0,     0,
       0,     0,   455,   456,   457,     0,     0,     0,     0,     0,
     717,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,     0,     0,    68,     0,     0,     0,   220,   221,   222,
     223,   196,     0,     0,     0,     0,     0,     0,   458,     0,
       0,     0,     0,   388,     0,   618,   605,     0,     0,     0,
       0,     0,     0,     0,     0,   637,     0,     0,   544,     0,
       0,     0,   555,   531,     0,   588,   589,   590,     0,   570,
       0,     0,   350,   852,     0,   855,     0,   858,   859,     0,
       0,   839,     0,   877,   871,     0,     0,     0,     0,     0,
     655,   657,   659,     0,     0,   241,   151,   163,   164,   165,
     166,   167,   162,   169,   171,   378,   519,   558,   154,   176,
     177,   178,   179,   175,   461,    38,   620,   622,     0,     0,
     625,   340,     0,     0,     0,   722,     0,     0,   182,   184,
       0,     0,    51,   211,   214,   215,   213,   218,   219,   217,
     442,   444,   446,   595,   440,   448,   452,   454,   450,     0,
     617,   675,   661,   663,   665,   669,   667,   673,   671,   547,
     284,   551,   549,   554,   585,   592,   356,   358,   854,   857,
     862,   863,   861,   865,   241,    42,     0,     0,     0,   233,
     235,     0,   228,   231,   232,   274,   276,   278,   280,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   294,
       0,     0,   301,   303,   305,   307,   273,     0,   248,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,     0,   246,     0,   242,   243,   383,     0,   379,   380,
     524,     0,   520,   521,   563,     0,   559,   560,   466,     0,
     462,   463,   319,   320,   321,   322,   323,     0,   311,   314,
     315,   316,   317,   318,   686,     0,   683,   630,     0,   626,
     627,   345,     0,   341,   342,     0,     0,     0,     0,     0,
       0,     0,   361,   364,   365,   366,   367,   368,   369,     0,
       0,     0,   334,     0,   326,   329,   330,   331,   332,   333,
     745,   750,   752,     0,   775,     0,   756,   744,   737,   738,
     739,   742,   743,     0,   729,   732,   733,   734,   735,   740,
     741,   736,   727,     0,   723,   724,     0,   829,     0,   832,
     825,   826,     0,   819,   822,   823,   824,   827,     0,   883,
       0,   880,     0,     0,     0,     0,   929,     0,   922,   925,
     926,   927,   928,    53,   600,     0,   596,   597,   679,     0,
     678,     0,    62,   867,   194,     0,     0,   230,   227,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     250,   225,   238,     0,   240,   245,     0,   377,   382,   528,
     516,   523,   567,   557,   562,     0,   460,   465,   313,   310,
     688,   685,   682,   634,   624,   629,     0,   339,   344,     0,
       0,     0,     0,     0,     0,   363,   360,     0,     0,     0,
     328,   325,     0,     0,     0,     0,     0,     0,     0,   731,
     719,     0,   721,   726,     0,     0,     0,     0,   821,   818,
     835,     0,   882,   879,     0,     0,     0,     0,   924,   921,
      55,     0,    54,     0,   594,   599,     0,   677,   876,     0,
       0,   229,     0,     0,     0,     0,   282,   285,   286,   287,
     288,   289,   290,   291,   292,   293,     0,   299,   300,     0,
       0,     0,     0,   249,     0,   244,     0,   381,     0,   522,
       0,   561,   514,   489,   490,   491,   474,   475,   494,   495,
     496,   497,   498,   512,   477,   478,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   513,
     471,   472,   473,   486,   487,   488,   483,   484,   485,     0,
     468,   476,   492,   493,   479,   480,   481,   482,   464,   312,
     711,   713,     0,     0,   705,   706,   707,   708,   709,   710,
     698,   699,   703,   704,   700,   701,   702,     0,   689,   690,
     693,   694,   695,   696,   697,   684,     0,   628,     0,   343,
     370,   371,   372,   373,   374,   375,   362,   335,   336,   337,
     327,     0,     0,     0,   754,     0,   755,     0,   730,     0,
     725,   828,     0,   831,     0,   820,   898,     0,   896,   894,
     888,   892,   893,     0,   885,   890,   891,   889,   881,   930,
     931,   932,   933,   923,    52,    57,     0,   598,     0,   234,
     236,   275,   277,   279,   281,   296,   297,   298,   295,   302,
     304,   306,   308,   247,   384,   525,   564,   470,   467,     0,
       0,     0,     0,   687,   692,   631,   346,   747,   748,   749,
     746,   751,   753,     0,   758,   728,   830,   833,     0,     0,
       0,   887,   884,    56,   601,   680,   469,     0,     0,   715,
     716,   691,   787,   790,   792,   794,   786,   785,   784,     0,
     777,   780,   781,   782,   783,   763,     0,   759,   760,     0,
     895,     0,   886,   712,   714,     0,     0,     0,     0,   779,
     776,     0,   757,   762,     0,   897,     0,     0,     0,     0,
     778,    31,   769,   772,   768,   770,   771,     0,   765,   761,
     903,     0,   900,   789,   788,   791,   793,   796,   767,   764,
       0,   902,   899,   801,     0,   797,   798,   766,   913,     0,
       0,     0,   918,     0,   905,   908,   909,   910,   911,   912,
     901,     0,   795,   800,     0,     0,     0,     0,     0,   907,
     904,   813,   815,   812,   806,   808,   810,   811,     0,   803,
     807,   809,   799,     0,   915,   916,   917,     0,   906,     0,
       0,   805,   802,   914,   919,     0,     0,   804,   814,   816
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343,    -5, -1343,  -574, -1343,   426,
   -1343, -1343, -1343, -1343, -1343, -1343,  -639, -1343, -1343, -1343,
     -69, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   423,   629,
     -39,    31,    46,   -59,   -31,   -18,     6,    25,    57,    59,
   -1343, -1343, -1343, -1343,    62, -1343, -1343,    64,    65,    67,
      69,    70,    72, -1343, -1343,    77, -1343,    80, -1343,    82,
      83,    84, -1343, -1343,    85,    88, -1343,    90, -1343,    95,
   -1343, -1343, -1343, -1343, -1343,    47, -1343, -1343, -1343,   422,
     624, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
     145, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   339,
   -1343,   119, -1343,  -707,   125, -1343, -1343, -1342, -1343, -1337,
   -1343, -1343, -1343, -1343,   -47, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
    -743, -1343,  -739, -1343,  -731, -1343, -1343, -1343, -1343, -1343,
   -1343,   109, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
      89, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   104, -1343,
   -1343, -1343,   107,   583, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343,    99, -1343, -1343, -1343, -1343, -1343, -1343, -1009, -1343,
   -1343, -1343,   118, -1343, -1343, -1343,   130,   621, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1002, -1343,   -67, -1343,
     -25, -1343,   -14, -1343,    96,    98,   100, -1343, -1343, -1343,
   -1343, -1343,   113, -1343, -1343,  -122,   -61, -1343, -1343, -1343,
   -1343, -1343,   126, -1343, -1343, -1343,   131, -1343,   603, -1343,
     -62, -1343, -1343, -1343, -1343, -1343,   -60, -1343, -1343, -1343,
   -1343, -1343,   -29, -1343, -1343, -1343,   127, -1343, -1343, -1343,
     133, -1343,   606, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343,    71, -1343, -1343,
   -1343,    74,   630, -1343, -1343, -1343,   -51, -1343,    -4, -1343,
     -53, -1343, -1343, -1343,   114, -1343, -1343, -1343,   120, -1343,
     626,     9, -1343,    19, -1343,    35, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1001, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343,   121, -1343, -1343, -1343,  -115, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
     106, -1343,   111,   112, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343,  -173, -1343, -1343,
    -196, -1343, -1343, -1343, -1343,  -166, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343,  -219, -1343, -1343,
    -246, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   115, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   419,
     608, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,   463,   598,
   -1343, -1343, -1343, -1343, -1343, -1343,   117, -1343, -1343,  -123,
   -1343, -1343, -1343, -1343, -1343, -1343,  -187, -1343, -1343,  -214,
   -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343, -1343,
     123, -1343, -1343, -1343, -1343
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,  1352,    38,    39,    66,   746,
      84,    85,    40,    65,    81,    82,   763,   983,  1091,  1092,
     836,    42,    68,    88,   436,    89,    44,    69,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   464,   174,   175,   481,   176,   177,   178,   179,
     180,   181,   182,   470,   732,   183,   471,   184,   472,   185,
     186,   187,   482,   743,   188,   189,   500,   190,   501,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   440,   238,
     239,    46,    70,   240,   510,   241,   511,   766,   242,   512,
     769,   243,   244,   245,   246,   200,   450,   201,   441,   811,
     812,   813,   995,   814,   996,   202,   451,   203,   452,   863,
     864,   865,  1023,   837,   838,   839,   999,   840,  1000,   841,
    1001,   842,  1002,   843,   844,   548,   845,   846,   847,   848,
     849,   850,   851,   852,   853,   854,  1013,  1268,   855,   856,
     857,  1016,   858,  1017,   859,  1018,   860,  1019,   204,   489,
     887,   888,   889,   890,   891,   892,   893,   205,   495,   923,
     924,   925,   926,   927,   206,   492,   902,   903,   904,  1046,
      60,    77,   399,   400,   401,   563,   402,   564,   207,   493,
     911,   912,   913,   914,   915,   916,   917,   918,   208,   477,
     867,   868,   869,  1026,    48,    71,   288,   289,   290,   523,
     291,   519,   292,   520,   293,   521,   294,   524,   295,   528,
     296,   526,   297,   527,   209,   210,   211,   301,   212,   483,
     879,   880,   881,  1035,  1169,  1170,   213,   478,    54,    74,
     871,   872,   873,  1029,    56,    75,   360,   361,   362,   363,
     364,   365,   366,   547,   367,   551,   368,   550,   369,   370,
     552,   371,   214,   479,   875,   876,   877,  1032,    58,    76,
     383,   384,   385,   386,   387,   556,   388,   389,   390,   391,
     392,   393,   560,   303,   522,   985,   986,   987,  1093,    50,
      72,   318,   319,   320,   532,   321,   215,   484,   216,   485,
     217,   491,   898,   899,   900,  1043,    52,    73,   336,   337,
     338,   218,   445,   219,   446,   220,   447,   342,   537,   343,
     538,   344,   539,   345,   541,   346,   540,   347,   543,   348,
     542,   349,   536,   310,   529,   989,   990,  1096,   221,   490,
     895,   896,  1040,  1197,  1198,  1199,  1200,  1201,  1279,  1202,
    1280,  1203,  1204,   222,   223,   496,   224,   497,   953,   954,
     955,  1071,   943,   944,   945,  1062,  1290,   946,  1063,   947,
    1064,   948,   949,   950,  1068,  1326,  1327,  1328,  1341,  1357,
    1358,    67,   951,  1066,  1319,  1320,  1321,  1335,  1364,  1322,
    1336,  1323,  1337,  1324,  1338,  1374,  1375,  1376,  1391,  1408,
    1409,  1410,  1419,  1411,  1420,   225,   498,   962,   963,   964,
     965,  1075,   966,   967,  1077,   226,   499,    62,    78,   414,
     415,   416,   417,   568,   418,   419,   570,   420,   421,   422,
     573,   802,   423,   574,   227,   439,    64,    79,   426,   427,
     428,   577,   429,   228,   505,   970,   971,  1081,  1243,  1244,
    1245,  1246,  1300,  1247,  1298,  1361,  1362,  1370,  1383,  1384,
    1385,  1394,  1386,  1387,  1388,  1389,  1398,   229,   506,   977,
     978,   979,   980,   981,   982
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     159,   237,   260,   313,   332,   314,   358,   379,   398,   411,
      37,   938,   264,   350,   381,   939,   382,   861,   306,   247,
     304,   322,   334,   940,   372,   394,  1161,   412,   359,   380,
     776,   777,   261,  1162,  1177,    29,   800,    30,   781,    31,
     265,    28,   302,   317,   333,   396,   397,   315,    29,  1404,
      30,  1312,    31,   266,  1405,    41,   745,    43,   316,   795,
      80,    45,   727,   728,   729,   730,   248,   305,   323,   335,
      47,   373,   395,    49,   413,    51,   437,   267,   508,  1404,
     307,   438,   339,   509,  1405,    53,   972,   973,   974,   975,
     308,    83,   340,    55,  1038,  1041,   268,  1039,  1042,   816,
     817,   731,   262,   158,   517,   530,   309,    86,   341,   518,
     531,  1082,   230,   231,  1083,   129,   232,   263,   287,   233,
     234,   235,   236,    57,   352,   135,   136,   745,   269,   158,
     270,    59,   534,   271,   351,   272,   273,   535,   274,  1371,
     275,   276,  1372,   277,   135,   136,   430,   565,   278,   424,
     425,   279,   566,   280,   281,   282,   283,   575,   579,   284,
     508,   285,   576,   580,   432,   992,   286,   298,    61,   299,
     579,   300,   135,   136,    87,   993,    63,   517,   431,  1313,
    1314,  1315,   994,    96,    97,    98,    99,   997,   352,   433,
     353,   354,   998,  1020,  1020,   355,   356,   357,  1021,  1022,
      96,    97,    98,   130,   434,    32,   435,   801,   135,   136,
     442,   135,   136,   443,  1055,   104,   105,   106,    32,  1056,
     764,   765,  1060,   311,   135,   136,   352,  1061,  1069,  1401,
    1402,  1078,   575,  1070,   256,   257,  1079,  1080,   158,   444,
     258,   312,   448,   129,   130,   352,   135,   136,   396,   397,
    1088,  1020,   544,   135,   136,  1089,  1273,  1351,    34,    35,
      36,   130,   530,   545,  1277,   135,   136,  1274,  1161,  1278,
      33,    34,    35,    36,   449,  1162,  1177,  1180,  1181,  1182,
    1183,   565,   135,   136,   453,   158,  1286,   882,   883,   884,
     885,   324,   886,   919,   920,   921,   739,   740,   741,   742,
     454,   325,   326,   327,   328,   329,   330,   331,  1069,  1301,
     534,   135,   136,  1295,  1302,  1304,  1124,   832,   833,   834,
    1339,   158,  1368,   546,   158,  1340,   938,  1369,   938,  1399,
     939,   455,   939,  1236,  1400,  1237,  1238,   158,   940,   456,
     940,   554,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   767,   768,   158,
     830,   831,   832,   833,   834,   835,   158,   457,  1421,   561,
     458,   135,   136,  1422,   956,   957,   958,   459,   158,   809,
     810,   352,   374,   353,   354,   375,   376,   377,  1378,   460,
     461,  1379,  1380,  1381,  1382,   158,   352,  1265,  1266,  1267,
     462,   135,   136,   463,   905,   906,   907,   908,   909,   910,
     378,  1287,  1288,  1289,   465,   466,   930,   467,   468,   469,
     931,   932,   933,   934,   959,   473,   581,   582,   474,   475,
     935,   936,   476,   480,   486,   487,   488,   494,   502,   159,
     583,   503,   504,   507,   513,   514,   515,   516,   237,   525,
     533,   549,   553,   555,   588,   557,   589,   558,   559,   562,
     590,   260,   567,   569,   571,   313,   247,   314,   572,   578,
     584,   264,   585,   586,   587,   591,   332,   306,   592,   304,
     593,   594,   595,   322,   158,   596,   358,   597,   598,   610,
     599,   261,   600,   379,   334,   601,   602,   603,   616,   265,
     381,   302,   382,   604,   372,   317,   411,   608,   359,   315,
     605,   394,   266,   248,   158,   380,   333,   606,   607,   609,
     316,   611,   612,   617,   412,   613,   305,   614,   615,   158,
     323,   618,   623,   619,   620,   624,   267,   621,   625,   307,
     622,   335,   626,   627,   628,   629,   630,   631,   632,   308,
     633,   373,   634,   635,   339,   268,   636,   637,   395,   638,
     639,   262,   640,   641,   340,   309,   135,   136,   642,   643,
     644,   413,   645,   646,   647,   648,   263,   287,   649,   650,
     341,   651,   652,   654,   655,   656,   657,   269,   658,   270,
     659,   662,   271,   663,   272,   273,   660,   274,   664,   275,
     276,   665,   277,   666,   667,   668,   669,   278,   670,   671,
     279,   672,   280,   281,   282,   283,   674,   675,   284,  1305,
     285,   677,   678,   679,   680,   286,   298,   681,   299,   682,
     300,   683,   684,   403,   404,   405,   406,   407,   408,   409,
     410,   686,   687,   689,   688,   690,   691,   159,   692,   237,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   694,   698,   695,   700,   247,   701,   704,
     706,   709,   710,   712,   696,   715,   988,   705,  1024,   158,
     716,   717,   718,   707,   922,   937,   719,   697,   411,   723,
     708,   703,   976,   724,   725,   713,   735,   736,   737,   720,
     721,    90,   928,   941,    91,   960,   412,   722,   744,   726,
     805,    30,   748,   733,   248,   734,    92,   738,   747,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     749,   750,   751,   758,   759,   752,   753,   754,   755,   756,
     760,   757,   762,   761,   770,   771,   773,   772,   774,   929,
     942,   775,   961,   413,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   779,
     804,   778,   129,   130,   780,   782,   862,   783,   784,   785,
     786,   803,   866,   870,   131,   132,   133,   874,   787,   788,
     789,   134,   790,   791,   135,   136,   878,   894,   897,   137,
     138,   139,   140,   141,   901,   792,   952,   793,   794,   796,
     798,   969,   142,   799,   984,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,   143,  1010,  1011,   144,  1012,  1014,  1015,  1025,
    1028,  1027,   145,   146,  1030,  1031,  1033,   147,   148,  1034,
    1036,  1037,  1045,  1044,  1048,  1073,  1047,  1049,  1050,  1051,
    1052,  1053,  1054,  1057,  1058,  1059,   149,  1065,  1067,  1095,
     150,  1072,  1074,  1076,  1084,  1085,  1086,  1087,  1090,  1107,
    1094,  1099,  1098,  1097,  1100,   151,   152,   153,   154,   155,
     156,  1102,  1103,  1104,  1105,  1116,  1119,  1120,  1106,   157,
    1121,  1122,  1221,  1222,  1108,  1223,  1110,  1109,  1111,  1112,
    1225,  1113,  1114,  1115,  1227,  1118,  1232,   158,  1117,  1234,
    1254,  1255,  1210,  1211,  1212,  1213,  1214,  1215,  1258,  1218,
    1217,  1275,  1226,  1219,  1224,  1276,  1281,  1233,  1231,  1282,
    1249,  1250,  1251,  1252,  1259,  1260,  1261,  1262,  1263,  1264,
    1269,  1270,  1283,  1284,  1285,  1293,  1294,   260,  1271,  1299,
     358,  1307,  1308,   379,  1329,  1272,  1132,   264,  1163,  1291,
     381,  1184,   382,   306,   332,   304,  1136,   398,   372,  1190,
    1292,   394,   359,  1296,  1172,   380,  1303,   261,  1160,  1192,
    1309,   922,   334,  1189,  1310,   265,  1133,   302,  1325,  1330,
     937,  1185,   937,  1331,  1137,  1333,  1171,  1334,   266,   928,
    1164,  1191,  1239,  1342,   333,  1343,  1344,  1138,   941,   976,
     941,  1165,   305,  1345,   313,   373,   314,   960,   395,  1346,
    1241,  1173,   267,  1347,  1240,   307,  1193,  1348,  1349,   335,
    1365,  1139,   322,  1360,  1174,   308,  1363,  1366,  1367,  1194,
    1392,   268,   339,  1373,  1175,  1393,   929,   262,  1395,  1195,
    1140,   309,   340,  1396,   317,   942,  1134,   942,   315,  1397,
    1176,  1186,   263,   287,   961,  1196,  1413,  1242,   341,   316,
    1417,  1135,  1159,   269,  1425,   270,  1187,  1188,   271,   323,
     272,   273,  1141,   274,  1142,   275,   276,  1143,   277,  1144,
    1145,  1426,  1146,   278,  1147,  1148,   279,  1149,   280,   281,
     282,   283,  1150,  1414,   284,  1151,   285,  1152,  1153,  1154,
    1155,   286,   298,  1156,   299,  1157,   300,   797,  1415,  1423,
    1158,  1166,  1416,  1167,  1424,  1168,  1428,   653,  1429,   806,
     808,   661,  1101,   991,  1125,  1123,  1127,  1179,   702,  1220,
    1178,   673,  1209,  1208,  1216,  1306,  1126,  1129,   693,  1207,
    1128,  1131,  1205,  1206,   676,  1130,  1257,  1256,   699,  1311,
    1359,   685,  1377,  1350,  1412,  1427,   968,   714,  1332,  1230,
     807,  1228,  1229,   711,  1390,  1418,     0,     0,     0,     0,
       0,     0,     0,  1235,     0,     0,     0,     0,     0,  1248,
       0,     0,     0,     0,     0,     0,     0,     0,  1132,     0,
    1163,  1253,     0,     0,     0,  1184,     0,     0,  1136,     0,
       0,     0,     0,  1190,  1316,     0,  1172,     0,     0,  1297,
    1160,     0,  1239,  1192,     0,     0,     0,  1189,  1133,     0,
       0,     0,  1317,     0,     0,  1185,  1137,     0,  1171,     0,
    1241,     0,  1164,     0,  1240,  1191,     0,     0,     0,  1138,
       0,     0,     0,  1165,     0,     0,     0,     0,     0,     0,
    1316,     0,  1353,  1173,     0,     0,     0,     0,     0,     0,
    1193,     0,     0,  1139,     0,     0,  1174,     0,  1317,  1318,
    1355,     0,     0,  1194,  1354,     0,  1175,  1242,     0,  1353,
       0,     0,  1140,  1195,     0,     0,     0,     0,  1134,     0,
       0,     0,  1176,     0,     0,  1186,     0,  1355,     0,  1196,
       0,  1354,  1403,  1135,  1159,     0,     0,     0,     0,     0,
    1187,  1188,     0,     0,  1141,  1318,  1142,  1356,     0,  1143,
    1406,  1144,  1145,     0,  1146,     0,  1147,  1148,     0,  1149,
       0,     0,  1403,     0,  1150,     0,     0,  1151,     0,  1152,
    1153,  1154,  1155,     0,  1356,  1156,     0,  1157,     0,     0,
    1406,     0,  1158,  1166,     0,  1167,     0,  1168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1407,    94,    95,
      96,    97,    98,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1407,     0,     0,
       0,     0,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,   249,   250,   251,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   132,   133,     0,     0,     0,     0,     0,
     252,     0,   135,   136,   253,   254,   255,   137,   138,   139,
       0,     0,   256,   257,     0,     0,     0,     0,   258,     0,
     142,     0,    94,    95,    96,    97,    98,    99,   259,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,     0,     0,   151,   152,   130,   352,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,   133,     0,
       0,     0,     0,     0,     0,     0,   135,   136,     0,   254,
       0,   137,   138,   139,     0,   158,   256,   257,     0,     0,
       0,     0,   258,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   259,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      69,    70,    71,    72,    73,    72,    75,    76,    77,    78,
      15,   754,    71,    74,    76,   754,    76,   724,    71,    70,
      71,    72,    73,   754,    75,    76,  1035,    78,    75,    76,
     669,   670,    71,  1035,  1035,     5,    18,     7,   677,     9,
      71,     0,    71,    72,    73,   143,   144,    72,     5,  1391,
       7,    40,     9,    71,  1391,     7,   630,     7,    72,   698,
      65,     7,   191,   192,   193,   194,    70,    71,    72,    73,
       7,    75,    76,     7,    78,     7,     3,    71,     3,  1421,
      71,     8,    73,     8,  1421,     7,   210,   211,   212,   213,
      71,   227,    73,     7,     3,     3,    71,     6,     6,    41,
      42,   230,    71,   227,     3,     3,    71,     4,    73,     8,
       8,     3,    15,    16,     6,    92,    19,    71,    71,    22,
      23,    24,    25,     7,    94,   114,   115,   701,    71,   227,
      71,     7,     3,    71,    40,    71,    71,     8,    71,     3,
      71,    71,     6,    71,   114,   115,     6,     3,    71,    12,
      13,    71,     8,    71,    71,    71,    71,     3,     3,    71,
       3,    71,     8,     8,     4,     8,    71,    71,     7,    71,
       3,    71,   114,   115,    10,     8,     7,     3,     3,   168,
     169,   170,     8,    32,    33,    34,    35,     3,    94,     8,
      96,    97,     8,     3,     3,   101,   102,   103,     8,     8,
      32,    33,    34,    93,     3,   175,   227,   189,   114,   115,
       4,   114,   115,     4,     3,    64,    65,    66,   175,     8,
      17,    18,     3,   113,   114,   115,    94,     8,     3,   171,
     172,     3,     3,     8,   124,   125,     8,     8,   227,     4,
     130,   131,     4,    92,    93,    94,   114,   115,   143,   144,
       3,     3,     8,   114,   115,     8,     8,   227,   228,   229,
     230,    93,     3,     3,     3,   114,   115,     8,  1277,     8,
     227,   228,   229,   230,     4,  1277,  1277,   126,   127,   128,
     129,     3,   114,   115,     4,   227,     8,   134,   135,   136,
     137,   123,   139,   154,   155,   156,   107,   108,   109,   110,
       4,   133,   134,   135,   136,   137,   138,   139,     3,     3,
       3,   114,   115,     8,     8,     8,  1023,    60,    61,    62,
       3,   227,     3,     8,   227,     8,  1069,     8,  1071,     3,
    1069,     4,  1071,   201,     8,   203,   204,   227,  1069,     4,
    1071,     8,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    20,    21,   227,
      58,    59,    60,    61,    62,    63,   227,     4,     3,     8,
       4,   114,   115,     8,   177,   178,   179,     4,   227,    27,
      28,    94,    95,    96,    97,    98,    99,   100,   202,     4,
       4,   205,   206,   207,   208,   227,    94,    55,    56,    57,
       4,   114,   115,     4,   146,   147,   148,   149,   150,   151,
     123,   160,   161,   162,     4,     4,   159,     4,     4,     4,
     163,   164,   165,   166,   227,     4,   431,   432,     4,     4,
     173,   174,     4,     4,     4,     4,     4,     4,     4,   508,
     227,     4,     4,     4,     4,     4,     4,     4,   517,     4,
       4,     4,     4,     3,   230,     4,   230,     4,     4,     3,
     230,   530,     4,     4,     4,   534,   517,   534,     4,     4,
       4,   530,     4,     4,     4,     4,   545,   530,     4,   530,
       4,   228,   230,   534,   227,     4,   555,     4,     4,     4,
     228,   530,   228,   562,   545,   228,   228,   228,     4,   530,
     562,   530,   562,   230,   555,   534,   575,   228,   555,   534,
     229,   562,   530,   517,   227,   562,   545,   229,   229,   228,
     534,   228,   228,     4,   575,   230,   530,   230,   230,   227,
     534,     4,     4,   230,   230,     4,   530,   229,     4,   530,
     230,   545,   228,     4,     4,     4,     4,     4,   230,   530,
     230,   555,   230,     4,   545,   530,     4,     4,   562,     4,
       4,   530,   228,     4,   545,   530,   114,   115,     4,     4,
       4,   575,     4,     4,     4,   230,   530,   530,   230,   230,
     545,     4,     4,     4,     4,     4,   230,   530,   230,   530,
     228,     4,   530,     4,   530,   530,   228,   530,     4,   530,
     530,     4,   530,     4,     4,   228,     4,   530,     4,     4,
     530,     4,   530,   530,   530,   530,     4,   228,   530,  1258,
     530,     4,     4,     4,     4,   530,   530,     4,   530,     4,
     530,     4,     4,   181,   182,   183,   184,   185,   186,   187,
     188,     4,     4,     4,   228,     4,     4,   716,   230,   718,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,     4,     4,   230,     4,   718,     4,     4,
       4,     4,     4,     4,   230,     4,   141,   228,     6,   227,
       7,     7,     7,   228,   753,   754,     7,   230,   757,     7,
     228,   230,   761,     7,     5,   228,     5,     5,     5,   227,
     227,    11,   753,   754,    14,   756,   757,   227,     5,   227,
     715,     7,     5,   227,   718,   227,    26,   227,   227,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       5,     5,     5,   227,   227,     7,     7,     7,     5,     7,
       5,     7,     5,     7,   227,   227,     5,   227,   227,   753,
     754,   227,   756,   757,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     7,
       5,   227,    92,    93,   227,   227,     7,   227,   227,   227,
     227,   190,     7,     7,   104,   105,   106,     7,   227,   227,
     227,   111,   227,   227,   114,   115,     7,     7,     7,   119,
     120,   121,   122,   123,     7,   227,     7,   227,   227,   227,
     227,     7,   132,   227,     7,     4,     4,     4,     4,     4,
       4,     4,   142,     4,     4,   145,     4,     4,     4,     3,
       3,     6,   152,   153,     6,     3,     6,   157,   158,     3,
       6,     3,     3,     6,     3,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   176,     4,     4,     3,
     180,     6,     4,     4,     4,     4,     4,     4,   227,   230,
       6,     4,     6,     8,     4,   195,   196,   197,   198,   199,
     200,     4,     4,     4,     4,     4,     4,     4,   228,   209,
       4,     4,     4,     4,   228,     4,   228,   230,   228,   228,
       4,   228,   228,   228,     4,   228,     4,   227,   230,     4,
       6,     3,   228,   228,   228,   228,   228,   228,     4,   228,
     230,     8,   230,   228,   228,     8,     4,   228,   230,     4,
     230,   230,   230,   230,   227,   227,   227,   227,   227,   227,
     227,   227,     8,     3,     8,     7,     5,  1026,   227,     4,
    1029,     4,     4,  1032,     4,   227,  1035,  1026,  1035,   227,
    1032,  1040,  1032,  1026,  1043,  1026,  1035,  1046,  1029,  1040,
     227,  1032,  1029,   227,  1035,  1032,   227,  1026,  1035,  1040,
     230,  1060,  1043,  1040,   230,  1026,  1035,  1026,     7,   228,
    1069,  1040,  1071,     4,  1035,   227,  1035,   227,  1026,  1060,
    1035,  1040,  1081,     6,  1043,     3,     5,  1035,  1069,  1088,
    1071,  1035,  1026,   227,  1093,  1029,  1093,  1078,  1032,     4,
    1081,  1035,  1026,     4,  1081,  1026,  1040,     4,     4,  1043,
     227,  1035,  1093,     7,  1035,  1026,   167,   227,     5,  1040,
       6,  1026,  1043,     7,  1035,     3,  1060,  1026,     4,  1040,
    1035,  1026,  1043,     4,  1093,  1069,  1035,  1071,  1093,     4,
    1035,  1040,  1026,  1026,  1078,  1040,     4,  1081,  1043,  1093,
       4,  1035,  1035,  1026,     4,  1026,  1040,  1040,  1026,  1093,
    1026,  1026,  1035,  1026,  1035,  1026,  1026,  1035,  1026,  1035,
    1035,     4,  1035,  1026,  1035,  1035,  1026,  1035,  1026,  1026,
    1026,  1026,  1035,   230,  1026,  1035,  1026,  1035,  1035,  1035,
    1035,  1026,  1026,  1035,  1026,  1035,  1026,   701,   228,   227,
    1035,  1035,   228,  1035,   227,  1035,   227,   508,   227,   716,
     718,   517,   997,   804,  1025,  1020,  1028,  1038,   565,  1060,
    1037,   530,  1048,  1046,  1055,  1277,  1026,  1031,   555,  1045,
    1029,  1034,  1041,  1043,   534,  1032,  1095,  1093,   562,  1284,
    1343,   545,  1368,  1339,  1393,  1421,   757,   579,  1301,  1073,
     717,  1069,  1071,   575,  1371,  1399,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1078,    -1,    -1,    -1,    -1,    -1,  1082,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1277,    -1,
    1277,  1088,    -1,    -1,    -1,  1284,    -1,    -1,  1277,    -1,
      -1,    -1,    -1,  1284,  1293,    -1,  1277,    -1,    -1,  1234,
    1277,    -1,  1301,  1284,    -1,    -1,    -1,  1284,  1277,    -1,
      -1,    -1,  1293,    -1,    -1,  1284,  1277,    -1,  1277,    -1,
    1301,    -1,  1277,    -1,  1301,  1284,    -1,    -1,    -1,  1277,
      -1,    -1,    -1,  1277,    -1,    -1,    -1,    -1,    -1,    -1,
    1339,    -1,  1341,  1277,    -1,    -1,    -1,    -1,    -1,    -1,
    1284,    -1,    -1,  1277,    -1,    -1,  1277,    -1,  1339,  1293,
    1341,    -1,    -1,  1284,  1341,    -1,  1277,  1301,    -1,  1368,
      -1,    -1,  1277,  1284,    -1,    -1,    -1,    -1,  1277,    -1,
      -1,    -1,  1277,    -1,    -1,  1284,    -1,  1368,    -1,  1284,
      -1,  1368,  1391,  1277,  1277,    -1,    -1,    -1,    -1,    -1,
    1284,  1284,    -1,    -1,  1277,  1339,  1277,  1341,    -1,  1277,
    1391,  1277,  1277,    -1,  1277,    -1,  1277,  1277,    -1,  1277,
      -1,    -1,  1421,    -1,  1277,    -1,    -1,  1277,    -1,  1277,
    1277,  1277,  1277,    -1,  1368,  1277,    -1,  1277,    -1,    -1,
    1421,    -1,  1277,  1277,    -1,  1277,    -1,  1277,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1391,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1421,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    89,    90,    91,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
      -1,    -1,   124,   125,    -1,    -1,    -1,    -1,   130,    -1,
     132,    -1,    30,    31,    32,    33,    34,    35,   140,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,   195,   196,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,   115,    -1,   117,
      -1,   119,   120,   121,    -1,   227,   124,   125,    -1,    -1,
      -1,    -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,     0,     5,
       7,     9,   175,   227,   228,   229,   230,   246,   247,   248,
     253,     7,   262,     7,   267,     7,   322,     7,   435,     7,
     520,     7,   537,     7,   469,     7,   475,     7,   499,     7,
     411,     7,   648,     7,   667,   254,   249,   612,   263,   268,
     323,   436,   521,   538,   470,   476,   500,   412,   649,   668,
     246,   255,   256,   227,   251,   252,     4,    10,   264,   266,
      11,    14,    26,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    92,
      93,   104,   105,   106,   111,   114,   115,   119,   120,   121,
     122,   123,   132,   142,   145,   152,   153,   157,   158,   176,
     180,   195,   196,   197,   198,   199,   200,   209,   227,   261,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   284,   285,   287,   288,   289,   290,
     291,   292,   293,   296,   298,   300,   301,   302,   305,   306,
     308,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     336,   338,   346,   348,   389,   398,   405,   419,   429,   455,
     456,   457,   459,   467,   493,   527,   529,   531,   542,   544,
     546,   569,   584,   585,   587,   636,   646,   665,   674,   698,
      15,    16,    19,    22,    23,    24,    25,   261,   320,   321,
     324,   326,   329,   332,   333,   334,   335,   527,   529,    89,
      90,    91,   112,   116,   117,   118,   124,   125,   130,   140,
     261,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   285,   288,   289,   290,   291,   292,   293,   296,   298,
     300,   301,   302,   305,   306,   308,   310,   316,   437,   438,
     439,   441,   443,   445,   447,   449,   451,   453,   455,   456,
     457,   458,   493,   514,   527,   529,   531,   542,   544,   546,
     564,   113,   131,   261,   449,   451,   453,   493,   522,   523,
     524,   526,   527,   529,   123,   133,   134,   135,   136,   137,
     138,   139,   261,   493,   527,   529,   539,   540,   541,   542,
     544,   546,   548,   550,   552,   554,   556,   558,   560,   562,
     467,    40,    94,    96,    97,   101,   102,   103,   261,   365,
     477,   478,   479,   480,   481,   482,   483,   485,   487,   489,
     490,   492,   527,   529,    95,    98,    99,   100,   123,   261,
     365,   481,   487,   501,   502,   503,   504,   505,   507,   508,
     509,   510,   511,   512,   527,   529,   143,   144,   261,   413,
     414,   415,   417,   181,   182,   183,   184,   185,   186,   187,
     188,   261,   527,   529,   650,   651,   652,   653,   655,   656,
     658,   659,   660,   663,    12,    13,   669,   670,   671,   673,
       6,     3,     4,     8,     3,   227,   265,     3,     8,   666,
     319,   339,     4,     4,     4,   543,   545,   547,     4,     4,
     337,   347,   349,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   283,     4,     4,     4,     4,     4,
     294,   297,   299,     4,     4,     4,     4,   430,   468,   494,
       4,   286,   303,   460,   528,   530,     4,     4,     4,   390,
     570,   532,   406,   420,     4,   399,   586,   588,   637,   647,
     307,   309,     4,     4,     4,   675,   699,     4,     3,     8,
     325,   327,   330,     4,     4,     4,     4,     3,     8,   442,
     444,   446,   515,   440,   448,     4,   452,   454,   450,   565,
       3,     8,   525,     4,     3,     8,   563,   549,   551,   553,
     557,   555,   561,   559,     8,     3,     8,   484,   366,     4,
     488,   486,   491,     4,     8,     3,   506,     4,     4,     4,
     513,     8,     3,   416,   418,     3,     8,     4,   654,     4,
     657,     4,     4,   661,   664,     3,     8,   672,     4,     3,
       8,   246,   246,   227,     4,     4,     4,     4,   230,   230,
     230,     4,     4,     4,   228,   230,     4,     4,     4,   228,
     228,   228,   228,   228,   230,   229,   229,   229,   228,   228,
       4,   228,   228,   230,   230,   230,     4,     4,     4,   230,
     230,   229,   230,     4,     4,     4,   228,     4,     4,     4,
       4,     4,   230,   230,   230,     4,     4,     4,     4,     4,
     228,     4,     4,     4,     4,     4,     4,     4,   230,   230,
     230,     4,     4,   270,     4,     4,     4,   230,   230,   228,
     228,   321,     4,     4,     4,     4,     4,     4,   228,     4,
       4,     4,     4,   438,     4,   228,   523,     4,     4,     4,
       4,     4,     4,     4,     4,   541,     4,     4,   228,     4,
       4,     4,   230,   479,     4,   230,   230,   230,     4,   503,
       4,     4,   414,   230,     4,   228,     4,   228,   228,     4,
       4,   651,     4,   228,   670,     4,     7,     7,     7,     7,
     227,   227,   227,     7,     7,     5,   227,   191,   192,   193,
     194,   230,   295,   227,   227,     5,     5,     5,   227,   107,
     108,   109,   110,   304,     5,   248,   250,   227,     5,     5,
       5,     5,     7,     7,     7,     5,     7,     7,   227,   227,
       5,     7,     5,   257,    17,    18,   328,    20,    21,   331,
     227,   227,   227,     5,   227,   227,   257,   257,   227,     7,
     227,   257,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   257,   227,   250,   227,   227,
      18,   189,   662,   190,     5,   246,   269,   669,   320,    27,
      28,   340,   341,   342,   344,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      58,    59,    60,    61,    62,    63,   261,   354,   355,   356,
     358,   360,   362,   364,   365,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   379,   380,   381,   383,   385,
     387,   354,     7,   350,   351,   352,     7,   431,   432,   433,
       7,   471,   472,   473,     7,   495,   496,   497,     7,   461,
     462,   463,   134,   135,   136,   137,   139,   391,   392,   393,
     394,   395,   396,   397,     7,   571,   572,     7,   533,   534,
     535,     7,   407,   408,   409,   146,   147,   148,   149,   150,
     151,   421,   422,   423,   424,   425,   426,   427,   428,   154,
     155,   156,   261,   400,   401,   402,   403,   404,   527,   529,
     159,   163,   164,   165,   166,   173,   174,   261,   381,   383,
     385,   527,   529,   593,   594,   595,   598,   600,   602,   603,
     604,   613,     7,   589,   590,   591,   177,   178,   179,   227,
     527,   529,   638,   639,   640,   641,   643,   644,   650,     7,
     676,   677,   210,   211,   212,   213,   261,   700,   701,   702,
     703,   704,   705,   258,     7,   516,   517,   518,   141,   566,
     567,   350,     8,     8,     8,   343,   345,     3,     8,   357,
     359,   361,   363,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   377,     4,     4,   382,   384,   386,   388,
       3,     8,     8,   353,     6,     3,   434,     6,     3,   474,
       6,     3,   498,     6,     3,   464,     6,     3,     3,     6,
     573,     3,     6,   536,     6,     3,   410,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   596,   599,   601,     4,   614,     4,   605,     3,
       8,   592,     6,     3,     4,   642,     4,   645,     3,     8,
       8,   678,     3,     6,     4,     4,     4,     4,     3,     8,
     227,   259,   260,   519,     6,     3,   568,     8,     6,     4,
       4,   341,     4,     4,     4,     4,   228,   230,   228,   230,
     228,   228,   228,   228,   228,   228,     4,   230,   228,     4,
       4,     4,     4,   355,   354,   352,   437,   433,   477,   473,
     501,   497,   261,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   285,   288,   289,   290,   291,   292,   293,
     296,   298,   300,   301,   302,   305,   306,   308,   310,   316,
     365,   429,   447,   449,   451,   453,   455,   456,   457,   465,
     466,   493,   527,   529,   542,   544,   546,   564,   463,   392,
     126,   127,   128,   129,   261,   271,   272,   273,   316,   365,
     467,   493,   527,   529,   542,   544,   546,   574,   575,   576,
     577,   578,   580,   582,   583,   572,   539,   535,   413,   409,
     228,   228,   228,   228,   228,   228,   422,   230,   228,   228,
     401,     4,     4,     4,   228,     4,   230,     4,   594,   593,
     591,   230,     4,   228,     4,   639,   201,   203,   204,   261,
     365,   527,   529,   679,   680,   681,   682,   684,   677,   230,
     230,   230,   230,   701,     6,     3,   522,   518,     4,   227,
     227,   227,   227,   227,   227,    55,    56,    57,   378,   227,
     227,   227,   227,     8,     8,     8,     8,     3,     8,   579,
     581,     4,     4,     8,     3,     8,     8,   160,   161,   162,
     597,   227,   227,     7,     5,     8,   227,   246,   685,     4,
     683,     3,     8,   227,     8,   257,   466,     4,     4,   230,
     230,   576,    40,   168,   169,   170,   261,   527,   529,   615,
     616,   617,   620,   622,   624,     7,   606,   607,   608,     4,
     228,     4,   680,   227,   227,   618,   621,   623,   625,     3,
       8,   609,     6,     3,     5,   227,     4,     4,     4,     4,
     616,   227,   246,   261,   365,   527,   529,   610,   611,   608,
       7,   686,   687,   167,   619,   227,   227,     5,     3,     8,
     688,     3,     6,     7,   626,   627,   628,   611,   202,   205,
     206,   207,   208,   689,   690,   691,   693,   694,   695,   696,
     687,   629,     6,     3,   692,     4,     4,     4,   697,     3,
       8,   171,   172,   261,   358,   360,   527,   529,   630,   631,
     632,   634,   628,     4,   230,   228,   228,     4,   690,   633,
     635,     3,     8,   227,   227,     4,     4,   631,   227,   227
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
     438,   438,   438,   438,   438,   438,   438,   438,   438,   440,
     439,   442,   441,   444,   443,   446,   445,   448,   447,   450,
     449,   452,   451,   454,   453,   455,   456,   457,   458,   460,
     459,   461,   461,   462,   462,   462,   464,   463,   465,   465,
     465,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   468,   467,   470,   469,   471,
     471,   472,   472,   472,   474,   473,   476,   475,   477,   477,
     478,   478,   478,   479,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   480,   481,   482,   484,   483,   486,   485,
     488,   487,   489,   491,   490,   492,   494,   493,   495,   495,
     496,   496,   496,   498,   497,   500,   499,   501,   501,   502,
     502,   502,   503,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   504,   506,   505,   507,   508,   509,   510,
     511,   513,   512,   515,   514,   516,   516,   517,   517,   517,
     519,   518,   521,   520,   522,   522,   522,   523,   523,   523,
     523,   523,   523,   523,   523,   523,   525,   524,   526,   528,
     527,   530,   529,   532,   531,   533,   533,   534,   534,   534,
     536,   535,   538,   537,   539,   539,   540,   540,   540,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   543,   542,   545,   544,   547,   546,
     549,   548,   551,   550,   553,   552,   555,   554,   557,   556,
     559,   558,   561,   560,   563,   562,   565,   564,   566,   568,
     567,   570,   569,   571,   571,   571,   573,   572,   574,   574,
     575,   575,   575,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     577,   579,   578,   581,   580,   582,   583,   584,   586,   585,
     588,   587,   589,   589,   590,   590,   590,   592,   591,   593,
     593,   593,   594,   594,   594,   594,   594,   594,   594,   594,
     594,   594,   594,   594,   594,   596,   595,   597,   597,   597,
     599,   598,   601,   600,   602,   603,   605,   604,   606,   606,
     607,   607,   607,   609,   608,   610,   610,   610,   611,   611,
     611,   611,   611,   612,   246,   614,   613,   615,   615,   615,
     616,   616,   616,   616,   616,   616,   616,   618,   617,   619,
     621,   620,   623,   622,   625,   624,   626,   626,   627,   627,
     627,   629,   628,   630,   630,   630,   631,   631,   631,   631,
     631,   631,   631,   633,   632,   635,   634,   637,   636,   638,
     638,   638,   639,   639,   639,   639,   639,   639,   640,   642,
     641,   643,   645,   644,   647,   646,   649,   648,   650,   650,
     650,   651,   651,   651,   651,   651,   651,   651,   651,   651,
     651,   651,   652,   654,   653,   655,   657,   656,   658,   659,
     661,   660,   662,   662,   664,   663,   666,   665,   668,   667,
     669,   669,   669,   670,   670,   672,   671,   673,   675,   674,
     676,   676,   676,   678,   677,   679,   679,   679,   680,   680,
     680,   680,   680,   680,   680,   681,   683,   682,   685,   684,
     686,   686,   686,   688,   687,   689,   689,   689,   690,   690,
     690,   690,   690,   692,   691,   693,   694,   695,   697,   696,
     699,   698,   700,   700,   700,   701,   701,   701,   701,   701,
     702,   703,   704,   705
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       3,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     3,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     2,
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
  "$@66", "require_client_classes", "$@67", "evaluate_additional_classes",
  "$@68", "reservations_global", "reservations_in_subnet",
  "reservations_out_of_pool", "id", "shared_networks", "$@69",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@70", "shared_network_params", "shared_network_param",
  "option_def_list", "$@71", "sub_option_def_list", "$@72",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@73", "sub_option_def", "$@74",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@75",
  "option_def_record_types", "$@76", "space", "$@77", "option_def_space",
  "option_def_encapsulate", "$@78", "option_def_array", "option_data_list",
  "$@79", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@80", "sub_option_data", "$@81",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@82",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@83", "pools_list", "$@84",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@85",
  "sub_pool4", "$@86", "pool_params", "pool_param", "pool_entry", "$@87",
  "pool_id", "user_context", "$@88", "comment", "$@89", "reservations",
  "$@90", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@93", "server_hostname", "$@94", "boot_file_name", "$@95",
  "ip_address", "$@96", "duid", "$@97", "hw_address", "$@98",
  "client_id_value", "$@99", "circuit_id_value", "$@100", "flex_id_value",
  "$@101", "hostname", "$@102", "reservation_client_classes", "$@103",
  "relay", "$@104", "relay_map", "ip_addresses", "$@105", "client_classes",
  "$@106", "client_classes_list", "client_class_entry", "$@107",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@108",
  "client_class_template_test", "$@109", "only_if_required",
  "only_in_additional_list", "dhcp4o6_port", "control_socket", "$@110",
  "control_sockets", "$@111", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@112",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@113", "control_socket_type_value", "control_socket_name", "$@114",
  "control_socket_address", "$@115", "control_socket_port",
  "cert_required", "http_headers", "$@116", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@117",
  "http_header_params", "http_header_param", "$@118", "authentication",
  "$@119", "auth_params", "auth_param", "auth_type", "$@120",
  "auth_type_value", "realm", "$@121", "directory", "$@122", "clients",
  "$@123", "clients_list", "not_empty_clients_list", "basic_auth", "$@124",
  "clients_params", "clients_param", "user_file", "$@125", "password_file",
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
    1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1646,
    1646,  1655,  1655,  1664,  1664,  1673,  1673,  1682,  1682,  1691,
    1691,  1701,  1701,  1712,  1712,  1723,  1729,  1735,  1741,  1749,
    1749,  1761,  1762,  1766,  1767,  1768,  1773,  1773,  1781,  1782,
    1783,  1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,
    1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,
    1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,  1826,
    1827,  1828,  1829,  1830,  1831,  1838,  1838,  1852,  1852,  1861,
    1862,  1865,  1866,  1867,  1874,  1874,  1889,  1889,  1903,  1904,
    1907,  1908,  1909,  1914,  1915,  1916,  1917,  1918,  1919,  1920,
    1921,  1922,  1923,  1926,  1928,  1934,  1936,  1936,  1945,  1945,
    1954,  1954,  1963,  1965,  1965,  1974,  1984,  1984,  1997,  1998,
    2003,  2004,  2005,  2012,  2012,  2024,  2024,  2036,  2037,  2042,
    2043,  2044,  2051,  2052,  2053,  2054,  2055,  2056,  2057,  2058,
    2059,  2060,  2061,  2064,  2066,  2066,  2075,  2077,  2079,  2085,
    2091,  2097,  2097,  2111,  2111,  2124,  2125,  2128,  2129,  2130,
    2135,  2135,  2145,  2145,  2155,  2156,  2157,  2162,  2163,  2164,
    2165,  2166,  2167,  2168,  2169,  2170,  2173,  2173,  2182,  2188,
    2188,  2213,  2213,  2243,  2243,  2254,  2255,  2258,  2259,  2260,
    2265,  2265,  2274,  2274,  2283,  2284,  2287,  2288,  2289,  2295,
    2296,  2297,  2298,  2299,  2300,  2301,  2302,  2303,  2304,  2305,
    2306,  2307,  2308,  2309,  2312,  2312,  2321,  2321,  2330,  2330,
    2339,  2339,  2348,  2348,  2357,  2357,  2366,  2366,  2375,  2375,
    2384,  2384,  2393,  2393,  2402,  2402,  2416,  2416,  2427,  2430,
    2430,  2444,  2444,  2455,  2456,  2457,  2462,  2462,  2472,  2473,
    2476,  2477,  2478,  2483,  2484,  2485,  2486,  2487,  2488,  2489,
    2490,  2491,  2492,  2493,  2494,  2495,  2496,  2497,  2498,  2499,
    2502,  2504,  2504,  2513,  2513,  2523,  2529,  2537,  2545,  2545,
    2557,  2557,  2569,  2570,  2573,  2574,  2575,  2580,  2580,  2588,
    2589,  2590,  2595,  2596,  2597,  2598,  2599,  2600,  2601,  2602,
    2603,  2604,  2605,  2606,  2607,  2610,  2610,  2619,  2620,  2621,
    2624,  2624,  2634,  2634,  2644,  2650,  2656,  2656,  2666,  2667,
    2670,  2671,  2672,  2677,  2677,  2685,  2686,  2687,  2692,  2693,
    2694,  2695,  2696,  2699,  2699,  2710,  2710,  2723,  2724,  2725,
    2730,  2731,  2732,  2733,  2734,  2735,  2736,  2739,  2739,  2747,
    2750,  2750,  2759,  2759,  2768,  2768,  2779,  2780,  2783,  2784,
    2785,  2790,  2790,  2798,  2799,  2800,  2805,  2806,  2807,  2808,
    2809,  2810,  2811,  2814,  2814,  2823,  2823,  2834,  2834,  2847,
    2848,  2849,  2854,  2855,  2856,  2857,  2858,  2859,  2862,  2868,
    2868,  2877,  2883,  2883,  2893,  2893,  2906,  2906,  2916,  2917,
    2918,  2923,  2924,  2925,  2926,  2927,  2928,  2929,  2930,  2931,
    2932,  2933,  2936,  2942,  2942,  2951,  2957,  2957,  2966,  2972,
    2978,  2978,  2987,  2988,  2991,  2991,  3002,  3002,  3014,  3014,
    3024,  3025,  3026,  3032,  3033,  3036,  3036,  3047,  3055,  3055,
    3068,  3069,  3070,  3076,  3076,  3084,  3085,  3086,  3091,  3092,
    3093,  3094,  3095,  3096,  3097,  3100,  3106,  3106,  3115,  3115,
    3126,  3127,  3128,  3133,  3133,  3141,  3142,  3143,  3148,  3149,
    3150,  3151,  3152,  3155,  3155,  3164,  3170,  3176,  3182,  3182,
    3191,  3191,  3202,  3203,  3204,  3209,  3210,  3211,  3212,  3213,
    3216,  3222,  3228,  3234
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
#line 6845 "dhcp4_parser.cc"

#line 3240 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
