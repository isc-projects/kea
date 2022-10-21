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
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 295 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 295 "dhcp6_parser.yy"
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
#line 304 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 305 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 306 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 307 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 308 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 309 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 310 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 311 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 312 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 313 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 314 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 315 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 316 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 317 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 325 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 326 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 327 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 328 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 329 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 330 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 331 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 334 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 339 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 344 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 350 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 357 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 362 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 368 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 373 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 376 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 384 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 388 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 392 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 398 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 400 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 409 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 413 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 417 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 427 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 436 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 441 "dhcp6_parser.yy"
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
#line 451 "dhcp6_parser.yy"
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
#line 460 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 468 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 474 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 478 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 485 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 137: // $@21: %empty
#line 559 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 138: // data_directory: "data-directory" $@21 ":" "constant string"
#line 562 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 139: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 568 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 140: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 574 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 141: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 580 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 586 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 592 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 598 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 604 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 610 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 616 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 622 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 628 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 634 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 640 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 646 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 153: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 652 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 154: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 658 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 155: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 664 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 156: // $@22: %empty
#line 670 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 673 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "when-present"
#line 679 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "never"
#line 682 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "always"
#line 685 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-not-present"
#line 688 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "boolean"
#line 691 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 163: // $@23: %empty
#line 697 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 164: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 700 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 165: // $@24: %empty
#line 706 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 166: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 709 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 167: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 715 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 168: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 721 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 169: // $@25: %empty
#line 727 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 730 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 171: // $@26: %empty
#line 736 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 739 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 173: // store_extended_info: "store-extended-info" ":" "boolean"
#line 745 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 174: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 751 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 175: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 757 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 176: // $@27: %empty
#line 763 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 177: // server_tag: "server-tag" $@27 ":" "constant string"
#line 766 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 178: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 772 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 179: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 778 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 180: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 784 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 181: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 790 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 182: // $@28: %empty
#line 796 "dhcp6_parser.yy"
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
#line 802 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 184: // $@29: %empty
#line 808 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 185: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 812 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // interfaces_config_params: interfaces_config_params ","
#line 819 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1598 "dhcp6_parser.cc"
    break;

  case 197: // $@30: %empty
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

  case 198: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 840 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 199: // re_detect: "re-detect" ":" "boolean"
#line 845 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 200: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 851 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 201: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 857 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 202: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 863 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 869 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1671 "dhcp6_parser.cc"
    break;

  case 204: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 875 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1682 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 882 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1694 "dhcp6_parser.cc"
    break;

  case 206: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 888 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1705 "dhcp6_parser.cc"
    break;

  case 207: // $@33: %empty
#line 895 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1717 "dhcp6_parser.cc"
    break;

  case 208: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 901 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 213: // not_empty_database_list: not_empty_database_list ","
#line 912 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1734 "dhcp6_parser.cc"
    break;

  case 214: // $@34: %empty
#line 917 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1744 "dhcp6_parser.cc"
    break;

  case 215: // database: "{" $@34 database_map_params "}"
#line 921 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1754 "dhcp6_parser.cc"
    break;

  case 218: // database_map_params: database_map_params ","
#line 929 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1762 "dhcp6_parser.cc"
    break;

  case 238: // $@35: %empty
#line 955 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1771 "dhcp6_parser.cc"
    break;

  case 239: // database_type: "type" $@35 ":" db_type
#line 958 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 240: // db_type: "memfile"
#line 963 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1786 "dhcp6_parser.cc"
    break;

  case 241: // db_type: "mysql"
#line 964 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1792 "dhcp6_parser.cc"
    break;

  case 242: // db_type: "postgresql"
#line 965 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1798 "dhcp6_parser.cc"
    break;

  case 243: // $@36: %empty
#line 968 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc"
    break;

  case 244: // user: "user" $@36 ":" "constant string"
#line 971 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 245: // $@37: %empty
#line 977 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1826 "dhcp6_parser.cc"
    break;

  case 246: // password: "password" $@37 ":" "constant string"
#line 980 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1836 "dhcp6_parser.cc"
    break;

  case 247: // $@38: %empty
#line 986 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 248: // host: "host" $@38 ":" "constant string"
#line 989 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 249: // port: "port" ":" "integer"
#line 995 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 250: // $@39: %empty
#line 1001 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 251: // name: "name" $@39 ":" "constant string"
#line 1004 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1884 "dhcp6_parser.cc"
    break;

  case 252: // persist: "persist" ":" "boolean"
#line 1010 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1894 "dhcp6_parser.cc"
    break;

  case 253: // lfc_interval: "lfc-interval" ":" "integer"
#line 1016 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 254: // readonly: "readonly" ":" "boolean"
#line 1022 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 255: // connect_timeout: "connect-timeout" ":" "integer"
#line 1028 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 256: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1034 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 257: // $@40: %empty
#line 1040 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 258: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1043 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 259: // on_fail_mode: "stop-retry-exit"
#line 1048 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1958 "dhcp6_parser.cc"
    break;

  case 260: // on_fail_mode: "serve-retry-exit"
#line 1049 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1964 "dhcp6_parser.cc"
    break;

  case 261: // on_fail_mode: "serve-retry-continue"
#line 1050 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1970 "dhcp6_parser.cc"
    break;

  case 262: // max_row_errors: "max-row-errors" ":" "integer"
#line 1053 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 263: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1059 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1990 "dhcp6_parser.cc"
    break;

  case 264: // $@41: %empty
#line 1065 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 265: // trust_anchor: "trust-anchor" $@41 ":" "constant string"
#line 1068 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1074 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 267: // cert_file: "cert-file" $@42 ":" "constant string"
#line 1077 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2028 "dhcp6_parser.cc"
    break;

  case 268: // $@43: %empty
#line 1083 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 269: // key_file: "key-file" $@43 ":" "constant string"
#line 1086 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 270: // $@44: %empty
#line 1092 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 271: // cipher_list: "cipher-list" $@44 ":" "constant string"
#line 1095 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 272: // $@45: %empty
#line 1101 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2078 "dhcp6_parser.cc"
    break;

  case 273: // sanity_checks: "sanity-checks" $@45 ":" "{" sanity_checks_params "}"
#line 1107 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 276: // sanity_checks_params: sanity_checks_params ","
#line 1114 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2095 "dhcp6_parser.cc"
    break;

  case 279: // $@46: %empty
#line 1123 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2104 "dhcp6_parser.cc"
    break;

  case 280: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1126 "dhcp6_parser.yy"
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
#line 2124 "dhcp6_parser.cc"
    break;

  case 281: // $@47: %empty
#line 1142 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2133 "dhcp6_parser.cc"
    break;

  case 282: // extended_info_checks: "extended-info-checks" $@47 ":" "constant string"
#line 1145 "dhcp6_parser.yy"
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
#line 2152 "dhcp6_parser.cc"
    break;

  case 283: // $@48: %empty
#line 1160 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 284: // mac_sources: "mac-sources" $@48 ":" "[" mac_sources_list "]"
#line 1166 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 287: // mac_sources_list: mac_sources_list ","
#line 1173 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2181 "dhcp6_parser.cc"
    break;

  case 290: // duid_id: "duid"
#line 1182 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 291: // string_id: "constant string"
#line 1187 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2199 "dhcp6_parser.cc"
    break;

  case 292: // $@49: %empty
#line 1192 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 293: // host_reservation_identifiers: "host-reservation-identifiers" $@49 ":" "[" host_reservation_identifiers_list "]"
#line 1198 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 296: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1205 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2228 "dhcp6_parser.cc"
    break;

  case 300: // hw_address_id: "hw-address"
#line 1215 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2237 "dhcp6_parser.cc"
    break;

  case 301: // flex_id: "flex-id"
#line 1220 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2246 "dhcp6_parser.cc"
    break;

  case 302: // $@50: %empty
#line 1227 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 303: // relay_supplied_options: "relay-supplied-options" $@50 ":" "[" list_content "]"
#line 1233 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 304: // $@51: %empty
#line 1240 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2279 "dhcp6_parser.cc"
    break;

  case 305: // dhcp_multi_threading: "multi-threading" $@51 ":" "{" multi_threading_params "}"
#line 1246 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc"
    break;

  case 308: // multi_threading_params: multi_threading_params ","
#line 1255 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2298 "dhcp6_parser.cc"
    break;

  case 315: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1268 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2308 "dhcp6_parser.cc"
    break;

  case 316: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1274 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 317: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1280 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2328 "dhcp6_parser.cc"
    break;

  case 318: // $@52: %empty
#line 1286 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2340 "dhcp6_parser.cc"
    break;

  case 319: // hooks_libraries: "hooks-libraries" $@52 ":" "[" hooks_libraries_list "]"
#line 1292 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2349 "dhcp6_parser.cc"
    break;

  case 324: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1303 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2357 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1308 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 326: // hooks_library: "{" $@53 hooks_params "}"
#line 1312 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2377 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1318 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 328: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1322 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2397 "dhcp6_parser.cc"
    break;

  case 331: // hooks_params: hooks_params ","
#line 1330 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2405 "dhcp6_parser.cc"
    break;

  case 335: // $@55: %empty
#line 1340 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp6_parser.cc"
    break;

  case 336: // library: "library" $@55 ":" "constant string"
#line 1343 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 337: // $@56: %empty
#line 1349 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2433 "dhcp6_parser.cc"
    break;

  case 338: // parameters: "parameters" $@56 ":" map_value
#line 1352 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2442 "dhcp6_parser.cc"
    break;

  case 339: // $@57: %empty
#line 1358 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2454 "dhcp6_parser.cc"
    break;

  case 340: // expired_leases_processing: "expired-leases-processing" $@57 ":" "{" expired_leases_params "}"
#line 1364 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2464 "dhcp6_parser.cc"
    break;

  case 343: // expired_leases_params: expired_leases_params ","
#line 1372 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2472 "dhcp6_parser.cc"
    break;

  case 350: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1385 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2482 "dhcp6_parser.cc"
    break;

  case 351: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1391 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2492 "dhcp6_parser.cc"
    break;

  case 352: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1397 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2502 "dhcp6_parser.cc"
    break;

  case 353: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1403 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2512 "dhcp6_parser.cc"
    break;

  case 354: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1409 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2522 "dhcp6_parser.cc"
    break;

  case 355: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1415 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 356: // $@58: %empty
#line 1424 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2544 "dhcp6_parser.cc"
    break;

  case 357: // subnet6_list: "subnet6" $@58 ":" "[" subnet6_list_content "]"
#line 1430 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2553 "dhcp6_parser.cc"
    break;

  case 362: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1444 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2561 "dhcp6_parser.cc"
    break;

  case 363: // $@59: %empty
#line 1453 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2571 "dhcp6_parser.cc"
    break;

  case 364: // subnet6: "{" $@59 subnet6_params "}"
#line 1457 "dhcp6_parser.yy"
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
#line 2597 "dhcp6_parser.cc"
    break;

  case 365: // $@60: %empty
#line 1479 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2607 "dhcp6_parser.cc"
    break;

  case 366: // sub_subnet6: "{" $@60 subnet6_params "}"
#line 1483 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2617 "dhcp6_parser.cc"
    break;

  case 369: // subnet6_params: subnet6_params ","
#line 1492 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2625 "dhcp6_parser.cc"
    break;

  case 413: // $@61: %empty
#line 1543 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp6_parser.cc"
    break;

  case 414: // subnet: "subnet" $@61 ":" "constant string"
#line 1546 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc"
    break;

  case 415: // $@62: %empty
#line 1552 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 416: // interface: "interface" $@62 ":" "constant string"
#line 1555 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 417: // $@63: %empty
#line 1561 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp6_parser.cc"
    break;

  case 418: // interface_id: "interface-id" $@63 ":" "constant string"
#line 1564 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2682 "dhcp6_parser.cc"
    break;

  case 419: // $@64: %empty
#line 1570 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 420: // client_class: "client-class" $@64 ":" "constant string"
#line 1573 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 421: // $@65: %empty
#line 1579 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 422: // require_client_classes: "require-client-classes" $@65 ":" list_strings
#line 1585 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 423: // reservations_global: "reservations-global" ":" "boolean"
#line 1590 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 424: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1596 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 425: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1602 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2752 "dhcp6_parser.cc"
    break;

  case 426: // $@66: %empty
#line 1608 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2761 "dhcp6_parser.cc"
    break;

  case 427: // reservation_mode: "reservation-mode" $@66 ":" hr_mode
#line 1611 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2770 "dhcp6_parser.cc"
    break;

  case 428: // hr_mode: "disabled"
#line 1616 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2776 "dhcp6_parser.cc"
    break;

  case 429: // hr_mode: "out-of-pool"
#line 1617 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2782 "dhcp6_parser.cc"
    break;

  case 430: // hr_mode: "global"
#line 1618 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2788 "dhcp6_parser.cc"
    break;

  case 431: // hr_mode: "all"
#line 1619 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2794 "dhcp6_parser.cc"
    break;

  case 432: // id: "id" ":" "integer"
#line 1622 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 433: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1628 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 434: // $@67: %empty
#line 1636 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2826 "dhcp6_parser.cc"
    break;

  case 435: // shared_networks: "shared-networks" $@67 ":" "[" shared_networks_content "]"
#line 1642 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc"
    break;

  case 440: // shared_networks_list: shared_networks_list ","
#line 1655 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2843 "dhcp6_parser.cc"
    break;

  case 441: // $@68: %empty
#line 1660 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2853 "dhcp6_parser.cc"
    break;

  case 442: // shared_network: "{" $@68 shared_network_params "}"
#line 1664 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2861 "dhcp6_parser.cc"
    break;

  case 445: // shared_network_params: shared_network_params ","
#line 1670 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2869 "dhcp6_parser.cc"
    break;

  case 486: // $@69: %empty
#line 1721 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2881 "dhcp6_parser.cc"
    break;

  case 487: // option_def_list: "option-def" $@69 ":" "[" option_def_list_content "]"
#line 1727 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 488: // $@70: %empty
#line 1735 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2899 "dhcp6_parser.cc"
    break;

  case 489: // sub_option_def_list: "{" $@70 option_def_list "}"
#line 1738 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2907 "dhcp6_parser.cc"
    break;

  case 494: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1750 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2915 "dhcp6_parser.cc"
    break;

  case 495: // $@71: %empty
#line 1757 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 496: // option_def_entry: "{" $@71 option_def_params "}"
#line 1761 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2937 "dhcp6_parser.cc"
    break;

  case 497: // $@72: %empty
#line 1772 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2947 "dhcp6_parser.cc"
    break;

  case 498: // sub_option_def: "{" $@72 option_def_params "}"
#line 1776 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2959 "dhcp6_parser.cc"
    break;

  case 503: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1792 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2967 "dhcp6_parser.cc"
    break;

  case 515: // code: "code" ":" "integer"
#line 1811 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2977 "dhcp6_parser.cc"
    break;

  case 517: // $@73: %empty
#line 1819 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 518: // option_def_type: "type" $@73 ":" "constant string"
#line 1822 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2996 "dhcp6_parser.cc"
    break;

  case 519: // $@74: %empty
#line 1828 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 520: // option_def_record_types: "record-types" $@74 ":" "constant string"
#line 1831 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 521: // $@75: %empty
#line 1837 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 522: // space: "space" $@75 ":" "constant string"
#line 1840 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 524: // $@76: %empty
#line 1848 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3043 "dhcp6_parser.cc"
    break;

  case 525: // option_def_encapsulate: "encapsulate" $@76 ":" "constant string"
#line 1851 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 526: // option_def_array: "array" ":" "boolean"
#line 1857 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 527: // $@77: %empty
#line 1867 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3075 "dhcp6_parser.cc"
    break;

  case 528: // option_data_list: "option-data" $@77 ":" "[" option_data_list_content "]"
#line 1873 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 533: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1888 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3092 "dhcp6_parser.cc"
    break;

  case 534: // $@78: %empty
#line 1895 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3102 "dhcp6_parser.cc"
    break;

  case 535: // option_data_entry: "{" $@78 option_data_params "}"
#line 1899 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 536: // $@79: %empty
#line 1907 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 537: // sub_option_data: "{" $@79 option_data_params "}"
#line 1911 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 542: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1927 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3138 "dhcp6_parser.cc"
    break;

  case 553: // $@80: %empty
#line 1947 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3147 "dhcp6_parser.cc"
    break;

  case 554: // option_data_data: "data" $@80 ":" "constant string"
#line 1950 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 557: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1960 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 558: // option_data_always_send: "always-send" ":" "boolean"
#line 1966 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 559: // $@81: %empty
#line 1975 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 560: // pools_list: "pools" $@81 ":" "[" pools_list_content "]"
#line 1981 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 565: // not_empty_pools_list: not_empty_pools_list ","
#line 1994 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3206 "dhcp6_parser.cc"
    break;

  case 566: // $@82: %empty
#line 1999 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 567: // pool_list_entry: "{" $@82 pool_params "}"
#line 2003 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 568: // $@83: %empty
#line 2009 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 569: // sub_pool6: "{" $@83 pool_params "}"
#line 2013 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 572: // pool_params: pool_params ","
#line 2021 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3254 "dhcp6_parser.cc"
    break;

  case 580: // $@84: %empty
#line 2035 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp6_parser.cc"
    break;

  case 581: // pool_entry: "pool" $@84 ":" "constant string"
#line 2038 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3273 "dhcp6_parser.cc"
    break;

  case 582: // $@85: %empty
#line 2044 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3281 "dhcp6_parser.cc"
    break;

  case 583: // user_context: "user-context" $@85 ":" map_value
#line 2046 "dhcp6_parser.yy"
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
#line 3308 "dhcp6_parser.cc"
    break;

  case 584: // $@86: %empty
#line 2069 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3316 "dhcp6_parser.cc"
    break;

  case 585: // comment: "comment" $@86 ":" "constant string"
#line 2071 "dhcp6_parser.yy"
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
#line 3345 "dhcp6_parser.cc"
    break;

  case 586: // $@87: %empty
#line 2099 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 587: // pd_pools_list: "pd-pools" $@87 ":" "[" pd_pools_list_content "]"
#line 2105 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 592: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2118 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3374 "dhcp6_parser.cc"
    break;

  case 593: // $@88: %empty
#line 2123 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 594: // pd_pool_entry: "{" $@88 pd_pool_params "}"
#line 2127 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3396 "dhcp6_parser.cc"
    break;

  case 595: // $@89: %empty
#line 2135 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3406 "dhcp6_parser.cc"
    break;

  case 596: // sub_pd_pool: "{" $@89 pd_pool_params "}"
#line 2139 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 599: // pd_pool_params: pd_pool_params ","
#line 2149 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3426 "dhcp6_parser.cc"
    break;

  case 611: // $@90: %empty
#line 2167 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 612: // pd_prefix: "prefix" $@90 ":" "constant string"
#line 2170 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 613: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2176 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3455 "dhcp6_parser.cc"
    break;

  case 614: // $@91: %empty
#line 2182 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3464 "dhcp6_parser.cc"
    break;

  case 615: // excluded_prefix: "excluded-prefix" $@91 ":" "constant string"
#line 2185 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3474 "dhcp6_parser.cc"
    break;

  case 616: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2191 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 617: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2197 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 618: // $@92: %empty
#line 2206 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 619: // reservations: "reservations" $@92 ":" "[" reservations_list "]"
#line 2212 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3515 "dhcp6_parser.cc"
    break;

  case 624: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2223 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3523 "dhcp6_parser.cc"
    break;

  case 625: // $@93: %empty
#line 2228 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3533 "dhcp6_parser.cc"
    break;

  case 626: // reservation: "{" $@93 reservation_params "}"
#line 2232 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 627: // $@94: %empty
#line 2237 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 628: // sub_reservation: "{" $@94 reservation_params "}"
#line 2241 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3561 "dhcp6_parser.cc"
    break;

  case 633: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2252 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3569 "dhcp6_parser.cc"
    break;

  case 645: // $@95: %empty
#line 2271 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3581 "dhcp6_parser.cc"
    break;

  case 646: // ip_addresses: "ip-addresses" $@95 ":" list_strings
#line 2277 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3590 "dhcp6_parser.cc"
    break;

  case 647: // $@96: %empty
#line 2282 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3602 "dhcp6_parser.cc"
    break;

  case 648: // prefixes: "prefixes" $@96 ":" list_strings
#line 2288 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3611 "dhcp6_parser.cc"
    break;

  case 649: // $@97: %empty
#line 2293 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3620 "dhcp6_parser.cc"
    break;

  case 650: // duid: "duid" $@97 ":" "constant string"
#line 2296 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 651: // $@98: %empty
#line 2302 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 652: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2305 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 653: // $@99: %empty
#line 2311 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 654: // hostname: "hostname" $@99 ":" "constant string"
#line 2314 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 655: // $@100: %empty
#line 2320 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 656: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2323 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 657: // $@101: %empty
#line 2329 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 658: // reservation_client_classes: "client-classes" $@101 ":" list_strings
#line 2335 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 659: // $@102: %empty
#line 2343 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 660: // relay: "relay" $@102 ":" "{" relay_map "}"
#line 2349 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3729 "dhcp6_parser.cc"
    break;

  case 663: // $@103: %empty
#line 2358 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 664: // ip_address: "ip-address" $@103 ":" "constant string"
#line 2361 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3748 "dhcp6_parser.cc"
    break;

  case 665: // $@104: %empty
#line 2370 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3760 "dhcp6_parser.cc"
    break;

  case 666: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2376 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3769 "dhcp6_parser.cc"
    break;

  case 669: // client_classes_list: client_classes_list ","
#line 2383 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3777 "dhcp6_parser.cc"
    break;

  case 670: // $@105: %empty
#line 2388 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 671: // client_class_entry: "{" $@105 client_class_params "}"
#line 2392 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3797 "dhcp6_parser.cc"
    break;

  case 676: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2404 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3805 "dhcp6_parser.cc"
    break;

  case 692: // $@106: %empty
#line 2427 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 693: // client_class_test: "test" $@106 ":" "constant string"
#line 2430 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 694: // $@107: %empty
#line 2436 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 695: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2439 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 696: // only_if_required: "only-if-required" ":" "boolean"
#line 2445 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 697: // $@108: %empty
#line 2454 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3865 "dhcp6_parser.cc"
    break;

  case 698: // server_id: "server-id" $@108 ":" "{" server_id_params "}"
#line 2460 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 701: // server_id_params: server_id_params ","
#line 2469 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3884 "dhcp6_parser.cc"
    break;

  case 711: // $@109: %empty
#line 2485 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 712: // server_id_type: "type" $@109 ":" duid_type
#line 2488 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 713: // duid_type: "LLT"
#line 2493 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3908 "dhcp6_parser.cc"
    break;

  case 714: // duid_type: "EN"
#line 2494 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3914 "dhcp6_parser.cc"
    break;

  case 715: // duid_type: "LL"
#line 2495 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3920 "dhcp6_parser.cc"
    break;

  case 716: // htype: "htype" ":" "integer"
#line 2498 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 717: // $@110: %empty
#line 2504 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 718: // identifier: "identifier" $@110 ":" "constant string"
#line 2507 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 719: // time: "time" ":" "integer"
#line 2513 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3959 "dhcp6_parser.cc"
    break;

  case 720: // enterprise_id: "enterprise-id" ":" "integer"
#line 2519 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3969 "dhcp6_parser.cc"
    break;

  case 721: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2527 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3979 "dhcp6_parser.cc"
    break;

  case 722: // $@111: %empty
#line 2535 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3991 "dhcp6_parser.cc"
    break;

  case 723: // control_socket: "control-socket" $@111 ":" "{" control_socket_params "}"
#line 2541 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 726: // control_socket_params: control_socket_params ","
#line 2548 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4008 "dhcp6_parser.cc"
    break;

  case 732: // $@112: %empty
#line 2560 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4017 "dhcp6_parser.cc"
    break;

  case 733: // socket_type: "socket-type" $@112 ":" "constant string"
#line 2563 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 734: // $@113: %empty
#line 2569 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4036 "dhcp6_parser.cc"
    break;

  case 735: // socket_name: "socket-name" $@113 ":" "constant string"
#line 2572 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4046 "dhcp6_parser.cc"
    break;

  case 736: // $@114: %empty
#line 2581 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4058 "dhcp6_parser.cc"
    break;

  case 737: // dhcp_queue_control: "dhcp-queue-control" $@114 ":" "{" queue_control_params "}"
#line 2587 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 740: // queue_control_params: queue_control_params ","
#line 2596 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4077 "dhcp6_parser.cc"
    break;

  case 747: // enable_queue: "enable-queue" ":" "boolean"
#line 2609 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 748: // $@115: %empty
#line 2615 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4096 "dhcp6_parser.cc"
    break;

  case 749: // queue_type: "queue-type" $@115 ":" "constant string"
#line 2618 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4106 "dhcp6_parser.cc"
    break;

  case 750: // capacity: "capacity" ":" "integer"
#line 2624 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4116 "dhcp6_parser.cc"
    break;

  case 751: // $@116: %empty
#line 2630 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4125 "dhcp6_parser.cc"
    break;

  case 752: // arbitrary_map_entry: "constant string" $@116 ":" value
#line 2633 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4134 "dhcp6_parser.cc"
    break;

  case 753: // $@117: %empty
#line 2640 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4146 "dhcp6_parser.cc"
    break;

  case 754: // dhcp_ddns: "dhcp-ddns" $@117 ":" "{" dhcp_ddns_params "}"
#line 2646 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 755: // $@118: %empty
#line 2653 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4167 "dhcp6_parser.cc"
    break;

  case 756: // sub_dhcp_ddns: "{" $@118 dhcp_ddns_params "}"
#line 2657 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4177 "dhcp6_parser.cc"
    break;

  case 759: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2665 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4185 "dhcp6_parser.cc"
    break;

  case 778: // enable_updates: "enable-updates" ":" "boolean"
#line 2690 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 779: // $@119: %empty
#line 2697 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4204 "dhcp6_parser.cc"
    break;

  case 780: // dep_qualifying_suffix: "qualifying-suffix" $@119 ":" "constant string"
#line 2700 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 781: // $@120: %empty
#line 2706 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4223 "dhcp6_parser.cc"
    break;

  case 782: // server_ip: "server-ip" $@120 ":" "constant string"
#line 2709 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4233 "dhcp6_parser.cc"
    break;

  case 783: // server_port: "server-port" ":" "integer"
#line 2715 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4243 "dhcp6_parser.cc"
    break;

  case 784: // $@121: %empty
#line 2721 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4252 "dhcp6_parser.cc"
    break;

  case 785: // sender_ip: "sender-ip" $@121 ":" "constant string"
#line 2724 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4262 "dhcp6_parser.cc"
    break;

  case 786: // sender_port: "sender-port" ":" "integer"
#line 2730 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 787: // max_queue_size: "max-queue-size" ":" "integer"
#line 2736 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 788: // $@122: %empty
#line 2742 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4291 "dhcp6_parser.cc"
    break;

  case 789: // ncr_protocol: "ncr-protocol" $@122 ":" ncr_protocol_value
#line 2745 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4300 "dhcp6_parser.cc"
    break;

  case 790: // ncr_protocol_value: "UDP"
#line 2751 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4306 "dhcp6_parser.cc"
    break;

  case 791: // ncr_protocol_value: "TCP"
#line 2752 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4312 "dhcp6_parser.cc"
    break;

  case 792: // $@123: %empty
#line 2755 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4321 "dhcp6_parser.cc"
    break;

  case 793: // ncr_format: "ncr-format" $@123 ":" "JSON"
#line 2758 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4331 "dhcp6_parser.cc"
    break;

  case 794: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2765 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4341 "dhcp6_parser.cc"
    break;

  case 795: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2772 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4351 "dhcp6_parser.cc"
    break;

  case 796: // $@124: %empty
#line 2779 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4360 "dhcp6_parser.cc"
    break;

  case 797: // dep_replace_client_name: "replace-client-name" $@124 ":" ddns_replace_client_name_value
#line 2782 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 798: // $@125: %empty
#line 2788 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 799: // dep_generated_prefix: "generated-prefix" $@125 ":" "constant string"
#line 2791 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4388 "dhcp6_parser.cc"
    break;

  case 800: // $@126: %empty
#line 2798 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4397 "dhcp6_parser.cc"
    break;

  case 801: // dep_hostname_char_set: "hostname-char-set" $@126 ":" "constant string"
#line 2801 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 802: // $@127: %empty
#line 2808 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4416 "dhcp6_parser.cc"
    break;

  case 803: // dep_hostname_char_replacement: "hostname-char-replacement" $@127 ":" "constant string"
#line 2811 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4426 "dhcp6_parser.cc"
    break;

  case 804: // $@128: %empty
#line 2820 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4438 "dhcp6_parser.cc"
    break;

  case 805: // config_control: "config-control" $@128 ":" "{" config_control_params "}"
#line 2826 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4448 "dhcp6_parser.cc"
    break;

  case 806: // $@129: %empty
#line 2832 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4458 "dhcp6_parser.cc"
    break;

  case 807: // sub_config_control: "{" $@129 config_control_params "}"
#line 2836 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4467 "dhcp6_parser.cc"
    break;

  case 810: // config_control_params: config_control_params ","
#line 2844 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4475 "dhcp6_parser.cc"
    break;

  case 813: // $@130: %empty
#line 2854 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4487 "dhcp6_parser.cc"
    break;

  case 814: // config_databases: "config-databases" $@130 ":" "[" database_list "]"
#line 2860 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4496 "dhcp6_parser.cc"
    break;

  case 815: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2865 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4506 "dhcp6_parser.cc"
    break;

  case 816: // $@131: %empty
#line 2873 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4518 "dhcp6_parser.cc"
    break;

  case 817: // loggers: "loggers" $@131 ":" "[" loggers_entries "]"
#line 2879 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4527 "dhcp6_parser.cc"
    break;

  case 820: // loggers_entries: loggers_entries ","
#line 2888 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4535 "dhcp6_parser.cc"
    break;

  case 821: // $@132: %empty
#line 2894 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4545 "dhcp6_parser.cc"
    break;

  case 822: // logger_entry: "{" $@132 logger_params "}"
#line 2898 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 825: // logger_params: logger_params ","
#line 2904 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4561 "dhcp6_parser.cc"
    break;

  case 833: // debuglevel: "debuglevel" ":" "integer"
#line 2918 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4571 "dhcp6_parser.cc"
    break;

  case 834: // $@133: %empty
#line 2924 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4580 "dhcp6_parser.cc"
    break;

  case 835: // severity: "severity" $@133 ":" "constant string"
#line 2927 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4590 "dhcp6_parser.cc"
    break;

  case 836: // $@134: %empty
#line 2933 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4602 "dhcp6_parser.cc"
    break;

  case 837: // output_options_list: "output_options" $@134 ":" "[" output_options_list_content "]"
#line 2939 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4611 "dhcp6_parser.cc"
    break;

  case 840: // output_options_list_content: output_options_list_content ","
#line 2946 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4619 "dhcp6_parser.cc"
    break;

  case 841: // $@135: %empty
#line 2951 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4629 "dhcp6_parser.cc"
    break;

  case 842: // output_entry: "{" $@135 output_params_list "}"
#line 2955 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4637 "dhcp6_parser.cc"
    break;

  case 845: // output_params_list: output_params_list ","
#line 2961 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4645 "dhcp6_parser.cc"
    break;

  case 851: // $@136: %empty
#line 2973 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4654 "dhcp6_parser.cc"
    break;

  case 852: // output: "output" $@136 ":" "constant string"
#line 2976 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4664 "dhcp6_parser.cc"
    break;

  case 853: // flush: "flush" ":" "boolean"
#line 2982 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4674 "dhcp6_parser.cc"
    break;

  case 854: // maxsize: "maxsize" ":" "integer"
#line 2988 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4684 "dhcp6_parser.cc"
    break;

  case 855: // maxver: "maxver" ":" "integer"
#line 2994 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4694 "dhcp6_parser.cc"
    break;

  case 856: // $@137: %empty
#line 3000 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4703 "dhcp6_parser.cc"
    break;

  case 857: // pattern: "pattern" $@137 ":" "constant string"
#line 3003 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4713 "dhcp6_parser.cc"
    break;

  case 858: // $@138: %empty
#line 3009 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4725 "dhcp6_parser.cc"
    break;

  case 859: // compatibility: "compatibility" $@138 ":" "{" compatibility_params "}"
#line 3015 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4734 "dhcp6_parser.cc"
    break;

  case 862: // compatibility_params: compatibility_params ","
#line 3022 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4742 "dhcp6_parser.cc"
    break;

  case 865: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3031 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4752 "dhcp6_parser.cc"
    break;


#line 4756 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -997;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     526,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,    43,    35,    79,    98,   116,
     136,   146,   166,   167,   219,   236,   237,   239,   278,   288,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,    35,  -147,
     154,   129,    63,   562,   352,   287,   290,   142,   198,    20,
     -87,   696,    40,  -997,   282,   294,   299,   283,   303,  -997,
      49,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   305,   313,
     349,   366,   369,   390,   391,   396,   398,   399,   401,   403,
     405,   407,  -997,   408,   415,   418,   419,   422,  -997,  -997,
    -997,   424,   429,   430,  -997,  -997,  -997,   435,  -997,  -997,
    -997,  -997,   437,   439,   440,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   441,  -997,  -997,  -997,  -997,  -997,
    -997,   442,   445,   446,  -997,  -997,   447,  -997,    58,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   448,   451,   452,   454,  -997,
     101,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   455,   456,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   105,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   158,
    -997,  -997,  -997,  -997,  -997,   457,  -997,   458,   459,  -997,
    -997,  -997,  -997,  -997,  -997,   159,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   328,   304,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   462,  -997,  -997,   463,  -997,  -997,  -997,
     467,  -997,  -997,   469,   330,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   474,   476,
    -997,  -997,  -997,  -997,   473,   484,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   202,  -997,
    -997,  -997,   486,  -997,  -997,   488,  -997,   490,   492,  -997,
    -997,   493,   500,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     205,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   501,   209,
    -997,  -997,  -997,  -997,    35,    35,  -997,   254,   503,  -997,
    -997,   504,   513,   514,   517,   519,   520,   275,   317,   318,
     320,   321,   322,   323,   334,   312,   335,   336,   337,   343,
     347,   524,   348,   350,   333,   353,   355,   525,   539,   540,
     356,   359,   363,   561,   563,   571,   367,   577,   578,   579,
     581,   371,   373,   377,   589,   591,   592,   594,   595,   596,
     598,   599,   600,   392,   602,   603,   604,   618,   619,   620,
     410,   420,   421,   634,   635,  -997,   129,  -997,   636,   426,
     427,   431,   432,    63,  -997,   639,   642,   643,   644,   646,
     443,   438,   650,   661,   663,   562,  -997,   664,   352,  -997,
     668,   460,   670,   464,   465,   287,  -997,   671,   672,   676,
     677,   678,   681,   682,  -997,   290,  -997,   683,   689,   481,
     691,   693,   694,   489,  -997,   198,   701,   491,   494,  -997,
      20,   703,   704,   -65,  -997,   495,   707,   709,   502,   710,
     505,   506,   712,   713,   507,   523,   716,   717,   735,   736,
     696,  -997,   737,   529,    40,  -997,  -997,  -997,   739,   740,
     534,   741,   742,   743,   744,   747,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     541,  -997,  -997,  -997,  -997,  -997,   -50,   542,   543,  -997,
    -997,  -997,   770,   771,   772,  -997,   783,   786,   582,   326,
    -997,  -997,  -997,   790,   791,   792,   793,   794,   796,   797,
     798,   799,  -997,   800,   801,   804,   807,   586,   605,  -997,
    -997,  -997,   813,   812,  -997,   815,  -997,  -997,  -997,  -997,
    -997,   819,   820,   614,   615,   616,  -997,  -997,   815,   617,
     823,  -997,   621,  -997,   622,  -997,   624,  -997,  -997,  -997,
     815,   815,   815,   625,   626,   627,   628,  -997,   629,   630,
    -997,   632,   633,   637,  -997,  -997,   638,  -997,  -997,  -997,
     640,   786,  -997,  -997,   641,   645,  -997,   659,  -997,  -997,
     -64,   655,  -997,  -997,   -50,   660,   662,   665,  -997,   841,
    -997,  -997,    35,   129,  -997,    40,    63,   314,   314,   840,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   844,
     847,   848,   849,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   -86,    35,     8,   144,   866,   868,   869,   117,    23,
      -5,    -1,    61,   696,  -997,  -997,   873,  -156,  -997,  -997,
     874,   875,  -997,  -997,  -997,  -997,  -997,   -72,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,   840,  -997,   215,
     225,   226,  -997,  -997,  -997,  -997,   879,   880,   881,   882,
     883,   884,   885,  -997,   886,  -997,  -997,  -997,  -997,  -997,
     258,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     281,  -997,   842,   888,  -997,  -997,   887,   889,  -997,  -997,
     892,   891,  -997,  -997,   893,   897,  -997,  -997,   895,   899,
    -997,  -997,  -997,    71,  -997,  -997,  -997,   898,  -997,  -997,
    -997,   157,  -997,  -997,  -997,  -997,  -997,   284,  -997,  -997,
    -997,  -997,   169,  -997,  -997,   900,   902,  -997,  -997,   901,
     906,  -997,   907,   908,   909,   910,   911,   912,   302,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   913,   914,
     915,  -997,  -997,  -997,  -997,   315,  -997,  -997,  -997,  -997,
    -997,  -997,   916,   917,   918,  -997,   316,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   329,  -997,
    -997,  -997,   919,  -997,   920,  -997,  -997,  -997,   331,  -997,
    -997,  -997,  -997,  -997,   332,  -997,   203,  -997,   921,  -997,
     358,  -997,  -997,   698,  -997,   922,   924,  -997,  -997,   923,
     927,  -997,  -997,  -997,   795,  -997,   925,  -997,  -997,  -997,
     928,   929,   930,   931,   690,   680,   723,   722,   725,   726,
     727,   937,   730,   940,   942,   943,   945,   314,  -997,  -997,
     314,  -997,   840,   562,  -997,   844,   198,  -997,   847,    20,
    -997,   848,   714,  -997,   849,   -86,  -997,  -997,     8,  -997,
     946,   948,   144,  -997,   279,   866,  -997,   290,  -997,   868,
     -87,  -997,   869,   745,   748,   755,   759,   769,   773,   117,
    -997,   950,   951,   774,   784,   789,    23,  -997,   768,   805,
     809,    -5,  -997,   980,  1000,    -1,  -997,   802,  1002,   811,
    1021,    61,  -997,  -997,   325,   873,  -997,   824,  -156,  -997,
    -997,  1024,  1032,   352,  -997,   874,   287,  -997,   875,  1041,
    -997,  -997,   242,   853,   862,   878,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   397,  -997,   890,   894,   896,   903,  -997,
     360,  -997,   361,  -997,  1084,  -997,  1087,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   364,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   904,   905,  -997,  -997,  -997,  1093,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    1091,  1097,  -997,  -997,  -997,  -997,  -997,  -997,  1095,  -997,
     368,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   178,
     926,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   932,
     933,  -997,  -997,   934,  -997,    35,  -997,  -997,  1101,  -997,
    -997,  -997,  -997,  -997,   381,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   935,   384,  -997,   385,  -997,   936,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   714,  -997,
    -997,  -997,  1103,  1105,   938,  -997,   279,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  1106,   939,
    1107,   325,  -997,  -997,  -997,  -997,  -997,  -997,   944,   947,
    -997,  -997,  1108,  -997,   949,  -997,  -997,  -997,  1111,  -997,
    -997,   224,  -997,   107,  1111,  -997,  -997,  1110,  1115,  1116,
    -997,   388,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  1117,
     952,   941,   953,  1118,   107,  -997,   956,  -997,  -997,  -997,
     957,  -997,  -997,  -997
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   184,     9,   365,    11,
     568,    13,   595,    15,   627,    17,   488,    19,   497,    21,
     536,    23,   327,    25,   755,    27,   806,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   629,     0,   499,   538,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   137,   804,   182,   203,   205,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   156,   163,
     165,     0,     0,     0,   356,   486,   527,     0,   434,   582,
     584,   426,     0,     0,     0,   283,   302,   292,   272,   665,
     618,   318,   339,   697,     0,   304,   722,   736,   753,   169,
     171,     0,     0,     0,   816,   858,     0,   136,     0,    69,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   117,   118,   127,   128,   129,   106,   135,
     131,   132,   133,    84,    85,    86,    87,   103,    88,    90,
      89,   130,    94,    95,    82,   108,   109,   110,   107,    83,
      92,    93,   101,   102,   104,    91,    96,    97,    98,    99,
     100,   105,   116,   134,   197,     0,     0,     0,     0,   196,
       0,   186,   189,   190,   191,   192,   193,   194,   195,   559,
     586,   413,   415,   417,     0,     0,   421,   419,   659,   412,
     370,   371,   372,   373,   374,   375,   376,   377,   396,   397,
     398,   399,   400,   403,   404,   405,   406,   407,   408,   409,
     410,   401,   402,   411,     0,   367,   381,   382,   383,   386,
     387,   390,   391,   392,   389,   384,   385,   378,   379,   394,
     395,   380,   388,   393,   580,   579,   575,   576,   574,     0,
     570,   573,   577,   578,   611,     0,   614,     0,     0,   610,
     604,   605,   603,   608,   609,     0,   597,   600,   601,   606,
     607,   602,   657,   645,   647,   649,   651,   653,   655,   644,
     641,   642,   643,     0,   630,   631,   636,   637,   634,   638,
     639,   640,   635,     0,   517,   250,     0,   521,   519,   524,
       0,   513,   514,     0,   500,   501,   504,   516,   505,   506,
     507,   523,   508,   509,   510,   511,   512,   553,     0,     0,
     551,   552,   555,   556,     0,   539,   540,   543,   544,   545,
     546,   547,   548,   549,   550,   335,   337,   332,     0,   329,
     333,   334,     0,   779,   781,     0,   784,     0,     0,   788,
     792,     0,     0,   796,   798,   800,   802,   777,   775,   776,
       0,   757,   760,   772,   761,   762,   763,   764,   765,   766,
     767,   768,   769,   770,   771,   773,   774,   813,     0,     0,
     808,   811,   812,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   188,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   369,   366,     0,   572,   569,
       0,     0,     0,     0,     0,   599,   596,     0,     0,     0,
       0,     0,     0,     0,   628,   633,   489,     0,     0,     0,
       0,     0,     0,     0,   498,   503,     0,     0,     0,   537,
     542,     0,     0,   331,   328,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   756,     0,     0,   810,   807,    51,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,   174,   175,   153,   154,   155,     0,     0,     0,   167,
     168,   173,     0,     0,     0,   178,     0,     0,     0,     0,
     423,   424,   425,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   721,     0,     0,     0,     0,     0,     0,   179,
     180,   181,     0,     0,    70,     0,   199,   200,   201,   202,
     187,     0,     0,     0,     0,     0,   432,   433,     0,     0,
       0,   368,     0,   571,     0,   613,     0,   616,   617,   598,
       0,     0,     0,     0,     0,     0,     0,   632,     0,     0,
     515,     0,     0,     0,   526,   502,     0,   557,   558,   541,
       0,     0,   330,   778,     0,     0,   783,     0,   786,   787,
       0,     0,   794,   795,     0,     0,     0,     0,   758,     0,
     815,   809,     0,     0,   138,     0,     0,     0,     0,   209,
     177,   158,   159,   160,   161,   162,   157,   164,   166,   358,
     490,   529,   436,    40,   583,   585,   428,   429,   430,   431,
     427,     0,    48,     0,     0,     0,   620,   320,     0,     0,
       0,     0,     0,     0,   170,   172,     0,     0,    53,   198,
     561,   588,   414,   416,   418,   422,   420,     0,   581,   612,
     615,   658,   646,   648,   650,   652,   654,   656,   518,   251,
     522,   520,   525,   554,   336,   338,   780,   782,   785,   790,
     791,   789,   793,   797,   799,   801,   803,   209,    44,     0,
       0,     0,   238,   243,   245,   247,     0,     0,     0,     0,
       0,     0,     0,   257,     0,   264,   266,   268,   270,   237,
       0,   216,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   230,   231,   232,   229,   233,   234,   235,   236,
       0,   214,     0,   210,   211,   363,     0,   359,   360,   495,
       0,   491,   492,   534,     0,   530,   531,   441,     0,   437,
     438,   290,   291,     0,   285,   288,   289,     0,   300,   301,
     297,     0,   294,   298,   299,   279,   281,     0,   274,   277,
     278,   670,     0,   667,   625,     0,   621,   622,   325,     0,
     321,   322,     0,     0,     0,     0,     0,     0,     0,   341,
     344,   345,   346,   347,   348,   349,   711,   717,     0,     0,
       0,   710,   707,   708,   709,     0,   699,   702,   705,   703,
     704,   706,     0,     0,     0,   314,     0,   306,   309,   310,
     311,   312,   313,   732,   734,   731,   729,   730,     0,   724,
     727,   728,     0,   748,     0,   751,   744,   745,     0,   738,
     741,   742,   743,   746,     0,   821,     0,   818,     0,   864,
       0,   860,   863,    55,   566,     0,   562,   563,   593,     0,
     589,   590,   663,   662,     0,   661,     0,    64,   805,   183,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   218,   204,   206,
       0,   208,   213,     0,   357,   362,   499,   487,   494,   538,
     528,   533,     0,   435,   440,   287,   284,   303,   296,   293,
       0,     0,   276,   273,   672,   669,   666,   629,   619,   624,
       0,   319,   324,     0,     0,     0,     0,     0,     0,   343,
     340,     0,     0,     0,     0,     0,   701,   698,     0,     0,
       0,   308,   305,     0,     0,   726,   723,     0,     0,     0,
       0,   740,   737,   754,     0,   820,   817,     0,   862,   859,
      57,     0,    56,     0,   560,   565,     0,   587,   592,     0,
     660,   814,     0,     0,     0,     0,   249,   252,   253,   254,
     255,   263,   256,     0,   262,     0,     0,     0,     0,   217,
       0,   212,     0,   361,     0,   493,     0,   532,   485,   460,
     461,   462,   464,   465,   466,   450,   451,   469,   470,   471,
     472,   473,   476,   477,   478,   479,   480,   481,   482,   483,
     474,   475,   484,   446,   447,   448,   449,   458,   459,   455,
     456,   457,   454,   463,     0,   443,   452,   467,   468,   453,
     439,   286,   295,     0,     0,   275,   692,   694,     0,   690,
     684,   685,   686,   687,   688,   689,   691,   681,   682,   683,
       0,   673,   674,   677,   678,   679,   680,   668,     0,   623,
       0,   323,   350,   351,   352,   353,   354,   355,   342,     0,
       0,   716,   719,   720,   700,   315,   316,   317,   307,     0,
       0,   725,   747,     0,   750,     0,   739,   836,     0,   834,
     832,   826,   830,   831,     0,   823,   828,   829,   827,   819,
     865,   861,    54,    59,     0,   564,     0,   591,     0,   240,
     241,   242,   239,   244,   246,   248,   259,   260,   261,   258,
     265,   267,   269,   271,   215,   364,   496,   535,   445,   442,
     280,   282,     0,     0,     0,   671,   676,   626,   326,   713,
     714,   715,   712,   718,   733,   735,   749,   752,     0,     0,
       0,   825,   822,    58,   567,   594,   664,   444,     0,     0,
     696,   675,     0,   833,     0,   824,   693,   695,     0,   835,
     841,     0,   838,     0,   840,   837,   851,     0,     0,     0,
     856,     0,   843,   846,   847,   848,   849,   850,   839,     0,
       0,     0,     0,     0,   845,   842,     0,   853,   854,   855,
       0,   844,   852,   857
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   -10,  -997,  -579,  -997,
     103,  -997,  -997,  -997,  -997,   372,  -997,  -618,  -997,  -997,
    -997,   -71,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   389,
     623,  -997,  -997,   -46,   -43,   -14,   -13,    14,    15,   -49,
     -24,    16,    29,    30,    33,    34,  -997,    37,    41,    44,
      47,  -997,   409,    48,  -997,    51,  -997,    54,    59,    62,
    -997,    64,  -997,    65,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   400,   612,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     324,  -997,   115,  -997,  -706,   121,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   -41,  -997,  -748,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   100,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,   108,  -730,  -997,
    -997,  -997,  -997,   102,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,    73,  -997,  -997,  -997,  -997,  -997,  -997,  -997,    93,
    -997,  -997,  -997,    96,   574,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,    90,  -997,  -997,  -997,  -997,  -997,  -997,  -996,
    -997,  -997,  -997,   125,  -997,  -997,  -997,   128,   647,  -997,
    -997,  -994,  -997,  -993,  -997,    10,  -997,    18,  -997,    66,
      69,    72,    76,  -997,  -997,  -997,  -987,  -997,  -997,  -997,
    -997,   118,  -997,  -997,  -115,  1072,  -997,  -997,  -997,  -997,
    -997,   132,  -997,  -997,  -997,   135,  -997,   607,  -997,   -62,
    -997,  -997,  -997,  -997,  -997,   -54,  -997,  -997,  -997,  -997,
    -997,   -42,  -997,  -997,  -997,   134,  -997,  -997,  -997,   138,
    -997,   610,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,    75,  -997,  -997,  -997,    80,   648,  -997,
    -997,   -60,  -997,    -3,  -997,  -997,  -997,  -997,  -997,    70,
    -997,  -997,  -997,    78,   649,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   -53,  -997,  -997,  -997,   126,  -997,  -997,  -997,
     137,  -997,   651,   394,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -986,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   140,  -997,  -997,  -997,   -93,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   122,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   112,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     109,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   416,   601,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   461,   606,  -997,  -997,  -997,  -997,  -997,  -997,
     110,  -997,  -997,   -99,  -997,  -997,  -997,  -997,  -997,  -997,
    -121,  -997,  -997,  -136,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   111,  -997
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     744,    87,    88,    41,    68,    84,    85,   769,   973,  1081,
    1082,   829,    43,    70,    90,   438,    91,    45,    71,   158,
     159,   160,   441,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   467,   736,   179,   468,   180,   469,   181,   182,   183,
     498,   184,   499,   185,   186,   187,   188,   461,   189,   190,
     191,   192,   193,   443,    47,    72,   230,   231,   232,   508,
     233,   234,   235,   236,   194,   444,   195,   445,   196,   446,
     852,   853,   854,  1010,   830,   831,   832,   990,  1242,   833,
     991,   834,   992,   835,   993,   836,   837,   548,   838,   839,
     840,   841,   842,   843,  1001,  1249,   844,   845,   846,  1003,
     847,  1004,   848,  1005,   849,  1006,   197,   487,   887,   888,
     889,  1030,   890,  1031,   198,   484,   873,   874,   875,   876,
     199,   486,   881,   882,   883,   884,   200,   485,   201,   494,
     936,   937,   938,   939,   940,   202,   490,   899,   900,   901,
    1040,    63,    80,   388,   389,   390,   561,   391,   562,   203,
     491,   908,   909,   910,   911,   912,   913,   914,   915,   204,
     473,   856,   857,   858,  1013,    49,    73,   274,   275,   276,
     517,   277,   518,   278,   519,   279,   523,   280,   522,   205,
     206,   207,   208,   480,   750,   285,   286,   209,   477,   868,
     869,   870,  1022,  1154,  1155,   210,   474,    57,    77,   860,
     861,   862,  1016,    59,    78,   353,   354,   355,   356,   357,
     358,   359,   547,   360,   551,   361,   550,   362,   363,   552,
     364,   211,   475,   864,   865,   866,  1019,    61,    79,   374,
     375,   376,   377,   378,   556,   379,   380,   381,   382,   288,
     515,   975,   976,   977,  1083,    51,    74,   299,   300,   301,
     527,   212,   478,   213,   479,   291,   516,   979,   980,   981,
    1086,    53,    75,   315,   316,   317,   530,   318,   319,   532,
     320,   321,   214,   489,   895,   896,   897,  1037,    55,    76,
     333,   334,   335,   336,   538,   337,   539,   338,   540,   339,
     541,   340,   542,   341,   543,   342,   537,   293,   524,   984,
     985,  1089,   215,   488,   892,   893,  1034,  1180,  1181,  1182,
    1183,  1184,  1262,  1185,  1263,  1186,   216,   492,   925,   926,
     927,  1051,  1272,   928,   929,  1052,   930,   931,   217,   218,
     495,   948,   949,   950,  1063,   951,  1064,   219,   496,   958,
     959,   960,   961,  1068,   962,   963,  1070,   220,   497,    65,
      81,   410,   411,   412,   413,   566,   414,   567,   415,   416,
     569,   417,   418,   419,   572,   801,   420,   573,   421,   422,
     423,   576,   424,   577,   425,   578,   426,   579,   221,   442,
      67,    82,   429,   430,   431,   582,   432,   222,   503,   966,
     967,  1074,  1224,  1225,  1226,  1227,  1280,  1228,  1278,  1301,
    1302,  1303,  1311,  1312,  1313,  1319,  1314,  1315,  1316,  1317,
    1323,   223,   504,   970,   971,   972
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     157,   229,   249,   295,   309,   329,    38,   351,   370,   387,
     407,   922,   237,   289,   302,   313,   331,   372,   365,   383,
     292,   408,   850,   880,   256,   373,  1144,   250,  1145,  1146,
     251,   287,   298,   312,   330,  1153,  1159,   352,   371,   871,
      31,   968,    32,    30,    33,   385,   386,   916,   743,   257,
     775,   323,   439,   427,   428,   817,   156,   440,   982,   252,
     253,   506,   781,   782,   783,    86,   507,   385,   386,   238,
     290,   303,   314,   332,  1025,   366,   384,  1026,   409,   224,
     225,   226,   227,   228,   296,   310,    42,   254,   255,   258,
     129,   130,   297,   311,   129,   130,   345,   367,   346,   347,
     368,   369,   259,   260,   513,    44,   261,   262,   525,   514,
     263,   799,   800,   526,   264,   129,   130,   265,   129,   130,
     266,   267,   743,    46,   268,   156,   872,   269,   731,   732,
     733,   734,   270,   871,   878,   271,   879,   272,   273,   281,
      92,    93,   282,    48,    94,   283,   932,   933,   934,   284,
      95,    96,    97,    50,   943,   944,   129,   130,   129,   130,
    1028,   528,   535,  1029,    89,   735,   529,   536,   917,   918,
     919,   920,  1035,    52,    54,  1036,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   563,  1075,   156,   580,  1076,
     564,   156,   584,   581,   127,   128,   125,   585,   506,   952,
     953,   954,   344,   987,   129,   130,    56,  1304,   584,   513,
    1305,   131,   156,   988,   989,   156,   132,   133,   134,   135,
     136,   137,   138,    58,    60,   139,    62,    34,    35,    36,
      37,   140,   902,   903,   904,   905,   906,   907,   885,   886,
     141,  1007,  1144,   142,  1145,  1146,  1008,  1239,  1240,  1241,
     143,  1153,  1159,   955,   345,   156,   346,   347,   144,   145,
     348,   349,   350,   146,  1007,    64,   147,  1032,   433,  1009,
     148,   436,  1033,   129,   130,    66,  1306,   434,   880,  1307,
    1308,  1309,  1310,   435,  1110,  1049,   437,   545,   922,   447,
    1050,   149,   150,   151,   152,   153,   154,   448,  1056,  1061,
    1269,  1270,  1271,  1057,  1062,   155,    98,    99,   100,   101,
     102,   103,  1065,   555,  1071,   580,   544,  1066,   812,  1072,
    1073,   156,   813,   814,   815,   816,   817,   818,   819,   820,
     821,   822,   823,   449,   126,   345,   824,   825,   826,   827,
     828,  1078,   126,  1007,   525,   126,  1079,  1258,  1254,  1255,
     450,   563,  1259,   451,   129,   130,  1268,   304,   305,   306,
     307,   308,   129,   130,  1281,   129,   130,   528,   535,  1282,
     345,  1324,  1284,  1285,   452,   453,  1325,  1166,  1167,  1168,
     454,   345,   455,   456,   246,   457,   322,   458,   247,   459,
     156,   460,   462,   323,   324,   325,   326,   327,   328,   463,
     129,   130,   464,   465,   586,   587,   466,   126,   470,   746,
     747,   748,   749,   471,   472,   157,  1246,  1247,  1248,   476,
     294,   481,   229,   482,   483,   493,   500,   129,   130,   501,
     502,   505,   509,   237,   249,   510,   511,   295,   512,   520,
     521,   531,   533,   534,   309,   289,   588,   549,   302,   246,
     546,   553,   292,   247,   329,   313,   256,   554,   557,   250,
     558,   559,   251,   287,   351,   331,   298,   560,   596,   370,
     565,   156,   568,   312,   570,   365,   571,   574,   372,   156,
     383,   257,   156,   330,   575,   583,   373,   589,   590,   407,
     238,   252,   253,  1217,   352,  1218,  1219,   591,   592,   371,
     408,   593,   290,   594,   595,   303,   156,   604,   610,   616,
     597,   598,   314,   599,   600,   601,   602,   156,   296,   254,
     255,   258,   332,   617,   618,   310,   297,   603,   613,   605,
     606,   607,   366,   311,   259,   260,   608,   384,   261,   262,
     609,   611,   263,   612,   156,   622,   264,   623,   614,   265,
     615,   619,   266,   267,   620,   624,   268,   409,   621,   269,
     625,   626,   627,   628,   270,   629,   630,   271,   631,   272,
     273,   281,   632,   633,   282,   634,   635,   283,   636,   637,
     638,   284,   639,   640,   641,   642,   643,   644,   645,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   646,   647,   648,   649,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   650,   651,   126,   652,   653,
     655,   656,   657,   661,   658,   659,   662,   663,   664,   239,
     665,   240,   157,   667,   668,   229,   666,   129,   130,   241,
     242,   243,   244,   245,   131,   669,   237,   670,   672,   132,
     133,   134,   674,   675,   676,   680,   681,   677,   678,   246,
     682,   683,   684,   247,   140,   685,   686,   688,   921,   935,
     945,   248,   407,   689,   690,   691,   969,   692,   693,   923,
     941,   946,   956,   408,   694,   696,   697,   700,   701,   698,
     703,   704,   808,   705,   707,   706,   710,   711,   708,   709,
     714,   715,   712,   238,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   713,   716,
     717,   719,   720,   722,   149,   150,   724,   723,   725,   726,
     727,   728,   729,   730,   737,   738,   924,   942,   947,   957,
     409,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   156,   739,   740,   741,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   742,   126,
     345,   129,   130,    32,   745,   751,   752,   753,   764,   755,
     754,   756,   757,  1090,   795,   758,   759,   760,   761,   129,
     130,   762,   242,   243,   763,   245,   131,   765,   766,   767,
     768,   132,   133,   134,   770,   771,   772,   773,   774,   776,
     777,   246,   802,   778,   779,   247,   780,   784,   785,   786,
     787,   788,   789,   248,   790,   791,   807,   851,  1011,   792,
     793,   855,   794,   796,   859,   863,   867,   797,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   798,   804,   891,   805,   894,   898,   806,   405,   406,
     965,   974,   978,   994,   995,   996,   997,   998,   999,  1000,
    1002,  1012,  1015,  1014,  1018,  1097,   149,   150,  1017,  1020,
    1021,  1023,  1024,  1096,  1027,  1039,  1038,  1041,   156,  1042,
    1080,  1043,  1044,  1045,  1046,  1047,  1048,  1053,  1054,  1055,
    1058,  1059,  1060,  1067,  1069,  1077,   156,  1085,  1084,  1087,
    1088,  1091,  1092,  1093,  1094,  1095,  1098,  1099,  1100,  1101,
    1102,  1103,   249,  1104,  1105,   351,  1106,  1107,   370,  1108,
    1163,  1118,  1164,   289,  1199,  1200,   365,   372,  1192,   383,
     292,  1193,  1157,  1169,   256,   373,   329,   250,  1194,   387,
     251,   287,  1195,  1125,  1178,   352,  1119,   331,   371,  1120,
    1156,  1143,  1196,  1205,  1209,   921,  1197,  1201,  1170,   257,
     935,  1171,  1177,  1176,   945,   330,   923,  1202,  1126,   252,
     253,   941,  1203,  1220,  1210,   946,  1213,   969,  1121,  1122,
     290,   956,   295,   366,  1222,   309,   384,  1212,  1206,  1158,
    1172,  1173,  1207,   302,  1214,  1215,   313,   254,   255,   258,
    1232,  1179,  1147,  1221,   332,  1233,  1123,  1124,  1127,  1230,
    1148,   298,   259,   260,   312,  1238,   261,   262,  1174,  1175,
     263,  1128,  1129,   924,   264,  1130,  1131,   265,   942,  1132,
     266,   267,   947,  1133,   268,  1243,  1134,   269,   957,  1135,
    1136,  1223,   270,  1137,  1244,   271,  1138,   272,   273,   281,
     303,  1139,   282,   314,  1140,   283,  1141,  1142,  1149,   284,
    1245,  1150,  1256,   296,  1151,  1257,   310,  1264,  1152,  1265,
    1266,   297,  1250,  1267,   311,  1279,  1251,  1288,  1252,  1289,
    1292,  1294,   809,  1298,  1320,  1253,  1260,  1261,  1300,  1321,
    1322,  1326,  1330,   803,   877,   660,   811,  1111,  1109,   654,
    1162,   986,  1165,  1161,  1208,  1191,  1190,   702,  1273,  1198,
    1113,  1112,  1160,  1287,  1274,  1275,  1276,  1283,  1286,   343,
    1115,  1114,  1293,  1290,  1328,  1117,  1296,  1116,  1237,  1297,
    1235,  1299,   695,  1234,  1236,  1189,  1329,  1327,  1332,  1333,
     699,   983,   671,  1291,  1188,  1187,   673,  1211,  1204,   964,
    1216,   718,  1295,  1318,   679,  1229,   810,  1118,  1331,  1231,
     721,     0,     0,     0,     0,  1169,   687,     0,  1157,     0,
       0,     0,     0,     0,     0,  1277,  1178,     0,     0,  1125,
    1220,     0,  1119,     0,     0,  1120,  1156,  1143,     0,     0,
    1170,  1222,     0,  1171,  1177,  1176,     0,     0,     0,     0,
       0,     0,     0,     0,  1126,     0,     0,     0,     0,     0,
    1221,     0,     0,     0,  1121,  1122,     0,     0,     0,     0,
       0,     0,  1172,  1173,     0,  1158,     0,     0,     0,     0,
       0,     0,     0,  1179,     0,     0,     0,     0,  1147,     0,
       0,     0,  1123,  1124,  1127,     0,  1148,     0,  1223,     0,
    1174,  1175,     0,     0,     0,     0,     0,  1128,  1129,     0,
       0,  1130,  1131,     0,     0,  1132,     0,     0,     0,  1133,
       0,     0,  1134,     0,     0,  1135,  1136,     0,     0,  1137,
       0,     0,  1138,     0,     0,     0,     0,  1139,     0,     0,
    1140,     0,  1141,  1142,  1149,     0,     0,  1150,     0,     0,
    1151,     0,     0,     0,  1152
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   759,    72,    73,    74,    75,    76,    79,    78,    79,
      73,    81,   728,   753,    73,    79,  1022,    73,  1022,  1022,
      73,    73,    74,    75,    76,  1022,  1022,    78,    79,   125,
       5,   197,     7,     0,     9,   132,   133,    24,   627,    73,
     668,   123,     3,    13,    14,    32,   212,     8,   130,    73,
      73,     3,   680,   681,   682,   212,     8,   132,   133,    72,
      73,    74,    75,    76,     3,    78,    79,     6,    81,    16,
      17,    18,    19,    20,    74,    75,     7,    73,    73,    73,
      95,    96,    74,    75,    95,    96,    76,    77,    78,    79,
      80,    81,    73,    73,     3,     7,    73,    73,     3,     8,
      73,   175,   176,     8,    73,    95,    96,    73,    95,    96,
      73,    73,   701,     7,    73,   212,   212,    73,   178,   179,
     180,   181,    73,   125,   126,    73,   128,    73,    73,    73,
      11,    12,    73,     7,    15,    73,   151,   152,   153,    73,
      21,    22,    23,     7,   155,   156,    95,    96,    95,    96,
       3,     3,     3,     6,    10,   215,     8,     8,   145,   146,
     147,   148,     3,     7,     7,     6,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,     3,     3,   212,     3,     6,
       8,   212,     3,     8,    85,    86,    74,     8,     3,   158,
     159,   160,    24,     8,    95,    96,     7,     3,     3,     3,
       6,   102,   212,     8,     8,   212,   107,   108,   109,   110,
     111,   112,   113,     7,     7,   116,     7,   212,   213,   214,
     215,   122,   135,   136,   137,   138,   139,   140,   114,   115,
     131,     3,  1258,   134,  1258,  1258,     8,    25,    26,    27,
     141,  1258,  1258,   212,    76,   212,    78,    79,   149,   150,
      82,    83,    84,   154,     3,     7,   157,     3,     6,     8,
     161,     8,     8,    95,    96,     7,   189,     3,  1028,   192,
     193,   194,   195,     4,  1010,     3,     3,     3,  1056,     4,
       8,   182,   183,   184,   185,   186,   187,     4,     3,     3,
     142,   143,   144,     8,     8,   196,    47,    48,    49,    50,
      51,    52,     3,     3,     3,     3,     8,     8,    24,     8,
       8,   212,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,     4,    75,    76,    42,    43,    44,    45,
      46,     3,    75,     3,     3,    75,     8,     3,     8,     8,
       4,     3,     8,     4,    95,    96,     8,    90,    91,    92,
      93,    94,    95,    96,     3,    95,    96,     3,     3,     8,
      76,     3,     8,     8,     4,     4,     8,   118,   119,   120,
       4,    76,     4,     4,   117,     4,   116,     4,   121,     4,
     212,     4,     4,   123,   124,   125,   126,   127,   128,     4,
      95,    96,     4,     4,   434,   435,     4,    75,     4,   103,
     104,   105,   106,     4,     4,   506,    39,    40,    41,     4,
      88,     4,   513,     4,     4,     4,     4,    95,    96,     4,
       4,     4,     4,   513,   525,     4,     4,   528,     4,     4,
       4,     4,     4,     4,   535,   525,   212,     4,   528,   117,
       8,     4,   525,   121,   545,   535,   525,     8,     4,   525,
       4,     8,   525,   525,   555,   545,   528,     3,   213,   560,
       4,   212,     4,   535,     4,   555,     4,     4,   560,   212,
     560,   525,   212,   545,     4,     4,   560,     4,     4,   580,
     513,   525,   525,   188,   555,   190,   191,     4,     4,   560,
     580,     4,   525,     4,     4,   528,   212,   215,     4,     4,
     213,   213,   535,   213,   213,   213,   213,   212,   528,   525,
     525,   525,   545,     4,     4,   535,   528,   213,   215,   214,
     214,   214,   555,   535,   525,   525,   213,   560,   525,   525,
     213,   213,   525,   213,   212,     4,   525,     4,   215,   525,
     215,   215,   525,   525,   215,     4,   525,   580,   215,   525,
     213,     4,     4,     4,   525,     4,   215,   525,   215,   525,
     525,   525,   215,     4,   525,     4,     4,   525,     4,     4,
       4,   525,     4,     4,     4,   213,     4,     4,     4,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,     4,     4,     4,   215,    64,    65,    66,    67,
      68,    69,    70,    71,    72,   215,   215,    75,     4,     4,
       4,   215,   215,     4,   213,   213,     4,     4,     4,    87,
       4,    89,   723,   215,     4,   726,   213,    95,    96,    97,
      98,    99,   100,   101,   102,     4,   726,     4,     4,   107,
     108,   109,     4,   213,     4,     4,     4,   213,   213,   117,
       4,     4,     4,   121,   122,     4,     4,     4,   759,   760,
     761,   129,   763,     4,   213,     4,   767,     4,     4,   759,
     760,   761,   762,   763,   215,     4,   215,     4,     4,   215,
     215,     4,   722,     4,     4,   213,     4,     4,   213,   213,
       4,     4,   215,   726,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   215,     4,
       4,     4,   213,     4,   182,   183,   212,     7,     7,     7,
       7,     7,     5,   212,   212,   212,   759,   760,   761,   762,
     763,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,   212,     5,     5,     5,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     5,    75,
      76,    95,    96,     7,   212,     5,     5,     5,   212,     5,
       7,     5,     5,     8,   701,     7,     7,     7,     7,    95,
      96,     7,    98,    99,     7,   101,   102,   212,     5,     7,
       5,   107,   108,   109,     5,     5,   212,   212,   212,   212,
       7,   117,   177,   212,   212,   121,   212,   212,   212,   212,
     212,   212,   212,   129,   212,   212,     5,     7,     6,   212,
     212,     7,   212,   212,     7,     7,     7,   212,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   212,   212,     7,   212,     7,     7,   212,   182,   183,
       7,     7,     7,     4,     4,     4,     4,     4,     4,     4,
       4,     3,     3,     6,     3,   215,   182,   183,     6,     6,
       3,     6,     3,   213,     6,     3,     6,     6,   212,     3,
     212,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   212,     3,     6,     6,
       3,     6,     4,     4,     4,     4,   213,   215,   213,   213,
     213,     4,  1013,   213,     4,  1016,     4,     4,  1019,     4,
       4,  1022,     4,  1013,     4,     4,  1016,  1019,   213,  1019,
    1013,   213,  1022,  1034,  1013,  1019,  1037,  1013,   213,  1040,
    1013,  1013,   213,  1022,  1034,  1016,  1022,  1037,  1019,  1022,
    1022,  1022,   213,   215,     4,  1056,   213,   213,  1034,  1013,
    1061,  1034,  1034,  1034,  1065,  1037,  1056,   213,  1022,  1013,
    1013,  1061,   213,  1074,     4,  1065,     4,  1078,  1022,  1022,
    1013,  1071,  1083,  1016,  1074,  1086,  1019,   215,   213,  1022,
    1034,  1034,   213,  1083,   213,     4,  1086,  1013,  1013,  1013,
       6,  1034,  1022,  1074,  1037,     3,  1022,  1022,  1022,   215,
    1022,  1083,  1013,  1013,  1086,     4,  1013,  1013,  1034,  1034,
    1013,  1022,  1022,  1056,  1013,  1022,  1022,  1013,  1061,  1022,
    1013,  1013,  1065,  1022,  1013,   212,  1022,  1013,  1071,  1022,
    1022,  1074,  1013,  1022,   212,  1013,  1022,  1013,  1013,  1013,
    1083,  1022,  1013,  1086,  1022,  1013,  1022,  1022,  1022,  1013,
     212,  1022,     8,  1083,  1022,     8,  1086,     4,  1022,     8,
       3,  1083,   212,     8,  1086,     4,   212,     4,   212,     4,
       4,     4,   723,     5,     4,   212,   212,   212,     7,     4,
       4,     4,     4,   714,   752,   513,   726,  1012,  1007,   506,
    1028,   807,  1032,  1025,  1061,  1042,  1040,   563,   212,  1049,
    1015,  1013,  1024,  1258,   212,   212,   212,   212,   212,    77,
    1018,  1016,   213,   215,   213,  1021,   212,  1019,  1088,   212,
    1085,   212,   555,  1083,  1086,  1039,   213,   215,   212,   212,
     560,   777,   525,  1266,  1037,  1035,   528,  1065,  1056,   763,
    1071,   580,  1281,  1304,   535,  1075,   725,  1258,  1324,  1078,
     584,    -1,    -1,    -1,    -1,  1266,   545,    -1,  1258,    -1,
      -1,    -1,    -1,    -1,    -1,  1215,  1266,    -1,    -1,  1258,
    1281,    -1,  1258,    -1,    -1,  1258,  1258,  1258,    -1,    -1,
    1266,  1281,    -1,  1266,  1266,  1266,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1258,    -1,    -1,    -1,    -1,    -1,
    1281,    -1,    -1,    -1,  1258,  1258,    -1,    -1,    -1,    -1,
      -1,    -1,  1266,  1266,    -1,  1258,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1266,    -1,    -1,    -1,    -1,  1258,    -1,
      -1,    -1,  1258,  1258,  1258,    -1,  1258,    -1,  1281,    -1,
    1266,  1266,    -1,    -1,    -1,    -1,    -1,  1258,  1258,    -1,
      -1,  1258,  1258,    -1,    -1,  1258,    -1,    -1,    -1,  1258,
      -1,    -1,  1258,    -1,    -1,  1258,  1258,    -1,    -1,  1258,
      -1,    -1,  1258,    -1,    -1,    -1,    -1,  1258,    -1,    -1,
    1258,    -1,  1258,  1258,  1258,    -1,    -1,  1258,    -1,    -1,
    1258,    -1,    -1,    -1,  1258
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
       0,     5,     7,     9,   212,   213,   214,   215,   232,   233,
     234,   239,     7,   248,     7,   253,     7,   300,     7,   411,
       7,   491,     7,   507,     7,   524,     7,   443,     7,   449,
       7,   473,     7,   387,     7,   595,     7,   626,   240,   235,
     249,   254,   301,   412,   492,   508,   525,   444,   450,   474,
     388,   596,   627,   232,   241,   242,   212,   237,   238,    10,
     250,   252,    11,    12,    15,    21,    22,    23,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    85,    86,    95,
      96,   102,   107,   108,   109,   110,   111,   112,   113,   116,
     122,   131,   134,   141,   149,   150,   154,   157,   161,   182,
     183,   184,   185,   186,   187,   196,   212,   247,   255,   256,
     257,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   279,
     281,   283,   284,   285,   287,   289,   290,   291,   292,   294,
     295,   296,   297,   298,   310,   312,   314,   352,   360,   366,
     372,   374,   381,   395,   405,   425,   426,   427,   428,   433,
     441,   467,   497,   499,   518,   548,   562,   574,   575,   583,
     593,   624,   633,   657,    16,    17,    18,    19,    20,   247,
     302,   303,   304,   306,   307,   308,   309,   497,   499,    87,
      89,    97,    98,    99,   100,   101,   117,   121,   129,   247,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   273,   274,   275,   276,   279,   281,   283,
     284,   285,   287,   289,   413,   414,   415,   417,   419,   421,
     423,   425,   426,   427,   428,   431,   432,   467,   485,   497,
     499,   501,   518,   543,    88,   247,   421,   423,   467,   493,
     494,   495,   497,   499,    90,    91,    92,    93,    94,   247,
     421,   423,   467,   497,   499,   509,   510,   511,   513,   514,
     516,   517,   116,   123,   124,   125,   126,   127,   128,   247,
     467,   497,   499,   526,   527,   528,   529,   531,   533,   535,
     537,   539,   541,   441,    24,    76,    78,    79,    82,    83,
      84,   247,   332,   451,   452,   453,   454,   455,   456,   457,
     459,   461,   463,   464,   466,   497,   499,    77,    80,    81,
     247,   332,   455,   461,   475,   476,   477,   478,   479,   481,
     482,   483,   484,   497,   499,   132,   133,   247,   389,   390,
     391,   393,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   182,   183,   247,   497,   499,
     597,   598,   599,   600,   602,   604,   605,   607,   608,   609,
     612,   614,   615,   616,   618,   620,   622,    13,    14,   628,
     629,   630,   632,     6,     3,     4,     8,     3,   251,     3,
       8,   258,   625,   299,   311,   313,   315,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   293,     4,     4,     4,     4,     4,   277,   280,   282,
       4,     4,     4,   406,   442,   468,     4,   434,   498,   500,
     429,     4,     4,     4,   361,   373,   367,   353,   549,   519,
     382,   396,   563,     4,   375,   576,   584,   594,   286,   288,
       4,     4,     4,   634,   658,     4,     3,     8,   305,     4,
       4,     4,     4,     3,     8,   486,   502,   416,   418,   420,
       4,     4,   424,   422,   544,     3,     8,   496,     3,     8,
     512,     4,   515,     4,     4,     3,     8,   542,   530,   532,
     534,   536,   538,   540,     8,     3,     8,   458,   333,     4,
     462,   460,   465,     4,     8,     3,   480,     4,     4,     8,
       3,   392,   394,     3,     8,     4,   601,   603,     4,   606,
       4,     4,   610,   613,     4,     4,   617,   619,   621,   623,
       3,     8,   631,     4,     3,     8,   232,   232,   212,     4,
       4,     4,     4,     4,     4,     4,   213,   213,   213,   213,
     213,   213,   213,   213,   215,   214,   214,   214,   213,   213,
       4,   213,   213,   215,   215,   215,     4,     4,     4,   215,
     215,   215,     4,     4,     4,   213,     4,     4,     4,     4,
     215,   215,   215,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   213,     4,     4,     4,     4,     4,     4,   215,
     215,   215,     4,     4,   256,     4,   215,   215,   213,   213,
     303,     4,     4,     4,     4,     4,   213,   215,     4,     4,
       4,   414,     4,   494,     4,   213,     4,   213,   213,   510,
       4,     4,     4,     4,     4,     4,     4,   528,     4,     4,
     213,     4,     4,     4,   215,   453,     4,   215,   215,   477,
       4,     4,   390,   215,     4,     4,   213,     4,   213,   213,
       4,     4,   215,   215,     4,     4,     4,     4,   598,     4,
     213,   629,     4,     7,   212,     7,     7,     7,     7,     5,
     212,   178,   179,   180,   181,   215,   278,   212,   212,     5,
       5,     5,     5,   234,   236,   212,   103,   104,   105,   106,
     430,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   212,   212,     5,     7,     5,   243,
       5,     5,   212,   212,   212,   243,   212,     7,   212,   212,
     212,   243,   243,   243,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   236,   212,   212,   212,   175,
     176,   611,   177,   278,   212,   212,   212,     5,   232,   255,
     628,   302,    24,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    42,    43,    44,    45,    46,   247,
     320,   321,   322,   325,   327,   329,   331,   332,   334,   335,
     336,   337,   338,   339,   342,   343,   344,   346,   348,   350,
     320,     7,   316,   317,   318,     7,   407,   408,   409,     7,
     445,   446,   447,     7,   469,   470,   471,     7,   435,   436,
     437,   125,   212,   362,   363,   364,   365,   241,   126,   128,
     364,   368,   369,   370,   371,   114,   115,   354,   355,   356,
     358,     7,   550,   551,     7,   520,   521,   522,     7,   383,
     384,   385,   135,   136,   137,   138,   139,   140,   397,   398,
     399,   400,   401,   402,   403,   404,    24,   145,   146,   147,
     148,   247,   334,   497,   499,   564,   565,   566,   569,   570,
     572,   573,   151,   152,   153,   247,   376,   377,   378,   379,
     380,   497,   499,   155,   156,   247,   497,   499,   577,   578,
     579,   581,   158,   159,   160,   212,   497,   499,   585,   586,
     587,   588,   590,   591,   597,     7,   635,   636,   197,   247,
     659,   660,   661,   244,     7,   487,   488,   489,     7,   503,
     504,   505,   130,   529,   545,   546,   316,     8,     8,     8,
     323,   326,   328,   330,     4,     4,     4,     4,     4,     4,
       4,   340,     4,   345,   347,   349,   351,     3,     8,     8,
     319,     6,     3,   410,     6,     3,   448,     6,     3,   472,
       6,     3,   438,     6,     3,     3,     6,     6,     3,     6,
     357,   359,     3,     8,   552,     3,     6,   523,     6,     3,
     386,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   567,   571,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   580,   582,     3,     8,     4,   589,     4,
     592,     3,     8,     8,   637,     3,     6,     4,     3,     8,
     212,   245,   246,   490,     6,     3,   506,     6,     3,   547,
       8,     6,     4,     4,     4,     4,   213,   215,   213,   215,
     213,   213,   213,     4,   213,     4,     4,     4,     4,   321,
     320,   318,   413,   409,   451,   447,   475,   471,   247,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   273,   274,   275,   276,   279,   281,   283,   284,
     285,   287,   289,   332,   405,   417,   419,   421,   423,   425,
     426,   427,   428,   432,   439,   440,   467,   497,   499,   543,
     437,   363,   369,     4,     4,   355,   118,   119,   120,   247,
     259,   260,   261,   262,   263,   264,   332,   467,   497,   499,
     553,   554,   555,   556,   557,   559,   561,   551,   526,   522,
     389,   385,   213,   213,   213,   213,   213,   213,   398,     4,
       4,   213,   213,   213,   565,   215,   213,   213,   377,     4,
       4,   578,   215,     4,   213,     4,   586,   188,   190,   191,
     247,   332,   497,   499,   638,   639,   640,   641,   643,   636,
     215,   660,     6,     3,   493,   489,   509,   505,     4,    25,
      26,    27,   324,   212,   212,   212,    39,    40,    41,   341,
     212,   212,   212,   212,     8,     8,     8,     8,     3,     8,
     212,   212,   558,   560,     4,     8,     3,     8,     8,   142,
     143,   144,   568,   212,   212,   212,   212,   232,   644,     4,
     642,     3,     8,   212,     8,     8,   212,   440,     4,     4,
     215,   555,     4,   213,     4,   639,   212,   212,     5,   212,
       7,   645,   646,   647,     3,     6,   189,   192,   193,   194,
     195,   648,   649,   650,   652,   653,   654,   655,   646,   651,
       4,     4,     4,   656,     3,     8,     4,   215,   213,   213,
       4,   649,   212,   212
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   216,   218,   217,   219,   217,   220,   217,   221,   217,
     222,   217,   223,   217,   224,   217,   225,   217,   226,   217,
     227,   217,   228,   217,   229,   217,   230,   217,   231,   217,
     232,   232,   232,   232,   232,   232,   232,   233,   235,   234,
     236,   237,   237,   238,   238,   238,   240,   239,   241,   241,
     242,   242,   242,   244,   243,   245,   245,   246,   246,   246,
     247,   249,   248,   251,   250,   250,   252,   254,   253,   255,
     255,   255,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   258,   257,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   277,   276,   278,   278,
     278,   278,   278,   280,   279,   282,   281,   283,   284,   286,
     285,   288,   287,   289,   290,   291,   293,   292,   294,   295,
     296,   297,   299,   298,   301,   300,   302,   302,   302,   303,
     303,   303,   303,   303,   303,   303,   303,   305,   304,   306,
     307,   308,   309,   311,   310,   313,   312,   315,   314,   316,
     316,   317,   317,   317,   319,   318,   320,   320,   320,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   323,   322,
     324,   324,   324,   326,   325,   328,   327,   330,   329,   331,
     333,   332,   334,   335,   336,   337,   338,   340,   339,   341,
     341,   341,   342,   343,   345,   344,   347,   346,   349,   348,
     351,   350,   353,   352,   354,   354,   354,   355,   355,   357,
     356,   359,   358,   361,   360,   362,   362,   362,   363,   363,
     364,   365,   367,   366,   368,   368,   368,   369,   369,   369,
     370,   371,   373,   372,   375,   374,   376,   376,   376,   377,
     377,   377,   377,   377,   377,   378,   379,   380,   382,   381,
     383,   383,   384,   384,   384,   386,   385,   388,   387,   389,
     389,   389,   389,   390,   390,   392,   391,   394,   393,   396,
     395,   397,   397,   397,   398,   398,   398,   398,   398,   398,
     399,   400,   401,   402,   403,   404,   406,   405,   407,   407,
     408,   408,   408,   410,   409,   412,   411,   413,   413,   413,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   416,   415,   418,   417,   420,   419,   422,
     421,   424,   423,   425,   426,   427,   429,   428,   430,   430,
     430,   430,   431,   432,   434,   433,   435,   435,   436,   436,
     436,   438,   437,   439,   439,   439,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   442,   441,   444,   443,
     445,   445,   446,   446,   446,   448,   447,   450,   449,   451,
     451,   452,   452,   452,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   454,   455,   456,   458,   457,   460,
     459,   462,   461,   463,   465,   464,   466,   468,   467,   469,
     469,   470,   470,   470,   472,   471,   474,   473,   475,   475,
     476,   476,   476,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   478,   480,   479,   481,   482,   483,   484,   486,
     485,   487,   487,   488,   488,   488,   490,   489,   492,   491,
     493,   493,   493,   494,   494,   494,   494,   494,   494,   494,
     496,   495,   498,   497,   500,   499,   502,   501,   503,   503,
     504,   504,   504,   506,   505,   508,   507,   509,   509,   509,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     510,   512,   511,   513,   515,   514,   516,   517,   519,   518,
     520,   520,   521,   521,   521,   523,   522,   525,   524,   526,
     526,   527,   527,   527,   528,   528,   528,   528,   528,   528,
     528,   528,   528,   528,   528,   530,   529,   532,   531,   534,
     533,   536,   535,   538,   537,   540,   539,   542,   541,   544,
     543,   545,   545,   547,   546,   549,   548,   550,   550,   550,
     552,   551,   553,   553,   554,   554,   554,   555,   555,   555,
     555,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     555,   556,   558,   557,   560,   559,   561,   563,   562,   564,
     564,   564,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   567,   566,   568,   568,   568,   569,   571,   570,   572,
     573,   574,   576,   575,   577,   577,   577,   578,   578,   578,
     578,   578,   580,   579,   582,   581,   584,   583,   585,   585,
     585,   586,   586,   586,   586,   586,   586,   587,   589,   588,
     590,   592,   591,   594,   593,   596,   595,   597,   597,   597,
     598,   598,   598,   598,   598,   598,   598,   598,   598,   598,
     598,   598,   598,   598,   598,   598,   598,   598,   599,   601,
     600,   603,   602,   604,   606,   605,   607,   608,   610,   609,
     611,   611,   613,   612,   614,   615,   617,   616,   619,   618,
     621,   620,   623,   622,   625,   624,   627,   626,   628,   628,
     628,   629,   629,   631,   630,   632,   634,   633,   635,   635,
     635,   637,   636,   638,   638,   638,   639,   639,   639,   639,
     639,   639,   639,   640,   642,   641,   644,   643,   645,   645,
     645,   647,   646,   648,   648,   648,   649,   649,   649,   649,
     649,   651,   650,   652,   653,   654,   656,   655,   658,   657,
     659,   659,   659,   660,   660,   661
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
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
  "parked_packet_limit", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@28", "sub_interfaces6", "$@29",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@30", "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@31", "hosts_database", "$@32", "hosts_databases",
  "$@33", "database_list", "not_empty_database_list", "database", "$@34",
  "database_map_params", "database_map_param", "database_type", "$@35",
  "db_type", "user", "$@36", "password", "$@37", "host", "$@38", "port",
  "name", "$@39", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "on_fail", "$@40", "on_fail_mode",
  "max_row_errors", "max_reconnect_tries", "trust_anchor", "$@41",
  "cert_file", "$@42", "key_file", "$@43", "cipher_list", "$@44",
  "sanity_checks", "$@45", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@46", "extended_info_checks", "$@47", "mac_sources",
  "$@48", "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@49",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@50",
  "dhcp_multi_threading", "$@51", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@52", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@53",
  "sub_hooks_library", "$@54", "hooks_params", "hooks_param", "library",
  "$@55", "parameters", "$@56", "expired_leases_processing", "$@57",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@58",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@59",
  "sub_subnet6", "$@60", "subnet6_params", "subnet6_param", "subnet",
  "$@61", "interface", "$@62", "interface_id", "$@63", "client_class",
  "$@64", "require_client_classes", "$@65", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@66", "hr_mode", "id", "rapid_commit", "shared_networks", "$@67",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@68", "shared_network_params", "shared_network_param",
  "option_def_list", "$@69", "sub_option_def_list", "$@70",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@71", "sub_option_def", "$@72",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@73",
  "option_def_record_types", "$@74", "space", "$@75", "option_def_space",
  "option_def_encapsulate", "$@76", "option_def_array", "option_data_list",
  "$@77", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@78", "sub_option_data", "$@79",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@80",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@81", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@82", "sub_pool6", "$@83",
  "pool_params", "pool_param", "pool_entry", "$@84", "user_context",
  "$@85", "comment", "$@86", "pd_pools_list", "$@87",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@88", "sub_pd_pool", "$@89", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@90", "pd_prefix_len", "excluded_prefix", "$@91",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@92",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@93", "sub_reservation", "$@94", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@95", "prefixes", "$@96", "duid", "$@97", "hw_address", "$@98",
  "hostname", "$@99", "flex_id_value", "$@100",
  "reservation_client_classes", "$@101", "relay", "$@102", "relay_map",
  "ip_address", "$@103", "client_classes", "$@104", "client_classes_list",
  "client_class_entry", "$@105", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@106",
  "client_class_template_test", "$@107", "only_if_required", "server_id",
  "$@108", "server_id_params", "server_id_param", "server_id_type",
  "$@109", "duid_type", "htype", "identifier", "$@110", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@111",
  "control_socket_params", "control_socket_param", "socket_type", "$@112",
  "socket_name", "$@113", "dhcp_queue_control", "$@114",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@115", "capacity", "arbitrary_map_entry", "$@116",
  "dhcp_ddns", "$@117", "sub_dhcp_ddns", "$@118", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@119",
  "server_ip", "$@120", "server_port", "sender_ip", "$@121", "sender_port",
  "max_queue_size", "ncr_protocol", "$@122", "ncr_protocol_value",
  "ncr_format", "$@123", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@124",
  "dep_generated_prefix", "$@125", "dep_hostname_char_set", "$@126",
  "dep_hostname_char_replacement", "$@127", "config_control", "$@128",
  "sub_config_control", "$@129", "config_control_params",
  "config_control_param", "config_databases", "$@130",
  "config_fetch_wait_time", "loggers", "$@131", "loggers_entries",
  "logger_entry", "$@132", "logger_params", "logger_param", "debuglevel",
  "severity", "$@133", "output_options_list", "$@134",
  "output_options_list_content", "output_entry", "$@135",
  "output_params_list", "output_params", "output", "$@136", "flush",
  "maxsize", "maxver", "pattern", "$@137", "compatibility", "$@138",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   304,   304,   304,   305,   305,   306,   306,   307,   307,
     308,   308,   309,   309,   310,   310,   311,   311,   312,   312,
     313,   313,   314,   314,   315,   315,   316,   316,   317,   317,
     325,   326,   327,   328,   329,   330,   331,   334,   339,   339,
     350,   353,   354,   357,   362,   368,   373,   373,   380,   381,
     384,   388,   392,   398,   398,   405,   406,   409,   413,   417,
     427,   436,   436,   451,   451,   465,   468,   474,   474,   483,
     484,   485,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   559,   559,   568,
     574,   580,   586,   592,   598,   604,   610,   616,   622,   628,
     634,   640,   646,   652,   658,   664,   670,   670,   679,   682,
     685,   688,   691,   697,   697,   706,   706,   715,   721,   727,
     727,   736,   736,   745,   751,   757,   763,   763,   772,   778,
     784,   790,   796,   796,   808,   808,   817,   818,   819,   824,
     825,   826,   827,   828,   829,   830,   831,   834,   834,   845,
     851,   857,   863,   869,   869,   882,   882,   895,   895,   906,
     907,   910,   911,   912,   917,   917,   927,   928,   929,   934,
     935,   936,   937,   938,   939,   940,   941,   942,   943,   944,
     945,   946,   947,   948,   949,   950,   951,   952,   955,   955,
     963,   964,   965,   968,   968,   977,   977,   986,   986,   995,
    1001,  1001,  1010,  1016,  1022,  1028,  1034,  1040,  1040,  1048,
    1049,  1050,  1053,  1059,  1065,  1065,  1074,  1074,  1083,  1083,
    1092,  1092,  1101,  1101,  1112,  1113,  1114,  1119,  1120,  1123,
    1123,  1142,  1142,  1160,  1160,  1171,  1172,  1173,  1178,  1179,
    1182,  1187,  1192,  1192,  1203,  1204,  1205,  1210,  1211,  1212,
    1215,  1220,  1227,  1227,  1240,  1240,  1253,  1254,  1255,  1260,
    1261,  1262,  1263,  1264,  1265,  1268,  1274,  1280,  1286,  1286,
    1297,  1298,  1301,  1302,  1303,  1308,  1308,  1318,  1318,  1328,
    1329,  1330,  1333,  1336,  1337,  1340,  1340,  1349,  1349,  1358,
    1358,  1370,  1371,  1372,  1377,  1378,  1379,  1380,  1381,  1382,
    1385,  1391,  1397,  1403,  1409,  1415,  1424,  1424,  1438,  1439,
    1442,  1443,  1444,  1453,  1453,  1479,  1479,  1490,  1491,  1492,
    1498,  1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,
    1508,  1509,  1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,
    1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,
    1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,
    1538,  1539,  1540,  1543,  1543,  1552,  1552,  1561,  1561,  1570,
    1570,  1579,  1579,  1590,  1596,  1602,  1608,  1608,  1616,  1617,
    1618,  1619,  1622,  1628,  1636,  1636,  1648,  1649,  1653,  1654,
    1655,  1660,  1660,  1668,  1669,  1670,  1675,  1676,  1677,  1678,
    1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,
    1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,
    1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,
    1709,  1710,  1711,  1712,  1713,  1714,  1721,  1721,  1735,  1735,
    1744,  1745,  1748,  1749,  1750,  1757,  1757,  1772,  1772,  1786,
    1787,  1790,  1791,  1792,  1797,  1798,  1799,  1800,  1801,  1802,
    1803,  1804,  1805,  1806,  1809,  1811,  1817,  1819,  1819,  1828,
    1828,  1837,  1837,  1846,  1848,  1848,  1857,  1867,  1867,  1880,
    1881,  1886,  1887,  1888,  1895,  1895,  1907,  1907,  1919,  1920,
    1925,  1926,  1927,  1934,  1935,  1936,  1937,  1938,  1939,  1940,
    1941,  1942,  1945,  1947,  1947,  1956,  1958,  1960,  1966,  1975,
    1975,  1988,  1989,  1992,  1993,  1994,  1999,  1999,  2009,  2009,
    2019,  2020,  2021,  2026,  2027,  2028,  2029,  2030,  2031,  2032,
    2035,  2035,  2044,  2044,  2069,  2069,  2099,  2099,  2112,  2113,
    2116,  2117,  2118,  2123,  2123,  2135,  2135,  2147,  2148,  2149,
    2154,  2155,  2156,  2157,  2158,  2159,  2160,  2161,  2162,  2163,
    2164,  2167,  2167,  2176,  2182,  2182,  2191,  2197,  2206,  2206,
    2217,  2218,  2221,  2222,  2223,  2228,  2228,  2237,  2237,  2246,
    2247,  2250,  2251,  2252,  2258,  2259,  2260,  2261,  2262,  2263,
    2264,  2265,  2266,  2267,  2268,  2271,  2271,  2282,  2282,  2293,
    2293,  2302,  2302,  2311,  2311,  2320,  2320,  2329,  2329,  2343,
    2343,  2354,  2355,  2358,  2358,  2370,  2370,  2381,  2382,  2383,
    2388,  2388,  2398,  2399,  2402,  2403,  2404,  2409,  2410,  2411,
    2412,  2413,  2414,  2415,  2416,  2417,  2418,  2419,  2420,  2421,
    2422,  2425,  2427,  2427,  2436,  2436,  2445,  2454,  2454,  2467,
    2468,  2469,  2474,  2475,  2476,  2477,  2478,  2479,  2480,  2481,
    2482,  2485,  2485,  2493,  2494,  2495,  2498,  2504,  2504,  2513,
    2519,  2527,  2535,  2535,  2546,  2547,  2548,  2553,  2554,  2555,
    2556,  2557,  2560,  2560,  2569,  2569,  2581,  2581,  2594,  2595,
    2596,  2601,  2602,  2603,  2604,  2605,  2606,  2609,  2615,  2615,
    2624,  2630,  2630,  2640,  2640,  2653,  2653,  2663,  2664,  2665,
    2670,  2671,  2672,  2673,  2674,  2675,  2676,  2677,  2678,  2679,
    2680,  2681,  2682,  2683,  2684,  2685,  2686,  2687,  2690,  2697,
    2697,  2706,  2706,  2715,  2721,  2721,  2730,  2736,  2742,  2742,
    2751,  2752,  2755,  2755,  2765,  2772,  2779,  2779,  2788,  2788,
    2798,  2798,  2808,  2808,  2820,  2820,  2832,  2832,  2842,  2843,
    2844,  2850,  2851,  2854,  2854,  2865,  2873,  2873,  2886,  2887,
    2888,  2894,  2894,  2902,  2903,  2904,  2909,  2910,  2911,  2912,
    2913,  2914,  2915,  2918,  2924,  2924,  2933,  2933,  2944,  2945,
    2946,  2951,  2951,  2959,  2960,  2961,  2966,  2967,  2968,  2969,
    2970,  2973,  2973,  2982,  2988,  2994,  3000,  3000,  3009,  3009,
    3020,  3021,  3022,  3027,  3028,  3031
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
#line 6407 "dhcp6_parser.cc"

#line 3037 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
