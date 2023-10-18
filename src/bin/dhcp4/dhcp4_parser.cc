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
      case symbol_kind::S_hr_mode: // hr_mode
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
      case symbol_kind::S_hr_mode: // hr_mode
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
      case symbol_kind::S_hr_mode: // hr_mode
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
      case symbol_kind::S_hr_mode: // hr_mode
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
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 311 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 311 "dhcp4_parser.yy"
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
#line 320 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 321 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 322 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 323 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 324 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 325 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 326 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 327 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 328 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 329 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 330 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 331 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 332 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 340 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 341 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 342 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 343 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 344 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 345 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 346 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 349 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 354 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 359 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 365 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 372 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 377 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 383 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 388 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 391 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 399 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 403 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 407 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 413 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 415 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 424 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 428 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 432 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 442 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 451 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 456 "dhcp4_parser.yy"
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
#line 466 "dhcp4_parser.yy"
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
#line 475 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 483 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 489 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 493 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 500 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 138: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 577 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 139: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 583 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 140: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 589 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 141: // renew_timer: "renew-timer" ":" "integer"
#line 595 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 142: // rebind_timer: "rebind-timer" ":" "integer"
#line 601 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 143: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 607 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 144: // t1_percent: "t1-percent" ":" "floating point"
#line 613 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 145: // t2_percent: "t2-percent" ":" "floating point"
#line 619 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 146: // cache_threshold: "cache-threshold" ":" "floating point"
#line 625 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 147: // cache_max_age: "cache-max-age" ":" "integer"
#line 631 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 148: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 637 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 149: // $@20: %empty
#line 643 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 150: // server_tag: "server-tag" $@20 ":" "constant string"
#line 646 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 151: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 652 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 152: // $@21: %empty
#line 658 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 153: // allocator: "allocator" $@21 ":" "constant string"
#line 661 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 154: // echo_client_id: "echo-client-id" ":" "boolean"
#line 667 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 155: // match_client_id: "match-client-id" ":" "boolean"
#line 673 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 156: // authoritative: "authoritative" ":" "boolean"
#line 679 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 685 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 691 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 697 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 160: // $@22: %empty
#line 703 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 706 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 712 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 715 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 718 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 721 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 724 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 167: // $@23: %empty
#line 730 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 733 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 169: // $@24: %empty
#line 739 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 742 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 748 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 757 "dhcp4_parser.yy"
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

  case 173: // $@25: %empty
#line 767 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 770 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 776 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 779 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 782 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 785 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 790 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 180: // $@26: %empty
#line 796 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 799 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 182: // $@27: %empty
#line 805 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 808 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 814 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 820 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 826 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 187: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 832 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 188: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 838 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 189: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 844 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 190: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 850 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 191: // $@28: %empty
#line 856 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1656 "dhcp4_parser.cc"
    break;

  case 192: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 862 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 195: // interfaces_config_params: interfaces_config_params ","
#line 870 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1674 "dhcp4_parser.cc"
    break;

  case 206: // $@29: %empty
#line 887 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 207: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 891 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1693 "dhcp4_parser.cc"
    break;

  case 208: // $@30: %empty
#line 896 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1705 "dhcp4_parser.cc"
    break;

  case 209: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 902 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 210: // $@31: %empty
#line 907 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1723 "dhcp4_parser.cc"
    break;

  case 211: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 910 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1732 "dhcp4_parser.cc"
    break;

  case 212: // socket_type: "raw"
#line 915 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1738 "dhcp4_parser.cc"
    break;

  case 213: // socket_type: "udp"
#line 916 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1744 "dhcp4_parser.cc"
    break;

  case 214: // $@32: %empty
#line 919 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 215: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 922 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1762 "dhcp4_parser.cc"
    break;

  case 216: // outbound_interface_value: "same-as-inbound"
#line 927 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface_value: "use-routing"
#line 929 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1778 "dhcp4_parser.cc"
    break;

  case 218: // re_detect: "re-detect" ":" "boolean"
#line 933 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1788 "dhcp4_parser.cc"
    break;

  case 219: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 939 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 220: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 945 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 951 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 222: // $@33: %empty
#line 957 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1830 "dhcp4_parser.cc"
    break;

  case 223: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 963 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc"
    break;

  case 224: // $@34: %empty
#line 970 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1853 "dhcp4_parser.cc"
    break;

  case 225: // sanity_checks: "sanity-checks" $@34 ":" "{" sanity_checks_params "}"
#line 976 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 228: // sanity_checks_params: sanity_checks_params ","
#line 983 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1870 "dhcp4_parser.cc"
    break;

  case 231: // $@35: %empty
#line 992 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 232: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 995 "dhcp4_parser.yy"
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
#line 1899 "dhcp4_parser.cc"
    break;

  case 233: // $@36: %empty
#line 1011 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 234: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1014 "dhcp4_parser.yy"
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
#line 1927 "dhcp4_parser.cc"
    break;

  case 235: // $@37: %empty
#line 1029 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1939 "dhcp4_parser.cc"
    break;

  case 236: // hosts_database: "hosts-database" $@37 ":" "{" database_map_params "}"
#line 1035 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1950 "dhcp4_parser.cc"
    break;

  case 237: // $@38: %empty
#line 1042 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 238: // hosts_databases: "hosts-databases" $@38 ":" "[" database_list "]"
#line 1048 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 243: // not_empty_database_list: not_empty_database_list ","
#line 1059 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1979 "dhcp4_parser.cc"
    break;

  case 244: // $@39: %empty
#line 1064 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1989 "dhcp4_parser.cc"
    break;

  case 245: // database: "{" $@39 database_map_params "}"
#line 1068 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 248: // database_map_params: database_map_params ","
#line 1076 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2007 "dhcp4_parser.cc"
    break;

  case 272: // $@40: %empty
#line 1106 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 2016 "dhcp4_parser.cc"
    break;

  case 273: // database_type: "type" $@40 ":" db_type
#line 1109 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc"
    break;

  case 274: // db_type: "memfile"
#line 1114 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 2031 "dhcp4_parser.cc"
    break;

  case 275: // db_type: "mysql"
#line 1115 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 2037 "dhcp4_parser.cc"
    break;

  case 276: // db_type: "postgresql"
#line 1116 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 2043 "dhcp4_parser.cc"
    break;

  case 277: // $@41: %empty
#line 1119 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp4_parser.cc"
    break;

  case 278: // user: "user" $@41 ":" "constant string"
#line 1122 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2062 "dhcp4_parser.cc"
    break;

  case 279: // $@42: %empty
#line 1128 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2071 "dhcp4_parser.cc"
    break;

  case 280: // password: "password" $@42 ":" "constant string"
#line 1131 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2081 "dhcp4_parser.cc"
    break;

  case 281: // $@43: %empty
#line 1137 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp4_parser.cc"
    break;

  case 282: // host: "host" $@43 ":" "constant string"
#line 1140 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 283: // port: "port" ":" "integer"
#line 1146 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 284: // $@44: %empty
#line 1152 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 285: // name: "name" $@44 ":" "constant string"
#line 1155 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 286: // persist: "persist" ":" "boolean"
#line 1161 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 287: // lfc_interval: "lfc-interval" ":" "integer"
#line 1167 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2149 "dhcp4_parser.cc"
    break;

  case 288: // readonly: "readonly" ":" "boolean"
#line 1173 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 289: // connect_timeout: "connect-timeout" ":" "integer"
#line 1179 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 290: // read_timeout: "read-timeout" ":" "integer"
#line 1185 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2179 "dhcp4_parser.cc"
    break;

  case 291: // write_timeout: "write-timeout" ":" "integer"
#line 1191 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 292: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1197 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2199 "dhcp4_parser.cc"
    break;

  case 293: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1203 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 294: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1209 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 295: // $@45: %empty
#line 1215 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 296: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1218 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2237 "dhcp4_parser.cc"
    break;

  case 297: // on_fail_mode: "stop-retry-exit"
#line 1223 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2243 "dhcp4_parser.cc"
    break;

  case 298: // on_fail_mode: "serve-retry-exit"
#line 1224 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2249 "dhcp4_parser.cc"
    break;

  case 299: // on_fail_mode: "serve-retry-continue"
#line 1225 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2255 "dhcp4_parser.cc"
    break;

  case 300: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1228 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2265 "dhcp4_parser.cc"
    break;

  case 301: // max_row_errors: "max-row-errors" ":" "integer"
#line 1234 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2275 "dhcp4_parser.cc"
    break;

  case 302: // $@46: %empty
#line 1240 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2284 "dhcp4_parser.cc"
    break;

  case 303: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1243 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2294 "dhcp4_parser.cc"
    break;

  case 304: // $@47: %empty
#line 1249 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2303 "dhcp4_parser.cc"
    break;

  case 305: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1252 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 306: // $@48: %empty
#line 1258 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2322 "dhcp4_parser.cc"
    break;

  case 307: // key_file: "key-file" $@48 ":" "constant string"
#line 1261 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 308: // $@49: %empty
#line 1267 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 309: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1270 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 310: // $@50: %empty
#line 1276 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2363 "dhcp4_parser.cc"
    break;

  case 311: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1282 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2372 "dhcp4_parser.cc"
    break;

  case 314: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1289 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2380 "dhcp4_parser.cc"
    break;

  case 320: // duid_id: "duid"
#line 1301 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2389 "dhcp4_parser.cc"
    break;

  case 321: // hw_address_id: "hw-address"
#line 1306 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 322: // circuit_id: "circuit-id"
#line 1311 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 323: // client_id: "client-id"
#line 1316 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 324: // flex_id: "flex-id"
#line 1321 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 325: // $@51: %empty
#line 1328 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2437 "dhcp4_parser.cc"
    break;

  case 326: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1334 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2448 "dhcp4_parser.cc"
    break;

  case 329: // multi_threading_params: multi_threading_params ","
#line 1343 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2456 "dhcp4_parser.cc"
    break;

  case 336: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1356 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2466 "dhcp4_parser.cc"
    break;

  case 337: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1362 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2476 "dhcp4_parser.cc"
    break;

  case 338: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1368 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2486 "dhcp4_parser.cc"
    break;

  case 339: // $@52: %empty
#line 1374 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2498 "dhcp4_parser.cc"
    break;

  case 340: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1380 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 345: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1391 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2515 "dhcp4_parser.cc"
    break;

  case 346: // $@53: %empty
#line 1396 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp4_parser.cc"
    break;

  case 347: // hooks_library: "{" $@53 hooks_params "}"
#line 1400 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 348: // $@54: %empty
#line 1406 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 349: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1410 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 352: // hooks_params: hooks_params ","
#line 1418 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2563 "dhcp4_parser.cc"
    break;

  case 356: // $@55: %empty
#line 1428 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp4_parser.cc"
    break;

  case 357: // library: "library" $@55 ":" "constant string"
#line 1431 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2582 "dhcp4_parser.cc"
    break;

  case 358: // $@56: %empty
#line 1437 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp4_parser.cc"
    break;

  case 359: // parameters: "parameters" $@56 ":" map_value
#line 1440 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2600 "dhcp4_parser.cc"
    break;

  case 360: // $@57: %empty
#line 1446 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2612 "dhcp4_parser.cc"
    break;

  case 361: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1452 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2622 "dhcp4_parser.cc"
    break;

  case 364: // expired_leases_params: expired_leases_params ","
#line 1460 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2630 "dhcp4_parser.cc"
    break;

  case 371: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1473 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2640 "dhcp4_parser.cc"
    break;

  case 372: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1479 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2650 "dhcp4_parser.cc"
    break;

  case 373: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1485 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 374: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1491 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 375: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1497 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 376: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1503 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2690 "dhcp4_parser.cc"
    break;

  case 377: // $@58: %empty
#line 1512 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 378: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1518 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 383: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1532 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2719 "dhcp4_parser.cc"
    break;

  case 384: // $@59: %empty
#line 1541 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2729 "dhcp4_parser.cc"
    break;

  case 385: // subnet4: "{" $@59 subnet4_params "}"
#line 1545 "dhcp4_parser.yy"
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
#line 2755 "dhcp4_parser.cc"
    break;

  case 386: // $@60: %empty
#line 1567 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2765 "dhcp4_parser.cc"
    break;

  case 387: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1571 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2775 "dhcp4_parser.cc"
    break;

  case 390: // subnet4_params: subnet4_params ","
#line 1580 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2783 "dhcp4_parser.cc"
    break;

  case 440: // $@61: %empty
#line 1637 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 441: // subnet: "subnet" $@61 ":" "constant string"
#line 1640 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 442: // $@62: %empty
#line 1646 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 443: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1649 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 444: // $@63: %empty
#line 1655 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1658 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 446: // $@64: %empty
#line 1664 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc"
    break;

  case 447: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1667 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 448: // $@65: %empty
#line 1673 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp4_parser.cc"
    break;

  case 449: // interface: "interface" $@65 ":" "constant string"
#line 1676 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2878 "dhcp4_parser.cc"
    break;

  case 450: // $@66: %empty
#line 1682 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2887 "dhcp4_parser.cc"
    break;

  case 451: // client_class: "client-class" $@66 ":" "constant string"
#line 1685 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2897 "dhcp4_parser.cc"
    break;

  case 452: // $@67: %empty
#line 1691 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 453: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1697 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2918 "dhcp4_parser.cc"
    break;

  case 454: // reservations_global: "reservations-global" ":" "boolean"
#line 1702 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2928 "dhcp4_parser.cc"
    break;

  case 455: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1708 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 456: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1714 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2948 "dhcp4_parser.cc"
    break;

  case 457: // $@68: %empty
#line 1720 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 458: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1723 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2966 "dhcp4_parser.cc"
    break;

  case 459: // hr_mode: "disabled"
#line 1728 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2972 "dhcp4_parser.cc"
    break;

  case 460: // hr_mode: "out-of-pool"
#line 1729 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2978 "dhcp4_parser.cc"
    break;

  case 461: // hr_mode: "global"
#line 1730 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2984 "dhcp4_parser.cc"
    break;

  case 462: // hr_mode: "all"
#line 1731 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2990 "dhcp4_parser.cc"
    break;

  case 463: // id: "id" ":" "integer"
#line 1734 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 464: // $@69: %empty
#line 1742 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3012 "dhcp4_parser.cc"
    break;

  case 465: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1748 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3021 "dhcp4_parser.cc"
    break;

  case 470: // shared_networks_list: shared_networks_list ","
#line 1761 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3029 "dhcp4_parser.cc"
    break;

  case 471: // $@70: %empty
#line 1766 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3039 "dhcp4_parser.cc"
    break;

  case 472: // shared_network: "{" $@70 shared_network_params "}"
#line 1770 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3047 "dhcp4_parser.cc"
    break;

  case 475: // shared_network_params: shared_network_params ","
#line 1776 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3055 "dhcp4_parser.cc"
    break;

  case 520: // $@71: %empty
#line 1831 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3067 "dhcp4_parser.cc"
    break;

  case 521: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1837 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3076 "dhcp4_parser.cc"
    break;

  case 522: // $@72: %empty
#line 1845 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3085 "dhcp4_parser.cc"
    break;

  case 523: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1848 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3093 "dhcp4_parser.cc"
    break;

  case 528: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1860 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3101 "dhcp4_parser.cc"
    break;

  case 529: // $@73: %empty
#line 1867 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 530: // option_def_entry: "{" $@73 option_def_params "}"
#line 1871 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3123 "dhcp4_parser.cc"
    break;

  case 531: // $@74: %empty
#line 1882 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3133 "dhcp4_parser.cc"
    break;

  case 532: // sub_option_def: "{" $@74 option_def_params "}"
#line 1886 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3145 "dhcp4_parser.cc"
    break;

  case 537: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1902 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3153 "dhcp4_parser.cc"
    break;

  case 549: // code: "code" ":" "integer"
#line 1921 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3163 "dhcp4_parser.cc"
    break;

  case 551: // $@75: %empty
#line 1929 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3172 "dhcp4_parser.cc"
    break;

  case 552: // option_def_type: "type" $@75 ":" "constant string"
#line 1932 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 553: // $@76: %empty
#line 1938 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3191 "dhcp4_parser.cc"
    break;

  case 554: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1941 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3201 "dhcp4_parser.cc"
    break;

  case 555: // $@77: %empty
#line 1947 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3210 "dhcp4_parser.cc"
    break;

  case 556: // space: "space" $@77 ":" "constant string"
#line 1950 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3220 "dhcp4_parser.cc"
    break;

  case 558: // $@78: %empty
#line 1958 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3229 "dhcp4_parser.cc"
    break;

  case 559: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1961 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3239 "dhcp4_parser.cc"
    break;

  case 560: // option_def_array: "array" ":" "boolean"
#line 1967 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 561: // $@79: %empty
#line 1977 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3261 "dhcp4_parser.cc"
    break;

  case 562: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1983 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3270 "dhcp4_parser.cc"
    break;

  case 567: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1998 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3278 "dhcp4_parser.cc"
    break;

  case 568: // $@80: %empty
#line 2005 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3288 "dhcp4_parser.cc"
    break;

  case 569: // option_data_entry: "{" $@80 option_data_params "}"
#line 2009 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3297 "dhcp4_parser.cc"
    break;

  case 570: // $@81: %empty
#line 2017 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 571: // sub_option_data: "{" $@81 option_data_params "}"
#line 2021 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3316 "dhcp4_parser.cc"
    break;

  case 576: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2037 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3324 "dhcp4_parser.cc"
    break;

  case 588: // $@82: %empty
#line 2058 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3333 "dhcp4_parser.cc"
    break;

  case 589: // option_data_data: "data" $@82 ":" "constant string"
#line 2061 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3343 "dhcp4_parser.cc"
    break;

  case 592: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2071 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 593: // option_data_always_send: "always-send" ":" "boolean"
#line 2077 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 594: // option_data_never_send: "never-send" ":" "boolean"
#line 2083 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 595: // $@83: %empty
#line 2092 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3385 "dhcp4_parser.cc"
    break;

  case 596: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2098 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 601: // not_empty_pools_list: not_empty_pools_list ","
#line 2111 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3402 "dhcp4_parser.cc"
    break;

  case 602: // $@84: %empty
#line 2116 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3412 "dhcp4_parser.cc"
    break;

  case 603: // pool_list_entry: "{" $@84 pool_params "}"
#line 2120 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 604: // $@85: %empty
#line 2126 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 605: // sub_pool4: "{" $@85 pool_params "}"
#line 2130 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3442 "dhcp4_parser.cc"
    break;

  case 608: // pool_params: pool_params ","
#line 2138 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3450 "dhcp4_parser.cc"
    break;

  case 617: // $@86: %empty
#line 2153 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 618: // pool_entry: "pool" $@86 ":" "constant string"
#line 2156 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3469 "dhcp4_parser.cc"
    break;

  case 619: // pool_id: "pool-id" ":" "integer"
#line 2162 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 620: // $@87: %empty
#line 2168 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 621: // user_context: "user-context" $@87 ":" map_value
#line 2170 "dhcp4_parser.yy"
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
#line 3514 "dhcp4_parser.cc"
    break;

  case 622: // $@88: %empty
#line 2193 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3522 "dhcp4_parser.cc"
    break;

  case 623: // comment: "comment" $@88 ":" "constant string"
#line 2195 "dhcp4_parser.yy"
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
#line 3551 "dhcp4_parser.cc"
    break;

  case 624: // $@89: %empty
#line 2223 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 625: // reservations: "reservations" $@89 ":" "[" reservations_list "]"
#line 2229 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 630: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2240 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3580 "dhcp4_parser.cc"
    break;

  case 631: // $@90: %empty
#line 2245 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3590 "dhcp4_parser.cc"
    break;

  case 632: // reservation: "{" $@90 reservation_params "}"
#line 2249 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3599 "dhcp4_parser.cc"
    break;

  case 633: // $@91: %empty
#line 2254 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3609 "dhcp4_parser.cc"
    break;

  case 634: // sub_reservation: "{" $@91 reservation_params "}"
#line 2258 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3618 "dhcp4_parser.cc"
    break;

  case 639: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2269 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3626 "dhcp4_parser.cc"
    break;

  case 655: // $@92: %empty
#line 2292 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 656: // next_server: "next-server" $@92 ":" "constant string"
#line 2295 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 657: // $@93: %empty
#line 2301 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3654 "dhcp4_parser.cc"
    break;

  case 658: // server_hostname: "server-hostname" $@93 ":" "constant string"
#line 2304 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 659: // $@94: %empty
#line 2310 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 660: // boot_file_name: "boot-file-name" $@94 ":" "constant string"
#line 2313 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 661: // $@95: %empty
#line 2319 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 662: // ip_address: "ip-address" $@95 ":" "constant string"
#line 2322 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 663: // $@96: %empty
#line 2328 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 664: // ip_addresses: "ip-addresses" $@96 ":" list_strings
#line 2334 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 665: // $@97: %empty
#line 2339 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 666: // duid: "duid" $@97 ":" "constant string"
#line 2342 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 667: // $@98: %empty
#line 2348 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 668: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2351 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 669: // $@99: %empty
#line 2357 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 670: // client_id_value: "client-id" $@99 ":" "constant string"
#line 2360 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 671: // $@100: %empty
#line 2366 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3789 "dhcp4_parser.cc"
    break;

  case 672: // circuit_id_value: "circuit-id" $@100 ":" "constant string"
#line 2369 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 673: // $@101: %empty
#line 2375 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 674: // flex_id_value: "flex-id" $@101 ":" "constant string"
#line 2378 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 675: // $@102: %empty
#line 2384 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 676: // hostname: "hostname" $@102 ":" "constant string"
#line 2387 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 677: // $@103: %empty
#line 2393 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3849 "dhcp4_parser.cc"
    break;

  case 678: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2399 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 679: // $@104: %empty
#line 2407 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3870 "dhcp4_parser.cc"
    break;

  case 680: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2413 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3879 "dhcp4_parser.cc"
    break;

  case 683: // $@105: %empty
#line 2425 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 684: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2431 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3900 "dhcp4_parser.cc"
    break;

  case 687: // client_classes_list: client_classes_list ","
#line 2438 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3908 "dhcp4_parser.cc"
    break;

  case 688: // $@106: %empty
#line 2443 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 689: // client_class_entry: "{" $@106 client_class_params "}"
#line 2447 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 694: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2459 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3936 "dhcp4_parser.cc"
    break;

  case 712: // $@107: %empty
#line 2484 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3945 "dhcp4_parser.cc"
    break;

  case 713: // client_class_test: "test" $@107 ":" "constant string"
#line 2487 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3955 "dhcp4_parser.cc"
    break;

  case 714: // $@108: %empty
#line 2493 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3964 "dhcp4_parser.cc"
    break;

  case 715: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2496 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3974 "dhcp4_parser.cc"
    break;

  case 716: // only_if_required: "only-if-required" ":" "boolean"
#line 2502 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 717: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2510 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 718: // $@109: %empty
#line 2518 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 719: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2524 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4015 "dhcp4_parser.cc"
    break;

  case 722: // control_socket_params: control_socket_params ","
#line 2531 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4023 "dhcp4_parser.cc"
    break;

  case 728: // $@110: %empty
#line 2543 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 729: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2546 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 730: // $@111: %empty
#line 2552 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 731: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2555 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4061 "dhcp4_parser.cc"
    break;

  case 732: // $@112: %empty
#line 2564 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4073 "dhcp4_parser.cc"
    break;

  case 733: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2570 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 736: // queue_control_params: queue_control_params ","
#line 2579 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4092 "dhcp4_parser.cc"
    break;

  case 743: // enable_queue: "enable-queue" ":" "boolean"
#line 2592 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4102 "dhcp4_parser.cc"
    break;

  case 744: // $@113: %empty
#line 2598 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4111 "dhcp4_parser.cc"
    break;

  case 745: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2601 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 746: // capacity: "capacity" ":" "integer"
#line 2607 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 747: // $@114: %empty
#line 2613 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4140 "dhcp4_parser.cc"
    break;

  case 748: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2616 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4149 "dhcp4_parser.cc"
    break;

  case 749: // $@115: %empty
#line 2623 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 750: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2629 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4172 "dhcp4_parser.cc"
    break;

  case 751: // $@116: %empty
#line 2636 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 752: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2640 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 755: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2648 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4200 "dhcp4_parser.cc"
    break;

  case 774: // enable_updates: "enable-updates" ":" "boolean"
#line 2673 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4210 "dhcp4_parser.cc"
    break;

  case 775: // $@117: %empty
#line 2679 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4219 "dhcp4_parser.cc"
    break;

  case 776: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2682 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4229 "dhcp4_parser.cc"
    break;

  case 777: // server_port: "server-port" ":" "integer"
#line 2688 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4239 "dhcp4_parser.cc"
    break;

  case 778: // $@118: %empty
#line 2694 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4248 "dhcp4_parser.cc"
    break;

  case 779: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2697 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 780: // sender_port: "sender-port" ":" "integer"
#line 2703 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4268 "dhcp4_parser.cc"
    break;

  case 781: // max_queue_size: "max-queue-size" ":" "integer"
#line 2709 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4278 "dhcp4_parser.cc"
    break;

  case 782: // $@119: %empty
#line 2715 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4287 "dhcp4_parser.cc"
    break;

  case 783: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2718 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4296 "dhcp4_parser.cc"
    break;

  case 784: // ncr_protocol_value: "udp"
#line 2724 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4302 "dhcp4_parser.cc"
    break;

  case 785: // ncr_protocol_value: "tcp"
#line 2725 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4308 "dhcp4_parser.cc"
    break;

  case 786: // $@120: %empty
#line 2728 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4317 "dhcp4_parser.cc"
    break;

  case 787: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2731 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4327 "dhcp4_parser.cc"
    break;

  case 788: // $@121: %empty
#line 2738 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4336 "dhcp4_parser.cc"
    break;

  case 789: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2741 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4346 "dhcp4_parser.cc"
    break;

  case 790: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2748 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4356 "dhcp4_parser.cc"
    break;

  case 791: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2755 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4366 "dhcp4_parser.cc"
    break;

  case 792: // $@122: %empty
#line 2762 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4375 "dhcp4_parser.cc"
    break;

  case 793: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2765 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4384 "dhcp4_parser.cc"
    break;

  case 794: // $@123: %empty
#line 2771 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4393 "dhcp4_parser.cc"
    break;

  case 795: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2774 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4403 "dhcp4_parser.cc"
    break;

  case 796: // $@124: %empty
#line 2781 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4412 "dhcp4_parser.cc"
    break;

  case 797: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2784 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 798: // $@125: %empty
#line 2791 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4431 "dhcp4_parser.cc"
    break;

  case 799: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2794 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4441 "dhcp4_parser.cc"
    break;

  case 800: // $@126: %empty
#line 2803 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 801: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2809 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 802: // $@127: %empty
#line 2815 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4473 "dhcp4_parser.cc"
    break;

  case 803: // sub_config_control: "{" $@127 config_control_params "}"
#line 2819 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 806: // config_control_params: config_control_params ","
#line 2827 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4490 "dhcp4_parser.cc"
    break;

  case 809: // $@128: %empty
#line 2837 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4502 "dhcp4_parser.cc"
    break;

  case 810: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2843 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4511 "dhcp4_parser.cc"
    break;

  case 811: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2848 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4521 "dhcp4_parser.cc"
    break;

  case 812: // $@129: %empty
#line 2856 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4533 "dhcp4_parser.cc"
    break;

  case 813: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2862 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 816: // loggers_entries: loggers_entries ","
#line 2871 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4550 "dhcp4_parser.cc"
    break;

  case 817: // $@130: %empty
#line 2877 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4560 "dhcp4_parser.cc"
    break;

  case 818: // logger_entry: "{" $@130 logger_params "}"
#line 2881 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4568 "dhcp4_parser.cc"
    break;

  case 821: // logger_params: logger_params ","
#line 2887 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4576 "dhcp4_parser.cc"
    break;

  case 829: // debuglevel: "debuglevel" ":" "integer"
#line 2901 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4586 "dhcp4_parser.cc"
    break;

  case 830: // $@131: %empty
#line 2907 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4595 "dhcp4_parser.cc"
    break;

  case 831: // severity: "severity" $@131 ":" "constant string"
#line 2910 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4605 "dhcp4_parser.cc"
    break;

  case 832: // $@132: %empty
#line 2916 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4617 "dhcp4_parser.cc"
    break;

  case 833: // output_options_list: "output-options" $@132 ":" "[" output_options_list_content "]"
#line 2922 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4626 "dhcp4_parser.cc"
    break;

  case 836: // output_options_list_content: output_options_list_content ","
#line 2929 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4634 "dhcp4_parser.cc"
    break;

  case 837: // $@133: %empty
#line 2934 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4644 "dhcp4_parser.cc"
    break;

  case 838: // output_entry: "{" $@133 output_params_list "}"
#line 2938 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4652 "dhcp4_parser.cc"
    break;

  case 841: // output_params_list: output_params_list ","
#line 2944 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4660 "dhcp4_parser.cc"
    break;

  case 847: // $@134: %empty
#line 2956 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4669 "dhcp4_parser.cc"
    break;

  case 848: // output: "output" $@134 ":" "constant string"
#line 2959 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4679 "dhcp4_parser.cc"
    break;

  case 849: // flush: "flush" ":" "boolean"
#line 2965 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4689 "dhcp4_parser.cc"
    break;

  case 850: // maxsize: "maxsize" ":" "integer"
#line 2971 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4699 "dhcp4_parser.cc"
    break;

  case 851: // maxver: "maxver" ":" "integer"
#line 2977 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4709 "dhcp4_parser.cc"
    break;

  case 852: // $@135: %empty
#line 2983 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4718 "dhcp4_parser.cc"
    break;

  case 853: // pattern: "pattern" $@135 ":" "constant string"
#line 2986 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4728 "dhcp4_parser.cc"
    break;

  case 854: // $@136: %empty
#line 2992 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4740 "dhcp4_parser.cc"
    break;

  case 855: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2998 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4749 "dhcp4_parser.cc"
    break;

  case 858: // compatibility_params: compatibility_params ","
#line 3005 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4757 "dhcp4_parser.cc"
    break;

  case 864: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3017 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4767 "dhcp4_parser.cc"
    break;

  case 865: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3023 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 866: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3029 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4787 "dhcp4_parser.cc"
    break;

  case 867: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3035 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4797 "dhcp4_parser.cc"
    break;


#line 4801 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1025;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     423, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,    37,    31,    24,    60,    64,    82,
      94,   174,   182,   216,   219,   226,   228,   271, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,    31,  -176,   181,   130,   154,   273,
     -39,   535,   -15,   550,   350,  -114,   634,   103, -1025,    75,
     155,   268,   289,   297, -1025,    54, -1025, -1025, -1025, -1025,
     305,   321,   330, -1025, -1025, -1025,   331, -1025, -1025, -1025,
     334,   346,   348,   359,   369,   375,   378,   381,   382,   391,
     392, -1025,   401,   402,   403,   429,   430, -1025, -1025, -1025,
     438,   439,   441,   460, -1025, -1025, -1025,   464, -1025, -1025,
   -1025, -1025, -1025, -1025,   466,   469,   470, -1025, -1025, -1025,
   -1025, -1025,   471, -1025, -1025, -1025, -1025, -1025, -1025,   473,
     475,   477, -1025, -1025,   478, -1025,    62, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   480,   481,
     482,   484, -1025,    65, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
     485, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025,    72, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025,   487, -1025, -1025, -1025,
   -1025,    83, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   341,
     367, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025,   406, -1025, -1025,   488, -1025, -1025, -1025,
     489, -1025, -1025,   491,   494, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   497,   499,
     500, -1025, -1025, -1025, -1025,   503,   504, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
      91, -1025, -1025, -1025,   511, -1025, -1025,   513, -1025,   516,
     517, -1025, -1025,   519,   521, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025,   110, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
     523,   120, -1025, -1025, -1025, -1025,    31,    31, -1025,   163,
     524, -1025, -1025,   525,   526,   527,   309,   312,   314,   536,
     537,   538,   317,   539,   540,   545,   332,   333,   335,   337,
     340,   327,   343,   347,   349,   342,   352,   548,   353,   356,
     339,   355,   357,   552,   582,   587,   372,   383,   370,   385,
     588,   595,   600,   388,   607,   608,   613,   615,   616,   617,
     398,   399,   400,   621,   622,   623,   624,   625,   422,   641,
     643,   646,   652,   653,   654,   435,   436,   440,   658,   665,
   -1025,   130, -1025,   666,   667,   668,   455,   458,   461,   462,
     154, -1025,   681,   682,   683,   684,   691,   692,   476,   693,
     695,   696,   273, -1025,   697,   483,   -39, -1025,   698,   703,
     704,   705,   707,   708,   709,   710, -1025,   535, -1025,   711,
     712,   495,   714,   715,   731,   512, -1025,   550,   733,   514,
     528,   529, -1025,   350,   753,   754,    23, -1025,   541,   755,
     760,   546,   765,   551,   555,   766,   768,   557,   558,   770,
     775,   779,   780,   634, -1025,   784,   567,   103, -1025, -1025,
   -1025,   787,   785,   786,   788,   789, -1025, -1025, -1025,   576,
     577,   578, -1025,   793,   794,   797, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025,   596, -1025, -1025,
   -1025, -1025, -1025,  -136,   597,   598, -1025, -1025, -1025, -1025,
     815,   816,   817, -1025,   604,   345,   821,   820,   609,   336,
   -1025, -1025, -1025,   823,   824,   826,   827,   828, -1025,   829,
     830,   831,   832,   612,   619, -1025, -1025, -1025,   836,   835,
   -1025,   838,   157,   255, -1025, -1025, -1025, -1025, -1025,   626,
     629,   630,   839,   631,   632, -1025,   838,   633,   849, -1025,
     636, -1025, -1025,   838,   637,   638,   639,   640,   642,   644,
     645, -1025,   647,   648, -1025,   649,   650,   651, -1025, -1025,
     655, -1025, -1025, -1025, -1025,   656,   820, -1025, -1025,   657,
     660, -1025,   661, -1025, -1025,     5,   662, -1025, -1025,  -136,
     663,   664,   669, -1025,   840, -1025, -1025,    31,   130,   103,
     154,   258, -1025, -1025, -1025,   376,   376,   855, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025,   857,   860,   866,
   -1025, -1025, -1025, -1025, -1025, -1025,   867, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025,   -35,   868,   872,   876,   162,
     105,    77,   115,   634, -1025, -1025,   879,   -95, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   880,
   -1025, -1025, -1025, -1025,   148, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025,   855, -1025,   126,   128,   143, -1025, -1025,
     144, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   884,   885,
     887,   888,   889,   890,   891,   892,   893,   894, -1025,   895,
     896, -1025, -1025, -1025, -1025, -1025,   184, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
     187, -1025,   897,   898, -1025, -1025,   899,   901, -1025, -1025,
     900,   904, -1025, -1025,   902,   906, -1025, -1025,   905,   907,
   -1025, -1025, -1025, -1025, -1025, -1025,    38, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,    87, -1025, -1025,   908,   909, -1025,
   -1025,   910,   912, -1025,   913,   914,   915,   916,   917,   918,
     231, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   919,   920,
     921, -1025,   265, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,   266, -1025, -1025, -1025,   922, -1025,
     923, -1025, -1025, -1025,   276, -1025, -1025, -1025, -1025, -1025,
     293, -1025,   127, -1025,   924,   925,   926,   927, -1025,   329,
   -1025, -1025, -1025, -1025, -1025,   713, -1025,   929,   930, -1025,
   -1025, -1025, -1025,   928,   931, -1025, -1025, -1025,   934,   935,
     258, -1025,   936,   937,   938,   939,   680,   610,   722,   689,
     723,   724,   725,   726,   727,   728,   947,   729,   730,   950,
     951,   952,   953,   376, -1025, -1025,   376, -1025,   855,   273,
   -1025,   857,   550, -1025,   860,   350, -1025,   866,   659, -1025,
     867,   -35, -1025,   195,   868, -1025,   535, -1025,   872,  -114,
   -1025,   876,   736,   737,   738,   739,   741,   742,   162, -1025,
     743,   744,   747,   105, -1025,   966,   970,    77, -1025,   761,
     973,   756,   984,   115, -1025, -1025,   214,   879, -1025,   771,
     781,   783,   802,   -95, -1025, -1025,   998,  1007,   -39, -1025,
     880,  1026, -1025, -1025,   813,   814, -1025,   208,   819,   847,
     852, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025,    -4, -1025, -1025,   911,   932,   933,   941, -1025,   364,
   -1025,   366, -1025,  1029, -1025,  1036, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,   368, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025,  1043, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025,  1040,  1047, -1025, -1025, -1025, -1025, -1025, -1025,  1052,
   -1025,   380, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,   942,   943, -1025, -1025,   944, -1025,
      31, -1025, -1025,  1057, -1025, -1025, -1025, -1025, -1025,   394,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025,   948,   395, -1025,   838, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025,   659, -1025,  1066,  1114,
     903, -1025,   195, -1025, -1025, -1025, -1025, -1025, -1025,  1116,
     946,  1117,   214, -1025, -1025, -1025, -1025, -1025,   949,   954,
   -1025, -1025,  1118, -1025,   955, -1025, -1025, -1025,  1119, -1025,
   -1025,   151, -1025,   -16,  1119, -1025, -1025,  1121,  1124,  1125,
   -1025,   410, -1025, -1025, -1025, -1025, -1025, -1025, -1025,  1126,
     956,   957,   959,  1127,   -16, -1025,   961, -1025, -1025, -1025,
     962, -1025, -1025, -1025
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   206,     9,   386,    11,   604,    13,
     633,    15,   522,    17,   531,    19,   570,    21,   348,    23,
     751,    25,   802,    27,    46,    39,     0,     0,     0,     0,
       0,   635,     0,   533,   572,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   800,   191,   224,
       0,     0,     0,   655,   657,   659,     0,   222,   235,   237,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,     0,     0,     0,     0,     0,   160,   167,   169,
       0,     0,     0,     0,   377,   520,   561,     0,   152,   173,
     464,   620,   622,   457,     0,     0,     0,   310,   683,   624,
     339,   360,     0,   325,   718,   732,   749,   180,   182,     0,
       0,     0,   812,   854,     0,   137,     0,    67,    70,    71,
      72,    73,    74,   108,   109,   110,   111,   112,    75,   103,
     134,   135,    92,    93,    94,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   114,   115,   126,   127,   128,
     130,   131,   132,   136,    78,    79,   100,    80,    81,    82,
     129,    86,    87,    76,   105,   106,   107,   104,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   113,   133,   208,   210,   214,     0,     0,
       0,     0,   205,     0,   193,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   442,   444,   446,   595,   440,   448,
       0,   452,   450,   679,   439,   391,   392,   393,   394,   395,
     419,   420,   421,   422,   423,   437,   409,   410,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   438,     0,   388,   398,   414,   415,   416,   399,   401,
     402,   405,   406,   407,   404,   400,   396,   397,   417,   418,
     403,   411,   412,   413,   408,   617,     0,   616,   612,   613,
     611,     0,   606,   609,   610,   614,   615,   677,   665,   667,
     671,   669,   675,   673,   661,   654,   648,   652,   653,     0,
     636,   637,   649,   650,   651,   645,   640,   646,   642,   643,
     644,   647,   641,     0,   551,   284,     0,   555,   553,   558,
       0,   547,   548,     0,   534,   535,   538,   550,   539,   540,
     541,   557,   542,   543,   544,   545,   546,   588,     0,     0,
       0,   586,   587,   590,   591,     0,   573,   574,   577,   578,
     579,   580,   581,   582,   583,   584,   585,   356,   358,   353,
       0,   350,   354,   355,     0,   788,   775,     0,   778,     0,
       0,   782,   786,     0,     0,   792,   794,   796,   798,   773,
     771,   772,     0,   753,   756,   757,   758,   759,   760,   761,
     762,   763,   768,   764,   765,   766,   767,   769,   770,   809,
       0,     0,   804,   807,   808,    45,    50,     0,    37,    43,
       0,    64,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    69,    66,     0,     0,     0,     0,     0,     0,     0,
     195,   207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   390,   387,     0,     0,   608,   605,     0,     0,
       0,     0,     0,     0,     0,     0,   634,   639,   523,     0,
       0,     0,     0,     0,     0,     0,   532,   537,     0,     0,
       0,     0,   571,   576,     0,     0,   352,   349,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   755,   752,     0,     0,   806,   803,    49,
      41,     0,     0,     0,     0,     0,   154,   155,   156,     0,
       0,     0,   190,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,   185,   186,
     157,   158,   159,     0,     0,     0,   171,   172,   179,   184,
       0,     0,     0,   151,     0,     0,     0,     0,     0,     0,
     454,   455,   456,     0,     0,     0,     0,     0,   717,     0,
       0,     0,     0,     0,     0,   187,   188,   189,     0,     0,
      68,     0,     0,     0,   218,   219,   220,   221,   194,     0,
       0,     0,     0,     0,     0,   463,     0,     0,     0,   389,
       0,   619,   607,     0,     0,     0,     0,     0,     0,     0,
       0,   638,     0,     0,   549,     0,     0,     0,   560,   536,
       0,   592,   593,   594,   575,     0,     0,   351,   774,     0,
       0,   777,     0,   780,   781,     0,     0,   790,   791,     0,
       0,     0,     0,   754,     0,   811,   805,     0,     0,     0,
       0,     0,   656,   658,   660,     0,     0,   239,   150,   162,
     163,   164,   165,   166,   161,   168,   170,   379,   524,   563,
     153,   175,   176,   177,   178,   174,   466,    38,   621,   623,
     459,   460,   461,   462,   458,     0,     0,   626,   341,     0,
       0,     0,     0,     0,   181,   183,     0,     0,    51,   209,
     212,   213,   211,   216,   217,   215,   443,   445,   447,   597,
     441,   449,   453,   451,     0,   618,   678,   666,   668,   672,
     670,   676,   674,   662,   552,   285,   556,   554,   559,   589,
     357,   359,   789,   776,   779,   784,   785,   783,   787,   793,
     795,   797,   799,   239,    42,     0,     0,     0,   231,   233,
       0,   226,   229,   230,   272,   277,   279,   281,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   295,     0,
       0,   302,   304,   306,   308,   271,     0,   246,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
       0,   244,     0,   240,   241,   384,     0,   380,   381,   529,
       0,   525,   526,   568,     0,   564,   565,   471,     0,   467,
     468,   320,   321,   322,   323,   324,     0,   312,   315,   316,
     317,   318,   319,   688,     0,   685,   631,     0,   627,   628,
     346,     0,   342,   343,     0,     0,     0,     0,     0,     0,
       0,   362,   365,   366,   367,   368,   369,   370,     0,     0,
       0,   335,     0,   327,   330,   331,   332,   333,   334,   728,
     730,   727,   725,   726,     0,   720,   723,   724,     0,   744,
       0,   747,   740,   741,     0,   734,   737,   738,   739,   742,
       0,   817,     0,   814,     0,     0,     0,     0,   863,     0,
     856,   859,   860,   861,   862,    53,   602,     0,   598,   599,
     663,   681,   682,     0,     0,    62,   801,   192,     0,     0,
     228,   225,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   248,   223,   236,     0,   238,   243,     0,
     378,   383,   533,   521,   528,   572,   562,   567,     0,   465,
     470,   314,   311,   690,   687,   684,   635,   625,   630,     0,
     340,   345,     0,     0,     0,     0,     0,     0,   364,   361,
       0,     0,     0,   329,   326,     0,     0,   722,   719,     0,
       0,     0,     0,   736,   733,   750,     0,   816,   813,     0,
       0,     0,     0,   858,   855,    55,     0,    54,     0,   596,
     601,     0,   680,   810,     0,     0,   227,     0,     0,     0,
       0,   283,   286,   287,   288,   289,   290,   291,   292,   293,
     294,     0,   300,   301,     0,     0,     0,     0,   247,     0,
     242,     0,   382,     0,   527,     0,   566,   519,   494,   495,
     496,   479,   480,   499,   500,   501,   502,   503,   517,   482,
     483,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   518,   476,   477,   478,   492,   493,
     489,   490,   491,   488,     0,   473,   481,   497,   498,   484,
     485,   486,   487,   469,   313,   712,   714,     0,   706,   707,
     708,   709,   710,   711,   699,   700,   704,   705,   701,   702,
     703,     0,   691,   692,   695,   696,   697,   698,   686,     0,
     629,     0,   344,   371,   372,   373,   374,   375,   376,   363,
     336,   337,   338,   328,     0,     0,   721,   743,     0,   746,
       0,   735,   832,     0,   830,   828,   822,   826,   827,     0,
     819,   824,   825,   823,   815,   864,   865,   866,   867,   857,
      52,    57,     0,   600,     0,   232,   234,   274,   275,   276,
     273,   278,   280,   282,   297,   298,   299,   296,   303,   305,
     307,   309,   245,   385,   530,   569,   475,   472,     0,     0,
       0,   689,   694,   632,   347,   729,   731,   745,   748,     0,
       0,     0,   821,   818,    56,   603,   664,   474,     0,     0,
     716,   693,     0,   829,     0,   820,   713,   715,     0,   831,
     837,     0,   834,     0,   836,   833,   847,     0,     0,     0,
     852,     0,   839,   842,   843,   844,   845,   846,   835,     0,
       0,     0,     0,     0,   841,   838,     0,   849,   850,   851,
       0,   840,   848,   853
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025,   -59, -1025,  -619, -1025,   427,
   -1025, -1025, -1025, -1025, -1025, -1025,  -650, -1025, -1025, -1025,
     -67, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   204,   627,
     -30,   -26,    26,   -54,   -37,   -27,     0,    14,    16,    45,
   -1025, -1025, -1025, -1025,    48, -1025, -1025,    50,    51,    52,
      53,    55,    56, -1025,   415,    58, -1025,    63, -1025,    66,
      68,    69, -1025, -1025,    70,    71, -1025,    73, -1025,    74,
   -1025, -1025, -1025, -1025, -1025,    33, -1025, -1025,   405,   620,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   136,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,   316, -1025,
     109, -1025,  -724,   118, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,   -45, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025,   101, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
      80, -1025, -1025, -1025, -1025, -1025, -1025, -1025,    93, -1025,
   -1025, -1025,    96,   580, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025,    89, -1025, -1025, -1025, -1025, -1025, -1025, -1024, -1025,
   -1025, -1025,   117, -1025, -1025, -1025,   121,   628, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1022, -1025,    78, -1025,
      79, -1025,    76,    81,    84,    86, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025,   111, -1025, -1025,  -117,   -62, -1025, -1025,
   -1025, -1025, -1025,   122, -1025, -1025, -1025,   123, -1025,   601,
   -1025,   -63, -1025, -1025, -1025, -1025, -1025,   -44, -1025, -1025,
   -1025, -1025, -1025,   -23, -1025, -1025, -1025,   134, -1025, -1025,
   -1025,   124, -1025,   589, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025,    67, -1025, -1025, -1025,
      85,   670, -1025, -1025, -1025,   -49, -1025,   -10, -1025,   -56,
   -1025, -1025, -1025,   129, -1025, -1025, -1025,   132, -1025,   671,
       3, -1025,    13, -1025,    29, -1025,   390, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1021, -1025, -1025, -1025, -1025, -1025,
     141, -1025, -1025, -1025,  -100, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025,   107, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025,   113, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025,   414,   605, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025,   463,   602, -1025, -1025, -1025,
   -1025, -1025, -1025,   114, -1025, -1025,   -92, -1025, -1025, -1025,
   -1025, -1025, -1025,  -111, -1025, -1025,  -130, -1025, -1025, -1025,
   -1025, -1025, -1025, -1025, -1025, -1025, -1025,   112, -1025, -1025,
   -1025, -1025
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   758,
      82,    83,    39,    64,    79,    80,   779,   985,  1086,  1087,
     855,    41,    66,    85,   440,    86,    43,    67,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   467,   170,   171,   484,   172,   173,   174,   175,
     176,   177,   178,   473,   744,   179,   474,   180,   475,   181,
     182,   183,   485,   755,   184,   185,   503,   186,   504,   187,
     188,   189,   190,   191,   192,   193,   194,   444,   233,   234,
      45,    68,   235,   513,   236,   514,   782,   237,   515,   785,
     238,   239,   240,   241,   195,   453,   196,   445,   830,   831,
     832,   998,   833,   999,   197,   454,   198,   455,   882,   883,
     884,  1026,   856,   857,   858,  1002,  1250,   859,  1003,   860,
    1004,   861,  1005,   862,   863,   550,   864,   865,   866,   867,
     868,   869,   870,   871,   872,   873,  1016,  1257,   874,   875,
     876,  1019,   877,  1020,   878,  1021,   879,  1022,   199,   493,
     906,   907,   908,   909,   910,   911,   912,   200,   499,   942,
     943,   944,   945,   946,   201,   496,   921,   922,   923,  1049,
      59,    75,   390,   391,   392,   564,   393,   565,   202,   497,
     930,   931,   932,   933,   934,   935,   936,   937,   203,   480,
     886,   887,   888,  1029,    47,    69,   282,   283,   284,   526,
     285,   522,   286,   523,   287,   524,   288,   527,   289,   530,
     290,   529,   204,   205,   206,   207,   489,   764,   295,   208,
     486,   898,   899,   900,  1038,  1164,  1165,   209,   481,    53,
      72,   890,   891,   892,  1032,    55,    73,   353,   354,   355,
     356,   357,   358,   359,   549,   360,   553,   361,   552,   362,
     363,   554,   364,   210,   482,   894,   895,   896,  1035,    57,
      74,   375,   376,   377,   378,   379,   558,   380,   381,   382,
     383,   384,   297,   525,   987,   988,   989,  1088,    49,    70,
     311,   312,   313,   534,   314,   211,   487,   212,   488,   213,
     495,   917,   918,   919,  1046,    51,    71,   329,   330,   331,
     214,   449,   215,   450,   216,   451,   335,   545,   992,  1091,
     336,   539,   337,   540,   338,   542,   339,   541,   340,   544,
     341,   543,   342,   538,   304,   531,   993,   217,   494,   914,
     915,  1043,  1191,  1192,  1193,  1194,  1195,  1268,  1196,  1269,
    1197,   218,   219,   500,   954,   955,   956,  1065,   957,  1066,
     220,   501,   964,   965,   966,   967,  1070,   968,   969,  1072,
     221,   502,    61,    76,   412,   413,   414,   415,   570,   416,
     417,   572,   418,   419,   420,   575,   817,   421,   576,   422,
     569,   423,   424,   425,   579,   426,   580,   427,   581,   428,
     582,   222,   443,    63,    77,   431,   432,   433,   585,   434,
     223,   508,   972,   973,  1076,  1229,  1230,  1231,  1232,  1281,
    1233,  1279,  1301,  1302,  1303,  1311,  1312,  1313,  1319,  1314,
    1315,  1316,  1317,  1323,   224,   509,   979,   980,   981,   982,
     983,   984
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     155,   232,   254,   307,   325,    78,   351,   371,   389,   409,
     343,   373,   880,   300,  1156,   258,  1157,  1172,   757,   242,
     298,   315,   327,   815,   365,   385,   792,   410,   352,   372,
     374,    40,   259,   796,   387,   388,    29,    28,    30,   255,
      31,  1041,   260,   256,  1042,    81,   296,   310,   326,   739,
     740,   741,   742,  1254,  1255,  1256,   126,   441,   243,   299,
     316,   328,   442,   366,   386,   511,   411,    42,   520,   261,
     512,    44,   301,   521,   332,   532,   305,   131,   132,   125,
     533,   435,   302,   262,   333,   263,   536,   757,   743,    46,
    1044,   537,   251,  1045,   566,   257,   252,   306,   303,   567,
     334,    48,   281,   901,   902,   903,   904,   154,   905,   974,
     975,   976,   977,   583,   264,   429,   430,   265,   584,   266,
     267,   268,   269,   587,   270,   271,   154,   272,   588,   511,
    1077,   587,   273,  1078,   995,   274,   996,   275,   276,   277,
     278,    87,   279,   280,    88,   291,   520,  1000,   308,   309,
     292,   997,  1001,   293,  1304,   294,    89,  1305,   436,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   225,
     226,   387,   388,   227,   780,   781,   228,   229,   230,   231,
    1306,    50,   154,  1307,  1308,  1309,  1310,  1023,   816,    52,
    1023,    84,  1024,   131,   132,  1025,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   131,   132,    54,   125,   126,    56,    93,    94,    95,
      96,   131,   132,    58,  1058,    60,   127,   128,   129,  1059,
     949,   950,  1156,   130,  1157,  1172,   131,   132,  1247,  1248,
    1249,   133,    32,    33,    34,    35,   134,   135,   136,   137,
     138,   100,   101,   102,   938,   939,   940,   139,  1063,  1067,
     131,   132,   437,  1064,  1068,   783,   784,   140,    62,  1073,
     141,   958,   959,   960,  1074,   828,   829,   142,   143,   125,
     126,   345,   144,   324,   990,   145,   583,   438,   154,   146,
     439,  1075,  1119,    91,    92,    93,    94,    95,    96,   446,
     345,   131,   132,   924,   925,   926,   927,   928,   929,   147,
     148,   149,   150,   151,   152,   447,   154,  1175,  1176,  1177,
     131,   132,  1083,   153,   448,   452,   961,  1084,   456,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   546,
     457,   154,   458,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   459,   244,   245,   246,  1023,   126,   532,
     547,  1266,  1262,   460,  1263,   154,  1267,   589,   590,   461,
     128,   129,   462,   566,   591,   463,   464,   247,  1274,   131,
     132,   248,   249,   250,   133,   465,   466,  1282,   536,   134,
     135,   136,  1283,  1285,   251,   468,   469,   470,   252,  1222,
     139,  1223,  1224,  1324,   548,   834,   154,   253,  1325,   835,
     836,   837,   838,   839,   840,   841,   842,   843,   844,   845,
     846,   847,   848,   471,   472,   154,   849,   850,   851,   852,
     853,   854,   476,   477,   155,   478,   345,   367,   346,   347,
     368,   369,   370,   232,   751,   752,   753,   754,   760,   761,
     762,   763,   147,   148,   479,   254,   131,   132,   483,   307,
     490,   242,   345,   491,   492,   498,   300,   505,   258,   506,
     325,   507,   510,   298,   516,   517,   518,   315,   519,   528,
     351,   535,   551,   555,   154,   259,   371,   557,   327,   556,
     373,   559,   255,   560,   561,   260,   256,   563,   365,   296,
     243,   562,   352,   310,   385,   568,   409,   571,   372,   374,
     573,   574,   299,   577,   326,   578,   316,   586,   592,   593,
     594,   595,   261,   596,   410,   301,   597,   328,   598,   602,
     599,   600,   601,   603,   604,   302,   262,   366,   263,   605,
     332,   611,   617,   386,   606,   607,   623,   608,   257,   609,
     333,   303,   610,   620,   615,   281,   612,    93,    94,    95,
     613,   154,   614,   411,   616,   618,   334,   264,   619,   621,
     265,   622,   266,   267,   268,   269,   624,   270,   271,   344,
     272,   625,   630,   628,  1286,   273,   626,   154,   274,   631,
     275,   276,   277,   278,   632,   279,   280,   627,   291,   629,
     633,   634,   635,   292,   308,   309,   293,   636,   294,   637,
     638,   639,   640,   641,   642,   643,   644,   645,   646,   647,
     126,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   648,   649,   345,   650,   346,   347,
     651,   131,   132,   348,   349,   350,   652,   653,   654,   655,
     656,   155,   658,   232,   657,   317,   131,   132,   824,   659,
     661,   662,   663,   318,   319,   320,   321,   322,   323,   664,
     324,   242,   665,   666,   667,   669,   670,   671,   672,    91,
      92,    93,    94,    95,    96,   673,   674,   676,   675,   677,
     678,   680,   683,   941,   951,   681,   409,   684,   685,   686,
     978,   687,   688,   689,   690,   692,   693,   694,   695,   696,
     243,   947,   952,   962,   410,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   697,   698,   700,   701,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     131,   132,   702,   703,   126,   345,   154,   705,   706,   709,
     948,   953,   963,   411,   710,   708,   128,   129,   711,   712,
     715,   154,   716,   713,   719,   131,   132,   714,   249,   720,
     133,   717,   718,   721,   722,   134,   135,   136,   724,   725,
     251,   727,   728,   729,   252,   730,   731,   732,   733,   734,
     735,   736,   737,   253,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   738,   745,   746,
     747,   748,   749,   407,   408,   750,   756,    30,   765,   766,
     759,   767,   768,   774,  1102,   769,   770,   771,   772,   773,
     775,   776,   777,   778,   789,   823,   818,   786,   147,   148,
     787,   788,   790,   791,   793,   154,   794,   795,   797,   798,
     799,   800,   881,   801,   885,   802,   803,   889,   804,   805,
     806,   807,   808,   893,   897,   913,   809,   810,   812,   916,
     154,   813,   814,   920,   820,   821,   971,   986,  1006,  1007,
     822,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1017,
    1018,  1028,  1101,  1027,  1031,  1030,  1033,  1034,  1036,  1037,
    1040,  1039,  1048,  1104,  1047,  1051,  1050,  1052,  1053,  1054,
    1055,  1056,  1057,  1060,  1061,  1062,  1069,  1071,  1079,  1080,
    1081,  1082,   825,  1090,  1085,  1089,  1092,  1093,  1094,  1095,
    1097,  1098,  1099,  1100,  1103,  1105,  1106,  1107,  1108,  1109,
    1110,  1111,  1113,  1112,  1114,  1115,  1116,  1117,  1203,  1204,
    1205,  1206,   254,  1207,  1208,   351,  1211,  1210,   371,  1212,
    1214,  1127,   373,   300,  1215,   258,  1178,  1218,  1219,   325,
     298,  1184,   389,   365,  1131,  1217,   385,   352,  1220,  1167,
     372,   374,   259,  1155,  1186,  1235,   941,   327,  1183,   255,
     951,  1132,   260,   256,  1240,  1236,   296,  1237,  1128,  1225,
    1241,  1133,  1129,  1179,   947,  1166,   978,  1180,   952,   299,
    1185,   307,   366,   326,   962,   386,  1238,  1227,  1168,   261,
    1244,  1226,   301,  1187,  1245,  1246,   328,  1264,  1134,   315,
    1251,  1169,   302,   262,  1265,   263,  1188,  1270,  1271,   332,
    1272,  1170,  1135,   948,  1136,   257,  1189,   953,   303,   333,
    1273,  1280,   281,   963,  1130,   310,  1228,  1171,  1252,  1181,
    1288,  1154,  1190,  1253,   264,   334,  1182,   265,   316,   266,
     267,   268,   269,  1137,   270,   271,  1138,   272,  1139,  1140,
    1141,  1142,   273,  1143,  1144,   274,  1145,   275,   276,   277,
     278,  1146,   279,   280,  1147,   291,  1148,  1149,  1150,  1151,
     292,  1152,  1153,   293,  1160,   294,  1158,  1159,  1289,  1161,
    1292,  1294,  1162,  1298,  1163,  1320,  1300,  1290,  1321,  1322,
    1326,  1330,  1258,   811,   819,   827,  1096,  1120,   660,   994,
     668,  1118,  1174,  1213,  1202,  1201,   707,  1209,  1122,  1287,
    1121,  1173,   704,  1259,  1260,  1123,  1124,  1243,   699,  1125,
     679,  1278,  1261,  1275,  1276,  1277,   308,   309,  1293,  1284,
    1296,  1126,  1291,  1242,  1216,  1297,  1299,  1200,  1199,  1328,
    1327,  1329,  1332,  1333,   991,  1198,  1221,   970,   723,   726,
    1295,  1234,   826,  1318,  1331,  1239,     0,     0,     0,  1127,
       0,     0,     0,     0,     0,  1178,   682,     0,     0,     0,
    1184,     0,  1131,     0,     0,  1225,     0,  1167,   691,     0,
       0,  1155,     0,  1186,     0,     0,     0,  1183,     0,  1132,
       0,     0,     0,  1227,     0,     0,  1128,  1226,     0,  1133,
    1129,     0,  1179,  1166,     0,     0,  1180,     0,     0,  1185,
       0,     0,     0,     0,     0,     0,  1168,     0,     0,     0,
       0,     0,  1187,     0,     0,     0,  1134,     0,     0,  1169,
       0,     0,  1228,     0,     0,  1188,     0,     0,     0,  1170,
    1135,     0,  1136,     0,     0,  1189,     0,     0,     0,     0,
       0,     0,  1130,     0,     0,  1171,     0,     0,  1181,  1154,
       0,  1190,     0,     0,     0,  1182,     0,     0,     0,     0,
       0,  1137,     0,     0,  1138,     0,  1139,  1140,  1141,  1142,
       0,  1143,  1144,     0,  1145,     0,     0,     0,     0,  1146,
       0,     0,  1147,     0,  1148,  1149,  1150,  1151,     0,  1152,
    1153,     0,  1160,     0,  1158,  1159,     0,  1161,     0,     0,
    1162,     0,  1163
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   736,    69,  1038,    69,  1038,  1038,   637,    68,
      69,    70,    71,    18,    73,    74,   676,    76,    73,    74,
      74,     7,    69,   683,   148,   149,     5,     0,     7,    69,
       9,     3,    69,    69,     6,   221,    69,    70,    71,   185,
     186,   187,   188,    57,    58,    59,    95,     3,    68,    69,
      70,    71,     8,    73,    74,     3,    76,     7,     3,    69,
       8,     7,    69,     8,    71,     3,   115,   116,   117,    94,
       8,     6,    69,    69,    71,    69,     3,   706,   224,     7,
       3,     8,   131,     6,     3,    69,   135,   136,    69,     8,
      71,     7,    69,   138,   139,   140,   141,   221,   143,   204,
     205,   206,   207,     3,    69,    12,    13,    69,     8,    69,
      69,    69,    69,     3,    69,    69,   221,    69,     8,     3,
       3,     3,    69,     6,     8,    69,     8,    69,    69,    69,
      69,    11,    69,    69,    14,    69,     3,     3,    70,    70,
      69,     8,     8,    69,     3,    69,    26,     6,     3,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    15,
      16,   148,   149,    19,    17,    18,    22,    23,    24,    25,
     196,     7,   221,   199,   200,   201,   202,     3,   183,     7,
       3,    10,     8,   116,   117,     8,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   116,   117,     7,    94,    95,     7,    32,    33,    34,
      35,   116,   117,     7,     3,     7,   106,   107,   108,     8,
     163,   164,  1266,   113,  1266,  1266,   116,   117,    40,    41,
      42,   121,   221,   222,   223,   224,   126,   127,   128,   129,
     130,    66,    67,    68,   159,   160,   161,   137,     3,     3,
     116,   117,     4,     8,     8,    20,    21,   147,     7,     3,
     150,   166,   167,   168,     8,    27,    28,   157,   158,    94,
      95,    96,   162,   145,   146,   165,     3,     8,   221,   169,
       3,     8,  1026,    30,    31,    32,    33,    34,    35,     4,
      96,   116,   117,   151,   152,   153,   154,   155,   156,   189,
     190,   191,   192,   193,   194,     4,   221,   132,   133,   134,
     116,   117,     3,   203,     4,     4,   221,     8,     4,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,     8,
       4,   221,     4,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     4,    91,    92,    93,     3,    95,     3,
       3,     3,     8,     4,     8,   221,     8,   436,   437,     4,
     107,   108,     4,     3,   221,     4,     4,   114,     8,   116,
     117,   118,   119,   120,   121,     4,     4,     3,     3,   126,
     127,   128,     8,     8,   131,     4,     4,     4,   135,   195,
     137,   197,   198,     3,     8,    39,   221,   144,     8,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,     4,     4,   221,    60,    61,    62,    63,
      64,    65,     4,     4,   511,     4,    96,    97,    98,    99,
     100,   101,   102,   520,   109,   110,   111,   112,   122,   123,
     124,   125,   189,   190,     4,   532,   116,   117,     4,   536,
       4,   520,    96,     4,     4,     4,   532,     4,   532,     4,
     547,     4,     4,   532,     4,     4,     4,   536,     4,     4,
     557,     4,     4,     4,   221,   532,   563,     3,   547,     8,
     563,     4,   532,     4,     4,   532,   532,     3,   557,   532,
     520,     8,   557,   536,   563,     4,   583,     4,   563,   563,
       4,     4,   532,     4,   547,     4,   536,     4,     4,     4,
       4,     4,   532,   224,   583,   532,   224,   547,   224,   222,
       4,     4,     4,     4,     4,   532,   532,   557,   532,     4,
     547,   224,     4,   563,   222,   222,     4,   222,   532,   222,
     547,   532,   222,   224,   222,   532,   223,    32,    33,    34,
     223,   221,   223,   583,   222,   222,   547,   532,   222,   224,
     532,   224,   532,   532,   532,   532,     4,   532,   532,    39,
     532,     4,     4,   223,  1244,   532,   224,   221,   532,     4,
     532,   532,   532,   532,     4,   532,   532,   224,   532,   224,
     222,     4,     4,   532,   536,   536,   532,     4,   532,     4,
       4,     4,   224,   224,   224,     4,     4,     4,     4,     4,
      95,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   222,     4,    96,     4,    98,    99,
       4,   116,   117,   103,   104,   105,     4,     4,     4,   224,
     224,   728,     4,   730,   224,   130,   116,   117,   727,     4,
       4,     4,     4,   138,   139,   140,   141,   142,   143,   224,
     145,   730,   224,   222,   222,     4,     4,     4,     4,    30,
      31,    32,    33,    34,    35,     4,     4,     4,   222,     4,
       4,     4,     4,   770,   771,   222,   773,     4,     4,     4,
     777,     4,     4,     4,     4,     4,     4,   222,     4,     4,
     730,   770,   771,   772,   773,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,     4,   224,     4,   224,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
     116,   117,   224,   224,    95,    96,   221,     4,     4,     4,
     770,   771,   772,   773,     4,   224,   107,   108,   222,     4,
       4,   221,     4,   222,     4,   116,   117,   222,   119,     4,
     121,   224,   224,     4,     4,   126,   127,   128,     4,   222,
     131,     4,     7,     7,   135,     7,     7,   221,   221,   221,
       7,     7,     5,   144,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   221,   221,   221,
       5,     5,     5,   189,   190,   221,     5,     7,     5,     5,
     221,     5,     5,   221,   224,     7,     7,     7,     7,     7,
     221,     5,     7,     5,     5,     5,   184,   221,   189,   190,
     221,   221,   221,   221,   221,   221,     7,   221,   221,   221,
     221,   221,     7,   221,     7,   221,   221,     7,   221,   221,
     221,   221,   221,     7,     7,     7,   221,   221,   221,     7,
     221,   221,   221,     7,   221,   221,     7,     7,     4,     4,
     221,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   222,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,   224,     6,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   728,     3,   221,     6,     8,     6,     4,     4,
       4,     4,     4,     4,   222,   222,   222,   222,   222,   222,
     222,     4,   222,   224,     4,     4,     4,     4,   222,   222,
     222,   222,  1029,   222,   222,  1032,   222,   224,  1035,   222,
       4,  1038,  1035,  1029,     4,  1029,  1043,     4,   222,  1046,
    1029,  1043,  1049,  1032,  1038,   224,  1035,  1032,     4,  1038,
    1035,  1035,  1029,  1038,  1043,   224,  1063,  1046,  1043,  1029,
    1067,  1038,  1029,  1029,     6,   224,  1029,   224,  1038,  1076,
       3,  1038,  1038,  1043,  1063,  1038,  1083,  1043,  1067,  1029,
    1043,  1088,  1032,  1046,  1073,  1035,   224,  1076,  1038,  1029,
       4,  1076,  1029,  1043,   221,   221,  1046,     8,  1038,  1088,
     221,  1038,  1029,  1029,     8,  1029,  1043,     4,     8,  1046,
       3,  1038,  1038,  1063,  1038,  1029,  1043,  1067,  1029,  1046,
       8,     4,  1029,  1073,  1038,  1088,  1076,  1038,   221,  1043,
       4,  1038,  1043,   221,  1029,  1046,  1043,  1029,  1088,  1029,
    1029,  1029,  1029,  1038,  1029,  1029,  1038,  1029,  1038,  1038,
    1038,  1038,  1029,  1038,  1038,  1029,  1038,  1029,  1029,  1029,
    1029,  1038,  1029,  1029,  1038,  1029,  1038,  1038,  1038,  1038,
    1029,  1038,  1038,  1029,  1038,  1029,  1038,  1038,     4,  1038,
       4,     4,  1038,     5,  1038,     4,     7,   224,     4,     4,
       4,     4,   221,   706,   719,   730,  1000,  1028,   511,   823,
     520,  1023,  1041,  1063,  1051,  1049,   566,  1058,  1031,  1266,
    1029,  1040,   563,   221,   221,  1032,  1034,  1090,   557,  1035,
     532,  1220,   221,   221,   221,   221,  1088,  1088,   222,   221,
     221,  1037,  1272,  1088,  1067,   221,   221,  1048,  1046,   222,
     224,   222,   221,   221,   794,  1044,  1073,   773,   583,   587,
    1282,  1077,   729,  1304,  1324,  1083,    -1,    -1,    -1,  1266,
      -1,    -1,    -1,    -1,    -1,  1272,   536,    -1,    -1,    -1,
    1272,    -1,  1266,    -1,    -1,  1282,    -1,  1266,   547,    -1,
      -1,  1266,    -1,  1272,    -1,    -1,    -1,  1272,    -1,  1266,
      -1,    -1,    -1,  1282,    -1,    -1,  1266,  1282,    -1,  1266,
    1266,    -1,  1272,  1266,    -1,    -1,  1272,    -1,    -1,  1272,
      -1,    -1,    -1,    -1,    -1,    -1,  1266,    -1,    -1,    -1,
      -1,    -1,  1272,    -1,    -1,    -1,  1266,    -1,    -1,  1266,
      -1,    -1,  1282,    -1,    -1,  1272,    -1,    -1,    -1,  1266,
    1266,    -1,  1266,    -1,    -1,  1272,    -1,    -1,    -1,    -1,
      -1,    -1,  1266,    -1,    -1,  1266,    -1,    -1,  1272,  1266,
      -1,  1272,    -1,    -1,    -1,  1272,    -1,    -1,    -1,    -1,
      -1,  1266,    -1,    -1,  1266,    -1,  1266,  1266,  1266,  1266,
      -1,  1266,  1266,    -1,  1266,    -1,    -1,    -1,    -1,  1266,
      -1,    -1,  1266,    -1,  1266,  1266,  1266,  1266,    -1,  1266,
    1266,    -1,  1266,    -1,  1266,  1266,    -1,  1266,    -1,    -1,
    1266,    -1,  1266
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,     0,     5,
       7,     9,   221,   222,   223,   224,   240,   241,   242,   247,
       7,   256,     7,   261,     7,   315,     7,   429,     7,   513,
       7,   530,     7,   464,     7,   470,     7,   494,     7,   405,
       7,   597,     7,   628,   248,   243,   257,   262,   316,   430,
     514,   531,   465,   471,   495,   406,   598,   629,   240,   249,
     250,   221,   245,   246,    10,   258,   260,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    94,    95,   106,   107,   108,
     113,   116,   117,   121,   126,   127,   128,   129,   130,   137,
     147,   150,   157,   158,   162,   165,   169,   189,   190,   191,
     192,   193,   194,   203,   221,   255,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     278,   279,   281,   282,   283,   284,   285,   286,   287,   290,
     292,   294,   295,   296,   299,   300,   302,   304,   305,   306,
     307,   308,   309,   310,   311,   329,   331,   339,   341,   383,
     392,   399,   413,   423,   447,   448,   449,   450,   454,   462,
     488,   520,   522,   524,   535,   537,   539,   562,   576,   577,
     585,   595,   626,   635,   659,    15,    16,    19,    22,    23,
      24,    25,   255,   313,   314,   317,   319,   322,   325,   326,
     327,   328,   520,   522,    91,    92,    93,   114,   118,   119,
     120,   131,   135,   144,   255,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   279,   282,   283,   284,   285,
     286,   287,   290,   292,   294,   295,   296,   299,   300,   302,
     304,   310,   431,   432,   433,   435,   437,   439,   441,   443,
     445,   447,   448,   449,   450,   453,   488,   507,   520,   522,
     524,   535,   537,   539,   559,   115,   136,   255,   443,   445,
     488,   515,   516,   517,   519,   520,   522,   130,   138,   139,
     140,   141,   142,   143,   145,   255,   488,   520,   522,   532,
     533,   534,   535,   537,   539,   541,   545,   547,   549,   551,
     553,   555,   557,   462,    39,    96,    98,    99,   103,   104,
     105,   255,   359,   472,   473,   474,   475,   476,   477,   478,
     480,   482,   484,   485,   487,   520,   522,    97,   100,   101,
     102,   255,   359,   476,   482,   496,   497,   498,   499,   500,
     502,   503,   504,   505,   506,   520,   522,   148,   149,   255,
     407,   408,   409,   411,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   189,   190,   255,
     520,   522,   599,   600,   601,   602,   604,   605,   607,   608,
     609,   612,   614,   616,   617,   618,   620,   622,   624,    12,
      13,   630,   631,   632,   634,     6,     3,     4,     8,     3,
     259,     3,     8,   627,   312,   332,     4,     4,     4,   536,
     538,   540,     4,   330,   340,   342,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   277,     4,     4,
       4,     4,     4,   288,   291,   293,     4,     4,     4,     4,
     424,   463,   489,     4,   280,   297,   455,   521,   523,   451,
       4,     4,     4,   384,   563,   525,   400,   414,     4,   393,
     578,   586,   596,   301,   303,     4,     4,     4,   636,   660,
       4,     3,     8,   318,   320,   323,     4,     4,     4,     4,
       3,     8,   436,   438,   440,   508,   434,   442,     4,   446,
     444,   560,     3,     8,   518,     4,     3,     8,   558,   546,
     548,   552,   550,   556,   554,   542,     8,     3,     8,   479,
     360,     4,   483,   481,   486,     4,     8,     3,   501,     4,
       4,     4,     8,     3,   410,   412,     3,     8,     4,   615,
     603,     4,   606,     4,     4,   610,   613,     4,     4,   619,
     621,   623,   625,     3,     8,   633,     4,     3,     8,   240,
     240,   221,     4,     4,     4,     4,   224,   224,   224,     4,
       4,     4,   222,     4,     4,     4,   222,   222,   222,   222,
     222,   224,   223,   223,   223,   222,   222,     4,   222,   222,
     224,   224,   224,     4,     4,     4,   224,   224,   223,   224,
       4,     4,     4,   222,     4,     4,     4,     4,     4,     4,
     224,   224,   224,     4,     4,     4,     4,     4,   222,     4,
       4,     4,     4,     4,     4,   224,   224,   224,     4,     4,
     264,     4,     4,     4,   224,   224,   222,   222,   314,     4,
       4,     4,     4,     4,     4,   222,     4,     4,     4,   432,
       4,   222,   516,     4,     4,     4,     4,     4,     4,     4,
       4,   534,     4,     4,   222,     4,     4,     4,   224,   474,
       4,   224,   224,   224,   498,     4,     4,   408,   224,     4,
       4,   222,     4,   222,   222,     4,     4,   224,   224,     4,
       4,     4,     4,   600,     4,   222,   631,     4,     7,     7,
       7,     7,   221,   221,   221,     7,     7,     5,   221,   185,
     186,   187,   188,   224,   289,   221,   221,     5,     5,     5,
     221,   109,   110,   111,   112,   298,     5,   242,   244,   221,
     122,   123,   124,   125,   452,     5,     5,     5,     5,     7,
       7,     7,     7,     7,   221,   221,     5,     7,     5,   251,
      17,    18,   321,    20,    21,   324,   221,   221,   221,     5,
     221,   221,   251,   221,     7,   221,   251,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   244,   221,   221,   221,    18,   183,   611,   184,   289,
     221,   221,   221,     5,   240,   263,   630,   313,    27,    28,
     333,   334,   335,   337,    39,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    60,
      61,    62,    63,    64,    65,   255,   347,   348,   349,   352,
     354,   356,   358,   359,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   373,   374,   375,   377,   379,   381,
     347,     7,   343,   344,   345,     7,   425,   426,   427,     7,
     466,   467,   468,     7,   490,   491,   492,     7,   456,   457,
     458,   138,   139,   140,   141,   143,   385,   386,   387,   388,
     389,   390,   391,     7,   564,   565,     7,   526,   527,   528,
       7,   401,   402,   403,   151,   152,   153,   154,   155,   156,
     415,   416,   417,   418,   419,   420,   421,   422,   159,   160,
     161,   255,   394,   395,   396,   397,   398,   520,   522,   163,
     164,   255,   520,   522,   579,   580,   581,   583,   166,   167,
     168,   221,   520,   522,   587,   588,   589,   590,   592,   593,
     599,     7,   637,   638,   204,   205,   206,   207,   255,   661,
     662,   663,   664,   665,   666,   252,     7,   509,   510,   511,
     146,   541,   543,   561,   343,     8,     8,     8,   336,   338,
       3,     8,   350,   353,   355,   357,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   371,     4,     4,   376,
     378,   380,   382,     3,     8,     8,   346,     6,     3,   428,
       6,     3,   469,     6,     3,   493,     6,     3,   459,     6,
       3,     3,     6,   566,     3,     6,   529,     6,     3,   404,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   582,   584,     3,     8,     4,
     591,     4,   594,     3,     8,     8,   639,     3,     6,     4,
       4,     4,     4,     3,     8,   221,   253,   254,   512,     6,
       3,   544,     8,     6,     4,     4,   334,     4,     4,     4,
       4,   222,   224,   222,   224,   222,   222,   222,   222,   222,
     222,     4,   224,   222,     4,     4,     4,     4,   348,   347,
     345,   431,   427,   472,   468,   496,   492,   255,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   279,   282,
     283,   284,   285,   286,   287,   290,   292,   294,   295,   296,
     299,   300,   302,   304,   310,   359,   423,   441,   443,   445,
     447,   448,   449,   450,   460,   461,   488,   520,   522,   535,
     537,   539,   559,   458,   386,   132,   133,   134,   255,   265,
     266,   267,   310,   359,   462,   488,   520,   522,   535,   537,
     539,   567,   568,   569,   570,   571,   573,   575,   565,   532,
     528,   407,   403,   222,   222,   222,   222,   222,   222,   416,
     224,   222,   222,   395,     4,     4,   580,   224,     4,   222,
       4,   588,   195,   197,   198,   255,   359,   520,   522,   640,
     641,   642,   643,   645,   638,   224,   224,   224,   224,   662,
       6,     3,   515,   511,     4,   221,   221,    40,    41,    42,
     351,   221,   221,   221,    57,    58,    59,   372,   221,   221,
     221,   221,     8,     8,     8,     8,     3,     8,   572,   574,
       4,     8,     3,     8,     8,   221,   221,   221,   240,   646,
       4,   644,     3,     8,   221,     8,   251,   461,     4,     4,
     224,   569,     4,   222,     4,   641,   221,   221,     5,   221,
       7,   647,   648,   649,     3,     6,   196,   199,   200,   201,
     202,   650,   651,   652,   654,   655,   656,   657,   648,   653,
       4,     4,     4,   658,     3,     8,     4,   224,   222,   222,
       4,   651,   221,   221
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   225,   227,   226,   228,   226,   229,   226,   230,   226,
     231,   226,   232,   226,   233,   226,   234,   226,   235,   226,
     236,   226,   237,   226,   238,   226,   239,   226,   240,   240,
     240,   240,   240,   240,   240,   241,   243,   242,   244,   245,
     245,   246,   246,   246,   248,   247,   249,   249,   250,   250,
     250,   252,   251,   253,   253,   254,   254,   254,   255,   257,
     256,   259,   258,   258,   260,   262,   261,   263,   263,   263,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   277,
     276,   278,   280,   279,   281,   282,   283,   284,   285,   286,
     288,   287,   289,   289,   289,   289,   289,   291,   290,   293,
     292,   294,   295,   297,   296,   298,   298,   298,   298,   299,
     301,   300,   303,   302,   304,   305,   306,   307,   308,   309,
     310,   312,   311,   313,   313,   313,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   316,   315,   318,   317,
     320,   319,   321,   321,   323,   322,   324,   324,   325,   326,
     327,   328,   330,   329,   332,   331,   333,   333,   333,   334,
     334,   336,   335,   338,   337,   340,   339,   342,   341,   343,
     343,   344,   344,   344,   346,   345,   347,   347,   347,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   350,   349,   351,   351,   351,   353,   352,   355,
     354,   357,   356,   358,   360,   359,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   371,   370,   372,   372,   372,
     373,   374,   376,   375,   378,   377,   380,   379,   382,   381,
     384,   383,   385,   385,   385,   386,   386,   386,   386,   386,
     387,   388,   389,   390,   391,   393,   392,   394,   394,   394,
     395,   395,   395,   395,   395,   395,   396,   397,   398,   400,
     399,   401,   401,   402,   402,   402,   404,   403,   406,   405,
     407,   407,   407,   407,   408,   408,   410,   409,   412,   411,
     414,   413,   415,   415,   415,   416,   416,   416,   416,   416,
     416,   417,   418,   419,   420,   421,   422,   424,   423,   425,
     425,   426,   426,   426,   428,   427,   430,   429,   431,   431,
     431,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     434,   433,   436,   435,   438,   437,   440,   439,   442,   441,
     444,   443,   446,   445,   447,   448,   449,   451,   450,   452,
     452,   452,   452,   453,   455,   454,   456,   456,   457,   457,
     457,   459,   458,   460,   460,   460,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     463,   462,   465,   464,   466,   466,   467,   467,   467,   469,
     468,   471,   470,   472,   472,   473,   473,   473,   474,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   475,   476,
     477,   479,   478,   481,   480,   483,   482,   484,   486,   485,
     487,   489,   488,   490,   490,   491,   491,   491,   493,   492,
     495,   494,   496,   496,   497,   497,   497,   498,   498,   498,
     498,   498,   498,   498,   498,   498,   498,   499,   501,   500,
     502,   503,   504,   505,   506,   508,   507,   509,   509,   510,
     510,   510,   512,   511,   514,   513,   515,   515,   515,   516,
     516,   516,   516,   516,   516,   516,   516,   518,   517,   519,
     521,   520,   523,   522,   525,   524,   526,   526,   527,   527,
     527,   529,   528,   531,   530,   532,   532,   533,   533,   533,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   536,   535,   538,   537,   540,
     539,   542,   541,   544,   543,   546,   545,   548,   547,   550,
     549,   552,   551,   554,   553,   556,   555,   558,   557,   560,
     559,   561,   561,   563,   562,   564,   564,   564,   566,   565,
     567,   567,   568,   568,   568,   569,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   569,   569,   569,   569,
     569,   570,   572,   571,   574,   573,   575,   576,   578,   577,
     579,   579,   579,   580,   580,   580,   580,   580,   582,   581,
     584,   583,   586,   585,   587,   587,   587,   588,   588,   588,
     588,   588,   588,   589,   591,   590,   592,   594,   593,   596,
     595,   598,   597,   599,   599,   599,   600,   600,   600,   600,
     600,   600,   600,   600,   600,   600,   600,   600,   600,   600,
     600,   600,   600,   600,   601,   603,   602,   604,   606,   605,
     607,   608,   610,   609,   611,   611,   613,   612,   615,   614,
     616,   617,   619,   618,   621,   620,   623,   622,   625,   624,
     627,   626,   629,   628,   630,   630,   630,   631,   631,   633,
     632,   634,   636,   635,   637,   637,   637,   639,   638,   640,
     640,   640,   641,   641,   641,   641,   641,   641,   641,   642,
     644,   643,   646,   645,   647,   647,   647,   649,   648,   650,
     650,   650,   651,   651,   651,   651,   651,   653,   652,   654,
     655,   656,   658,   657,   660,   659,   661,   661,   661,   662,
     662,   662,   662,   662,   663,   664,   665,   666
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
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     3,
       3,     3,     0,     6,     0,     6,     1,     3,     2,     1,
       1,     0,     4,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
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
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     3
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
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"template-test\"",
  "\"only-if-required\"", "\"client-class\"", "\"pool-id\"",
  "\"reservations\"", "\"duid\"", "\"hw-address\"", "\"circuit-id\"",
  "\"client-id\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
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
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@68", "hr_mode", "id", "shared_networks", "$@69",
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
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@83", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@84", "sub_pool4", "$@85", "pool_params", "pool_param", "pool_entry",
  "$@86", "pool_id", "user_context", "$@87", "comment", "$@88",
  "reservations", "$@89", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@90", "sub_reservation",
  "$@91", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@92", "server_hostname", "$@93",
  "boot_file_name", "$@94", "ip_address", "$@95", "ip_addresses", "$@96",
  "duid", "$@97", "hw_address", "$@98", "client_id_value", "$@99",
  "circuit_id_value", "$@100", "flex_id_value", "$@101", "hostname",
  "$@102", "reservation_client_classes", "$@103", "relay", "$@104",
  "relay_map", "client_classes", "$@105", "client_classes_list",
  "client_class_entry", "$@106", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@107",
  "client_class_template_test", "$@108", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@109", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@110",
  "control_socket_name", "$@111", "dhcp_queue_control", "$@112",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@113", "capacity", "arbitrary_map_entry", "$@114",
  "dhcp_ddns", "$@115", "sub_dhcp_ddns", "$@116", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@117", "server_port",
  "sender_ip", "$@118", "sender_port", "max_queue_size", "ncr_protocol",
  "$@119", "ncr_protocol_value", "ncr_format", "$@120",
  "dep_qualifying_suffix", "$@121", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@122",
  "dep_generated_prefix", "$@123", "dep_hostname_char_set", "$@124",
  "dep_hostname_char_replacement", "$@125", "config_control", "$@126",
  "sub_config_control", "$@127", "config_control_params",
  "config_control_param", "config_databases", "$@128",
  "config_fetch_wait_time", "loggers", "$@129", "loggers_entries",
  "logger_entry", "$@130", "logger_params", "logger_param", "debuglevel",
  "severity", "$@131", "output_options_list", "$@132",
  "output_options_list_content", "output_entry", "$@133",
  "output_params_list", "output_params", "output", "$@134", "flush",
  "maxsize", "maxver", "pattern", "$@135", "compatibility", "$@136",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   320,   320,   320,   321,   321,   322,   322,   323,   323,
     324,   324,   325,   325,   326,   326,   327,   327,   328,   328,
     329,   329,   330,   330,   331,   331,   332,   332,   340,   341,
     342,   343,   344,   345,   346,   349,   354,   354,   365,   368,
     369,   372,   377,   383,   388,   388,   395,   396,   399,   403,
     407,   413,   413,   420,   421,   424,   428,   432,   442,   451,
     451,   466,   466,   480,   483,   489,   489,   498,   499,   500,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   577,   583,
     589,   595,   601,   607,   613,   619,   625,   631,   637,   643,
     643,   652,   658,   658,   667,   673,   679,   685,   691,   697,
     703,   703,   712,   715,   718,   721,   724,   730,   730,   739,
     739,   748,   757,   767,   767,   776,   779,   782,   785,   790,
     796,   796,   805,   805,   814,   820,   826,   832,   838,   844,
     850,   856,   856,   868,   869,   870,   875,   876,   877,   878,
     879,   880,   881,   882,   883,   884,   887,   887,   896,   896,
     907,   907,   915,   916,   919,   919,   927,   929,   933,   939,
     945,   951,   957,   957,   970,   970,   981,   982,   983,   988,
     989,   992,   992,  1011,  1011,  1029,  1029,  1042,  1042,  1053,
    1054,  1057,  1058,  1059,  1064,  1064,  1074,  1075,  1076,  1081,
    1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,
    1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,
    1102,  1103,  1106,  1106,  1114,  1115,  1116,  1119,  1119,  1128,
    1128,  1137,  1137,  1146,  1152,  1152,  1161,  1167,  1173,  1179,
    1185,  1191,  1197,  1203,  1209,  1215,  1215,  1223,  1224,  1225,
    1228,  1234,  1240,  1240,  1249,  1249,  1258,  1258,  1267,  1267,
    1276,  1276,  1287,  1288,  1289,  1294,  1295,  1296,  1297,  1298,
    1301,  1306,  1311,  1316,  1321,  1328,  1328,  1341,  1342,  1343,
    1348,  1349,  1350,  1351,  1352,  1353,  1356,  1362,  1368,  1374,
    1374,  1385,  1386,  1389,  1390,  1391,  1396,  1396,  1406,  1406,
    1416,  1417,  1418,  1421,  1424,  1425,  1428,  1428,  1437,  1437,
    1446,  1446,  1458,  1459,  1460,  1465,  1466,  1467,  1468,  1469,
    1470,  1473,  1479,  1485,  1491,  1497,  1503,  1512,  1512,  1526,
    1527,  1530,  1531,  1532,  1541,  1541,  1567,  1567,  1578,  1579,
    1580,  1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,  1594,
    1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,  1604,
    1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,
    1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,
    1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,
    1637,  1637,  1646,  1646,  1655,  1655,  1664,  1664,  1673,  1673,
    1682,  1682,  1691,  1691,  1702,  1708,  1714,  1720,  1720,  1728,
    1729,  1730,  1731,  1734,  1742,  1742,  1754,  1755,  1759,  1760,
    1761,  1766,  1766,  1774,  1775,  1776,  1781,  1782,  1783,  1784,
    1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,
    1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,
    1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,
    1831,  1831,  1845,  1845,  1854,  1855,  1858,  1859,  1860,  1867,
    1867,  1882,  1882,  1896,  1897,  1900,  1901,  1902,  1907,  1908,
    1909,  1910,  1911,  1912,  1913,  1914,  1915,  1916,  1919,  1921,
    1927,  1929,  1929,  1938,  1938,  1947,  1947,  1956,  1958,  1958,
    1967,  1977,  1977,  1990,  1991,  1996,  1997,  1998,  2005,  2005,
    2017,  2017,  2029,  2030,  2035,  2036,  2037,  2044,  2045,  2046,
    2047,  2048,  2049,  2050,  2051,  2052,  2053,  2056,  2058,  2058,
    2067,  2069,  2071,  2077,  2083,  2092,  2092,  2105,  2106,  2109,
    2110,  2111,  2116,  2116,  2126,  2126,  2136,  2137,  2138,  2143,
    2144,  2145,  2146,  2147,  2148,  2149,  2150,  2153,  2153,  2162,
    2168,  2168,  2193,  2193,  2223,  2223,  2234,  2235,  2238,  2239,
    2240,  2245,  2245,  2254,  2254,  2263,  2264,  2267,  2268,  2269,
    2275,  2276,  2277,  2278,  2279,  2280,  2281,  2282,  2283,  2284,
    2285,  2286,  2287,  2288,  2289,  2292,  2292,  2301,  2301,  2310,
    2310,  2319,  2319,  2328,  2328,  2339,  2339,  2348,  2348,  2357,
    2357,  2366,  2366,  2375,  2375,  2384,  2384,  2393,  2393,  2407,
    2407,  2418,  2419,  2425,  2425,  2436,  2437,  2438,  2443,  2443,
    2453,  2454,  2457,  2458,  2459,  2464,  2465,  2466,  2467,  2468,
    2469,  2470,  2471,  2472,  2473,  2474,  2475,  2476,  2477,  2478,
    2479,  2482,  2484,  2484,  2493,  2493,  2502,  2510,  2518,  2518,
    2529,  2530,  2531,  2536,  2537,  2538,  2539,  2540,  2543,  2543,
    2552,  2552,  2564,  2564,  2577,  2578,  2579,  2584,  2585,  2586,
    2587,  2588,  2589,  2592,  2598,  2598,  2607,  2613,  2613,  2623,
    2623,  2636,  2636,  2646,  2647,  2648,  2653,  2654,  2655,  2656,
    2657,  2658,  2659,  2660,  2661,  2662,  2663,  2664,  2665,  2666,
    2667,  2668,  2669,  2670,  2673,  2679,  2679,  2688,  2694,  2694,
    2703,  2709,  2715,  2715,  2724,  2725,  2728,  2728,  2738,  2738,
    2748,  2755,  2762,  2762,  2771,  2771,  2781,  2781,  2791,  2791,
    2803,  2803,  2815,  2815,  2825,  2826,  2827,  2833,  2834,  2837,
    2837,  2848,  2856,  2856,  2869,  2870,  2871,  2877,  2877,  2885,
    2886,  2887,  2892,  2893,  2894,  2895,  2896,  2897,  2898,  2901,
    2907,  2907,  2916,  2916,  2927,  2928,  2929,  2934,  2934,  2942,
    2943,  2944,  2949,  2950,  2951,  2952,  2953,  2956,  2956,  2965,
    2971,  2977,  2983,  2983,  2992,  2992,  3003,  3004,  3005,  3010,
    3011,  3012,  3013,  3014,  3017,  3023,  3029,  3035
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
#line 6461 "dhcp4_parser.cc"

#line 3041 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
