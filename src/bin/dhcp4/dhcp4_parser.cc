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
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 307 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 307 "dhcp4_parser.yy"
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
#line 316 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 317 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 318 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 789 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 319 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 320 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 801 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 321 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 322 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 813 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 323 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 819 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 324 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 825 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 325 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 831 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 326 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 837 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 327 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 843 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 328 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 849 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 336 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 855 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 337 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 338 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 339 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 340 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 341 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 885 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 342 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 345 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 900 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 350 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 911 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 355 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 921 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 361 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 927 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 368 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 373 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 379 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 956 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 384 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 387 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 395 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 399 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 403 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 999 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 409 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1007 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 411 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1016 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 420 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1025 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 424 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1034 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 428 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1042 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 438 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1053 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 447 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1064 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 452 "dhcp4_parser.yy"
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
#line 462 "dhcp4_parser.yy"
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
#line 471 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1102 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 479 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 485 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 489 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1129 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 496 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1137 "dhcp4_parser.cc"
    break;

  case 139: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 574 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1147 "dhcp4_parser.cc"
    break;

  case 140: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 580 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 141: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 586 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 142: // renew_timer: "renew-timer" ":" "integer"
#line 592 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 143: // rebind_timer: "rebind-timer" ":" "integer"
#line 598 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1187 "dhcp4_parser.cc"
    break;

  case 144: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 604 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp4_parser.cc"
    break;

  case 145: // t1_percent: "t1-percent" ":" "floating point"
#line 610 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1207 "dhcp4_parser.cc"
    break;

  case 146: // t2_percent: "t2-percent" ":" "floating point"
#line 616 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1217 "dhcp4_parser.cc"
    break;

  case 147: // cache_threshold: "cache-threshold" ":" "floating point"
#line 622 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1227 "dhcp4_parser.cc"
    break;

  case 148: // cache_max_age: "cache-max-age" ":" "integer"
#line 628 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1237 "dhcp4_parser.cc"
    break;

  case 149: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 634 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 150: // $@20: %empty
#line 640 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 151: // server_tag: "server-tag" $@20 ":" "constant string"
#line 643 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 152: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 649 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1276 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 655 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1285 "dhcp4_parser.cc"
    break;

  case 154: // allocator: "allocator" $@21 ":" "constant string"
#line 658 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 155: // echo_client_id: "echo-client-id" ":" "boolean"
#line 664 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 156: // match_client_id: "match-client-id" ":" "boolean"
#line 670 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 157: // authoritative: "authoritative" ":" "boolean"
#line 676 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 158: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 682 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 159: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 688 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1345 "dhcp4_parser.cc"
    break;

  case 160: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 694 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1355 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 700 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 703 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1373 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-present"
#line 709 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "never"
#line 712 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "always"
#line 715 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1397 "dhcp4_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-not-present"
#line 718 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1405 "dhcp4_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "boolean"
#line 721 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1414 "dhcp4_parser.cc"
    break;

  case 168: // $@23: %empty
#line 727 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 169: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 730 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1433 "dhcp4_parser.cc"
    break;

  case 170: // $@24: %empty
#line 736 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 171: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 739 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 172: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 745 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1462 "dhcp4_parser.cc"
    break;

  case 173: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 754 "dhcp4_parser.yy"
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
#line 764 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 767 "dhcp4_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 773 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1502 "dhcp4_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 776 "dhcp4_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1510 "dhcp4_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 779 "dhcp4_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1518 "dhcp4_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 782 "dhcp4_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1526 "dhcp4_parser.cc"
    break;

  case 180: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 787 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // $@26: %empty
#line 793 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 796 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 183: // $@27: %empty
#line 802 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 184: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 805 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 185: // store_extended_info: "store-extended-info" ":" "boolean"
#line 811 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 186: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 817 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 187: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 823 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 188: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 829 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 189: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 835 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 841 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 191: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 847 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 192: // stash_agent_options: "stash-agent-options" ":" "boolean"
#line 853 "dhcp4_parser.yy"
                                                       {
    ctx.unique("stash-agent-options", ctx.loc2pos(yystack_[2].location));
    ElementPtr stash(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("stash-agent-options", stash);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 193: // $@28: %empty
#line 859 "dhcp4_parser.yy"
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
#line 865 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 197: // interfaces_config_params: interfaces_config_params ","
#line 873 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1684 "dhcp4_parser.cc"
    break;

  case 208: // $@29: %empty
#line 890 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 209: // sub_interfaces4: "{" $@29 interfaces_config_params "}"
#line 894 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1703 "dhcp4_parser.cc"
    break;

  case 210: // $@30: %empty
#line 899 "dhcp4_parser.yy"
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
#line 905 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1724 "dhcp4_parser.cc"
    break;

  case 212: // $@31: %empty
#line 910 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 213: // dhcp_socket_type: "dhcp-socket-type" $@31 ":" socket_type
#line 913 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1742 "dhcp4_parser.cc"
    break;

  case 214: // socket_type: "raw"
#line 918 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp4_parser.cc"
    break;

  case 215: // socket_type: "udp"
#line 919 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp4_parser.cc"
    break;

  case 216: // $@32: %empty
#line 922 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 217: // outbound_interface: "outbound-interface" $@32 ":" outbound_interface_value
#line 925 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 218: // outbound_interface_value: "same-as-inbound"
#line 930 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 219: // outbound_interface_value: "use-routing"
#line 932 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1788 "dhcp4_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 936 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 942 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 948 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 954 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 224: // $@33: %empty
#line 960 "dhcp4_parser.yy"
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
#line 966 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 226: // $@34: %empty
#line 973 "dhcp4_parser.yy"
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
#line 979 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 230: // sanity_checks_params: sanity_checks_params ","
#line 986 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1880 "dhcp4_parser.cc"
    break;

  case 233: // $@35: %empty
#line 995 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp4_parser.cc"
    break;

  case 234: // lease_checks: "lease-checks" $@35 ":" "constant string"
#line 998 "dhcp4_parser.yy"
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
#line 1014 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1918 "dhcp4_parser.cc"
    break;

  case 236: // extended_info_checks: "extended-info-checks" $@36 ":" "constant string"
#line 1017 "dhcp4_parser.yy"
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
#line 1032 "dhcp4_parser.yy"
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
#line 1038 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 239: // $@38: %empty
#line 1045 "dhcp4_parser.yy"
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
#line 1051 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 245: // not_empty_database_list: not_empty_database_list ","
#line 1062 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1989 "dhcp4_parser.cc"
    break;

  case 246: // $@39: %empty
#line 1067 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1999 "dhcp4_parser.cc"
    break;

  case 247: // database: "{" $@39 database_map_params "}"
#line 1071 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2009 "dhcp4_parser.cc"
    break;

  case 250: // database_map_params: database_map_params ","
#line 1079 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 2017 "dhcp4_parser.cc"
    break;

  case 274: // $@40: %empty
#line 1109 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 2026 "dhcp4_parser.cc"
    break;

  case 275: // database_type: "type" $@40 ":" db_type
#line 1112 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2035 "dhcp4_parser.cc"
    break;

  case 276: // db_type: "memfile"
#line 1117 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 2041 "dhcp4_parser.cc"
    break;

  case 277: // db_type: "mysql"
#line 1118 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 2047 "dhcp4_parser.cc"
    break;

  case 278: // db_type: "postgresql"
#line 1119 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 2053 "dhcp4_parser.cc"
    break;

  case 279: // $@41: %empty
#line 1122 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp4_parser.cc"
    break;

  case 280: // user: "user" $@41 ":" "constant string"
#line 1125 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 2072 "dhcp4_parser.cc"
    break;

  case 281: // $@42: %empty
#line 1131 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc"
    break;

  case 282: // password: "password" $@42 ":" "constant string"
#line 1134 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc"
    break;

  case 283: // $@43: %empty
#line 1140 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 284: // host: "host" $@43 ":" "constant string"
#line 1143 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 285: // port: "port" ":" "integer"
#line 1149 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 286: // $@44: %empty
#line 1155 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 287: // name: "name" $@44 ":" "constant string"
#line 1158 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 288: // persist: "persist" ":" "boolean"
#line 1164 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2149 "dhcp4_parser.cc"
    break;

  case 289: // lfc_interval: "lfc-interval" ":" "integer"
#line 1170 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 290: // readonly: "readonly" ":" "boolean"
#line 1176 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 291: // connect_timeout: "connect-timeout" ":" "integer"
#line 1182 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2179 "dhcp4_parser.cc"
    break;

  case 292: // read_timeout: "read-timeout" ":" "integer"
#line 1188 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 293: // write_timeout: "write-timeout" ":" "integer"
#line 1194 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2199 "dhcp4_parser.cc"
    break;

  case 294: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1200 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 295: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1206 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 296: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1212 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2229 "dhcp4_parser.cc"
    break;

  case 297: // $@45: %empty
#line 1218 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 298: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1221 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2247 "dhcp4_parser.cc"
    break;

  case 299: // on_fail_mode: "stop-retry-exit"
#line 1226 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2253 "dhcp4_parser.cc"
    break;

  case 300: // on_fail_mode: "serve-retry-exit"
#line 1227 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2259 "dhcp4_parser.cc"
    break;

  case 301: // on_fail_mode: "serve-retry-continue"
#line 1228 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2265 "dhcp4_parser.cc"
    break;

  case 302: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1231 "dhcp4_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2275 "dhcp4_parser.cc"
    break;

  case 303: // max_row_errors: "max-row-errors" ":" "integer"
#line 1237 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2285 "dhcp4_parser.cc"
    break;

  case 304: // $@46: %empty
#line 1243 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2294 "dhcp4_parser.cc"
    break;

  case 305: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1246 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2304 "dhcp4_parser.cc"
    break;

  case 306: // $@47: %empty
#line 1252 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 307: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1255 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc"
    break;

  case 308: // $@48: %empty
#line 1261 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 309: // key_file: "key-file" $@48 ":" "constant string"
#line 1264 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2342 "dhcp4_parser.cc"
    break;

  case 310: // $@49: %empty
#line 1270 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 311: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1273 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1279 "dhcp4_parser.yy"
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
#line 1285 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2382 "dhcp4_parser.cc"
    break;

  case 316: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1292 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2390 "dhcp4_parser.cc"
    break;

  case 322: // duid_id: "duid"
#line 1304 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2399 "dhcp4_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1309 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 324: // circuit_id: "circuit-id"
#line 1314 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 325: // client_id: "client-id"
#line 1319 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2426 "dhcp4_parser.cc"
    break;

  case 326: // flex_id: "flex-id"
#line 1324 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 327: // $@51: %empty
#line 1331 "dhcp4_parser.yy"
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
#line 1337 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2458 "dhcp4_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1346 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2466 "dhcp4_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1359 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2476 "dhcp4_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1365 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2486 "dhcp4_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1371 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2496 "dhcp4_parser.cc"
    break;

  case 341: // $@52: %empty
#line 1377 "dhcp4_parser.yy"
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
#line 1383 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2517 "dhcp4_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1394 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2525 "dhcp4_parser.cc"
    break;

  case 348: // $@53: %empty
#line 1399 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 349: // hooks_library: "{" $@53 hooks_params "}"
#line 1403 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 350: // $@54: %empty
#line 1409 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1413 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1421 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2573 "dhcp4_parser.cc"
    break;

  case 358: // $@55: %empty
#line 1431 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2582 "dhcp4_parser.cc"
    break;

  case 359: // library: "library" $@55 ":" "constant string"
#line 1434 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2592 "dhcp4_parser.cc"
    break;

  case 360: // $@56: %empty
#line 1440 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2601 "dhcp4_parser.cc"
    break;

  case 361: // parameters: "parameters" $@56 ":" map_value
#line 1443 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2610 "dhcp4_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1449 "dhcp4_parser.yy"
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
#line 1455 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2632 "dhcp4_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1463 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2640 "dhcp4_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1476 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2650 "dhcp4_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1482 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1488 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1494 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1500 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2690 "dhcp4_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1506 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2700 "dhcp4_parser.cc"
    break;

  case 379: // $@58: %empty
#line 1515 "dhcp4_parser.yy"
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
#line 1521 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 385: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1535 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2729 "dhcp4_parser.cc"
    break;

  case 386: // $@59: %empty
#line 1544 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2739 "dhcp4_parser.cc"
    break;

  case 387: // subnet4: "{" $@59 subnet4_params "}"
#line 1548 "dhcp4_parser.yy"
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
#line 1570 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2775 "dhcp4_parser.cc"
    break;

  case 389: // sub_subnet4: "{" $@60 subnet4_params "}"
#line 1574 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2785 "dhcp4_parser.cc"
    break;

  case 392: // subnet4_params: subnet4_params ","
#line 1583 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2793 "dhcp4_parser.cc"
    break;

  case 442: // $@61: %empty
#line 1640 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 443: // subnet: "subnet" $@61 ":" "constant string"
#line 1643 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 444: // $@62: %empty
#line 1649 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 445: // subnet_4o6_interface: "4o6-interface" $@62 ":" "constant string"
#line 1652 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 446: // $@63: %empty
#line 1658 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 447: // subnet_4o6_interface_id: "4o6-interface-id" $@63 ":" "constant string"
#line 1661 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2850 "dhcp4_parser.cc"
    break;

  case 448: // $@64: %empty
#line 1667 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 449: // subnet_4o6_subnet: "4o6-subnet" $@64 ":" "constant string"
#line 1670 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 450: // $@65: %empty
#line 1676 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2878 "dhcp4_parser.cc"
    break;

  case 451: // interface: "interface" $@65 ":" "constant string"
#line 1679 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2888 "dhcp4_parser.cc"
    break;

  case 452: // $@66: %empty
#line 1685 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2897 "dhcp4_parser.cc"
    break;

  case 453: // client_class: "client-class" $@66 ":" "constant string"
#line 1688 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2907 "dhcp4_parser.cc"
    break;

  case 454: // $@67: %empty
#line 1694 "dhcp4_parser.yy"
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
#line 1700 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc"
    break;

  case 456: // reservations_global: "reservations-global" ":" "boolean"
#line 1705 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 457: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1711 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2948 "dhcp4_parser.cc"
    break;

  case 458: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1717 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2958 "dhcp4_parser.cc"
    break;

  case 459: // $@68: %empty
#line 1723 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 460: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1726 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 461: // hr_mode: "disabled"
#line 1731 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2982 "dhcp4_parser.cc"
    break;

  case 462: // hr_mode: "out-of-pool"
#line 1732 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2988 "dhcp4_parser.cc"
    break;

  case 463: // hr_mode: "global"
#line 1733 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2994 "dhcp4_parser.cc"
    break;

  case 464: // hr_mode: "all"
#line 1734 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 3000 "dhcp4_parser.cc"
    break;

  case 465: // id: "id" ":" "integer"
#line 1737 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3010 "dhcp4_parser.cc"
    break;

  case 466: // $@69: %empty
#line 1745 "dhcp4_parser.yy"
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
#line 1751 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3031 "dhcp4_parser.cc"
    break;

  case 472: // shared_networks_list: shared_networks_list ","
#line 1764 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3039 "dhcp4_parser.cc"
    break;

  case 473: // $@70: %empty
#line 1769 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3049 "dhcp4_parser.cc"
    break;

  case 474: // shared_network: "{" $@70 shared_network_params "}"
#line 1773 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 477: // shared_network_params: shared_network_params ","
#line 1779 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3065 "dhcp4_parser.cc"
    break;

  case 522: // $@71: %empty
#line 1834 "dhcp4_parser.yy"
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
#line 1840 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp4_parser.cc"
    break;

  case 524: // $@72: %empty
#line 1848 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3095 "dhcp4_parser.cc"
    break;

  case 525: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1851 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3103 "dhcp4_parser.cc"
    break;

  case 530: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1863 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3111 "dhcp4_parser.cc"
    break;

  case 531: // $@73: %empty
#line 1870 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 532: // option_def_entry: "{" $@73 option_def_params "}"
#line 1874 "dhcp4_parser.yy"
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
#line 1885 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3143 "dhcp4_parser.cc"
    break;

  case 534: // sub_option_def: "{" $@74 option_def_params "}"
#line 1889 "dhcp4_parser.yy"
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
#line 1905 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3163 "dhcp4_parser.cc"
    break;

  case 551: // code: "code" ":" "integer"
#line 1924 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 553: // $@75: %empty
#line 1932 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 554: // option_def_type: "type" $@75 ":" "constant string"
#line 1935 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3192 "dhcp4_parser.cc"
    break;

  case 555: // $@76: %empty
#line 1941 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp4_parser.cc"
    break;

  case 556: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1944 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 557: // $@77: %empty
#line 1950 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3220 "dhcp4_parser.cc"
    break;

  case 558: // space: "space" $@77 ":" "constant string"
#line 1953 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3230 "dhcp4_parser.cc"
    break;

  case 560: // $@78: %empty
#line 1961 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp4_parser.cc"
    break;

  case 561: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1964 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 562: // option_def_array: "array" ":" "boolean"
#line 1970 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3259 "dhcp4_parser.cc"
    break;

  case 563: // $@79: %empty
#line 1980 "dhcp4_parser.yy"
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
#line 1986 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3280 "dhcp4_parser.cc"
    break;

  case 569: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2001 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3288 "dhcp4_parser.cc"
    break;

  case 570: // $@80: %empty
#line 2008 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3298 "dhcp4_parser.cc"
    break;

  case 571: // option_data_entry: "{" $@80 option_data_params "}"
#line 2012 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 572: // $@81: %empty
#line 2020 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3317 "dhcp4_parser.cc"
    break;

  case 573: // sub_option_data: "{" $@81 option_data_params "}"
#line 2024 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3326 "dhcp4_parser.cc"
    break;

  case 578: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2040 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3334 "dhcp4_parser.cc"
    break;

  case 590: // $@82: %empty
#line 2061 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3343 "dhcp4_parser.cc"
    break;

  case 591: // option_data_data: "data" $@82 ":" "constant string"
#line 2064 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 594: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2074 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 595: // option_data_always_send: "always-send" ":" "boolean"
#line 2080 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3373 "dhcp4_parser.cc"
    break;

  case 596: // option_data_never_send: "never-send" ":" "boolean"
#line 2086 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3383 "dhcp4_parser.cc"
    break;

  case 597: // $@83: %empty
#line 2095 "dhcp4_parser.yy"
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
#line 2101 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3404 "dhcp4_parser.cc"
    break;

  case 603: // not_empty_pools_list: not_empty_pools_list ","
#line 2114 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3412 "dhcp4_parser.cc"
    break;

  case 604: // $@84: %empty
#line 2119 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 605: // pool_list_entry: "{" $@84 pool_params "}"
#line 2123 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 606: // $@85: %empty
#line 2129 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3442 "dhcp4_parser.cc"
    break;

  case 607: // sub_pool4: "{" $@85 pool_params "}"
#line 2133 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 610: // pool_params: pool_params ","
#line 2141 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3460 "dhcp4_parser.cc"
    break;

  case 619: // $@86: %empty
#line 2156 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3469 "dhcp4_parser.cc"
    break;

  case 620: // pool_entry: "pool" $@86 ":" "constant string"
#line 2159 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 621: // pool_id: "pool-id" ":" "integer"
#line 2165 "dhcp4_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3489 "dhcp4_parser.cc"
    break;

  case 622: // $@87: %empty
#line 2171 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3497 "dhcp4_parser.cc"
    break;

  case 623: // user_context: "user-context" $@87 ":" map_value
#line 2173 "dhcp4_parser.yy"
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
#line 2196 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3532 "dhcp4_parser.cc"
    break;

  case 625: // comment: "comment" $@88 ":" "constant string"
#line 2198 "dhcp4_parser.yy"
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
#line 2226 "dhcp4_parser.yy"
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
#line 2232 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 632: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2243 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3590 "dhcp4_parser.cc"
    break;

  case 633: // $@90: %empty
#line 2248 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3600 "dhcp4_parser.cc"
    break;

  case 634: // reservation: "{" $@90 reservation_params "}"
#line 2252 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3609 "dhcp4_parser.cc"
    break;

  case 635: // $@91: %empty
#line 2257 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3619 "dhcp4_parser.cc"
    break;

  case 636: // sub_reservation: "{" $@91 reservation_params "}"
#line 2261 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3628 "dhcp4_parser.cc"
    break;

  case 641: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2272 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3636 "dhcp4_parser.cc"
    break;

  case 657: // $@92: %empty
#line 2295 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 658: // next_server: "next-server" $@92 ":" "constant string"
#line 2298 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 659: // $@93: %empty
#line 2304 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 660: // server_hostname: "server-hostname" $@93 ":" "constant string"
#line 2307 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 661: // $@94: %empty
#line 2313 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 662: // boot_file_name: "boot-file-name" $@94 ":" "constant string"
#line 2316 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 663: // $@95: %empty
#line 2322 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 664: // ip_address: "ip-address" $@95 ":" "constant string"
#line 2325 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 665: // $@96: %empty
#line 2331 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 666: // duid: "duid" $@96 ":" "constant string"
#line 2334 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 667: // $@97: %empty
#line 2340 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3740 "dhcp4_parser.cc"
    break;

  case 668: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2343 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3750 "dhcp4_parser.cc"
    break;

  case 669: // $@98: %empty
#line 2349 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 670: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2352 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 671: // $@99: %empty
#line 2358 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 672: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2361 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 673: // $@100: %empty
#line 2367 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3797 "dhcp4_parser.cc"
    break;

  case 674: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2370 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3807 "dhcp4_parser.cc"
    break;

  case 675: // $@101: %empty
#line 2376 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3816 "dhcp4_parser.cc"
    break;

  case 676: // hostname: "hostname" $@101 ":" "constant string"
#line 2379 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3826 "dhcp4_parser.cc"
    break;

  case 677: // $@102: %empty
#line 2385 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3838 "dhcp4_parser.cc"
    break;

  case 678: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2391 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3847 "dhcp4_parser.cc"
    break;

  case 679: // $@103: %empty
#line 2399 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3859 "dhcp4_parser.cc"
    break;

  case 680: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2405 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 682: // $@104: %empty
#line 2413 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3880 "dhcp4_parser.cc"
    break;

  case 683: // ip_addresses: "ip-addresses" $@104 ":" list_strings
#line 2419 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3889 "dhcp4_parser.cc"
    break;

  case 684: // $@105: %empty
#line 2427 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 685: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2433 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 688: // client_classes_list: client_classes_list ","
#line 2440 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3918 "dhcp4_parser.cc"
    break;

  case 689: // $@106: %empty
#line 2445 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 690: // client_class_entry: "{" $@106 client_class_params "}"
#line 2449 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3938 "dhcp4_parser.cc"
    break;

  case 695: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2461 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3946 "dhcp4_parser.cc"
    break;

  case 713: // $@107: %empty
#line 2486 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3955 "dhcp4_parser.cc"
    break;

  case 714: // client_class_test: "test" $@107 ":" "constant string"
#line 2489 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3965 "dhcp4_parser.cc"
    break;

  case 715: // $@108: %empty
#line 2495 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3974 "dhcp4_parser.cc"
    break;

  case 716: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2498 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 717: // only_if_required: "only-if-required" ":" "boolean"
#line 2504 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 718: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2512 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4004 "dhcp4_parser.cc"
    break;

  case 719: // $@109: %empty
#line 2520 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4016 "dhcp4_parser.cc"
    break;

  case 720: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2526 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4025 "dhcp4_parser.cc"
    break;

  case 723: // control_socket_params: control_socket_params ","
#line 2533 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4033 "dhcp4_parser.cc"
    break;

  case 729: // $@110: %empty
#line 2545 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 730: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2548 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4052 "dhcp4_parser.cc"
    break;

  case 731: // $@111: %empty
#line 2554 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4061 "dhcp4_parser.cc"
    break;

  case 732: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2557 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4071 "dhcp4_parser.cc"
    break;

  case 733: // $@112: %empty
#line 2566 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4083 "dhcp4_parser.cc"
    break;

  case 734: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2572 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4094 "dhcp4_parser.cc"
    break;

  case 737: // queue_control_params: queue_control_params ","
#line 2581 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4102 "dhcp4_parser.cc"
    break;

  case 744: // enable_queue: "enable-queue" ":" "boolean"
#line 2594 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4112 "dhcp4_parser.cc"
    break;

  case 745: // $@113: %empty
#line 2600 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 746: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2603 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 747: // capacity: "capacity" ":" "integer"
#line 2609 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 748: // $@114: %empty
#line 2615 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4150 "dhcp4_parser.cc"
    break;

  case 749: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2618 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4159 "dhcp4_parser.cc"
    break;

  case 750: // $@115: %empty
#line 2625 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 751: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2631 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 752: // $@116: %empty
#line 2638 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 753: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2642 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 756: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2650 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4210 "dhcp4_parser.cc"
    break;

  case 768: // enable_updates: "enable-updates" ":" "boolean"
#line 2668 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4220 "dhcp4_parser.cc"
    break;

  case 769: // $@117: %empty
#line 2674 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4229 "dhcp4_parser.cc"
    break;

  case 770: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2677 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4239 "dhcp4_parser.cc"
    break;

  case 771: // server_port: "server-port" ":" "integer"
#line 2683 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4249 "dhcp4_parser.cc"
    break;

  case 772: // $@118: %empty
#line 2689 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 773: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2692 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4268 "dhcp4_parser.cc"
    break;

  case 774: // sender_port: "sender-port" ":" "integer"
#line 2698 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4278 "dhcp4_parser.cc"
    break;

  case 775: // max_queue_size: "max-queue-size" ":" "integer"
#line 2704 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4288 "dhcp4_parser.cc"
    break;

  case 776: // $@119: %empty
#line 2710 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4297 "dhcp4_parser.cc"
    break;

  case 777: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2713 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4306 "dhcp4_parser.cc"
    break;

  case 778: // ncr_protocol_value: "udp"
#line 2719 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4312 "dhcp4_parser.cc"
    break;

  case 779: // ncr_protocol_value: "tcp"
#line 2720 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4318 "dhcp4_parser.cc"
    break;

  case 780: // $@120: %empty
#line 2723 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4327 "dhcp4_parser.cc"
    break;

  case 781: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2726 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4337 "dhcp4_parser.cc"
    break;

  case 782: // $@121: %empty
#line 2734 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4349 "dhcp4_parser.cc"
    break;

  case 783: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2740 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4359 "dhcp4_parser.cc"
    break;

  case 784: // $@122: %empty
#line 2746 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4369 "dhcp4_parser.cc"
    break;

  case 785: // sub_config_control: "{" $@122 config_control_params "}"
#line 2750 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4378 "dhcp4_parser.cc"
    break;

  case 788: // config_control_params: config_control_params ","
#line 2758 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4386 "dhcp4_parser.cc"
    break;

  case 791: // $@123: %empty
#line 2768 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 792: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2774 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4407 "dhcp4_parser.cc"
    break;

  case 793: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2779 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4417 "dhcp4_parser.cc"
    break;

  case 794: // $@124: %empty
#line 2787 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4429 "dhcp4_parser.cc"
    break;

  case 795: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2793 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4438 "dhcp4_parser.cc"
    break;

  case 798: // loggers_entries: loggers_entries ","
#line 2802 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4446 "dhcp4_parser.cc"
    break;

  case 799: // $@125: %empty
#line 2808 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4456 "dhcp4_parser.cc"
    break;

  case 800: // logger_entry: "{" $@125 logger_params "}"
#line 2812 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4464 "dhcp4_parser.cc"
    break;

  case 803: // logger_params: logger_params ","
#line 2818 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4472 "dhcp4_parser.cc"
    break;

  case 811: // debuglevel: "debuglevel" ":" "integer"
#line 2832 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 812: // $@126: %empty
#line 2838 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4491 "dhcp4_parser.cc"
    break;

  case 813: // severity: "severity" $@126 ":" "constant string"
#line 2841 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4501 "dhcp4_parser.cc"
    break;

  case 814: // $@127: %empty
#line 2847 "dhcp4_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4513 "dhcp4_parser.cc"
    break;

  case 815: // output_options_list: "output-options" $@127 ":" "[" output_options_list_content "]"
#line 2853 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4522 "dhcp4_parser.cc"
    break;

  case 818: // output_options_list_content: output_options_list_content ","
#line 2860 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4530 "dhcp4_parser.cc"
    break;

  case 819: // $@128: %empty
#line 2865 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4540 "dhcp4_parser.cc"
    break;

  case 820: // output_entry: "{" $@128 output_params_list "}"
#line 2869 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4548 "dhcp4_parser.cc"
    break;

  case 823: // output_params_list: output_params_list ","
#line 2875 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4556 "dhcp4_parser.cc"
    break;

  case 829: // $@129: %empty
#line 2887 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4565 "dhcp4_parser.cc"
    break;

  case 830: // output: "output" $@129 ":" "constant string"
#line 2890 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4575 "dhcp4_parser.cc"
    break;

  case 831: // flush: "flush" ":" "boolean"
#line 2896 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4585 "dhcp4_parser.cc"
    break;

  case 832: // maxsize: "maxsize" ":" "integer"
#line 2902 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4595 "dhcp4_parser.cc"
    break;

  case 833: // maxver: "maxver" ":" "integer"
#line 2908 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4605 "dhcp4_parser.cc"
    break;

  case 834: // $@130: %empty
#line 2914 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4614 "dhcp4_parser.cc"
    break;

  case 835: // pattern: "pattern" $@130 ":" "constant string"
#line 2917 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4624 "dhcp4_parser.cc"
    break;

  case 836: // $@131: %empty
#line 2923 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4636 "dhcp4_parser.cc"
    break;

  case 837: // compatibility: "compatibility" $@131 ":" "{" compatibility_params "}"
#line 2929 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4645 "dhcp4_parser.cc"
    break;

  case 840: // compatibility_params: compatibility_params ","
#line 2936 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4653 "dhcp4_parser.cc"
    break;

  case 846: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2948 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4663 "dhcp4_parser.cc"
    break;

  case 847: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 2954 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4673 "dhcp4_parser.cc"
    break;

  case 848: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 2960 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4683 "dhcp4_parser.cc"
    break;

  case 849: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2966 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4693 "dhcp4_parser.cc"
    break;


#line 4697 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -995;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     417,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,    32,    39,    34,    40,    89,    92,
      95,   103,   111,   118,   132,   138,   156,   158,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,    39,  -188,    56,   193,   168,   638,
     -47,   306,   -15,    23,    77,  -116,   254,    60,  -995,    78,
     170,    90,   163,   185,  -995,    47,  -995,  -995,  -995,  -995,
     102,   283,   293,  -995,  -995,  -995,   305,   325,  -995,  -995,
    -995,   349,   351,   353,   354,   356,   357,   358,   360,   363,
     373,   380,  -995,   383,   386,   387,   389,   390,  -995,  -995,
    -995,   391,   395,   396,   397,  -995,  -995,  -995,   403,  -995,
    -995,  -995,  -995,  -995,  -995,   404,   405,   407,  -995,  -995,
    -995,  -995,  -995,   409,  -995,  -995,  -995,  -995,  -995,  -995,
     410,   411,   412,  -995,  -995,   413,  -995,    48,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     416,   418,   434,   435,  -995,    59,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,   436,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,    71,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   437,  -995,
    -995,  -995,  -995,    73,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   245,   288,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   318,  -995,  -995,   439,  -995,
    -995,  -995,   440,  -995,  -995,   320,   449,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     451,   452,   453,  -995,  -995,  -995,  -995,   445,   456,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,    84,  -995,  -995,  -995,   457,  -995,   458,  -995,
     459,   460,  -995,  -995,  -995,  -995,  -995,   109,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   461,   113,
    -995,  -995,  -995,  -995,    39,    39,  -995,  -131,   462,  -995,
    -995,   464,   469,   470,  -132,   201,   255,   473,   476,   477,
     265,   264,   482,   484,   488,   275,   277,   278,   281,   282,
     284,   289,   291,   292,   294,   299,   497,   304,   307,   286,
     308,   309,   498,   510,   515,   312,   315,   317,   321,   522,
     527,   533,   326,   534,   536,   541,   542,   544,   545,   331,
     332,   333,   550,   551,   552,   553,   555,   343,   556,   560,
     564,   565,   566,   568,   355,   359,   361,   569,   570,  -995,
     193,  -995,   572,   573,   576,   367,   371,   374,   375,   168,
    -995,   590,   591,   593,   594,   595,   601,   392,   605,   607,
     608,   638,  -995,   609,   399,   -47,  -995,   611,   630,   631,
     632,   634,   636,   637,   639,  -995,   306,  -995,   641,   642,
     424,   643,   644,   645,   430,  -995,    23,   647,   432,   433,
     438,  -995,    77,   650,   651,    53,  -995,   441,   652,   442,
     655,   444,   446,   659,   661,   254,  -995,   662,   463,    60,
    -995,  -995,  -995,   663,   667,   669,   670,   671,  -995,  -995,
    -995,   466,   467,   468,  -995,  -995,   680,   681,   684,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     474,  -995,  -995,  -995,  -995,  -995,   -24,   475,   478,  -995,
    -995,  -995,  -995,   685,   688,   689,  -995,   479,   263,   696,
     695,   486,   280,  -995,  -995,  -995,   699,   724,   728,   730,
     729,  -995,   731,   732,   733,   734,   520,   525,  -995,  -995,
    -995,   738,   737,  -995,   740,   226,   285,  -995,  -995,  -995,
    -995,  -995,   531,   532,   535,   745,   537,   546,  -995,   740,
     547,   744,  -995,   554,  -995,  -995,   740,   558,   561,   562,
     563,   571,   574,   575,  -995,   577,   578,  -995,   579,   580,
     581,  -995,  -995,   582,  -995,  -995,  -995,  -995,   583,   695,
    -995,  -995,   584,  -995,   585,  -995,  -995,    10,   588,  -995,
     756,  -995,  -995,    39,   193,    60,   168,   319,  -995,  -995,
    -995,  1073,  1073,   755,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,   762,   765,   766,  -995,  -995,  -995,  -995,
    -995,  -995,   770,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,    96,   774,   775,   778,    94,   -53,   -82,   -64,   254,
    -995,  -995,   779,    -3,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   780,  -995,  -995,  -995,  -995,
     646,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   755,  -995,   116,   139,   178,  -995,
    -995,   198,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   785,
     786,   799,   800,   801,   808,   809,   810,   811,   812,  -995,
     813,   814,  -995,  -995,  -995,  -995,  -995,   209,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   210,  -995,   777,   816,  -995,  -995,   815,   817,  -995,
    -995,   819,   823,  -995,  -995,   821,   825,  -995,  -995,   824,
     826,  -995,  -995,  -995,  -995,  -995,  -995,   140,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   166,  -995,  -995,   827,   828,
    -995,  -995,   829,   831,  -995,   818,   832,   833,   834,   835,
     836,   212,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   837,
     838,   849,  -995,   213,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   287,  -995,  -995,  -995,   850,
    -995,   852,  -995,  -995,  -995,   290,  -995,  -995,  -995,  -995,
    -995,   296,  -995,   179,  -995,   864,   865,   866,   867,  -995,
     300,  -995,  -995,  -995,  -995,  -995,   615,  -995,   868,   872,
    -995,  -995,   869,  -995,   870,  -995,  -995,  -995,   874,   875,
     319,  -995,   876,   877,   878,   879,   668,   672,   673,   675,
     679,   682,   683,   691,   692,   693,   883,   686,   697,   884,
     885,   886,   895,  1073,  -995,  -995,  1073,  -995,   755,   638,
    -995,   762,    23,  -995,   765,    77,  -995,   766,   776,  -995,
     770,    96,  -995,   301,   774,  -995,   306,  -995,   775,  -116,
    -995,   778,   698,   700,   701,   702,   703,   705,    94,  -995,
     687,   706,   707,   -53,  -995,   898,   909,   -82,  -995,   694,
     913,   708,   923,   -64,  -995,  -995,   195,   779,  -995,   709,
     710,   711,   713,    -3,  -995,  -995,   922,   931,   -47,  -995,
     780,   932,  -995,  -995,   720,   722,  -995,   192,   723,   726,
     741,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   258,  -995,  -995,   746,   748,   758,   759,  -995,   311,
    -995,   322,  -995,   939,  -995,   947,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   324,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,   953,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   964,   970,  -995,  -995,  -995,  -995,  -995,  -995,   972,
    -995,   334,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   761,   764,  -995,  -995,   782,  -995,
      39,  -995,  -995,   979,  -995,  -995,  -995,  -995,  -995,   340,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   793,   342,  -995,   740,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,   776,  -995,   999,  1007,
     796,  -995,   301,  -995,  -995,  -995,  -995,  -995,  -995,  1009,
     802,  1014,   195,  -995,  -995,  -995,  -995,  -995,   806,   807,
    -995,  -995,  1021,  -995,   830,  -995,  -995,  -995,  1022,  -995,
    -995,   249,  -995,    13,  1022,  -995,  -995,  1027,  1028,  1032,
    -995,   346,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  1044,
     880,   890,   891,  1045,    13,  -995,   887,  -995,  -995,  -995,
     893,  -995,  -995,  -995
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
     752,    25,   784,    27,    46,    39,     0,     0,     0,     0,
       0,   637,     0,   535,   574,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   782,   193,   226,
       0,     0,     0,   657,   659,   661,     0,     0,   224,   237,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,     0,     0,   161,   168,
     170,     0,     0,     0,     0,   379,   522,   563,     0,   153,
     174,   466,   622,   624,   459,     0,     0,     0,   312,   684,
     626,   341,   362,     0,   327,   719,   733,   750,   181,   183,
       0,     0,     0,   794,   836,     0,   138,     0,    67,    70,
      71,    72,    73,    74,   108,   109,   110,   111,   112,    75,
     103,   134,   135,    92,    93,    94,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   114,   115,   126,   127,
     128,   130,   131,   132,   136,   137,    78,    79,   100,    80,
      81,    82,   129,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   133,   210,   212,   216,
       0,     0,     0,     0,   207,     0,   195,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   444,   446,   448,   597,
     442,   450,     0,   454,   452,   679,   441,   393,   394,   395,
     396,   397,   421,   422,   423,   424,   425,   439,   411,   412,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   440,     0,   390,   400,   416,   417,   418,
     401,   403,   404,   407,   408,   409,   406,   402,   398,   399,
     419,   420,   405,   413,   414,   415,   410,   619,     0,   618,
     614,   615,   613,     0,   608,   611,   612,   616,   617,   677,
     663,   665,   667,   671,   669,   675,   673,   656,   650,   654,
     655,     0,   638,   639,   651,   652,   653,   647,   642,   648,
     644,   645,   646,   649,   643,     0,   553,   286,     0,   557,
     555,   560,     0,   549,   550,     0,   536,   537,   540,   552,
     541,   542,   543,   559,   544,   545,   546,   547,   548,   590,
       0,     0,     0,   588,   589,   592,   593,     0,   575,   576,
     579,   580,   581,   582,   583,   584,   585,   586,   587,   358,
     360,   355,     0,   352,   356,   357,     0,   769,     0,   772,
       0,     0,   776,   780,   767,   765,   766,     0,   754,   757,
     758,   759,   760,   761,   762,   763,   764,   791,     0,     0,
     786,   789,   790,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      69,    66,     0,     0,     0,     0,     0,     0,     0,   197,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   392,   389,     0,     0,   610,   607,     0,     0,     0,
       0,     0,     0,     0,     0,   636,   641,   525,     0,     0,
       0,     0,     0,     0,     0,   534,   539,     0,     0,     0,
       0,   573,   578,     0,     0,   354,   351,     0,     0,     0,
       0,     0,     0,     0,     0,   756,   753,     0,     0,   788,
     785,    49,    41,     0,     0,     0,     0,     0,   155,   156,
     157,     0,     0,     0,   191,   192,     0,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
       0,   186,   187,   158,   159,   160,     0,     0,     0,   172,
     173,   180,   185,     0,     0,     0,   152,     0,     0,     0,
       0,     0,     0,   456,   457,   458,     0,     0,     0,     0,
       0,   718,     0,     0,     0,     0,     0,     0,   188,   189,
     190,     0,     0,    68,     0,     0,     0,   220,   221,   222,
     223,   196,     0,     0,     0,     0,     0,     0,   465,     0,
       0,     0,   391,     0,   621,   609,     0,     0,     0,     0,
       0,     0,     0,     0,   640,     0,     0,   551,     0,     0,
       0,   562,   538,     0,   594,   595,   596,   577,     0,     0,
     353,   768,     0,   771,     0,   774,   775,     0,     0,   755,
       0,   793,   787,     0,     0,     0,     0,     0,   658,   660,
     662,     0,     0,   241,   151,   163,   164,   165,   166,   167,
     162,   169,   171,   381,   526,   565,   154,   176,   177,   178,
     179,   175,   468,    38,   623,   625,   461,   462,   463,   464,
     460,     0,     0,   628,   343,     0,     0,     0,     0,     0,
     182,   184,     0,     0,    51,   211,   214,   215,   213,   218,
     219,   217,   445,   447,   449,   599,   443,   451,   455,   453,
       0,   620,   678,   664,   666,   668,   672,   670,   676,   674,
     554,   287,   558,   556,   561,   591,   359,   361,   770,   773,
     778,   779,   777,   781,   241,    42,     0,     0,     0,   233,
     235,     0,   228,   231,   232,   274,   279,   281,   283,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   297,
       0,     0,   304,   306,   308,   310,   273,     0,   248,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,     0,   246,     0,   242,   243,   386,     0,   382,   383,
     531,     0,   527,   528,   570,     0,   566,   567,   473,     0,
     469,   470,   322,   323,   324,   325,   326,     0,   314,   317,
     318,   319,   320,   321,   689,     0,   686,   633,     0,   629,
     630,   348,     0,   344,   345,     0,     0,     0,     0,     0,
       0,     0,   364,   367,   368,   369,   370,   371,   372,     0,
       0,     0,   337,     0,   329,   332,   333,   334,   335,   336,
     729,   731,   728,   726,   727,     0,   721,   724,   725,     0,
     745,     0,   748,   741,   742,     0,   735,   738,   739,   740,
     743,     0,   799,     0,   796,     0,     0,     0,     0,   845,
       0,   838,   841,   842,   843,   844,    53,   604,     0,   600,
     601,   682,     0,   681,     0,    62,   783,   194,     0,     0,
     230,   227,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   225,   238,     0,   240,   245,     0,
     380,   385,   535,   523,   530,   574,   564,   569,     0,   467,
     472,   316,   313,   691,   688,   685,   637,   627,   632,     0,
     342,   347,     0,     0,     0,     0,     0,     0,   366,   363,
       0,     0,     0,   331,   328,     0,     0,   723,   720,     0,
       0,     0,     0,   737,   734,   751,     0,   798,   795,     0,
       0,     0,     0,   840,   837,    55,     0,    54,     0,   598,
     603,     0,   680,   792,     0,     0,   229,     0,     0,     0,
       0,   285,   288,   289,   290,   291,   292,   293,   294,   295,
     296,     0,   302,   303,     0,     0,     0,     0,   249,     0,
     244,     0,   384,     0,   529,     0,   568,   521,   496,   497,
     498,   481,   482,   501,   502,   503,   504,   505,   519,   484,
     485,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   520,   478,   479,   480,   494,   495,
     491,   492,   493,   490,     0,   475,   483,   499,   500,   486,
     487,   488,   489,   471,   315,   713,   715,     0,   707,   708,
     709,   710,   711,   712,   700,   701,   705,   706,   702,   703,
     704,     0,   692,   693,   696,   697,   698,   699,   687,     0,
     631,     0,   346,   373,   374,   375,   376,   377,   378,   365,
     338,   339,   340,   330,     0,     0,   722,   744,     0,   747,
       0,   736,   814,     0,   812,   810,   804,   808,   809,     0,
     801,   806,   807,   805,   797,   846,   847,   848,   849,   839,
      52,    57,     0,   602,     0,   234,   236,   276,   277,   278,
     275,   280,   282,   284,   299,   300,   301,   298,   305,   307,
     309,   311,   247,   387,   532,   571,   477,   474,     0,     0,
       0,   690,   695,   634,   349,   730,   732,   746,   749,     0,
       0,     0,   803,   800,    56,   605,   683,   476,     0,     0,
     717,   694,     0,   811,     0,   802,   714,   716,     0,   813,
     819,     0,   816,     0,   818,   815,   829,     0,     0,     0,
     834,     0,   821,   824,   825,   826,   827,   828,   817,     0,
       0,     0,     0,     0,   823,   820,     0,   831,   832,   833,
       0,   822,   830,   835
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   -59,  -995,  -589,  -995,   362,
    -995,  -995,  -995,  -995,  -995,  -995,  -643,  -995,  -995,  -995,
     -67,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   398,   603,
      42,    44,    45,   -54,   -39,    -1,     9,    29,    57,    61,
    -995,  -995,  -995,  -995,    62,  -995,  -995,    63,    64,    65,
      67,    68,    69,  -995,  -995,    75,  -995,    79,  -995,    80,
      81,    82,  -995,  -995,    83,    85,  -995,    86,  -995,    87,
    -995,  -995,  -995,  -995,  -995,    46,  -995,  -995,  -995,   406,
     602,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     144,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   338,
    -995,   117,  -995,  -700,   123,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   -13,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,   122,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   107,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   120,
    -995,  -995,  -995,   124,   587,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,   119,  -995,  -995,  -995,  -995,  -995,  -995,  -994,
    -995,  -995,  -995,   143,  -995,  -995,  -995,   146,   625,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -991,  -995,   -18,
    -995,    91,  -995,    93,    97,    98,    99,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   141,  -995,  -995,   -88,   -62,  -995,
    -995,  -995,  -995,  -995,   148,  -995,  -995,  -995,   151,  -995,
     604,  -995,   -63,  -995,  -995,  -995,  -995,  -995,   -61,  -995,
    -995,  -995,  -995,  -995,   -12,  -995,  -995,  -995,   147,  -995,
    -995,  -995,   150,  -995,   606,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,   100,  -995,  -995,
    -995,   101,   640,  -995,  -995,  -995,   -49,  -995,   -31,  -995,
     -51,  -995,  -995,  -995,   145,  -995,  -995,  -995,   152,  -995,
     620,     6,  -995,    22,  -995,    26,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -982,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   153,  -995,  -995,  -995,   -85,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,   125,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   121,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   422,   596,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   471,   597,  -995,  -995,  -995,  -995,
    -995,  -995,   126,  -995,  -995,   -80,  -995,  -995,  -995,  -995,
    -995,  -995,  -100,  -995,  -995,  -117,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,   128,  -995,  -995,  -995,
    -995
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   734,
      82,    83,    39,    64,    79,    80,   755,   956,  1056,  1057,
     826,    41,    66,    85,   428,    86,    43,    67,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   456,   171,   172,   473,   173,   174,   175,   176,
     177,   178,   179,   462,   720,   180,   463,   181,   464,   182,
     183,   184,   474,   731,   185,   186,   492,   187,   493,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   432,   235,
     236,    45,    68,   237,   502,   238,   503,   758,   239,   504,
     761,   240,   241,   242,   243,   197,   442,   198,   433,   801,
     802,   803,   968,   804,   969,   199,   443,   200,   444,   853,
     854,   855,   996,   827,   828,   829,   972,  1220,   830,   973,
     831,   974,   832,   975,   833,   834,   539,   835,   836,   837,
     838,   839,   840,   841,   842,   843,   844,   986,  1227,   845,
     846,   847,   989,   848,   990,   849,   991,   850,   992,   201,
     482,   877,   878,   879,   880,   881,   882,   883,   202,   488,
     913,   914,   915,   916,   917,   203,   485,   892,   893,   894,
    1019,    59,    75,   392,   393,   394,   553,   395,   554,   204,
     486,   901,   902,   903,   904,   905,   906,   907,   908,   205,
     469,   857,   858,   859,   999,    47,    69,   284,   285,   286,
     515,   287,   511,   288,   512,   289,   513,   290,   516,   291,
     519,   292,   518,   206,   207,   208,   209,   478,   740,   297,
     210,   475,   869,   870,   871,  1008,  1134,  1135,   211,   470,
      53,    72,   861,   862,   863,  1002,    55,    73,   355,   356,
     357,   358,   359,   360,   361,   538,   362,   542,   363,   541,
     364,   365,   543,   366,   212,   471,   865,   866,   867,  1005,
      57,    74,   377,   378,   379,   380,   381,   547,   382,   383,
     384,   385,   386,   299,   514,   958,   959,   960,  1058,    49,
      70,   313,   314,   315,   523,   316,   213,   476,   214,   477,
     215,   484,   888,   889,   890,  1016,    51,    71,   331,   332,
     333,   216,   437,   217,   438,   218,   439,   337,   528,   338,
     529,   339,   530,   340,   532,   341,   531,   342,   534,   343,
     533,   344,   527,   306,   520,   962,   963,  1061,   219,   483,
     885,   886,  1013,  1161,  1162,  1163,  1164,  1165,  1238,  1166,
    1239,  1167,   220,   221,   489,   925,   926,   927,  1035,   928,
    1036,   222,   490,   935,   936,   937,   938,  1040,   939,   940,
    1042,   223,   491,    61,    76,   407,   408,   409,   410,   558,
     411,   412,   560,   413,   414,   415,   563,   792,   416,   564,
     224,   431,    63,    77,   419,   420,   421,   567,   422,   225,
     497,   943,   944,  1046,  1199,  1200,  1201,  1202,  1251,  1203,
    1249,  1271,  1272,  1273,  1281,  1282,  1283,  1289,  1284,  1285,
    1286,  1287,  1293,   226,   498,   950,   951,   952,   953,   954,
     955
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     156,   234,   256,   309,   327,    78,   353,   373,   391,   404,
     345,   375,   851,   376,  1126,   260,   768,  1127,   302,   244,
     300,   317,   329,   772,   367,   387,  1142,   405,   790,    81,
     261,   733,    28,   389,   390,   132,   133,   245,   301,   318,
     330,    40,   368,   388,    29,   406,    30,    42,    31,   127,
     429,   500,   310,   132,   133,   430,   501,   298,   312,   328,
     354,   374,   509,   346,   132,   133,    84,   510,   262,   307,
     132,   133,   417,   418,   521,   303,   525,   334,   263,   522,
     126,   526,   920,   921,   423,   253,   573,   555,   578,   254,
     308,   304,   556,   335,   425,   305,    44,   336,   264,    46,
     733,   155,    48,   929,   930,   931,   434,   909,   910,   911,
      50,   257,   565,   258,   259,   283,   569,   566,    52,   500,
     347,   570,   348,   349,   965,    54,   265,   350,   351,   352,
     266,   267,   268,   269,   270,   155,   271,   272,   273,    56,
     132,   133,   569,  1011,   274,    58,  1012,   966,   275,   276,
     277,   278,   279,   932,   280,   281,   282,   715,   716,   717,
     718,   311,   293,    60,   155,    62,   294,   295,   296,  1014,
     155,   426,  1015,   424,   347,   369,   348,   349,   370,   371,
     372,   509,  1047,   227,   228,  1048,   967,   229,   427,   791,
     230,   231,   232,   233,   132,   133,   719,   945,   946,   947,
     948,   970,   389,   390,    87,  1276,   971,    88,  1277,  1278,
    1279,  1280,   993,   993,   155,  1028,  1033,   994,   995,    89,
    1029,  1034,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,  1217,  1218,  1219,   872,   873,   874,   875,
     155,   876,  1126,   756,   757,  1127,   895,   896,   897,   898,
     899,   900,  1274,   535,  1142,  1275,    32,    33,    34,    35,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   132,   133,   435,   126,   127,
    1037,   536,   347,  1043,   155,  1038,  1089,   436,  1044,   565,
     128,   129,   130,  1053,  1045,   759,   760,   131,  1054,   440,
     132,   133,   132,   133,   993,   134,  1224,  1225,  1226,  1232,
     135,   136,   137,   138,   139,   521,   537,  1236,   545,   441,
    1233,   140,  1237,    93,    94,    95,    96,   555,    93,    94,
      95,   141,  1244,  1252,   142,   525,   799,   800,  1253,  1294,
    1255,   143,   144,   445,  1295,   446,   145,   447,   448,   146,
     449,   450,   451,   147,   452,   571,   572,   453,   101,   102,
     103,   132,   133,   727,   728,   729,   730,   454,   148,   149,
     150,   151,   152,   153,   455,   155,  1192,   457,  1193,  1194,
     458,   459,   154,   460,   461,   465,   126,   127,   347,   466,
     467,   468,   127,   736,   737,   738,   739,   472,   479,   480,
     155,   481,   155,   487,   494,   495,   496,   499,   132,   133,
     505,   579,   506,   132,   133,   396,   397,   398,   399,   400,
     401,   402,   403,   156,  1145,  1146,  1147,   319,   507,   508,
     517,   524,   234,   540,   544,   320,   321,   322,   323,   324,
     325,   326,   546,   551,   256,   548,   549,   550,   309,   552,
     244,   557,   559,   561,   562,   568,   574,   260,   575,   327,
     302,   155,   300,   576,   577,   580,   317,   581,   245,   353,
     582,   583,   261,   584,   585,   373,   586,   329,   587,   375,
     301,   376,   588,   589,   318,   590,   591,   367,   404,   592,
     593,   600,   606,   387,   594,   330,   603,   310,   595,   298,
     596,   597,   598,   312,   607,   368,   405,   599,   155,   608,
     262,   388,   601,   155,   328,   602,   613,   303,   604,   605,
     263,   614,   609,   354,   406,   610,   611,   615,   617,   374,
     618,   612,   334,   304,   616,   619,   620,   305,   621,   622,
     264,   623,   624,   625,   626,   627,   628,   629,   335,   630,
     632,   631,   336,   257,   633,   258,   259,   283,   634,   635,
     636,  1256,   637,   641,   642,   638,   644,   645,   265,   639,
     646,   640,   266,   267,   268,   269,   270,   647,   271,   272,
     273,   648,   649,   650,   652,   653,   274,   654,   655,   656,
     275,   276,   277,   278,   279,   657,   280,   281,   282,   659,
     658,   660,   661,   663,   293,   666,   311,   664,   294,   295,
     296,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   667,   668,   669,   156,   670,   234,
     671,   672,   677,   673,   795,   675,   676,   678,   679,   680,
     681,   683,   684,   685,   688,   689,   692,   244,   686,   694,
     693,   691,   695,   697,   696,   698,   700,   703,    91,    92,
      93,    94,    95,    96,   704,   245,   705,   706,   707,   912,
     922,   701,   404,   708,   709,   710,   949,   711,   712,   713,
     723,   714,   721,   724,   725,   722,   726,   918,   923,   933,
     405,   732,    30,   735,   741,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   919,   924,   934,   406,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   742,
     246,   247,   248,   743,   127,   744,   745,   750,   746,   747,
     748,   749,   751,   752,   753,   754,   129,   130,   762,   763,
     765,   770,   764,   249,   766,   132,   133,   250,   251,   252,
     134,   794,   852,   767,   769,   135,   136,   137,   793,   856,
     253,   771,   860,   864,   254,   773,   140,   868,   774,   775,
     776,   884,   887,   997,   255,   891,   942,   957,   777,   976,
     977,   778,   779,   961,   780,   781,   782,   783,   784,   785,
     786,   788,   789,   978,   979,   980,    91,    92,    93,    94,
      95,    96,   981,   982,   983,   984,   985,   987,   988,   998,
    1001,  1000,  1022,   148,   149,  1003,  1004,  1006,  1007,  1010,
    1009,  1018,  1055,  1017,  1021,  1020,  1023,  1024,  1025,  1026,
    1027,  1030,  1031,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,  1032,  1039,   155,  1041,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,  1049,  1050,
    1051,  1052,   127,   347,  1059,  1060,  1063,  1062,  1064,  1065,
    1067,  1068,  1069,  1070,   129,   130,  1071,  1081,  1084,  1085,
    1086,  1073,  1072,   132,   133,  1074,   251,  1075,   134,  1087,
    1076,  1077,  1184,   135,   136,   137,  1082,  1180,   253,  1078,
    1079,  1080,   254,  1185,  1187,  1083,  1173,  1188,  1174,  1175,
    1176,  1177,   255,  1178,  1181,  1182,  1189,  1190,  1210,  1205,
    1206,  1207,   256,  1208,  1211,   353,  1214,  1215,   373,  1216,
    1221,  1097,   375,  1222,   376,   260,  1148,  1234,   302,   327,
     300,  1154,   391,   367,  1101,  1235,   387,  1240,  1223,  1137,
     261,   148,   149,  1228,  1156,  1229,   912,   329,   301,  1102,
     922,   368,  1241,  1242,   388,  1230,  1231,  1138,  1245,  1195,
    1243,  1246,  1157,  1250,   918,   330,   949,   298,   923,   354,
    1128,   309,   374,   155,   933,  1125,  1136,  1197,   262,  1247,
    1153,  1155,   919,  1258,   328,   303,   924,  1103,   263,   317,
    1254,  1259,   934,  1262,  1139,  1198,  1260,  1104,  1264,  1158,
    1263,   304,   334,  1266,  1267,   305,  1268,   318,   264,  1270,
    1140,  1290,  1291,  1196,  1141,  1159,  1292,  1105,   335,  1160,
     310,   257,   336,   258,   259,   283,   312,  1269,  1296,  1300,
    1098,   787,  1099,  1100,  1124,  1149,   265,  1150,  1151,  1152,
     266,   267,   268,   269,   270,  1106,   271,   272,   273,  1107,
    1108,  1109,  1110,  1111,   274,  1112,  1113,  1114,   275,   276,
     277,   278,   279,  1115,   280,   281,   282,  1116,  1117,  1118,
    1119,  1120,   293,  1121,  1122,  1123,   294,   295,   296,  1129,
    1297,  1130,   796,   643,  1302,  1131,  1132,  1133,  1298,  1299,
    1303,   651,   798,   805,  1066,  1090,  1088,   806,   807,   808,
     809,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,  1248,   964,  1144,   820,   821,   822,   823,   824,   825,
    1183,  1172,   690,  1171,  1092,  1091,   662,  1179,  1257,   311,
     682,  1143,  1094,  1093,  1096,  1095,   674,  1261,   687,  1212,
    1213,   699,  1186,  1170,  1191,   665,   702,  1168,  1169,  1097,
     347,   941,  1265,  1204,  1288,  1148,   797,  1301,     0,     0,
    1154,  1209,  1101,     0,     0,  1195,     0,  1137,     0,     0,
       0,     0,     0,  1156,     0,     0,     0,  1102,     0,     0,
       0,     0,     0,  1197,     0,  1138,     0,     0,     0,     0,
       0,  1157,     0,     0,     0,     0,     0,     0,  1128,     0,
       0,  1198,     0,  1125,  1136,     0,     0,     0,     0,  1153,
    1155,     0,     0,     0,     0,  1103,     0,     0,     0,  1196,
       0,     0,  1139,     0,     0,  1104,     0,     0,  1158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1140,     0,
       0,     0,  1141,     0,  1159,  1105,     0,     0,  1160,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1098,     0,
    1099,  1100,  1124,     0,  1149,     0,  1150,  1151,  1152,     0,
     155,     0,     0,  1106,     0,     0,     0,  1107,  1108,  1109,
    1110,  1111,     0,  1112,  1113,  1114,     0,     0,     0,     0,
       0,  1115,     0,     0,     0,  1116,  1117,  1118,  1119,  1120,
       0,  1121,  1122,  1123,     0,     0,     0,  1129,     0,  1130,
       0,     0,     0,  1131,  1132,  1133
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    64,    73,    74,    75,    76,
      72,    74,   712,    74,  1008,    69,   659,  1008,    69,    68,
      69,    70,    71,   666,    73,    74,  1008,    76,    18,   217,
      69,   620,     0,   149,   150,   117,   118,    68,    69,    70,
      71,     7,    73,    74,     5,    76,     7,     7,     9,    96,
       3,     3,    70,   117,   118,     8,     8,    69,    70,    71,
      73,    74,     3,    40,   117,   118,    10,     8,    69,   116,
     117,   118,    12,    13,     3,    69,     3,    71,    69,     8,
      95,     8,   164,   165,     6,   132,   217,     3,   220,   136,
     137,    69,     8,    71,     4,    69,     7,    71,    69,     7,
     689,   217,     7,   167,   168,   169,     4,   160,   161,   162,
       7,    69,     3,    69,    69,    69,     3,     8,     7,     3,
      97,     8,    99,   100,     8,     7,    69,   104,   105,   106,
      69,    69,    69,    69,    69,   217,    69,    69,    69,     7,
     117,   118,     3,     3,    69,     7,     6,     8,    69,    69,
      69,    69,    69,   217,    69,    69,    69,   181,   182,   183,
     184,    70,    69,     7,   217,     7,    69,    69,    69,     3,
     217,     8,     6,     3,    97,    98,    99,   100,   101,   102,
     103,     3,     3,    15,    16,     6,     8,    19,     3,   179,
      22,    23,    24,    25,   117,   118,   220,   200,   201,   202,
     203,     3,   149,   150,    11,   192,     8,    14,   195,   196,
     197,   198,     3,     3,   217,     3,     3,     8,     8,    26,
       8,     8,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    41,    42,    43,   140,   141,   142,   143,
     217,   145,  1236,    17,    18,  1236,   152,   153,   154,   155,
     156,   157,     3,     8,  1236,     6,   217,   218,   219,   220,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,   117,   118,     4,    95,    96,
       3,     3,    97,     3,   217,     8,   996,     4,     8,     3,
     107,   108,   109,     3,     8,    20,    21,   114,     8,     4,
     117,   118,   117,   118,     3,   122,    58,    59,    60,     8,
     127,   128,   129,   130,   131,     3,     8,     3,     8,     4,
       8,   138,     8,    32,    33,    34,    35,     3,    32,    33,
      34,   148,     8,     3,   151,     3,    27,    28,     8,     3,
       8,   158,   159,     4,     8,     4,   163,     4,     4,   166,
       4,     4,     4,   170,     4,   424,   425,     4,    67,    68,
      69,   117,   118,   110,   111,   112,   113,     4,   185,   186,
     187,   188,   189,   190,     4,   217,   191,     4,   193,   194,
       4,     4,   199,     4,     4,     4,    95,    96,    97,     4,
       4,     4,    96,   123,   124,   125,   126,     4,     4,     4,
     217,     4,   217,     4,     4,     4,     4,     4,   117,   118,
       4,   220,     4,   117,   118,   171,   172,   173,   174,   175,
     176,   177,   178,   500,   133,   134,   135,   131,     4,     4,
       4,     4,   509,     4,     4,   139,   140,   141,   142,   143,
     144,   145,     3,     8,   521,     4,     4,     4,   525,     3,
     509,     4,     4,     4,     4,     4,     4,   521,     4,   536,
     521,   217,   521,     4,     4,   220,   525,     4,   509,   546,
       4,     4,   521,   218,   220,   552,     4,   536,     4,   552,
     521,   552,     4,   218,   525,   218,   218,   546,   565,   218,
     218,     4,     4,   552,   220,   536,   220,   525,   219,   521,
     219,   219,   218,   525,     4,   546,   565,   218,   217,     4,
     521,   552,   218,   217,   536,   218,     4,   521,   220,   220,
     521,     4,   220,   546,   565,   220,   219,     4,     4,   552,
       4,   220,   536,   521,   218,     4,     4,   521,     4,     4,
     521,   220,   220,   220,     4,     4,     4,     4,   536,     4,
       4,   218,   536,   521,     4,   521,   521,   521,     4,     4,
       4,  1214,     4,     4,     4,   220,     4,     4,   521,   220,
       4,   220,   521,   521,   521,   521,   521,   220,   521,   521,
     521,   220,   218,   218,     4,     4,   521,     4,     4,     4,
     521,   521,   521,   521,   521,     4,   521,   521,   521,     4,
     218,     4,     4,     4,   521,     4,   525,   218,   521,   521,
     521,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,     4,     4,     4,   704,     4,   706,
       4,     4,   218,     4,   703,     4,     4,     4,     4,     4,
     220,     4,   220,   220,     4,     4,     4,   706,   220,     4,
     218,   220,   218,     4,   218,     4,     4,     4,    30,    31,
      32,    33,    34,    35,     7,   706,     7,     7,     7,   746,
     747,   218,   749,   217,   217,   217,   753,     7,     7,     5,
       5,   217,   217,     5,     5,   217,   217,   746,   747,   748,
     749,     5,     7,   217,     5,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,   746,   747,   748,   749,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     5,
      92,    93,    94,     5,    96,     5,     7,   217,     7,     7,
       7,     7,   217,     5,     7,     5,   108,   109,   217,   217,
       5,     7,   217,   115,   217,   117,   118,   119,   120,   121,
     122,     5,     7,   217,   217,   127,   128,   129,   180,     7,
     132,   217,     7,     7,   136,   217,   138,     7,   217,   217,
     217,     7,     7,     6,   146,     7,     7,     7,   217,     4,
       4,   217,   217,   147,   217,   217,   217,   217,   217,   217,
     217,   217,   217,     4,     4,     4,    30,    31,    32,    33,
      34,    35,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     6,     4,   185,   186,     6,     3,     6,     3,     3,
       6,     3,   217,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     4,     4,   217,     4,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,     4,     4,
       4,     4,    96,    97,     6,     3,     6,     8,     4,     4,
       4,     4,     4,     4,   108,   109,   218,     4,     4,     4,
       4,   218,   220,   117,   118,   220,   120,   218,   122,     4,
     218,   218,     4,   127,   128,   129,   220,   220,   132,   218,
     218,   218,   136,     4,   220,   218,   218,     4,   218,   218,
     218,   218,   146,   218,   218,   218,   218,     4,     6,   220,
     220,   220,   999,   220,     3,  1002,     4,   217,  1005,   217,
     217,  1008,  1005,   217,  1005,   999,  1013,     8,   999,  1016,
     999,  1013,  1019,  1002,  1008,     8,  1005,     4,   217,  1008,
     999,   185,   186,   217,  1013,   217,  1033,  1016,   999,  1008,
    1037,  1002,     8,     3,  1005,   217,   217,  1008,   217,  1046,
       8,   217,  1013,     4,  1033,  1016,  1053,   999,  1037,  1002,
    1008,  1058,  1005,   217,  1043,  1008,  1008,  1046,   999,   217,
    1013,  1013,  1033,     4,  1016,   999,  1037,  1008,   999,  1058,
     217,     4,  1043,     4,  1008,  1046,   220,  1008,     4,  1013,
     218,   999,  1016,   217,   217,   999,     5,  1058,   999,     7,
    1008,     4,     4,  1046,  1008,  1013,     4,  1008,  1016,  1013,
    1058,   999,  1016,   999,   999,   999,  1058,   217,     4,     4,
    1008,   689,  1008,  1008,  1008,  1013,   999,  1013,  1013,  1013,
     999,   999,   999,   999,   999,  1008,   999,   999,   999,  1008,
    1008,  1008,  1008,  1008,   999,  1008,  1008,  1008,   999,   999,
     999,   999,   999,  1008,   999,   999,   999,  1008,  1008,  1008,
    1008,  1008,   999,  1008,  1008,  1008,   999,   999,   999,  1008,
     220,  1008,   704,   500,   217,  1008,  1008,  1008,   218,   218,
     217,   509,   706,    40,   970,   998,   993,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,  1190,   794,  1011,    61,    62,    63,    64,    65,    66,
    1033,  1021,   555,  1019,  1001,   999,   521,  1028,  1236,  1058,
     546,  1010,  1004,  1002,  1007,  1005,   536,  1242,   552,  1058,
    1060,   565,  1037,  1018,  1043,   525,   569,  1014,  1016,  1236,
      97,   749,  1252,  1047,  1274,  1242,   705,  1294,    -1,    -1,
    1242,  1053,  1236,    -1,    -1,  1252,    -1,  1236,    -1,    -1,
      -1,    -1,    -1,  1242,    -1,    -1,    -1,  1236,    -1,    -1,
      -1,    -1,    -1,  1252,    -1,  1236,    -1,    -1,    -1,    -1,
      -1,  1242,    -1,    -1,    -1,    -1,    -1,    -1,  1236,    -1,
      -1,  1252,    -1,  1236,  1236,    -1,    -1,    -1,    -1,  1242,
    1242,    -1,    -1,    -1,    -1,  1236,    -1,    -1,    -1,  1252,
      -1,    -1,  1236,    -1,    -1,  1236,    -1,    -1,  1242,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1236,    -1,
      -1,    -1,  1236,    -1,  1242,  1236,    -1,    -1,  1242,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1236,    -1,
    1236,  1236,  1236,    -1,  1242,    -1,  1242,  1242,  1242,    -1,
     217,    -1,    -1,  1236,    -1,    -1,    -1,  1236,  1236,  1236,
    1236,  1236,    -1,  1236,  1236,  1236,    -1,    -1,    -1,    -1,
      -1,  1236,    -1,    -1,    -1,  1236,  1236,  1236,  1236,  1236,
      -1,  1236,  1236,  1236,    -1,    -1,    -1,  1236,    -1,  1236,
      -1,    -1,    -1,  1236,  1236,  1236
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,     0,     5,
       7,     9,   217,   218,   219,   220,   236,   237,   238,   243,
       7,   252,     7,   257,     7,   312,     7,   426,     7,   510,
       7,   527,     7,   461,     7,   467,     7,   491,     7,   402,
       7,   594,     7,   613,   244,   239,   253,   258,   313,   427,
     511,   528,   462,   468,   492,   403,   595,   614,   236,   245,
     246,   217,   241,   242,    10,   254,   256,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    95,    96,   107,   108,
     109,   114,   117,   118,   122,   127,   128,   129,   130,   131,
     138,   148,   151,   158,   159,   163,   166,   170,   185,   186,
     187,   188,   189,   190,   199,   217,   251,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   274,   275,   277,   278,   279,   280,   281,   282,   283,
     286,   288,   290,   291,   292,   295,   296,   298,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   326,   328,   336,
     338,   380,   389,   396,   410,   420,   444,   445,   446,   447,
     451,   459,   485,   517,   519,   521,   532,   534,   536,   559,
     573,   574,   582,   592,   611,   620,   644,    15,    16,    19,
      22,    23,    24,    25,   251,   310,   311,   314,   316,   319,
     322,   323,   324,   325,   517,   519,    92,    93,    94,   115,
     119,   120,   121,   132,   136,   146,   251,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   275,   278,   279,
     280,   281,   282,   283,   286,   288,   290,   291,   292,   295,
     296,   298,   300,   306,   428,   429,   430,   432,   434,   436,
     438,   440,   442,   444,   445,   446,   447,   450,   485,   504,
     517,   519,   521,   532,   534,   536,   554,   116,   137,   251,
     440,   442,   485,   512,   513,   514,   516,   517,   519,   131,
     139,   140,   141,   142,   143,   144,   145,   251,   485,   517,
     519,   529,   530,   531,   532,   534,   536,   538,   540,   542,
     544,   546,   548,   550,   552,   459,    40,    97,    99,   100,
     104,   105,   106,   251,   356,   469,   470,   471,   472,   473,
     474,   475,   477,   479,   481,   482,   484,   517,   519,    98,
     101,   102,   103,   251,   356,   473,   479,   493,   494,   495,
     496,   497,   499,   500,   501,   502,   503,   517,   519,   149,
     150,   251,   404,   405,   406,   408,   171,   172,   173,   174,
     175,   176,   177,   178,   251,   517,   519,   596,   597,   598,
     599,   601,   602,   604,   605,   606,   609,    12,    13,   615,
     616,   617,   619,     6,     3,     4,     8,     3,   255,     3,
       8,   612,   309,   329,     4,     4,     4,   533,   535,   537,
       4,     4,   327,   337,   339,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   273,     4,     4,     4,
       4,     4,   284,   287,   289,     4,     4,     4,     4,   421,
     460,   486,     4,   276,   293,   452,   518,   520,   448,     4,
       4,     4,   381,   560,   522,   397,   411,     4,   390,   575,
     583,   593,   297,   299,     4,     4,     4,   621,   645,     4,
       3,     8,   315,   317,   320,     4,     4,     4,     4,     3,
       8,   433,   435,   437,   505,   431,   439,     4,   443,   441,
     555,     3,     8,   515,     4,     3,     8,   553,   539,   541,
     543,   547,   545,   551,   549,     8,     3,     8,   476,   357,
       4,   480,   478,   483,     4,     8,     3,   498,     4,     4,
       4,     8,     3,   407,   409,     3,     8,     4,   600,     4,
     603,     4,     4,   607,   610,     3,     8,   618,     4,     3,
       8,   236,   236,   217,     4,     4,     4,     4,   220,   220,
     220,     4,     4,     4,   218,   220,     4,     4,     4,   218,
     218,   218,   218,   218,   220,   219,   219,   219,   218,   218,
       4,   218,   218,   220,   220,   220,     4,     4,     4,   220,
     220,   219,   220,     4,     4,     4,   218,     4,     4,     4,
       4,     4,     4,   220,   220,   220,     4,     4,     4,     4,
       4,   218,     4,     4,     4,     4,     4,     4,   220,   220,
     220,     4,     4,   260,     4,     4,     4,   220,   220,   218,
     218,   311,     4,     4,     4,     4,     4,     4,   218,     4,
       4,     4,   429,     4,   218,   513,     4,     4,     4,     4,
       4,     4,     4,     4,   531,     4,     4,   218,     4,     4,
       4,   220,   471,     4,   220,   220,   220,   495,     4,     4,
     405,   220,     4,   218,     4,   218,   218,     4,     4,   597,
       4,   218,   616,     4,     7,     7,     7,     7,   217,   217,
     217,     7,     7,     5,   217,   181,   182,   183,   184,   220,
     285,   217,   217,     5,     5,     5,   217,   110,   111,   112,
     113,   294,     5,   238,   240,   217,   123,   124,   125,   126,
     449,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     217,   217,     5,     7,     5,   247,    17,    18,   318,    20,
      21,   321,   217,   217,   217,     5,   217,   217,   247,   217,
       7,   217,   247,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   240,   217,   217,
      18,   179,   608,   180,     5,   236,   259,   615,   310,    27,
      28,   330,   331,   332,   334,    40,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      61,    62,    63,    64,    65,    66,   251,   344,   345,   346,
     349,   351,   353,   355,   356,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   370,   371,   372,   374,   376,
     378,   344,     7,   340,   341,   342,     7,   422,   423,   424,
       7,   463,   464,   465,     7,   487,   488,   489,     7,   453,
     454,   455,   140,   141,   142,   143,   145,   382,   383,   384,
     385,   386,   387,   388,     7,   561,   562,     7,   523,   524,
     525,     7,   398,   399,   400,   152,   153,   154,   155,   156,
     157,   412,   413,   414,   415,   416,   417,   418,   419,   160,
     161,   162,   251,   391,   392,   393,   394,   395,   517,   519,
     164,   165,   251,   517,   519,   576,   577,   578,   580,   167,
     168,   169,   217,   517,   519,   584,   585,   586,   587,   589,
     590,   596,     7,   622,   623,   200,   201,   202,   203,   251,
     646,   647,   648,   649,   650,   651,   248,     7,   506,   507,
     508,   147,   556,   557,   340,     8,     8,     8,   333,   335,
       3,     8,   347,   350,   352,   354,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   368,     4,     4,   373,
     375,   377,   379,     3,     8,     8,   343,     6,     3,   425,
       6,     3,   466,     6,     3,   490,     6,     3,   456,     6,
       3,     3,     6,   563,     3,     6,   526,     6,     3,   401,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   579,   581,     3,     8,     4,
     588,     4,   591,     3,     8,     8,   624,     3,     6,     4,
       4,     4,     4,     3,     8,   217,   249,   250,   509,     6,
       3,   558,     8,     6,     4,     4,   331,     4,     4,     4,
       4,   218,   220,   218,   220,   218,   218,   218,   218,   218,
     218,     4,   220,   218,     4,     4,     4,     4,   345,   344,
     342,   428,   424,   469,   465,   493,   489,   251,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   275,   278,
     279,   280,   281,   282,   283,   286,   288,   290,   291,   292,
     295,   296,   298,   300,   306,   356,   420,   438,   440,   442,
     444,   445,   446,   447,   457,   458,   485,   517,   519,   532,
     534,   536,   554,   455,   383,   133,   134,   135,   251,   261,
     262,   263,   306,   356,   459,   485,   517,   519,   532,   534,
     536,   564,   565,   566,   567,   568,   570,   572,   562,   529,
     525,   404,   400,   218,   218,   218,   218,   218,   218,   413,
     220,   218,   218,   392,     4,     4,   577,   220,     4,   218,
       4,   585,   191,   193,   194,   251,   356,   517,   519,   625,
     626,   627,   628,   630,   623,   220,   220,   220,   220,   647,
       6,     3,   512,   508,     4,   217,   217,    41,    42,    43,
     348,   217,   217,   217,    58,    59,    60,   369,   217,   217,
     217,   217,     8,     8,     8,     8,     3,     8,   569,   571,
       4,     8,     3,     8,     8,   217,   217,   217,   236,   631,
       4,   629,     3,     8,   217,     8,   247,   458,     4,     4,
     220,   566,     4,   218,     4,   626,   217,   217,     5,   217,
       7,   632,   633,   634,     3,     6,   192,   195,   196,   197,
     198,   635,   636,   637,   639,   640,   641,   642,   633,   638,
       4,     4,     4,   643,     3,     8,     4,   220,   218,   218,
       4,   636,   217,   217
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   221,   223,   222,   224,   222,   225,   222,   226,   222,
     227,   222,   228,   222,   229,   222,   230,   222,   231,   222,
     232,   222,   233,   222,   234,   222,   235,   222,   236,   236,
     236,   236,   236,   236,   236,   237,   239,   238,   240,   241,
     241,   242,   242,   242,   244,   243,   245,   245,   246,   246,
     246,   248,   247,   249,   249,   250,   250,   250,   251,   253,
     252,   255,   254,   254,   256,   258,   257,   259,   259,   259,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     273,   272,   274,   276,   275,   277,   278,   279,   280,   281,
     282,   284,   283,   285,   285,   285,   285,   285,   287,   286,
     289,   288,   290,   291,   293,   292,   294,   294,   294,   294,
     295,   297,   296,   299,   298,   300,   301,   302,   303,   304,
     305,   306,   307,   309,   308,   310,   310,   310,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   313,   312,
     315,   314,   317,   316,   318,   318,   320,   319,   321,   321,
     322,   323,   324,   325,   327,   326,   329,   328,   330,   330,
     330,   331,   331,   333,   332,   335,   334,   337,   336,   339,
     338,   340,   340,   341,   341,   341,   343,   342,   344,   344,
     344,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   347,   346,   348,   348,   348,   350,
     349,   352,   351,   354,   353,   355,   357,   356,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   368,   367,   369,
     369,   369,   370,   371,   373,   372,   375,   374,   377,   376,
     379,   378,   381,   380,   382,   382,   382,   383,   383,   383,
     383,   383,   384,   385,   386,   387,   388,   390,   389,   391,
     391,   391,   392,   392,   392,   392,   392,   392,   393,   394,
     395,   397,   396,   398,   398,   399,   399,   399,   401,   400,
     403,   402,   404,   404,   404,   404,   405,   405,   407,   406,
     409,   408,   411,   410,   412,   412,   412,   413,   413,   413,
     413,   413,   413,   414,   415,   416,   417,   418,   419,   421,
     420,   422,   422,   423,   423,   423,   425,   424,   427,   426,
     428,   428,   428,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   431,   430,   433,   432,   435,   434,   437,   436,
     439,   438,   441,   440,   443,   442,   444,   445,   446,   448,
     447,   449,   449,   449,   449,   450,   452,   451,   453,   453,
     454,   454,   454,   456,   455,   457,   457,   457,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   460,   459,   462,   461,   463,   463,   464,   464,
     464,   466,   465,   468,   467,   469,   469,   470,   470,   470,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     472,   473,   474,   476,   475,   478,   477,   480,   479,   481,
     483,   482,   484,   486,   485,   487,   487,   488,   488,   488,
     490,   489,   492,   491,   493,   493,   494,   494,   494,   495,
     495,   495,   495,   495,   495,   495,   495,   495,   495,   496,
     498,   497,   499,   500,   501,   502,   503,   505,   504,   506,
     506,   507,   507,   507,   509,   508,   511,   510,   512,   512,
     512,   513,   513,   513,   513,   513,   513,   513,   513,   515,
     514,   516,   518,   517,   520,   519,   522,   521,   523,   523,
     524,   524,   524,   526,   525,   528,   527,   529,   529,   530,
     530,   530,   531,   531,   531,   531,   531,   531,   531,   531,
     531,   531,   531,   531,   531,   531,   531,   533,   532,   535,
     534,   537,   536,   539,   538,   541,   540,   543,   542,   545,
     544,   547,   546,   549,   548,   551,   550,   553,   552,   555,
     554,   556,   558,   557,   560,   559,   561,   561,   561,   563,
     562,   564,   564,   565,   565,   565,   566,   566,   566,   566,
     566,   566,   566,   566,   566,   566,   566,   566,   566,   566,
     566,   566,   567,   569,   568,   571,   570,   572,   573,   575,
     574,   576,   576,   576,   577,   577,   577,   577,   577,   579,
     578,   581,   580,   583,   582,   584,   584,   584,   585,   585,
     585,   585,   585,   585,   586,   588,   587,   589,   591,   590,
     593,   592,   595,   594,   596,   596,   596,   597,   597,   597,
     597,   597,   597,   597,   597,   597,   597,   597,   598,   600,
     599,   601,   603,   602,   604,   605,   607,   606,   608,   608,
     610,   609,   612,   611,   614,   613,   615,   615,   615,   616,
     616,   618,   617,   619,   621,   620,   622,   622,   622,   624,
     623,   625,   625,   625,   626,   626,   626,   626,   626,   626,
     626,   627,   629,   628,   631,   630,   632,   632,   632,   634,
     633,   635,   635,   635,   636,   636,   636,   636,   636,   638,
     637,   639,   640,   641,   643,   642,   645,   644,   646,   646,
     646,   647,   647,   647,   647,   647,   648,   649,   650,   651
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
       6,     1,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
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
  "boot_file_name", "$@94", "ip_address", "$@95", "duid", "$@96",
  "hw_address", "$@97", "client_id_value", "$@98", "circuit_id_value",
  "$@99", "flex_id_value", "$@100", "hostname", "$@101",
  "reservation_client_classes", "$@102", "relay", "$@103", "relay_map",
  "ip_addresses", "$@104", "client_classes", "$@105",
  "client_classes_list", "client_class_entry", "$@106",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@107",
  "client_class_template_test", "$@108", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@109", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@110",
  "control_socket_name", "$@111", "dhcp_queue_control", "$@112",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@113", "capacity", "arbitrary_map_entry", "$@114",
  "dhcp_ddns", "$@115", "sub_dhcp_ddns", "$@116", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@117", "server_port",
  "sender_ip", "$@118", "sender_port", "max_queue_size", "ncr_protocol",
  "$@119", "ncr_protocol_value", "ncr_format", "$@120", "config_control",
  "$@121", "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "loggers", "$@124", "loggers_entries",
  "logger_entry", "$@125", "logger_params", "logger_param", "debuglevel",
  "severity", "$@126", "output_options_list", "$@127",
  "output_options_list_content", "output_entry", "$@128",
  "output_params_list", "output_params", "output", "$@129", "flush",
  "maxsize", "maxver", "pattern", "$@130", "compatibility", "$@131",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   316,   316,   316,   317,   317,   318,   318,   319,   319,
     320,   320,   321,   321,   322,   322,   323,   323,   324,   324,
     325,   325,   326,   326,   327,   327,   328,   328,   336,   337,
     338,   339,   340,   341,   342,   345,   350,   350,   361,   364,
     365,   368,   373,   379,   384,   384,   391,   392,   395,   399,
     403,   409,   409,   416,   417,   420,   424,   428,   438,   447,
     447,   462,   462,   476,   479,   485,   485,   494,   495,   496,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   574,
     580,   586,   592,   598,   604,   610,   616,   622,   628,   634,
     640,   640,   649,   655,   655,   664,   670,   676,   682,   688,
     694,   700,   700,   709,   712,   715,   718,   721,   727,   727,
     736,   736,   745,   754,   764,   764,   773,   776,   779,   782,
     787,   793,   793,   802,   802,   811,   817,   823,   829,   835,
     841,   847,   853,   859,   859,   871,   872,   873,   878,   879,
     880,   881,   882,   883,   884,   885,   886,   887,   890,   890,
     899,   899,   910,   910,   918,   919,   922,   922,   930,   932,
     936,   942,   948,   954,   960,   960,   973,   973,   984,   985,
     986,   991,   992,   995,   995,  1014,  1014,  1032,  1032,  1045,
    1045,  1056,  1057,  1060,  1061,  1062,  1067,  1067,  1077,  1078,
    1079,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1106,  1109,  1109,  1117,  1118,  1119,  1122,
    1122,  1131,  1131,  1140,  1140,  1149,  1155,  1155,  1164,  1170,
    1176,  1182,  1188,  1194,  1200,  1206,  1212,  1218,  1218,  1226,
    1227,  1228,  1231,  1237,  1243,  1243,  1252,  1252,  1261,  1261,
    1270,  1270,  1279,  1279,  1290,  1291,  1292,  1297,  1298,  1299,
    1300,  1301,  1304,  1309,  1314,  1319,  1324,  1331,  1331,  1344,
    1345,  1346,  1351,  1352,  1353,  1354,  1355,  1356,  1359,  1365,
    1371,  1377,  1377,  1388,  1389,  1392,  1393,  1394,  1399,  1399,
    1409,  1409,  1419,  1420,  1421,  1424,  1427,  1428,  1431,  1431,
    1440,  1440,  1449,  1449,  1461,  1462,  1463,  1468,  1469,  1470,
    1471,  1472,  1473,  1476,  1482,  1488,  1494,  1500,  1506,  1515,
    1515,  1529,  1530,  1533,  1534,  1535,  1544,  1544,  1570,  1570,
    1581,  1582,  1583,  1589,  1590,  1591,  1592,  1593,  1594,  1595,
    1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1640,  1640,  1649,  1649,  1658,  1658,  1667,  1667,
    1676,  1676,  1685,  1685,  1694,  1694,  1705,  1711,  1717,  1723,
    1723,  1731,  1732,  1733,  1734,  1737,  1745,  1745,  1757,  1758,
    1762,  1763,  1764,  1769,  1769,  1777,  1778,  1779,  1784,  1785,
    1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,
    1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,
    1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,
    1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,
    1826,  1827,  1834,  1834,  1848,  1848,  1857,  1858,  1861,  1862,
    1863,  1870,  1870,  1885,  1885,  1899,  1900,  1903,  1904,  1905,
    1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,
    1922,  1924,  1930,  1932,  1932,  1941,  1941,  1950,  1950,  1959,
    1961,  1961,  1970,  1980,  1980,  1993,  1994,  1999,  2000,  2001,
    2008,  2008,  2020,  2020,  2032,  2033,  2038,  2039,  2040,  2047,
    2048,  2049,  2050,  2051,  2052,  2053,  2054,  2055,  2056,  2059,
    2061,  2061,  2070,  2072,  2074,  2080,  2086,  2095,  2095,  2108,
    2109,  2112,  2113,  2114,  2119,  2119,  2129,  2129,  2139,  2140,
    2141,  2146,  2147,  2148,  2149,  2150,  2151,  2152,  2153,  2156,
    2156,  2165,  2171,  2171,  2196,  2196,  2226,  2226,  2237,  2238,
    2241,  2242,  2243,  2248,  2248,  2257,  2257,  2266,  2267,  2270,
    2271,  2272,  2278,  2279,  2280,  2281,  2282,  2283,  2284,  2285,
    2286,  2287,  2288,  2289,  2290,  2291,  2292,  2295,  2295,  2304,
    2304,  2313,  2313,  2322,  2322,  2331,  2331,  2340,  2340,  2349,
    2349,  2358,  2358,  2367,  2367,  2376,  2376,  2385,  2385,  2399,
    2399,  2410,  2413,  2413,  2427,  2427,  2438,  2439,  2440,  2445,
    2445,  2455,  2456,  2459,  2460,  2461,  2466,  2467,  2468,  2469,
    2470,  2471,  2472,  2473,  2474,  2475,  2476,  2477,  2478,  2479,
    2480,  2481,  2484,  2486,  2486,  2495,  2495,  2504,  2512,  2520,
    2520,  2531,  2532,  2533,  2538,  2539,  2540,  2541,  2542,  2545,
    2545,  2554,  2554,  2566,  2566,  2579,  2580,  2581,  2586,  2587,
    2588,  2589,  2590,  2591,  2594,  2600,  2600,  2609,  2615,  2615,
    2625,  2625,  2638,  2638,  2648,  2649,  2650,  2655,  2656,  2657,
    2658,  2659,  2660,  2661,  2662,  2663,  2664,  2665,  2668,  2674,
    2674,  2683,  2689,  2689,  2698,  2704,  2710,  2710,  2719,  2720,
    2723,  2723,  2734,  2734,  2746,  2746,  2756,  2757,  2758,  2764,
    2765,  2768,  2768,  2779,  2787,  2787,  2800,  2801,  2802,  2808,
    2808,  2816,  2817,  2818,  2823,  2824,  2825,  2826,  2827,  2828,
    2829,  2832,  2838,  2838,  2847,  2847,  2858,  2859,  2860,  2865,
    2865,  2873,  2874,  2875,  2880,  2881,  2882,  2883,  2884,  2887,
    2887,  2896,  2902,  2908,  2914,  2914,  2923,  2923,  2934,  2935,
    2936,  2941,  2942,  2943,  2944,  2945,  2948,  2954,  2960,  2966
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
#line 6331 "dhcp4_parser.cc"

#line 2972 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
