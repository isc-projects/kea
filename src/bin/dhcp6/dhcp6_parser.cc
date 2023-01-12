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
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 296 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 296 "dhcp6_parser.yy"
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
#line 305 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 306 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 307 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 308 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 309 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 310 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 311 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 312 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 313 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 314 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 315 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 316 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 317 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 318 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 326 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 327 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 328 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 329 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 330 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 331 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 332 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 335 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 340 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 345 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 351 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 358 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 363 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 369 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 374 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 377 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 385 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 389 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 393 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 399 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 401 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 410 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 414 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 418 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 428 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 437 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 442 "dhcp6_parser.yy"
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
#line 452 "dhcp6_parser.yy"
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
#line 461 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 469 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 475 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 479 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 486 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 137: // $@21: %empty
#line 560 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 138: // data_directory: "data-directory" $@21 ":" "constant string"
#line 563 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 139: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 569 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 140: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 575 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 141: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 587 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 617 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 623 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 629 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 635 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 641 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 647 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 153: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 653 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 154: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 659 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 155: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 665 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 156: // $@22: %empty
#line 671 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 674 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "when-present"
#line 680 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "never"
#line 683 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "always"
#line 686 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-not-present"
#line 689 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "boolean"
#line 692 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 163: // $@23: %empty
#line 698 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 164: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 701 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 165: // $@24: %empty
#line 707 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 166: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 710 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 167: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 716 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 168: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 722 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 169: // $@25: %empty
#line 728 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 731 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 171: // $@26: %empty
#line 737 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 740 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 173: // store_extended_info: "store-extended-info" ":" "boolean"
#line 746 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 174: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 752 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 175: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 758 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 176: // $@27: %empty
#line 764 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 177: // server_tag: "server-tag" $@27 ":" "constant string"
#line 767 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 178: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 773 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 179: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 779 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 180: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 785 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 181: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 791 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 182: // $@28: %empty
#line 797 "dhcp6_parser.yy"
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
#line 803 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 184: // $@29: %empty
#line 809 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 185: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 813 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // interfaces_config_params: interfaces_config_params ","
#line 820 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1598 "dhcp6_parser.cc"
    break;

  case 197: // $@30: %empty
#line 835 "dhcp6_parser.yy"
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
#line 841 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 199: // re_detect: "re-detect" ":" "boolean"
#line 846 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 200: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 852 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 201: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 858 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 202: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 864 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 870 "dhcp6_parser.yy"
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
#line 876 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1682 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 883 "dhcp6_parser.yy"
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
#line 889 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1705 "dhcp6_parser.cc"
    break;

  case 207: // $@33: %empty
#line 896 "dhcp6_parser.yy"
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
#line 902 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 213: // not_empty_database_list: not_empty_database_list ","
#line 913 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1734 "dhcp6_parser.cc"
    break;

  case 214: // $@34: %empty
#line 918 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1744 "dhcp6_parser.cc"
    break;

  case 215: // database: "{" $@34 database_map_params "}"
#line 922 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1754 "dhcp6_parser.cc"
    break;

  case 218: // database_map_params: database_map_params ","
#line 930 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1762 "dhcp6_parser.cc"
    break;

  case 241: // $@35: %empty
#line 959 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1771 "dhcp6_parser.cc"
    break;

  case 242: // database_type: "type" $@35 ":" db_type
#line 962 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 243: // db_type: "memfile"
#line 967 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1786 "dhcp6_parser.cc"
    break;

  case 244: // db_type: "mysql"
#line 968 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1792 "dhcp6_parser.cc"
    break;

  case 245: // db_type: "postgresql"
#line 969 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1798 "dhcp6_parser.cc"
    break;

  case 246: // $@36: %empty
#line 972 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc"
    break;

  case 247: // user: "user" $@36 ":" "constant string"
#line 975 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 248: // $@37: %empty
#line 981 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1826 "dhcp6_parser.cc"
    break;

  case 249: // password: "password" $@37 ":" "constant string"
#line 984 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1836 "dhcp6_parser.cc"
    break;

  case 250: // $@38: %empty
#line 990 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 251: // host: "host" $@38 ":" "constant string"
#line 993 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 252: // port: "port" ":" "integer"
#line 999 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 253: // $@39: %empty
#line 1005 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 254: // name: "name" $@39 ":" "constant string"
#line 1008 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1884 "dhcp6_parser.cc"
    break;

  case 255: // persist: "persist" ":" "boolean"
#line 1014 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1894 "dhcp6_parser.cc"
    break;

  case 256: // lfc_interval: "lfc-interval" ":" "integer"
#line 1020 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 257: // readonly: "readonly" ":" "boolean"
#line 1026 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 258: // connect_timeout: "connect-timeout" ":" "integer"
#line 1032 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 259: // read_timeout: "read-timeout" ":" "integer"
#line 1038 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 260: // write_timeout: "write-timeout" ":" "integer"
#line 1044 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 1944 "dhcp6_parser.cc"
    break;

  case 261: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1050 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 262: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1057 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1964 "dhcp6_parser.cc"
    break;

  case 263: // $@40: %empty
#line 1063 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1973 "dhcp6_parser.cc"
    break;

  case 264: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1066 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1982 "dhcp6_parser.cc"
    break;

  case 265: // on_fail_mode: "stop-retry-exit"
#line 1071 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1988 "dhcp6_parser.cc"
    break;

  case 266: // on_fail_mode: "serve-retry-exit"
#line 1072 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1994 "dhcp6_parser.cc"
    break;

  case 267: // on_fail_mode: "serve-retry-continue"
#line 1073 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2000 "dhcp6_parser.cc"
    break;

  case 268: // max_row_errors: "max-row-errors" ":" "integer"
#line 1076 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2010 "dhcp6_parser.cc"
    break;

  case 269: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1082 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2020 "dhcp6_parser.cc"
    break;

  case 270: // $@41: %empty
#line 1088 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 271: // trust_anchor: "trust-anchor" $@41 ":" "constant string"
#line 1091 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 272: // $@42: %empty
#line 1097 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2048 "dhcp6_parser.cc"
    break;

  case 273: // cert_file: "cert-file" $@42 ":" "constant string"
#line 1100 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2058 "dhcp6_parser.cc"
    break;

  case 274: // $@43: %empty
#line 1106 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 275: // key_file: "key-file" $@43 ":" "constant string"
#line 1109 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 276: // $@44: %empty
#line 1115 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 277: // cipher_list: "cipher-list" $@44 ":" "constant string"
#line 1118 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 278: // $@45: %empty
#line 1124 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2108 "dhcp6_parser.cc"
    break;

  case 279: // sanity_checks: "sanity-checks" $@45 ":" "{" sanity_checks_params "}"
#line 1130 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2117 "dhcp6_parser.cc"
    break;

  case 282: // sanity_checks_params: sanity_checks_params ","
#line 1137 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2125 "dhcp6_parser.cc"
    break;

  case 284: // $@46: %empty
#line 1144 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 285: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1147 "dhcp6_parser.yy"
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
#line 2154 "dhcp6_parser.cc"
    break;

  case 286: // $@47: %empty
#line 1163 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2166 "dhcp6_parser.cc"
    break;

  case 287: // mac_sources: "mac-sources" $@47 ":" "[" mac_sources_list "]"
#line 1169 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2175 "dhcp6_parser.cc"
    break;

  case 290: // mac_sources_list: mac_sources_list ","
#line 1176 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2183 "dhcp6_parser.cc"
    break;

  case 293: // duid_id: "duid"
#line 1185 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 294: // string_id: "constant string"
#line 1190 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1195 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2213 "dhcp6_parser.cc"
    break;

  case 296: // host_reservation_identifiers: "host-reservation-identifiers" $@48 ":" "[" host_reservation_identifiers_list "]"
#line 1201 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2222 "dhcp6_parser.cc"
    break;

  case 299: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1208 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2230 "dhcp6_parser.cc"
    break;

  case 303: // hw_address_id: "hw-address"
#line 1218 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 304: // flex_id: "flex-id"
#line 1223 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 305: // $@49: %empty
#line 1230 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2260 "dhcp6_parser.cc"
    break;

  case 306: // relay_supplied_options: "relay-supplied-options" $@49 ":" "[" list_content "]"
#line 1236 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 307: // $@50: %empty
#line 1243 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2281 "dhcp6_parser.cc"
    break;

  case 308: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1249 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2292 "dhcp6_parser.cc"
    break;

  case 311: // multi_threading_params: multi_threading_params ","
#line 1258 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2300 "dhcp6_parser.cc"
    break;

  case 318: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1271 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2310 "dhcp6_parser.cc"
    break;

  case 319: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1277 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2320 "dhcp6_parser.cc"
    break;

  case 320: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1283 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2330 "dhcp6_parser.cc"
    break;

  case 321: // $@51: %empty
#line 1289 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2342 "dhcp6_parser.cc"
    break;

  case 322: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1295 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2351 "dhcp6_parser.cc"
    break;

  case 327: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1306 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2359 "dhcp6_parser.cc"
    break;

  case 328: // $@52: %empty
#line 1311 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2369 "dhcp6_parser.cc"
    break;

  case 329: // hooks_library: "{" $@52 hooks_params "}"
#line 1315 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2379 "dhcp6_parser.cc"
    break;

  case 330: // $@53: %empty
#line 1321 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 331: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1325 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 334: // hooks_params: hooks_params ","
#line 1333 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2407 "dhcp6_parser.cc"
    break;

  case 338: // $@54: %empty
#line 1343 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp6_parser.cc"
    break;

  case 339: // library: "library" $@54 ":" "constant string"
#line 1346 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2426 "dhcp6_parser.cc"
    break;

  case 340: // $@55: %empty
#line 1352 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2435 "dhcp6_parser.cc"
    break;

  case 341: // parameters: "parameters" $@55 ":" map_value
#line 1355 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2444 "dhcp6_parser.cc"
    break;

  case 342: // $@56: %empty
#line 1361 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 343: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1367 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 346: // expired_leases_params: expired_leases_params ","
#line 1375 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2474 "dhcp6_parser.cc"
    break;

  case 353: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1388 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2484 "dhcp6_parser.cc"
    break;

  case 354: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1394 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2494 "dhcp6_parser.cc"
    break;

  case 355: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1400 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2504 "dhcp6_parser.cc"
    break;

  case 356: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1406 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2514 "dhcp6_parser.cc"
    break;

  case 357: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1412 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2524 "dhcp6_parser.cc"
    break;

  case 358: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1418 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 359: // $@57: %empty
#line 1427 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 360: // subnet6_list: "subnet6" $@57 ":" "[" subnet6_list_content "]"
#line 1433 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 365: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1447 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2563 "dhcp6_parser.cc"
    break;

  case 366: // $@58: %empty
#line 1456 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2573 "dhcp6_parser.cc"
    break;

  case 367: // subnet6: "{" $@58 subnet6_params "}"
#line 1460 "dhcp6_parser.yy"
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
#line 2599 "dhcp6_parser.cc"
    break;

  case 368: // $@59: %empty
#line 1482 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2609 "dhcp6_parser.cc"
    break;

  case 369: // sub_subnet6: "{" $@59 subnet6_params "}"
#line 1486 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2619 "dhcp6_parser.cc"
    break;

  case 372: // subnet6_params: subnet6_params ","
#line 1495 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2627 "dhcp6_parser.cc"
    break;

  case 416: // $@60: %empty
#line 1546 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2636 "dhcp6_parser.cc"
    break;

  case 417: // subnet: "subnet" $@60 ":" "constant string"
#line 1549 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2646 "dhcp6_parser.cc"
    break;

  case 418: // $@61: %empty
#line 1555 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2655 "dhcp6_parser.cc"
    break;

  case 419: // interface: "interface" $@61 ":" "constant string"
#line 1558 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2665 "dhcp6_parser.cc"
    break;

  case 420: // $@62: %empty
#line 1564 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2674 "dhcp6_parser.cc"
    break;

  case 421: // interface_id: "interface-id" $@62 ":" "constant string"
#line 1567 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 422: // $@63: %empty
#line 1573 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 423: // client_class: "client-class" $@63 ":" "constant string"
#line 1576 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 424: // $@64: %empty
#line 1582 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 425: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1588 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc"
    break;

  case 426: // reservations_global: "reservations-global" ":" "boolean"
#line 1593 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2734 "dhcp6_parser.cc"
    break;

  case 427: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1599 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2744 "dhcp6_parser.cc"
    break;

  case 428: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1605 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2754 "dhcp6_parser.cc"
    break;

  case 429: // $@65: %empty
#line 1611 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 430: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1614 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2772 "dhcp6_parser.cc"
    break;

  case 431: // hr_mode: "disabled"
#line 1619 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2778 "dhcp6_parser.cc"
    break;

  case 432: // hr_mode: "out-of-pool"
#line 1620 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2784 "dhcp6_parser.cc"
    break;

  case 433: // hr_mode: "global"
#line 1621 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2790 "dhcp6_parser.cc"
    break;

  case 434: // hr_mode: "all"
#line 1622 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2796 "dhcp6_parser.cc"
    break;

  case 435: // id: "id" ":" "integer"
#line 1625 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2806 "dhcp6_parser.cc"
    break;

  case 436: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1631 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2816 "dhcp6_parser.cc"
    break;

  case 437: // $@66: %empty
#line 1639 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2828 "dhcp6_parser.cc"
    break;

  case 438: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1645 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2837 "dhcp6_parser.cc"
    break;

  case 443: // shared_networks_list: shared_networks_list ","
#line 1658 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2845 "dhcp6_parser.cc"
    break;

  case 444: // $@67: %empty
#line 1663 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2855 "dhcp6_parser.cc"
    break;

  case 445: // shared_network: "{" $@67 shared_network_params "}"
#line 1667 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 448: // shared_network_params: shared_network_params ","
#line 1673 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2871 "dhcp6_parser.cc"
    break;

  case 489: // $@68: %empty
#line 1724 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2883 "dhcp6_parser.cc"
    break;

  case 490: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1730 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2892 "dhcp6_parser.cc"
    break;

  case 491: // $@69: %empty
#line 1738 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2901 "dhcp6_parser.cc"
    break;

  case 492: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1741 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2909 "dhcp6_parser.cc"
    break;

  case 497: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1753 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2917 "dhcp6_parser.cc"
    break;

  case 498: // $@70: %empty
#line 1760 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2927 "dhcp6_parser.cc"
    break;

  case 499: // option_def_entry: "{" $@70 option_def_params "}"
#line 1764 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2939 "dhcp6_parser.cc"
    break;

  case 500: // $@71: %empty
#line 1775 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2949 "dhcp6_parser.cc"
    break;

  case 501: // sub_option_def: "{" $@71 option_def_params "}"
#line 1779 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2961 "dhcp6_parser.cc"
    break;

  case 506: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1795 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2969 "dhcp6_parser.cc"
    break;

  case 518: // code: "code" ":" "integer"
#line 1814 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2979 "dhcp6_parser.cc"
    break;

  case 520: // $@72: %empty
#line 1822 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2988 "dhcp6_parser.cc"
    break;

  case 521: // option_def_type: "type" $@72 ":" "constant string"
#line 1825 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2998 "dhcp6_parser.cc"
    break;

  case 522: // $@73: %empty
#line 1831 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3007 "dhcp6_parser.cc"
    break;

  case 523: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1834 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 524: // $@74: %empty
#line 1840 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp6_parser.cc"
    break;

  case 525: // space: "space" $@74 ":" "constant string"
#line 1843 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3036 "dhcp6_parser.cc"
    break;

  case 527: // $@75: %empty
#line 1851 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 528: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1854 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 529: // option_def_array: "array" ":" "boolean"
#line 1860 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 530: // $@76: %empty
#line 1870 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3077 "dhcp6_parser.cc"
    break;

  case 531: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1876 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp6_parser.cc"
    break;

  case 536: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1891 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3094 "dhcp6_parser.cc"
    break;

  case 537: // $@77: %empty
#line 1898 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 538: // option_data_entry: "{" $@77 option_data_params "}"
#line 1902 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3113 "dhcp6_parser.cc"
    break;

  case 539: // $@78: %empty
#line 1910 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3123 "dhcp6_parser.cc"
    break;

  case 540: // sub_option_data: "{" $@78 option_data_params "}"
#line 1914 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 545: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1930 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3140 "dhcp6_parser.cc"
    break;

  case 556: // $@79: %empty
#line 1950 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 557: // option_data_data: "data" $@79 ":" "constant string"
#line 1953 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 560: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1963 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3169 "dhcp6_parser.cc"
    break;

  case 561: // option_data_always_send: "always-send" ":" "boolean"
#line 1969 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 562: // $@80: %empty
#line 1978 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3191 "dhcp6_parser.cc"
    break;

  case 563: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1984 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 568: // not_empty_pools_list: not_empty_pools_list ","
#line 1997 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3208 "dhcp6_parser.cc"
    break;

  case 569: // $@81: %empty
#line 2002 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3218 "dhcp6_parser.cc"
    break;

  case 570: // pool_list_entry: "{" $@81 pool_params "}"
#line 2006 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3228 "dhcp6_parser.cc"
    break;

  case 571: // $@82: %empty
#line 2012 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 572: // sub_pool6: "{" $@82 pool_params "}"
#line 2016 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3248 "dhcp6_parser.cc"
    break;

  case 575: // pool_params: pool_params ","
#line 2024 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3256 "dhcp6_parser.cc"
    break;

  case 583: // $@83: %empty
#line 2038 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3265 "dhcp6_parser.cc"
    break;

  case 584: // pool_entry: "pool" $@83 ":" "constant string"
#line 2041 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3275 "dhcp6_parser.cc"
    break;

  case 585: // $@84: %empty
#line 2047 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 586: // user_context: "user-context" $@84 ":" map_value
#line 2049 "dhcp6_parser.yy"
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
#line 3310 "dhcp6_parser.cc"
    break;

  case 587: // $@85: %empty
#line 2072 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 588: // comment: "comment" $@85 ":" "constant string"
#line 2074 "dhcp6_parser.yy"
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
#line 3347 "dhcp6_parser.cc"
    break;

  case 589: // $@86: %empty
#line 2102 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 590: // pd_pools_list: "pd-pools" $@86 ":" "[" pd_pools_list_content "]"
#line 2108 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3368 "dhcp6_parser.cc"
    break;

  case 595: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2121 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3376 "dhcp6_parser.cc"
    break;

  case 596: // $@87: %empty
#line 2126 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3386 "dhcp6_parser.cc"
    break;

  case 597: // pd_pool_entry: "{" $@87 pd_pool_params "}"
#line 2130 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 598: // $@88: %empty
#line 2138 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 599: // sub_pd_pool: "{" $@88 pd_pool_params "}"
#line 2142 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 602: // pd_pool_params: pd_pool_params ","
#line 2152 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3428 "dhcp6_parser.cc"
    break;

  case 614: // $@89: %empty
#line 2170 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 615: // pd_prefix: "prefix" $@89 ":" "constant string"
#line 2173 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3447 "dhcp6_parser.cc"
    break;

  case 616: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2179 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3457 "dhcp6_parser.cc"
    break;

  case 617: // $@90: %empty
#line 2185 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp6_parser.cc"
    break;

  case 618: // excluded_prefix: "excluded-prefix" $@90 ":" "constant string"
#line 2188 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 619: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2194 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3486 "dhcp6_parser.cc"
    break;

  case 620: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2200 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3496 "dhcp6_parser.cc"
    break;

  case 621: // $@91: %empty
#line 2209 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 622: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2215 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3517 "dhcp6_parser.cc"
    break;

  case 627: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2226 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3525 "dhcp6_parser.cc"
    break;

  case 628: // $@92: %empty
#line 2231 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 629: // reservation: "{" $@92 reservation_params "}"
#line 2235 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 630: // $@93: %empty
#line 2240 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3554 "dhcp6_parser.cc"
    break;

  case 631: // sub_reservation: "{" $@93 reservation_params "}"
#line 2244 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3563 "dhcp6_parser.cc"
    break;

  case 636: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2255 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3571 "dhcp6_parser.cc"
    break;

  case 648: // $@94: %empty
#line 2274 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp6_parser.cc"
    break;

  case 649: // ip_addresses: "ip-addresses" $@94 ":" list_strings
#line 2280 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3592 "dhcp6_parser.cc"
    break;

  case 650: // $@95: %empty
#line 2285 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 651: // prefixes: "prefixes" $@95 ":" list_strings
#line 2291 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 652: // $@96: %empty
#line 2296 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 653: // duid: "duid" $@96 ":" "constant string"
#line 2299 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 654: // $@97: %empty
#line 2305 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3641 "dhcp6_parser.cc"
    break;

  case 655: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2308 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3651 "dhcp6_parser.cc"
    break;

  case 656: // $@98: %empty
#line 2314 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3660 "dhcp6_parser.cc"
    break;

  case 657: // hostname: "hostname" $@98 ":" "constant string"
#line 2317 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3670 "dhcp6_parser.cc"
    break;

  case 658: // $@99: %empty
#line 2323 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3679 "dhcp6_parser.cc"
    break;

  case 659: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2326 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3689 "dhcp6_parser.cc"
    break;

  case 660: // $@100: %empty
#line 2332 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 661: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2338 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 662: // $@101: %empty
#line 2346 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3722 "dhcp6_parser.cc"
    break;

  case 663: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2352 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3731 "dhcp6_parser.cc"
    break;

  case 666: // $@102: %empty
#line 2361 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3740 "dhcp6_parser.cc"
    break;

  case 667: // ip_address: "ip-address" $@102 ":" "constant string"
#line 2364 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3750 "dhcp6_parser.cc"
    break;

  case 668: // $@103: %empty
#line 2373 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3762 "dhcp6_parser.cc"
    break;

  case 669: // client_classes: "client-classes" $@103 ":" "[" client_classes_list "]"
#line 2379 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3771 "dhcp6_parser.cc"
    break;

  case 672: // client_classes_list: client_classes_list ","
#line 2386 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3779 "dhcp6_parser.cc"
    break;

  case 673: // $@104: %empty
#line 2391 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3789 "dhcp6_parser.cc"
    break;

  case 674: // client_class_entry: "{" $@104 client_class_params "}"
#line 2395 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3799 "dhcp6_parser.cc"
    break;

  case 679: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2407 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3807 "dhcp6_parser.cc"
    break;

  case 694: // $@105: %empty
#line 2429 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3816 "dhcp6_parser.cc"
    break;

  case 695: // client_class_test: "test" $@105 ":" "constant string"
#line 2432 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3826 "dhcp6_parser.cc"
    break;

  case 696: // only_if_required: "only-if-required" ":" "boolean"
#line 2438 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 697: // $@106: %empty
#line 2447 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 698: // server_id: "server-id" $@106 ":" "{" server_id_params "}"
#line 2453 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3859 "dhcp6_parser.cc"
    break;

  case 701: // server_id_params: server_id_params ","
#line 2462 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3867 "dhcp6_parser.cc"
    break;

  case 711: // $@107: %empty
#line 2478 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 712: // server_id_type: "type" $@107 ":" duid_type
#line 2481 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3885 "dhcp6_parser.cc"
    break;

  case 713: // duid_type: "LLT"
#line 2486 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3891 "dhcp6_parser.cc"
    break;

  case 714: // duid_type: "EN"
#line 2487 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3897 "dhcp6_parser.cc"
    break;

  case 715: // duid_type: "LL"
#line 2488 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3903 "dhcp6_parser.cc"
    break;

  case 716: // htype: "htype" ":" "integer"
#line 2491 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3913 "dhcp6_parser.cc"
    break;

  case 717: // $@108: %empty
#line 2497 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3922 "dhcp6_parser.cc"
    break;

  case 718: // identifier: "identifier" $@108 ":" "constant string"
#line 2500 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 719: // time: "time" ":" "integer"
#line 2506 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 720: // enterprise_id: "enterprise-id" ":" "integer"
#line 2512 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3952 "dhcp6_parser.cc"
    break;

  case 721: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2520 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 722: // $@109: %empty
#line 2528 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 723: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2534 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 726: // control_socket_params: control_socket_params ","
#line 2541 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3991 "dhcp6_parser.cc"
    break;

  case 732: // $@110: %empty
#line 2553 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 733: // socket_type: "socket-type" $@110 ":" "constant string"
#line 2556 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 734: // $@111: %empty
#line 2562 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 735: // socket_name: "socket-name" $@111 ":" "constant string"
#line 2565 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 736: // $@112: %empty
#line 2574 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 737: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2580 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 740: // queue_control_params: queue_control_params ","
#line 2589 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4060 "dhcp6_parser.cc"
    break;

  case 747: // enable_queue: "enable-queue" ":" "boolean"
#line 2602 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4070 "dhcp6_parser.cc"
    break;

  case 748: // $@113: %empty
#line 2608 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4079 "dhcp6_parser.cc"
    break;

  case 749: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2611 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 750: // capacity: "capacity" ":" "integer"
#line 2617 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4099 "dhcp6_parser.cc"
    break;

  case 751: // $@114: %empty
#line 2623 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 752: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2626 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 753: // $@115: %empty
#line 2633 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4129 "dhcp6_parser.cc"
    break;

  case 754: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2639 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4140 "dhcp6_parser.cc"
    break;

  case 755: // $@116: %empty
#line 2646 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4150 "dhcp6_parser.cc"
    break;

  case 756: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2650 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4160 "dhcp6_parser.cc"
    break;

  case 759: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2658 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4168 "dhcp6_parser.cc"
    break;

  case 778: // enable_updates: "enable-updates" ":" "boolean"
#line 2683 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4178 "dhcp6_parser.cc"
    break;

  case 779: // $@117: %empty
#line 2690 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4187 "dhcp6_parser.cc"
    break;

  case 780: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2693 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4197 "dhcp6_parser.cc"
    break;

  case 781: // $@118: %empty
#line 2699 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 782: // server_ip: "server-ip" $@118 ":" "constant string"
#line 2702 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 783: // server_port: "server-port" ":" "integer"
#line 2708 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 784: // $@119: %empty
#line 2714 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4235 "dhcp6_parser.cc"
    break;

  case 785: // sender_ip: "sender-ip" $@119 ":" "constant string"
#line 2717 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 786: // sender_port: "sender-port" ":" "integer"
#line 2723 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 787: // max_queue_size: "max-queue-size" ":" "integer"
#line 2729 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 788: // $@120: %empty
#line 2735 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4274 "dhcp6_parser.cc"
    break;

  case 789: // ncr_protocol: "ncr-protocol" $@120 ":" ncr_protocol_value
#line 2738 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 790: // ncr_protocol_value: "UDP"
#line 2744 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4289 "dhcp6_parser.cc"
    break;

  case 791: // ncr_protocol_value: "TCP"
#line 2745 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4295 "dhcp6_parser.cc"
    break;

  case 792: // $@121: %empty
#line 2748 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4304 "dhcp6_parser.cc"
    break;

  case 793: // ncr_format: "ncr-format" $@121 ":" "JSON"
#line 2751 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4314 "dhcp6_parser.cc"
    break;

  case 794: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2758 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4324 "dhcp6_parser.cc"
    break;

  case 795: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2765 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4334 "dhcp6_parser.cc"
    break;

  case 796: // $@122: %empty
#line 2772 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4343 "dhcp6_parser.cc"
    break;

  case 797: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2775 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4352 "dhcp6_parser.cc"
    break;

  case 798: // $@123: %empty
#line 2781 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4361 "dhcp6_parser.cc"
    break;

  case 799: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2784 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4371 "dhcp6_parser.cc"
    break;

  case 800: // $@124: %empty
#line 2791 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4380 "dhcp6_parser.cc"
    break;

  case 801: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2794 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4390 "dhcp6_parser.cc"
    break;

  case 802: // $@125: %empty
#line 2801 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4399 "dhcp6_parser.cc"
    break;

  case 803: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2804 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 804: // $@126: %empty
#line 2813 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4421 "dhcp6_parser.cc"
    break;

  case 805: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2819 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 806: // $@127: %empty
#line 2825 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 807: // sub_config_control: "{" $@127 config_control_params "}"
#line 2829 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 810: // config_control_params: config_control_params ","
#line 2837 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4458 "dhcp6_parser.cc"
    break;

  case 813: // $@128: %empty
#line 2847 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4470 "dhcp6_parser.cc"
    break;

  case 814: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2853 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4479 "dhcp6_parser.cc"
    break;

  case 815: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2858 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4489 "dhcp6_parser.cc"
    break;

  case 816: // $@129: %empty
#line 2866 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4501 "dhcp6_parser.cc"
    break;

  case 817: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2872 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4510 "dhcp6_parser.cc"
    break;

  case 820: // loggers_entries: loggers_entries ","
#line 2881 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4518 "dhcp6_parser.cc"
    break;

  case 821: // $@130: %empty
#line 2887 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4528 "dhcp6_parser.cc"
    break;

  case 822: // logger_entry: "{" $@130 logger_params "}"
#line 2891 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4536 "dhcp6_parser.cc"
    break;

  case 825: // logger_params: logger_params ","
#line 2897 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4544 "dhcp6_parser.cc"
    break;

  case 833: // debuglevel: "debuglevel" ":" "integer"
#line 2911 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4554 "dhcp6_parser.cc"
    break;

  case 834: // $@131: %empty
#line 2917 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4563 "dhcp6_parser.cc"
    break;

  case 835: // severity: "severity" $@131 ":" "constant string"
#line 2920 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4573 "dhcp6_parser.cc"
    break;

  case 836: // $@132: %empty
#line 2926 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4585 "dhcp6_parser.cc"
    break;

  case 837: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2932 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 840: // output_options_list_content: output_options_list_content ","
#line 2939 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4602 "dhcp6_parser.cc"
    break;

  case 841: // $@133: %empty
#line 2944 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4612 "dhcp6_parser.cc"
    break;

  case 842: // output_entry: "{" $@133 output_params_list "}"
#line 2948 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4620 "dhcp6_parser.cc"
    break;

  case 845: // output_params_list: output_params_list ","
#line 2954 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4628 "dhcp6_parser.cc"
    break;

  case 851: // $@134: %empty
#line 2966 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4637 "dhcp6_parser.cc"
    break;

  case 852: // output: "output" $@134 ":" "constant string"
#line 2969 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4647 "dhcp6_parser.cc"
    break;

  case 853: // flush: "flush" ":" "boolean"
#line 2975 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4657 "dhcp6_parser.cc"
    break;

  case 854: // maxsize: "maxsize" ":" "integer"
#line 2981 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4667 "dhcp6_parser.cc"
    break;

  case 855: // maxver: "maxver" ":" "integer"
#line 2987 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4677 "dhcp6_parser.cc"
    break;

  case 856: // $@135: %empty
#line 2993 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 857: // pattern: "pattern" $@135 ":" "constant string"
#line 2996 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4696 "dhcp6_parser.cc"
    break;

  case 858: // $@136: %empty
#line 3002 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4708 "dhcp6_parser.cc"
    break;

  case 859: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 3008 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 862: // compatibility_params: compatibility_params ","
#line 3015 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4725 "dhcp6_parser.cc"
    break;

  case 865: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3024 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4735 "dhcp6_parser.cc"
    break;


#line 4739 "dhcp6_parser.cc"

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
     434, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,    68,    30,    74,    81,    92,
     102,   110,   126,   137,   147,   163,   167,   173,   177,   187,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,    30,  -137,
     130,   160,    78,   665,   311,   230,   238,    13,    80,   108,
     -82,   448,    43, -1005,   158,   153,   205,   249,   247, -1005,
      67, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   257,   286,
     336,   338,   346,   364,   368,   386,   387,   393,   403,   416,
     417,   427, -1005,   428,   436,   437,   440,   441, -1005, -1005,
   -1005,   442,   444,   445, -1005, -1005, -1005,   446, -1005, -1005,
   -1005, -1005,   449,   451,   452, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,   455, -1005, -1005, -1005, -1005, -1005,
   -1005,   456,   457,   458, -1005, -1005,   459, -1005,    79, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,   463,   464,   465,   467, -1005,
      83, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,   468,   471, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,    97, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   112,
   -1005, -1005, -1005, -1005, -1005,   472, -1005,   473,   474, -1005,
   -1005, -1005, -1005, -1005, -1005,   113, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   289,   304, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   323, -1005, -1005,   475, -1005, -1005, -1005,
     477, -1005, -1005,   343,   367, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   479,   481,
   -1005, -1005, -1005, -1005,   411,   483, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   133, -1005,
   -1005, -1005,   484, -1005, -1005,   487, -1005,   488,   498, -1005,
   -1005,   499,   500, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
     143, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   502,   149,
   -1005, -1005, -1005, -1005,    30,    30, -1005,   294,   504, -1005,
   -1005,   508,   510,   513,   515,   518,   522,   273,   313,   316,
     317,   320,   321,   322,   324,   236,   325,   337,   339,   341,
     342,   524,   351,   353,   334,   345,   348,   547,   549,   553,
     354,   355,   356,   565,   569,   571,   362,   574,   578,   579,
     581,   370,   372,   373,   586,   588,   589,   592,   594,   595,
     596,   598,   600,   391,   602,   603,   605,   620,   621,   622,
     412,   413,   431,   623,   626, -1005,   160, -1005,   644,   433,
     435,   439,   443,    78, -1005,   646,   650,   652,   654,   655,
     450,   447,   656,   658,   661,   665, -1005,   662,   311, -1005,
     663,   454,   666,   460,   461,   230, -1005,   668,   669,   672,
     673,   674,   675,   676, -1005,   238, -1005,   677,   678,   469,
     680,   681,   682,   453, -1005,    80,   683,   478,   482, -1005,
     108,   687,   689,   -50, -1005,   485,   691,   693,   486,   695,
     489,   495,   698,   706,   497,   512,   707,   725,   726,   727,
     448, -1005,   737,   528,    43, -1005, -1005, -1005,   740,   738,
     533,   745,   746,   747,   749,   754, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
     545, -1005, -1005, -1005, -1005, -1005,  -108,   548,   558, -1005,
   -1005, -1005,   755,   757,   767, -1005,   768,   771,   561,   330,
   -1005, -1005, -1005,   774,   775,   776,   778,   777,   781,   784,
     783,   785, -1005,   786,   787,   789,   790,   570,   585, -1005,
   -1005, -1005,   794,   793, -1005,   796, -1005, -1005, -1005, -1005,
   -1005,   797,   811,   604,   606,   617, -1005, -1005,   796,   624,
     826, -1005,   625, -1005,   627, -1005,   628, -1005, -1005, -1005,
     796,   796,   796,   629,   630,   631,   632, -1005,   633,   634,
   -1005,   637,   640,   643, -1005, -1005,   647, -1005, -1005, -1005,
     648,   771, -1005, -1005,   649,   653, -1005,   657, -1005, -1005,
      25,   613, -1005, -1005,  -108,   660,   664,   667, -1005,   813,
   -1005, -1005,    30,   160, -1005,    43,    78,   347,   347,   827,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   828,
     829,   832,   852, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,   -94,    30,    -3,   750,   861,   862,   864,   275,   106,
      87,   -44,   -58,   448, -1005, -1005,   867,  -160, -1005, -1005,
     869,   872, -1005, -1005, -1005, -1005, -1005,   -66, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,   827, -1005,   150,
     165,   192, -1005, -1005, -1005, -1005,   877,   878,   880,   881,
     882,   883,   884,   885,   886,   887, -1005,   888, -1005, -1005,
   -1005, -1005, -1005,   200, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   239, -1005,   889,   890,
   -1005, -1005,   891,   893, -1005, -1005,   892,   896, -1005, -1005,
     894,   898, -1005, -1005,   897,   899, -1005, -1005, -1005,   131,
   -1005, -1005, -1005,   900, -1005, -1005, -1005,   157, -1005, -1005,
   -1005, -1005,   248, -1005, -1005, -1005,   303, -1005, -1005,   901,
     902, -1005, -1005,   903,   905, -1005,   906,   907,   908,   909,
     910,   911,   274, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   912,   913,   914, -1005, -1005, -1005, -1005,   291,
   -1005, -1005, -1005, -1005, -1005, -1005,   915,   916,   917, -1005,
     293, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   295, -1005, -1005, -1005,   918, -1005,   919, -1005,
   -1005, -1005,   327, -1005, -1005, -1005, -1005, -1005,   331, -1005,
     314, -1005,   920, -1005,   350, -1005, -1005,   712, -1005,   921,
     923, -1005, -1005,   922,   926, -1005, -1005, -1005,   924, -1005,
     925, -1005, -1005, -1005,   929,   930,   931,   934,   690,   714,
     728,   723,   729,   730,   731,   732,   733,   734,   936,   736,
     937,   947,   949,   950,   347, -1005, -1005,   347, -1005,   827,
     665, -1005,   828,    80, -1005,   829,   108, -1005,   832,   753,
   -1005,   852,   -94, -1005, -1005,    -3, -1005,   952,   750, -1005,
     234,   861, -1005,   238, -1005,   862,   -82, -1005,   864,   743,
     759,   762,   765,   766,   769,   275, -1005,   959,   960,   773,
     791,   805,   106, -1005,   751,   806,   809,    87, -1005,   978,
    1000,   -44, -1005,   814,  1006,   815,  1023,   -58, -1005, -1005,
     329,   867, -1005,   822,  -160, -1005, -1005,  1036,  1040,   311,
   -1005,   869,   230, -1005,   872,  1042, -1005, -1005,   242,   838,
     851,   858, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   237, -1005,   874,   895,   904,   927, -1005,   366,
   -1005,   395, -1005,  1086, -1005,  1089, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   396, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,   928, -1005, -1005,  1096, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005,  1095,  1102, -1005,
   -1005, -1005, -1005, -1005,  1098, -1005,   397, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,   216,   932, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005,   933,   935, -1005, -1005,   938,
   -1005,    30, -1005, -1005,  1103, -1005, -1005, -1005, -1005, -1005,
     398, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   939,
     414, -1005,   415, -1005,   940, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,   753, -1005, -1005,  1105,   941, -1005,
     234, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,  1106,   942,  1107,   329, -1005, -1005, -1005, -1005,
   -1005, -1005,   945, -1005, -1005,  1108, -1005,   946, -1005, -1005,
    1109, -1005, -1005,   335, -1005,     3,  1109, -1005, -1005,  1110,
    1111,  1114, -1005,   426, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,  1115,   944,   954,   955,  1116,     3, -1005,   948, -1005,
   -1005, -1005,   953, -1005, -1005, -1005
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   184,     9,   368,    11,
     571,    13,   598,    15,   630,    17,   491,    19,   500,    21,
     539,    23,   330,    25,   755,    27,   806,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   632,     0,   502,   541,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   137,   804,   182,   203,   205,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   156,   163,
     165,     0,     0,     0,   359,   489,   530,     0,   437,   585,
     587,   429,     0,     0,     0,   286,   305,   295,   278,   668,
     621,   321,   342,   697,     0,   307,   722,   736,   753,   169,
     171,     0,     0,     0,   816,   858,     0,   136,     0,    69,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   117,   118,   127,   128,   129,   106,   135,
     131,   132,   133,    84,    85,    86,    87,   103,    88,    90,
      89,   130,    94,    95,    82,   108,   109,   110,   107,    83,
      92,    93,   101,   102,   104,    91,    96,    97,    98,    99,
     100,   105,   116,   134,   197,     0,     0,     0,     0,   196,
       0,   186,   189,   190,   191,   192,   193,   194,   195,   562,
     589,   416,   418,   420,     0,     0,   424,   422,   662,   415,
     373,   374,   375,   376,   377,   378,   379,   380,   399,   400,
     401,   402,   403,   406,   407,   408,   409,   410,   411,   412,
     413,   404,   405,   414,     0,   370,   384,   385,   386,   389,
     390,   393,   394,   395,   392,   387,   388,   381,   382,   397,
     398,   383,   391,   396,   583,   582,   578,   579,   577,     0,
     573,   576,   580,   581,   614,     0,   617,     0,     0,   613,
     607,   608,   606,   611,   612,     0,   600,   603,   604,   609,
     610,   605,   660,   648,   650,   652,   654,   656,   658,   647,
     644,   645,   646,     0,   633,   634,   639,   640,   637,   641,
     642,   643,   638,     0,   520,   253,     0,   524,   522,   527,
       0,   516,   517,     0,   503,   504,   507,   519,   508,   509,
     510,   526,   511,   512,   513,   514,   515,   556,     0,     0,
     554,   555,   558,   559,     0,   542,   543,   546,   547,   548,
     549,   550,   551,   552,   553,   338,   340,   335,     0,   332,
     336,   337,     0,   779,   781,     0,   784,     0,     0,   788,
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
       0,     0,     0,     0,     0,   372,   369,     0,   575,   572,
       0,     0,     0,     0,     0,   602,   599,     0,     0,     0,
       0,     0,     0,     0,   631,   636,   492,     0,     0,     0,
       0,     0,     0,     0,   501,   506,     0,     0,     0,   540,
     545,     0,     0,   334,   331,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   756,     0,     0,   810,   807,    51,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,   174,   175,   153,   154,   155,     0,     0,     0,   167,
     168,   173,     0,     0,     0,   178,     0,     0,     0,     0,
     426,   427,   428,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   721,     0,     0,     0,     0,     0,     0,   179,
     180,   181,     0,     0,    70,     0,   199,   200,   201,   202,
     187,     0,     0,     0,     0,     0,   435,   436,     0,     0,
       0,   371,     0,   574,     0,   616,     0,   619,   620,   601,
       0,     0,     0,     0,     0,     0,     0,   635,     0,     0,
     518,     0,     0,     0,   529,   505,     0,   560,   561,   544,
       0,     0,   333,   778,     0,     0,   783,     0,   786,   787,
       0,     0,   794,   795,     0,     0,     0,     0,   758,     0,
     815,   809,     0,     0,   138,     0,     0,     0,     0,   209,
     177,   158,   159,   160,   161,   162,   157,   164,   166,   361,
     493,   532,   439,    40,   586,   588,   431,   432,   433,   434,
     430,     0,    48,     0,     0,     0,   623,   323,     0,     0,
       0,     0,     0,     0,   170,   172,     0,     0,    53,   198,
     564,   591,   417,   419,   421,   425,   423,     0,   584,   615,
     618,   661,   649,   651,   653,   655,   657,   659,   521,   254,
     525,   523,   528,   557,   339,   341,   780,   782,   785,   790,
     791,   789,   793,   797,   799,   801,   803,   209,    44,     0,
       0,     0,   241,   246,   248,   250,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   263,     0,   270,   272,
     274,   276,   240,     0,   216,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   233,   234,
     235,   232,   236,   237,   238,   239,     0,   214,     0,   210,
     211,   366,     0,   362,   363,   498,     0,   494,   495,   537,
       0,   533,   534,   444,     0,   440,   441,   293,   294,     0,
     288,   291,   292,     0,   303,   304,   300,     0,   297,   301,
     302,   284,     0,   280,   283,   673,     0,   670,   628,     0,
     624,   625,   328,     0,   324,   325,     0,     0,     0,     0,
       0,     0,     0,   344,   347,   348,   349,   350,   351,   352,
     711,   717,     0,     0,     0,   710,   707,   708,   709,     0,
     699,   702,   705,   703,   704,   706,     0,     0,     0,   317,
       0,   309,   312,   313,   314,   315,   316,   732,   734,   731,
     729,   730,     0,   724,   727,   728,     0,   748,     0,   751,
     744,   745,     0,   738,   741,   742,   743,   746,     0,   821,
       0,   818,     0,   864,     0,   860,   863,    55,   569,     0,
     565,   566,   596,     0,   592,   593,   666,   665,     0,   664,
       0,    64,   805,   183,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   218,   204,   206,     0,   208,   213,
       0,   360,   365,   502,   490,   497,   541,   531,   536,     0,
     438,   443,   290,   287,   306,   299,   296,     0,   282,   279,
     675,   672,   669,   632,   622,   627,     0,   322,   327,     0,
       0,     0,     0,     0,     0,   346,   343,     0,     0,     0,
       0,     0,   701,   698,     0,     0,     0,   311,   308,     0,
       0,   726,   723,     0,     0,     0,     0,   740,   737,   754,
       0,   820,   817,     0,   862,   859,    57,     0,    56,     0,
     563,   568,     0,   590,   595,     0,   663,   814,     0,     0,
       0,     0,   252,   255,   256,   257,   258,   259,   260,   261,
     269,   262,     0,   268,     0,     0,     0,     0,   217,     0,
     212,     0,   364,     0,   496,     0,   535,   488,   463,   464,
     465,   467,   468,   469,   453,   454,   472,   473,   474,   475,
     476,   479,   480,   481,   482,   483,   484,   485,   486,   477,
     478,   487,   449,   450,   451,   452,   461,   462,   458,   459,
     460,   457,   466,     0,   446,   455,   470,   471,   456,   442,
     289,   298,     0,   281,   694,     0,   692,   686,   687,   688,
     689,   690,   691,   693,   683,   684,   685,     0,   676,   677,
     680,   681,   682,   671,     0,   626,     0,   326,   353,   354,
     355,   356,   357,   358,   345,     0,     0,   716,   719,   720,
     700,   318,   319,   320,   310,     0,     0,   725,   747,     0,
     750,     0,   739,   836,     0,   834,   832,   826,   830,   831,
       0,   823,   828,   829,   827,   819,   865,   861,    54,    59,
       0,   567,     0,   594,     0,   243,   244,   245,   242,   247,
     249,   251,   265,   266,   267,   264,   271,   273,   275,   277,
     215,   367,   499,   538,   448,   445,   285,     0,     0,   674,
     679,   629,   329,   713,   714,   715,   712,   718,   733,   735,
     749,   752,     0,     0,     0,   825,   822,    58,   570,   597,
     667,   447,     0,   696,   678,     0,   833,     0,   824,   695,
       0,   835,   841,     0,   838,     0,   840,   837,   851,     0,
       0,     0,   856,     0,   843,   846,   847,   848,   849,   850,
     839,     0,     0,     0,     0,     0,   845,   842,     0,   853,
     854,   855,     0,   844,   852,   857
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   -10, -1005,  -583, -1005,
     193, -1005, -1005, -1005, -1005,   360, -1005,  -632, -1005, -1005,
   -1005,   -71, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   399,
     615, -1005, -1005,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19, -1005,    34,    37,    38,
      41, -1005,   409,    49, -1005,    52, -1005,    54,    55,    56,
   -1005,    59, -1005,    62, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   400,   611, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
     318, -1005,   109, -1005,  -712,   115, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   -45, -1005,  -748, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,    89, -1005, -1005, -1005, -1005, -1005,    98,  -731,
   -1005, -1005, -1005, -1005,    96, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005,    65, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
      85, -1005, -1005, -1005,    88,   572, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,    82, -1005, -1005, -1005, -1005, -1005, -1005,
   -1004, -1005, -1005, -1005,   114, -1005, -1005, -1005,   118,   614,
   -1005, -1005, -1002, -1005, -1001, -1005,    73, -1005,    75, -1005,
      66,    69,    70,    72, -1005, -1005, -1005, -1000, -1005, -1005,
   -1005, -1005,   111, -1005, -1005,  -121,  1067, -1005, -1005, -1005,
   -1005, -1005,   122, -1005, -1005, -1005,   127, -1005,   599, -1005,
     -67, -1005, -1005, -1005, -1005, -1005,   -64, -1005, -1005, -1005,
   -1005, -1005,     4, -1005, -1005, -1005,   121, -1005, -1005, -1005,
     129, -1005,   610, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005,    84, -1005, -1005, -1005,    90,   635,
   -1005, -1005,   -55, -1005,   -12, -1005, -1005, -1005, -1005, -1005,
      77, -1005, -1005, -1005,    86,   638, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   -60, -1005, -1005, -1005,   132, -1005, -1005,
   -1005,   138, -1005,   639,   405, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,  -998, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005,   135, -1005, -1005, -1005,
     -98, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   123, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,   103, -1005, -1005, -1005, -1005, -1005, -1005, -1005,   117,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
     420,   607, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005,   466,   608, -1005, -1005, -1005, -1005, -1005, -1005,    99,
   -1005, -1005,   -99, -1005, -1005, -1005, -1005, -1005, -1005,  -118,
   -1005, -1005,  -136, -1005, -1005, -1005, -1005, -1005, -1005, -1005,
   -1005, -1005, -1005,   105, -1005
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     744,    87,    88,    41,    68,    84,    85,   769,   977,  1087,
    1088,   832,    43,    70,    90,   438,    91,    45,    71,   158,
     159,   160,   441,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   467,   736,   179,   468,   180,   469,   181,   182,   183,
     498,   184,   499,   185,   186,   187,   188,   461,   189,   190,
     191,   192,   193,   443,    47,    72,   230,   231,   232,   508,
     233,   234,   235,   236,   194,   444,   195,   445,   196,   446,
     858,   859,   860,  1017,   833,   834,   835,   994,  1248,   836,
     995,   837,   996,   838,   997,   839,   840,   548,   841,   842,
     843,   844,   845,   846,   847,   848,   849,  1008,  1255,   850,
     851,   852,  1010,   853,  1011,   854,  1012,   855,  1013,   197,
     487,   892,   893,   894,  1037,   198,   484,   879,   880,   881,
     882,   199,   486,   887,   888,   889,   890,   200,   485,   201,
     494,   940,   941,   942,   943,   944,   202,   490,   903,   904,
     905,  1046,    63,    80,   388,   389,   390,   561,   391,   562,
     203,   491,   912,   913,   914,   915,   916,   917,   918,   919,
     204,   473,   862,   863,   864,  1020,    49,    73,   274,   275,
     276,   517,   277,   518,   278,   519,   279,   523,   280,   522,
     205,   206,   207,   208,   480,   750,   285,   286,   209,   477,
     874,   875,   876,  1029,  1163,  1164,   210,   474,    57,    77,
     866,   867,   868,  1023,    59,    78,   353,   354,   355,   356,
     357,   358,   359,   547,   360,   551,   361,   550,   362,   363,
     552,   364,   211,   475,   870,   871,   872,  1026,    61,    79,
     374,   375,   376,   377,   378,   556,   379,   380,   381,   382,
     288,   515,   979,   980,   981,  1089,    51,    74,   299,   300,
     301,   527,   212,   478,   213,   479,   291,   516,   983,   984,
     985,  1092,    53,    75,   315,   316,   317,   530,   318,   319,
     532,   320,   321,   214,   489,   899,   900,   901,  1043,    55,
      76,   333,   334,   335,   336,   538,   337,   539,   338,   540,
     339,   541,   340,   542,   341,   543,   342,   537,   293,   524,
     988,   989,  1095,   215,   488,   896,   897,  1040,  1187,  1188,
    1189,  1190,  1191,  1267,  1192,   216,   492,   929,   930,   931,
    1057,  1276,   932,   933,  1058,   934,   935,   217,   218,   495,
     952,   953,   954,  1069,   955,  1070,   219,   496,   962,   963,
     964,   965,  1074,   966,   967,  1076,   220,   497,    65,    81,
     410,   411,   412,   413,   566,   414,   567,   415,   416,   569,
     417,   418,   419,   572,   801,   420,   573,   421,   422,   423,
     576,   424,   577,   425,   578,   426,   579,   221,   442,    67,
      82,   429,   430,   431,   582,   432,   222,   503,   970,   971,
    1080,  1230,  1231,  1232,  1233,  1284,  1234,  1282,  1303,  1304,
    1305,  1313,  1314,  1315,  1321,  1316,  1317,  1318,  1319,  1325,
     223,   504,   974,   975,   976
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     157,   229,   249,   295,   309,   329,    38,   351,   370,   387,
     407,   926,   372,   292,   256,   373,   856,   237,   289,   302,
     313,   331,   886,   365,   383,  1153,   408,  1154,  1155,  1162,
     250,  1168,   877,   352,   371,    31,   775,    32,   972,    33,
     129,   130,   257,   258,   743,   259,   260,   261,   781,   782,
     783,   385,   386,   156,   129,   130,   427,   428,   323,   251,
     238,   290,   303,   314,   332,   986,   366,   384,    30,   409,
     439,   731,   732,   733,   734,   440,    86,   287,   298,   312,
     330,    42,   506,   385,   386,   252,   513,   507,    44,   253,
     125,   514,   262,   254,   224,   225,   226,   227,   228,    46,
     525,   956,   957,   958,   344,   526,   255,   263,   735,    48,
     264,   265,   947,   948,   266,   528,   535,    50,   743,   878,
     529,   536,   267,   877,   884,   268,   885,   269,   270,   271,
     920,   156,   272,    52,  1032,   273,   563,  1033,   817,   281,
      89,   564,   282,   283,    54,   284,   580,   296,   310,   297,
     311,   581,   584,   506,    56,   959,   434,   585,   991,   345,
    1035,   346,   347,  1036,   433,   348,   349,   350,   584,   156,
      58,    92,    93,   992,    60,    94,   129,   130,   129,   130,
      62,    95,    96,    97,    64,   129,   130,   345,   367,   346,
     347,   368,   369,  1308,    66,   513,  1309,  1310,  1311,  1312,
     993,   799,   800,  1014,   129,   130,   129,   130,  1015,   435,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   936,
     937,   938,  1014,    34,    35,    36,    37,  1016,   127,   128,
     437,  1038,   921,   922,   923,   924,  1039,   436,   129,   130,
    1153,   447,  1154,  1155,  1162,   131,  1168,  1245,  1246,  1247,
     132,   133,   134,   135,   136,   137,   138,  1055,   139,  1252,
    1253,  1254,  1056,   140,    98,    99,   100,   101,   102,   103,
     448,   156,   141,   156,  1062,   142,  1067,   544,  1071,  1063,
     156,  1068,   143,  1072,   886,  1119,  1041,   545,   126,  1042,
     144,   145,   126,   345,   926,   146,   126,  1081,   147,   156,
    1082,   156,   148,   304,   305,   306,   307,   308,   129,   130,
    1077,   546,   129,   130,   580,  1078,   129,   130,  1306,  1079,
     449,  1307,   450,   149,   150,   151,   152,   153,   154,   246,
     451,   554,   247,  1084,  1174,  1175,   322,   155,  1085,  1273,
    1274,  1275,   323,   324,   325,   326,   327,   328,   452,  1014,
     555,   812,   453,   156,  1260,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   823,   824,   825,   826,   126,
     454,   455,   827,   828,   829,   830,   831,   456,   525,  1264,
     563,  1285,   294,  1261,  1265,  1272,  1286,   457,   345,   129,
     130,   906,   907,   908,   909,   910,   911,   528,   535,   559,
     458,   459,  1288,  1289,   586,   587,   345,   129,   130,  1326,
     246,   460,   462,   247,  1327,   157,   746,   747,   748,   749,
     463,   464,   229,   156,   465,   466,   470,   156,   471,   472,
     476,   156,   604,   481,   249,   482,   483,   295,   237,   493,
     500,   501,   502,   505,   309,   292,   256,   509,   510,   511,
     289,   512,   520,   302,   329,   521,   531,   533,   534,   549,
     313,   553,   250,   557,   351,   558,   560,   596,   565,   370,
     331,   568,   570,   372,   257,   258,   373,   259,   260,   261,
     365,   238,   571,   574,   575,   383,   583,   588,   589,   407,
     352,   251,   590,   290,   591,   371,   303,   592,  1223,   593,
    1224,  1225,   594,   314,   156,   408,   595,   597,   610,   287,
     598,   599,   298,   332,   600,   601,   602,   252,   603,   312,
     605,   253,   156,   366,   262,   254,   129,   130,   384,   330,
     613,   616,   606,   617,   607,   608,   609,   618,   255,   263,
     156,   614,   264,   265,   615,   611,   266,   612,   409,   622,
     619,   620,   621,   623,   267,   624,   625,   268,   626,   269,
     270,   271,   627,   628,   272,   629,   630,   273,   631,   632,
     633,   281,   634,   635,   282,   283,   636,   284,   637,   638,
     639,   296,   640,   297,   641,   642,   643,   644,   310,   645,
     311,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   646,   647,   648,   652,   649,   650,
     653,   405,   406,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   651,   655,   656,
     661,   657,   157,   658,   662,   229,   663,   659,   664,   665,
     668,   156,   669,   667,   666,   670,   672,   674,   675,   694,
     676,   237,   680,   681,   677,   678,   682,   683,   684,   685,
     686,   688,   689,   690,   691,   692,   693,   696,   925,   939,
     949,   700,   407,   701,   697,   704,   973,   705,   698,   707,
     706,   703,   710,   708,   927,   945,   950,   960,   408,   709,
     711,   714,   808,   712,   238,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   713,   715,
     716,   717,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   719,   720,   126,   722,   723,   724,   928,   946,   951,
     961,   409,   725,   726,   727,   239,   728,   240,   730,   729,
     739,   737,   740,   129,   130,   241,   242,   243,   244,   245,
     131,   738,   741,   742,   745,   132,   133,   134,    32,   751,
     752,   753,   755,   764,   246,   754,   756,   247,   140,   757,
     758,   802,   759,   760,   761,   248,   762,   763,   765,   766,
     767,   768,   770,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   771,   772,   807,   773,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     774,   126,   345,   777,   857,   861,   865,   776,   778,   869,
     779,   780,   784,   785,   786,   787,   788,   789,   149,   150,
     790,   129,   130,   791,   242,   243,   792,   245,   131,   873,
     793,   794,   796,   132,   133,   134,   797,   891,   895,   898,
     798,   902,   246,   804,   969,   247,   978,   805,   156,   982,
     806,   998,   999,   248,  1000,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1009,  1019,   795,  1018,  1022,  1021,  1024,  1025,
    1027,  1028,  1031,  1030,  1102,  1045,  1034,  1044,  1048,  1047,
    1049,  1050,  1051,  1052,  1053,  1054,  1059,  1060,  1061,  1064,
    1065,  1066,  1073,  1075,  1083,  1086,  1091,  1090,  1093,  1094,
    1103,  1097,  1096,  1098,  1099,  1100,   149,   150,  1101,  1105,
    1112,  1114,  1104,  1106,  1107,  1108,  1109,  1110,  1111,   249,
    1113,  1115,   351,  1116,  1117,   370,  1172,  1198,  1127,   372,
     292,   256,   373,  1205,  1206,   289,   156,  1211,   365,  1176,
    1134,   383,   329,  1199,  1166,   387,  1200,   250,   352,  1201,
    1202,   371,  1215,  1203,  1152,  1185,  1128,  1207,   331,   257,
     258,   925,   259,   260,   261,  1183,   939,  1177,  1135,  1136,
     949,  1137,  1138,  1139,  1216,  1208,   251,   927,   290,  1226,
    1219,   366,   945,   973,   384,  1129,   950,  1167,   295,  1209,
    1212,   309,   960,  1213,   287,  1228,  1178,  1221,  1186,  1220,
    1218,   332,   252,  1165,   302,  1227,   253,   313,  1236,   262,
     254,  1130,  1238,  1239,  1184,  1131,  1244,   330,  1140,  1132,
     928,  1249,  1179,   255,   263,   946,  1180,   264,   265,   951,
    1181,   266,  1133,  1141,  1250,   961,  1142,  1143,  1229,   267,
    1144,  1251,   268,  1182,   269,   270,   271,   303,  1145,   272,
     314,  1146,   273,  1147,  1148,  1149,   281,  1256,  1150,   282,
     283,  1151,   284,   298,  1262,  1158,   312,  1263,  1159,  1160,
    1268,  1161,  1156,  1269,  1157,  1270,  1271,  1283,  1257,  1292,
    1295,  1297,   883,  1300,  1322,  1323,  1302,  1258,  1324,  1328,
    1332,   654,   809,   803,   660,   990,   811,  1173,  1120,  1118,
    1170,  1171,  1214,  1197,  1196,   702,  1122,  1204,  1121,   671,
    1259,  1266,  1169,  1291,   343,  1277,  1278,  1124,  1279,  1126,
    1123,  1280,  1287,  1290,   695,  1125,  1296,  1293,  1299,  1301,
    1329,  1334,   296,   673,   297,   310,  1335,   311,  1330,  1331,
     699,  1243,  1294,   679,  1217,  1241,  1193,  1195,  1242,  1240,
    1235,  1194,   987,   968,   687,  1210,  1298,   718,  1320,  1237,
    1333,   810,   721,  1127,  1222,     0,     0,     0,     0,  1176,
       0,     0,     0,     0,     0,  1134,     0,     0,     0,  1166,
       0,  1281,     0,     0,  1226,  1185,     0,     0,     0,  1152,
       0,  1128,     0,     0,     0,  1183,     0,  1177,     0,     0,
    1228,     0,     0,  1135,  1136,     0,  1137,  1138,  1139,     0,
    1227,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1129,     0,  1167,     0,     0,     0,  1178,     0,  1186,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1165,     0,
       0,     0,     0,  1229,  1184,     0,  1130,     0,     0,     0,
    1131,     0,  1179,  1140,  1132,     0,  1180,     0,     0,     0,
    1181,     0,     0,     0,     0,     0,     0,  1133,  1141,     0,
       0,  1142,  1143,  1182,     0,  1144,     0,     0,     0,     0,
       0,     0,     0,  1145,     0,     0,  1146,     0,  1147,  1148,
    1149,     0,     0,  1150,     0,     0,  1151,     0,     0,     0,
    1158,     0,     0,  1159,  1160,     0,  1161,  1156,     0,  1157
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   759,    79,    73,    73,    79,   728,    72,    73,    74,
      75,    76,   753,    78,    79,  1029,    81,  1029,  1029,  1029,
      73,  1029,   126,    78,    79,     5,   668,     7,   198,     9,
      98,    99,    73,    73,   627,    73,    73,    73,   680,   681,
     682,   133,   134,   213,    98,    99,    13,    14,   124,    73,
      72,    73,    74,    75,    76,   131,    78,    79,     0,    81,
       3,   179,   180,   181,   182,     8,   213,    73,    74,    75,
      76,     7,     3,   133,   134,    73,     3,     8,     7,    73,
      77,     8,    73,    73,    16,    17,    18,    19,    20,     7,
       3,   159,   160,   161,    24,     8,    73,    73,   216,     7,
      73,    73,   156,   157,    73,     3,     3,     7,   701,   213,
       8,     8,    73,   126,   127,    73,   129,    73,    73,    73,
      24,   213,    73,     7,     3,    73,     3,     6,    32,    73,
      10,     8,    73,    73,     7,    73,     3,    74,    75,    74,
      75,     8,     3,     3,     7,   213,     3,     8,     8,    79,
       3,    81,    82,     6,     6,    85,    86,    87,     3,   213,
       7,    11,    12,     8,     7,    15,    98,    99,    98,    99,
       7,    21,    22,    23,     7,    98,    99,    79,    80,    81,
      82,    83,    84,   190,     7,     3,   193,   194,   195,   196,
       8,   176,   177,     3,    98,    99,    98,    99,     8,     4,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,   152,
     153,   154,     3,   213,   214,   215,   216,     8,    88,    89,
       3,     3,   146,   147,   148,   149,     8,     8,    98,    99,
    1264,     4,  1264,  1264,  1264,   105,  1264,    25,    26,    27,
     110,   111,   112,   113,   114,   115,   116,     3,   118,    42,
      43,    44,     8,   123,    50,    51,    52,    53,    54,    55,
       4,   213,   132,   213,     3,   135,     3,     8,     3,     8,
     213,     8,   142,     8,  1035,  1017,     3,     3,    78,     6,
     150,   151,    78,    79,  1062,   155,    78,     3,   158,   213,
       6,   213,   162,    93,    94,    95,    96,    97,    98,    99,
       3,     8,    98,    99,     3,     8,    98,    99,     3,     8,
       4,     6,     4,   183,   184,   185,   186,   187,   188,   119,
       4,     8,   122,     3,   120,   121,   118,   197,     8,   143,
     144,   145,   124,   125,   126,   127,   128,   129,     4,     3,
       3,    24,     4,   213,     8,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    78,
       4,     4,    45,    46,    47,    48,    49,     4,     3,     3,
       3,     3,    91,     8,     8,     8,     8,     4,    79,    98,
      99,   136,   137,   138,   139,   140,   141,     3,     3,     8,
       4,     4,     8,     8,   434,   435,    79,    98,    99,     3,
     119,     4,     4,   122,     8,   506,   106,   107,   108,   109,
       4,     4,   513,   213,     4,     4,     4,   213,     4,     4,
       4,   213,   216,     4,   525,     4,     4,   528,   513,     4,
       4,     4,     4,     4,   535,   525,   525,     4,     4,     4,
     525,     4,     4,   528,   545,     4,     4,     4,     4,     4,
     535,     4,   525,     4,   555,     4,     3,   214,     4,   560,
     545,     4,     4,   560,   525,   525,   560,   525,   525,   525,
     555,   513,     4,     4,     4,   560,     4,   213,     4,   580,
     555,   525,     4,   525,     4,   560,   528,     4,   189,     4,
     191,   192,     4,   535,   213,   580,     4,   214,     4,   525,
     214,   214,   528,   545,   214,   214,   214,   525,   214,   535,
     215,   525,   213,   555,   525,   525,    98,    99,   560,   545,
     216,     4,   215,     4,   215,   214,   214,     4,   525,   525,
     213,   216,   525,   525,   216,   214,   525,   214,   580,     4,
     216,   216,   216,     4,   525,     4,   214,   525,     4,   525,
     525,   525,     4,     4,   525,     4,   216,   525,   216,   216,
       4,   525,     4,     4,   525,   525,     4,   525,     4,     4,
       4,   528,     4,   528,     4,   214,     4,     4,   535,     4,
     535,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     4,     4,     4,     4,   216,   216,
       4,   183,   184,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   216,     4,   216,
       4,   216,   723,   214,     4,   726,     4,   214,     4,     4,
       4,   213,     4,   216,   214,     4,     4,     4,   214,   216,
       4,   726,     4,     4,   214,   214,     4,     4,     4,     4,
       4,     4,     4,   214,     4,     4,     4,     4,   759,   760,
     761,     4,   763,     4,   216,     4,   767,     4,   216,     4,
     214,   216,     4,   214,   759,   760,   761,   762,   763,   214,
       4,     4,   722,   216,   726,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,   216,     4,
       4,     4,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     4,   214,    78,     4,     7,   213,   759,   760,   761,
     762,   763,     7,     7,     7,    90,     7,    92,   213,     5,
       5,   213,     5,    98,    99,   100,   101,   102,   103,   104,
     105,   213,     5,     5,   213,   110,   111,   112,     7,     5,
       5,     5,     5,   213,   119,     7,     5,   122,   123,     5,
       7,   178,     7,     7,     7,   130,     7,     7,   213,     5,
       7,     5,     5,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     5,   213,     5,   213,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     213,    78,    79,     7,     7,     7,     7,   213,   213,     7,
     213,   213,   213,   213,   213,   213,   213,   213,   183,   184,
     213,    98,    99,   213,   101,   102,   213,   104,   105,     7,
     213,   213,   213,   110,   111,   112,   213,   117,     7,     7,
     213,     7,   119,   213,     7,   122,     7,   213,   213,     7,
     213,     4,     4,   130,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   701,     6,     3,     6,     6,     3,
       6,     3,     3,     6,   214,     3,     6,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   213,     3,     6,     6,     3,
     216,     6,     8,     4,     4,     4,   183,   184,     4,   216,
       4,     4,   214,   214,   214,   214,   214,   214,   214,  1020,
     214,     4,  1023,     4,     4,  1026,     4,   214,  1029,  1026,
    1020,  1020,  1026,     4,     4,  1020,   213,   216,  1023,  1040,
    1029,  1026,  1043,   214,  1029,  1046,   214,  1020,  1023,   214,
     214,  1026,     4,   214,  1029,  1040,  1029,   214,  1043,  1020,
    1020,  1062,  1020,  1020,  1020,  1040,  1067,  1040,  1029,  1029,
    1071,  1029,  1029,  1029,     4,   214,  1020,  1062,  1020,  1080,
       4,  1023,  1067,  1084,  1026,  1029,  1071,  1029,  1089,   214,
     214,  1092,  1077,   214,  1020,  1080,  1040,     4,  1040,   214,
     216,  1043,  1020,  1029,  1089,  1080,  1020,  1092,   216,  1020,
    1020,  1029,     6,     3,  1040,  1029,     4,  1043,  1029,  1029,
    1062,   213,  1040,  1020,  1020,  1067,  1040,  1020,  1020,  1071,
    1040,  1020,  1029,  1029,   213,  1077,  1029,  1029,  1080,  1020,
    1029,   213,  1020,  1040,  1020,  1020,  1020,  1089,  1029,  1020,
    1092,  1029,  1020,  1029,  1029,  1029,  1020,   213,  1029,  1020,
    1020,  1029,  1020,  1089,     8,  1029,  1092,     8,  1029,  1029,
       4,  1029,  1029,     8,  1029,     3,     8,     4,   213,     4,
       4,     4,   752,     5,     4,     4,     7,   213,     4,     4,
       4,   506,   723,   714,   513,   807,   726,  1038,  1019,  1014,
    1032,  1035,  1067,  1048,  1046,   563,  1022,  1055,  1020,   525,
     213,   213,  1031,  1264,    77,   213,   213,  1025,   213,  1028,
    1023,   213,   213,   213,   555,  1026,   214,   216,   213,   213,
     216,   213,  1089,   528,  1089,  1092,   213,  1092,   214,   214,
     560,  1094,  1270,   535,  1071,  1091,  1041,  1045,  1092,  1089,
    1081,  1043,   777,   763,   545,  1062,  1285,   580,  1306,  1084,
    1326,   725,   584,  1264,  1077,    -1,    -1,    -1,    -1,  1270,
      -1,    -1,    -1,    -1,    -1,  1264,    -1,    -1,    -1,  1264,
      -1,  1221,    -1,    -1,  1285,  1270,    -1,    -1,    -1,  1264,
      -1,  1264,    -1,    -1,    -1,  1270,    -1,  1270,    -1,    -1,
    1285,    -1,    -1,  1264,  1264,    -1,  1264,  1264,  1264,    -1,
    1285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1264,    -1,  1264,    -1,    -1,    -1,  1270,    -1,  1270,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1264,    -1,
      -1,    -1,    -1,  1285,  1270,    -1,  1264,    -1,    -1,    -1,
    1264,    -1,  1270,  1264,  1264,    -1,  1270,    -1,    -1,    -1,
    1270,    -1,    -1,    -1,    -1,    -1,    -1,  1264,  1264,    -1,
      -1,  1264,  1264,  1270,    -1,  1264,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1264,    -1,    -1,  1264,    -1,  1264,  1264,
    1264,    -1,    -1,  1264,    -1,    -1,  1264,    -1,    -1,    -1,
    1264,    -1,    -1,  1264,  1264,    -1,  1264,  1264,    -1,  1264
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
       0,     5,     7,     9,   213,   214,   215,   216,   233,   234,
     235,   240,     7,   249,     7,   254,     7,   301,     7,   413,
       7,   493,     7,   509,     7,   526,     7,   445,     7,   451,
       7,   475,     7,   389,     7,   595,     7,   626,   241,   236,
     250,   255,   302,   414,   494,   510,   527,   446,   452,   476,
     390,   596,   627,   233,   242,   243,   213,   238,   239,    10,
     251,   253,    11,    12,    15,    21,    22,    23,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    88,    89,    98,
      99,   105,   110,   111,   112,   113,   114,   115,   116,   118,
     123,   132,   135,   142,   150,   151,   155,   158,   162,   183,
     184,   185,   186,   187,   188,   197,   213,   248,   256,   257,
     258,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   280,
     282,   284,   285,   286,   288,   290,   291,   292,   293,   295,
     296,   297,   298,   299,   311,   313,   315,   356,   362,   368,
     374,   376,   383,   397,   407,   427,   428,   429,   430,   435,
     443,   469,   499,   501,   520,   550,   562,   574,   575,   583,
     593,   624,   633,   657,    16,    17,    18,    19,    20,   248,
     303,   304,   305,   307,   308,   309,   310,   499,   501,    90,
      92,   100,   101,   102,   103,   104,   119,   122,   130,   248,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   274,   275,   276,   277,   280,   282,   284,
     285,   286,   288,   290,   415,   416,   417,   419,   421,   423,
     425,   427,   428,   429,   430,   433,   434,   469,   487,   499,
     501,   503,   520,   545,    91,   248,   423,   425,   469,   495,
     496,   497,   499,   501,    93,    94,    95,    96,    97,   248,
     423,   425,   469,   499,   501,   511,   512,   513,   515,   516,
     518,   519,   118,   124,   125,   126,   127,   128,   129,   248,
     469,   499,   501,   528,   529,   530,   531,   533,   535,   537,
     539,   541,   543,   443,    24,    79,    81,    82,    85,    86,
      87,   248,   333,   453,   454,   455,   456,   457,   458,   459,
     461,   463,   465,   466,   468,   499,   501,    80,    83,    84,
     248,   333,   457,   463,   477,   478,   479,   480,   481,   483,
     484,   485,   486,   499,   501,   133,   134,   248,   391,   392,
     393,   395,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   183,   184,   248,   499,   501,
     597,   598,   599,   600,   602,   604,   605,   607,   608,   609,
     612,   614,   615,   616,   618,   620,   622,    13,    14,   628,
     629,   630,   632,     6,     3,     4,     8,     3,   252,     3,
       8,   259,   625,   300,   312,   314,   316,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   294,     4,     4,     4,     4,     4,   278,   281,   283,
       4,     4,     4,   408,   444,   470,     4,   436,   500,   502,
     431,     4,     4,     4,   363,   375,   369,   357,   551,   521,
     384,   398,   563,     4,   377,   576,   584,   594,   287,   289,
       4,     4,     4,   634,   658,     4,     3,     8,   306,     4,
       4,     4,     4,     3,     8,   488,   504,   418,   420,   422,
       4,     4,   426,   424,   546,     3,     8,   498,     3,     8,
     514,     4,   517,     4,     4,     3,     8,   544,   532,   534,
     536,   538,   540,   542,     8,     3,     8,   460,   334,     4,
     464,   462,   467,     4,     8,     3,   482,     4,     4,     8,
       3,   394,   396,     3,     8,     4,   601,   603,     4,   606,
       4,     4,   610,   613,     4,     4,   617,   619,   621,   623,
       3,     8,   631,     4,     3,     8,   233,   233,   213,     4,
       4,     4,     4,     4,     4,     4,   214,   214,   214,   214,
     214,   214,   214,   214,   216,   215,   215,   215,   214,   214,
       4,   214,   214,   216,   216,   216,     4,     4,     4,   216,
     216,   216,     4,     4,     4,   214,     4,     4,     4,     4,
     216,   216,   216,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   214,     4,     4,     4,     4,     4,     4,   216,
     216,   216,     4,     4,   257,     4,   216,   216,   214,   214,
     304,     4,     4,     4,     4,     4,   214,   216,     4,     4,
       4,   416,     4,   496,     4,   214,     4,   214,   214,   512,
       4,     4,     4,     4,     4,     4,     4,   530,     4,     4,
     214,     4,     4,     4,   216,   455,     4,   216,   216,   479,
       4,     4,   392,   216,     4,     4,   214,     4,   214,   214,
       4,     4,   216,   216,     4,     4,     4,     4,   598,     4,
     214,   629,     4,     7,   213,     7,     7,     7,     7,     5,
     213,   179,   180,   181,   182,   216,   279,   213,   213,     5,
       5,     5,     5,   235,   237,   213,   106,   107,   108,   109,
     432,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   213,   213,     5,     7,     5,   244,
       5,     5,   213,   213,   213,   244,   213,     7,   213,   213,
     213,   244,   244,   244,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   237,   213,   213,   213,   176,
     177,   611,   178,   279,   213,   213,   213,     5,   233,   256,
     628,   303,    24,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    45,    46,    47,
      48,    49,   248,   321,   322,   323,   326,   328,   330,   332,
     333,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     346,   347,   348,   350,   352,   354,   321,     7,   317,   318,
     319,     7,   409,   410,   411,     7,   447,   448,   449,     7,
     471,   472,   473,     7,   437,   438,   439,   126,   213,   364,
     365,   366,   367,   242,   127,   129,   366,   370,   371,   372,
     373,   117,   358,   359,   360,     7,   552,   553,     7,   522,
     523,   524,     7,   385,   386,   387,   136,   137,   138,   139,
     140,   141,   399,   400,   401,   402,   403,   404,   405,   406,
      24,   146,   147,   148,   149,   248,   335,   499,   501,   564,
     565,   566,   569,   570,   572,   573,   152,   153,   154,   248,
     378,   379,   380,   381,   382,   499,   501,   156,   157,   248,
     499,   501,   577,   578,   579,   581,   159,   160,   161,   213,
     499,   501,   585,   586,   587,   588,   590,   591,   597,     7,
     635,   636,   198,   248,   659,   660,   661,   245,     7,   489,
     490,   491,     7,   505,   506,   507,   131,   531,   547,   548,
     317,     8,     8,     8,   324,   327,   329,   331,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   344,     4,
     349,   351,   353,   355,     3,     8,     8,   320,     6,     3,
     412,     6,     3,   450,     6,     3,   474,     6,     3,   440,
       6,     3,     3,     6,     6,     3,     6,   361,     3,     8,
     554,     3,     6,   525,     6,     3,   388,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   567,   571,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   580,
     582,     3,     8,     4,   589,     4,   592,     3,     8,     8,
     637,     3,     6,     4,     3,     8,   213,   246,   247,   492,
       6,     3,   508,     6,     3,   549,     8,     6,     4,     4,
       4,     4,   214,   216,   214,   216,   214,   214,   214,   214,
     214,   214,     4,   214,     4,     4,     4,     4,   322,   321,
     319,   415,   411,   453,   449,   477,   473,   248,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   274,   275,   276,   277,   280,   282,   284,   285,   286,
     288,   290,   333,   407,   419,   421,   423,   425,   427,   428,
     429,   430,   434,   441,   442,   469,   499,   501,   545,   439,
     365,   371,     4,   359,   120,   121,   248,   260,   261,   262,
     263,   264,   265,   333,   469,   499,   501,   555,   556,   557,
     558,   559,   561,   553,   528,   524,   391,   387,   214,   214,
     214,   214,   214,   214,   400,     4,     4,   214,   214,   214,
     565,   216,   214,   214,   379,     4,     4,   578,   216,     4,
     214,     4,   586,   189,   191,   192,   248,   333,   499,   501,
     638,   639,   640,   641,   643,   636,   216,   660,     6,     3,
     495,   491,   511,   507,     4,    25,    26,    27,   325,   213,
     213,   213,    42,    43,    44,   345,   213,   213,   213,   213,
       8,     8,     8,     8,     3,     8,   213,   560,     4,     8,
       3,     8,     8,   143,   144,   145,   568,   213,   213,   213,
     213,   233,   644,     4,   642,     3,     8,   213,     8,     8,
     213,   442,     4,   216,   557,     4,   214,     4,   639,   213,
       5,   213,     7,   645,   646,   647,     3,     6,   190,   193,
     194,   195,   196,   648,   649,   650,   652,   653,   654,   655,
     646,   651,     4,     4,     4,   656,     3,     8,     4,   216,
     214,   214,     4,   649,   213,   213
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   217,   219,   218,   220,   218,   221,   218,   222,   218,
     223,   218,   224,   218,   225,   218,   226,   218,   227,   218,
     228,   218,   229,   218,   230,   218,   231,   218,   232,   218,
     233,   233,   233,   233,   233,   233,   233,   234,   236,   235,
     237,   238,   238,   239,   239,   239,   241,   240,   242,   242,
     243,   243,   243,   245,   244,   246,   246,   247,   247,   247,
     248,   250,   249,   252,   251,   251,   253,   255,   254,   256,
     256,   256,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   259,   258,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   278,   277,   279,   279,
     279,   279,   279,   281,   280,   283,   282,   284,   285,   287,
     286,   289,   288,   290,   291,   292,   294,   293,   295,   296,
     297,   298,   300,   299,   302,   301,   303,   303,   303,   304,
     304,   304,   304,   304,   304,   304,   304,   306,   305,   307,
     308,   309,   310,   312,   311,   314,   313,   316,   315,   317,
     317,   318,   318,   318,   320,   319,   321,   321,   321,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   322,   322,   322,   322,   322,   322,   322,   322,   322,
     322,   324,   323,   325,   325,   325,   327,   326,   329,   328,
     331,   330,   332,   334,   333,   335,   336,   337,   338,   339,
     340,   341,   342,   344,   343,   345,   345,   345,   346,   347,
     349,   348,   351,   350,   353,   352,   355,   354,   357,   356,
     358,   358,   358,   359,   361,   360,   363,   362,   364,   364,
     364,   365,   365,   366,   367,   369,   368,   370,   370,   370,
     371,   371,   371,   372,   373,   375,   374,   377,   376,   378,
     378,   378,   379,   379,   379,   379,   379,   379,   380,   381,
     382,   384,   383,   385,   385,   386,   386,   386,   388,   387,
     390,   389,   391,   391,   391,   391,   392,   392,   394,   393,
     396,   395,   398,   397,   399,   399,   399,   400,   400,   400,
     400,   400,   400,   401,   402,   403,   404,   405,   406,   408,
     407,   409,   409,   410,   410,   410,   412,   411,   414,   413,
     415,   415,   415,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   418,   417,   420,   419,
     422,   421,   424,   423,   426,   425,   427,   428,   429,   431,
     430,   432,   432,   432,   432,   433,   434,   436,   435,   437,
     437,   438,   438,   438,   440,   439,   441,   441,   441,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   444,
     443,   446,   445,   447,   447,   448,   448,   448,   450,   449,
     452,   451,   453,   453,   454,   454,   454,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   456,   457,   458,
     460,   459,   462,   461,   464,   463,   465,   467,   466,   468,
     470,   469,   471,   471,   472,   472,   472,   474,   473,   476,
     475,   477,   477,   478,   478,   478,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   480,   482,   481,   483,   484,
     485,   486,   488,   487,   489,   489,   490,   490,   490,   492,
     491,   494,   493,   495,   495,   495,   496,   496,   496,   496,
     496,   496,   496,   498,   497,   500,   499,   502,   501,   504,
     503,   505,   505,   506,   506,   506,   508,   507,   510,   509,
     511,   511,   511,   512,   512,   512,   512,   512,   512,   512,
     512,   512,   512,   512,   514,   513,   515,   517,   516,   518,
     519,   521,   520,   522,   522,   523,   523,   523,   525,   524,
     527,   526,   528,   528,   529,   529,   529,   530,   530,   530,
     530,   530,   530,   530,   530,   530,   530,   530,   532,   531,
     534,   533,   536,   535,   538,   537,   540,   539,   542,   541,
     544,   543,   546,   545,   547,   547,   549,   548,   551,   550,
     552,   552,   552,   554,   553,   555,   555,   556,   556,   556,
     557,   557,   557,   557,   557,   557,   557,   557,   557,   557,
     557,   557,   557,   558,   560,   559,   561,   563,   562,   564,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     1,
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
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
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
  "$@30", "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@31", "hosts_database", "$@32", "hosts_databases",
  "$@33", "database_list", "not_empty_database_list", "database", "$@34",
  "database_map_params", "database_map_param", "database_type", "$@35",
  "db_type", "user", "$@36", "password", "$@37", "host", "$@38", "port",
  "name", "$@39", "persist", "lfc_interval", "readonly", "connect_timeout",
  "read_timeout", "write_timeout", "tcp_user_timeout",
  "reconnect_wait_time", "on_fail", "$@40", "on_fail_mode",
  "max_row_errors", "max_reconnect_tries", "trust_anchor", "$@41",
  "cert_file", "$@42", "key_file", "$@43", "cipher_list", "$@44",
  "sanity_checks", "$@45", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@46", "mac_sources", "$@47", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@49",
  "dhcp_multi_threading", "$@50", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@51", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@52",
  "sub_hooks_library", "$@53", "hooks_params", "hooks_param", "library",
  "$@54", "parameters", "$@55", "expired_leases_processing", "$@56",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@57",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@58",
  "sub_subnet6", "$@59", "subnet6_params", "subnet6_param", "subnet",
  "$@60", "interface", "$@61", "interface_id", "$@62", "client_class",
  "$@63", "require_client_classes", "$@64", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@65", "hr_mode", "id", "rapid_commit", "shared_networks", "$@66",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@67", "shared_network_params", "shared_network_param",
  "option_def_list", "$@68", "sub_option_def_list", "$@69",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@70", "sub_option_def", "$@71",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@72",
  "option_def_record_types", "$@73", "space", "$@74", "option_def_space",
  "option_def_encapsulate", "$@75", "option_def_array", "option_data_list",
  "$@76", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@77", "sub_option_data", "$@78",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@79",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@80", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@81", "sub_pool6", "$@82",
  "pool_params", "pool_param", "pool_entry", "$@83", "user_context",
  "$@84", "comment", "$@85", "pd_pools_list", "$@86",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@87", "sub_pd_pool", "$@88", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@89", "pd_prefix_len", "excluded_prefix", "$@90",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@91",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@92", "sub_reservation", "$@93", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@94", "prefixes", "$@95", "duid", "$@96", "hw_address", "$@97",
  "hostname", "$@98", "flex_id_value", "$@99",
  "reservation_client_classes", "$@100", "relay", "$@101", "relay_map",
  "ip_address", "$@102", "client_classes", "$@103", "client_classes_list",
  "client_class_entry", "$@104", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@105", "only_if_required",
  "server_id", "$@106", "server_id_params", "server_id_param",
  "server_id_type", "$@107", "duid_type", "htype", "identifier", "$@108",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@109",
  "control_socket_params", "control_socket_param", "socket_type", "$@110",
  "socket_name", "$@111", "dhcp_queue_control", "$@112",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@113", "capacity", "arbitrary_map_entry", "$@114",
  "dhcp_ddns", "$@115", "sub_dhcp_ddns", "$@116", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@117",
  "server_ip", "$@118", "server_port", "sender_ip", "$@119", "sender_port",
  "max_queue_size", "ncr_protocol", "$@120", "ncr_protocol_value",
  "ncr_format", "$@121", "dep_override_no_update",
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
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   305,   305,   305,   306,   306,   307,   307,   308,   308,
     309,   309,   310,   310,   311,   311,   312,   312,   313,   313,
     314,   314,   315,   315,   316,   316,   317,   317,   318,   318,
     326,   327,   328,   329,   330,   331,   332,   335,   340,   340,
     351,   354,   355,   358,   363,   369,   374,   374,   381,   382,
     385,   389,   393,   399,   399,   406,   407,   410,   414,   418,
     428,   437,   437,   452,   452,   466,   469,   475,   475,   484,
     485,   486,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   560,   560,   569,
     575,   581,   587,   593,   599,   605,   611,   617,   623,   629,
     635,   641,   647,   653,   659,   665,   671,   671,   680,   683,
     686,   689,   692,   698,   698,   707,   707,   716,   722,   728,
     728,   737,   737,   746,   752,   758,   764,   764,   773,   779,
     785,   791,   797,   797,   809,   809,   818,   819,   820,   825,
     826,   827,   828,   829,   830,   831,   832,   835,   835,   846,
     852,   858,   864,   870,   870,   883,   883,   896,   896,   907,
     908,   911,   912,   913,   918,   918,   928,   929,   930,   935,
     936,   937,   938,   939,   940,   941,   942,   943,   944,   945,
     946,   947,   948,   949,   950,   951,   952,   953,   954,   955,
     956,   959,   959,   967,   968,   969,   972,   972,   981,   981,
     990,   990,   999,  1005,  1005,  1014,  1020,  1026,  1032,  1038,
    1044,  1050,  1057,  1063,  1063,  1071,  1072,  1073,  1076,  1082,
    1088,  1088,  1097,  1097,  1106,  1106,  1115,  1115,  1124,  1124,
    1135,  1136,  1137,  1142,  1144,  1144,  1163,  1163,  1174,  1175,
    1176,  1181,  1182,  1185,  1190,  1195,  1195,  1206,  1207,  1208,
    1213,  1214,  1215,  1218,  1223,  1230,  1230,  1243,  1243,  1256,
    1257,  1258,  1263,  1264,  1265,  1266,  1267,  1268,  1271,  1277,
    1283,  1289,  1289,  1300,  1301,  1304,  1305,  1306,  1311,  1311,
    1321,  1321,  1331,  1332,  1333,  1336,  1339,  1340,  1343,  1343,
    1352,  1352,  1361,  1361,  1373,  1374,  1375,  1380,  1381,  1382,
    1383,  1384,  1385,  1388,  1394,  1400,  1406,  1412,  1418,  1427,
    1427,  1441,  1442,  1445,  1446,  1447,  1456,  1456,  1482,  1482,
    1493,  1494,  1495,  1501,  1502,  1503,  1504,  1505,  1506,  1507,
    1508,  1509,  1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,
    1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,
    1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,
    1538,  1539,  1540,  1541,  1542,  1543,  1546,  1546,  1555,  1555,
    1564,  1564,  1573,  1573,  1582,  1582,  1593,  1599,  1605,  1611,
    1611,  1619,  1620,  1621,  1622,  1625,  1631,  1639,  1639,  1651,
    1652,  1656,  1657,  1658,  1663,  1663,  1671,  1672,  1673,  1678,
    1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,
    1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,
    1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,
    1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1724,
    1724,  1738,  1738,  1747,  1748,  1751,  1752,  1753,  1760,  1760,
    1775,  1775,  1789,  1790,  1793,  1794,  1795,  1800,  1801,  1802,
    1803,  1804,  1805,  1806,  1807,  1808,  1809,  1812,  1814,  1820,
    1822,  1822,  1831,  1831,  1840,  1840,  1849,  1851,  1851,  1860,
    1870,  1870,  1883,  1884,  1889,  1890,  1891,  1898,  1898,  1910,
    1910,  1922,  1923,  1928,  1929,  1930,  1937,  1938,  1939,  1940,
    1941,  1942,  1943,  1944,  1945,  1948,  1950,  1950,  1959,  1961,
    1963,  1969,  1978,  1978,  1991,  1992,  1995,  1996,  1997,  2002,
    2002,  2012,  2012,  2022,  2023,  2024,  2029,  2030,  2031,  2032,
    2033,  2034,  2035,  2038,  2038,  2047,  2047,  2072,  2072,  2102,
    2102,  2115,  2116,  2119,  2120,  2121,  2126,  2126,  2138,  2138,
    2150,  2151,  2152,  2157,  2158,  2159,  2160,  2161,  2162,  2163,
    2164,  2165,  2166,  2167,  2170,  2170,  2179,  2185,  2185,  2194,
    2200,  2209,  2209,  2220,  2221,  2224,  2225,  2226,  2231,  2231,
    2240,  2240,  2249,  2250,  2253,  2254,  2255,  2261,  2262,  2263,
    2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,  2274,  2274,
    2285,  2285,  2296,  2296,  2305,  2305,  2314,  2314,  2323,  2323,
    2332,  2332,  2346,  2346,  2357,  2358,  2361,  2361,  2373,  2373,
    2384,  2385,  2386,  2391,  2391,  2401,  2402,  2405,  2406,  2407,
    2412,  2413,  2414,  2415,  2416,  2417,  2418,  2419,  2420,  2421,
    2422,  2423,  2424,  2427,  2429,  2429,  2438,  2447,  2447,  2460,
    2461,  2462,  2467,  2468,  2469,  2470,  2471,  2472,  2473,  2474,
    2475,  2478,  2478,  2486,  2487,  2488,  2491,  2497,  2497,  2506,
    2512,  2520,  2528,  2528,  2539,  2540,  2541,  2546,  2547,  2548,
    2549,  2550,  2553,  2553,  2562,  2562,  2574,  2574,  2587,  2588,
    2589,  2594,  2595,  2596,  2597,  2598,  2599,  2602,  2608,  2608,
    2617,  2623,  2623,  2633,  2633,  2646,  2646,  2656,  2657,  2658,
    2663,  2664,  2665,  2666,  2667,  2668,  2669,  2670,  2671,  2672,
    2673,  2674,  2675,  2676,  2677,  2678,  2679,  2680,  2683,  2690,
    2690,  2699,  2699,  2708,  2714,  2714,  2723,  2729,  2735,  2735,
    2744,  2745,  2748,  2748,  2758,  2765,  2772,  2772,  2781,  2781,
    2791,  2791,  2801,  2801,  2813,  2813,  2825,  2825,  2835,  2836,
    2837,  2843,  2844,  2847,  2847,  2858,  2866,  2866,  2879,  2880,
    2881,  2887,  2887,  2895,  2896,  2897,  2902,  2903,  2904,  2905,
    2906,  2907,  2908,  2911,  2917,  2917,  2926,  2926,  2937,  2938,
    2939,  2944,  2944,  2952,  2953,  2954,  2959,  2960,  2961,  2962,
    2963,  2966,  2966,  2975,  2981,  2987,  2993,  2993,  3002,  3002,
    3013,  3014,  3015,  3020,  3021,  3024
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
#line 6390 "dhcp6_parser.cc"

#line 3030 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
