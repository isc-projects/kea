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
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 310 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 310 "dhcp4_parser.yy"
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
#line 319 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 320 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 321 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 322 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 323 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 324 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 325 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 326 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 327 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 328 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 329 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 330 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 331 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 339 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 340 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 341 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 342 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 343 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 344 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 345 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 348 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 353 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 358 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 364 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 371 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 376 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 382 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 387 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 390 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 398 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 402 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 406 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 412 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 414 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 423 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 427 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 431 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 441 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 450 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 455 "dhcp4_parser.yy"
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
#line 465 "dhcp4_parser.yy"
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
#line 474 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 482 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 488 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 492 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 499 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 138: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 576 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 139: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 582 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 140: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 588 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 141: // renew_timer: "renew-timer" ":" "integer"
#line 594 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 142: // rebind_timer: "rebind-timer" ":" "integer"
#line 600 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 143: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 606 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 144: // t1_percent: "t1-percent" ":" "floating point"
#line 612 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 145: // t2_percent: "t2-percent" ":" "floating point"
#line 618 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 146: // cache_threshold: "cache-threshold" ":" "floating point"
#line 624 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 147: // cache_max_age: "cache-max-age" ":" "integer"
#line 630 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 148: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 636 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 149: // $@20: %empty
#line 642 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 150: // server_tag: "server-tag" $@20 ":" "constant string"
#line 645 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 151: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 651 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 152: // $@21: %empty
#line 657 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 153: // allocator: "allocator" $@21 ":" "constant string"
#line 660 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 154: // echo_client_id: "echo-client-id" ":" "boolean"
#line 666 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 155: // match_client_id: "match-client-id" ":" "boolean"
#line 672 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 156: // authoritative: "authoritative" ":" "boolean"
#line 678 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 684 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 690 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 696 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 160: // $@22: %empty
#line 702 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 705 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 711 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 714 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 717 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 720 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 723 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 167: // $@23: %empty
#line 729 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 732 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 169: // $@24: %empty
#line 738 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 741 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 747 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 756 "dhcp4_parser.yy"
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
#line 766 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 769 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 775 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 778 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 781 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 784 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 789 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 180: // $@26: %empty
#line 795 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 798 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 182: // $@27: %empty
#line 804 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 807 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 813 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 819 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 825 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 187: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 831 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 188: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 837 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 189: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 843 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 190: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 849 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 191: // $@28: %empty
#line 855 "dhcp4_parser.yy"
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
#line 861 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 195: // interfaces_config_params: interfaces_config_params ","
#line 869 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1674 "dhcp4_parser.cc"
    break;

  case 206: // $@29: %empty
#line 886 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 207: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 890 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1693 "dhcp4_parser.cc"
    break;

  case 208: // $@30: %empty
#line 895 "dhcp4_parser.yy"
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
#line 901 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1714 "dhcp4_parser.cc"
    break;

  case 210: // $@31: %empty
#line 906 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1723 "dhcp4_parser.cc"
    break;

  case 211: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 909 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1732 "dhcp4_parser.cc"
    break;

  case 212: // socket_type: "raw"
#line 914 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1738 "dhcp4_parser.cc"
    break;

  case 213: // socket_type: "udp"
#line 915 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1744 "dhcp4_parser.cc"
    break;

  case 214: // $@32: %empty
#line 918 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 215: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 921 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1762 "dhcp4_parser.cc"
    break;

  case 216: // outbound_interface_value: "same-as-inbound"
#line 926 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface_value: "use-routing"
#line 928 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1778 "dhcp4_parser.cc"
    break;

  case 218: // re_detect: "re-detect" ":" "boolean"
#line 932 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1788 "dhcp4_parser.cc"
    break;

  case 219: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 938 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 220: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 944 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 950 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 222: // $@33: %empty
#line 956 "dhcp4_parser.yy"
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
#line 962 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc"
    break;

  case 224: // $@34: %empty
#line 969 "dhcp4_parser.yy"
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
#line 975 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 228: // sanity_checks_params: sanity_checks_params ","
#line 982 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1870 "dhcp4_parser.cc"
    break;

  case 231: // $@35: %empty
#line 991 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 232: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 994 "dhcp4_parser.yy"
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
#line 1010 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 234: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1013 "dhcp4_parser.yy"
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
#line 1028 "dhcp4_parser.yy"
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
#line 1034 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1950 "dhcp4_parser.cc"
    break;

  case 237: // $@38: %empty
#line 1041 "dhcp4_parser.yy"
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
#line 1047 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 243: // not_empty_database_list: not_empty_database_list ","
#line 1058 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1979 "dhcp4_parser.cc"
    break;

  case 244: // $@39: %empty
#line 1063 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1989 "dhcp4_parser.cc"
    break;

  case 245: // database: "{" $@39 database_map_params "}"
#line 1067 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 248: // database_map_params: database_map_params ","
#line 1075 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2007 "dhcp4_parser.cc"
    break;

  case 271: // $@40: %empty
#line 1104 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 2016 "dhcp4_parser.cc"
    break;

  case 272: // database_type: "type" $@40 ":" db_type
#line 1107 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2025 "dhcp4_parser.cc"
    break;

  case 273: // db_type: "memfile"
#line 1112 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 2031 "dhcp4_parser.cc"
    break;

  case 274: // db_type: "mysql"
#line 1113 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 2037 "dhcp4_parser.cc"
    break;

  case 275: // db_type: "postgresql"
#line 1114 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 2043 "dhcp4_parser.cc"
    break;

  case 276: // $@41: %empty
#line 1117 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp4_parser.cc"
    break;

  case 277: // user: "user" $@41 ":" "constant string"
#line 1120 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2062 "dhcp4_parser.cc"
    break;

  case 278: // $@42: %empty
#line 1126 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2071 "dhcp4_parser.cc"
    break;

  case 279: // password: "password" $@42 ":" "constant string"
#line 1129 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2081 "dhcp4_parser.cc"
    break;

  case 280: // $@43: %empty
#line 1135 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp4_parser.cc"
    break;

  case 281: // host: "host" $@43 ":" "constant string"
#line 1138 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 282: // port: "port" ":" "integer"
#line 1144 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1150 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 284: // name: "name" $@44 ":" "constant string"
#line 1153 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 285: // persist: "persist" ":" "boolean"
#line 1159 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 286: // lfc_interval: "lfc-interval" ":" "integer"
#line 1165 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2149 "dhcp4_parser.cc"
    break;

  case 287: // readonly: "readonly" ":" "boolean"
#line 1171 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 288: // connect_timeout: "connect-timeout" ":" "integer"
#line 1177 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 289: // read_timeout: "read-timeout" ":" "integer"
#line 1183 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2179 "dhcp4_parser.cc"
    break;

  case 290: // write_timeout: "write-timeout" ":" "integer"
#line 1189 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 291: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1195 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2199 "dhcp4_parser.cc"
    break;

  case 292: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1201 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 293: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1207 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1213 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 295: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1216 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2237 "dhcp4_parser.cc"
    break;

  case 296: // on_fail_mode: "stop-retry-exit"
#line 1221 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2243 "dhcp4_parser.cc"
    break;

  case 297: // on_fail_mode: "serve-retry-exit"
#line 1222 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2249 "dhcp4_parser.cc"
    break;

  case 298: // on_fail_mode: "serve-retry-continue"
#line 1223 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2255 "dhcp4_parser.cc"
    break;

  case 299: // max_row_errors: "max-row-errors" ":" "integer"
#line 1226 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2265 "dhcp4_parser.cc"
    break;

  case 300: // $@46: %empty
#line 1232 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 301: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1235 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2284 "dhcp4_parser.cc"
    break;

  case 302: // $@47: %empty
#line 1241 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc"
    break;

  case 303: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1244 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc"
    break;

  case 304: // $@48: %empty
#line 1250 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2312 "dhcp4_parser.cc"
    break;

  case 305: // key_file: "key-file" $@48 ":" "constant string"
#line 1253 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2322 "dhcp4_parser.cc"
    break;

  case 306: // $@49: %empty
#line 1259 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 307: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1262 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 308: // $@50: %empty
#line 1268 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2353 "dhcp4_parser.cc"
    break;

  case 309: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1274 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 312: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1281 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2370 "dhcp4_parser.cc"
    break;

  case 318: // duid_id: "duid"
#line 1293 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2379 "dhcp4_parser.cc"
    break;

  case 319: // hw_address_id: "hw-address"
#line 1298 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 320: // circuit_id: "circuit-id"
#line 1303 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2397 "dhcp4_parser.cc"
    break;

  case 321: // client_id: "client-id"
#line 1308 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 322: // flex_id: "flex-id"
#line 1313 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 323: // $@51: %empty
#line 1320 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2427 "dhcp4_parser.cc"
    break;

  case 324: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1326 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp4_parser.cc"
    break;

  case 327: // multi_threading_params: multi_threading_params ","
#line 1335 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2446 "dhcp4_parser.cc"
    break;

  case 334: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1348 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2456 "dhcp4_parser.cc"
    break;

  case 335: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1354 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2466 "dhcp4_parser.cc"
    break;

  case 336: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1360 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2476 "dhcp4_parser.cc"
    break;

  case 337: // $@52: %empty
#line 1366 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2488 "dhcp4_parser.cc"
    break;

  case 338: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1372 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2497 "dhcp4_parser.cc"
    break;

  case 343: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1383 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2505 "dhcp4_parser.cc"
    break;

  case 344: // $@53: %empty
#line 1388 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2515 "dhcp4_parser.cc"
    break;

  case 345: // hooks_library: "{" $@53 hooks_params "}"
#line 1392 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2525 "dhcp4_parser.cc"
    break;

  case 346: // $@54: %empty
#line 1398 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 347: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1402 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 350: // hooks_params: hooks_params ","
#line 1410 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2553 "dhcp4_parser.cc"
    break;

  case 354: // $@55: %empty
#line 1420 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2562 "dhcp4_parser.cc"
    break;

  case 355: // library: "library" $@55 ":" "constant string"
#line 1423 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2572 "dhcp4_parser.cc"
    break;

  case 356: // $@56: %empty
#line 1429 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2581 "dhcp4_parser.cc"
    break;

  case 357: // parameters: "parameters" $@56 ":" map_value
#line 1432 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 358: // $@57: %empty
#line 1438 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2602 "dhcp4_parser.cc"
    break;

  case 359: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1444 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2612 "dhcp4_parser.cc"
    break;

  case 362: // expired_leases_params: expired_leases_params ","
#line 1452 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2620 "dhcp4_parser.cc"
    break;

  case 369: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1465 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2630 "dhcp4_parser.cc"
    break;

  case 370: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1471 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2640 "dhcp4_parser.cc"
    break;

  case 371: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1477 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2650 "dhcp4_parser.cc"
    break;

  case 372: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1483 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 373: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1489 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 374: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1495 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 375: // $@58: %empty
#line 1504 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 376: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1510 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 381: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1524 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2709 "dhcp4_parser.cc"
    break;

  case 382: // $@59: %empty
#line 1533 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2719 "dhcp4_parser.cc"
    break;

  case 383: // subnet4: "{" $@59 subnet4_params "}"
#line 1537 "dhcp4_parser.yy"
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
#line 2745 "dhcp4_parser.cc"
    break;

  case 384: // $@60: %empty
#line 1559 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2755 "dhcp4_parser.cc"
    break;

  case 385: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1563 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2765 "dhcp4_parser.cc"
    break;

  case 388: // subnet4_params: subnet4_params ","
#line 1572 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2773 "dhcp4_parser.cc"
    break;

  case 438: // $@61: %empty
#line 1629 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 439: // subnet: "subnet" $@61 ":" "constant string"
#line 1632 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 440: // $@62: %empty
#line 1638 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 441: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1641 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 442: // $@63: %empty
#line 1647 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 443: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1650 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 444: // $@64: %empty
#line 1656 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2839 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1659 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2849 "dhcp4_parser.cc"
    break;

  case 446: // $@65: %empty
#line 1665 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp4_parser.cc"
    break;

  case 447: // interface: "interface" $@65 ":" "constant string"
#line 1668 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2868 "dhcp4_parser.cc"
    break;

  case 448: // $@66: %empty
#line 1674 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2877 "dhcp4_parser.cc"
    break;

  case 449: // client_class: "client-class" $@66 ":" "constant string"
#line 1677 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2887 "dhcp4_parser.cc"
    break;

  case 450: // $@67: %empty
#line 1683 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 451: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1689 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 452: // reservations_global: "reservations-global" ":" "boolean"
#line 1694 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2918 "dhcp4_parser.cc"
    break;

  case 453: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1700 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2928 "dhcp4_parser.cc"
    break;

  case 454: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1706 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 455: // $@68: %empty
#line 1712 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 456: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1715 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 457: // hr_mode: "disabled"
#line 1720 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2962 "dhcp4_parser.cc"
    break;

  case 458: // hr_mode: "out-of-pool"
#line 1721 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2968 "dhcp4_parser.cc"
    break;

  case 459: // hr_mode: "global"
#line 1722 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2974 "dhcp4_parser.cc"
    break;

  case 460: // hr_mode: "all"
#line 1723 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2980 "dhcp4_parser.cc"
    break;

  case 461: // id: "id" ":" "integer"
#line 1726 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 462: // $@69: %empty
#line 1734 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3002 "dhcp4_parser.cc"
    break;

  case 463: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1740 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 468: // shared_networks_list: shared_networks_list ","
#line 1753 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3019 "dhcp4_parser.cc"
    break;

  case 469: // $@70: %empty
#line 1758 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3029 "dhcp4_parser.cc"
    break;

  case 470: // shared_network: "{" $@70 shared_network_params "}"
#line 1762 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3037 "dhcp4_parser.cc"
    break;

  case 473: // shared_network_params: shared_network_params ","
#line 1768 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3045 "dhcp4_parser.cc"
    break;

  case 518: // $@71: %empty
#line 1823 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 519: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1829 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3066 "dhcp4_parser.cc"
    break;

  case 520: // $@72: %empty
#line 1837 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3075 "dhcp4_parser.cc"
    break;

  case 521: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1840 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3083 "dhcp4_parser.cc"
    break;

  case 526: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1852 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3091 "dhcp4_parser.cc"
    break;

  case 527: // $@73: %empty
#line 1859 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 528: // option_def_entry: "{" $@73 option_def_params "}"
#line 1863 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3113 "dhcp4_parser.cc"
    break;

  case 529: // $@74: %empty
#line 1874 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3123 "dhcp4_parser.cc"
    break;

  case 530: // sub_option_def: "{" $@74 option_def_params "}"
#line 1878 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3135 "dhcp4_parser.cc"
    break;

  case 535: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1894 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3143 "dhcp4_parser.cc"
    break;

  case 547: // code: "code" ":" "integer"
#line 1913 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3153 "dhcp4_parser.cc"
    break;

  case 549: // $@75: %empty
#line 1921 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3162 "dhcp4_parser.cc"
    break;

  case 550: // option_def_type: "type" $@75 ":" "constant string"
#line 1924 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3172 "dhcp4_parser.cc"
    break;

  case 551: // $@76: %empty
#line 1930 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3181 "dhcp4_parser.cc"
    break;

  case 552: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1933 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3191 "dhcp4_parser.cc"
    break;

  case 553: // $@77: %empty
#line 1939 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp4_parser.cc"
    break;

  case 554: // space: "space" $@77 ":" "constant string"
#line 1942 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3210 "dhcp4_parser.cc"
    break;

  case 556: // $@78: %empty
#line 1950 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3219 "dhcp4_parser.cc"
    break;

  case 557: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1953 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3229 "dhcp4_parser.cc"
    break;

  case 558: // option_def_array: "array" ":" "boolean"
#line 1959 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3239 "dhcp4_parser.cc"
    break;

  case 559: // $@79: %empty
#line 1969 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3251 "dhcp4_parser.cc"
    break;

  case 560: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1975 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3260 "dhcp4_parser.cc"
    break;

  case 565: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1990 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3268 "dhcp4_parser.cc"
    break;

  case 566: // $@80: %empty
#line 1997 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3278 "dhcp4_parser.cc"
    break;

  case 567: // option_data_entry: "{" $@80 option_data_params "}"
#line 2001 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3287 "dhcp4_parser.cc"
    break;

  case 568: // $@81: %empty
#line 2009 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3297 "dhcp4_parser.cc"
    break;

  case 569: // sub_option_data: "{" $@81 option_data_params "}"
#line 2013 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3306 "dhcp4_parser.cc"
    break;

  case 574: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2029 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3314 "dhcp4_parser.cc"
    break;

  case 586: // $@82: %empty
#line 2050 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp4_parser.cc"
    break;

  case 587: // option_data_data: "data" $@82 ":" "constant string"
#line 2053 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3333 "dhcp4_parser.cc"
    break;

  case 590: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2063 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3343 "dhcp4_parser.cc"
    break;

  case 591: // option_data_always_send: "always-send" ":" "boolean"
#line 2069 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 592: // option_data_never_send: "never-send" ":" "boolean"
#line 2075 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 593: // $@83: %empty
#line 2084 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3375 "dhcp4_parser.cc"
    break;

  case 594: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2090 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3384 "dhcp4_parser.cc"
    break;

  case 599: // not_empty_pools_list: not_empty_pools_list ","
#line 2103 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3392 "dhcp4_parser.cc"
    break;

  case 600: // $@84: %empty
#line 2108 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3402 "dhcp4_parser.cc"
    break;

  case 601: // pool_list_entry: "{" $@84 pool_params "}"
#line 2112 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3412 "dhcp4_parser.cc"
    break;

  case 602: // $@85: %empty
#line 2118 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 603: // sub_pool4: "{" $@85 pool_params "}"
#line 2122 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 606: // pool_params: pool_params ","
#line 2130 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3440 "dhcp4_parser.cc"
    break;

  case 615: // $@86: %empty
#line 2145 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 616: // pool_entry: "pool" $@86 ":" "constant string"
#line 2148 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 617: // pool_id: "pool-id" ":" "integer"
#line 2154 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3469 "dhcp4_parser.cc"
    break;

  case 618: // $@87: %empty
#line 2160 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc"
    break;

  case 619: // user_context: "user-context" $@87 ":" map_value
#line 2162 "dhcp4_parser.yy"
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
#line 3504 "dhcp4_parser.cc"
    break;

  case 620: // $@88: %empty
#line 2185 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3512 "dhcp4_parser.cc"
    break;

  case 621: // comment: "comment" $@88 ":" "constant string"
#line 2187 "dhcp4_parser.yy"
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
#line 3541 "dhcp4_parser.cc"
    break;

  case 622: // $@89: %empty
#line 2215 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3553 "dhcp4_parser.cc"
    break;

  case 623: // reservations: "reservations" $@89 ":" "[" reservations_list "]"
#line 2221 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3562 "dhcp4_parser.cc"
    break;

  case 628: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2232 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3570 "dhcp4_parser.cc"
    break;

  case 629: // $@90: %empty
#line 2237 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3580 "dhcp4_parser.cc"
    break;

  case 630: // reservation: "{" $@90 reservation_params "}"
#line 2241 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3589 "dhcp4_parser.cc"
    break;

  case 631: // $@91: %empty
#line 2246 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3599 "dhcp4_parser.cc"
    break;

  case 632: // sub_reservation: "{" $@91 reservation_params "}"
#line 2250 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3608 "dhcp4_parser.cc"
    break;

  case 637: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2261 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3616 "dhcp4_parser.cc"
    break;

  case 653: // $@92: %empty
#line 2284 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3625 "dhcp4_parser.cc"
    break;

  case 654: // next_server: "next-server" $@92 ":" "constant string"
#line 2287 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 655: // $@93: %empty
#line 2293 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3644 "dhcp4_parser.cc"
    break;

  case 656: // server_hostname: "server-hostname" $@93 ":" "constant string"
#line 2296 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3654 "dhcp4_parser.cc"
    break;

  case 657: // $@94: %empty
#line 2302 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3663 "dhcp4_parser.cc"
    break;

  case 658: // boot_file_name: "boot-file-name" $@94 ":" "constant string"
#line 2305 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 659: // $@95: %empty
#line 2311 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3682 "dhcp4_parser.cc"
    break;

  case 660: // ip_address: "ip-address" $@95 ":" "constant string"
#line 2314 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 661: // $@96: %empty
#line 2320 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3704 "dhcp4_parser.cc"
    break;

  case 662: // ip_addresses: "ip-addresses" $@96 ":" list_strings
#line 2326 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3713 "dhcp4_parser.cc"
    break;

  case 663: // $@97: %empty
#line 2331 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 664: // duid: "duid" $@97 ":" "constant string"
#line 2334 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 665: // $@98: %empty
#line 2340 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 666: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2343 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 667: // $@99: %empty
#line 2349 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 668: // client_id_value: "client-id" $@99 ":" "constant string"
#line 2352 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 669: // $@100: %empty
#line 2358 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3779 "dhcp4_parser.cc"
    break;

  case 670: // circuit_id_value: "circuit-id" $@100 ":" "constant string"
#line 2361 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3789 "dhcp4_parser.cc"
    break;

  case 671: // $@101: %empty
#line 2367 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3798 "dhcp4_parser.cc"
    break;

  case 672: // flex_id_value: "flex-id" $@101 ":" "constant string"
#line 2370 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 673: // $@102: %empty
#line 2376 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp4_parser.cc"
    break;

  case 674: // hostname: "hostname" $@102 ":" "constant string"
#line 2379 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 675: // $@103: %empty
#line 2385 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3839 "dhcp4_parser.cc"
    break;

  case 676: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2391 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 677: // $@104: %empty
#line 2399 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3860 "dhcp4_parser.cc"
    break;

  case 678: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2405 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3869 "dhcp4_parser.cc"
    break;

  case 681: // $@105: %empty
#line 2417 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 682: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2423 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3890 "dhcp4_parser.cc"
    break;

  case 685: // client_classes_list: client_classes_list ","
#line 2430 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3898 "dhcp4_parser.cc"
    break;

  case 686: // $@106: %empty
#line 2435 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3908 "dhcp4_parser.cc"
    break;

  case 687: // client_class_entry: "{" $@106 client_class_params "}"
#line 2439 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 692: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2451 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3926 "dhcp4_parser.cc"
    break;

  case 710: // $@107: %empty
#line 2476 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3935 "dhcp4_parser.cc"
    break;

  case 711: // client_class_test: "test" $@107 ":" "constant string"
#line 2479 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3945 "dhcp4_parser.cc"
    break;

  case 712: // $@108: %empty
#line 2485 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3954 "dhcp4_parser.cc"
    break;

  case 713: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2488 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3964 "dhcp4_parser.cc"
    break;

  case 714: // only_if_required: "only-if-required" ":" "boolean"
#line 2494 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3974 "dhcp4_parser.cc"
    break;

  case 715: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2502 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 716: // $@109: %empty
#line 2510 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3996 "dhcp4_parser.cc"
    break;

  case 717: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2516 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4005 "dhcp4_parser.cc"
    break;

  case 720: // control_socket_params: control_socket_params ","
#line 2523 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4013 "dhcp4_parser.cc"
    break;

  case 726: // $@110: %empty
#line 2535 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4022 "dhcp4_parser.cc"
    break;

  case 727: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2538 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 728: // $@111: %empty
#line 2544 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 729: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2547 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 730: // $@112: %empty
#line 2556 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4063 "dhcp4_parser.cc"
    break;

  case 731: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2562 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 734: // queue_control_params: queue_control_params ","
#line 2571 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4082 "dhcp4_parser.cc"
    break;

  case 741: // enable_queue: "enable-queue" ":" "boolean"
#line 2584 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 742: // $@113: %empty
#line 2590 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4101 "dhcp4_parser.cc"
    break;

  case 743: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2593 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4111 "dhcp4_parser.cc"
    break;

  case 744: // capacity: "capacity" ":" "integer"
#line 2599 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 745: // $@114: %empty
#line 2605 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4130 "dhcp4_parser.cc"
    break;

  case 746: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2608 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 747: // $@115: %empty
#line 2615 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 748: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2621 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4162 "dhcp4_parser.cc"
    break;

  case 749: // $@116: %empty
#line 2628 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4172 "dhcp4_parser.cc"
    break;

  case 750: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2632 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 753: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2640 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4190 "dhcp4_parser.cc"
    break;

  case 772: // enable_updates: "enable-updates" ":" "boolean"
#line 2665 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4200 "dhcp4_parser.cc"
    break;

  case 773: // $@117: %empty
#line 2671 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4209 "dhcp4_parser.cc"
    break;

  case 774: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2674 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4219 "dhcp4_parser.cc"
    break;

  case 775: // server_port: "server-port" ":" "integer"
#line 2680 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4229 "dhcp4_parser.cc"
    break;

  case 776: // $@118: %empty
#line 2686 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4238 "dhcp4_parser.cc"
    break;

  case 777: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2689 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4248 "dhcp4_parser.cc"
    break;

  case 778: // sender_port: "sender-port" ":" "integer"
#line 2695 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 779: // max_queue_size: "max-queue-size" ":" "integer"
#line 2701 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4268 "dhcp4_parser.cc"
    break;

  case 780: // $@119: %empty
#line 2707 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4277 "dhcp4_parser.cc"
    break;

  case 781: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2710 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4286 "dhcp4_parser.cc"
    break;

  case 782: // ncr_protocol_value: "udp"
#line 2716 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4292 "dhcp4_parser.cc"
    break;

  case 783: // ncr_protocol_value: "tcp"
#line 2717 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4298 "dhcp4_parser.cc"
    break;

  case 784: // $@120: %empty
#line 2720 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4307 "dhcp4_parser.cc"
    break;

  case 785: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2723 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4317 "dhcp4_parser.cc"
    break;

  case 786: // $@121: %empty
#line 2730 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4326 "dhcp4_parser.cc"
    break;

  case 787: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2733 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4336 "dhcp4_parser.cc"
    break;

  case 788: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2740 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4346 "dhcp4_parser.cc"
    break;

  case 789: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2747 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4356 "dhcp4_parser.cc"
    break;

  case 790: // $@122: %empty
#line 2754 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4365 "dhcp4_parser.cc"
    break;

  case 791: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2757 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4374 "dhcp4_parser.cc"
    break;

  case 792: // $@123: %empty
#line 2763 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4383 "dhcp4_parser.cc"
    break;

  case 793: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2766 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4393 "dhcp4_parser.cc"
    break;

  case 794: // $@124: %empty
#line 2773 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4402 "dhcp4_parser.cc"
    break;

  case 795: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2776 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4412 "dhcp4_parser.cc"
    break;

  case 796: // $@125: %empty
#line 2783 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4421 "dhcp4_parser.cc"
    break;

  case 797: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2786 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4431 "dhcp4_parser.cc"
    break;

  case 798: // $@126: %empty
#line 2795 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4443 "dhcp4_parser.cc"
    break;

  case 799: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2801 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 800: // $@127: %empty
#line 2807 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 801: // sub_config_control: "{" $@127 config_control_params "}"
#line 2811 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4472 "dhcp4_parser.cc"
    break;

  case 804: // config_control_params: config_control_params ","
#line 2819 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4480 "dhcp4_parser.cc"
    break;

  case 807: // $@128: %empty
#line 2829 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4492 "dhcp4_parser.cc"
    break;

  case 808: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2835 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4501 "dhcp4_parser.cc"
    break;

  case 809: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2840 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4511 "dhcp4_parser.cc"
    break;

  case 810: // $@129: %empty
#line 2848 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4523 "dhcp4_parser.cc"
    break;

  case 811: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2854 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 814: // loggers_entries: loggers_entries ","
#line 2863 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4540 "dhcp4_parser.cc"
    break;

  case 815: // $@130: %empty
#line 2869 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4550 "dhcp4_parser.cc"
    break;

  case 816: // logger_entry: "{" $@130 logger_params "}"
#line 2873 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4558 "dhcp4_parser.cc"
    break;

  case 819: // logger_params: logger_params ","
#line 2879 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4566 "dhcp4_parser.cc"
    break;

  case 827: // debuglevel: "debuglevel" ":" "integer"
#line 2893 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4576 "dhcp4_parser.cc"
    break;

  case 828: // $@131: %empty
#line 2899 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4585 "dhcp4_parser.cc"
    break;

  case 829: // severity: "severity" $@131 ":" "constant string"
#line 2902 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4595 "dhcp4_parser.cc"
    break;

  case 830: // $@132: %empty
#line 2908 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4607 "dhcp4_parser.cc"
    break;

  case 831: // output_options_list: "output-options" $@132 ":" "[" output_options_list_content "]"
#line 2914 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4616 "dhcp4_parser.cc"
    break;

  case 834: // output_options_list_content: output_options_list_content ","
#line 2921 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4624 "dhcp4_parser.cc"
    break;

  case 835: // $@133: %empty
#line 2926 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4634 "dhcp4_parser.cc"
    break;

  case 836: // output_entry: "{" $@133 output_params_list "}"
#line 2930 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4642 "dhcp4_parser.cc"
    break;

  case 839: // output_params_list: output_params_list ","
#line 2936 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4650 "dhcp4_parser.cc"
    break;

  case 845: // $@134: %empty
#line 2948 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4659 "dhcp4_parser.cc"
    break;

  case 846: // output: "output" $@134 ":" "constant string"
#line 2951 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4669 "dhcp4_parser.cc"
    break;

  case 847: // flush: "flush" ":" "boolean"
#line 2957 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4679 "dhcp4_parser.cc"
    break;

  case 848: // maxsize: "maxsize" ":" "integer"
#line 2963 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4689 "dhcp4_parser.cc"
    break;

  case 849: // maxver: "maxver" ":" "integer"
#line 2969 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4699 "dhcp4_parser.cc"
    break;

  case 850: // $@135: %empty
#line 2975 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4708 "dhcp4_parser.cc"
    break;

  case 851: // pattern: "pattern" $@135 ":" "constant string"
#line 2978 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4718 "dhcp4_parser.cc"
    break;

  case 852: // $@136: %empty
#line 2984 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4730 "dhcp4_parser.cc"
    break;

  case 853: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2990 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4739 "dhcp4_parser.cc"
    break;

  case 856: // compatibility_params: compatibility_params ","
#line 2997 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4747 "dhcp4_parser.cc"
    break;

  case 862: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3009 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4757 "dhcp4_parser.cc"
    break;

  case 863: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3015 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4767 "dhcp4_parser.cc"
    break;

  case 864: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3021 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 865: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3027 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4787 "dhcp4_parser.cc"
    break;


#line 4791 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1022;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     597, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022,    18,    44,    47,    64,    82,    90,
      98,   129,   145,   153,   172,   179,   190,   295, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022,    44,  -164,   106,   133,   159,   332,
     -24,   201,   -28,   257,   212,  -113,   476,   176, -1022,   230,
     251,   252,   262,   326, -1022,    23, -1022, -1022, -1022, -1022,
     333,   340,   345, -1022, -1022, -1022,   346, -1022, -1022, -1022,
     347,   352,   353,   354,   366,   367,   370,   371,   372,   376,
     384, -1022,   385,   390,   391,   392,   404, -1022, -1022, -1022,
     405,   406,   421,   423, -1022, -1022, -1022,   430, -1022, -1022,
   -1022, -1022, -1022, -1022,   431,   433,   442, -1022, -1022, -1022,
   -1022, -1022,   450, -1022, -1022, -1022, -1022, -1022, -1022,   451,
     452,   456, -1022, -1022,   457, -1022,    42, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   459,   460,
     463,   466, -1022,    49, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
     468, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,    59, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022,   470, -1022, -1022, -1022,
   -1022,    65, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   290,
     478, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022,   328, -1022, -1022,   475, -1022, -1022, -1022,
     480, -1022, -1022,   379,   479, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   481,   482,
     484, -1022, -1022, -1022, -1022,   489,   486, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
      85, -1022, -1022, -1022,   495, -1022, -1022,   497, -1022,   499,
     500, -1022, -1022,   503,   507, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,    91, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
     511,    93, -1022, -1022, -1022, -1022,    44,    44, -1022,   297,
     519, -1022, -1022,   521,   523,   524,   306,   307,   308,   529,
     532,   540,   330,   545,   550,   551,   335,   336,   338,   341,
     342,   343,   348,   349,   350,   357,   358,   560,   360,   365,
     344,   351,   373,   564,   565,   571,   381,   386,   377,   387,
     585,   589,   590,   398,   603,   607,   608,   616,   631,   632,
     414,   420,   435,   640,   655,   656,   658,   662,   446,   665,
     666,   667,   668,   670,   671,   453,   454,   455,   675,   676,
   -1022,   133, -1022,   678,   679,   680,   462,   464,   465,   467,
     159, -1022,   685,   693,   694,   695,   696,   697,   487,   698,
     701,   703,   332, -1022,   705,   490,   -24, -1022,   708,   709,
     710,   711,   712,   713,   714,   715, -1022,   201, -1022,   731,
     732,   516,   734,   746,   747,   530, -1022,   257,   748,   533,
     534,   535, -1022,   212,   755,   760,   -70, -1022,   542,   764,
     765,   549,   767,   552,   553,   768,   773,   556,   558,   778,
     779,   780,   784,   476, -1022,   785,   570,   176, -1022, -1022,
   -1022,   788,   786,   789,   790,   792, -1022, -1022, -1022,   575,
     580,   581, -1022,   795,   810,   813, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022,   599, -1022, -1022,
   -1022, -1022, -1022,     8,   600,   601, -1022, -1022, -1022, -1022,
     817,   818,   819, -1022,   605,   383,   821,   820,   609,   319,
   -1022, -1022, -1022,   823,   825,   826,   827,   828, -1022,   829,
     830,   831,   832,   613,   614, -1022, -1022, -1022,   835,   834,
   -1022,   837,   263,   294, -1022, -1022, -1022, -1022, -1022,   623,
     624,   625,   841,   627,   630, -1022,   837,   633,   844, -1022,
     634, -1022, -1022,   837,   635,   636,   637,   638,   639,   641,
     642, -1022,   643,   644, -1022,   645,   646,   647, -1022, -1022,
     648, -1022, -1022, -1022, -1022,   649,   820, -1022, -1022,   650,
     651, -1022,   652, -1022, -1022,     5,   669, -1022, -1022,     8,
     653,   654,   657, -1022,   855, -1022, -1022,    44,   133,   176,
     159,   256, -1022, -1022, -1022,   578,   578,   868, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022,   869,   871,   872,
   -1022, -1022, -1022, -1022, -1022, -1022,   874, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022,   291,   875,   876,   877,   388,
     -79,   -29,   216,   476, -1022, -1022,   878,   187, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   879,
   -1022, -1022, -1022, -1022,   189, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022,   868, -1022,   100,   101,   115, -1022, -1022,
     123, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   883,   884,
     885,   886,   887,   888,   889,   890,   891,   892, -1022,   893,
   -1022, -1022, -1022, -1022, -1022,   143, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   169, -1022,
     894,   895, -1022, -1022,   896,   898, -1022, -1022,   897,   901,
   -1022, -1022,   899,   903, -1022, -1022,   902,   904, -1022, -1022,
   -1022, -1022, -1022, -1022,    35, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,   109, -1022, -1022,   905,   906, -1022, -1022,   907,
     909, -1022,   910,   911,   912,   913,   914,   915,   182, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022,   916,   917,   918, -1022,
     220, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,   221, -1022, -1022, -1022,   919, -1022,   920, -1022,
   -1022, -1022,   222, -1022, -1022, -1022, -1022, -1022,   229, -1022,
     155, -1022,   921,   922,   923,   924, -1022,   239, -1022, -1022,
   -1022, -1022, -1022,   690, -1022,   925,   926, -1022, -1022, -1022,
   -1022,   927,   928, -1022, -1022, -1022,   929,   932,   256, -1022,
     933,   934,   935,   936,   720,   707,   721,   722,   723,   725,
     726,   727,   728,   729,   939,   730,   948,   949,   950,   951,
     578, -1022, -1022,   578, -1022,   868,   332, -1022,   869,   257,
   -1022,   871,   212, -1022,   872,   660, -1022,   874,   291, -1022,
     253,   875, -1022,   201, -1022,   876,  -113, -1022,   877,   735,
     736,   737,   739,   740,   742,   388, -1022,   741,   745,   750,
     -79, -1022,   963,   970,   -29, -1022,   752,   978,   771,   981,
     216, -1022, -1022,   -40,   878, -1022,   781,   800,   804,   808,
     187, -1022, -1022,   995,   999,   -24, -1022,   879,  1003, -1022,
   -1022,   812,   814, -1022,    88,   824,   838,   845, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   234, -1022,
     847,   850,   900,   908, -1022,   243, -1022,   247, -1022,  1029,
   -1022,  1033, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
     249, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022,  1041, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022,  1039,  1054, -1022,
   -1022, -1022, -1022, -1022, -1022,  1107, -1022,   260, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
     930,   931, -1022, -1022,   938, -1022,    44, -1022, -1022,  1113,
   -1022, -1022, -1022, -1022, -1022,   268, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022,   940,   269, -1022,
     837, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,   660, -1022,  1114,  1118,   942, -1022,   253, -1022,
   -1022, -1022, -1022, -1022, -1022,  1119,   941,  1120,   -40, -1022,
   -1022, -1022, -1022, -1022,   946,   947, -1022, -1022,  1121, -1022,
     952, -1022, -1022, -1022,  1122, -1022, -1022,   170, -1022,   105,
    1122, -1022, -1022,  1123,  1126,  1127, -1022,   270, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022,  1128,   945,   953,   954,  1129,
     105, -1022,   956, -1022, -1022, -1022,   957, -1022, -1022, -1022
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   206,     9,   384,    11,   602,    13,
     631,    15,   520,    17,   529,    19,   568,    21,   346,    23,
     749,    25,   800,    27,    46,    39,     0,     0,     0,     0,
       0,   633,     0,   531,   570,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   798,   191,   224,
       0,     0,     0,   653,   655,   657,     0,   222,   235,   237,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,     0,     0,     0,     0,     0,   160,   167,   169,
       0,     0,     0,     0,   375,   518,   559,     0,   152,   173,
     462,   618,   620,   455,     0,     0,     0,   308,   681,   622,
     337,   358,     0,   323,   716,   730,   747,   180,   182,     0,
       0,     0,   810,   852,     0,   137,     0,    67,    70,    71,
      72,    73,    74,   108,   109,   110,   111,   112,    75,   103,
     134,   135,    92,    93,    94,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   114,   115,   126,   127,   128,
     130,   131,   132,   136,    78,    79,   100,    80,    81,    82,
     129,    86,    87,    76,   105,   106,   107,   104,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   113,   133,   208,   210,   214,     0,     0,
       0,     0,   205,     0,   193,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   440,   442,   444,   593,   438,   446,
       0,   450,   448,   677,   437,   389,   390,   391,   392,   393,
     417,   418,   419,   420,   421,   435,   407,   408,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   436,     0,   386,   396,   412,   413,   414,   397,   399,
     400,   403,   404,   405,   402,   398,   394,   395,   415,   416,
     401,   409,   410,   411,   406,   615,     0,   614,   610,   611,
     609,     0,   604,   607,   608,   612,   613,   675,   663,   665,
     669,   667,   673,   671,   659,   652,   646,   650,   651,     0,
     634,   635,   647,   648,   649,   643,   638,   644,   640,   641,
     642,   645,   639,     0,   549,   283,     0,   553,   551,   556,
       0,   545,   546,     0,   532,   533,   536,   548,   537,   538,
     539,   555,   540,   541,   542,   543,   544,   586,     0,     0,
       0,   584,   585,   588,   589,     0,   571,   572,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   354,   356,   351,
       0,   348,   352,   353,     0,   786,   773,     0,   776,     0,
       0,   780,   784,     0,     0,   790,   792,   794,   796,   771,
     769,   770,     0,   751,   754,   755,   756,   757,   758,   759,
     760,   761,   766,   762,   763,   764,   765,   767,   768,   807,
       0,     0,   802,   805,   806,    45,    50,     0,    37,    43,
       0,    64,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    69,    66,     0,     0,     0,     0,     0,     0,     0,
     195,   207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   388,   385,     0,     0,   606,   603,     0,     0,
       0,     0,     0,     0,     0,     0,   632,   637,   521,     0,
       0,     0,     0,     0,     0,     0,   530,   535,     0,     0,
       0,     0,   569,   574,     0,     0,   350,   347,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   753,   750,     0,     0,   804,   801,    49,
      41,     0,     0,     0,     0,     0,   154,   155,   156,     0,
       0,     0,   190,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,   185,   186,
     157,   158,   159,     0,     0,     0,   171,   172,   179,   184,
       0,     0,     0,   151,     0,     0,     0,     0,     0,     0,
     452,   453,   454,     0,     0,     0,     0,     0,   715,     0,
       0,     0,     0,     0,     0,   187,   188,   189,     0,     0,
      68,     0,     0,     0,   218,   219,   220,   221,   194,     0,
       0,     0,     0,     0,     0,   461,     0,     0,     0,   387,
       0,   617,   605,     0,     0,     0,     0,     0,     0,     0,
       0,   636,     0,     0,   547,     0,     0,     0,   558,   534,
       0,   590,   591,   592,   573,     0,     0,   349,   772,     0,
       0,   775,     0,   778,   779,     0,     0,   788,   789,     0,
       0,     0,     0,   752,     0,   809,   803,     0,     0,     0,
       0,     0,   654,   656,   658,     0,     0,   239,   150,   162,
     163,   164,   165,   166,   161,   168,   170,   377,   522,   561,
     153,   175,   176,   177,   178,   174,   464,    38,   619,   621,
     457,   458,   459,   460,   456,     0,     0,   624,   339,     0,
       0,     0,     0,     0,   181,   183,     0,     0,    51,   209,
     212,   213,   211,   216,   217,   215,   441,   443,   445,   595,
     439,   447,   451,   449,     0,   616,   676,   664,   666,   670,
     668,   674,   672,   660,   550,   284,   554,   552,   557,   587,
     355,   357,   787,   774,   777,   782,   783,   781,   785,   791,
     793,   795,   797,   239,    42,     0,     0,     0,   231,   233,
       0,   226,   229,   230,   271,   276,   278,   280,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   294,     0,
     300,   302,   304,   306,   270,     0,   246,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,     0,   244,
       0,   240,   241,   382,     0,   378,   379,   527,     0,   523,
     524,   566,     0,   562,   563,   469,     0,   465,   466,   318,
     319,   320,   321,   322,     0,   310,   313,   314,   315,   316,
     317,   686,     0,   683,   629,     0,   625,   626,   344,     0,
     340,   341,     0,     0,     0,     0,     0,     0,     0,   360,
     363,   364,   365,   366,   367,   368,     0,     0,     0,   333,
       0,   325,   328,   329,   330,   331,   332,   726,   728,   725,
     723,   724,     0,   718,   721,   722,     0,   742,     0,   745,
     738,   739,     0,   732,   735,   736,   737,   740,     0,   815,
       0,   812,     0,     0,     0,     0,   861,     0,   854,   857,
     858,   859,   860,    53,   600,     0,   596,   597,   661,   679,
     680,     0,     0,    62,   799,   192,     0,     0,   228,   225,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     248,   223,   236,     0,   238,   243,     0,   376,   381,   531,
     519,   526,   570,   560,   565,     0,   463,   468,   312,   309,
     688,   685,   682,   633,   623,   628,     0,   338,   343,     0,
       0,     0,     0,     0,     0,   362,   359,     0,     0,     0,
     327,   324,     0,     0,   720,   717,     0,     0,     0,     0,
     734,   731,   748,     0,   814,   811,     0,     0,     0,     0,
     856,   853,    55,     0,    54,     0,   594,   599,     0,   678,
     808,     0,     0,   227,     0,     0,     0,     0,   282,   285,
     286,   287,   288,   289,   290,   291,   292,   293,     0,   299,
       0,     0,     0,     0,   247,     0,   242,     0,   380,     0,
     525,     0,   564,   517,   492,   493,   494,   477,   478,   497,
     498,   499,   500,   501,   515,   480,   481,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     516,   474,   475,   476,   490,   491,   487,   488,   489,   486,
       0,   471,   479,   495,   496,   482,   483,   484,   485,   467,
     311,   710,   712,     0,   704,   705,   706,   707,   708,   709,
     697,   698,   702,   703,   699,   700,   701,     0,   689,   690,
     693,   694,   695,   696,   684,     0,   627,     0,   342,   369,
     370,   371,   372,   373,   374,   361,   334,   335,   336,   326,
       0,     0,   719,   741,     0,   744,     0,   733,   830,     0,
     828,   826,   820,   824,   825,     0,   817,   822,   823,   821,
     813,   862,   863,   864,   865,   855,    52,    57,     0,   598,
       0,   232,   234,   273,   274,   275,   272,   277,   279,   281,
     296,   297,   298,   295,   301,   303,   305,   307,   245,   383,
     528,   567,   473,   470,     0,     0,     0,   687,   692,   630,
     345,   727,   729,   743,   746,     0,     0,     0,   819,   816,
      56,   601,   662,   472,     0,     0,   714,   691,     0,   827,
       0,   818,   711,   713,     0,   829,   835,     0,   832,     0,
     834,   831,   845,     0,     0,     0,   850,     0,   837,   840,
     841,   842,   843,   844,   833,     0,     0,     0,     0,     0,
     839,   836,     0,   847,   848,   849,     0,   838,   846,   851
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022,   -59, -1022,  -593, -1022,   193,
   -1022, -1022, -1022, -1022, -1022, -1022,  -643, -1022, -1022, -1022,
     -67, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   204,   626,
     -30,   -26,    26,   -54,   -37,   -27,     0,    14,    16,    45,
   -1022, -1022, -1022, -1022,    48, -1022, -1022,    50,    51,    52,
      53,    55,    56, -1022,   415,    58, -1022,    63, -1022,    66,
      68,    69, -1022, -1022,    70,    71, -1022,    73, -1022,    74,
   -1022, -1022, -1022, -1022, -1022,    33, -1022, -1022,   395,   615,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   138,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,   315, -1022,
     114, -1022,  -724,   120, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022,   -45, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
     103, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,    83,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022,    94, -1022, -1022,
   -1022,    99,   582, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
      89, -1022, -1022, -1022, -1022, -1022, -1022, -1021, -1022, -1022,
   -1022,   118, -1022, -1022, -1022,   121,   617, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1019, -1022,    78, -1022,    79,
   -1022,    76,    81,    84,    86, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,   116, -1022, -1022,  -110,   -62, -1022, -1022, -1022,
   -1022, -1022,   124, -1022, -1022, -1022,   125, -1022,   602, -1022,
     -63, -1022, -1022, -1022, -1022, -1022,   -44, -1022, -1022, -1022,
   -1022, -1022,   -23, -1022, -1022, -1022,   122, -1022, -1022, -1022,
     137, -1022,   598, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022,    92, -1022, -1022, -1022,    95,
     661, -1022, -1022, -1022,   -49, -1022,   -10, -1022,   -56, -1022,
   -1022, -1022,   126, -1022, -1022, -1022,   127, -1022,   663,     3,
   -1022,    13, -1022,    29, -1022,   389, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1018, -1022, -1022, -1022, -1022, -1022,   132,
   -1022, -1022, -1022,   -90, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022,   117, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022,   112, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022,   411,   604, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022,   461,   606, -1022, -1022, -1022, -1022,
   -1022, -1022,   111, -1022, -1022,   -92, -1022, -1022, -1022, -1022,
   -1022, -1022,  -112, -1022, -1022,  -131, -1022, -1022, -1022, -1022,
   -1022, -1022, -1022, -1022, -1022, -1022,   119, -1022, -1022, -1022,
   -1022
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   758,
      82,    83,    39,    64,    79,    80,   779,   983,  1083,  1084,
     854,    41,    66,    85,   440,    86,    43,    67,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   467,   170,   171,   484,   172,   173,   174,   175,
     176,   177,   178,   473,   744,   179,   474,   180,   475,   181,
     182,   183,   485,   755,   184,   185,   503,   186,   504,   187,
     188,   189,   190,   191,   192,   193,   194,   444,   233,   234,
      45,    68,   235,   513,   236,   514,   782,   237,   515,   785,
     238,   239,   240,   241,   195,   453,   196,   445,   830,   831,
     832,   996,   833,   997,   197,   454,   198,   455,   880,   881,
     882,  1023,   855,   856,   857,  1000,  1246,   858,  1001,   859,
    1002,   860,  1003,   861,   862,   550,   863,   864,   865,   866,
     867,   868,   869,   870,   871,   872,  1014,  1253,   873,   874,
    1016,   875,  1017,   876,  1018,   877,  1019,   199,   493,   904,
     905,   906,   907,   908,   909,   910,   200,   499,   940,   941,
     942,   943,   944,   201,   496,   919,   920,   921,  1046,    59,
      75,   390,   391,   392,   564,   393,   565,   202,   497,   928,
     929,   930,   931,   932,   933,   934,   935,   203,   480,   884,
     885,   886,  1026,    47,    69,   282,   283,   284,   526,   285,
     522,   286,   523,   287,   524,   288,   527,   289,   530,   290,
     529,   204,   205,   206,   207,   489,   764,   295,   208,   486,
     896,   897,   898,  1035,  1160,  1161,   209,   481,    53,    72,
     888,   889,   890,  1029,    55,    73,   353,   354,   355,   356,
     357,   358,   359,   549,   360,   553,   361,   552,   362,   363,
     554,   364,   210,   482,   892,   893,   894,  1032,    57,    74,
     375,   376,   377,   378,   379,   558,   380,   381,   382,   383,
     384,   297,   525,   985,   986,   987,  1085,    49,    70,   311,
     312,   313,   534,   314,   211,   487,   212,   488,   213,   495,
     915,   916,   917,  1043,    51,    71,   329,   330,   331,   214,
     449,   215,   450,   216,   451,   335,   545,   990,  1088,   336,
     539,   337,   540,   338,   542,   339,   541,   340,   544,   341,
     543,   342,   538,   304,   531,   991,   217,   494,   912,   913,
    1040,  1187,  1188,  1189,  1190,  1191,  1264,  1192,  1265,  1193,
     218,   219,   500,   952,   953,   954,  1062,   955,  1063,   220,
     501,   962,   963,   964,   965,  1067,   966,   967,  1069,   221,
     502,    61,    76,   412,   413,   414,   415,   570,   416,   417,
     572,   418,   419,   420,   575,   817,   421,   576,   422,   569,
     423,   424,   425,   579,   426,   580,   427,   581,   428,   582,
     222,   443,    63,    77,   431,   432,   433,   585,   434,   223,
     508,   970,   971,  1073,  1225,  1226,  1227,  1228,  1277,  1229,
    1275,  1297,  1298,  1299,  1307,  1308,  1309,  1315,  1310,  1311,
    1312,  1313,  1319,   224,   509,   977,   978,   979,   980,   981,
     982
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     155,   232,   254,   307,   325,    78,   351,   371,   389,   409,
     343,   373,   878,   300,  1152,   258,  1153,  1168,    28,   242,
     298,   315,   327,   815,   365,   385,   441,   410,   352,   372,
     374,   442,   259,   792,   387,   388,   131,   132,  1038,   255,
     796,  1039,   260,   256,   757,   511,   296,   310,   326,    29,
     512,    30,   520,    31,    40,   345,    81,   521,   243,   299,
     316,   328,   532,   366,   386,   125,   411,   533,   536,   261,
     126,    42,   301,   537,   332,   131,   132,   387,   388,   936,
     937,   938,   302,   262,   333,   263,   131,   132,   566,    44,
     305,   131,   132,   567,   583,   257,   587,    46,   303,   584,
     334,   588,   281,   511,   587,    48,   251,   154,   993,   994,
     252,   306,  1041,   757,   264,  1042,    84,   265,   520,   266,
     267,   268,   269,   995,   270,   271,   998,   272,  1243,  1244,
    1245,   999,   273,   947,   948,   274,    50,   275,   276,   277,
     278,   154,   279,   280,    87,   291,  1020,    88,   308,   309,
     292,  1021,    52,   293,  1218,   294,  1219,  1220,  1074,    89,
      54,  1075,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,  1020,  1300,   225,   226,  1301,  1022,   227,    56,
     154,   228,   229,   230,   231,  1055,    58,   816,   429,   430,
    1056,   154,   739,   740,   741,   742,   154,    60,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,  1060,  1064,  1070,   125,   126,  1061,  1065,
    1071,   743,   583,    93,    94,    95,   435,  1072,   127,   128,
     129,  1152,  1080,  1153,  1168,   130,  1020,  1081,   131,   132,
     532,  1258,  1262,   133,   436,  1259,   437,  1263,   134,   135,
     136,   137,   138,   566,    32,    33,    34,    35,  1270,   139,
     438,  1278,   536,  1320,   131,   132,  1279,  1281,  1321,   140,
     780,   781,   141,   828,   829,    93,    94,    95,    96,   142,
     143,  1250,  1251,  1252,   144,   126,   344,   145,   546,  1115,
    1302,   146,    62,  1303,  1304,  1305,  1306,   345,   367,   346,
     347,   368,   369,   370,   783,   784,   131,   132,   100,   101,
     102,   147,   148,   149,   150,   151,   152,   131,   132,   439,
     317,   131,   132,   324,   988,   153,   548,   446,   318,   319,
     320,   321,   322,   323,   447,   324,   125,   126,   345,   448,
     452,   456,   345,   154,   346,   347,   457,   458,   459,   348,
     349,   350,    91,    92,    93,    94,    95,    96,   131,   132,
     460,   461,   131,   132,   462,   463,   464,   589,   590,   154,
     465,   956,   957,   958,  1171,  1172,  1173,   556,   466,   468,
     972,   973,   974,   975,   469,   470,   471,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   154,   472,   476,
     477,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   154,   244,   245,   246,   478,   126,   479,   899,   900,
     901,   902,   154,   903,   483,   490,   959,   491,   128,   129,
     760,   761,   762,   763,   155,   247,   492,   131,   132,   248,
     249,   250,   133,   232,   498,   505,   506,   134,   135,   136,
     507,   510,   251,   516,   517,   254,   252,   518,   139,   307,
     519,   242,   528,   154,   535,   253,   300,   154,   258,   551,
     325,   547,   557,   298,   555,   559,   560,   315,   561,   563,
     351,   751,   752,   753,   754,   259,   371,   562,   327,   568,
     373,   571,   255,   573,   574,   260,   256,   577,   365,   296,
     243,   578,   352,   310,   385,   586,   409,   591,   372,   374,
     147,   148,   299,   592,   326,   593,   316,   594,   595,   596,
     597,   598,   261,   599,   410,   301,   600,   328,   922,   923,
     924,   925,   926,   927,   601,   302,   262,   366,   263,   603,
     332,   602,   154,   386,   604,   605,   606,   607,   257,   608,
     333,   303,   609,   610,   617,   281,   611,   620,   623,   624,
     612,   613,   614,   411,   621,   625,   334,   264,   615,   616,
     265,   618,   266,   267,   268,   269,   619,   270,   271,   630,
     272,   131,   132,   631,   632,   273,   622,  1282,   274,   628,
     275,   276,   277,   278,   626,   279,   280,   634,   291,   627,
     629,   635,   636,   292,   308,   309,   293,   834,   294,   633,
     637,   835,   836,   837,   838,   839,   840,   841,   842,   843,
     844,   845,   846,   847,   848,   638,   639,   640,   849,   850,
     851,   852,   853,   641,   643,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   642,   644,
     645,   155,   646,   232,   407,   408,   647,   648,   824,   649,
     650,   651,   652,   345,   653,   654,   655,   656,   657,   658,
     659,   242,   661,   662,   663,   664,   666,   665,   667,   669,
      91,    92,    93,    94,    95,    96,   154,   670,   671,   672,
     673,   674,   676,   939,   949,   677,   409,   678,   675,   680,
     976,   681,   683,   684,   685,   686,   687,   688,   689,   690,
     243,   945,   950,   960,   410,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   692,   693,   694,   695,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     696,   697,   700,   698,   126,   345,   701,   702,   703,   705,
     946,   951,   961,   411,   706,   708,   128,   129,   709,   710,
     711,   712,   715,   713,   714,   131,   132,   716,   249,   717,
     133,   718,   719,   720,   721,   134,   135,   136,   722,   724,
     251,   725,   727,   728,   252,   732,   729,   730,   154,   731,
     733,   734,   735,   253,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   736,   737,   738,
     745,   746,   747,   748,   749,   750,   756,    30,   765,   759,
     766,   767,   768,   774,   775,   769,   770,   771,   772,   773,
     776,   777,   778,   786,   787,   788,   789,   790,   147,   148,
     791,   794,   818,   793,   795,   797,   798,   799,   800,   801,
     823,   802,   803,   804,   805,   806,   807,   808,   809,   810,
     812,   813,   814,   820,   821,   879,   883,   822,   887,   891,
     154,   895,   911,   914,   918,   969,   984,  1004,  1005,  1006,
    1007,  1008,  1009,  1010,  1011,  1012,  1013,  1015,  1025,   811,
    1024,  1028,  1027,  1030,  1031,  1033,  1034,  1037,  1036,  1045,
    1082,  1044,  1048,  1047,  1049,  1050,  1051,  1052,  1053,  1054,
    1057,  1058,  1059,  1066,  1068,  1076,  1077,  1078,  1079,  1087,
    1099,  1086,   825,  1091,  1090,  1089,  1092,  1094,  1095,  1096,
    1097,  1098,  1100,  1108,  1102,  1101,  1103,  1104,  1105,  1106,
    1107,  1109,  1110,  1111,  1112,  1113,  1199,  1200,  1201,   254,
    1202,  1203,   351,  1204,  1206,   371,  1207,  1210,  1123,   373,
     300,  1208,   258,  1174,  1211,  1213,   325,   298,  1180,   389,
     365,  1127,  1214,   385,   352,  1216,  1163,   372,   374,   259,
    1151,  1182,  1215,   939,   327,  1179,   255,   949,  1128,   260,
     256,  1236,  1237,   296,  1231,  1124,  1221,  1240,  1129,  1125,
    1175,   945,  1162,   976,  1176,   950,   299,  1181,   307,   366,
     326,   960,   386,  1232,  1223,  1164,   261,  1233,  1222,   301,
    1183,  1234,  1241,   328,  1242,  1130,   315,  1260,  1165,   302,
     262,  1261,   263,  1184,  1247,  1266,   332,  1267,  1166,  1131,
     946,  1132,   257,  1185,   951,   303,   333,  1268,  1248,   281,
     961,  1126,   310,  1224,  1167,  1249,  1177,  1254,  1150,  1186,
    1255,   264,   334,  1178,   265,   316,   266,   267,   268,   269,
    1133,   270,   271,  1134,   272,  1135,  1136,  1137,  1138,   273,
    1139,  1140,   274,  1141,   275,   276,   277,   278,  1142,   279,
     280,  1143,   291,  1144,  1145,  1146,  1147,   292,  1148,  1149,
     293,  1156,   294,  1154,  1155,  1269,  1157,  1276,  1284,  1158,
    1256,  1159,  1285,  1288,  1290,   827,  1294,  1316,  1257,  1296,
    1317,  1318,  1322,  1326,   819,   668,  1093,   660,   992,  1116,
    1114,  1170,  1198,  1209,  1205,  1197,  1118,  1117,   707,   679,
    1271,  1272,  1283,  1169,  1119,  1120,  1122,  1274,  1273,   699,
    1280,   704,  1289,   308,   309,  1286,  1292,  1293,  1323,  1121,
    1195,  1196,  1295,  1194,  1324,  1325,  1328,  1329,  1287,  1239,
    1238,  1212,  1217,   989,   968,  1230,  1291,   723,  1314,  1327,
     826,     0,     0,   726,     0,  1123,     0,   682,     0,  1235,
       0,  1174,     0,     0,     0,     0,  1180,     0,  1127,     0,
     691,  1221,     0,  1163,     0,     0,     0,  1151,     0,  1182,
       0,     0,     0,  1179,     0,  1128,     0,     0,     0,  1223,
       0,     0,  1124,  1222,     0,  1129,  1125,     0,  1175,  1162,
       0,     0,  1176,     0,     0,  1181,     0,     0,     0,     0,
       0,     0,  1164,     0,     0,     0,     0,     0,  1183,     0,
       0,     0,  1130,     0,     0,  1165,     0,     0,  1224,     0,
       0,  1184,     0,     0,     0,  1166,  1131,     0,  1132,     0,
       0,  1185,     0,     0,     0,     0,     0,     0,  1126,     0,
       0,  1167,     0,     0,  1177,  1150,     0,  1186,     0,     0,
       0,  1178,     0,     0,     0,     0,     0,  1133,     0,     0,
    1134,     0,  1135,  1136,  1137,  1138,     0,  1139,  1140,     0,
    1141,     0,     0,     0,     0,  1142,     0,     0,  1143,     0,
    1144,  1145,  1146,  1147,     0,  1148,  1149,     0,  1156,     0,
    1154,  1155,     0,  1157,     0,     0,  1158,     0,  1159
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   736,    69,  1035,    69,  1035,  1035,     0,    68,
      69,    70,    71,    18,    73,    74,     3,    76,    73,    74,
      74,     8,    69,   676,   147,   148,   115,   116,     3,    69,
     683,     6,    69,    69,   637,     3,    69,    70,    71,     5,
       8,     7,     3,     9,     7,    95,   220,     8,    68,    69,
      70,    71,     3,    73,    74,    93,    76,     8,     3,    69,
      94,     7,    69,     8,    71,   115,   116,   147,   148,   158,
     159,   160,    69,    69,    71,    69,   115,   116,     3,     7,
     114,   115,   116,     8,     3,    69,     3,     7,    69,     8,
      71,     8,    69,     3,     3,     7,   130,   220,     8,     8,
     134,   135,     3,   706,    69,     6,    10,    69,     3,    69,
      69,    69,    69,     8,    69,    69,     3,    69,    40,    41,
      42,     8,    69,   162,   163,    69,     7,    69,    69,    69,
      69,   220,    69,    69,    11,    69,     3,    14,    70,    70,
      69,     8,     7,    69,   194,    69,   196,   197,     3,    26,
       7,     6,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     3,     3,    15,    16,     6,     8,    19,     7,
     220,    22,    23,    24,    25,     3,     7,   182,    12,    13,
       8,   220,   184,   185,   186,   187,   220,     7,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     3,     3,     3,    93,    94,     8,     8,
       8,   223,     3,    32,    33,    34,     6,     8,   105,   106,
     107,  1262,     3,  1262,  1262,   112,     3,     8,   115,   116,
       3,     8,     3,   120,     3,     8,     4,     8,   125,   126,
     127,   128,   129,     3,   220,   221,   222,   223,     8,   136,
       8,     3,     3,     3,   115,   116,     8,     8,     8,   146,
      17,    18,   149,    27,    28,    32,    33,    34,    35,   156,
     157,    57,    58,    59,   161,    94,    39,   164,     8,  1023,
     195,   168,     7,   198,   199,   200,   201,    95,    96,    97,
      98,    99,   100,   101,    20,    21,   115,   116,    65,    66,
      67,   188,   189,   190,   191,   192,   193,   115,   116,     3,
     129,   115,   116,   144,   145,   202,     8,     4,   137,   138,
     139,   140,   141,   142,     4,   144,    93,    94,    95,     4,
       4,     4,    95,   220,    97,    98,     4,     4,     4,   102,
     103,   104,    30,    31,    32,    33,    34,    35,   115,   116,
       4,     4,   115,   116,     4,     4,     4,   436,   437,   220,
       4,   165,   166,   167,   131,   132,   133,     8,     4,     4,
     203,   204,   205,   206,     4,     4,     4,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   220,     4,     4,
       4,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,   220,    90,    91,    92,     4,    94,     4,   137,   138,
     139,   140,   220,   142,     4,     4,   220,     4,   106,   107,
     121,   122,   123,   124,   511,   113,     4,   115,   116,   117,
     118,   119,   120,   520,     4,     4,     4,   125,   126,   127,
       4,     4,   130,     4,     4,   532,   134,     4,   136,   536,
       4,   520,     4,   220,     4,   143,   532,   220,   532,     4,
     547,     3,     3,   532,     4,     4,     4,   536,     4,     3,
     557,   108,   109,   110,   111,   532,   563,     8,   547,     4,
     563,     4,   532,     4,     4,   532,   532,     4,   557,   532,
     520,     4,   557,   536,   563,     4,   583,   220,   563,   563,
     188,   189,   532,     4,   547,     4,   536,     4,     4,   223,
     223,   223,   532,     4,   583,   532,     4,   547,   150,   151,
     152,   153,   154,   155,     4,   532,   532,   557,   532,     4,
     547,   221,   220,   563,     4,     4,   221,   221,   532,   221,
     547,   532,   221,   221,     4,   532,   223,   223,     4,     4,
     222,   222,   222,   583,   223,     4,   547,   532,   221,   221,
     532,   221,   532,   532,   532,   532,   221,   532,   532,     4,
     532,   115,   116,     4,     4,   532,   223,  1240,   532,   222,
     532,   532,   532,   532,   223,   532,   532,     4,   532,   223,
     223,     4,     4,   532,   536,   536,   532,    39,   532,   221,
       4,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,     4,     4,   223,    60,    61,
      62,    63,    64,   223,     4,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   223,     4,
       4,   728,     4,   730,   188,   189,     4,   221,   727,     4,
       4,     4,     4,    95,     4,     4,   223,   223,   223,     4,
       4,   730,     4,     4,     4,   223,   221,   223,   221,     4,
      30,    31,    32,    33,    34,    35,   220,     4,     4,     4,
       4,     4,     4,   770,   771,     4,   773,     4,   221,     4,
     777,   221,     4,     4,     4,     4,     4,     4,     4,     4,
     730,   770,   771,   772,   773,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     4,     4,   221,     4,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       4,     4,     4,   223,    94,    95,   223,   223,   223,     4,
     770,   771,   772,   773,     4,   223,   106,   107,     4,     4,
     221,     4,     4,   221,   221,   115,   116,     4,   118,   223,
     120,   223,     4,     4,     4,   125,   126,   127,     4,     4,
     130,   221,     4,     7,   134,   220,     7,     7,   220,     7,
     220,   220,     7,   143,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,     7,     5,   220,
     220,   220,     5,     5,     5,   220,     5,     7,     5,   220,
       5,     5,     5,   220,   220,     7,     7,     7,     7,     7,
       5,     7,     5,   220,   220,   220,     5,   220,   188,   189,
     220,     7,   183,   220,   220,   220,   220,   220,   220,   220,
       5,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,     7,     7,   220,     7,     7,
     220,     7,     7,     7,     7,     7,     7,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   706,
       6,     3,     6,     6,     3,     6,     3,     3,     6,     3,
     220,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     223,     6,   728,     4,     6,     8,     4,     4,     4,     4,
       4,   221,   221,     4,   221,   223,   221,   221,   221,   221,
     221,   221,     4,     4,     4,     4,   221,   221,   221,  1026,
     221,   221,  1029,   221,   223,  1032,   221,     4,  1035,  1032,
    1026,   221,  1026,  1040,     4,   223,  1043,  1026,  1040,  1046,
    1029,  1035,     4,  1032,  1029,     4,  1035,  1032,  1032,  1026,
    1035,  1040,   221,  1060,  1043,  1040,  1026,  1064,  1035,  1026,
    1026,     6,     3,  1026,   223,  1035,  1073,     4,  1035,  1035,
    1040,  1060,  1035,  1080,  1040,  1064,  1026,  1040,  1085,  1029,
    1043,  1070,  1032,   223,  1073,  1035,  1026,   223,  1073,  1026,
    1040,   223,   220,  1043,   220,  1035,  1085,     8,  1035,  1026,
    1026,     8,  1026,  1040,   220,     4,  1043,     8,  1035,  1035,
    1060,  1035,  1026,  1040,  1064,  1026,  1043,     3,   220,  1026,
    1070,  1035,  1085,  1073,  1035,   220,  1040,   220,  1035,  1040,
     220,  1026,  1043,  1040,  1026,  1085,  1026,  1026,  1026,  1026,
    1035,  1026,  1026,  1035,  1026,  1035,  1035,  1035,  1035,  1026,
    1035,  1035,  1026,  1035,  1026,  1026,  1026,  1026,  1035,  1026,
    1026,  1035,  1026,  1035,  1035,  1035,  1035,  1026,  1035,  1035,
    1026,  1035,  1026,  1035,  1035,     8,  1035,     4,     4,  1035,
     220,  1035,     4,     4,     4,   730,     5,     4,   220,     7,
       4,     4,     4,     4,   719,   520,   998,   511,   823,  1025,
    1020,  1038,  1048,  1060,  1055,  1046,  1028,  1026,   566,   532,
     220,   220,  1262,  1037,  1029,  1031,  1034,  1216,   220,   557,
     220,   563,   221,  1085,  1085,   223,   220,   220,   223,  1032,
    1043,  1045,   220,  1041,   221,   221,   220,   220,  1268,  1087,
    1085,  1064,  1070,   794,   773,  1074,  1278,   583,  1300,  1320,
     729,    -1,    -1,   587,    -1,  1262,    -1,   536,    -1,  1080,
      -1,  1268,    -1,    -1,    -1,    -1,  1268,    -1,  1262,    -1,
     547,  1278,    -1,  1262,    -1,    -1,    -1,  1262,    -1,  1268,
      -1,    -1,    -1,  1268,    -1,  1262,    -1,    -1,    -1,  1278,
      -1,    -1,  1262,  1278,    -1,  1262,  1262,    -1,  1268,  1262,
      -1,    -1,  1268,    -1,    -1,  1268,    -1,    -1,    -1,    -1,
      -1,    -1,  1262,    -1,    -1,    -1,    -1,    -1,  1268,    -1,
      -1,    -1,  1262,    -1,    -1,  1262,    -1,    -1,  1278,    -1,
      -1,  1268,    -1,    -1,    -1,  1262,  1262,    -1,  1262,    -1,
      -1,  1268,    -1,    -1,    -1,    -1,    -1,    -1,  1262,    -1,
      -1,  1262,    -1,    -1,  1268,  1262,    -1,  1268,    -1,    -1,
      -1,  1268,    -1,    -1,    -1,    -1,    -1,  1262,    -1,    -1,
    1262,    -1,  1262,  1262,  1262,  1262,    -1,  1262,  1262,    -1,
    1262,    -1,    -1,    -1,    -1,  1262,    -1,    -1,  1262,    -1,
    1262,  1262,  1262,  1262,    -1,  1262,  1262,    -1,  1262,    -1,
    1262,  1262,    -1,  1262,    -1,    -1,  1262,    -1,  1262
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,     0,     5,
       7,     9,   220,   221,   222,   223,   239,   240,   241,   246,
       7,   255,     7,   260,     7,   314,     7,   427,     7,   511,
       7,   528,     7,   462,     7,   468,     7,   492,     7,   403,
       7,   595,     7,   626,   247,   242,   256,   261,   315,   428,
     512,   529,   463,   469,   493,   404,   596,   627,   239,   248,
     249,   220,   244,   245,    10,   257,   259,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    93,    94,   105,   106,   107,
     112,   115,   116,   120,   125,   126,   127,   128,   129,   136,
     146,   149,   156,   157,   161,   164,   168,   188,   189,   190,
     191,   192,   193,   202,   220,   254,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     277,   278,   280,   281,   282,   283,   284,   285,   286,   289,
     291,   293,   294,   295,   298,   299,   301,   303,   304,   305,
     306,   307,   308,   309,   310,   328,   330,   338,   340,   381,
     390,   397,   411,   421,   445,   446,   447,   448,   452,   460,
     486,   518,   520,   522,   533,   535,   537,   560,   574,   575,
     583,   593,   624,   633,   657,    15,    16,    19,    22,    23,
      24,    25,   254,   312,   313,   316,   318,   321,   324,   325,
     326,   327,   518,   520,    90,    91,    92,   113,   117,   118,
     119,   130,   134,   143,   254,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   278,   281,   282,   283,   284,
     285,   286,   289,   291,   293,   294,   295,   298,   299,   301,
     303,   309,   429,   430,   431,   433,   435,   437,   439,   441,
     443,   445,   446,   447,   448,   451,   486,   505,   518,   520,
     522,   533,   535,   537,   557,   114,   135,   254,   441,   443,
     486,   513,   514,   515,   517,   518,   520,   129,   137,   138,
     139,   140,   141,   142,   144,   254,   486,   518,   520,   530,
     531,   532,   533,   535,   537,   539,   543,   545,   547,   549,
     551,   553,   555,   460,    39,    95,    97,    98,   102,   103,
     104,   254,   358,   470,   471,   472,   473,   474,   475,   476,
     478,   480,   482,   483,   485,   518,   520,    96,    99,   100,
     101,   254,   358,   474,   480,   494,   495,   496,   497,   498,
     500,   501,   502,   503,   504,   518,   520,   147,   148,   254,
     405,   406,   407,   409,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   188,   189,   254,
     518,   520,   597,   598,   599,   600,   602,   603,   605,   606,
     607,   610,   612,   614,   615,   616,   618,   620,   622,    12,
      13,   628,   629,   630,   632,     6,     3,     4,     8,     3,
     258,     3,     8,   625,   311,   331,     4,     4,     4,   534,
     536,   538,     4,   329,   339,   341,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   276,     4,     4,
       4,     4,     4,   287,   290,   292,     4,     4,     4,     4,
     422,   461,   487,     4,   279,   296,   453,   519,   521,   449,
       4,     4,     4,   382,   561,   523,   398,   412,     4,   391,
     576,   584,   594,   300,   302,     4,     4,     4,   634,   658,
       4,     3,     8,   317,   319,   322,     4,     4,     4,     4,
       3,     8,   434,   436,   438,   506,   432,   440,     4,   444,
     442,   558,     3,     8,   516,     4,     3,     8,   556,   544,
     546,   550,   548,   554,   552,   540,     8,     3,     8,   477,
     359,     4,   481,   479,   484,     4,     8,     3,   499,     4,
       4,     4,     8,     3,   408,   410,     3,     8,     4,   613,
     601,     4,   604,     4,     4,   608,   611,     4,     4,   617,
     619,   621,   623,     3,     8,   631,     4,     3,     8,   239,
     239,   220,     4,     4,     4,     4,   223,   223,   223,     4,
       4,     4,   221,     4,     4,     4,   221,   221,   221,   221,
     221,   223,   222,   222,   222,   221,   221,     4,   221,   221,
     223,   223,   223,     4,     4,     4,   223,   223,   222,   223,
       4,     4,     4,   221,     4,     4,     4,     4,     4,     4,
     223,   223,   223,     4,     4,     4,     4,     4,   221,     4,
       4,     4,     4,     4,     4,   223,   223,   223,     4,     4,
     263,     4,     4,     4,   223,   223,   221,   221,   313,     4,
       4,     4,     4,     4,     4,   221,     4,     4,     4,   430,
       4,   221,   514,     4,     4,     4,     4,     4,     4,     4,
       4,   532,     4,     4,   221,     4,     4,     4,   223,   472,
       4,   223,   223,   223,   496,     4,     4,   406,   223,     4,
       4,   221,     4,   221,   221,     4,     4,   223,   223,     4,
       4,     4,     4,   598,     4,   221,   629,     4,     7,     7,
       7,     7,   220,   220,   220,     7,     7,     5,   220,   184,
     185,   186,   187,   223,   288,   220,   220,     5,     5,     5,
     220,   108,   109,   110,   111,   297,     5,   241,   243,   220,
     121,   122,   123,   124,   450,     5,     5,     5,     5,     7,
       7,     7,     7,     7,   220,   220,     5,     7,     5,   250,
      17,    18,   320,    20,    21,   323,   220,   220,   220,     5,
     220,   220,   250,   220,     7,   220,   250,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   243,   220,   220,   220,    18,   182,   609,   183,   288,
     220,   220,   220,     5,   239,   262,   628,   312,    27,    28,
     332,   333,   334,   336,    39,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    60,
      61,    62,    63,    64,   254,   346,   347,   348,   351,   353,
     355,   357,   358,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   372,   373,   375,   377,   379,   346,     7,
     342,   343,   344,     7,   423,   424,   425,     7,   464,   465,
     466,     7,   488,   489,   490,     7,   454,   455,   456,   137,
     138,   139,   140,   142,   383,   384,   385,   386,   387,   388,
     389,     7,   562,   563,     7,   524,   525,   526,     7,   399,
     400,   401,   150,   151,   152,   153,   154,   155,   413,   414,
     415,   416,   417,   418,   419,   420,   158,   159,   160,   254,
     392,   393,   394,   395,   396,   518,   520,   162,   163,   254,
     518,   520,   577,   578,   579,   581,   165,   166,   167,   220,
     518,   520,   585,   586,   587,   588,   590,   591,   597,     7,
     635,   636,   203,   204,   205,   206,   254,   659,   660,   661,
     662,   663,   664,   251,     7,   507,   508,   509,   145,   539,
     541,   559,   342,     8,     8,     8,   335,   337,     3,     8,
     349,   352,   354,   356,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   370,     4,   374,   376,   378,   380,
       3,     8,     8,   345,     6,     3,   426,     6,     3,   467,
       6,     3,   491,     6,     3,   457,     6,     3,     3,     6,
     564,     3,     6,   527,     6,     3,   402,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   580,   582,     3,     8,     4,   589,     4,   592,
       3,     8,     8,   637,     3,     6,     4,     4,     4,     4,
       3,     8,   220,   252,   253,   510,     6,     3,   542,     8,
       6,     4,     4,   333,     4,     4,     4,     4,   221,   223,
     221,   223,   221,   221,   221,   221,   221,   221,     4,   221,
       4,     4,     4,     4,   347,   346,   344,   429,   425,   470,
     466,   494,   490,   254,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   278,   281,   282,   283,   284,   285,
     286,   289,   291,   293,   294,   295,   298,   299,   301,   303,
     309,   358,   421,   439,   441,   443,   445,   446,   447,   448,
     458,   459,   486,   518,   520,   533,   535,   537,   557,   456,
     384,   131,   132,   133,   254,   264,   265,   266,   309,   358,
     460,   486,   518,   520,   533,   535,   537,   565,   566,   567,
     568,   569,   571,   573,   563,   530,   526,   405,   401,   221,
     221,   221,   221,   221,   221,   414,   223,   221,   221,   393,
       4,     4,   578,   223,     4,   221,     4,   586,   194,   196,
     197,   254,   358,   518,   520,   638,   639,   640,   641,   643,
     636,   223,   223,   223,   223,   660,     6,     3,   513,   509,
       4,   220,   220,    40,    41,    42,   350,   220,   220,   220,
      57,    58,    59,   371,   220,   220,   220,   220,     8,     8,
       8,     8,     3,     8,   570,   572,     4,     8,     3,     8,
       8,   220,   220,   220,   239,   644,     4,   642,     3,     8,
     220,     8,   250,   459,     4,     4,   223,   567,     4,   221,
       4,   639,   220,   220,     5,   220,     7,   645,   646,   647,
       3,     6,   195,   198,   199,   200,   201,   648,   649,   650,
     652,   653,   654,   655,   646,   651,     4,     4,     4,   656,
       3,     8,     4,   223,   221,   221,     4,   649,   220,   220
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   224,   226,   225,   227,   225,   228,   225,   229,   225,
     230,   225,   231,   225,   232,   225,   233,   225,   234,   225,
     235,   225,   236,   225,   237,   225,   238,   225,   239,   239,
     239,   239,   239,   239,   239,   240,   242,   241,   243,   244,
     244,   245,   245,   245,   247,   246,   248,   248,   249,   249,
     249,   251,   250,   252,   252,   253,   253,   253,   254,   256,
     255,   258,   257,   257,   259,   261,   260,   262,   262,   262,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   276,
     275,   277,   279,   278,   280,   281,   282,   283,   284,   285,
     287,   286,   288,   288,   288,   288,   288,   290,   289,   292,
     291,   293,   294,   296,   295,   297,   297,   297,   297,   298,
     300,   299,   302,   301,   303,   304,   305,   306,   307,   308,
     309,   311,   310,   312,   312,   312,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   315,   314,   317,   316,
     319,   318,   320,   320,   322,   321,   323,   323,   324,   325,
     326,   327,   329,   328,   331,   330,   332,   332,   332,   333,
     333,   335,   334,   337,   336,   339,   338,   341,   340,   342,
     342,   343,   343,   343,   345,   344,   346,   346,   346,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   349,   348,   350,   350,   350,   352,   351,   354,   353,
     356,   355,   357,   359,   358,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   370,   369,   371,   371,   371,   372,
     374,   373,   376,   375,   378,   377,   380,   379,   382,   381,
     383,   383,   383,   384,   384,   384,   384,   384,   385,   386,
     387,   388,   389,   391,   390,   392,   392,   392,   393,   393,
     393,   393,   393,   393,   394,   395,   396,   398,   397,   399,
     399,   400,   400,   400,   402,   401,   404,   403,   405,   405,
     405,   405,   406,   406,   408,   407,   410,   409,   412,   411,
     413,   413,   413,   414,   414,   414,   414,   414,   414,   415,
     416,   417,   418,   419,   420,   422,   421,   423,   423,   424,
     424,   424,   426,   425,   428,   427,   429,   429,   429,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   432,   431,
     434,   433,   436,   435,   438,   437,   440,   439,   442,   441,
     444,   443,   445,   446,   447,   449,   448,   450,   450,   450,
     450,   451,   453,   452,   454,   454,   455,   455,   455,   457,
     456,   458,   458,   458,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   459,   459,   461,   460,
     463,   462,   464,   464,   465,   465,   465,   467,   466,   469,
     468,   470,   470,   471,   471,   471,   472,   472,   472,   472,
     472,   472,   472,   472,   472,   472,   473,   474,   475,   477,
     476,   479,   478,   481,   480,   482,   484,   483,   485,   487,
     486,   488,   488,   489,   489,   489,   491,   490,   493,   492,
     494,   494,   495,   495,   495,   496,   496,   496,   496,   496,
     496,   496,   496,   496,   496,   497,   499,   498,   500,   501,
     502,   503,   504,   506,   505,   507,   507,   508,   508,   508,
     510,   509,   512,   511,   513,   513,   513,   514,   514,   514,
     514,   514,   514,   514,   514,   516,   515,   517,   519,   518,
     521,   520,   523,   522,   524,   524,   525,   525,   525,   527,
     526,   529,   528,   530,   530,   531,   531,   531,   532,   532,
     532,   532,   532,   532,   532,   532,   532,   532,   532,   532,
     532,   532,   532,   534,   533,   536,   535,   538,   537,   540,
     539,   542,   541,   544,   543,   546,   545,   548,   547,   550,
     549,   552,   551,   554,   553,   556,   555,   558,   557,   559,
     559,   561,   560,   562,   562,   562,   564,   563,   565,   565,
     566,   566,   566,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   568,
     570,   569,   572,   571,   573,   574,   576,   575,   577,   577,
     577,   578,   578,   578,   578,   578,   580,   579,   582,   581,
     584,   583,   585,   585,   585,   586,   586,   586,   586,   586,
     586,   587,   589,   588,   590,   592,   591,   594,   593,   596,
     595,   597,   597,   597,   598,   598,   598,   598,   598,   598,
     598,   598,   598,   598,   598,   598,   598,   598,   598,   598,
     598,   598,   599,   601,   600,   602,   604,   603,   605,   606,
     608,   607,   609,   609,   611,   610,   613,   612,   614,   615,
     617,   616,   619,   618,   621,   620,   623,   622,   625,   624,
     627,   626,   628,   628,   628,   629,   629,   631,   630,   632,
     634,   633,   635,   635,   635,   637,   636,   638,   638,   638,
     639,   639,   639,   639,   639,   639,   639,   640,   642,   641,
     644,   643,   645,   645,   645,   647,   646,   648,   648,   648,
     649,   649,   649,   649,   649,   651,   650,   652,   653,   654,
     656,   655,   658,   657,   659,   659,   659,   660,   660,   660,
     660,   660,   661,   662,   663,   664
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
       1,     0,     4,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       1,     0,     6,     1,     3,     2,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
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
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"max-row-errors\"", "\"trust-anchor\"",
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
  "on_fail", "$@45", "on_fail_mode", "max_row_errors", "trust_anchor",
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
       0,   319,   319,   319,   320,   320,   321,   321,   322,   322,
     323,   323,   324,   324,   325,   325,   326,   326,   327,   327,
     328,   328,   329,   329,   330,   330,   331,   331,   339,   340,
     341,   342,   343,   344,   345,   348,   353,   353,   364,   367,
     368,   371,   376,   382,   387,   387,   394,   395,   398,   402,
     406,   412,   412,   419,   420,   423,   427,   431,   441,   450,
     450,   465,   465,   479,   482,   488,   488,   497,   498,   499,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   576,   582,
     588,   594,   600,   606,   612,   618,   624,   630,   636,   642,
     642,   651,   657,   657,   666,   672,   678,   684,   690,   696,
     702,   702,   711,   714,   717,   720,   723,   729,   729,   738,
     738,   747,   756,   766,   766,   775,   778,   781,   784,   789,
     795,   795,   804,   804,   813,   819,   825,   831,   837,   843,
     849,   855,   855,   867,   868,   869,   874,   875,   876,   877,
     878,   879,   880,   881,   882,   883,   886,   886,   895,   895,
     906,   906,   914,   915,   918,   918,   926,   928,   932,   938,
     944,   950,   956,   956,   969,   969,   980,   981,   982,   987,
     988,   991,   991,  1010,  1010,  1028,  1028,  1041,  1041,  1052,
    1053,  1056,  1057,  1058,  1063,  1063,  1073,  1074,  1075,  1080,
    1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,
    1091,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,
    1101,  1104,  1104,  1112,  1113,  1114,  1117,  1117,  1126,  1126,
    1135,  1135,  1144,  1150,  1150,  1159,  1165,  1171,  1177,  1183,
    1189,  1195,  1201,  1207,  1213,  1213,  1221,  1222,  1223,  1226,
    1232,  1232,  1241,  1241,  1250,  1250,  1259,  1259,  1268,  1268,
    1279,  1280,  1281,  1286,  1287,  1288,  1289,  1290,  1293,  1298,
    1303,  1308,  1313,  1320,  1320,  1333,  1334,  1335,  1340,  1341,
    1342,  1343,  1344,  1345,  1348,  1354,  1360,  1366,  1366,  1377,
    1378,  1381,  1382,  1383,  1388,  1388,  1398,  1398,  1408,  1409,
    1410,  1413,  1416,  1417,  1420,  1420,  1429,  1429,  1438,  1438,
    1450,  1451,  1452,  1457,  1458,  1459,  1460,  1461,  1462,  1465,
    1471,  1477,  1483,  1489,  1495,  1504,  1504,  1518,  1519,  1522,
    1523,  1524,  1533,  1533,  1559,  1559,  1570,  1571,  1572,  1578,
    1579,  1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,  1588,
    1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,
    1599,  1600,  1601,  1602,  1603,  1604,  1605,  1606,  1607,  1608,
    1609,  1610,  1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,
    1619,  1620,  1621,  1622,  1623,  1624,  1625,  1626,  1629,  1629,
    1638,  1638,  1647,  1647,  1656,  1656,  1665,  1665,  1674,  1674,
    1683,  1683,  1694,  1700,  1706,  1712,  1712,  1720,  1721,  1722,
    1723,  1726,  1734,  1734,  1746,  1747,  1751,  1752,  1753,  1758,
    1758,  1766,  1767,  1768,  1773,  1774,  1775,  1776,  1777,  1778,
    1779,  1780,  1781,  1782,  1783,  1784,  1785,  1786,  1787,  1788,
    1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,  1798,
    1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,  1808,
    1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,  1823,  1823,
    1837,  1837,  1846,  1847,  1850,  1851,  1852,  1859,  1859,  1874,
    1874,  1888,  1889,  1892,  1893,  1894,  1899,  1900,  1901,  1902,
    1903,  1904,  1905,  1906,  1907,  1908,  1911,  1913,  1919,  1921,
    1921,  1930,  1930,  1939,  1939,  1948,  1950,  1950,  1959,  1969,
    1969,  1982,  1983,  1988,  1989,  1990,  1997,  1997,  2009,  2009,
    2021,  2022,  2027,  2028,  2029,  2036,  2037,  2038,  2039,  2040,
    2041,  2042,  2043,  2044,  2045,  2048,  2050,  2050,  2059,  2061,
    2063,  2069,  2075,  2084,  2084,  2097,  2098,  2101,  2102,  2103,
    2108,  2108,  2118,  2118,  2128,  2129,  2130,  2135,  2136,  2137,
    2138,  2139,  2140,  2141,  2142,  2145,  2145,  2154,  2160,  2160,
    2185,  2185,  2215,  2215,  2226,  2227,  2230,  2231,  2232,  2237,
    2237,  2246,  2246,  2255,  2256,  2259,  2260,  2261,  2267,  2268,
    2269,  2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,
    2279,  2280,  2281,  2284,  2284,  2293,  2293,  2302,  2302,  2311,
    2311,  2320,  2320,  2331,  2331,  2340,  2340,  2349,  2349,  2358,
    2358,  2367,  2367,  2376,  2376,  2385,  2385,  2399,  2399,  2410,
    2411,  2417,  2417,  2428,  2429,  2430,  2435,  2435,  2445,  2446,
    2449,  2450,  2451,  2456,  2457,  2458,  2459,  2460,  2461,  2462,
    2463,  2464,  2465,  2466,  2467,  2468,  2469,  2470,  2471,  2474,
    2476,  2476,  2485,  2485,  2494,  2502,  2510,  2510,  2521,  2522,
    2523,  2528,  2529,  2530,  2531,  2532,  2535,  2535,  2544,  2544,
    2556,  2556,  2569,  2570,  2571,  2576,  2577,  2578,  2579,  2580,
    2581,  2584,  2590,  2590,  2599,  2605,  2605,  2615,  2615,  2628,
    2628,  2638,  2639,  2640,  2645,  2646,  2647,  2648,  2649,  2650,
    2651,  2652,  2653,  2654,  2655,  2656,  2657,  2658,  2659,  2660,
    2661,  2662,  2665,  2671,  2671,  2680,  2686,  2686,  2695,  2701,
    2707,  2707,  2716,  2717,  2720,  2720,  2730,  2730,  2740,  2747,
    2754,  2754,  2763,  2763,  2773,  2773,  2783,  2783,  2795,  2795,
    2807,  2807,  2817,  2818,  2819,  2825,  2826,  2829,  2829,  2840,
    2848,  2848,  2861,  2862,  2863,  2869,  2869,  2877,  2878,  2879,
    2884,  2885,  2886,  2887,  2888,  2889,  2890,  2893,  2899,  2899,
    2908,  2908,  2919,  2920,  2921,  2926,  2926,  2934,  2935,  2936,
    2941,  2942,  2943,  2944,  2945,  2948,  2948,  2957,  2963,  2969,
    2975,  2975,  2984,  2984,  2995,  2996,  2997,  3002,  3003,  3004,
    3005,  3006,  3009,  3015,  3021,  3027
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
#line 6446 "dhcp4_parser.cc"

#line 3033 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
