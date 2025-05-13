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
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy"

#include <dhcp6/parser_context.h>

// Avoid warnings with the error counter.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#line 57 "dhcp6_parser.cc"


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 150 "dhcp6_parser.cc"

  /// Build a parser object.
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
#if PARSER6_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}

  Dhcp6Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  Dhcp6Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp6Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
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

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
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
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
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

  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 409 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 415 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 421 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 427 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 433 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 439 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 308 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp6_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Dhcp6Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp6Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp6Parser::parse ()
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
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
#line 317 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 755 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 318 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 761 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 319 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 767 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 320 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 773 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 321 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 779 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 322 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 785 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 323 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 791 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 324 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 325 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 803 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 326 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 327 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 328 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 329 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 330 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 338 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 339 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 340 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 341 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 342 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 343 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 344 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 347 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 352 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 357 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 363 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 370 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 375 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 381 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 386 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 389 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 397 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 401 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 405 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 411 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 413 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 422 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 426 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 430 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 440 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 449 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 454 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1061 "dhcp6_parser.cc"
    break;

  case 63: // $@19: %empty
#line 464 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1076 "dhcp6_parser.cc"
    break;

  case 64: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 473 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 481 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 487 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 491 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 498 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp6_parser.cc"
    break;

  case 140: // $@21: %empty
#line 575 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1130 "dhcp6_parser.cc"
    break;

  case 141: // data_directory: "data-directory" $@21 ":" "constant string"
#line 578 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 585 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 591 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // renew_timer: "renew-timer" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // rebind_timer: "rebind-timer" ":" "integer"
#line 627 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 633 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // t1_percent: "t1-percent" ":" "floating point"
#line 639 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t2_percent: "t2-percent" ":" "floating point"
#line 645 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // cache_threshold: "cache-threshold" ":" "floating point"
#line 651 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_max_age: "cache-max-age" ":" "integer"
#line 657 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 663 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 669 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 675 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 681 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // $@22: %empty
#line 687 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1320 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 690 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1329 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-present"
#line 696 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1337 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "never"
#line 699 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1345 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "always"
#line 702 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1353 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "when-not-present"
#line 705 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1361 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "boolean"
#line 708 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1370 "dhcp6_parser.cc"
    break;

  case 166: // $@23: %empty
#line 714 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1379 "dhcp6_parser.cc"
    break;

  case 167: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 717 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // $@24: %empty
#line 723 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1398 "dhcp6_parser.cc"
    break;

  case 169: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 726 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 732 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 738 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 744 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1438 "dhcp6_parser.cc"
    break;

  case 173: // $@25: %empty
#line 750 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1447 "dhcp6_parser.cc"
    break;

  case 174: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 753 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1457 "dhcp6_parser.cc"
    break;

  case 175: // $@26: %empty
#line 759 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1466 "dhcp6_parser.cc"
    break;

  case 176: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 762 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // store_extended_info: "store-extended-info" ":" "boolean"
#line 768 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1486 "dhcp6_parser.cc"
    break;

  case 178: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 774 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1496 "dhcp6_parser.cc"
    break;

  case 179: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 780 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1506 "dhcp6_parser.cc"
    break;

  case 180: // $@27: %empty
#line 786 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1515 "dhcp6_parser.cc"
    break;

  case 181: // server_tag: "server-tag" $@27 ":" "constant string"
#line 789 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1525 "dhcp6_parser.cc"
    break;

  case 182: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 795 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1535 "dhcp6_parser.cc"
    break;

  case 183: // $@28: %empty
#line 801 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 184: // allocator: "allocator" $@28 ":" "constant string"
#line 804 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1554 "dhcp6_parser.cc"
    break;

  case 185: // $@29: %empty
#line 810 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 186: // pd_allocator: "pd-allocator" $@29 ":" "constant string"
#line 813 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc"
    break;

  case 187: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 819 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1583 "dhcp6_parser.cc"
    break;

  case 188: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 825 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1593 "dhcp6_parser.cc"
    break;

  case 189: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 831 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1603 "dhcp6_parser.cc"
    break;

  case 190: // $@30: %empty
#line 837 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1615 "dhcp6_parser.cc"
    break;

  case 191: // interfaces_config: "interfaces-config" $@30 ":" "{" interfaces_config_params "}"
#line 843 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1625 "dhcp6_parser.cc"
    break;

  case 192: // $@31: %empty
#line 849 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1635 "dhcp6_parser.cc"
    break;

  case 193: // sub_interfaces6: "{" $@31 interfaces_config_params "}"
#line 853 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1644 "dhcp6_parser.cc"
    break;

  case 196: // interfaces_config_params: interfaces_config_params ","
#line 860 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1652 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 875 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc"
    break;

  case 206: // interfaces_list: "interfaces" $@32 ":" list_strings
#line 881 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc"
    break;

  case 207: // re_detect: "re-detect" ":" "boolean"
#line 886 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1683 "dhcp6_parser.cc"
    break;

  case 208: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 892 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1693 "dhcp6_parser.cc"
    break;

  case 209: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 898 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1703 "dhcp6_parser.cc"
    break;

  case 210: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 904 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1713 "dhcp6_parser.cc"
    break;

  case 211: // $@33: %empty
#line 910 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1725 "dhcp6_parser.cc"
    break;

  case 212: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 916 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1736 "dhcp6_parser.cc"
    break;

  case 213: // $@34: %empty
#line 923 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 214: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 929 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1759 "dhcp6_parser.cc"
    break;

  case 215: // $@35: %empty
#line 936 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1771 "dhcp6_parser.cc"
    break;

  case 216: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 942 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 221: // not_empty_database_list: not_empty_database_list ","
#line 953 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1788 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 958 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1798 "dhcp6_parser.cc"
    break;

  case 223: // database: "{" $@36 database_map_params "}"
#line 962 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1808 "dhcp6_parser.cc"
    break;

  case 226: // database_map_params: database_map_params ","
#line 970 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1816 "dhcp6_parser.cc"
    break;

  case 249: // $@37: %empty
#line 999 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 250: // database_type: "type" $@37 ":" db_type
#line 1002 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 251: // db_type: "memfile"
#line 1007 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp6_parser.cc"
    break;

  case 252: // db_type: "mysql"
#line 1008 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp6_parser.cc"
    break;

  case 253: // db_type: "postgresql"
#line 1009 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp6_parser.cc"
    break;

  case 254: // $@38: %empty
#line 1012 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1861 "dhcp6_parser.cc"
    break;

  case 255: // user: "user" $@38 ":" "constant string"
#line 1015 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1871 "dhcp6_parser.cc"
    break;

  case 256: // $@39: %empty
#line 1021 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // password: "password" $@39 ":" "constant string"
#line 1024 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1890 "dhcp6_parser.cc"
    break;

  case 258: // $@40: %empty
#line 1030 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 259: // host: "host" $@40 ":" "constant string"
#line 1033 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 260: // port: "port" ":" "integer"
#line 1039 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1919 "dhcp6_parser.cc"
    break;

  case 261: // $@41: %empty
#line 1045 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1928 "dhcp6_parser.cc"
    break;

  case 262: // name: "name" $@41 ":" "constant string"
#line 1048 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1938 "dhcp6_parser.cc"
    break;

  case 263: // persist: "persist" ":" "boolean"
#line 1054 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1948 "dhcp6_parser.cc"
    break;

  case 264: // lfc_interval: "lfc-interval" ":" "integer"
#line 1060 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1958 "dhcp6_parser.cc"
    break;

  case 265: // readonly: "readonly" ":" "boolean"
#line 1066 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1968 "dhcp6_parser.cc"
    break;

  case 266: // connect_timeout: "connect-timeout" ":" "integer"
#line 1072 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1978 "dhcp6_parser.cc"
    break;

  case 267: // read_timeout: "read-timeout" ":" "integer"
#line 1078 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 1988 "dhcp6_parser.cc"
    break;

  case 268: // write_timeout: "write-timeout" ":" "integer"
#line 1084 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 269: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1090 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 270: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1097 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 271: // $@42: %empty
#line 1103 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 272: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1106 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2036 "dhcp6_parser.cc"
    break;

  case 273: // on_fail_mode: "stop-retry-exit"
#line 1111 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp6_parser.cc"
    break;

  case 274: // on_fail_mode: "serve-retry-exit"
#line 1112 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp6_parser.cc"
    break;

  case 275: // on_fail_mode: "serve-retry-continue"
#line 1113 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp6_parser.cc"
    break;

  case 276: // max_row_errors: "max-row-errors" ":" "integer"
#line 1116 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2064 "dhcp6_parser.cc"
    break;

  case 277: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1122 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2074 "dhcp6_parser.cc"
    break;

  case 278: // $@43: %empty
#line 1128 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 279: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1131 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 280: // $@44: %empty
#line 1137 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2102 "dhcp6_parser.cc"
    break;

  case 281: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1140 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2112 "dhcp6_parser.cc"
    break;

  case 282: // $@45: %empty
#line 1146 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 283: // key_file: "key-file" $@45 ":" "constant string"
#line 1149 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 284: // $@46: %empty
#line 1155 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc"
    break;

  case 285: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1158 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 286: // $@47: %empty
#line 1164 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2162 "dhcp6_parser.cc"
    break;

  case 287: // sanity_checks: "sanity-checks" $@47 ":" "{" sanity_checks_params "}"
#line 1170 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2171 "dhcp6_parser.cc"
    break;

  case 290: // sanity_checks_params: sanity_checks_params ","
#line 1177 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2179 "dhcp6_parser.cc"
    break;

  case 293: // $@48: %empty
#line 1186 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp6_parser.cc"
    break;

  case 294: // lease_checks: "lease-checks" $@48 ":" "constant string"
#line 1189 "dhcp6_parser.yy"
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
#line 2208 "dhcp6_parser.cc"
    break;

  case 295: // $@49: %empty
#line 1205 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2217 "dhcp6_parser.cc"
    break;

  case 296: // extended_info_checks: "extended-info-checks" $@49 ":" "constant string"
#line 1208 "dhcp6_parser.yy"
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
#line 2236 "dhcp6_parser.cc"
    break;

  case 297: // $@50: %empty
#line 1223 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 298: // mac_sources: "mac-sources" $@50 ":" "[" mac_sources_list "]"
#line 1229 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 301: // mac_sources_list: mac_sources_list ","
#line 1236 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2265 "dhcp6_parser.cc"
    break;

  case 304: // duid_id: "duid"
#line 1245 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2274 "dhcp6_parser.cc"
    break;

  case 305: // string_id: "constant string"
#line 1250 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2283 "dhcp6_parser.cc"
    break;

  case 306: // $@51: %empty
#line 1255 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2295 "dhcp6_parser.cc"
    break;

  case 307: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1261 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp6_parser.cc"
    break;

  case 310: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1268 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2312 "dhcp6_parser.cc"
    break;

  case 314: // hw_address_id: "hw-address"
#line 1278 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2321 "dhcp6_parser.cc"
    break;

  case 315: // flex_id: "flex-id"
#line 1283 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2330 "dhcp6_parser.cc"
    break;

  case 316: // $@52: %empty
#line 1290 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2342 "dhcp6_parser.cc"
    break;

  case 317: // relay_supplied_options: "relay-supplied-options" $@52 ":" "[" list_content "]"
#line 1296 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp6_parser.cc"
    break;

  case 318: // $@53: %empty
#line 1303 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2363 "dhcp6_parser.cc"
    break;

  case 319: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1309 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2374 "dhcp6_parser.cc"
    break;

  case 322: // multi_threading_params: multi_threading_params ","
#line 1318 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2382 "dhcp6_parser.cc"
    break;

  case 329: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1331 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2392 "dhcp6_parser.cc"
    break;

  case 330: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1337 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2402 "dhcp6_parser.cc"
    break;

  case 331: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1343 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2412 "dhcp6_parser.cc"
    break;

  case 332: // $@54: %empty
#line 1349 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 333: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1355 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2433 "dhcp6_parser.cc"
    break;

  case 338: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1366 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2441 "dhcp6_parser.cc"
    break;

  case 339: // $@55: %empty
#line 1371 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2451 "dhcp6_parser.cc"
    break;

  case 340: // hooks_library: "{" $@55 hooks_params "}"
#line 1375 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2461 "dhcp6_parser.cc"
    break;

  case 341: // $@56: %empty
#line 1381 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 342: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1385 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2481 "dhcp6_parser.cc"
    break;

  case 345: // hooks_params: hooks_params ","
#line 1393 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2489 "dhcp6_parser.cc"
    break;

  case 349: // $@57: %empty
#line 1403 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 350: // library: "library" $@57 ":" "constant string"
#line 1406 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 351: // $@58: %empty
#line 1412 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 352: // parameters: "parameters" $@58 ":" map_value
#line 1415 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2526 "dhcp6_parser.cc"
    break;

  case 353: // $@59: %empty
#line 1421 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 354: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1427 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp6_parser.cc"
    break;

  case 357: // expired_leases_params: expired_leases_params ","
#line 1435 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2556 "dhcp6_parser.cc"
    break;

  case 364: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1448 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 365: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1454 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 366: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1460 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 367: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1466 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2596 "dhcp6_parser.cc"
    break;

  case 368: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1472 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2606 "dhcp6_parser.cc"
    break;

  case 369: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1478 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2616 "dhcp6_parser.cc"
    break;

  case 370: // $@60: %empty
#line 1487 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 371: // subnet6_list: "subnet6" $@60 ":" "[" subnet6_list_content "]"
#line 1493 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2637 "dhcp6_parser.cc"
    break;

  case 376: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1507 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2645 "dhcp6_parser.cc"
    break;

  case 377: // $@61: %empty
#line 1516 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2655 "dhcp6_parser.cc"
    break;

  case 378: // subnet6: "{" $@61 subnet6_params "}"
#line 1520 "dhcp6_parser.yy"
                                {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2681 "dhcp6_parser.cc"
    break;

  case 379: // $@62: %empty
#line 1542 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 380: // sub_subnet6: "{" $@62 subnet6_params "}"
#line 1546 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 383: // subnet6_params: subnet6_params ","
#line 1555 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2709 "dhcp6_parser.cc"
    break;

  case 430: // $@63: %empty
#line 1609 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2718 "dhcp6_parser.cc"
    break;

  case 431: // subnet: "subnet" $@63 ":" "constant string"
#line 1612 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc"
    break;

  case 432: // $@64: %empty
#line 1618 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2737 "dhcp6_parser.cc"
    break;

  case 433: // interface: "interface" $@64 ":" "constant string"
#line 1621 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 434: // $@65: %empty
#line 1627 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2756 "dhcp6_parser.cc"
    break;

  case 435: // interface_id: "interface-id" $@65 ":" "constant string"
#line 1630 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 436: // $@66: %empty
#line 1636 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 437: // client_class: "client-class" $@66 ":" "constant string"
#line 1639 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 438: // $@67: %empty
#line 1645 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp6_parser.cc"
    break;

  case 439: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1651 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp6_parser.cc"
    break;

  case 440: // reservations_global: "reservations-global" ":" "boolean"
#line 1656 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2816 "dhcp6_parser.cc"
    break;

  case 441: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1662 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2826 "dhcp6_parser.cc"
    break;

  case 442: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1668 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2836 "dhcp6_parser.cc"
    break;

  case 443: // $@68: %empty
#line 1674 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2845 "dhcp6_parser.cc"
    break;

  case 444: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1677 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 445: // hr_mode: "disabled"
#line 1682 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2860 "dhcp6_parser.cc"
    break;

  case 446: // hr_mode: "out-of-pool"
#line 1683 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2866 "dhcp6_parser.cc"
    break;

  case 447: // hr_mode: "global"
#line 1684 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2872 "dhcp6_parser.cc"
    break;

  case 448: // hr_mode: "all"
#line 1685 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2878 "dhcp6_parser.cc"
    break;

  case 449: // id: "id" ":" "integer"
#line 1688 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2888 "dhcp6_parser.cc"
    break;

  case 450: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1694 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2898 "dhcp6_parser.cc"
    break;

  case 451: // $@69: %empty
#line 1702 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2910 "dhcp6_parser.cc"
    break;

  case 452: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1708 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 457: // shared_networks_list: shared_networks_list ","
#line 1721 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2927 "dhcp6_parser.cc"
    break;

  case 458: // $@70: %empty
#line 1726 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2937 "dhcp6_parser.cc"
    break;

  case 459: // shared_network: "{" $@70 shared_network_params "}"
#line 1730 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 462: // shared_network_params: shared_network_params ","
#line 1736 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2953 "dhcp6_parser.cc"
    break;

  case 506: // $@71: %empty
#line 1790 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2965 "dhcp6_parser.cc"
    break;

  case 507: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1796 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 508: // $@72: %empty
#line 1804 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 509: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1807 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2991 "dhcp6_parser.cc"
    break;

  case 514: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1819 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2999 "dhcp6_parser.cc"
    break;

  case 515: // $@73: %empty
#line 1826 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 516: // option_def_entry: "{" $@73 option_def_params "}"
#line 1830 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 517: // $@74: %empty
#line 1841 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3031 "dhcp6_parser.cc"
    break;

  case 518: // sub_option_def: "{" $@74 option_def_params "}"
#line 1845 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3043 "dhcp6_parser.cc"
    break;

  case 523: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1861 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3051 "dhcp6_parser.cc"
    break;

  case 535: // code: "code" ":" "integer"
#line 1880 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3061 "dhcp6_parser.cc"
    break;

  case 537: // $@75: %empty
#line 1888 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp6_parser.cc"
    break;

  case 538: // option_def_type: "type" $@75 ":" "constant string"
#line 1891 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3080 "dhcp6_parser.cc"
    break;

  case 539: // $@76: %empty
#line 1897 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 540: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1900 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 541: // $@77: %empty
#line 1906 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3108 "dhcp6_parser.cc"
    break;

  case 542: // space: "space" $@77 ":" "constant string"
#line 1909 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3118 "dhcp6_parser.cc"
    break;

  case 544: // $@78: %empty
#line 1917 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3127 "dhcp6_parser.cc"
    break;

  case 545: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1920 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3137 "dhcp6_parser.cc"
    break;

  case 546: // option_def_array: "array" ":" "boolean"
#line 1926 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3147 "dhcp6_parser.cc"
    break;

  case 547: // $@79: %empty
#line 1936 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 548: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1942 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 553: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1957 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3176 "dhcp6_parser.cc"
    break;

  case 554: // $@80: %empty
#line 1964 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 555: // option_data_entry: "{" $@80 option_data_params "}"
#line 1968 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 556: // $@81: %empty
#line 1976 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3205 "dhcp6_parser.cc"
    break;

  case 557: // sub_option_data: "{" $@81 option_data_params "}"
#line 1980 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3214 "dhcp6_parser.cc"
    break;

  case 562: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1996 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3222 "dhcp6_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2017 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 575: // option_data_data: "data" $@82 ":" "constant string"
#line 2020 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3241 "dhcp6_parser.cc"
    break;

  case 578: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2030 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3251 "dhcp6_parser.cc"
    break;

  case 579: // option_data_always_send: "always-send" ":" "boolean"
#line 2036 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3261 "dhcp6_parser.cc"
    break;

  case 580: // option_data_never_send: "never-send" ":" "boolean"
#line 2042 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3271 "dhcp6_parser.cc"
    break;

  case 581: // $@83: %empty
#line 2051 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 582: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2057 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3292 "dhcp6_parser.cc"
    break;

  case 587: // not_empty_pools_list: not_empty_pools_list ","
#line 2070 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3300 "dhcp6_parser.cc"
    break;

  case 588: // $@84: %empty
#line 2075 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3310 "dhcp6_parser.cc"
    break;

  case 589: // pool_list_entry: "{" $@84 pool_params "}"
#line 2079 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3320 "dhcp6_parser.cc"
    break;

  case 590: // $@85: %empty
#line 2085 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3330 "dhcp6_parser.cc"
    break;

  case 591: // sub_pool6: "{" $@85 pool_params "}"
#line 2089 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3340 "dhcp6_parser.cc"
    break;

  case 594: // pool_params: pool_params ","
#line 2097 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3348 "dhcp6_parser.cc"
    break;

  case 603: // $@86: %empty
#line 2112 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 604: // pool_entry: "pool" $@86 ":" "constant string"
#line 2115 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 605: // pool_id: "pool-id" ":" "integer"
#line 2121 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 606: // $@87: %empty
#line 2127 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3385 "dhcp6_parser.cc"
    break;

  case 607: // user_context: "user-context" $@87 ":" map_value
#line 2129 "dhcp6_parser.yy"
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
#line 3412 "dhcp6_parser.cc"
    break;

  case 608: // $@88: %empty
#line 2152 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 609: // comment: "comment" $@88 ":" "constant string"
#line 2154 "dhcp6_parser.yy"
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
#line 3449 "dhcp6_parser.cc"
    break;

  case 610: // $@89: %empty
#line 2182 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3461 "dhcp6_parser.cc"
    break;

  case 611: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2188 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3470 "dhcp6_parser.cc"
    break;

  case 616: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2201 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3478 "dhcp6_parser.cc"
    break;

  case 617: // $@90: %empty
#line 2206 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 618: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2210 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3500 "dhcp6_parser.cc"
    break;

  case 619: // $@91: %empty
#line 2218 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3510 "dhcp6_parser.cc"
    break;

  case 620: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2222 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3522 "dhcp6_parser.cc"
    break;

  case 623: // pd_pool_params: pd_pool_params ","
#line 2232 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3530 "dhcp6_parser.cc"
    break;

  case 635: // $@92: %empty
#line 2250 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3539 "dhcp6_parser.cc"
    break;

  case 636: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2253 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3549 "dhcp6_parser.cc"
    break;

  case 637: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2259 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3559 "dhcp6_parser.cc"
    break;

  case 638: // $@93: %empty
#line 2265 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3568 "dhcp6_parser.cc"
    break;

  case 639: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2268 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 640: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2274 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3588 "dhcp6_parser.cc"
    break;

  case 641: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2280 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3598 "dhcp6_parser.cc"
    break;

  case 642: // $@94: %empty
#line 2289 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3610 "dhcp6_parser.cc"
    break;

  case 643: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2295 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3619 "dhcp6_parser.cc"
    break;

  case 648: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2306 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3627 "dhcp6_parser.cc"
    break;

  case 649: // $@95: %empty
#line 2311 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 650: // reservation: "{" $@95 reservation_params "}"
#line 2315 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 651: // $@96: %empty
#line 2320 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 652: // sub_reservation: "{" $@96 reservation_params "}"
#line 2324 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3665 "dhcp6_parser.cc"
    break;

  case 657: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2335 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3673 "dhcp6_parser.cc"
    break;

  case 669: // $@97: %empty
#line 2354 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3685 "dhcp6_parser.cc"
    break;

  case 670: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2360 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3694 "dhcp6_parser.cc"
    break;

  case 671: // $@98: %empty
#line 2365 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 672: // prefixes: "prefixes" $@98 ":" list_strings
#line 2371 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3715 "dhcp6_parser.cc"
    break;

  case 673: // $@99: %empty
#line 2376 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3724 "dhcp6_parser.cc"
    break;

  case 674: // duid: "duid" $@99 ":" "constant string"
#line 2379 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 675: // $@100: %empty
#line 2385 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3743 "dhcp6_parser.cc"
    break;

  case 676: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2388 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3753 "dhcp6_parser.cc"
    break;

  case 677: // $@101: %empty
#line 2394 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3762 "dhcp6_parser.cc"
    break;

  case 678: // hostname: "hostname" $@101 ":" "constant string"
#line 2397 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 679: // $@102: %empty
#line 2403 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3781 "dhcp6_parser.cc"
    break;

  case 680: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2406 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3791 "dhcp6_parser.cc"
    break;

  case 681: // $@103: %empty
#line 2412 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 682: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2418 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3812 "dhcp6_parser.cc"
    break;

  case 683: // $@104: %empty
#line 2426 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 684: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2432 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 687: // $@105: %empty
#line 2441 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3842 "dhcp6_parser.cc"
    break;

  case 688: // ip_address: "ip-address" $@105 ":" "constant string"
#line 2444 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 689: // $@106: %empty
#line 2453 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3864 "dhcp6_parser.cc"
    break;

  case 690: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2459 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 693: // client_classes_list: client_classes_list ","
#line 2466 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3881 "dhcp6_parser.cc"
    break;

  case 694: // $@107: %empty
#line 2471 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3891 "dhcp6_parser.cc"
    break;

  case 695: // client_class_entry: "{" $@107 client_class_params "}"
#line 2475 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 700: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2487 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3909 "dhcp6_parser.cc"
    break;

  case 716: // $@108: %empty
#line 2510 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3918 "dhcp6_parser.cc"
    break;

  case 717: // client_class_test: "test" $@108 ":" "constant string"
#line 2513 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 718: // $@109: %empty
#line 2519 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3937 "dhcp6_parser.cc"
    break;

  case 719: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2522 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3947 "dhcp6_parser.cc"
    break;

  case 720: // only_if_required: "only-if-required" ":" "boolean"
#line 2528 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3957 "dhcp6_parser.cc"
    break;

  case 721: // $@110: %empty
#line 2537 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3969 "dhcp6_parser.cc"
    break;

  case 722: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2543 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 725: // server_id_params: server_id_params ","
#line 2552 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3988 "dhcp6_parser.cc"
    break;

  case 735: // $@111: %empty
#line 2568 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3997 "dhcp6_parser.cc"
    break;

  case 736: // server_id_type: "type" $@111 ":" duid_type
#line 2571 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4006 "dhcp6_parser.cc"
    break;

  case 737: // duid_type: "LLT"
#line 2576 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4012 "dhcp6_parser.cc"
    break;

  case 738: // duid_type: "EN"
#line 2577 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4018 "dhcp6_parser.cc"
    break;

  case 739: // duid_type: "LL"
#line 2578 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4024 "dhcp6_parser.cc"
    break;

  case 740: // htype: "htype" ":" "integer"
#line 2581 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4034 "dhcp6_parser.cc"
    break;

  case 741: // $@112: %empty
#line 2587 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4043 "dhcp6_parser.cc"
    break;

  case 742: // identifier: "identifier" $@112 ":" "constant string"
#line 2590 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4053 "dhcp6_parser.cc"
    break;

  case 743: // time: "time" ":" "integer"
#line 2596 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4063 "dhcp6_parser.cc"
    break;

  case 744: // enterprise_id: "enterprise-id" ":" "integer"
#line 2602 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4073 "dhcp6_parser.cc"
    break;

  case 745: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2610 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4083 "dhcp6_parser.cc"
    break;

  case 746: // $@113: %empty
#line 2618 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4095 "dhcp6_parser.cc"
    break;

  case 747: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2624 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4104 "dhcp6_parser.cc"
    break;

  case 750: // control_socket_params: control_socket_params ","
#line 2631 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4112 "dhcp6_parser.cc"
    break;

  case 756: // $@114: %empty
#line 2643 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp6_parser.cc"
    break;

  case 757: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2646 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4131 "dhcp6_parser.cc"
    break;

  case 758: // $@115: %empty
#line 2652 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4140 "dhcp6_parser.cc"
    break;

  case 759: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2655 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4150 "dhcp6_parser.cc"
    break;

  case 760: // $@116: %empty
#line 2664 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4162 "dhcp6_parser.cc"
    break;

  case 761: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2670 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4173 "dhcp6_parser.cc"
    break;

  case 764: // queue_control_params: queue_control_params ","
#line 2679 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4181 "dhcp6_parser.cc"
    break;

  case 771: // enable_queue: "enable-queue" ":" "boolean"
#line 2692 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4191 "dhcp6_parser.cc"
    break;

  case 772: // $@117: %empty
#line 2698 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4200 "dhcp6_parser.cc"
    break;

  case 773: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2701 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4210 "dhcp6_parser.cc"
    break;

  case 774: // capacity: "capacity" ":" "integer"
#line 2707 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4220 "dhcp6_parser.cc"
    break;

  case 775: // $@118: %empty
#line 2713 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4229 "dhcp6_parser.cc"
    break;

  case 776: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2716 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4238 "dhcp6_parser.cc"
    break;

  case 777: // $@119: %empty
#line 2723 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4250 "dhcp6_parser.cc"
    break;

  case 778: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2729 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4261 "dhcp6_parser.cc"
    break;

  case 779: // $@120: %empty
#line 2736 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4271 "dhcp6_parser.cc"
    break;

  case 780: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2740 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4281 "dhcp6_parser.cc"
    break;

  case 783: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2748 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4289 "dhcp6_parser.cc"
    break;

  case 802: // enable_updates: "enable-updates" ":" "boolean"
#line 2773 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4299 "dhcp6_parser.cc"
    break;

  case 803: // $@121: %empty
#line 2780 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4308 "dhcp6_parser.cc"
    break;

  case 804: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2783 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4318 "dhcp6_parser.cc"
    break;

  case 805: // $@122: %empty
#line 2789 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4327 "dhcp6_parser.cc"
    break;

  case 806: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2792 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4337 "dhcp6_parser.cc"
    break;

  case 807: // server_port: "server-port" ":" "integer"
#line 2798 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4347 "dhcp6_parser.cc"
    break;

  case 808: // $@123: %empty
#line 2804 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4356 "dhcp6_parser.cc"
    break;

  case 809: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2807 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 810: // sender_port: "sender-port" ":" "integer"
#line 2813 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4376 "dhcp6_parser.cc"
    break;

  case 811: // max_queue_size: "max-queue-size" ":" "integer"
#line 2819 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4386 "dhcp6_parser.cc"
    break;

  case 812: // $@124: %empty
#line 2825 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4395 "dhcp6_parser.cc"
    break;

  case 813: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2828 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4404 "dhcp6_parser.cc"
    break;

  case 814: // ncr_protocol_value: "UDP"
#line 2834 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4410 "dhcp6_parser.cc"
    break;

  case 815: // ncr_protocol_value: "TCP"
#line 2835 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4416 "dhcp6_parser.cc"
    break;

  case 816: // $@125: %empty
#line 2838 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4425 "dhcp6_parser.cc"
    break;

  case 817: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2841 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4435 "dhcp6_parser.cc"
    break;

  case 818: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2848 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4445 "dhcp6_parser.cc"
    break;

  case 819: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2855 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4455 "dhcp6_parser.cc"
    break;

  case 820: // $@126: %empty
#line 2862 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4464 "dhcp6_parser.cc"
    break;

  case 821: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2865 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4473 "dhcp6_parser.cc"
    break;

  case 822: // $@127: %empty
#line 2871 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4482 "dhcp6_parser.cc"
    break;

  case 823: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2874 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4492 "dhcp6_parser.cc"
    break;

  case 824: // $@128: %empty
#line 2881 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4501 "dhcp6_parser.cc"
    break;

  case 825: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2884 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4511 "dhcp6_parser.cc"
    break;

  case 826: // $@129: %empty
#line 2891 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4520 "dhcp6_parser.cc"
    break;

  case 827: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2894 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4530 "dhcp6_parser.cc"
    break;

  case 828: // $@130: %empty
#line 2903 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4542 "dhcp6_parser.cc"
    break;

  case 829: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2909 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4552 "dhcp6_parser.cc"
    break;

  case 830: // $@131: %empty
#line 2915 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4562 "dhcp6_parser.cc"
    break;

  case 831: // sub_config_control: "{" $@131 config_control_params "}"
#line 2919 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4571 "dhcp6_parser.cc"
    break;

  case 834: // config_control_params: config_control_params ","
#line 2927 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4579 "dhcp6_parser.cc"
    break;

  case 837: // $@132: %empty
#line 2937 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4591 "dhcp6_parser.cc"
    break;

  case 838: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2943 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4600 "dhcp6_parser.cc"
    break;

  case 839: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2948 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4610 "dhcp6_parser.cc"
    break;

  case 840: // $@133: %empty
#line 2956 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4622 "dhcp6_parser.cc"
    break;

  case 841: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2962 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4631 "dhcp6_parser.cc"
    break;

  case 844: // loggers_entries: loggers_entries ","
#line 2971 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4639 "dhcp6_parser.cc"
    break;

  case 845: // $@134: %empty
#line 2977 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4649 "dhcp6_parser.cc"
    break;

  case 846: // logger_entry: "{" $@134 logger_params "}"
#line 2981 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4657 "dhcp6_parser.cc"
    break;

  case 849: // logger_params: logger_params ","
#line 2987 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4665 "dhcp6_parser.cc"
    break;

  case 857: // debuglevel: "debuglevel" ":" "integer"
#line 3001 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4675 "dhcp6_parser.cc"
    break;

  case 858: // $@135: %empty
#line 3007 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4684 "dhcp6_parser.cc"
    break;

  case 859: // severity: "severity" $@135 ":" "constant string"
#line 3010 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4694 "dhcp6_parser.cc"
    break;

  case 860: // $@136: %empty
#line 3016 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4706 "dhcp6_parser.cc"
    break;

  case 861: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 3022 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4715 "dhcp6_parser.cc"
    break;

  case 864: // output_options_list_content: output_options_list_content ","
#line 3029 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4723 "dhcp6_parser.cc"
    break;

  case 865: // $@137: %empty
#line 3034 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4733 "dhcp6_parser.cc"
    break;

  case 866: // output_entry: "{" $@137 output_params_list "}"
#line 3038 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4741 "dhcp6_parser.cc"
    break;

  case 869: // output_params_list: output_params_list ","
#line 3044 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4749 "dhcp6_parser.cc"
    break;

  case 875: // $@138: %empty
#line 3056 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 876: // output: "output" $@138 ":" "constant string"
#line 3059 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4768 "dhcp6_parser.cc"
    break;

  case 877: // flush: "flush" ":" "boolean"
#line 3065 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4778 "dhcp6_parser.cc"
    break;

  case 878: // maxsize: "maxsize" ":" "integer"
#line 3071 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4788 "dhcp6_parser.cc"
    break;

  case 879: // maxver: "maxver" ":" "integer"
#line 3077 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4798 "dhcp6_parser.cc"
    break;

  case 880: // $@139: %empty
#line 3083 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4807 "dhcp6_parser.cc"
    break;

  case 881: // pattern: "pattern" $@139 ":" "constant string"
#line 3086 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4817 "dhcp6_parser.cc"
    break;

  case 882: // $@140: %empty
#line 3092 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4829 "dhcp6_parser.cc"
    break;

  case 883: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3098 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4838 "dhcp6_parser.cc"
    break;

  case 886: // compatibility_params: compatibility_params ","
#line 3105 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4846 "dhcp6_parser.cc"
    break;

  case 889: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3114 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4856 "dhcp6_parser.cc"
    break;


#line 4860 "dhcp6_parser.cc"

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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Dhcp6Parser::context.
  Dhcp6Parser::context::context (const Dhcp6Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Dhcp6Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  Dhcp6Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  Dhcp6Parser::yysyntax_error_ (const context& yyctx) const
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


  const short Dhcp6Parser::yypact_ninf_ = -1032;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     629, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032,    42,    34,    60,    67,    91,
      95,    97,   107,   111,   133,   212,   245,   252,   263,   265,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,    34,  -176,
     178,   172,    77,   697,   181,   225,    -2,   200,    83,   118,
    -105,   244,    72, -1032,   292,   297,   302,   300,   309, -1032,
     105, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   329,   338,
     347,   348,   356,   357,   389,   390,   396,   406,   455,   456,
     458,   459, -1032,   461,   462,   463,   464,   465, -1032, -1032,
   -1032,   467,   469,   478,   479, -1032, -1032, -1032,   481, -1032,
   -1032, -1032, -1032, -1032, -1032,   482,   483,   485, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032,   486, -1032, -1032,
   -1032, -1032, -1032, -1032,   488,   489,   490, -1032, -1032,   493,
   -1032,   143, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   495,   496,   499,   500, -1032,   147, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
     502,   504, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032,   159, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032,   505, -1032, -1032, -1032, -1032,   161,
   -1032, -1032, -1032, -1032, -1032, -1032,   506, -1032,   507,   510,
   -1032, -1032, -1032, -1032, -1032, -1032,   170, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032,   324,   366, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032,   363, -1032, -1032,   512, -1032, -1032,
   -1032,   514, -1032, -1032,   432,   516, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   518,
     519,   524, -1032, -1032, -1032, -1032,   527,   536, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   173, -1032, -1032, -1032,   539, -1032, -1032,   540, -1032,
     541,   543, -1032, -1032,   544,   546, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032,   174, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   548,   188, -1032, -1032, -1032, -1032,    34,    34, -1032,
     320,   549, -1032, -1032,   550,   553,   556,   557,   558,   559,
     343,   344,   345,   346,   355,   358,   359,   360,   354,   361,
     364,   368,   375,   376,   564,   377,   378,   371,   379,   388,
     578,   583,   585,   391,   392,   386,   393,   596,   597,   608,
     398,   609,   619,   620,   622,   624,   625,   407,   408,   409,
     631,   632,   633,   647,   648,   649,   650,   662,   665,   412,
     666,   667,   668,   669,   670,   672,   454,   460,   466,   677,
     678, -1032,   172, -1032,   680,   472,   475,   480,   484,    77,
   -1032,   681,   682,   683,   684,   695,   487,   477,   702,   703,
     705,   697, -1032,   706,   497,   181, -1032,   707,   498,   716,
     501,   503,   225, -1032,   719,   722,   728,   729,   730,   732,
     733, -1032,    -2, -1032,   734,   735,   520,   736,   738,   739,
     521, -1032,    83,   741,   537,   538,   551, -1032,   118,   758,
     759,   -49, -1032,   552,   773,   776,   565,   783,   569,   571,
     790,   791,   573,   574,   794,   803,   805,   806,   244, -1032,
     810,   594,    72, -1032, -1032, -1032,   812,   811,   599,   813,
     815,   816,   817,   821, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   610, -1032,
   -1032, -1032, -1032, -1032,  -141,   611,   612, -1032, -1032, -1032,
   -1032,   823,   824,   828, -1032,   630,   634,   844,   845,   635,
     -47, -1032, -1032, -1032,   846,   848,   851,   850,   853,   854,
     855,   856,   857, -1032,   858,   859,   860,   861,   641,   642,
   -1032, -1032, -1032,   864,   863, -1032,   866, -1032, -1032, -1032,
   -1032, -1032,   867,   868,   654,   655,   656, -1032, -1032,   866,
     657,   871, -1032,   659, -1032, -1032,   660, -1032,   661, -1032,
   -1032, -1032,   866,   866,   866,   663,   664,   671,   673, -1032,
     674,   675, -1032,   676,   679,   685, -1032, -1032,   686, -1032,
   -1032, -1032, -1032,   687,   845, -1032, -1032,   688,   689, -1032,
     690, -1032, -1032,    -9,   700, -1032, -1032,  -141,   691,   692,
     693, -1032,   877, -1032, -1032,    34,   172, -1032,    72,    77,
     350,   350,   879, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032,   882,   883,   885, -1032, -1032,   890, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032,  -101,    34,    56,    85,
     891,   893,   894,   211,    57,   373,   -52,   -23,   244, -1032,
   -1032,   895,  -121, -1032, -1032,   896,   897, -1032, -1032, -1032,
   -1032, -1032,   -70, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032,   879, -1032,   206,   250,   258, -1032, -1032, -1032,
   -1032,   910,   911,   912,   914,   915,   916,   917,   918,   919,
     920, -1032,   921, -1032, -1032, -1032, -1032, -1032,   277, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   291, -1032,   922,   814, -1032, -1032,   923,   924, -1032,
   -1032,   925,   927, -1032, -1032,   926,   930, -1032, -1032,   928,
     932, -1032, -1032, -1032,   155, -1032, -1032, -1032,   931, -1032,
   -1032, -1032,   202, -1032, -1032, -1032, -1032, -1032,   293, -1032,
   -1032, -1032, -1032,   276, -1032, -1032,   933,   935, -1032, -1032,
     934,   938, -1032,   939,   940,   941,   942,   943,   944,   328,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   945,
     946,   947, -1032, -1032, -1032, -1032,   332, -1032, -1032, -1032,
   -1032, -1032, -1032,   948,   949,   950, -1032,   336, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   340,
   -1032, -1032, -1032,   951, -1032,   952, -1032, -1032, -1032,   342,
   -1032, -1032, -1032, -1032, -1032,   365, -1032,   443, -1032,   953,
   -1032,   367, -1032, -1032,   740, -1032,   936,   955, -1032, -1032,
     956,   958, -1032, -1032, -1032,   957, -1032,   960, -1032, -1032,
   -1032,   959,   963,   964,   965,   715,   747,   743,   748,   751,
     752,   753,   754,   756,   757,   976,   760,   979,   980,   985,
     987,   350, -1032, -1032,   350, -1032,   879,   697, -1032,   882,
      83, -1032,   883,   118, -1032,   885,   588, -1032,   890,  -101,
   -1032, -1032,    56, -1032,   988,   990,    85, -1032,   352,   891,
   -1032,    -2, -1032,   893,  -105, -1032,   894,   777,   780,   784,
     785,   786,   789,   211, -1032,  1012,  1014,   799,   800,   801,
      57, -1032,   820,   833,   835,   373, -1032,  1030,  1054,   -52,
   -1032,   836,  1065,   874,  1068,   -23, -1032, -1032,   213,   895,
   -1032,   852,  -121, -1032, -1032,  1070,  1071,   181, -1032,   896,
     225, -1032,   897,  1077, -1032, -1032,   190,   888,   913,   929,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
     385, -1032,   937,   954,   961,   962, -1032,   369, -1032,   405,
   -1032,  1122, -1032,  1123, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032,   433, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032,   966,   967, -1032, -1032, -1032,  1130, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
    1131,  1137, -1032, -1032, -1032, -1032, -1032, -1032,  1133, -1032,
     436, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   168,
     968, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   969,
     971, -1032, -1032,   972, -1032,    34, -1032, -1032,  1138, -1032,
   -1032, -1032, -1032, -1032,   439, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032,   974,   440, -1032,   449, -1032,   975, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   588, -1032,
   -1032, -1032,  1139,  1140,   973, -1032,   352, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,  1141,   977,
    1142,   213, -1032, -1032, -1032, -1032, -1032, -1032,   981,   983,
   -1032, -1032,  1143, -1032,   984, -1032, -1032, -1032,  1144, -1032,
   -1032,   447, -1032,   -75,  1144, -1032, -1032,  1146,  1148,  1149,
   -1032,   453, -1032, -1032, -1032, -1032, -1032, -1032, -1032,  1150,
     982,   986,   989,  1151,   -75, -1032,   991, -1032, -1032, -1032,
     992, -1032, -1032, -1032
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   192,     9,   379,    11,
     590,    13,   619,    15,   651,    17,   508,    19,   517,    21,
     556,    23,   341,    25,   779,    27,   830,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   653,     0,   519,   558,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   140,   828,   190,   211,   213,   215,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,     0,     0,     0,     0,     0,   159,   166,
     168,     0,     0,     0,     0,   370,   506,   547,     0,   183,
     185,   451,   606,   608,   443,     0,     0,     0,   297,   316,
     306,   286,   689,   642,   332,   353,   721,     0,   318,   746,
     760,   777,   173,   175,     0,     0,     0,   840,   882,     0,
     139,     0,    69,    72,    73,    74,    75,    76,    77,    78,
      79,    80,   111,   112,   113,   114,   115,    81,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   117,   118,   128,
     129,   130,   106,   136,   137,   138,   132,   133,   134,    84,
      85,    86,    87,   103,    88,    90,    89,   131,    94,    95,
      82,   108,   109,   110,   107,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   116,   135,
     205,     0,     0,     0,     0,   204,     0,   194,   197,   198,
     199,   200,   201,   202,   203,   581,   610,   430,   432,   434,
       0,     0,   438,   436,   683,   429,   384,   385,   386,   387,
     388,   389,   390,   391,   410,   411,   412,   413,   414,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   415,   416,
     426,   427,   428,     0,   381,   395,   396,   397,   400,   401,
     404,   405,   406,   403,   398,   399,   392,   393,   408,   409,
     394,   402,   407,   603,     0,   602,   598,   599,   597,     0,
     592,   595,   596,   600,   601,   635,     0,   638,     0,     0,
     634,   628,   629,   627,   632,   633,     0,   621,   624,   625,
     630,   631,   626,   681,   669,   671,   673,   675,   677,   679,
     668,   665,   666,   667,     0,   654,   655,   660,   661,   658,
     662,   663,   664,   659,     0,   537,   261,     0,   541,   539,
     544,     0,   533,   534,     0,   520,   521,   524,   536,   525,
     526,   527,   543,   528,   529,   530,   531,   532,   574,     0,
       0,     0,   572,   573,   576,   577,     0,   559,   560,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   349,   351,
     346,     0,   343,   347,   348,     0,   803,   805,     0,   808,
       0,     0,   812,   816,     0,     0,   820,   822,   824,   826,
     801,   799,   800,     0,   781,   784,   796,   785,   786,   787,
     788,   789,   790,   791,   792,   793,   794,   795,   797,   798,
     837,     0,     0,   832,   835,   836,    47,    52,     0,    39,
      45,     0,    66,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    71,    68,     0,     0,     0,     0,     0,   196,
     193,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   383,   380,     0,     0,   594,   591,     0,     0,     0,
       0,     0,   623,   620,     0,     0,     0,     0,     0,     0,
       0,   652,   657,   509,     0,     0,     0,     0,     0,     0,
       0,   518,   523,     0,     0,     0,     0,   557,   562,     0,
       0,   345,   342,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   783,   780,
       0,     0,   834,   831,    51,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,   178,
     179,   156,   157,   158,     0,     0,     0,   170,   171,   172,
     177,     0,     0,     0,   182,     0,     0,     0,     0,     0,
       0,   440,   441,   442,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   745,     0,     0,     0,     0,     0,     0,
     187,   188,   189,     0,     0,    70,     0,   207,   208,   209,
     210,   195,     0,     0,     0,     0,     0,   449,   450,     0,
       0,     0,   382,     0,   605,   593,     0,   637,     0,   640,
     641,   622,     0,     0,     0,     0,     0,     0,     0,   656,
       0,     0,   535,     0,     0,     0,   546,   522,     0,   578,
     579,   580,   561,     0,     0,   344,   802,     0,     0,   807,
       0,   810,   811,     0,     0,   818,   819,     0,     0,     0,
       0,   782,     0,   839,   833,     0,     0,   141,     0,     0,
       0,     0,   217,   181,   161,   162,   163,   164,   165,   160,
     167,   169,   372,   510,   549,   184,   186,   453,    40,   607,
     609,   445,   446,   447,   448,   444,     0,    48,     0,     0,
       0,   644,   334,     0,     0,     0,     0,     0,     0,   174,
     176,     0,     0,    53,   206,   583,   612,   431,   433,   435,
     439,   437,     0,   604,   636,   639,   682,   670,   672,   674,
     676,   678,   680,   538,   262,   542,   540,   545,   575,   350,
     352,   804,   806,   809,   814,   815,   813,   817,   821,   823,
     825,   827,   217,    44,     0,     0,     0,   249,   254,   256,
     258,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,   278,   280,   282,   284,   248,     0,   224,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   241,   242,   243,   240,   244,   245,   246,
     247,     0,   222,     0,   218,   219,   377,     0,   373,   374,
     515,     0,   511,   512,   554,     0,   550,   551,   458,     0,
     454,   455,   304,   305,     0,   299,   302,   303,     0,   314,
     315,   311,     0,   308,   312,   313,   293,   295,     0,   288,
     291,   292,   694,     0,   691,   649,     0,   645,   646,   339,
       0,   335,   336,     0,     0,     0,     0,     0,     0,     0,
     355,   358,   359,   360,   361,   362,   363,   735,   741,     0,
       0,     0,   734,   731,   732,   733,     0,   723,   726,   729,
     727,   728,   730,     0,     0,     0,   328,     0,   320,   323,
     324,   325,   326,   327,   756,   758,   755,   753,   754,     0,
     748,   751,   752,     0,   772,     0,   775,   768,   769,     0,
     762,   765,   766,   767,   770,     0,   845,     0,   842,     0,
     888,     0,   884,   887,    55,   588,     0,   584,   585,   617,
       0,   613,   614,   687,   686,     0,   685,     0,    64,   829,
     191,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   226,   212,   214,     0,   216,   221,     0,   371,   376,
     519,   507,   514,   558,   548,   553,     0,   452,   457,   301,
     298,   317,   310,   307,     0,     0,   290,   287,   696,   693,
     690,   653,   643,   648,     0,   333,   338,     0,     0,     0,
       0,     0,     0,   357,   354,     0,     0,     0,     0,     0,
     725,   722,     0,     0,     0,   322,   319,     0,     0,   750,
     747,     0,     0,     0,     0,   764,   761,   778,     0,   844,
     841,     0,   886,   883,    57,     0,    56,     0,   582,   587,
       0,   611,   616,     0,   684,   838,     0,     0,     0,     0,
     260,   263,   264,   265,   266,   267,   268,   269,   277,   270,
       0,   276,     0,     0,     0,     0,   225,     0,   220,     0,
     375,     0,   513,     0,   552,   505,   477,   478,   479,   481,
     482,   483,   467,   468,   486,   487,   488,   489,   490,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   491,   492,
     502,   503,   504,   463,   464,   465,   466,   475,   476,   472,
     473,   474,   471,   480,     0,   460,   469,   484,   485,   470,
     456,   300,   309,     0,     0,   289,   716,   718,     0,   714,
     708,   709,   710,   711,   712,   713,   715,   705,   706,   707,
       0,   697,   698,   701,   702,   703,   704,   692,     0,   647,
       0,   337,   364,   365,   366,   367,   368,   369,   356,     0,
       0,   740,   743,   744,   724,   329,   330,   331,   321,     0,
       0,   749,   771,     0,   774,     0,   763,   860,     0,   858,
     856,   850,   854,   855,     0,   847,   852,   853,   851,   843,
     889,   885,    54,    59,     0,   586,     0,   615,     0,   251,
     252,   253,   250,   255,   257,   259,   273,   274,   275,   272,
     279,   281,   283,   285,   223,   378,   516,   555,   462,   459,
     294,   296,     0,     0,     0,   695,   700,   650,   340,   737,
     738,   739,   736,   742,   757,   759,   773,   776,     0,     0,
       0,   849,   846,    58,   589,   618,   688,   461,     0,     0,
     720,   699,     0,   857,     0,   848,   717,   719,     0,   859,
     865,     0,   862,     0,   864,   861,   875,     0,     0,     0,
     880,     0,   867,   870,   871,   872,   873,   874,   863,     0,
       0,     0,     0,     0,   869,   866,     0,   877,   878,   879,
       0,   868,   876,   881
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032,   -10, -1032,  -615, -1032,
     235, -1032, -1032, -1032, -1032,   149, -1032,  -649, -1032, -1032,
   -1032,   -71, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   401,
     636, -1032, -1032,   -43,   -39,    10,    14,    15,    17,   -61,
     -24,   -21,   -17,   -11,    30,    32, -1032,    33,    37,    43,
      44, -1032,   419,    47, -1032,    50, -1032,    51,    62,    63,
      64, -1032,    65, -1032,    66, -1032, -1032, -1032, -1032, -1032,
      68, -1032,    69, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   410,   637, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032,   330, -1032,   114, -1032,  -731,
     120, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   -41, -1032,  -773, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032,    98, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032,   104,  -755, -1032, -1032, -1032,
   -1032,   103, -1032, -1032, -1032, -1032, -1032, -1032, -1032,    74,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032,    92, -1032, -1032,
   -1032,    93,   589, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
      88, -1032, -1032, -1032, -1032, -1032, -1032, -1031, -1032, -1032,
   -1032,   123, -1032, -1032, -1032,   126,   638, -1032, -1032, -1030,
   -1032, -1029, -1032,    73, -1032,    82, -1032,    76,    79,    80,
      81, -1032, -1032, -1032, -1027, -1032, -1032, -1032, -1032,   117,
   -1032, -1032,  -122,  1100, -1032, -1032, -1032, -1032, -1032,   128,
   -1032, -1032, -1032,   134, -1032,   606, -1032,   -66, -1032, -1032,
   -1032, -1032, -1032,   -65, -1032, -1032, -1032, -1032, -1032,   -16,
   -1032, -1032, -1032,   130, -1032, -1032, -1032,   144, -1032,   605,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032,    87, -1032, -1032, -1032,    96,   694, -1032, -1032,
   -1032,   -57, -1032,    -3, -1032, -1032, -1032, -1032, -1032,    78,
   -1032, -1032, -1032,    89,   696, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032,   -45, -1032, -1032, -1032,   135, -1032, -1032, -1032,
     145, -1032,   652,   413, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1025, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032,   148, -1032, -1032, -1032,   -88,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,   129,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032,   121, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
     116, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032,   434,   626, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032,   492,   621, -1032, -1032, -1032, -1032, -1032, -1032,
     119, -1032, -1032,   -96, -1032, -1032, -1032, -1032, -1032, -1032,
    -118, -1032, -1032,  -135, -1032, -1032, -1032, -1032, -1032, -1032,
   -1032, -1032, -1032, -1032,   122, -1032
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     769,    87,    88,    41,    68,    84,    85,   794,  1004,  1115,
    1116,   857,    43,    70,    90,   451,    91,    45,    71,   161,
     162,   163,   454,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   480,   759,   182,   481,   183,   482,   184,   185,   186,
     187,   514,   188,   515,   189,   190,   191,   192,   474,   193,
     194,   491,   195,   492,   196,   197,   198,   199,   456,    47,
      72,   236,   237,   238,   524,   239,   240,   241,   242,   200,
     457,   201,   458,   202,   459,   883,   884,   885,  1044,   858,
     859,   860,  1021,  1282,   861,  1022,   862,  1023,   863,  1024,
     864,   865,   565,   866,   867,   868,   869,   870,   871,   872,
     873,   874,  1035,  1289,   875,   876,   877,  1037,   878,  1038,
     879,  1039,   880,  1040,   203,   503,   918,   919,   920,  1064,
     921,  1065,   204,   500,   904,   905,   906,   907,   205,   502,
     912,   913,   914,   915,   206,   501,   207,   510,   967,   968,
     969,   970,   971,   208,   506,   930,   931,   932,  1074,    63,
      80,   401,   402,   403,   579,   404,   580,   209,   507,   939,
     940,   941,   942,   943,   944,   945,   946,   210,   487,   887,
     888,   889,  1047,    49,    73,   283,   284,   285,   533,   286,
     534,   287,   535,   288,   539,   289,   538,   211,   212,   213,
     214,   496,   775,   294,   295,   215,   493,   899,   900,   901,
    1056,  1194,  1195,   216,   488,    57,    77,   891,   892,   893,
    1050,    59,    78,   364,   365,   366,   367,   368,   369,   370,
     564,   371,   568,   372,   567,   373,   374,   569,   375,   217,
     489,   895,   896,   897,  1053,    61,    79,   386,   387,   388,
     389,   390,   573,   391,   392,   393,   394,   395,   297,   531,
    1006,  1007,  1008,  1117,    51,    74,   309,   310,   311,   543,
     312,   218,   494,   219,   495,   300,   532,  1010,  1011,  1012,
    1120,    53,    75,   326,   327,   328,   547,   329,   330,   549,
     331,   332,   220,   505,   926,   927,   928,  1071,    55,    76,
     344,   345,   346,   347,   555,   348,   556,   349,   557,   350,
     558,   351,   559,   352,   560,   353,   554,   302,   540,  1015,
    1016,  1123,   221,   504,   923,   924,  1068,  1220,  1221,  1222,
    1223,  1224,  1302,  1225,  1303,  1226,   222,   508,   956,   957,
     958,  1085,  1312,   959,   960,  1086,   961,   962,   223,   224,
     511,   979,   980,   981,  1097,   982,  1098,   225,   512,   989,
     990,   991,   992,  1102,   993,   994,  1104,   226,   513,    65,
      81,   423,   424,   425,   426,   584,   427,   585,   428,   429,
     587,   430,   431,   432,   590,   826,   433,   591,   434,   435,
     436,   594,   437,   595,   438,   596,   439,   597,   227,   455,
      67,    82,   442,   443,   444,   600,   445,   228,   519,   997,
     998,  1108,  1264,  1265,  1266,  1267,  1320,  1268,  1318,  1341,
    1342,  1343,  1351,  1352,  1353,  1359,  1354,  1355,  1356,  1357,
    1363,   229,   520,  1001,  1002,  1003
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     160,   235,   255,   305,   320,   340,    38,   362,   382,   400,
     420,   953,   262,   384,   385,   243,   298,   313,   324,   342,
     881,   376,   396,   911,   421,  1184,  1185,  1186,   301,  1193,
     256,  1199,   902,   768,   257,   398,   399,   363,   383,    31,
     800,    32,    30,    33,    86,   754,   755,   756,   757,   263,
     132,   133,   264,   806,   807,   808,   265,   296,   308,   323,
     341,   334,   266,   771,   772,   773,   774,    42,  1013,   244,
     299,   314,   325,   343,    44,   377,   397,   127,   422,   132,
     133,   947,   758,   258,   999,   440,   441,   259,   260,   842,
     261,   398,   399,   230,   231,   232,   233,   234,    46,   159,
     132,   133,    48,   267,    50,   268,   269,   355,   452,   768,
     270,   974,   975,   453,    52,   159,   271,   272,    54,   903,
     273,   333,  1346,   274,   275,  1347,  1348,  1349,  1350,   334,
     335,   336,   337,   338,   339,   276,   277,   278,   279,   280,
      56,   281,   282,   983,   984,   985,   522,   306,   321,   290,
     529,   523,   291,   292,   293,   530,   307,   322,  1059,   132,
     133,  1060,   541,   356,   545,   357,   358,   542,   159,   546,
     359,   360,   361,   552,   824,   825,   581,   598,   553,   132,
     133,   582,   599,    92,    93,   132,   133,    94,    89,   902,
     909,   602,   910,    95,    96,    97,   603,   986,   356,   378,
     357,   358,   379,   380,   381,  1062,   916,   917,  1063,   522,
     948,   949,   950,   951,  1018,  1279,  1280,  1281,   159,    58,
     132,   133,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    60,   602,    34,    35,    36,    37,  1019,    62,
     127,   529,   128,   129,   130,   131,  1020,  1184,  1185,  1186,
      64,  1193,    66,  1199,   132,   133,   303,   159,   126,  1069,
    1041,   134,  1070,   132,   133,  1042,   135,   136,   137,   138,
     139,   140,   141,   356,  1041,   142,  1066,   159,   446,  1043,
     447,  1067,   143,   159,   127,   252,   448,   911,   449,   253,
     304,   144,   450,  1147,   145,   132,   133,   953,  1309,  1310,
    1311,   146,   315,   316,   317,   318,   319,   132,   133,   147,
     148,  1083,   561,   460,   149,  1090,  1084,   150,   159,  1095,
    1091,   151,   461,  1099,  1096,  1105,   132,   133,  1100,   252,
    1106,   462,   463,   253,   933,   934,   935,   936,   937,   938,
     464,   465,   152,   153,   154,   155,   156,   157,   598,   562,
    1112,   563,  1041,  1107,   837,  1113,   158,  1294,   838,   839,
     840,   841,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   159,   466,   467,   852,   853,   854,   855,   856,
     468,   159,    98,    99,   100,   101,   102,   103,   541,  1257,
     469,  1258,  1259,  1295,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,  1286,  1287,  1288,
     356,   127,   356,   159,   418,   419,  1298,   604,   605,   581,
     571,  1299,  1321,   545,  1308,   159,  1109,  1322,  1324,  1110,
    1344,   160,   552,  1345,   132,   133,  1364,  1325,   235,   470,
     471,  1365,   472,   473,   159,   475,   476,   477,   478,   479,
     255,   483,   243,   484,   305,   132,   133,  1206,  1207,  1208,
     262,   320,   485,   486,   298,   490,   497,   498,   313,   499,
     509,   340,   516,   517,   518,   324,   301,   521,   256,   525,
     526,   362,   257,   527,   528,   342,   536,   382,   537,   544,
     548,   550,   384,   385,   551,   376,   566,   263,   570,   572,
     264,   396,   574,   575,   265,   296,   244,   420,   576,   308,
     266,   363,   963,   964,   965,   577,   323,   383,   299,   578,
     606,   421,   314,   583,   586,   588,   341,   589,   592,   325,
     593,   258,   601,   607,   608,   259,   260,   609,   261,   343,
     610,   611,   612,   613,   614,   615,   616,   617,   628,   377,
     159,   267,   159,   268,   269,   397,   618,   622,   270,   619,
     620,   621,   634,   623,   271,   272,   624,   635,   273,   636,
     625,   274,   275,   159,   631,   422,   626,   627,   629,   630,
     641,   642,   632,   276,   277,   278,   279,   280,   639,   281,
     282,   633,   643,   645,   637,   638,   640,   290,   306,   644,
     291,   292,   293,   646,   647,   321,   648,   307,   649,   650,
     651,   652,   653,   663,   322,   654,   655,   656,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   657,   658,   659,   660,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   661,   127,   356,   662,
     664,   665,   666,   667,   668,   160,   669,   670,   235,   129,
     130,   673,   674,   671,   676,   682,   683,   684,   685,   672,
     132,   133,   243,   248,   249,   677,   251,   134,   678,   686,
     688,   679,   135,   136,   137,   680,   689,   690,   687,   691,
     693,   696,   252,   952,   966,   976,   253,   420,   694,   697,
     698,  1000,   699,   702,   700,   254,   703,   954,   972,   977,
     987,   421,   704,   705,   706,   833,   707,   708,   710,   711,
     713,   712,   714,   715,   716,   718,   244,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     719,   720,   723,   724,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   721,   726,   127,   727,   152,   153,
     728,   955,   973,   978,   988,   422,   729,   730,   129,   130,
     731,   245,   732,   246,   733,   734,   735,   736,   737,   132,
     133,   247,   248,   249,   250,   251,   134,   738,   159,   739,
     740,   135,   136,   137,   742,   743,   745,  1046,   746,   747,
     748,   252,   749,   750,   751,   253,   752,   143,   762,   763,
     753,   760,   761,   764,   254,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   767,
     765,   776,    32,   777,   766,   770,   778,   779,   780,   781,
     782,   789,   790,   783,   784,   785,   786,   787,   788,   791,
     792,   793,   795,   796,   797,   798,   799,   801,   802,   803,
     804,   805,   832,   809,   810,   827,   882,   152,   153,   886,
     890,   811,   894,   812,   813,   814,   815,   898,   922,   816,
     925,   929,   996,  1005,  1009,   817,   818,   819,   821,   822,
     823,   829,   830,   831,  1025,  1026,  1027,   159,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1036,   908,  1049,  1045,  1048,
    1052,  1051,  1054,  1055,  1057,  1058,  1130,  1061,  1073,  1072,
    1075,  1076,  1118,  1077,  1078,  1079,  1080,  1081,  1082,  1087,
    1088,  1089,  1092,  1093,  1094,  1101,  1103,  1111,  1119,   820,
    1114,  1122,  1121,  1126,  1132,  1124,  1125,  1127,  1128,  1129,
    1131,  1133,  1134,  1135,  1136,  1137,   255,  1138,  1139,   362,
    1140,  1141,   382,  1142,  1143,  1155,   262,   384,   385,  1144,
     298,  1145,  1203,   376,  1204,  1162,   396,  1209,  1232,  1197,
     340,  1233,   301,   400,   256,  1234,  1235,  1236,   257,   363,
    1237,  1218,   383,  1156,   342,  1183,  1239,  1157,  1240,   952,
    1241,  1242,  1243,   263,   966,  1210,   264,  1216,   976,  1211,
     265,   296,  1163,   954,  1249,  1164,   266,  1260,   972,  1165,
    1196,  1000,   977,  1245,   299,  1166,   305,   377,   987,   320,
     397,  1262,  1217,  1198,  1246,   341,  1247,   258,  1250,  1252,
     313,   259,   260,   324,   261,  1219,  1158,  1261,   343,  1253,
    1159,  1160,  1255,  1161,  1273,  1270,  1272,   267,  1212,   268,
     269,  1278,  1213,  1214,   270,  1215,  1167,   955,  1168,  1169,
     271,   272,   973,  1170,   273,  1254,   978,   274,   275,  1171,
    1172,   308,   988,  1173,   323,  1263,  1174,  1175,  1283,   276,
     277,   278,   279,   280,   314,   281,   282,   325,  1176,  1177,
    1178,  1179,  1180,   290,  1181,  1182,   291,   292,   293,  1187,
    1296,  1297,  1189,  1284,  1304,  1190,  1191,  1192,  1188,  1305,
    1306,  1307,  1319,  1328,  1329,  1332,  1334,   834,  1338,  1285,
    1360,  1340,  1361,  1362,  1366,  1370,   828,  1290,   675,   836,
    1148,  1146,  1017,  1201,  1205,  1202,   681,  1230,  1231,  1248,
     725,  1238,  1150,  1149,  1291,  1200,  1327,   354,   717,   692,
    1152,  1292,  1293,   722,  1151,  1154,  1300,  1301,  1313,  1314,
     306,  1315,  1316,   321,  1323,  1326,  1330,  1153,  1333,   307,
    1277,  1336,   322,  1337,  1339,  1367,  1275,  1368,  1229,  1276,
    1369,  1372,  1373,  1274,   709,  1014,  1228,  1227,  1331,  1244,
    1251,  1256,   995,   744,   741,  1335,  1358,  1155,  1269,  1371,
       0,     0,     0,     0,  1271,  1209,     0,  1162,     0,   695,
     835,  1197,     0,     0,     0,  1317,     0,     0,   701,  1218,
    1260,     0,     0,     0,     0,  1156,     0,  1183,     0,  1157,
       0,     0,     0,  1210,  1262,  1216,     0,  1211,     0,     0,
       0,     0,     0,     0,  1163,     0,     0,  1164,     0,     0,
    1261,  1165,  1196,     0,     0,     0,     0,  1166,     0,     0,
    1217,     0,     0,     0,     0,  1198,     0,     0,     0,     0,
       0,     0,     0,  1219,     0,     0,     0,     0,  1158,     0,
       0,     0,  1159,  1160,     0,  1161,  1212,     0,  1263,     0,
    1213,  1214,     0,  1215,     0,     0,     0,     0,  1167,     0,
    1168,  1169,     0,     0,     0,  1170,     0,     0,     0,     0,
       0,  1171,  1172,     0,     0,  1173,     0,     0,  1174,  1175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1176,  1177,  1178,  1179,  1180,     0,  1181,  1182,     0,     0,
       0,  1187,     0,     0,  1189,     0,     0,  1190,  1191,  1192,
    1188
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   784,    73,    79,    79,    72,    73,    74,    75,    76,
     751,    78,    79,   778,    81,  1056,  1056,  1056,    73,  1056,
      73,  1056,   133,   648,    73,   140,   141,    78,    79,     5,
     689,     7,     0,     9,   220,   186,   187,   188,   189,    73,
     102,   103,    73,   702,   703,   704,    73,    73,    74,    75,
      76,   131,    73,   110,   111,   112,   113,     7,   138,    72,
      73,    74,    75,    76,     7,    78,    79,    79,    81,   102,
     103,    24,   223,    73,   205,    13,    14,    73,    73,    32,
      73,   140,   141,    16,    17,    18,    19,    20,     7,   220,
     102,   103,     7,    73,     7,    73,    73,    24,     3,   724,
      73,   163,   164,     8,     7,   220,    73,    73,     7,   220,
      73,   123,   197,    73,    73,   200,   201,   202,   203,   131,
     132,   133,   134,   135,   136,    73,    73,    73,    73,    73,
       7,    73,    73,   166,   167,   168,     3,    74,    75,    73,
       3,     8,    73,    73,    73,     8,    74,    75,     3,   102,
     103,     6,     3,    80,     3,    82,    83,     8,   220,     8,
      87,    88,    89,     3,   183,   184,     3,     3,     8,   102,
     103,     8,     8,    11,    12,   102,   103,    15,    10,   133,
     134,     3,   136,    21,    22,    23,     8,   220,    80,    81,
      82,    83,    84,    85,    86,     3,   121,   122,     6,     3,
     153,   154,   155,   156,     8,    25,    26,    27,   220,     7,
     102,   103,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,     7,     3,   220,   221,   222,   223,     8,     7,
      79,     3,    90,    91,    92,    93,     8,  1298,  1298,  1298,
       7,  1298,     7,  1298,   102,   103,    95,   220,    78,     3,
       3,   109,     6,   102,   103,     8,   114,   115,   116,   117,
     118,   119,   120,    80,     3,   123,     3,   220,     6,     8,
       3,     8,   130,   220,    79,   124,     4,  1062,     8,   128,
     129,   139,     3,  1044,   142,   102,   103,  1090,   150,   151,
     152,   149,    97,    98,    99,   100,   101,   102,   103,   157,
     158,     3,     8,     4,   162,     3,     8,   165,   220,     3,
       8,   169,     4,     3,     8,     3,   102,   103,     8,   124,
       8,     4,     4,   128,   143,   144,   145,   146,   147,   148,
       4,     4,   190,   191,   192,   193,   194,   195,     3,     3,
       3,     8,     3,     8,    24,     8,   204,     8,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,   220,     4,     4,    45,    46,    47,    48,    49,
       4,   220,    50,    51,    52,    53,    54,    55,     3,   196,
       4,   198,   199,     8,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,    42,    43,    44,
      80,    79,    80,   220,   190,   191,     3,   447,   448,     3,
       8,     8,     3,     3,     8,   220,     3,     8,     8,     6,
       3,   522,     3,     6,   102,   103,     3,     8,   529,     4,
       4,     8,     4,     4,   220,     4,     4,     4,     4,     4,
     541,     4,   529,     4,   545,   102,   103,   125,   126,   127,
     541,   552,     4,     4,   541,     4,     4,     4,   545,     4,
       4,   562,     4,     4,     4,   552,   541,     4,   541,     4,
       4,   572,   541,     4,     4,   562,     4,   578,     4,     4,
       4,     4,   578,   578,     4,   572,     4,   541,     4,     3,
     541,   578,     4,     4,   541,   541,   529,   598,     4,   545,
     541,   572,   159,   160,   161,     8,   552,   578,   541,     3,
     220,   598,   545,     4,     4,     4,   562,     4,     4,   552,
       4,   541,     4,     4,     4,   541,   541,     4,   541,   562,
       4,     4,     4,     4,   221,   221,   221,   221,     4,   572,
     220,   541,   220,   541,   541,   578,   221,   223,   541,   221,
     221,   221,     4,   222,   541,   541,   222,     4,   541,     4,
     222,   541,   541,   220,   223,   598,   221,   221,   221,   221,
       4,     4,   223,   541,   541,   541,   541,   541,   222,   541,
     541,   223,     4,     4,   223,   223,   223,   541,   545,   221,
     541,   541,   541,     4,     4,   552,     4,   545,     4,     4,
     223,   223,   223,   221,   552,     4,     4,     4,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     4,     4,     4,     4,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,     4,    79,    80,     4,
       4,     4,     4,     4,     4,   746,     4,   223,   749,    91,
      92,     4,     4,   223,     4,     4,     4,     4,     4,   223,
     102,   103,   749,   105,   106,   223,   108,   109,   223,     4,
     223,   221,   114,   115,   116,   221,     4,     4,   221,     4,
       4,     4,   124,   784,   785,   786,   128,   788,   221,   221,
       4,   792,   221,     4,   221,   137,     4,   784,   785,   786,
     787,   788,     4,     4,     4,   745,     4,     4,     4,     4,
       4,   221,     4,     4,   223,     4,   749,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
     223,   223,     4,     4,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   223,   223,    79,     4,   190,   191,
       4,   784,   785,   786,   787,   788,   221,     4,    91,    92,
     221,    94,   221,    96,     4,     4,   223,   223,     4,   102,
     103,   104,   105,   106,   107,   108,   109,     4,   220,     4,
       4,   114,   115,   116,     4,   221,     4,     3,     7,   220,
       7,   124,     7,     7,     7,   128,     5,   130,     5,     5,
     220,   220,   220,     5,   137,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,     5,
     220,     5,     7,     5,   220,   220,     5,     7,     5,     5,
       5,   220,   220,     7,     7,     7,     7,     7,     7,     5,
       7,     5,     5,     5,   220,   220,   220,   220,     7,   220,
     220,   220,     5,   220,   220,   185,     7,   190,   191,     7,
       7,   220,     7,   220,   220,   220,   220,     7,     7,   220,
       7,     7,     7,     7,     7,   220,   220,   220,   220,   220,
     220,   220,   220,   220,     4,     4,     4,   220,     4,     4,
       4,     4,     4,     4,     4,     4,   777,     3,     6,     6,
       3,     6,     6,     3,     6,     3,   221,     6,     3,     6,
       6,     3,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   724,
     220,     3,     6,     4,   221,     8,     6,     4,     4,     4,
     223,   223,   221,   221,   221,   221,  1047,   221,   221,  1050,
       4,   221,  1053,     4,     4,  1056,  1047,  1053,  1053,     4,
    1047,     4,     4,  1050,     4,  1056,  1053,  1068,   221,  1056,
    1071,   221,  1047,  1074,  1047,   221,   221,   221,  1047,  1050,
     221,  1068,  1053,  1056,  1071,  1056,     4,  1056,     4,  1090,
     221,   221,   221,  1047,  1095,  1068,  1047,  1068,  1099,  1068,
    1047,  1047,  1056,  1090,     4,  1056,  1047,  1108,  1095,  1056,
    1056,  1112,  1099,   223,  1047,  1056,  1117,  1050,  1105,  1120,
    1053,  1108,  1068,  1056,   221,  1071,   221,  1047,     4,   223,
    1117,  1047,  1047,  1120,  1047,  1068,  1056,  1108,  1071,     4,
    1056,  1056,     4,  1056,     3,   223,     6,  1047,  1068,  1047,
    1047,     4,  1068,  1068,  1047,  1068,  1056,  1090,  1056,  1056,
    1047,  1047,  1095,  1056,  1047,   221,  1099,  1047,  1047,  1056,
    1056,  1117,  1105,  1056,  1120,  1108,  1056,  1056,   220,  1047,
    1047,  1047,  1047,  1047,  1117,  1047,  1047,  1120,  1056,  1056,
    1056,  1056,  1056,  1047,  1056,  1056,  1047,  1047,  1047,  1056,
       8,     8,  1056,   220,     4,  1056,  1056,  1056,  1056,     8,
       3,     8,     4,     4,     4,     4,     4,   746,     5,   220,
       4,     7,     4,     4,     4,     4,   737,   220,   522,   749,
    1046,  1041,   832,  1059,  1066,  1062,   529,  1074,  1076,  1095,
     581,  1083,  1049,  1047,   220,  1058,  1298,    77,   572,   541,
    1052,   220,   220,   578,  1050,  1055,   220,   220,   220,   220,
    1117,   220,   220,  1120,   220,   220,   223,  1053,   221,  1117,
    1122,   220,  1120,   220,   220,   223,  1119,   221,  1073,  1120,
     221,   220,   220,  1117,   562,   802,  1071,  1069,  1306,  1090,
    1099,  1105,   788,   602,   598,  1321,  1344,  1298,  1109,  1364,
      -1,    -1,    -1,    -1,  1112,  1306,    -1,  1298,    -1,   545,
     748,  1298,    -1,    -1,    -1,  1255,    -1,    -1,   552,  1306,
    1321,    -1,    -1,    -1,    -1,  1298,    -1,  1298,    -1,  1298,
      -1,    -1,    -1,  1306,  1321,  1306,    -1,  1306,    -1,    -1,
      -1,    -1,    -1,    -1,  1298,    -1,    -1,  1298,    -1,    -1,
    1321,  1298,  1298,    -1,    -1,    -1,    -1,  1298,    -1,    -1,
    1306,    -1,    -1,    -1,    -1,  1298,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1306,    -1,    -1,    -1,    -1,  1298,    -1,
      -1,    -1,  1298,  1298,    -1,  1298,  1306,    -1,  1321,    -1,
    1306,  1306,    -1,  1306,    -1,    -1,    -1,    -1,  1298,    -1,
    1298,  1298,    -1,    -1,    -1,  1298,    -1,    -1,    -1,    -1,
      -1,  1298,  1298,    -1,    -1,  1298,    -1,    -1,  1298,  1298,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1298,  1298,  1298,  1298,  1298,    -1,  1298,  1298,    -1,    -1,
      -1,  1298,    -1,    -1,  1298,    -1,    -1,  1298,  1298,  1298,
    1298
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
       0,     5,     7,     9,   220,   221,   222,   223,   240,   241,
     242,   247,     7,   256,     7,   261,     7,   313,     7,   427,
       7,   508,     7,   525,     7,   542,     7,   459,     7,   465,
       7,   489,     7,   403,     7,   613,     7,   644,   248,   243,
     257,   262,   314,   428,   509,   526,   543,   460,   466,   490,
     404,   614,   645,   240,   249,   250,   220,   245,   246,    10,
     258,   260,    11,    12,    15,    21,    22,    23,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    90,    91,
      92,    93,   102,   103,   109,   114,   115,   116,   117,   118,
     119,   120,   123,   130,   139,   142,   149,   157,   158,   162,
     165,   169,   190,   191,   192,   193,   194,   195,   204,   220,
     255,   263,   264,   265,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   287,   289,   291,   292,   293,   294,   296,   298,
     299,   300,   301,   303,   304,   306,   308,   309,   310,   311,
     323,   325,   327,   368,   376,   382,   388,   390,   397,   411,
     421,   441,   442,   443,   444,   449,   457,   483,   515,   517,
     536,   566,   580,   592,   593,   601,   611,   642,   651,   675,
      16,    17,    18,    19,    20,   255,   315,   316,   317,   319,
     320,   321,   322,   515,   517,    94,    96,   104,   105,   106,
     107,   108,   124,   128,   137,   255,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   281,
     282,   283,   284,   287,   289,   291,   292,   293,   294,   296,
     298,   304,   306,   429,   430,   431,   433,   435,   437,   439,
     441,   442,   443,   444,   447,   448,   483,   502,   515,   517,
     519,   536,   561,    95,   129,   255,   437,   439,   483,   510,
     511,   512,   514,   515,   517,    97,    98,    99,   100,   101,
     255,   437,   439,   483,   515,   517,   527,   528,   529,   531,
     532,   534,   535,   123,   131,   132,   133,   134,   135,   136,
     255,   483,   515,   517,   544,   545,   546,   547,   549,   551,
     553,   555,   557,   559,   457,    24,    80,    82,    83,    87,
      88,    89,   255,   345,   467,   468,   469,   470,   471,   472,
     473,   475,   477,   479,   480,   482,   515,   517,    81,    84,
      85,    86,   255,   345,   471,   477,   491,   492,   493,   494,
     495,   497,   498,   499,   500,   501,   515,   517,   140,   141,
     255,   405,   406,   407,   409,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   190,   191,
     255,   515,   517,   615,   616,   617,   618,   620,   622,   623,
     625,   626,   627,   630,   632,   633,   634,   636,   638,   640,
      13,    14,   646,   647,   648,   650,     6,     3,     4,     8,
       3,   259,     3,     8,   266,   643,   312,   324,   326,   328,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   302,     4,     4,     4,     4,     4,
     285,   288,   290,     4,     4,     4,     4,   422,   458,   484,
       4,   305,   307,   450,   516,   518,   445,     4,     4,     4,
     377,   389,   383,   369,   567,   537,   398,   412,   581,     4,
     391,   594,   602,   612,   295,   297,     4,     4,     4,   652,
     676,     4,     3,     8,   318,     4,     4,     4,     4,     3,
       8,   503,   520,   432,   434,   436,     4,     4,   440,   438,
     562,     3,     8,   513,     4,     3,     8,   530,     4,   533,
       4,     4,     3,     8,   560,   548,   550,   552,   554,   556,
     558,     8,     3,     8,   474,   346,     4,   478,   476,   481,
       4,     8,     3,   496,     4,     4,     4,     8,     3,   408,
     410,     3,     8,     4,   619,   621,     4,   624,     4,     4,
     628,   631,     4,     4,   635,   637,   639,   641,     3,     8,
     649,     4,     3,     8,   240,   240,   220,     4,     4,     4,
       4,     4,     4,     4,   221,   221,   221,   221,   221,   221,
     221,   221,   223,   222,   222,   222,   221,   221,     4,   221,
     221,   223,   223,   223,     4,     4,     4,   223,   223,   222,
     223,     4,     4,     4,   221,     4,     4,     4,     4,     4,
       4,   223,   223,   223,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   221,     4,     4,     4,     4,     4,     4,
     223,   223,   223,     4,     4,   264,     4,   223,   223,   221,
     221,   316,     4,     4,     4,     4,     4,   221,   223,     4,
       4,     4,   430,     4,   221,   511,     4,   221,     4,   221,
     221,   528,     4,     4,     4,     4,     4,     4,     4,   546,
       4,     4,   221,     4,     4,     4,   223,   469,     4,   223,
     223,   223,   493,     4,     4,   406,   223,     4,     4,   221,
       4,   221,   221,     4,     4,   223,   223,     4,     4,     4,
       4,   616,     4,   221,   647,     4,     7,   220,     7,     7,
       7,     7,     5,   220,   186,   187,   188,   189,   223,   286,
     220,   220,     5,     5,     5,   220,   220,     5,   242,   244,
     220,   110,   111,   112,   113,   446,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   220,
     220,     5,     7,     5,   251,     5,     5,   220,   220,   220,
     251,   220,     7,   220,   220,   220,   251,   251,   251,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     244,   220,   220,   220,   183,   184,   629,   185,   286,   220,
     220,   220,     5,   240,   263,   646,   315,    24,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    45,    46,    47,    48,    49,   255,   333,   334,
     335,   338,   340,   342,   344,   345,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   358,   359,   360,   362,   364,
     366,   333,     7,   329,   330,   331,     7,   423,   424,   425,
       7,   461,   462,   463,     7,   485,   486,   487,     7,   451,
     452,   453,   133,   220,   378,   379,   380,   381,   249,   134,
     136,   380,   384,   385,   386,   387,   121,   122,   370,   371,
     372,   374,     7,   568,   569,     7,   538,   539,   540,     7,
     399,   400,   401,   143,   144,   145,   146,   147,   148,   413,
     414,   415,   416,   417,   418,   419,   420,    24,   153,   154,
     155,   156,   255,   347,   515,   517,   582,   583,   584,   587,
     588,   590,   591,   159,   160,   161,   255,   392,   393,   394,
     395,   396,   515,   517,   163,   164,   255,   515,   517,   595,
     596,   597,   599,   166,   167,   168,   220,   515,   517,   603,
     604,   605,   606,   608,   609,   615,     7,   653,   654,   205,
     255,   677,   678,   679,   252,     7,   504,   505,   506,     7,
     521,   522,   523,   138,   547,   563,   564,   329,     8,     8,
       8,   336,   339,   341,   343,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   356,     4,   361,   363,   365,
     367,     3,     8,     8,   332,     6,     3,   426,     6,     3,
     464,     6,     3,   488,     6,     3,   454,     6,     3,     3,
       6,     6,     3,     6,   373,   375,     3,     8,   570,     3,
       6,   541,     6,     3,   402,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   585,   589,     4,     4,     4,
       3,     8,     4,     4,     4,     3,     8,   598,   600,     3,
       8,     4,   607,     4,   610,     3,     8,     8,   655,     3,
       6,     4,     3,     8,   220,   253,   254,   507,     6,     3,
     524,     6,     3,   565,     8,     6,     4,     4,     4,     4,
     221,   223,   221,   223,   221,   221,   221,   221,   221,   221,
       4,   221,     4,     4,     4,     4,   334,   333,   331,   429,
     425,   467,   463,   491,   487,   255,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   281,
     282,   283,   284,   287,   289,   291,   292,   293,   294,   296,
     298,   304,   306,   345,   421,   433,   435,   437,   439,   441,
     442,   443,   444,   448,   455,   456,   483,   515,   517,   561,
     453,   379,   385,     4,     4,   371,   125,   126,   127,   255,
     267,   268,   269,   270,   271,   272,   345,   483,   515,   517,
     571,   572,   573,   574,   575,   577,   579,   569,   544,   540,
     405,   401,   221,   221,   221,   221,   221,   221,   414,     4,
       4,   221,   221,   221,   583,   223,   221,   221,   393,     4,
       4,   596,   223,     4,   221,     4,   604,   196,   198,   199,
     255,   345,   515,   517,   656,   657,   658,   659,   661,   654,
     223,   678,     6,     3,   510,   506,   527,   523,     4,    25,
      26,    27,   337,   220,   220,   220,    42,    43,    44,   357,
     220,   220,   220,   220,     8,     8,     8,     8,     3,     8,
     220,   220,   576,   578,     4,     8,     3,     8,     8,   150,
     151,   152,   586,   220,   220,   220,   220,   240,   662,     4,
     660,     3,     8,   220,     8,     8,   220,   456,     4,     4,
     223,   573,     4,   221,     4,   657,   220,   220,     5,   220,
       7,   663,   664,   665,     3,     6,   197,   200,   201,   202,
     203,   666,   667,   668,   670,   671,   672,   673,   664,   669,
       4,     4,     4,   674,     3,     8,     4,   223,   221,   221,
       4,   667,   220,   220
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   224,   226,   225,   227,   225,   228,   225,   229,   225,
     230,   225,   231,   225,   232,   225,   233,   225,   234,   225,
     235,   225,   236,   225,   237,   225,   238,   225,   239,   225,
     240,   240,   240,   240,   240,   240,   240,   241,   243,   242,
     244,   245,   245,   246,   246,   246,   248,   247,   249,   249,
     250,   250,   250,   252,   251,   253,   253,   254,   254,   254,
     255,   257,   256,   259,   258,   258,   260,   262,   261,   263,
     263,   263,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     266,   265,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   285,
     284,   286,   286,   286,   286,   286,   288,   287,   290,   289,
     291,   292,   293,   295,   294,   297,   296,   298,   299,   300,
     302,   301,   303,   305,   304,   307,   306,   308,   309,   310,
     312,   311,   314,   313,   315,   315,   315,   316,   316,   316,
     316,   316,   316,   316,   316,   318,   317,   319,   320,   321,
     322,   324,   323,   326,   325,   328,   327,   329,   329,   330,
     330,   330,   332,   331,   333,   333,   333,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   336,
     335,   337,   337,   337,   339,   338,   341,   340,   343,   342,
     344,   346,   345,   347,   348,   349,   350,   351,   352,   353,
     354,   356,   355,   357,   357,   357,   358,   359,   361,   360,
     363,   362,   365,   364,   367,   366,   369,   368,   370,   370,
     370,   371,   371,   373,   372,   375,   374,   377,   376,   378,
     378,   378,   379,   379,   380,   381,   383,   382,   384,   384,
     384,   385,   385,   385,   386,   387,   389,   388,   391,   390,
     392,   392,   392,   393,   393,   393,   393,   393,   393,   394,
     395,   396,   398,   397,   399,   399,   400,   400,   400,   402,
     401,   404,   403,   405,   405,   405,   405,   406,   406,   408,
     407,   410,   409,   412,   411,   413,   413,   413,   414,   414,
     414,   414,   414,   414,   415,   416,   417,   418,   419,   420,
     422,   421,   423,   423,   424,   424,   424,   426,   425,   428,
     427,   429,   429,   429,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     432,   431,   434,   433,   436,   435,   438,   437,   440,   439,
     441,   442,   443,   445,   444,   446,   446,   446,   446,   447,
     448,   450,   449,   451,   451,   452,   452,   452,   454,   453,
     455,   455,   455,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,   456,   458,   457,   460,   459,
     461,   461,   462,   462,   462,   464,   463,   466,   465,   467,
     467,   468,   468,   468,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   470,   471,   472,   474,   473,   476,
     475,   478,   477,   479,   481,   480,   482,   484,   483,   485,
     485,   486,   486,   486,   488,   487,   490,   489,   491,   491,
     492,   492,   492,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   494,   496,   495,   497,   498,   499,   500,
     501,   503,   502,   504,   504,   505,   505,   505,   507,   506,
     509,   508,   510,   510,   510,   511,   511,   511,   511,   511,
     511,   511,   511,   513,   512,   514,   516,   515,   518,   517,
     520,   519,   521,   521,   522,   522,   522,   524,   523,   526,
     525,   527,   527,   527,   528,   528,   528,   528,   528,   528,
     528,   528,   528,   528,   528,   530,   529,   531,   533,   532,
     534,   535,   537,   536,   538,   538,   539,   539,   539,   541,
     540,   543,   542,   544,   544,   545,   545,   545,   546,   546,
     546,   546,   546,   546,   546,   546,   546,   546,   546,   548,
     547,   550,   549,   552,   551,   554,   553,   556,   555,   558,
     557,   560,   559,   562,   561,   563,   563,   565,   564,   567,
     566,   568,   568,   568,   570,   569,   571,   571,   572,   572,
     572,   573,   573,   573,   573,   573,   573,   573,   573,   573,
     573,   573,   573,   573,   573,   574,   576,   575,   578,   577,
     579,   581,   580,   582,   582,   582,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   585,   584,   586,   586,   586,
     587,   589,   588,   590,   591,   592,   594,   593,   595,   595,
     595,   596,   596,   596,   596,   596,   598,   597,   600,   599,
     602,   601,   603,   603,   603,   604,   604,   604,   604,   604,
     604,   605,   607,   606,   608,   610,   609,   612,   611,   614,
     613,   615,   615,   615,   616,   616,   616,   616,   616,   616,
     616,   616,   616,   616,   616,   616,   616,   616,   616,   616,
     616,   616,   617,   619,   618,   621,   620,   622,   624,   623,
     625,   626,   628,   627,   629,   629,   631,   630,   632,   633,
     635,   634,   637,   636,   639,   638,   641,   640,   643,   642,
     645,   644,   646,   646,   646,   647,   647,   649,   648,   650,
     652,   651,   653,   653,   653,   655,   654,   656,   656,   656,
     657,   657,   657,   657,   657,   657,   657,   658,   660,   659,
     662,   661,   663,   663,   663,   665,   664,   666,   666,   666,
     667,   667,   667,   667,   667,   669,   668,   670,   671,   672,
     674,   673,   676,   675,   677,   677,   677,   678,   678,   679
  };

  const signed char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     2,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     0,     1,     1,     3,     2,
       2,     0,     4,     0,     6,     1,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     0,     4,     3,     3,     3,
       0,     4,     3,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       3,     0,     6,     0,     6,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     4,     0,
       6,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     0,     6,     3,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     3
  };


#if PARSER6_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"data-directory\"", "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"service-sockets-require-all\"",
  "\"service-sockets-retry-wait-time\"", "\"service-sockets-max-retries\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"max-row-errors\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
  "\"preferred-lifetime\"", "\"min-preferred-lifetime\"",
  "\"max-preferred-lifetime\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"ddns-ttl-percent\"", "\"store-extended-info\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"never-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"parked-packet-limit\"", "\"allocator\"", "\"pd-allocator\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"extended-info-checks\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"template-test\"",
  "\"only-if-required\"", "\"client-class\"", "\"pool-id\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"early-global-reservations-lookup\"",
  "\"ip-reservations-unique\"", "\"reservations-lookup-first\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"compatibility\"", "\"lenient-option-parsing\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "value", "sub_json", "map2", "$@15",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@16",
  "list_content", "not_empty_list", "list_strings", "$@17",
  "list_strings_content", "not_empty_list_strings", "unknown_map_entry",
  "syntax_map", "$@18", "global_object", "$@19", "global_object_comma",
  "sub_dhcp6", "$@20", "global_params", "global_param", "data_directory",
  "$@21", "preferred_lifetime", "min_preferred_lifetime",
  "max_preferred_lifetime", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "ddns_ttl_percent", "hostname_char_set", "$@25",
  "hostname_char_replacement", "$@26", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@27", "parked_packet_limit", "allocator", "$@28",
  "pd_allocator", "$@29", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@30", "sub_interfaces6", "$@31",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@32", "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@33", "hosts_database", "$@34", "hosts_databases",
  "$@35", "database_list", "not_empty_database_list", "database", "$@36",
  "database_map_params", "database_map_param", "database_type", "$@37",
  "db_type", "user", "$@38", "password", "$@39", "host", "$@40", "port",
  "name", "$@41", "persist", "lfc_interval", "readonly", "connect_timeout",
  "read_timeout", "write_timeout", "tcp_user_timeout",
  "reconnect_wait_time", "on_fail", "$@42", "on_fail_mode",
  "max_row_errors", "max_reconnect_tries", "trust_anchor", "$@43",
  "cert_file", "$@44", "key_file", "$@45", "cipher_list", "$@46",
  "sanity_checks", "$@47", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@48", "extended_info_checks", "$@49", "mac_sources",
  "$@50", "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@51",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@52",
  "dhcp_multi_threading", "$@53", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@54", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@55",
  "sub_hooks_library", "$@56", "hooks_params", "hooks_param", "library",
  "$@57", "parameters", "$@58", "expired_leases_processing", "$@59",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@60",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@61",
  "sub_subnet6", "$@62", "subnet6_params", "subnet6_param", "subnet",
  "$@63", "interface", "$@64", "interface_id", "$@65", "client_class",
  "$@66", "require_client_classes", "$@67", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@68", "hr_mode", "id", "rapid_commit", "shared_networks", "$@69",
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
  "$@84", "sub_pool6", "$@85", "pool_params", "pool_param", "pool_entry",
  "$@86", "pool_id", "user_context", "$@87", "comment", "$@88",
  "pd_pools_list", "$@89", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@90", "sub_pd_pool",
  "$@91", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@92",
  "pd_prefix_len", "excluded_prefix", "$@93", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@94", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@95", "sub_reservation",
  "$@96", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@97", "prefixes", "$@98", "duid",
  "$@99", "hw_address", "$@100", "hostname", "$@101", "flex_id_value",
  "$@102", "reservation_client_classes", "$@103", "relay", "$@104",
  "relay_map", "ip_address", "$@105", "client_classes", "$@106",
  "client_classes_list", "client_class_entry", "$@107",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@108",
  "client_class_template_test", "$@109", "only_if_required", "server_id",
  "$@110", "server_id_params", "server_id_param", "server_id_type",
  "$@111", "duid_type", "htype", "identifier", "$@112", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@113",
  "control_socket_params", "control_socket_param", "socket_type", "$@114",
  "socket_name", "$@115", "dhcp_queue_control", "$@116",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@117", "capacity", "arbitrary_map_entry", "$@118",
  "dhcp_ddns", "$@119", "sub_dhcp_ddns", "$@120", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@121",
  "server_ip", "$@122", "server_port", "sender_ip", "$@123", "sender_port",
  "max_queue_size", "ncr_protocol", "$@124", "ncr_protocol_value",
  "ncr_format", "$@125", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@126",
  "dep_generated_prefix", "$@127", "dep_hostname_char_set", "$@128",
  "dep_hostname_char_replacement", "$@129", "config_control", "$@130",
  "sub_config_control", "$@131", "config_control_params",
  "config_control_param", "config_databases", "$@132",
  "config_fetch_wait_time", "loggers", "$@133", "loggers_entries",
  "logger_entry", "$@134", "logger_params", "logger_param", "debuglevel",
  "severity", "$@135", "output_options_list", "$@136",
  "output_options_list_content", "output_entry", "$@137",
  "output_params_list", "output_params", "output", "$@138", "flush",
  "maxsize", "maxver", "pattern", "$@139", "compatibility", "$@140",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   317,   317,   317,   318,   318,   319,   319,   320,   320,
     321,   321,   322,   322,   323,   323,   324,   324,   325,   325,
     326,   326,   327,   327,   328,   328,   329,   329,   330,   330,
     338,   339,   340,   341,   342,   343,   344,   347,   352,   352,
     363,   366,   367,   370,   375,   381,   386,   386,   393,   394,
     397,   401,   405,   411,   411,   418,   419,   422,   426,   430,
     440,   449,   449,   464,   464,   478,   481,   487,   487,   496,
     497,   498,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     575,   575,   585,   591,   597,   603,   609,   615,   621,   627,
     633,   639,   645,   651,   657,   663,   669,   675,   681,   687,
     687,   696,   699,   702,   705,   708,   714,   714,   723,   723,
     732,   738,   744,   750,   750,   759,   759,   768,   774,   780,
     786,   786,   795,   801,   801,   810,   810,   819,   825,   831,
     837,   837,   849,   849,   858,   859,   860,   865,   866,   867,
     868,   869,   870,   871,   872,   875,   875,   886,   892,   898,
     904,   910,   910,   923,   923,   936,   936,   947,   948,   951,
     952,   953,   958,   958,   968,   969,   970,   975,   976,   977,
     978,   979,   980,   981,   982,   983,   984,   985,   986,   987,
     988,   989,   990,   991,   992,   993,   994,   995,   996,   999,
     999,  1007,  1008,  1009,  1012,  1012,  1021,  1021,  1030,  1030,
    1039,  1045,  1045,  1054,  1060,  1066,  1072,  1078,  1084,  1090,
    1097,  1103,  1103,  1111,  1112,  1113,  1116,  1122,  1128,  1128,
    1137,  1137,  1146,  1146,  1155,  1155,  1164,  1164,  1175,  1176,
    1177,  1182,  1183,  1186,  1186,  1205,  1205,  1223,  1223,  1234,
    1235,  1236,  1241,  1242,  1245,  1250,  1255,  1255,  1266,  1267,
    1268,  1273,  1274,  1275,  1278,  1283,  1290,  1290,  1303,  1303,
    1316,  1317,  1318,  1323,  1324,  1325,  1326,  1327,  1328,  1331,
    1337,  1343,  1349,  1349,  1360,  1361,  1364,  1365,  1366,  1371,
    1371,  1381,  1381,  1391,  1392,  1393,  1396,  1399,  1400,  1403,
    1403,  1412,  1412,  1421,  1421,  1433,  1434,  1435,  1440,  1441,
    1442,  1443,  1444,  1445,  1448,  1454,  1460,  1466,  1472,  1478,
    1487,  1487,  1501,  1502,  1505,  1506,  1507,  1516,  1516,  1542,
    1542,  1553,  1554,  1555,  1561,  1562,  1563,  1564,  1565,  1566,
    1567,  1568,  1569,  1570,  1571,  1572,  1573,  1574,  1575,  1576,
    1577,  1578,  1579,  1580,  1581,  1582,  1583,  1584,  1585,  1586,
    1587,  1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,
    1597,  1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,  1606,
    1609,  1609,  1618,  1618,  1627,  1627,  1636,  1636,  1645,  1645,
    1656,  1662,  1668,  1674,  1674,  1682,  1683,  1684,  1685,  1688,
    1694,  1702,  1702,  1714,  1715,  1719,  1720,  1721,  1726,  1726,
    1734,  1735,  1736,  1741,  1742,  1743,  1744,  1745,  1746,  1747,
    1748,  1749,  1750,  1751,  1752,  1753,  1754,  1755,  1756,  1757,
    1758,  1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,  1767,
    1768,  1769,  1770,  1771,  1772,  1773,  1774,  1775,  1776,  1777,
    1778,  1779,  1780,  1781,  1782,  1783,  1790,  1790,  1804,  1804,
    1813,  1814,  1817,  1818,  1819,  1826,  1826,  1841,  1841,  1855,
    1856,  1859,  1860,  1861,  1866,  1867,  1868,  1869,  1870,  1871,
    1872,  1873,  1874,  1875,  1878,  1880,  1886,  1888,  1888,  1897,
    1897,  1906,  1906,  1915,  1917,  1917,  1926,  1936,  1936,  1949,
    1950,  1955,  1956,  1957,  1964,  1964,  1976,  1976,  1988,  1989,
    1994,  1995,  1996,  2003,  2004,  2005,  2006,  2007,  2008,  2009,
    2010,  2011,  2012,  2015,  2017,  2017,  2026,  2028,  2030,  2036,
    2042,  2051,  2051,  2064,  2065,  2068,  2069,  2070,  2075,  2075,
    2085,  2085,  2095,  2096,  2097,  2102,  2103,  2104,  2105,  2106,
    2107,  2108,  2109,  2112,  2112,  2121,  2127,  2127,  2152,  2152,
    2182,  2182,  2195,  2196,  2199,  2200,  2201,  2206,  2206,  2218,
    2218,  2230,  2231,  2232,  2237,  2238,  2239,  2240,  2241,  2242,
    2243,  2244,  2245,  2246,  2247,  2250,  2250,  2259,  2265,  2265,
    2274,  2280,  2289,  2289,  2300,  2301,  2304,  2305,  2306,  2311,
    2311,  2320,  2320,  2329,  2330,  2333,  2334,  2335,  2341,  2342,
    2343,  2344,  2345,  2346,  2347,  2348,  2349,  2350,  2351,  2354,
    2354,  2365,  2365,  2376,  2376,  2385,  2385,  2394,  2394,  2403,
    2403,  2412,  2412,  2426,  2426,  2437,  2438,  2441,  2441,  2453,
    2453,  2464,  2465,  2466,  2471,  2471,  2481,  2482,  2485,  2486,
    2487,  2492,  2493,  2494,  2495,  2496,  2497,  2498,  2499,  2500,
    2501,  2502,  2503,  2504,  2505,  2508,  2510,  2510,  2519,  2519,
    2528,  2537,  2537,  2550,  2551,  2552,  2557,  2558,  2559,  2560,
    2561,  2562,  2563,  2564,  2565,  2568,  2568,  2576,  2577,  2578,
    2581,  2587,  2587,  2596,  2602,  2610,  2618,  2618,  2629,  2630,
    2631,  2636,  2637,  2638,  2639,  2640,  2643,  2643,  2652,  2652,
    2664,  2664,  2677,  2678,  2679,  2684,  2685,  2686,  2687,  2688,
    2689,  2692,  2698,  2698,  2707,  2713,  2713,  2723,  2723,  2736,
    2736,  2746,  2747,  2748,  2753,  2754,  2755,  2756,  2757,  2758,
    2759,  2760,  2761,  2762,  2763,  2764,  2765,  2766,  2767,  2768,
    2769,  2770,  2773,  2780,  2780,  2789,  2789,  2798,  2804,  2804,
    2813,  2819,  2825,  2825,  2834,  2835,  2838,  2838,  2848,  2855,
    2862,  2862,  2871,  2871,  2881,  2881,  2891,  2891,  2903,  2903,
    2915,  2915,  2925,  2926,  2927,  2933,  2934,  2937,  2937,  2948,
    2956,  2956,  2969,  2970,  2971,  2977,  2977,  2985,  2986,  2987,
    2992,  2993,  2994,  2995,  2996,  2997,  2998,  3001,  3007,  3007,
    3016,  3016,  3027,  3028,  3029,  3034,  3034,  3042,  3043,  3044,
    3049,  3050,  3051,  3052,  3053,  3056,  3056,  3065,  3071,  3077,
    3083,  3083,  3092,  3092,  3103,  3104,  3105,  3110,  3111,  3114
  };

  void
  Dhcp6Parser::yy_stack_print_ () const
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule) const
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 6545 "dhcp6_parser.cc"

#line 3120 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
