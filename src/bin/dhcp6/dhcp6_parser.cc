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

  case 136: // $@21: %empty
#line 560 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 137: // data_directory: "data-directory" $@21 ":" "constant string"
#line 563 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 138: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 569 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 139: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 575 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 140: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 141: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 587 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 142: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 143: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 144: // renew_timer: "renew-timer" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 145: // rebind_timer: "rebind-timer" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 146: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 617 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 147: // t1_percent: "t1-percent" ":" "floating point"
#line 623 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 148: // t2_percent: "t2-percent" ":" "floating point"
#line 629 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 149: // cache_threshold: "cache-threshold" ":" "floating point"
#line 635 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 150: // cache_max_age: "cache-max-age" ":" "integer"
#line 641 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 151: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 647 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 152: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 653 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 153: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 659 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 154: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 665 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 155: // $@22: %empty
#line 671 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 156: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 674 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "when-present"
#line 680 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "never"
#line 683 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "always"
#line 686 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "when-not-present"
#line 689 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "boolean"
#line 692 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 162: // $@23: %empty
#line 698 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 163: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 701 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 164: // $@24: %empty
#line 707 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 165: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 710 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 166: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 716 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 167: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 722 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 168: // $@25: %empty
#line 728 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 169: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 731 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 170: // $@26: %empty
#line 737 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 171: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 740 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 172: // store_extended_info: "store-extended-info" ":" "boolean"
#line 746 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 173: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 752 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 174: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 758 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 175: // $@27: %empty
#line 764 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 176: // server_tag: "server-tag" $@27 ":" "constant string"
#line 767 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 177: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 773 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 178: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 779 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 179: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 785 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 180: // $@28: %empty
#line 791 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 181: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 797 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 182: // $@29: %empty
#line 803 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 183: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 807 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1580 "dhcp6_parser.cc"
    break;

  case 186: // interfaces_config_params: interfaces_config_params ","
#line 814 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1588 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 826 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1600 "dhcp6_parser.cc"
    break;

  case 193: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 832 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 194: // re_detect: "re-detect" ":" "boolean"
#line 837 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 195: // $@31: %empty
#line 843 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 196: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 849 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1642 "dhcp6_parser.cc"
    break;

  case 197: // $@32: %empty
#line 856 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1654 "dhcp6_parser.cc"
    break;

  case 198: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 862 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1665 "dhcp6_parser.cc"
    break;

  case 199: // $@33: %empty
#line 869 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 200: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 875 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1686 "dhcp6_parser.cc"
    break;

  case 205: // not_empty_database_list: not_empty_database_list ","
#line 886 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1694 "dhcp6_parser.cc"
    break;

  case 206: // $@34: %empty
#line 891 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1704 "dhcp6_parser.cc"
    break;

  case 207: // database: "{" $@34 database_map_params "}"
#line 895 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1714 "dhcp6_parser.cc"
    break;

  case 210: // database_map_params: database_map_params ","
#line 903 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1722 "dhcp6_parser.cc"
    break;

  case 237: // $@35: %empty
#line 936 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 238: // database_type: "type" $@35 ":" db_type
#line 939 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1740 "dhcp6_parser.cc"
    break;

  case 239: // db_type: "memfile"
#line 944 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1746 "dhcp6_parser.cc"
    break;

  case 240: // db_type: "mysql"
#line 945 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1752 "dhcp6_parser.cc"
    break;

  case 241: // db_type: "postgresql"
#line 946 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1758 "dhcp6_parser.cc"
    break;

  case 242: // db_type: "cql"
#line 947 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1764 "dhcp6_parser.cc"
    break;

  case 243: // $@36: %empty
#line 950 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1773 "dhcp6_parser.cc"
    break;

  case 244: // user: "user" $@36 ":" "constant string"
#line 953 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1783 "dhcp6_parser.cc"
    break;

  case 245: // $@37: %empty
#line 959 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 246: // password: "password" $@37 ":" "constant string"
#line 962 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1802 "dhcp6_parser.cc"
    break;

  case 247: // $@38: %empty
#line 968 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1811 "dhcp6_parser.cc"
    break;

  case 248: // host: "host" $@38 ":" "constant string"
#line 971 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1821 "dhcp6_parser.cc"
    break;

  case 249: // port: "port" ":" "integer"
#line 977 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1831 "dhcp6_parser.cc"
    break;

  case 250: // $@39: %empty
#line 983 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1840 "dhcp6_parser.cc"
    break;

  case 251: // name: "name" $@39 ":" "constant string"
#line 986 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1850 "dhcp6_parser.cc"
    break;

  case 252: // persist: "persist" ":" "boolean"
#line 992 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1860 "dhcp6_parser.cc"
    break;

  case 253: // lfc_interval: "lfc-interval" ":" "integer"
#line 998 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 254: // readonly: "readonly" ":" "boolean"
#line 1004 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1880 "dhcp6_parser.cc"
    break;

  case 255: // connect_timeout: "connect-timeout" ":" "integer"
#line 1010 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1890 "dhcp6_parser.cc"
    break;

  case 256: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1016 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 257: // $@40: %empty
#line 1022 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 258: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1025 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 259: // on_fail_mode: "stop-retry-exit"
#line 1030 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1924 "dhcp6_parser.cc"
    break;

  case 260: // on_fail_mode: "serve-retry-exit"
#line 1031 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1930 "dhcp6_parser.cc"
    break;

  case 261: // on_fail_mode: "serve-retry-continue"
#line 1032 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1936 "dhcp6_parser.cc"
    break;

  case 262: // max_row_errors: "max-row-errors" ":" "integer"
#line 1035 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 263: // request_timeout: "request-timeout" ":" "integer"
#line 1041 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 264: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1047 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 265: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1053 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1976 "dhcp6_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1059 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 267: // contact_points: "contact-points" $@41 ":" "constant string"
#line 1062 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 268: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1068 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2005 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1074 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2014 "dhcp6_parser.cc"
    break;

  case 270: // keyspace: "keyspace" $@42 ":" "constant string"
#line 1077 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2024 "dhcp6_parser.cc"
    break;

  case 271: // $@43: %empty
#line 1083 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2033 "dhcp6_parser.cc"
    break;

  case 272: // consistency: "consistency" $@43 ":" "constant string"
#line 1086 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2043 "dhcp6_parser.cc"
    break;

  case 273: // $@44: %empty
#line 1092 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 274: // serial_consistency: "serial-consistency" $@44 ":" "constant string"
#line 1095 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 275: // $@45: %empty
#line 1101 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 276: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1104 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2081 "dhcp6_parser.cc"
    break;

  case 277: // $@46: %empty
#line 1110 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp6_parser.cc"
    break;

  case 278: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1113 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 279: // $@47: %empty
#line 1119 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp6_parser.cc"
    break;

  case 280: // key_file: "key-file" $@47 ":" "constant string"
#line 1122 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2119 "dhcp6_parser.cc"
    break;

  case 281: // $@48: %empty
#line 1128 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 282: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1131 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 283: // $@49: %empty
#line 1137 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 284: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1143 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 287: // sanity_checks_params: sanity_checks_params ","
#line 1150 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2167 "dhcp6_parser.cc"
    break;

  case 289: // $@50: %empty
#line 1157 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc"
    break;

  case 290: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1160 "dhcp6_parser.yy"
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
#line 2196 "dhcp6_parser.cc"
    break;

  case 291: // $@51: %empty
#line 1176 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2208 "dhcp6_parser.cc"
    break;

  case 292: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1182 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp6_parser.cc"
    break;

  case 295: // mac_sources_list: mac_sources_list ","
#line 1189 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2225 "dhcp6_parser.cc"
    break;

  case 298: // duid_id: "duid"
#line 1198 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2234 "dhcp6_parser.cc"
    break;

  case 299: // string_id: "constant string"
#line 1203 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 300: // $@52: %empty
#line 1208 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2255 "dhcp6_parser.cc"
    break;

  case 301: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1214 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2264 "dhcp6_parser.cc"
    break;

  case 304: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1221 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2272 "dhcp6_parser.cc"
    break;

  case 308: // hw_address_id: "hw-address"
#line 1231 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2281 "dhcp6_parser.cc"
    break;

  case 309: // flex_id: "flex-id"
#line 1236 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2290 "dhcp6_parser.cc"
    break;

  case 310: // $@53: %empty
#line 1243 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp6_parser.cc"
    break;

  case 311: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1249 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2311 "dhcp6_parser.cc"
    break;

  case 312: // $@54: %empty
#line 1256 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2323 "dhcp6_parser.cc"
    break;

  case 313: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1262 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2334 "dhcp6_parser.cc"
    break;

  case 316: // multi_threading_params: multi_threading_params ","
#line 1271 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2342 "dhcp6_parser.cc"
    break;

  case 323: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1284 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2352 "dhcp6_parser.cc"
    break;

  case 324: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1290 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 325: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1296 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 326: // $@55: %empty
#line 1302 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 327: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1308 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc"
    break;

  case 332: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1319 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2401 "dhcp6_parser.cc"
    break;

  case 333: // $@56: %empty
#line 1324 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 334: // hooks_library: "{" $@56 hooks_params "}"
#line 1328 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2421 "dhcp6_parser.cc"
    break;

  case 335: // $@57: %empty
#line 1334 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 336: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1338 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2441 "dhcp6_parser.cc"
    break;

  case 339: // hooks_params: hooks_params ","
#line 1346 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2449 "dhcp6_parser.cc"
    break;

  case 343: // $@58: %empty
#line 1356 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2458 "dhcp6_parser.cc"
    break;

  case 344: // library: "library" $@58 ":" "constant string"
#line 1359 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2468 "dhcp6_parser.cc"
    break;

  case 345: // $@59: %empty
#line 1365 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2477 "dhcp6_parser.cc"
    break;

  case 346: // parameters: "parameters" $@59 ":" map_value
#line 1368 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 347: // $@60: %empty
#line 1374 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 348: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1380 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 351: // expired_leases_params: expired_leases_params ","
#line 1388 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2516 "dhcp6_parser.cc"
    break;

  case 358: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1401 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2526 "dhcp6_parser.cc"
    break;

  case 359: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1407 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 360: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1413 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 361: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1419 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2556 "dhcp6_parser.cc"
    break;

  case 362: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1425 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 363: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1431 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 364: // $@61: %empty
#line 1440 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2588 "dhcp6_parser.cc"
    break;

  case 365: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1446 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2597 "dhcp6_parser.cc"
    break;

  case 370: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1460 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2605 "dhcp6_parser.cc"
    break;

  case 371: // $@62: %empty
#line 1469 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2615 "dhcp6_parser.cc"
    break;

  case 372: // subnet6: "{" $@62 subnet6_params "}"
#line 1473 "dhcp6_parser.yy"
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
#line 2641 "dhcp6_parser.cc"
    break;

  case 373: // $@63: %empty
#line 1495 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2651 "dhcp6_parser.cc"
    break;

  case 374: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1499 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2661 "dhcp6_parser.cc"
    break;

  case 377: // subnet6_params: subnet6_params ","
#line 1508 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2669 "dhcp6_parser.cc"
    break;

  case 421: // $@64: %empty
#line 1559 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp6_parser.cc"
    break;

  case 422: // subnet: "subnet" $@64 ":" "constant string"
#line 1562 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 423: // $@65: %empty
#line 1568 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 424: // interface: "interface" $@65 ":" "constant string"
#line 1571 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 425: // $@66: %empty
#line 1577 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp6_parser.cc"
    break;

  case 426: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1580 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2726 "dhcp6_parser.cc"
    break;

  case 427: // $@67: %empty
#line 1586 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 428: // client_class: "client-class" $@67 ":" "constant string"
#line 1589 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2745 "dhcp6_parser.cc"
    break;

  case 429: // $@68: %empty
#line 1595 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 430: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1601 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 431: // reservations_global: "reservations-global" ":" "boolean"
#line 1606 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 432: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1612 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 433: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1618 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 434: // $@69: %empty
#line 1624 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2805 "dhcp6_parser.cc"
    break;

  case 435: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1627 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 436: // hr_mode: "disabled"
#line 1632 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2820 "dhcp6_parser.cc"
    break;

  case 437: // hr_mode: "out-of-pool"
#line 1633 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2826 "dhcp6_parser.cc"
    break;

  case 438: // hr_mode: "global"
#line 1634 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2832 "dhcp6_parser.cc"
    break;

  case 439: // hr_mode: "all"
#line 1635 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2838 "dhcp6_parser.cc"
    break;

  case 440: // id: "id" ":" "integer"
#line 1638 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2848 "dhcp6_parser.cc"
    break;

  case 441: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1644 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 442: // $@70: %empty
#line 1652 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2870 "dhcp6_parser.cc"
    break;

  case 443: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1658 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2879 "dhcp6_parser.cc"
    break;

  case 448: // shared_networks_list: shared_networks_list ","
#line 1671 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2887 "dhcp6_parser.cc"
    break;

  case 449: // $@71: %empty
#line 1676 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2897 "dhcp6_parser.cc"
    break;

  case 450: // shared_network: "{" $@71 shared_network_params "}"
#line 1680 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 453: // shared_network_params: shared_network_params ","
#line 1686 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2913 "dhcp6_parser.cc"
    break;

  case 494: // $@72: %empty
#line 1737 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 495: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1743 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 496: // $@73: %empty
#line 1751 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 497: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1754 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2951 "dhcp6_parser.cc"
    break;

  case 502: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1766 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2959 "dhcp6_parser.cc"
    break;

  case 503: // $@74: %empty
#line 1773 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2969 "dhcp6_parser.cc"
    break;

  case 504: // option_def_entry: "{" $@74 option_def_params "}"
#line 1777 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 505: // $@75: %empty
#line 1788 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2991 "dhcp6_parser.cc"
    break;

  case 506: // sub_option_def: "{" $@75 option_def_params "}"
#line 1792 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3003 "dhcp6_parser.cc"
    break;

  case 511: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1808 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3011 "dhcp6_parser.cc"
    break;

  case 523: // code: "code" ":" "integer"
#line 1827 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 525: // $@76: %empty
#line 1835 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3030 "dhcp6_parser.cc"
    break;

  case 526: // option_def_type: "type" $@76 ":" "constant string"
#line 1838 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3040 "dhcp6_parser.cc"
    break;

  case 527: // $@77: %empty
#line 1844 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3049 "dhcp6_parser.cc"
    break;

  case 528: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1847 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3059 "dhcp6_parser.cc"
    break;

  case 529: // $@78: %empty
#line 1853 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3068 "dhcp6_parser.cc"
    break;

  case 530: // space: "space" $@78 ":" "constant string"
#line 1856 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3078 "dhcp6_parser.cc"
    break;

  case 532: // $@79: %empty
#line 1864 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 533: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1867 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3097 "dhcp6_parser.cc"
    break;

  case 534: // option_def_array: "array" ":" "boolean"
#line 1873 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3107 "dhcp6_parser.cc"
    break;

  case 535: // $@80: %empty
#line 1883 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 536: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1889 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3128 "dhcp6_parser.cc"
    break;

  case 541: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1904 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3136 "dhcp6_parser.cc"
    break;

  case 542: // $@81: %empty
#line 1911 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3146 "dhcp6_parser.cc"
    break;

  case 543: // option_data_entry: "{" $@81 option_data_params "}"
#line 1915 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3155 "dhcp6_parser.cc"
    break;

  case 544: // $@82: %empty
#line 1923 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3165 "dhcp6_parser.cc"
    break;

  case 545: // sub_option_data: "{" $@82 option_data_params "}"
#line 1927 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3174 "dhcp6_parser.cc"
    break;

  case 550: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1943 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3182 "dhcp6_parser.cc"
    break;

  case 561: // $@83: %empty
#line 1963 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3191 "dhcp6_parser.cc"
    break;

  case 562: // option_data_data: "data" $@83 ":" "constant string"
#line 1966 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 565: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1976 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 566: // option_data_always_send: "always-send" ":" "boolean"
#line 1982 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 567: // $@84: %empty
#line 1991 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3233 "dhcp6_parser.cc"
    break;

  case 568: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 1997 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp6_parser.cc"
    break;

  case 573: // not_empty_pools_list: not_empty_pools_list ","
#line 2010 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3250 "dhcp6_parser.cc"
    break;

  case 574: // $@85: %empty
#line 2015 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 575: // pool_list_entry: "{" $@85 pool_params "}"
#line 2019 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3270 "dhcp6_parser.cc"
    break;

  case 576: // $@86: %empty
#line 2025 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3280 "dhcp6_parser.cc"
    break;

  case 577: // sub_pool6: "{" $@86 pool_params "}"
#line 2029 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3290 "dhcp6_parser.cc"
    break;

  case 580: // pool_params: pool_params ","
#line 2037 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3298 "dhcp6_parser.cc"
    break;

  case 588: // $@87: %empty
#line 2051 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3307 "dhcp6_parser.cc"
    break;

  case 589: // pool_entry: "pool" $@87 ":" "constant string"
#line 2054 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3317 "dhcp6_parser.cc"
    break;

  case 590: // $@88: %empty
#line 2060 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 591: // user_context: "user-context" $@88 ":" map_value
#line 2062 "dhcp6_parser.yy"
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
#line 3352 "dhcp6_parser.cc"
    break;

  case 592: // $@89: %empty
#line 2085 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3360 "dhcp6_parser.cc"
    break;

  case 593: // comment: "comment" $@89 ":" "constant string"
#line 2087 "dhcp6_parser.yy"
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
#line 3389 "dhcp6_parser.cc"
    break;

  case 594: // $@90: %empty
#line 2115 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 595: // pd_pools_list: "pd-pools" $@90 ":" "[" pd_pools_list_content "]"
#line 2121 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 600: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2134 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3418 "dhcp6_parser.cc"
    break;

  case 601: // $@91: %empty
#line 2139 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 602: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2143 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3440 "dhcp6_parser.cc"
    break;

  case 603: // $@92: %empty
#line 2151 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 604: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2155 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3462 "dhcp6_parser.cc"
    break;

  case 607: // pd_pool_params: pd_pool_params ","
#line 2165 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3470 "dhcp6_parser.cc"
    break;

  case 619: // $@93: %empty
#line 2183 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 620: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2186 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3489 "dhcp6_parser.cc"
    break;

  case 621: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2192 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 622: // $@94: %empty
#line 2198 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 623: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2201 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 624: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2207 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 625: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2213 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 626: // $@95: %empty
#line 2222 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3550 "dhcp6_parser.cc"
    break;

  case 627: // reservations: "reservations" $@95 ":" "[" reservations_list "]"
#line 2228 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3559 "dhcp6_parser.cc"
    break;

  case 632: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2239 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3567 "dhcp6_parser.cc"
    break;

  case 633: // $@96: %empty
#line 2244 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3577 "dhcp6_parser.cc"
    break;

  case 634: // reservation: "{" $@96 reservation_params "}"
#line 2248 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3586 "dhcp6_parser.cc"
    break;

  case 635: // $@97: %empty
#line 2253 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 636: // sub_reservation: "{" $@97 reservation_params "}"
#line 2257 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3605 "dhcp6_parser.cc"
    break;

  case 641: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2268 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3613 "dhcp6_parser.cc"
    break;

  case 653: // $@98: %empty
#line 2287 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 654: // ip_addresses: "ip-addresses" $@98 ":" list_strings
#line 2293 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3634 "dhcp6_parser.cc"
    break;

  case 655: // $@99: %empty
#line 2298 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 656: // prefixes: "prefixes" $@99 ":" list_strings
#line 2304 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3655 "dhcp6_parser.cc"
    break;

  case 657: // $@100: %empty
#line 2309 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp6_parser.cc"
    break;

  case 658: // duid: "duid" $@100 ":" "constant string"
#line 2312 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3674 "dhcp6_parser.cc"
    break;

  case 659: // $@101: %empty
#line 2318 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp6_parser.cc"
    break;

  case 660: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2321 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3693 "dhcp6_parser.cc"
    break;

  case 661: // $@102: %empty
#line 2327 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3702 "dhcp6_parser.cc"
    break;

  case 662: // hostname: "hostname" $@102 ":" "constant string"
#line 2330 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3712 "dhcp6_parser.cc"
    break;

  case 663: // $@103: %empty
#line 2336 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3721 "dhcp6_parser.cc"
    break;

  case 664: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2339 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3731 "dhcp6_parser.cc"
    break;

  case 665: // $@104: %empty
#line 2345 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3743 "dhcp6_parser.cc"
    break;

  case 666: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2351 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3752 "dhcp6_parser.cc"
    break;

  case 667: // $@105: %empty
#line 2359 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3764 "dhcp6_parser.cc"
    break;

  case 668: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2365 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3773 "dhcp6_parser.cc"
    break;

  case 671: // $@106: %empty
#line 2374 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3782 "dhcp6_parser.cc"
    break;

  case 672: // ip_address: "ip-address" $@106 ":" "constant string"
#line 2377 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3792 "dhcp6_parser.cc"
    break;

  case 673: // $@107: %empty
#line 2386 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 674: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2392 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 677: // client_classes_list: client_classes_list ","
#line 2399 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3821 "dhcp6_parser.cc"
    break;

  case 678: // $@108: %empty
#line 2404 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 679: // client_class_entry: "{" $@108 client_class_params "}"
#line 2408 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3841 "dhcp6_parser.cc"
    break;

  case 684: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2420 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3849 "dhcp6_parser.cc"
    break;

  case 699: // $@109: %empty
#line 2442 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3858 "dhcp6_parser.cc"
    break;

  case 700: // client_class_test: "test" $@109 ":" "constant string"
#line 2445 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3868 "dhcp6_parser.cc"
    break;

  case 701: // only_if_required: "only-if-required" ":" "boolean"
#line 2451 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3878 "dhcp6_parser.cc"
    break;

  case 702: // $@110: %empty
#line 2460 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 703: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2466 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 706: // server_id_params: server_id_params ","
#line 2475 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3909 "dhcp6_parser.cc"
    break;

  case 716: // $@111: %empty
#line 2491 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3918 "dhcp6_parser.cc"
    break;

  case 717: // server_id_type: "type" $@111 ":" duid_type
#line 2494 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3927 "dhcp6_parser.cc"
    break;

  case 718: // duid_type: "LLT"
#line 2499 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3933 "dhcp6_parser.cc"
    break;

  case 719: // duid_type: "EN"
#line 2500 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3939 "dhcp6_parser.cc"
    break;

  case 720: // duid_type: "LL"
#line 2501 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3945 "dhcp6_parser.cc"
    break;

  case 721: // htype: "htype" ":" "integer"
#line 2504 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3955 "dhcp6_parser.cc"
    break;

  case 722: // $@112: %empty
#line 2510 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3964 "dhcp6_parser.cc"
    break;

  case 723: // identifier: "identifier" $@112 ":" "constant string"
#line 2513 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 724: // time: "time" ":" "integer"
#line 2519 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 725: // enterprise_id: "enterprise-id" ":" "integer"
#line 2525 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3994 "dhcp6_parser.cc"
    break;

  case 726: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2533 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4004 "dhcp6_parser.cc"
    break;

  case 727: // $@113: %empty
#line 2541 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4016 "dhcp6_parser.cc"
    break;

  case 728: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2547 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4025 "dhcp6_parser.cc"
    break;

  case 731: // control_socket_params: control_socket_params ","
#line 2554 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4033 "dhcp6_parser.cc"
    break;

  case 737: // $@114: %empty
#line 2566 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4042 "dhcp6_parser.cc"
    break;

  case 738: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2569 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 739: // $@115: %empty
#line 2575 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 740: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2578 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 741: // $@116: %empty
#line 2587 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4083 "dhcp6_parser.cc"
    break;

  case 742: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2593 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4094 "dhcp6_parser.cc"
    break;

  case 745: // queue_control_params: queue_control_params ","
#line 2602 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4102 "dhcp6_parser.cc"
    break;

  case 752: // enable_queue: "enable-queue" ":" "boolean"
#line 2615 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4112 "dhcp6_parser.cc"
    break;

  case 753: // $@117: %empty
#line 2621 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp6_parser.cc"
    break;

  case 754: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2624 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4131 "dhcp6_parser.cc"
    break;

  case 755: // capacity: "capacity" ":" "integer"
#line 2630 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4141 "dhcp6_parser.cc"
    break;

  case 756: // $@118: %empty
#line 2636 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4150 "dhcp6_parser.cc"
    break;

  case 757: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2639 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 758: // $@119: %empty
#line 2646 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4171 "dhcp6_parser.cc"
    break;

  case 759: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2652 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4182 "dhcp6_parser.cc"
    break;

  case 760: // $@120: %empty
#line 2659 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4192 "dhcp6_parser.cc"
    break;

  case 761: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2663 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4202 "dhcp6_parser.cc"
    break;

  case 764: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2671 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4210 "dhcp6_parser.cc"
    break;

  case 783: // enable_updates: "enable-updates" ":" "boolean"
#line 2696 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4220 "dhcp6_parser.cc"
    break;

  case 784: // $@121: %empty
#line 2703 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4229 "dhcp6_parser.cc"
    break;

  case 785: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2706 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4239 "dhcp6_parser.cc"
    break;

  case 786: // $@122: %empty
#line 2712 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4248 "dhcp6_parser.cc"
    break;

  case 787: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2715 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4258 "dhcp6_parser.cc"
    break;

  case 788: // server_port: "server-port" ":" "integer"
#line 2721 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4268 "dhcp6_parser.cc"
    break;

  case 789: // $@123: %empty
#line 2727 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4277 "dhcp6_parser.cc"
    break;

  case 790: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2730 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4287 "dhcp6_parser.cc"
    break;

  case 791: // sender_port: "sender-port" ":" "integer"
#line 2736 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 792: // max_queue_size: "max-queue-size" ":" "integer"
#line 2742 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4307 "dhcp6_parser.cc"
    break;

  case 793: // $@124: %empty
#line 2748 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4316 "dhcp6_parser.cc"
    break;

  case 794: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2751 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4325 "dhcp6_parser.cc"
    break;

  case 795: // ncr_protocol_value: "UDP"
#line 2757 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4331 "dhcp6_parser.cc"
    break;

  case 796: // ncr_protocol_value: "TCP"
#line 2758 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4337 "dhcp6_parser.cc"
    break;

  case 797: // $@125: %empty
#line 2761 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4346 "dhcp6_parser.cc"
    break;

  case 798: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2764 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4356 "dhcp6_parser.cc"
    break;

  case 799: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2771 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 800: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2778 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4376 "dhcp6_parser.cc"
    break;

  case 801: // $@126: %empty
#line 2785 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4385 "dhcp6_parser.cc"
    break;

  case 802: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2788 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4394 "dhcp6_parser.cc"
    break;

  case 803: // $@127: %empty
#line 2794 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4403 "dhcp6_parser.cc"
    break;

  case 804: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2797 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4413 "dhcp6_parser.cc"
    break;

  case 805: // $@128: %empty
#line 2804 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 806: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2807 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4432 "dhcp6_parser.cc"
    break;

  case 807: // $@129: %empty
#line 2814 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 808: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2817 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4451 "dhcp6_parser.cc"
    break;

  case 809: // $@130: %empty
#line 2826 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4463 "dhcp6_parser.cc"
    break;

  case 810: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2832 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4473 "dhcp6_parser.cc"
    break;

  case 811: // $@131: %empty
#line 2838 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4483 "dhcp6_parser.cc"
    break;

  case 812: // sub_config_control: "{" $@131 config_control_params "}"
#line 2842 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4492 "dhcp6_parser.cc"
    break;

  case 815: // config_control_params: config_control_params ","
#line 2850 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4500 "dhcp6_parser.cc"
    break;

  case 818: // $@132: %empty
#line 2860 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4512 "dhcp6_parser.cc"
    break;

  case 819: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2866 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4521 "dhcp6_parser.cc"
    break;

  case 820: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2871 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 821: // $@133: %empty
#line 2879 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4543 "dhcp6_parser.cc"
    break;

  case 822: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2885 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4552 "dhcp6_parser.cc"
    break;

  case 825: // loggers_entries: loggers_entries ","
#line 2894 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4560 "dhcp6_parser.cc"
    break;

  case 826: // $@134: %empty
#line 2900 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4570 "dhcp6_parser.cc"
    break;

  case 827: // logger_entry: "{" $@134 logger_params "}"
#line 2904 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4578 "dhcp6_parser.cc"
    break;

  case 830: // logger_params: logger_params ","
#line 2910 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4586 "dhcp6_parser.cc"
    break;

  case 838: // debuglevel: "debuglevel" ":" "integer"
#line 2924 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4596 "dhcp6_parser.cc"
    break;

  case 839: // $@135: %empty
#line 2930 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4605 "dhcp6_parser.cc"
    break;

  case 840: // severity: "severity" $@135 ":" "constant string"
#line 2933 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4615 "dhcp6_parser.cc"
    break;

  case 841: // $@136: %empty
#line 2939 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4627 "dhcp6_parser.cc"
    break;

  case 842: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 2945 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4636 "dhcp6_parser.cc"
    break;

  case 845: // output_options_list_content: output_options_list_content ","
#line 2952 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4644 "dhcp6_parser.cc"
    break;

  case 846: // $@137: %empty
#line 2957 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4654 "dhcp6_parser.cc"
    break;

  case 847: // output_entry: "{" $@137 output_params_list "}"
#line 2961 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4662 "dhcp6_parser.cc"
    break;

  case 850: // output_params_list: output_params_list ","
#line 2967 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4670 "dhcp6_parser.cc"
    break;

  case 856: // $@138: %empty
#line 2979 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4679 "dhcp6_parser.cc"
    break;

  case 857: // output: "output" $@138 ":" "constant string"
#line 2982 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4689 "dhcp6_parser.cc"
    break;

  case 858: // flush: "flush" ":" "boolean"
#line 2988 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4699 "dhcp6_parser.cc"
    break;

  case 859: // maxsize: "maxsize" ":" "integer"
#line 2994 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 860: // maxver: "maxver" ":" "integer"
#line 3000 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4719 "dhcp6_parser.cc"
    break;

  case 861: // $@139: %empty
#line 3006 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4728 "dhcp6_parser.cc"
    break;

  case 862: // pattern: "pattern" $@139 ":" "constant string"
#line 3009 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 863: // $@140: %empty
#line 3015 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4750 "dhcp6_parser.cc"
    break;

  case 864: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3021 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4759 "dhcp6_parser.cc"
    break;

  case 867: // compatibility_params: compatibility_params ","
#line 3028 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4767 "dhcp6_parser.cc"
    break;

  case 870: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3037 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4777 "dhcp6_parser.cc"
    break;


#line 4781 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1001;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     456, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,    65,    30,    31,    61,    80,
      94,    98,   116,   117,   123,   131,   133,   137,   148,   165,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,    30,  -101,
     213,   142,    36,   647,   184,   288,    51,   145,    15,    83,
     -95,   438,    35, -1001,   234,   238,   244,   266,   275, -1001,
      78, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   276,   287,
     292,   296,   303,   328,   332,   350,   351,   376,   389,   427,
     437,   446, -1001,   447,   451,   452,   453,   455, -1001, -1001,
   -1001,   459,   460,   461, -1001, -1001, -1001,   462, -1001, -1001,
   -1001, -1001,   463,   465,   467, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   469, -1001, -1001, -1001, -1001, -1001,
   -1001,   470,   471, -1001, -1001,   472, -1001,    92, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   475, -1001,   118, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   476,   486, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   138, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,   155, -1001, -1001, -1001, -1001, -1001,   487, -1001,   488,
     490, -1001, -1001, -1001, -1001, -1001, -1001,   222, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   311,   319, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   317, -1001, -1001,   491, -1001,
   -1001, -1001,   492, -1001, -1001,   327,   401, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     496,   501, -1001, -1001, -1001, -1001,   384,   404, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     223, -1001, -1001, -1001,   502, -1001, -1001,   503, -1001,   504,
     505, -1001, -1001,   506,   508, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,   231, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     510,   258, -1001, -1001, -1001, -1001,    30,    30, -1001,   246,
     511, -1001, -1001,   512,   514,   515,   518,   519,   520,   313,
     325,   326,   329,   333,   334,   337,   338,   309,   339,   341,
     342,   344,   345,   530,   346,   348,   347,   349,   353,   538,
     539,   541,   354,   356,   357,   572,   573,   574,   365,   577,
     580,   582,   583,   371,   373,   375,   589,   590,   591,   593,
     595,   596,   597,   598,   612,   402,   614,   615,   616,   617,
     618,   621,   409,   410,   624,   625, -1001,   142, -1001,   626,
     414,    36, -1001,   628,   629,   630,   631,   633,   423,   426,
     636,   637,   638,   647, -1001,   640,   184, -1001,   641,   431,
     643,   433,   434,   288, -1001,   646,   649,   650,   666,   667,
     671,   673, -1001,    51, -1001,   674,   675,   436,   677,   678,
     679,   468, -1001,    15,   680,   477,   478, -1001,    83,   682,
     683,    50, -1001,   480,   689,   708,   498,   710,   500,   513,
     721,   722,   521,   523,   725,   726,   732,   733,   438, -1001,
     738,   528,    35, -1001, -1001, -1001,   740,   739,   531,   748,
     749,   750,   751,   757, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   549, -1001,
   -1001, -1001, -1001, -1001,  -127,   550,   551, -1001, -1001, -1001,
     761,   762,   764, -1001,   765,   766,   560,   261, -1001, -1001,
   -1001,   770,   771,   772,   773,   776,   777,   778,   779,   793,
   -1001,   794,   795,   796,   807,   564,   570, -1001, -1001,   780,
     810, -1001,   813, -1001, -1001,   814,   815,   607,   608,   609,
   -1001, -1001,   813,   610,   818, -1001,   613, -1001,   620, -1001,
     623, -1001, -1001, -1001,   813,   813,   813,   632,   639,   644,
     648, -1001,   651,   652, -1001,   654,   655,   656, -1001, -1001,
     657, -1001, -1001, -1001,   658,   766, -1001, -1001,   659,   660,
   -1001,   661, -1001, -1001,    14,   663, -1001, -1001,  -127,   662,
     664,   665, -1001,   821, -1001, -1001,    30,   142, -1001,    35,
      36,   316,   316,   822, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   823,   824,   833,   837, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   -96,    30,   -57,   709,   838,
     843,   844,   171,    87,   127,   -25,    90,   438, -1001, -1001,
     845,  -141, -1001, -1001,   847,   848, -1001, -1001, -1001, -1001,
   -1001,   -82, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,   822, -1001,   260,   284,   285, -1001, -1001, -1001, -1001,
     853,   856,   859,   860,   873, -1001,   876,   877, -1001, -1001,
   -1001, -1001,   878,   879,   880,   881, -1001, -1001, -1001, -1001,
   -1001,   295, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   312, -1001,
     882,   883, -1001, -1001,   884,   886, -1001, -1001,   885,   889,
   -1001, -1001,   887,   891, -1001, -1001,   890,   892, -1001, -1001,
   -1001,    85, -1001, -1001, -1001,   893, -1001, -1001, -1001,    91,
   -1001, -1001, -1001, -1001,   315, -1001, -1001, -1001,   106, -1001,
   -1001,   894,   895, -1001, -1001,   896,   898, -1001,   899,   900,
     901,   902,   903,   904,   330, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   905,   906,   907, -1001, -1001, -1001,
   -1001,   331, -1001, -1001, -1001, -1001, -1001, -1001,   908,   909,
     910, -1001,   387, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   388, -1001, -1001, -1001,   911, -1001,
     912, -1001, -1001, -1001,   391, -1001, -1001, -1001, -1001, -1001,
     397, -1001,   153, -1001,   913, -1001,   403, -1001, -1001,   704,
   -1001,   916,   920, -1001, -1001,   918,   922, -1001, -1001, -1001,
     919, -1001,   923, -1001, -1001, -1001,   915,   924,   926,   927,
     672,   715,   711,   716,   719,   931,   723,   724,   932,   933,
     936,   937,   727,   728,   729,   737,   940,   943,   946,   949,
     316, -1001, -1001,   316, -1001,   822,   647, -1001,   823,    15,
   -1001,   824,    83, -1001,   833,   735, -1001,   837,   -96, -1001,
   -1001,   -57, -1001,   955,   709, -1001,   321,   838, -1001,    51,
   -1001,   843,   -95, -1001,   844,   745,   747,   754,   760,   763,
     768,   171, -1001,   959,   968,   785,   786,   791,    87, -1001,
     759,   800,   801,   127, -1001,   975,  1015,   -25, -1001,   806,
    1021,   811,  1030,    90, -1001, -1001,   189,   845, -1001,   825,
    -141, -1001, -1001,  1032,  1036,   184, -1001,   847,   288, -1001,
     848,  1043, -1001, -1001,   412,   846,   869,   888, -1001, -1001,
   -1001, -1001, -1001,   897, -1001, -1001,   400,   914,   917,   921,
   -1001, -1001, -1001, -1001,   925,   928,   929,   930, -1001,   405,
   -1001,   407, -1001,  1059, -1001,  1082, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   411, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,   934, -1001, -1001,  1089, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,  1088,  1096, -1001,
   -1001, -1001, -1001, -1001,  1093, -1001,   415, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   302,   935, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   938,   939, -1001, -1001,   941,
   -1001,    30, -1001, -1001,  1099, -1001, -1001, -1001, -1001, -1001,
     417, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   942,
     421, -1001,   424, -1001,   945, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   735,
   -1001, -1001,  1100,   947, -1001,   321, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,  1101,   950,  1102,
     189, -1001, -1001, -1001, -1001, -1001, -1001,   948, -1001, -1001,
    1103, -1001,   952, -1001, -1001,  1105, -1001, -1001,   318, -1001,
     -21,  1105, -1001, -1001,  1106,  1109,  1110, -1001,   425, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,  1111,   951,   954,   956,
    1112,   -21, -1001,   953, -1001, -1001, -1001,   958, -1001, -1001,
   -1001
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   182,     9,   373,    11,
     576,    13,   603,    15,   635,    17,   496,    19,   505,    21,
     544,    23,   335,    25,   760,    27,   811,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   637,     0,   507,   546,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   136,   809,   180,   195,   197,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,     0,     0,     0,     0,     0,   155,   162,
     164,     0,     0,     0,   364,   494,   535,     0,   442,   590,
     592,   434,     0,     0,     0,   291,   310,   300,   283,   673,
     626,   326,   347,   702,     0,   312,   727,   741,   758,   168,
     170,     0,     0,   821,   863,     0,   135,     0,    69,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   111,   112,
     113,   114,   115,    81,   119,   120,   121,   122,   123,   124,
     125,   126,   117,   118,   127,   128,   129,   106,   134,   131,
     132,    84,    85,    86,    87,   103,    88,    90,    89,   130,
      94,    95,    82,   108,   109,   110,   107,    83,    92,    93,
     101,   102,   104,    91,    96,    97,    98,    99,   100,   105,
     116,   133,   192,     0,   191,     0,   184,   187,   188,   189,
     190,   567,   594,   421,   423,   425,     0,     0,   429,   427,
     667,   420,   378,   379,   380,   381,   382,   383,   384,   385,
     404,   405,   406,   407,   408,   411,   412,   413,   414,   415,
     416,   417,   418,   409,   410,   419,     0,   375,   389,   390,
     391,   394,   395,   398,   399,   400,   397,   392,   393,   386,
     387,   402,   403,   388,   396,   401,   588,   587,   583,   584,
     582,     0,   578,   581,   585,   586,   619,     0,   622,     0,
       0,   618,   612,   613,   611,   616,   617,     0,   605,   608,
     609,   614,   615,   610,   665,   653,   655,   657,   659,   661,
     663,   652,   649,   650,   651,     0,   638,   639,   644,   645,
     642,   646,   647,   648,   643,     0,   525,   250,     0,   529,
     527,   532,     0,   521,   522,     0,   508,   509,   512,   524,
     513,   514,   515,   531,   516,   517,   518,   519,   520,   561,
       0,     0,   559,   560,   563,   564,     0,   547,   548,   551,
     552,   553,   554,   555,   556,   557,   558,   343,   345,   340,
       0,   337,   341,   342,     0,   784,   786,     0,   789,     0,
       0,   793,   797,     0,     0,   801,   803,   805,   807,   782,
     780,   781,     0,   762,   765,   777,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   778,   779,   818,
       0,     0,   813,   816,   817,    47,    52,     0,    39,    45,
       0,    66,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    71,    68,     0,
       0,   186,   183,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   377,   374,     0,   580,   577,     0,     0,
       0,     0,     0,   607,   604,     0,     0,     0,     0,     0,
       0,     0,   636,   641,   497,     0,     0,     0,     0,     0,
       0,     0,   506,   511,     0,     0,     0,   545,   550,     0,
       0,   339,   336,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   764,   761,
       0,     0,   815,   812,    51,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,   173,
     174,   152,   153,   154,     0,     0,     0,   166,   167,   172,
       0,     0,     0,   177,     0,     0,     0,     0,   431,   432,
     433,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     726,     0,     0,     0,     0,     0,     0,   178,   179,     0,
       0,    70,     0,   194,   185,     0,     0,     0,     0,     0,
     440,   441,     0,     0,     0,   376,     0,   579,     0,   621,
       0,   624,   625,   606,     0,     0,     0,     0,     0,     0,
       0,   640,     0,     0,   523,     0,     0,     0,   534,   510,
       0,   565,   566,   549,     0,     0,   338,   783,     0,     0,
     788,     0,   791,   792,     0,     0,   799,   800,     0,     0,
       0,     0,   763,     0,   820,   814,     0,     0,   137,     0,
       0,     0,     0,   201,   176,   157,   158,   159,   160,   161,
     156,   163,   165,   366,   498,   537,   444,    40,   591,   593,
     436,   437,   438,   439,   435,     0,    48,     0,     0,     0,
     628,   328,     0,     0,     0,     0,     0,     0,   169,   171,
       0,     0,    53,   193,   569,   596,   422,   424,   426,   430,
     428,     0,   589,   620,   623,   666,   654,   656,   658,   660,
     662,   664,   526,   251,   530,   528,   533,   562,   344,   346,
     785,   787,   790,   795,   796,   794,   798,   802,   804,   806,
     808,   201,    44,     0,     0,     0,   237,   243,   245,   247,
       0,     0,     0,     0,     0,   266,     0,     0,   257,   269,
     271,   273,     0,     0,     0,     0,   275,   277,   279,   281,
     236,     0,   208,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   223,   224,   231,   225,   226,   227,   221,
     222,   228,   229,   230,   232,   233,   234,   235,     0,   206,
       0,   202,   203,   371,     0,   367,   368,   503,     0,   499,
     500,   542,     0,   538,   539,   449,     0,   445,   446,   298,
     299,     0,   293,   296,   297,     0,   308,   309,   305,     0,
     302,   306,   307,   289,     0,   285,   288,   678,     0,   675,
     633,     0,   629,   630,   333,     0,   329,   330,     0,     0,
       0,     0,     0,     0,     0,   349,   352,   353,   354,   355,
     356,   357,   716,   722,     0,     0,     0,   715,   712,   713,
     714,     0,   704,   707,   710,   708,   709,   711,     0,     0,
       0,   322,     0,   314,   317,   318,   319,   320,   321,   737,
     739,   736,   734,   735,     0,   729,   732,   733,     0,   753,
       0,   756,   749,   750,     0,   743,   746,   747,   748,   751,
       0,   826,     0,   823,     0,   869,     0,   865,   868,    55,
     574,     0,   570,   571,   601,     0,   597,   598,   671,   670,
       0,   669,     0,    64,   810,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     210,   196,   198,     0,   200,   205,     0,   365,   370,   507,
     495,   502,   546,   536,   541,     0,   443,   448,   295,   292,
     311,   304,   301,     0,   287,   284,   680,   677,   674,   637,
     627,   632,     0,   327,   332,     0,     0,     0,     0,     0,
       0,   351,   348,     0,     0,     0,     0,     0,   706,   703,
       0,     0,     0,   316,   313,     0,     0,   731,   728,     0,
       0,     0,     0,   745,   742,   759,     0,   825,   822,     0,
     867,   864,    57,     0,    56,     0,   568,   573,     0,   595,
     600,     0,   668,   819,     0,     0,     0,     0,   249,   252,
     253,   254,   255,     0,   268,   256,     0,     0,     0,     0,
     263,   264,   265,   262,     0,     0,     0,     0,   209,     0,
     204,     0,   369,     0,   501,     0,   540,   493,   468,   469,
     470,   472,   473,   474,   458,   459,   477,   478,   479,   480,
     481,   484,   485,   486,   487,   488,   489,   490,   491,   482,
     483,   492,   454,   455,   456,   457,   466,   467,   463,   464,
     465,   462,   471,     0,   451,   460,   475,   476,   461,   447,
     294,   303,     0,   286,   699,     0,   697,   691,   692,   693,
     694,   695,   696,   698,   688,   689,   690,     0,   681,   682,
     685,   686,   687,   676,     0,   631,     0,   331,   358,   359,
     360,   361,   362,   363,   350,     0,     0,   721,   724,   725,
     705,   323,   324,   325,   315,     0,     0,   730,   752,     0,
     755,     0,   744,   841,     0,   839,   837,   831,   835,   836,
       0,   828,   833,   834,   832,   824,   870,   866,    54,    59,
       0,   572,     0,   599,     0,   239,   240,   241,   242,   238,
     244,   246,   248,   267,   259,   260,   261,   258,   270,   272,
     274,   276,   278,   280,   282,   207,   372,   504,   543,   453,
     450,   290,     0,     0,   679,   684,   634,   334,   718,   719,
     720,   717,   723,   738,   740,   754,   757,     0,     0,     0,
     830,   827,    58,   575,   602,   672,   452,     0,   701,   683,
       0,   838,     0,   829,   700,     0,   840,   846,     0,   843,
       0,   845,   842,   856,     0,     0,     0,   861,     0,   848,
     851,   852,   853,   854,   855,   844,     0,     0,     0,     0,
       0,   850,   847,     0,   858,   859,   860,     0,   849,   857,
     862
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   -10, -1001,  -565, -1001,
     212, -1001, -1001, -1001, -1001,   381, -1001,  -582, -1001, -1001,
   -1001,   -71, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   413,
     622, -1001, -1001,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19, -1001,    34,    37,    38,
      41, -1001,   420,    49, -1001,    52, -1001,    54,    55,    56,
   -1001,    59, -1001,    62, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   399,   606, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   335, -1001,   107, -1001,
    -696,   111, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,   -45, -1001,  -732, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,    89, -1001, -1001, -1001,
   -1001, -1001,    96,  -715, -1001, -1001, -1001, -1001,    99, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,    64, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,    81, -1001, -1001, -1001,    95,   578,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,    82, -1001, -1001,
   -1001, -1001, -1001, -1001, -1000, -1001, -1001, -1001,   114, -1001,
   -1001, -1001,   120,   627, -1001, -1001,  -998, -1001,  -997, -1001,
      73, -1001,    75, -1001,    66,    69,    70,    72, -1001, -1001,
   -1001,  -996, -1001, -1001, -1001, -1001,   119, -1001, -1001,  -135,
    1061, -1001, -1001, -1001, -1001, -1001,   124, -1001, -1001, -1001,
     122, -1001,   604, -1001,   -67, -1001, -1001, -1001, -1001, -1001,
     -64, -1001, -1001, -1001, -1001, -1001,     4, -1001, -1001, -1001,
     126, -1001, -1001, -1001,   129, -1001,   634, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,    67, -1001,
   -1001, -1001,    88,   668, -1001, -1001,   -55, -1001,   -12, -1001,
   -1001, -1001, -1001, -1001,    84, -1001, -1001, -1001,    93,   653,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,   -60, -1001, -1001,
   -1001,   134, -1001, -1001, -1001,   139, -1001,   669,   396, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,  -994, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     140, -1001, -1001, -1001,  -105, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,   121, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   113, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   110, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   439,   619, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   479,   635, -1001, -1001, -1001,
   -1001, -1001, -1001,   108, -1001, -1001,  -100, -1001, -1001, -1001,
   -1001, -1001, -1001,  -122, -1001, -1001,  -140, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,   112, -1001
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     728,    87,    88,    41,    68,    84,    85,   753,   969,  1083,
    1084,   820,    43,    70,    90,   430,    91,    45,    71,   157,
     158,   159,   433,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   459,   720,   178,   460,   179,   461,   180,   181,   182,
     490,   183,   491,   184,   185,   186,   187,   453,   188,   189,
     190,   191,   435,    47,    72,   225,   226,   227,   499,   228,
     192,   436,   193,   437,   194,   438,   850,   851,   852,  1013,
     821,   822,   823,   986,  1249,   824,   987,   825,   988,   826,
     989,   827,   828,   536,   829,   830,   831,   832,   833,   834,
     998,  1257,   835,   836,   837,   838,   839,   995,   840,   841,
     999,   842,  1000,   843,  1001,   844,  1006,   845,  1007,   846,
    1008,   847,  1009,   195,   479,   884,   885,   886,  1033,   196,
     476,   871,   872,   873,   874,   197,   478,   879,   880,   881,
     882,   198,   477,   199,   486,   932,   933,   934,   935,   936,
     200,   482,   895,   896,   897,  1042,    63,    80,   380,   381,
     382,   549,   383,   550,   201,   483,   904,   905,   906,   907,
     908,   909,   910,   911,   202,   465,   854,   855,   856,  1016,
      49,    73,   266,   267,   268,   505,   269,   506,   270,   507,
     271,   511,   272,   510,   203,   204,   205,   206,   472,   734,
     277,   278,   207,   469,   866,   867,   868,  1025,  1163,  1164,
     208,   466,    57,    77,   858,   859,   860,  1019,    59,    78,
     345,   346,   347,   348,   349,   350,   351,   535,   352,   539,
     353,   538,   354,   355,   540,   356,   209,   467,   862,   863,
     864,  1022,    61,    79,   366,   367,   368,   369,   370,   544,
     371,   372,   373,   374,   280,   503,   971,   972,   973,  1085,
      51,    74,   291,   292,   293,   515,   210,   470,   211,   471,
     283,   504,   975,   976,   977,  1088,    53,    75,   307,   308,
     309,   518,   310,   311,   520,   312,   313,   212,   481,   891,
     892,   893,  1039,    55,    76,   325,   326,   327,   328,   526,
     329,   527,   330,   528,   331,   529,   332,   530,   333,   531,
     334,   525,   285,   512,   980,   981,  1091,   213,   480,   888,
     889,  1036,  1187,  1188,  1189,  1190,  1191,  1272,  1192,   214,
     484,   921,   922,   923,  1053,  1281,   924,   925,  1054,   926,
     927,   215,   216,   487,   944,   945,   946,  1065,   947,  1066,
     217,   488,   954,   955,   956,   957,  1070,   958,   959,  1072,
     218,   489,    65,    81,   402,   403,   404,   405,   554,   406,
     555,   407,   408,   557,   409,   410,   411,   560,   785,   412,
     561,   413,   414,   415,   564,   416,   565,   417,   566,   418,
     567,   219,   434,    67,    82,   421,   422,   423,   570,   424,
     220,   494,   962,   963,  1076,  1230,  1231,  1232,  1233,  1289,
    1234,  1287,  1308,  1309,  1310,  1318,  1319,  1320,  1326,  1321,
    1322,  1323,  1324,  1330,   221,   495,   966,   967,   968
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     156,   224,   241,   287,   301,   321,    38,   343,   362,   379,
     399,   918,   364,   284,   248,   365,   848,   229,   281,   294,
     305,   323,   878,   357,   375,  1153,   400,  1154,  1155,  1162,
     242,  1168,   869,   344,   363,    31,   336,    32,    42,    33,
     377,   378,   249,   250,   315,   251,   252,   253,   419,   420,
     727,   978,   222,   223,   715,   716,   717,   718,   964,   243,
     230,   282,   295,   306,   324,    30,   358,   376,    44,   401,
     759,   869,   876,   155,   877,   129,   130,   279,   290,   304,
     322,   431,   765,   766,   767,   244,   432,    46,  1028,   245,
     719,  1029,   254,   246,  1031,   497,   337,  1032,   338,   339,
     498,    48,   340,   341,   342,    50,   247,   255,   912,  1037,
     256,   257,  1038,    86,   258,   129,   130,   801,   870,   155,
     727,   501,   259,    52,    54,   260,   502,   261,   262,   263,
      56,   126,   264,   939,   940,   265,   129,   130,    58,   273,
      60,   513,   274,   275,    62,   276,   514,   288,   302,   289,
     303,   129,   130,    92,    93,    64,  1077,    94,   516,  1078,
      95,    96,    97,   517,   337,   359,   338,   339,   360,   361,
    1313,   314,    66,  1314,  1315,  1316,  1317,   315,   316,   317,
     318,   319,   320,   129,   130,   377,   378,   129,   130,   155,
     129,   130,   783,   784,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    89,   125,   523,   551,   129,   130,   155,
     524,   552,   127,   128,   568,   913,   914,   915,   916,   569,
     425,   426,   129,   130,    34,    35,    36,    37,   427,   131,
     155,   948,   949,   950,   132,   133,   134,   135,   136,   137,
     138,   572,   139,   497,   126,   155,   573,   140,   983,  1153,
     337,  1154,  1155,  1162,   428,  1168,   141,   286,   429,   142,
     439,   928,   929,   930,   129,   130,   143,   572,   501,   129,
     130,   440,   984,   985,   144,   145,   441,   155,  1010,   146,
     442,   155,   147,  1011,   951,   238,   148,   443,   239,   898,
     899,   900,   901,   902,   903,  1010,   878,  1119,  1034,   532,
    1012,  1311,   533,  1035,  1312,   534,   918,   149,   150,   151,
     152,   153,   444,  1051,  1058,   542,   445,   796,  1052,  1059,
     154,   155,   797,   798,   799,   800,   801,   802,   803,   804,
     805,   806,   807,   808,   446,   447,   155,   809,   810,   811,
     812,   813,   814,   815,   816,   817,   818,   819,   126,   730,
     731,   732,   733,    98,    99,   100,   101,   102,   103,  1223,
     448,  1224,  1225,   296,   297,   298,   299,   300,   129,   130,
    1063,  1067,   547,   449,  1073,  1064,  1068,   337,   155,  1074,
     568,   126,   337,   155,   543,  1075,  1080,   548,  1010,   238,
     513,  1081,   239,  1265,  1269,  1266,   574,   575,   551,  1270,
    1290,   129,   130,  1277,   516,  1291,   156,   523,  1331,  1293,
     224,   450,  1294,  1332,  1245,  1246,  1247,  1248,  1254,  1255,
    1256,   451,   241,  1174,  1175,   287,   229,  1278,  1279,  1280,
     452,   454,   301,   284,   248,   455,   456,   457,   281,   458,
     576,   294,   321,   462,   463,   464,   468,   473,   305,   474,
     242,   475,   343,   485,   492,   493,   496,   362,   323,   500,
     508,   364,   249,   250,   365,   251,   252,   253,   357,   230,
     509,   519,   521,   375,   522,   537,   541,   399,   344,   243,
     545,   282,   155,   363,   295,   546,   553,   556,   558,   559,
     562,   306,   563,   400,   571,   577,   578,   279,   579,   580,
     290,   324,   581,   582,   583,   244,   592,   304,   584,   245,
     155,   358,   254,   246,   598,   155,   376,   322,   129,   130,
     585,   586,   604,   605,   587,   606,   247,   255,   588,   589,
     256,   257,   590,   591,   258,   593,   401,   594,   595,   596,
     597,   599,   259,   600,   601,   260,   602,   261,   262,   263,
     603,   607,   264,   608,   609,   265,   610,   611,   612,   273,
     613,   614,   274,   275,   615,   276,   616,   617,   618,   288,
     619,   289,   620,   621,   622,   623,   302,   624,   303,   625,
     626,   627,   628,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   629,   630,   631,   632,
     633,   634,   635,   397,   398,   636,   637,   638,   639,   640,
     642,   643,   645,   646,   647,   648,   156,   649,   650,   224,
     652,   653,   654,   651,   656,   658,   659,   660,   661,   662,
     664,   674,   155,   665,   666,   229,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     667,   668,   917,   931,   941,   669,   399,   670,   672,   673,
     965,   675,   676,   677,   680,   678,   684,   685,   919,   937,
     942,   952,   400,   688,   681,   682,   792,   687,   230,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   689,   690,   691,   692,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   694,   695,   126,   693,   698,
     699,   920,   938,   943,   953,   401,   700,   701,   696,   231,
     697,   232,   703,   704,   706,   708,   707,   129,   130,   233,
     234,   235,   236,   237,   131,   709,   710,   711,   712,   132,
     133,   134,   713,   714,   721,   722,   723,   724,   238,   725,
     726,   239,   140,    32,   729,   735,   736,   737,   748,   240,
     738,   739,   740,   741,   749,   750,   742,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     743,   744,   745,   746,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   747,   126,   337,   751,   752,   754,
     755,   756,   757,   758,   760,   761,   791,   762,   883,   849,
     853,   857,   149,   150,   763,   129,   130,   764,   234,   235,
     861,   237,   131,   786,   865,   887,   768,   132,   133,   134,
     890,   894,   961,   769,   970,   974,   238,   990,   770,   239,
     991,   155,   771,   992,   993,   772,   773,   240,   774,   775,
     776,   777,   778,   780,   781,   782,   788,   994,   789,   790,
     996,   997,  1002,  1003,  1004,  1005,  1015,  1098,  1014,  1018,
    1017,  1020,  1021,  1023,  1024,  1027,  1026,   779,  1041,  1030,
    1040,  1044,  1043,  1045,  1046,  1047,  1048,  1049,  1050,  1055,
    1056,  1057,  1060,  1061,  1062,  1069,  1071,  1079,  1082,  1094,
     149,   150,  1086,  1087,  1089,  1090,  1100,  1092,  1095,  1093,
    1096,  1097,  1099,  1101,  1102,  1103,  1106,  1107,  1104,  1105,
    1108,  1109,  1110,  1111,  1114,   241,  1112,  1115,   343,   155,
    1116,   362,  1113,  1117,  1127,   364,   284,   248,   365,  1172,
    1198,   281,  1199,  1205,   357,  1176,  1134,   375,   321,  1200,
    1166,   379,  1206,   242,   344,  1201,  1211,   363,  1202,  1215,
    1152,  1185,  1128,  1203,   323,   249,   250,   917,   251,   252,
     253,  1183,   931,  1177,  1135,  1136,   941,  1137,  1138,  1139,
    1207,  1208,   243,   919,   282,  1226,  1209,   358,   937,   965,
     376,  1129,   942,  1167,   287,  1212,  1213,   301,   952,  1216,
     279,  1228,  1178,  1218,  1186,  1219,  1220,   324,   244,  1165,
     294,  1227,   245,   305,  1221,   254,   246,  1130,  1238,  1239,
    1184,  1131,  1236,   322,  1140,  1132,   920,  1244,  1179,   247,
     255,   938,  1180,   256,   257,   943,  1181,   258,  1133,  1141,
    1250,   953,  1142,  1143,  1229,   259,  1144,  1267,   260,  1182,
     261,   262,   263,   295,  1145,   264,   306,  1146,   265,  1147,
    1148,  1149,   273,  1251,  1150,   274,   275,  1151,   276,   290,
    1268,  1158,   304,  1273,  1159,  1160,  1274,  1161,  1156,  1275,
    1157,  1276,  1252,  1288,  1297,  1300,  1302,   644,  1305,   795,
    1327,  1253,  1307,  1328,  1329,  1333,  1337,   875,   787,   641,
     793,  1118,  1120,  1173,  1170,  1197,   982,  1214,  1258,   686,
    1171,  1259,  1122,  1204,  1296,  1260,  1121,  1196,   335,  1261,
     655,  1123,  1262,  1263,  1264,  1124,  1169,   679,  1271,  1282,
    1126,  1125,  1283,  1284,  1241,  1285,  1292,   979,   288,  1295,
     289,   302,  1304,   303,  1298,  1301,  1306,  1339,  1334,  1335,
    1299,  1336,  1340,  1240,  1243,  1195,   663,  1193,  1194,  1210,
    1217,  1242,   683,  1222,   657,  1235,   960,   702,   794,  1325,
    1303,  1338,  1237,     0,     0,     0,     0,     0,  1127,     0,
       0,     0,   671,     0,  1176,     0,     0,   705,     0,     0,
    1134,  1286,     0,     0,  1166,     0,     0,     0,     0,  1226,
    1185,     0,     0,     0,  1152,     0,  1128,     0,     0,     0,
    1183,     0,  1177,     0,     0,  1228,     0,     0,  1135,  1136,
       0,  1137,  1138,  1139,     0,  1227,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1129,     0,  1167,     0,     0,
       0,  1178,     0,  1186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1165,     0,     0,     0,     0,  1229,  1184,
       0,  1130,     0,     0,     0,  1131,     0,  1179,  1140,  1132,
       0,  1180,     0,     0,     0,  1181,     0,     0,     0,     0,
       0,     0,  1133,  1141,     0,     0,  1142,  1143,  1182,     0,
    1144,     0,     0,     0,     0,     0,     0,     0,  1145,     0,
       0,  1146,     0,  1147,  1148,  1149,     0,     0,  1150,     0,
       0,  1151,     0,     0,     0,  1158,     0,     0,  1159,  1160,
       0,  1161,  1156,     0,  1157
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   743,    79,    73,    73,    79,   712,    72,    73,    74,
      75,    76,   737,    78,    79,  1025,    81,  1025,  1025,  1025,
      73,  1025,   128,    78,    79,     5,    21,     7,     7,     9,
     135,   136,    73,    73,   126,    73,    73,    73,    13,    14,
     615,   133,    16,    17,   181,   182,   183,   184,   199,    73,
      72,    73,    74,    75,    76,     0,    78,    79,     7,    81,
     652,   128,   129,   214,   131,   100,   101,    73,    74,    75,
      76,     3,   664,   665,   666,    73,     8,     7,     3,    73,
     217,     6,    73,    73,     3,     3,    81,     6,    83,    84,
       8,     7,    87,    88,    89,     7,    73,    73,    21,     3,
      73,    73,     6,   214,    73,   100,   101,    30,   214,   214,
     685,     3,    73,     7,     7,    73,     8,    73,    73,    73,
       7,    80,    73,   158,   159,    73,   100,   101,     7,    73,
       7,     3,    73,    73,     7,    73,     8,    74,    75,    74,
      75,   100,   101,    11,    12,     7,     3,    15,     3,     6,
      18,    19,    20,     8,    81,    82,    83,    84,    85,    86,
     191,   120,     7,   194,   195,   196,   197,   126,   127,   128,
     129,   130,   131,   100,   101,   135,   136,   100,   101,   214,
     100,   101,   178,   179,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    10,    79,     3,     3,   100,   101,   214,
       8,     8,    90,    91,     3,   148,   149,   150,   151,     8,
       6,     3,   100,   101,   214,   215,   216,   217,     4,   107,
     214,   161,   162,   163,   112,   113,   114,   115,   116,   117,
     118,     3,   120,     3,    80,   214,     8,   125,     8,  1269,
      81,  1269,  1269,  1269,     8,  1269,   134,    93,     3,   137,
       4,   154,   155,   156,   100,   101,   144,     3,     3,   100,
     101,     4,     8,     8,   152,   153,     4,   214,     3,   157,
       4,   214,   160,     8,   214,   121,   164,     4,   124,   138,
     139,   140,   141,   142,   143,     3,  1031,  1013,     3,     8,
       8,     3,     3,     8,     6,     8,  1058,   185,   186,   187,
     188,   189,     4,     3,     3,     8,     4,    21,     8,     8,
     198,   214,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     4,     4,   214,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    80,   108,
     109,   110,   111,    52,    53,    54,    55,    56,    57,   190,
       4,   192,   193,    95,    96,    97,    98,    99,   100,   101,
       3,     3,     8,     4,     3,     8,     8,    81,   214,     8,
       3,    80,    81,   214,     3,     8,     3,     3,     3,   121,
       3,     8,   124,     8,     3,     8,   426,   427,     3,     8,
       3,   100,   101,     8,     3,     8,   497,     3,     3,     8,
     501,     4,     8,     8,    22,    23,    24,    25,    38,    39,
      40,     4,   513,   122,   123,   516,   501,   145,   146,   147,
       4,     4,   523,   513,   513,     4,     4,     4,   513,     4,
     214,   516,   533,     4,     4,     4,     4,     4,   523,     4,
     513,     4,   543,     4,     4,     4,     4,   548,   533,     4,
       4,   548,   513,   513,   548,   513,   513,   513,   543,   501,
       4,     4,     4,   548,     4,     4,     4,   568,   543,   513,
       4,   513,   214,   548,   516,     4,     4,     4,     4,     4,
       4,   523,     4,   568,     4,     4,     4,   513,     4,     4,
     516,   533,     4,     4,     4,   513,   217,   523,   215,   513,
     214,   543,   513,   513,     4,   214,   548,   533,   100,   101,
     215,   215,     4,     4,   215,     4,   513,   513,   215,   215,
     513,   513,   215,   215,   513,   216,   568,   216,   216,   215,
     215,   215,   513,   215,   217,   513,   217,   513,   513,   513,
     217,   217,   513,   217,   217,   513,     4,     4,     4,   513,
     215,     4,   513,   513,     4,   513,     4,     4,   217,   516,
     217,   516,   217,     4,     4,     4,   523,     4,   523,     4,
       4,     4,     4,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,     4,   215,     4,     4,
       4,     4,     4,   185,   186,     4,   217,   217,     4,     4,
       4,   217,     4,     4,     4,     4,   707,     4,   215,   710,
       4,     4,     4,   217,     4,     4,   215,     4,   215,   215,
       4,   215,   214,     4,     4,   710,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
       4,     4,   743,   744,   745,     4,   747,     4,     4,     4,
     751,     4,     4,     4,     4,   217,     4,     4,   743,   744,
     745,   746,   747,     4,   217,   217,   706,   217,   710,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,     4,   215,     4,   215,    69,    70,    71,    72,
      73,    74,    75,    76,    77,     4,     4,    80,   215,     4,
       4,   743,   744,   745,   746,   747,     4,     4,   217,    92,
     217,    94,     4,   215,     4,   214,     7,   100,   101,   102,
     103,   104,   105,   106,   107,     7,     7,     7,     7,   112,
     113,   114,     5,   214,   214,   214,     5,     5,   121,     5,
       5,   124,   125,     7,   214,     5,     5,     5,   214,   132,
       7,     5,     5,     5,   214,     5,     7,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       7,     7,     7,     7,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     7,    80,    81,     7,     5,     5,
       5,   214,   214,   214,   214,     7,     5,   214,   119,     7,
       7,     7,   185,   186,   214,   100,   101,   214,   103,   104,
       7,   106,   107,   180,     7,     7,   214,   112,   113,   114,
       7,     7,     7,   214,     7,     7,   121,     4,   214,   124,
       4,   214,   214,     4,     4,   214,   214,   132,   214,   214,
     214,   214,   214,   214,   214,   214,   214,     4,   214,   214,
       4,     4,     4,     4,     4,     4,     3,   215,     6,     3,
       6,     6,     3,     6,     3,     3,     6,   685,     3,     6,
       6,     3,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   214,     4,
     185,   186,     6,     3,     6,     3,   215,     8,     4,     6,
       4,     4,   217,   217,   215,     4,     4,     4,   215,   215,
       4,     4,   215,   215,     4,  1016,   217,     4,  1019,   214,
       4,  1022,   215,     4,  1025,  1022,  1016,  1016,  1022,     4,
     215,  1016,   215,     4,  1019,  1036,  1025,  1022,  1039,   215,
    1025,  1042,     4,  1016,  1019,   215,   217,  1022,   215,     4,
    1025,  1036,  1025,   215,  1039,  1016,  1016,  1058,  1016,  1016,
    1016,  1036,  1063,  1036,  1025,  1025,  1067,  1025,  1025,  1025,
     215,   215,  1016,  1058,  1016,  1076,   215,  1019,  1063,  1080,
    1022,  1025,  1067,  1025,  1085,   215,   215,  1088,  1073,     4,
    1016,  1076,  1036,   217,  1036,     4,   215,  1039,  1016,  1025,
    1085,  1076,  1016,  1088,     4,  1016,  1016,  1025,     6,     3,
    1036,  1025,   217,  1039,  1025,  1025,  1058,     4,  1036,  1016,
    1016,  1063,  1036,  1016,  1016,  1067,  1036,  1016,  1025,  1025,
     214,  1073,  1025,  1025,  1076,  1016,  1025,     8,  1016,  1036,
    1016,  1016,  1016,  1085,  1025,  1016,  1088,  1025,  1016,  1025,
    1025,  1025,  1016,   214,  1025,  1016,  1016,  1025,  1016,  1085,
       8,  1025,  1088,     4,  1025,  1025,     8,  1025,  1025,     3,
    1025,     8,   214,     4,     4,     4,     4,   501,     5,   710,
       4,   214,     7,     4,     4,     4,     4,   736,   698,   497,
     707,  1010,  1015,  1034,  1028,  1044,   791,  1063,   214,   551,
    1031,   214,  1018,  1051,  1269,   214,  1016,  1042,    77,   214,
     513,  1019,   214,   214,   214,  1021,  1027,   543,   214,   214,
    1024,  1022,   214,   214,  1087,   214,   214,   761,  1085,   214,
    1085,  1088,   214,  1088,   217,   215,   214,   214,   217,   215,
    1275,   215,   214,  1085,  1090,  1041,   523,  1037,  1039,  1058,
    1067,  1088,   548,  1073,   516,  1077,   747,   568,   709,  1311,
    1290,  1331,  1080,    -1,    -1,    -1,    -1,    -1,  1269,    -1,
      -1,    -1,   533,    -1,  1275,    -1,    -1,   572,    -1,    -1,
    1269,  1221,    -1,    -1,  1269,    -1,    -1,    -1,    -1,  1290,
    1275,    -1,    -1,    -1,  1269,    -1,  1269,    -1,    -1,    -1,
    1275,    -1,  1275,    -1,    -1,  1290,    -1,    -1,  1269,  1269,
      -1,  1269,  1269,  1269,    -1,  1290,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1269,    -1,  1269,    -1,    -1,
      -1,  1275,    -1,  1275,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1269,    -1,    -1,    -1,    -1,  1290,  1275,
      -1,  1269,    -1,    -1,    -1,  1269,    -1,  1275,  1269,  1269,
      -1,  1275,    -1,    -1,    -1,  1275,    -1,    -1,    -1,    -1,
      -1,    -1,  1269,  1269,    -1,    -1,  1269,  1269,  1275,    -1,
    1269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1269,    -1,
      -1,  1269,    -1,  1269,  1269,  1269,    -1,    -1,  1269,    -1,
      -1,  1269,    -1,    -1,    -1,  1269,    -1,    -1,  1269,  1269,
      -1,  1269,  1269,    -1,  1269
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       0,     5,     7,     9,   214,   215,   216,   217,   234,   235,
     236,   241,     7,   250,     7,   255,     7,   301,     7,   418,
       7,   498,     7,   514,     7,   531,     7,   450,     7,   456,
       7,   480,     7,   394,     7,   600,     7,   631,   242,   237,
     251,   256,   302,   419,   499,   515,   532,   451,   457,   481,
     395,   601,   632,   234,   243,   244,   214,   239,   240,    10,
     252,   254,    11,    12,    15,    18,    19,    20,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    90,    91,   100,
     101,   107,   112,   113,   114,   115,   116,   117,   118,   120,
     125,   134,   137,   144,   152,   153,   157,   160,   164,   185,
     186,   187,   188,   189,   198,   214,   249,   257,   258,   259,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   281,   283,
     285,   286,   287,   289,   291,   292,   293,   294,   296,   297,
     298,   299,   308,   310,   312,   361,   367,   373,   379,   381,
     388,   402,   412,   432,   433,   434,   435,   440,   448,   474,
     504,   506,   525,   555,   567,   579,   580,   588,   598,   629,
     638,   662,    16,    17,   249,   303,   304,   305,   307,   504,
     506,    92,    94,   102,   103,   104,   105,   106,   121,   124,
     132,   249,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   275,   276,   277,   278,   281,
     283,   285,   286,   287,   289,   291,   420,   421,   422,   424,
     426,   428,   430,   432,   433,   434,   435,   438,   439,   474,
     492,   504,   506,   508,   525,   550,    93,   249,   428,   430,
     474,   500,   501,   502,   504,   506,    95,    96,    97,    98,
      99,   249,   428,   430,   474,   504,   506,   516,   517,   518,
     520,   521,   523,   524,   120,   126,   127,   128,   129,   130,
     131,   249,   474,   504,   506,   533,   534,   535,   536,   538,
     540,   542,   544,   546,   548,   448,    21,    81,    83,    84,
      87,    88,    89,   249,   330,   458,   459,   460,   461,   462,
     463,   464,   466,   468,   470,   471,   473,   504,   506,    82,
      85,    86,   249,   330,   462,   468,   482,   483,   484,   485,
     486,   488,   489,   490,   491,   504,   506,   135,   136,   249,
     396,   397,   398,   400,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   185,   186,   249,
     504,   506,   602,   603,   604,   605,   607,   609,   610,   612,
     613,   614,   617,   619,   620,   621,   623,   625,   627,    13,
      14,   633,   634,   635,   637,     6,     3,     4,     8,     3,
     253,     3,     8,   260,   630,   300,   309,   311,   313,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   295,     4,     4,     4,     4,     4,   279,
     282,   284,     4,     4,     4,   413,   449,   475,     4,   441,
     505,   507,   436,     4,     4,     4,   368,   380,   374,   362,
     556,   526,   389,   403,   568,     4,   382,   581,   589,   599,
     288,   290,     4,     4,   639,   663,     4,     3,     8,   306,
       4,     3,     8,   493,   509,   423,   425,   427,     4,     4,
     431,   429,   551,     3,     8,   503,     3,     8,   519,     4,
     522,     4,     4,     3,     8,   549,   537,   539,   541,   543,
     545,   547,     8,     3,     8,   465,   331,     4,   469,   467,
     472,     4,     8,     3,   487,     4,     4,     8,     3,   399,
     401,     3,     8,     4,   606,   608,     4,   611,     4,     4,
     615,   618,     4,     4,   622,   624,   626,   628,     3,     8,
     636,     4,     3,     8,   234,   234,   214,     4,     4,     4,
       4,     4,     4,     4,   215,   215,   215,   215,   215,   215,
     215,   215,   217,   216,   216,   216,   215,   215,     4,   215,
     215,   217,   217,   217,     4,     4,     4,   217,   217,   217,
       4,     4,     4,   215,     4,     4,     4,     4,   217,   217,
     217,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     215,     4,     4,     4,     4,     4,     4,   217,   217,     4,
       4,   258,     4,   217,   304,     4,     4,     4,     4,     4,
     215,   217,     4,     4,     4,   421,     4,   501,     4,   215,
       4,   215,   215,   517,     4,     4,     4,     4,     4,     4,
       4,   535,     4,     4,   215,     4,     4,     4,   217,   460,
       4,   217,   217,   484,     4,     4,   397,   217,     4,     4,
     215,     4,   215,   215,     4,     4,   217,   217,     4,     4,
       4,     4,   603,     4,   215,   634,     4,     7,   214,     7,
       7,     7,     7,     5,   214,   181,   182,   183,   184,   217,
     280,   214,   214,     5,     5,     5,     5,   236,   238,   214,
     108,   109,   110,   111,   437,     5,     5,     5,     7,     5,
       5,     5,     7,     7,     7,     7,     7,     7,   214,   214,
       5,     7,     5,   245,     5,     5,   214,   214,   214,   245,
     214,     7,   214,   214,   214,   245,   245,   245,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   238,
     214,   214,   214,   178,   179,   616,   180,   280,   214,   214,
     214,     5,   234,   257,   633,   303,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
     249,   318,   319,   320,   323,   325,   327,   329,   330,   332,
     333,   334,   335,   336,   337,   340,   341,   342,   343,   344,
     346,   347,   349,   351,   353,   355,   357,   359,   318,     7,
     314,   315,   316,     7,   414,   415,   416,     7,   452,   453,
     454,     7,   476,   477,   478,     7,   442,   443,   444,   128,
     214,   369,   370,   371,   372,   243,   129,   131,   371,   375,
     376,   377,   378,   119,   363,   364,   365,     7,   557,   558,
       7,   527,   528,   529,     7,   390,   391,   392,   138,   139,
     140,   141,   142,   143,   404,   405,   406,   407,   408,   409,
     410,   411,    21,   148,   149,   150,   151,   249,   332,   504,
     506,   569,   570,   571,   574,   575,   577,   578,   154,   155,
     156,   249,   383,   384,   385,   386,   387,   504,   506,   158,
     159,   249,   504,   506,   582,   583,   584,   586,   161,   162,
     163,   214,   504,   506,   590,   591,   592,   593,   595,   596,
     602,     7,   640,   641,   199,   249,   664,   665,   666,   246,
       7,   494,   495,   496,     7,   510,   511,   512,   133,   536,
     552,   553,   314,     8,     8,     8,   321,   324,   326,   328,
       4,     4,     4,     4,     4,   345,     4,     4,   338,   348,
     350,   352,     4,     4,     4,     4,   354,   356,   358,   360,
       3,     8,     8,   317,     6,     3,   417,     6,     3,   455,
       6,     3,   479,     6,     3,   445,     6,     3,     3,     6,
       6,     3,     6,   366,     3,     8,   559,     3,     6,   530,
       6,     3,   393,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   572,   576,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   585,   587,     3,     8,     4,
     594,     4,   597,     3,     8,     8,   642,     3,     6,     4,
       3,     8,   214,   247,   248,   497,     6,     3,   513,     6,
       3,   554,     8,     6,     4,     4,     4,     4,   215,   217,
     215,   217,   215,     4,   215,   215,     4,     4,     4,     4,
     215,   215,   217,   215,     4,     4,     4,     4,   319,   318,
     316,   420,   416,   458,   454,   482,   478,   249,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   275,   276,   277,   278,   281,   283,   285,   286,   287,
     289,   291,   330,   412,   424,   426,   428,   430,   432,   433,
     434,   435,   439,   446,   447,   474,   504,   506,   550,   444,
     370,   376,     4,   364,   122,   123,   249,   261,   262,   263,
     264,   265,   266,   330,   474,   504,   506,   560,   561,   562,
     563,   564,   566,   558,   533,   529,   396,   392,   215,   215,
     215,   215,   215,   215,   405,     4,     4,   215,   215,   215,
     570,   217,   215,   215,   384,     4,     4,   583,   217,     4,
     215,     4,   591,   190,   192,   193,   249,   330,   504,   506,
     643,   644,   645,   646,   648,   641,   217,   665,     6,     3,
     500,   496,   516,   512,     4,    22,    23,    24,    25,   322,
     214,   214,   214,   214,    38,    39,    40,   339,   214,   214,
     214,   214,   214,   214,   214,     8,     8,     8,     8,     3,
       8,   214,   565,     4,     8,     3,     8,     8,   145,   146,
     147,   573,   214,   214,   214,   214,   234,   649,     4,   647,
       3,     8,   214,     8,     8,   214,   447,     4,   217,   562,
       4,   215,     4,   644,   214,     5,   214,     7,   650,   651,
     652,     3,     6,   191,   194,   195,   196,   197,   653,   654,
     655,   657,   658,   659,   660,   651,   656,     4,     4,     4,
     661,     3,     8,     4,   217,   215,   215,     4,   654,   214,
     214
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
     258,   258,   258,   258,   258,   258,   260,   259,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   279,   278,   280,   280,   280,
     280,   280,   282,   281,   284,   283,   285,   286,   288,   287,
     290,   289,   291,   292,   293,   295,   294,   296,   297,   298,
     300,   299,   302,   301,   303,   303,   303,   304,   304,   304,
     304,   304,   306,   305,   307,   309,   308,   311,   310,   313,
     312,   314,   314,   315,   315,   315,   317,   316,   318,   318,
     318,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   321,   320,   322,
     322,   322,   322,   324,   323,   326,   325,   328,   327,   329,
     331,   330,   332,   333,   334,   335,   336,   338,   337,   339,
     339,   339,   340,   341,   342,   343,   345,   344,   346,   348,
     347,   350,   349,   352,   351,   354,   353,   356,   355,   358,
     357,   360,   359,   362,   361,   363,   363,   363,   364,   366,
     365,   368,   367,   369,   369,   369,   370,   370,   371,   372,
     374,   373,   375,   375,   375,   376,   376,   376,   377,   378,
     380,   379,   382,   381,   383,   383,   383,   384,   384,   384,
     384,   384,   384,   385,   386,   387,   389,   388,   390,   390,
     391,   391,   391,   393,   392,   395,   394,   396,   396,   396,
     396,   397,   397,   399,   398,   401,   400,   403,   402,   404,
     404,   404,   405,   405,   405,   405,   405,   405,   406,   407,
     408,   409,   410,   411,   413,   412,   414,   414,   415,   415,
     415,   417,   416,   419,   418,   420,   420,   420,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   423,   422,   425,   424,   427,   426,   429,   428,   431,
     430,   432,   433,   434,   436,   435,   437,   437,   437,   437,
     438,   439,   441,   440,   442,   442,   443,   443,   443,   445,
     444,   446,   446,   446,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   449,   448,   451,   450,   452,   452,
     453,   453,   453,   455,   454,   457,   456,   458,   458,   459,
     459,   459,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   461,   462,   463,   465,   464,   467,   466,   469,
     468,   470,   472,   471,   473,   475,   474,   476,   476,   477,
     477,   477,   479,   478,   481,   480,   482,   482,   483,   483,
     483,   484,   484,   484,   484,   484,   484,   484,   484,   484,
     485,   487,   486,   488,   489,   490,   491,   493,   492,   494,
     494,   495,   495,   495,   497,   496,   499,   498,   500,   500,
     500,   501,   501,   501,   501,   501,   501,   501,   503,   502,
     505,   504,   507,   506,   509,   508,   510,   510,   511,   511,
     511,   513,   512,   515,   514,   516,   516,   516,   517,   517,
     517,   517,   517,   517,   517,   517,   517,   517,   517,   519,
     518,   520,   522,   521,   523,   524,   526,   525,   527,   527,
     528,   528,   528,   530,   529,   532,   531,   533,   533,   534,
     534,   534,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   537,   536,   539,   538,   541,   540,   543,
     542,   545,   544,   547,   546,   549,   548,   551,   550,   552,
     552,   554,   553,   556,   555,   557,   557,   557,   559,   558,
     560,   560,   561,   561,   561,   562,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   563,   565,
     564,   566,   568,   567,   569,   569,   569,   570,   570,   570,
     570,   570,   570,   570,   570,   570,   572,   571,   573,   573,
     573,   574,   576,   575,   577,   578,   579,   581,   580,   582,
     582,   582,   583,   583,   583,   583,   583,   585,   584,   587,
     586,   589,   588,   590,   590,   590,   591,   591,   591,   591,
     591,   591,   592,   594,   593,   595,   597,   596,   599,   598,
     601,   600,   602,   602,   602,   603,   603,   603,   603,   603,
     603,   603,   603,   603,   603,   603,   603,   603,   603,   603,
     603,   603,   603,   604,   606,   605,   608,   607,   609,   611,
     610,   612,   613,   615,   614,   616,   616,   618,   617,   619,
     620,   622,   621,   624,   623,   626,   625,   628,   627,   630,
     629,   632,   631,   633,   633,   633,   634,   634,   636,   635,
     637,   639,   638,   640,   640,   640,   642,   641,   643,   643,
     643,   644,   644,   644,   644,   644,   644,   644,   645,   647,
     646,   649,   648,   650,   650,   650,   652,   651,   653,   653,
     653,   654,   654,   654,   654,   654,   656,   655,   657,   658,
     659,   661,   660,   663,   662,   664,   664,   664,   665,   665,
     666
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
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     3,     3,     3,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     6,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
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
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       3
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
  "\"hostname-char-replacement\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_object", "$@19", "global_object_comma", "sub_dhcp6", "$@20",
  "global_params", "global_param", "data_directory", "$@21",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "cache_threshold", "cache_max_age",
  "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@27",
  "parked_packet_limit", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@28",
  "sub_interfaces6", "$@29", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@30", "re_detect",
  "lease_database", "$@31", "hosts_database", "$@32", "hosts_databases",
  "$@33", "database_list", "not_empty_database_list", "database", "$@34",
  "database_map_params", "database_map_param", "database_type", "$@35",
  "db_type", "user", "$@36", "password", "$@37", "host", "$@38", "port",
  "name", "$@39", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "on_fail", "$@40", "on_fail_mode",
  "max_row_errors", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@41", "max_reconnect_tries", "keyspace", "$@42",
  "consistency", "$@43", "serial_consistency", "$@44", "trust_anchor",
  "$@45", "cert_file", "$@46", "key_file", "$@47", "cipher_list", "$@48",
  "sanity_checks", "$@49", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@50", "mac_sources", "$@51", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
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
     552,   553,   554,   555,   556,   557,   560,   560,   569,   575,
     581,   587,   593,   599,   605,   611,   617,   623,   629,   635,
     641,   647,   653,   659,   665,   671,   671,   680,   683,   686,
     689,   692,   698,   698,   707,   707,   716,   722,   728,   728,
     737,   737,   746,   752,   758,   764,   764,   773,   779,   785,
     791,   791,   803,   803,   812,   813,   814,   819,   820,   821,
     822,   823,   826,   826,   837,   843,   843,   856,   856,   869,
     869,   880,   881,   884,   885,   886,   891,   891,   901,   902,
     903,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   936,   936,   944,
     945,   946,   947,   950,   950,   959,   959,   968,   968,   977,
     983,   983,   992,   998,  1004,  1010,  1016,  1022,  1022,  1030,
    1031,  1032,  1035,  1041,  1047,  1053,  1059,  1059,  1068,  1074,
    1074,  1083,  1083,  1092,  1092,  1101,  1101,  1110,  1110,  1119,
    1119,  1128,  1128,  1137,  1137,  1148,  1149,  1150,  1155,  1157,
    1157,  1176,  1176,  1187,  1188,  1189,  1194,  1195,  1198,  1203,
    1208,  1208,  1219,  1220,  1221,  1226,  1227,  1228,  1231,  1236,
    1243,  1243,  1256,  1256,  1269,  1270,  1271,  1276,  1277,  1278,
    1279,  1280,  1281,  1284,  1290,  1296,  1302,  1302,  1313,  1314,
    1317,  1318,  1319,  1324,  1324,  1334,  1334,  1344,  1345,  1346,
    1349,  1352,  1353,  1356,  1356,  1365,  1365,  1374,  1374,  1386,
    1387,  1388,  1393,  1394,  1395,  1396,  1397,  1398,  1401,  1407,
    1413,  1419,  1425,  1431,  1440,  1440,  1454,  1455,  1458,  1459,
    1460,  1469,  1469,  1495,  1495,  1506,  1507,  1508,  1514,  1515,
    1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,
    1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,
    1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,
    1556,  1559,  1559,  1568,  1568,  1577,  1577,  1586,  1586,  1595,
    1595,  1606,  1612,  1618,  1624,  1624,  1632,  1633,  1634,  1635,
    1638,  1644,  1652,  1652,  1664,  1665,  1669,  1670,  1671,  1676,
    1676,  1684,  1685,  1686,  1691,  1692,  1693,  1694,  1695,  1696,
    1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,
    1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,
    1717,  1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,
    1727,  1728,  1729,  1730,  1737,  1737,  1751,  1751,  1760,  1761,
    1764,  1765,  1766,  1773,  1773,  1788,  1788,  1802,  1803,  1806,
    1807,  1808,  1813,  1814,  1815,  1816,  1817,  1818,  1819,  1820,
    1821,  1822,  1825,  1827,  1833,  1835,  1835,  1844,  1844,  1853,
    1853,  1862,  1864,  1864,  1873,  1883,  1883,  1896,  1897,  1902,
    1903,  1904,  1911,  1911,  1923,  1923,  1935,  1936,  1941,  1942,
    1943,  1950,  1951,  1952,  1953,  1954,  1955,  1956,  1957,  1958,
    1961,  1963,  1963,  1972,  1974,  1976,  1982,  1991,  1991,  2004,
    2005,  2008,  2009,  2010,  2015,  2015,  2025,  2025,  2035,  2036,
    2037,  2042,  2043,  2044,  2045,  2046,  2047,  2048,  2051,  2051,
    2060,  2060,  2085,  2085,  2115,  2115,  2128,  2129,  2132,  2133,
    2134,  2139,  2139,  2151,  2151,  2163,  2164,  2165,  2170,  2171,
    2172,  2173,  2174,  2175,  2176,  2177,  2178,  2179,  2180,  2183,
    2183,  2192,  2198,  2198,  2207,  2213,  2222,  2222,  2233,  2234,
    2237,  2238,  2239,  2244,  2244,  2253,  2253,  2262,  2263,  2266,
    2267,  2268,  2274,  2275,  2276,  2277,  2278,  2279,  2280,  2281,
    2282,  2283,  2284,  2287,  2287,  2298,  2298,  2309,  2309,  2318,
    2318,  2327,  2327,  2336,  2336,  2345,  2345,  2359,  2359,  2370,
    2371,  2374,  2374,  2386,  2386,  2397,  2398,  2399,  2404,  2404,
    2414,  2415,  2418,  2419,  2420,  2425,  2426,  2427,  2428,  2429,
    2430,  2431,  2432,  2433,  2434,  2435,  2436,  2437,  2440,  2442,
    2442,  2451,  2460,  2460,  2473,  2474,  2475,  2480,  2481,  2482,
    2483,  2484,  2485,  2486,  2487,  2488,  2491,  2491,  2499,  2500,
    2501,  2504,  2510,  2510,  2519,  2525,  2533,  2541,  2541,  2552,
    2553,  2554,  2559,  2560,  2561,  2562,  2563,  2566,  2566,  2575,
    2575,  2587,  2587,  2600,  2601,  2602,  2607,  2608,  2609,  2610,
    2611,  2612,  2615,  2621,  2621,  2630,  2636,  2636,  2646,  2646,
    2659,  2659,  2669,  2670,  2671,  2676,  2677,  2678,  2679,  2680,
    2681,  2682,  2683,  2684,  2685,  2686,  2687,  2688,  2689,  2690,
    2691,  2692,  2693,  2696,  2703,  2703,  2712,  2712,  2721,  2727,
    2727,  2736,  2742,  2748,  2748,  2757,  2758,  2761,  2761,  2771,
    2778,  2785,  2785,  2794,  2794,  2804,  2804,  2814,  2814,  2826,
    2826,  2838,  2838,  2848,  2849,  2850,  2856,  2857,  2860,  2860,
    2871,  2879,  2879,  2892,  2893,  2894,  2900,  2900,  2908,  2909,
    2910,  2915,  2916,  2917,  2918,  2919,  2920,  2921,  2924,  2930,
    2930,  2939,  2939,  2950,  2951,  2952,  2957,  2957,  2965,  2966,
    2967,  2972,  2973,  2974,  2975,  2976,  2979,  2979,  2988,  2994,
    3000,  3006,  3006,  3015,  3015,  3026,  3027,  3028,  3033,  3034,
    3037
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
#line 6438 "dhcp6_parser.cc"

#line 3043 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
