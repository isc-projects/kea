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
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 301 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 301 "dhcp6_parser.yy"
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
#line 310 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 311 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 312 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 313 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 314 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 315 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 316 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 317 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 318 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 319 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 320 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 321 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 322 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 323 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 331 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 332 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 333 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 334 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 335 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 336 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 337 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 340 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 345 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 350 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 356 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 363 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 368 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 374 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 379 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 382 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 390 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 394 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 398 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 404 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 406 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 415 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 419 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 423 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 433 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 442 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 447 "dhcp6_parser.yy"
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
#line 457 "dhcp6_parser.yy"
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
#line 466 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 474 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 480 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 484 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 491 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 139: // $@21: %empty
#line 567 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 140: // data_directory: "data-directory" $@21 ":" "constant string"
#line 570 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 141: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 576 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 142: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 582 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 143: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 588 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 144: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 594 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 145: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 600 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 146: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 606 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 147: // renew_timer: "renew-timer" ":" "integer"
#line 612 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 148: // rebind_timer: "rebind-timer" ":" "integer"
#line 618 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 149: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 624 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 150: // t1_percent: "t1-percent" ":" "floating point"
#line 630 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 151: // t2_percent: "t2-percent" ":" "floating point"
#line 636 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 152: // cache_threshold: "cache-threshold" ":" "floating point"
#line 642 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 153: // cache_max_age: "cache-max-age" ":" "integer"
#line 648 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 154: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 654 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 155: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 660 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 156: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 666 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 157: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 672 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 158: // $@22: %empty
#line 678 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 681 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "when-present"
#line 687 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "never"
#line 690 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "always"
#line 693 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-not-present"
#line 696 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "boolean"
#line 699 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 165: // $@23: %empty
#line 705 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 166: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 708 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 167: // $@24: %empty
#line 714 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 168: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 717 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 169: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 723 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 170: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 729 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 171: // $@25: %empty
#line 735 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 738 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 173: // $@26: %empty
#line 744 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 174: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 747 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // store_extended_info: "store-extended-info" ":" "boolean"
#line 753 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 176: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 759 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 177: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 765 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 178: // $@27: %empty
#line 771 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 179: // server_tag: "server-tag" $@27 ":" "constant string"
#line 774 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 180: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 780 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 181: // $@28: %empty
#line 786 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1528 "dhcp6_parser.cc"
    break;

  case 182: // allocator: "allocator" $@28 ":" "constant string"
#line 789 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1538 "dhcp6_parser.cc"
    break;

  case 183: // $@29: %empty
#line 795 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1547 "dhcp6_parser.cc"
    break;

  case 184: // pd_allocator: "pd-allocator" $@29 ":" "constant string"
#line 798 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1557 "dhcp6_parser.cc"
    break;

  case 185: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 804 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1567 "dhcp6_parser.cc"
    break;

  case 186: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 810 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 187: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 816 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 188: // $@30: %empty
#line 822 "dhcp6_parser.yy"
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
#line 828 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 190: // $@31: %empty
#line 834 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 191: // sub_interfaces6: "{" $@31 interfaces_config_params "}"
#line 838 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 194: // interfaces_config_params: interfaces_config_params ","
#line 845 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1636 "dhcp6_parser.cc"
    break;

  case 203: // $@32: %empty
#line 860 "dhcp6_parser.yy"
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
#line 866 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 205: // re_detect: "re-detect" ":" "boolean"
#line 871 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 206: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 877 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 207: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 883 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 208: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 889 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 209: // $@33: %empty
#line 895 "dhcp6_parser.yy"
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
#line 901 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 211: // $@34: %empty
#line 908 "dhcp6_parser.yy"
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
#line 914 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1743 "dhcp6_parser.cc"
    break;

  case 213: // $@35: %empty
#line 921 "dhcp6_parser.yy"
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
#line 927 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 219: // not_empty_database_list: not_empty_database_list ","
#line 938 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1772 "dhcp6_parser.cc"
    break;

  case 220: // $@36: %empty
#line 943 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 221: // database: "{" $@36 database_map_params "}"
#line 947 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 224: // database_map_params: database_map_params ","
#line 955 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1800 "dhcp6_parser.cc"
    break;

  case 247: // $@37: %empty
#line 984 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 248: // database_type: "type" $@37 ":" db_type
#line 987 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 249: // db_type: "memfile"
#line 992 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1824 "dhcp6_parser.cc"
    break;

  case 250: // db_type: "mysql"
#line 993 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1830 "dhcp6_parser.cc"
    break;

  case 251: // db_type: "postgresql"
#line 994 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1836 "dhcp6_parser.cc"
    break;

  case 252: // $@38: %empty
#line 997 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 253: // user: "user" $@38 ":" "constant string"
#line 1000 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 254: // $@39: %empty
#line 1006 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 255: // password: "password" $@39 ":" "constant string"
#line 1009 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 256: // $@40: %empty
#line 1015 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 257: // host: "host" $@40 ":" "constant string"
#line 1018 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 258: // port: "port" ":" "integer"
#line 1024 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1903 "dhcp6_parser.cc"
    break;

  case 259: // $@41: %empty
#line 1030 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp6_parser.cc"
    break;

  case 260: // name: "name" $@41 ":" "constant string"
#line 1033 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 261: // persist: "persist" ":" "boolean"
#line 1039 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1932 "dhcp6_parser.cc"
    break;

  case 262: // lfc_interval: "lfc-interval" ":" "integer"
#line 1045 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 263: // readonly: "readonly" ":" "boolean"
#line 1051 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 264: // connect_timeout: "connect-timeout" ":" "integer"
#line 1057 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1962 "dhcp6_parser.cc"
    break;

  case 265: // read_timeout: "read-timeout" ":" "integer"
#line 1063 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 266: // write_timeout: "write-timeout" ":" "integer"
#line 1069 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 1982 "dhcp6_parser.cc"
    break;

  case 267: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1075 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 268: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1082 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1088 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 270: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1091 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2020 "dhcp6_parser.cc"
    break;

  case 271: // on_fail_mode: "stop-retry-exit"
#line 1096 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2026 "dhcp6_parser.cc"
    break;

  case 272: // on_fail_mode: "serve-retry-exit"
#line 1097 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2032 "dhcp6_parser.cc"
    break;

  case 273: // on_fail_mode: "serve-retry-continue"
#line 1098 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2038 "dhcp6_parser.cc"
    break;

  case 274: // max_row_errors: "max-row-errors" ":" "integer"
#line 1101 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2048 "dhcp6_parser.cc"
    break;

  case 275: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1107 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2058 "dhcp6_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1113 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 277: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1116 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 278: // $@44: %empty
#line 1122 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 279: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1125 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 280: // $@45: %empty
#line 1131 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 281: // key_file: "key-file" $@45 ":" "constant string"
#line 1134 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 282: // $@46: %empty
#line 1140 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp6_parser.cc"
    break;

  case 283: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1143 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 284: // $@47: %empty
#line 1149 "dhcp6_parser.yy"
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
#line 1155 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 288: // sanity_checks_params: sanity_checks_params ","
#line 1162 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2163 "dhcp6_parser.cc"
    break;

  case 291: // $@48: %empty
#line 1171 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2172 "dhcp6_parser.cc"
    break;

  case 292: // lease_checks: "lease-checks" $@48 ":" "constant string"
#line 1174 "dhcp6_parser.yy"
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
#line 1190 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 294: // extended_info_checks: "extended-info-checks" $@49 ":" "constant string"
#line 1193 "dhcp6_parser.yy"
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
#line 1208 "dhcp6_parser.yy"
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
#line 1214 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2241 "dhcp6_parser.cc"
    break;

  case 299: // mac_sources_list: mac_sources_list ","
#line 1221 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2249 "dhcp6_parser.cc"
    break;

  case 302: // duid_id: "duid"
#line 1230 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 303: // string_id: "constant string"
#line 1235 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 304: // $@51: %empty
#line 1240 "dhcp6_parser.yy"
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
#line 1246 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2288 "dhcp6_parser.cc"
    break;

  case 308: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1253 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2296 "dhcp6_parser.cc"
    break;

  case 312: // hw_address_id: "hw-address"
#line 1263 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 313: // flex_id: "flex-id"
#line 1268 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 314: // $@52: %empty
#line 1275 "dhcp6_parser.yy"
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
#line 1281 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 316: // $@53: %empty
#line 1288 "dhcp6_parser.yy"
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
#line 1294 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2358 "dhcp6_parser.cc"
    break;

  case 320: // multi_threading_params: multi_threading_params ","
#line 1303 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2366 "dhcp6_parser.cc"
    break;

  case 327: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1316 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2376 "dhcp6_parser.cc"
    break;

  case 328: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1322 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2386 "dhcp6_parser.cc"
    break;

  case 329: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1328 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2396 "dhcp6_parser.cc"
    break;

  case 330: // $@54: %empty
#line 1334 "dhcp6_parser.yy"
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
#line 1340 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 336: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1351 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2425 "dhcp6_parser.cc"
    break;

  case 337: // $@55: %empty
#line 1356 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2435 "dhcp6_parser.cc"
    break;

  case 338: // hooks_library: "{" $@55 hooks_params "}"
#line 1360 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2445 "dhcp6_parser.cc"
    break;

  case 339: // $@56: %empty
#line 1366 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp6_parser.cc"
    break;

  case 340: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1370 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 343: // hooks_params: hooks_params ","
#line 1378 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2473 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1388 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp6_parser.cc"
    break;

  case 348: // library: "library" $@57 ":" "constant string"
#line 1391 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2492 "dhcp6_parser.cc"
    break;

  case 349: // $@58: %empty
#line 1397 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp6_parser.cc"
    break;

  case 350: // parameters: "parameters" $@58 ":" map_value
#line 1400 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2510 "dhcp6_parser.cc"
    break;

  case 351: // $@59: %empty
#line 1406 "dhcp6_parser.yy"
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
#line 1412 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 355: // expired_leases_params: expired_leases_params ","
#line 1420 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2540 "dhcp6_parser.cc"
    break;

  case 362: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1433 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 363: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1439 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 364: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1445 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 365: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1451 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 366: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1457 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 367: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1463 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 368: // $@60: %empty
#line 1472 "dhcp6_parser.yy"
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
#line 1478 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc"
    break;

  case 374: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1492 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2629 "dhcp6_parser.cc"
    break;

  case 375: // $@61: %empty
#line 1501 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2639 "dhcp6_parser.cc"
    break;

  case 376: // subnet6: "{" $@61 subnet6_params "}"
#line 1505 "dhcp6_parser.yy"
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
#line 1527 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 378: // sub_subnet6: "{" $@62 subnet6_params "}"
#line 1531 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 381: // subnet6_params: subnet6_params ","
#line 1540 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2693 "dhcp6_parser.cc"
    break;

  case 427: // $@63: %empty
#line 1593 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp6_parser.cc"
    break;

  case 428: // subnet: "subnet" $@63 ":" "constant string"
#line 1596 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 429: // $@64: %empty
#line 1602 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp6_parser.cc"
    break;

  case 430: // interface: "interface" $@64 ":" "constant string"
#line 1605 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2731 "dhcp6_parser.cc"
    break;

  case 431: // $@65: %empty
#line 1611 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp6_parser.cc"
    break;

  case 432: // interface_id: "interface-id" $@65 ":" "constant string"
#line 1614 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2750 "dhcp6_parser.cc"
    break;

  case 433: // $@66: %empty
#line 1620 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp6_parser.cc"
    break;

  case 434: // client_class: "client-class" $@66 ":" "constant string"
#line 1623 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2769 "dhcp6_parser.cc"
    break;

  case 435: // $@67: %empty
#line 1629 "dhcp6_parser.yy"
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
#line 1635 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2790 "dhcp6_parser.cc"
    break;

  case 437: // reservations_global: "reservations-global" ":" "boolean"
#line 1640 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2800 "dhcp6_parser.cc"
    break;

  case 438: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1646 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2810 "dhcp6_parser.cc"
    break;

  case 439: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1652 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2820 "dhcp6_parser.cc"
    break;

  case 440: // $@68: %empty
#line 1658 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 441: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1661 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 442: // hr_mode: "disabled"
#line 1666 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2844 "dhcp6_parser.cc"
    break;

  case 443: // hr_mode: "out-of-pool"
#line 1667 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2850 "dhcp6_parser.cc"
    break;

  case 444: // hr_mode: "global"
#line 1668 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2856 "dhcp6_parser.cc"
    break;

  case 445: // hr_mode: "all"
#line 1669 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2862 "dhcp6_parser.cc"
    break;

  case 446: // id: "id" ":" "integer"
#line 1672 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2872 "dhcp6_parser.cc"
    break;

  case 447: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1678 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 448: // $@69: %empty
#line 1686 "dhcp6_parser.yy"
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
#line 1692 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 454: // shared_networks_list: shared_networks_list ","
#line 1705 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2911 "dhcp6_parser.cc"
    break;

  case 455: // $@70: %empty
#line 1710 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 456: // shared_network: "{" $@70 shared_network_params "}"
#line 1714 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2929 "dhcp6_parser.cc"
    break;

  case 459: // shared_network_params: shared_network_params ","
#line 1720 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2937 "dhcp6_parser.cc"
    break;

  case 502: // $@71: %empty
#line 1773 "dhcp6_parser.yy"
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
#line 1779 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2958 "dhcp6_parser.cc"
    break;

  case 504: // $@72: %empty
#line 1787 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2967 "dhcp6_parser.cc"
    break;

  case 505: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1790 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2975 "dhcp6_parser.cc"
    break;

  case 510: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1802 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2983 "dhcp6_parser.cc"
    break;

  case 511: // $@73: %empty
#line 1809 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 512: // option_def_entry: "{" $@73 option_def_params "}"
#line 1813 "dhcp6_parser.yy"
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
#line 1824 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 514: // sub_option_def: "{" $@74 option_def_params "}"
#line 1828 "dhcp6_parser.yy"
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
#line 1844 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3035 "dhcp6_parser.cc"
    break;

  case 531: // code: "code" ":" "integer"
#line 1863 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 533: // $@75: %empty
#line 1871 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 534: // option_def_type: "type" $@75 ":" "constant string"
#line 1874 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 535: // $@76: %empty
#line 1880 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp6_parser.cc"
    break;

  case 536: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1883 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 537: // $@77: %empty
#line 1889 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp6_parser.cc"
    break;

  case 538: // space: "space" $@77 ":" "constant string"
#line 1892 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3102 "dhcp6_parser.cc"
    break;

  case 540: // $@78: %empty
#line 1900 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 541: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1903 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 542: // option_def_array: "array" ":" "boolean"
#line 1909 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 543: // $@79: %empty
#line 1919 "dhcp6_parser.yy"
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
#line 1925 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3152 "dhcp6_parser.cc"
    break;

  case 549: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1940 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3160 "dhcp6_parser.cc"
    break;

  case 550: // $@80: %empty
#line 1947 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 551: // option_data_entry: "{" $@80 option_data_params "}"
#line 1951 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 552: // $@81: %empty
#line 1959 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 553: // sub_option_data: "{" $@81 option_data_params "}"
#line 1963 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 558: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1979 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3206 "dhcp6_parser.cc"
    break;

  case 570: // $@82: %empty
#line 2000 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp6_parser.cc"
    break;

  case 571: // option_data_data: "data" $@82 ":" "constant string"
#line 2003 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc"
    break;

  case 574: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2013 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3235 "dhcp6_parser.cc"
    break;

  case 575: // option_data_always_send: "always-send" ":" "boolean"
#line 2019 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3245 "dhcp6_parser.cc"
    break;

  case 576: // option_data_never_send: "never-send" ":" "boolean"
#line 2025 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", persist);
}
#line 3255 "dhcp6_parser.cc"
    break;

  case 577: // $@83: %empty
#line 2034 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3267 "dhcp6_parser.cc"
    break;

  case 578: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2040 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 583: // not_empty_pools_list: not_empty_pools_list ","
#line 2053 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3284 "dhcp6_parser.cc"
    break;

  case 584: // $@84: %empty
#line 2058 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 585: // pool_list_entry: "{" $@84 pool_params "}"
#line 2062 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 586: // $@85: %empty
#line 2068 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 587: // sub_pool6: "{" $@85 pool_params "}"
#line 2072 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3324 "dhcp6_parser.cc"
    break;

  case 590: // pool_params: pool_params ","
#line 2080 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3332 "dhcp6_parser.cc"
    break;

  case 598: // $@86: %empty
#line 2094 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3341 "dhcp6_parser.cc"
    break;

  case 599: // pool_entry: "pool" $@86 ":" "constant string"
#line 2097 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3351 "dhcp6_parser.cc"
    break;

  case 600: // $@87: %empty
#line 2103 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 601: // user_context: "user-context" $@87 ":" map_value
#line 2105 "dhcp6_parser.yy"
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
#line 3386 "dhcp6_parser.cc"
    break;

  case 602: // $@88: %empty
#line 2128 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 603: // comment: "comment" $@88 ":" "constant string"
#line 2130 "dhcp6_parser.yy"
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
#line 3423 "dhcp6_parser.cc"
    break;

  case 604: // $@89: %empty
#line 2158 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 605: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2164 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3444 "dhcp6_parser.cc"
    break;

  case 610: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2177 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3452 "dhcp6_parser.cc"
    break;

  case 611: // $@90: %empty
#line 2182 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3462 "dhcp6_parser.cc"
    break;

  case 612: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2186 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3474 "dhcp6_parser.cc"
    break;

  case 613: // $@91: %empty
#line 2194 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 614: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2198 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3496 "dhcp6_parser.cc"
    break;

  case 617: // pd_pool_params: pd_pool_params ","
#line 2208 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3504 "dhcp6_parser.cc"
    break;

  case 629: // $@92: %empty
#line 2226 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3513 "dhcp6_parser.cc"
    break;

  case 630: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2229 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3523 "dhcp6_parser.cc"
    break;

  case 631: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2235 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3533 "dhcp6_parser.cc"
    break;

  case 632: // $@93: %empty
#line 2241 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 633: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2244 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 634: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2250 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 635: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2256 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3572 "dhcp6_parser.cc"
    break;

  case 636: // $@94: %empty
#line 2265 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 637: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2271 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3593 "dhcp6_parser.cc"
    break;

  case 642: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2282 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3601 "dhcp6_parser.cc"
    break;

  case 643: // $@95: %empty
#line 2287 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3611 "dhcp6_parser.cc"
    break;

  case 644: // reservation: "{" $@95 reservation_params "}"
#line 2291 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3620 "dhcp6_parser.cc"
    break;

  case 645: // $@96: %empty
#line 2296 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 646: // sub_reservation: "{" $@96 reservation_params "}"
#line 2300 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 651: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2311 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3647 "dhcp6_parser.cc"
    break;

  case 663: // $@97: %empty
#line 2330 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3659 "dhcp6_parser.cc"
    break;

  case 664: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2336 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 665: // $@98: %empty
#line 2341 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3680 "dhcp6_parser.cc"
    break;

  case 666: // prefixes: "prefixes" $@98 ":" list_strings
#line 2347 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3689 "dhcp6_parser.cc"
    break;

  case 667: // $@99: %empty
#line 2352 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3698 "dhcp6_parser.cc"
    break;

  case 668: // duid: "duid" $@99 ":" "constant string"
#line 2355 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 669: // $@100: %empty
#line 2361 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 670: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2364 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 671: // $@101: %empty
#line 2370 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 672: // hostname: "hostname" $@101 ":" "constant string"
#line 2373 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 673: // $@102: %empty
#line 2379 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 674: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2382 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3765 "dhcp6_parser.cc"
    break;

  case 675: // $@103: %empty
#line 2388 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 676: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2394 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 677: // $@104: %empty
#line 2402 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 678: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2408 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 681: // $@105: %empty
#line 2417 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3816 "dhcp6_parser.cc"
    break;

  case 682: // ip_address: "ip-address" $@105 ":" "constant string"
#line 2420 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3826 "dhcp6_parser.cc"
    break;

  case 683: // $@106: %empty
#line 2429 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3838 "dhcp6_parser.cc"
    break;

  case 684: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2435 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3847 "dhcp6_parser.cc"
    break;

  case 687: // client_classes_list: client_classes_list ","
#line 2442 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3855 "dhcp6_parser.cc"
    break;

  case 688: // $@107: %empty
#line 2447 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3865 "dhcp6_parser.cc"
    break;

  case 689: // client_class_entry: "{" $@107 client_class_params "}"
#line 2451 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3875 "dhcp6_parser.cc"
    break;

  case 694: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2463 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3883 "dhcp6_parser.cc"
    break;

  case 710: // $@108: %empty
#line 2486 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 711: // client_class_test: "test" $@108 ":" "constant string"
#line 2489 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 712: // $@109: %empty
#line 2495 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 713: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2498 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 714: // only_if_required: "only-if-required" ":" "boolean"
#line 2504 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3931 "dhcp6_parser.cc"
    break;

  case 715: // $@110: %empty
#line 2513 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 716: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2519 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3954 "dhcp6_parser.cc"
    break;

  case 719: // server_id_params: server_id_params ","
#line 2528 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3962 "dhcp6_parser.cc"
    break;

  case 729: // $@111: %empty
#line 2544 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 730: // server_id_type: "type" $@111 ":" duid_type
#line 2547 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 731: // duid_type: "LLT"
#line 2552 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3986 "dhcp6_parser.cc"
    break;

  case 732: // duid_type: "EN"
#line 2553 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3992 "dhcp6_parser.cc"
    break;

  case 733: // duid_type: "LL"
#line 2554 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3998 "dhcp6_parser.cc"
    break;

  case 734: // htype: "htype" ":" "integer"
#line 2557 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 735: // $@112: %empty
#line 2563 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4017 "dhcp6_parser.cc"
    break;

  case 736: // identifier: "identifier" $@112 ":" "constant string"
#line 2566 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 737: // time: "time" ":" "integer"
#line 2572 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4037 "dhcp6_parser.cc"
    break;

  case 738: // enterprise_id: "enterprise-id" ":" "integer"
#line 2578 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4047 "dhcp6_parser.cc"
    break;

  case 739: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2586 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4057 "dhcp6_parser.cc"
    break;

  case 740: // $@113: %empty
#line 2594 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 741: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2600 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4078 "dhcp6_parser.cc"
    break;

  case 744: // control_socket_params: control_socket_params ","
#line 2607 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4086 "dhcp6_parser.cc"
    break;

  case 750: // $@114: %empty
#line 2619 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4095 "dhcp6_parser.cc"
    break;

  case 751: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2622 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4105 "dhcp6_parser.cc"
    break;

  case 752: // $@115: %empty
#line 2628 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4114 "dhcp6_parser.cc"
    break;

  case 753: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2631 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4124 "dhcp6_parser.cc"
    break;

  case 754: // $@116: %empty
#line 2640 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4136 "dhcp6_parser.cc"
    break;

  case 755: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2646 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 758: // queue_control_params: queue_control_params ","
#line 2655 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4155 "dhcp6_parser.cc"
    break;

  case 765: // enable_queue: "enable-queue" ":" "boolean"
#line 2668 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4165 "dhcp6_parser.cc"
    break;

  case 766: // $@117: %empty
#line 2674 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4174 "dhcp6_parser.cc"
    break;

  case 767: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2677 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4184 "dhcp6_parser.cc"
    break;

  case 768: // capacity: "capacity" ":" "integer"
#line 2683 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4194 "dhcp6_parser.cc"
    break;

  case 769: // $@118: %empty
#line 2689 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4203 "dhcp6_parser.cc"
    break;

  case 770: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2692 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4212 "dhcp6_parser.cc"
    break;

  case 771: // $@119: %empty
#line 2699 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4224 "dhcp6_parser.cc"
    break;

  case 772: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2705 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4235 "dhcp6_parser.cc"
    break;

  case 773: // $@120: %empty
#line 2712 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 774: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2716 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 777: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2724 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4263 "dhcp6_parser.cc"
    break;

  case 796: // enable_updates: "enable-updates" ":" "boolean"
#line 2749 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 797: // $@121: %empty
#line 2756 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 798: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2759 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4292 "dhcp6_parser.cc"
    break;

  case 799: // $@122: %empty
#line 2765 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4301 "dhcp6_parser.cc"
    break;

  case 800: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2768 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4311 "dhcp6_parser.cc"
    break;

  case 801: // server_port: "server-port" ":" "integer"
#line 2774 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4321 "dhcp6_parser.cc"
    break;

  case 802: // $@123: %empty
#line 2780 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4330 "dhcp6_parser.cc"
    break;

  case 803: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2783 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4340 "dhcp6_parser.cc"
    break;

  case 804: // sender_port: "sender-port" ":" "integer"
#line 2789 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4350 "dhcp6_parser.cc"
    break;

  case 805: // max_queue_size: "max-queue-size" ":" "integer"
#line 2795 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4360 "dhcp6_parser.cc"
    break;

  case 806: // $@124: %empty
#line 2801 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 807: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2804 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 808: // ncr_protocol_value: "UDP"
#line 2810 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4384 "dhcp6_parser.cc"
    break;

  case 809: // ncr_protocol_value: "TCP"
#line 2811 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4390 "dhcp6_parser.cc"
    break;

  case 810: // $@125: %empty
#line 2814 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4399 "dhcp6_parser.cc"
    break;

  case 811: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2817 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 812: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2824 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4419 "dhcp6_parser.cc"
    break;

  case 813: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2831 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4429 "dhcp6_parser.cc"
    break;

  case 814: // $@126: %empty
#line 2838 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4438 "dhcp6_parser.cc"
    break;

  case 815: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2841 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4447 "dhcp6_parser.cc"
    break;

  case 816: // $@127: %empty
#line 2847 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4456 "dhcp6_parser.cc"
    break;

  case 817: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2850 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4466 "dhcp6_parser.cc"
    break;

  case 818: // $@128: %empty
#line 2857 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4475 "dhcp6_parser.cc"
    break;

  case 819: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2860 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4485 "dhcp6_parser.cc"
    break;

  case 820: // $@129: %empty
#line 2867 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4494 "dhcp6_parser.cc"
    break;

  case 821: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2870 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 822: // $@130: %empty
#line 2879 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4516 "dhcp6_parser.cc"
    break;

  case 823: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2885 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4526 "dhcp6_parser.cc"
    break;

  case 824: // $@131: %empty
#line 2891 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4536 "dhcp6_parser.cc"
    break;

  case 825: // sub_config_control: "{" $@131 config_control_params "}"
#line 2895 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4545 "dhcp6_parser.cc"
    break;

  case 828: // config_control_params: config_control_params ","
#line 2903 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4553 "dhcp6_parser.cc"
    break;

  case 831: // $@132: %empty
#line 2913 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4565 "dhcp6_parser.cc"
    break;

  case 832: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2919 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4574 "dhcp6_parser.cc"
    break;

  case 833: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2924 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4584 "dhcp6_parser.cc"
    break;

  case 834: // $@133: %empty
#line 2932 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4596 "dhcp6_parser.cc"
    break;

  case 835: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2938 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4605 "dhcp6_parser.cc"
    break;

  case 838: // loggers_entries: loggers_entries ","
#line 2947 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4613 "dhcp6_parser.cc"
    break;

  case 839: // $@134: %empty
#line 2953 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4623 "dhcp6_parser.cc"
    break;

  case 840: // logger_entry: "{" $@134 logger_params "}"
#line 2957 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4631 "dhcp6_parser.cc"
    break;

  case 843: // logger_params: logger_params ","
#line 2963 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4639 "dhcp6_parser.cc"
    break;

  case 851: // debuglevel: "debuglevel" ":" "integer"
#line 2977 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4649 "dhcp6_parser.cc"
    break;

  case 852: // $@135: %empty
#line 2983 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4658 "dhcp6_parser.cc"
    break;

  case 853: // severity: "severity" $@135 ":" "constant string"
#line 2986 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4668 "dhcp6_parser.cc"
    break;

  case 854: // $@136: %empty
#line 2992 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4680 "dhcp6_parser.cc"
    break;

  case 855: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 2998 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4689 "dhcp6_parser.cc"
    break;

  case 858: // output_options_list_content: output_options_list_content ","
#line 3005 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4697 "dhcp6_parser.cc"
    break;

  case 859: // $@137: %empty
#line 3010 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 860: // output_entry: "{" $@137 output_params_list "}"
#line 3014 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4715 "dhcp6_parser.cc"
    break;

  case 863: // output_params_list: output_params_list ","
#line 3020 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4723 "dhcp6_parser.cc"
    break;

  case 869: // $@138: %empty
#line 3032 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4732 "dhcp6_parser.cc"
    break;

  case 870: // output: "output" $@138 ":" "constant string"
#line 3035 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4742 "dhcp6_parser.cc"
    break;

  case 871: // flush: "flush" ":" "boolean"
#line 3041 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4752 "dhcp6_parser.cc"
    break;

  case 872: // maxsize: "maxsize" ":" "integer"
#line 3047 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4762 "dhcp6_parser.cc"
    break;

  case 873: // maxver: "maxver" ":" "integer"
#line 3053 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4772 "dhcp6_parser.cc"
    break;

  case 874: // $@139: %empty
#line 3059 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4781 "dhcp6_parser.cc"
    break;

  case 875: // pattern: "pattern" $@139 ":" "constant string"
#line 3062 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4791 "dhcp6_parser.cc"
    break;

  case 876: // $@140: %empty
#line 3068 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4803 "dhcp6_parser.cc"
    break;

  case 877: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3074 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4812 "dhcp6_parser.cc"
    break;

  case 880: // compatibility_params: compatibility_params ","
#line 3081 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4820 "dhcp6_parser.cc"
    break;

  case 883: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3090 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4830 "dhcp6_parser.cc"
    break;


#line 4834 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1023;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     483, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023,    53,    29,    30,    34,    48,
      70,    73,    76,    96,   142,   154,   156,   158,   174,   268,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,    29,  -102,
     122,   163,    78,   691,    43,   -35,   210,   206,   109,   309,
     -89,   468,    72, -1023,   284,   170,   256,   297,   311, -1023,
      37, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   324,   327,
     353,   376,   378,   391,   402,   408,   414,   418,   419,   422,
     423,   434, -1023,   438,   439,   440,   442,   445, -1023, -1023,
   -1023,   446,   447,   449, -1023, -1023, -1023,   450, -1023, -1023,
   -1023, -1023, -1023, -1023,   451,   452,   453, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023,   454, -1023, -1023, -1023,
   -1023, -1023, -1023,   455,   456,   457, -1023, -1023,   458, -1023,
     131, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   461,
     462,   464,   465, -1023,   135, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   469,   472,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     138, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023,   148, -1023, -1023, -1023, -1023,
   -1023,   473, -1023,   475,   476, -1023, -1023, -1023, -1023, -1023,
   -1023,   159, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   397,
     478, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   474,
   -1023, -1023,   479, -1023, -1023, -1023,   484, -1023, -1023,   481,
     487, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023,   488,   492,   493, -1023, -1023, -1023,
   -1023,   490,   496, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023,   168, -1023, -1023, -1023,
     497, -1023, -1023,   498, -1023,   499,   503, -1023, -1023,   506,
     509, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   179, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023,   510,   186, -1023, -1023,
   -1023, -1023,    29,    29, -1023,   269,   511, -1023, -1023,   512,
     513,   514,   517,   520,   522,   272,   310,   313,   315,   318,
     320,   322,   323,   307,   316,   328,   331,   335,   339,   539,
     340,   341,   326,   336,   351,   540,   557,   558,   352,   354,
     357,   563,   570,   573,   364,   580,   581,   583,   584,   585,
     586,   372,   373,   374,   592,   595,   596,   597,   599,   601,
     602,   603,   604,   392,   609,   614,   615,   616,   618,   620,
     404,   406,   410,   622,   625, -1023,   163, -1023,   628,   428,
     429,   415,   416,    78, -1023,   629,   647,   648,   649,   650,
     436,   437,   655,   656,   657,   691, -1023,   658,    43, -1023,
     659,   448,   660,   459,   460,   -35, -1023,   661,   664,   666,
     667,   668,   669,   670, -1023,   210, -1023,   671,   672,   463,
     673,   677,   679,   480, -1023,   109,   680,   482,   486,   489,
   -1023,   309,   681,   698,   183, -1023,   500,   705,   707,   494,
     710,   501,   504,   718,   720,   507,   508,   721,   723,   726,
     727,   468, -1023,   728,   515,    72, -1023, -1023, -1023,   729,
     730,   518,   731,   732,   747,   748,   751, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023,   549, -1023, -1023, -1023, -1023, -1023,  -128,   550,   552,
   -1023, -1023, -1023,   752,   766,   767, -1023,   555,   556,   775,
     776,   567,   325, -1023, -1023, -1023,   782,   783,   784,   793,
     785,   786,   796,   795,   800, -1023,   801,   802,   803,   804,
     594,   598, -1023, -1023, -1023,   798,   806, -1023,   810, -1023,
   -1023, -1023, -1023, -1023,   812,   815,   605,   606,   607, -1023,
   -1023,   810,   610,   814, -1023,   611, -1023,   612, -1023,   613,
   -1023, -1023, -1023,   810,   810,   810,   617,   619,   621,   623,
   -1023,   624,   626, -1023,   627,   630,   631, -1023, -1023,   632,
   -1023, -1023, -1023, -1023,   633,   776, -1023, -1023,   634,   635,
   -1023,   636, -1023, -1023,   167,   639, -1023, -1023,  -128,   637,
     638,   640, -1023,   822, -1023, -1023,    29,   163, -1023,    72,
      78,   338,   338,   825, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023,   826,   827,   829, -1023, -1023,   831, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023,   -96,    29,   -32,
     240,   833,   836,   839,   192,    91,   -50,   185,   -54,   468,
   -1023, -1023,   840,  -164, -1023, -1023,   850,   852, -1023, -1023,
   -1023, -1023, -1023,   -47, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023,   825, -1023,   204,   243,   254, -1023, -1023,
   -1023, -1023,   856,   857,   858,   859,   860,   861,   862,   863,
     864,   865, -1023,   866, -1023, -1023, -1023, -1023, -1023,   255,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023,   281, -1023,   867,   868, -1023, -1023,   869,   871,
   -1023, -1023,   870,   874, -1023, -1023,   872,   878, -1023, -1023,
     876,   880, -1023, -1023, -1023,   125, -1023, -1023, -1023,   879,
   -1023, -1023, -1023,   166, -1023, -1023, -1023, -1023, -1023,   290,
   -1023, -1023, -1023, -1023,   202, -1023, -1023,   881,   883, -1023,
   -1023,   882,   886, -1023,   887,   888,   889,   890,   891,   892,
     294, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     893,   894,   895, -1023, -1023, -1023, -1023,   296, -1023, -1023,
   -1023, -1023, -1023, -1023,   896,   897,   898, -1023,   298, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     305, -1023, -1023, -1023,   899, -1023,   900, -1023, -1023, -1023,
     317, -1023, -1023, -1023, -1023, -1023,   321, -1023,   203, -1023,
     901, -1023,   342, -1023, -1023,   654, -1023,   884,   903, -1023,
   -1023,   902,   904, -1023, -1023, -1023,   905, -1023,   906, -1023,
   -1023, -1023,   907,   910,   911,   912,   516,   663,   699,   689,
     700,   701,   702,   703,   704,   706,   913,   708,   920,   922,
     924,   925,   338, -1023, -1023,   338, -1023,   825,   691, -1023,
     826,   109, -1023,   827,   309, -1023,   829,  1097, -1023,   831,
     -96, -1023, -1023,   -32, -1023,   926,   927,   240, -1023,   346,
     833, -1023,   210, -1023,   836,   -89, -1023,   839,   713,   714,
     715,   716,   717,   719,   192, -1023,   933,   935,   722,   724,
     725,    91, -1023,   733,   734,   736,   -50, -1023,   936,   938,
     185, -1023,   735,   941,   738,   942,   -54, -1023, -1023,    98,
     840, -1023,   737,  -164, -1023, -1023,   943,   944,    43, -1023,
     850,   -35, -1023,   852,   946, -1023, -1023,   247,   741,   742,
     743, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023,   387, -1023,   744,   745,   746,   750, -1023,   355, -1023,
     356, -1023,   940, -1023,   957, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023,   399, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023,   753,   754, -1023, -1023, -1023,   947, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     958,   949, -1023, -1023, -1023, -1023, -1023, -1023,   961, -1023,
     401, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   291,
     756, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   757,
     759, -1023, -1023,   761, -1023,    29, -1023, -1023,   976, -1023,
   -1023, -1023, -1023, -1023,   405, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023,   765,   411, -1023,   412, -1023,   768, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,  1097, -1023,
   -1023, -1023,   986,   988,   772, -1023,   346, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   993,   781,
     999,    98, -1023, -1023, -1023, -1023, -1023, -1023,   788,   790,
   -1023, -1023,  1007, -1023,   805, -1023, -1023, -1023,   997, -1023,
   -1023,   253, -1023,     3,   997, -1023, -1023,  1010,  1018,  1020,
   -1023,   413, -1023, -1023, -1023, -1023, -1023, -1023, -1023,  1023,
     808,   816,   824,  1027,     3, -1023,   828, -1023, -1023, -1023,
     832, -1023, -1023, -1023
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   190,     9,   377,    11,
     586,    13,   613,    15,   645,    17,   504,    19,   513,    21,
     552,    23,   339,    25,   773,    27,   824,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   647,     0,   515,   554,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   139,   822,   188,   209,   211,   213,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,     0,     0,     0,     0,     0,   158,   165,
     167,     0,     0,     0,   368,   502,   543,     0,   181,   183,
     448,   600,   602,   440,     0,     0,     0,   295,   314,   304,
     284,   683,   636,   330,   351,   715,     0,   316,   740,   754,
     771,   171,   173,     0,     0,     0,   834,   876,     0,   138,
       0,    69,    72,    73,    74,    75,    76,    77,    78,    79,
      80,   111,   112,   113,   114,   115,    81,   119,   120,   121,
     122,   123,   124,   125,   126,   117,   118,   127,   128,   129,
     106,   135,   136,   137,   131,   132,   133,    84,    85,    86,
      87,   103,    88,    90,    89,   130,    94,    95,    82,   108,
     109,   110,   107,    83,    92,    93,   101,   102,   104,    91,
      96,    97,    98,    99,   100,   105,   116,   134,   203,     0,
       0,     0,     0,   202,     0,   192,   195,   196,   197,   198,
     199,   200,   201,   577,   604,   427,   429,   431,     0,     0,
     435,   433,   677,   426,   382,   383,   384,   385,   386,   387,
     388,   389,   408,   409,   410,   411,   412,   415,   416,   417,
     418,   419,   420,   421,   422,   413,   414,   423,   424,   425,
       0,   379,   393,   394,   395,   398,   399,   402,   403,   404,
     401,   396,   397,   390,   391,   406,   407,   392,   400,   405,
     598,   597,   593,   594,   592,     0,   588,   591,   595,   596,
     629,     0,   632,     0,     0,   628,   622,   623,   621,   626,
     627,     0,   615,   618,   619,   624,   625,   620,   675,   663,
     665,   667,   669,   671,   673,   662,   659,   660,   661,     0,
     648,   649,   654,   655,   652,   656,   657,   658,   653,     0,
     533,   259,     0,   537,   535,   540,     0,   529,   530,     0,
     516,   517,   520,   532,   521,   522,   523,   539,   524,   525,
     526,   527,   528,   570,     0,     0,     0,   568,   569,   572,
     573,     0,   555,   556,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   347,   349,   344,     0,   341,   345,   346,
       0,   797,   799,     0,   802,     0,     0,   806,   810,     0,
       0,   814,   816,   818,   820,   795,   793,   794,     0,   775,
     778,   790,   779,   780,   781,   782,   783,   784,   785,   786,
     787,   788,   789,   791,   792,   831,     0,     0,   826,   829,
     830,    47,    52,     0,    39,    45,     0,    66,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   194,   191,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   381,   378,     0,   590,   587,
       0,     0,     0,     0,     0,   617,   614,     0,     0,     0,
       0,     0,     0,     0,   646,   651,   505,     0,     0,     0,
       0,     0,     0,     0,   514,   519,     0,     0,     0,     0,
     553,   558,     0,     0,   343,   340,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   777,   774,     0,     0,   828,   825,    51,    43,     0,
       0,     0,     0,     0,     0,     0,     0,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,   176,   177,   155,   156,   157,     0,     0,     0,
     169,   170,   175,     0,     0,     0,   180,     0,     0,     0,
       0,     0,     0,   437,   438,   439,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   739,     0,     0,     0,     0,
       0,     0,   185,   186,   187,     0,     0,    70,     0,   205,
     206,   207,   208,   193,     0,     0,     0,     0,     0,   446,
     447,     0,     0,     0,   380,     0,   589,     0,   631,     0,
     634,   635,   616,     0,     0,     0,     0,     0,     0,     0,
     650,     0,     0,   531,     0,     0,     0,   542,   518,     0,
     574,   575,   576,   557,     0,     0,   342,   796,     0,     0,
     801,     0,   804,   805,     0,     0,   812,   813,     0,     0,
       0,     0,   776,     0,   833,   827,     0,     0,   140,     0,
       0,     0,     0,   215,   179,   160,   161,   162,   163,   164,
     159,   166,   168,   370,   506,   545,   182,   184,   450,    40,
     601,   603,   442,   443,   444,   445,   441,     0,    48,     0,
       0,     0,   638,   332,     0,     0,     0,     0,     0,     0,
     172,   174,     0,     0,    53,   204,   579,   606,   428,   430,
     432,   436,   434,     0,   599,   630,   633,   676,   664,   666,
     668,   670,   672,   674,   534,   260,   538,   536,   541,   571,
     348,   350,   798,   800,   803,   808,   809,   807,   811,   815,
     817,   819,   821,   215,    44,     0,     0,     0,   247,   252,
     254,   256,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   269,     0,   276,   278,   280,   282,   246,     0,
     222,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   239,   240,   241,   238,   242,   243,
     244,   245,     0,   220,     0,   216,   217,   375,     0,   371,
     372,   511,     0,   507,   508,   550,     0,   546,   547,   455,
       0,   451,   452,   302,   303,     0,   297,   300,   301,     0,
     312,   313,   309,     0,   306,   310,   311,   291,   293,     0,
     286,   289,   290,   688,     0,   685,   643,     0,   639,   640,
     337,     0,   333,   334,     0,     0,     0,     0,     0,     0,
       0,   353,   356,   357,   358,   359,   360,   361,   729,   735,
       0,     0,     0,   728,   725,   726,   727,     0,   717,   720,
     723,   721,   722,   724,     0,     0,     0,   326,     0,   318,
     321,   322,   323,   324,   325,   750,   752,   749,   747,   748,
       0,   742,   745,   746,     0,   766,     0,   769,   762,   763,
       0,   756,   759,   760,   761,   764,     0,   839,     0,   836,
       0,   882,     0,   878,   881,    55,   584,     0,   580,   581,
     611,     0,   607,   608,   681,   680,     0,   679,     0,    64,
     823,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   224,   210,   212,     0,   214,   219,     0,   369,
     374,   515,   503,   510,   554,   544,   549,     0,   449,   454,
     299,   296,   315,   308,   305,     0,     0,   288,   285,   690,
     687,   684,   647,   637,   642,     0,   331,   336,     0,     0,
       0,     0,     0,     0,   355,   352,     0,     0,     0,     0,
       0,   719,   716,     0,     0,     0,   320,   317,     0,     0,
     744,   741,     0,     0,     0,     0,   758,   755,   772,     0,
     838,   835,     0,   880,   877,    57,     0,    56,     0,   578,
     583,     0,   605,   610,     0,   678,   832,     0,     0,     0,
       0,   258,   261,   262,   263,   264,   265,   266,   267,   275,
     268,     0,   274,     0,     0,     0,     0,   223,     0,   218,
       0,   373,     0,   509,     0,   548,   501,   474,   475,   476,
     478,   479,   480,   464,   465,   483,   484,   485,   486,   487,
     490,   491,   492,   493,   494,   495,   496,   497,   488,   489,
     498,   499,   500,   460,   461,   462,   463,   472,   473,   469,
     470,   471,   468,   477,     0,   457,   466,   481,   482,   467,
     453,   298,   307,     0,     0,   287,   710,   712,     0,   708,
     702,   703,   704,   705,   706,   707,   709,   699,   700,   701,
       0,   691,   692,   695,   696,   697,   698,   686,     0,   641,
       0,   335,   362,   363,   364,   365,   366,   367,   354,     0,
       0,   734,   737,   738,   718,   327,   328,   329,   319,     0,
       0,   743,   765,     0,   768,     0,   757,   854,     0,   852,
     850,   844,   848,   849,     0,   841,   846,   847,   845,   837,
     883,   879,    54,    59,     0,   582,     0,   609,     0,   249,
     250,   251,   248,   253,   255,   257,   271,   272,   273,   270,
     277,   279,   281,   283,   221,   376,   512,   551,   459,   456,
     292,   294,     0,     0,     0,   689,   694,   644,   338,   731,
     732,   733,   730,   736,   751,   753,   767,   770,     0,     0,
       0,   843,   840,    58,   585,   612,   682,   458,     0,     0,
     714,   693,     0,   851,     0,   842,   711,   713,     0,   853,
     859,     0,   856,     0,   858,   855,   869,     0,     0,     0,
     874,     0,   861,   864,   865,   866,   867,   868,   857,     0,
       0,     0,     0,     0,   863,   860,     0,   871,   872,   873,
       0,   862,   870,   875
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023,   -10, -1023,  -610, -1023,
     330, -1023, -1023, -1023, -1023,   292, -1023,  -568, -1023, -1023,
   -1023,   -71, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   337,
     547, -1023, -1023,   -42,    11,    14,    17,    18,    28,   -31,
     -29,   -27,   -13,    31,    33,    41, -1023,    44,    45,    46,
      47, -1023,   344,    51, -1023,    57, -1023,    62,    63,    67,
   -1023,    69, -1023,    74, -1023, -1023, -1023, -1023, -1023,    75,
   -1023,    77, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     362,   544, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023,   245, -1023,    60, -1023,  -720,    93,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     -46, -1023,  -764, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023,    66, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023,    84,  -746, -1023, -1023, -1023, -1023,
      86, -1023, -1023, -1023, -1023, -1023, -1023, -1023,    49, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023,    64, -1023, -1023, -1023,
      68,   562, -1023, -1023, -1023, -1023, -1023, -1023, -1023,    71,
   -1023, -1023, -1023, -1023, -1023, -1023, -1022, -1023, -1023, -1023,
      97, -1023, -1023, -1023,   100,   608, -1023, -1023, -1021, -1023,
   -1020, -1023,    83, -1023,    85, -1023,    79,    80,    81,    82,
   -1023, -1023, -1023, -1019, -1023, -1023, -1023, -1023,    92, -1023,
   -1023,  -148,  1065, -1023, -1023, -1023, -1023, -1023,   101, -1023,
   -1023, -1023,   105, -1023,   641, -1023,   -62, -1023, -1023, -1023,
   -1023, -1023,   -59, -1023, -1023, -1023, -1023, -1023,    -5, -1023,
   -1023, -1023,   114, -1023, -1023, -1023,   117, -1023,   591, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023,    87, -1023, -1023, -1023,    55,   642, -1023, -1023,   -60,
   -1023,     0, -1023, -1023, -1023, -1023, -1023,    61, -1023, -1023,
   -1023,    89,   644, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     -49, -1023, -1023, -1023,   113, -1023, -1023, -1023,   116, -1023,
     652,   386, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1018, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023,   121, -1023, -1023, -1023,  -114, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023,   102, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
      94, -1023, -1023, -1023, -1023, -1023, -1023, -1023,    90, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,   424,
     643, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
     470,   590, -1023, -1023, -1023, -1023, -1023, -1023,    95, -1023,
   -1023,  -121, -1023, -1023, -1023, -1023, -1023, -1023,  -142, -1023,
   -1023,  -146, -1023, -1023, -1023, -1023, -1023, -1023, -1023, -1023,
   -1023, -1023,   110, -1023
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     760,    87,    88,    41,    68,    84,    85,   785,   995,  1106,
    1107,   848,    43,    70,    90,   446,    91,    45,    71,   160,
     161,   162,   449,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   475,   750,   181,   476,   182,   477,   183,   184,   185,
     508,   186,   509,   187,   188,   189,   190,   469,   191,   192,
     485,   193,   486,   194,   195,   196,   197,   451,    47,    72,
     234,   235,   236,   518,   237,   238,   239,   240,   198,   452,
     199,   453,   200,   454,   874,   875,   876,  1035,   849,   850,
     851,  1012,  1272,   852,  1013,   853,  1014,   854,  1015,   855,
     856,   558,   857,   858,   859,   860,   861,   862,   863,   864,
     865,  1026,  1279,   866,   867,   868,  1028,   869,  1029,   870,
    1030,   871,  1031,   201,   497,   909,   910,   911,  1055,   912,
    1056,   202,   494,   895,   896,   897,   898,   203,   496,   903,
     904,   905,   906,   204,   495,   205,   504,   958,   959,   960,
     961,   962,   206,   500,   921,   922,   923,  1065,    63,    80,
     396,   397,   398,   572,   399,   573,   207,   501,   930,   931,
     932,   933,   934,   935,   936,   937,   208,   481,   878,   879,
     880,  1038,    49,    73,   280,   281,   282,   527,   283,   528,
     284,   529,   285,   533,   286,   532,   209,   210,   211,   212,
     490,   766,   291,   292,   213,   487,   890,   891,   892,  1047,
    1184,  1185,   214,   482,    57,    77,   882,   883,   884,  1041,
      59,    78,   359,   360,   361,   362,   363,   364,   365,   557,
     366,   561,   367,   560,   368,   369,   562,   370,   215,   483,
     886,   887,   888,  1044,    61,    79,   381,   382,   383,   384,
     385,   566,   386,   387,   388,   389,   390,   294,   525,   997,
     998,   999,  1108,    51,    74,   305,   306,   307,   537,   216,
     488,   217,   489,   297,   526,  1001,  1002,  1003,  1111,    53,
      75,   321,   322,   323,   540,   324,   325,   542,   326,   327,
     218,   499,   917,   918,   919,  1062,    55,    76,   339,   340,
     341,   342,   548,   343,   549,   344,   550,   345,   551,   346,
     552,   347,   553,   348,   547,   299,   534,  1006,  1007,  1114,
     219,   498,   914,   915,  1059,  1210,  1211,  1212,  1213,  1214,
    1292,  1215,  1293,  1216,   220,   502,   947,   948,   949,  1076,
    1302,   950,   951,  1077,   952,   953,   221,   222,   505,   970,
     971,   972,  1088,   973,  1089,   223,   506,   980,   981,   982,
     983,  1093,   984,   985,  1095,   224,   507,    65,    81,   418,
     419,   420,   421,   577,   422,   578,   423,   424,   580,   425,
     426,   427,   583,   817,   428,   584,   429,   430,   431,   587,
     432,   588,   433,   589,   434,   590,   225,   450,    67,    82,
     437,   438,   439,   593,   440,   226,   513,   988,   989,  1099,
    1254,  1255,  1256,  1257,  1310,  1258,  1308,  1331,  1332,  1333,
    1341,  1342,  1343,  1349,  1344,  1345,  1346,  1347,  1353,   227,
     514,   992,   993,   994
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     159,   233,   253,   301,   315,   335,    38,   357,   377,   395,
     415,   944,   241,   295,   308,   319,   337,   379,   371,   391,
     380,   416,   872,   902,   298,  1174,  1175,  1176,  1183,  1189,
     759,   254,   358,   378,    31,   893,    32,    42,    33,   990,
     447,    44,   260,   126,   261,   448,   262,   131,   132,   393,
     394,   131,   132,    30,   158,    46,   745,   746,   747,   748,
     263,   310,   311,   312,   313,   314,   131,   132,   293,   304,
     318,   336,   242,   296,   309,   320,   338,    48,   372,   392,
      50,   417,   329,    52,   255,   435,   436,   256,   250,  1004,
     257,   258,   251,   749,   228,   229,   230,   231,   232,   893,
     900,   259,   901,    54,   264,   759,   265,   954,   955,   956,
     974,   975,   976,   791,   266,   938,    86,   267,   268,   269,
     270,   126,   894,   833,   271,   797,   798,   799,  1050,   158,
     272,  1051,    89,   350,   516,   273,   274,   300,   523,   517,
     275,   535,   276,   524,   131,   132,   536,   277,   278,    56,
     279,   538,   287,   288,   289,   290,   539,   302,   316,   303,
     317,    58,   545,    60,   977,    62,   250,   546,   158,  1053,
     251,   574,  1054,   442,    92,    93,   575,   351,    94,   131,
     132,    64,   591,   158,    95,    96,    97,   592,   351,   595,
     352,   353,   131,   132,   596,   354,   355,   356,  1336,   131,
     132,  1337,  1338,  1339,  1340,  1060,  1100,   516,  1061,  1101,
     131,   132,  1009,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   939,   940,   941,   942,   595,    34,    35,    36,
      37,  1010,   127,   128,   129,   130,  1334,   523,  1032,  1335,
     443,   158,  1011,  1033,   131,   132,  1174,  1175,  1176,  1183,
    1189,   133,  1269,  1270,  1271,    66,   134,   135,   136,   137,
     138,   139,   140,   125,  1032,   141,   131,   132,   126,  1034,
     441,   142,  1247,  1057,  1248,  1249,   158,  1074,  1058,  1081,
     143,  1086,  1075,   144,  1082,   444,  1087,   902,  1090,   158,
     145,   131,   132,  1091,   445,  1138,   158,   944,   146,   147,
    1096,   393,   394,   148,   591,  1097,   149,   158,   455,  1098,
     150,   456,   328,   924,   925,   926,   927,   928,   929,   329,
     330,   331,   332,   333,   334,  1103,   965,   966,   815,   816,
    1104,   151,   152,   153,   154,   155,   156,   457,  1032,   535,
     907,   908,   828,  1284,  1285,   157,   829,   830,   831,   832,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
     458,   158,   459,   843,   844,   845,   846,   847,   351,   373,
     352,   353,   374,   375,   376,   460,    98,    99,   100,   101,
     102,   103,  1288,   158,   574,   554,   461,  1289,  1311,  1298,
     131,   132,   462,  1312,   538,   545,  1354,   351,   463,  1314,
    1315,  1355,   464,   465,   126,   351,   466,   467,   158,  1276,
    1277,  1278,   597,   598,   762,   763,   764,   765,   468,  1299,
    1300,  1301,   470,   471,   472,   159,   473,   131,   132,   474,
     478,   479,   233,   480,   484,   491,   492,   493,   503,   510,
     511,   512,   515,   241,   253,   519,   520,   301,   521,   522,
    1196,  1197,  1198,   530,   315,   295,   531,   541,   308,   543,
     544,   555,   556,   559,   335,   319,   298,   599,   563,   564,
     565,   607,   567,   254,   357,   337,   568,   569,   570,   571,
     377,   576,   579,   581,   260,   371,   261,   582,   262,   379,
     585,   391,   380,   586,   594,   600,   601,   602,   603,   358,
     415,   604,   263,   242,   605,   378,   606,   158,   615,   608,
     293,   416,   609,   304,   610,   296,   616,   611,   309,   612,
     318,   613,   614,   621,   627,   320,   255,   624,   617,   256,
     336,   618,   257,   258,   619,   338,   158,   625,   620,   622,
     623,   628,   629,   259,   158,   372,   264,   633,   265,   131,
     132,   392,   626,   630,   634,   631,   266,   635,   632,   267,
     268,   269,   270,   636,   637,   638,   271,   639,   640,   641,
     642,   417,   272,   643,   644,   645,   646,   273,   274,   647,
     648,   649,   275,   650,   276,   651,   652,   653,   654,   277,
     278,   655,   279,   656,   287,   288,   289,   290,   657,   658,
     659,   302,   660,   303,   661,   662,   665,   663,   316,   666,
     317,   664,   668,   674,   671,   672,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   669,
     670,   675,   676,   677,   678,   679,   413,   414,   680,   681,
     682,   683,   685,   687,   689,   693,   159,   688,   694,   233,
     695,   696,   697,   698,   699,   701,   702,   704,   690,   691,
     241,   705,   703,   706,   709,   714,   158,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   707,   715,   710,   943,   957,   967,   711,   415,   718,
     712,   719,   991,   720,   721,   945,   963,   968,   978,   416,
     722,   717,   724,   723,   725,   728,   824,   729,   726,   727,
     730,   731,   733,   736,   734,  1121,   738,   737,   739,   740,
     242,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   741,   742,   743,   753,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   744,   751,   126,
     752,   754,   755,   756,   757,   946,   964,   969,   979,   417,
     758,   128,   129,    32,   243,   761,   244,   767,   768,   769,
     771,   772,   131,   132,   245,   246,   247,   248,   249,   133,
     770,   773,   774,   782,   134,   135,   136,   775,   776,   777,
     778,   779,   780,   783,   250,   784,   781,   786,   251,   142,
     787,   793,   818,   788,   789,   790,   252,   823,   792,   794,
     795,   796,   873,   877,   881,   800,   885,   801,   889,   802,
     913,   803,   804,   916,   805,   806,   920,   987,   807,   808,
     809,   810,   812,   813,   814,   820,   821,   996,   822,  1000,
    1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,
    1027,  1037,  1105,  1036,  1040,  1039,  1042,  1043,  1045,   151,
     152,  1046,  1048,  1049,  1122,  1052,  1064,  1063,  1066,  1067,
    1109,  1068,  1069,  1070,  1071,  1072,  1073,  1078,  1079,  1080,
    1083,  1084,  1085,  1092,  1094,  1102,  1110,  1113,  1112,   158,
    1124,  1117,  1116,  1115,  1118,  1119,  1120,  1131,  1123,  1125,
    1126,  1127,  1128,  1129,  1133,  1130,  1134,  1132,  1135,  1136,
    1193,  1194,  1222,  1223,  1224,  1225,  1226,  1229,  1227,  1230,
    1239,  1231,  1240,  1232,  1233,  1243,  1245,  1263,  1286,  1262,
    1268,  1294,  1296,  1236,  1235,  1237,  1242,  1244,  1260,  1273,
    1274,  1275,  1280,  1281,  1282,  1287,  1295,   253,  1283,  1297,
     357,  1290,  1291,   377,  1303,  1304,  1146,  1305,   295,  1306,
    1309,   371,   379,  1313,   391,   380,  1316,  1187,  1199,   298,
    1318,   335,  1319,  1320,   395,   358,   254,  1322,   378,  1208,
    1323,  1173,   337,  1324,  1330,  1147,  1326,   260,  1327,   261,
     943,   262,  1328,  1206,  1350,   957,  1153,  1200,  1154,   967,
    1155,   945,  1351,  1329,  1352,   263,   963,  1356,  1250,  1357,
     968,  1360,   991,   293,  1156,  1358,   978,   301,   296,  1252,
     315,   372,  1186,  1359,   392,   811,  1362,  1188,   308,   255,
    1363,   319,   256,  1251,  1207,   257,   258,   336,  1148,  1209,
     899,  1149,   338,   667,  1150,  1151,   259,   673,  1008,   264,
    1201,   265,   819,  1202,   825,  1152,  1203,  1204,  1157,   266,
    1158,   946,   267,   268,   269,   270,   964,  1205,  1159,   271,
     969,  1160,  1161,  1162,  1163,   272,   979,  1139,  1164,  1253,
     273,   274,   827,   304,  1165,   275,   318,   276,   309,  1166,
    1167,   320,   277,   278,  1168,   279,  1169,   287,   288,   289,
     290,  1170,  1171,  1195,  1172,  1137,  1179,  1180,  1181,  1182,
    1177,  1221,  1178,  1220,  1191,  1238,   716,  1141,  1140,  1192,
    1317,  1190,   349,   684,  1143,  1228,  1142,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
    1145,  1144,   713,  1264,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,  1267,   126,   351,  1219,  1218,  1005,
     686,  1217,  1321,  1234,  1241,   735,  1246,   128,   129,   692,
    1325,   302,  1348,   303,   316,  1259,   317,  1265,   131,   132,
    1266,   246,   247,   986,   249,   133,   708,   700,  1361,   826,
     134,   135,   136,  1261,     0,     0,     0,  1146,     0,     0,
     250,     0,     0,     0,   251,  1199,     0,     0,  1187,     0,
       0,     0,   252,     0,   732,  1307,  1208,     0,     0,     0,
    1250,     0,  1173,     0,     0,     0,  1147,     0,     0,     0,
    1206,  1252,     0,     0,  1200,     0,     0,  1153,     0,  1154,
       0,  1155,     0,     0,     0,  1251,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1156,     0,     0,     0,     0,
       0,     0,     0,  1186,     0,   151,   152,     0,  1188,     0,
       0,  1207,     0,     0,     0,     0,  1209,     0,     0,  1148,
       0,     0,  1149,     0,     0,  1150,  1151,  1201,     0,     0,
    1202,  1253,     0,  1203,  1204,   158,  1152,     0,     0,  1157,
       0,  1158,     0,     0,  1205,     0,     0,     0,     0,  1159,
       0,     0,  1160,  1161,  1162,  1163,     0,     0,     0,  1164,
       0,     0,     0,     0,     0,  1165,     0,     0,     0,     0,
    1166,  1167,     0,     0,     0,  1168,     0,  1169,     0,     0,
       0,     0,  1170,  1171,     0,  1172,     0,  1179,  1180,  1181,
    1182,  1177,     0,  1178
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   775,    72,    73,    74,    75,    76,    79,    78,    79,
      79,    81,   742,   769,    73,  1047,  1047,  1047,  1047,  1047,
     640,    73,    78,    79,     5,   131,     7,     7,     9,   203,
       3,     7,    73,    78,    73,     8,    73,   101,   102,   138,
     139,   101,   102,     0,   218,     7,   184,   185,   186,   187,
      73,    96,    97,    98,    99,   100,   101,   102,    73,    74,
      75,    76,    72,    73,    74,    75,    76,     7,    78,    79,
       7,    81,   129,     7,    73,    13,    14,    73,   123,   136,
      73,    73,   127,   221,    16,    17,    18,    19,    20,   131,
     132,    73,   134,     7,    73,   715,    73,   157,   158,   159,
     164,   165,   166,   681,    73,    24,   218,    73,    73,    73,
      73,    78,   218,    32,    73,   693,   694,   695,     3,   218,
      73,     6,    10,    24,     3,    73,    73,    94,     3,     8,
      73,     3,    73,     8,   101,   102,     8,    73,    73,     7,
      73,     3,    73,    73,    73,    73,     8,    74,    75,    74,
      75,     7,     3,     7,   218,     7,   123,     8,   218,     3,
     127,     3,     6,     3,    11,    12,     8,    79,    15,   101,
     102,     7,     3,   218,    21,    22,    23,     8,    79,     3,
      81,    82,   101,   102,     8,    86,    87,    88,   195,   101,
     102,   198,   199,   200,   201,     3,     3,     3,     6,     6,
     101,   102,     8,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,   151,   152,   153,   154,     3,   218,   219,   220,
     221,     8,    89,    90,    91,    92,     3,     3,     3,     6,
       4,   218,     8,     8,   101,   102,  1288,  1288,  1288,  1288,
    1288,   108,    25,    26,    27,     7,   113,   114,   115,   116,
     117,   118,   119,    77,     3,   122,   101,   102,    78,     8,
       6,   128,   194,     3,   196,   197,   218,     3,     8,     3,
     137,     3,     8,   140,     8,     8,     8,  1053,     3,   218,
     147,   101,   102,     8,     3,  1035,   218,  1081,   155,   156,
       3,   138,   139,   160,     3,     8,   163,   218,     4,     8,
     167,     4,   122,   141,   142,   143,   144,   145,   146,   129,
     130,   131,   132,   133,   134,     3,   161,   162,   181,   182,
       8,   188,   189,   190,   191,   192,   193,     4,     3,     3,
     120,   121,    24,     8,     8,   202,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       4,   218,     4,    45,    46,    47,    48,    49,    79,    80,
      81,    82,    83,    84,    85,     4,    50,    51,    52,    53,
      54,    55,     3,   218,     3,     8,     4,     8,     3,     8,
     101,   102,     4,     8,     3,     3,     3,    79,     4,     8,
       8,     8,     4,     4,    78,    79,     4,     4,   218,    42,
      43,    44,   442,   443,   109,   110,   111,   112,     4,   148,
     149,   150,     4,     4,     4,   516,     4,   101,   102,     4,
       4,     4,   523,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   523,   535,     4,     4,   538,     4,     4,
     124,   125,   126,     4,   545,   535,     4,     4,   538,     4,
       4,     3,     8,     4,   555,   545,   535,   218,     4,     8,
       3,   219,     4,   535,   565,   555,     4,     4,     8,     3,
     571,     4,     4,     4,   535,   565,   535,     4,   535,   571,
       4,   571,   571,     4,     4,     4,     4,     4,     4,   565,
     591,     4,   535,   523,     4,   571,     4,   218,   221,   219,
     535,   591,   219,   538,   219,   535,   220,   219,   538,   219,
     545,   219,   219,     4,     4,   545,   535,   221,   220,   535,
     555,   220,   535,   535,   219,   555,   218,   221,   219,   219,
     219,     4,     4,   535,   218,   565,   535,     4,   535,   101,
     102,   571,   221,   221,     4,   221,   535,     4,   221,   535,
     535,   535,   535,   219,     4,     4,   535,     4,     4,     4,
       4,   591,   535,   221,   221,   221,     4,   535,   535,     4,
       4,     4,   535,     4,   535,     4,     4,     4,     4,   535,
     535,   219,   535,     4,   535,   535,   535,   535,     4,     4,
       4,   538,     4,   538,     4,   221,     4,   221,   545,     4,
     545,   221,     4,     4,   219,   219,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   221,
     221,     4,     4,     4,     4,   219,   188,   189,   221,     4,
       4,     4,     4,     4,     4,     4,   737,   219,     4,   740,
       4,     4,     4,     4,     4,     4,     4,     4,   219,   219,
     740,     4,   219,     4,     4,     4,   218,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   221,     4,   221,   775,   776,   777,   221,   779,     4,
     221,     4,   783,   219,     4,   775,   776,   777,   778,   779,
     219,   221,     4,   219,     4,     4,   736,     4,   221,   221,
       4,     4,     4,     4,   219,   219,   218,     7,     7,     7,
     740,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     7,     7,     5,     5,    67,    68,
      69,    70,    71,    72,    73,    74,    75,   218,   218,    78,
     218,     5,     5,   218,   218,   775,   776,   777,   778,   779,
       5,    90,    91,     7,    93,   218,    95,     5,     5,     5,
       5,     5,   101,   102,   103,   104,   105,   106,   107,   108,
       7,     5,     7,     5,   113,   114,   115,     7,     7,     7,
       7,     7,   218,     7,   123,     5,   218,     5,   127,   128,
       5,     7,   183,   218,   218,   218,   135,     5,   218,   218,
     218,   218,     7,     7,     7,   218,     7,   218,     7,   218,
       7,   218,   218,     7,   218,   218,     7,     7,   218,   218,
     218,   218,   218,   218,   218,   218,   218,     7,   218,     7,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   218,     6,     3,     6,     6,     3,     6,   188,
     189,     3,     6,     3,   221,     6,     3,     6,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     6,   218,
     221,     4,     6,     8,     4,     4,     4,     4,   219,   219,
     219,   219,   219,   219,     4,   219,     4,   219,     4,     4,
       4,     4,   219,   219,   219,   219,   219,     4,   219,     4,
       4,   219,     4,   219,   219,     4,     4,     3,     8,     6,
       4,     4,     3,   219,   221,   219,   221,   219,   221,   218,
     218,   218,   218,   218,   218,     8,     8,  1038,   218,     8,
    1041,   218,   218,  1044,   218,   218,  1047,   218,  1038,   218,
       4,  1041,  1044,   218,  1044,  1044,   218,  1047,  1059,  1038,
       4,  1062,     4,   221,  1065,  1041,  1038,     4,  1044,  1059,
     219,  1047,  1062,     4,     7,  1047,   218,  1038,   218,  1038,
    1081,  1038,     5,  1059,     4,  1086,  1047,  1059,  1047,  1090,
    1047,  1081,     4,   218,     4,  1038,  1086,     4,  1099,   221,
    1090,     4,  1103,  1038,  1047,   219,  1096,  1108,  1038,  1099,
    1111,  1041,  1047,   219,  1044,   715,   218,  1047,  1108,  1038,
     218,  1111,  1038,  1099,  1059,  1038,  1038,  1062,  1047,  1059,
     768,  1047,  1062,   516,  1047,  1047,  1038,   523,   823,  1038,
    1059,  1038,   728,  1059,   737,  1047,  1059,  1059,  1047,  1038,
    1047,  1081,  1038,  1038,  1038,  1038,  1086,  1059,  1047,  1038,
    1090,  1047,  1047,  1047,  1047,  1038,  1096,  1037,  1047,  1099,
    1038,  1038,   740,  1108,  1047,  1038,  1111,  1038,  1108,  1047,
    1047,  1111,  1038,  1038,  1047,  1038,  1047,  1038,  1038,  1038,
    1038,  1047,  1047,  1057,  1047,  1032,  1047,  1047,  1047,  1047,
    1047,  1067,  1047,  1065,  1050,  1086,   574,  1040,  1038,  1053,
    1288,  1049,    77,   535,  1043,  1074,  1041,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
    1046,  1044,   571,  1108,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,  1113,    78,    79,  1064,  1062,   793,
     538,  1060,  1296,  1081,  1090,   595,  1096,    90,    91,   545,
    1311,  1108,  1334,  1108,  1111,  1100,  1111,  1110,   101,   102,
    1111,   104,   105,   779,   107,   108,   565,   555,  1354,   739,
     113,   114,   115,  1103,    -1,    -1,    -1,  1288,    -1,    -1,
     123,    -1,    -1,    -1,   127,  1296,    -1,    -1,  1288,    -1,
      -1,    -1,   135,    -1,   591,  1245,  1296,    -1,    -1,    -1,
    1311,    -1,  1288,    -1,    -1,    -1,  1288,    -1,    -1,    -1,
    1296,  1311,    -1,    -1,  1296,    -1,    -1,  1288,    -1,  1288,
      -1,  1288,    -1,    -1,    -1,  1311,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1288,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1288,    -1,   188,   189,    -1,  1288,    -1,
      -1,  1296,    -1,    -1,    -1,    -1,  1296,    -1,    -1,  1288,
      -1,    -1,  1288,    -1,    -1,  1288,  1288,  1296,    -1,    -1,
    1296,  1311,    -1,  1296,  1296,   218,  1288,    -1,    -1,  1288,
      -1,  1288,    -1,    -1,  1296,    -1,    -1,    -1,    -1,  1288,
      -1,    -1,  1288,  1288,  1288,  1288,    -1,    -1,    -1,  1288,
      -1,    -1,    -1,    -1,    -1,  1288,    -1,    -1,    -1,    -1,
    1288,  1288,    -1,    -1,    -1,  1288,    -1,  1288,    -1,    -1,
      -1,    -1,  1288,  1288,    -1,  1288,    -1,  1288,  1288,  1288,
    1288,  1288,    -1,  1288
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
       0,     5,     7,     9,   218,   219,   220,   221,   238,   239,
     240,   245,     7,   254,     7,   259,     7,   310,     7,   424,
       7,   505,     7,   521,     7,   538,     7,   456,     7,   462,
       7,   486,     7,   400,     7,   609,     7,   640,   246,   241,
     255,   260,   311,   425,   506,   522,   539,   457,   463,   487,
     401,   610,   641,   238,   247,   248,   218,   243,   244,    10,
     256,   258,    11,    12,    15,    21,    22,    23,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    89,    90,    91,
      92,   101,   102,   108,   113,   114,   115,   116,   117,   118,
     119,   122,   128,   137,   140,   147,   155,   156,   160,   163,
     167,   188,   189,   190,   191,   192,   193,   202,   218,   253,
     261,   262,   263,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   285,   287,   289,   290,   291,   293,   295,   296,   297,
     298,   300,   301,   303,   305,   306,   307,   308,   320,   322,
     324,   365,   373,   379,   385,   387,   394,   408,   418,   438,
     439,   440,   441,   446,   454,   480,   511,   513,   532,   562,
     576,   588,   589,   597,   607,   638,   647,   671,    16,    17,
      18,    19,    20,   253,   312,   313,   314,   316,   317,   318,
     319,   511,   513,    93,    95,   103,   104,   105,   106,   107,
     123,   127,   135,   253,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   279,   280,   281,
     282,   285,   287,   289,   290,   291,   293,   295,   301,   303,
     426,   427,   428,   430,   432,   434,   436,   438,   439,   440,
     441,   444,   445,   480,   499,   511,   513,   515,   532,   557,
      94,   253,   434,   436,   480,   507,   508,   509,   511,   513,
      96,    97,    98,    99,   100,   253,   434,   436,   480,   511,
     513,   523,   524,   525,   527,   528,   530,   531,   122,   129,
     130,   131,   132,   133,   134,   253,   480,   511,   513,   540,
     541,   542,   543,   545,   547,   549,   551,   553,   555,   454,
      24,    79,    81,    82,    86,    87,    88,   253,   342,   464,
     465,   466,   467,   468,   469,   470,   472,   474,   476,   477,
     479,   511,   513,    80,    83,    84,    85,   253,   342,   468,
     474,   488,   489,   490,   491,   492,   494,   495,   496,   497,
     498,   511,   513,   138,   139,   253,   402,   403,   404,   406,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   188,   189,   253,   511,   513,   611,   612,
     613,   614,   616,   618,   619,   621,   622,   623,   626,   628,
     629,   630,   632,   634,   636,    13,    14,   642,   643,   644,
     646,     6,     3,     4,     8,     3,   257,     3,     8,   264,
     639,   309,   321,   323,   325,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   299,
       4,     4,     4,     4,     4,   283,   286,   288,     4,     4,
       4,   419,   455,   481,     4,   302,   304,   447,   512,   514,
     442,     4,     4,     4,   374,   386,   380,   366,   563,   533,
     395,   409,   577,     4,   388,   590,   598,   608,   292,   294,
       4,     4,     4,   648,   672,     4,     3,     8,   315,     4,
       4,     4,     4,     3,     8,   500,   516,   429,   431,   433,
       4,     4,   437,   435,   558,     3,     8,   510,     3,     8,
     526,     4,   529,     4,     4,     3,     8,   556,   544,   546,
     548,   550,   552,   554,     8,     3,     8,   471,   343,     4,
     475,   473,   478,     4,     8,     3,   493,     4,     4,     4,
       8,     3,   405,   407,     3,     8,     4,   615,   617,     4,
     620,     4,     4,   624,   627,     4,     4,   631,   633,   635,
     637,     3,     8,   645,     4,     3,     8,   238,   238,   218,
       4,     4,     4,     4,     4,     4,     4,   219,   219,   219,
     219,   219,   219,   219,   219,   221,   220,   220,   220,   219,
     219,     4,   219,   219,   221,   221,   221,     4,     4,     4,
     221,   221,   221,     4,     4,     4,   219,     4,     4,     4,
       4,     4,     4,   221,   221,   221,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   219,     4,     4,     4,     4,
       4,     4,   221,   221,   221,     4,     4,   262,     4,   221,
     221,   219,   219,   313,     4,     4,     4,     4,     4,   219,
     221,     4,     4,     4,   427,     4,   508,     4,   219,     4,
     219,   219,   524,     4,     4,     4,     4,     4,     4,     4,
     542,     4,     4,   219,     4,     4,     4,   221,   466,     4,
     221,   221,   221,   490,     4,     4,   403,   221,     4,     4,
     219,     4,   219,   219,     4,     4,   221,   221,     4,     4,
       4,     4,   612,     4,   219,   643,     4,     7,   218,     7,
       7,     7,     7,     5,   218,   184,   185,   186,   187,   221,
     284,   218,   218,     5,     5,     5,   218,   218,     5,   240,
     242,   218,   109,   110,   111,   112,   443,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     7,     7,
     218,   218,     5,     7,     5,   249,     5,     5,   218,   218,
     218,   249,   218,     7,   218,   218,   218,   249,   249,   249,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   242,   218,   218,   218,   181,   182,   625,   183,   284,
     218,   218,   218,     5,   238,   261,   642,   312,    24,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    45,    46,    47,    48,    49,   253,   330,
     331,   332,   335,   337,   339,   341,   342,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   355,   356,   357,   359,
     361,   363,   330,     7,   326,   327,   328,     7,   420,   421,
     422,     7,   458,   459,   460,     7,   482,   483,   484,     7,
     448,   449,   450,   131,   218,   375,   376,   377,   378,   247,
     132,   134,   377,   381,   382,   383,   384,   120,   121,   367,
     368,   369,   371,     7,   564,   565,     7,   534,   535,   536,
       7,   396,   397,   398,   141,   142,   143,   144,   145,   146,
     410,   411,   412,   413,   414,   415,   416,   417,    24,   151,
     152,   153,   154,   253,   344,   511,   513,   578,   579,   580,
     583,   584,   586,   587,   157,   158,   159,   253,   389,   390,
     391,   392,   393,   511,   513,   161,   162,   253,   511,   513,
     591,   592,   593,   595,   164,   165,   166,   218,   511,   513,
     599,   600,   601,   602,   604,   605,   611,     7,   649,   650,
     203,   253,   673,   674,   675,   250,     7,   501,   502,   503,
       7,   517,   518,   519,   136,   543,   559,   560,   326,     8,
       8,     8,   333,   336,   338,   340,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   353,     4,   358,   360,
     362,   364,     3,     8,     8,   329,     6,     3,   423,     6,
       3,   461,     6,     3,   485,     6,     3,   451,     6,     3,
       3,     6,     6,     3,     6,   370,   372,     3,     8,   566,
       3,     6,   537,     6,     3,   399,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   581,   585,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   594,   596,
       3,     8,     4,   603,     4,   606,     3,     8,     8,   651,
       3,     6,     4,     3,     8,   218,   251,   252,   504,     6,
       3,   520,     6,     3,   561,     8,     6,     4,     4,     4,
       4,   219,   221,   219,   221,   219,   219,   219,   219,   219,
     219,     4,   219,     4,     4,     4,     4,   331,   330,   328,
     426,   422,   464,   460,   488,   484,   253,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     279,   280,   281,   282,   285,   287,   289,   290,   291,   293,
     295,   301,   303,   342,   418,   430,   432,   434,   436,   438,
     439,   440,   441,   445,   452,   453,   480,   511,   513,   557,
     450,   376,   382,     4,     4,   368,   124,   125,   126,   253,
     265,   266,   267,   268,   269,   270,   342,   480,   511,   513,
     567,   568,   569,   570,   571,   573,   575,   565,   540,   536,
     402,   398,   219,   219,   219,   219,   219,   219,   411,     4,
       4,   219,   219,   219,   579,   221,   219,   219,   390,     4,
       4,   592,   221,     4,   219,     4,   600,   194,   196,   197,
     253,   342,   511,   513,   652,   653,   654,   655,   657,   650,
     221,   674,     6,     3,   507,   503,   523,   519,     4,    25,
      26,    27,   334,   218,   218,   218,    42,    43,    44,   354,
     218,   218,   218,   218,     8,     8,     8,     8,     3,     8,
     218,   218,   572,   574,     4,     8,     3,     8,     8,   148,
     149,   150,   582,   218,   218,   218,   218,   238,   658,     4,
     656,     3,     8,   218,     8,     8,   218,   453,     4,     4,
     221,   569,     4,   219,     4,   653,   218,   218,     5,   218,
       7,   659,   660,   661,     3,     6,   195,   198,   199,   200,
     201,   662,   663,   664,   666,   667,   668,   669,   660,   665,
       4,     4,     4,   670,     3,     8,     4,   221,   219,   219,
       4,   663,   218,   218
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   222,   224,   223,   225,   223,   226,   223,   227,   223,
     228,   223,   229,   223,   230,   223,   231,   223,   232,   223,
     233,   223,   234,   223,   235,   223,   236,   223,   237,   223,
     238,   238,   238,   238,   238,   238,   238,   239,   241,   240,
     242,   243,   243,   244,   244,   244,   246,   245,   247,   247,
     248,   248,   248,   250,   249,   251,   251,   252,   252,   252,
     253,   255,   254,   257,   256,   256,   258,   260,   259,   261,
     261,   261,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   264,
     263,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   283,   282,
     284,   284,   284,   284,   284,   286,   285,   288,   287,   289,
     290,   292,   291,   294,   293,   295,   296,   297,   299,   298,
     300,   302,   301,   304,   303,   305,   306,   307,   309,   308,
     311,   310,   312,   312,   312,   313,   313,   313,   313,   313,
     313,   313,   313,   315,   314,   316,   317,   318,   319,   321,
     320,   323,   322,   325,   324,   326,   326,   327,   327,   327,
     329,   328,   330,   330,   330,   331,   331,   331,   331,   331,
     331,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     331,   331,   331,   331,   331,   331,   331,   333,   332,   334,
     334,   334,   336,   335,   338,   337,   340,   339,   341,   343,
     342,   344,   345,   346,   347,   348,   349,   350,   351,   353,
     352,   354,   354,   354,   355,   356,   358,   357,   360,   359,
     362,   361,   364,   363,   366,   365,   367,   367,   367,   368,
     368,   370,   369,   372,   371,   374,   373,   375,   375,   375,
     376,   376,   377,   378,   380,   379,   381,   381,   381,   382,
     382,   382,   383,   384,   386,   385,   388,   387,   389,   389,
     389,   390,   390,   390,   390,   390,   390,   391,   392,   393,
     395,   394,   396,   396,   397,   397,   397,   399,   398,   401,
     400,   402,   402,   402,   402,   403,   403,   405,   404,   407,
     406,   409,   408,   410,   410,   410,   411,   411,   411,   411,
     411,   411,   412,   413,   414,   415,   416,   417,   419,   418,
     420,   420,   421,   421,   421,   423,   422,   425,   424,   426,
     426,   426,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   427,   427,   427,   427,   427,   429,   428,   431,
     430,   433,   432,   435,   434,   437,   436,   438,   439,   440,
     442,   441,   443,   443,   443,   443,   444,   445,   447,   446,
     448,   448,   449,   449,   449,   451,   450,   452,   452,   452,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   455,   454,   457,   456,   458,   458,   459,   459,
     459,   461,   460,   463,   462,   464,   464,   465,   465,   465,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     467,   468,   469,   471,   470,   473,   472,   475,   474,   476,
     478,   477,   479,   481,   480,   482,   482,   483,   483,   483,
     485,   484,   487,   486,   488,   488,   489,   489,   489,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   491,
     493,   492,   494,   495,   496,   497,   498,   500,   499,   501,
     501,   502,   502,   502,   504,   503,   506,   505,   507,   507,
     507,   508,   508,   508,   508,   508,   508,   508,   510,   509,
     512,   511,   514,   513,   516,   515,   517,   517,   518,   518,
     518,   520,   519,   522,   521,   523,   523,   523,   524,   524,
     524,   524,   524,   524,   524,   524,   524,   524,   524,   526,
     525,   527,   529,   528,   530,   531,   533,   532,   534,   534,
     535,   535,   535,   537,   536,   539,   538,   540,   540,   541,
     541,   541,   542,   542,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   544,   543,   546,   545,   548,   547,   550,
     549,   552,   551,   554,   553,   556,   555,   558,   557,   559,
     559,   561,   560,   563,   562,   564,   564,   564,   566,   565,
     567,   567,   568,   568,   568,   569,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   569,   569,   569,   570,
     572,   571,   574,   573,   575,   577,   576,   578,   578,   578,
     579,   579,   579,   579,   579,   579,   579,   579,   579,   581,
     580,   582,   582,   582,   583,   585,   584,   586,   587,   588,
     590,   589,   591,   591,   591,   592,   592,   592,   592,   592,
     594,   593,   596,   595,   598,   597,   599,   599,   599,   600,
     600,   600,   600,   600,   600,   601,   603,   602,   604,   606,
     605,   608,   607,   610,   609,   611,   611,   611,   612,   612,
     612,   612,   612,   612,   612,   612,   612,   612,   612,   612,
     612,   612,   612,   612,   612,   612,   613,   615,   614,   617,
     616,   618,   620,   619,   621,   622,   624,   623,   625,   625,
     627,   626,   628,   629,   631,   630,   633,   632,   635,   634,
     637,   636,   639,   638,   641,   640,   642,   642,   642,   643,
     643,   645,   644,   646,   648,   647,   649,   649,   649,   651,
     650,   652,   652,   652,   653,   653,   653,   653,   653,   653,
     653,   654,   656,   655,   658,   657,   659,   659,   659,   661,
     660,   662,   662,   662,   663,   663,   663,   663,   663,   665,
     664,   666,   667,   668,   670,   669,   672,   671,   673,   673,
     673,   674,   674,   675
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     0,     6,     3,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     3
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
  "\"csv-format\"", "\"always-send\"", "\"never-send\"",
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
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
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
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@83", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@84", "sub_pool6", "$@85", "pool_params", "pool_param", "pool_entry",
  "$@86", "user_context", "$@87", "comment", "$@88", "pd_pools_list",
  "$@89", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@90", "sub_pd_pool", "$@91", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@92", "pd_prefix_len", "excluded_prefix",
  "$@93", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@94", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@95", "sub_reservation", "$@96", "reservation_params",
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
       0,   310,   310,   310,   311,   311,   312,   312,   313,   313,
     314,   314,   315,   315,   316,   316,   317,   317,   318,   318,
     319,   319,   320,   320,   321,   321,   322,   322,   323,   323,
     331,   332,   333,   334,   335,   336,   337,   340,   345,   345,
     356,   359,   360,   363,   368,   374,   379,   379,   386,   387,
     390,   394,   398,   404,   404,   411,   412,   415,   419,   423,
     433,   442,   442,   457,   457,   471,   474,   480,   480,   489,
     490,   491,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   567,
     567,   576,   582,   588,   594,   600,   606,   612,   618,   624,
     630,   636,   642,   648,   654,   660,   666,   672,   678,   678,
     687,   690,   693,   696,   699,   705,   705,   714,   714,   723,
     729,   735,   735,   744,   744,   753,   759,   765,   771,   771,
     780,   786,   786,   795,   795,   804,   810,   816,   822,   822,
     834,   834,   843,   844,   845,   850,   851,   852,   853,   854,
     855,   856,   857,   860,   860,   871,   877,   883,   889,   895,
     895,   908,   908,   921,   921,   932,   933,   936,   937,   938,
     943,   943,   953,   954,   955,   960,   961,   962,   963,   964,
     965,   966,   967,   968,   969,   970,   971,   972,   973,   974,
     975,   976,   977,   978,   979,   980,   981,   984,   984,   992,
     993,   994,   997,   997,  1006,  1006,  1015,  1015,  1024,  1030,
    1030,  1039,  1045,  1051,  1057,  1063,  1069,  1075,  1082,  1088,
    1088,  1096,  1097,  1098,  1101,  1107,  1113,  1113,  1122,  1122,
    1131,  1131,  1140,  1140,  1149,  1149,  1160,  1161,  1162,  1167,
    1168,  1171,  1171,  1190,  1190,  1208,  1208,  1219,  1220,  1221,
    1226,  1227,  1230,  1235,  1240,  1240,  1251,  1252,  1253,  1258,
    1259,  1260,  1263,  1268,  1275,  1275,  1288,  1288,  1301,  1302,
    1303,  1308,  1309,  1310,  1311,  1312,  1313,  1316,  1322,  1328,
    1334,  1334,  1345,  1346,  1349,  1350,  1351,  1356,  1356,  1366,
    1366,  1376,  1377,  1378,  1381,  1384,  1385,  1388,  1388,  1397,
    1397,  1406,  1406,  1418,  1419,  1420,  1425,  1426,  1427,  1428,
    1429,  1430,  1433,  1439,  1445,  1451,  1457,  1463,  1472,  1472,
    1486,  1487,  1490,  1491,  1492,  1501,  1501,  1527,  1527,  1538,
    1539,  1540,  1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,
    1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,  1562,  1563,
    1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,  1572,  1573,
    1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,  1582,  1583,
    1584,  1585,  1586,  1587,  1588,  1589,  1590,  1593,  1593,  1602,
    1602,  1611,  1611,  1620,  1620,  1629,  1629,  1640,  1646,  1652,
    1658,  1658,  1666,  1667,  1668,  1669,  1672,  1678,  1686,  1686,
    1698,  1699,  1703,  1704,  1705,  1710,  1710,  1718,  1719,  1720,
    1725,  1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,
    1735,  1736,  1737,  1738,  1739,  1740,  1741,  1742,  1743,  1744,
    1745,  1746,  1747,  1748,  1749,  1750,  1751,  1752,  1753,  1754,
    1755,  1756,  1757,  1758,  1759,  1760,  1761,  1762,  1763,  1764,
    1765,  1766,  1773,  1773,  1787,  1787,  1796,  1797,  1800,  1801,
    1802,  1809,  1809,  1824,  1824,  1838,  1839,  1842,  1843,  1844,
    1849,  1850,  1851,  1852,  1853,  1854,  1855,  1856,  1857,  1858,
    1861,  1863,  1869,  1871,  1871,  1880,  1880,  1889,  1889,  1898,
    1900,  1900,  1909,  1919,  1919,  1932,  1933,  1938,  1939,  1940,
    1947,  1947,  1959,  1959,  1971,  1972,  1977,  1978,  1979,  1986,
    1987,  1988,  1989,  1990,  1991,  1992,  1993,  1994,  1995,  1998,
    2000,  2000,  2009,  2011,  2013,  2019,  2025,  2034,  2034,  2047,
    2048,  2051,  2052,  2053,  2058,  2058,  2068,  2068,  2078,  2079,
    2080,  2085,  2086,  2087,  2088,  2089,  2090,  2091,  2094,  2094,
    2103,  2103,  2128,  2128,  2158,  2158,  2171,  2172,  2175,  2176,
    2177,  2182,  2182,  2194,  2194,  2206,  2207,  2208,  2213,  2214,
    2215,  2216,  2217,  2218,  2219,  2220,  2221,  2222,  2223,  2226,
    2226,  2235,  2241,  2241,  2250,  2256,  2265,  2265,  2276,  2277,
    2280,  2281,  2282,  2287,  2287,  2296,  2296,  2305,  2306,  2309,
    2310,  2311,  2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,
    2325,  2326,  2327,  2330,  2330,  2341,  2341,  2352,  2352,  2361,
    2361,  2370,  2370,  2379,  2379,  2388,  2388,  2402,  2402,  2413,
    2414,  2417,  2417,  2429,  2429,  2440,  2441,  2442,  2447,  2447,
    2457,  2458,  2461,  2462,  2463,  2468,  2469,  2470,  2471,  2472,
    2473,  2474,  2475,  2476,  2477,  2478,  2479,  2480,  2481,  2484,
    2486,  2486,  2495,  2495,  2504,  2513,  2513,  2526,  2527,  2528,
    2533,  2534,  2535,  2536,  2537,  2538,  2539,  2540,  2541,  2544,
    2544,  2552,  2553,  2554,  2557,  2563,  2563,  2572,  2578,  2586,
    2594,  2594,  2605,  2606,  2607,  2612,  2613,  2614,  2615,  2616,
    2619,  2619,  2628,  2628,  2640,  2640,  2653,  2654,  2655,  2660,
    2661,  2662,  2663,  2664,  2665,  2668,  2674,  2674,  2683,  2689,
    2689,  2699,  2699,  2712,  2712,  2722,  2723,  2724,  2729,  2730,
    2731,  2732,  2733,  2734,  2735,  2736,  2737,  2738,  2739,  2740,
    2741,  2742,  2743,  2744,  2745,  2746,  2749,  2756,  2756,  2765,
    2765,  2774,  2780,  2780,  2789,  2795,  2801,  2801,  2810,  2811,
    2814,  2814,  2824,  2831,  2838,  2838,  2847,  2847,  2857,  2857,
    2867,  2867,  2879,  2879,  2891,  2891,  2901,  2902,  2903,  2909,
    2910,  2913,  2913,  2924,  2932,  2932,  2945,  2946,  2947,  2953,
    2953,  2961,  2962,  2963,  2968,  2969,  2970,  2971,  2972,  2973,
    2974,  2977,  2983,  2983,  2992,  2992,  3003,  3004,  3005,  3010,
    3010,  3018,  3019,  3020,  3025,  3026,  3027,  3028,  3029,  3032,
    3032,  3041,  3047,  3053,  3059,  3059,  3068,  3068,  3079,  3080,
    3081,  3086,  3087,  3090
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
#line 6513 "dhcp6_parser.cc"

#line 3096 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
