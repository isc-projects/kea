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

#line 52 "dhcp6_parser.cc"


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
#line 145 "dhcp6_parser.cc"

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
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 300 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 470 "dhcp6_parser.cc"
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
#line 309 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 310 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 311 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 312 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 313 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 314 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 315 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 316 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 317 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 318 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 319 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 320 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 321 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 322 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 330 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 331 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 332 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 333 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 334 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 335 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 336 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 339 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 344 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 349 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 355 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 362 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 367 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 373 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 378 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 381 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 389 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 393 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 397 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 403 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 405 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 414 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 418 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 422 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 432 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 441 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 446 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 63: // $@19: %empty
#line 456 "dhcp6_parser.yy"
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
#line 1071 "dhcp6_parser.cc"
    break;

  case 64: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 465 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 473 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 479 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 483 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 490 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 139: // $@21: %empty
#line 566 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 140: // data_directory: "data-directory" $@21 ":" "constant string"
#line 569 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 141: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 575 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 142: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 143: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 587 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 144: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 145: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 146: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 147: // renew_timer: "renew-timer" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 148: // rebind_timer: "rebind-timer" ":" "integer"
#line 617 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 149: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 623 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 150: // t1_percent: "t1-percent" ":" "floating point"
#line 629 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 151: // t2_percent: "t2-percent" ":" "floating point"
#line 635 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 152: // cache_threshold: "cache-threshold" ":" "floating point"
#line 641 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 153: // cache_max_age: "cache-max-age" ":" "integer"
#line 647 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 154: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 653 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 155: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 659 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 156: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 665 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 157: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 671 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 158: // $@22: %empty
#line 677 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 680 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "when-present"
#line 686 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "never"
#line 689 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "always"
#line 692 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-not-present"
#line 695 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "boolean"
#line 698 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 165: // $@23: %empty
#line 704 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 166: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 707 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 167: // $@24: %empty
#line 713 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 168: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 716 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 169: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 722 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 170: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 728 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 171: // $@25: %empty
#line 734 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 737 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 173: // $@26: %empty
#line 743 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 174: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 746 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // store_extended_info: "store-extended-info" ":" "boolean"
#line 752 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 176: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 758 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 177: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 764 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 178: // $@27: %empty
#line 770 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 179: // server_tag: "server-tag" $@27 ":" "constant string"
#line 773 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 180: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 779 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 181: // $@28: %empty
#line 785 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1528 "dhcp6_parser.cc"
    break;

  case 182: // allocator: "allocator" $@28 ":" "constant string"
#line 788 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1538 "dhcp6_parser.cc"
    break;

  case 183: // $@29: %empty
#line 794 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1547 "dhcp6_parser.cc"
    break;

  case 184: // pd_allocator: "pd-allocator" $@29 ":" "constant string"
#line 797 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1557 "dhcp6_parser.cc"
    break;

  case 185: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 803 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1567 "dhcp6_parser.cc"
    break;

  case 186: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 809 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 187: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 815 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 188: // $@30: %empty
#line 821 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 189: // interfaces_config: "interfaces-config" $@30 ":" "{" interfaces_config_params "}"
#line 827 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 190: // $@31: %empty
#line 833 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 191: // sub_interfaces6: "{" $@31 interfaces_config_params "}"
#line 837 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 194: // interfaces_config_params: interfaces_config_params ","
#line 844 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1636 "dhcp6_parser.cc"
    break;

  case 203: // $@32: %empty
#line 859 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 204: // interfaces_list: "interfaces" $@32 ":" list_strings
#line 865 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 205: // re_detect: "re-detect" ":" "boolean"
#line 870 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 206: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 876 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 207: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 882 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 208: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 888 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 209: // $@33: %empty
#line 894 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 210: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 900 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 211: // $@34: %empty
#line 907 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1732 "dhcp6_parser.cc"
    break;

  case 212: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 913 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1743 "dhcp6_parser.cc"
    break;

  case 213: // $@35: %empty
#line 920 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 214: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 926 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 219: // not_empty_database_list: not_empty_database_list ","
#line 937 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1772 "dhcp6_parser.cc"
    break;

  case 220: // $@36: %empty
#line 942 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 221: // database: "{" $@36 database_map_params "}"
#line 946 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 224: // database_map_params: database_map_params ","
#line 954 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1800 "dhcp6_parser.cc"
    break;

  case 247: // $@37: %empty
#line 983 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 248: // database_type: "type" $@37 ":" db_type
#line 986 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 249: // db_type: "memfile"
#line 991 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1824 "dhcp6_parser.cc"
    break;

  case 250: // db_type: "mysql"
#line 992 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1830 "dhcp6_parser.cc"
    break;

  case 251: // db_type: "postgresql"
#line 993 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1836 "dhcp6_parser.cc"
    break;

  case 252: // $@38: %empty
#line 996 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 253: // user: "user" $@38 ":" "constant string"
#line 999 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 254: // $@39: %empty
#line 1005 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 255: // password: "password" $@39 ":" "constant string"
#line 1008 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 256: // $@40: %empty
#line 1014 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 257: // host: "host" $@40 ":" "constant string"
#line 1017 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 258: // port: "port" ":" "integer"
#line 1023 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1903 "dhcp6_parser.cc"
    break;

  case 259: // $@41: %empty
#line 1029 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp6_parser.cc"
    break;

  case 260: // name: "name" $@41 ":" "constant string"
#line 1032 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 261: // persist: "persist" ":" "boolean"
#line 1038 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1932 "dhcp6_parser.cc"
    break;

  case 262: // lfc_interval: "lfc-interval" ":" "integer"
#line 1044 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 263: // readonly: "readonly" ":" "boolean"
#line 1050 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 264: // connect_timeout: "connect-timeout" ":" "integer"
#line 1056 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1962 "dhcp6_parser.cc"
    break;

  case 265: // read_timeout: "read-timeout" ":" "integer"
#line 1062 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 266: // write_timeout: "write-timeout" ":" "integer"
#line 1068 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 1982 "dhcp6_parser.cc"
    break;

  case 267: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1074 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 268: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1081 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1087 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 270: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1090 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2020 "dhcp6_parser.cc"
    break;

  case 271: // on_fail_mode: "stop-retry-exit"
#line 1095 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2026 "dhcp6_parser.cc"
    break;

  case 272: // on_fail_mode: "serve-retry-exit"
#line 1096 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2032 "dhcp6_parser.cc"
    break;

  case 273: // on_fail_mode: "serve-retry-continue"
#line 1097 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2038 "dhcp6_parser.cc"
    break;

  case 274: // max_row_errors: "max-row-errors" ":" "integer"
#line 1100 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2048 "dhcp6_parser.cc"
    break;

  case 275: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1106 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2058 "dhcp6_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1112 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 277: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1115 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 278: // $@44: %empty
#line 1121 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 279: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1124 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 280: // $@45: %empty
#line 1130 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 281: // key_file: "key-file" $@45 ":" "constant string"
#line 1133 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 282: // $@46: %empty
#line 1139 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp6_parser.cc"
    break;

  case 283: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1142 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 284: // $@47: %empty
#line 1148 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2146 "dhcp6_parser.cc"
    break;

  case 285: // sanity_checks: "sanity-checks" $@47 ":" "{" sanity_checks_params "}"
#line 1154 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 288: // sanity_checks_params: sanity_checks_params ","
#line 1161 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2163 "dhcp6_parser.cc"
    break;

  case 291: // $@48: %empty
#line 1170 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2172 "dhcp6_parser.cc"
    break;

  case 292: // lease_checks: "lease-checks" $@48 ":" "constant string"
#line 1173 "dhcp6_parser.yy"
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
#line 2192 "dhcp6_parser.cc"
    break;

  case 293: // $@49: %empty
#line 1189 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 294: // extended_info_checks: "extended-info-checks" $@49 ":" "constant string"
#line 1192 "dhcp6_parser.yy"
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
#line 2220 "dhcp6_parser.cc"
    break;

  case 295: // $@50: %empty
#line 1207 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2232 "dhcp6_parser.cc"
    break;

  case 296: // mac_sources: "mac-sources" $@50 ":" "[" mac_sources_list "]"
#line 1213 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2241 "dhcp6_parser.cc"
    break;

  case 299: // mac_sources_list: mac_sources_list ","
#line 1220 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2249 "dhcp6_parser.cc"
    break;

  case 302: // duid_id: "duid"
#line 1229 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 303: // string_id: "constant string"
#line 1234 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 304: // $@51: %empty
#line 1239 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2279 "dhcp6_parser.cc"
    break;

  case 305: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1245 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2288 "dhcp6_parser.cc"
    break;

  case 308: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1252 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2296 "dhcp6_parser.cc"
    break;

  case 312: // hw_address_id: "hw-address"
#line 1262 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 313: // flex_id: "flex-id"
#line 1267 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 314: // $@52: %empty
#line 1274 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 315: // relay_supplied_options: "relay-supplied-options" $@52 ":" "[" list_content "]"
#line 1280 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 316: // $@53: %empty
#line 1287 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2347 "dhcp6_parser.cc"
    break;

  case 317: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1293 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2358 "dhcp6_parser.cc"
    break;

  case 320: // multi_threading_params: multi_threading_params ","
#line 1302 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2366 "dhcp6_parser.cc"
    break;

  case 327: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1315 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2376 "dhcp6_parser.cc"
    break;

  case 328: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1321 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2386 "dhcp6_parser.cc"
    break;

  case 329: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1327 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2396 "dhcp6_parser.cc"
    break;

  case 330: // $@54: %empty
#line 1333 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 331: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1339 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 336: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1350 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2425 "dhcp6_parser.cc"
    break;

  case 337: // $@55: %empty
#line 1355 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2435 "dhcp6_parser.cc"
    break;

  case 338: // hooks_library: "{" $@55 hooks_params "}"
#line 1359 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2445 "dhcp6_parser.cc"
    break;

  case 339: // $@56: %empty
#line 1365 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp6_parser.cc"
    break;

  case 340: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1369 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 343: // hooks_params: hooks_params ","
#line 1377 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2473 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1387 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc"
    break;

  case 348: // library: "library" $@57 ":" "constant string"
#line 1390 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2492 "dhcp6_parser.cc"
    break;

  case 349: // $@58: %empty
#line 1396 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp6_parser.cc"
    break;

  case 350: // parameters: "parameters" $@58 ":" map_value
#line 1399 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2510 "dhcp6_parser.cc"
    break;

  case 351: // $@59: %empty
#line 1405 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2522 "dhcp6_parser.cc"
    break;

  case 352: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1411 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 355: // expired_leases_params: expired_leases_params ","
#line 1419 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2540 "dhcp6_parser.cc"
    break;

  case 362: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1432 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 363: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1438 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 364: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1444 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 365: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1450 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 366: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1456 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 367: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1462 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 368: // $@60: %empty
#line 1471 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2612 "dhcp6_parser.cc"
    break;

  case 369: // subnet6_list: "subnet6" $@60 ":" "[" subnet6_list_content "]"
#line 1477 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc"
    break;

  case 374: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1491 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2629 "dhcp6_parser.cc"
    break;

  case 375: // $@61: %empty
#line 1500 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2639 "dhcp6_parser.cc"
    break;

  case 376: // subnet6: "{" $@61 subnet6_params "}"
#line 1504 "dhcp6_parser.yy"
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
#line 2665 "dhcp6_parser.cc"
    break;

  case 377: // $@62: %empty
#line 1526 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 378: // sub_subnet6: "{" $@62 subnet6_params "}"
#line 1530 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 381: // subnet6_params: subnet6_params ","
#line 1539 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2693 "dhcp6_parser.cc"
    break;

  case 427: // $@63: %empty
#line 1592 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp6_parser.cc"
    break;

  case 428: // subnet: "subnet" $@63 ":" "constant string"
#line 1595 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 429: // $@64: %empty
#line 1601 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp6_parser.cc"
    break;

  case 430: // interface: "interface" $@64 ":" "constant string"
#line 1604 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2731 "dhcp6_parser.cc"
    break;

  case 431: // $@65: %empty
#line 1610 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp6_parser.cc"
    break;

  case 432: // interface_id: "interface-id" $@65 ":" "constant string"
#line 1613 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2750 "dhcp6_parser.cc"
    break;

  case 433: // $@66: %empty
#line 1619 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp6_parser.cc"
    break;

  case 434: // client_class: "client-class" $@66 ":" "constant string"
#line 1622 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2769 "dhcp6_parser.cc"
    break;

  case 435: // $@67: %empty
#line 1628 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 436: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1634 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2790 "dhcp6_parser.cc"
    break;

  case 437: // reservations_global: "reservations-global" ":" "boolean"
#line 1639 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2800 "dhcp6_parser.cc"
    break;

  case 438: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1645 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2810 "dhcp6_parser.cc"
    break;

  case 439: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1651 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2820 "dhcp6_parser.cc"
    break;

  case 440: // $@68: %empty
#line 1657 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 441: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1660 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 442: // hr_mode: "disabled"
#line 1665 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2844 "dhcp6_parser.cc"
    break;

  case 443: // hr_mode: "out-of-pool"
#line 1666 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2850 "dhcp6_parser.cc"
    break;

  case 444: // hr_mode: "global"
#line 1667 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2856 "dhcp6_parser.cc"
    break;

  case 445: // hr_mode: "all"
#line 1668 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2862 "dhcp6_parser.cc"
    break;

  case 446: // id: "id" ":" "integer"
#line 1671 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2872 "dhcp6_parser.cc"
    break;

  case 447: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1677 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 448: // $@69: %empty
#line 1685 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 449: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1691 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 454: // shared_networks_list: shared_networks_list ","
#line 1704 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2911 "dhcp6_parser.cc"
    break;

  case 455: // $@70: %empty
#line 1709 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 456: // shared_network: "{" $@70 shared_network_params "}"
#line 1713 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2929 "dhcp6_parser.cc"
    break;

  case 459: // shared_network_params: shared_network_params ","
#line 1719 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2937 "dhcp6_parser.cc"
    break;

  case 502: // $@71: %empty
#line 1772 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2949 "dhcp6_parser.cc"
    break;

  case 503: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1778 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2958 "dhcp6_parser.cc"
    break;

  case 504: // $@72: %empty
#line 1786 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2967 "dhcp6_parser.cc"
    break;

  case 505: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1789 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2975 "dhcp6_parser.cc"
    break;

  case 510: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1801 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2983 "dhcp6_parser.cc"
    break;

  case 511: // $@73: %empty
#line 1808 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 512: // option_def_entry: "{" $@73 option_def_params "}"
#line 1812 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 513: // $@74: %empty
#line 1823 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 514: // sub_option_def: "{" $@74 option_def_params "}"
#line 1827 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 519: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1843 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3035 "dhcp6_parser.cc"
    break;

  case 531: // code: "code" ":" "integer"
#line 1862 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 533: // $@75: %empty
#line 1870 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 534: // option_def_type: "type" $@75 ":" "constant string"
#line 1873 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 535: // $@76: %empty
#line 1879 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp6_parser.cc"
    break;

  case 536: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1882 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 537: // $@77: %empty
#line 1888 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp6_parser.cc"
    break;

  case 538: // space: "space" $@77 ":" "constant string"
#line 1891 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3102 "dhcp6_parser.cc"
    break;

  case 540: // $@78: %empty
#line 1899 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 541: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1902 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 542: // option_def_array: "array" ":" "boolean"
#line 1908 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 543: // $@79: %empty
#line 1918 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3143 "dhcp6_parser.cc"
    break;

  case 544: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1924 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3152 "dhcp6_parser.cc"
    break;

  case 549: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1939 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3160 "dhcp6_parser.cc"
    break;

  case 550: // $@80: %empty
#line 1946 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 551: // option_data_entry: "{" $@80 option_data_params "}"
#line 1950 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 552: // $@81: %empty
#line 1958 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 553: // sub_option_data: "{" $@81 option_data_params "}"
#line 1962 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 558: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1978 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3206 "dhcp6_parser.cc"
    break;

  case 569: // $@82: %empty
#line 1998 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp6_parser.cc"
    break;

  case 570: // option_data_data: "data" $@82 ":" "constant string"
#line 2001 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc"
    break;

  case 573: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2011 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3235 "dhcp6_parser.cc"
    break;

  case 574: // option_data_always_send: "always-send" ":" "boolean"
#line 2017 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3245 "dhcp6_parser.cc"
    break;

  case 575: // $@83: %empty
#line 2026 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 576: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2032 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 581: // not_empty_pools_list: not_empty_pools_list ","
#line 2045 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3274 "dhcp6_parser.cc"
    break;

  case 582: // $@84: %empty
#line 2050 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 583: // pool_list_entry: "{" $@84 pool_params "}"
#line 2054 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 584: // $@85: %empty
#line 2060 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 585: // sub_pool6: "{" $@85 pool_params "}"
#line 2064 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 588: // pool_params: pool_params ","
#line 2072 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3322 "dhcp6_parser.cc"
    break;

  case 596: // $@86: %empty
#line 2086 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3331 "dhcp6_parser.cc"
    break;

  case 597: // pool_entry: "pool" $@86 ":" "constant string"
#line 2089 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3341 "dhcp6_parser.cc"
    break;

  case 598: // $@87: %empty
#line 2095 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 599: // user_context: "user-context" $@87 ":" map_value
#line 2097 "dhcp6_parser.yy"
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
#line 3376 "dhcp6_parser.cc"
    break;

  case 600: // $@88: %empty
#line 2120 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 601: // comment: "comment" $@88 ":" "constant string"
#line 2122 "dhcp6_parser.yy"
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
#line 3413 "dhcp6_parser.cc"
    break;

  case 602: // $@89: %empty
#line 2150 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3425 "dhcp6_parser.cc"
    break;

  case 603: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2156 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3434 "dhcp6_parser.cc"
    break;

  case 608: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2169 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3442 "dhcp6_parser.cc"
    break;

  case 609: // $@90: %empty
#line 2174 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3452 "dhcp6_parser.cc"
    break;

  case 610: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2178 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3464 "dhcp6_parser.cc"
    break;

  case 611: // $@91: %empty
#line 2186 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3474 "dhcp6_parser.cc"
    break;

  case 612: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2190 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3486 "dhcp6_parser.cc"
    break;

  case 615: // pd_pool_params: pd_pool_params ","
#line 2200 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3494 "dhcp6_parser.cc"
    break;

  case 627: // $@92: %empty
#line 2218 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3503 "dhcp6_parser.cc"
    break;

  case 628: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2221 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3513 "dhcp6_parser.cc"
    break;

  case 629: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2227 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3523 "dhcp6_parser.cc"
    break;

  case 630: // $@93: %empty
#line 2233 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3532 "dhcp6_parser.cc"
    break;

  case 631: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2236 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 632: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2242 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 633: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2248 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 634: // $@94: %empty
#line 2257 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 635: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2263 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3583 "dhcp6_parser.cc"
    break;

  case 640: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2274 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3591 "dhcp6_parser.cc"
    break;

  case 641: // $@95: %empty
#line 2279 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3601 "dhcp6_parser.cc"
    break;

  case 642: // reservation: "{" $@95 reservation_params "}"
#line 2283 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3610 "dhcp6_parser.cc"
    break;

  case 643: // $@96: %empty
#line 2288 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3620 "dhcp6_parser.cc"
    break;

  case 644: // sub_reservation: "{" $@96 reservation_params "}"
#line 2292 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3629 "dhcp6_parser.cc"
    break;

  case 649: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2303 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3637 "dhcp6_parser.cc"
    break;

  case 661: // $@97: %empty
#line 2322 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 662: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2328 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 663: // $@98: %empty
#line 2333 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3670 "dhcp6_parser.cc"
    break;

  case 664: // prefixes: "prefixes" $@98 ":" list_strings
#line 2339 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3679 "dhcp6_parser.cc"
    break;

  case 665: // $@99: %empty
#line 2344 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3688 "dhcp6_parser.cc"
    break;

  case 666: // duid: "duid" $@99 ":" "constant string"
#line 2347 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3698 "dhcp6_parser.cc"
    break;

  case 667: // $@100: %empty
#line 2353 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3707 "dhcp6_parser.cc"
    break;

  case 668: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2356 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 669: // $@101: %empty
#line 2362 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3726 "dhcp6_parser.cc"
    break;

  case 670: // hostname: "hostname" $@101 ":" "constant string"
#line 2365 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 671: // $@102: %empty
#line 2371 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3745 "dhcp6_parser.cc"
    break;

  case 672: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2374 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 673: // $@103: %empty
#line 2380 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 674: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2386 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 675: // $@104: %empty
#line 2394 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3788 "dhcp6_parser.cc"
    break;

  case 676: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2400 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3797 "dhcp6_parser.cc"
    break;

  case 679: // $@105: %empty
#line 2409 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3806 "dhcp6_parser.cc"
    break;

  case 680: // ip_address: "ip-address" $@105 ":" "constant string"
#line 2412 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3816 "dhcp6_parser.cc"
    break;

  case 681: // $@106: %empty
#line 2421 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3828 "dhcp6_parser.cc"
    break;

  case 682: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2427 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3837 "dhcp6_parser.cc"
    break;

  case 685: // client_classes_list: client_classes_list ","
#line 2434 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3845 "dhcp6_parser.cc"
    break;

  case 686: // $@107: %empty
#line 2439 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 687: // client_class_entry: "{" $@107 client_class_params "}"
#line 2443 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3865 "dhcp6_parser.cc"
    break;

  case 692: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2455 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3873 "dhcp6_parser.cc"
    break;

  case 708: // $@108: %empty
#line 2478 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 709: // client_class_test: "test" $@108 ":" "constant string"
#line 2481 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 710: // $@109: %empty
#line 2487 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 711: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2490 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 712: // only_if_required: "only-if-required" ":" "boolean"
#line 2496 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 713: // $@110: %empty
#line 2505 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 714: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2511 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3944 "dhcp6_parser.cc"
    break;

  case 717: // server_id_params: server_id_params ","
#line 2520 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3952 "dhcp6_parser.cc"
    break;

  case 727: // $@111: %empty
#line 2536 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3961 "dhcp6_parser.cc"
    break;

  case 728: // server_id_type: "type" $@111 ":" duid_type
#line 2539 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 729: // duid_type: "LLT"
#line 2544 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3976 "dhcp6_parser.cc"
    break;

  case 730: // duid_type: "EN"
#line 2545 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3982 "dhcp6_parser.cc"
    break;

  case 731: // duid_type: "LL"
#line 2546 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3988 "dhcp6_parser.cc"
    break;

  case 732: // htype: "htype" ":" "integer"
#line 2549 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3998 "dhcp6_parser.cc"
    break;

  case 733: // $@112: %empty
#line 2555 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4007 "dhcp6_parser.cc"
    break;

  case 734: // identifier: "identifier" $@112 ":" "constant string"
#line 2558 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4017 "dhcp6_parser.cc"
    break;

  case 735: // time: "time" ":" "integer"
#line 2564 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 736: // enterprise_id: "enterprise-id" ":" "integer"
#line 2570 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4037 "dhcp6_parser.cc"
    break;

  case 737: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2578 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4047 "dhcp6_parser.cc"
    break;

  case 738: // $@113: %empty
#line 2586 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4059 "dhcp6_parser.cc"
    break;

  case 739: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2592 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4068 "dhcp6_parser.cc"
    break;

  case 742: // control_socket_params: control_socket_params ","
#line 2599 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4076 "dhcp6_parser.cc"
    break;

  case 748: // $@114: %empty
#line 2611 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4085 "dhcp6_parser.cc"
    break;

  case 749: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2614 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4095 "dhcp6_parser.cc"
    break;

  case 750: // $@115: %empty
#line 2620 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4104 "dhcp6_parser.cc"
    break;

  case 751: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2623 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4114 "dhcp6_parser.cc"
    break;

  case 752: // $@116: %empty
#line 2632 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4126 "dhcp6_parser.cc"
    break;

  case 753: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2638 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 756: // queue_control_params: queue_control_params ","
#line 2647 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4145 "dhcp6_parser.cc"
    break;

  case 763: // enable_queue: "enable-queue" ":" "boolean"
#line 2660 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4155 "dhcp6_parser.cc"
    break;

  case 764: // $@117: %empty
#line 2666 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4164 "dhcp6_parser.cc"
    break;

  case 765: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2669 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4174 "dhcp6_parser.cc"
    break;

  case 766: // capacity: "capacity" ":" "integer"
#line 2675 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4184 "dhcp6_parser.cc"
    break;

  case 767: // $@118: %empty
#line 2681 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4193 "dhcp6_parser.cc"
    break;

  case 768: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2684 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4202 "dhcp6_parser.cc"
    break;

  case 769: // $@119: %empty
#line 2691 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 770: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2697 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4225 "dhcp6_parser.cc"
    break;

  case 771: // $@120: %empty
#line 2704 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4235 "dhcp6_parser.cc"
    break;

  case 772: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2708 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 775: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2716 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4253 "dhcp6_parser.cc"
    break;

  case 794: // enable_updates: "enable-updates" ":" "boolean"
#line 2741 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 795: // $@121: %empty
#line 2748 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 796: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2751 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 797: // $@122: %empty
#line 2757 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4291 "dhcp6_parser.cc"
    break;

  case 798: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2760 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4301 "dhcp6_parser.cc"
    break;

  case 799: // server_port: "server-port" ":" "integer"
#line 2766 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4311 "dhcp6_parser.cc"
    break;

  case 800: // $@123: %empty
#line 2772 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4320 "dhcp6_parser.cc"
    break;

  case 801: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2775 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4330 "dhcp6_parser.cc"
    break;

  case 802: // sender_port: "sender-port" ":" "integer"
#line 2781 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4340 "dhcp6_parser.cc"
    break;

  case 803: // max_queue_size: "max-queue-size" ":" "integer"
#line 2787 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4350 "dhcp6_parser.cc"
    break;

  case 804: // $@124: %empty
#line 2793 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 805: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2796 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4368 "dhcp6_parser.cc"
    break;

  case 806: // ncr_protocol_value: "UDP"
#line 2802 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4374 "dhcp6_parser.cc"
    break;

  case 807: // ncr_protocol_value: "TCP"
#line 2803 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4380 "dhcp6_parser.cc"
    break;

  case 808: // $@125: %empty
#line 2806 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4389 "dhcp6_parser.cc"
    break;

  case 809: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2809 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4399 "dhcp6_parser.cc"
    break;

  case 810: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2816 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 811: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2823 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4419 "dhcp6_parser.cc"
    break;

  case 812: // $@126: %empty
#line 2830 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4428 "dhcp6_parser.cc"
    break;

  case 813: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2833 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4437 "dhcp6_parser.cc"
    break;

  case 814: // $@127: %empty
#line 2839 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4446 "dhcp6_parser.cc"
    break;

  case 815: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2842 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4456 "dhcp6_parser.cc"
    break;

  case 816: // $@128: %empty
#line 2849 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4465 "dhcp6_parser.cc"
    break;

  case 817: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2852 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4475 "dhcp6_parser.cc"
    break;

  case 818: // $@129: %empty
#line 2859 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4484 "dhcp6_parser.cc"
    break;

  case 819: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2862 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4494 "dhcp6_parser.cc"
    break;

  case 820: // $@130: %empty
#line 2871 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4506 "dhcp6_parser.cc"
    break;

  case 821: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2877 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4516 "dhcp6_parser.cc"
    break;

  case 822: // $@131: %empty
#line 2883 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4526 "dhcp6_parser.cc"
    break;

  case 823: // sub_config_control: "{" $@131 config_control_params "}"
#line 2887 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4535 "dhcp6_parser.cc"
    break;

  case 826: // config_control_params: config_control_params ","
#line 2895 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4543 "dhcp6_parser.cc"
    break;

  case 829: // $@132: %empty
#line 2905 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4555 "dhcp6_parser.cc"
    break;

  case 830: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2911 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4564 "dhcp6_parser.cc"
    break;

  case 831: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2916 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4574 "dhcp6_parser.cc"
    break;

  case 832: // $@133: %empty
#line 2924 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4586 "dhcp6_parser.cc"
    break;

  case 833: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2930 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4595 "dhcp6_parser.cc"
    break;

  case 836: // loggers_entries: loggers_entries ","
#line 2939 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4603 "dhcp6_parser.cc"
    break;

  case 837: // $@134: %empty
#line 2945 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4613 "dhcp6_parser.cc"
    break;

  case 838: // logger_entry: "{" $@134 logger_params "}"
#line 2949 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4621 "dhcp6_parser.cc"
    break;

  case 841: // logger_params: logger_params ","
#line 2955 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4629 "dhcp6_parser.cc"
    break;

  case 849: // debuglevel: "debuglevel" ":" "integer"
#line 2969 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4639 "dhcp6_parser.cc"
    break;

  case 850: // $@135: %empty
#line 2975 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4648 "dhcp6_parser.cc"
    break;

  case 851: // severity: "severity" $@135 ":" "constant string"
#line 2978 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4658 "dhcp6_parser.cc"
    break;

  case 852: // $@136: %empty
#line 2984 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4670 "dhcp6_parser.cc"
    break;

  case 853: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 2990 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4679 "dhcp6_parser.cc"
    break;

  case 856: // output_options_list_content: output_options_list_content ","
#line 2997 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4687 "dhcp6_parser.cc"
    break;

  case 857: // $@137: %empty
#line 3002 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4697 "dhcp6_parser.cc"
    break;

  case 858: // output_entry: "{" $@137 output_params_list "}"
#line 3006 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4705 "dhcp6_parser.cc"
    break;

  case 861: // output_params_list: output_params_list ","
#line 3012 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4713 "dhcp6_parser.cc"
    break;

  case 867: // $@138: %empty
#line 3024 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4722 "dhcp6_parser.cc"
    break;

  case 868: // output: "output" $@138 ":" "constant string"
#line 3027 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4732 "dhcp6_parser.cc"
    break;

  case 869: // flush: "flush" ":" "boolean"
#line 3033 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4742 "dhcp6_parser.cc"
    break;

  case 870: // maxsize: "maxsize" ":" "integer"
#line 3039 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4752 "dhcp6_parser.cc"
    break;

  case 871: // maxver: "maxver" ":" "integer"
#line 3045 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4762 "dhcp6_parser.cc"
    break;

  case 872: // $@139: %empty
#line 3051 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4771 "dhcp6_parser.cc"
    break;

  case 873: // pattern: "pattern" $@139 ":" "constant string"
#line 3054 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4781 "dhcp6_parser.cc"
    break;

  case 874: // $@140: %empty
#line 3060 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4793 "dhcp6_parser.cc"
    break;

  case 875: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3066 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4802 "dhcp6_parser.cc"
    break;

  case 878: // compatibility_params: compatibility_params ","
#line 3073 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4810 "dhcp6_parser.cc"
    break;

  case 881: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3082 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4820 "dhcp6_parser.cc"
    break;


#line 4824 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1018;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     443, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018,    90,    35,    56,    70,    94,
      98,   104,   112,   116,   161,   185,   205,   249,   251,   268,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,    35,   -27,
     292,   172,    63,   684,   203,    -4,    78,   221,    88,   327,
     -92,   457,   299, -1018,   294,   307,   326,   316,   330, -1018,
      49, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   335,   342,
     345,   353,   370,   393,   394,   401,   408,   421,   431,   432,
     437,   438, -1018,   444,   445,   447,   448,   449, -1018, -1018,
   -1018,   450,   451,   452, -1018, -1018, -1018,   453, -1018, -1018,
   -1018, -1018, -1018, -1018,   454,   455,   456, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   459, -1018, -1018, -1018,
   -1018, -1018, -1018,   460,   462,   464, -1018, -1018,   465, -1018,
      50, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   467,
     470,   471,   473, -1018,    58, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   474,   475,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
     101, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018,   105, -1018, -1018, -1018, -1018,
   -1018,   477, -1018,   481,   482, -1018, -1018, -1018, -1018, -1018,
   -1018,   126, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   340,
     363, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   425,
   -1018, -1018,   484, -1018, -1018, -1018,   485, -1018, -1018,   439,
     492, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,   494,   495, -1018, -1018, -1018, -1018,
     488,   497, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,   128, -1018, -1018, -1018,   498, -1018,
   -1018,   500, -1018,   501,   506, -1018, -1018,   508,   509, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   140, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,   511,   143, -1018, -1018, -1018, -1018,
      35,    35, -1018,   304,   512, -1018, -1018,   519,   520,   521,
     522,   525,   527,   314,   317,   318,   319,   321,   323,   324,
     325,   331,   315,   333,   336,   338,   341,   534,   343,   350,
     334,   349,   351,   541,   568,   569,   355,   356,   358,   575,
     578,   579,   368,   584,   585,   586,   587,   589,   590,   376,
     380,   381,   599,   600,   602,   603,   604,   607,   609,   610,
     611,   399,   614,   615,   616,   617,   618,   633,   418,   419,
     420,   637,   638, -1018,   172, -1018,   639,   440,   441,   446,
     461,    63, -1018,   659,   662,   663,   664,   665,   463,   458,
     666,   667,   668,   684, -1018,   669,   203, -1018,   671,   466,
     673,   468,   469,    -4, -1018,   676,   678,   679,   681,   685,
     686,   687, -1018,    78, -1018,   688,   689,   476,   691,   692,
     693,   478, -1018,    88,   695,   483,   486, -1018,   327,   701,
     703,   -70, -1018,   489,   706,   712,   499,   714,   502,   503,
     715,   719,   504,   505,   722,   723,   724,   725,   457, -1018,
     726,   513,   299, -1018, -1018, -1018,   728,   740,   531,   742,
     743,   753,   754,   683, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   546, -1018,
   -1018, -1018, -1018, -1018,    31,   547,   548, -1018, -1018, -1018,
     761,   762,   770, -1018,   560,   562,   775,   774,   565,   110,
   -1018, -1018, -1018,   778,   787,   788,   792,   789,   790,   795,
     794,   796, -1018,   797,   798,   800,   801,   592,   595, -1018,
   -1018, -1018,   808,   807, -1018,   810, -1018, -1018, -1018, -1018,
   -1018,   811,   812,   605,   606,   608, -1018, -1018,   810,   612,
     813, -1018,   613, -1018,   619, -1018,   620, -1018, -1018, -1018,
     810,   810,   810,   621,   622,   623,   624, -1018,   625,   626,
   -1018,   627,   628,   629, -1018, -1018,   630, -1018, -1018, -1018,
     631,   774, -1018, -1018,   632,   634, -1018,   635, -1018, -1018,
    -130,   642, -1018, -1018,    31,   636,   640,   641, -1018,   814,
   -1018, -1018,    35,   172, -1018,   299,    63,   347,   347,   819,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   820,
     821,   824, -1018, -1018,   825, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018,   -91,    35,   225,   216,   826,   827,   828,
      60,   250,    40,   -45,   253,   457, -1018, -1018,   843,  -155,
   -1018, -1018,   847,   848, -1018, -1018, -1018, -1018, -1018,   -87,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   819,
   -1018,   150,   158,   168, -1018, -1018, -1018, -1018,   817,   852,
     855,   856,   857,   858,   859,   860,   861,   862, -1018,   863,
   -1018, -1018, -1018, -1018, -1018,   174, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   177, -1018,
     864,   799, -1018, -1018,   867,   865, -1018, -1018,   868,   866,
   -1018, -1018,   869,   873, -1018, -1018,   871,   875, -1018, -1018,
   -1018,   127, -1018, -1018, -1018,   874, -1018, -1018, -1018,   141,
   -1018, -1018, -1018, -1018, -1018,   183, -1018, -1018, -1018, -1018,
     159, -1018, -1018,   876,   878, -1018, -1018,   877,   881, -1018,
     882,   883,   884,   885,   886,   887,   256, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   888,   889,   890, -1018,
   -1018, -1018, -1018,   263, -1018, -1018, -1018, -1018, -1018, -1018,
     891,   892,   893, -1018,   275, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   289, -1018, -1018, -1018,
     894, -1018,   895, -1018, -1018, -1018,   298, -1018, -1018, -1018,
   -1018, -1018,   306, -1018,   262, -1018,   896, -1018,   320, -1018,
   -1018,   690, -1018,   879,   899, -1018, -1018,   897,   901, -1018,
   -1018, -1018,   898, -1018,   902, -1018, -1018, -1018,   905,   906,
     907,   908,   661,   694,   697,   696,   699,   700,   702,   704,
     705,   707,   909,   708,   915,   917,   920,   923,   347, -1018,
   -1018,   347, -1018,   819,   684, -1018,   820,    88, -1018,   821,
     327, -1018,   824,  1076, -1018,   825,   -91, -1018, -1018,   225,
   -1018,   924,   925,   216, -1018,   290,   826, -1018,    78, -1018,
     827,   -92, -1018,   828,   713,   716,   717,   718,   720,   721,
      60, -1018,   926,   928,   727,   729,   730,   250, -1018,   731,
     732,   734,    40, -1018,   929,   933,   -45, -1018,   733,   936,
     736,   937,   253, -1018, -1018,   -36,   843, -1018,   735,  -155,
   -1018, -1018,   938,   939,   203, -1018,   847,    -4, -1018,   848,
     942, -1018, -1018,   413,   739,   741,   744, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018,   379, -1018,   745,
     747,   748,   750, -1018,   329, -1018,   344, -1018,   935, -1018,
     941, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
     362, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   751,
     756, -1018, -1018, -1018,   953, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   951,   957, -1018, -1018,
   -1018, -1018, -1018, -1018,   962, -1018,   364, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018,   297,   758, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018,   759,   765, -1018, -1018,   772,
   -1018,    35, -1018, -1018,   967, -1018, -1018, -1018, -1018, -1018,
     396, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   776,
     416, -1018,   426, -1018,   786, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,  1076, -1018, -1018, -1018,   975,  1000,
     785, -1018,   290, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,  1003,   805,  1004,   -36, -1018, -1018,
   -1018, -1018, -1018, -1018,   822,   829, -1018, -1018,   900, -1018,
     834, -1018, -1018, -1018,  1011, -1018, -1018,   288, -1018,   122,
    1011, -1018, -1018,  1021,  1023,  1034, -1018,   429, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018,  1039,   836,   842,   903,  1041,
     122, -1018,   844, -1018, -1018, -1018,   849, -1018, -1018, -1018
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   190,     9,   377,    11,
     584,    13,   611,    15,   643,    17,   504,    19,   513,    21,
     552,    23,   339,    25,   771,    27,   822,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   645,     0,   515,   554,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   139,   820,   188,   209,   211,   213,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,     0,     0,     0,     0,     0,   158,   165,
     167,     0,     0,     0,   368,   502,   543,     0,   181,   183,
     448,   598,   600,   440,     0,     0,     0,   295,   314,   304,
     284,   681,   634,   330,   351,   713,     0,   316,   738,   752,
     769,   171,   173,     0,     0,     0,   832,   874,     0,   138,
       0,    69,    72,    73,    74,    75,    76,    77,    78,    79,
      80,   111,   112,   113,   114,   115,    81,   119,   120,   121,
     122,   123,   124,   125,   126,   117,   118,   127,   128,   129,
     106,   135,   136,   137,   131,   132,   133,    84,    85,    86,
      87,   103,    88,    90,    89,   130,    94,    95,    82,   108,
     109,   110,   107,    83,    92,    93,   101,   102,   104,    91,
      96,    97,    98,    99,   100,   105,   116,   134,   203,     0,
       0,     0,     0,   202,     0,   192,   195,   196,   197,   198,
     199,   200,   201,   575,   602,   427,   429,   431,     0,     0,
     435,   433,   675,   426,   382,   383,   384,   385,   386,   387,
     388,   389,   408,   409,   410,   411,   412,   415,   416,   417,
     418,   419,   420,   421,   422,   413,   414,   423,   424,   425,
       0,   379,   393,   394,   395,   398,   399,   402,   403,   404,
     401,   396,   397,   390,   391,   406,   407,   392,   400,   405,
     596,   595,   591,   592,   590,     0,   586,   589,   593,   594,
     627,     0,   630,     0,     0,   626,   620,   621,   619,   624,
     625,     0,   613,   616,   617,   622,   623,   618,   673,   661,
     663,   665,   667,   669,   671,   660,   657,   658,   659,     0,
     646,   647,   652,   653,   650,   654,   655,   656,   651,     0,
     533,   259,     0,   537,   535,   540,     0,   529,   530,     0,
     516,   517,   520,   532,   521,   522,   523,   539,   524,   525,
     526,   527,   528,   569,     0,     0,   567,   568,   571,   572,
       0,   555,   556,   559,   560,   561,   562,   563,   564,   565,
     566,   347,   349,   344,     0,   341,   345,   346,     0,   795,
     797,     0,   800,     0,     0,   804,   808,     0,     0,   812,
     814,   816,   818,   793,   791,   792,     0,   773,   776,   788,
     777,   778,   779,   780,   781,   782,   783,   784,   785,   786,
     787,   789,   790,   829,     0,     0,   824,   827,   828,    47,
      52,     0,    39,    45,     0,    66,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   194,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   381,   378,     0,   588,   585,     0,     0,
       0,     0,     0,   615,   612,     0,     0,     0,     0,     0,
       0,     0,   644,   649,   505,     0,     0,     0,     0,     0,
       0,     0,   514,   519,     0,     0,     0,   553,   558,     0,
       0,   343,   340,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   775,   772,
       0,     0,   826,   823,    51,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,     0,   176,
     177,   155,   156,   157,     0,     0,     0,   169,   170,   175,
       0,     0,     0,   180,     0,     0,     0,     0,     0,     0,
     437,   438,   439,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   737,     0,     0,     0,     0,     0,     0,   185,
     186,   187,     0,     0,    70,     0,   205,   206,   207,   208,
     193,     0,     0,     0,     0,     0,   446,   447,     0,     0,
       0,   380,     0,   587,     0,   629,     0,   632,   633,   614,
       0,     0,     0,     0,     0,     0,     0,   648,     0,     0,
     531,     0,     0,     0,   542,   518,     0,   573,   574,   557,
       0,     0,   342,   794,     0,     0,   799,     0,   802,   803,
       0,     0,   810,   811,     0,     0,     0,     0,   774,     0,
     831,   825,     0,     0,   140,     0,     0,     0,     0,   215,
     179,   160,   161,   162,   163,   164,   159,   166,   168,   370,
     506,   545,   182,   184,   450,    40,   599,   601,   442,   443,
     444,   445,   441,     0,    48,     0,     0,     0,   636,   332,
       0,     0,     0,     0,     0,     0,   172,   174,     0,     0,
      53,   204,   577,   604,   428,   430,   432,   436,   434,     0,
     597,   628,   631,   674,   662,   664,   666,   668,   670,   672,
     534,   260,   538,   536,   541,   570,   348,   350,   796,   798,
     801,   806,   807,   805,   809,   813,   815,   817,   819,   215,
      44,     0,     0,     0,   247,   252,   254,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   269,     0,
     276,   278,   280,   282,   246,     0,   222,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     239,   240,   241,   238,   242,   243,   244,   245,     0,   220,
       0,   216,   217,   375,     0,   371,   372,   511,     0,   507,
     508,   550,     0,   546,   547,   455,     0,   451,   452,   302,
     303,     0,   297,   300,   301,     0,   312,   313,   309,     0,
     306,   310,   311,   291,   293,     0,   286,   289,   290,   686,
       0,   683,   641,     0,   637,   638,   337,     0,   333,   334,
       0,     0,     0,     0,     0,     0,     0,   353,   356,   357,
     358,   359,   360,   361,   727,   733,     0,     0,     0,   726,
     723,   724,   725,     0,   715,   718,   721,   719,   720,   722,
       0,     0,     0,   326,     0,   318,   321,   322,   323,   324,
     325,   748,   750,   747,   745,   746,     0,   740,   743,   744,
       0,   764,     0,   767,   760,   761,     0,   754,   757,   758,
     759,   762,     0,   837,     0,   834,     0,   880,     0,   876,
     879,    55,   582,     0,   578,   579,   609,     0,   605,   606,
     679,   678,     0,   677,     0,    64,   821,   189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   224,   210,
     212,     0,   214,   219,     0,   369,   374,   515,   503,   510,
     554,   544,   549,     0,   449,   454,   299,   296,   315,   308,
     305,     0,     0,   288,   285,   688,   685,   682,   645,   635,
     640,     0,   331,   336,     0,     0,     0,     0,     0,     0,
     355,   352,     0,     0,     0,     0,     0,   717,   714,     0,
       0,     0,   320,   317,     0,     0,   742,   739,     0,     0,
       0,     0,   756,   753,   770,     0,   836,   833,     0,   878,
     875,    57,     0,    56,     0,   576,   581,     0,   603,   608,
       0,   676,   830,     0,     0,     0,     0,   258,   261,   262,
     263,   264,   265,   266,   267,   275,   268,     0,   274,     0,
       0,     0,     0,   223,     0,   218,     0,   373,     0,   509,
       0,   548,   501,   474,   475,   476,   478,   479,   480,   464,
     465,   483,   484,   485,   486,   487,   490,   491,   492,   493,
     494,   495,   496,   497,   488,   489,   498,   499,   500,   460,
     461,   462,   463,   472,   473,   469,   470,   471,   468,   477,
       0,   457,   466,   481,   482,   467,   453,   298,   307,     0,
       0,   287,   708,   710,     0,   706,   700,   701,   702,   703,
     704,   705,   707,   697,   698,   699,     0,   689,   690,   693,
     694,   695,   696,   684,     0,   639,     0,   335,   362,   363,
     364,   365,   366,   367,   354,     0,     0,   732,   735,   736,
     716,   327,   328,   329,   319,     0,     0,   741,   763,     0,
     766,     0,   755,   852,     0,   850,   848,   842,   846,   847,
       0,   839,   844,   845,   843,   835,   881,   877,    54,    59,
       0,   580,     0,   607,     0,   249,   250,   251,   248,   253,
     255,   257,   271,   272,   273,   270,   277,   279,   281,   283,
     221,   376,   512,   551,   459,   456,   292,   294,     0,     0,
       0,   687,   692,   642,   338,   729,   730,   731,   728,   734,
     749,   751,   765,   768,     0,     0,     0,   841,   838,    58,
     583,   610,   680,   458,     0,     0,   712,   691,     0,   849,
       0,   840,   709,   711,     0,   851,   857,     0,   854,     0,
     856,   853,   867,     0,     0,     0,   872,     0,   859,   862,
     863,   864,   865,   866,   855,     0,     0,     0,     0,     0,
     861,   858,     0,   869,   870,   871,     0,   860,   868,   873
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   -10, -1018,  -583, -1018,
     375, -1018, -1018, -1018, -1018,   352, -1018,  -592, -1018, -1018,
   -1018,   -71, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   385,
     581, -1018, -1018,   -46,   -43,   -14,   -13,    14,    15,   -49,
     -24,    16,    29,    30,    33,    34, -1018,    37,    41,    44,
      47, -1018,   400,    48, -1018,    51, -1018,    54,    59,    62,
   -1018,    64, -1018,    65, -1018, -1018, -1018, -1018, -1018,    66,
   -1018,    69, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
     389,   643, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,   322, -1018,   106, -1018,  -716,   114,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
     -41, -1018,  -760, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,    87, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018,   107,  -742, -1018, -1018, -1018, -1018,
     108, -1018, -1018, -1018, -1018, -1018, -1018, -1018,    74, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,    95, -1018, -1018, -1018,
      99,   588, -1018, -1018, -1018, -1018, -1018, -1018, -1018,    91,
   -1018, -1018, -1018, -1018, -1018, -1018, -1017, -1018, -1018, -1018,
     131, -1018, -1018, -1018,   129,   645, -1018, -1018, -1015, -1018,
   -1014, -1018,    10, -1018,    80, -1018,    72,    76,    77,    79,
   -1018, -1018, -1018, -1008, -1018, -1018, -1018, -1018,   117, -1018,
   -1018,  -116,  1092, -1018, -1018, -1018, -1018, -1018,   132, -1018,
   -1018, -1018,   133, -1018,   644, -1018,   -62, -1018, -1018, -1018,
   -1018, -1018,   -54, -1018, -1018, -1018, -1018, -1018,   -42, -1018,
   -1018, -1018,   130, -1018, -1018, -1018,   134, -1018,   646, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
      67, -1018, -1018, -1018,    71,   649, -1018, -1018,   -60, -1018,
      -3, -1018, -1018, -1018, -1018, -1018,    82, -1018, -1018, -1018,
      85,   650, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   -53,
   -1018, -1018, -1018,   121, -1018, -1018, -1018,   136, -1018,   647,
     397, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1007, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018,   139, -1018, -1018, -1018,   -96, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018,   120, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   113,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018,   109, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   428,   651,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,   480,
     648, -1018, -1018, -1018, -1018, -1018, -1018,   115, -1018, -1018,
    -103, -1018, -1018, -1018, -1018, -1018, -1018,  -125, -1018, -1018,
    -144, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018, -1018,
   -1018,   118, -1018
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     756,    87,    88,    41,    68,    84,    85,   781,   991,  1102,
    1103,   844,    43,    70,    90,   444,    91,    45,    71,   160,
     161,   162,   447,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   473,   746,   181,   474,   182,   475,   183,   184,   185,
     506,   186,   507,   187,   188,   189,   190,   467,   191,   192,
     483,   193,   484,   194,   195,   196,   197,   449,    47,    72,
     234,   235,   236,   516,   237,   238,   239,   240,   198,   450,
     199,   451,   200,   452,   870,   871,   872,  1031,   845,   846,
     847,  1008,  1268,   848,  1009,   849,  1010,   850,  1011,   851,
     852,   556,   853,   854,   855,   856,   857,   858,   859,   860,
     861,  1022,  1275,   862,   863,   864,  1024,   865,  1025,   866,
    1026,   867,  1027,   201,   495,   905,   906,   907,  1051,   908,
    1052,   202,   492,   891,   892,   893,   894,   203,   494,   899,
     900,   901,   902,   204,   493,   205,   502,   954,   955,   956,
     957,   958,   206,   498,   917,   918,   919,  1061,    63,    80,
     394,   395,   396,   569,   397,   570,   207,   499,   926,   927,
     928,   929,   930,   931,   932,   933,   208,   479,   874,   875,
     876,  1034,    49,    73,   280,   281,   282,   525,   283,   526,
     284,   527,   285,   531,   286,   530,   209,   210,   211,   212,
     488,   762,   291,   292,   213,   485,   886,   887,   888,  1043,
    1180,  1181,   214,   480,    57,    77,   878,   879,   880,  1037,
      59,    78,   359,   360,   361,   362,   363,   364,   365,   555,
     366,   559,   367,   558,   368,   369,   560,   370,   215,   481,
     882,   883,   884,  1040,    61,    79,   380,   381,   382,   383,
     384,   564,   385,   386,   387,   388,   294,   523,   993,   994,
     995,  1104,    51,    74,   305,   306,   307,   535,   216,   486,
     217,   487,   297,   524,   997,   998,   999,  1107,    53,    75,
     321,   322,   323,   538,   324,   325,   540,   326,   327,   218,
     497,   913,   914,   915,  1058,    55,    76,   339,   340,   341,
     342,   546,   343,   547,   344,   548,   345,   549,   346,   550,
     347,   551,   348,   545,   299,   532,  1002,  1003,  1110,   219,
     496,   910,   911,  1055,  1206,  1207,  1208,  1209,  1210,  1288,
    1211,  1289,  1212,   220,   500,   943,   944,   945,  1072,  1298,
     946,   947,  1073,   948,   949,   221,   222,   503,   966,   967,
     968,  1084,   969,  1085,   223,   504,   976,   977,   978,   979,
    1089,   980,   981,  1091,   224,   505,    65,    81,   416,   417,
     418,   419,   574,   420,   575,   421,   422,   577,   423,   424,
     425,   580,   813,   426,   581,   427,   428,   429,   584,   430,
     585,   431,   586,   432,   587,   225,   448,    67,    82,   435,
     436,   437,   590,   438,   226,   511,   984,   985,  1095,  1250,
    1251,  1252,  1253,  1306,  1254,  1304,  1327,  1328,  1329,  1337,
    1338,  1339,  1345,  1340,  1341,  1342,  1343,  1349,   227,   512,
     988,   989,   990
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     159,   233,   253,   301,   315,   335,    38,   357,   376,   393,
     413,   940,   241,   295,   308,   319,   337,   378,   371,   389,
     298,   414,   868,   898,   260,   379,  1170,   254,  1171,  1172,
     255,   293,   304,   318,   336,  1179,  1185,   358,   377,   889,
      31,   329,    32,   351,    33,   391,   392,   986,  1000,   261,
     811,   812,   445,   514,   755,   131,   132,   446,   515,   256,
     257,   521,   158,    42,   131,   132,   522,   391,   392,   242,
     296,   309,   320,   338,   126,   372,   390,    44,   415,   228,
     229,   230,   231,   232,   302,   316,   787,   258,   259,   262,
      30,   310,   311,   312,   313,   314,   131,   132,   793,   794,
     795,    46,   263,   264,   533,    48,   265,   266,   536,   534,
     267,    50,   350,   537,   268,   961,   962,   269,   250,    52,
     270,   271,   251,    54,   272,   158,   890,   273,   755,   543,
    1046,   571,   274,  1047,   544,   275,   572,   276,   277,   278,
     131,   132,   279,   588,  1049,   287,   592,  1050,   589,   288,
     289,   593,   290,   514,   303,   317,   126,  1243,  1005,  1244,
    1245,   592,  1056,   131,   132,  1057,  1006,   351,    56,   352,
     353,   521,   158,   354,   355,   356,  1007,  1028,   131,   132,
    1028,   158,  1029,    92,    93,  1030,  1053,    94,   131,   132,
      86,  1054,    58,    95,    96,    97,   950,   951,   952,   328,
     920,   921,   922,   923,   924,   925,   329,   330,   331,   332,
     333,   334,    60,   158,   741,   742,   743,   744,   758,   759,
     760,   761,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   745,    34,    35,    36,    37,    62,   158,    64,  1070,
     127,   128,   129,   130,  1071,  1096,  1077,  1170,  1097,  1171,
    1172,  1078,   131,   132,   934,    66,  1179,  1185,  1082,   133,
     158,   126,   829,  1083,   134,   135,   136,   137,   138,   139,
     140,  1330,  1086,   141,  1331,   158,   300,  1087,   125,   142,
     439,  1092,    89,   131,   132,   158,  1093,   898,   143,   588,
     440,   144,   433,   434,  1094,  1134,  1332,   940,   145,  1333,
    1334,  1335,  1336,  1099,   442,   250,   146,   147,  1100,   251,
     441,   148,  1028,   443,   149,   903,   904,  1280,   150,   453,
      98,    99,   100,   101,   102,   103,   454,   533,   552,   455,
     131,   132,  1281,   131,   132,   889,   896,   456,   897,   151,
     152,   153,   154,   155,   156,  1284,   553,   571,   126,   351,
    1285,   824,  1294,   157,   457,   825,   826,   827,   828,   829,
     830,   831,   832,   833,   834,   835,   836,   837,   838,   158,
     131,   132,   839,   840,   841,   842,   843,   458,   459,  1307,
     935,   936,   937,   938,  1308,   460,   351,   373,   352,   353,
     374,   375,   461,  1192,  1193,  1194,   970,   971,   972,   536,
     158,  1272,  1273,  1274,  1310,   462,   351,   131,   132,   543,
     594,   595,  1350,   554,  1311,   463,   464,  1351,  1265,  1266,
    1267,   465,   466,   159,  1295,  1296,  1297,   562,   468,   469,
     233,   470,   471,   472,   476,   477,   478,   482,   489,   490,
     491,   241,   253,   501,   508,   301,   509,   158,   510,   513,
     973,   517,   315,   295,   518,   519,   308,   520,   528,   529,
     298,   539,   335,   319,   260,   541,   542,   254,   557,   561,
     255,   293,   357,   337,   304,   563,   567,   376,   565,   566,
     568,   318,   573,   371,   576,   578,   378,   158,   389,   261,
     579,   336,   582,   583,   379,   591,   597,   413,   242,   256,
     257,   596,   358,   598,   599,   600,   601,   377,   414,   602,
     296,   603,   604,   309,   613,   605,   606,   607,   618,   608,
     320,   609,   610,   611,   158,   624,   302,   258,   259,   262,
     338,   612,   614,   316,   621,   615,   616,   131,   132,   617,
     372,   619,   263,   264,   158,   390,   265,   266,   620,   622,
     267,   623,   625,   626,   268,   627,   628,   269,   629,   630,
     270,   271,   631,   632,   272,   415,   633,   273,   634,   635,
     636,   637,   274,   638,   639,   275,   640,   276,   277,   278,
     641,   642,   279,   643,   644,   287,   645,   646,   647,   288,
     289,   648,   290,   649,   650,   651,   303,   652,   653,   654,
     655,   656,   657,   317,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   658,   659,   660,
     661,   662,   663,   665,   411,   412,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     666,   667,   159,   671,   668,   233,   672,   673,   674,   675,
     678,   679,   680,   682,   158,   684,   241,   686,   677,   669,
     690,   676,   691,   692,   685,   693,   687,   688,   739,   694,
     695,   696,   698,   699,   700,   701,   702,   703,   704,   706,
     939,   953,   963,   707,   413,   710,   708,   711,   987,   713,
     714,   941,   959,   964,   974,   414,   715,   716,   717,   720,
     718,   719,   820,   721,   722,   723,   724,   725,   726,   727,
     729,   730,   732,   242,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   733,   734,   735,
     736,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     737,   738,   126,   740,   747,   748,   749,   750,   942,   960,
     965,   975,   415,   128,   129,   751,   243,   752,   244,   753,
     754,    32,   757,   763,   131,   132,   245,   246,   247,   248,
     249,   133,   764,   765,   767,   768,   134,   135,   136,   766,
     769,   770,  1033,   771,   772,   773,   250,   774,   775,   776,
     251,   142,   777,   778,   779,   780,   782,   783,   252,   819,
     789,  1012,   784,   785,   814,   786,   869,   873,   877,   788,
     790,   881,   885,   909,   912,   916,   791,   792,   796,   797,
     798,   799,   800,   801,   802,   803,   804,   805,   806,   808,
     983,   809,   810,   816,   992,   996,  1013,   817,   818,  1014,
    1015,  1016,  1017,  1018,  1019,  1020,  1021,  1023,  1036,  1039,
    1032,   151,   152,  1035,  1038,  1041,  1042,  1044,  1045,  1117,
    1048,  1060,  1059,  1062,  1063,  1105,  1064,  1065,  1066,  1067,
    1068,  1069,  1074,  1075,  1076,  1079,  1080,  1081,  1088,  1090,
    1098,   158,  1106,  1108,  1109,  1324,  1111,  1101,  1112,  1113,
    1114,  1115,  1116,  1127,  1118,  1119,  1120,  1121,  1122,  1129,
    1123,  1130,  1124,  1125,  1131,  1126,  1128,  1132,  1189,  1190,
    1225,  1218,  1226,  1235,  1219,  1220,  1221,  1236,  1222,  1223,
    1239,  1241,  1259,  1282,  1258,  1227,  1264,  1228,  1229,  1283,
    1232,  1231,  1233,  1238,  1240,  1256,  1269,  1290,  1270,  1291,
    1292,  1271,  1276,   253,  1277,  1278,   357,  1279,  1286,   376,
    1293,  1305,  1142,  1287,   295,  1299,  1300,   371,   378,  1314,
     389,   298,  1301,  1183,  1195,   260,   379,   335,   254,  1302,
     393,   255,   293,  1309,  1149,  1204,   358,  1143,   337,   377,
    1144,  1182,  1169,  1312,  1315,  1316,   939,  1318,  1320,  1196,
     261,   953,  1197,  1203,  1202,   963,   336,   941,  1326,  1150,
     256,   257,   959,  1319,  1246,  1346,   964,  1347,   987,  1145,
    1146,   296,   974,   301,   372,  1248,   315,   390,  1348,  1322,
    1184,  1198,  1199,  1352,   308,  1356,  1323,   319,   258,   259,
     262,  1325,  1205,  1173,  1247,   338,  1353,  1147,  1148,  1151,
    1354,  1358,   304,   263,   264,   318,  1359,   265,   266,  1200,
    1201,   267,  1152,  1153,   942,   268,  1154,  1155,   269,   960,
    1156,   270,   271,   965,  1157,   272,   807,  1158,   273,   975,
    1159,  1160,  1249,   274,  1161,   664,   275,  1162,   276,   277,
     278,   309,  1163,   279,   320,  1164,   287,  1165,  1166,  1167,
     288,   289,  1168,   290,   302,  1175,   895,   316,   821,  1176,
    1177,  1355,  1178,  1174,   815,   823,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,  1135,
    1191,  1004,  1133,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,  1187,   126,   351,  1234,  1188,  1217,   712,
    1216,  1224,  1186,  1136,   670,   128,   129,  1137,  1313,   349,
    1138,  1139,  1141,  1261,  1140,  1260,   131,   132,   681,   246,
     247,  1215,   249,   133,   303,   683,  1001,   317,   134,   135,
     136,  1263,  1262,   689,  1214,  1213,  1317,  1230,   250,  1237,
     697,  1242,   251,   982,  1321,  1344,  1357,   705,     0,     0,
     252,  1255,     0,  1142,   709,   822,     0,  1257,     0,     0,
       0,  1195,     0,     0,  1183,     0,     0,     0,     0,     0,
       0,  1303,  1204,     0,     0,  1149,  1246,     0,  1143,   728,
     731,  1144,  1182,  1169,     0,     0,  1196,  1248,     0,  1197,
    1203,  1202,     0,     0,     0,     0,     0,     0,     0,     0,
    1150,     0,     0,   151,   152,     0,  1247,     0,     0,     0,
    1145,  1146,     0,     0,     0,     0,     0,     0,  1198,  1199,
       0,  1184,     0,     0,     0,     0,     0,     0,     0,  1205,
       0,     0,     0,   158,  1173,     0,     0,     0,  1147,  1148,
    1151,     0,     0,     0,  1249,     0,  1200,  1201,     0,     0,
       0,     0,     0,  1152,  1153,     0,     0,  1154,  1155,     0,
       0,  1156,     0,     0,     0,  1157,     0,     0,  1158,     0,
       0,  1159,  1160,     0,     0,  1161,     0,     0,  1162,     0,
       0,     0,     0,  1163,     0,     0,  1164,     0,  1165,  1166,
    1167,     0,     0,  1168,     0,     0,  1175,     0,     0,     0,
    1176,  1177,     0,  1178,  1174
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   771,    72,    73,    74,    75,    76,    79,    78,    79,
      73,    81,   738,   765,    73,    79,  1043,    73,  1043,  1043,
      73,    73,    74,    75,    76,  1043,  1043,    78,    79,   130,
       5,   128,     7,    79,     9,   137,   138,   202,   135,    73,
     180,   181,     3,     3,   637,   100,   101,     8,     8,    73,
      73,     3,   217,     7,   100,   101,     8,   137,   138,    72,
      73,    74,    75,    76,    78,    78,    79,     7,    81,    16,
      17,    18,    19,    20,    74,    75,   678,    73,    73,    73,
       0,    95,    96,    97,    98,    99,   100,   101,   690,   691,
     692,     7,    73,    73,     3,     7,    73,    73,     3,     8,
      73,     7,    24,     8,    73,   160,   161,    73,   122,     7,
      73,    73,   126,     7,    73,   217,   217,    73,   711,     3,
       3,     3,    73,     6,     8,    73,     8,    73,    73,    73,
     100,   101,    73,     3,     3,    73,     3,     6,     8,    73,
      73,     8,    73,     3,    74,    75,    78,   193,     8,   195,
     196,     3,     3,   100,   101,     6,     8,    79,     7,    81,
      82,     3,   217,    85,    86,    87,     8,     3,   100,   101,
       3,   217,     8,    11,    12,     8,     3,    15,   100,   101,
     217,     8,     7,    21,    22,    23,   156,   157,   158,   121,
     140,   141,   142,   143,   144,   145,   128,   129,   130,   131,
     132,   133,     7,   217,   183,   184,   185,   186,   108,   109,
     110,   111,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,   220,   217,   218,   219,   220,     7,   217,     7,     3,
      88,    89,    90,    91,     8,     3,     3,  1284,     6,  1284,
    1284,     8,   100,   101,    24,     7,  1284,  1284,     3,   107,
     217,    78,    32,     8,   112,   113,   114,   115,   116,   117,
     118,     3,     3,   121,     6,   217,    93,     8,    77,   127,
       6,     3,    10,   100,   101,   217,     8,  1049,   136,     3,
       3,   139,    13,    14,     8,  1031,   194,  1077,   146,   197,
     198,   199,   200,     3,     8,   122,   154,   155,     8,   126,
       4,   159,     3,     3,   162,   119,   120,     8,   166,     4,
      50,    51,    52,    53,    54,    55,     4,     3,     8,     4,
     100,   101,     8,   100,   101,   130,   131,     4,   133,   187,
     188,   189,   190,   191,   192,     3,     3,     3,    78,    79,
       8,    24,     8,   201,     4,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,   217,
     100,   101,    45,    46,    47,    48,    49,     4,     4,     3,
     150,   151,   152,   153,     8,     4,    79,    80,    81,    82,
      83,    84,     4,   123,   124,   125,   163,   164,   165,     3,
     217,    42,    43,    44,     8,     4,    79,   100,   101,     3,
     440,   441,     3,     8,     8,     4,     4,     8,    25,    26,
      27,     4,     4,   514,   147,   148,   149,     8,     4,     4,
     521,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   521,   533,     4,     4,   536,     4,   217,     4,     4,
     217,     4,   543,   533,     4,     4,   536,     4,     4,     4,
     533,     4,   553,   543,   533,     4,     4,   533,     4,     4,
     533,   533,   563,   553,   536,     3,     8,   568,     4,     4,
       3,   543,     4,   563,     4,     4,   568,   217,   568,   533,
       4,   553,     4,     4,   568,     4,     4,   588,   521,   533,
     533,   217,   563,     4,     4,     4,     4,   568,   588,     4,
     533,     4,   218,   536,   219,   218,   218,   218,     4,   218,
     543,   218,   218,   218,   217,     4,   536,   533,   533,   533,
     553,   220,   219,   543,   220,   219,   218,   100,   101,   218,
     563,   218,   533,   533,   217,   568,   533,   533,   218,   220,
     533,   220,     4,     4,   533,   220,   220,   533,   220,     4,
     533,   533,     4,     4,   533,   588,   218,   533,     4,     4,
       4,     4,   533,     4,     4,   533,   220,   533,   533,   533,
     220,   220,   533,     4,     4,   533,     4,     4,     4,   533,
     533,     4,   533,     4,     4,     4,   536,   218,     4,     4,
       4,     4,     4,   543,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,     4,   220,   220,
     220,     4,     4,     4,   187,   188,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     220,   220,   733,     4,   218,   736,     4,     4,     4,     4,
       4,     4,     4,     4,   217,     4,   736,     4,   220,   218,
       4,   218,     4,     4,   218,     4,   218,   218,     5,     4,
       4,     4,     4,     4,   218,     4,     4,     4,   220,     4,
     771,   772,   773,   220,   775,     4,   220,     4,   779,   220,
       4,   771,   772,   773,   774,   775,     4,   218,     4,     4,
     218,   218,   732,     4,   220,   220,     4,     4,     4,     4,
       4,   218,     4,   736,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     7,   217,     7,
       7,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       7,     7,    78,   217,   217,   217,     5,     5,   771,   772,
     773,   774,   775,    89,    90,     5,    92,   217,    94,   217,
       5,     7,   217,     5,   100,   101,   102,   103,   104,   105,
     106,   107,     5,     5,     5,     5,   112,   113,   114,     7,
       5,     7,     3,     7,     7,     7,   122,     7,     7,   217,
     126,   127,   217,     5,     7,     5,     5,     5,   134,     5,
       7,     4,   217,   217,   182,   217,     7,     7,     7,   217,
     217,     7,     7,     7,     7,     7,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
       7,   217,   217,   217,     7,     7,     4,   217,   217,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       6,   187,   188,     6,     6,     6,     3,     6,     3,   218,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   217,     3,     6,     3,     5,     8,   217,     6,     4,
       4,     4,     4,     4,   220,   218,   220,   218,   218,     4,
     218,     4,   218,   218,     4,   218,   218,     4,     4,     4,
       4,   218,     4,     4,   218,   218,   218,     4,   218,   218,
       4,     4,     3,     8,     6,   218,     4,   218,   218,     8,
     218,   220,   218,   220,   218,   220,   217,     4,   217,     8,
       3,   217,   217,  1034,   217,   217,  1037,   217,   217,  1040,
       8,     4,  1043,   217,  1034,   217,   217,  1037,  1040,     4,
    1040,  1034,   217,  1043,  1055,  1034,  1040,  1058,  1034,   217,
    1061,  1034,  1034,   217,  1043,  1055,  1037,  1043,  1058,  1040,
    1043,  1043,  1043,   217,     4,   220,  1077,     4,     4,  1055,
    1034,  1082,  1055,  1055,  1055,  1086,  1058,  1077,     7,  1043,
    1034,  1034,  1082,   218,  1095,     4,  1086,     4,  1099,  1043,
    1043,  1034,  1092,  1104,  1037,  1095,  1107,  1040,     4,   217,
    1043,  1055,  1055,     4,  1104,     4,   217,  1107,  1034,  1034,
    1034,   217,  1055,  1043,  1095,  1058,   220,  1043,  1043,  1043,
     218,   217,  1104,  1034,  1034,  1107,   217,  1034,  1034,  1055,
    1055,  1034,  1043,  1043,  1077,  1034,  1043,  1043,  1034,  1082,
    1043,  1034,  1034,  1086,  1043,  1034,   711,  1043,  1034,  1092,
    1043,  1043,  1095,  1034,  1043,   514,  1034,  1043,  1034,  1034,
    1034,  1104,  1043,  1034,  1107,  1043,  1034,  1043,  1043,  1043,
    1034,  1034,  1043,  1034,  1104,  1043,   764,  1107,   733,  1043,
    1043,   218,  1043,  1043,   724,   736,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,  1033,
    1053,   819,  1028,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,  1046,    78,    79,  1082,  1049,  1063,   571,
    1061,  1070,  1045,  1034,   521,    89,    90,  1036,  1284,    77,
    1037,  1039,  1042,  1106,  1040,  1104,   100,   101,   533,   103,
     104,  1060,   106,   107,  1104,   536,   789,  1107,   112,   113,
     114,  1109,  1107,   543,  1058,  1056,  1292,  1077,   122,  1086,
     553,  1092,   126,   775,  1307,  1330,  1350,   563,    -1,    -1,
     134,  1096,    -1,  1284,   568,   735,    -1,  1099,    -1,    -1,
      -1,  1292,    -1,    -1,  1284,    -1,    -1,    -1,    -1,    -1,
      -1,  1241,  1292,    -1,    -1,  1284,  1307,    -1,  1284,   588,
     592,  1284,  1284,  1284,    -1,    -1,  1292,  1307,    -1,  1292,
    1292,  1292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1284,    -1,    -1,   187,   188,    -1,  1307,    -1,    -1,    -1,
    1284,  1284,    -1,    -1,    -1,    -1,    -1,    -1,  1292,  1292,
      -1,  1284,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1292,
      -1,    -1,    -1,   217,  1284,    -1,    -1,    -1,  1284,  1284,
    1284,    -1,    -1,    -1,  1307,    -1,  1292,  1292,    -1,    -1,
      -1,    -1,    -1,  1284,  1284,    -1,    -1,  1284,  1284,    -1,
      -1,  1284,    -1,    -1,    -1,  1284,    -1,    -1,  1284,    -1,
      -1,  1284,  1284,    -1,    -1,  1284,    -1,    -1,  1284,    -1,
      -1,    -1,    -1,  1284,    -1,    -1,  1284,    -1,  1284,  1284,
    1284,    -1,    -1,  1284,    -1,    -1,  1284,    -1,    -1,    -1,
    1284,  1284,    -1,  1284,  1284
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
       0,     5,     7,     9,   217,   218,   219,   220,   237,   238,
     239,   244,     7,   253,     7,   258,     7,   309,     7,   423,
       7,   503,     7,   519,     7,   536,     7,   455,     7,   461,
       7,   485,     7,   399,     7,   607,     7,   638,   245,   240,
     254,   259,   310,   424,   504,   520,   537,   456,   462,   486,
     400,   608,   639,   237,   246,   247,   217,   242,   243,    10,
     255,   257,    11,    12,    15,    21,    22,    23,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    88,    89,    90,
      91,   100,   101,   107,   112,   113,   114,   115,   116,   117,
     118,   121,   127,   136,   139,   146,   154,   155,   159,   162,
     166,   187,   188,   189,   190,   191,   192,   201,   217,   252,
     260,   261,   262,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   284,   286,   288,   289,   290,   292,   294,   295,   296,
     297,   299,   300,   302,   304,   305,   306,   307,   319,   321,
     323,   364,   372,   378,   384,   386,   393,   407,   417,   437,
     438,   439,   440,   445,   453,   479,   509,   511,   530,   560,
     574,   586,   587,   595,   605,   636,   645,   669,    16,    17,
      18,    19,    20,   252,   311,   312,   313,   315,   316,   317,
     318,   509,   511,    92,    94,   102,   103,   104,   105,   106,
     122,   126,   134,   252,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   278,   279,   280,
     281,   284,   286,   288,   289,   290,   292,   294,   300,   302,
     425,   426,   427,   429,   431,   433,   435,   437,   438,   439,
     440,   443,   444,   479,   497,   509,   511,   513,   530,   555,
      93,   252,   433,   435,   479,   505,   506,   507,   509,   511,
      95,    96,    97,    98,    99,   252,   433,   435,   479,   509,
     511,   521,   522,   523,   525,   526,   528,   529,   121,   128,
     129,   130,   131,   132,   133,   252,   479,   509,   511,   538,
     539,   540,   541,   543,   545,   547,   549,   551,   553,   453,
      24,    79,    81,    82,    85,    86,    87,   252,   341,   463,
     464,   465,   466,   467,   468,   469,   471,   473,   475,   476,
     478,   509,   511,    80,    83,    84,   252,   341,   467,   473,
     487,   488,   489,   490,   491,   493,   494,   495,   496,   509,
     511,   137,   138,   252,   401,   402,   403,   405,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   187,   188,   252,   509,   511,   609,   610,   611,   612,
     614,   616,   617,   619,   620,   621,   624,   626,   627,   628,
     630,   632,   634,    13,    14,   640,   641,   642,   644,     6,
       3,     4,     8,     3,   256,     3,     8,   263,   637,   308,
     320,   322,   324,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   298,     4,     4,
       4,     4,     4,   282,   285,   287,     4,     4,     4,   418,
     454,   480,     4,   301,   303,   446,   510,   512,   441,     4,
       4,     4,   373,   385,   379,   365,   561,   531,   394,   408,
     575,     4,   387,   588,   596,   606,   291,   293,     4,     4,
       4,   646,   670,     4,     3,     8,   314,     4,     4,     4,
       4,     3,     8,   498,   514,   428,   430,   432,     4,     4,
     436,   434,   556,     3,     8,   508,     3,     8,   524,     4,
     527,     4,     4,     3,     8,   554,   542,   544,   546,   548,
     550,   552,     8,     3,     8,   470,   342,     4,   474,   472,
     477,     4,     8,     3,   492,     4,     4,     8,     3,   404,
     406,     3,     8,     4,   613,   615,     4,   618,     4,     4,
     622,   625,     4,     4,   629,   631,   633,   635,     3,     8,
     643,     4,     3,     8,   237,   237,   217,     4,     4,     4,
       4,     4,     4,     4,   218,   218,   218,   218,   218,   218,
     218,   218,   220,   219,   219,   219,   218,   218,     4,   218,
     218,   220,   220,   220,     4,     4,     4,   220,   220,   220,
       4,     4,     4,   218,     4,     4,     4,     4,     4,     4,
     220,   220,   220,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   218,     4,     4,     4,     4,     4,     4,   220,
     220,   220,     4,     4,   261,     4,   220,   220,   218,   218,
     312,     4,     4,     4,     4,     4,   218,   220,     4,     4,
       4,   426,     4,   506,     4,   218,     4,   218,   218,   522,
       4,     4,     4,     4,     4,     4,     4,   540,     4,     4,
     218,     4,     4,     4,   220,   465,     4,   220,   220,   489,
       4,     4,   402,   220,     4,     4,   218,     4,   218,   218,
       4,     4,   220,   220,     4,     4,     4,     4,   610,     4,
     218,   641,     4,     7,   217,     7,     7,     7,     7,     5,
     217,   183,   184,   185,   186,   220,   283,   217,   217,     5,
       5,     5,   217,   217,     5,   239,   241,   217,   108,   109,
     110,   111,   442,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,     7,     7,     7,   217,   217,     5,     7,
       5,   248,     5,     5,   217,   217,   217,   248,   217,     7,
     217,   217,   217,   248,   248,   248,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   241,   217,   217,
     217,   180,   181,   623,   182,   283,   217,   217,   217,     5,
     237,   260,   640,   311,    24,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    45,
      46,    47,    48,    49,   252,   329,   330,   331,   334,   336,
     338,   340,   341,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   354,   355,   356,   358,   360,   362,   329,     7,
     325,   326,   327,     7,   419,   420,   421,     7,   457,   458,
     459,     7,   481,   482,   483,     7,   447,   448,   449,   130,
     217,   374,   375,   376,   377,   246,   131,   133,   376,   380,
     381,   382,   383,   119,   120,   366,   367,   368,   370,     7,
     562,   563,     7,   532,   533,   534,     7,   395,   396,   397,
     140,   141,   142,   143,   144,   145,   409,   410,   411,   412,
     413,   414,   415,   416,    24,   150,   151,   152,   153,   252,
     343,   509,   511,   576,   577,   578,   581,   582,   584,   585,
     156,   157,   158,   252,   388,   389,   390,   391,   392,   509,
     511,   160,   161,   252,   509,   511,   589,   590,   591,   593,
     163,   164,   165,   217,   509,   511,   597,   598,   599,   600,
     602,   603,   609,     7,   647,   648,   202,   252,   671,   672,
     673,   249,     7,   499,   500,   501,     7,   515,   516,   517,
     135,   541,   557,   558,   325,     8,     8,     8,   332,   335,
     337,   339,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   352,     4,   357,   359,   361,   363,     3,     8,
       8,   328,     6,     3,   422,     6,     3,   460,     6,     3,
     484,     6,     3,   450,     6,     3,     3,     6,     6,     3,
       6,   369,   371,     3,     8,   564,     3,     6,   535,     6,
       3,   398,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   579,   583,     4,     4,     4,     3,     8,     4,
       4,     4,     3,     8,   592,   594,     3,     8,     4,   601,
       4,   604,     3,     8,     8,   649,     3,     6,     4,     3,
       8,   217,   250,   251,   502,     6,     3,   518,     6,     3,
     559,     8,     6,     4,     4,     4,     4,   218,   220,   218,
     220,   218,   218,   218,   218,   218,   218,     4,   218,     4,
       4,     4,     4,   330,   329,   327,   425,   421,   463,   459,
     487,   483,   252,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   278,   279,   280,   281,
     284,   286,   288,   289,   290,   292,   294,   300,   302,   341,
     417,   429,   431,   433,   435,   437,   438,   439,   440,   444,
     451,   452,   479,   509,   511,   555,   449,   375,   381,     4,
       4,   367,   123,   124,   125,   252,   264,   265,   266,   267,
     268,   269,   341,   479,   509,   511,   565,   566,   567,   568,
     569,   571,   573,   563,   538,   534,   401,   397,   218,   218,
     218,   218,   218,   218,   410,     4,     4,   218,   218,   218,
     577,   220,   218,   218,   389,     4,     4,   590,   220,     4,
     218,     4,   598,   193,   195,   196,   252,   341,   509,   511,
     650,   651,   652,   653,   655,   648,   220,   672,     6,     3,
     505,   501,   521,   517,     4,    25,    26,    27,   333,   217,
     217,   217,    42,    43,    44,   353,   217,   217,   217,   217,
       8,     8,     8,     8,     3,     8,   217,   217,   570,   572,
       4,     8,     3,     8,     8,   147,   148,   149,   580,   217,
     217,   217,   217,   237,   656,     4,   654,     3,     8,   217,
       8,     8,   217,   452,     4,     4,   220,   567,     4,   218,
       4,   651,   217,   217,     5,   217,     7,   657,   658,   659,
       3,     6,   194,   197,   198,   199,   200,   660,   661,   662,
     664,   665,   666,   667,   658,   663,     4,     4,     4,   668,
       3,     8,     4,   220,   218,   218,     4,   661,   217,   217
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   221,   223,   222,   224,   222,   225,   222,   226,   222,
     227,   222,   228,   222,   229,   222,   230,   222,   231,   222,
     232,   222,   233,   222,   234,   222,   235,   222,   236,   222,
     237,   237,   237,   237,   237,   237,   237,   238,   240,   239,
     241,   242,   242,   243,   243,   243,   245,   244,   246,   246,
     247,   247,   247,   249,   248,   250,   250,   251,   251,   251,
     252,   254,   253,   256,   255,   255,   257,   259,   258,   260,
     260,   260,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   263,
     262,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   282,   281,
     283,   283,   283,   283,   283,   285,   284,   287,   286,   288,
     289,   291,   290,   293,   292,   294,   295,   296,   298,   297,
     299,   301,   300,   303,   302,   304,   305,   306,   308,   307,
     310,   309,   311,   311,   311,   312,   312,   312,   312,   312,
     312,   312,   312,   314,   313,   315,   316,   317,   318,   320,
     319,   322,   321,   324,   323,   325,   325,   326,   326,   326,
     328,   327,   329,   329,   329,   330,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   332,   331,   333,
     333,   333,   335,   334,   337,   336,   339,   338,   340,   342,
     341,   343,   344,   345,   346,   347,   348,   349,   350,   352,
     351,   353,   353,   353,   354,   355,   357,   356,   359,   358,
     361,   360,   363,   362,   365,   364,   366,   366,   366,   367,
     367,   369,   368,   371,   370,   373,   372,   374,   374,   374,
     375,   375,   376,   377,   379,   378,   380,   380,   380,   381,
     381,   381,   382,   383,   385,   384,   387,   386,   388,   388,
     388,   389,   389,   389,   389,   389,   389,   390,   391,   392,
     394,   393,   395,   395,   396,   396,   396,   398,   397,   400,
     399,   401,   401,   401,   401,   402,   402,   404,   403,   406,
     405,   408,   407,   409,   409,   409,   410,   410,   410,   410,
     410,   410,   411,   412,   413,   414,   415,   416,   418,   417,
     419,   419,   420,   420,   420,   422,   421,   424,   423,   425,
     425,   425,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   428,   427,   430,
     429,   432,   431,   434,   433,   436,   435,   437,   438,   439,
     441,   440,   442,   442,   442,   442,   443,   444,   446,   445,
     447,   447,   448,   448,   448,   450,   449,   451,   451,   451,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   454,   453,   456,   455,   457,   457,   458,   458,
     458,   460,   459,   462,   461,   463,   463,   464,   464,   464,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     466,   467,   468,   470,   469,   472,   471,   474,   473,   475,
     477,   476,   478,   480,   479,   481,   481,   482,   482,   482,
     484,   483,   486,   485,   487,   487,   488,   488,   488,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   490,   492,
     491,   493,   494,   495,   496,   498,   497,   499,   499,   500,
     500,   500,   502,   501,   504,   503,   505,   505,   505,   506,
     506,   506,   506,   506,   506,   506,   508,   507,   510,   509,
     512,   511,   514,   513,   515,   515,   516,   516,   516,   518,
     517,   520,   519,   521,   521,   521,   522,   522,   522,   522,
     522,   522,   522,   522,   522,   522,   522,   524,   523,   525,
     527,   526,   528,   529,   531,   530,   532,   532,   533,   533,
     533,   535,   534,   537,   536,   538,   538,   539,   539,   539,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   540,
     540,   542,   541,   544,   543,   546,   545,   548,   547,   550,
     549,   552,   551,   554,   553,   556,   555,   557,   557,   559,
     558,   561,   560,   562,   562,   562,   564,   563,   565,   565,
     566,   566,   566,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   568,   570,   569,
     572,   571,   573,   575,   574,   576,   576,   576,   577,   577,
     577,   577,   577,   577,   577,   577,   577,   579,   578,   580,
     580,   580,   581,   583,   582,   584,   585,   586,   588,   587,
     589,   589,   589,   590,   590,   590,   590,   590,   592,   591,
     594,   593,   596,   595,   597,   597,   597,   598,   598,   598,
     598,   598,   598,   599,   601,   600,   602,   604,   603,   606,
     605,   608,   607,   609,   609,   609,   610,   610,   610,   610,
     610,   610,   610,   610,   610,   610,   610,   610,   610,   610,
     610,   610,   610,   610,   611,   613,   612,   615,   614,   616,
     618,   617,   619,   620,   622,   621,   623,   623,   625,   624,
     626,   627,   629,   628,   631,   630,   633,   632,   635,   634,
     637,   636,   639,   638,   640,   640,   640,   641,   641,   643,
     642,   644,   646,   645,   647,   647,   647,   649,   648,   650,
     650,   650,   651,   651,   651,   651,   651,   651,   651,   652,
     654,   653,   656,   655,   657,   657,   657,   659,   658,   660,
     660,   660,   661,   661,   661,   661,   661,   663,   662,   664,
     665,   666,   668,   667,   670,   669,   671,   671,   671,   672,
     672,   673
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     4,     0,     4,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     4,     3,     3,     3,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     6,     0,     6,     1,     3,
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     3
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
  "\"store-extended-info\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"parked-packet-limit\"",
  "\"allocator\"", "\"pd-allocator\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"extended-info-checks\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"template-test\"", "\"only-if-required\"", "\"client-class\"",
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
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@27",
  "parked_packet_limit", "allocator", "$@28", "pd_allocator", "$@29",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@30",
  "sub_interfaces6", "$@31", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@32", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "read_timeout",
  "write_timeout", "tcp_user_timeout", "reconnect_wait_time", "on_fail",
  "$@42", "on_fail_mode", "max_row_errors", "max_reconnect_tries",
  "trust_anchor", "$@43", "cert_file", "$@44", "key_file", "$@45",
  "cipher_list", "$@46", "sanity_checks", "$@47", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@48", "extended_info_checks",
  "$@49", "mac_sources", "$@50", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@51",
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
  "option_data_always_send", "pools_list", "$@83", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@84", "sub_pool6", "$@85",
  "pool_params", "pool_param", "pool_entry", "$@86", "user_context",
  "$@87", "comment", "$@88", "pd_pools_list", "$@89",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@90", "sub_pd_pool", "$@91", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@92", "pd_prefix_len", "excluded_prefix", "$@93",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@94",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@95", "sub_reservation", "$@96", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@97", "prefixes", "$@98", "duid", "$@99", "hw_address", "$@100",
  "hostname", "$@101", "flex_id_value", "$@102",
  "reservation_client_classes", "$@103", "relay", "$@104", "relay_map",
  "ip_address", "$@105", "client_classes", "$@106", "client_classes_list",
  "client_class_entry", "$@107", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@108",
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
       0,   309,   309,   309,   310,   310,   311,   311,   312,   312,
     313,   313,   314,   314,   315,   315,   316,   316,   317,   317,
     318,   318,   319,   319,   320,   320,   321,   321,   322,   322,
     330,   331,   332,   333,   334,   335,   336,   339,   344,   344,
     355,   358,   359,   362,   367,   373,   378,   378,   385,   386,
     389,   393,   397,   403,   403,   410,   411,   414,   418,   422,
     432,   441,   441,   456,   456,   470,   473,   479,   479,   488,
     489,   490,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   566,
     566,   575,   581,   587,   593,   599,   605,   611,   617,   623,
     629,   635,   641,   647,   653,   659,   665,   671,   677,   677,
     686,   689,   692,   695,   698,   704,   704,   713,   713,   722,
     728,   734,   734,   743,   743,   752,   758,   764,   770,   770,
     779,   785,   785,   794,   794,   803,   809,   815,   821,   821,
     833,   833,   842,   843,   844,   849,   850,   851,   852,   853,
     854,   855,   856,   859,   859,   870,   876,   882,   888,   894,
     894,   907,   907,   920,   920,   931,   932,   935,   936,   937,
     942,   942,   952,   953,   954,   959,   960,   961,   962,   963,
     964,   965,   966,   967,   968,   969,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,   983,   983,   991,
     992,   993,   996,   996,  1005,  1005,  1014,  1014,  1023,  1029,
    1029,  1038,  1044,  1050,  1056,  1062,  1068,  1074,  1081,  1087,
    1087,  1095,  1096,  1097,  1100,  1106,  1112,  1112,  1121,  1121,
    1130,  1130,  1139,  1139,  1148,  1148,  1159,  1160,  1161,  1166,
    1167,  1170,  1170,  1189,  1189,  1207,  1207,  1218,  1219,  1220,
    1225,  1226,  1229,  1234,  1239,  1239,  1250,  1251,  1252,  1257,
    1258,  1259,  1262,  1267,  1274,  1274,  1287,  1287,  1300,  1301,
    1302,  1307,  1308,  1309,  1310,  1311,  1312,  1315,  1321,  1327,
    1333,  1333,  1344,  1345,  1348,  1349,  1350,  1355,  1355,  1365,
    1365,  1375,  1376,  1377,  1380,  1383,  1384,  1387,  1387,  1396,
    1396,  1405,  1405,  1417,  1418,  1419,  1424,  1425,  1426,  1427,
    1428,  1429,  1432,  1438,  1444,  1450,  1456,  1462,  1471,  1471,
    1485,  1486,  1489,  1490,  1491,  1500,  1500,  1526,  1526,  1537,
    1538,  1539,  1545,  1546,  1547,  1548,  1549,  1550,  1551,  1552,
    1553,  1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,  1562,
    1563,  1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,  1572,
    1573,  1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,  1582,
    1583,  1584,  1585,  1586,  1587,  1588,  1589,  1592,  1592,  1601,
    1601,  1610,  1610,  1619,  1619,  1628,  1628,  1639,  1645,  1651,
    1657,  1657,  1665,  1666,  1667,  1668,  1671,  1677,  1685,  1685,
    1697,  1698,  1702,  1703,  1704,  1709,  1709,  1717,  1718,  1719,
    1724,  1725,  1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,
    1734,  1735,  1736,  1737,  1738,  1739,  1740,  1741,  1742,  1743,
    1744,  1745,  1746,  1747,  1748,  1749,  1750,  1751,  1752,  1753,
    1754,  1755,  1756,  1757,  1758,  1759,  1760,  1761,  1762,  1763,
    1764,  1765,  1772,  1772,  1786,  1786,  1795,  1796,  1799,  1800,
    1801,  1808,  1808,  1823,  1823,  1837,  1838,  1841,  1842,  1843,
    1848,  1849,  1850,  1851,  1852,  1853,  1854,  1855,  1856,  1857,
    1860,  1862,  1868,  1870,  1870,  1879,  1879,  1888,  1888,  1897,
    1899,  1899,  1908,  1918,  1918,  1931,  1932,  1937,  1938,  1939,
    1946,  1946,  1958,  1958,  1970,  1971,  1976,  1977,  1978,  1985,
    1986,  1987,  1988,  1989,  1990,  1991,  1992,  1993,  1996,  1998,
    1998,  2007,  2009,  2011,  2017,  2026,  2026,  2039,  2040,  2043,
    2044,  2045,  2050,  2050,  2060,  2060,  2070,  2071,  2072,  2077,
    2078,  2079,  2080,  2081,  2082,  2083,  2086,  2086,  2095,  2095,
    2120,  2120,  2150,  2150,  2163,  2164,  2167,  2168,  2169,  2174,
    2174,  2186,  2186,  2198,  2199,  2200,  2205,  2206,  2207,  2208,
    2209,  2210,  2211,  2212,  2213,  2214,  2215,  2218,  2218,  2227,
    2233,  2233,  2242,  2248,  2257,  2257,  2268,  2269,  2272,  2273,
    2274,  2279,  2279,  2288,  2288,  2297,  2298,  2301,  2302,  2303,
    2309,  2310,  2311,  2312,  2313,  2314,  2315,  2316,  2317,  2318,
    2319,  2322,  2322,  2333,  2333,  2344,  2344,  2353,  2353,  2362,
    2362,  2371,  2371,  2380,  2380,  2394,  2394,  2405,  2406,  2409,
    2409,  2421,  2421,  2432,  2433,  2434,  2439,  2439,  2449,  2450,
    2453,  2454,  2455,  2460,  2461,  2462,  2463,  2464,  2465,  2466,
    2467,  2468,  2469,  2470,  2471,  2472,  2473,  2476,  2478,  2478,
    2487,  2487,  2496,  2505,  2505,  2518,  2519,  2520,  2525,  2526,
    2527,  2528,  2529,  2530,  2531,  2532,  2533,  2536,  2536,  2544,
    2545,  2546,  2549,  2555,  2555,  2564,  2570,  2578,  2586,  2586,
    2597,  2598,  2599,  2604,  2605,  2606,  2607,  2608,  2611,  2611,
    2620,  2620,  2632,  2632,  2645,  2646,  2647,  2652,  2653,  2654,
    2655,  2656,  2657,  2660,  2666,  2666,  2675,  2681,  2681,  2691,
    2691,  2704,  2704,  2714,  2715,  2716,  2721,  2722,  2723,  2724,
    2725,  2726,  2727,  2728,  2729,  2730,  2731,  2732,  2733,  2734,
    2735,  2736,  2737,  2738,  2741,  2748,  2748,  2757,  2757,  2766,
    2772,  2772,  2781,  2787,  2793,  2793,  2802,  2803,  2806,  2806,
    2816,  2823,  2830,  2830,  2839,  2839,  2849,  2849,  2859,  2859,
    2871,  2871,  2883,  2883,  2893,  2894,  2895,  2901,  2902,  2905,
    2905,  2916,  2924,  2924,  2937,  2938,  2939,  2945,  2945,  2953,
    2954,  2955,  2960,  2961,  2962,  2963,  2964,  2965,  2966,  2969,
    2975,  2975,  2984,  2984,  2995,  2996,  2997,  3002,  3002,  3010,
    3011,  3012,  3017,  3018,  3019,  3020,  3021,  3024,  3024,  3033,
    3039,  3045,  3051,  3051,  3060,  3060,  3071,  3072,  3073,  3078,
    3079,  3082
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
#line 6497 "dhcp6_parser.cc"

#line 3088 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
