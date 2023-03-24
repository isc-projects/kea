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
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 302 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 302 "dhcp6_parser.yy"
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
#line 311 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 312 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 313 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 314 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 315 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 316 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 317 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 318 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 319 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 320 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 321 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 322 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 323 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 324 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 332 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 333 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 334 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 335 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 336 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 337 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 338 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 341 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 346 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 351 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 357 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 364 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 369 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 375 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 380 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 383 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 391 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 395 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 399 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 405 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 407 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 416 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 420 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 424 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 434 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 443 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 448 "dhcp6_parser.yy"
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
#line 458 "dhcp6_parser.yy"
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
#line 467 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 475 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 481 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 485 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 492 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 140: // $@21: %empty
#line 569 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 141: // data_directory: "data-directory" $@21 ":" "constant string"
#line 572 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 142: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 578 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 143: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 584 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 144: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 590 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 145: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 596 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 146: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 602 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 147: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 608 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 148: // renew_timer: "renew-timer" ":" "integer"
#line 614 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 149: // rebind_timer: "rebind-timer" ":" "integer"
#line 620 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 150: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 626 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 151: // t1_percent: "t1-percent" ":" "floating point"
#line 632 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 152: // t2_percent: "t2-percent" ":" "floating point"
#line 638 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 153: // cache_threshold: "cache-threshold" ":" "floating point"
#line 644 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 154: // cache_max_age: "cache-max-age" ":" "integer"
#line 650 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 155: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 656 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 156: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 662 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 157: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 668 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 674 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 159: // $@22: %empty
#line 680 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 683 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-present"
#line 689 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "never"
#line 692 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "always"
#line 695 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "when-not-present"
#line 698 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "boolean"
#line 701 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 166: // $@23: %empty
#line 707 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 167: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 710 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 168: // $@24: %empty
#line 716 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 169: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 719 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 170: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 725 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 171: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 731 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 172: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 737 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1432 "dhcp6_parser.cc"
    break;

  case 173: // $@25: %empty
#line 743 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 174: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 746 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 175: // $@26: %empty
#line 752 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 176: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 755 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 177: // store_extended_info: "store-extended-info" ":" "boolean"
#line 761 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 178: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 767 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 179: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 773 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1500 "dhcp6_parser.cc"
    break;

  case 180: // $@27: %empty
#line 779 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 181: // server_tag: "server-tag" $@27 ":" "constant string"
#line 782 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 182: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 788 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 183: // $@28: %empty
#line 794 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1538 "dhcp6_parser.cc"
    break;

  case 184: // allocator: "allocator" $@28 ":" "constant string"
#line 797 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1548 "dhcp6_parser.cc"
    break;

  case 185: // $@29: %empty
#line 803 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1557 "dhcp6_parser.cc"
    break;

  case 186: // pd_allocator: "pd-allocator" $@29 ":" "constant string"
#line 806 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1567 "dhcp6_parser.cc"
    break;

  case 187: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 812 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 188: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 818 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 189: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 824 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 190: // $@30: %empty
#line 830 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 191: // interfaces_config: "interfaces-config" $@30 ":" "{" interfaces_config_params "}"
#line 836 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 192: // $@31: %empty
#line 842 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 193: // sub_interfaces6: "{" $@31 interfaces_config_params "}"
#line 846 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 196: // interfaces_config_params: interfaces_config_params ","
#line 853 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1646 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 868 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 206: // interfaces_list: "interfaces" $@32 ":" list_strings
#line 874 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 207: // re_detect: "re-detect" ":" "boolean"
#line 879 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 208: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 885 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 209: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 891 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 210: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 897 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1707 "dhcp6_parser.cc"
    break;

  case 211: // $@33: %empty
#line 903 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 212: // lease_database: "lease-database" $@33 ":" "{" database_map_params "}"
#line 909 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1730 "dhcp6_parser.cc"
    break;

  case 213: // $@34: %empty
#line 916 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1742 "dhcp6_parser.cc"
    break;

  case 214: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 922 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1753 "dhcp6_parser.cc"
    break;

  case 215: // $@35: %empty
#line 929 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 216: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 935 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1774 "dhcp6_parser.cc"
    break;

  case 221: // not_empty_database_list: not_empty_database_list ","
#line 946 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1782 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 951 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 223: // database: "{" $@36 database_map_params "}"
#line 955 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1802 "dhcp6_parser.cc"
    break;

  case 226: // database_map_params: database_map_params ","
#line 963 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1810 "dhcp6_parser.cc"
    break;

  case 249: // $@37: %empty
#line 992 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 250: // database_type: "type" $@37 ":" db_type
#line 995 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1828 "dhcp6_parser.cc"
    break;

  case 251: // db_type: "memfile"
#line 1000 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1834 "dhcp6_parser.cc"
    break;

  case 252: // db_type: "mysql"
#line 1001 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp6_parser.cc"
    break;

  case 253: // db_type: "postgresql"
#line 1002 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp6_parser.cc"
    break;

  case 254: // $@38: %empty
#line 1005 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 255: // user: "user" $@38 ":" "constant string"
#line 1008 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 256: // $@39: %empty
#line 1014 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 257: // password: "password" $@39 ":" "constant string"
#line 1017 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1884 "dhcp6_parser.cc"
    break;

  case 258: // $@40: %empty
#line 1023 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 259: // host: "host" $@40 ":" "constant string"
#line 1026 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1903 "dhcp6_parser.cc"
    break;

  case 260: // port: "port" ":" "integer"
#line 1032 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1913 "dhcp6_parser.cc"
    break;

  case 261: // $@41: %empty
#line 1038 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 262: // name: "name" $@41 ":" "constant string"
#line 1041 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1932 "dhcp6_parser.cc"
    break;

  case 263: // persist: "persist" ":" "boolean"
#line 1047 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 264: // lfc_interval: "lfc-interval" ":" "integer"
#line 1053 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 265: // readonly: "readonly" ":" "boolean"
#line 1059 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1962 "dhcp6_parser.cc"
    break;

  case 266: // connect_timeout: "connect-timeout" ":" "integer"
#line 1065 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 267: // read_timeout: "read-timeout" ":" "integer"
#line 1071 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 1982 "dhcp6_parser.cc"
    break;

  case 268: // write_timeout: "write-timeout" ":" "integer"
#line 1077 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 269: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1083 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 270: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1090 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 271: // $@42: %empty
#line 1096 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 272: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1099 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2030 "dhcp6_parser.cc"
    break;

  case 273: // on_fail_mode: "stop-retry-exit"
#line 1104 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2036 "dhcp6_parser.cc"
    break;

  case 274: // on_fail_mode: "serve-retry-exit"
#line 1105 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp6_parser.cc"
    break;

  case 275: // on_fail_mode: "serve-retry-continue"
#line 1106 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp6_parser.cc"
    break;

  case 276: // max_row_errors: "max-row-errors" ":" "integer"
#line 1109 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2058 "dhcp6_parser.cc"
    break;

  case 277: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1115 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2068 "dhcp6_parser.cc"
    break;

  case 278: // $@43: %empty
#line 1121 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 279: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1124 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 280: // $@44: %empty
#line 1130 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 281: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1133 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 282: // $@45: %empty
#line 1139 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 283: // key_file: "key-file" $@45 ":" "constant string"
#line 1142 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 284: // $@46: %empty
#line 1148 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 285: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1151 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc"
    break;

  case 286: // $@47: %empty
#line 1157 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2156 "dhcp6_parser.cc"
    break;

  case 287: // sanity_checks: "sanity-checks" $@47 ":" "{" sanity_checks_params "}"
#line 1163 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2165 "dhcp6_parser.cc"
    break;

  case 290: // sanity_checks_params: sanity_checks_params ","
#line 1170 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2173 "dhcp6_parser.cc"
    break;

  case 293: // $@48: %empty
#line 1179 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp6_parser.cc"
    break;

  case 294: // lease_checks: "lease-checks" $@48 ":" "constant string"
#line 1182 "dhcp6_parser.yy"
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
#line 2202 "dhcp6_parser.cc"
    break;

  case 295: // $@49: %empty
#line 1198 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 296: // extended_info_checks: "extended-info-checks" $@49 ":" "constant string"
#line 1201 "dhcp6_parser.yy"
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
#line 2230 "dhcp6_parser.cc"
    break;

  case 297: // $@50: %empty
#line 1216 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2242 "dhcp6_parser.cc"
    break;

  case 298: // mac_sources: "mac-sources" $@50 ":" "[" mac_sources_list "]"
#line 1222 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc"
    break;

  case 301: // mac_sources_list: mac_sources_list ","
#line 1229 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2259 "dhcp6_parser.cc"
    break;

  case 304: // duid_id: "duid"
#line 1238 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2268 "dhcp6_parser.cc"
    break;

  case 305: // string_id: "constant string"
#line 1243 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2277 "dhcp6_parser.cc"
    break;

  case 306: // $@51: %empty
#line 1248 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2289 "dhcp6_parser.cc"
    break;

  case 307: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1254 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2298 "dhcp6_parser.cc"
    break;

  case 310: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1261 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2306 "dhcp6_parser.cc"
    break;

  case 314: // hw_address_id: "hw-address"
#line 1271 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2315 "dhcp6_parser.cc"
    break;

  case 315: // flex_id: "flex-id"
#line 1276 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 316: // $@52: %empty
#line 1283 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 317: // relay_supplied_options: "relay-supplied-options" $@52 ":" "[" list_content "]"
#line 1289 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2345 "dhcp6_parser.cc"
    break;

  case 318: // $@53: %empty
#line 1296 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2357 "dhcp6_parser.cc"
    break;

  case 319: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1302 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2368 "dhcp6_parser.cc"
    break;

  case 322: // multi_threading_params: multi_threading_params ","
#line 1311 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2376 "dhcp6_parser.cc"
    break;

  case 329: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1324 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2386 "dhcp6_parser.cc"
    break;

  case 330: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1330 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2396 "dhcp6_parser.cc"
    break;

  case 331: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1336 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2406 "dhcp6_parser.cc"
    break;

  case 332: // $@54: %empty
#line 1342 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 333: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1348 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 338: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1359 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2435 "dhcp6_parser.cc"
    break;

  case 339: // $@55: %empty
#line 1364 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2445 "dhcp6_parser.cc"
    break;

  case 340: // hooks_library: "{" $@55 hooks_params "}"
#line 1368 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2455 "dhcp6_parser.cc"
    break;

  case 341: // $@56: %empty
#line 1374 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 342: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1378 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 345: // hooks_params: hooks_params ","
#line 1386 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2483 "dhcp6_parser.cc"
    break;

  case 349: // $@57: %empty
#line 1396 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp6_parser.cc"
    break;

  case 350: // library: "library" $@57 ":" "constant string"
#line 1399 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2502 "dhcp6_parser.cc"
    break;

  case 351: // $@58: %empty
#line 1405 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp6_parser.cc"
    break;

  case 352: // parameters: "parameters" $@58 ":" map_value
#line 1408 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2520 "dhcp6_parser.cc"
    break;

  case 353: // $@59: %empty
#line 1414 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 354: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1420 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2542 "dhcp6_parser.cc"
    break;

  case 357: // expired_leases_params: expired_leases_params ","
#line 1428 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2550 "dhcp6_parser.cc"
    break;

  case 364: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1441 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 365: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1447 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 366: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1453 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 367: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1459 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 368: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1465 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 369: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1471 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 370: // $@60: %empty
#line 1480 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2622 "dhcp6_parser.cc"
    break;

  case 371: // subnet6_list: "subnet6" $@60 ":" "[" subnet6_list_content "]"
#line 1486 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2631 "dhcp6_parser.cc"
    break;

  case 376: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1500 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2639 "dhcp6_parser.cc"
    break;

  case 377: // $@61: %empty
#line 1509 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2649 "dhcp6_parser.cc"
    break;

  case 378: // subnet6: "{" $@61 subnet6_params "}"
#line 1513 "dhcp6_parser.yy"
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
#line 2675 "dhcp6_parser.cc"
    break;

  case 379: // $@62: %empty
#line 1535 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 380: // sub_subnet6: "{" $@62 subnet6_params "}"
#line 1539 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2695 "dhcp6_parser.cc"
    break;

  case 383: // subnet6_params: subnet6_params ","
#line 1548 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2703 "dhcp6_parser.cc"
    break;

  case 430: // $@63: %empty
#line 1602 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 431: // subnet: "subnet" $@63 ":" "constant string"
#line 1605 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 432: // $@64: %empty
#line 1611 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp6_parser.cc"
    break;

  case 433: // interface: "interface" $@64 ":" "constant string"
#line 1614 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 434: // $@65: %empty
#line 1620 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp6_parser.cc"
    break;

  case 435: // interface_id: "interface-id" $@65 ":" "constant string"
#line 1623 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2760 "dhcp6_parser.cc"
    break;

  case 436: // $@66: %empty
#line 1629 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2769 "dhcp6_parser.cc"
    break;

  case 437: // client_class: "client-class" $@66 ":" "constant string"
#line 1632 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2779 "dhcp6_parser.cc"
    break;

  case 438: // $@67: %empty
#line 1638 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp6_parser.cc"
    break;

  case 439: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1644 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2800 "dhcp6_parser.cc"
    break;

  case 440: // reservations_global: "reservations-global" ":" "boolean"
#line 1649 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2810 "dhcp6_parser.cc"
    break;

  case 441: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1655 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2820 "dhcp6_parser.cc"
    break;

  case 442: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1661 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2830 "dhcp6_parser.cc"
    break;

  case 443: // $@68: %empty
#line 1667 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2839 "dhcp6_parser.cc"
    break;

  case 444: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1670 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2848 "dhcp6_parser.cc"
    break;

  case 445: // hr_mode: "disabled"
#line 1675 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2854 "dhcp6_parser.cc"
    break;

  case 446: // hr_mode: "out-of-pool"
#line 1676 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2860 "dhcp6_parser.cc"
    break;

  case 447: // hr_mode: "global"
#line 1677 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2866 "dhcp6_parser.cc"
    break;

  case 448: // hr_mode: "all"
#line 1678 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2872 "dhcp6_parser.cc"
    break;

  case 449: // id: "id" ":" "integer"
#line 1681 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 450: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1687 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2892 "dhcp6_parser.cc"
    break;

  case 451: // $@69: %empty
#line 1695 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 452: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1701 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 457: // shared_networks_list: shared_networks_list ","
#line 1714 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2921 "dhcp6_parser.cc"
    break;

  case 458: // $@70: %empty
#line 1719 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2931 "dhcp6_parser.cc"
    break;

  case 459: // shared_network: "{" $@70 shared_network_params "}"
#line 1723 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2939 "dhcp6_parser.cc"
    break;

  case 462: // shared_network_params: shared_network_params ","
#line 1729 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2947 "dhcp6_parser.cc"
    break;

  case 506: // $@71: %empty
#line 1783 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2959 "dhcp6_parser.cc"
    break;

  case 507: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1789 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2968 "dhcp6_parser.cc"
    break;

  case 508: // $@72: %empty
#line 1797 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2977 "dhcp6_parser.cc"
    break;

  case 509: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1800 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 514: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1812 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2993 "dhcp6_parser.cc"
    break;

  case 515: // $@73: %empty
#line 1819 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3003 "dhcp6_parser.cc"
    break;

  case 516: // option_def_entry: "{" $@73 option_def_params "}"
#line 1823 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 517: // $@74: %empty
#line 1834 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 518: // sub_option_def: "{" $@74 option_def_params "}"
#line 1838 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 523: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1854 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3045 "dhcp6_parser.cc"
    break;

  case 535: // code: "code" ":" "integer"
#line 1873 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 537: // $@75: %empty
#line 1881 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 538: // option_def_type: "type" $@75 ":" "constant string"
#line 1884 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3074 "dhcp6_parser.cc"
    break;

  case 539: // $@76: %empty
#line 1890 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 540: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1893 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3093 "dhcp6_parser.cc"
    break;

  case 541: // $@77: %empty
#line 1899 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3102 "dhcp6_parser.cc"
    break;

  case 542: // space: "space" $@77 ":" "constant string"
#line 1902 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 544: // $@78: %empty
#line 1910 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 545: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1913 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 546: // option_def_array: "array" ":" "boolean"
#line 1919 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 547: // $@79: %empty
#line 1929 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3153 "dhcp6_parser.cc"
    break;

  case 548: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1935 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3162 "dhcp6_parser.cc"
    break;

  case 553: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1950 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3170 "dhcp6_parser.cc"
    break;

  case 554: // $@80: %empty
#line 1957 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3180 "dhcp6_parser.cc"
    break;

  case 555: // option_data_entry: "{" $@80 option_data_params "}"
#line 1961 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 556: // $@81: %empty
#line 1969 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3199 "dhcp6_parser.cc"
    break;

  case 557: // sub_option_data: "{" $@81 option_data_params "}"
#line 1973 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 562: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1989 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3216 "dhcp6_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2010 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3225 "dhcp6_parser.cc"
    break;

  case 575: // option_data_data: "data" $@82 ":" "constant string"
#line 2013 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3235 "dhcp6_parser.cc"
    break;

  case 578: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2023 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3245 "dhcp6_parser.cc"
    break;

  case 579: // option_data_always_send: "always-send" ":" "boolean"
#line 2029 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3255 "dhcp6_parser.cc"
    break;

  case 580: // option_data_never_send: "never-send" ":" "boolean"
#line 2035 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3265 "dhcp6_parser.cc"
    break;

  case 581: // $@83: %empty
#line 2044 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3277 "dhcp6_parser.cc"
    break;

  case 582: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2050 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3286 "dhcp6_parser.cc"
    break;

  case 587: // not_empty_pools_list: not_empty_pools_list ","
#line 2063 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3294 "dhcp6_parser.cc"
    break;

  case 588: // $@84: %empty
#line 2068 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 589: // pool_list_entry: "{" $@84 pool_params "}"
#line 2072 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 590: // $@85: %empty
#line 2078 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3324 "dhcp6_parser.cc"
    break;

  case 591: // sub_pool6: "{" $@85 pool_params "}"
#line 2082 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3334 "dhcp6_parser.cc"
    break;

  case 594: // pool_params: pool_params ","
#line 2090 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3342 "dhcp6_parser.cc"
    break;

  case 602: // $@86: %empty
#line 2104 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3351 "dhcp6_parser.cc"
    break;

  case 603: // pool_entry: "pool" $@86 ":" "constant string"
#line 2107 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3361 "dhcp6_parser.cc"
    break;

  case 604: // $@87: %empty
#line 2113 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3369 "dhcp6_parser.cc"
    break;

  case 605: // user_context: "user-context" $@87 ":" map_value
#line 2115 "dhcp6_parser.yy"
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
#line 3396 "dhcp6_parser.cc"
    break;

  case 606: // $@88: %empty
#line 2138 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 607: // comment: "comment" $@88 ":" "constant string"
#line 2140 "dhcp6_parser.yy"
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
#line 3433 "dhcp6_parser.cc"
    break;

  case 608: // $@89: %empty
#line 2168 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 609: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2174 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3454 "dhcp6_parser.cc"
    break;

  case 614: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2187 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3462 "dhcp6_parser.cc"
    break;

  case 615: // $@90: %empty
#line 2192 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3472 "dhcp6_parser.cc"
    break;

  case 616: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2196 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 617: // $@91: %empty
#line 2204 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 618: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2208 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 621: // pd_pool_params: pd_pool_params ","
#line 2218 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3514 "dhcp6_parser.cc"
    break;

  case 633: // $@92: %empty
#line 2236 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp6_parser.cc"
    break;

  case 634: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2239 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3533 "dhcp6_parser.cc"
    break;

  case 635: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2245 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3543 "dhcp6_parser.cc"
    break;

  case 636: // $@93: %empty
#line 2251 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 637: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2254 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 638: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2260 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3572 "dhcp6_parser.cc"
    break;

  case 639: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2266 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3582 "dhcp6_parser.cc"
    break;

  case 640: // $@94: %empty
#line 2275 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3594 "dhcp6_parser.cc"
    break;

  case 641: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2281 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3603 "dhcp6_parser.cc"
    break;

  case 646: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2292 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3611 "dhcp6_parser.cc"
    break;

  case 647: // $@95: %empty
#line 2297 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 648: // reservation: "{" $@95 reservation_params "}"
#line 2301 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 649: // $@96: %empty
#line 2306 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3640 "dhcp6_parser.cc"
    break;

  case 650: // sub_reservation: "{" $@96 reservation_params "}"
#line 2310 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 655: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2321 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3657 "dhcp6_parser.cc"
    break;

  case 667: // $@97: %empty
#line 2340 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3669 "dhcp6_parser.cc"
    break;

  case 668: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2346 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3678 "dhcp6_parser.cc"
    break;

  case 669: // $@98: %empty
#line 2351 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 670: // prefixes: "prefixes" $@98 ":" list_strings
#line 2357 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 671: // $@99: %empty
#line 2362 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 672: // duid: "duid" $@99 ":" "constant string"
#line 2365 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3718 "dhcp6_parser.cc"
    break;

  case 673: // $@100: %empty
#line 2371 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 674: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2374 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 675: // $@101: %empty
#line 2380 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 676: // hostname: "hostname" $@101 ":" "constant string"
#line 2383 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 677: // $@102: %empty
#line 2389 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3765 "dhcp6_parser.cc"
    break;

  case 678: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2392 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 679: // $@103: %empty
#line 2398 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 680: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2404 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3796 "dhcp6_parser.cc"
    break;

  case 681: // $@104: %empty
#line 2412 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 682: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2418 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 685: // $@105: %empty
#line 2427 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3826 "dhcp6_parser.cc"
    break;

  case 686: // ip_address: "ip-address" $@105 ":" "constant string"
#line 2430 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 687: // $@106: %empty
#line 2439 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 688: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2445 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3857 "dhcp6_parser.cc"
    break;

  case 691: // client_classes_list: client_classes_list ","
#line 2452 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3865 "dhcp6_parser.cc"
    break;

  case 692: // $@107: %empty
#line 2457 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3875 "dhcp6_parser.cc"
    break;

  case 693: // client_class_entry: "{" $@107 client_class_params "}"
#line 2461 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3885 "dhcp6_parser.cc"
    break;

  case 698: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2473 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3893 "dhcp6_parser.cc"
    break;

  case 714: // $@108: %empty
#line 2496 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 715: // client_class_test: "test" $@108 ":" "constant string"
#line 2499 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3912 "dhcp6_parser.cc"
    break;

  case 716: // $@109: %empty
#line 2505 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 717: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2508 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3931 "dhcp6_parser.cc"
    break;

  case 718: // only_if_required: "only-if-required" ":" "boolean"
#line 2514 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3941 "dhcp6_parser.cc"
    break;

  case 719: // $@110: %empty
#line 2523 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 720: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2529 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3964 "dhcp6_parser.cc"
    break;

  case 723: // server_id_params: server_id_params ","
#line 2538 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3972 "dhcp6_parser.cc"
    break;

  case 733: // $@111: %empty
#line 2554 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 734: // server_id_type: "type" $@111 ":" duid_type
#line 2557 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 735: // duid_type: "LLT"
#line 2562 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3996 "dhcp6_parser.cc"
    break;

  case 736: // duid_type: "EN"
#line 2563 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4002 "dhcp6_parser.cc"
    break;

  case 737: // duid_type: "LL"
#line 2564 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4008 "dhcp6_parser.cc"
    break;

  case 738: // htype: "htype" ":" "integer"
#line 2567 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4018 "dhcp6_parser.cc"
    break;

  case 739: // $@112: %empty
#line 2573 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 740: // identifier: "identifier" $@112 ":" "constant string"
#line 2576 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4037 "dhcp6_parser.cc"
    break;

  case 741: // time: "time" ":" "integer"
#line 2582 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4047 "dhcp6_parser.cc"
    break;

  case 742: // enterprise_id: "enterprise-id" ":" "integer"
#line 2588 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4057 "dhcp6_parser.cc"
    break;

  case 743: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2596 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4067 "dhcp6_parser.cc"
    break;

  case 744: // $@113: %empty
#line 2604 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4079 "dhcp6_parser.cc"
    break;

  case 745: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2610 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4088 "dhcp6_parser.cc"
    break;

  case 748: // control_socket_params: control_socket_params ","
#line 2617 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4096 "dhcp6_parser.cc"
    break;

  case 754: // $@114: %empty
#line 2629 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4105 "dhcp6_parser.cc"
    break;

  case 755: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2632 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4115 "dhcp6_parser.cc"
    break;

  case 756: // $@115: %empty
#line 2638 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4124 "dhcp6_parser.cc"
    break;

  case 757: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2641 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4134 "dhcp6_parser.cc"
    break;

  case 758: // $@116: %empty
#line 2650 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4146 "dhcp6_parser.cc"
    break;

  case 759: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2656 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 762: // queue_control_params: queue_control_params ","
#line 2665 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4165 "dhcp6_parser.cc"
    break;

  case 769: // enable_queue: "enable-queue" ":" "boolean"
#line 2678 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4175 "dhcp6_parser.cc"
    break;

  case 770: // $@117: %empty
#line 2684 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4184 "dhcp6_parser.cc"
    break;

  case 771: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2687 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4194 "dhcp6_parser.cc"
    break;

  case 772: // capacity: "capacity" ":" "integer"
#line 2693 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4204 "dhcp6_parser.cc"
    break;

  case 773: // $@118: %empty
#line 2699 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4213 "dhcp6_parser.cc"
    break;

  case 774: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2702 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4222 "dhcp6_parser.cc"
    break;

  case 775: // $@119: %empty
#line 2709 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4234 "dhcp6_parser.cc"
    break;

  case 776: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2715 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 777: // $@120: %empty
#line 2722 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 778: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2726 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 781: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2734 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4273 "dhcp6_parser.cc"
    break;

  case 800: // enable_updates: "enable-updates" ":" "boolean"
#line 2759 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 801: // $@121: %empty
#line 2766 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4292 "dhcp6_parser.cc"
    break;

  case 802: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2769 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 803: // $@122: %empty
#line 2775 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4311 "dhcp6_parser.cc"
    break;

  case 804: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2778 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4321 "dhcp6_parser.cc"
    break;

  case 805: // server_port: "server-port" ":" "integer"
#line 2784 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4331 "dhcp6_parser.cc"
    break;

  case 806: // $@123: %empty
#line 2790 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4340 "dhcp6_parser.cc"
    break;

  case 807: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2793 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4350 "dhcp6_parser.cc"
    break;

  case 808: // sender_port: "sender-port" ":" "integer"
#line 2799 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4360 "dhcp6_parser.cc"
    break;

  case 809: // max_queue_size: "max-queue-size" ":" "integer"
#line 2805 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4370 "dhcp6_parser.cc"
    break;

  case 810: // $@124: %empty
#line 2811 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4379 "dhcp6_parser.cc"
    break;

  case 811: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2814 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4388 "dhcp6_parser.cc"
    break;

  case 812: // ncr_protocol_value: "UDP"
#line 2820 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4394 "dhcp6_parser.cc"
    break;

  case 813: // ncr_protocol_value: "TCP"
#line 2821 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4400 "dhcp6_parser.cc"
    break;

  case 814: // $@125: %empty
#line 2824 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 815: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2827 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4419 "dhcp6_parser.cc"
    break;

  case 816: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2834 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4429 "dhcp6_parser.cc"
    break;

  case 817: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2841 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4439 "dhcp6_parser.cc"
    break;

  case 818: // $@126: %empty
#line 2848 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4448 "dhcp6_parser.cc"
    break;

  case 819: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2851 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4457 "dhcp6_parser.cc"
    break;

  case 820: // $@127: %empty
#line 2857 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4466 "dhcp6_parser.cc"
    break;

  case 821: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2860 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4476 "dhcp6_parser.cc"
    break;

  case 822: // $@128: %empty
#line 2867 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4485 "dhcp6_parser.cc"
    break;

  case 823: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2870 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4495 "dhcp6_parser.cc"
    break;

  case 824: // $@129: %empty
#line 2877 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 825: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2880 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4514 "dhcp6_parser.cc"
    break;

  case 826: // $@130: %empty
#line 2889 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4526 "dhcp6_parser.cc"
    break;

  case 827: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2895 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4536 "dhcp6_parser.cc"
    break;

  case 828: // $@131: %empty
#line 2901 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4546 "dhcp6_parser.cc"
    break;

  case 829: // sub_config_control: "{" $@131 config_control_params "}"
#line 2905 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4555 "dhcp6_parser.cc"
    break;

  case 832: // config_control_params: config_control_params ","
#line 2913 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4563 "dhcp6_parser.cc"
    break;

  case 835: // $@132: %empty
#line 2923 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 836: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2929 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4584 "dhcp6_parser.cc"
    break;

  case 837: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2934 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 838: // $@133: %empty
#line 2942 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4606 "dhcp6_parser.cc"
    break;

  case 839: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2948 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4615 "dhcp6_parser.cc"
    break;

  case 842: // loggers_entries: loggers_entries ","
#line 2957 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4623 "dhcp6_parser.cc"
    break;

  case 843: // $@134: %empty
#line 2963 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4633 "dhcp6_parser.cc"
    break;

  case 844: // logger_entry: "{" $@134 logger_params "}"
#line 2967 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4641 "dhcp6_parser.cc"
    break;

  case 847: // logger_params: logger_params ","
#line 2973 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4649 "dhcp6_parser.cc"
    break;

  case 855: // debuglevel: "debuglevel" ":" "integer"
#line 2987 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4659 "dhcp6_parser.cc"
    break;

  case 856: // $@135: %empty
#line 2993 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4668 "dhcp6_parser.cc"
    break;

  case 857: // severity: "severity" $@135 ":" "constant string"
#line 2996 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4678 "dhcp6_parser.cc"
    break;

  case 858: // $@136: %empty
#line 3002 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4690 "dhcp6_parser.cc"
    break;

  case 859: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 3008 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4699 "dhcp6_parser.cc"
    break;

  case 862: // output_options_list_content: output_options_list_content ","
#line 3015 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4707 "dhcp6_parser.cc"
    break;

  case 863: // $@137: %empty
#line 3020 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 864: // output_entry: "{" $@137 output_params_list "}"
#line 3024 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4725 "dhcp6_parser.cc"
    break;

  case 867: // output_params_list: output_params_list ","
#line 3030 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4733 "dhcp6_parser.cc"
    break;

  case 873: // $@138: %empty
#line 3042 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4742 "dhcp6_parser.cc"
    break;

  case 874: // output: "output" $@138 ":" "constant string"
#line 3045 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4752 "dhcp6_parser.cc"
    break;

  case 875: // flush: "flush" ":" "boolean"
#line 3051 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4762 "dhcp6_parser.cc"
    break;

  case 876: // maxsize: "maxsize" ":" "integer"
#line 3057 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4772 "dhcp6_parser.cc"
    break;

  case 877: // maxver: "maxver" ":" "integer"
#line 3063 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4782 "dhcp6_parser.cc"
    break;

  case 878: // $@139: %empty
#line 3069 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4791 "dhcp6_parser.cc"
    break;

  case 879: // pattern: "pattern" $@139 ":" "constant string"
#line 3072 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4801 "dhcp6_parser.cc"
    break;

  case 880: // $@140: %empty
#line 3078 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4813 "dhcp6_parser.cc"
    break;

  case 881: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3084 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4822 "dhcp6_parser.cc"
    break;

  case 884: // compatibility_params: compatibility_params ","
#line 3091 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4830 "dhcp6_parser.cc"
    break;

  case 887: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3100 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4840 "dhcp6_parser.cc"
    break;


#line 4844 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1028;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     486, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,    37,    29,    38,    73,    76,
     108,   118,   130,   150,   152,   172,   191,   192,   287,   295,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,    29,  -142,
     275,   163,    78,   696,   211,   -36,    70,   280,   107,   262,
     -90,   471,    72, -1028,   316,   337,   355,   352,   358, -1028,
     113, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   377,   379,
     385,   392,   394,   402,   412,   413,   433,   436,   437,   438,
     439,   440, -1028,   441,   442,   443,   444,   446, -1028, -1028,
   -1028,   449,   450,   451,   453, -1028, -1028, -1028,   454, -1028,
   -1028, -1028, -1028, -1028, -1028,   455,   456,   457, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028,   458, -1028, -1028,
   -1028, -1028, -1028, -1028,   459,   460,   461, -1028, -1028,   462,
   -1028,   124, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   465,   466,   468,   469, -1028,   131, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
     473,   476, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028,   135, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   143, -1028,
   -1028, -1028, -1028, -1028,   479, -1028,   480,   481, -1028, -1028,
   -1028, -1028, -1028, -1028,   162, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028,   354,   411, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028,   478, -1028, -1028,   483, -1028, -1028, -1028,   487,
   -1028, -1028,   484,   490, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028,   491,   492,   496,
   -1028, -1028, -1028, -1028,   493,   499, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   168,
   -1028, -1028, -1028,   501, -1028, -1028,   502, -1028,   503,   507,
   -1028, -1028,   510,   513, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   174, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   514,
     189, -1028, -1028, -1028, -1028,    29,    29, -1028,   284,   515,
   -1028, -1028,   516,   517,   518,   521,   524,   526,   274,   311,
     312,   318,   320,   321,   323,   325,   314,   327,   331,   334,
     340,   341,   529,   342,   343,   324,   344,   356,   543,   547,
     560,   357,   359,   350,   360,   561,   572,   573,   367,   584,
     585,   587,   588,   589,   590,   375,   376,   378,   595,   599,
     600,   601,   603,   605,   606,   607,   608,   395,   613,   618,
     619,   621,   622,   623,   407,   409,   414,   628,   629, -1028,
     163, -1028,   630,   416,   417,   434,   435,    78, -1028,   649,
     652,   653,   654,   655,   445,   447,   658,   659,   660,   696,
   -1028,   662,   211, -1028,   663,   448,   666,   452,   463,   -36,
   -1028,   669,   671,   672,   673,   674,   675,   676, -1028,    70,
   -1028,   677,   678,   464,   682,   683,   684,   467, -1028,   107,
     701,   485,   494,   497, -1028,   262,   702,   704,   -37, -1028,
     504,   708,   710,   495,   714,   505,   508,   723,   725,   511,
     512,   726,   728,   731,   732,   471, -1028,   733,   519,    72,
   -1028, -1028, -1028,   734,   735,   522,   736,   737,   752,   753,
     756, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   554, -1028, -1028, -1028, -1028,
   -1028,  -129,   555,   557, -1028, -1028, -1028, -1028,   757,   772,
     773, -1028,   566,   567,   774,   782,   574,   133, -1028, -1028,
   -1028,   786,   789,   791,   788,   792,   801,   802,   806,   807,
   -1028,   808,   809,   810,   811,   602,   604, -1028, -1028, -1028,
     803,   812, -1028,   804, -1028, -1028, -1028, -1028, -1028,   817,
     821,   609,   610,   611, -1028, -1028,   804,   612,   820, -1028,
     614, -1028,   615, -1028,   616, -1028, -1028, -1028,   804,   804,
     804,   617,   620,   634,   635, -1028,   636,   637, -1028,   656,
     657,   661, -1028, -1028,   664, -1028, -1028, -1028, -1028,   665,
     782, -1028, -1028,   668,   670, -1028,   681, -1028, -1028,   -38,
     556, -1028, -1028,  -129,   688,   689,   690, -1028,   832, -1028,
   -1028,    29,   163, -1028,    72,    78,   339,   339,   831, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   861,   864,
     865, -1028, -1028,   866, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028,   -97,    29,    34,   137,   867,   870,   871,   278,
     109,   -51,   -63,   -55,   471, -1028, -1028,   872,   -91, -1028,
   -1028,   881,   883, -1028, -1028, -1028, -1028, -1028,   -48, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   831, -1028,
     244,   285,   288, -1028, -1028, -1028, -1028,   887,   890,   893,
     897,   898,   899,   906,   907,   908,   909, -1028,   912, -1028,
   -1028, -1028, -1028, -1028,   292, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028,   300, -1028,   911,
     916, -1028, -1028,   914,   918, -1028, -1028,   917,   919, -1028,
   -1028,   921,   922, -1028, -1028,   923,   925, -1028, -1028, -1028,
     120, -1028, -1028, -1028,   924, -1028, -1028, -1028,   185, -1028,
   -1028, -1028, -1028, -1028,   302, -1028, -1028, -1028, -1028,   254,
   -1028, -1028,   926,   928, -1028, -1028,   927,   931, -1028,   920,
     932,   933,   934,   935,   936,   313, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   937,   938,   939, -1028, -1028,
   -1028, -1028,   315, -1028, -1028, -1028, -1028, -1028, -1028,   940,
     941,   942, -1028,   322, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   326, -1028, -1028, -1028,   943,
   -1028,   944, -1028, -1028, -1028,   329, -1028, -1028, -1028, -1028,
   -1028,   330, -1028,   281, -1028,   945, -1028,   333, -1028, -1028,
     716, -1028,   946,   947, -1028, -1028,   948,   950, -1028, -1028,
   -1028,   949, -1028,   952, -1028, -1028, -1028,   951,   955,   956,
     957,   742,   729,   743,   744,   745,   747,   748,   749,   750,
     751,   960,   754,   969,   972,   973,   978,   339, -1028, -1028,
     339, -1028,   831,   696, -1028,   861,   107, -1028,   864,   262,
   -1028,   865,   790, -1028,   866,   -97, -1028, -1028,    34, -1028,
     980,   981,   137, -1028,   349,   867, -1028,    70, -1028,   870,
     -90, -1028,   871,   768,   771,   775,   777,   778,   785,   278,
   -1028,   998,  1004,   793,   797,   799,   109, -1028,   805,   814,
     816,   -51, -1028,  1007,  1024,   -63, -1028,   818,  1025,   828,
    1028,   -55, -1028, -1028,   196,   872, -1028,   829,   -91, -1028,
   -1028,  1044,   953,   211, -1028,   881,   -36, -1028,   883,  1051,
   -1028, -1028,   181,   846,   849,   853, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028,   231, -1028,   854,   858,
     860,   888, -1028,   387, -1028,   389, -1028,  1094, -1028,  1122,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
     404, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   929,
     930, -1028, -1028, -1028,  1131, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028,  1128,  1136, -1028, -1028,
   -1028, -1028, -1028, -1028,  1133, -1028,   410, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   200,   954, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   958,   959, -1028, -1028,   961,
   -1028,    29, -1028, -1028,  1138, -1028, -1028, -1028, -1028, -1028,
     423, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   962,
     424, -1028,   430, -1028,   963, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028,   790, -1028, -1028, -1028,  1139,  1140,
     964, -1028,   349, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028,  1141,   965,  1142,   196, -1028, -1028,
   -1028, -1028, -1028, -1028,   968,   970, -1028, -1028,  1145, -1028,
     971, -1028, -1028, -1028,  1144, -1028, -1028,   306, -1028,   209,
    1144, -1028, -1028,  1143,  1148,  1149, -1028,   431, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,  1150,   966,   974,   975,  1151,
     209, -1028,   977, -1028, -1028, -1028,   979, -1028, -1028, -1028
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   192,     9,   379,    11,
     590,    13,   617,    15,   649,    17,   508,    19,   517,    21,
     556,    23,   341,    25,   777,    27,   828,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   651,     0,   519,   558,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   140,   826,   190,   211,   213,   215,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,     0,     0,     0,     0,     0,   159,   166,
     168,     0,     0,     0,     0,   370,   506,   547,     0,   183,
     185,   451,   604,   606,   443,     0,     0,     0,   297,   316,
     306,   286,   687,   640,   332,   353,   719,     0,   318,   744,
     758,   775,   173,   175,     0,     0,     0,   838,   880,     0,
     139,     0,    69,    72,    73,    74,    75,    76,    77,    78,
      79,    80,   111,   112,   113,   114,   115,    81,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   117,   118,   128,
     129,   130,   106,   136,   137,   138,   132,   133,   134,    84,
      85,    86,    87,   103,    88,    90,    89,   131,    94,    95,
      82,   108,   109,   110,   107,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   116,   135,
     205,     0,     0,     0,     0,   204,     0,   194,   197,   198,
     199,   200,   201,   202,   203,   581,   608,   430,   432,   434,
       0,     0,   438,   436,   681,   429,   384,   385,   386,   387,
     388,   389,   390,   391,   410,   411,   412,   413,   414,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   415,   416,
     426,   427,   428,     0,   381,   395,   396,   397,   400,   401,
     404,   405,   406,   403,   398,   399,   392,   393,   408,   409,
     394,   402,   407,   602,   601,   597,   598,   596,     0,   592,
     595,   599,   600,   633,     0,   636,     0,     0,   632,   626,
     627,   625,   630,   631,     0,   619,   622,   623,   628,   629,
     624,   679,   667,   669,   671,   673,   675,   677,   666,   663,
     664,   665,     0,   652,   653,   658,   659,   656,   660,   661,
     662,   657,     0,   537,   261,     0,   541,   539,   544,     0,
     533,   534,     0,   520,   521,   524,   536,   525,   526,   527,
     543,   528,   529,   530,   531,   532,   574,     0,     0,     0,
     572,   573,   576,   577,     0,   559,   560,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   349,   351,   346,     0,
     343,   347,   348,     0,   801,   803,     0,   806,     0,     0,
     810,   814,     0,     0,   818,   820,   822,   824,   799,   797,
     798,     0,   779,   782,   794,   783,   784,   785,   786,   787,
     788,   789,   790,   791,   792,   793,   795,   796,   835,     0,
       0,   830,   833,   834,    47,    52,     0,    39,    45,     0,
      66,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      71,    68,     0,     0,     0,     0,     0,   196,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   383,
     380,     0,   594,   591,     0,     0,     0,     0,     0,   621,
     618,     0,     0,     0,     0,     0,     0,     0,   650,   655,
     509,     0,     0,     0,     0,     0,     0,     0,   518,   523,
       0,     0,     0,     0,   557,   562,     0,     0,   345,   342,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   781,   778,     0,     0,   832,
     829,    51,    43,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,     0,   178,   179,   156,   157,
     158,     0,     0,     0,   170,   171,   172,   177,     0,     0,
       0,   182,     0,     0,     0,     0,     0,     0,   440,   441,
     442,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     743,     0,     0,     0,     0,     0,     0,   187,   188,   189,
       0,     0,    70,     0,   207,   208,   209,   210,   195,     0,
       0,     0,     0,     0,   449,   450,     0,     0,     0,   382,
       0,   593,     0,   635,     0,   638,   639,   620,     0,     0,
       0,     0,     0,     0,     0,   654,     0,     0,   535,     0,
       0,     0,   546,   522,     0,   578,   579,   580,   561,     0,
       0,   344,   800,     0,     0,   805,     0,   808,   809,     0,
       0,   816,   817,     0,     0,     0,     0,   780,     0,   837,
     831,     0,     0,   141,     0,     0,     0,     0,   217,   181,
     161,   162,   163,   164,   165,   160,   167,   169,   372,   510,
     549,   184,   186,   453,    40,   605,   607,   445,   446,   447,
     448,   444,     0,    48,     0,     0,     0,   642,   334,     0,
       0,     0,     0,     0,     0,   174,   176,     0,     0,    53,
     206,   583,   610,   431,   433,   435,   439,   437,     0,   603,
     634,   637,   680,   668,   670,   672,   674,   676,   678,   538,
     262,   542,   540,   545,   575,   350,   352,   802,   804,   807,
     812,   813,   811,   815,   819,   821,   823,   825,   217,    44,
       0,     0,     0,   249,   254,   256,   258,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   271,     0,   278,
     280,   282,   284,   248,     0,   224,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   241,
     242,   243,   240,   244,   245,   246,   247,     0,   222,     0,
     218,   219,   377,     0,   373,   374,   515,     0,   511,   512,
     554,     0,   550,   551,   458,     0,   454,   455,   304,   305,
       0,   299,   302,   303,     0,   314,   315,   311,     0,   308,
     312,   313,   293,   295,     0,   288,   291,   292,   692,     0,
     689,   647,     0,   643,   644,   339,     0,   335,   336,     0,
       0,     0,     0,     0,     0,     0,   355,   358,   359,   360,
     361,   362,   363,   733,   739,     0,     0,     0,   732,   729,
     730,   731,     0,   721,   724,   727,   725,   726,   728,     0,
       0,     0,   328,     0,   320,   323,   324,   325,   326,   327,
     754,   756,   753,   751,   752,     0,   746,   749,   750,     0,
     770,     0,   773,   766,   767,     0,   760,   763,   764,   765,
     768,     0,   843,     0,   840,     0,   886,     0,   882,   885,
      55,   588,     0,   584,   585,   615,     0,   611,   612,   685,
     684,     0,   683,     0,    64,   827,   191,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   226,   212,   214,
       0,   216,   221,     0,   371,   376,   519,   507,   514,   558,
     548,   553,     0,   452,   457,   301,   298,   317,   310,   307,
       0,     0,   290,   287,   694,   691,   688,   651,   641,   646,
       0,   333,   338,     0,     0,     0,     0,     0,     0,   357,
     354,     0,     0,     0,     0,     0,   723,   720,     0,     0,
       0,   322,   319,     0,     0,   748,   745,     0,     0,     0,
       0,   762,   759,   776,     0,   842,   839,     0,   884,   881,
      57,     0,    56,     0,   582,   587,     0,   609,   614,     0,
     682,   836,     0,     0,     0,     0,   260,   263,   264,   265,
     266,   267,   268,   269,   277,   270,     0,   276,     0,     0,
       0,     0,   225,     0,   220,     0,   375,     0,   513,     0,
     552,   505,   477,   478,   479,   481,   482,   483,   467,   468,
     486,   487,   488,   489,   490,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   491,   492,   502,   503,   504,   463,
     464,   465,   466,   475,   476,   472,   473,   474,   471,   480,
       0,   460,   469,   484,   485,   470,   456,   300,   309,     0,
       0,   289,   714,   716,     0,   712,   706,   707,   708,   709,
     710,   711,   713,   703,   704,   705,     0,   695,   696,   699,
     700,   701,   702,   690,     0,   645,     0,   337,   364,   365,
     366,   367,   368,   369,   356,     0,     0,   738,   741,   742,
     722,   329,   330,   331,   321,     0,     0,   747,   769,     0,
     772,     0,   761,   858,     0,   856,   854,   848,   852,   853,
       0,   845,   850,   851,   849,   841,   887,   883,    54,    59,
       0,   586,     0,   613,     0,   251,   252,   253,   250,   255,
     257,   259,   273,   274,   275,   272,   279,   281,   283,   285,
     223,   378,   516,   555,   462,   459,   294,   296,     0,     0,
       0,   693,   698,   648,   340,   735,   736,   737,   734,   740,
     755,   757,   771,   774,     0,     0,     0,   847,   844,    58,
     589,   616,   686,   461,     0,     0,   718,   697,     0,   855,
       0,   846,   715,   717,     0,   857,   863,     0,   860,     0,
     862,   859,   873,     0,     0,     0,   878,     0,   865,   868,
     869,   870,   871,   872,   861,     0,     0,     0,     0,     0,
     867,   864,     0,   875,   876,   877,     0,   866,   874,   879
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028,   -10, -1028,  -615, -1028,
     472, -1028, -1028, -1028, -1028,   383, -1028,  -645, -1028, -1028,
   -1028,   -71, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   415,
     638, -1028, -1028,   -42,    11,    14,    17,    18,    28,   -31,
     -29,   -27,   -13,    31,    33,    41, -1028,    44,    45,    46,
      47, -1028,   426,    51, -1028,    57, -1028,    62,    63,    67,
      69, -1028,    74, -1028,    75, -1028, -1028, -1028, -1028, -1028,
      77, -1028,    79, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   418,   633, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   336, -1028,   119, -1028,  -725,
     125, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   -46, -1028,  -769, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028,   103, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028,   111,  -751, -1028, -1028, -1028,
   -1028,   110, -1028, -1028, -1028, -1028, -1028, -1028, -1028,    83,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028,    95, -1028, -1028,
   -1028,    99,   592, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
      92, -1028, -1028, -1028, -1028, -1028, -1028, -1027, -1028, -1028,
   -1028,   127, -1028, -1028, -1028,   132,   640, -1028, -1028, -1026,
   -1028, -1025, -1028,    86, -1028,    88, -1028,    80,    81,    82,
      85, -1028, -1028, -1028, -1024, -1028, -1028, -1028, -1028,   122,
   -1028, -1028,  -111,  1107, -1028, -1028, -1028, -1028, -1028,   145,
   -1028, -1028, -1028,   151, -1028,   631, -1028,   -62, -1028, -1028,
   -1028, -1028, -1028,   -59, -1028, -1028, -1028, -1028, -1028,    -5,
   -1028, -1028, -1028,   140, -1028, -1028, -1028,   154, -1028,   632,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028,    90, -1028, -1028, -1028,    93,   667, -1028, -1028,
     -60, -1028,     0, -1028, -1028, -1028, -1028, -1028,    94, -1028,
   -1028, -1028,    97,   679, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   -49, -1028, -1028, -1028,   139, -1028, -1028, -1028,   144,
   -1028,   651,   419, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1023, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028,   149, -1028, -1028, -1028,   -87, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   134, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   121, -1028, -1028, -1028, -1028, -1028, -1028, -1028,   117,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
     470,   624, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028,   477,   625, -1028, -1028, -1028, -1028, -1028, -1028,   128,
   -1028, -1028,   -95, -1028, -1028, -1028, -1028, -1028, -1028,  -115,
   -1028, -1028,  -134, -1028, -1028, -1028, -1028, -1028, -1028, -1028,
   -1028, -1028, -1028,   129, -1028
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     765,    87,    88,    41,    68,    84,    85,   790,  1000,  1111,
    1112,   853,    43,    70,    90,   449,    91,    45,    71,   161,
     162,   163,   452,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   478,   755,   182,   479,   183,   480,   184,   185,   186,
     187,   512,   188,   513,   189,   190,   191,   192,   472,   193,
     194,   489,   195,   490,   196,   197,   198,   199,   454,    47,
      72,   236,   237,   238,   522,   239,   240,   241,   242,   200,
     455,   201,   456,   202,   457,   879,   880,   881,  1040,   854,
     855,   856,  1017,  1278,   857,  1018,   858,  1019,   859,  1020,
     860,   861,   562,   862,   863,   864,   865,   866,   867,   868,
     869,   870,  1031,  1285,   871,   872,   873,  1033,   874,  1034,
     875,  1035,   876,  1036,   203,   501,   914,   915,   916,  1060,
     917,  1061,   204,   498,   900,   901,   902,   903,   205,   500,
     908,   909,   910,   911,   206,   499,   207,   508,   963,   964,
     965,   966,   967,   208,   504,   926,   927,   928,  1070,    63,
      80,   399,   400,   401,   576,   402,   577,   209,   505,   935,
     936,   937,   938,   939,   940,   941,   942,   210,   485,   883,
     884,   885,  1043,    49,    73,   283,   284,   285,   531,   286,
     532,   287,   533,   288,   537,   289,   536,   211,   212,   213,
     214,   494,   771,   294,   295,   215,   491,   895,   896,   897,
    1052,  1190,  1191,   216,   486,    57,    77,   887,   888,   889,
    1046,    59,    78,   362,   363,   364,   365,   366,   367,   368,
     561,   369,   565,   370,   564,   371,   372,   566,   373,   217,
     487,   891,   892,   893,  1049,    61,    79,   384,   385,   386,
     387,   388,   570,   389,   390,   391,   392,   393,   297,   529,
    1002,  1003,  1004,  1113,    51,    74,   308,   309,   310,   541,
     218,   492,   219,   493,   300,   530,  1006,  1007,  1008,  1116,
      53,    75,   324,   325,   326,   544,   327,   328,   546,   329,
     330,   220,   503,   922,   923,   924,  1067,    55,    76,   342,
     343,   344,   345,   552,   346,   553,   347,   554,   348,   555,
     349,   556,   350,   557,   351,   551,   302,   538,  1011,  1012,
    1119,   221,   502,   919,   920,  1064,  1216,  1217,  1218,  1219,
    1220,  1298,  1221,  1299,  1222,   222,   506,   952,   953,   954,
    1081,  1308,   955,   956,  1082,   957,   958,   223,   224,   509,
     975,   976,   977,  1093,   978,  1094,   225,   510,   985,   986,
     987,   988,  1098,   989,   990,  1100,   226,   511,    65,    81,
     421,   422,   423,   424,   581,   425,   582,   426,   427,   584,
     428,   429,   430,   587,   822,   431,   588,   432,   433,   434,
     591,   435,   592,   436,   593,   437,   594,   227,   453,    67,
      82,   440,   441,   442,   597,   443,   228,   517,   993,   994,
    1104,  1260,  1261,  1262,  1263,  1316,  1264,  1314,  1337,  1338,
    1339,  1347,  1348,  1349,  1355,  1350,  1351,  1352,  1353,  1359,
     229,   518,   997,   998,   999
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     160,   235,   255,   304,   318,   338,    38,   360,   380,   398,
     418,   949,   243,   298,   311,   322,   340,   382,   374,   394,
     383,   419,   877,   907,   301,  1180,  1181,  1182,  1189,  1195,
     764,   256,   361,   381,    31,   898,    32,    30,    33,   132,
     133,   796,   262,   127,   263,    42,   264,   132,   133,   396,
     397,   132,   133,   802,   803,   804,   750,   751,   752,   753,
     265,   313,   314,   315,   316,   317,   132,   133,   296,   307,
     321,   339,   244,   299,   312,   323,   341,    86,   375,   395,
      44,   420,   332,    46,   257,   438,   439,   258,   252,  1009,
     259,   260,   253,   754,   230,   231,   232,   233,   234,   970,
     971,   261,   396,   397,   266,   764,   267,   959,   960,   961,
     979,   980,   981,   995,   268,    48,   450,   269,   270,   271,
     272,   451,   899,  1055,   273,    50,  1056,   520,   159,   159,
     274,   353,   521,   943,   527,   275,   276,    52,   539,   528,
     277,   838,   278,   540,   820,   821,   542,   279,   280,   127,
     281,   543,   282,   290,   291,   292,   159,    54,   293,    56,
     305,   319,   306,   320,   982,   549,   898,   905,   159,   906,
     550,   578,   132,   133,    92,    93,   579,   595,    94,    58,
     132,   133,   596,   159,    95,    96,    97,   354,  1058,   355,
     356,  1059,   599,   331,   357,   358,   359,   600,    60,    62,
     332,   333,   334,   335,   336,   337,  1275,  1276,  1277,   132,
     133,   132,   133,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   767,   768,   769,   770,   520,    34,    35,
      36,    37,  1014,   128,   129,   130,   131,  1065,   912,   913,
    1066,   944,   945,   946,   947,   132,   133,  1180,  1181,  1182,
    1189,  1195,   134,  1282,  1283,  1284,   354,   135,   136,   137,
     138,   139,   140,   141,  1105,    89,   142,  1106,   599,   159,
     127,   527,   143,  1015,    64,  1037,  1016,   159,   132,   133,
    1038,   144,    66,  1037,   145,  1062,   303,   907,  1039,  1340,
    1063,   146,  1341,   132,   133,  1143,  1079,   949,  1086,   147,
     148,  1080,   444,  1087,   149,  1091,   159,   150,   159,  1095,
    1092,   151,  1101,   595,  1096,   252,  1108,  1102,  1103,   253,
     445,  1109,   354,   376,   355,   356,   377,   378,   379,  1305,
    1306,  1307,   152,   153,   154,   155,   156,   157,   126,   446,
     447,   448,   558,   833,   132,   133,   158,   834,   835,   836,
     837,   838,   839,   840,   841,   842,   843,   844,   845,   846,
     847,   458,   159,   459,   848,   849,   850,   851,   852,   460,
    1037,  1253,   539,  1254,  1255,  1290,   461,  1291,   462,    98,
      99,   100,   101,   102,   103,  1342,   463,  1294,  1343,  1344,
    1345,  1346,  1295,   578,   559,   159,   464,   465,  1304,   354,
     929,   930,   931,   932,   933,   934,  1317,   542,   127,   354,
     159,  1318,  1320,   549,  1360,   601,   602,   466,  1321,  1361,
     467,   468,   469,   470,   471,   473,   474,   475,   476,   160,
     477,   132,   133,   481,   482,   483,   235,   484,   488,   495,
     496,   497,   507,   514,   515,   516,   519,   243,   255,   523,
     524,   304,   525,   526,  1202,  1203,  1204,   534,   318,   298,
     535,   159,   311,   545,   547,   548,   560,   563,   338,   322,
     301,   567,   568,   569,   611,   571,   572,   256,   360,   340,
     573,   574,   575,   603,   380,   580,   583,   585,   262,   374,
     263,   586,   264,   382,   589,   394,   383,   590,   598,   604,
     605,   606,   607,   361,   418,   608,   265,   244,   609,   381,
     610,   612,   613,   625,   296,   419,   619,   307,   614,   299,
     615,   616,   312,   617,   321,   618,   628,   631,   620,   323,
     257,   632,   621,   258,   339,   622,   259,   260,   159,   341,
     623,   624,   626,   627,   633,   638,   629,   261,   159,   375,
     266,   636,   267,   132,   133,   395,   639,   640,   630,   634,
     268,   635,   637,   269,   270,   271,   272,   641,   642,   643,
     273,   644,   645,   646,   647,   420,   274,   648,   649,   651,
     650,   275,   276,   652,   653,   654,   277,   655,   278,   656,
     657,   658,   659,   279,   280,   660,   281,   661,   282,   290,
     291,   292,   662,   663,   293,   664,   665,   666,   305,   667,
     306,   668,   670,   671,   673,   319,   669,   320,   674,   675,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   679,   676,   677,   680,   681,   682,   683,
     416,   417,   686,   687,   688,   684,   690,   692,   693,   685,
     694,   160,   695,   698,   235,   699,   700,   701,   702,   703,
     704,   706,   707,   696,   708,   243,   709,   710,   711,   712,
     159,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   714,   719,   715,   720,   948,
     962,   972,   723,   418,   724,   725,   716,   996,   726,   717,
     950,   968,   973,   983,   419,   727,   722,   729,   728,   730,
     733,   829,   734,   731,   732,   735,   736,   738,   741,   739,
     823,   743,   742,   744,   745,   244,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   746,
     747,   748,   758,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   749,   756,   127,   757,   759,   760,   763,
     951,   969,   974,   984,   420,   761,   762,   129,   130,    32,
     245,   772,   246,   766,   773,   775,   774,   776,   132,   133,
     247,   248,   249,   250,   251,   134,   777,   778,   787,   789,
     135,   136,   137,   779,   780,   781,   782,   783,   784,   788,
     252,   785,   791,   786,   253,   143,   792,   798,   793,   794,
     795,   797,   254,   799,   800,   801,   805,   828,   878,   806,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   807,   808,   809,   810,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   882,   127,
     354,   886,   890,   894,   918,   811,   812,   921,   925,   992,
     813,   129,   130,   814,   815,   152,   153,   817,  1001,   818,
    1005,  1021,   132,   133,  1022,   248,   249,  1023,   251,   134,
     819,  1024,  1025,  1026,   135,   136,   137,   825,   826,   827,
    1027,  1028,  1029,  1030,   252,   159,  1032,  1041,   253,  1042,
    1044,  1045,  1048,  1047,  1073,  1051,   254,  1050,  1054,  1053,
    1057,  1069,  1068,  1071,  1072,  1110,  1074,  1075,  1076,  1077,
    1078,  1083,  1084,  1085,  1088,  1089,  1090,  1097,  1099,  1107,
    1115,  1127,  1114,  1118,  1117,  1122,  1269,  1120,  1121,  1123,
    1124,  1125,  1126,  1128,  1136,  1130,  1129,  1131,  1132,  1133,
    1134,  1135,   255,  1138,  1137,   360,  1139,  1140,   380,   152,
     153,  1151,  1141,   298,  1199,  1200,   374,   382,  1228,   394,
     383,  1229,  1193,  1205,   301,  1230,   338,  1231,  1232,   398,
     361,   256,  1235,   381,  1214,  1233,  1179,   340,  1236,   159,
    1152,  1245,   262,  1237,   263,   948,   264,  1238,  1212,  1239,
     962,  1158,  1206,  1159,   972,  1160,   950,  1241,  1246,  1249,
     265,   968,  1251,  1256,  1242,   973,  1243,   996,   296,  1161,
    1248,   983,   304,   299,  1258,   318,   375,  1192,  1250,   395,
    1268,  1266,  1194,   311,   257,  1274,   322,   258,  1257,  1213,
     259,   260,   339,  1153,  1215,  1279,  1154,   341,  1280,  1155,
    1156,   261,  1281,  1286,   266,  1207,   267,  1287,  1208,  1288,
    1157,  1209,  1210,  1162,   268,  1163,   951,   269,   270,   271,
     272,   969,  1211,  1164,   273,   974,  1165,  1166,  1167,  1168,
     274,   984,  1292,  1169,  1259,   275,   276,  1289,   307,  1170,
     277,   321,   278,   312,  1171,  1172,   323,   279,   280,  1173,
     281,  1174,   282,   290,   291,   292,  1175,  1176,   293,  1177,
    1293,  1178,  1185,  1186,  1187,  1300,  1301,  1188,  1183,  1302,
    1184,  1303,  1315,  1324,  1325,  1328,  1330,  1356,  1296,  1297,
    1334,  1336,  1357,  1358,  1362,  1366,   904,   830,   672,   824,
     678,  1144,  1142,   832,  1013,  1201,  1197,  1227,  1198,  1226,
     721,  1234,  1146,  1309,  1244,  1145,  1196,  1310,  1311,   689,
    1312,  1319,  1322,  1323,   352,  1329,  1326,  1332,  1363,  1333,
    1335,  1150,   816,  1148,  1364,  1365,  1368,  1147,  1369,   305,
     713,   306,   319,  1149,   320,  1271,  1270,   718,  1225,   691,
     705,  1224,  1273,  1272,  1223,  1327,  1247,  1010,  1252,   737,
    1240,   831,  1331,  1151,   740,  1354,  1367,     0,   697,     0,
       0,  1205,     0,  1265,  1193,     0,     0,  1267,     0,     0,
       0,  1313,  1214,     0,     0,     0,  1256,     0,  1179,     0,
       0,     0,  1152,     0,   991,     0,  1212,  1258,     0,     0,
    1206,     0,     0,  1158,     0,  1159,     0,  1160,     0,     0,
       0,  1257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1161,     0,     0,     0,     0,     0,     0,     0,  1192,
       0,     0,     0,     0,  1194,     0,     0,  1213,     0,     0,
       0,     0,  1215,     0,     0,  1153,     0,     0,  1154,     0,
       0,  1155,  1156,  1207,     0,     0,  1208,  1259,     0,  1209,
    1210,     0,  1157,     0,     0,  1162,     0,  1163,     0,     0,
    1211,     0,     0,     0,     0,  1164,     0,     0,  1165,  1166,
    1167,  1168,     0,     0,     0,  1169,     0,     0,     0,     0,
       0,  1170,     0,     0,     0,     0,  1171,  1172,     0,     0,
       0,  1173,     0,  1174,     0,     0,     0,     0,  1175,  1176,
       0,  1177,     0,  1178,  1185,  1186,  1187,     0,     0,  1188,
    1183,     0,  1184
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   780,    72,    73,    74,    75,    76,    79,    78,    79,
      79,    81,   747,   774,    73,  1052,  1052,  1052,  1052,  1052,
     645,    73,    78,    79,     5,   132,     7,     0,     9,   102,
     103,   686,    73,    79,    73,     7,    73,   102,   103,   139,
     140,   102,   103,   698,   699,   700,   185,   186,   187,   188,
      73,    97,    98,    99,   100,   101,   102,   103,    73,    74,
      75,    76,    72,    73,    74,    75,    76,   219,    78,    79,
       7,    81,   130,     7,    73,    13,    14,    73,   124,   137,
      73,    73,   128,   222,    16,    17,    18,    19,    20,   162,
     163,    73,   139,   140,    73,   720,    73,   158,   159,   160,
     165,   166,   167,   204,    73,     7,     3,    73,    73,    73,
      73,     8,   219,     3,    73,     7,     6,     3,   219,   219,
      73,    24,     8,    24,     3,    73,    73,     7,     3,     8,
      73,    32,    73,     8,   182,   183,     3,    73,    73,    79,
      73,     8,    73,    73,    73,    73,   219,     7,    73,     7,
      74,    75,    74,    75,   219,     3,   132,   133,   219,   135,
       8,     3,   102,   103,    11,    12,     8,     3,    15,     7,
     102,   103,     8,   219,    21,    22,    23,    80,     3,    82,
      83,     6,     3,   123,    87,    88,    89,     8,     7,     7,
     130,   131,   132,   133,   134,   135,    25,    26,    27,   102,
     103,   102,   103,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,   110,   111,   112,   113,     3,   219,   220,
     221,   222,     8,    90,    91,    92,    93,     3,   121,   122,
       6,   152,   153,   154,   155,   102,   103,  1294,  1294,  1294,
    1294,  1294,   109,    42,    43,    44,    80,   114,   115,   116,
     117,   118,   119,   120,     3,    10,   123,     6,     3,   219,
      79,     3,   129,     8,     7,     3,     8,   219,   102,   103,
       8,   138,     7,     3,   141,     3,    95,  1058,     8,     3,
       8,   148,     6,   102,   103,  1040,     3,  1086,     3,   156,
     157,     8,     6,     8,   161,     3,   219,   164,   219,     3,
       8,   168,     3,     3,     8,   124,     3,     8,     8,   128,
       3,     8,    80,    81,    82,    83,    84,    85,    86,   149,
     150,   151,   189,   190,   191,   192,   193,   194,    78,     4,
       8,     3,     8,    24,   102,   103,   203,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     4,   219,     4,    45,    46,    47,    48,    49,     4,
       3,   195,     3,   197,   198,     8,     4,     8,     4,    50,
      51,    52,    53,    54,    55,   196,     4,     3,   199,   200,
     201,   202,     8,     3,     3,   219,     4,     4,     8,    80,
     142,   143,   144,   145,   146,   147,     3,     3,    79,    80,
     219,     8,     8,     3,     3,   445,   446,     4,     8,     8,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   520,
       4,   102,   103,     4,     4,     4,   527,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   527,   539,     4,
       4,   542,     4,     4,   125,   126,   127,     4,   549,   539,
       4,   219,   542,     4,     4,     4,     8,     4,   559,   549,
     539,     4,     8,     3,   220,     4,     4,   539,   569,   559,
       4,     8,     3,   219,   575,     4,     4,     4,   539,   569,
     539,     4,   539,   575,     4,   575,   575,     4,     4,     4,
       4,     4,     4,   569,   595,     4,   539,   527,     4,   575,
       4,   220,   220,     4,   539,   595,   222,   542,   220,   539,
     220,   220,   542,   220,   549,   220,   222,     4,   221,   549,
     539,     4,   221,   539,   559,   221,   539,   539,   219,   559,
     220,   220,   220,   220,     4,     4,   222,   539,   219,   569,
     539,   221,   539,   102,   103,   575,     4,     4,   222,   222,
     539,   222,   222,   539,   539,   539,   539,   220,     4,     4,
     539,     4,     4,     4,     4,   595,   539,   222,   222,     4,
     222,   539,   539,     4,     4,     4,   539,     4,   539,     4,
       4,     4,     4,   539,   539,   220,   539,     4,   539,   539,
     539,   539,     4,     4,   539,     4,     4,     4,   542,   222,
     542,   222,     4,     4,     4,   549,   222,   549,   222,   222,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,     4,   220,   220,     4,     4,     4,     4,
     189,   190,     4,     4,     4,   220,     4,     4,   220,   222,
       4,   742,   220,     4,   745,     4,     4,     4,     4,     4,
       4,     4,     4,   220,   220,   745,     4,     4,     4,   222,
     219,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,     4,     4,   222,     4,   780,
     781,   782,     4,   784,     4,   220,   222,   788,     4,   222,
     780,   781,   782,   783,   784,   220,   222,     4,   220,     4,
       4,   741,     4,   222,   222,     4,     4,     4,     4,   220,
     184,   219,     7,     7,     7,   745,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     7,
       7,     5,     5,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,   219,   219,    79,   219,     5,     5,     5,
     780,   781,   782,   783,   784,   219,   219,    91,    92,     7,
      94,     5,    96,   219,     5,     7,     5,     5,   102,   103,
     104,   105,   106,   107,   108,   109,     5,     5,     5,     5,
     114,   115,   116,     7,     7,     7,     7,     7,     7,     7,
     124,   219,     5,   219,   128,   129,     5,     7,   219,   219,
     219,   219,   136,   219,   219,   219,   219,     5,     7,   219,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   219,   219,   219,   219,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,     7,    79,
      80,     7,     7,     7,     7,   219,   219,     7,     7,     7,
     219,    91,    92,   219,   219,   189,   190,   219,     7,   219,
       7,     4,   102,   103,     4,   105,   106,     4,   108,   109,
     219,     4,     4,     4,   114,   115,   116,   219,   219,   219,
       4,     4,     4,     4,   124,   219,     4,     6,   128,     3,
       6,     3,     3,     6,     4,     3,   136,     6,     3,     6,
       6,     3,     6,     6,     3,   219,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   222,     6,     3,     6,     4,     3,     8,     6,     4,
       4,     4,   220,   220,     4,   220,   222,   220,   220,   220,
     220,   220,  1043,     4,   220,  1046,     4,     4,  1049,   189,
     190,  1052,     4,  1043,     4,     4,  1046,  1049,   220,  1049,
    1049,   220,  1052,  1064,  1043,   220,  1067,   220,   220,  1070,
    1046,  1043,     4,  1049,  1064,   220,  1052,  1067,     4,   219,
    1052,     4,  1043,   220,  1043,  1086,  1043,   220,  1064,   220,
    1091,  1052,  1064,  1052,  1095,  1052,  1086,   222,     4,     4,
    1043,  1091,     4,  1104,   220,  1095,   220,  1108,  1043,  1052,
     222,  1101,  1113,  1043,  1104,  1116,  1046,  1052,   220,  1049,
       6,   222,  1052,  1113,  1043,     4,  1116,  1043,  1104,  1064,
    1043,  1043,  1067,  1052,  1064,   219,  1052,  1067,   219,  1052,
    1052,  1043,   219,   219,  1043,  1064,  1043,   219,  1064,   219,
    1052,  1064,  1064,  1052,  1043,  1052,  1086,  1043,  1043,  1043,
    1043,  1091,  1064,  1052,  1043,  1095,  1052,  1052,  1052,  1052,
    1043,  1101,     8,  1052,  1104,  1043,  1043,   219,  1113,  1052,
    1043,  1116,  1043,  1113,  1052,  1052,  1116,  1043,  1043,  1052,
    1043,  1052,  1043,  1043,  1043,  1043,  1052,  1052,  1043,  1052,
       8,  1052,  1052,  1052,  1052,     4,     8,  1052,  1052,     3,
    1052,     8,     4,     4,     4,     4,     4,     4,   219,   219,
       5,     7,     4,     4,     4,     4,   773,   742,   520,   733,
     527,  1042,  1037,   745,   828,  1062,  1055,  1072,  1058,  1070,
     578,  1079,  1045,   219,  1091,  1043,  1054,   219,   219,   539,
     219,   219,   219,  1294,    77,   220,   222,   219,   222,   219,
     219,  1051,   720,  1048,   220,   220,   219,  1046,   219,  1113,
     569,  1113,  1116,  1049,  1116,  1115,  1113,   575,  1069,   542,
     559,  1067,  1118,  1116,  1065,  1302,  1095,   798,  1101,   595,
    1086,   744,  1317,  1294,   599,  1340,  1360,    -1,   549,    -1,
      -1,  1302,    -1,  1105,  1294,    -1,    -1,  1108,    -1,    -1,
      -1,  1251,  1302,    -1,    -1,    -1,  1317,    -1,  1294,    -1,
      -1,    -1,  1294,    -1,   784,    -1,  1302,  1317,    -1,    -1,
    1302,    -1,    -1,  1294,    -1,  1294,    -1,  1294,    -1,    -1,
      -1,  1317,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1294,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1294,
      -1,    -1,    -1,    -1,  1294,    -1,    -1,  1302,    -1,    -1,
      -1,    -1,  1302,    -1,    -1,  1294,    -1,    -1,  1294,    -1,
      -1,  1294,  1294,  1302,    -1,    -1,  1302,  1317,    -1,  1302,
    1302,    -1,  1294,    -1,    -1,  1294,    -1,  1294,    -1,    -1,
    1302,    -1,    -1,    -1,    -1,  1294,    -1,    -1,  1294,  1294,
    1294,  1294,    -1,    -1,    -1,  1294,    -1,    -1,    -1,    -1,
      -1,  1294,    -1,    -1,    -1,    -1,  1294,  1294,    -1,    -1,
      -1,  1294,    -1,  1294,    -1,    -1,    -1,    -1,  1294,  1294,
      -1,  1294,    -1,  1294,  1294,  1294,  1294,    -1,    -1,  1294,
    1294,    -1,  1294
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
       0,     5,     7,     9,   219,   220,   221,   222,   239,   240,
     241,   246,     7,   255,     7,   260,     7,   312,     7,   426,
       7,   507,     7,   523,     7,   540,     7,   458,     7,   464,
       7,   488,     7,   402,     7,   611,     7,   642,   247,   242,
     256,   261,   313,   427,   508,   524,   541,   459,   465,   489,
     403,   612,   643,   239,   248,   249,   219,   244,   245,    10,
     257,   259,    11,    12,    15,    21,    22,    23,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    90,    91,
      92,    93,   102,   103,   109,   114,   115,   116,   117,   118,
     119,   120,   123,   129,   138,   141,   148,   156,   157,   161,
     164,   168,   189,   190,   191,   192,   193,   194,   203,   219,
     254,   262,   263,   264,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   286,   288,   290,   291,   292,   293,   295,   297,
     298,   299,   300,   302,   303,   305,   307,   308,   309,   310,
     322,   324,   326,   367,   375,   381,   387,   389,   396,   410,
     420,   440,   441,   442,   443,   448,   456,   482,   513,   515,
     534,   564,   578,   590,   591,   599,   609,   640,   649,   673,
      16,    17,    18,    19,    20,   254,   314,   315,   316,   318,
     319,   320,   321,   513,   515,    94,    96,   104,   105,   106,
     107,   108,   124,   128,   136,   254,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   280,
     281,   282,   283,   286,   288,   290,   291,   292,   293,   295,
     297,   303,   305,   428,   429,   430,   432,   434,   436,   438,
     440,   441,   442,   443,   446,   447,   482,   501,   513,   515,
     517,   534,   559,    95,   254,   436,   438,   482,   509,   510,
     511,   513,   515,    97,    98,    99,   100,   101,   254,   436,
     438,   482,   513,   515,   525,   526,   527,   529,   530,   532,
     533,   123,   130,   131,   132,   133,   134,   135,   254,   482,
     513,   515,   542,   543,   544,   545,   547,   549,   551,   553,
     555,   557,   456,    24,    80,    82,    83,    87,    88,    89,
     254,   344,   466,   467,   468,   469,   470,   471,   472,   474,
     476,   478,   479,   481,   513,   515,    81,    84,    85,    86,
     254,   344,   470,   476,   490,   491,   492,   493,   494,   496,
     497,   498,   499,   500,   513,   515,   139,   140,   254,   404,
     405,   406,   408,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   189,   190,   254,   513,
     515,   613,   614,   615,   616,   618,   620,   621,   623,   624,
     625,   628,   630,   631,   632,   634,   636,   638,    13,    14,
     644,   645,   646,   648,     6,     3,     4,     8,     3,   258,
       3,     8,   265,   641,   311,   323,   325,   327,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   301,     4,     4,     4,     4,     4,   284,   287,
     289,     4,     4,     4,     4,   421,   457,   483,     4,   304,
     306,   449,   514,   516,   444,     4,     4,     4,   376,   388,
     382,   368,   565,   535,   397,   411,   579,     4,   390,   592,
     600,   610,   294,   296,     4,     4,     4,   650,   674,     4,
       3,     8,   317,     4,     4,     4,     4,     3,     8,   502,
     518,   431,   433,   435,     4,     4,   439,   437,   560,     3,
       8,   512,     3,     8,   528,     4,   531,     4,     4,     3,
       8,   558,   546,   548,   550,   552,   554,   556,     8,     3,
       8,   473,   345,     4,   477,   475,   480,     4,     8,     3,
     495,     4,     4,     4,     8,     3,   407,   409,     3,     8,
       4,   617,   619,     4,   622,     4,     4,   626,   629,     4,
       4,   633,   635,   637,   639,     3,     8,   647,     4,     3,
       8,   239,   239,   219,     4,     4,     4,     4,     4,     4,
       4,   220,   220,   220,   220,   220,   220,   220,   220,   222,
     221,   221,   221,   220,   220,     4,   220,   220,   222,   222,
     222,     4,     4,     4,   222,   222,   221,   222,     4,     4,
       4,   220,     4,     4,     4,     4,     4,     4,   222,   222,
     222,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     220,     4,     4,     4,     4,     4,     4,   222,   222,   222,
       4,     4,   263,     4,   222,   222,   220,   220,   315,     4,
       4,     4,     4,     4,   220,   222,     4,     4,     4,   429,
       4,   510,     4,   220,     4,   220,   220,   526,     4,     4,
       4,     4,     4,     4,     4,   544,     4,     4,   220,     4,
       4,     4,   222,   468,     4,   222,   222,   222,   492,     4,
       4,   405,   222,     4,     4,   220,     4,   220,   220,     4,
       4,   222,   222,     4,     4,     4,     4,   614,     4,   220,
     645,     4,     7,   219,     7,     7,     7,     7,     5,   219,
     185,   186,   187,   188,   222,   285,   219,   219,     5,     5,
       5,   219,   219,     5,   241,   243,   219,   110,   111,   112,
     113,   445,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     7,     7,   219,   219,     5,     7,     5,
     250,     5,     5,   219,   219,   219,   250,   219,     7,   219,
     219,   219,   250,   250,   250,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   243,   219,   219,   219,
     182,   183,   627,   184,   285,   219,   219,   219,     5,   239,
     262,   644,   314,    24,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    45,    46,
      47,    48,    49,   254,   332,   333,   334,   337,   339,   341,
     343,   344,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   357,   358,   359,   361,   363,   365,   332,     7,   328,
     329,   330,     7,   422,   423,   424,     7,   460,   461,   462,
       7,   484,   485,   486,     7,   450,   451,   452,   132,   219,
     377,   378,   379,   380,   248,   133,   135,   379,   383,   384,
     385,   386,   121,   122,   369,   370,   371,   373,     7,   566,
     567,     7,   536,   537,   538,     7,   398,   399,   400,   142,
     143,   144,   145,   146,   147,   412,   413,   414,   415,   416,
     417,   418,   419,    24,   152,   153,   154,   155,   254,   346,
     513,   515,   580,   581,   582,   585,   586,   588,   589,   158,
     159,   160,   254,   391,   392,   393,   394,   395,   513,   515,
     162,   163,   254,   513,   515,   593,   594,   595,   597,   165,
     166,   167,   219,   513,   515,   601,   602,   603,   604,   606,
     607,   613,     7,   651,   652,   204,   254,   675,   676,   677,
     251,     7,   503,   504,   505,     7,   519,   520,   521,   137,
     545,   561,   562,   328,     8,     8,     8,   335,   338,   340,
     342,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   355,     4,   360,   362,   364,   366,     3,     8,     8,
     331,     6,     3,   425,     6,     3,   463,     6,     3,   487,
       6,     3,   453,     6,     3,     3,     6,     6,     3,     6,
     372,   374,     3,     8,   568,     3,     6,   539,     6,     3,
     401,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   583,   587,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   596,   598,     3,     8,     4,   605,     4,
     608,     3,     8,     8,   653,     3,     6,     4,     3,     8,
     219,   252,   253,   506,     6,     3,   522,     6,     3,   563,
       8,     6,     4,     4,     4,     4,   220,   222,   220,   222,
     220,   220,   220,   220,   220,   220,     4,   220,     4,     4,
       4,     4,   333,   332,   330,   428,   424,   466,   462,   490,
     486,   254,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   280,   281,   282,   283,   286,
     288,   290,   291,   292,   293,   295,   297,   303,   305,   344,
     420,   432,   434,   436,   438,   440,   441,   442,   443,   447,
     454,   455,   482,   513,   515,   559,   452,   378,   384,     4,
       4,   370,   125,   126,   127,   254,   266,   267,   268,   269,
     270,   271,   344,   482,   513,   515,   569,   570,   571,   572,
     573,   575,   577,   567,   542,   538,   404,   400,   220,   220,
     220,   220,   220,   220,   413,     4,     4,   220,   220,   220,
     581,   222,   220,   220,   392,     4,     4,   594,   222,     4,
     220,     4,   602,   195,   197,   198,   254,   344,   513,   515,
     654,   655,   656,   657,   659,   652,   222,   676,     6,     3,
     509,   505,   525,   521,     4,    25,    26,    27,   336,   219,
     219,   219,    42,    43,    44,   356,   219,   219,   219,   219,
       8,     8,     8,     8,     3,     8,   219,   219,   574,   576,
       4,     8,     3,     8,     8,   149,   150,   151,   584,   219,
     219,   219,   219,   239,   660,     4,   658,     3,     8,   219,
       8,     8,   219,   455,     4,     4,   222,   571,     4,   220,
       4,   655,   219,   219,     5,   219,     7,   661,   662,   663,
       3,     6,   196,   199,   200,   201,   202,   664,   665,   666,
     668,   669,   670,   671,   662,   667,     4,     4,     4,   672,
       3,     8,     4,   222,   220,   220,     4,   665,   219,   219
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   223,   225,   224,   226,   224,   227,   224,   228,   224,
     229,   224,   230,   224,   231,   224,   232,   224,   233,   224,
     234,   224,   235,   224,   236,   224,   237,   224,   238,   224,
     239,   239,   239,   239,   239,   239,   239,   240,   242,   241,
     243,   244,   244,   245,   245,   245,   247,   246,   248,   248,
     249,   249,   249,   251,   250,   252,   252,   253,   253,   253,
     254,   256,   255,   258,   257,   257,   259,   261,   260,   262,
     262,   262,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     265,   264,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   284,
     283,   285,   285,   285,   285,   285,   287,   286,   289,   288,
     290,   291,   292,   294,   293,   296,   295,   297,   298,   299,
     301,   300,   302,   304,   303,   306,   305,   307,   308,   309,
     311,   310,   313,   312,   314,   314,   314,   315,   315,   315,
     315,   315,   315,   315,   315,   317,   316,   318,   319,   320,
     321,   323,   322,   325,   324,   327,   326,   328,   328,   329,
     329,   329,   331,   330,   332,   332,   332,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   335,
     334,   336,   336,   336,   338,   337,   340,   339,   342,   341,
     343,   345,   344,   346,   347,   348,   349,   350,   351,   352,
     353,   355,   354,   356,   356,   356,   357,   358,   360,   359,
     362,   361,   364,   363,   366,   365,   368,   367,   369,   369,
     369,   370,   370,   372,   371,   374,   373,   376,   375,   377,
     377,   377,   378,   378,   379,   380,   382,   381,   383,   383,
     383,   384,   384,   384,   385,   386,   388,   387,   390,   389,
     391,   391,   391,   392,   392,   392,   392,   392,   392,   393,
     394,   395,   397,   396,   398,   398,   399,   399,   399,   401,
     400,   403,   402,   404,   404,   404,   404,   405,   405,   407,
     406,   409,   408,   411,   410,   412,   412,   412,   413,   413,
     413,   413,   413,   413,   414,   415,   416,   417,   418,   419,
     421,   420,   422,   422,   423,   423,   423,   425,   424,   427,
     426,   428,   428,   428,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     431,   430,   433,   432,   435,   434,   437,   436,   439,   438,
     440,   441,   442,   444,   443,   445,   445,   445,   445,   446,
     447,   449,   448,   450,   450,   451,   451,   451,   453,   452,
     454,   454,   454,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   457,   456,   459,   458,
     460,   460,   461,   461,   461,   463,   462,   465,   464,   466,
     466,   467,   467,   467,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   469,   470,   471,   473,   472,   475,
     474,   477,   476,   478,   480,   479,   481,   483,   482,   484,
     484,   485,   485,   485,   487,   486,   489,   488,   490,   490,
     491,   491,   491,   492,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   493,   495,   494,   496,   497,   498,   499,
     500,   502,   501,   503,   503,   504,   504,   504,   506,   505,
     508,   507,   509,   509,   509,   510,   510,   510,   510,   510,
     510,   510,   512,   511,   514,   513,   516,   515,   518,   517,
     519,   519,   520,   520,   520,   522,   521,   524,   523,   525,
     525,   525,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   526,   526,   528,   527,   529,   531,   530,   532,   533,
     535,   534,   536,   536,   537,   537,   537,   539,   538,   541,
     540,   542,   542,   543,   543,   543,   544,   544,   544,   544,
     544,   544,   544,   544,   544,   544,   544,   546,   545,   548,
     547,   550,   549,   552,   551,   554,   553,   556,   555,   558,
     557,   560,   559,   561,   561,   563,   562,   565,   564,   566,
     566,   566,   568,   567,   569,   569,   570,   570,   570,   571,
     571,   571,   571,   571,   571,   571,   571,   571,   571,   571,
     571,   571,   571,   572,   574,   573,   576,   575,   577,   579,
     578,   580,   580,   580,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   583,   582,   584,   584,   584,   585,   587,
     586,   588,   589,   590,   592,   591,   593,   593,   593,   594,
     594,   594,   594,   594,   596,   595,   598,   597,   600,   599,
     601,   601,   601,   602,   602,   602,   602,   602,   602,   603,
     605,   604,   606,   608,   607,   610,   609,   612,   611,   613,
     613,   613,   614,   614,   614,   614,   614,   614,   614,   614,
     614,   614,   614,   614,   614,   614,   614,   614,   614,   614,
     615,   617,   616,   619,   618,   620,   622,   621,   623,   624,
     626,   625,   627,   627,   629,   628,   630,   631,   633,   632,
     635,   634,   637,   636,   639,   638,   641,   640,   643,   642,
     644,   644,   644,   645,   645,   647,   646,   648,   650,   649,
     651,   651,   651,   653,   652,   654,   654,   654,   655,   655,
     655,   655,   655,   655,   655,   656,   658,   657,   660,   659,
     661,   661,   661,   663,   662,   664,   664,   664,   665,   665,
     665,   665,   665,   667,   666,   668,   669,   670,   672,   671,
     674,   673,   675,   675,   675,   676,   676,   677
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
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     4,     0,     6,     1,
       3,     2,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     0,     6,     3,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     3
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
       0,   311,   311,   311,   312,   312,   313,   313,   314,   314,
     315,   315,   316,   316,   317,   317,   318,   318,   319,   319,
     320,   320,   321,   321,   322,   322,   323,   323,   324,   324,
     332,   333,   334,   335,   336,   337,   338,   341,   346,   346,
     357,   360,   361,   364,   369,   375,   380,   380,   387,   388,
     391,   395,   399,   405,   405,   412,   413,   416,   420,   424,
     434,   443,   443,   458,   458,   472,   475,   481,   481,   490,
     491,   492,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     569,   569,   578,   584,   590,   596,   602,   608,   614,   620,
     626,   632,   638,   644,   650,   656,   662,   668,   674,   680,
     680,   689,   692,   695,   698,   701,   707,   707,   716,   716,
     725,   731,   737,   743,   743,   752,   752,   761,   767,   773,
     779,   779,   788,   794,   794,   803,   803,   812,   818,   824,
     830,   830,   842,   842,   851,   852,   853,   858,   859,   860,
     861,   862,   863,   864,   865,   868,   868,   879,   885,   891,
     897,   903,   903,   916,   916,   929,   929,   940,   941,   944,
     945,   946,   951,   951,   961,   962,   963,   968,   969,   970,
     971,   972,   973,   974,   975,   976,   977,   978,   979,   980,
     981,   982,   983,   984,   985,   986,   987,   988,   989,   992,
     992,  1000,  1001,  1002,  1005,  1005,  1014,  1014,  1023,  1023,
    1032,  1038,  1038,  1047,  1053,  1059,  1065,  1071,  1077,  1083,
    1090,  1096,  1096,  1104,  1105,  1106,  1109,  1115,  1121,  1121,
    1130,  1130,  1139,  1139,  1148,  1148,  1157,  1157,  1168,  1169,
    1170,  1175,  1176,  1179,  1179,  1198,  1198,  1216,  1216,  1227,
    1228,  1229,  1234,  1235,  1238,  1243,  1248,  1248,  1259,  1260,
    1261,  1266,  1267,  1268,  1271,  1276,  1283,  1283,  1296,  1296,
    1309,  1310,  1311,  1316,  1317,  1318,  1319,  1320,  1321,  1324,
    1330,  1336,  1342,  1342,  1353,  1354,  1357,  1358,  1359,  1364,
    1364,  1374,  1374,  1384,  1385,  1386,  1389,  1392,  1393,  1396,
    1396,  1405,  1405,  1414,  1414,  1426,  1427,  1428,  1433,  1434,
    1435,  1436,  1437,  1438,  1441,  1447,  1453,  1459,  1465,  1471,
    1480,  1480,  1494,  1495,  1498,  1499,  1500,  1509,  1509,  1535,
    1535,  1546,  1547,  1548,  1554,  1555,  1556,  1557,  1558,  1559,
    1560,  1561,  1562,  1563,  1564,  1565,  1566,  1567,  1568,  1569,
    1570,  1571,  1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,
    1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,  1588,  1589,
    1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,
    1602,  1602,  1611,  1611,  1620,  1620,  1629,  1629,  1638,  1638,
    1649,  1655,  1661,  1667,  1667,  1675,  1676,  1677,  1678,  1681,
    1687,  1695,  1695,  1707,  1708,  1712,  1713,  1714,  1719,  1719,
    1727,  1728,  1729,  1734,  1735,  1736,  1737,  1738,  1739,  1740,
    1741,  1742,  1743,  1744,  1745,  1746,  1747,  1748,  1749,  1750,
    1751,  1752,  1753,  1754,  1755,  1756,  1757,  1758,  1759,  1760,
    1761,  1762,  1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,
    1771,  1772,  1773,  1774,  1775,  1776,  1783,  1783,  1797,  1797,
    1806,  1807,  1810,  1811,  1812,  1819,  1819,  1834,  1834,  1848,
    1849,  1852,  1853,  1854,  1859,  1860,  1861,  1862,  1863,  1864,
    1865,  1866,  1867,  1868,  1871,  1873,  1879,  1881,  1881,  1890,
    1890,  1899,  1899,  1908,  1910,  1910,  1919,  1929,  1929,  1942,
    1943,  1948,  1949,  1950,  1957,  1957,  1969,  1969,  1981,  1982,
    1987,  1988,  1989,  1996,  1997,  1998,  1999,  2000,  2001,  2002,
    2003,  2004,  2005,  2008,  2010,  2010,  2019,  2021,  2023,  2029,
    2035,  2044,  2044,  2057,  2058,  2061,  2062,  2063,  2068,  2068,
    2078,  2078,  2088,  2089,  2090,  2095,  2096,  2097,  2098,  2099,
    2100,  2101,  2104,  2104,  2113,  2113,  2138,  2138,  2168,  2168,
    2181,  2182,  2185,  2186,  2187,  2192,  2192,  2204,  2204,  2216,
    2217,  2218,  2223,  2224,  2225,  2226,  2227,  2228,  2229,  2230,
    2231,  2232,  2233,  2236,  2236,  2245,  2251,  2251,  2260,  2266,
    2275,  2275,  2286,  2287,  2290,  2291,  2292,  2297,  2297,  2306,
    2306,  2315,  2316,  2319,  2320,  2321,  2327,  2328,  2329,  2330,
    2331,  2332,  2333,  2334,  2335,  2336,  2337,  2340,  2340,  2351,
    2351,  2362,  2362,  2371,  2371,  2380,  2380,  2389,  2389,  2398,
    2398,  2412,  2412,  2423,  2424,  2427,  2427,  2439,  2439,  2450,
    2451,  2452,  2457,  2457,  2467,  2468,  2471,  2472,  2473,  2478,
    2479,  2480,  2481,  2482,  2483,  2484,  2485,  2486,  2487,  2488,
    2489,  2490,  2491,  2494,  2496,  2496,  2505,  2505,  2514,  2523,
    2523,  2536,  2537,  2538,  2543,  2544,  2545,  2546,  2547,  2548,
    2549,  2550,  2551,  2554,  2554,  2562,  2563,  2564,  2567,  2573,
    2573,  2582,  2588,  2596,  2604,  2604,  2615,  2616,  2617,  2622,
    2623,  2624,  2625,  2626,  2629,  2629,  2638,  2638,  2650,  2650,
    2663,  2664,  2665,  2670,  2671,  2672,  2673,  2674,  2675,  2678,
    2684,  2684,  2693,  2699,  2699,  2709,  2709,  2722,  2722,  2732,
    2733,  2734,  2739,  2740,  2741,  2742,  2743,  2744,  2745,  2746,
    2747,  2748,  2749,  2750,  2751,  2752,  2753,  2754,  2755,  2756,
    2759,  2766,  2766,  2775,  2775,  2784,  2790,  2790,  2799,  2805,
    2811,  2811,  2820,  2821,  2824,  2824,  2834,  2841,  2848,  2848,
    2857,  2857,  2867,  2867,  2877,  2877,  2889,  2889,  2901,  2901,
    2911,  2912,  2913,  2919,  2920,  2923,  2923,  2934,  2942,  2942,
    2955,  2956,  2957,  2963,  2963,  2971,  2972,  2973,  2978,  2979,
    2980,  2981,  2982,  2983,  2984,  2987,  2993,  2993,  3002,  3002,
    3013,  3014,  3015,  3020,  3020,  3028,  3029,  3030,  3035,  3036,
    3037,  3038,  3039,  3042,  3042,  3051,  3057,  3063,  3069,  3069,
    3078,  3078,  3089,  3090,  3091,  3096,  3097,  3100
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
#line 6526 "dhcp6_parser.cc"

#line 3106 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
