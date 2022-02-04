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
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 298 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 298 "dhcp6_parser.yy"
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
#line 307 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 308 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 309 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 310 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 311 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 312 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 313 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 314 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 315 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 316 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 317 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 318 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 319 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 320 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 328 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 329 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 330 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 331 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 332 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 333 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 334 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 337 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 342 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 347 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 353 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 360 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 365 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 371 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 376 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 379 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 387 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 391 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 395 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 401 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 403 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 412 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 416 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 420 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 430 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 439 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 444 "dhcp6_parser.yy"
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
#line 454 "dhcp6_parser.yy"
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
#line 463 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 471 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 477 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 481 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 488 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 137: // $@21: %empty
#line 562 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 138: // data_directory: "data-directory" $@21 ":" "constant string"
#line 565 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 139: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 571 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 140: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 577 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 141: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 583 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 589 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 595 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 601 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 607 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 613 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 619 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 625 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 631 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 637 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 643 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 649 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 153: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 655 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 154: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 661 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 155: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 667 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 156: // $@22: %empty
#line 673 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 676 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "when-present"
#line 682 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "never"
#line 685 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "always"
#line 688 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-not-present"
#line 691 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "boolean"
#line 694 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 163: // $@23: %empty
#line 700 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 164: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 703 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 165: // $@24: %empty
#line 709 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 166: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 712 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 167: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 718 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 168: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 724 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 169: // $@25: %empty
#line 730 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 733 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 171: // $@26: %empty
#line 739 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 742 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 173: // store_extended_info: "store-extended-info" ":" "boolean"
#line 748 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 174: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 754 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 175: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 760 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 176: // $@27: %empty
#line 766 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 177: // server_tag: "server-tag" $@27 ":" "constant string"
#line 769 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 178: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 775 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 179: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 781 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 180: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 787 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 181: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 793 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 182: // $@28: %empty
#line 799 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 183: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 805 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 184: // $@29: %empty
#line 811 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 185: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 815 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // interfaces_config_params: interfaces_config_params ","
#line 822 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1598 "dhcp6_parser.cc"
    break;

  case 194: // $@30: %empty
#line 834 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "dhcp6_parser.cc"
    break;

  case 195: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 840 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 196: // re_detect: "re-detect" ":" "boolean"
#line 845 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 851 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 198: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 857 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1652 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 864 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1664 "dhcp6_parser.cc"
    break;

  case 200: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 870 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1675 "dhcp6_parser.cc"
    break;

  case 201: // $@33: %empty
#line 877 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 202: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 883 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1696 "dhcp6_parser.cc"
    break;

  case 207: // not_empty_database_list: not_empty_database_list ","
#line 894 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1704 "dhcp6_parser.cc"
    break;

  case 208: // $@34: %empty
#line 899 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1714 "dhcp6_parser.cc"
    break;

  case 209: // database: "{" $@34 database_map_params "}"
#line 903 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1724 "dhcp6_parser.cc"
    break;

  case 212: // database_map_params: database_map_params ","
#line 911 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1732 "dhcp6_parser.cc"
    break;

  case 239: // $@35: %empty
#line 944 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 240: // database_type: "type" $@35 ":" db_type
#line 947 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1750 "dhcp6_parser.cc"
    break;

  case 241: // db_type: "memfile"
#line 952 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1756 "dhcp6_parser.cc"
    break;

  case 242: // db_type: "mysql"
#line 953 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1762 "dhcp6_parser.cc"
    break;

  case 243: // db_type: "postgresql"
#line 954 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1768 "dhcp6_parser.cc"
    break;

  case 244: // db_type: "cql"
#line 955 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1774 "dhcp6_parser.cc"
    break;

  case 245: // $@36: %empty
#line 958 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1783 "dhcp6_parser.cc"
    break;

  case 246: // user: "user" $@36 ":" "constant string"
#line 961 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1793 "dhcp6_parser.cc"
    break;

  case 247: // $@37: %empty
#line 967 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1802 "dhcp6_parser.cc"
    break;

  case 248: // password: "password" $@37 ":" "constant string"
#line 970 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1812 "dhcp6_parser.cc"
    break;

  case 249: // $@38: %empty
#line 976 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1821 "dhcp6_parser.cc"
    break;

  case 250: // host: "host" $@38 ":" "constant string"
#line 979 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1831 "dhcp6_parser.cc"
    break;

  case 251: // port: "port" ":" "integer"
#line 985 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1841 "dhcp6_parser.cc"
    break;

  case 252: // $@39: %empty
#line 991 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1850 "dhcp6_parser.cc"
    break;

  case 253: // name: "name" $@39 ":" "constant string"
#line 994 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1860 "dhcp6_parser.cc"
    break;

  case 254: // persist: "persist" ":" "boolean"
#line 1000 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 255: // lfc_interval: "lfc-interval" ":" "integer"
#line 1006 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1880 "dhcp6_parser.cc"
    break;

  case 256: // readonly: "readonly" ":" "boolean"
#line 1012 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1890 "dhcp6_parser.cc"
    break;

  case 257: // connect_timeout: "connect-timeout" ":" "integer"
#line 1018 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 258: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1024 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1910 "dhcp6_parser.cc"
    break;

  case 259: // $@40: %empty
#line 1030 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1919 "dhcp6_parser.cc"
    break;

  case 260: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1033 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1928 "dhcp6_parser.cc"
    break;

  case 261: // on_fail_mode: "stop-retry-exit"
#line 1038 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1934 "dhcp6_parser.cc"
    break;

  case 262: // on_fail_mode: "serve-retry-exit"
#line 1039 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1940 "dhcp6_parser.cc"
    break;

  case 263: // on_fail_mode: "serve-retry-continue"
#line 1040 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1946 "dhcp6_parser.cc"
    break;

  case 264: // max_row_errors: "max-row-errors" ":" "integer"
#line 1043 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 265: // request_timeout: "request-timeout" ":" "integer"
#line 1049 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 266: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1055 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1976 "dhcp6_parser.cc"
    break;

  case 267: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1061 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1986 "dhcp6_parser.cc"
    break;

  case 268: // $@41: %empty
#line 1067 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 269: // contact_points: "contact-points" $@41 ":" "constant string"
#line 1070 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 2005 "dhcp6_parser.cc"
    break;

  case 270: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1076 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2015 "dhcp6_parser.cc"
    break;

  case 271: // $@42: %empty
#line 1082 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2024 "dhcp6_parser.cc"
    break;

  case 272: // keyspace: "keyspace" $@42 ":" "constant string"
#line 1085 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2034 "dhcp6_parser.cc"
    break;

  case 273: // $@43: %empty
#line 1091 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2043 "dhcp6_parser.cc"
    break;

  case 274: // consistency: "consistency" $@43 ":" "constant string"
#line 1094 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2053 "dhcp6_parser.cc"
    break;

  case 275: // $@44: %empty
#line 1100 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 276: // serial_consistency: "serial-consistency" $@44 ":" "constant string"
#line 1103 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 277: // $@45: %empty
#line 1109 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp6_parser.cc"
    break;

  case 278: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1112 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 279: // $@46: %empty
#line 1118 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 280: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1121 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2110 "dhcp6_parser.cc"
    break;

  case 281: // $@47: %empty
#line 1127 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2119 "dhcp6_parser.cc"
    break;

  case 282: // key_file: "key-file" $@47 ":" "constant string"
#line 1130 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2129 "dhcp6_parser.cc"
    break;

  case 283: // $@48: %empty
#line 1136 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 284: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1139 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 285: // $@49: %empty
#line 1145 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2160 "dhcp6_parser.cc"
    break;

  case 286: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1151 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2169 "dhcp6_parser.cc"
    break;

  case 289: // sanity_checks_params: sanity_checks_params ","
#line 1158 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2177 "dhcp6_parser.cc"
    break;

  case 291: // $@50: %empty
#line 1165 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2186 "dhcp6_parser.cc"
    break;

  case 292: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1168 "dhcp6_parser.yy"
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
#line 2206 "dhcp6_parser.cc"
    break;

  case 293: // $@51: %empty
#line 1184 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2218 "dhcp6_parser.cc"
    break;

  case 294: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1190 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2227 "dhcp6_parser.cc"
    break;

  case 297: // mac_sources_list: mac_sources_list ","
#line 1197 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2235 "dhcp6_parser.cc"
    break;

  case 300: // duid_id: "duid"
#line 1206 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2244 "dhcp6_parser.cc"
    break;

  case 301: // string_id: "constant string"
#line 1211 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 302: // $@52: %empty
#line 1216 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2265 "dhcp6_parser.cc"
    break;

  case 303: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1222 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2274 "dhcp6_parser.cc"
    break;

  case 306: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1229 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2282 "dhcp6_parser.cc"
    break;

  case 310: // hw_address_id: "hw-address"
#line 1239 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 311: // flex_id: "flex-id"
#line 1244 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 312: // $@53: %empty
#line 1251 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2312 "dhcp6_parser.cc"
    break;

  case 313: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1257 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc"
    break;

  case 314: // $@54: %empty
#line 1264 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2333 "dhcp6_parser.cc"
    break;

  case 315: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1270 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 318: // multi_threading_params: multi_threading_params ","
#line 1279 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2352 "dhcp6_parser.cc"
    break;

  case 325: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1292 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 326: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1298 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 327: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1304 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2382 "dhcp6_parser.cc"
    break;

  case 328: // $@55: %empty
#line 1310 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2394 "dhcp6_parser.cc"
    break;

  case 329: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1316 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2403 "dhcp6_parser.cc"
    break;

  case 334: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1327 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2411 "dhcp6_parser.cc"
    break;

  case 335: // $@56: %empty
#line 1332 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2421 "dhcp6_parser.cc"
    break;

  case 336: // hooks_library: "{" $@56 hooks_params "}"
#line 1336 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 337: // $@57: %empty
#line 1342 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2441 "dhcp6_parser.cc"
    break;

  case 338: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1346 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2451 "dhcp6_parser.cc"
    break;

  case 341: // hooks_params: hooks_params ","
#line 1354 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2459 "dhcp6_parser.cc"
    break;

  case 345: // $@58: %empty
#line 1364 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2468 "dhcp6_parser.cc"
    break;

  case 346: // library: "library" $@58 ":" "constant string"
#line 1367 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2478 "dhcp6_parser.cc"
    break;

  case 347: // $@59: %empty
#line 1373 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 348: // parameters: "parameters" $@59 ":" map_value
#line 1376 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc"
    break;

  case 349: // $@60: %empty
#line 1382 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 350: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1388 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 353: // expired_leases_params: expired_leases_params ","
#line 1396 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2526 "dhcp6_parser.cc"
    break;

  case 360: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1409 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 361: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1415 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 362: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1421 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2556 "dhcp6_parser.cc"
    break;

  case 363: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1427 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 364: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1433 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 365: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1439 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 366: // $@61: %empty
#line 1448 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2598 "dhcp6_parser.cc"
    break;

  case 367: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1454 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2607 "dhcp6_parser.cc"
    break;

  case 372: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1468 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2615 "dhcp6_parser.cc"
    break;

  case 373: // $@62: %empty
#line 1477 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2625 "dhcp6_parser.cc"
    break;

  case 374: // subnet6: "{" $@62 subnet6_params "}"
#line 1481 "dhcp6_parser.yy"
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
#line 2651 "dhcp6_parser.cc"
    break;

  case 375: // $@63: %empty
#line 1503 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2661 "dhcp6_parser.cc"
    break;

  case 376: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1507 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 379: // subnet6_params: subnet6_params ","
#line 1516 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2679 "dhcp6_parser.cc"
    break;

  case 423: // $@64: %empty
#line 1567 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 424: // subnet: "subnet" $@64 ":" "constant string"
#line 1570 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2698 "dhcp6_parser.cc"
    break;

  case 425: // $@65: %empty
#line 1576 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 426: // interface: "interface" $@65 ":" "constant string"
#line 1579 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2717 "dhcp6_parser.cc"
    break;

  case 427: // $@66: %empty
#line 1585 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp6_parser.cc"
    break;

  case 428: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1588 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2736 "dhcp6_parser.cc"
    break;

  case 429: // $@67: %empty
#line 1594 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2745 "dhcp6_parser.cc"
    break;

  case 430: // client_class: "client-class" $@67 ":" "constant string"
#line 1597 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2755 "dhcp6_parser.cc"
    break;

  case 431: // $@68: %empty
#line 1603 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2767 "dhcp6_parser.cc"
    break;

  case 432: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1609 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 433: // reservations_global: "reservations-global" ":" "boolean"
#line 1614 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 434: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1620 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 435: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1626 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2806 "dhcp6_parser.cc"
    break;

  case 436: // $@69: %empty
#line 1632 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2815 "dhcp6_parser.cc"
    break;

  case 437: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1635 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 438: // hr_mode: "disabled"
#line 1640 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2830 "dhcp6_parser.cc"
    break;

  case 439: // hr_mode: "out-of-pool"
#line 1641 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2836 "dhcp6_parser.cc"
    break;

  case 440: // hr_mode: "global"
#line 1642 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2842 "dhcp6_parser.cc"
    break;

  case 441: // hr_mode: "all"
#line 1643 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2848 "dhcp6_parser.cc"
    break;

  case 442: // id: "id" ":" "integer"
#line 1646 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 443: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1652 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 444: // $@70: %empty
#line 1660 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2880 "dhcp6_parser.cc"
    break;

  case 445: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1666 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2889 "dhcp6_parser.cc"
    break;

  case 450: // shared_networks_list: shared_networks_list ","
#line 1679 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2897 "dhcp6_parser.cc"
    break;

  case 451: // $@71: %empty
#line 1684 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2907 "dhcp6_parser.cc"
    break;

  case 452: // shared_network: "{" $@71 shared_network_params "}"
#line 1688 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 455: // shared_network_params: shared_network_params ","
#line 1694 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2923 "dhcp6_parser.cc"
    break;

  case 496: // $@72: %empty
#line 1745 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 497: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1751 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2944 "dhcp6_parser.cc"
    break;

  case 498: // $@73: %empty
#line 1759 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 499: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1762 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2961 "dhcp6_parser.cc"
    break;

  case 504: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1774 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2969 "dhcp6_parser.cc"
    break;

  case 505: // $@74: %empty
#line 1781 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2979 "dhcp6_parser.cc"
    break;

  case 506: // option_def_entry: "{" $@74 option_def_params "}"
#line 1785 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2991 "dhcp6_parser.cc"
    break;

  case 507: // $@75: %empty
#line 1796 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3001 "dhcp6_parser.cc"
    break;

  case 508: // sub_option_def: "{" $@75 option_def_params "}"
#line 1800 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3013 "dhcp6_parser.cc"
    break;

  case 513: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1816 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3021 "dhcp6_parser.cc"
    break;

  case 525: // code: "code" ":" "integer"
#line 1835 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3031 "dhcp6_parser.cc"
    break;

  case 527: // $@76: %empty
#line 1843 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3040 "dhcp6_parser.cc"
    break;

  case 528: // option_def_type: "type" $@76 ":" "constant string"
#line 1846 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3050 "dhcp6_parser.cc"
    break;

  case 529: // $@77: %empty
#line 1852 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3059 "dhcp6_parser.cc"
    break;

  case 530: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1855 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3069 "dhcp6_parser.cc"
    break;

  case 531: // $@78: %empty
#line 1861 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3078 "dhcp6_parser.cc"
    break;

  case 532: // space: "space" $@78 ":" "constant string"
#line 1864 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3088 "dhcp6_parser.cc"
    break;

  case 534: // $@79: %empty
#line 1872 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3097 "dhcp6_parser.cc"
    break;

  case 535: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1875 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3107 "dhcp6_parser.cc"
    break;

  case 536: // option_def_array: "array" ":" "boolean"
#line 1881 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3117 "dhcp6_parser.cc"
    break;

  case 537: // $@80: %empty
#line 1891 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3129 "dhcp6_parser.cc"
    break;

  case 538: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1897 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3138 "dhcp6_parser.cc"
    break;

  case 543: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1912 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3146 "dhcp6_parser.cc"
    break;

  case 544: // $@81: %empty
#line 1919 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3156 "dhcp6_parser.cc"
    break;

  case 545: // option_data_entry: "{" $@81 option_data_params "}"
#line 1923 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3165 "dhcp6_parser.cc"
    break;

  case 546: // $@82: %empty
#line 1931 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 547: // sub_option_data: "{" $@82 option_data_params "}"
#line 1935 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3184 "dhcp6_parser.cc"
    break;

  case 552: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1951 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3192 "dhcp6_parser.cc"
    break;

  case 563: // $@83: %empty
#line 1971 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 564: // option_data_data: "data" $@83 ":" "constant string"
#line 1974 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 567: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1984 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 568: // option_data_always_send: "always-send" ":" "boolean"
#line 1990 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 569: // $@84: %empty
#line 1999 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3243 "dhcp6_parser.cc"
    break;

  case 570: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2005 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3252 "dhcp6_parser.cc"
    break;

  case 575: // not_empty_pools_list: not_empty_pools_list ","
#line 2018 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3260 "dhcp6_parser.cc"
    break;

  case 576: // $@85: %empty
#line 2023 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3270 "dhcp6_parser.cc"
    break;

  case 577: // pool_list_entry: "{" $@85 pool_params "}"
#line 2027 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3280 "dhcp6_parser.cc"
    break;

  case 578: // $@86: %empty
#line 2033 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3290 "dhcp6_parser.cc"
    break;

  case 579: // sub_pool6: "{" $@86 pool_params "}"
#line 2037 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3300 "dhcp6_parser.cc"
    break;

  case 582: // pool_params: pool_params ","
#line 2045 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3308 "dhcp6_parser.cc"
    break;

  case 590: // $@87: %empty
#line 2059 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3317 "dhcp6_parser.cc"
    break;

  case 591: // pool_entry: "pool" $@87 ":" "constant string"
#line 2062 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 592: // $@88: %empty
#line 2068 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 593: // user_context: "user-context" $@88 ":" map_value
#line 2070 "dhcp6_parser.yy"
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
#line 3362 "dhcp6_parser.cc"
    break;

  case 594: // $@89: %empty
#line 2093 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3370 "dhcp6_parser.cc"
    break;

  case 595: // comment: "comment" $@89 ":" "constant string"
#line 2095 "dhcp6_parser.yy"
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
#line 3399 "dhcp6_parser.cc"
    break;

  case 596: // $@90: %empty
#line 2123 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3411 "dhcp6_parser.cc"
    break;

  case 597: // pd_pools_list: "pd-pools" $@90 ":" "[" pd_pools_list_content "]"
#line 2129 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 602: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2142 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3428 "dhcp6_parser.cc"
    break;

  case 603: // $@91: %empty
#line 2147 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 604: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2151 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 605: // $@92: %empty
#line 2159 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 606: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2163 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3472 "dhcp6_parser.cc"
    break;

  case 609: // pd_pool_params: pd_pool_params ","
#line 2173 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3480 "dhcp6_parser.cc"
    break;

  case 621: // $@93: %empty
#line 2191 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3489 "dhcp6_parser.cc"
    break;

  case 622: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2194 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 623: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2200 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 624: // $@94: %empty
#line 2206 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 625: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2209 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 626: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2215 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 627: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2221 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3548 "dhcp6_parser.cc"
    break;

  case 628: // $@95: %empty
#line 2230 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 629: // reservations: "reservations" $@95 ":" "[" reservations_list "]"
#line 2236 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3569 "dhcp6_parser.cc"
    break;

  case 634: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2247 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3577 "dhcp6_parser.cc"
    break;

  case 635: // $@96: %empty
#line 2252 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3587 "dhcp6_parser.cc"
    break;

  case 636: // reservation: "{" $@96 reservation_params "}"
#line 2256 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 637: // $@97: %empty
#line 2261 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 638: // sub_reservation: "{" $@97 reservation_params "}"
#line 2265 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3615 "dhcp6_parser.cc"
    break;

  case 643: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2276 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3623 "dhcp6_parser.cc"
    break;

  case 655: // $@98: %empty
#line 2295 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp6_parser.cc"
    break;

  case 656: // ip_addresses: "ip-addresses" $@98 ":" list_strings
#line 2301 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3644 "dhcp6_parser.cc"
    break;

  case 657: // $@99: %empty
#line 2306 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 658: // prefixes: "prefixes" $@99 ":" list_strings
#line 2312 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3665 "dhcp6_parser.cc"
    break;

  case 659: // $@100: %empty
#line 2317 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3674 "dhcp6_parser.cc"
    break;

  case 660: // duid: "duid" $@100 ":" "constant string"
#line 2320 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 661: // $@101: %empty
#line 2326 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3693 "dhcp6_parser.cc"
    break;

  case 662: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2329 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3703 "dhcp6_parser.cc"
    break;

  case 663: // $@102: %empty
#line 2335 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3712 "dhcp6_parser.cc"
    break;

  case 664: // hostname: "hostname" $@102 ":" "constant string"
#line 2338 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3722 "dhcp6_parser.cc"
    break;

  case 665: // $@103: %empty
#line 2344 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3731 "dhcp6_parser.cc"
    break;

  case 666: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2347 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3741 "dhcp6_parser.cc"
    break;

  case 667: // $@104: %empty
#line 2353 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3753 "dhcp6_parser.cc"
    break;

  case 668: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2359 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3762 "dhcp6_parser.cc"
    break;

  case 669: // $@105: %empty
#line 2367 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3774 "dhcp6_parser.cc"
    break;

  case 670: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2373 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3783 "dhcp6_parser.cc"
    break;

  case 673: // $@106: %empty
#line 2382 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3792 "dhcp6_parser.cc"
    break;

  case 674: // ip_address: "ip-address" $@106 ":" "constant string"
#line 2385 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 675: // $@107: %empty
#line 2394 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 676: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2400 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3823 "dhcp6_parser.cc"
    break;

  case 679: // client_classes_list: client_classes_list ","
#line 2407 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3831 "dhcp6_parser.cc"
    break;

  case 680: // $@108: %empty
#line 2412 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3841 "dhcp6_parser.cc"
    break;

  case 681: // client_class_entry: "{" $@108 client_class_params "}"
#line 2416 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3851 "dhcp6_parser.cc"
    break;

  case 686: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2428 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3859 "dhcp6_parser.cc"
    break;

  case 701: // $@109: %empty
#line 2450 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3868 "dhcp6_parser.cc"
    break;

  case 702: // client_class_test: "test" $@109 ":" "constant string"
#line 2453 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3878 "dhcp6_parser.cc"
    break;

  case 703: // only_if_required: "only-if-required" ":" "boolean"
#line 2459 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3888 "dhcp6_parser.cc"
    break;

  case 704: // $@110: %empty
#line 2468 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3900 "dhcp6_parser.cc"
    break;

  case 705: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2474 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 708: // server_id_params: server_id_params ","
#line 2483 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3919 "dhcp6_parser.cc"
    break;

  case 718: // $@111: %empty
#line 2499 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 719: // server_id_type: "type" $@111 ":" duid_type
#line 2502 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3937 "dhcp6_parser.cc"
    break;

  case 720: // duid_type: "LLT"
#line 2507 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3943 "dhcp6_parser.cc"
    break;

  case 721: // duid_type: "EN"
#line 2508 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3949 "dhcp6_parser.cc"
    break;

  case 722: // duid_type: "LL"
#line 2509 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3955 "dhcp6_parser.cc"
    break;

  case 723: // htype: "htype" ":" "integer"
#line 2512 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3965 "dhcp6_parser.cc"
    break;

  case 724: // $@112: %empty
#line 2518 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 725: // identifier: "identifier" $@112 ":" "constant string"
#line 2521 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 726: // time: "time" ":" "integer"
#line 2527 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3994 "dhcp6_parser.cc"
    break;

  case 727: // enterprise_id: "enterprise-id" ":" "integer"
#line 2533 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4004 "dhcp6_parser.cc"
    break;

  case 728: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2541 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4014 "dhcp6_parser.cc"
    break;

  case 729: // $@113: %empty
#line 2549 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4026 "dhcp6_parser.cc"
    break;

  case 730: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2555 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4035 "dhcp6_parser.cc"
    break;

  case 733: // control_socket_params: control_socket_params ","
#line 2562 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4043 "dhcp6_parser.cc"
    break;

  case 739: // $@114: %empty
#line 2574 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 740: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2577 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 741: // $@115: %empty
#line 2583 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 742: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2586 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 743: // $@116: %empty
#line 2595 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4093 "dhcp6_parser.cc"
    break;

  case 744: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2601 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4104 "dhcp6_parser.cc"
    break;

  case 747: // queue_control_params: queue_control_params ","
#line 2610 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4112 "dhcp6_parser.cc"
    break;

  case 754: // enable_queue: "enable-queue" ":" "boolean"
#line 2623 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4122 "dhcp6_parser.cc"
    break;

  case 755: // $@117: %empty
#line 2629 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4131 "dhcp6_parser.cc"
    break;

  case 756: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2632 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4141 "dhcp6_parser.cc"
    break;

  case 757: // capacity: "capacity" ":" "integer"
#line 2638 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4151 "dhcp6_parser.cc"
    break;

  case 758: // $@118: %empty
#line 2644 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4160 "dhcp6_parser.cc"
    break;

  case 759: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2647 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4169 "dhcp6_parser.cc"
    break;

  case 760: // $@119: %empty
#line 2654 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4181 "dhcp6_parser.cc"
    break;

  case 761: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2660 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4192 "dhcp6_parser.cc"
    break;

  case 762: // $@120: %empty
#line 2667 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4202 "dhcp6_parser.cc"
    break;

  case 763: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2671 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4212 "dhcp6_parser.cc"
    break;

  case 766: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2679 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4220 "dhcp6_parser.cc"
    break;

  case 785: // enable_updates: "enable-updates" ":" "boolean"
#line 2704 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4230 "dhcp6_parser.cc"
    break;

  case 786: // $@121: %empty
#line 2711 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4239 "dhcp6_parser.cc"
    break;

  case 787: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2714 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4249 "dhcp6_parser.cc"
    break;

  case 788: // $@122: %empty
#line 2720 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4258 "dhcp6_parser.cc"
    break;

  case 789: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2723 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4268 "dhcp6_parser.cc"
    break;

  case 790: // server_port: "server-port" ":" "integer"
#line 2729 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4278 "dhcp6_parser.cc"
    break;

  case 791: // $@123: %empty
#line 2735 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4287 "dhcp6_parser.cc"
    break;

  case 792: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2738 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 793: // sender_port: "sender-port" ":" "integer"
#line 2744 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4307 "dhcp6_parser.cc"
    break;

  case 794: // max_queue_size: "max-queue-size" ":" "integer"
#line 2750 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4317 "dhcp6_parser.cc"
    break;

  case 795: // $@124: %empty
#line 2756 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4326 "dhcp6_parser.cc"
    break;

  case 796: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2759 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4335 "dhcp6_parser.cc"
    break;

  case 797: // ncr_protocol_value: "UDP"
#line 2765 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4341 "dhcp6_parser.cc"
    break;

  case 798: // ncr_protocol_value: "TCP"
#line 2766 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4347 "dhcp6_parser.cc"
    break;

  case 799: // $@125: %empty
#line 2769 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4356 "dhcp6_parser.cc"
    break;

  case 800: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2772 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 801: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2779 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4376 "dhcp6_parser.cc"
    break;

  case 802: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2786 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4386 "dhcp6_parser.cc"
    break;

  case 803: // $@126: %empty
#line 2793 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4395 "dhcp6_parser.cc"
    break;

  case 804: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2796 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4404 "dhcp6_parser.cc"
    break;

  case 805: // $@127: %empty
#line 2802 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4413 "dhcp6_parser.cc"
    break;

  case 806: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2805 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4423 "dhcp6_parser.cc"
    break;

  case 807: // $@128: %empty
#line 2812 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4432 "dhcp6_parser.cc"
    break;

  case 808: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2815 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4442 "dhcp6_parser.cc"
    break;

  case 809: // $@129: %empty
#line 2822 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4451 "dhcp6_parser.cc"
    break;

  case 810: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2825 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4461 "dhcp6_parser.cc"
    break;

  case 811: // $@130: %empty
#line 2834 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4473 "dhcp6_parser.cc"
    break;

  case 812: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2840 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4483 "dhcp6_parser.cc"
    break;

  case 813: // $@131: %empty
#line 2846 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4493 "dhcp6_parser.cc"
    break;

  case 814: // sub_config_control: "{" $@131 config_control_params "}"
#line 2850 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4502 "dhcp6_parser.cc"
    break;

  case 817: // config_control_params: config_control_params ","
#line 2858 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4510 "dhcp6_parser.cc"
    break;

  case 820: // $@132: %empty
#line 2868 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4522 "dhcp6_parser.cc"
    break;

  case 821: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2874 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 822: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2879 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4541 "dhcp6_parser.cc"
    break;

  case 823: // $@133: %empty
#line 2887 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 824: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2893 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4562 "dhcp6_parser.cc"
    break;

  case 827: // loggers_entries: loggers_entries ","
#line 2902 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4570 "dhcp6_parser.cc"
    break;

  case 828: // $@134: %empty
#line 2908 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4580 "dhcp6_parser.cc"
    break;

  case 829: // logger_entry: "{" $@134 logger_params "}"
#line 2912 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4588 "dhcp6_parser.cc"
    break;

  case 832: // logger_params: logger_params ","
#line 2918 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4596 "dhcp6_parser.cc"
    break;

  case 840: // debuglevel: "debuglevel" ":" "integer"
#line 2932 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4606 "dhcp6_parser.cc"
    break;

  case 841: // $@135: %empty
#line 2938 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4615 "dhcp6_parser.cc"
    break;

  case 842: // severity: "severity" $@135 ":" "constant string"
#line 2941 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4625 "dhcp6_parser.cc"
    break;

  case 843: // $@136: %empty
#line 2947 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4637 "dhcp6_parser.cc"
    break;

  case 844: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 2953 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4646 "dhcp6_parser.cc"
    break;

  case 847: // output_options_list_content: output_options_list_content ","
#line 2960 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4654 "dhcp6_parser.cc"
    break;

  case 848: // $@137: %empty
#line 2965 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4664 "dhcp6_parser.cc"
    break;

  case 849: // output_entry: "{" $@137 output_params_list "}"
#line 2969 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4672 "dhcp6_parser.cc"
    break;

  case 852: // output_params_list: output_params_list ","
#line 2975 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4680 "dhcp6_parser.cc"
    break;

  case 858: // $@138: %empty
#line 2987 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4689 "dhcp6_parser.cc"
    break;

  case 859: // output: "output" $@138 ":" "constant string"
#line 2990 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4699 "dhcp6_parser.cc"
    break;

  case 860: // flush: "flush" ":" "boolean"
#line 2996 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 861: // maxsize: "maxsize" ":" "integer"
#line 3002 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4719 "dhcp6_parser.cc"
    break;

  case 862: // maxver: "maxver" ":" "integer"
#line 3008 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4729 "dhcp6_parser.cc"
    break;

  case 863: // $@139: %empty
#line 3014 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 864: // pattern: "pattern" $@139 ":" "constant string"
#line 3017 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4748 "dhcp6_parser.cc"
    break;

  case 865: // $@140: %empty
#line 3023 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4760 "dhcp6_parser.cc"
    break;

  case 866: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3029 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4769 "dhcp6_parser.cc"
    break;

  case 869: // compatibility_params: compatibility_params ","
#line 3036 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4777 "dhcp6_parser.cc"
    break;

  case 872: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3045 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4787 "dhcp6_parser.cc"
    break;


#line 4791 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1005;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     423, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,    48,    30,    31,    58,    61,
      77,    84,    94,   106,   123,   133,   137,   158,   160,   176,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,    30,   -81,
     181,   142,    36,   651,   197,   212,    51,   114,    15,   290,
     -95,   437,    44, -1005,   217,   228,   248,   253,   267, -1005,
      46, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   270,   283,
     300,   333,   352,   354,   366,   376,   377,   384,   385,   410,
     422,   424, -1005,   428,   430,   431,   439,   440, -1005, -1005,
   -1005,   442,   443,   446, -1005, -1005, -1005,   447, -1005, -1005,
   -1005, -1005,   450,   458,   459, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,   462, -1005, -1005, -1005, -1005, -1005,
   -1005,   463,   464,   465, -1005, -1005,   466, -1005,    78, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,   468, -1005,    79, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   470,   472,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,    80, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,    87, -1005, -1005, -1005, -1005, -1005,   473,
   -1005,   474,   475, -1005, -1005, -1005, -1005, -1005, -1005,    97,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,   293,   331, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,   409, -1005, -1005,
     478, -1005, -1005, -1005,   479, -1005, -1005,   485,   491, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   493,   494, -1005, -1005, -1005, -1005,   487,   496,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   109, -1005, -1005, -1005,   499, -1005, -1005,   504,
   -1005,   505,   506, -1005, -1005,   507,   508, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,   130, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   509,   138, -1005, -1005, -1005, -1005,    30,    30,
   -1005,   302,   511, -1005, -1005,   514,   515,   517,   518,   521,
     522,   315,   325,   326,   327,   328,   336,   339,   340,   309,
     329,   334,   341,   344,   345,   525,   346,   347,   348,   349,
     351,   543,   544,   560,   355,   356,   358,   573,   575,   576,
     365,   579,   580,   583,   585,   372,   373,   375,   591,   592,
     593,   594,   596,   611,   612,   613,   614,   403,   616,   617,
     634,   635,   637,   638,   426,   427,   429,   642,   644, -1005,
     142, -1005,   645,   432,    36, -1005,   647,   649,   650,   652,
     653,   444,   445,   654,   657,   658,   651, -1005,   660,   197,
   -1005,   661,   451,   662,   452,   453,   212, -1005,   666,   667,
     668,   669,   670,   671,   675, -1005,    51, -1005,   677,   678,
     467,   681,   682,   683,   471, -1005,    15,   684,   480,   481,
   -1005,   290,   686,   687,   189, -1005,   483,   693,   712,   501,
     714,   503,   513,   726,   728,   516,   523,   729,   736,   740,
     742,   437, -1005,   743,   526,    44, -1005, -1005, -1005,   744,
     648,   534,   752,   753,   754,   755,   745, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,   551, -1005, -1005, -1005, -1005, -1005,  -110,   552,   553,
   -1005, -1005, -1005,   764,   765,   766, -1005,   768,   767,   562,
     314, -1005, -1005, -1005,   773,   774,   775,   777,   776,   780,
     781,   782,   796, -1005,   797,   798,   799,   810,   567,   572,
   -1005, -1005, -1005,   783,   813, -1005,   816, -1005, -1005,   817,
     818,   609,   610,   615, -1005, -1005,   816,   618,   819, -1005,
     619, -1005,   620, -1005,   625, -1005, -1005, -1005,   816,   816,
     816,   628,   631,   632,   633, -1005,   639,   640, -1005,   641,
     643,   646, -1005, -1005,   656, -1005, -1005, -1005,   659,   767,
   -1005, -1005,   663,   664, -1005,   665, -1005, -1005,   199,   673,
   -1005, -1005,  -110,   672,   674,   676, -1005,   822, -1005, -1005,
      30,   142, -1005,    44,    36,   318,   318,   821, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,   824,   825,   842,
     850, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   -96,
      30,    -5,   710,   853,   856,   857,   254,    88,   127,   164,
      63,   437, -1005, -1005,   858,  -145, -1005, -1005,   860,   861,
   -1005, -1005, -1005, -1005, -1005,   -82, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,   821, -1005,   184,   226,   232,
   -1005, -1005, -1005, -1005,   865,   868,   869,   871,   872, -1005,
     873,   877, -1005, -1005, -1005, -1005,   878,   879,   880,   881,
   -1005, -1005, -1005, -1005, -1005,   260, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   277, -1005,   882,   883, -1005, -1005,   884,   889,
   -1005, -1005,   887,   891, -1005, -1005,   890,   892, -1005, -1005,
     893,   894, -1005, -1005, -1005,    91, -1005, -1005, -1005,   895,
   -1005, -1005, -1005,   152, -1005, -1005, -1005, -1005,   281, -1005,
   -1005, -1005,   153, -1005, -1005,   896,   897, -1005, -1005,   898,
     900, -1005,   901,   902,   903,   904,   905,   906,   285, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   907,   908,
     909, -1005, -1005, -1005, -1005,   288, -1005, -1005, -1005, -1005,
   -1005, -1005,   910,   911,   912, -1005,   297, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   311, -1005,
   -1005, -1005,   913, -1005,   914, -1005, -1005, -1005,   312, -1005,
   -1005, -1005, -1005, -1005,   332, -1005,   238, -1005,   915, -1005,
     335, -1005, -1005,   705, -1005,   916,   918, -1005, -1005,   919,
     923, -1005, -1005, -1005,   920, -1005,   921, -1005, -1005, -1005,
     925,   926,   927,   928,   717,   680,   718,   719,   720,   931,
     722,   723,   936,   937,   938,   939,   730,   731,   727,   732,
     940,   946,   947,   950,   318, -1005, -1005,   318, -1005,   821,
     651, -1005,   824,    15, -1005,   825,   290, -1005,   842,   738,
   -1005,   850,   -96, -1005, -1005,    -5, -1005,   952,   710, -1005,
     330,   853, -1005,    51, -1005,   856,   -95, -1005,   857,   741,
     747,   748,   750,   751,   757,   254, -1005,   972,   975,   771,
     788,   789,    88, -1005,   762,   794,   803,   127, -1005,   978,
     979,   164, -1005,   802,  1019,   811,  1025,    63, -1005, -1005,
     -25,   858, -1005,   812,  -145, -1005, -1005,  1032,  1039,   197,
   -1005,   860,   212, -1005,   861,  1042, -1005, -1005,   414,   828,
     836,   849, -1005, -1005, -1005, -1005, -1005,   885, -1005, -1005,
     402,   888,   899,   917, -1005, -1005, -1005, -1005,   922,   924,
     929,   930, -1005,   395, -1005,   397, -1005,  1063, -1005,  1079,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,   398, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   932, -1005, -1005,  1090,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,  1089,  1102, -1005, -1005, -1005, -1005, -1005,  1098, -1005,
     399, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   313,
     933, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   934,
     935, -1005, -1005,   941, -1005,    30, -1005, -1005,  1103, -1005,
   -1005, -1005, -1005, -1005,   401, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   942,   405, -1005,   412, -1005,   943, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   738, -1005, -1005,  1104,   945, -1005,   330,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,  1105,   944,  1106,   -25, -1005, -1005, -1005, -1005, -1005,
   -1005,   951, -1005, -1005,  1107, -1005,   953, -1005, -1005,  1108,
   -1005, -1005,   247, -1005,   -22,  1108, -1005, -1005,  1109,  1112,
    1113, -1005,   413, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
    1114,   954,   955,   957,  1115,   -22, -1005,   959, -1005, -1005,
   -1005,   960, -1005, -1005, -1005
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   184,     9,   375,    11,
     578,    13,   605,    15,   637,    17,   498,    19,   507,    21,
     546,    23,   337,    25,   762,    27,   813,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   639,     0,   509,   548,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   137,   811,   182,   197,   199,   201,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   156,   163,
     165,     0,     0,     0,   366,   496,   537,     0,   444,   592,
     594,   436,     0,     0,     0,   293,   312,   302,   285,   675,
     628,   328,   349,   704,     0,   314,   729,   743,   760,   169,
     171,     0,     0,     0,   823,   865,     0,   136,     0,    69,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   117,   118,   127,   128,   129,   106,   135,
     131,   132,   133,    84,    85,    86,    87,   103,    88,    90,
      89,   130,    94,    95,    82,   108,   109,   110,   107,    83,
      92,    93,   101,   102,   104,    91,    96,    97,    98,    99,
     100,   105,   116,   134,   194,     0,   193,     0,   186,   189,
     190,   191,   192,   569,   596,   423,   425,   427,     0,     0,
     431,   429,   669,   422,   380,   381,   382,   383,   384,   385,
     386,   387,   406,   407,   408,   409,   410,   413,   414,   415,
     416,   417,   418,   419,   420,   411,   412,   421,     0,   377,
     391,   392,   393,   396,   397,   400,   401,   402,   399,   394,
     395,   388,   389,   404,   405,   390,   398,   403,   590,   589,
     585,   586,   584,     0,   580,   583,   587,   588,   621,     0,
     624,     0,     0,   620,   614,   615,   613,   618,   619,     0,
     607,   610,   611,   616,   617,   612,   667,   655,   657,   659,
     661,   663,   665,   654,   651,   652,   653,     0,   640,   641,
     646,   647,   644,   648,   649,   650,   645,     0,   527,   252,
       0,   531,   529,   534,     0,   523,   524,     0,   510,   511,
     514,   526,   515,   516,   517,   533,   518,   519,   520,   521,
     522,   563,     0,     0,   561,   562,   565,   566,     0,   549,
     550,   553,   554,   555,   556,   557,   558,   559,   560,   345,
     347,   342,     0,   339,   343,   344,     0,   786,   788,     0,
     791,     0,     0,   795,   799,     0,     0,   803,   805,   807,
     809,   784,   782,   783,     0,   764,   767,   779,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   780,
     781,   820,     0,     0,   815,   818,   819,    47,    52,     0,
      39,    45,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      71,    68,     0,     0,   188,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   379,   376,     0,   582,
     579,     0,     0,     0,     0,     0,   609,   606,     0,     0,
       0,     0,     0,     0,     0,   638,   643,   499,     0,     0,
       0,     0,     0,     0,     0,   508,   513,     0,     0,     0,
     547,   552,     0,     0,   341,   338,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   766,   763,     0,     0,   817,   814,    51,    43,     0,
       0,     0,     0,     0,     0,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,   174,   175,   153,   154,   155,     0,     0,     0,
     167,   168,   173,     0,     0,     0,   178,     0,     0,     0,
       0,   433,   434,   435,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   728,     0,     0,     0,     0,     0,     0,
     179,   180,   181,     0,     0,    70,     0,   196,   187,     0,
       0,     0,     0,     0,   442,   443,     0,     0,     0,   378,
       0,   581,     0,   623,     0,   626,   627,   608,     0,     0,
       0,     0,     0,     0,     0,   642,     0,     0,   525,     0,
       0,     0,   536,   512,     0,   567,   568,   551,     0,     0,
     340,   785,     0,     0,   790,     0,   793,   794,     0,     0,
     801,   802,     0,     0,     0,     0,   765,     0,   822,   816,
       0,     0,   138,     0,     0,     0,     0,   203,   177,   158,
     159,   160,   161,   162,   157,   164,   166,   368,   500,   539,
     446,    40,   593,   595,   438,   439,   440,   441,   437,     0,
      48,     0,     0,     0,   630,   330,     0,     0,     0,     0,
       0,     0,   170,   172,     0,     0,    53,   195,   571,   598,
     424,   426,   428,   432,   430,     0,   591,   622,   625,   668,
     656,   658,   660,   662,   664,   666,   528,   253,   532,   530,
     535,   564,   346,   348,   787,   789,   792,   797,   798,   796,
     800,   804,   806,   808,   810,   203,    44,     0,     0,     0,
     239,   245,   247,   249,     0,     0,     0,     0,     0,   268,
       0,     0,   259,   271,   273,   275,     0,     0,     0,     0,
     277,   279,   281,   283,   238,     0,   210,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   225,   226,   233,
     227,   228,   229,   223,   224,   230,   231,   232,   234,   235,
     236,   237,     0,   208,     0,   204,   205,   373,     0,   369,
     370,   505,     0,   501,   502,   544,     0,   540,   541,   451,
       0,   447,   448,   300,   301,     0,   295,   298,   299,     0,
     310,   311,   307,     0,   304,   308,   309,   291,     0,   287,
     290,   680,     0,   677,   635,     0,   631,   632,   335,     0,
     331,   332,     0,     0,     0,     0,     0,     0,     0,   351,
     354,   355,   356,   357,   358,   359,   718,   724,     0,     0,
       0,   717,   714,   715,   716,     0,   706,   709,   712,   710,
     711,   713,     0,     0,     0,   324,     0,   316,   319,   320,
     321,   322,   323,   739,   741,   738,   736,   737,     0,   731,
     734,   735,     0,   755,     0,   758,   751,   752,     0,   745,
     748,   749,   750,   753,     0,   828,     0,   825,     0,   871,
       0,   867,   870,    55,   576,     0,   572,   573,   603,     0,
     599,   600,   673,   672,     0,   671,     0,    64,   812,   183,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   212,   198,   200,     0,   202,   207,
       0,   367,   372,   509,   497,   504,   548,   538,   543,     0,
     445,   450,   297,   294,   313,   306,   303,     0,   289,   286,
     682,   679,   676,   639,   629,   634,     0,   329,   334,     0,
       0,     0,     0,     0,     0,   353,   350,     0,     0,     0,
       0,     0,   708,   705,     0,     0,     0,   318,   315,     0,
       0,   733,   730,     0,     0,     0,     0,   747,   744,   761,
       0,   827,   824,     0,   869,   866,    57,     0,    56,     0,
     570,   575,     0,   597,   602,     0,   670,   821,     0,     0,
       0,     0,   251,   254,   255,   256,   257,     0,   270,   258,
       0,     0,     0,     0,   265,   266,   267,   264,     0,     0,
       0,     0,   211,     0,   206,     0,   371,     0,   503,     0,
     542,   495,   470,   471,   472,   474,   475,   476,   460,   461,
     479,   480,   481,   482,   483,   486,   487,   488,   489,   490,
     491,   492,   493,   484,   485,   494,   456,   457,   458,   459,
     468,   469,   465,   466,   467,   464,   473,     0,   453,   462,
     477,   478,   463,   449,   296,   305,     0,   288,   701,     0,
     699,   693,   694,   695,   696,   697,   698,   700,   690,   691,
     692,     0,   683,   684,   687,   688,   689,   678,     0,   633,
       0,   333,   360,   361,   362,   363,   364,   365,   352,     0,
       0,   723,   726,   727,   707,   325,   326,   327,   317,     0,
       0,   732,   754,     0,   757,     0,   746,   843,     0,   841,
     839,   833,   837,   838,     0,   830,   835,   836,   834,   826,
     872,   868,    54,    59,     0,   574,     0,   601,     0,   241,
     242,   243,   244,   240,   246,   248,   250,   269,   261,   262,
     263,   260,   272,   274,   276,   278,   280,   282,   284,   209,
     374,   506,   545,   455,   452,   292,     0,     0,   681,   686,
     636,   336,   720,   721,   722,   719,   725,   740,   742,   756,
     759,     0,     0,     0,   832,   829,    58,   577,   604,   674,
     454,     0,   703,   685,     0,   840,     0,   831,   702,     0,
     842,   848,     0,   845,     0,   847,   844,   858,     0,     0,
       0,   863,     0,   850,   853,   854,   855,   856,   857,   846,
       0,     0,     0,     0,     0,   852,   849,     0,   860,   861,
     862,     0,   851,   859,   864
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   -10, -1005,  -568, -1005,
     433, -1005, -1005, -1005, -1005,   371, -1005,  -484, -1005, -1005,
   -1005,   -71, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   415,
     621, -1005, -1005,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19, -1005,    34,    37,    38,
      41, -1005,   418,    49, -1005,    52, -1005,    54,    55,    56,
   -1005,    59, -1005,    62, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   411,   623, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,   338, -1005,   104,
   -1005,  -700,   110, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   -45, -1005,  -736, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,    90, -1005, -1005,
   -1005, -1005, -1005,    98,  -719, -1005, -1005, -1005, -1005,    96,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,    67, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,    81, -1005, -1005, -1005,    89,
     582, -1005, -1005, -1005, -1005, -1005, -1005, -1005,    83, -1005,
   -1005, -1005, -1005, -1005, -1005, -1004, -1005, -1005, -1005,   118,
   -1005, -1005, -1005,   121,   626, -1005, -1005, -1002, -1005, -1001,
   -1005,    73, -1005,    75, -1005,    66,    69,    70,    72, -1005,
   -1005, -1005, -1000, -1005, -1005, -1005, -1005,   112, -1005, -1005,
    -127,  1074, -1005, -1005, -1005, -1005, -1005,   128, -1005, -1005,
   -1005,   129, -1005,   608, -1005,   -67, -1005, -1005, -1005, -1005,
   -1005,   -64, -1005, -1005, -1005, -1005, -1005,     4, -1005, -1005,
   -1005,   131, -1005, -1005, -1005,   135, -1005,   604, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,    85,
   -1005, -1005, -1005,    92,   679, -1005, -1005,   -55, -1005,   -12,
   -1005, -1005, -1005, -1005, -1005,    76, -1005, -1005, -1005,    86,
     685, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   -60, -1005,
   -1005, -1005,   124, -1005, -1005, -1005,   134, -1005,   655,   417,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,  -998, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,   139, -1005, -1005, -1005,  -100, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   122, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   115, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,   108, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,   436,   622, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   476,   624, -1005, -1005,
   -1005, -1005, -1005, -1005,   102, -1005, -1005,  -106, -1005, -1005,
   -1005, -1005, -1005, -1005,  -125, -1005, -1005,  -143, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   111, -1005
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     732,    87,    88,    41,    68,    84,    85,   757,   973,  1087,
    1088,   824,    43,    70,    90,   432,    91,    45,    71,   158,
     159,   160,   435,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   461,   724,   179,   462,   180,   463,   181,   182,   183,
     492,   184,   493,   185,   186,   187,   188,   455,   189,   190,
     191,   192,   193,   437,    47,    72,   227,   228,   229,   502,
     230,   194,   438,   195,   439,   196,   440,   854,   855,   856,
    1017,   825,   826,   827,   990,  1253,   828,   991,   829,   992,
     830,   993,   831,   832,   539,   833,   834,   835,   836,   837,
     838,  1002,  1261,   839,   840,   841,   842,   843,   999,   844,
     845,  1003,   846,  1004,   847,  1005,   848,  1010,   849,  1011,
     850,  1012,   851,  1013,   197,   481,   888,   889,   890,  1037,
     198,   478,   875,   876,   877,   878,   199,   480,   883,   884,
     885,   886,   200,   479,   201,   488,   936,   937,   938,   939,
     940,   202,   484,   899,   900,   901,  1046,    63,    80,   382,
     383,   384,   552,   385,   553,   203,   485,   908,   909,   910,
     911,   912,   913,   914,   915,   204,   467,   858,   859,   860,
    1020,    49,    73,   268,   269,   270,   508,   271,   509,   272,
     510,   273,   514,   274,   513,   205,   206,   207,   208,   474,
     738,   279,   280,   209,   471,   870,   871,   872,  1029,  1167,
    1168,   210,   468,    57,    77,   862,   863,   864,  1023,    59,
      78,   347,   348,   349,   350,   351,   352,   353,   538,   354,
     542,   355,   541,   356,   357,   543,   358,   211,   469,   866,
     867,   868,  1026,    61,    79,   368,   369,   370,   371,   372,
     547,   373,   374,   375,   376,   282,   506,   975,   976,   977,
    1089,    51,    74,   293,   294,   295,   518,   212,   472,   213,
     473,   285,   507,   979,   980,   981,  1092,    53,    75,   309,
     310,   311,   521,   312,   313,   523,   314,   315,   214,   483,
     895,   896,   897,  1043,    55,    76,   327,   328,   329,   330,
     529,   331,   530,   332,   531,   333,   532,   334,   533,   335,
     534,   336,   528,   287,   515,   984,   985,  1095,   215,   482,
     892,   893,  1040,  1191,  1192,  1193,  1194,  1195,  1276,  1196,
     216,   486,   925,   926,   927,  1057,  1285,   928,   929,  1058,
     930,   931,   217,   218,   489,   948,   949,   950,  1069,   951,
    1070,   219,   490,   958,   959,   960,   961,  1074,   962,   963,
    1076,   220,   491,    65,    81,   404,   405,   406,   407,   557,
     408,   558,   409,   410,   560,   411,   412,   413,   563,   789,
     414,   564,   415,   416,   417,   567,   418,   568,   419,   569,
     420,   570,   221,   436,    67,    82,   423,   424,   425,   573,
     426,   222,   497,   966,   967,  1080,  1234,  1235,  1236,  1237,
    1293,  1238,  1291,  1312,  1313,  1314,  1322,  1323,  1324,  1330,
    1325,  1326,  1327,  1328,  1334,   223,   498,   970,   971,   972
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     157,   226,   243,   289,   303,   323,    38,   345,   364,   381,
     401,   922,   366,   286,   250,   367,   852,   231,   283,   296,
     307,   325,   882,   359,   377,  1157,   402,  1158,  1159,  1166,
     244,  1172,   873,   346,   365,    31,   338,    32,    42,    33,
     379,   380,   251,   252,   317,   253,   254,   255,    30,   433,
     731,   982,   224,   225,   434,   968,   339,   421,   422,   245,
     232,   284,   297,   308,   326,    44,   360,   378,    46,   403,
     156,   719,   720,   721,   722,   129,   130,   281,   292,   306,
     324,   500,   504,   516,    48,   246,   501,   505,   517,   247,
     519,    50,   256,   248,  1032,   520,   339,  1033,   340,   341,
     526,    52,   342,   343,   344,   527,   249,   257,   723,   916,
     258,   259,   554,    54,   260,   129,   130,   555,   805,   874,
     156,   731,   261,   873,   880,   262,   881,   263,   264,   265,
      56,   126,   266,   571,    86,   267,   129,   130,   572,   275,
      58,   575,   276,   277,    60,   278,   576,   290,   304,   291,
     305,   129,   130,    92,    93,  1035,  1041,    94,  1036,  1042,
      95,    96,    97,   129,   130,    62,  1227,    64,  1228,  1229,
    1317,   316,   763,  1318,  1319,  1320,  1321,   317,   318,   319,
     320,   321,   322,    66,   769,   770,   771,   500,   129,   130,
     156,    89,   987,   125,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   427,   952,   953,   954,   129,   130,   575,
     156,   428,   127,   128,   988,   504,   917,   918,   919,   920,
     989,  1081,   129,   130,  1082,    34,    35,    36,    37,   131,
    1315,   156,   429,  1316,   132,   133,   134,   135,   136,   137,
     138,   430,   139,  1014,   129,   130,   156,   140,  1015,  1157,
     431,  1158,  1159,  1166,   441,  1172,   141,   126,   955,   142,
    1014,   932,   933,   934,  1038,  1016,   143,   442,  1055,  1039,
     288,  1062,   126,  1056,   144,   145,  1063,   129,   130,   146,
    1067,   535,   147,   156,   443,  1068,   148,   298,   299,   300,
     301,   302,   129,   130,  1071,  1077,   882,  1123,   240,  1072,
    1078,   241,   943,   944,   379,   380,   922,   149,   150,   151,
     152,   153,   154,   240,   536,   571,   241,   444,  1084,   800,
    1079,   155,   156,  1085,   801,   802,   803,   804,   805,   806,
     807,   808,   809,   810,   811,   812,   445,   156,   446,   813,
     814,   815,   816,   817,   818,   819,   820,   821,   822,   823,
     447,   339,   361,   340,   341,   362,   363,   787,   788,   156,
     448,   449,    98,    99,   100,   101,   102,   103,   450,   451,
     129,   130,   902,   903,   904,   905,   906,   907,  1014,   339,
     516,  1273,   554,  1269,  1294,  1270,  1274,  1281,   519,  1295,
     126,   339,   156,  1297,   452,   526,  1335,   537,   577,   578,
    1298,  1336,   734,   735,   736,   737,   453,   156,   454,   157,
     129,   130,   456,   226,   457,   458,  1249,  1250,  1251,  1252,
    1258,  1259,  1260,   459,   460,   243,   464,   465,   289,   231,
     466,   470,  1178,  1179,   475,   303,   286,   250,  1282,  1283,
    1284,   283,   476,   477,   296,   323,   487,   494,   495,   496,
     499,   307,   503,   244,   511,   345,   512,   522,   524,   525,
     364,   325,   540,   544,   366,   251,   252,   367,   253,   254,
     255,   359,   232,   545,   546,   550,   377,   548,   549,   551,
     401,   346,   245,   556,   284,   156,   365,   297,   559,   561,
     562,   565,   566,   574,   308,   580,   402,   579,   581,   582,
     281,   583,   584,   292,   326,   585,   586,   595,   246,   601,
     306,   587,   247,   156,   360,   256,   248,   129,   130,   378,
     324,   588,   589,   590,   591,   156,   596,   607,   608,   249,
     257,   597,   592,   258,   259,   593,   594,   260,   598,   403,
     599,   600,   602,   603,   609,   261,   604,   605,   262,   606,
     263,   264,   265,   610,   611,   266,   612,   613,   267,   614,
     615,   616,   275,   617,   618,   276,   277,   619,   278,   620,
     621,   622,   290,   623,   291,   624,   625,   626,   627,   304,
     628,   305,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   629,   630,   631,   632,   633,
     634,   635,   399,   400,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   636,   637,
     157,   638,   639,   226,   640,   641,   643,   642,   644,   646,
     647,   649,   156,   650,   651,   711,   652,   653,   656,   231,
     654,   657,   658,   655,   660,   662,   664,   663,   665,   666,
     668,   669,   670,   671,   672,   673,   921,   935,   945,   674,
     401,   676,   677,   678,   969,   679,   680,   681,   684,   682,
     688,   689,   923,   941,   946,   956,   402,   692,   685,   686,
     796,   691,   232,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   693,   694,   695,   696,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   697,
     698,   126,   699,   702,   700,   924,   942,   947,   957,   403,
     703,   701,   708,   233,   704,   234,   705,   707,   710,   712,
     717,   129,   130,   235,   236,   237,   238,   239,   131,   713,
     714,   715,   716,   132,   133,   134,   718,   725,   726,   727,
     728,   729,   240,   730,    32,   241,   140,   733,   739,   740,
     741,   743,   752,   242,   742,   744,   745,   753,   754,   746,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   747,   748,   749,   750,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   751,   126,   339,
     755,   756,   758,   759,   760,   761,   765,   795,   853,   887,
     762,   857,   861,   764,   766,   767,   149,   150,   129,   130,
     768,   236,   237,   772,   239,   131,   773,   774,   775,   865,
     132,   133,   134,   790,   776,   777,   778,   869,   779,   240,
     891,   780,   241,   894,   898,   965,   156,   974,   978,   994,
     242,   781,   995,   996,   782,   997,   998,  1000,   784,   785,
     786,  1001,  1006,  1007,  1008,  1009,  1019,   792,  1018,   793,
    1021,   794,  1022,  1024,  1025,  1028,  1027,  1031,  1103,  1030,
    1045,  1034,  1044,  1048,  1047,  1049,  1050,  1051,  1052,  1053,
    1054,  1059,  1060,  1061,  1064,  1065,  1066,  1073,  1075,  1083,
    1086,  1091,  1090,   149,   150,  1093,  1094,  1097,  1096,  1098,
    1099,  1100,  1101,  1102,  1104,  1107,  1106,  1105,  1108,  1109,
    1110,  1111,  1112,  1113,  1118,  1116,  1114,  1115,  1117,   243,
    1119,  1120,   345,   156,  1121,   364,  1176,  1202,  1131,   366,
     286,   250,   367,  1203,  1204,   283,  1205,  1206,   359,  1180,
    1138,   377,   323,  1207,  1170,   381,  1209,   244,   346,  1210,
    1215,   365,  1219,  1220,  1156,  1189,  1132,  1211,   325,   251,
     252,   921,   253,   254,   255,  1187,   935,  1181,  1139,  1140,
     945,  1141,  1142,  1143,  1212,  1213,   245,   923,   284,  1230,
    1216,   360,   941,   969,   378,  1133,   946,  1171,   289,  1217,
    1222,   303,   956,  1223,   281,  1232,  1182,  1224,  1190,  1225,
    1240,   326,   246,  1169,   296,  1231,   247,   307,  1242,   256,
     248,  1134,  1243,  1254,  1188,  1135,  1248,   324,  1144,  1136,
     924,  1255,  1183,   249,   257,   942,  1184,   258,   259,   947,
    1185,   260,  1137,  1145,  1256,   957,  1146,  1147,  1233,   261,
    1148,  1271,   262,  1186,   263,   264,   265,   297,  1149,   266,
     308,  1150,   267,  1151,  1152,  1153,   275,  1272,  1154,   276,
     277,  1155,   278,   292,  1277,  1162,   306,  1278,  1163,  1164,
    1257,  1165,  1160,  1262,  1161,  1279,  1280,  1292,  1301,  1304,
    1306,   879,  1309,  1331,  1263,  1311,  1332,  1333,  1337,  1341,
     791,   645,   783,  1124,  1122,   799,   797,   648,  1177,  1201,
    1174,  1175,  1264,   986,  1218,  1200,   690,  1265,  1208,  1266,
    1126,  1125,   659,  1173,  1267,  1268,  1300,  1275,  1286,  1287,
    1288,   337,  1127,  1128,   683,   687,  1289,  1296,  1299,  1130,
    1305,  1129,   290,  1302,   291,   304,  1308,   305,  1310,  1199,
    1247,  1339,  1338,  1340,  1343,  1344,  1245,  1198,  1246,  1303,
    1197,  1244,   983,  1239,  1214,  1226,  1221,   964,  1307,   798,
    1329,   675,  1342,   706,     0,  1241,     0,     0,   661,   709,
       0,     0,  1131,     0,     0,     0,     0,     0,  1180,     0,
       0,   667,     0,     0,  1138,  1290,     0,     0,  1170,     0,
       0,     0,     0,  1230,  1189,     0,     0,     0,  1156,     0,
    1132,     0,     0,     0,  1187,     0,  1181,     0,     0,  1232,
       0,     0,  1139,  1140,     0,  1141,  1142,  1143,     0,  1231,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1133,
       0,  1171,     0,     0,     0,  1182,     0,  1190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1169,     0,     0,
       0,     0,  1233,  1188,     0,  1134,     0,     0,     0,  1135,
       0,  1183,  1144,  1136,     0,  1184,     0,     0,     0,  1185,
       0,     0,     0,     0,     0,     0,  1137,  1145,     0,     0,
    1146,  1147,  1186,     0,  1148,     0,     0,     0,     0,     0,
       0,     0,  1149,     0,     0,  1150,     0,  1151,  1152,  1153,
       0,     0,  1154,     0,     0,  1155,     0,     0,     0,  1162,
       0,     0,  1163,  1164,     0,  1165,  1160,     0,  1161
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   747,    79,    73,    73,    79,   716,    72,    73,    74,
      75,    76,   741,    78,    79,  1029,    81,  1029,  1029,  1029,
      73,  1029,   128,    78,    79,     5,    21,     7,     7,     9,
     135,   136,    73,    73,   126,    73,    73,    73,     0,     3,
     618,   133,    16,    17,     8,   200,    81,    13,    14,    73,
      72,    73,    74,    75,    76,     7,    78,    79,     7,    81,
     215,   181,   182,   183,   184,   100,   101,    73,    74,    75,
      76,     3,     3,     3,     7,    73,     8,     8,     8,    73,
       3,     7,    73,    73,     3,     8,    81,     6,    83,    84,
       3,     7,    87,    88,    89,     8,    73,    73,   218,    21,
      73,    73,     3,     7,    73,   100,   101,     8,    30,   215,
     215,   689,    73,   128,   129,    73,   131,    73,    73,    73,
       7,    80,    73,     3,   215,    73,   100,   101,     8,    73,
       7,     3,    73,    73,     7,    73,     8,    74,    75,    74,
      75,   100,   101,    11,    12,     3,     3,    15,     6,     6,
      18,    19,    20,   100,   101,     7,   191,     7,   193,   194,
     192,   120,   656,   195,   196,   197,   198,   126,   127,   128,
     129,   130,   131,     7,   668,   669,   670,     3,   100,   101,
     215,    10,     8,    79,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     6,   161,   162,   163,   100,   101,     3,
     215,     3,    90,    91,     8,     3,   148,   149,   150,   151,
       8,     3,   100,   101,     6,   215,   216,   217,   218,   107,
       3,   215,     4,     6,   112,   113,   114,   115,   116,   117,
     118,     8,   120,     3,   100,   101,   215,   125,     8,  1273,
       3,  1273,  1273,  1273,     4,  1273,   134,    80,   215,   137,
       3,   154,   155,   156,     3,     8,   144,     4,     3,     8,
      93,     3,    80,     8,   152,   153,     8,   100,   101,   157,
       3,     8,   160,   215,     4,     8,   164,    95,    96,    97,
      98,    99,   100,   101,     3,     3,  1035,  1017,   121,     8,
       8,   124,   158,   159,   135,   136,  1062,   185,   186,   187,
     188,   189,   190,   121,     3,     3,   124,     4,     3,    21,
       8,   199,   215,     8,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     4,   215,     4,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
       4,    81,    82,    83,    84,    85,    86,   178,   179,   215,
       4,     4,    52,    53,    54,    55,    56,    57,     4,     4,
     100,   101,   138,   139,   140,   141,   142,   143,     3,    81,
       3,     3,     3,     8,     3,     8,     8,     8,     3,     8,
      80,    81,   215,     8,     4,     3,     3,     8,   428,   429,
       8,     8,   108,   109,   110,   111,     4,   215,     4,   500,
     100,   101,     4,   504,     4,     4,    22,    23,    24,    25,
      38,    39,    40,     4,     4,   516,     4,     4,   519,   504,
       4,     4,   122,   123,     4,   526,   516,   516,   145,   146,
     147,   516,     4,     4,   519,   536,     4,     4,     4,     4,
       4,   526,     4,   516,     4,   546,     4,     4,     4,     4,
     551,   536,     4,     4,   551,   516,   516,   551,   516,   516,
     516,   546,   504,     8,     3,     8,   551,     4,     4,     3,
     571,   546,   516,     4,   516,   215,   551,   519,     4,     4,
       4,     4,     4,     4,   526,     4,   571,   215,     4,     4,
     516,     4,     4,   519,   536,     4,     4,   218,   516,     4,
     526,   216,   516,   215,   546,   516,   516,   100,   101,   551,
     536,   216,   216,   216,   216,   215,   217,     4,     4,   516,
     516,   217,   216,   516,   516,   216,   216,   516,   217,   571,
     216,   216,   216,   216,     4,   516,   218,   218,   516,   218,
     516,   516,   516,   218,   218,   516,   218,     4,   516,     4,
       4,   216,   516,     4,     4,   516,   516,     4,   516,     4,
     218,   218,   519,   218,   519,     4,     4,     4,     4,   526,
       4,   526,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,     4,     4,     4,     4,   216,
       4,     4,   185,   186,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,     4,     4,
     711,     4,     4,   714,   218,   218,     4,   218,     4,     4,
     218,     4,   215,     4,     4,     7,     4,     4,     4,   714,
     216,     4,     4,   218,     4,     4,     4,   216,   216,   216,
       4,     4,     4,     4,     4,     4,   747,   748,   749,     4,
     751,     4,     4,   216,   755,     4,     4,     4,     4,   218,
       4,     4,   747,   748,   749,   750,   751,     4,   218,   218,
     710,   218,   714,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     4,   216,     4,   216,
      69,    70,    71,    72,    73,    74,    75,    76,    77,   216,
       4,    80,     4,     4,   218,   747,   748,   749,   750,   751,
       4,   218,   216,    92,     4,    94,     4,     4,     4,   215,
       5,   100,   101,   102,   103,   104,   105,   106,   107,     7,
       7,     7,     7,   112,   113,   114,   215,   215,   215,     5,
       5,     5,   121,     5,     7,   124,   125,   215,     5,     5,
       5,     5,   215,   132,     7,     5,     5,   215,     5,     7,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     7,     7,     7,     7,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     7,    80,    81,
       7,     5,     5,     5,   215,   215,     7,     5,     7,   119,
     215,     7,     7,   215,   215,   215,   185,   186,   100,   101,
     215,   103,   104,   215,   106,   107,   215,   215,   215,     7,
     112,   113,   114,   180,   215,   215,   215,     7,   215,   121,
       7,   215,   124,     7,     7,     7,   215,     7,     7,     4,
     132,   215,     4,     4,   215,     4,     4,     4,   215,   215,
     215,     4,     4,     4,     4,     4,     3,   215,     6,   215,
       6,   215,     3,     6,     3,     3,     6,     3,   218,     6,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     215,     3,     6,   185,   186,     6,     3,     6,     8,     4,
       4,     4,     4,   216,   216,     4,   216,   218,   216,   216,
       4,     4,     4,     4,     4,   218,   216,   216,   216,  1020,
       4,     4,  1023,   215,     4,  1026,     4,   216,  1029,  1026,
    1020,  1020,  1026,   216,   216,  1020,   216,   216,  1023,  1040,
    1029,  1026,  1043,   216,  1029,  1046,     4,  1020,  1023,     4,
     218,  1026,     4,     4,  1029,  1040,  1029,   216,  1043,  1020,
    1020,  1062,  1020,  1020,  1020,  1040,  1067,  1040,  1029,  1029,
    1071,  1029,  1029,  1029,   216,   216,  1020,  1062,  1020,  1080,
     216,  1023,  1067,  1084,  1026,  1029,  1071,  1029,  1089,   216,
     218,  1092,  1077,     4,  1020,  1080,  1040,   216,  1040,     4,
     218,  1043,  1020,  1029,  1089,  1080,  1020,  1092,     6,  1020,
    1020,  1029,     3,   215,  1040,  1029,     4,  1043,  1029,  1029,
    1062,   215,  1040,  1020,  1020,  1067,  1040,  1020,  1020,  1071,
    1040,  1020,  1029,  1029,   215,  1077,  1029,  1029,  1080,  1020,
    1029,     8,  1020,  1040,  1020,  1020,  1020,  1089,  1029,  1020,
    1092,  1029,  1020,  1029,  1029,  1029,  1020,     8,  1029,  1020,
    1020,  1029,  1020,  1089,     4,  1029,  1092,     8,  1029,  1029,
     215,  1029,  1029,   215,  1029,     3,     8,     4,     4,     4,
       4,   740,     5,     4,   215,     7,     4,     4,     4,     4,
     702,   500,   689,  1019,  1014,   714,   711,   504,  1038,  1048,
    1032,  1035,   215,   795,  1067,  1046,   554,   215,  1055,   215,
    1022,  1020,   516,  1031,   215,   215,  1273,   215,   215,   215,
     215,    77,  1023,  1025,   546,   551,   215,   215,   215,  1028,
     216,  1026,  1089,   218,  1089,  1092,   215,  1092,   215,  1045,
    1094,   216,   218,   216,   215,   215,  1091,  1043,  1092,  1279,
    1041,  1089,   765,  1081,  1062,  1077,  1071,   751,  1294,   713,
    1315,   536,  1335,   571,    -1,  1084,    -1,    -1,   519,   575,
      -1,    -1,  1273,    -1,    -1,    -1,    -1,    -1,  1279,    -1,
      -1,   526,    -1,    -1,  1273,  1225,    -1,    -1,  1273,    -1,
      -1,    -1,    -1,  1294,  1279,    -1,    -1,    -1,  1273,    -1,
    1273,    -1,    -1,    -1,  1279,    -1,  1279,    -1,    -1,  1294,
      -1,    -1,  1273,  1273,    -1,  1273,  1273,  1273,    -1,  1294,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1273,
      -1,  1273,    -1,    -1,    -1,  1279,    -1,  1279,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1273,    -1,    -1,
      -1,    -1,  1294,  1279,    -1,  1273,    -1,    -1,    -1,  1273,
      -1,  1279,  1273,  1273,    -1,  1279,    -1,    -1,    -1,  1279,
      -1,    -1,    -1,    -1,    -1,    -1,  1273,  1273,    -1,    -1,
    1273,  1273,  1279,    -1,  1273,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1273,    -1,    -1,  1273,    -1,  1273,  1273,  1273,
      -1,    -1,  1273,    -1,    -1,  1273,    -1,    -1,    -1,  1273,
      -1,    -1,  1273,  1273,    -1,  1273,  1273,    -1,  1273
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
       0,     5,     7,     9,   215,   216,   217,   218,   235,   236,
     237,   242,     7,   251,     7,   256,     7,   303,     7,   420,
       7,   500,     7,   516,     7,   533,     7,   452,     7,   458,
       7,   482,     7,   396,     7,   602,     7,   633,   243,   238,
     252,   257,   304,   421,   501,   517,   534,   453,   459,   483,
     397,   603,   634,   235,   244,   245,   215,   240,   241,    10,
     253,   255,    11,    12,    15,    18,    19,    20,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    90,    91,   100,
     101,   107,   112,   113,   114,   115,   116,   117,   118,   120,
     125,   134,   137,   144,   152,   153,   157,   160,   164,   185,
     186,   187,   188,   189,   190,   199,   215,   250,   258,   259,
     260,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   282,
     284,   286,   287,   288,   290,   292,   293,   294,   295,   297,
     298,   299,   300,   301,   310,   312,   314,   363,   369,   375,
     381,   383,   390,   404,   414,   434,   435,   436,   437,   442,
     450,   476,   506,   508,   527,   557,   569,   581,   582,   590,
     600,   631,   640,   664,    16,    17,   250,   305,   306,   307,
     309,   506,   508,    92,    94,   102,   103,   104,   105,   106,
     121,   124,   132,   250,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   276,   277,   278,
     279,   282,   284,   286,   287,   288,   290,   292,   422,   423,
     424,   426,   428,   430,   432,   434,   435,   436,   437,   440,
     441,   476,   494,   506,   508,   510,   527,   552,    93,   250,
     430,   432,   476,   502,   503,   504,   506,   508,    95,    96,
      97,    98,    99,   250,   430,   432,   476,   506,   508,   518,
     519,   520,   522,   523,   525,   526,   120,   126,   127,   128,
     129,   130,   131,   250,   476,   506,   508,   535,   536,   537,
     538,   540,   542,   544,   546,   548,   550,   450,    21,    81,
      83,    84,    87,    88,    89,   250,   332,   460,   461,   462,
     463,   464,   465,   466,   468,   470,   472,   473,   475,   506,
     508,    82,    85,    86,   250,   332,   464,   470,   484,   485,
     486,   487,   488,   490,   491,   492,   493,   506,   508,   135,
     136,   250,   398,   399,   400,   402,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   185,
     186,   250,   506,   508,   604,   605,   606,   607,   609,   611,
     612,   614,   615,   616,   619,   621,   622,   623,   625,   627,
     629,    13,    14,   635,   636,   637,   639,     6,     3,     4,
       8,     3,   254,     3,     8,   261,   632,   302,   311,   313,
     315,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   296,     4,     4,     4,     4,
       4,   280,   283,   285,     4,     4,     4,   415,   451,   477,
       4,   443,   507,   509,   438,     4,     4,     4,   370,   382,
     376,   364,   558,   528,   391,   405,   570,     4,   384,   583,
     591,   601,   289,   291,     4,     4,     4,   641,   665,     4,
       3,     8,   308,     4,     3,     8,   495,   511,   425,   427,
     429,     4,     4,   433,   431,   553,     3,     8,   505,     3,
       8,   521,     4,   524,     4,     4,     3,     8,   551,   539,
     541,   543,   545,   547,   549,     8,     3,     8,   467,   333,
       4,   471,   469,   474,     4,     8,     3,   489,     4,     4,
       8,     3,   401,   403,     3,     8,     4,   608,   610,     4,
     613,     4,     4,   617,   620,     4,     4,   624,   626,   628,
     630,     3,     8,   638,     4,     3,     8,   235,   235,   215,
       4,     4,     4,     4,     4,     4,     4,   216,   216,   216,
     216,   216,   216,   216,   216,   218,   217,   217,   217,   216,
     216,     4,   216,   216,   218,   218,   218,     4,     4,     4,
     218,   218,   218,     4,     4,     4,   216,     4,     4,     4,
       4,   218,   218,   218,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   216,     4,     4,     4,     4,     4,     4,
     218,   218,   218,     4,     4,   259,     4,   218,   306,     4,
       4,     4,     4,     4,   216,   218,     4,     4,     4,   423,
       4,   503,     4,   216,     4,   216,   216,   519,     4,     4,
       4,     4,     4,     4,     4,   537,     4,     4,   216,     4,
       4,     4,   218,   462,     4,   218,   218,   486,     4,     4,
     399,   218,     4,     4,   216,     4,   216,   216,     4,     4,
     218,   218,     4,     4,     4,     4,   605,     4,   216,   636,
       4,     7,   215,     7,     7,     7,     7,     5,   215,   181,
     182,   183,   184,   218,   281,   215,   215,     5,     5,     5,
       5,   237,   239,   215,   108,   109,   110,   111,   439,     5,
       5,     5,     7,     5,     5,     5,     7,     7,     7,     7,
       7,     7,   215,   215,     5,     7,     5,   246,     5,     5,
     215,   215,   215,   246,   215,     7,   215,   215,   215,   246,
     246,   246,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   239,   215,   215,   215,   178,   179,   618,
     180,   281,   215,   215,   215,     5,   235,   258,   635,   305,
      21,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,   250,   320,   321,   322,   325,   327,
     329,   331,   332,   334,   335,   336,   337,   338,   339,   342,
     343,   344,   345,   346,   348,   349,   351,   353,   355,   357,
     359,   361,   320,     7,   316,   317,   318,     7,   416,   417,
     418,     7,   454,   455,   456,     7,   478,   479,   480,     7,
     444,   445,   446,   128,   215,   371,   372,   373,   374,   244,
     129,   131,   373,   377,   378,   379,   380,   119,   365,   366,
     367,     7,   559,   560,     7,   529,   530,   531,     7,   392,
     393,   394,   138,   139,   140,   141,   142,   143,   406,   407,
     408,   409,   410,   411,   412,   413,    21,   148,   149,   150,
     151,   250,   334,   506,   508,   571,   572,   573,   576,   577,
     579,   580,   154,   155,   156,   250,   385,   386,   387,   388,
     389,   506,   508,   158,   159,   250,   506,   508,   584,   585,
     586,   588,   161,   162,   163,   215,   506,   508,   592,   593,
     594,   595,   597,   598,   604,     7,   642,   643,   200,   250,
     666,   667,   668,   247,     7,   496,   497,   498,     7,   512,
     513,   514,   133,   538,   554,   555,   316,     8,     8,     8,
     323,   326,   328,   330,     4,     4,     4,     4,     4,   347,
       4,     4,   340,   350,   352,   354,     4,     4,     4,     4,
     356,   358,   360,   362,     3,     8,     8,   319,     6,     3,
     419,     6,     3,   457,     6,     3,   481,     6,     3,   447,
       6,     3,     3,     6,     6,     3,     6,   368,     3,     8,
     561,     3,     6,   532,     6,     3,   395,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   574,   578,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   587,
     589,     3,     8,     4,   596,     4,   599,     3,     8,     8,
     644,     3,     6,     4,     3,     8,   215,   248,   249,   499,
       6,     3,   515,     6,     3,   556,     8,     6,     4,     4,
       4,     4,   216,   218,   216,   218,   216,     4,   216,   216,
       4,     4,     4,     4,   216,   216,   218,   216,     4,     4,
       4,     4,   321,   320,   318,   422,   418,   460,   456,   484,
     480,   250,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   276,   277,   278,   279,   282,
     284,   286,   287,   288,   290,   292,   332,   414,   426,   428,
     430,   432,   434,   435,   436,   437,   441,   448,   449,   476,
     506,   508,   552,   446,   372,   378,     4,   366,   122,   123,
     250,   262,   263,   264,   265,   266,   267,   332,   476,   506,
     508,   562,   563,   564,   565,   566,   568,   560,   535,   531,
     398,   394,   216,   216,   216,   216,   216,   216,   407,     4,
       4,   216,   216,   216,   572,   218,   216,   216,   386,     4,
       4,   585,   218,     4,   216,     4,   593,   191,   193,   194,
     250,   332,   506,   508,   645,   646,   647,   648,   650,   643,
     218,   667,     6,     3,   502,   498,   518,   514,     4,    22,
      23,    24,    25,   324,   215,   215,   215,   215,    38,    39,
      40,   341,   215,   215,   215,   215,   215,   215,   215,     8,
       8,     8,     8,     3,     8,   215,   567,     4,     8,     3,
       8,     8,   145,   146,   147,   575,   215,   215,   215,   215,
     235,   651,     4,   649,     3,     8,   215,     8,     8,   215,
     449,     4,   218,   564,     4,   216,     4,   646,   215,     5,
     215,     7,   652,   653,   654,     3,     6,   192,   195,   196,
     197,   198,   655,   656,   657,   659,   660,   661,   662,   653,
     658,     4,     4,     4,   663,     3,     8,     4,   218,   216,
     216,     4,   656,   215,   215
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   219,   221,   220,   222,   220,   223,   220,   224,   220,
     225,   220,   226,   220,   227,   220,   228,   220,   229,   220,
     230,   220,   231,   220,   232,   220,   233,   220,   234,   220,
     235,   235,   235,   235,   235,   235,   235,   236,   238,   237,
     239,   240,   240,   241,   241,   241,   243,   242,   244,   244,
     245,   245,   245,   247,   246,   248,   248,   249,   249,   249,
     250,   252,   251,   254,   253,   253,   255,   257,   256,   258,
     258,   258,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   261,   260,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   280,   279,   281,   281,
     281,   281,   281,   283,   282,   285,   284,   286,   287,   289,
     288,   291,   290,   292,   293,   294,   296,   295,   297,   298,
     299,   300,   302,   301,   304,   303,   305,   305,   305,   306,
     306,   306,   306,   306,   308,   307,   309,   311,   310,   313,
     312,   315,   314,   316,   316,   317,   317,   317,   319,   318,
     320,   320,   320,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   323,
     322,   324,   324,   324,   324,   326,   325,   328,   327,   330,
     329,   331,   333,   332,   334,   335,   336,   337,   338,   340,
     339,   341,   341,   341,   342,   343,   344,   345,   347,   346,
     348,   350,   349,   352,   351,   354,   353,   356,   355,   358,
     357,   360,   359,   362,   361,   364,   363,   365,   365,   365,
     366,   368,   367,   370,   369,   371,   371,   371,   372,   372,
     373,   374,   376,   375,   377,   377,   377,   378,   378,   378,
     379,   380,   382,   381,   384,   383,   385,   385,   385,   386,
     386,   386,   386,   386,   386,   387,   388,   389,   391,   390,
     392,   392,   393,   393,   393,   395,   394,   397,   396,   398,
     398,   398,   398,   399,   399,   401,   400,   403,   402,   405,
     404,   406,   406,   406,   407,   407,   407,   407,   407,   407,
     408,   409,   410,   411,   412,   413,   415,   414,   416,   416,
     417,   417,   417,   419,   418,   421,   420,   422,   422,   422,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   425,   424,   427,   426,   429,   428,   431,
     430,   433,   432,   434,   435,   436,   438,   437,   439,   439,
     439,   439,   440,   441,   443,   442,   444,   444,   445,   445,
     445,   447,   446,   448,   448,   448,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   451,   450,   453,   452,
     454,   454,   455,   455,   455,   457,   456,   459,   458,   460,
     460,   461,   461,   461,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   463,   464,   465,   467,   466,   469,
     468,   471,   470,   472,   474,   473,   475,   477,   476,   478,
     478,   479,   479,   479,   481,   480,   483,   482,   484,   484,
     485,   485,   485,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   487,   489,   488,   490,   491,   492,   493,   495,
     494,   496,   496,   497,   497,   497,   499,   498,   501,   500,
     502,   502,   502,   503,   503,   503,   503,   503,   503,   503,
     505,   504,   507,   506,   509,   508,   511,   510,   512,   512,
     513,   513,   513,   515,   514,   517,   516,   518,   518,   518,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   521,   520,   522,   524,   523,   525,   526,   528,   527,
     529,   529,   530,   530,   530,   532,   531,   534,   533,   535,
     535,   536,   536,   536,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   539,   538,   541,   540,   543,
     542,   545,   544,   547,   546,   549,   548,   551,   550,   553,
     552,   554,   554,   556,   555,   558,   557,   559,   559,   559,
     561,   560,   562,   562,   563,   563,   563,   564,   564,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     565,   567,   566,   568,   570,   569,   571,   571,   571,   572,
     572,   572,   572,   572,   572,   572,   572,   572,   574,   573,
     575,   575,   575,   576,   578,   577,   579,   580,   581,   583,
     582,   584,   584,   584,   585,   585,   585,   585,   585,   587,
     586,   589,   588,   591,   590,   592,   592,   592,   593,   593,
     593,   593,   593,   593,   594,   596,   595,   597,   599,   598,
     601,   600,   603,   602,   604,   604,   604,   605,   605,   605,
     605,   605,   605,   605,   605,   605,   605,   605,   605,   605,
     605,   605,   605,   605,   605,   606,   608,   607,   610,   609,
     611,   613,   612,   614,   615,   617,   616,   618,   618,   620,
     619,   621,   622,   624,   623,   626,   625,   628,   627,   630,
     629,   632,   631,   634,   633,   635,   635,   635,   636,   636,
     638,   637,   639,   641,   640,   642,   642,   642,   644,   643,
     645,   645,   645,   646,   646,   646,   646,   646,   646,   646,
     647,   649,   648,   651,   650,   652,   652,   652,   654,   653,
     655,   655,   655,   656,   656,   656,   656,   656,   658,   657,
     659,   660,   661,   663,   662,   665,   664,   666,   666,   666,
     667,   667,   668
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     3,
       3,     3,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     3,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     1,     3,     2,     1,
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
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
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
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     3
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
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"on-fail\"", "\"stop-retry-exit\"",
  "\"serve-retry-exit\"", "\"serve-retry-continue\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"max-row-errors\"",
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
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
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"client-classes\"", "\"require-client-classes\"",
  "\"test\"", "\"only-if-required\"", "\"client-class\"",
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
  "parked_packet_limit", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@28", "sub_interfaces6", "$@29",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@30", "re_detect", "lease_database", "$@31", "hosts_database", "$@32",
  "hosts_databases", "$@33", "database_list", "not_empty_database_list",
  "database", "$@34", "database_map_params", "database_map_param",
  "database_type", "$@35", "db_type", "user", "$@36", "password", "$@37",
  "host", "$@38", "port", "name", "$@39", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "on_fail", "$@40",
  "on_fail_mode", "max_row_errors", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@41", "max_reconnect_tries",
  "keyspace", "$@42", "consistency", "$@43", "serial_consistency", "$@44",
  "trust_anchor", "$@45", "cert_file", "$@46", "key_file", "$@47",
  "cipher_list", "$@48", "sanity_checks", "$@49", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@50", "mac_sources", "$@51",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@52",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@53",
  "dhcp_multi_threading", "$@54", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@55", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@56",
  "sub_hooks_library", "$@57", "hooks_params", "hooks_param", "library",
  "$@58", "parameters", "$@59", "expired_leases_processing", "$@60",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@61",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@62",
  "sub_subnet6", "$@63", "subnet6_params", "subnet6_param", "subnet",
  "$@64", "interface", "$@65", "interface_id", "$@66", "client_class",
  "$@67", "require_client_classes", "$@68", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@69", "hr_mode", "id", "rapid_commit", "shared_networks", "$@70",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@71", "shared_network_params", "shared_network_param",
  "option_def_list", "$@72", "sub_option_def_list", "$@73",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@74", "sub_option_def", "$@75",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@76",
  "option_def_record_types", "$@77", "space", "$@78", "option_def_space",
  "option_def_encapsulate", "$@79", "option_def_array", "option_data_list",
  "$@80", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@81", "sub_option_data", "$@82",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@83",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@84", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@85", "sub_pool6", "$@86",
  "pool_params", "pool_param", "pool_entry", "$@87", "user_context",
  "$@88", "comment", "$@89", "pd_pools_list", "$@90",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@91", "sub_pd_pool", "$@92", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@93", "pd_prefix_len", "excluded_prefix", "$@94",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@95",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@96", "sub_reservation", "$@97", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@98", "prefixes", "$@99", "duid", "$@100", "hw_address", "$@101",
  "hostname", "$@102", "flex_id_value", "$@103",
  "reservation_client_classes", "$@104", "relay", "$@105", "relay_map",
  "ip_address", "$@106", "client_classes", "$@107", "client_classes_list",
  "client_class_entry", "$@108", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@109", "only_if_required",
  "server_id", "$@110", "server_id_params", "server_id_param",
  "server_id_type", "$@111", "duid_type", "htype", "identifier", "$@112",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@113",
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
       0,   307,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   314,   315,   315,
     316,   316,   317,   317,   318,   318,   319,   319,   320,   320,
     328,   329,   330,   331,   332,   333,   334,   337,   342,   342,
     353,   356,   357,   360,   365,   371,   376,   376,   383,   384,
     387,   391,   395,   401,   401,   408,   409,   412,   416,   420,
     430,   439,   439,   454,   454,   468,   471,   477,   477,   486,
     487,   488,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   562,   562,   571,
     577,   583,   589,   595,   601,   607,   613,   619,   625,   631,
     637,   643,   649,   655,   661,   667,   673,   673,   682,   685,
     688,   691,   694,   700,   700,   709,   709,   718,   724,   730,
     730,   739,   739,   748,   754,   760,   766,   766,   775,   781,
     787,   793,   799,   799,   811,   811,   820,   821,   822,   827,
     828,   829,   830,   831,   834,   834,   845,   851,   851,   864,
     864,   877,   877,   888,   889,   892,   893,   894,   899,   899,
     909,   910,   911,   916,   917,   918,   919,   920,   921,   922,
     923,   924,   925,   926,   927,   928,   929,   930,   931,   932,
     933,   934,   935,   936,   937,   938,   939,   940,   941,   944,
     944,   952,   953,   954,   955,   958,   958,   967,   967,   976,
     976,   985,   991,   991,  1000,  1006,  1012,  1018,  1024,  1030,
    1030,  1038,  1039,  1040,  1043,  1049,  1055,  1061,  1067,  1067,
    1076,  1082,  1082,  1091,  1091,  1100,  1100,  1109,  1109,  1118,
    1118,  1127,  1127,  1136,  1136,  1145,  1145,  1156,  1157,  1158,
    1163,  1165,  1165,  1184,  1184,  1195,  1196,  1197,  1202,  1203,
    1206,  1211,  1216,  1216,  1227,  1228,  1229,  1234,  1235,  1236,
    1239,  1244,  1251,  1251,  1264,  1264,  1277,  1278,  1279,  1284,
    1285,  1286,  1287,  1288,  1289,  1292,  1298,  1304,  1310,  1310,
    1321,  1322,  1325,  1326,  1327,  1332,  1332,  1342,  1342,  1352,
    1353,  1354,  1357,  1360,  1361,  1364,  1364,  1373,  1373,  1382,
    1382,  1394,  1395,  1396,  1401,  1402,  1403,  1404,  1405,  1406,
    1409,  1415,  1421,  1427,  1433,  1439,  1448,  1448,  1462,  1463,
    1466,  1467,  1468,  1477,  1477,  1503,  1503,  1514,  1515,  1516,
    1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,
    1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,  1540,  1541,
    1542,  1543,  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,
    1552,  1553,  1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,
    1562,  1563,  1564,  1567,  1567,  1576,  1576,  1585,  1585,  1594,
    1594,  1603,  1603,  1614,  1620,  1626,  1632,  1632,  1640,  1641,
    1642,  1643,  1646,  1652,  1660,  1660,  1672,  1673,  1677,  1678,
    1679,  1684,  1684,  1692,  1693,  1694,  1699,  1700,  1701,  1702,
    1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,
    1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,
    1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,  1731,  1732,
    1733,  1734,  1735,  1736,  1737,  1738,  1745,  1745,  1759,  1759,
    1768,  1769,  1772,  1773,  1774,  1781,  1781,  1796,  1796,  1810,
    1811,  1814,  1815,  1816,  1821,  1822,  1823,  1824,  1825,  1826,
    1827,  1828,  1829,  1830,  1833,  1835,  1841,  1843,  1843,  1852,
    1852,  1861,  1861,  1870,  1872,  1872,  1881,  1891,  1891,  1904,
    1905,  1910,  1911,  1912,  1919,  1919,  1931,  1931,  1943,  1944,
    1949,  1950,  1951,  1958,  1959,  1960,  1961,  1962,  1963,  1964,
    1965,  1966,  1969,  1971,  1971,  1980,  1982,  1984,  1990,  1999,
    1999,  2012,  2013,  2016,  2017,  2018,  2023,  2023,  2033,  2033,
    2043,  2044,  2045,  2050,  2051,  2052,  2053,  2054,  2055,  2056,
    2059,  2059,  2068,  2068,  2093,  2093,  2123,  2123,  2136,  2137,
    2140,  2141,  2142,  2147,  2147,  2159,  2159,  2171,  2172,  2173,
    2178,  2179,  2180,  2181,  2182,  2183,  2184,  2185,  2186,  2187,
    2188,  2191,  2191,  2200,  2206,  2206,  2215,  2221,  2230,  2230,
    2241,  2242,  2245,  2246,  2247,  2252,  2252,  2261,  2261,  2270,
    2271,  2274,  2275,  2276,  2282,  2283,  2284,  2285,  2286,  2287,
    2288,  2289,  2290,  2291,  2292,  2295,  2295,  2306,  2306,  2317,
    2317,  2326,  2326,  2335,  2335,  2344,  2344,  2353,  2353,  2367,
    2367,  2378,  2379,  2382,  2382,  2394,  2394,  2405,  2406,  2407,
    2412,  2412,  2422,  2423,  2426,  2427,  2428,  2433,  2434,  2435,
    2436,  2437,  2438,  2439,  2440,  2441,  2442,  2443,  2444,  2445,
    2448,  2450,  2450,  2459,  2468,  2468,  2481,  2482,  2483,  2488,
    2489,  2490,  2491,  2492,  2493,  2494,  2495,  2496,  2499,  2499,
    2507,  2508,  2509,  2512,  2518,  2518,  2527,  2533,  2541,  2549,
    2549,  2560,  2561,  2562,  2567,  2568,  2569,  2570,  2571,  2574,
    2574,  2583,  2583,  2595,  2595,  2608,  2609,  2610,  2615,  2616,
    2617,  2618,  2619,  2620,  2623,  2629,  2629,  2638,  2644,  2644,
    2654,  2654,  2667,  2667,  2677,  2678,  2679,  2684,  2685,  2686,
    2687,  2688,  2689,  2690,  2691,  2692,  2693,  2694,  2695,  2696,
    2697,  2698,  2699,  2700,  2701,  2704,  2711,  2711,  2720,  2720,
    2729,  2735,  2735,  2744,  2750,  2756,  2756,  2765,  2766,  2769,
    2769,  2779,  2786,  2793,  2793,  2802,  2802,  2812,  2812,  2822,
    2822,  2834,  2834,  2846,  2846,  2856,  2857,  2858,  2864,  2865,
    2868,  2868,  2879,  2887,  2887,  2900,  2901,  2902,  2908,  2908,
    2916,  2917,  2918,  2923,  2924,  2925,  2926,  2927,  2928,  2929,
    2932,  2938,  2938,  2947,  2947,  2958,  2959,  2960,  2965,  2965,
    2973,  2974,  2975,  2980,  2981,  2982,  2983,  2984,  2987,  2987,
    2996,  3002,  3008,  3014,  3014,  3023,  3023,  3034,  3035,  3036,
    3041,  3042,  3045
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
#line 6448 "dhcp6_parser.cc"

#line 3051 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
