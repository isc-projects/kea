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
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 301 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp4_parser.cc"
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
#line 310 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 311 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 312 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 778 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 313 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 314 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 790 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 315 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 316 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 802 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 317 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 808 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 318 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 814 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 319 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 820 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 320 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 826 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 321 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 832 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 322 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 838 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 330 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 844 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 331 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 332 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 333 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 334 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 335 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 874 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 336 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 339 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 889 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 344 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 900 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 349 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 910 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 355 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 916 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 362 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 926 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 367 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 373 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 945 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 378 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 954 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 381 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 962 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 389 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 971 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 393 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 980 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 397 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 988 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 403 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 996 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 405 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1005 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 414 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1014 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 418 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1023 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 422 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1031 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 432 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1042 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 441 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 446 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1066 "dhcp4_parser.cc"
    break;

  case 61: // $@18: %empty
#line 456 "dhcp4_parser.yy"
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
#line 1081 "dhcp4_parser.cc"
    break;

  case 62: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 465 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1091 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 473 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1099 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 479 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1109 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 483 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1118 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 490 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1126 "dhcp4_parser.cc"
    break;

  case 138: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 567 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1136 "dhcp4_parser.cc"
    break;

  case 139: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 573 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1146 "dhcp4_parser.cc"
    break;

  case 140: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 579 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1156 "dhcp4_parser.cc"
    break;

  case 141: // renew_timer: "renew-timer" ":" "integer"
#line 585 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1166 "dhcp4_parser.cc"
    break;

  case 142: // rebind_timer: "rebind-timer" ":" "integer"
#line 591 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1176 "dhcp4_parser.cc"
    break;

  case 143: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 597 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1186 "dhcp4_parser.cc"
    break;

  case 144: // t1_percent: "t1-percent" ":" "floating point"
#line 603 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1196 "dhcp4_parser.cc"
    break;

  case 145: // t2_percent: "t2-percent" ":" "floating point"
#line 609 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1206 "dhcp4_parser.cc"
    break;

  case 146: // cache_threshold: "cache-threshold" ":" "floating point"
#line 615 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1216 "dhcp4_parser.cc"
    break;

  case 147: // cache_max_age: "cache-max-age" ":" "integer"
#line 621 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1226 "dhcp4_parser.cc"
    break;

  case 148: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 627 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1236 "dhcp4_parser.cc"
    break;

  case 149: // $@20: %empty
#line 633 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1245 "dhcp4_parser.cc"
    break;

  case 150: // server_tag: "server-tag" $@20 ":" "constant string"
#line 636 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1255 "dhcp4_parser.cc"
    break;

  case 151: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 642 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1265 "dhcp4_parser.cc"
    break;

  case 152: // $@21: %empty
#line 648 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1274 "dhcp4_parser.cc"
    break;

  case 153: // allocator: "allocator" $@21 ":" "constant string"
#line 651 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1284 "dhcp4_parser.cc"
    break;

  case 154: // echo_client_id: "echo-client-id" ":" "boolean"
#line 657 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1294 "dhcp4_parser.cc"
    break;

  case 155: // match_client_id: "match-client-id" ":" "boolean"
#line 663 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1304 "dhcp4_parser.cc"
    break;

  case 156: // authoritative: "authoritative" ":" "boolean"
#line 669 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1314 "dhcp4_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 675 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1324 "dhcp4_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 681 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1334 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 687 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1344 "dhcp4_parser.cc"
    break;

  case 160: // $@22: %empty
#line 693 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1353 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 696 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 702 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 705 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1378 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 708 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1386 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 711 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1394 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 714 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1403 "dhcp4_parser.cc"
    break;

  case 167: // $@23: %empty
#line 720 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1412 "dhcp4_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 723 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1422 "dhcp4_parser.cc"
    break;

  case 169: // $@24: %empty
#line 729 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp4_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 732 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1441 "dhcp4_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 738 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1451 "dhcp4_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 747 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 173: // $@25: %empty
#line 757 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1474 "dhcp4_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 760 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1483 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 766 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1491 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 769 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1499 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 772 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1507 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 775 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1515 "dhcp4_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 780 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 180: // $@26: %empty
#line 786 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 789 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 182: // $@27: %empty
#line 795 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1553 "dhcp4_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 798 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1563 "dhcp4_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 804 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1573 "dhcp4_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 810 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 816 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1593 "dhcp4_parser.cc"
    break;

  case 187: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 822 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 188: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 828 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 189: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 834 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 190: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 840 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 191: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 846 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1643 "dhcp4_parser.cc"
    break;

  case 192: // $@28: %empty
#line 852 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 193: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 858 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 196: // interfaces_config_params: interfaces_config_params ","
#line 866 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1673 "dhcp4_parser.cc"
    break;

  case 207: // $@29: %empty
#line 883 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1683 "dhcp4_parser.cc"
    break;

  case 208: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 887 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1692 "dhcp4_parser.cc"
    break;

  case 209: // $@30: %empty
#line 892 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1704 "dhcp4_parser.cc"
    break;

  case 210: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 898 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1713 "dhcp4_parser.cc"
    break;

  case 211: // $@31: %empty
#line 903 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1722 "dhcp4_parser.cc"
    break;

  case 212: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 906 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1731 "dhcp4_parser.cc"
    break;

  case 213: // socket_type: "raw"
#line 911 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1737 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "udp"
#line 912 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1743 "dhcp4_parser.cc"
    break;

  case 215: // $@32: %empty
#line 915 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1752 "dhcp4_parser.cc"
    break;

  case 216: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 918 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1761 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface_value: "same-as-inbound"
#line 923 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1769 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "use-routing"
#line 925 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1777 "dhcp4_parser.cc"
    break;

  case 219: // re_detect: "re-detect" ":" "boolean"
#line 929 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1787 "dhcp4_parser.cc"
    break;

  case 220: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 935 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1797 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 941 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1807 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 947 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1817 "dhcp4_parser.cc"
    break;

  case 223: // $@33: %empty
#line 953 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1829 "dhcp4_parser.cc"
    break;

  case 224: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 959 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1840 "dhcp4_parser.cc"
    break;

  case 225: // $@34: %empty
#line 966 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 226: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 972 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc"
    break;

  case 229: // sanity_checks_params: sanity_checks_params ","
#line 979 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1869 "dhcp4_parser.cc"
    break;

  case 232: // $@35: %empty
#line 988 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 233: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 991 "dhcp4_parser.yy"
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
#line 1898 "dhcp4_parser.cc"
    break;

  case 234: // $@36: %empty
#line 1007 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1907 "dhcp4_parser.cc"
    break;

  case 235: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1010 "dhcp4_parser.yy"
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
#line 1926 "dhcp4_parser.cc"
    break;

  case 236: // $@37: %empty
#line 1025 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1938 "dhcp4_parser.cc"
    break;

  case 237: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1031 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1949 "dhcp4_parser.cc"
    break;

  case 238: // $@38: %empty
#line 1038 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1961 "dhcp4_parser.cc"
    break;

  case 239: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1044 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1970 "dhcp4_parser.cc"
    break;

  case 244: // not_empty_database_list: not_empty_database_list ","
#line 1055 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1978 "dhcp4_parser.cc"
    break;

  case 245: // $@39: %empty
#line 1060 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 246: // database: "{" $@39 database_map_params "}"
#line 1064 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 249: // database_map_params: database_map_params ","
#line 1072 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2006 "dhcp4_parser.cc"
    break;

  case 273: // $@40: %empty
#line 1102 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 2015 "dhcp4_parser.cc"
    break;

  case 274: // database_type: "type" $@40 ":" db_type
#line 1105 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2024 "dhcp4_parser.cc"
    break;

  case 275: // db_type: "memfile"
#line 1110 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 2030 "dhcp4_parser.cc"
    break;

  case 276: // db_type: "mysql"
#line 1111 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 2036 "dhcp4_parser.cc"
    break;

  case 277: // db_type: "postgresql"
#line 1112 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp4_parser.cc"
    break;

  case 278: // $@41: %empty
#line 1115 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2051 "dhcp4_parser.cc"
    break;

  case 279: // user: "user" $@41 ":" "constant string"
#line 1118 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2061 "dhcp4_parser.cc"
    break;

  case 280: // $@42: %empty
#line 1124 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 281: // password: "password" $@42 ":" "constant string"
#line 1127 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2080 "dhcp4_parser.cc"
    break;

  case 282: // $@43: %empty
#line 1133 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 283: // host: "host" $@43 ":" "constant string"
#line 1136 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 284: // port: "port" ":" "integer"
#line 1142 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 285: // $@44: %empty
#line 1148 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 286: // name: "name" $@44 ":" "constant string"
#line 1151 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2128 "dhcp4_parser.cc"
    break;

  case 287: // persist: "persist" ":" "boolean"
#line 1157 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2138 "dhcp4_parser.cc"
    break;

  case 288: // lfc_interval: "lfc-interval" ":" "integer"
#line 1163 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2148 "dhcp4_parser.cc"
    break;

  case 289: // readonly: "readonly" ":" "boolean"
#line 1169 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2158 "dhcp4_parser.cc"
    break;

  case 290: // connect_timeout: "connect-timeout" ":" "integer"
#line 1175 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2168 "dhcp4_parser.cc"
    break;

  case 291: // read_timeout: "read-timeout" ":" "integer"
#line 1181 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2178 "dhcp4_parser.cc"
    break;

  case 292: // write_timeout: "write-timeout" ":" "integer"
#line 1187 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2188 "dhcp4_parser.cc"
    break;

  case 293: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1193 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2198 "dhcp4_parser.cc"
    break;

  case 294: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1199 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2208 "dhcp4_parser.cc"
    break;

  case 295: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1205 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2218 "dhcp4_parser.cc"
    break;

  case 296: // $@45: %empty
#line 1211 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 297: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1214 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 298: // on_fail_mode: "stop-retry-exit"
#line 1219 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2242 "dhcp4_parser.cc"
    break;

  case 299: // on_fail_mode: "serve-retry-exit"
#line 1220 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2248 "dhcp4_parser.cc"
    break;

  case 300: // on_fail_mode: "serve-retry-continue"
#line 1221 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2254 "dhcp4_parser.cc"
    break;

  case 301: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1224 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2264 "dhcp4_parser.cc"
    break;

  case 302: // max_row_errors: "max-row-errors" ":" "integer"
#line 1230 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 303: // $@46: %empty
#line 1236 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 304: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1239 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2293 "dhcp4_parser.cc"
    break;

  case 305: // $@47: %empty
#line 1245 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp4_parser.cc"
    break;

  case 306: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1248 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2312 "dhcp4_parser.cc"
    break;

  case 307: // $@48: %empty
#line 1254 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2321 "dhcp4_parser.cc"
    break;

  case 308: // key_file: "key-file" $@48 ":" "constant string"
#line 1257 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 309: // $@49: %empty
#line 1263 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2340 "dhcp4_parser.cc"
    break;

  case 310: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1266 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2350 "dhcp4_parser.cc"
    break;

  case 311: // $@50: %empty
#line 1272 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 312: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1278 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2371 "dhcp4_parser.cc"
    break;

  case 315: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1285 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2379 "dhcp4_parser.cc"
    break;

  case 321: // duid_id: "duid"
#line 1297 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 322: // hw_address_id: "hw-address"
#line 1302 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2397 "dhcp4_parser.cc"
    break;

  case 323: // circuit_id: "circuit-id"
#line 1307 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 324: // client_id: "client-id"
#line 1312 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 325: // flex_id: "flex-id"
#line 1317 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2424 "dhcp4_parser.cc"
    break;

  case 326: // $@51: %empty
#line 1324 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2436 "dhcp4_parser.cc"
    break;

  case 327: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1330 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2447 "dhcp4_parser.cc"
    break;

  case 330: // multi_threading_params: multi_threading_params ","
#line 1339 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2455 "dhcp4_parser.cc"
    break;

  case 337: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1352 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 338: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1358 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2475 "dhcp4_parser.cc"
    break;

  case 339: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1364 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2485 "dhcp4_parser.cc"
    break;

  case 340: // $@52: %empty
#line 1370 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2497 "dhcp4_parser.cc"
    break;

  case 341: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1376 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2506 "dhcp4_parser.cc"
    break;

  case 346: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1387 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2514 "dhcp4_parser.cc"
    break;

  case 347: // $@53: %empty
#line 1392 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2524 "dhcp4_parser.cc"
    break;

  case 348: // hooks_library: "{" $@53 hooks_params "}"
#line 1396 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2534 "dhcp4_parser.cc"
    break;

  case 349: // $@54: %empty
#line 1402 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2544 "dhcp4_parser.cc"
    break;

  case 350: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1406 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2554 "dhcp4_parser.cc"
    break;

  case 353: // hooks_params: hooks_params ","
#line 1414 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2562 "dhcp4_parser.cc"
    break;

  case 357: // $@55: %empty
#line 1424 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2571 "dhcp4_parser.cc"
    break;

  case 358: // library: "library" $@55 ":" "constant string"
#line 1427 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2581 "dhcp4_parser.cc"
    break;

  case 359: // $@56: %empty
#line 1433 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 360: // parameters: "parameters" $@56 ":" map_value
#line 1436 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 361: // $@57: %empty
#line 1442 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2611 "dhcp4_parser.cc"
    break;

  case 362: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1448 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 365: // expired_leases_params: expired_leases_params ","
#line 1456 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2629 "dhcp4_parser.cc"
    break;

  case 372: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1469 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2639 "dhcp4_parser.cc"
    break;

  case 373: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1475 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2649 "dhcp4_parser.cc"
    break;

  case 374: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1481 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2659 "dhcp4_parser.cc"
    break;

  case 375: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1487 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2669 "dhcp4_parser.cc"
    break;

  case 376: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1493 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2679 "dhcp4_parser.cc"
    break;

  case 377: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1499 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2689 "dhcp4_parser.cc"
    break;

  case 378: // $@58: %empty
#line 1508 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 379: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1514 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 384: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1528 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2718 "dhcp4_parser.cc"
    break;

  case 385: // $@59: %empty
#line 1537 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2728 "dhcp4_parser.cc"
    break;

  case 386: // subnet4: "{" $@59 subnet4_params "}"
#line 1541 "dhcp4_parser.yy"
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
#line 2754 "dhcp4_parser.cc"
    break;

  case 387: // $@60: %empty
#line 1563 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2764 "dhcp4_parser.cc"
    break;

  case 388: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1567 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2774 "dhcp4_parser.cc"
    break;

  case 391: // subnet4_params: subnet4_params ","
#line 1576 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2782 "dhcp4_parser.cc"
    break;

  case 440: // $@61: %empty
#line 1632 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 441: // subnet: "subnet" $@61 ":" "constant string"
#line 1635 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 442: // $@62: %empty
#line 1641 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 443: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1644 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 444: // $@63: %empty
#line 1650 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1653 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2839 "dhcp4_parser.cc"
    break;

  case 446: // $@64: %empty
#line 1659 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 447: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1662 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2858 "dhcp4_parser.cc"
    break;

  case 448: // $@65: %empty
#line 1668 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2867 "dhcp4_parser.cc"
    break;

  case 449: // interface: "interface" $@65 ":" "constant string"
#line 1671 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2877 "dhcp4_parser.cc"
    break;

  case 450: // $@66: %empty
#line 1677 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2886 "dhcp4_parser.cc"
    break;

  case 451: // client_class: "client-class" $@66 ":" "constant string"
#line 1680 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2896 "dhcp4_parser.cc"
    break;

  case 452: // $@67: %empty
#line 1686 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 453: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1692 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 454: // reservations_global: "reservations-global" ":" "boolean"
#line 1697 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 455: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1703 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2937 "dhcp4_parser.cc"
    break;

  case 456: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1709 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 457: // id: "id" ":" "integer"
#line 1715 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 458: // $@68: %empty
#line 1723 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 459: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1729 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 464: // shared_networks_list: shared_networks_list ","
#line 1742 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2986 "dhcp4_parser.cc"
    break;

  case 465: // $@69: %empty
#line 1747 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 466: // shared_network: "{" $@69 shared_network_params "}"
#line 1751 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3004 "dhcp4_parser.cc"
    break;

  case 469: // shared_network_params: shared_network_params ","
#line 1757 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3012 "dhcp4_parser.cc"
    break;

  case 513: // $@70: %empty
#line 1811 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3024 "dhcp4_parser.cc"
    break;

  case 514: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1817 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 515: // $@71: %empty
#line 1825 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 516: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1828 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3050 "dhcp4_parser.cc"
    break;

  case 521: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1840 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3058 "dhcp4_parser.cc"
    break;

  case 522: // $@72: %empty
#line 1847 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3068 "dhcp4_parser.cc"
    break;

  case 523: // option_def_entry: "{" $@72 option_def_params "}"
#line 1851 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 524: // $@73: %empty
#line 1862 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 525: // sub_option_def: "{" $@73 option_def_params "}"
#line 1866 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 530: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1882 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3110 "dhcp4_parser.cc"
    break;

  case 542: // code: "code" ":" "integer"
#line 1901 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 544: // $@74: %empty
#line 1909 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp4_parser.cc"
    break;

  case 545: // option_def_type: "type" $@74 ":" "constant string"
#line 1912 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 546: // $@75: %empty
#line 1918 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3148 "dhcp4_parser.cc"
    break;

  case 547: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1921 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3158 "dhcp4_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1927 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 549: // space: "space" $@76 ":" "constant string"
#line 1930 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 551: // $@77: %empty
#line 1938 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 552: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1941 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 553: // option_def_array: "array" ":" "boolean"
#line 1947 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 554: // $@78: %empty
#line 1957 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3218 "dhcp4_parser.cc"
    break;

  case 555: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1963 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3227 "dhcp4_parser.cc"
    break;

  case 560: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1978 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3235 "dhcp4_parser.cc"
    break;

  case 561: // $@79: %empty
#line 1985 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 562: // option_data_entry: "{" $@79 option_data_params "}"
#line 1989 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 563: // $@80: %empty
#line 1997 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3264 "dhcp4_parser.cc"
    break;

  case 564: // sub_option_data: "{" $@80 option_data_params "}"
#line 2001 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 569: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2017 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3281 "dhcp4_parser.cc"
    break;

  case 581: // $@81: %empty
#line 2038 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3290 "dhcp4_parser.cc"
    break;

  case 582: // option_data_data: "data" $@81 ":" "constant string"
#line 2041 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3300 "dhcp4_parser.cc"
    break;

  case 585: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2051 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3310 "dhcp4_parser.cc"
    break;

  case 586: // option_data_always_send: "always-send" ":" "boolean"
#line 2057 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 587: // option_data_never_send: "never-send" ":" "boolean"
#line 2063 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 588: // $@82: %empty
#line 2072 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 589: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2078 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 594: // not_empty_pools_list: not_empty_pools_list ","
#line 2091 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3359 "dhcp4_parser.cc"
    break;

  case 595: // $@83: %empty
#line 2096 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3369 "dhcp4_parser.cc"
    break;

  case 596: // pool_list_entry: "{" $@83 pool_params "}"
#line 2100 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 597: // $@84: %empty
#line 2106 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 598: // sub_pool4: "{" $@84 pool_params "}"
#line 2110 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3399 "dhcp4_parser.cc"
    break;

  case 601: // pool_params: pool_params ","
#line 2118 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3407 "dhcp4_parser.cc"
    break;

  case 610: // $@85: %empty
#line 2133 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3416 "dhcp4_parser.cc"
    break;

  case 611: // pool_entry: "pool" $@85 ":" "constant string"
#line 2136 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 612: // pool_id: "pool-id" ":" "integer"
#line 2142 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 613: // $@86: %empty
#line 2148 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 614: // user_context: "user-context" $@86 ":" map_value
#line 2150 "dhcp4_parser.yy"
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
#line 3471 "dhcp4_parser.cc"
    break;

  case 615: // $@87: %empty
#line 2173 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 616: // comment: "comment" $@87 ":" "constant string"
#line 2175 "dhcp4_parser.yy"
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
#line 3508 "dhcp4_parser.cc"
    break;

  case 617: // $@88: %empty
#line 2203 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 618: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2209 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3529 "dhcp4_parser.cc"
    break;

  case 623: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2220 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3537 "dhcp4_parser.cc"
    break;

  case 624: // $@89: %empty
#line 2225 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3547 "dhcp4_parser.cc"
    break;

  case 625: // reservation: "{" $@89 reservation_params "}"
#line 2229 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 626: // $@90: %empty
#line 2234 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3566 "dhcp4_parser.cc"
    break;

  case 627: // sub_reservation: "{" $@90 reservation_params "}"
#line 2238 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3575 "dhcp4_parser.cc"
    break;

  case 632: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2249 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3583 "dhcp4_parser.cc"
    break;

  case 648: // $@91: %empty
#line 2272 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 649: // next_server: "next-server" $@91 ":" "constant string"
#line 2275 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 650: // $@92: %empty
#line 2281 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 651: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2284 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 652: // $@93: %empty
#line 2290 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 653: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2293 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3640 "dhcp4_parser.cc"
    break;

  case 654: // $@94: %empty
#line 2299 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3649 "dhcp4_parser.cc"
    break;

  case 655: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2302 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 656: // $@95: %empty
#line 2308 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 657: // duid: "duid" $@95 ":" "constant string"
#line 2311 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3678 "dhcp4_parser.cc"
    break;

  case 658: // $@96: %empty
#line 2317 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3687 "dhcp4_parser.cc"
    break;

  case 659: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2320 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3697 "dhcp4_parser.cc"
    break;

  case 660: // $@97: %empty
#line 2326 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3706 "dhcp4_parser.cc"
    break;

  case 661: // client_id_value: "client-id" $@97 ":" "constant string"
#line 2329 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3716 "dhcp4_parser.cc"
    break;

  case 662: // $@98: %empty
#line 2335 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3725 "dhcp4_parser.cc"
    break;

  case 663: // circuit_id_value: "circuit-id" $@98 ":" "constant string"
#line 2338 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3735 "dhcp4_parser.cc"
    break;

  case 664: // $@99: %empty
#line 2344 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3744 "dhcp4_parser.cc"
    break;

  case 665: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2347 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3754 "dhcp4_parser.cc"
    break;

  case 666: // $@100: %empty
#line 2353 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3763 "dhcp4_parser.cc"
    break;

  case 667: // hostname: "hostname" $@100 ":" "constant string"
#line 2356 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3773 "dhcp4_parser.cc"
    break;

  case 668: // $@101: %empty
#line 2362 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3785 "dhcp4_parser.cc"
    break;

  case 669: // reservation_client_classes: "client-classes" $@101 ":" list_strings
#line 2368 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3794 "dhcp4_parser.cc"
    break;

  case 670: // $@102: %empty
#line 2376 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 671: // relay: "relay" $@102 ":" "{" relay_map "}"
#line 2382 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 673: // $@103: %empty
#line 2390 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 674: // ip_addresses: "ip-addresses" $@103 ":" list_strings
#line 2396 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3836 "dhcp4_parser.cc"
    break;

  case 675: // $@104: %empty
#line 2404 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 676: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2410 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3857 "dhcp4_parser.cc"
    break;

  case 679: // client_classes_list: client_classes_list ","
#line 2417 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3865 "dhcp4_parser.cc"
    break;

  case 680: // $@105: %empty
#line 2422 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3875 "dhcp4_parser.cc"
    break;

  case 681: // client_class_entry: "{" $@105 client_class_params "}"
#line 2426 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3885 "dhcp4_parser.cc"
    break;

  case 686: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2438 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3893 "dhcp4_parser.cc"
    break;

  case 704: // $@106: %empty
#line 2463 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp4_parser.cc"
    break;

  case 705: // client_class_test: "test" $@106 ":" "constant string"
#line 2466 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3912 "dhcp4_parser.cc"
    break;

  case 706: // $@107: %empty
#line 2472 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3921 "dhcp4_parser.cc"
    break;

  case 707: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2475 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3931 "dhcp4_parser.cc"
    break;

  case 708: // only_if_required: "only-if-required" ":" "boolean"
#line 2481 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3941 "dhcp4_parser.cc"
    break;

  case 709: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2489 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3951 "dhcp4_parser.cc"
    break;

  case 710: // $@108: %empty
#line 2497 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 711: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2503 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3972 "dhcp4_parser.cc"
    break;

  case 714: // control_socket_params: control_socket_params ","
#line 2510 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3980 "dhcp4_parser.cc"
    break;

  case 720: // $@109: %empty
#line 2522 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 721: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2525 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 722: // $@110: %empty
#line 2531 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4008 "dhcp4_parser.cc"
    break;

  case 723: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2534 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 724: // $@111: %empty
#line 2543 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4030 "dhcp4_parser.cc"
    break;

  case 725: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2549 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 728: // queue_control_params: queue_control_params ","
#line 2558 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4049 "dhcp4_parser.cc"
    break;

  case 735: // enable_queue: "enable-queue" ":" "boolean"
#line 2571 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4059 "dhcp4_parser.cc"
    break;

  case 736: // $@112: %empty
#line 2577 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4068 "dhcp4_parser.cc"
    break;

  case 737: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2580 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4078 "dhcp4_parser.cc"
    break;

  case 738: // capacity: "capacity" ":" "integer"
#line 2586 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4088 "dhcp4_parser.cc"
    break;

  case 739: // $@113: %empty
#line 2592 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 740: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2595 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4106 "dhcp4_parser.cc"
    break;

  case 741: // $@114: %empty
#line 2602 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4118 "dhcp4_parser.cc"
    break;

  case 742: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2608 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 743: // $@115: %empty
#line 2615 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 744: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2619 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4149 "dhcp4_parser.cc"
    break;

  case 747: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2627 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4157 "dhcp4_parser.cc"
    break;

  case 759: // enable_updates: "enable-updates" ":" "boolean"
#line 2645 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 760: // $@116: %empty
#line 2651 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4176 "dhcp4_parser.cc"
    break;

  case 761: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2654 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4186 "dhcp4_parser.cc"
    break;

  case 762: // server_port: "server-port" ":" "integer"
#line 2660 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 763: // $@117: %empty
#line 2666 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4205 "dhcp4_parser.cc"
    break;

  case 764: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2669 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4215 "dhcp4_parser.cc"
    break;

  case 765: // sender_port: "sender-port" ":" "integer"
#line 2675 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4225 "dhcp4_parser.cc"
    break;

  case 766: // max_queue_size: "max-queue-size" ":" "integer"
#line 2681 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4235 "dhcp4_parser.cc"
    break;

  case 767: // $@118: %empty
#line 2687 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4244 "dhcp4_parser.cc"
    break;

  case 768: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2690 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4253 "dhcp4_parser.cc"
    break;

  case 769: // ncr_protocol_value: "udp"
#line 2696 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4259 "dhcp4_parser.cc"
    break;

  case 770: // ncr_protocol_value: "tcp"
#line 2697 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4265 "dhcp4_parser.cc"
    break;

  case 771: // $@119: %empty
#line 2700 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4274 "dhcp4_parser.cc"
    break;

  case 772: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2703 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 773: // $@120: %empty
#line 2711 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4296 "dhcp4_parser.cc"
    break;

  case 774: // config_control: "config-control" $@120 ":" "{" config_control_params "}"
#line 2717 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4306 "dhcp4_parser.cc"
    break;

  case 775: // $@121: %empty
#line 2723 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4316 "dhcp4_parser.cc"
    break;

  case 776: // sub_config_control: "{" $@121 config_control_params "}"
#line 2727 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4325 "dhcp4_parser.cc"
    break;

  case 779: // config_control_params: config_control_params ","
#line 2735 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4333 "dhcp4_parser.cc"
    break;

  case 782: // $@122: %empty
#line 2745 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4345 "dhcp4_parser.cc"
    break;

  case 783: // config_databases: "config-databases" $@122 ":" "[" database_list "]"
#line 2751 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4354 "dhcp4_parser.cc"
    break;

  case 784: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2756 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4364 "dhcp4_parser.cc"
    break;

  case 785: // $@123: %empty
#line 2764 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4376 "dhcp4_parser.cc"
    break;

  case 786: // loggers: "loggers" $@123 ":" "[" loggers_entries "]"
#line 2770 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4385 "dhcp4_parser.cc"
    break;

  case 789: // loggers_entries: loggers_entries ","
#line 2779 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4393 "dhcp4_parser.cc"
    break;

  case 790: // $@124: %empty
#line 2785 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4403 "dhcp4_parser.cc"
    break;

  case 791: // logger_entry: "{" $@124 logger_params "}"
#line 2789 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 794: // logger_params: logger_params ","
#line 2795 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4419 "dhcp4_parser.cc"
    break;

  case 802: // debuglevel: "debuglevel" ":" "integer"
#line 2809 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4429 "dhcp4_parser.cc"
    break;

  case 803: // $@125: %empty
#line 2815 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4438 "dhcp4_parser.cc"
    break;

  case 804: // severity: "severity" $@125 ":" "constant string"
#line 2818 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4448 "dhcp4_parser.cc"
    break;

  case 805: // $@126: %empty
#line 2824 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4460 "dhcp4_parser.cc"
    break;

  case 806: // output_options_list: "output-options" $@126 ":" "[" output_options_list_content "]"
#line 2830 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4469 "dhcp4_parser.cc"
    break;

  case 809: // output_options_list_content: output_options_list_content ","
#line 2837 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4477 "dhcp4_parser.cc"
    break;

  case 810: // $@127: %empty
#line 2842 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4487 "dhcp4_parser.cc"
    break;

  case 811: // output_entry: "{" $@127 output_params_list "}"
#line 2846 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4495 "dhcp4_parser.cc"
    break;

  case 814: // output_params_list: output_params_list ","
#line 2852 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4503 "dhcp4_parser.cc"
    break;

  case 820: // $@128: %empty
#line 2864 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4512 "dhcp4_parser.cc"
    break;

  case 821: // output: "output" $@128 ":" "constant string"
#line 2867 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4522 "dhcp4_parser.cc"
    break;

  case 822: // flush: "flush" ":" "boolean"
#line 2873 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 823: // maxsize: "maxsize" ":" "integer"
#line 2879 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 824: // maxver: "maxver" ":" "integer"
#line 2885 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 825: // $@129: %empty
#line 2891 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 826: // pattern: "pattern" $@129 ":" "constant string"
#line 2894 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4571 "dhcp4_parser.cc"
    break;

  case 827: // $@130: %empty
#line 2900 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4583 "dhcp4_parser.cc"
    break;

  case 828: // compatibility: "compatibility" $@130 ":" "{" compatibility_params "}"
#line 2906 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4592 "dhcp4_parser.cc"
    break;

  case 831: // compatibility_params: compatibility_params ","
#line 2913 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4600 "dhcp4_parser.cc"
    break;

  case 837: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2925 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4610 "dhcp4_parser.cc"
    break;

  case 838: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 2931 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4620 "dhcp4_parser.cc"
    break;

  case 839: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 2937 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4630 "dhcp4_parser.cc"
    break;

  case 840: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2943 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4640 "dhcp4_parser.cc"
    break;


#line 4644 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -985;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     408,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,    47,    39,    42,    55,    60,    80,
     109,   115,   117,   127,   129,   137,   141,   143,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,    39,  -158,    68,   188,   163,   625,
     -41,   296,    35,    92,   131,   -94,   276,    28,  -985,   148,
      62,   152,   150,   191,  -985,    15,  -985,  -985,  -985,  -985,
     162,   201,   211,  -985,  -985,  -985,   235,   246,  -985,  -985,
    -985,   288,   303,   305,   322,   350,   357,   363,   370,   374,
     375,   376,  -985,   377,   379,   380,   384,   385,  -985,  -985,
    -985,   386,   387,   391,   392,  -985,  -985,  -985,   393,  -985,
    -985,  -985,  -985,  -985,   394,   395,   397,  -985,  -985,  -985,
    -985,  -985,   398,  -985,  -985,  -985,  -985,  -985,  -985,   399,
     400,   401,  -985,  -985,   402,  -985,    49,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   405,   406,
     407,   411,  -985,    93,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
     412,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,    96,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   413,  -985,  -985,  -985,  -985,
     103,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   340,   409,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   415,  -985,  -985,   417,  -985,  -985,  -985,   420,
    -985,  -985,   418,   422,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,   423,   424,   433,
    -985,  -985,  -985,  -985,   431,   437,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   104,
    -985,  -985,  -985,   447,  -985,   448,  -985,   449,   451,  -985,
    -985,  -985,  -985,  -985,   111,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   453,   123,  -985,  -985,  -985,
    -985,    39,    39,  -985,   229,   454,  -985,  -985,   455,   456,
     458,   249,   251,   252,   465,   466,   467,   260,   259,   472,
     473,   474,   266,   269,   271,   273,   279,   274,   282,   284,
     291,   297,   301,   496,   302,   308,   294,   298,   304,   497,
     512,   514,   310,   311,   309,   313,   523,   525,   530,   323,
     533,   535,   536,   537,   538,   329,   333,   334,   543,   548,
     550,   551,   552,   346,   553,   556,   558,   560,   562,   563,
     355,   359,   362,   568,   574,  -985,   188,  -985,   575,   578,
     580,   381,   382,   372,   389,   163,  -985,   586,   588,   591,
     594,   599,   600,   410,   601,   616,   617,   625,  -985,   618,
     414,   -41,  -985,   620,   621,   622,   624,   626,   627,   629,
     631,  -985,   296,  -985,   632,   633,   416,   634,   636,   637,
     427,  -985,    92,   639,   429,   430,   432,  -985,   131,   642,
     644,   -52,  -985,   434,   646,   438,   649,   441,   450,   657,
     658,   276,  -985,   660,   452,    28,  -985,  -985,  -985,   662,
     661,   664,   666,   667,  -985,  -985,  -985,   463,   468,   469,
    -985,  -985,   670,   671,   674,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,   470,  -985,  -985,  -985,
    -985,  -985,   -15,   471,   490,  -985,  -985,  -985,  -985,   679,
     680,   681,  -985,   491,   206,   699,   698,   504,  -985,  -985,
    -985,   715,   717,   718,   719,   723,  -985,   724,   725,   728,
     729,   513,   526,  -985,  -985,  -985,   732,   734,  -985,   745,
     319,   160,  -985,  -985,  -985,  -985,  -985,   527,   539,   541,
     749,   545,   547,  -985,   745,   549,   748,  -985,   555,  -985,
    -985,   745,   557,   559,   567,   569,   570,   571,   572,  -985,
     573,   576,  -985,   577,   579,   581,  -985,  -985,   582,  -985,
    -985,  -985,  -985,   583,   698,  -985,  -985,   584,  -985,   585,
    -985,  -985,    19,   492,  -985,   755,  -985,  -985,    39,   188,
      28,   163,   349,  -985,  -985,  -985,  1041,  1041,   756,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   757,   758,
     761,  -985,  -985,  -985,  -985,  -985,  -985,   763,  -985,  -985,
    -985,   100,   765,   773,   779,    25,   -47,    86,   -83,   276,
    -985,  -985,   780,   -28,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   783,  -985,  -985,  -985,  -985,
     650,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,   756,  -985,   134,   144,   187,  -985,
    -985,   198,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   794,
     795,   796,   797,   798,   799,   800,   803,   804,   805,  -985,
     816,   817,  -985,  -985,  -985,  -985,  -985,   204,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   205,  -985,   829,   759,  -985,  -985,   830,   819,  -985,
    -985,   832,   820,  -985,  -985,   835,   839,  -985,  -985,   837,
     841,  -985,  -985,  -985,  -985,  -985,  -985,    30,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,    50,  -985,  -985,   840,   842,
    -985,  -985,   843,   844,  -985,   846,   849,   850,   851,   852,
     853,   208,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   854,
     855,   858,  -985,   239,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   286,  -985,  -985,  -985,   860,
    -985,   864,  -985,  -985,  -985,   300,  -985,  -985,  -985,  -985,
    -985,   312,  -985,    97,  -985,   865,   867,   868,   869,  -985,
     324,  -985,  -985,  -985,  -985,  -985,   663,  -985,   870,   845,
    -985,  -985,   871,  -985,   872,  -985,  -985,  -985,   873,   876,
     349,  -985,   877,   878,   879,   881,   673,   672,   675,   676,
     677,   682,   683,   684,   685,   686,   885,   678,   687,   888,
     890,   897,   898,  1041,  -985,  -985,  1041,  -985,   756,   625,
    -985,   757,    92,  -985,   758,   131,  -985,   761,   743,  -985,
     763,   100,  -985,   290,   765,  -985,   296,  -985,   773,   -94,
    -985,   779,   690,   691,   692,   693,   694,   695,    25,  -985,
     696,   697,   700,   -47,  -985,   905,   908,    86,  -985,   701,
     910,   702,   913,   -83,  -985,  -985,   -29,   780,  -985,   703,
     704,   705,   706,   -28,  -985,  -985,   920,   924,   -41,  -985,
     783,   925,  -985,  -985,   722,   726,  -985,   258,   733,   736,
     752,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   306,  -985,  -985,   753,   771,   774,   778,  -985,   330,
    -985,   332,  -985,   922,  -985,   929,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   336,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,   963,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
     962,   972,  -985,  -985,  -985,  -985,  -985,  -985,   986,  -985,
     342,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   785,   788,  -985,  -985,   792,  -985,    39,
    -985,  -985,   991,  -985,  -985,  -985,  -985,  -985,   344,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
     808,   348,  -985,   745,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   743,  -985,  1003,  1004,   806,
    -985,   290,  -985,  -985,  -985,  -985,  -985,  -985,  1006,   815,
    1026,   -29,  -985,  -985,  -985,  -985,  -985,   866,   887,  -985,
    -985,  1071,  -985,   889,  -985,  -985,  -985,  1072,  -985,  -985,
     287,  -985,    95,  1072,  -985,  -985,  1080,  1096,  1104,  -985,
     352,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  1105,   895,
     899,   900,  1107,    95,  -985,   902,  -985,  -985,  -985,   903,
    -985,  -985,  -985
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   207,     9,   387,    11,   597,    13,
     626,    15,   515,    17,   524,    19,   563,    21,   349,    23,
     743,    25,   775,    27,    46,    39,     0,     0,     0,     0,
       0,   628,     0,   526,   565,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   773,   192,   225,
       0,     0,     0,   648,   650,   652,     0,     0,   223,   236,
     238,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   149,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   378,   513,   554,     0,   152,
     173,   458,   613,   615,     0,     0,     0,   311,   675,   617,
     340,   361,     0,   326,   710,   724,   741,   180,   182,     0,
       0,     0,   785,   827,     0,   137,     0,    67,    70,    71,
      72,    73,    74,   107,   108,   109,   110,   111,    75,   103,
     133,   134,    92,    93,    94,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   113,   114,   125,   126,   127,
     129,   130,   131,   135,   136,    78,    79,   100,    80,    81,
      82,   128,    86,    87,    76,   104,   105,   106,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   112,   132,   209,   211,   215,     0,     0,
       0,     0,   206,     0,   194,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   442,   444,   446,   588,   440,   448,
       0,   452,   450,   670,   439,   392,   393,   394,   395,   396,
     419,   420,   421,   422,   423,   437,   409,   410,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   438,     0,   389,   399,   414,   415,   416,   400,   402,
     403,   405,   406,   407,   401,   397,   398,   417,   418,   404,
     411,   412,   413,   408,   610,     0,   609,   605,   606,   604,
       0,   599,   602,   603,   607,   608,   668,   654,   656,   658,
     662,   660,   666,   664,   647,   641,   645,   646,     0,   629,
     630,   642,   643,   644,   638,   633,   639,   635,   636,   637,
     640,   634,     0,   544,   285,     0,   548,   546,   551,     0,
     540,   541,     0,   527,   528,   531,   543,   532,   533,   534,
     550,   535,   536,   537,   538,   539,   581,     0,     0,     0,
     579,   580,   583,   584,     0,   566,   567,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   357,   359,   354,     0,
     351,   355,   356,     0,   760,     0,   763,     0,     0,   767,
     771,   758,   756,   757,     0,   745,   748,   749,   750,   751,
     752,   753,   754,   755,   782,     0,     0,   777,   780,   781,
      45,    50,     0,    37,    43,     0,    64,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    69,    66,     0,     0,
       0,     0,     0,     0,     0,   196,   208,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   391,   388,     0,
       0,   601,   598,     0,     0,     0,     0,     0,     0,     0,
       0,   627,   632,   516,     0,     0,     0,     0,     0,     0,
       0,   525,   530,     0,     0,     0,     0,   564,   569,     0,
       0,   353,   350,     0,     0,     0,     0,     0,     0,     0,
       0,   747,   744,     0,     0,   779,   776,    49,    41,     0,
       0,     0,     0,     0,   154,   155,   156,     0,     0,     0,
     190,   191,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     0,   185,   186,   157,
     158,   159,     0,     0,     0,   171,   172,   179,   184,     0,
       0,     0,   151,     0,     0,     0,     0,     0,   454,   455,
     456,     0,     0,     0,     0,     0,   709,     0,     0,     0,
       0,     0,     0,   187,   188,   189,     0,     0,    68,     0,
       0,     0,   219,   220,   221,   222,   195,     0,     0,     0,
       0,     0,     0,   457,     0,     0,     0,   390,     0,   612,
     600,     0,     0,     0,     0,     0,     0,     0,     0,   631,
       0,     0,   542,     0,     0,     0,   553,   529,     0,   585,
     586,   587,   568,     0,     0,   352,   759,     0,   762,     0,
     765,   766,     0,     0,   746,     0,   784,   778,     0,     0,
       0,     0,     0,   649,   651,   653,     0,     0,   240,   150,
     162,   163,   164,   165,   166,   161,   168,   170,   380,   517,
     556,   153,   175,   176,   177,   178,   174,   460,    38,   614,
     616,     0,     0,   619,   342,     0,     0,     0,     0,     0,
     181,   183,     0,     0,    51,   210,   213,   214,   212,   217,
     218,   216,   443,   445,   447,   590,   441,   449,   453,   451,
       0,   611,   669,   655,   657,   659,   663,   661,   667,   665,
     545,   286,   549,   547,   552,   582,   358,   360,   761,   764,
     769,   770,   768,   772,   240,    42,     0,     0,     0,   232,
     234,     0,   227,   230,   231,   273,   278,   280,   282,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   296,
       0,     0,   303,   305,   307,   309,   272,     0,   247,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,     0,   245,     0,   241,   242,   385,     0,   381,   382,
     522,     0,   518,   519,   561,     0,   557,   558,   465,     0,
     461,   462,   321,   322,   323,   324,   325,     0,   313,   316,
     317,   318,   319,   320,   680,     0,   677,   624,     0,   620,
     621,   347,     0,   343,   344,     0,     0,     0,     0,     0,
       0,     0,   363,   366,   367,   368,   369,   370,   371,     0,
       0,     0,   336,     0,   328,   331,   332,   333,   334,   335,
     720,   722,   719,   717,   718,     0,   712,   715,   716,     0,
     736,     0,   739,   732,   733,     0,   726,   729,   730,   731,
     734,     0,   790,     0,   787,     0,     0,     0,     0,   836,
       0,   829,   832,   833,   834,   835,    53,   595,     0,   591,
     592,   673,     0,   672,     0,    62,   774,   193,     0,     0,
     229,   226,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,   224,   237,     0,   239,   244,     0,
     379,   384,   526,   514,   521,   565,   555,   560,     0,   459,
     464,   315,   312,   682,   679,   676,   628,   618,   623,     0,
     341,   346,     0,     0,     0,     0,     0,     0,   365,   362,
       0,     0,     0,   330,   327,     0,     0,   714,   711,     0,
       0,     0,     0,   728,   725,   742,     0,   789,   786,     0,
       0,     0,     0,   831,   828,    55,     0,    54,     0,   589,
     594,     0,   671,   783,     0,     0,   228,     0,     0,     0,
       0,   284,   287,   288,   289,   290,   291,   292,   293,   294,
     295,     0,   301,   302,     0,     0,     0,     0,   248,     0,
     243,     0,   383,     0,   520,     0,   559,   512,   487,   488,
     489,   473,   474,   492,   493,   494,   495,   496,   510,   476,
     477,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   511,   470,   471,   472,   485,   486,
     482,   483,   484,     0,   467,   475,   490,   491,   478,   479,
     480,   481,   463,   314,   704,   706,     0,   698,   699,   700,
     701,   702,   703,   691,   692,   696,   697,   693,   694,   695,
       0,   683,   684,   687,   688,   689,   690,   678,     0,   622,
       0,   345,   372,   373,   374,   375,   376,   377,   364,   337,
     338,   339,   329,     0,     0,   713,   735,     0,   738,     0,
     727,   805,     0,   803,   801,   795,   799,   800,     0,   792,
     797,   798,   796,   788,   837,   838,   839,   840,   830,    52,
      57,     0,   593,     0,   233,   235,   275,   276,   277,   274,
     279,   281,   283,   298,   299,   300,   297,   304,   306,   308,
     310,   246,   386,   523,   562,   469,   466,     0,     0,     0,
     681,   686,   625,   348,   721,   723,   737,   740,     0,     0,
       0,   794,   791,    56,   596,   674,   468,     0,     0,   708,
     685,     0,   802,     0,   793,   705,   707,     0,   804,   810,
       0,   807,     0,   809,   806,   820,     0,     0,     0,   825,
       0,   812,   815,   816,   817,   818,   819,   808,     0,     0,
       0,     0,     0,   814,   811,     0,   822,   823,   824,     0,
     813,   821,   826
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   -59,  -985,  -590,  -985,   435,
    -985,  -985,  -985,  -985,  -985,  -985,  -623,  -985,  -985,  -985,
     -67,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   419,   628,
     -37,   -30,    33,   -54,   -27,     0,    14,    16,    29,    44,
    -985,  -985,  -985,  -985,    46,  -985,  -985,    48,    51,    52,
      54,    56,    58,  -985,  -985,    59,  -985,    64,  -985,    66,
      69,    70,  -985,  -985,    71,    72,  -985,    74,  -985,    76,
    -985,  -985,  -985,  -985,  -985,    36,  -985,  -985,  -985,   421,
     611,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
     157,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   337,
    -985,   135,  -985,  -695,   142,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   -45,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   125,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   105,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   118,
    -985,  -985,  -985,   121,   589,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   113,  -985,  -985,  -985,  -985,  -985,  -985,  -984,
    -985,  -985,  -985,   145,  -985,  -985,  -985,   146,   615,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -982,  -985,    79,
    -985,    85,  -985,    77,    82,    84,  -985,  -985,  -985,  -985,
    -985,   139,  -985,  -985,   -91,   -62,  -985,  -985,  -985,  -985,
    -985,   147,  -985,  -985,  -985,   151,  -985,   595,  -985,   -63,
    -985,  -985,  -985,  -985,  -985,   -44,  -985,  -985,  -985,  -985,
    -985,     3,  -985,  -985,  -985,   149,  -985,  -985,  -985,   153,
    -985,   596,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,    99,  -985,  -985,  -985,    94,   630,
    -985,  -985,  -985,   -49,  -985,   -10,  -985,   -56,  -985,  -985,
    -985,   154,  -985,  -985,  -985,   155,  -985,   613,   -26,  -985,
      13,  -985,    26,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -981,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   156,  -985,
    -985,  -985,   -84,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   126,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   119,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   426,   593,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   457,   590,  -985,  -985,  -985,  -985,  -985,  -985,   122,
    -985,  -985,   -85,  -985,  -985,  -985,  -985,  -985,  -985,  -113,
    -985,  -985,  -120,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   124,  -985,  -985,  -985,  -985
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   729,
      82,    83,    39,    64,    79,    80,   745,   946,  1046,  1047,
     816,    41,    66,    85,   425,    86,    43,    67,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   453,   170,   171,   470,   172,   173,   174,   175,
     176,   177,   178,   459,   715,   179,   460,   180,   461,   181,
     182,   183,   471,   726,   184,   185,   488,   186,   489,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   429,   233,
     234,    45,    68,   235,   498,   236,   499,   748,   237,   500,
     751,   238,   239,   240,   241,   196,   439,   197,   430,   791,
     792,   793,   958,   794,   959,   198,   440,   199,   441,   843,
     844,   845,   986,   817,   818,   819,   962,  1209,   820,   963,
     821,   964,   822,   965,   823,   824,   535,   825,   826,   827,
     828,   829,   830,   831,   832,   833,   834,   976,  1216,   835,
     836,   837,   979,   838,   980,   839,   981,   840,   982,   200,
     478,   867,   868,   869,   870,   871,   872,   873,   201,   484,
     903,   904,   905,   906,   907,   202,   481,   882,   883,   884,
    1009,    59,    75,   389,   390,   391,   549,   392,   550,   203,
     482,   891,   892,   893,   894,   895,   896,   897,   898,   204,
     466,   847,   848,   849,   989,    47,    69,   282,   283,   284,
     511,   285,   507,   286,   508,   287,   509,   288,   512,   289,
     515,   290,   514,   205,   206,   207,   294,   208,   472,   859,
     860,   861,   998,  1123,  1124,   209,   467,    53,    72,   851,
     852,   853,   992,    55,    73,   352,   353,   354,   355,   356,
     357,   358,   534,   359,   538,   360,   537,   361,   362,   539,
     363,   210,   468,   855,   856,   857,   995,    57,    74,   374,
     375,   376,   377,   378,   543,   379,   380,   381,   382,   383,
     296,   510,   948,   949,   950,  1048,    49,    70,   310,   311,
     312,   519,   313,   211,   473,   212,   474,   213,   480,   878,
     879,   880,  1006,    51,    71,   328,   329,   330,   214,   434,
     215,   435,   216,   436,   334,   524,   335,   525,   336,   526,
     337,   528,   338,   527,   339,   530,   340,   529,   341,   523,
     303,   516,   952,   953,  1051,   217,   479,   875,   876,  1003,
    1150,  1151,  1152,  1153,  1154,  1227,  1155,  1228,  1156,   218,
     219,   485,   915,   916,   917,  1025,   918,  1026,   220,   486,
     925,   926,   927,   928,  1030,   929,   930,  1032,   221,   487,
      61,    76,   404,   405,   406,   407,   554,   408,   409,   556,
     410,   411,   412,   559,   782,   413,   560,   222,   428,    63,
      77,   416,   417,   418,   563,   419,   223,   493,   933,   934,
    1036,  1188,  1189,  1190,  1191,  1240,  1192,  1238,  1260,  1261,
    1262,  1270,  1271,  1272,  1278,  1273,  1274,  1275,  1276,  1282,
     224,   494,   940,   941,   942,   943,   944,   945
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     155,   232,   254,   306,   324,    78,   350,   370,   388,   401,
     342,   372,   841,   299,  1116,   258,  1117,  1131,   426,   242,
     297,   314,   326,   427,   364,   384,   728,   402,   351,   371,
     373,   758,   255,  1001,   132,   133,  1002,   780,   762,   256,
     414,   415,   259,   300,    29,   331,    30,    28,    31,    40,
     386,   387,   496,  1004,    81,   127,  1005,   497,   243,   298,
     315,   327,    42,   365,   385,   421,   403,    44,   344,   260,
     132,   133,   295,   309,   325,   304,   132,   133,    84,   919,
     920,   921,   301,   261,   332,   262,   251,    46,   132,   133,
     252,   305,   386,   387,   728,   302,   505,   333,   263,   517,
    1037,   506,   257,  1038,   518,   281,   521,   551,   899,   900,
     901,   522,   552,   264,   561,   265,    48,   266,   154,   562,
     267,   268,    50,   269,    52,   270,   565,   271,   272,   922,
     126,   566,   343,   273,    54,   274,    56,   496,   275,   276,
     277,   278,   955,   279,    58,   280,   291,   565,    60,   307,
      62,   292,   956,   293,   420,   308,   422,  1181,   423,  1182,
    1183,   710,   711,   712,   713,   154,   431,   935,   936,   937,
     938,   154,   885,   886,   887,   888,   889,   890,   225,   226,
     749,   750,   227,   154,   154,   228,   229,   230,   231,   344,
     505,   345,   346,   781,   424,   957,   347,   348,   349,    87,
     714,   960,    88,   132,   133,   432,   961,   983,   983,   132,
     133,  1018,   984,   985,    89,   433,  1019,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   344,   366,
     345,   346,   367,   368,   369,   862,   863,   864,   865,   437,
     866,  1116,  1023,  1117,  1131,   910,   911,  1024,   132,   133,
     438,    32,    33,    34,    35,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     132,   133,  1265,   126,   127,  1266,  1267,  1268,  1269,  1027,
    1263,  1079,   442,  1264,  1028,   128,   129,   130,   154,  1206,
    1207,  1208,   131,  1033,   154,   132,   133,   443,  1034,   444,
     134,   135,   136,   137,   138,   561,   722,   723,   724,   725,
    1035,   139,    93,    94,    95,    96,   445,  1043,    93,    94,
      95,   140,  1044,   983,   141,   517,   746,   747,  1221,  1225,
    1222,   142,   143,   154,  1226,   551,   144,  1241,   531,   145,
    1233,   521,  1242,   146,   446,  1283,  1244,   101,   102,   103,
    1284,   447,   567,   568,  1213,  1214,  1215,   448,   147,   148,
     149,   150,   151,   152,   449,   154,   789,   790,   450,   451,
     452,   454,   153,   455,   456,   126,   127,   344,   457,   458,
     462,   463,   127,   132,   133,   464,   465,   469,   475,   476,
     154,   477,   483,   490,   491,   492,   495,   132,   133,   501,
     502,   503,   532,   132,   133,   504,   513,   520,  1134,  1135,
    1136,   536,   316,   533,   540,   542,   541,   544,   545,   155,
     317,   318,   319,   320,   321,   322,   323,   546,   232,   547,
     548,   569,   393,   394,   395,   396,   397,   398,   399,   400,
     254,   553,   555,   557,   306,   558,   242,   564,   570,   571,
     572,   299,   573,   258,   574,   324,   575,   576,   297,   577,
     578,   579,   314,   580,   581,   350,   582,   583,   584,   585,
     255,   370,   586,   326,   587,   372,   588,   256,   154,   590,
     259,   300,   589,   364,   401,   243,   591,   351,   592,   384,
     596,   602,   154,   371,   373,   593,   331,   298,   154,   599,
     594,   315,   402,   600,   595,   597,   603,   260,   604,   601,
     295,   598,   327,   607,   309,   605,   606,   609,   608,   610,
     301,   261,   365,   262,   611,   325,   612,   613,   385,   614,
     615,   616,   617,   302,   618,   332,   263,   621,   619,   620,
     257,   403,   622,   281,   623,   624,   625,   627,   333,   626,
     628,   264,   629,   265,   630,   266,   631,   632,   267,   268,
     633,   269,   636,   270,   634,   271,   272,   635,   637,   639,
    1245,   273,   640,   274,   641,   644,   275,   276,   277,   278,
     647,   279,   648,   280,   291,   649,   642,   643,   650,   292,
     307,   293,   645,   651,   652,   654,   308,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     655,   656,   658,   653,   661,   662,   663,   659,   664,   672,
     665,   666,   155,   667,   232,   668,   670,   671,   673,   785,
     674,   675,   676,   678,   679,   680,   683,   681,   684,   686,
     687,   688,   242,   689,   690,    91,    92,    93,    94,    95,
      96,   692,   693,   691,   695,   696,   698,   783,   699,   902,
     912,   700,   401,   701,   702,   703,   939,   706,   707,   708,
     704,   705,   709,   716,   718,   719,   720,   908,   913,   923,
     402,   243,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   717,   721,   727,    30,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   730,   244,   245,   246,
     731,   127,   732,   733,   734,   740,   909,   914,   924,   403,
     735,   736,   737,   129,   130,   738,   739,   742,   741,   752,
     247,   743,   132,   133,   248,   249,   250,   134,   135,   136,
     744,   753,   251,   754,   755,   760,   252,   756,   139,   757,
     784,   759,   988,   842,   846,   850,   253,   761,   854,   763,
     858,   764,   874,    91,    92,    93,    94,    95,    96,   765,
     877,   766,   767,   768,   769,   770,   881,   932,   771,   772,
     947,   773,   951,   774,   775,   776,   778,   779,   966,   967,
     968,   969,   970,   971,   972,   147,   148,   973,   974,   975,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     977,   978,   991,   994,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   987,   990,   154,   993,   127,
     344,   996,   997,   999,  1000,  1008,  1007,  1011,  1050,  1010,
    1012,   129,   130,  1013,  1014,  1015,  1016,  1017,  1020,  1021,
     132,   133,  1022,   249,  1029,   134,   135,   136,  1031,  1039,
     251,  1040,  1041,  1042,   252,  1045,  1049,  1054,  1053,  1052,
    1055,  1057,  1058,  1059,   253,  1060,  1061,  1062,  1063,  1071,
    1065,  1064,  1074,  1072,  1075,  1066,  1067,  1068,  1069,  1070,
    1073,  1076,  1077,  1162,  1163,  1164,  1165,  1166,  1167,  1173,
    1170,  1169,  1174,  1171,  1177,  1178,  1176,  1179,  1194,  1195,
    1196,  1197,   254,   147,   148,   350,  1199,  1200,   370,  1203,
    1223,  1087,   372,   299,  1204,   258,  1137,  1224,  1205,   324,
     297,  1143,   388,   364,  1091,  1210,   384,   351,  1211,  1126,
     371,   373,   255,  1115,  1145,   154,   902,   326,  1142,   256,
     912,  1088,   259,   300,  1212,  1217,  1138,  1229,  1089,  1184,
    1230,  1092,  1128,  1139,   908,  1231,   939,  1147,   913,   298,
     331,   306,   365,  1218,   923,   385,  1219,  1186,  1127,   260,
    1220,  1185,   295,  1146,  1232,  1239,   327,  1234,  1093,   314,
    1235,  1125,   301,   261,  1236,   262,  1144,  1247,  1248,   325,
    1251,  1129,  1094,   909,  1095,   302,  1148,   914,   263,   332,
    1243,  1249,   257,   924,  1130,   281,  1187,  1096,  1252,  1149,
    1253,  1090,   333,   264,  1114,   265,  1140,   266,   315,  1141,
     267,   268,  1097,   269,  1098,   270,  1099,   271,   272,  1100,
    1101,   309,  1102,   273,  1103,   274,  1104,  1105,   275,   276,
     277,   278,  1106,   279,  1107,   280,   291,  1108,  1109,  1110,
    1111,   292,  1112,   293,  1113,  1120,  1257,  1118,  1255,  1259,
    1121,   795,  1122,  1119,  1279,   796,   797,   798,   799,   800,
     801,   802,   803,   804,   805,   806,   807,   808,   809,  1256,
    1280,  1258,   810,   811,   812,   813,   814,   815,  1281,  1285,
    1286,  1289,  1287,  1288,  1291,  1292,   646,  1056,   786,   777,
    1237,   954,   788,  1080,   638,  1078,  1133,   307,  1172,  1161,
    1160,  1168,   657,   308,  1246,  1081,  1082,   677,   344,  1132,
     685,  1084,  1201,  1083,   682,   669,  1086,  1250,  1085,  1202,
    1277,   660,  1180,  1175,   694,   697,  1254,   787,  1087,  1193,
    1157,  1158,  1159,  1290,  1137,   931,     0,  1198,     0,  1143,
       0,  1091,     0,     0,  1184,     0,  1126,     0,     0,     0,
    1115,     0,  1145,     0,     0,     0,  1142,     0,  1088,     0,
       0,     0,  1186,     0,  1138,  1089,  1185,     0,  1092,  1128,
       0,  1139,     0,     0,     0,  1147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1127,     0,     0,     0,     0,
       0,  1146,     0,     0,     0,  1093,     0,     0,  1125,     0,
       0,  1187,     0,     0,  1144,     0,     0,     0,  1129,  1094,
       0,  1095,     0,     0,  1148,     0,     0,     0,     0,     0,
       0,  1130,     0,   154,  1096,     0,     0,  1149,  1090,     0,
       0,  1114,     0,     0,  1140,     0,     0,  1141,     0,  1097,
       0,  1098,     0,  1099,     0,     0,  1100,  1101,     0,  1102,
       0,  1103,     0,  1104,  1105,     0,     0,     0,     0,  1106,
       0,  1107,     0,     0,  1108,  1109,  1110,  1111,     0,  1112,
       0,  1113,  1120,     0,  1118,     0,     0,  1121,     0,  1122,
    1119
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   707,    69,   998,    69,   998,   998,     3,    68,
      69,    70,    71,     8,    73,    74,   616,    76,    73,    74,
      74,   654,    69,     3,   117,   118,     6,    18,   661,    69,
      12,    13,    69,    69,     5,    71,     7,     0,     9,     7,
     144,   145,     3,     3,   212,    96,     6,     8,    68,    69,
      70,    71,     7,    73,    74,     3,    76,     7,    97,    69,
     117,   118,    69,    70,    71,   116,   117,   118,    10,   162,
     163,   164,    69,    69,    71,    69,   127,     7,   117,   118,
     131,   132,   144,   145,   684,    69,     3,    71,    69,     3,
       3,     8,    69,     6,     8,    69,     3,     3,   155,   156,
     157,     8,     8,    69,     3,    69,     7,    69,   212,     8,
      69,    69,     7,    69,     7,    69,     3,    69,    69,   212,
      95,     8,    40,    69,     7,    69,     7,     3,    69,    69,
      69,    69,     8,    69,     7,    69,    69,     3,     7,    70,
       7,    69,     8,    69,     6,    70,     4,   186,     8,   188,
     189,   176,   177,   178,   179,   212,     4,   195,   196,   197,
     198,   212,   147,   148,   149,   150,   151,   152,    15,    16,
      20,    21,    19,   212,   212,    22,    23,    24,    25,    97,
       3,    99,   100,   174,     3,     8,   104,   105,   106,    11,
     215,     3,    14,   117,   118,     4,     8,     3,     3,   117,
     118,     3,     8,     8,    26,     4,     8,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    97,    98,
      99,   100,   101,   102,   103,   135,   136,   137,   138,     4,
     140,  1225,     3,  1225,  1225,   159,   160,     8,   117,   118,
       4,   212,   213,   214,   215,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
     117,   118,   187,    95,    96,   190,   191,   192,   193,     3,
       3,   986,     4,     6,     8,   107,   108,   109,   212,    41,
      42,    43,   114,     3,   212,   117,   118,     4,     8,     4,
     122,   123,   124,   125,   126,     3,   110,   111,   112,   113,
       8,   133,    32,    33,    34,    35,     4,     3,    32,    33,
      34,   143,     8,     3,   146,     3,    17,    18,     8,     3,
       8,   153,   154,   212,     8,     3,   158,     3,     8,   161,
       8,     3,     8,   165,     4,     3,     8,    67,    68,    69,
       8,     4,   421,   422,    58,    59,    60,     4,   180,   181,
     182,   183,   184,   185,     4,   212,    27,    28,     4,     4,
       4,     4,   194,     4,     4,    95,    96,    97,     4,     4,
       4,     4,    96,   117,   118,     4,     4,     4,     4,     4,
     212,     4,     4,     4,     4,     4,     4,   117,   118,     4,
       4,     4,     3,   117,   118,     4,     4,     4,   128,   129,
     130,     4,   126,     8,     4,     3,     8,     4,     4,   496,
     134,   135,   136,   137,   138,   139,   140,     4,   505,     8,
       3,   212,   166,   167,   168,   169,   170,   171,   172,   173,
     517,     4,     4,     4,   521,     4,   505,     4,     4,     4,
       4,   517,     4,   517,   215,   532,   215,   215,   517,     4,
       4,     4,   521,   213,   215,   542,     4,     4,     4,   213,
     517,   548,   213,   532,   213,   548,   213,   517,   212,   215,
     517,   517,   213,   542,   561,   505,   214,   542,   214,   548,
       4,     4,   212,   548,   548,   214,   532,   517,   212,   215,
     213,   521,   561,   215,   213,   213,     4,   517,     4,   215,
     517,   213,   532,   214,   521,   215,   215,     4,   215,     4,
     517,   517,   542,   517,     4,   532,   213,     4,   548,     4,
       4,     4,     4,   517,   215,   532,   517,     4,   215,   215,
     517,   561,     4,   517,     4,     4,     4,     4,   532,   213,
       4,   517,     4,   517,     4,   517,     4,     4,   517,   517,
     215,   517,     4,   517,   215,   517,   517,   215,     4,     4,
    1203,   517,     4,   517,     4,   213,   517,   517,   517,   517,
       4,   517,     4,   517,   517,     4,   215,   215,     4,   517,
     521,   517,   213,     4,     4,     4,   521,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
       4,     4,     4,   213,     4,     4,     4,   213,     4,   213,
       4,     4,   699,     4,   701,     4,     4,     4,     4,   698,
       4,     4,   215,     4,   215,   215,     4,   215,     4,   215,
       4,   213,   701,     4,   213,    30,    31,    32,    33,    34,
      35,     4,     4,   213,     4,   213,     4,   175,     7,   736,
     737,     7,   739,     7,     7,   212,   743,     7,     7,     5,
     212,   212,   212,   212,     5,     5,     5,   736,   737,   738,
     739,   701,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   212,   212,     5,     7,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,   212,    92,    93,    94,
       5,    96,     5,     5,     5,   212,   736,   737,   738,   739,
       7,     7,     7,   108,   109,     7,     7,     5,   212,   212,
     115,     7,   117,   118,   119,   120,   121,   122,   123,   124,
       5,   212,   127,   212,     5,     7,   131,   212,   133,   212,
       5,   212,     3,     7,     7,     7,   141,   212,     7,   212,
       7,   212,     7,    30,    31,    32,    33,    34,    35,   212,
       7,   212,   212,   212,   212,   212,     7,     7,   212,   212,
       7,   212,   142,   212,   212,   212,   212,   212,     4,     4,
       4,     4,     4,     4,     4,   180,   181,     4,     4,     4,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
       4,     4,     3,     3,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,     6,     6,   212,     6,    96,
      97,     6,     3,     6,     3,     3,     6,     3,     3,     6,
       4,   108,   109,     4,     4,     4,     4,     4,     4,     4,
     117,   118,     4,   120,     4,   122,   123,   124,     4,     4,
     127,     4,     4,     4,   131,   212,     6,     4,     6,     8,
       4,     4,     4,     4,   141,     4,   213,   215,   213,     4,
     213,   215,     4,   215,     4,   213,   213,   213,   213,   213,
     213,     4,     4,   213,   213,   213,   213,   213,   213,     4,
     213,   215,     4,   213,     4,   213,   215,     4,   215,   215,
     215,   215,   989,   180,   181,   992,     6,     3,   995,     4,
       8,   998,   995,   989,   212,   989,  1003,     8,   212,  1006,
     989,  1003,  1009,   992,   998,   212,   995,   992,   212,   998,
     995,   995,   989,   998,  1003,   212,  1023,  1006,  1003,   989,
    1027,   998,   989,   989,   212,   212,  1003,     4,   998,  1036,
       8,   998,   998,  1003,  1023,     3,  1043,  1003,  1027,   989,
    1006,  1048,   992,   212,  1033,   995,   212,  1036,   998,   989,
     212,  1036,   989,  1003,     8,     4,  1006,   212,   998,  1048,
     212,   998,   989,   989,   212,   989,  1003,     4,     4,  1006,
       4,   998,   998,  1023,   998,   989,  1003,  1027,   989,  1006,
     212,   215,   989,  1033,   998,   989,  1036,   998,   213,  1003,
       4,   998,  1006,   989,   998,   989,  1003,   989,  1048,  1003,
     989,   989,   998,   989,   998,   989,   998,   989,   989,   998,
     998,  1048,   998,   989,   998,   989,   998,   998,   989,   989,
     989,   989,   998,   989,   998,   989,   989,   998,   998,   998,
     998,   989,   998,   989,   998,   998,     5,   998,   212,     7,
     998,    40,   998,   998,     4,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,   212,
       4,   212,    61,    62,    63,    64,    65,    66,     4,     4,
     215,     4,   213,   213,   212,   212,   505,   960,   699,   684,
    1179,   784,   701,   988,   496,   983,  1001,  1048,  1023,  1011,
    1009,  1018,   517,  1048,  1225,   989,   991,   542,    97,  1000,
     551,   994,  1048,   992,   548,   532,   997,  1231,   995,  1050,
    1263,   521,  1033,  1027,   561,   565,  1241,   700,  1225,  1037,
    1004,  1006,  1008,  1283,  1231,   739,    -1,  1043,    -1,  1231,
      -1,  1225,    -1,    -1,  1241,    -1,  1225,    -1,    -1,    -1,
    1225,    -1,  1231,    -1,    -1,    -1,  1231,    -1,  1225,    -1,
      -1,    -1,  1241,    -1,  1231,  1225,  1241,    -1,  1225,  1225,
      -1,  1231,    -1,    -1,    -1,  1231,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1225,    -1,    -1,    -1,    -1,
      -1,  1231,    -1,    -1,    -1,  1225,    -1,    -1,  1225,    -1,
      -1,  1241,    -1,    -1,  1231,    -1,    -1,    -1,  1225,  1225,
      -1,  1225,    -1,    -1,  1231,    -1,    -1,    -1,    -1,    -1,
      -1,  1225,    -1,   212,  1225,    -1,    -1,  1231,  1225,    -1,
      -1,  1225,    -1,    -1,  1231,    -1,    -1,  1231,    -1,  1225,
      -1,  1225,    -1,  1225,    -1,    -1,  1225,  1225,    -1,  1225,
      -1,  1225,    -1,  1225,  1225,    -1,    -1,    -1,    -1,  1225,
      -1,  1225,    -1,    -1,  1225,  1225,  1225,  1225,    -1,  1225,
      -1,  1225,  1225,    -1,  1225,    -1,    -1,  1225,    -1,  1225,
    1225
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,     0,     5,
       7,     9,   212,   213,   214,   215,   231,   232,   233,   238,
       7,   247,     7,   252,     7,   307,     7,   421,     7,   502,
       7,   519,     7,   453,     7,   459,     7,   483,     7,   397,
       7,   586,     7,   605,   239,   234,   248,   253,   308,   422,
     503,   520,   454,   460,   484,   398,   587,   606,   231,   240,
     241,   212,   236,   237,    10,   249,   251,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    95,    96,   107,   108,
     109,   114,   117,   118,   122,   123,   124,   125,   126,   133,
     143,   146,   153,   154,   158,   161,   165,   180,   181,   182,
     183,   184,   185,   194,   212,   246,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     269,   270,   272,   273,   274,   275,   276,   277,   278,   281,
     283,   285,   286,   287,   290,   291,   293,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   321,   323,   331,   333,
     375,   384,   391,   405,   415,   439,   440,   441,   443,   451,
     477,   509,   511,   513,   524,   526,   528,   551,   565,   566,
     574,   584,   603,   612,   636,    15,    16,    19,    22,    23,
      24,    25,   246,   305,   306,   309,   311,   314,   317,   318,
     319,   320,   509,   511,    92,    93,    94,   115,   119,   120,
     121,   127,   131,   141,   246,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   270,   273,   274,   275,   276,
     277,   278,   281,   283,   285,   286,   287,   290,   291,   293,
     295,   301,   423,   424,   425,   427,   429,   431,   433,   435,
     437,   439,   440,   441,   442,   477,   496,   509,   511,   513,
     524,   526,   528,   546,   116,   132,   246,   435,   437,   477,
     504,   505,   506,   508,   509,   511,   126,   134,   135,   136,
     137,   138,   139,   140,   246,   477,   509,   511,   521,   522,
     523,   524,   526,   528,   530,   532,   534,   536,   538,   540,
     542,   544,   451,    40,    97,    99,   100,   104,   105,   106,
     246,   351,   461,   462,   463,   464,   465,   466,   467,   469,
     471,   473,   474,   476,   509,   511,    98,   101,   102,   103,
     246,   351,   465,   471,   485,   486,   487,   488,   489,   491,
     492,   493,   494,   495,   509,   511,   144,   145,   246,   399,
     400,   401,   403,   166,   167,   168,   169,   170,   171,   172,
     173,   246,   509,   511,   588,   589,   590,   591,   593,   594,
     596,   597,   598,   601,    12,    13,   607,   608,   609,   611,
       6,     3,     4,     8,     3,   250,     3,     8,   604,   304,
     324,     4,     4,     4,   525,   527,   529,     4,     4,   322,
     332,   334,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   268,     4,     4,     4,     4,     4,   279,
     282,   284,     4,     4,     4,     4,   416,   452,   478,     4,
     271,   288,   444,   510,   512,     4,     4,     4,   376,   552,
     514,   392,   406,     4,   385,   567,   575,   585,   292,   294,
       4,     4,     4,   613,   637,     4,     3,     8,   310,   312,
     315,     4,     4,     4,     4,     3,     8,   428,   430,   432,
     497,   426,   434,     4,   438,   436,   547,     3,     8,   507,
       4,     3,     8,   545,   531,   533,   535,   539,   537,   543,
     541,     8,     3,     8,   468,   352,     4,   472,   470,   475,
       4,     8,     3,   490,     4,     4,     4,     8,     3,   402,
     404,     3,     8,     4,   592,     4,   595,     4,     4,   599,
     602,     3,     8,   610,     4,     3,     8,   231,   231,   212,
       4,     4,     4,     4,   215,   215,   215,     4,     4,     4,
     213,   215,     4,     4,     4,   213,   213,   213,   213,   213,
     215,   214,   214,   214,   213,   213,     4,   213,   213,   215,
     215,   215,     4,     4,     4,   215,   215,   214,   215,     4,
       4,     4,   213,     4,     4,     4,     4,     4,   215,   215,
     215,     4,     4,     4,     4,     4,   213,     4,     4,     4,
       4,     4,     4,   215,   215,   215,     4,     4,   255,     4,
       4,     4,   215,   215,   213,   213,   306,     4,     4,     4,
       4,     4,     4,   213,     4,     4,     4,   424,     4,   213,
     505,     4,     4,     4,     4,     4,     4,     4,     4,   523,
       4,     4,   213,     4,     4,     4,   215,   463,     4,   215,
     215,   215,   487,     4,     4,   400,   215,     4,   213,     4,
     213,   213,     4,     4,   589,     4,   213,   608,     4,     7,
       7,     7,     7,   212,   212,   212,     7,     7,     5,   212,
     176,   177,   178,   179,   215,   280,   212,   212,     5,     5,
       5,   212,   110,   111,   112,   113,   289,     5,   233,   235,
     212,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     212,   212,     5,     7,     5,   242,    17,    18,   313,    20,
      21,   316,   212,   212,   212,     5,   212,   212,   242,   212,
       7,   212,   242,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   235,   212,   212,
      18,   174,   600,   175,     5,   231,   254,   607,   305,    27,
      28,   325,   326,   327,   329,    40,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      61,    62,    63,    64,    65,    66,   246,   339,   340,   341,
     344,   346,   348,   350,   351,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   365,   366,   367,   369,   371,
     373,   339,     7,   335,   336,   337,     7,   417,   418,   419,
       7,   455,   456,   457,     7,   479,   480,   481,     7,   445,
     446,   447,   135,   136,   137,   138,   140,   377,   378,   379,
     380,   381,   382,   383,     7,   553,   554,     7,   515,   516,
     517,     7,   393,   394,   395,   147,   148,   149,   150,   151,
     152,   407,   408,   409,   410,   411,   412,   413,   414,   155,
     156,   157,   246,   386,   387,   388,   389,   390,   509,   511,
     159,   160,   246,   509,   511,   568,   569,   570,   572,   162,
     163,   164,   212,   509,   511,   576,   577,   578,   579,   581,
     582,   588,     7,   614,   615,   195,   196,   197,   198,   246,
     638,   639,   640,   641,   642,   643,   243,     7,   498,   499,
     500,   142,   548,   549,   335,     8,     8,     8,   328,   330,
       3,     8,   342,   345,   347,   349,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   363,     4,     4,   368,
     370,   372,   374,     3,     8,     8,   338,     6,     3,   420,
       6,     3,   458,     6,     3,   482,     6,     3,   448,     6,
       3,     3,     6,   555,     3,     6,   518,     6,     3,   396,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   571,   573,     3,     8,     4,
     580,     4,   583,     3,     8,     8,   616,     3,     6,     4,
       4,     4,     4,     3,     8,   212,   244,   245,   501,     6,
       3,   550,     8,     6,     4,     4,   326,     4,     4,     4,
       4,   213,   215,   213,   215,   213,   213,   213,   213,   213,
     213,     4,   215,   213,     4,     4,     4,     4,   340,   339,
     337,   423,   419,   461,   457,   485,   481,   246,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   270,   273,
     274,   275,   276,   277,   278,   281,   283,   285,   286,   287,
     290,   291,   293,   295,   301,   351,   415,   433,   435,   437,
     439,   440,   441,   449,   450,   477,   509,   511,   524,   526,
     528,   546,   447,   378,   128,   129,   130,   246,   256,   257,
     258,   301,   351,   451,   477,   509,   511,   524,   526,   528,
     556,   557,   558,   559,   560,   562,   564,   554,   521,   517,
     399,   395,   213,   213,   213,   213,   213,   213,   408,   215,
     213,   213,   387,     4,     4,   569,   215,     4,   213,     4,
     577,   186,   188,   189,   246,   351,   509,   511,   617,   618,
     619,   620,   622,   615,   215,   215,   215,   215,   639,     6,
       3,   504,   500,     4,   212,   212,    41,    42,    43,   343,
     212,   212,   212,    58,    59,    60,   364,   212,   212,   212,
     212,     8,     8,     8,     8,     3,     8,   561,   563,     4,
       8,     3,     8,     8,   212,   212,   212,   231,   623,     4,
     621,     3,     8,   212,     8,   242,   450,     4,     4,   215,
     558,     4,   213,     4,   618,   212,   212,     5,   212,     7,
     624,   625,   626,     3,     6,   187,   190,   191,   192,   193,
     627,   628,   629,   631,   632,   633,   634,   625,   630,     4,
       4,     4,   635,     3,     8,     4,   215,   213,   213,     4,
     628,   212,   212
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   216,   218,   217,   219,   217,   220,   217,   221,   217,
     222,   217,   223,   217,   224,   217,   225,   217,   226,   217,
     227,   217,   228,   217,   229,   217,   230,   217,   231,   231,
     231,   231,   231,   231,   231,   232,   234,   233,   235,   236,
     236,   237,   237,   237,   239,   238,   240,   240,   241,   241,
     241,   243,   242,   244,   244,   245,   245,   245,   246,   248,
     247,   250,   249,   249,   251,   253,   252,   254,   254,   254,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   268,
     267,   269,   271,   270,   272,   273,   274,   275,   276,   277,
     279,   278,   280,   280,   280,   280,   280,   282,   281,   284,
     283,   285,   286,   288,   287,   289,   289,   289,   289,   290,
     292,   291,   294,   293,   295,   296,   297,   298,   299,   300,
     301,   302,   304,   303,   305,   305,   305,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   308,   307,   310,
     309,   312,   311,   313,   313,   315,   314,   316,   316,   317,
     318,   319,   320,   322,   321,   324,   323,   325,   325,   325,
     326,   326,   328,   327,   330,   329,   332,   331,   334,   333,
     335,   335,   336,   336,   336,   338,   337,   339,   339,   339,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   342,   341,   343,   343,   343,   345,   344,
     347,   346,   349,   348,   350,   352,   351,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   363,   362,   364,   364,
     364,   365,   366,   368,   367,   370,   369,   372,   371,   374,
     373,   376,   375,   377,   377,   377,   378,   378,   378,   378,
     378,   379,   380,   381,   382,   383,   385,   384,   386,   386,
     386,   387,   387,   387,   387,   387,   387,   388,   389,   390,
     392,   391,   393,   393,   394,   394,   394,   396,   395,   398,
     397,   399,   399,   399,   399,   400,   400,   402,   401,   404,
     403,   406,   405,   407,   407,   407,   408,   408,   408,   408,
     408,   408,   409,   410,   411,   412,   413,   414,   416,   415,
     417,   417,   418,   418,   418,   420,   419,   422,   421,   423,
     423,   423,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     426,   425,   428,   427,   430,   429,   432,   431,   434,   433,
     436,   435,   438,   437,   439,   440,   441,   442,   444,   443,
     445,   445,   446,   446,   446,   448,   447,   449,   449,   449,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   452,   451,   454,   453,   455,   455,   456,
     456,   456,   458,   457,   460,   459,   461,   461,   462,   462,
     462,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   464,   465,   466,   468,   467,   470,   469,   472,   471,
     473,   475,   474,   476,   478,   477,   479,   479,   480,   480,
     480,   482,   481,   484,   483,   485,   485,   486,   486,   486,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     488,   490,   489,   491,   492,   493,   494,   495,   497,   496,
     498,   498,   499,   499,   499,   501,   500,   503,   502,   504,
     504,   504,   505,   505,   505,   505,   505,   505,   505,   505,
     507,   506,   508,   510,   509,   512,   511,   514,   513,   515,
     515,   516,   516,   516,   518,   517,   520,   519,   521,   521,
     522,   522,   522,   523,   523,   523,   523,   523,   523,   523,
     523,   523,   523,   523,   523,   523,   523,   523,   525,   524,
     527,   526,   529,   528,   531,   530,   533,   532,   535,   534,
     537,   536,   539,   538,   541,   540,   543,   542,   545,   544,
     547,   546,   548,   550,   549,   552,   551,   553,   553,   553,
     555,   554,   556,   556,   557,   557,   557,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   559,   561,   560,   563,   562,   564,   565,
     567,   566,   568,   568,   568,   569,   569,   569,   569,   569,
     571,   570,   573,   572,   575,   574,   576,   576,   576,   577,
     577,   577,   577,   577,   577,   578,   580,   579,   581,   583,
     582,   585,   584,   587,   586,   588,   588,   588,   589,   589,
     589,   589,   589,   589,   589,   589,   589,   589,   589,   590,
     592,   591,   593,   595,   594,   596,   597,   599,   598,   600,
     600,   602,   601,   604,   603,   606,   605,   607,   607,   607,
     608,   608,   610,   609,   611,   613,   612,   614,   614,   614,
     616,   615,   617,   617,   617,   618,   618,   618,   618,   618,
     618,   618,   619,   621,   620,   623,   622,   624,   624,   624,
     626,   625,   627,   627,   627,   628,   628,   628,   628,   628,
     630,   629,   631,   632,   633,   635,   634,   637,   636,   638,
     638,   638,   639,   639,   639,   639,   639,   640,   641,   642,
     643
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     4,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       3,     3,     3,     0,     6,     0,     6,     1,     3,     2,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
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
       1,     0,     4,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     3,     3,     3,
       3
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
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
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
  "dhcp4o6_port", "control_socket", "$@108", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@109",
  "control_socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@116", "server_port",
  "sender_ip", "$@117", "sender_port", "max_queue_size", "ncr_protocol",
  "$@118", "ncr_protocol_value", "ncr_format", "$@119", "config_control",
  "$@120", "sub_config_control", "$@121", "config_control_params",
  "config_control_param", "config_databases", "$@122",
  "config_fetch_wait_time", "loggers", "$@123", "loggers_entries",
  "logger_entry", "$@124", "logger_params", "logger_param", "debuglevel",
  "severity", "$@125", "output_options_list", "$@126",
  "output_options_list_content", "output_entry", "$@127",
  "output_params_list", "output_params", "output", "$@128", "flush",
  "maxsize", "maxver", "pattern", "$@129", "compatibility", "$@130",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   310,   310,   310,   311,   311,   312,   312,   313,   313,
     314,   314,   315,   315,   316,   316,   317,   317,   318,   318,
     319,   319,   320,   320,   321,   321,   322,   322,   330,   331,
     332,   333,   334,   335,   336,   339,   344,   344,   355,   358,
     359,   362,   367,   373,   378,   378,   385,   386,   389,   393,
     397,   403,   403,   410,   411,   414,   418,   422,   432,   441,
     441,   456,   456,   470,   473,   479,   479,   488,   489,   490,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   567,   573,
     579,   585,   591,   597,   603,   609,   615,   621,   627,   633,
     633,   642,   648,   648,   657,   663,   669,   675,   681,   687,
     693,   693,   702,   705,   708,   711,   714,   720,   720,   729,
     729,   738,   747,   757,   757,   766,   769,   772,   775,   780,
     786,   786,   795,   795,   804,   810,   816,   822,   828,   834,
     840,   846,   852,   852,   864,   865,   866,   871,   872,   873,
     874,   875,   876,   877,   878,   879,   880,   883,   883,   892,
     892,   903,   903,   911,   912,   915,   915,   923,   925,   929,
     935,   941,   947,   953,   953,   966,   966,   977,   978,   979,
     984,   985,   988,   988,  1007,  1007,  1025,  1025,  1038,  1038,
    1049,  1050,  1053,  1054,  1055,  1060,  1060,  1070,  1071,  1072,
    1077,  1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,
    1087,  1088,  1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,
    1097,  1098,  1099,  1102,  1102,  1110,  1111,  1112,  1115,  1115,
    1124,  1124,  1133,  1133,  1142,  1148,  1148,  1157,  1163,  1169,
    1175,  1181,  1187,  1193,  1199,  1205,  1211,  1211,  1219,  1220,
    1221,  1224,  1230,  1236,  1236,  1245,  1245,  1254,  1254,  1263,
    1263,  1272,  1272,  1283,  1284,  1285,  1290,  1291,  1292,  1293,
    1294,  1297,  1302,  1307,  1312,  1317,  1324,  1324,  1337,  1338,
    1339,  1344,  1345,  1346,  1347,  1348,  1349,  1352,  1358,  1364,
    1370,  1370,  1381,  1382,  1385,  1386,  1387,  1392,  1392,  1402,
    1402,  1412,  1413,  1414,  1417,  1420,  1421,  1424,  1424,  1433,
    1433,  1442,  1442,  1454,  1455,  1456,  1461,  1462,  1463,  1464,
    1465,  1466,  1469,  1475,  1481,  1487,  1493,  1499,  1508,  1508,
    1522,  1523,  1526,  1527,  1528,  1537,  1537,  1563,  1563,  1574,
    1575,  1576,  1582,  1583,  1584,  1585,  1586,  1587,  1588,  1589,
    1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,
    1600,  1601,  1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,
    1610,  1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,
    1620,  1621,  1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,
    1632,  1632,  1641,  1641,  1650,  1650,  1659,  1659,  1668,  1668,
    1677,  1677,  1686,  1686,  1697,  1703,  1709,  1715,  1723,  1723,
    1735,  1736,  1740,  1741,  1742,  1747,  1747,  1755,  1756,  1757,
    1762,  1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1771,
    1772,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,
    1782,  1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,  1791,
    1792,  1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,
    1802,  1803,  1804,  1811,  1811,  1825,  1825,  1834,  1835,  1838,
    1839,  1840,  1847,  1847,  1862,  1862,  1876,  1877,  1880,  1881,
    1882,  1887,  1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,
    1896,  1899,  1901,  1907,  1909,  1909,  1918,  1918,  1927,  1927,
    1936,  1938,  1938,  1947,  1957,  1957,  1970,  1971,  1976,  1977,
    1978,  1985,  1985,  1997,  1997,  2009,  2010,  2015,  2016,  2017,
    2024,  2025,  2026,  2027,  2028,  2029,  2030,  2031,  2032,  2033,
    2036,  2038,  2038,  2047,  2049,  2051,  2057,  2063,  2072,  2072,
    2085,  2086,  2089,  2090,  2091,  2096,  2096,  2106,  2106,  2116,
    2117,  2118,  2123,  2124,  2125,  2126,  2127,  2128,  2129,  2130,
    2133,  2133,  2142,  2148,  2148,  2173,  2173,  2203,  2203,  2214,
    2215,  2218,  2219,  2220,  2225,  2225,  2234,  2234,  2243,  2244,
    2247,  2248,  2249,  2255,  2256,  2257,  2258,  2259,  2260,  2261,
    2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2272,  2272,
    2281,  2281,  2290,  2290,  2299,  2299,  2308,  2308,  2317,  2317,
    2326,  2326,  2335,  2335,  2344,  2344,  2353,  2353,  2362,  2362,
    2376,  2376,  2387,  2390,  2390,  2404,  2404,  2415,  2416,  2417,
    2422,  2422,  2432,  2433,  2436,  2437,  2438,  2443,  2444,  2445,
    2446,  2447,  2448,  2449,  2450,  2451,  2452,  2453,  2454,  2455,
    2456,  2457,  2458,  2461,  2463,  2463,  2472,  2472,  2481,  2489,
    2497,  2497,  2508,  2509,  2510,  2515,  2516,  2517,  2518,  2519,
    2522,  2522,  2531,  2531,  2543,  2543,  2556,  2557,  2558,  2563,
    2564,  2565,  2566,  2567,  2568,  2571,  2577,  2577,  2586,  2592,
    2592,  2602,  2602,  2615,  2615,  2625,  2626,  2627,  2632,  2633,
    2634,  2635,  2636,  2637,  2638,  2639,  2640,  2641,  2642,  2645,
    2651,  2651,  2660,  2666,  2666,  2675,  2681,  2687,  2687,  2696,
    2697,  2700,  2700,  2711,  2711,  2723,  2723,  2733,  2734,  2735,
    2741,  2742,  2745,  2745,  2756,  2764,  2764,  2777,  2778,  2779,
    2785,  2785,  2793,  2794,  2795,  2800,  2801,  2802,  2803,  2804,
    2805,  2806,  2809,  2815,  2815,  2824,  2824,  2835,  2836,  2837,
    2842,  2842,  2850,  2851,  2852,  2857,  2858,  2859,  2860,  2861,
    2864,  2864,  2873,  2879,  2885,  2891,  2891,  2900,  2900,  2911,
    2912,  2913,  2918,  2919,  2920,  2921,  2922,  2925,  2931,  2937,
    2943
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
#line 6268 "dhcp4_parser.cc"

#line 2949 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
