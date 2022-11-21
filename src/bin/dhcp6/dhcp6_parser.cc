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
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 297 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 297 "dhcp6_parser.yy"
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
#line 306 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 307 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 308 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 309 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 310 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 311 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 312 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 313 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 314 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 315 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 316 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 317 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 318 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 319 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 327 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 328 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 329 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 330 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 331 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 332 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 333 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 336 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 341 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 346 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 352 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 359 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 364 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 370 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 375 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 378 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 386 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 390 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 394 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 400 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 402 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 411 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 415 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 419 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 429 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 438 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 443 "dhcp6_parser.yy"
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
#line 453 "dhcp6_parser.yy"
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
#line 462 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 470 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 476 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 480 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 487 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 139: // $@21: %empty
#line 563 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 140: // data_directory: "data-directory" $@21 ":" "constant string"
#line 566 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 141: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 572 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 142: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 578 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 143: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 584 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 144: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 590 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 145: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 596 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 146: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 602 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 147: // renew_timer: "renew-timer" ":" "integer"
#line 608 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 148: // rebind_timer: "rebind-timer" ":" "integer"
#line 614 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 149: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 620 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 150: // t1_percent: "t1-percent" ":" "floating point"
#line 626 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 151: // t2_percent: "t2-percent" ":" "floating point"
#line 632 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 152: // cache_threshold: "cache-threshold" ":" "floating point"
#line 638 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 153: // cache_max_age: "cache-max-age" ":" "integer"
#line 644 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 154: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 650 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 155: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 656 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 156: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 662 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 157: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 668 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 158: // $@22: %empty
#line 674 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 677 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "when-present"
#line 683 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "never"
#line 686 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "always"
#line 689 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-not-present"
#line 692 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "boolean"
#line 695 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 165: // $@23: %empty
#line 701 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 166: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 704 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 167: // $@24: %empty
#line 710 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 168: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 713 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 169: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 719 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 170: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 725 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 171: // $@25: %empty
#line 731 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 734 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 173: // $@26: %empty
#line 740 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 174: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 743 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // store_extended_info: "store-extended-info" ":" "boolean"
#line 749 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 176: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 755 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 177: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 761 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 178: // $@27: %empty
#line 767 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 179: // server_tag: "server-tag" $@27 ":" "constant string"
#line 770 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 180: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 776 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 181: // $@28: %empty
#line 782 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1528 "dhcp6_parser.cc"
    break;

  case 182: // allocator: "allocator" $@28 ":" "constant string"
#line 785 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1538 "dhcp6_parser.cc"
    break;

  case 183: // $@29: %empty
#line 791 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1547 "dhcp6_parser.cc"
    break;

  case 184: // pd_allocator: "pd-allocator" $@29 ":" "constant string"
#line 794 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1557 "dhcp6_parser.cc"
    break;

  case 185: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 800 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1567 "dhcp6_parser.cc"
    break;

  case 186: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 806 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 187: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 812 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 188: // $@30: %empty
#line 818 "dhcp6_parser.yy"
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
#line 824 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 190: // $@31: %empty
#line 830 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 191: // sub_interfaces6: "{" $@31 interfaces_config_params "}"
#line 834 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 194: // interfaces_config_params: interfaces_config_params ","
#line 841 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1636 "dhcp6_parser.cc"
    break;

  case 203: // $@32: %empty
#line 856 "dhcp6_parser.yy"
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
#line 862 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 205: // re_detect: "re-detect" ":" "boolean"
#line 867 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 206: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 873 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 207: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 879 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 208: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 885 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 209: // $@33: %empty
#line 891 "dhcp6_parser.yy"
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
#line 897 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 211: // $@34: %empty
#line 904 "dhcp6_parser.yy"
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
#line 910 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1743 "dhcp6_parser.cc"
    break;

  case 213: // $@35: %empty
#line 917 "dhcp6_parser.yy"
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
#line 923 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 219: // not_empty_database_list: not_empty_database_list ","
#line 934 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1772 "dhcp6_parser.cc"
    break;

  case 220: // $@36: %empty
#line 939 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 221: // database: "{" $@36 database_map_params "}"
#line 943 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 224: // database_map_params: database_map_params ","
#line 951 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1800 "dhcp6_parser.cc"
    break;

  case 244: // $@37: %empty
#line 977 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 245: // database_type: "type" $@37 ":" db_type
#line 980 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 246: // db_type: "memfile"
#line 985 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1824 "dhcp6_parser.cc"
    break;

  case 247: // db_type: "mysql"
#line 986 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1830 "dhcp6_parser.cc"
    break;

  case 248: // db_type: "postgresql"
#line 987 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1836 "dhcp6_parser.cc"
    break;

  case 249: // $@38: %empty
#line 990 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 250: // user: "user" $@38 ":" "constant string"
#line 993 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 251: // $@39: %empty
#line 999 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 252: // password: "password" $@39 ":" "constant string"
#line 1002 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 253: // $@40: %empty
#line 1008 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 254: // host: "host" $@40 ":" "constant string"
#line 1011 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 255: // port: "port" ":" "integer"
#line 1017 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1903 "dhcp6_parser.cc"
    break;

  case 256: // $@41: %empty
#line 1023 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1912 "dhcp6_parser.cc"
    break;

  case 257: // name: "name" $@41 ":" "constant string"
#line 1026 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 258: // persist: "persist" ":" "boolean"
#line 1032 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1932 "dhcp6_parser.cc"
    break;

  case 259: // lfc_interval: "lfc-interval" ":" "integer"
#line 1038 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 260: // readonly: "readonly" ":" "boolean"
#line 1044 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 261: // connect_timeout: "connect-timeout" ":" "integer"
#line 1050 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1962 "dhcp6_parser.cc"
    break;

  case 262: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1056 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 263: // $@42: %empty
#line 1062 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1981 "dhcp6_parser.cc"
    break;

  case 264: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1065 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1990 "dhcp6_parser.cc"
    break;

  case 265: // on_fail_mode: "stop-retry-exit"
#line 1070 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1996 "dhcp6_parser.cc"
    break;

  case 266: // on_fail_mode: "serve-retry-exit"
#line 1071 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2002 "dhcp6_parser.cc"
    break;

  case 267: // on_fail_mode: "serve-retry-continue"
#line 1072 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2008 "dhcp6_parser.cc"
    break;

  case 268: // max_row_errors: "max-row-errors" ":" "integer"
#line 1075 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 269: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1081 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2028 "dhcp6_parser.cc"
    break;

  case 270: // $@43: %empty
#line 1087 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 271: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1090 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 272: // $@44: %empty
#line 1096 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 273: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1099 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 274: // $@45: %empty
#line 1105 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 275: // key_file: "key-file" $@45 ":" "constant string"
#line 1108 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2085 "dhcp6_parser.cc"
    break;

  case 276: // $@46: %empty
#line 1114 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp6_parser.cc"
    break;

  case 277: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1117 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2104 "dhcp6_parser.cc"
    break;

  case 278: // $@47: %empty
#line 1123 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 279: // sanity_checks: "sanity-checks" $@47 ":" "{" sanity_checks_params "}"
#line 1129 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 282: // sanity_checks_params: sanity_checks_params ","
#line 1136 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2133 "dhcp6_parser.cc"
    break;

  case 285: // $@48: %empty
#line 1145 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp6_parser.cc"
    break;

  case 286: // lease_checks: "lease-checks" $@48 ":" "constant string"
#line 1148 "dhcp6_parser.yy"
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
#line 2162 "dhcp6_parser.cc"
    break;

  case 287: // $@49: %empty
#line 1164 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2171 "dhcp6_parser.cc"
    break;

  case 288: // extended_info_checks: "extended-info-checks" $@49 ":" "constant string"
#line 1167 "dhcp6_parser.yy"
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
#line 2190 "dhcp6_parser.cc"
    break;

  case 289: // $@50: %empty
#line 1182 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 290: // mac_sources: "mac-sources" $@50 ":" "[" mac_sources_list "]"
#line 1188 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 293: // mac_sources_list: mac_sources_list ","
#line 1195 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2219 "dhcp6_parser.cc"
    break;

  case 296: // duid_id: "duid"
#line 1204 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 297: // string_id: "constant string"
#line 1209 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2237 "dhcp6_parser.cc"
    break;

  case 298: // $@51: %empty
#line 1214 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2249 "dhcp6_parser.cc"
    break;

  case 299: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1220 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 302: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1227 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2266 "dhcp6_parser.cc"
    break;

  case 306: // hw_address_id: "hw-address"
#line 1237 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2275 "dhcp6_parser.cc"
    break;

  case 307: // flex_id: "flex-id"
#line 1242 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2284 "dhcp6_parser.cc"
    break;

  case 308: // $@52: %empty
#line 1249 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp6_parser.cc"
    break;

  case 309: // relay_supplied_options: "relay-supplied-options" $@52 ":" "[" list_content "]"
#line 1255 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 310: // $@53: %empty
#line 1262 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2317 "dhcp6_parser.cc"
    break;

  case 311: // dhcp_multi_threading: "multi-threading" $@53 ":" "{" multi_threading_params "}"
#line 1268 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2328 "dhcp6_parser.cc"
    break;

  case 314: // multi_threading_params: multi_threading_params ","
#line 1277 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2336 "dhcp6_parser.cc"
    break;

  case 321: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1290 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2346 "dhcp6_parser.cc"
    break;

  case 322: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1296 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2356 "dhcp6_parser.cc"
    break;

  case 323: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1302 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2366 "dhcp6_parser.cc"
    break;

  case 324: // $@54: %empty
#line 1308 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 325: // hooks_libraries: "hooks-libraries" $@54 ":" "[" hooks_libraries_list "]"
#line 1314 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 330: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1325 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2395 "dhcp6_parser.cc"
    break;

  case 331: // $@55: %empty
#line 1330 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2405 "dhcp6_parser.cc"
    break;

  case 332: // hooks_library: "{" $@55 hooks_params "}"
#line 1334 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 333: // $@56: %empty
#line 1340 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp6_parser.cc"
    break;

  case 334: // sub_hooks_library: "{" $@56 hooks_params "}"
#line 1344 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2435 "dhcp6_parser.cc"
    break;

  case 337: // hooks_params: hooks_params ","
#line 1352 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2443 "dhcp6_parser.cc"
    break;

  case 341: // $@57: %empty
#line 1362 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2452 "dhcp6_parser.cc"
    break;

  case 342: // library: "library" $@57 ":" "constant string"
#line 1365 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2462 "dhcp6_parser.cc"
    break;

  case 343: // $@58: %empty
#line 1371 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 344: // parameters: "parameters" $@58 ":" map_value
#line 1374 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2480 "dhcp6_parser.cc"
    break;

  case 345: // $@59: %empty
#line 1380 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2492 "dhcp6_parser.cc"
    break;

  case 346: // expired_leases_processing: "expired-leases-processing" $@59 ":" "{" expired_leases_params "}"
#line 1386 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2502 "dhcp6_parser.cc"
    break;

  case 349: // expired_leases_params: expired_leases_params ","
#line 1394 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2510 "dhcp6_parser.cc"
    break;

  case 356: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1407 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2520 "dhcp6_parser.cc"
    break;

  case 357: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1413 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2530 "dhcp6_parser.cc"
    break;

  case 358: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1419 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 359: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1425 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 360: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1431 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 361: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1437 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1446 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 363: // subnet6_list: "subnet6" $@60 ":" "[" subnet6_list_content "]"
#line 1452 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 368: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1466 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2599 "dhcp6_parser.cc"
    break;

  case 369: // $@61: %empty
#line 1475 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2609 "dhcp6_parser.cc"
    break;

  case 370: // subnet6: "{" $@61 subnet6_params "}"
#line 1479 "dhcp6_parser.yy"
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
#line 2635 "dhcp6_parser.cc"
    break;

  case 371: // $@62: %empty
#line 1501 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2645 "dhcp6_parser.cc"
    break;

  case 372: // sub_subnet6: "{" $@62 subnet6_params "}"
#line 1505 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2655 "dhcp6_parser.cc"
    break;

  case 375: // subnet6_params: subnet6_params ","
#line 1514 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2663 "dhcp6_parser.cc"
    break;

  case 421: // $@63: %empty
#line 1567 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp6_parser.cc"
    break;

  case 422: // subnet: "subnet" $@63 ":" "constant string"
#line 1570 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2682 "dhcp6_parser.cc"
    break;

  case 423: // $@64: %empty
#line 1576 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 424: // interface: "interface" $@64 ":" "constant string"
#line 1579 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 425: // $@65: %empty
#line 1585 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2710 "dhcp6_parser.cc"
    break;

  case 426: // interface_id: "interface-id" $@65 ":" "constant string"
#line 1588 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2720 "dhcp6_parser.cc"
    break;

  case 427: // $@66: %empty
#line 1594 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 428: // client_class: "client-class" $@66 ":" "constant string"
#line 1597 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2739 "dhcp6_parser.cc"
    break;

  case 429: // $@67: %empty
#line 1603 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 430: // require_client_classes: "require-client-classes" $@67 ":" list_strings
#line 1609 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2760 "dhcp6_parser.cc"
    break;

  case 431: // reservations_global: "reservations-global" ":" "boolean"
#line 1614 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2770 "dhcp6_parser.cc"
    break;

  case 432: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1620 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2780 "dhcp6_parser.cc"
    break;

  case 433: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1626 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2790 "dhcp6_parser.cc"
    break;

  case 434: // $@68: %empty
#line 1632 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 435: // reservation_mode: "reservation-mode" $@68 ":" hr_mode
#line 1635 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 436: // hr_mode: "disabled"
#line 1640 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2814 "dhcp6_parser.cc"
    break;

  case 437: // hr_mode: "out-of-pool"
#line 1641 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2820 "dhcp6_parser.cc"
    break;

  case 438: // hr_mode: "global"
#line 1642 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2826 "dhcp6_parser.cc"
    break;

  case 439: // hr_mode: "all"
#line 1643 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2832 "dhcp6_parser.cc"
    break;

  case 440: // id: "id" ":" "integer"
#line 1646 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 441: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1652 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2852 "dhcp6_parser.cc"
    break;

  case 442: // $@69: %empty
#line 1660 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2864 "dhcp6_parser.cc"
    break;

  case 443: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1666 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2873 "dhcp6_parser.cc"
    break;

  case 448: // shared_networks_list: shared_networks_list ","
#line 1679 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2881 "dhcp6_parser.cc"
    break;

  case 449: // $@70: %empty
#line 1684 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2891 "dhcp6_parser.cc"
    break;

  case 450: // shared_network: "{" $@70 shared_network_params "}"
#line 1688 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2899 "dhcp6_parser.cc"
    break;

  case 453: // shared_network_params: shared_network_params ","
#line 1694 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2907 "dhcp6_parser.cc"
    break;

  case 496: // $@71: %empty
#line 1747 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 497: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1753 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 498: // $@72: %empty
#line 1761 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2937 "dhcp6_parser.cc"
    break;

  case 499: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1764 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 504: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1776 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2953 "dhcp6_parser.cc"
    break;

  case 505: // $@73: %empty
#line 1783 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2963 "dhcp6_parser.cc"
    break;

  case 506: // option_def_entry: "{" $@73 option_def_params "}"
#line 1787 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2975 "dhcp6_parser.cc"
    break;

  case 507: // $@74: %empty
#line 1798 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 508: // sub_option_def: "{" $@74 option_def_params "}"
#line 1802 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2997 "dhcp6_parser.cc"
    break;

  case 513: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1818 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3005 "dhcp6_parser.cc"
    break;

  case 525: // code: "code" ":" "integer"
#line 1837 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 527: // $@75: %empty
#line 1845 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 528: // option_def_type: "type" $@75 ":" "constant string"
#line 1848 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 529: // $@76: %empty
#line 1854 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3043 "dhcp6_parser.cc"
    break;

  case 530: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1857 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 531: // $@77: %empty
#line 1863 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp6_parser.cc"
    break;

  case 532: // space: "space" $@77 ":" "constant string"
#line 1866 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3072 "dhcp6_parser.cc"
    break;

  case 534: // $@78: %empty
#line 1874 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3081 "dhcp6_parser.cc"
    break;

  case 535: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1877 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3091 "dhcp6_parser.cc"
    break;

  case 536: // option_def_array: "array" ":" "boolean"
#line 1883 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3101 "dhcp6_parser.cc"
    break;

  case 537: // $@79: %empty
#line 1893 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3113 "dhcp6_parser.cc"
    break;

  case 538: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1899 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3122 "dhcp6_parser.cc"
    break;

  case 543: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1914 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3130 "dhcp6_parser.cc"
    break;

  case 544: // $@80: %empty
#line 1921 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 545: // option_data_entry: "{" $@80 option_data_params "}"
#line 1925 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 546: // $@81: %empty
#line 1933 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 547: // sub_option_data: "{" $@81 option_data_params "}"
#line 1937 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 552: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1953 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3176 "dhcp6_parser.cc"
    break;

  case 563: // $@82: %empty
#line 1973 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp6_parser.cc"
    break;

  case 564: // option_data_data: "data" $@82 ":" "constant string"
#line 1976 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 567: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1986 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3205 "dhcp6_parser.cc"
    break;

  case 568: // option_data_always_send: "always-send" ":" "boolean"
#line 1992 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3215 "dhcp6_parser.cc"
    break;

  case 569: // $@83: %empty
#line 2001 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3227 "dhcp6_parser.cc"
    break;

  case 570: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2007 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 575: // not_empty_pools_list: not_empty_pools_list ","
#line 2020 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3244 "dhcp6_parser.cc"
    break;

  case 576: // $@84: %empty
#line 2025 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3254 "dhcp6_parser.cc"
    break;

  case 577: // pool_list_entry: "{" $@84 pool_params "}"
#line 2029 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3264 "dhcp6_parser.cc"
    break;

  case 578: // $@85: %empty
#line 2035 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 579: // sub_pool6: "{" $@85 pool_params "}"
#line 2039 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 582: // pool_params: pool_params ","
#line 2047 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3292 "dhcp6_parser.cc"
    break;

  case 590: // $@86: %empty
#line 2061 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp6_parser.cc"
    break;

  case 591: // pool_entry: "pool" $@86 ":" "constant string"
#line 2064 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3311 "dhcp6_parser.cc"
    break;

  case 592: // $@87: %empty
#line 2070 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp6_parser.cc"
    break;

  case 593: // user_context: "user-context" $@87 ":" map_value
#line 2072 "dhcp6_parser.yy"
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
#line 3346 "dhcp6_parser.cc"
    break;

  case 594: // $@88: %empty
#line 2095 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3354 "dhcp6_parser.cc"
    break;

  case 595: // comment: "comment" $@88 ":" "constant string"
#line 2097 "dhcp6_parser.yy"
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
#line 3383 "dhcp6_parser.cc"
    break;

  case 596: // $@89: %empty
#line 2125 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3395 "dhcp6_parser.cc"
    break;

  case 597: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2131 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 602: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2144 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3412 "dhcp6_parser.cc"
    break;

  case 603: // $@90: %empty
#line 2149 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3422 "dhcp6_parser.cc"
    break;

  case 604: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2153 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3434 "dhcp6_parser.cc"
    break;

  case 605: // $@91: %empty
#line 2161 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3444 "dhcp6_parser.cc"
    break;

  case 606: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2165 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3456 "dhcp6_parser.cc"
    break;

  case 609: // pd_pool_params: pd_pool_params ","
#line 2175 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3464 "dhcp6_parser.cc"
    break;

  case 621: // $@92: %empty
#line 2193 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3473 "dhcp6_parser.cc"
    break;

  case 622: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2196 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3483 "dhcp6_parser.cc"
    break;

  case 623: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2202 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3493 "dhcp6_parser.cc"
    break;

  case 624: // $@93: %empty
#line 2208 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3502 "dhcp6_parser.cc"
    break;

  case 625: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2211 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3512 "dhcp6_parser.cc"
    break;

  case 626: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2217 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3522 "dhcp6_parser.cc"
    break;

  case 627: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2223 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3532 "dhcp6_parser.cc"
    break;

  case 628: // $@94: %empty
#line 2232 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 629: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2238 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 634: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2249 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3561 "dhcp6_parser.cc"
    break;

  case 635: // $@95: %empty
#line 2254 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3571 "dhcp6_parser.cc"
    break;

  case 636: // reservation: "{" $@95 reservation_params "}"
#line 2258 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3580 "dhcp6_parser.cc"
    break;

  case 637: // $@96: %empty
#line 2263 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3590 "dhcp6_parser.cc"
    break;

  case 638: // sub_reservation: "{" $@96 reservation_params "}"
#line 2267 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3599 "dhcp6_parser.cc"
    break;

  case 643: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2278 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3607 "dhcp6_parser.cc"
    break;

  case 655: // $@97: %empty
#line 2297 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3619 "dhcp6_parser.cc"
    break;

  case 656: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2303 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3628 "dhcp6_parser.cc"
    break;

  case 657: // $@98: %empty
#line 2308 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3640 "dhcp6_parser.cc"
    break;

  case 658: // prefixes: "prefixes" $@98 ":" list_strings
#line 2314 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 659: // $@99: %empty
#line 2319 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 660: // duid: "duid" $@99 ":" "constant string"
#line 2322 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 661: // $@100: %empty
#line 2328 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 662: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2331 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 663: // $@101: %empty
#line 2337 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 664: // hostname: "hostname" $@101 ":" "constant string"
#line 2340 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 665: // $@102: %empty
#line 2346 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3715 "dhcp6_parser.cc"
    break;

  case 666: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2349 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3725 "dhcp6_parser.cc"
    break;

  case 667: // $@103: %empty
#line 2355 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 668: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2361 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 669: // $@104: %empty
#line 2369 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 670: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2375 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 673: // $@105: %empty
#line 2384 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 674: // ip_address: "ip-address" $@105 ":" "constant string"
#line 2387 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 675: // $@106: %empty
#line 2396 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 676: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2402 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 679: // client_classes_list: client_classes_list ","
#line 2409 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3815 "dhcp6_parser.cc"
    break;

  case 680: // $@107: %empty
#line 2414 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3825 "dhcp6_parser.cc"
    break;

  case 681: // client_class_entry: "{" $@107 client_class_params "}"
#line 2418 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3835 "dhcp6_parser.cc"
    break;

  case 686: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2430 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3843 "dhcp6_parser.cc"
    break;

  case 702: // $@108: %empty
#line 2453 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 703: // client_class_test: "test" $@108 ":" "constant string"
#line 2456 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3862 "dhcp6_parser.cc"
    break;

  case 704: // $@109: %empty
#line 2462 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3871 "dhcp6_parser.cc"
    break;

  case 705: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2465 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 706: // only_if_required: "only-if-required" ":" "boolean"
#line 2471 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3891 "dhcp6_parser.cc"
    break;

  case 707: // $@110: %empty
#line 2480 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 708: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2486 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3914 "dhcp6_parser.cc"
    break;

  case 711: // server_id_params: server_id_params ","
#line 2495 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3922 "dhcp6_parser.cc"
    break;

  case 721: // $@111: %empty
#line 2511 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3931 "dhcp6_parser.cc"
    break;

  case 722: // server_id_type: "type" $@111 ":" duid_type
#line 2514 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 723: // duid_type: "LLT"
#line 2519 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3946 "dhcp6_parser.cc"
    break;

  case 724: // duid_type: "EN"
#line 2520 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3952 "dhcp6_parser.cc"
    break;

  case 725: // duid_type: "LL"
#line 2521 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3958 "dhcp6_parser.cc"
    break;

  case 726: // htype: "htype" ":" "integer"
#line 2524 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3968 "dhcp6_parser.cc"
    break;

  case 727: // $@112: %empty
#line 2530 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3977 "dhcp6_parser.cc"
    break;

  case 728: // identifier: "identifier" $@112 ":" "constant string"
#line 2533 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3987 "dhcp6_parser.cc"
    break;

  case 729: // time: "time" ":" "integer"
#line 2539 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3997 "dhcp6_parser.cc"
    break;

  case 730: // enterprise_id: "enterprise-id" ":" "integer"
#line 2545 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4007 "dhcp6_parser.cc"
    break;

  case 731: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2553 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4017 "dhcp6_parser.cc"
    break;

  case 732: // $@113: %empty
#line 2561 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 733: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2567 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4038 "dhcp6_parser.cc"
    break;

  case 736: // control_socket_params: control_socket_params ","
#line 2574 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4046 "dhcp6_parser.cc"
    break;

  case 742: // $@114: %empty
#line 2586 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4055 "dhcp6_parser.cc"
    break;

  case 743: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2589 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4065 "dhcp6_parser.cc"
    break;

  case 744: // $@115: %empty
#line 2595 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4074 "dhcp6_parser.cc"
    break;

  case 745: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2598 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4084 "dhcp6_parser.cc"
    break;

  case 746: // $@116: %empty
#line 2607 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4096 "dhcp6_parser.cc"
    break;

  case 747: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2613 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 750: // queue_control_params: queue_control_params ","
#line 2622 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4115 "dhcp6_parser.cc"
    break;

  case 757: // enable_queue: "enable-queue" ":" "boolean"
#line 2635 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4125 "dhcp6_parser.cc"
    break;

  case 758: // $@117: %empty
#line 2641 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4134 "dhcp6_parser.cc"
    break;

  case 759: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2644 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4144 "dhcp6_parser.cc"
    break;

  case 760: // capacity: "capacity" ":" "integer"
#line 2650 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4154 "dhcp6_parser.cc"
    break;

  case 761: // $@118: %empty
#line 2656 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4163 "dhcp6_parser.cc"
    break;

  case 762: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2659 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4172 "dhcp6_parser.cc"
    break;

  case 763: // $@119: %empty
#line 2666 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4184 "dhcp6_parser.cc"
    break;

  case 764: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2672 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 765: // $@120: %empty
#line 2679 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 766: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2683 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4215 "dhcp6_parser.cc"
    break;

  case 769: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2691 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4223 "dhcp6_parser.cc"
    break;

  case 788: // enable_updates: "enable-updates" ":" "boolean"
#line 2716 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4233 "dhcp6_parser.cc"
    break;

  case 789: // $@121: %empty
#line 2723 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4242 "dhcp6_parser.cc"
    break;

  case 790: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2726 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4252 "dhcp6_parser.cc"
    break;

  case 791: // $@122: %empty
#line 2732 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4261 "dhcp6_parser.cc"
    break;

  case 792: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2735 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4271 "dhcp6_parser.cc"
    break;

  case 793: // server_port: "server-port" ":" "integer"
#line 2741 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4281 "dhcp6_parser.cc"
    break;

  case 794: // $@123: %empty
#line 2747 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4290 "dhcp6_parser.cc"
    break;

  case 795: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2750 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4300 "dhcp6_parser.cc"
    break;

  case 796: // sender_port: "sender-port" ":" "integer"
#line 2756 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4310 "dhcp6_parser.cc"
    break;

  case 797: // max_queue_size: "max-queue-size" ":" "integer"
#line 2762 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4320 "dhcp6_parser.cc"
    break;

  case 798: // $@124: %empty
#line 2768 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4329 "dhcp6_parser.cc"
    break;

  case 799: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2771 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4338 "dhcp6_parser.cc"
    break;

  case 800: // ncr_protocol_value: "UDP"
#line 2777 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4344 "dhcp6_parser.cc"
    break;

  case 801: // ncr_protocol_value: "TCP"
#line 2778 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4350 "dhcp6_parser.cc"
    break;

  case 802: // $@125: %empty
#line 2781 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 803: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2784 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 804: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2791 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4379 "dhcp6_parser.cc"
    break;

  case 805: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2798 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4389 "dhcp6_parser.cc"
    break;

  case 806: // $@126: %empty
#line 2805 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4398 "dhcp6_parser.cc"
    break;

  case 807: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2808 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 808: // $@127: %empty
#line 2814 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4416 "dhcp6_parser.cc"
    break;

  case 809: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2817 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4426 "dhcp6_parser.cc"
    break;

  case 810: // $@128: %empty
#line 2824 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4435 "dhcp6_parser.cc"
    break;

  case 811: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2827 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4445 "dhcp6_parser.cc"
    break;

  case 812: // $@129: %empty
#line 2834 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4454 "dhcp6_parser.cc"
    break;

  case 813: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2837 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4464 "dhcp6_parser.cc"
    break;

  case 814: // $@130: %empty
#line 2846 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4476 "dhcp6_parser.cc"
    break;

  case 815: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2852 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4486 "dhcp6_parser.cc"
    break;

  case 816: // $@131: %empty
#line 2858 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4496 "dhcp6_parser.cc"
    break;

  case 817: // sub_config_control: "{" $@131 config_control_params "}"
#line 2862 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4505 "dhcp6_parser.cc"
    break;

  case 820: // config_control_params: config_control_params ","
#line 2870 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4513 "dhcp6_parser.cc"
    break;

  case 823: // $@132: %empty
#line 2880 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4525 "dhcp6_parser.cc"
    break;

  case 824: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2886 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4534 "dhcp6_parser.cc"
    break;

  case 825: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2891 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4544 "dhcp6_parser.cc"
    break;

  case 826: // $@133: %empty
#line 2899 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 827: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2905 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4565 "dhcp6_parser.cc"
    break;

  case 830: // loggers_entries: loggers_entries ","
#line 2914 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4573 "dhcp6_parser.cc"
    break;

  case 831: // $@134: %empty
#line 2920 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4583 "dhcp6_parser.cc"
    break;

  case 832: // logger_entry: "{" $@134 logger_params "}"
#line 2924 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4591 "dhcp6_parser.cc"
    break;

  case 835: // logger_params: logger_params ","
#line 2930 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4599 "dhcp6_parser.cc"
    break;

  case 843: // debuglevel: "debuglevel" ":" "integer"
#line 2944 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 844: // $@135: %empty
#line 2950 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 845: // severity: "severity" $@135 ":" "constant string"
#line 2953 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4628 "dhcp6_parser.cc"
    break;

  case 846: // $@136: %empty
#line 2959 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4640 "dhcp6_parser.cc"
    break;

  case 847: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 2965 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4649 "dhcp6_parser.cc"
    break;

  case 850: // output_options_list_content: output_options_list_content ","
#line 2972 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4657 "dhcp6_parser.cc"
    break;

  case 851: // $@137: %empty
#line 2977 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4667 "dhcp6_parser.cc"
    break;

  case 852: // output_entry: "{" $@137 output_params_list "}"
#line 2981 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4675 "dhcp6_parser.cc"
    break;

  case 855: // output_params_list: output_params_list ","
#line 2987 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4683 "dhcp6_parser.cc"
    break;

  case 861: // $@138: %empty
#line 2999 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4692 "dhcp6_parser.cc"
    break;

  case 862: // output: "output" $@138 ":" "constant string"
#line 3002 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4702 "dhcp6_parser.cc"
    break;

  case 863: // flush: "flush" ":" "boolean"
#line 3008 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4712 "dhcp6_parser.cc"
    break;

  case 864: // maxsize: "maxsize" ":" "integer"
#line 3014 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4722 "dhcp6_parser.cc"
    break;

  case 865: // maxver: "maxver" ":" "integer"
#line 3020 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4732 "dhcp6_parser.cc"
    break;

  case 866: // $@139: %empty
#line 3026 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4741 "dhcp6_parser.cc"
    break;

  case 867: // pattern: "pattern" $@139 ":" "constant string"
#line 3029 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4751 "dhcp6_parser.cc"
    break;

  case 868: // $@140: %empty
#line 3035 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4763 "dhcp6_parser.cc"
    break;

  case 869: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3041 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4772 "dhcp6_parser.cc"
    break;

  case 872: // compatibility_params: compatibility_params ","
#line 3048 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4780 "dhcp6_parser.cc"
    break;

  case 875: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3057 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4790 "dhcp6_parser.cc"
    break;


#line 4794 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1009;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     446, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,    50,    35,    70,    83,    94,
     104,   112,   133,   161,   163,   178,   184,   254,   265,   271,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,    35,  -159,
      73,   171,    46,   687,   173,    -1,   264,   -17,   253,   119,
     -89,   460,   134, -1009,   281,   288,   299,   293,   322, -1009,
      53, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   324,   334,
     348,   350,   376,   401,   414,   423,   425,   428,   434,   435,
     436,   437, -1009,   438,   440,   441,   442,   447, -1009, -1009,
   -1009,   448,   449,   450, -1009, -1009, -1009,   451, -1009, -1009,
   -1009, -1009, -1009, -1009,   452,   453,   454, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   455, -1009, -1009, -1009,
   -1009, -1009, -1009,   456,   462,   464, -1009, -1009,   465, -1009,
     101, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   466,
     467,   470,   471, -1009,   120, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   473,   475,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     126, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,   128, -1009, -1009, -1009, -1009,
   -1009,   477, -1009,   481,   482, -1009, -1009, -1009, -1009, -1009,
   -1009,   138, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   318,
     361, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   408,
   -1009, -1009,   484, -1009, -1009, -1009,   485, -1009, -1009,   487,
     381, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   492,   494, -1009, -1009, -1009, -1009,
     491,   461, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   148, -1009, -1009, -1009,   496, -1009,
   -1009,   498, -1009,   500,   501, -1009, -1009,   503,   506, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   198, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   508,   199, -1009, -1009, -1009, -1009,
      35,    35, -1009,   301,   509, -1009, -1009,   512,   517,   519,
     520,   521,   522,   314,   317,   319,   320,   321,   323,   329,
     330,   325,   315,   335,   336,   339,   340,   533,   344,   346,
     326,   347,   351,   535,   552,   565,   354,   355,   356,   571,
     572,   574,   364,   578,   579,   582,   584,   585,   586,   374,
     377,   379,   589,   596,   597,   599,   600,   602,   603,   604,
     607,   398,   610,   611,   613,   614,   615,   616,   404,   420,
     421,   618,   635, -1009,   171, -1009,   636,   424,   426,   427,
     445,    46, -1009,   657,   659,   660,   662,   663,   457,   458,
     664,   665,   666,   687, -1009,   667,   173, -1009,   669,   463,
     673,   468,   469,    -1, -1009,   675,   676,   677,   678,   681,
     682,   683, -1009,   264, -1009,   684,   685,   476,   686,   688,
     689,   478, -1009,   253,   690,   479,   480, -1009,   119,   694,
     695,   -67, -1009,   486,   701,   702,   495,   703,   502,   504,
     705,   712,   507,   510,   714,   716,   717,   719,   460, -1009,
     721,   511,   134, -1009, -1009, -1009,   724,   722,   516,   725,
     740,   741,   742,   726, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   536, -1009,
   -1009, -1009, -1009, -1009,  -101,   546,   547, -1009, -1009, -1009,
     758,   759,   760, -1009,   553,   561,   761,   770,   566,   328,
   -1009, -1009, -1009,   774,   776,   777,   785,   778,   788,   789,
     792,   793, -1009,   794,   795,   796,   797,   581,   591, -1009,
   -1009, -1009,   802,   801, -1009,   804, -1009, -1009, -1009, -1009,
   -1009,   807,   808,   601,   605,   606, -1009, -1009,   804,   608,
     809, -1009,   609, -1009,   612, -1009,   617, -1009, -1009, -1009,
     804,   804,   804,   619,   620,   621,   622, -1009,   623,   624,
   -1009,   625,   626,   627, -1009, -1009,   628, -1009, -1009, -1009,
     629,   770, -1009, -1009,   630,   631, -1009,   632, -1009, -1009,
     164,   638, -1009, -1009,  -101,   633,   634,   637, -1009,   816,
   -1009, -1009,    35,   171, -1009,   134,    46,   129,   129,   817,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   818,
     820,   821, -1009, -1009,   822, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,   -88,    35,    84,   137,   823,   825,   842,
      39,   223,   212,   -45,   249,   460, -1009, -1009,   843,  -156,
   -1009, -1009,   845,   846, -1009, -1009, -1009, -1009, -1009,   -78,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   817,
   -1009,   200,   201,   207, -1009, -1009, -1009, -1009,   810,   850,
     851,   852,   853,   854,   855, -1009,   856, -1009, -1009, -1009,
   -1009, -1009,   285, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009,   291, -1009,   857,   858, -1009, -1009,   859,   861,
   -1009, -1009,   860,   864, -1009, -1009,   862,   866, -1009, -1009,
     867,   871, -1009, -1009, -1009,    45, -1009, -1009, -1009,   869,
   -1009, -1009, -1009,   102, -1009, -1009, -1009, -1009, -1009,   294,
   -1009, -1009, -1009, -1009,   127, -1009, -1009,   870,   874, -1009,
   -1009,   872,   876, -1009,   877,   878,   879,   880,   881,   882,
     297, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     883,   884,   885, -1009, -1009, -1009, -1009,   310, -1009, -1009,
   -1009, -1009, -1009, -1009,   886,   887,   888, -1009,   316, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     337, -1009, -1009, -1009,   889, -1009,   890, -1009, -1009, -1009,
     341, -1009, -1009, -1009, -1009, -1009,   345, -1009,   259, -1009,
     891, -1009,   360, -1009, -1009,   648, -1009,   892,   893, -1009,
   -1009,   894,   896, -1009, -1009, -1009,   895, -1009,   898, -1009,
   -1009, -1009,   901,   902,   903,   904,   655,   680,   696,   692,
     697,   698,   699,   906,   700,   912,   913,   914,   915,   129,
   -1009, -1009,   129, -1009,   817,   687, -1009,   818,   253, -1009,
     820,   119, -1009,   821,  1076, -1009,   822,   -88, -1009, -1009,
      84, -1009,   916,   917,   137, -1009,   327,   823, -1009,   264,
   -1009,   825,   -89, -1009,   842,   707,   708,   709,   710,   711,
     713,    39, -1009,   923,   925,   715,   718,   720,   223, -1009,
     723,   727,   728,   212, -1009,   927,   928,   -45, -1009,   729,
     930,   730,   932,   249, -1009, -1009,   214,   843, -1009,   731,
    -156, -1009, -1009,   931,   899,   173, -1009,   845,    -1, -1009,
     846,   934, -1009, -1009,   290,   733,   735,   736, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,   358, -1009,   737,   738,   739,
     744, -1009,   378, -1009,   380, -1009,   933, -1009,   936, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   392, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009,   745,   747, -1009,
   -1009, -1009,   935, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   947,   953, -1009, -1009, -1009, -1009,
   -1009, -1009,   954, -1009,   393, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,   277,   750, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,   752,   753, -1009, -1009,   756, -1009,    35,
   -1009, -1009,   969, -1009, -1009, -1009, -1009, -1009,   405, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009,   766,   409, -1009,
     411, -1009,   780, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009,  1076, -1009, -1009, -1009,   980,   991,   779, -1009,
     327, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009,   994,   784,  1005,   214, -1009, -1009, -1009, -1009,
   -1009, -1009,   800,   815, -1009, -1009,   875, -1009,   828, -1009,
   -1009, -1009,  1009, -1009, -1009,   273, -1009,    -7,  1009, -1009,
   -1009,  1014,  1026,  1030, -1009,   412, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,  1032,   830,   836,   837,  1033,    -7, -1009,
     863, -1009, -1009, -1009,   905, -1009, -1009, -1009
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   190,     9,   371,    11,
     578,    13,   605,    15,   637,    17,   498,    19,   507,    21,
     546,    23,   333,    25,   765,    27,   816,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   639,     0,   509,   548,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   139,   814,   188,   209,   211,   213,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,     0,     0,     0,     0,     0,   158,   165,
     167,     0,     0,     0,   362,   496,   537,     0,   181,   183,
     442,   592,   594,   434,     0,     0,     0,   289,   308,   298,
     278,   675,   628,   324,   345,   707,     0,   310,   732,   746,
     763,   171,   173,     0,     0,     0,   826,   868,     0,   138,
       0,    69,    72,    73,    74,    75,    76,    77,    78,    79,
      80,   111,   112,   113,   114,   115,    81,   119,   120,   121,
     122,   123,   124,   125,   126,   117,   118,   127,   128,   129,
     106,   135,   136,   137,   131,   132,   133,    84,    85,    86,
      87,   103,    88,    90,    89,   130,    94,    95,    82,   108,
     109,   110,   107,    83,    92,    93,   101,   102,   104,    91,
      96,    97,    98,    99,   100,   105,   116,   134,   203,     0,
       0,     0,     0,   202,     0,   192,   195,   196,   197,   198,
     199,   200,   201,   569,   596,   421,   423,   425,     0,     0,
     429,   427,   669,   420,   376,   377,   378,   379,   380,   381,
     382,   383,   402,   403,   404,   405,   406,   409,   410,   411,
     412,   413,   414,   415,   416,   407,   408,   417,   418,   419,
       0,   373,   387,   388,   389,   392,   393,   396,   397,   398,
     395,   390,   391,   384,   385,   400,   401,   386,   394,   399,
     590,   589,   585,   586,   584,     0,   580,   583,   587,   588,
     621,     0,   624,     0,     0,   620,   614,   615,   613,   618,
     619,     0,   607,   610,   611,   616,   617,   612,   667,   655,
     657,   659,   661,   663,   665,   654,   651,   652,   653,     0,
     640,   641,   646,   647,   644,   648,   649,   650,   645,     0,
     527,   256,     0,   531,   529,   534,     0,   523,   524,     0,
     510,   511,   514,   526,   515,   516,   517,   533,   518,   519,
     520,   521,   522,   563,     0,     0,   561,   562,   565,   566,
       0,   549,   550,   553,   554,   555,   556,   557,   558,   559,
     560,   341,   343,   338,     0,   335,   339,   340,     0,   789,
     791,     0,   794,     0,     0,   798,   802,     0,     0,   806,
     808,   810,   812,   787,   785,   786,     0,   767,   770,   782,
     771,   772,   773,   774,   775,   776,   777,   778,   779,   780,
     781,   783,   784,   823,     0,     0,   818,   821,   822,    47,
      52,     0,    39,    45,     0,    66,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   194,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   375,   372,     0,   582,   579,     0,     0,
       0,     0,     0,   609,   606,     0,     0,     0,     0,     0,
       0,     0,   638,   643,   499,     0,     0,     0,     0,     0,
       0,     0,   508,   513,     0,     0,     0,   547,   552,     0,
       0,   337,   334,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   769,   766,
       0,     0,   820,   817,    51,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,     0,   176,
     177,   155,   156,   157,     0,     0,     0,   169,   170,   175,
       0,     0,     0,   180,     0,     0,     0,     0,     0,     0,
     431,   432,   433,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   731,     0,     0,     0,     0,     0,     0,   185,
     186,   187,     0,     0,    70,     0,   205,   206,   207,   208,
     193,     0,     0,     0,     0,     0,   440,   441,     0,     0,
       0,   374,     0,   581,     0,   623,     0,   626,   627,   608,
       0,     0,     0,     0,     0,     0,     0,   642,     0,     0,
     525,     0,     0,     0,   536,   512,     0,   567,   568,   551,
       0,     0,   336,   788,     0,     0,   793,     0,   796,   797,
       0,     0,   804,   805,     0,     0,     0,     0,   768,     0,
     825,   819,     0,     0,   140,     0,     0,     0,     0,   215,
     179,   160,   161,   162,   163,   164,   159,   166,   168,   364,
     500,   539,   182,   184,   444,    40,   593,   595,   436,   437,
     438,   439,   435,     0,    48,     0,     0,     0,   630,   326,
       0,     0,     0,     0,     0,     0,   172,   174,     0,     0,
      53,   204,   571,   598,   422,   424,   426,   430,   428,     0,
     591,   622,   625,   668,   656,   658,   660,   662,   664,   666,
     528,   257,   532,   530,   535,   564,   342,   344,   790,   792,
     795,   800,   801,   799,   803,   807,   809,   811,   813,   215,
      44,     0,     0,     0,   244,   249,   251,   253,     0,     0,
       0,     0,     0,     0,     0,   263,     0,   270,   272,   274,
     276,   243,     0,   222,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   236,   237,   238,   235,   239,   240,
     241,   242,     0,   220,     0,   216,   217,   369,     0,   365,
     366,   505,     0,   501,   502,   544,     0,   540,   541,   449,
       0,   445,   446,   296,   297,     0,   291,   294,   295,     0,
     306,   307,   303,     0,   300,   304,   305,   285,   287,     0,
     280,   283,   284,   680,     0,   677,   635,     0,   631,   632,
     331,     0,   327,   328,     0,     0,     0,     0,     0,     0,
       0,   347,   350,   351,   352,   353,   354,   355,   721,   727,
       0,     0,     0,   720,   717,   718,   719,     0,   709,   712,
     715,   713,   714,   716,     0,     0,     0,   320,     0,   312,
     315,   316,   317,   318,   319,   742,   744,   741,   739,   740,
       0,   734,   737,   738,     0,   758,     0,   761,   754,   755,
       0,   748,   751,   752,   753,   756,     0,   831,     0,   828,
       0,   874,     0,   870,   873,    55,   576,     0,   572,   573,
     603,     0,   599,   600,   673,   672,     0,   671,     0,    64,
     815,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   224,
     210,   212,     0,   214,   219,     0,   363,   368,   509,   497,
     504,   548,   538,   543,     0,   443,   448,   293,   290,   309,
     302,   299,     0,     0,   282,   279,   682,   679,   676,   639,
     629,   634,     0,   325,   330,     0,     0,     0,     0,     0,
       0,   349,   346,     0,     0,     0,     0,     0,   711,   708,
       0,     0,     0,   314,   311,     0,     0,   736,   733,     0,
       0,     0,     0,   750,   747,   764,     0,   830,   827,     0,
     872,   869,    57,     0,    56,     0,   570,   575,     0,   597,
     602,     0,   670,   824,     0,     0,     0,     0,   255,   258,
     259,   260,   261,   269,   262,     0,   268,     0,     0,     0,
       0,   223,     0,   218,     0,   367,     0,   503,     0,   542,
     495,   468,   469,   470,   472,   473,   474,   458,   459,   477,
     478,   479,   480,   481,   484,   485,   486,   487,   488,   489,
     490,   491,   482,   483,   492,   493,   494,   454,   455,   456,
     457,   466,   467,   463,   464,   465,   462,   471,     0,   451,
     460,   475,   476,   461,   447,   292,   301,     0,     0,   281,
     702,   704,     0,   700,   694,   695,   696,   697,   698,   699,
     701,   691,   692,   693,     0,   683,   684,   687,   688,   689,
     690,   678,     0,   633,     0,   329,   356,   357,   358,   359,
     360,   361,   348,     0,     0,   726,   729,   730,   710,   321,
     322,   323,   313,     0,     0,   735,   757,     0,   760,     0,
     749,   846,     0,   844,   842,   836,   840,   841,     0,   833,
     838,   839,   837,   829,   875,   871,    54,    59,     0,   574,
       0,   601,     0,   246,   247,   248,   245,   250,   252,   254,
     265,   266,   267,   264,   271,   273,   275,   277,   221,   370,
     506,   545,   453,   450,   286,   288,     0,     0,     0,   681,
     686,   636,   332,   723,   724,   725,   722,   728,   743,   745,
     759,   762,     0,     0,     0,   835,   832,    58,   577,   604,
     674,   452,     0,     0,   706,   685,     0,   843,     0,   834,
     703,   705,     0,   845,   851,     0,   848,     0,   850,   847,
     861,     0,     0,     0,   866,     0,   853,   856,   857,   858,
     859,   860,   849,     0,     0,     0,     0,     0,   855,   852,
       0,   863,   864,   865,     0,   854,   862,   867
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   -10, -1009,  -596, -1009,
     375, -1009, -1009, -1009, -1009,   343, -1009,  -592, -1009, -1009,
   -1009,   -71, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   382,
     543, -1009, -1009,   -46,   -43,   -14,   -13,    14,    15,   -49,
     -24,    16,    29,    30,    33,    34, -1009,    37,    41,    44,
      47, -1009,   385,    48, -1009,    51, -1009,    54,    59,    62,
   -1009,    64, -1009,    65, -1009, -1009, -1009, -1009, -1009,    66,
   -1009,    69, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     384,   595, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   298, -1009,    88, -1009,  -716,    99,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
     -41, -1009,  -760, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,    78, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009,   100,  -742, -1009, -1009, -1009, -1009,    81, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,    63, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,    85, -1009, -1009, -1009,    86,   583, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,    89, -1009, -1009, -1009,
   -1009, -1009, -1009, -1008, -1009, -1009, -1009,   130, -1009, -1009,
   -1009,   131,   639, -1009, -1009, -1006, -1009, -1005, -1009,    10,
   -1009,    80, -1009,    72,    76,    77,    79, -1009, -1009, -1009,
    -999, -1009, -1009, -1009, -1009,   117, -1009, -1009,  -117,  1081,
   -1009, -1009, -1009, -1009, -1009,   135, -1009, -1009, -1009,   132,
   -1009,   598, -1009,   -62, -1009, -1009, -1009, -1009, -1009,   -54,
   -1009, -1009, -1009, -1009, -1009,   -42, -1009, -1009, -1009,   136,
   -1009, -1009, -1009,   139, -1009,   640, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009,    67, -1009, -1009,
   -1009,    71,   645, -1009, -1009,   -60, -1009,    -3, -1009, -1009,
   -1009, -1009, -1009,    68, -1009, -1009, -1009,    61,   641, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   -53, -1009, -1009, -1009,
     116, -1009, -1009, -1009,   122, -1009,   643,   394, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009,  -998, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   141,
   -1009, -1009, -1009,   -98, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009,   121, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   113, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009,   108, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009,   417,   644, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009,   459,   649, -1009, -1009,
   -1009, -1009, -1009, -1009,   106, -1009, -1009,   -97, -1009, -1009,
   -1009, -1009, -1009, -1009,  -121, -1009, -1009,  -138, -1009, -1009,
   -1009, -1009, -1009, -1009, -1009, -1009, -1009, -1009,   114, -1009
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     756,    87,    88,    41,    68,    84,    85,   781,   985,  1093,
    1094,   841,    43,    70,    90,   444,    91,    45,    71,   160,
     161,   162,   447,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   473,   746,   181,   474,   182,   475,   183,   184,   185,
     506,   186,   507,   187,   188,   189,   190,   467,   191,   192,
     483,   193,   484,   194,   195,   196,   197,   449,    47,    72,
     234,   235,   236,   516,   237,   238,   239,   240,   198,   450,
     199,   451,   200,   452,   864,   865,   866,  1022,   842,   843,
     844,  1002,  1256,   845,  1003,   846,  1004,   847,  1005,   848,
     849,   556,   850,   851,   852,   853,   854,   855,  1013,  1263,
     856,   857,   858,  1015,   859,  1016,   860,  1017,   861,  1018,
     201,   495,   899,   900,   901,  1042,   902,  1043,   202,   492,
     885,   886,   887,   888,   203,   494,   893,   894,   895,   896,
     204,   493,   205,   502,   948,   949,   950,   951,   952,   206,
     498,   911,   912,   913,  1052,    63,    80,   394,   395,   396,
     569,   397,   570,   207,   499,   920,   921,   922,   923,   924,
     925,   926,   927,   208,   479,   868,   869,   870,  1025,    49,
      73,   280,   281,   282,   525,   283,   526,   284,   527,   285,
     531,   286,   530,   209,   210,   211,   212,   488,   762,   291,
     292,   213,   485,   880,   881,   882,  1034,  1168,  1169,   214,
     480,    57,    77,   872,   873,   874,  1028,    59,    78,   359,
     360,   361,   362,   363,   364,   365,   555,   366,   559,   367,
     558,   368,   369,   560,   370,   215,   481,   876,   877,   878,
    1031,    61,    79,   380,   381,   382,   383,   384,   564,   385,
     386,   387,   388,   294,   523,   987,   988,   989,  1095,    51,
      74,   305,   306,   307,   535,   216,   486,   217,   487,   297,
     524,   991,   992,   993,  1098,    53,    75,   321,   322,   323,
     538,   324,   325,   540,   326,   327,   218,   497,   907,   908,
     909,  1049,    55,    76,   339,   340,   341,   342,   546,   343,
     547,   344,   548,   345,   549,   346,   550,   347,   551,   348,
     545,   299,   532,   996,   997,  1101,   219,   496,   904,   905,
    1046,  1194,  1195,  1196,  1197,  1198,  1276,  1199,  1277,  1200,
     220,   500,   937,   938,   939,  1063,  1286,   940,   941,  1064,
     942,   943,   221,   222,   503,   960,   961,   962,  1075,   963,
    1076,   223,   504,   970,   971,   972,   973,  1080,   974,   975,
    1082,   224,   505,    65,    81,   416,   417,   418,   419,   574,
     420,   575,   421,   422,   577,   423,   424,   425,   580,   813,
     426,   581,   427,   428,   429,   584,   430,   585,   431,   586,
     432,   587,   225,   448,    67,    82,   435,   436,   437,   590,
     438,   226,   511,   978,   979,  1086,  1238,  1239,  1240,  1241,
    1294,  1242,  1292,  1315,  1316,  1317,  1325,  1326,  1327,  1333,
    1328,  1329,  1330,  1331,  1337,   227,   512,   982,   983,   984
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     159,   233,   253,   301,   315,   335,    38,   357,   376,   393,
     413,   934,   241,   295,   308,   319,   337,   378,   371,   389,
     298,   414,   862,   892,   260,   379,  1158,   254,  1159,  1160,
     255,   293,   304,   318,   336,  1167,  1173,   358,   377,   883,
      31,   755,    32,   980,    33,   391,   392,   329,  1037,   261,
      30,  1038,   131,   132,   994,    86,   445,   125,   158,   256,
     257,   446,   228,   229,   230,   231,   232,   391,   392,   242,
     296,   309,   320,   338,   126,   372,   390,    42,   415,   741,
     742,   743,   744,    89,   302,   316,   787,   258,   259,   262,
      44,   310,   311,   312,   313,   314,   131,   132,   793,   794,
     795,    46,   263,   264,   514,  1040,   265,   266,  1041,   515,
     267,    48,   955,   956,   268,   755,   745,   269,   250,    50,
     270,   271,   251,   521,   272,   158,   884,   273,   522,   533,
    1047,   536,   274,  1048,   534,   275,   537,   276,   277,   278,
      52,   543,   279,   131,   132,   287,   544,   433,   434,   288,
     289,   571,   290,   824,   303,   317,   572,   825,   826,   827,
     828,   829,   830,   831,   832,   833,   834,   835,    54,   158,
      56,   836,   837,   838,   839,   840,   914,   915,   916,   917,
     918,   919,    92,    93,  1320,    58,    94,  1321,  1322,  1323,
    1324,    60,    95,    96,    97,   351,   373,   352,   353,   374,
     375,   588,   592,   514,   592,   351,   589,   593,   999,  1000,
     521,   883,   890,   158,   891,  1001,   131,   132,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   928,   126,    34,
      35,    36,    37,   897,   898,   829,   127,   128,   129,   130,
     158,    62,  1087,   300,  1158,  1088,  1159,  1160,   131,   132,
     131,   132,    64,  1167,  1173,   133,  1318,   350,    66,  1319,
     134,   135,   136,   137,   138,   139,   140,   439,  1019,   141,
     351,   440,   250,  1020,  1019,   142,   251,  1044,   892,  1021,
    1061,   442,  1045,   441,   143,  1062,  1122,   144,   934,   131,
     132,   131,   132,  1068,   145,  1253,  1254,  1255,  1069,  1073,
     131,   132,   146,   147,  1074,   443,   552,   148,   453,   351,
     149,   352,   353,   158,   150,   354,   355,   356,   454,   126,
    1077,   811,   812,   158,  1083,  1078,   131,   132,   588,  1084,
     131,   132,   455,  1085,   456,   151,   152,   153,   154,   155,
     156,   131,   132,  1090,   553,   944,   945,   946,  1091,   157,
     929,   930,   931,   932,    98,    99,   100,   101,   102,   103,
     457,  1019,   328,   533,   563,   158,  1268,   158,  1269,   329,
     330,   331,   332,   333,   334,  1272,   571,  1260,  1261,  1262,
    1273,  1282,   126,   351,  1231,   458,  1232,  1233,  1295,   964,
     965,   966,   536,  1296,   543,  1338,   554,  1298,   459,  1299,
    1339,  1283,  1284,  1285,   131,   132,   158,   460,   158,   461,
     594,   595,   462,   758,   759,   760,   761,   158,   463,   464,
     465,   466,   468,   159,   469,   470,   471,  1180,  1181,  1182,
     233,   472,   476,   477,   478,   482,   489,   490,   491,   501,
     508,   241,   253,   967,   568,   301,   509,   158,   510,   513,
     517,   518,   315,   295,   519,   520,   308,   528,   158,   529,
     298,   539,   335,   319,   260,   541,   542,   254,   557,   561,
     255,   293,   357,   337,   304,   562,   565,   376,   566,   567,
     573,   318,   576,   371,   578,   579,   378,   582,   389,   261,
     583,   336,   591,   597,   379,   596,   598,   413,   242,   256,
     257,   599,   358,   600,   601,   602,   603,   377,   414,   604,
     296,   613,   605,   309,   606,   607,   608,   618,   609,   624,
     320,   158,   612,   621,   610,   611,   302,   258,   259,   262,
     338,   614,   615,   316,   616,   617,   625,   131,   132,   619,
     372,   620,   263,   264,   622,   390,   265,   266,   623,   626,
     267,   627,   628,   629,   268,   630,   631,   269,   632,   633,
     270,   271,   634,   635,   272,   415,   636,   273,   637,   638,
     639,   640,   274,   643,   641,   275,   642,   276,   277,   278,
     644,   645,   279,   646,   647,   287,   648,   649,   650,   288,
     289,   651,   290,   652,   653,   654,   303,   655,   656,   657,
     658,   659,   662,   317,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   660,   661,   663,
     665,   666,   668,   667,   411,   412,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     669,   671,   159,   672,   673,   233,   674,   675,   678,   679,
     680,   682,   676,   684,   158,   677,   241,   686,   685,   690,
     691,   692,   693,   687,   688,   694,   695,   696,   698,   699,
     701,   700,   702,   703,   706,   704,   707,   708,   710,   711,
     933,   947,   957,   713,   413,   714,   715,   717,   981,   720,
     716,   935,   953,   958,   968,   414,   721,   718,   724,   719,
     725,   726,   820,   727,   722,   729,   730,   723,   732,   733,
     734,   739,   735,   242,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   736,   737,   738,
     740,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     747,   748,   126,   749,   750,   751,   754,   752,   936,   954,
     959,   969,   415,   128,   129,   753,   243,    32,   244,   763,
     757,   764,   765,   767,   131,   132,   245,   246,   247,   248,
     249,   133,   766,   768,   769,   776,   134,   135,   136,   770,
     771,   772,   773,   774,   775,   777,   250,   778,   779,   780,
     251,   142,   782,   783,  1006,   784,   789,   814,   252,   785,
     786,   819,   788,   790,   863,   867,   791,   871,   875,   879,
     903,   792,   906,   796,   797,   798,   799,   800,   801,   802,
     803,   804,   805,   806,   808,   809,   810,   816,   817,   910,
     977,   818,   986,   990,  1007,  1008,  1009,  1010,  1011,  1012,
    1014,  1024,  1092,  1023,  1027,  1026,  1029,  1030,  1032,  1033,
    1108,   151,   152,  1035,  1036,  1039,  1050,  1051,  1053,  1054,
    1312,  1055,  1056,  1057,  1058,  1059,  1060,  1065,  1066,  1067,
    1070,  1071,  1072,  1079,  1081,  1089,  1097,  1109,  1096,  1100,
    1099,   158,  1247,  1102,  1103,  1104,  1105,  1106,  1107,  1111,
    1115,  1110,  1112,  1113,  1114,  1116,  1117,  1118,  1119,  1120,
    1177,  1178,  1206,  1207,  1208,  1209,  1210,  1213,  1211,  1214,
    1215,  1223,  1224,  1216,  1227,  1217,  1229,  1246,  1252,  1278,
    1219,  1270,  1220,  1221,  1271,  1228,  1226,  1257,  1244,  1258,
    1259,  1264,  1265,  1266,   253,  1279,  1280,   357,  1267,  1274,
     376,  1275,  1281,  1130,  1287,   295,  1288,  1289,   371,   378,
    1290,   389,   298,  1293,  1171,  1183,   260,   379,   335,   254,
    1297,   393,   255,   293,  1302,  1137,  1192,   358,  1131,   337,
     377,  1132,  1170,  1157,  1300,  1303,  1304,   933,  1306,  1307,
    1184,   261,   947,  1185,  1191,  1190,   957,   336,   935,  1308,
    1138,   256,   257,   953,  1310,  1234,  1314,   958,  1334,   981,
    1133,  1134,   296,   968,   301,   372,  1236,   315,   390,  1311,
    1335,  1172,  1186,  1187,  1336,   308,  1340,  1344,   319,   258,
     259,   262,  1313,  1193,  1161,  1235,   338,  1341,  1135,  1136,
    1139,  1342,  1343,   304,   263,   264,   318,   664,   265,   266,
    1188,  1189,   267,  1140,  1141,   936,   268,  1142,  1143,   269,
     954,  1144,   270,   271,   959,  1145,   272,  1346,  1146,   273,
     969,  1147,  1148,  1237,   274,  1149,   807,   275,  1150,   276,
     277,   278,   309,  1151,   279,   320,  1152,   287,  1153,  1154,
    1155,   288,   289,  1156,   290,   302,  1163,   889,   316,   815,
    1164,  1165,  1123,  1166,  1162,   821,   670,   998,  1121,  1347,
     823,  1176,  1179,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,  1222,  1175,  1204,  1205,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
    1212,   126,   351,  1174,   712,  1301,  1124,  1125,   349,  1250,
    1126,   705,   128,   129,  1249,  1127,  1248,  1203,  1251,  1129,
    1128,  1202,   681,   131,   132,   303,   246,   247,   317,   249,
     133,   683,  1305,   995,   689,   134,   135,   136,  1201,  1218,
    1225,  1230,   976,  1243,   822,   250,   697,  1332,  1309,   251,
    1345,  1130,     0,     0,  1245,     0,     0,   252,   709,  1183,
       0,     0,  1171,     0,     0,     0,     0,     0,     0,  1291,
    1192,     0,     0,  1137,  1234,     0,  1131,     0,     0,  1132,
    1170,  1157,   728,     0,  1184,  1236,     0,  1185,  1191,  1190,
       0,   731,     0,     0,     0,     0,     0,     0,  1138,     0,
       0,     0,     0,     0,  1235,     0,     0,     0,  1133,  1134,
     151,   152,     0,     0,     0,     0,  1186,  1187,     0,  1172,
       0,     0,     0,     0,     0,     0,     0,  1193,     0,     0,
       0,     0,  1161,     0,     0,     0,  1135,  1136,  1139,     0,
     158,     0,  1237,     0,  1188,  1189,     0,     0,     0,     0,
       0,  1140,  1141,     0,     0,  1142,  1143,     0,     0,  1144,
       0,     0,     0,  1145,     0,     0,  1146,     0,     0,  1147,
    1148,     0,     0,  1149,     0,     0,  1150,     0,     0,     0,
       0,  1151,     0,     0,  1152,     0,  1153,  1154,  1155,     0,
       0,  1156,     0,     0,  1163,     0,     0,     0,  1164,  1165,
       0,  1166,  1162
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   771,    72,    73,    74,    75,    76,    79,    78,    79,
      73,    81,   738,   765,    73,    79,  1034,    73,  1034,  1034,
      73,    73,    74,    75,    76,  1034,  1034,    78,    79,   127,
       5,   637,     7,   199,     9,   134,   135,   125,     3,    73,
       0,     6,    97,    98,   132,   214,     3,    74,   214,    73,
      73,     8,    16,    17,    18,    19,    20,   134,   135,    72,
      73,    74,    75,    76,    75,    78,    79,     7,    81,   180,
     181,   182,   183,    10,    74,    75,   678,    73,    73,    73,
       7,    92,    93,    94,    95,    96,    97,    98,   690,   691,
     692,     7,    73,    73,     3,     3,    73,    73,     6,     8,
      73,     7,   157,   158,    73,   711,   217,    73,   119,     7,
      73,    73,   123,     3,    73,   214,   214,    73,     8,     3,
       3,     3,    73,     6,     8,    73,     8,    73,    73,    73,
       7,     3,    73,    97,    98,    73,     8,    13,    14,    73,
      73,     3,    73,    24,    74,    75,     8,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,     7,   214,
       7,    42,    43,    44,    45,    46,   137,   138,   139,   140,
     141,   142,    11,    12,   191,     7,    15,   194,   195,   196,
     197,     7,    21,    22,    23,    76,    77,    78,    79,    80,
      81,     3,     3,     3,     3,    76,     8,     8,     8,     8,
       3,   127,   128,   214,   130,     8,    97,    98,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    24,    75,   214,
     215,   216,   217,   116,   117,    32,    85,    86,    87,    88,
     214,     7,     3,    90,  1272,     6,  1272,  1272,    97,    98,
      97,    98,     7,  1272,  1272,   104,     3,    24,     7,     6,
     109,   110,   111,   112,   113,   114,   115,     6,     3,   118,
      76,     3,   119,     8,     3,   124,   123,     3,  1040,     8,
       3,     8,     8,     4,   133,     8,  1022,   136,  1068,    97,
      98,    97,    98,     3,   143,    25,    26,    27,     8,     3,
      97,    98,   151,   152,     8,     3,     8,   156,     4,    76,
     159,    78,    79,   214,   163,    82,    83,    84,     4,    75,
       3,   177,   178,   214,     3,     8,    97,    98,     3,     8,
      97,    98,     4,     8,     4,   184,   185,   186,   187,   188,
     189,    97,    98,     3,     3,   153,   154,   155,     8,   198,
     147,   148,   149,   150,    47,    48,    49,    50,    51,    52,
       4,     3,   118,     3,     3,   214,     8,   214,     8,   125,
     126,   127,   128,   129,   130,     3,     3,    39,    40,    41,
       8,     8,    75,    76,   190,     4,   192,   193,     3,   160,
     161,   162,     3,     8,     3,     3,     8,     8,     4,     8,
       8,   144,   145,   146,    97,    98,   214,     4,   214,     4,
     440,   441,     4,   105,   106,   107,   108,   214,     4,     4,
       4,     4,     4,   514,     4,     4,     4,   120,   121,   122,
     521,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   521,   533,   214,     3,   536,     4,   214,     4,     4,
       4,     4,   543,   533,     4,     4,   536,     4,   214,     4,
     533,     4,   553,   543,   533,     4,     4,   533,     4,     4,
     533,   533,   563,   553,   536,     8,     4,   568,     4,     8,
       4,   543,     4,   563,     4,     4,   568,     4,   568,   533,
       4,   553,     4,     4,   568,   214,     4,   588,   521,   533,
     533,     4,   563,     4,     4,     4,     4,   568,   588,   215,
     533,   216,   215,   536,   215,   215,   215,     4,   215,     4,
     543,   214,   217,   217,   215,   215,   536,   533,   533,   533,
     553,   216,   216,   543,   215,   215,     4,    97,    98,   215,
     563,   215,   533,   533,   217,   568,   533,   533,   217,     4,
     533,   217,   217,   217,   533,     4,     4,   533,     4,   215,
     533,   533,     4,     4,   533,   588,     4,   533,     4,     4,
       4,   217,   533,     4,   217,   533,   217,   533,   533,   533,
       4,     4,   533,     4,     4,   533,     4,     4,     4,   533,
     533,     4,   533,   215,     4,     4,   536,     4,     4,     4,
       4,   217,     4,   543,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   217,   217,     4,
       4,   217,   215,   217,   184,   185,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     215,     4,   733,     4,     4,   736,     4,     4,     4,     4,
       4,     4,   215,     4,   214,   217,   736,     4,   215,     4,
       4,     4,     4,   215,   215,     4,     4,     4,     4,     4,
       4,   215,     4,     4,     4,   217,   217,   217,     4,     4,
     771,   772,   773,   217,   775,     4,     4,     4,   779,     4,
     215,   771,   772,   773,   774,   775,     4,   215,     4,   215,
       4,     4,   732,     4,   217,     4,   215,   217,     4,     7,
     214,     5,     7,   736,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,     7,     7,     7,
     214,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     214,   214,    75,     5,     5,     5,     5,   214,   771,   772,
     773,   774,   775,    86,    87,   214,    89,     7,    91,     5,
     214,     5,     5,     5,    97,    98,    99,   100,   101,   102,
     103,   104,     7,     5,     5,   214,   109,   110,   111,     7,
       7,     7,     7,     7,     7,   214,   119,     5,     7,     5,
     123,   124,     5,     5,     4,   214,     7,   179,   131,   214,
     214,     5,   214,   214,     7,     7,   214,     7,     7,     7,
       7,   214,     7,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,     7,
       7,   214,     7,     7,     4,     4,     4,     4,     4,     4,
       4,     3,   214,     6,     3,     6,     6,     3,     6,     3,
     215,   184,   185,     6,     3,     6,     6,     3,     6,     3,
       5,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   217,     6,     3,
       6,   214,     3,     8,     6,     4,     4,     4,     4,   217,
       4,   215,   215,   215,   215,   215,     4,     4,     4,     4,
       4,     4,   215,   215,   215,   215,   215,     4,   215,     4,
     215,     4,     4,   215,     4,   215,     4,     6,     4,     4,
     217,     8,   215,   215,     8,   215,   217,   214,   217,   214,
     214,   214,   214,   214,  1025,     8,     3,  1028,   214,   214,
    1031,   214,     8,  1034,   214,  1025,   214,   214,  1028,  1031,
     214,  1031,  1025,     4,  1034,  1046,  1025,  1031,  1049,  1025,
     214,  1052,  1025,  1025,     4,  1034,  1046,  1028,  1034,  1049,
    1031,  1034,  1034,  1034,   214,     4,   217,  1068,     4,   215,
    1046,  1025,  1073,  1046,  1046,  1046,  1077,  1049,  1068,     4,
    1034,  1025,  1025,  1073,   214,  1086,     7,  1077,     4,  1090,
    1034,  1034,  1025,  1083,  1095,  1028,  1086,  1098,  1031,   214,
       4,  1034,  1046,  1046,     4,  1095,     4,     4,  1098,  1025,
    1025,  1025,   214,  1046,  1034,  1086,  1049,   217,  1034,  1034,
    1034,   215,   215,  1095,  1025,  1025,  1098,   514,  1025,  1025,
    1046,  1046,  1025,  1034,  1034,  1068,  1025,  1034,  1034,  1025,
    1073,  1034,  1025,  1025,  1077,  1034,  1025,   214,  1034,  1025,
    1083,  1034,  1034,  1086,  1025,  1034,   711,  1025,  1034,  1025,
    1025,  1025,  1095,  1034,  1025,  1098,  1034,  1025,  1034,  1034,
    1034,  1025,  1025,  1034,  1025,  1095,  1034,   764,  1098,   724,
    1034,  1034,  1024,  1034,  1034,   733,   521,   819,  1019,   214,
     736,  1040,  1044,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,  1073,  1037,  1052,  1054,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
    1061,    75,    76,  1036,   571,  1272,  1025,  1027,    77,  1098,
    1028,   563,    86,    87,  1097,  1030,  1095,  1051,  1100,  1033,
    1031,  1049,   533,    97,    98,  1095,   100,   101,  1098,   103,
     104,   536,  1280,   789,   543,   109,   110,   111,  1047,  1068,
    1077,  1083,   775,  1087,   735,   119,   553,  1318,  1295,   123,
    1338,  1272,    -1,    -1,  1090,    -1,    -1,   131,   568,  1280,
      -1,    -1,  1272,    -1,    -1,    -1,    -1,    -1,    -1,  1229,
    1280,    -1,    -1,  1272,  1295,    -1,  1272,    -1,    -1,  1272,
    1272,  1272,   588,    -1,  1280,  1295,    -1,  1280,  1280,  1280,
      -1,   592,    -1,    -1,    -1,    -1,    -1,    -1,  1272,    -1,
      -1,    -1,    -1,    -1,  1295,    -1,    -1,    -1,  1272,  1272,
     184,   185,    -1,    -1,    -1,    -1,  1280,  1280,    -1,  1272,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1280,    -1,    -1,
      -1,    -1,  1272,    -1,    -1,    -1,  1272,  1272,  1272,    -1,
     214,    -1,  1295,    -1,  1280,  1280,    -1,    -1,    -1,    -1,
      -1,  1272,  1272,    -1,    -1,  1272,  1272,    -1,    -1,  1272,
      -1,    -1,    -1,  1272,    -1,    -1,  1272,    -1,    -1,  1272,
    1272,    -1,    -1,  1272,    -1,    -1,  1272,    -1,    -1,    -1,
      -1,  1272,    -1,    -1,  1272,    -1,  1272,  1272,  1272,    -1,
      -1,  1272,    -1,    -1,  1272,    -1,    -1,    -1,  1272,  1272,
      -1,  1272,  1272
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       0,     5,     7,     9,   214,   215,   216,   217,   234,   235,
     236,   241,     7,   250,     7,   255,     7,   306,     7,   417,
       7,   497,     7,   513,     7,   530,     7,   449,     7,   455,
       7,   479,     7,   393,     7,   601,     7,   632,   242,   237,
     251,   256,   307,   418,   498,   514,   531,   450,   456,   480,
     394,   602,   633,   234,   243,   244,   214,   239,   240,    10,
     252,   254,    11,    12,    15,    21,    22,    23,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    85,    86,    87,
      88,    97,    98,   104,   109,   110,   111,   112,   113,   114,
     115,   118,   124,   133,   136,   143,   151,   152,   156,   159,
     163,   184,   185,   186,   187,   188,   189,   198,   214,   249,
     257,   258,   259,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   281,   283,   285,   286,   287,   289,   291,   292,   293,
     294,   296,   297,   299,   301,   302,   303,   304,   316,   318,
     320,   358,   366,   372,   378,   380,   387,   401,   411,   431,
     432,   433,   434,   439,   447,   473,   503,   505,   524,   554,
     568,   580,   581,   589,   599,   630,   639,   663,    16,    17,
      18,    19,    20,   249,   308,   309,   310,   312,   313,   314,
     315,   503,   505,    89,    91,    99,   100,   101,   102,   103,
     119,   123,   131,   249,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   275,   276,   277,
     278,   281,   283,   285,   286,   287,   289,   291,   297,   299,
     419,   420,   421,   423,   425,   427,   429,   431,   432,   433,
     434,   437,   438,   473,   491,   503,   505,   507,   524,   549,
      90,   249,   427,   429,   473,   499,   500,   501,   503,   505,
      92,    93,    94,    95,    96,   249,   427,   429,   473,   503,
     505,   515,   516,   517,   519,   520,   522,   523,   118,   125,
     126,   127,   128,   129,   130,   249,   473,   503,   505,   532,
     533,   534,   535,   537,   539,   541,   543,   545,   547,   447,
      24,    76,    78,    79,    82,    83,    84,   249,   338,   457,
     458,   459,   460,   461,   462,   463,   465,   467,   469,   470,
     472,   503,   505,    77,    80,    81,   249,   338,   461,   467,
     481,   482,   483,   484,   485,   487,   488,   489,   490,   503,
     505,   134,   135,   249,   395,   396,   397,   399,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   184,   185,   249,   503,   505,   603,   604,   605,   606,
     608,   610,   611,   613,   614,   615,   618,   620,   621,   622,
     624,   626,   628,    13,    14,   634,   635,   636,   638,     6,
       3,     4,     8,     3,   253,     3,     8,   260,   631,   305,
     317,   319,   321,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   295,     4,     4,
       4,     4,     4,   279,   282,   284,     4,     4,     4,   412,
     448,   474,     4,   298,   300,   440,   504,   506,   435,     4,
       4,     4,   367,   379,   373,   359,   555,   525,   388,   402,
     569,     4,   381,   582,   590,   600,   288,   290,     4,     4,
       4,   640,   664,     4,     3,     8,   311,     4,     4,     4,
       4,     3,     8,   492,   508,   422,   424,   426,     4,     4,
     430,   428,   550,     3,     8,   502,     3,     8,   518,     4,
     521,     4,     4,     3,     8,   548,   536,   538,   540,   542,
     544,   546,     8,     3,     8,   464,   339,     4,   468,   466,
     471,     4,     8,     3,   486,     4,     4,     8,     3,   398,
     400,     3,     8,     4,   607,   609,     4,   612,     4,     4,
     616,   619,     4,     4,   623,   625,   627,   629,     3,     8,
     637,     4,     3,     8,   234,   234,   214,     4,     4,     4,
       4,     4,     4,     4,   215,   215,   215,   215,   215,   215,
     215,   215,   217,   216,   216,   216,   215,   215,     4,   215,
     215,   217,   217,   217,     4,     4,     4,   217,   217,   217,
       4,     4,     4,   215,     4,     4,     4,     4,     4,     4,
     217,   217,   217,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   215,     4,     4,     4,     4,     4,     4,   217,
     217,   217,     4,     4,   258,     4,   217,   217,   215,   215,
     309,     4,     4,     4,     4,     4,   215,   217,     4,     4,
       4,   420,     4,   500,     4,   215,     4,   215,   215,   516,
       4,     4,     4,     4,     4,     4,     4,   534,     4,     4,
     215,     4,     4,     4,   217,   459,     4,   217,   217,   483,
       4,     4,   396,   217,     4,     4,   215,     4,   215,   215,
       4,     4,   217,   217,     4,     4,     4,     4,   604,     4,
     215,   635,     4,     7,   214,     7,     7,     7,     7,     5,
     214,   180,   181,   182,   183,   217,   280,   214,   214,     5,
       5,     5,   214,   214,     5,   236,   238,   214,   105,   106,
     107,   108,   436,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,     7,     7,     7,   214,   214,     5,     7,
       5,   245,     5,     5,   214,   214,   214,   245,   214,     7,
     214,   214,   214,   245,   245,   245,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   238,   214,   214,
     214,   177,   178,   617,   179,   280,   214,   214,   214,     5,
     234,   257,   634,   308,    24,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    42,    43,    44,    45,
      46,   249,   326,   327,   328,   331,   333,   335,   337,   338,
     340,   341,   342,   343,   344,   345,   348,   349,   350,   352,
     354,   356,   326,     7,   322,   323,   324,     7,   413,   414,
     415,     7,   451,   452,   453,     7,   475,   476,   477,     7,
     441,   442,   443,   127,   214,   368,   369,   370,   371,   243,
     128,   130,   370,   374,   375,   376,   377,   116,   117,   360,
     361,   362,   364,     7,   556,   557,     7,   526,   527,   528,
       7,   389,   390,   391,   137,   138,   139,   140,   141,   142,
     403,   404,   405,   406,   407,   408,   409,   410,    24,   147,
     148,   149,   150,   249,   340,   503,   505,   570,   571,   572,
     575,   576,   578,   579,   153,   154,   155,   249,   382,   383,
     384,   385,   386,   503,   505,   157,   158,   249,   503,   505,
     583,   584,   585,   587,   160,   161,   162,   214,   503,   505,
     591,   592,   593,   594,   596,   597,   603,     7,   641,   642,
     199,   249,   665,   666,   667,   246,     7,   493,   494,   495,
       7,   509,   510,   511,   132,   535,   551,   552,   322,     8,
       8,     8,   329,   332,   334,   336,     4,     4,     4,     4,
       4,     4,     4,   346,     4,   351,   353,   355,   357,     3,
       8,     8,   325,     6,     3,   416,     6,     3,   454,     6,
       3,   478,     6,     3,   444,     6,     3,     3,     6,     6,
       3,     6,   363,   365,     3,     8,   558,     3,     6,   529,
       6,     3,   392,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   573,   577,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   586,   588,     3,     8,     4,
     595,     4,   598,     3,     8,     8,   643,     3,     6,     4,
       3,     8,   214,   247,   248,   496,     6,     3,   512,     6,
       3,   553,     8,     6,     4,     4,     4,     4,   215,   217,
     215,   217,   215,   215,   215,     4,   215,     4,     4,     4,
       4,   327,   326,   324,   419,   415,   457,   453,   481,   477,
     249,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   275,   276,   277,   278,   281,   283,
     285,   286,   287,   289,   291,   297,   299,   338,   411,   423,
     425,   427,   429,   431,   432,   433,   434,   438,   445,   446,
     473,   503,   505,   549,   443,   369,   375,     4,     4,   361,
     120,   121,   122,   249,   261,   262,   263,   264,   265,   266,
     338,   473,   503,   505,   559,   560,   561,   562,   563,   565,
     567,   557,   532,   528,   395,   391,   215,   215,   215,   215,
     215,   215,   404,     4,     4,   215,   215,   215,   571,   217,
     215,   215,   383,     4,     4,   584,   217,     4,   215,     4,
     592,   190,   192,   193,   249,   338,   503,   505,   644,   645,
     646,   647,   649,   642,   217,   666,     6,     3,   499,   495,
     515,   511,     4,    25,    26,    27,   330,   214,   214,   214,
      39,    40,    41,   347,   214,   214,   214,   214,     8,     8,
       8,     8,     3,     8,   214,   214,   564,   566,     4,     8,
       3,     8,     8,   144,   145,   146,   574,   214,   214,   214,
     214,   234,   650,     4,   648,     3,     8,   214,     8,     8,
     214,   446,     4,     4,   217,   561,     4,   215,     4,   645,
     214,   214,     5,   214,     7,   651,   652,   653,     3,     6,
     191,   194,   195,   196,   197,   654,   655,   656,   658,   659,
     660,   661,   652,   657,     4,     4,     4,   662,     3,     8,
       4,   217,   215,   215,     4,   655,   214,   214
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   218,   220,   219,   221,   219,   222,   219,   223,   219,
     224,   219,   225,   219,   226,   219,   227,   219,   228,   219,
     229,   219,   230,   219,   231,   219,   232,   219,   233,   219,
     234,   234,   234,   234,   234,   234,   234,   235,   237,   236,
     238,   239,   239,   240,   240,   240,   242,   241,   243,   243,
     244,   244,   244,   246,   245,   247,   247,   248,   248,   248,
     249,   251,   250,   253,   252,   252,   254,   256,   255,   257,
     257,   257,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   260,
     259,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   279,   278,
     280,   280,   280,   280,   280,   282,   281,   284,   283,   285,
     286,   288,   287,   290,   289,   291,   292,   293,   295,   294,
     296,   298,   297,   300,   299,   301,   302,   303,   305,   304,
     307,   306,   308,   308,   308,   309,   309,   309,   309,   309,
     309,   309,   309,   311,   310,   312,   313,   314,   315,   317,
     316,   319,   318,   321,   320,   322,   322,   323,   323,   323,
     325,   324,   326,   326,   326,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   329,   328,   330,   330,   330,   332,
     331,   334,   333,   336,   335,   337,   339,   338,   340,   341,
     342,   343,   344,   346,   345,   347,   347,   347,   348,   349,
     351,   350,   353,   352,   355,   354,   357,   356,   359,   358,
     360,   360,   360,   361,   361,   363,   362,   365,   364,   367,
     366,   368,   368,   368,   369,   369,   370,   371,   373,   372,
     374,   374,   374,   375,   375,   375,   376,   377,   379,   378,
     381,   380,   382,   382,   382,   383,   383,   383,   383,   383,
     383,   384,   385,   386,   388,   387,   389,   389,   390,   390,
     390,   392,   391,   394,   393,   395,   395,   395,   395,   396,
     396,   398,   397,   400,   399,   402,   401,   403,   403,   403,
     404,   404,   404,   404,   404,   404,   405,   406,   407,   408,
     409,   410,   412,   411,   413,   413,   414,   414,   414,   416,
     415,   418,   417,   419,   419,   419,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     420,   422,   421,   424,   423,   426,   425,   428,   427,   430,
     429,   431,   432,   433,   435,   434,   436,   436,   436,   436,
     437,   438,   440,   439,   441,   441,   442,   442,   442,   444,
     443,   445,   445,   445,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   448,   447,   450,   449,
     451,   451,   452,   452,   452,   454,   453,   456,   455,   457,
     457,   458,   458,   458,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   460,   461,   462,   464,   463,   466,
     465,   468,   467,   469,   471,   470,   472,   474,   473,   475,
     475,   476,   476,   476,   478,   477,   480,   479,   481,   481,
     482,   482,   482,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   484,   486,   485,   487,   488,   489,   490,   492,
     491,   493,   493,   494,   494,   494,   496,   495,   498,   497,
     499,   499,   499,   500,   500,   500,   500,   500,   500,   500,
     502,   501,   504,   503,   506,   505,   508,   507,   509,   509,
     510,   510,   510,   512,   511,   514,   513,   515,   515,   515,
     516,   516,   516,   516,   516,   516,   516,   516,   516,   516,
     516,   518,   517,   519,   521,   520,   522,   523,   525,   524,
     526,   526,   527,   527,   527,   529,   528,   531,   530,   532,
     532,   533,   533,   533,   534,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   536,   535,   538,   537,   540,
     539,   542,   541,   544,   543,   546,   545,   548,   547,   550,
     549,   551,   551,   553,   552,   555,   554,   556,   556,   556,
     558,   557,   559,   559,   560,   560,   560,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   562,   564,   563,   566,   565,   567,   569,   568,   570,
     570,   570,   571,   571,   571,   571,   571,   571,   571,   571,
     571,   573,   572,   574,   574,   574,   575,   577,   576,   578,
     579,   580,   582,   581,   583,   583,   583,   584,   584,   584,
     584,   584,   586,   585,   588,   587,   590,   589,   591,   591,
     591,   592,   592,   592,   592,   592,   592,   593,   595,   594,
     596,   598,   597,   600,   599,   602,   601,   603,   603,   603,
     604,   604,   604,   604,   604,   604,   604,   604,   604,   604,
     604,   604,   604,   604,   604,   604,   604,   604,   605,   607,
     606,   609,   608,   610,   612,   611,   613,   614,   616,   615,
     617,   617,   619,   618,   620,   621,   623,   622,   625,   624,
     627,   626,   629,   628,   631,   630,   633,   632,   634,   634,
     634,   635,   635,   637,   636,   638,   640,   639,   641,   641,
     641,   643,   642,   644,   644,   644,   645,   645,   645,   645,
     645,   645,   645,   646,   648,   647,   650,   649,   651,   651,
     651,   653,   652,   654,   654,   654,   655,   655,   655,   655,
     655,   657,   656,   658,   659,   660,   662,   661,   664,   663,
     665,   665,   665,   666,   666,   667
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
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
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
       1,     1,     0,     4,     0,     4,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     0,     6,     3,     0,     6,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     3
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
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "on_fail", "$@42", "on_fail_mode", "max_row_errors",
  "max_reconnect_tries", "trust_anchor", "$@43", "cert_file", "$@44",
  "key_file", "$@45", "cipher_list", "$@46", "sanity_checks", "$@47",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@48",
  "extended_info_checks", "$@49", "mac_sources", "$@50",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
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
       0,   306,   306,   306,   307,   307,   308,   308,   309,   309,
     310,   310,   311,   311,   312,   312,   313,   313,   314,   314,
     315,   315,   316,   316,   317,   317,   318,   318,   319,   319,
     327,   328,   329,   330,   331,   332,   333,   336,   341,   341,
     352,   355,   356,   359,   364,   370,   375,   375,   382,   383,
     386,   390,   394,   400,   400,   407,   408,   411,   415,   419,
     429,   438,   438,   453,   453,   467,   470,   476,   476,   485,
     486,   487,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   563,
     563,   572,   578,   584,   590,   596,   602,   608,   614,   620,
     626,   632,   638,   644,   650,   656,   662,   668,   674,   674,
     683,   686,   689,   692,   695,   701,   701,   710,   710,   719,
     725,   731,   731,   740,   740,   749,   755,   761,   767,   767,
     776,   782,   782,   791,   791,   800,   806,   812,   818,   818,
     830,   830,   839,   840,   841,   846,   847,   848,   849,   850,
     851,   852,   853,   856,   856,   867,   873,   879,   885,   891,
     891,   904,   904,   917,   917,   928,   929,   932,   933,   934,
     939,   939,   949,   950,   951,   956,   957,   958,   959,   960,
     961,   962,   963,   964,   965,   966,   967,   968,   969,   970,
     971,   972,   973,   974,   977,   977,   985,   986,   987,   990,
     990,   999,   999,  1008,  1008,  1017,  1023,  1023,  1032,  1038,
    1044,  1050,  1056,  1062,  1062,  1070,  1071,  1072,  1075,  1081,
    1087,  1087,  1096,  1096,  1105,  1105,  1114,  1114,  1123,  1123,
    1134,  1135,  1136,  1141,  1142,  1145,  1145,  1164,  1164,  1182,
    1182,  1193,  1194,  1195,  1200,  1201,  1204,  1209,  1214,  1214,
    1225,  1226,  1227,  1232,  1233,  1234,  1237,  1242,  1249,  1249,
    1262,  1262,  1275,  1276,  1277,  1282,  1283,  1284,  1285,  1286,
    1287,  1290,  1296,  1302,  1308,  1308,  1319,  1320,  1323,  1324,
    1325,  1330,  1330,  1340,  1340,  1350,  1351,  1352,  1355,  1358,
    1359,  1362,  1362,  1371,  1371,  1380,  1380,  1392,  1393,  1394,
    1399,  1400,  1401,  1402,  1403,  1404,  1407,  1413,  1419,  1425,
    1431,  1437,  1446,  1446,  1460,  1461,  1464,  1465,  1466,  1475,
    1475,  1501,  1501,  1512,  1513,  1514,  1520,  1521,  1522,  1523,
    1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,
    1534,  1535,  1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,
    1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,
    1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,  1562,  1563,
    1564,  1567,  1567,  1576,  1576,  1585,  1585,  1594,  1594,  1603,
    1603,  1614,  1620,  1626,  1632,  1632,  1640,  1641,  1642,  1643,
    1646,  1652,  1660,  1660,  1672,  1673,  1677,  1678,  1679,  1684,
    1684,  1692,  1693,  1694,  1699,  1700,  1701,  1702,  1703,  1704,
    1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,
    1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,  1723,  1724,
    1725,  1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,
    1735,  1736,  1737,  1738,  1739,  1740,  1747,  1747,  1761,  1761,
    1770,  1771,  1774,  1775,  1776,  1783,  1783,  1798,  1798,  1812,
    1813,  1816,  1817,  1818,  1823,  1824,  1825,  1826,  1827,  1828,
    1829,  1830,  1831,  1832,  1835,  1837,  1843,  1845,  1845,  1854,
    1854,  1863,  1863,  1872,  1874,  1874,  1883,  1893,  1893,  1906,
    1907,  1912,  1913,  1914,  1921,  1921,  1933,  1933,  1945,  1946,
    1951,  1952,  1953,  1960,  1961,  1962,  1963,  1964,  1965,  1966,
    1967,  1968,  1971,  1973,  1973,  1982,  1984,  1986,  1992,  2001,
    2001,  2014,  2015,  2018,  2019,  2020,  2025,  2025,  2035,  2035,
    2045,  2046,  2047,  2052,  2053,  2054,  2055,  2056,  2057,  2058,
    2061,  2061,  2070,  2070,  2095,  2095,  2125,  2125,  2138,  2139,
    2142,  2143,  2144,  2149,  2149,  2161,  2161,  2173,  2174,  2175,
    2180,  2181,  2182,  2183,  2184,  2185,  2186,  2187,  2188,  2189,
    2190,  2193,  2193,  2202,  2208,  2208,  2217,  2223,  2232,  2232,
    2243,  2244,  2247,  2248,  2249,  2254,  2254,  2263,  2263,  2272,
    2273,  2276,  2277,  2278,  2284,  2285,  2286,  2287,  2288,  2289,
    2290,  2291,  2292,  2293,  2294,  2297,  2297,  2308,  2308,  2319,
    2319,  2328,  2328,  2337,  2337,  2346,  2346,  2355,  2355,  2369,
    2369,  2380,  2381,  2384,  2384,  2396,  2396,  2407,  2408,  2409,
    2414,  2414,  2424,  2425,  2428,  2429,  2430,  2435,  2436,  2437,
    2438,  2439,  2440,  2441,  2442,  2443,  2444,  2445,  2446,  2447,
    2448,  2451,  2453,  2453,  2462,  2462,  2471,  2480,  2480,  2493,
    2494,  2495,  2500,  2501,  2502,  2503,  2504,  2505,  2506,  2507,
    2508,  2511,  2511,  2519,  2520,  2521,  2524,  2530,  2530,  2539,
    2545,  2553,  2561,  2561,  2572,  2573,  2574,  2579,  2580,  2581,
    2582,  2583,  2586,  2586,  2595,  2595,  2607,  2607,  2620,  2621,
    2622,  2627,  2628,  2629,  2630,  2631,  2632,  2635,  2641,  2641,
    2650,  2656,  2656,  2666,  2666,  2679,  2679,  2689,  2690,  2691,
    2696,  2697,  2698,  2699,  2700,  2701,  2702,  2703,  2704,  2705,
    2706,  2707,  2708,  2709,  2710,  2711,  2712,  2713,  2716,  2723,
    2723,  2732,  2732,  2741,  2747,  2747,  2756,  2762,  2768,  2768,
    2777,  2778,  2781,  2781,  2791,  2798,  2805,  2805,  2814,  2814,
    2824,  2824,  2834,  2834,  2846,  2846,  2858,  2858,  2868,  2869,
    2870,  2876,  2877,  2880,  2880,  2891,  2899,  2899,  2912,  2913,
    2914,  2920,  2920,  2928,  2929,  2930,  2935,  2936,  2937,  2938,
    2939,  2940,  2941,  2944,  2950,  2950,  2959,  2959,  2970,  2971,
    2972,  2977,  2977,  2985,  2986,  2987,  2992,  2993,  2994,  2995,
    2996,  2999,  2999,  3008,  3014,  3020,  3026,  3026,  3035,  3035,
    3046,  3047,  3048,  3053,  3054,  3057
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
#line 6456 "dhcp6_parser.cc"

#line 3063 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
