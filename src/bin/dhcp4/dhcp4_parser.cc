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
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 312 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 312 "dhcp4_parser.yy"
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
#line 321 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 322 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 323 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 324 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 325 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 326 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 327 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 328 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 329 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 330 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 331 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 332 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 333 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 341 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 342 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 343 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 344 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 345 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 346 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 347 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 350 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 355 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 360 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 366 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 373 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 378 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 384 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 389 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 392 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 400 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 404 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 408 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 414 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 416 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 425 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 429 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 433 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 443 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 452 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 457 "dhcp4_parser.yy"
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
#line 467 "dhcp4_parser.yy"
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
#line 476 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 484 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 490 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 494 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 501 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 139: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 579 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 140: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 585 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 141: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 591 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 142: // renew_timer: "renew-timer" ":" "integer"
#line 597 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 143: // rebind_timer: "rebind-timer" ":" "integer"
#line 603 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 144: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 609 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 145: // t1_percent: "t1-percent" ":" "floating point"
#line 615 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 146: // t2_percent: "t2-percent" ":" "floating point"
#line 621 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 147: // cache_threshold: "cache-threshold" ":" "floating point"
#line 627 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 148: // cache_max_age: "cache-max-age" ":" "integer"
#line 633 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 149: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 639 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 150: // $@20: %empty
#line 645 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 151: // server_tag: "server-tag" $@20 ":" "constant string"
#line 648 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 152: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 654 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 660 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 154: // allocator: "allocator" $@21 ":" "constant string"
#line 663 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 155: // echo_client_id: "echo-client-id" ":" "boolean"
#line 669 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 156: // match_client_id: "match-client-id" ":" "boolean"
#line 675 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 157: // authoritative: "authoritative" ":" "boolean"
#line 681 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 158: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 687 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 693 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 160: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 699 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 705 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 708 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-present"
#line 714 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "never"
#line 717 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "always"
#line 720 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-not-present"
#line 723 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "boolean"
#line 726 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 168: // $@23: %empty
#line 732 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 169: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 735 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 170: // $@24: %empty
#line 741 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 171: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 744 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 172: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 750 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 173: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 759 "dhcp4_parser.yy"
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
#line 769 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 772 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 778 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 781 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 784 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 787 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 180: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 792 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 798 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 801 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 183: // $@27: %empty
#line 807 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 184: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 810 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 185: // store_extended_info: "store-extended-info" ":" "boolean"
#line 816 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 822 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 187: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 828 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 188: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 834 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 189: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 840 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 846 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 191: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 852 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 192: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 858 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 864 "dhcp4_parser.yy"
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
#line 870 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 197: // interfaces_config_params: interfaces_config_params ","
#line 878 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1684 "dhcp4_parser.cc"
    break;

  case 208: // $@29: %empty
#line 895 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 209: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 899 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1703 "dhcp4_parser.cc"
    break;

  case 210: // $@30: %empty
#line 904 "dhcp4_parser.yy"
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
#line 910 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 212: // $@31: %empty
#line 915 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 213: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 918 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1742 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "raw"
#line 923 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp4_parser.cc"
    break;

  case 215: // socket_type: "udp"
#line 924 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp4_parser.cc"
    break;

  case 216: // $@32: %empty
#line 927 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 930 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "same-as-inbound"
#line 935 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 219: // outbound_interface_value: "use-routing"
#line 937 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1788 "dhcp4_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 941 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 947 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 953 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 959 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 224: // $@33: %empty
#line 965 "dhcp4_parser.yy"
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
#line 971 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 226: // $@34: %empty
#line 978 "dhcp4_parser.yy"
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
#line 984 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 230: // sanity_checks_params: sanity_checks_params ","
#line 991 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1880 "dhcp4_parser.cc"
    break;

  case 233: // $@35: %empty
#line 1000 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp4_parser.cc"
    break;

  case 234: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 1003 "dhcp4_parser.yy"
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
#line 1019 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp4_parser.cc"
    break;

  case 236: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1022 "dhcp4_parser.yy"
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
#line 1037 "dhcp4_parser.yy"
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
#line 1043 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 239: // $@38: %empty
#line 1050 "dhcp4_parser.yy"
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
#line 1056 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 245: // not_empty_database_list: not_empty_database_list ","
#line 1067 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1989 "dhcp4_parser.cc"
    break;

  case 246: // $@39: %empty
#line 1072 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 247: // database: "{" $@39 database_map_params "}"
#line 1076 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2009 "dhcp4_parser.cc"
    break;

  case 250: // database_map_params: database_map_params ","
#line 1084 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2017 "dhcp4_parser.cc"
    break;

  case 274: // $@40: %empty
#line 1114 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 2026 "dhcp4_parser.cc"
    break;

  case 275: // database_type: "type" $@40 ":" db_type
#line 1117 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2035 "dhcp4_parser.cc"
    break;

  case 276: // db_type: "memfile"
#line 1122 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 2041 "dhcp4_parser.cc"
    break;

  case 277: // db_type: "mysql"
#line 1123 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 2047 "dhcp4_parser.cc"
    break;

  case 278: // db_type: "postgresql"
#line 1124 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 2053 "dhcp4_parser.cc"
    break;

  case 279: // $@41: %empty
#line 1127 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp4_parser.cc"
    break;

  case 280: // user: "user" $@41 ":" "constant string"
#line 1130 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2072 "dhcp4_parser.cc"
    break;

  case 281: // $@42: %empty
#line 1136 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc"
    break;

  case 282: // password: "password" $@42 ":" "constant string"
#line 1139 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc"
    break;

  case 283: // $@43: %empty
#line 1145 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 284: // host: "host" $@43 ":" "constant string"
#line 1148 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 285: // port: "port" ":" "integer"
#line 1154 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 286: // $@44: %empty
#line 1160 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 287: // name: "name" $@44 ":" "constant string"
#line 1163 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 288: // persist: "persist" ":" "boolean"
#line 1169 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2149 "dhcp4_parser.cc"
    break;

  case 289: // lfc_interval: "lfc-interval" ":" "integer"
#line 1175 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 290: // readonly: "readonly" ":" "boolean"
#line 1181 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 291: // connect_timeout: "connect-timeout" ":" "integer"
#line 1187 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2179 "dhcp4_parser.cc"
    break;

  case 292: // read_timeout: "read-timeout" ":" "integer"
#line 1193 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 293: // write_timeout: "write-timeout" ":" "integer"
#line 1199 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2199 "dhcp4_parser.cc"
    break;

  case 294: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1205 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 295: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1211 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 296: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1217 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2229 "dhcp4_parser.cc"
    break;

  case 297: // $@45: %empty
#line 1223 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 298: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1226 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2247 "dhcp4_parser.cc"
    break;

  case 299: // on_fail_mode: "stop-retry-exit"
#line 1231 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2253 "dhcp4_parser.cc"
    break;

  case 300: // on_fail_mode: "serve-retry-exit"
#line 1232 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2259 "dhcp4_parser.cc"
    break;

  case 301: // on_fail_mode: "serve-retry-continue"
#line 1233 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2265 "dhcp4_parser.cc"
    break;

  case 302: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1236 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2275 "dhcp4_parser.cc"
    break;

  case 303: // max_row_errors: "max-row-errors" ":" "integer"
#line 1242 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2285 "dhcp4_parser.cc"
    break;

  case 304: // $@46: %empty
#line 1248 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2294 "dhcp4_parser.cc"
    break;

  case 305: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1251 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc"
    break;

  case 306: // $@47: %empty
#line 1257 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 307: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1260 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc"
    break;

  case 308: // $@48: %empty
#line 1266 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 309: // key_file: "key-file" $@48 ":" "constant string"
#line 1269 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2342 "dhcp4_parser.cc"
    break;

  case 310: // $@49: %empty
#line 1275 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 311: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1278 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1284 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2373 "dhcp4_parser.cc"
    break;

  case 313: // host_reservation_identifiers: "host-reservation-identifiers" $@50 ":" "[" host_reservation_identifiers_list "]"
#line 1290 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2382 "dhcp4_parser.cc"
    break;

  case 316: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1297 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2390 "dhcp4_parser.cc"
    break;

  case 322: // duid_id: "duid"
#line 1309 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2399 "dhcp4_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1314 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 324: // circuit_id: "circuit-id"
#line 1319 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 325: // client_id: "client-id"
#line 1324 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2426 "dhcp4_parser.cc"
    break;

  case 326: // flex_id: "flex-id"
#line 1329 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 327: // $@51: %empty
#line 1336 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2447 "dhcp4_parser.cc"
    break;

  case 328: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1342 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2458 "dhcp4_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1351 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2466 "dhcp4_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1364 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2476 "dhcp4_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1370 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2486 "dhcp4_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1376 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2496 "dhcp4_parser.cc"
    break;

  case 341: // $@52: %empty
#line 1382 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2508 "dhcp4_parser.cc"
    break;

  case 342: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1388 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2517 "dhcp4_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1399 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2525 "dhcp4_parser.cc"
    break;

  case 348: // $@53: %empty
#line 1404 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 349: // hooks_library: "{" $@53 hooks_params "}"
#line 1408 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 350: // $@54: %empty
#line 1414 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1418 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1426 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2573 "dhcp4_parser.cc"
    break;

  case 358: // $@55: %empty
#line 1436 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc"
    break;

  case 359: // library: "library" $@55 ":" "constant string"
#line 1439 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc"
    break;

  case 360: // $@56: %empty
#line 1445 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2601 "dhcp4_parser.cc"
    break;

  case 361: // parameters: "parameters" $@56 ":" map_value
#line 1448 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1454 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2622 "dhcp4_parser.cc"
    break;

  case 363: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1460 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2632 "dhcp4_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1468 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2640 "dhcp4_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1481 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2650 "dhcp4_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1487 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1493 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1499 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1505 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2690 "dhcp4_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1511 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2700 "dhcp4_parser.cc"
    break;

  case 379: // $@58: %empty
#line 1520 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 380: // subnet4_list: "subnet4" $@58 ":" "[" subnet4_list_content "]"
#line 1526 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 385: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1540 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2729 "dhcp4_parser.cc"
    break;

  case 386: // $@59: %empty
#line 1549 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2739 "dhcp4_parser.cc"
    break;

  case 387: // subnet4: "{" $@59 subnet4_params "}"
#line 1553 "dhcp4_parser.yy"
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
#line 2765 "dhcp4_parser.cc"
    break;

  case 388: // $@60: %empty
#line 1575 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2775 "dhcp4_parser.cc"
    break;

  case 389: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1579 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 392: // subnet4_params: subnet4_params ","
#line 1588 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2793 "dhcp4_parser.cc"
    break;

  case 442: // $@61: %empty
#line 1645 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 443: // subnet: "subnet" $@61 ":" "constant string"
#line 1648 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 444: // $@62: %empty
#line 1654 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1657 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 446: // $@63: %empty
#line 1663 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 447: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1666 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2850 "dhcp4_parser.cc"
    break;

  case 448: // $@64: %empty
#line 1672 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 449: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1675 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 450: // $@65: %empty
#line 1681 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2878 "dhcp4_parser.cc"
    break;

  case 451: // interface: "interface" $@65 ":" "constant string"
#line 1684 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2888 "dhcp4_parser.cc"
    break;

  case 452: // $@66: %empty
#line 1690 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2897 "dhcp4_parser.cc"
    break;

  case 453: // client_class: "client-class" $@66 ":" "constant string"
#line 1693 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2907 "dhcp4_parser.cc"
    break;

  case 454: // $@67: %empty
#line 1699 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp4_parser.cc"
    break;

  case 455: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1705 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc"
    break;

  case 456: // reservations_global: "reservations-global" ":" "boolean"
#line 1710 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 457: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1716 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2948 "dhcp4_parser.cc"
    break;

  case 458: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1722 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2958 "dhcp4_parser.cc"
    break;

  case 459: // $@68: %empty
#line 1728 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 460: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1731 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 461: // hr_mode: "disabled"
#line 1736 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2982 "dhcp4_parser.cc"
    break;

  case 462: // hr_mode: "out-of-pool"
#line 1737 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2988 "dhcp4_parser.cc"
    break;

  case 463: // hr_mode: "global"
#line 1738 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2994 "dhcp4_parser.cc"
    break;

  case 464: // hr_mode: "all"
#line 1739 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 3000 "dhcp4_parser.cc"
    break;

  case 465: // id: "id" ":" "integer"
#line 1742 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3010 "dhcp4_parser.cc"
    break;

  case 466: // $@69: %empty
#line 1750 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3022 "dhcp4_parser.cc"
    break;

  case 467: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1756 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3031 "dhcp4_parser.cc"
    break;

  case 472: // shared_networks_list: shared_networks_list ","
#line 1769 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3039 "dhcp4_parser.cc"
    break;

  case 473: // $@70: %empty
#line 1774 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3049 "dhcp4_parser.cc"
    break;

  case 474: // shared_network: "{" $@70 shared_network_params "}"
#line 1778 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 477: // shared_network_params: shared_network_params ","
#line 1784 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3065 "dhcp4_parser.cc"
    break;

  case 522: // $@71: %empty
#line 1839 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3077 "dhcp4_parser.cc"
    break;

  case 523: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1845 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp4_parser.cc"
    break;

  case 524: // $@72: %empty
#line 1853 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3095 "dhcp4_parser.cc"
    break;

  case 525: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1856 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3103 "dhcp4_parser.cc"
    break;

  case 530: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1868 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3111 "dhcp4_parser.cc"
    break;

  case 531: // $@73: %empty
#line 1875 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 532: // option_def_entry: "{" $@73 option_def_params "}"
#line 1879 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3133 "dhcp4_parser.cc"
    break;

  case 533: // $@74: %empty
#line 1890 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3143 "dhcp4_parser.cc"
    break;

  case 534: // sub_option_def: "{" $@74 option_def_params "}"
#line 1894 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3155 "dhcp4_parser.cc"
    break;

  case 539: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1910 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3163 "dhcp4_parser.cc"
    break;

  case 551: // code: "code" ":" "integer"
#line 1929 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 553: // $@75: %empty
#line 1937 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 554: // option_def_type: "type" $@75 ":" "constant string"
#line 1940 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3192 "dhcp4_parser.cc"
    break;

  case 555: // $@76: %empty
#line 1946 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp4_parser.cc"
    break;

  case 556: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1949 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 557: // $@77: %empty
#line 1955 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3220 "dhcp4_parser.cc"
    break;

  case 558: // space: "space" $@77 ":" "constant string"
#line 1958 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3230 "dhcp4_parser.cc"
    break;

  case 560: // $@78: %empty
#line 1966 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp4_parser.cc"
    break;

  case 561: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1969 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 562: // option_def_array: "array" ":" "boolean"
#line 1975 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3259 "dhcp4_parser.cc"
    break;

  case 563: // $@79: %empty
#line 1985 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3271 "dhcp4_parser.cc"
    break;

  case 564: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1991 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3280 "dhcp4_parser.cc"
    break;

  case 569: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2006 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3288 "dhcp4_parser.cc"
    break;

  case 570: // $@80: %empty
#line 2013 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3298 "dhcp4_parser.cc"
    break;

  case 571: // option_data_entry: "{" $@80 option_data_params "}"
#line 2017 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 572: // $@81: %empty
#line 2025 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3317 "dhcp4_parser.cc"
    break;

  case 573: // sub_option_data: "{" $@81 option_data_params "}"
#line 2029 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3326 "dhcp4_parser.cc"
    break;

  case 578: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2045 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3334 "dhcp4_parser.cc"
    break;

  case 590: // $@82: %empty
#line 2066 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3343 "dhcp4_parser.cc"
    break;

  case 591: // option_data_data: "data" $@82 ":" "constant string"
#line 2069 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 594: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2079 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 595: // option_data_always_send: "always-send" ":" "boolean"
#line 2085 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 596: // option_data_never_send: "never-send" ":" "boolean"
#line 2091 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3383 "dhcp4_parser.cc"
    break;

  case 597: // $@83: %empty
#line 2100 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3395 "dhcp4_parser.cc"
    break;

  case 598: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2106 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3404 "dhcp4_parser.cc"
    break;

  case 603: // not_empty_pools_list: not_empty_pools_list ","
#line 2119 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3412 "dhcp4_parser.cc"
    break;

  case 604: // $@84: %empty
#line 2124 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 605: // pool_list_entry: "{" $@84 pool_params "}"
#line 2128 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 606: // $@85: %empty
#line 2134 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3442 "dhcp4_parser.cc"
    break;

  case 607: // sub_pool4: "{" $@85 pool_params "}"
#line 2138 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 610: // pool_params: pool_params ","
#line 2146 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3460 "dhcp4_parser.cc"
    break;

  case 619: // $@86: %empty
#line 2161 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3469 "dhcp4_parser.cc"
    break;

  case 620: // pool_entry: "pool" $@86 ":" "constant string"
#line 2164 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 621: // pool_id: "pool-id" ":" "integer"
#line 2170 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3489 "dhcp4_parser.cc"
    break;

  case 622: // $@87: %empty
#line 2176 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3497 "dhcp4_parser.cc"
    break;

  case 623: // user_context: "user-context" $@87 ":" map_value
#line 2178 "dhcp4_parser.yy"
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
#line 3524 "dhcp4_parser.cc"
    break;

  case 624: // $@88: %empty
#line 2201 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3532 "dhcp4_parser.cc"
    break;

  case 625: // comment: "comment" $@88 ":" "constant string"
#line 2203 "dhcp4_parser.yy"
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
#line 3561 "dhcp4_parser.cc"
    break;

  case 626: // $@89: %empty
#line 2231 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 627: // reservations: "reservations" $@89 ":" "[" reservations_list "]"
#line 2237 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 632: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2248 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3590 "dhcp4_parser.cc"
    break;

  case 633: // $@90: %empty
#line 2253 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3600 "dhcp4_parser.cc"
    break;

  case 634: // reservation: "{" $@90 reservation_params "}"
#line 2257 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3609 "dhcp4_parser.cc"
    break;

  case 635: // $@91: %empty
#line 2262 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3619 "dhcp4_parser.cc"
    break;

  case 636: // sub_reservation: "{" $@91 reservation_params "}"
#line 2266 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3628 "dhcp4_parser.cc"
    break;

  case 641: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2277 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3636 "dhcp4_parser.cc"
    break;

  case 657: // $@92: %empty
#line 2300 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 658: // next_server: "next-server" $@92 ":" "constant string"
#line 2303 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 659: // $@93: %empty
#line 2309 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 660: // server_hostname: "server-hostname" $@93 ":" "constant string"
#line 2312 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 661: // $@94: %empty
#line 2318 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 662: // boot_file_name: "boot-file-name" $@94 ":" "constant string"
#line 2321 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 663: // $@95: %empty
#line 2327 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 664: // ip_address: "ip-address" $@95 ":" "constant string"
#line 2330 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 665: // $@96: %empty
#line 2336 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 666: // ip_addresses: "ip-addresses" $@96 ":" list_strings
#line 2342 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 667: // $@97: %empty
#line 2347 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 668: // duid: "duid" $@97 ":" "constant string"
#line 2350 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3752 "dhcp4_parser.cc"
    break;

  case 669: // $@98: %empty
#line 2356 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 670: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2359 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 671: // $@99: %empty
#line 2365 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 672: // client_id_value: "client-id" $@99 ":" "constant string"
#line 2368 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 673: // $@100: %empty
#line 2374 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 674: // circuit_id_value: "circuit-id" $@100 ":" "constant string"
#line 2377 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 675: // $@101: %empty
#line 2383 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 676: // flex_id_value: "flex-id" $@101 ":" "constant string"
#line 2386 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 677: // $@102: %empty
#line 2392 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 678: // hostname: "hostname" $@102 ":" "constant string"
#line 2395 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3847 "dhcp4_parser.cc"
    break;

  case 679: // $@103: %empty
#line 2401 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3859 "dhcp4_parser.cc"
    break;

  case 680: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2407 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 681: // $@104: %empty
#line 2415 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3880 "dhcp4_parser.cc"
    break;

  case 682: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2421 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3889 "dhcp4_parser.cc"
    break;

  case 685: // $@105: %empty
#line 2433 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 686: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2439 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 689: // client_classes_list: client_classes_list ","
#line 2446 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3918 "dhcp4_parser.cc"
    break;

  case 690: // $@106: %empty
#line 2451 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 691: // client_class_entry: "{" $@106 client_class_params "}"
#line 2455 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 696: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2467 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3946 "dhcp4_parser.cc"
    break;

  case 714: // $@107: %empty
#line 2492 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3955 "dhcp4_parser.cc"
    break;

  case 715: // client_class_test: "test" $@107 ":" "constant string"
#line 2495 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3965 "dhcp4_parser.cc"
    break;

  case 716: // $@108: %empty
#line 2501 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3974 "dhcp4_parser.cc"
    break;

  case 717: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2504 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 718: // only_if_required: "only-if-required" ":" "boolean"
#line 2510 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 719: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2518 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4004 "dhcp4_parser.cc"
    break;

  case 720: // $@109: %empty
#line 2526 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4016 "dhcp4_parser.cc"
    break;

  case 721: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2532 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4025 "dhcp4_parser.cc"
    break;

  case 724: // control_socket_params: control_socket_params ","
#line 2539 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4033 "dhcp4_parser.cc"
    break;

  case 730: // $@110: %empty
#line 2551 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 731: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2554 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4052 "dhcp4_parser.cc"
    break;

  case 732: // $@111: %empty
#line 2560 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4061 "dhcp4_parser.cc"
    break;

  case 733: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2563 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4071 "dhcp4_parser.cc"
    break;

  case 734: // $@112: %empty
#line 2572 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4083 "dhcp4_parser.cc"
    break;

  case 735: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2578 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4094 "dhcp4_parser.cc"
    break;

  case 738: // queue_control_params: queue_control_params ","
#line 2587 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4102 "dhcp4_parser.cc"
    break;

  case 745: // enable_queue: "enable-queue" ":" "boolean"
#line 2600 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4112 "dhcp4_parser.cc"
    break;

  case 746: // $@113: %empty
#line 2606 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 747: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2609 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 748: // capacity: "capacity" ":" "integer"
#line 2615 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 749: // $@114: %empty
#line 2621 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4150 "dhcp4_parser.cc"
    break;

  case 750: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2624 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4159 "dhcp4_parser.cc"
    break;

  case 751: // $@115: %empty
#line 2631 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 752: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2637 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 753: // $@116: %empty
#line 2644 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 754: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2648 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 757: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2656 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4210 "dhcp4_parser.cc"
    break;

  case 776: // enable_updates: "enable-updates" ":" "boolean"
#line 2681 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4220 "dhcp4_parser.cc"
    break;

  case 777: // $@117: %empty
#line 2687 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4229 "dhcp4_parser.cc"
    break;

  case 778: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2690 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4239 "dhcp4_parser.cc"
    break;

  case 779: // server_port: "server-port" ":" "integer"
#line 2696 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4249 "dhcp4_parser.cc"
    break;

  case 780: // $@118: %empty
#line 2702 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 781: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2705 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4268 "dhcp4_parser.cc"
    break;

  case 782: // sender_port: "sender-port" ":" "integer"
#line 2711 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4278 "dhcp4_parser.cc"
    break;

  case 783: // max_queue_size: "max-queue-size" ":" "integer"
#line 2717 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4288 "dhcp4_parser.cc"
    break;

  case 784: // $@119: %empty
#line 2723 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4297 "dhcp4_parser.cc"
    break;

  case 785: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2726 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4306 "dhcp4_parser.cc"
    break;

  case 786: // ncr_protocol_value: "udp"
#line 2732 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4312 "dhcp4_parser.cc"
    break;

  case 787: // ncr_protocol_value: "tcp"
#line 2733 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4318 "dhcp4_parser.cc"
    break;

  case 788: // $@120: %empty
#line 2736 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4327 "dhcp4_parser.cc"
    break;

  case 789: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2739 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4337 "dhcp4_parser.cc"
    break;

  case 790: // $@121: %empty
#line 2746 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4346 "dhcp4_parser.cc"
    break;

  case 791: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2749 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4356 "dhcp4_parser.cc"
    break;

  case 792: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2756 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4366 "dhcp4_parser.cc"
    break;

  case 793: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2763 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4376 "dhcp4_parser.cc"
    break;

  case 794: // $@122: %empty
#line 2770 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4385 "dhcp4_parser.cc"
    break;

  case 795: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2773 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4394 "dhcp4_parser.cc"
    break;

  case 796: // $@123: %empty
#line 2779 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4403 "dhcp4_parser.cc"
    break;

  case 797: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2782 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4413 "dhcp4_parser.cc"
    break;

  case 798: // $@124: %empty
#line 2789 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 799: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2792 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4432 "dhcp4_parser.cc"
    break;

  case 800: // $@125: %empty
#line 2799 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4441 "dhcp4_parser.cc"
    break;

  case 801: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2802 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4451 "dhcp4_parser.cc"
    break;

  case 802: // $@126: %empty
#line 2811 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 803: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2817 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4473 "dhcp4_parser.cc"
    break;

  case 804: // $@127: %empty
#line 2823 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 805: // sub_config_control: "{" $@127 config_control_params "}"
#line 2827 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4492 "dhcp4_parser.cc"
    break;

  case 808: // config_control_params: config_control_params ","
#line 2835 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4500 "dhcp4_parser.cc"
    break;

  case 811: // $@128: %empty
#line 2845 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4512 "dhcp4_parser.cc"
    break;

  case 812: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2851 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4521 "dhcp4_parser.cc"
    break;

  case 813: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2856 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4531 "dhcp4_parser.cc"
    break;

  case 814: // $@129: %empty
#line 2864 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4543 "dhcp4_parser.cc"
    break;

  case 815: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2870 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 818: // loggers_entries: loggers_entries ","
#line 2879 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4560 "dhcp4_parser.cc"
    break;

  case 819: // $@130: %empty
#line 2885 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4570 "dhcp4_parser.cc"
    break;

  case 820: // logger_entry: "{" $@130 logger_params "}"
#line 2889 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4578 "dhcp4_parser.cc"
    break;

  case 823: // logger_params: logger_params ","
#line 2895 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4586 "dhcp4_parser.cc"
    break;

  case 831: // debuglevel: "debuglevel" ":" "integer"
#line 2909 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4596 "dhcp4_parser.cc"
    break;

  case 832: // $@131: %empty
#line 2915 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4605 "dhcp4_parser.cc"
    break;

  case 833: // severity: "severity" $@131 ":" "constant string"
#line 2918 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4615 "dhcp4_parser.cc"
    break;

  case 834: // $@132: %empty
#line 2924 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4627 "dhcp4_parser.cc"
    break;

  case 835: // output_options_list: "output-options" $@132 ":" "[" output_options_list_content "]"
#line 2930 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4636 "dhcp4_parser.cc"
    break;

  case 838: // output_options_list_content: output_options_list_content ","
#line 2937 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4644 "dhcp4_parser.cc"
    break;

  case 839: // $@133: %empty
#line 2942 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4654 "dhcp4_parser.cc"
    break;

  case 840: // output_entry: "{" $@133 output_params_list "}"
#line 2946 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4662 "dhcp4_parser.cc"
    break;

  case 843: // output_params_list: output_params_list ","
#line 2952 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4670 "dhcp4_parser.cc"
    break;

  case 849: // $@134: %empty
#line 2964 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4679 "dhcp4_parser.cc"
    break;

  case 850: // output: "output" $@134 ":" "constant string"
#line 2967 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4689 "dhcp4_parser.cc"
    break;

  case 851: // flush: "flush" ":" "boolean"
#line 2973 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4699 "dhcp4_parser.cc"
    break;

  case 852: // maxsize: "maxsize" ":" "integer"
#line 2979 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4709 "dhcp4_parser.cc"
    break;

  case 853: // maxver: "maxver" ":" "integer"
#line 2985 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4719 "dhcp4_parser.cc"
    break;

  case 854: // $@135: %empty
#line 2991 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4728 "dhcp4_parser.cc"
    break;

  case 855: // pattern: "pattern" $@135 ":" "constant string"
#line 2994 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4738 "dhcp4_parser.cc"
    break;

  case 856: // $@136: %empty
#line 3000 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4750 "dhcp4_parser.cc"
    break;

  case 857: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 3006 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4759 "dhcp4_parser.cc"
    break;

  case 860: // compatibility_params: compatibility_params ","
#line 3013 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4767 "dhcp4_parser.cc"
    break;

  case 866: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3025 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4777 "dhcp4_parser.cc"
    break;

  case 867: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 3031 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4787 "dhcp4_parser.cc"
    break;

  case 868: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 3037 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4797 "dhcp4_parser.cc"
    break;

  case 869: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 3043 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4807 "dhcp4_parser.cc"
    break;


#line 4811 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1029;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     620, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,    31,    28,    27,    60,    64,    82,
     101,   127,   137,   139,   178,   256,   259,   266, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,    28,  -186,   287,   140,   165,   333,
     -40,   242,   -16,   552,   222,  -109,   637,    32, -1029,    49,
      88,    77,   306,   284, -1029,    54, -1029, -1029, -1029, -1029,
     311,   313,   314, -1029, -1029, -1029,   322,   332, -1029, -1029,
   -1029,   337,   350,   354,   357,   370,   371,   372,   406,   407,
     408,   409, -1029,   420,   424,   426,   427,   428, -1029, -1029,
   -1029,   429,   430,   431,   432, -1029, -1029, -1029,   433, -1029,
   -1029, -1029, -1029, -1029, -1029,   434,   435,   436, -1029, -1029,
   -1029, -1029, -1029,   439, -1029, -1029, -1029, -1029, -1029, -1029,
     441,   442,   445, -1029, -1029,   453, -1029,    62, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
     454,   455,   459,   462, -1029,    65, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,   463, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,    72, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   466, -1029,
   -1029, -1029, -1029,    91, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029,   465,   472, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,   468, -1029, -1029,   473, -1029,
   -1029, -1029,   476, -1029, -1029,   477,   481, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
     483,   484,   485, -1029, -1029, -1029, -1029,   486,   488, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,    98, -1029, -1029, -1029,   491, -1029, -1029,   492,
   -1029,   493,   496, -1029, -1029,   498,   500, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,   115, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,   502,   125, -1029, -1029, -1029, -1029,    28,    28,
   -1029,   270,   503, -1029, -1029,   506,   510,   514,   295,   303,
     307,   522,   526,   527,   310,   309,   532,   535,   537,   319,
     320,   321,   323,   324,   327,   330,   335,   336,   339,   342,
     541,   343,   346,   347,   348,   349,   553,   554,   563,   352,
     353,   351,   356,   566,   567,   578,   366,   590,   591,   592,
     593,   595,   596,   377,   382,   385,   608,   609,   610,   611,
     618,   400,   634,   635,   636,   643,   644,   646,   437,   438,
     443,   649,   650, -1029,   140, -1029,   651,   655,   656,   446,
     448,   451,   452,   165, -1029,   657,   660,   672,   674,   675,
     676,   458,   678,   679,   680,   333, -1029,   682,   464,   -40,
   -1029,   684,   685,   686,   687,   694,   695,   696,   697, -1029,
     242, -1029,   698,   699,   482,   700,   702,   705,   487, -1029,
     552,   707,   490,   494,   495, -1029,   222,   709,   712,   -34,
   -1029,   497,   713,   714,   516,   717,   517,   518,   719,   738,
     531,   536,   753,   756,   758,   759,   637, -1029,   764,   546,
      32, -1029, -1029, -1029,   768,   659,   766,   769,   770, -1029,
   -1029, -1029,   556,   559,   561, -1029, -1029,   778,   779,   782,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029,   570, -1029, -1029, -1029, -1029, -1029,  -137,   571,   573,
   -1029, -1029, -1029, -1029,   783,   791,   792, -1029,   577,   279,
     795,   794,   581,   273, -1029, -1029, -1029,   799,   800,   801,
     816,   815, -1029,   817,   818,   819,   835,   601,   621, -1029,
   -1029, -1029,   839,   838, -1029,   841,   143,   213, -1029, -1029,
   -1029, -1029, -1029,   625,   626,   627,   845,   629,   632, -1029,
     841,   633,   849, -1029,   638, -1029, -1029,   841,   639,   640,
     641,   642,   645,   647,   648, -1029,   652,   653, -1029,   654,
     658,   661, -1029, -1029,   663, -1029, -1029, -1029, -1029,   664,
     794, -1029, -1029,   665,   666, -1029,   667, -1029, -1029,     8,
     673, -1029, -1029,  -137,   668,   669,   670, -1029,   852, -1029,
   -1029,    28,   140,    32,   165,   262, -1029, -1029, -1029,   580,
     580,   858, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029,   859,   861,   864, -1029, -1029, -1029, -1029, -1029, -1029,
     865, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,    99,
     866,   870,   871,    41,   -31,    39,   -64,   637, -1029, -1029,
     872,   -96, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029,   874, -1029, -1029, -1029, -1029,    21, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029,   858, -1029,   133,
     144,   197, -1029, -1029,   198, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,   771,   878,   889,   890,   891,   892,   893,   894,
     895,   896, -1029,   897,   898, -1029, -1029, -1029, -1029, -1029,
     229, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,   252, -1029,   899,   900, -1029, -1029,
     901,   903, -1029, -1029,   902,   906, -1029, -1029,   904,   908,
   -1029, -1029,   907,   909, -1029, -1029, -1029, -1029, -1029, -1029,
      87, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   180, -1029,
   -1029,   910,   911, -1029, -1029,   912,   914, -1029,   915,   916,
     917,   918,   919,   920,   269, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,   921,   922,   923, -1029,   276, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   277, -1029,
   -1029, -1029,   924, -1029,   925, -1029, -1029, -1029,   278, -1029,
   -1029, -1029, -1029, -1029,   293, -1029,   196, -1029,   926,   927,
     928,   929, -1029,   297, -1029, -1029, -1029, -1029, -1029,   693,
   -1029,   930,   931, -1029, -1029, -1029, -1029,   932,   933, -1029,
   -1029, -1029,   934,   937,   262, -1029,   938,   939,   940,   941,
     681,   710,   723,   722,   725,   726,   727,   728,   729,   730,
     950,   731,   732,   953,   954,   955,   956,   580, -1029, -1029,
     580, -1029,   858,   333, -1029,   859,   552, -1029,   861,   222,
   -1029,   864,   662, -1029,   865,    99, -1029,   260,   866, -1029,
     242, -1029,   870,  -109, -1029,   871,   739,   740,   741,   742,
     744,   745,    41, -1029,   736,   747,   748,   -31, -1029,   969,
     970,    39, -1029,   757,   974,   776,   977,   -64, -1029, -1029,
     147,   872, -1029,   767,   784,   786,   789,   -96, -1029, -1029,
     983,  1005,   -40, -1029,   874,  1026, -1029, -1029,   715,   812,
   -1029,   329,   822,   826,   829, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,   291, -1029, -1029,   830,   832,
     842,   843, -1029,   301, -1029,   304, -1029,  1030, -1029,  1031,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   305, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029,  1037, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,  1064,  1071, -1029, -1029, -1029,
   -1029, -1029, -1029,  1069, -1029,   308, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   905,   913,
   -1029, -1029,   935, -1029,    28, -1029, -1029,  1118, -1029, -1029,
   -1029, -1029, -1029,   334, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,   936,   344, -1029,   841, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
     662, -1029,  1120,  1121,   942, -1029,   260, -1029, -1029, -1029,
   -1029, -1029, -1029,  1125,   943,  1126,   147, -1029, -1029, -1029,
   -1029, -1029,   946,   947, -1029, -1029,  1127, -1029,   951, -1029,
   -1029, -1029,  1124, -1029, -1029,   253, -1029,   -38,  1124, -1029,
   -1029,  1129,  1130,  1132, -1029,   345, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029,  1133,   949,   952,   957,  1134,   -38, -1029,
     959, -1029, -1029, -1029,   960, -1029, -1029, -1029
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   208,     9,   388,    11,   606,    13,
     635,    15,   524,    17,   533,    19,   572,    21,   350,    23,
     753,    25,   804,    27,    46,    39,     0,     0,     0,     0,
       0,   637,     0,   535,   574,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   802,   193,   226,
       0,     0,     0,   657,   659,   661,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   379,   522,   563,     0,   153,
     174,   466,   622,   624,   459,     0,     0,     0,   312,   685,
     626,   341,   362,     0,   327,   720,   734,   751,   181,   183,
       0,     0,     0,   814,   856,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     103,   134,   135,    92,    93,    94,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   100,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   444,   446,   448,   597,
     442,   450,     0,   454,   452,   681,   441,   393,   394,   395,
     396,   397,   421,   422,   423,   424,   425,   439,   411,   412,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   440,     0,   390,   400,   416,   417,   418,
     401,   403,   404,   407,   408,   409,   406,   402,   398,   399,
     419,   420,   405,   413,   414,   415,   410,   619,     0,   618,
     614,   615,   613,     0,   608,   611,   612,   616,   617,   679,
     667,   669,   673,   671,   677,   675,   663,   656,   650,   654,
     655,     0,   638,   639,   651,   652,   653,   647,   642,   648,
     644,   645,   646,   649,   643,     0,   553,   286,     0,   557,
     555,   560,     0,   549,   550,     0,   536,   537,   540,   552,
     541,   542,   543,   559,   544,   545,   546,   547,   548,   590,
       0,     0,     0,   588,   589,   592,   593,     0,   575,   576,
     579,   580,   581,   582,   583,   584,   585,   586,   587,   358,
     360,   355,     0,   352,   356,   357,     0,   790,   777,     0,
     780,     0,     0,   784,   788,     0,     0,   794,   796,   798,
     800,   775,   773,   774,     0,   755,   758,   759,   760,   761,
     762,   763,   764,   765,   770,   766,   767,   768,   769,   771,
     772,   811,     0,     0,   806,   809,   810,    45,    50,     0,
      37,    43,     0,    64,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    69,    66,     0,     0,     0,     0,
       0,     0,     0,   197,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   392,   389,     0,     0,   610,
     607,     0,     0,     0,     0,     0,     0,     0,     0,   636,
     641,   525,     0,     0,     0,     0,     0,     0,     0,   534,
     539,     0,     0,     0,     0,   573,   578,     0,     0,   354,
     351,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   757,   754,     0,     0,
     808,   805,    49,    41,     0,     0,     0,     0,     0,   155,
     156,   157,     0,     0,     0,   191,   192,     0,     0,     0,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,     0,   186,   187,   158,   159,   160,     0,     0,     0,
     172,   173,   180,   185,     0,     0,     0,   152,     0,     0,
       0,     0,     0,     0,   456,   457,   458,     0,     0,     0,
       0,     0,   719,     0,     0,     0,     0,     0,     0,   188,
     189,   190,     0,     0,    68,     0,     0,     0,   220,   221,
     222,   223,   196,     0,     0,     0,     0,     0,     0,   465,
       0,     0,     0,   391,     0,   621,   609,     0,     0,     0,
       0,     0,     0,     0,     0,   640,     0,     0,   551,     0,
       0,     0,   562,   538,     0,   594,   595,   596,   577,     0,
       0,   353,   776,     0,     0,   779,     0,   782,   783,     0,
       0,   792,   793,     0,     0,     0,     0,   756,     0,   813,
     807,     0,     0,     0,     0,     0,   658,   660,   662,     0,
       0,   241,   151,   163,   164,   165,   166,   167,   162,   169,
     171,   381,   526,   565,   154,   176,   177,   178,   179,   175,
     468,    38,   623,   625,   461,   462,   463,   464,   460,     0,
       0,   628,   343,     0,     0,     0,     0,     0,   182,   184,
       0,     0,    51,   211,   214,   215,   213,   218,   219,   217,
     445,   447,   449,   599,   443,   451,   455,   453,     0,   620,
     680,   668,   670,   674,   672,   678,   676,   664,   554,   287,
     558,   556,   561,   591,   359,   361,   791,   778,   781,   786,
     787,   785,   789,   795,   797,   799,   801,   241,    42,     0,
       0,     0,   233,   235,     0,   228,   231,   232,   274,   279,
     281,   283,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   297,     0,     0,   304,   306,   308,   310,   273,
       0,   248,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,     0,   246,     0,   242,   243,   386,
       0,   382,   383,   531,     0,   527,   528,   570,     0,   566,
     567,   473,     0,   469,   470,   322,   323,   324,   325,   326,
       0,   314,   317,   318,   319,   320,   321,   690,     0,   687,
     633,     0,   629,   630,   348,     0,   344,   345,     0,     0,
       0,     0,     0,     0,     0,   364,   367,   368,   369,   370,
     371,   372,     0,     0,     0,   337,     0,   329,   332,   333,
     334,   335,   336,   730,   732,   729,   727,   728,     0,   722,
     725,   726,     0,   746,     0,   749,   742,   743,     0,   736,
     739,   740,   741,   744,     0,   819,     0,   816,     0,     0,
       0,     0,   865,     0,   858,   861,   862,   863,   864,    53,
     604,     0,   600,   601,   665,   683,   684,     0,     0,    62,
     803,   194,     0,     0,   230,   227,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   250,   225,   238,
       0,   240,   245,     0,   380,   385,   535,   523,   530,   574,
     564,   569,     0,   467,   472,   316,   313,   692,   689,   686,
     637,   627,   632,     0,   342,   347,     0,     0,     0,     0,
       0,     0,   366,   363,     0,     0,     0,   331,   328,     0,
       0,   724,   721,     0,     0,     0,     0,   738,   735,   752,
       0,   818,   815,     0,     0,     0,     0,   860,   857,    55,
       0,    54,     0,   598,   603,     0,   682,   812,     0,     0,
     229,     0,     0,     0,     0,   285,   288,   289,   290,   291,
     292,   293,   294,   295,   296,     0,   302,   303,     0,     0,
       0,     0,   249,     0,   244,     0,   384,     0,   529,     0,
     568,   521,   496,   497,   498,   481,   482,   501,   502,   503,
     504,   505,   519,   484,   485,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   520,   478,
     479,   480,   494,   495,   491,   492,   493,   490,     0,   475,
     483,   499,   500,   486,   487,   488,   489,   471,   315,   714,
     716,     0,   708,   709,   710,   711,   712,   713,   701,   702,
     706,   707,   703,   704,   705,     0,   693,   694,   697,   698,
     699,   700,   688,     0,   631,     0,   346,   373,   374,   375,
     376,   377,   378,   365,   338,   339,   340,   330,     0,     0,
     723,   745,     0,   748,     0,   737,   834,     0,   832,   830,
     824,   828,   829,     0,   821,   826,   827,   825,   817,   866,
     867,   868,   869,   859,    52,    57,     0,   602,     0,   234,
     236,   276,   277,   278,   275,   280,   282,   284,   299,   300,
     301,   298,   305,   307,   309,   311,   247,   387,   532,   571,
     477,   474,     0,     0,     0,   691,   696,   634,   349,   731,
     733,   747,   750,     0,     0,     0,   823,   820,    56,   605,
     666,   476,     0,     0,   718,   695,     0,   831,     0,   822,
     715,   717,     0,   833,   839,     0,   836,     0,   838,   835,
     849,     0,     0,     0,   854,     0,   841,   844,   845,   846,
     847,   848,   837,     0,     0,     0,     0,     0,   843,   840,
       0,   851,   852,   853,     0,   842,   850,   855
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,   -59, -1029,  -603, -1029,   440,
   -1029, -1029, -1029, -1029, -1029, -1029,  -664, -1029, -1029, -1029,
     -67, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   410,   630,
     -30,   -26,    26,   -54,   -37,   -27,     0,    14,    16,    45,
   -1029, -1029, -1029, -1029,    48, -1029, -1029,    50,    51,    52,
      53,    55,    56, -1029,   416,    58, -1029,    63, -1029,    66,
      68,    69, -1029, -1029,    70,    71, -1029,    73, -1029,    74,
   -1029, -1029, -1029, -1029, -1029,    33, -1029, -1029, -1029,   411,
     617, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
     142, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   316,
   -1029,   109, -1029,  -728,   120, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,   -45, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,   103, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029,    85, -1029, -1029, -1029, -1029, -1029, -1029, -1029,    94,
   -1029, -1029, -1029,   100,   582, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029,    92, -1029, -1029, -1029, -1029, -1029, -1029, -1028,
   -1029, -1029, -1029,   121, -1029, -1029, -1029,   122,   624, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1025, -1029,    78,
   -1029,    79, -1029,    76,    81,    84,    86, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,   116, -1029, -1029,  -108,   -62, -1029,
   -1029, -1029, -1029, -1029,   123, -1029, -1029, -1029,   128, -1029,
     603, -1029,   -63, -1029, -1029, -1029, -1029, -1029,   -44, -1029,
   -1029, -1029, -1029, -1029,   -23, -1029, -1029, -1029,   131, -1029,
   -1029, -1029,   138, -1029,   612, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029,    89, -1029, -1029,
   -1029,    93,   671, -1029, -1029, -1029,   -49, -1029,   -10, -1029,
     -56, -1029, -1029, -1029,   124, -1029, -1029, -1029,   129, -1029,
     688,     3, -1029,    13, -1029,    29, -1029,   386, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1024, -1029, -1029, -1029, -1029,
   -1029,   141, -1029, -1029, -1029,   -90, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029,   117, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029,   110, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029,   413,   605, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029,   460,   602, -1029, -1029,
   -1029, -1029, -1029, -1029,   113, -1029, -1029,   -91, -1029, -1029,
   -1029, -1029, -1029, -1029,  -112, -1029, -1029,  -131, -1029, -1029,
   -1029, -1029, -1029, -1029, -1029, -1029, -1029, -1029,   111, -1029,
   -1029, -1029, -1029
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   762,
      82,    83,    39,    64,    79,    80,   783,   989,  1090,  1091,
     859,    41,    66,    85,   442,    86,    43,    67,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   470,   171,   172,   487,   173,   174,   175,   176,
     177,   178,   179,   476,   748,   180,   477,   181,   478,   182,
     183,   184,   488,   759,   185,   186,   506,   187,   507,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   446,   235,
     236,    45,    68,   237,   516,   238,   517,   786,   239,   518,
     789,   240,   241,   242,   243,   197,   456,   198,   447,   834,
     835,   836,  1002,   837,  1003,   199,   457,   200,   458,   886,
     887,   888,  1030,   860,   861,   862,  1006,  1254,   863,  1007,
     864,  1008,   865,  1009,   866,   867,   553,   868,   869,   870,
     871,   872,   873,   874,   875,   876,   877,  1020,  1261,   878,
     879,   880,  1023,   881,  1024,   882,  1025,   883,  1026,   201,
     496,   910,   911,   912,   913,   914,   915,   916,   202,   502,
     946,   947,   948,   949,   950,   203,   499,   925,   926,   927,
    1053,    59,    75,   392,   393,   394,   567,   395,   568,   204,
     500,   934,   935,   936,   937,   938,   939,   940,   941,   205,
     483,   890,   891,   892,  1033,    47,    69,   284,   285,   286,
     529,   287,   525,   288,   526,   289,   527,   290,   530,   291,
     533,   292,   532,   206,   207,   208,   209,   492,   768,   297,
     210,   489,   902,   903,   904,  1042,  1168,  1169,   211,   484,
      53,    72,   894,   895,   896,  1036,    55,    73,   355,   356,
     357,   358,   359,   360,   361,   552,   362,   556,   363,   555,
     364,   365,   557,   366,   212,   485,   898,   899,   900,  1039,
      57,    74,   377,   378,   379,   380,   381,   561,   382,   383,
     384,   385,   386,   299,   528,   991,   992,   993,  1092,    49,
      70,   313,   314,   315,   537,   316,   213,   490,   214,   491,
     215,   498,   921,   922,   923,  1050,    51,    71,   331,   332,
     333,   216,   451,   217,   452,   218,   453,   337,   548,   996,
    1095,   338,   542,   339,   543,   340,   545,   341,   544,   342,
     547,   343,   546,   344,   541,   306,   534,   997,   219,   497,
     918,   919,  1047,  1195,  1196,  1197,  1198,  1199,  1272,  1200,
    1273,  1201,   220,   221,   503,   958,   959,   960,  1069,   961,
    1070,   222,   504,   968,   969,   970,   971,  1074,   972,   973,
    1076,   223,   505,    61,    76,   414,   415,   416,   417,   573,
     418,   419,   575,   420,   421,   422,   578,   821,   423,   579,
     424,   572,   425,   426,   427,   582,   428,   583,   429,   584,
     430,   585,   224,   445,    63,    77,   433,   434,   435,   588,
     436,   225,   511,   976,   977,  1080,  1233,  1234,  1235,  1236,
    1285,  1237,  1283,  1305,  1306,  1307,  1315,  1316,  1317,  1323,
    1318,  1319,  1320,  1321,  1327,   226,   512,   983,   984,   985,
     986,   987,   988
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   256,   309,   327,    78,   353,   373,   391,   411,
     345,   375,   884,   302,  1160,   260,   796,  1161,  1176,   244,
     300,   317,   329,   800,   367,   387,   819,   412,   354,   374,
     376,    28,   261,    29,    40,    30,    81,    31,   761,   257,
     389,   390,   262,   258,   431,   432,   298,   312,   328,   743,
     744,   745,   746,   132,   133,   437,   127,   443,   245,   301,
     318,   330,   444,   368,   388,   514,   413,    42,   523,   263,
     515,    44,   303,   524,   334,   535,   307,   132,   133,   126,
     536,   439,   304,   264,   335,   265,   132,   133,   747,    46,
    1045,   438,   253,  1046,   539,   259,   254,   308,   305,   540,
     336,   569,   283,   962,   963,   964,   570,   761,    48,   978,
     979,   980,   981,   155,   266,   389,   390,   267,   586,   268,
     269,   270,   271,   587,   272,   273,   155,   274,   590,   942,
     943,   944,   275,   591,    50,   276,   514,   277,   278,   279,
     280,   999,   281,   282,    52,   293,    54,   590,   310,   311,
     294,    87,  1000,   295,    88,   296,   132,   133,   965,  1310,
     784,   785,  1311,  1312,  1313,  1314,    89,   326,   994,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     227,   228,   155,  1048,   229,    56,  1049,   230,   231,   232,
     233,   155,   820,   928,   929,   930,   931,   932,   933,  1081,
     523,  1004,  1082,   953,   954,  1001,  1005,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,  1027,   787,   788,   126,   127,  1028,   905,   906,
     907,   908,  1160,   909,   347,  1161,  1176,   128,   129,   130,
      32,    33,    34,    35,   131,  1027,  1308,   132,   133,  1309,
    1029,   155,   134,    58,   132,   133,    60,   135,   136,   137,
     138,   139,  1062,    62,    93,    94,    95,  1063,   140,  1067,
    1071,  1077,   132,   133,  1068,  1072,  1078,   441,   141,   832,
     833,   142,    93,    94,    95,    96,   586,    84,   143,   144,
    1087,  1079,  1123,   145,  1027,  1088,   146,   535,  1270,  1266,
     147,   569,  1267,  1271,   440,   448,  1278,   449,   450,   347,
     369,   348,   349,   370,   371,   372,   454,   101,   102,   103,
     148,   149,   150,   151,   152,   153,   455,  1286,   127,   132,
     133,   459,  1287,  1226,   154,  1227,  1228,   539,  1328,  1258,
    1259,  1260,  1289,  1329,   460,   126,   127,   347,   461,   132,
     133,   462,   155,    91,    92,    93,    94,    95,    96,   155,
    1251,  1252,  1253,   319,   463,   464,   465,   132,   133,   592,
     593,   320,   321,   322,   323,   324,   325,   155,   326,   755,
     756,   757,   758,  1179,  1180,  1181,   764,   765,   766,   767,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     466,   467,   468,   469,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   471,   246,   247,   248,   472,   127,
     473,   474,   475,   479,   480,   481,   482,   486,   493,   494,
     495,   129,   130,   501,   155,   508,   509,   156,   249,   510,
     132,   133,   250,   251,   252,   134,   234,   513,   519,   520,
     135,   136,   137,   521,   155,   253,   522,   531,   256,   254,
     538,   140,   309,   549,   244,   550,   551,   554,   255,   302,
     558,   260,   155,   327,   560,   559,   300,   562,   563,   564,
     317,   566,   594,   353,   565,   571,   574,   576,   261,   373,
     577,   329,   580,   375,   581,   257,   589,   595,   262,   258,
     596,   367,   298,   245,   597,   354,   312,   387,   598,   411,
     599,   374,   376,   148,   149,   301,   602,   328,   600,   318,
     603,   604,   601,   605,   606,   263,   607,   412,   303,   608,
     330,   609,   610,   611,   612,   621,   613,   614,   304,   264,
     368,   265,   615,   334,   616,   155,   388,   627,   628,   617,
     618,   259,   619,   335,   305,   620,   622,   629,   283,   623,
     634,   635,   624,   625,   626,   632,   413,   630,   631,   336,
     266,   633,   636,   267,  1290,   268,   269,   270,   271,   637,
     272,   273,   346,   274,   638,   639,   640,   641,   275,   642,
     643,   276,   644,   277,   278,   279,   280,   645,   281,   282,
     646,   293,   647,   648,   649,   650,   294,   310,   311,   295,
     838,   296,   651,   652,   839,   840,   841,   842,   843,   844,
     845,   846,   847,   848,   849,   850,   851,   852,   653,   654,
     655,   853,   854,   855,   856,   857,   858,   656,   657,   347,
     658,   348,   349,   662,   663,   665,   350,   351,   352,   666,
     667,   673,   659,   660,   674,   156,   732,   234,   661,   132,
     133,   668,   828,   669,   670,   671,   675,   347,   676,   677,
     678,   679,   680,   681,   682,   244,   684,   685,   687,   688,
     689,   690,    91,    92,    93,    94,    95,    96,   691,   692,
     693,   694,   696,   697,   699,   698,   700,   945,   955,   701,
     411,   704,   702,   709,   982,   705,   710,   713,   714,   706,
     707,   716,   712,   719,   245,   951,   956,   966,   412,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   715,
     717,   718,   720,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   132,   133,   721,   723,   127,   347,
     724,   722,   725,   726,   952,   957,   967,   413,   728,   729,
     129,   130,   731,   733,   155,  1010,   734,   735,   736,   132,
     133,   737,   251,   738,   134,   739,   740,   741,   751,   135,
     136,   137,   742,   749,   253,   750,   752,   753,   254,   754,
     760,    30,   155,   763,   769,   770,   771,   255,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   772,   773,   778,   774,   775,   776,   409,   410,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   777,   779,   780,   781,   782,   790,   791,   792,
     793,   794,   148,   149,   795,   797,   798,   827,   822,   155,
     799,   801,   802,   803,   804,   885,   889,   805,   893,   806,
     807,   897,   901,   917,   808,   809,   810,   920,   924,   975,
     811,   990,  1011,   812,   155,   813,   814,   816,   817,   818,
     824,   825,   826,  1012,  1013,  1014,  1015,  1016,  1017,  1018,
    1019,  1021,  1022,  1032,  1105,  1031,  1035,  1034,  1037,  1038,
    1040,  1041,  1044,  1043,  1052,  1089,  1051,  1055,  1054,  1056,
    1057,  1058,  1059,  1060,  1061,  1064,  1065,  1066,  1073,  1075,
    1083,  1084,  1085,  1086,  1094,  1106,  1093,  1249,  1098,  1097,
    1096,  1099,  1101,  1102,  1103,  1104,  1107,  1108,  1109,  1110,
    1111,  1112,  1113,  1114,  1115,  1117,  1116,  1118,  1119,  1120,
    1121,  1214,  1207,  1208,  1209,  1210,   256,  1211,  1212,   353,
    1215,  1216,   373,  1218,  1219,  1131,   375,   302,  1222,   260,
    1182,  1224,  1221,   327,   300,  1188,   391,   367,  1135,  1244,
     387,   354,  1239,  1171,   374,   376,   261,  1159,  1190,  1223,
     945,   329,  1187,   257,   955,  1136,   262,   258,  1245,  1240,
     298,  1241,  1132,  1229,  1242,  1137,  1133,  1183,   951,  1170,
     982,  1184,   956,   301,  1189,   309,   368,   328,   966,   388,
    1248,  1231,  1172,   263,  1250,  1230,   303,  1191,  1268,  1269,
     330,  1274,  1138,   317,  1255,  1173,   304,   264,  1256,   265,
    1192,  1257,  1262,   334,  1263,  1174,  1139,   952,  1140,   259,
    1193,   957,   305,   335,  1264,  1265,   283,   967,  1134,   312,
    1232,  1175,  1275,  1185,  1276,  1158,  1194,  1277,   266,   336,
    1186,   267,   318,   268,   269,   270,   271,  1141,   272,   273,
    1142,   274,  1143,  1144,  1145,  1146,   275,  1147,  1148,   276,
    1149,   277,   278,   279,   280,  1150,   281,   282,  1151,   293,
    1152,  1153,  1154,  1155,   294,  1156,  1157,   295,  1164,   296,
    1162,  1163,  1284,  1165,  1292,  1293,  1166,  1279,  1167,  1296,
    1298,  1304,  1302,  1324,  1325,  1280,  1326,  1330,  1334,   823,
     672,  1124,   829,   998,   664,   831,  1100,  1122,  1178,  1206,
     815,   711,  1217,  1205,  1213,  1125,  1126,  1281,  1288,   683,
    1177,  1128,  1291,   703,  1127,  1282,  1297,  1294,  1300,  1301,
     310,   311,  1130,  1303,  1331,  1332,  1204,  1129,   708,  1203,
    1333,  1336,  1337,  1247,   995,  1246,  1295,  1225,  1220,  1202,
     974,   727,   730,   830,  1238,  1299,  1322,  1335,  1243,     0,
       0,     0,     0,  1131,     0,     0,     0,     0,     0,  1182,
     686,     0,     0,     0,  1188,     0,  1135,     0,     0,  1229,
       0,  1171,     0,     0,     0,  1159,     0,  1190,     0,     0,
       0,  1187,     0,  1136,     0,     0,     0,  1231,   695,     0,
    1132,  1230,     0,  1137,  1133,     0,  1183,  1170,     0,     0,
    1184,     0,     0,  1189,     0,     0,     0,     0,     0,     0,
    1172,     0,     0,     0,     0,     0,  1191,     0,     0,     0,
    1138,     0,     0,  1173,     0,     0,  1232,     0,     0,  1192,
       0,     0,     0,  1174,  1139,     0,  1140,     0,     0,  1193,
       0,     0,     0,     0,     0,     0,  1134,     0,     0,  1175,
       0,     0,  1185,  1158,     0,  1194,     0,     0,     0,  1186,
       0,     0,     0,     0,     0,  1141,     0,     0,  1142,     0,
    1143,  1144,  1145,  1146,     0,  1147,  1148,     0,  1149,     0,
       0,     0,     0,  1150,     0,     0,  1151,     0,  1152,  1153,
    1154,  1155,     0,  1156,  1157,     0,  1164,     0,  1162,  1163,
       0,  1165,     0,     0,  1166,     0,  1167
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   740,    69,  1042,    69,   680,  1042,  1042,    68,
      69,    70,    71,   687,    73,    74,    18,    76,    73,    74,
      74,     0,    69,     5,     7,     7,   222,     9,   641,    69,
     149,   150,    69,    69,    12,    13,    69,    70,    71,   186,
     187,   188,   189,   117,   118,     6,    96,     3,    68,    69,
      70,    71,     8,    73,    74,     3,    76,     7,     3,    69,
       8,     7,    69,     8,    71,     3,   116,   117,   118,    95,
       8,     4,    69,    69,    71,    69,   117,   118,   225,     7,
       3,     3,   132,     6,     3,    69,   136,   137,    69,     8,
      71,     3,    69,   167,   168,   169,     8,   710,     7,   205,
     206,   207,   208,   222,    69,   149,   150,    69,     3,    69,
      69,    69,    69,     8,    69,    69,   222,    69,     3,   160,
     161,   162,    69,     8,     7,    69,     3,    69,    69,    69,
      69,     8,    69,    69,     7,    69,     7,     3,    70,    70,
      69,    11,     8,    69,    14,    69,   117,   118,   222,   197,
      17,    18,   200,   201,   202,   203,    26,   146,   147,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      15,    16,   222,     3,    19,     7,     6,    22,    23,    24,
      25,   222,   184,   152,   153,   154,   155,   156,   157,     3,
       3,     3,     6,   164,   165,     8,     8,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,     3,    20,    21,    95,    96,     8,   139,   140,
     141,   142,  1270,   144,    97,  1270,  1270,   107,   108,   109,
     222,   223,   224,   225,   114,     3,     3,   117,   118,     6,
       8,   222,   122,     7,   117,   118,     7,   127,   128,   129,
     130,   131,     3,     7,    32,    33,    34,     8,   138,     3,
       3,     3,   117,   118,     8,     8,     8,     3,   148,    27,
      28,   151,    32,    33,    34,    35,     3,    10,   158,   159,
       3,     8,  1030,   163,     3,     8,   166,     3,     3,     8,
     170,     3,     8,     8,     8,     4,     8,     4,     4,    97,
      98,    99,   100,   101,   102,   103,     4,    67,    68,    69,
     190,   191,   192,   193,   194,   195,     4,     3,    96,   117,
     118,     4,     8,   196,   204,   198,   199,     3,     3,    58,
      59,    60,     8,     8,     4,    95,    96,    97,     4,   117,
     118,     4,   222,    30,    31,    32,    33,    34,    35,   222,
      41,    42,    43,   131,     4,     4,     4,   117,   118,   438,
     439,   139,   140,   141,   142,   143,   144,   222,   146,   110,
     111,   112,   113,   133,   134,   135,   123,   124,   125,   126,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
       4,     4,     4,     4,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     4,    92,    93,    94,     4,    96,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   108,   109,     4,   222,     4,     4,   514,   115,     4,
     117,   118,   119,   120,   121,   122,   523,     4,     4,     4,
     127,   128,   129,     4,   222,   132,     4,     4,   535,   136,
       4,   138,   539,     8,   523,     3,     8,     4,   145,   535,
       4,   535,   222,   550,     3,     8,   535,     4,     4,     4,
     539,     3,   222,   560,     8,     4,     4,     4,   535,   566,
       4,   550,     4,   566,     4,   535,     4,     4,   535,   535,
       4,   560,   535,   523,     4,   560,   539,   566,     4,   586,
     225,   566,   566,   190,   191,   535,     4,   550,   225,   539,
       4,     4,   225,   223,   225,   535,     4,   586,   535,     4,
     550,     4,   223,   223,   223,     4,   223,   223,   535,   535,
     560,   535,   225,   550,   224,   222,   566,     4,     4,   224,
     224,   535,   223,   550,   535,   223,   223,     4,   535,   223,
       4,     4,   225,   225,   225,   224,   586,   225,   225,   550,
     535,   225,     4,   535,  1248,   535,   535,   535,   535,   223,
     535,   535,    40,   535,     4,     4,     4,     4,   535,     4,
       4,   535,   225,   535,   535,   535,   535,   225,   535,   535,
     225,   535,     4,     4,     4,     4,   535,   539,   539,   535,
      40,   535,     4,   223,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     4,     4,
       4,    61,    62,    63,    64,    65,    66,     4,     4,    97,
       4,    99,   100,     4,     4,     4,   104,   105,   106,     4,
       4,     4,   225,   225,     4,   732,     7,   734,   225,   117,
     118,   225,   731,   225,   223,   223,     4,    97,     4,     4,
       4,   223,     4,     4,     4,   734,     4,   223,     4,     4,
       4,     4,    30,    31,    32,    33,    34,    35,     4,     4,
       4,     4,     4,     4,     4,   223,     4,   774,   775,     4,
     777,     4,   225,     4,   781,   225,     4,     4,     4,   225,
     225,     4,   225,     4,   734,   774,   775,   776,   777,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,   223,
     223,   223,     4,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,   117,   118,   225,     4,    96,    97,
       4,   225,     4,     4,   774,   775,   776,   777,     4,   223,
     108,   109,     4,     7,   222,     4,     7,     7,   222,   117,
     118,   222,   120,   222,   122,     7,     7,     5,     5,   127,
     128,   129,   222,   222,   132,   222,     5,     5,   136,   222,
       5,     7,   222,   222,     5,     5,     5,   145,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,     5,     7,   222,     7,     7,     7,   190,   191,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,     7,   222,     5,     7,     5,   222,   222,   222,
       5,   222,   190,   191,   222,   222,     7,     5,   185,   222,
     222,   222,   222,   222,   222,     7,     7,   222,     7,   222,
     222,     7,     7,     7,   222,   222,   222,     7,     7,     7,
     222,     7,     4,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   223,     6,     3,     6,     6,     3,
       6,     3,     3,     6,     3,   222,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   225,     6,   222,     4,     6,
       8,     4,     4,     4,     4,     4,   223,   225,   223,   223,
     223,   223,   223,   223,     4,   223,   225,     4,     4,     4,
       4,   225,   223,   223,   223,   223,  1033,   223,   223,  1036,
     223,   223,  1039,     4,     4,  1042,  1039,  1033,     4,  1033,
    1047,     4,   225,  1050,  1033,  1047,  1053,  1036,  1042,     6,
    1039,  1036,   225,  1042,  1039,  1039,  1033,  1042,  1047,   223,
    1067,  1050,  1047,  1033,  1071,  1042,  1033,  1033,     3,   225,
    1033,   225,  1042,  1080,   225,  1042,  1042,  1047,  1067,  1042,
    1087,  1047,  1071,  1033,  1047,  1092,  1036,  1050,  1077,  1039,
       4,  1080,  1042,  1033,   222,  1080,  1033,  1047,     8,     8,
    1050,     4,  1042,  1092,   222,  1042,  1033,  1033,   222,  1033,
    1047,   222,   222,  1050,   222,  1042,  1042,  1067,  1042,  1033,
    1047,  1071,  1033,  1050,   222,   222,  1033,  1077,  1042,  1092,
    1080,  1042,     8,  1047,     3,  1042,  1047,     8,  1033,  1050,
    1047,  1033,  1092,  1033,  1033,  1033,  1033,  1042,  1033,  1033,
    1042,  1033,  1042,  1042,  1042,  1042,  1033,  1042,  1042,  1033,
    1042,  1033,  1033,  1033,  1033,  1042,  1033,  1033,  1042,  1033,
    1042,  1042,  1042,  1042,  1033,  1042,  1042,  1033,  1042,  1033,
    1042,  1042,     4,  1042,     4,     4,  1042,   222,  1042,     4,
       4,     7,     5,     4,     4,   222,     4,     4,     4,   723,
     523,  1032,   732,   827,   514,   734,  1004,  1027,  1045,  1055,
     710,   569,  1067,  1053,  1062,  1033,  1035,   222,   222,   535,
    1044,  1038,  1270,   560,  1036,  1224,   223,   225,   222,   222,
    1092,  1092,  1041,   222,   225,   223,  1052,  1039,   566,  1050,
     223,   222,   222,  1094,   798,  1092,  1276,  1077,  1071,  1048,
     777,   586,   590,   733,  1081,  1286,  1308,  1328,  1087,    -1,
      -1,    -1,    -1,  1270,    -1,    -1,    -1,    -1,    -1,  1276,
     539,    -1,    -1,    -1,  1276,    -1,  1270,    -1,    -1,  1286,
      -1,  1270,    -1,    -1,    -1,  1270,    -1,  1276,    -1,    -1,
      -1,  1276,    -1,  1270,    -1,    -1,    -1,  1286,   550,    -1,
    1270,  1286,    -1,  1270,  1270,    -1,  1276,  1270,    -1,    -1,
    1276,    -1,    -1,  1276,    -1,    -1,    -1,    -1,    -1,    -1,
    1270,    -1,    -1,    -1,    -1,    -1,  1276,    -1,    -1,    -1,
    1270,    -1,    -1,  1270,    -1,    -1,  1286,    -1,    -1,  1276,
      -1,    -1,    -1,  1270,  1270,    -1,  1270,    -1,    -1,  1276,
      -1,    -1,    -1,    -1,    -1,    -1,  1270,    -1,    -1,  1270,
      -1,    -1,  1276,  1270,    -1,  1276,    -1,    -1,    -1,  1276,
      -1,    -1,    -1,    -1,    -1,  1270,    -1,    -1,  1270,    -1,
    1270,  1270,  1270,  1270,    -1,  1270,  1270,    -1,  1270,    -1,
      -1,    -1,    -1,  1270,    -1,    -1,  1270,    -1,  1270,  1270,
    1270,  1270,    -1,  1270,  1270,    -1,  1270,    -1,  1270,  1270,
      -1,  1270,    -1,    -1,  1270,    -1,  1270
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,     0,     5,
       7,     9,   222,   223,   224,   225,   241,   242,   243,   248,
       7,   257,     7,   262,     7,   317,     7,   431,     7,   515,
       7,   532,     7,   466,     7,   472,     7,   496,     7,   407,
       7,   599,     7,   630,   249,   244,   258,   263,   318,   432,
     516,   533,   467,   473,   497,   408,   600,   631,   241,   250,
     251,   222,   246,   247,    10,   259,   261,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    95,    96,   107,   108,
     109,   114,   117,   118,   122,   127,   128,   129,   130,   131,
     138,   148,   151,   158,   159,   163,   166,   170,   190,   191,
     192,   193,   194,   195,   204,   222,   256,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   279,   280,   282,   283,   284,   285,   286,   287,   288,
     291,   293,   295,   296,   297,   300,   301,   303,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   331,   333,   341,
     343,   385,   394,   401,   415,   425,   449,   450,   451,   452,
     456,   464,   490,   522,   524,   526,   537,   539,   541,   564,
     578,   579,   587,   597,   628,   637,   661,    15,    16,    19,
      22,    23,    24,    25,   256,   315,   316,   319,   321,   324,
     327,   328,   329,   330,   522,   524,    92,    93,    94,   115,
     119,   120,   121,   132,   136,   145,   256,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   280,   283,   284,
     285,   286,   287,   288,   291,   293,   295,   296,   297,   300,
     301,   303,   305,   311,   433,   434,   435,   437,   439,   441,
     443,   445,   447,   449,   450,   451,   452,   455,   490,   509,
     522,   524,   526,   537,   539,   541,   561,   116,   137,   256,
     445,   447,   490,   517,   518,   519,   521,   522,   524,   131,
     139,   140,   141,   142,   143,   144,   146,   256,   490,   522,
     524,   534,   535,   536,   537,   539,   541,   543,   547,   549,
     551,   553,   555,   557,   559,   464,    40,    97,    99,   100,
     104,   105,   106,   256,   361,   474,   475,   476,   477,   478,
     479,   480,   482,   484,   486,   487,   489,   522,   524,    98,
     101,   102,   103,   256,   361,   478,   484,   498,   499,   500,
     501,   502,   504,   505,   506,   507,   508,   522,   524,   149,
     150,   256,   409,   410,   411,   413,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   190,
     191,   256,   522,   524,   601,   602,   603,   604,   606,   607,
     609,   610,   611,   614,   616,   618,   619,   620,   622,   624,
     626,    12,    13,   632,   633,   634,   636,     6,     3,     4,
       8,     3,   260,     3,     8,   629,   314,   334,     4,     4,
       4,   538,   540,   542,     4,     4,   332,   342,   344,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     278,     4,     4,     4,     4,     4,   289,   292,   294,     4,
       4,     4,     4,   426,   465,   491,     4,   281,   298,   457,
     523,   525,   453,     4,     4,     4,   386,   565,   527,   402,
     416,     4,   395,   580,   588,   598,   302,   304,     4,     4,
       4,   638,   662,     4,     3,     8,   320,   322,   325,     4,
       4,     4,     4,     3,     8,   438,   440,   442,   510,   436,
     444,     4,   448,   446,   562,     3,     8,   520,     4,     3,
       8,   560,   548,   550,   554,   552,   558,   556,   544,     8,
       3,     8,   481,   362,     4,   485,   483,   488,     4,     8,
       3,   503,     4,     4,     4,     8,     3,   412,   414,     3,
       8,     4,   617,   605,     4,   608,     4,     4,   612,   615,
       4,     4,   621,   623,   625,   627,     3,     8,   635,     4,
       3,     8,   241,   241,   222,     4,     4,     4,     4,   225,
     225,   225,     4,     4,     4,   223,   225,     4,     4,     4,
     223,   223,   223,   223,   223,   225,   224,   224,   224,   223,
     223,     4,   223,   223,   225,   225,   225,     4,     4,     4,
     225,   225,   224,   225,     4,     4,     4,   223,     4,     4,
       4,     4,     4,     4,   225,   225,   225,     4,     4,     4,
       4,     4,   223,     4,     4,     4,     4,     4,     4,   225,
     225,   225,     4,     4,   265,     4,     4,     4,   225,   225,
     223,   223,   316,     4,     4,     4,     4,     4,     4,   223,
       4,     4,     4,   434,     4,   223,   518,     4,     4,     4,
       4,     4,     4,     4,     4,   536,     4,     4,   223,     4,
       4,     4,   225,   476,     4,   225,   225,   225,   500,     4,
       4,   410,   225,     4,     4,   223,     4,   223,   223,     4,
       4,   225,   225,     4,     4,     4,     4,   602,     4,   223,
     633,     4,     7,     7,     7,     7,   222,   222,   222,     7,
       7,     5,   222,   186,   187,   188,   189,   225,   290,   222,
     222,     5,     5,     5,   222,   110,   111,   112,   113,   299,
       5,   243,   245,   222,   123,   124,   125,   126,   454,     5,
       5,     5,     5,     7,     7,     7,     7,     7,   222,   222,
       5,     7,     5,   252,    17,    18,   323,    20,    21,   326,
     222,   222,   222,     5,   222,   222,   252,   222,     7,   222,
     252,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   222,   245,   222,   222,   222,    18,
     184,   613,   185,   290,   222,   222,   222,     5,   241,   264,
     632,   315,    27,    28,   335,   336,   337,   339,    40,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    61,    62,    63,    64,    65,    66,   256,
     349,   350,   351,   354,   356,   358,   360,   361,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   375,   376,
     377,   379,   381,   383,   349,     7,   345,   346,   347,     7,
     427,   428,   429,     7,   468,   469,   470,     7,   492,   493,
     494,     7,   458,   459,   460,   139,   140,   141,   142,   144,
     387,   388,   389,   390,   391,   392,   393,     7,   566,   567,
       7,   528,   529,   530,     7,   403,   404,   405,   152,   153,
     154,   155,   156,   157,   417,   418,   419,   420,   421,   422,
     423,   424,   160,   161,   162,   256,   396,   397,   398,   399,
     400,   522,   524,   164,   165,   256,   522,   524,   581,   582,
     583,   585,   167,   168,   169,   222,   522,   524,   589,   590,
     591,   592,   594,   595,   601,     7,   639,   640,   205,   206,
     207,   208,   256,   663,   664,   665,   666,   667,   668,   253,
       7,   511,   512,   513,   147,   543,   545,   563,   345,     8,
       8,     8,   338,   340,     3,     8,   352,   355,   357,   359,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     373,     4,     4,   378,   380,   382,   384,     3,     8,     8,
     348,     6,     3,   430,     6,     3,   471,     6,     3,   495,
       6,     3,   461,     6,     3,     3,     6,   568,     3,     6,
     531,     6,     3,   406,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   584,
     586,     3,     8,     4,   593,     4,   596,     3,     8,     8,
     641,     3,     6,     4,     4,     4,     4,     3,     8,   222,
     254,   255,   514,     6,     3,   546,     8,     6,     4,     4,
     336,     4,     4,     4,     4,   223,   225,   223,   225,   223,
     223,   223,   223,   223,   223,     4,   225,   223,     4,     4,
       4,     4,   350,   349,   347,   433,   429,   474,   470,   498,
     494,   256,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   280,   283,   284,   285,   286,   287,   288,   291,
     293,   295,   296,   297,   300,   301,   303,   305,   311,   361,
     425,   443,   445,   447,   449,   450,   451,   452,   462,   463,
     490,   522,   524,   537,   539,   541,   561,   460,   388,   133,
     134,   135,   256,   266,   267,   268,   311,   361,   464,   490,
     522,   524,   537,   539,   541,   569,   570,   571,   572,   573,
     575,   577,   567,   534,   530,   409,   405,   223,   223,   223,
     223,   223,   223,   418,   225,   223,   223,   397,     4,     4,
     582,   225,     4,   223,     4,   590,   196,   198,   199,   256,
     361,   522,   524,   642,   643,   644,   645,   647,   640,   225,
     225,   225,   225,   664,     6,     3,   517,   513,     4,   222,
     222,    41,    42,    43,   353,   222,   222,   222,    58,    59,
      60,   374,   222,   222,   222,   222,     8,     8,     8,     8,
       3,     8,   574,   576,     4,     8,     3,     8,     8,   222,
     222,   222,   241,   648,     4,   646,     3,     8,   222,     8,
     252,   463,     4,     4,   225,   571,     4,   223,     4,   643,
     222,   222,     5,   222,     7,   649,   650,   651,     3,     6,
     197,   200,   201,   202,   203,   652,   653,   654,   656,   657,
     658,   659,   650,   655,     4,     4,     4,   660,     3,     8,
       4,   225,   223,   223,     4,   653,   222,   222
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   226,   228,   227,   229,   227,   230,   227,   231,   227,
     232,   227,   233,   227,   234,   227,   235,   227,   236,   227,
     237,   227,   238,   227,   239,   227,   240,   227,   241,   241,
     241,   241,   241,   241,   241,   242,   244,   243,   245,   246,
     246,   247,   247,   247,   249,   248,   250,   250,   251,   251,
     251,   253,   252,   254,   254,   255,   255,   255,   256,   258,
     257,   260,   259,   259,   261,   263,   262,   264,   264,   264,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     278,   277,   279,   281,   280,   282,   283,   284,   285,   286,
     287,   289,   288,   290,   290,   290,   290,   290,   292,   291,
     294,   293,   295,   296,   298,   297,   299,   299,   299,   299,
     300,   302,   301,   304,   303,   305,   306,   307,   308,   309,
     310,   311,   312,   314,   313,   315,   315,   315,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   318,   317,
     320,   319,   322,   321,   323,   323,   325,   324,   326,   326,
     327,   328,   329,   330,   332,   331,   334,   333,   335,   335,
     335,   336,   336,   338,   337,   340,   339,   342,   341,   344,
     343,   345,   345,   346,   346,   346,   348,   347,   349,   349,
     349,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   352,   351,   353,   353,   353,   355,
     354,   357,   356,   359,   358,   360,   362,   361,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   373,   372,   374,
     374,   374,   375,   376,   378,   377,   380,   379,   382,   381,
     384,   383,   386,   385,   387,   387,   387,   388,   388,   388,
     388,   388,   389,   390,   391,   392,   393,   395,   394,   396,
     396,   396,   397,   397,   397,   397,   397,   397,   398,   399,
     400,   402,   401,   403,   403,   404,   404,   404,   406,   405,
     408,   407,   409,   409,   409,   409,   410,   410,   412,   411,
     414,   413,   416,   415,   417,   417,   417,   418,   418,   418,
     418,   418,   418,   419,   420,   421,   422,   423,   424,   426,
     425,   427,   427,   428,   428,   428,   430,   429,   432,   431,
     433,   433,   433,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   436,   435,   438,   437,   440,   439,   442,   441,
     444,   443,   446,   445,   448,   447,   449,   450,   451,   453,
     452,   454,   454,   454,   454,   455,   457,   456,   458,   458,
     459,   459,   459,   461,   460,   462,   462,   462,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   465,   464,   467,   466,   468,   468,   469,   469,
     469,   471,   470,   473,   472,   474,   474,   475,   475,   475,
     476,   476,   476,   476,   476,   476,   476,   476,   476,   476,
     477,   478,   479,   481,   480,   483,   482,   485,   484,   486,
     488,   487,   489,   491,   490,   492,   492,   493,   493,   493,
     495,   494,   497,   496,   498,   498,   499,   499,   499,   500,
     500,   500,   500,   500,   500,   500,   500,   500,   500,   501,
     503,   502,   504,   505,   506,   507,   508,   510,   509,   511,
     511,   512,   512,   512,   514,   513,   516,   515,   517,   517,
     517,   518,   518,   518,   518,   518,   518,   518,   518,   520,
     519,   521,   523,   522,   525,   524,   527,   526,   528,   528,
     529,   529,   529,   531,   530,   533,   532,   534,   534,   535,
     535,   535,   536,   536,   536,   536,   536,   536,   536,   536,
     536,   536,   536,   536,   536,   536,   536,   538,   537,   540,
     539,   542,   541,   544,   543,   546,   545,   548,   547,   550,
     549,   552,   551,   554,   553,   556,   555,   558,   557,   560,
     559,   562,   561,   563,   563,   565,   564,   566,   566,   566,
     568,   567,   569,   569,   570,   570,   570,   571,   571,   571,
     571,   571,   571,   571,   571,   571,   571,   571,   571,   571,
     571,   571,   571,   572,   574,   573,   576,   575,   577,   578,
     580,   579,   581,   581,   581,   582,   582,   582,   582,   582,
     584,   583,   586,   585,   588,   587,   589,   589,   589,   590,
     590,   590,   590,   590,   590,   591,   593,   592,   594,   596,
     595,   598,   597,   600,   599,   601,   601,   601,   602,   602,
     602,   602,   602,   602,   602,   602,   602,   602,   602,   602,
     602,   602,   602,   602,   602,   602,   603,   605,   604,   606,
     608,   607,   609,   610,   612,   611,   613,   613,   615,   614,
     617,   616,   618,   619,   621,   620,   623,   622,   625,   624,
     627,   626,   629,   628,   631,   630,   632,   632,   632,   633,
     633,   635,   634,   636,   638,   637,   639,   639,   639,   641,
     640,   642,   642,   642,   643,   643,   643,   643,   643,   643,
     643,   644,   646,   645,   648,   647,   649,   649,   649,   651,
     650,   652,   652,   652,   653,   653,   653,   653,   653,   655,
     654,   656,   657,   658,   660,   659,   662,   661,   663,   663,
     663,   664,   664,   664,   664,   664,   665,   666,   667,   668
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
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
       0,   321,   321,   321,   322,   322,   323,   323,   324,   324,
     325,   325,   326,   326,   327,   327,   328,   328,   329,   329,
     330,   330,   331,   331,   332,   332,   333,   333,   341,   342,
     343,   344,   345,   346,   347,   350,   355,   355,   366,   369,
     370,   373,   378,   384,   389,   389,   396,   397,   400,   404,
     408,   414,   414,   421,   422,   425,   429,   433,   443,   452,
     452,   467,   467,   481,   484,   490,   490,   499,   500,   501,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   579,
     585,   591,   597,   603,   609,   615,   621,   627,   633,   639,
     645,   645,   654,   660,   660,   669,   675,   681,   687,   693,
     699,   705,   705,   714,   717,   720,   723,   726,   732,   732,
     741,   741,   750,   759,   769,   769,   778,   781,   784,   787,
     792,   798,   798,   807,   807,   816,   822,   828,   834,   840,
     846,   852,   858,   864,   864,   876,   877,   878,   883,   884,
     885,   886,   887,   888,   889,   890,   891,   892,   895,   895,
     904,   904,   915,   915,   923,   924,   927,   927,   935,   937,
     941,   947,   953,   959,   965,   965,   978,   978,   989,   990,
     991,   996,   997,  1000,  1000,  1019,  1019,  1037,  1037,  1050,
    1050,  1061,  1062,  1065,  1066,  1067,  1072,  1072,  1082,  1083,
    1084,  1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,
    1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,
    1108,  1109,  1110,  1111,  1114,  1114,  1122,  1123,  1124,  1127,
    1127,  1136,  1136,  1145,  1145,  1154,  1160,  1160,  1169,  1175,
    1181,  1187,  1193,  1199,  1205,  1211,  1217,  1223,  1223,  1231,
    1232,  1233,  1236,  1242,  1248,  1248,  1257,  1257,  1266,  1266,
    1275,  1275,  1284,  1284,  1295,  1296,  1297,  1302,  1303,  1304,
    1305,  1306,  1309,  1314,  1319,  1324,  1329,  1336,  1336,  1349,
    1350,  1351,  1356,  1357,  1358,  1359,  1360,  1361,  1364,  1370,
    1376,  1382,  1382,  1393,  1394,  1397,  1398,  1399,  1404,  1404,
    1414,  1414,  1424,  1425,  1426,  1429,  1432,  1433,  1436,  1436,
    1445,  1445,  1454,  1454,  1466,  1467,  1468,  1473,  1474,  1475,
    1476,  1477,  1478,  1481,  1487,  1493,  1499,  1505,  1511,  1520,
    1520,  1534,  1535,  1538,  1539,  1540,  1549,  1549,  1575,  1575,
    1586,  1587,  1588,  1594,  1595,  1596,  1597,  1598,  1599,  1600,
    1601,  1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,
    1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,
    1621,  1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,
    1641,  1642,  1645,  1645,  1654,  1654,  1663,  1663,  1672,  1672,
    1681,  1681,  1690,  1690,  1699,  1699,  1710,  1716,  1722,  1728,
    1728,  1736,  1737,  1738,  1739,  1742,  1750,  1750,  1762,  1763,
    1767,  1768,  1769,  1774,  1774,  1782,  1783,  1784,  1789,  1790,
    1791,  1792,  1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,
    1801,  1802,  1803,  1804,  1805,  1806,  1807,  1808,  1809,  1810,
    1811,  1812,  1813,  1814,  1815,  1816,  1817,  1818,  1819,  1820,
    1821,  1822,  1823,  1824,  1825,  1826,  1827,  1828,  1829,  1830,
    1831,  1832,  1839,  1839,  1853,  1853,  1862,  1863,  1866,  1867,
    1868,  1875,  1875,  1890,  1890,  1904,  1905,  1908,  1909,  1910,
    1915,  1916,  1917,  1918,  1919,  1920,  1921,  1922,  1923,  1924,
    1927,  1929,  1935,  1937,  1937,  1946,  1946,  1955,  1955,  1964,
    1966,  1966,  1975,  1985,  1985,  1998,  1999,  2004,  2005,  2006,
    2013,  2013,  2025,  2025,  2037,  2038,  2043,  2044,  2045,  2052,
    2053,  2054,  2055,  2056,  2057,  2058,  2059,  2060,  2061,  2064,
    2066,  2066,  2075,  2077,  2079,  2085,  2091,  2100,  2100,  2113,
    2114,  2117,  2118,  2119,  2124,  2124,  2134,  2134,  2144,  2145,
    2146,  2151,  2152,  2153,  2154,  2155,  2156,  2157,  2158,  2161,
    2161,  2170,  2176,  2176,  2201,  2201,  2231,  2231,  2242,  2243,
    2246,  2247,  2248,  2253,  2253,  2262,  2262,  2271,  2272,  2275,
    2276,  2277,  2283,  2284,  2285,  2286,  2287,  2288,  2289,  2290,
    2291,  2292,  2293,  2294,  2295,  2296,  2297,  2300,  2300,  2309,
    2309,  2318,  2318,  2327,  2327,  2336,  2336,  2347,  2347,  2356,
    2356,  2365,  2365,  2374,  2374,  2383,  2383,  2392,  2392,  2401,
    2401,  2415,  2415,  2426,  2427,  2433,  2433,  2444,  2445,  2446,
    2451,  2451,  2461,  2462,  2465,  2466,  2467,  2472,  2473,  2474,
    2475,  2476,  2477,  2478,  2479,  2480,  2481,  2482,  2483,  2484,
    2485,  2486,  2487,  2490,  2492,  2492,  2501,  2501,  2510,  2518,
    2526,  2526,  2537,  2538,  2539,  2544,  2545,  2546,  2547,  2548,
    2551,  2551,  2560,  2560,  2572,  2572,  2585,  2586,  2587,  2592,
    2593,  2594,  2595,  2596,  2597,  2600,  2606,  2606,  2615,  2621,
    2621,  2631,  2631,  2644,  2644,  2654,  2655,  2656,  2661,  2662,
    2663,  2664,  2665,  2666,  2667,  2668,  2669,  2670,  2671,  2672,
    2673,  2674,  2675,  2676,  2677,  2678,  2681,  2687,  2687,  2696,
    2702,  2702,  2711,  2717,  2723,  2723,  2732,  2733,  2736,  2736,
    2746,  2746,  2756,  2763,  2770,  2770,  2779,  2779,  2789,  2789,
    2799,  2799,  2811,  2811,  2823,  2823,  2833,  2834,  2835,  2841,
    2842,  2845,  2845,  2856,  2864,  2864,  2877,  2878,  2879,  2885,
    2885,  2893,  2894,  2895,  2900,  2901,  2902,  2903,  2904,  2905,
    2906,  2909,  2915,  2915,  2924,  2924,  2935,  2936,  2937,  2942,
    2942,  2950,  2951,  2952,  2957,  2958,  2959,  2960,  2961,  2964,
    2964,  2973,  2979,  2985,  2991,  2991,  3000,  3000,  3011,  3012,
    3013,  3018,  3019,  3020,  3021,  3022,  3025,  3031,  3037,  3043
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
#line 6472 "dhcp4_parser.cc"

#line 3049 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
