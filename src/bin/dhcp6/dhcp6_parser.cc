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

  case 135: // $@21: %empty
#line 558 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 136: // data_directory: "data-directory" $@21 ":" "constant string"
#line 561 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 137: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 567 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 138: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 573 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 139: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 579 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 140: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 585 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 141: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 591 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 142: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 143: // renew_timer: "renew-timer" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 144: // rebind_timer: "rebind-timer" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 145: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 615 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 146: // t1_percent: "t1-percent" ":" "floating point"
#line 621 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 147: // t2_percent: "t2-percent" ":" "floating point"
#line 627 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 148: // cache_threshold: "cache-threshold" ":" "floating point"
#line 633 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 149: // cache_max_age: "cache-max-age" ":" "integer"
#line 639 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 150: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 645 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 151: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 651 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 152: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 657 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 153: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 663 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 154: // $@22: %empty
#line 669 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 155: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 672 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "when-present"
#line 678 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "never"
#line 681 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "always"
#line 684 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-not-present"
#line 687 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "boolean"
#line 690 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 161: // $@23: %empty
#line 696 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 162: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 699 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 163: // $@24: %empty
#line 705 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 164: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 708 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 165: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 714 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 166: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 720 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 167: // $@25: %empty
#line 726 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 168: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 729 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 169: // $@26: %empty
#line 735 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 738 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 171: // store_extended_info: "store-extended-info" ":" "boolean"
#line 744 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 172: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 750 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 173: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 756 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 174: // $@27: %empty
#line 762 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 175: // server_tag: "server-tag" $@27 ":" "constant string"
#line 765 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 176: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 771 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 177: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 777 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 178: // $@28: %empty
#line 783 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 179: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 789 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 180: // $@29: %empty
#line 795 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 181: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 799 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 184: // interfaces_config_params: interfaces_config_params ","
#line 806 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1578 "dhcp6_parser.cc"
    break;

  case 190: // $@30: %empty
#line 818 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 191: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 824 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 192: // re_detect: "re-detect" ":" "boolean"
#line 829 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 193: // $@31: %empty
#line 835 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 194: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 841 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1632 "dhcp6_parser.cc"
    break;

  case 195: // $@32: %empty
#line 848 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1644 "dhcp6_parser.cc"
    break;

  case 196: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 854 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1655 "dhcp6_parser.cc"
    break;

  case 197: // $@33: %empty
#line 861 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 198: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 867 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp6_parser.cc"
    break;

  case 203: // not_empty_database_list: not_empty_database_list ","
#line 878 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1684 "dhcp6_parser.cc"
    break;

  case 204: // $@34: %empty
#line 883 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp6_parser.cc"
    break;

  case 205: // database: "{" $@34 database_map_params "}"
#line 887 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1704 "dhcp6_parser.cc"
    break;

  case 208: // database_map_params: database_map_params ","
#line 895 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1712 "dhcp6_parser.cc"
    break;

  case 235: // $@35: %empty
#line 928 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1721 "dhcp6_parser.cc"
    break;

  case 236: // database_type: "type" $@35 ":" db_type
#line 931 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1730 "dhcp6_parser.cc"
    break;

  case 237: // db_type: "memfile"
#line 936 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1736 "dhcp6_parser.cc"
    break;

  case 238: // db_type: "mysql"
#line 937 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1742 "dhcp6_parser.cc"
    break;

  case 239: // db_type: "postgresql"
#line 938 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp6_parser.cc"
    break;

  case 240: // db_type: "cql"
#line 939 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp6_parser.cc"
    break;

  case 241: // $@36: %empty
#line 942 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1763 "dhcp6_parser.cc"
    break;

  case 242: // user: "user" $@36 ":" "constant string"
#line 945 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1773 "dhcp6_parser.cc"
    break;

  case 243: // $@37: %empty
#line 951 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 244: // password: "password" $@37 ":" "constant string"
#line 954 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 245: // $@38: %empty
#line 960 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "dhcp6_parser.cc"
    break;

  case 246: // host: "host" $@38 ":" "constant string"
#line 963 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc"
    break;

  case 247: // port: "port" ":" "integer"
#line 969 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1821 "dhcp6_parser.cc"
    break;

  case 248: // $@39: %empty
#line 975 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1830 "dhcp6_parser.cc"
    break;

  case 249: // name: "name" $@39 ":" "constant string"
#line 978 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1840 "dhcp6_parser.cc"
    break;

  case 250: // persist: "persist" ":" "boolean"
#line 984 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1850 "dhcp6_parser.cc"
    break;

  case 251: // lfc_interval: "lfc-interval" ":" "integer"
#line 990 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1860 "dhcp6_parser.cc"
    break;

  case 252: // readonly: "readonly" ":" "boolean"
#line 996 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 253: // connect_timeout: "connect-timeout" ":" "integer"
#line 1002 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1880 "dhcp6_parser.cc"
    break;

  case 254: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1008 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1890 "dhcp6_parser.cc"
    break;

  case 255: // $@40: %empty
#line 1014 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 256: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1017 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1908 "dhcp6_parser.cc"
    break;

  case 257: // on_fail_mode: "stop-retry-exit"
#line 1022 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1914 "dhcp6_parser.cc"
    break;

  case 258: // on_fail_mode: "serve-retry-exit"
#line 1023 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1920 "dhcp6_parser.cc"
    break;

  case 259: // on_fail_mode: "serve-retry-continue"
#line 1024 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1926 "dhcp6_parser.cc"
    break;

  case 260: // max_row_errors: "max-row-errors" ":" "integer"
#line 1027 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 261: // request_timeout: "request-timeout" ":" "integer"
#line 1033 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 262: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1039 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 263: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1045 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 264: // $@41: %empty
#line 1051 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 265: // contact_points: "contact-points" $@41 ":" "constant string"
#line 1054 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 266: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1060 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 267: // $@42: %empty
#line 1066 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2004 "dhcp6_parser.cc"
    break;

  case 268: // keyspace: "keyspace" $@42 ":" "constant string"
#line 1069 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2014 "dhcp6_parser.cc"
    break;

  case 269: // $@43: %empty
#line 1075 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2023 "dhcp6_parser.cc"
    break;

  case 270: // consistency: "consistency" $@43 ":" "constant string"
#line 1078 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2033 "dhcp6_parser.cc"
    break;

  case 271: // $@44: %empty
#line 1084 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2042 "dhcp6_parser.cc"
    break;

  case 272: // serial_consistency: "serial-consistency" $@44 ":" "constant string"
#line 1087 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 273: // $@45: %empty
#line 1093 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 274: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1096 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 275: // $@46: %empty
#line 1102 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2080 "dhcp6_parser.cc"
    break;

  case 276: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1105 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2090 "dhcp6_parser.cc"
    break;

  case 277: // $@47: %empty
#line 1111 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp6_parser.cc"
    break;

  case 278: // key_file: "key-file" $@47 ":" "constant string"
#line 1114 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2109 "dhcp6_parser.cc"
    break;

  case 279: // $@48: %empty
#line 1120 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp6_parser.cc"
    break;

  case 280: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1123 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 281: // $@49: %empty
#line 1129 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2140 "dhcp6_parser.cc"
    break;

  case 282: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1135 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2149 "dhcp6_parser.cc"
    break;

  case 285: // sanity_checks_params: sanity_checks_params ","
#line 1142 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2157 "dhcp6_parser.cc"
    break;

  case 287: // $@50: %empty
#line 1149 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp6_parser.cc"
    break;

  case 288: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1152 "dhcp6_parser.yy"
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
#line 2186 "dhcp6_parser.cc"
    break;

  case 289: // $@51: %empty
#line 1168 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2198 "dhcp6_parser.cc"
    break;

  case 290: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1174 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2207 "dhcp6_parser.cc"
    break;

  case 293: // mac_sources_list: mac_sources_list ","
#line 1181 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2215 "dhcp6_parser.cc"
    break;

  case 296: // duid_id: "duid"
#line 1190 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2224 "dhcp6_parser.cc"
    break;

  case 297: // string_id: "constant string"
#line 1195 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2233 "dhcp6_parser.cc"
    break;

  case 298: // $@52: %empty
#line 1200 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 299: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1206 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc"
    break;

  case 302: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1213 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2262 "dhcp6_parser.cc"
    break;

  case 306: // hw_address_id: "hw-address"
#line 1223 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2271 "dhcp6_parser.cc"
    break;

  case 307: // flex_id: "flex-id"
#line 1228 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2280 "dhcp6_parser.cc"
    break;

  case 308: // $@53: %empty
#line 1235 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2292 "dhcp6_parser.cc"
    break;

  case 309: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1241 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp6_parser.cc"
    break;

  case 310: // $@54: %empty
#line 1248 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2313 "dhcp6_parser.cc"
    break;

  case 311: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1254 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 314: // multi_threading_params: multi_threading_params ","
#line 1263 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2332 "dhcp6_parser.cc"
    break;

  case 321: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1276 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2342 "dhcp6_parser.cc"
    break;

  case 322: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1282 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2352 "dhcp6_parser.cc"
    break;

  case 323: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1288 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 324: // $@55: %empty
#line 1294 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2374 "dhcp6_parser.cc"
    break;

  case 325: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1300 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2383 "dhcp6_parser.cc"
    break;

  case 330: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1311 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2391 "dhcp6_parser.cc"
    break;

  case 331: // $@56: %empty
#line 1316 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2401 "dhcp6_parser.cc"
    break;

  case 332: // hooks_library: "{" $@56 hooks_params "}"
#line 1320 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 333: // $@57: %empty
#line 1326 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2421 "dhcp6_parser.cc"
    break;

  case 334: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1330 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 337: // hooks_params: hooks_params ","
#line 1338 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2439 "dhcp6_parser.cc"
    break;

  case 341: // $@58: %empty
#line 1348 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 342: // library: "library" $@58 ":" "constant string"
#line 1351 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc"
    break;

  case 343: // $@59: %empty
#line 1357 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp6_parser.cc"
    break;

  case 344: // parameters: "parameters" $@59 ":" map_value
#line 1360 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 345: // $@60: %empty
#line 1366 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2488 "dhcp6_parser.cc"
    break;

  case 346: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1372 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 349: // expired_leases_params: expired_leases_params ","
#line 1380 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2506 "dhcp6_parser.cc"
    break;

  case 356: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1393 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2516 "dhcp6_parser.cc"
    break;

  case 357: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1399 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2526 "dhcp6_parser.cc"
    break;

  case 358: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1405 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 359: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1411 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 360: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1417 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2556 "dhcp6_parser.cc"
    break;

  case 361: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1423 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 362: // $@61: %empty
#line 1432 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 363: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1438 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2587 "dhcp6_parser.cc"
    break;

  case 368: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1452 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2595 "dhcp6_parser.cc"
    break;

  case 369: // $@62: %empty
#line 1461 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 370: // subnet6: "{" $@62 subnet6_params "}"
#line 1465 "dhcp6_parser.yy"
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
#line 2631 "dhcp6_parser.cc"
    break;

  case 371: // $@63: %empty
#line 1487 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2641 "dhcp6_parser.cc"
    break;

  case 372: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1491 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2651 "dhcp6_parser.cc"
    break;

  case 375: // subnet6_params: subnet6_params ","
#line 1500 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2659 "dhcp6_parser.cc"
    break;

  case 419: // $@64: %empty
#line 1551 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2668 "dhcp6_parser.cc"
    break;

  case 420: // subnet: "subnet" $@64 ":" "constant string"
#line 1554 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2678 "dhcp6_parser.cc"
    break;

  case 421: // $@65: %empty
#line 1560 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp6_parser.cc"
    break;

  case 422: // interface: "interface" $@65 ":" "constant string"
#line 1563 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 423: // $@66: %empty
#line 1569 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2706 "dhcp6_parser.cc"
    break;

  case 424: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1572 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2716 "dhcp6_parser.cc"
    break;

  case 425: // $@67: %empty
#line 1578 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 426: // client_class: "client-class" $@67 ":" "constant string"
#line 1581 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 427: // $@68: %empty
#line 1587 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 428: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1593 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2756 "dhcp6_parser.cc"
    break;

  case 429: // reservations_global: "reservations-global" ":" "boolean"
#line 1598 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 430: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1604 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 431: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1610 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 432: // $@69: %empty
#line 1616 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 433: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1619 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 434: // hr_mode: "disabled"
#line 1624 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2810 "dhcp6_parser.cc"
    break;

  case 435: // hr_mode: "out-of-pool"
#line 1625 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2816 "dhcp6_parser.cc"
    break;

  case 436: // hr_mode: "global"
#line 1626 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2822 "dhcp6_parser.cc"
    break;

  case 437: // hr_mode: "all"
#line 1627 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2828 "dhcp6_parser.cc"
    break;

  case 438: // id: "id" ":" "integer"
#line 1630 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 439: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1636 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2848 "dhcp6_parser.cc"
    break;

  case 440: // $@70: %empty
#line 1644 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2860 "dhcp6_parser.cc"
    break;

  case 441: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1650 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc"
    break;

  case 446: // shared_networks_list: shared_networks_list ","
#line 1663 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2877 "dhcp6_parser.cc"
    break;

  case 447: // $@71: %empty
#line 1668 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2887 "dhcp6_parser.cc"
    break;

  case 448: // shared_network: "{" $@71 shared_network_params "}"
#line 1672 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 451: // shared_network_params: shared_network_params ","
#line 1678 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2903 "dhcp6_parser.cc"
    break;

  case 492: // $@72: %empty
#line 1729 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 493: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1735 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 494: // $@73: %empty
#line 1743 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 495: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1746 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 500: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1758 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2949 "dhcp6_parser.cc"
    break;

  case 501: // $@74: %empty
#line 1765 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2959 "dhcp6_parser.cc"
    break;

  case 502: // option_def_entry: "{" $@74 option_def_params "}"
#line 1769 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2971 "dhcp6_parser.cc"
    break;

  case 503: // $@75: %empty
#line 1780 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 504: // sub_option_def: "{" $@75 option_def_params "}"
#line 1784 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 509: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1800 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3001 "dhcp6_parser.cc"
    break;

  case 521: // code: "code" ":" "integer"
#line 1819 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 523: // $@76: %empty
#line 1827 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp6_parser.cc"
    break;

  case 524: // option_def_type: "type" $@76 ":" "constant string"
#line 1830 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3030 "dhcp6_parser.cc"
    break;

  case 525: // $@77: %empty
#line 1836 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3039 "dhcp6_parser.cc"
    break;

  case 526: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1839 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3049 "dhcp6_parser.cc"
    break;

  case 527: // $@78: %empty
#line 1845 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3058 "dhcp6_parser.cc"
    break;

  case 528: // space: "space" $@78 ":" "constant string"
#line 1848 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3068 "dhcp6_parser.cc"
    break;

  case 530: // $@79: %empty
#line 1856 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3077 "dhcp6_parser.cc"
    break;

  case 531: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1859 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 532: // option_def_array: "array" ":" "boolean"
#line 1865 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3097 "dhcp6_parser.cc"
    break;

  case 533: // $@80: %empty
#line 1875 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 534: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1881 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3118 "dhcp6_parser.cc"
    break;

  case 539: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1896 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3126 "dhcp6_parser.cc"
    break;

  case 540: // $@81: %empty
#line 1903 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3136 "dhcp6_parser.cc"
    break;

  case 541: // option_data_entry: "{" $@81 option_data_params "}"
#line 1907 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3145 "dhcp6_parser.cc"
    break;

  case 542: // $@82: %empty
#line 1915 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3155 "dhcp6_parser.cc"
    break;

  case 543: // sub_option_data: "{" $@82 option_data_params "}"
#line 1919 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3164 "dhcp6_parser.cc"
    break;

  case 548: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1935 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3172 "dhcp6_parser.cc"
    break;

  case 559: // $@83: %empty
#line 1955 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3181 "dhcp6_parser.cc"
    break;

  case 560: // option_data_data: "data" $@83 ":" "constant string"
#line 1958 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3191 "dhcp6_parser.cc"
    break;

  case 563: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1968 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 564: // option_data_always_send: "always-send" ":" "boolean"
#line 1974 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 565: // $@84: %empty
#line 1983 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3223 "dhcp6_parser.cc"
    break;

  case 566: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 1989 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3232 "dhcp6_parser.cc"
    break;

  case 571: // not_empty_pools_list: not_empty_pools_list ","
#line 2002 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3240 "dhcp6_parser.cc"
    break;

  case 572: // $@85: %empty
#line 2007 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3250 "dhcp6_parser.cc"
    break;

  case 573: // pool_list_entry: "{" $@85 pool_params "}"
#line 2011 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 574: // $@86: %empty
#line 2017 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3270 "dhcp6_parser.cc"
    break;

  case 575: // sub_pool6: "{" $@86 pool_params "}"
#line 2021 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3280 "dhcp6_parser.cc"
    break;

  case 578: // pool_params: pool_params ","
#line 2029 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3288 "dhcp6_parser.cc"
    break;

  case 586: // $@87: %empty
#line 2043 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp6_parser.cc"
    break;

  case 587: // pool_entry: "pool" $@87 ":" "constant string"
#line 2046 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3307 "dhcp6_parser.cc"
    break;

  case 588: // $@88: %empty
#line 2052 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 589: // user_context: "user-context" $@88 ":" map_value
#line 2054 "dhcp6_parser.yy"
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
#line 3342 "dhcp6_parser.cc"
    break;

  case 590: // $@89: %empty
#line 2077 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3350 "dhcp6_parser.cc"
    break;

  case 591: // comment: "comment" $@89 ":" "constant string"
#line 2079 "dhcp6_parser.yy"
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
#line 3379 "dhcp6_parser.cc"
    break;

  case 592: // $@90: %empty
#line 2107 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 593: // pd_pools_list: "pd-pools" $@90 ":" "[" pd_pools_list_content "]"
#line 2113 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3400 "dhcp6_parser.cc"
    break;

  case 598: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2126 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3408 "dhcp6_parser.cc"
    break;

  case 599: // $@91: %empty
#line 2131 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 600: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2135 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 601: // $@92: %empty
#line 2143 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3440 "dhcp6_parser.cc"
    break;

  case 602: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2147 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3452 "dhcp6_parser.cc"
    break;

  case 605: // pd_pool_params: pd_pool_params ","
#line 2157 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3460 "dhcp6_parser.cc"
    break;

  case 617: // $@93: %empty
#line 2175 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3469 "dhcp6_parser.cc"
    break;

  case 618: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2178 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 619: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2184 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3489 "dhcp6_parser.cc"
    break;

  case 620: // $@94: %empty
#line 2190 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 621: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2193 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 622: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2199 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 623: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2205 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 624: // $@95: %empty
#line 2214 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3540 "dhcp6_parser.cc"
    break;

  case 625: // reservations: "reservations" $@95 ":" "[" reservations_list "]"
#line 2220 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3549 "dhcp6_parser.cc"
    break;

  case 630: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2231 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3557 "dhcp6_parser.cc"
    break;

  case 631: // $@96: %empty
#line 2236 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 632: // reservation: "{" $@96 reservation_params "}"
#line 2240 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3576 "dhcp6_parser.cc"
    break;

  case 633: // $@97: %empty
#line 2245 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3586 "dhcp6_parser.cc"
    break;

  case 634: // sub_reservation: "{" $@97 reservation_params "}"
#line 2249 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 639: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2260 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3603 "dhcp6_parser.cc"
    break;

  case 651: // $@98: %empty
#line 2279 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3615 "dhcp6_parser.cc"
    break;

  case 652: // ip_addresses: "ip-addresses" $@98 ":" list_strings
#line 2285 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3624 "dhcp6_parser.cc"
    break;

  case 653: // $@99: %empty
#line 2290 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3636 "dhcp6_parser.cc"
    break;

  case 654: // prefixes: "prefixes" $@99 ":" list_strings
#line 2296 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3645 "dhcp6_parser.cc"
    break;

  case 655: // $@100: %empty
#line 2301 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3654 "dhcp6_parser.cc"
    break;

  case 656: // duid: "duid" $@100 ":" "constant string"
#line 2304 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3664 "dhcp6_parser.cc"
    break;

  case 657: // $@101: %empty
#line 2310 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3673 "dhcp6_parser.cc"
    break;

  case 658: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2313 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3683 "dhcp6_parser.cc"
    break;

  case 659: // $@102: %empty
#line 2319 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3692 "dhcp6_parser.cc"
    break;

  case 660: // hostname: "hostname" $@102 ":" "constant string"
#line 2322 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3702 "dhcp6_parser.cc"
    break;

  case 661: // $@103: %empty
#line 2328 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 662: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2331 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3721 "dhcp6_parser.cc"
    break;

  case 663: // $@104: %empty
#line 2337 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3733 "dhcp6_parser.cc"
    break;

  case 664: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2343 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3742 "dhcp6_parser.cc"
    break;

  case 665: // $@105: %empty
#line 2351 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3754 "dhcp6_parser.cc"
    break;

  case 666: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2357 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 669: // $@106: %empty
#line 2366 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 670: // ip_address: "ip-address" $@106 ":" "constant string"
#line 2369 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3782 "dhcp6_parser.cc"
    break;

  case 671: // $@107: %empty
#line 2378 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3794 "dhcp6_parser.cc"
    break;

  case 672: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2384 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 675: // client_classes_list: client_classes_list ","
#line 2391 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3811 "dhcp6_parser.cc"
    break;

  case 676: // $@108: %empty
#line 2396 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3821 "dhcp6_parser.cc"
    break;

  case 677: // client_class_entry: "{" $@108 client_class_params "}"
#line 2400 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 682: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2412 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3839 "dhcp6_parser.cc"
    break;

  case 697: // $@109: %empty
#line 2434 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 698: // client_class_test: "test" $@109 ":" "constant string"
#line 2437 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3858 "dhcp6_parser.cc"
    break;

  case 699: // only_if_required: "only-if-required" ":" "boolean"
#line 2443 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3868 "dhcp6_parser.cc"
    break;

  case 700: // $@110: %empty
#line 2452 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3880 "dhcp6_parser.cc"
    break;

  case 701: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2458 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3891 "dhcp6_parser.cc"
    break;

  case 704: // server_id_params: server_id_params ","
#line 2467 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3899 "dhcp6_parser.cc"
    break;

  case 714: // $@111: %empty
#line 2483 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3908 "dhcp6_parser.cc"
    break;

  case 715: // server_id_type: "type" $@111 ":" duid_type
#line 2486 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3917 "dhcp6_parser.cc"
    break;

  case 716: // duid_type: "LLT"
#line 2491 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3923 "dhcp6_parser.cc"
    break;

  case 717: // duid_type: "EN"
#line 2492 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3929 "dhcp6_parser.cc"
    break;

  case 718: // duid_type: "LL"
#line 2493 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3935 "dhcp6_parser.cc"
    break;

  case 719: // htype: "htype" ":" "integer"
#line 2496 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3945 "dhcp6_parser.cc"
    break;

  case 720: // $@112: %empty
#line 2502 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3954 "dhcp6_parser.cc"
    break;

  case 721: // identifier: "identifier" $@112 ":" "constant string"
#line 2505 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3964 "dhcp6_parser.cc"
    break;

  case 722: // time: "time" ":" "integer"
#line 2511 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 723: // enterprise_id: "enterprise-id" ":" "integer"
#line 2517 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 724: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2525 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3994 "dhcp6_parser.cc"
    break;

  case 725: // $@113: %empty
#line 2533 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4006 "dhcp6_parser.cc"
    break;

  case 726: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2539 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4015 "dhcp6_parser.cc"
    break;

  case 729: // control_socket_params: control_socket_params ","
#line 2546 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4023 "dhcp6_parser.cc"
    break;

  case 735: // $@114: %empty
#line 2558 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4032 "dhcp6_parser.cc"
    break;

  case 736: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2561 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4042 "dhcp6_parser.cc"
    break;

  case 737: // $@115: %empty
#line 2567 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4051 "dhcp6_parser.cc"
    break;

  case 738: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2570 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 739: // $@116: %empty
#line 2579 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4073 "dhcp6_parser.cc"
    break;

  case 740: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2585 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4084 "dhcp6_parser.cc"
    break;

  case 743: // queue_control_params: queue_control_params ","
#line 2594 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4092 "dhcp6_parser.cc"
    break;

  case 750: // enable_queue: "enable-queue" ":" "boolean"
#line 2607 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4102 "dhcp6_parser.cc"
    break;

  case 751: // $@117: %empty
#line 2613 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4111 "dhcp6_parser.cc"
    break;

  case 752: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2616 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4121 "dhcp6_parser.cc"
    break;

  case 753: // capacity: "capacity" ":" "integer"
#line 2622 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4131 "dhcp6_parser.cc"
    break;

  case 754: // $@118: %empty
#line 2628 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4140 "dhcp6_parser.cc"
    break;

  case 755: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2631 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4149 "dhcp6_parser.cc"
    break;

  case 756: // $@119: %empty
#line 2638 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4161 "dhcp6_parser.cc"
    break;

  case 757: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2644 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4172 "dhcp6_parser.cc"
    break;

  case 758: // $@120: %empty
#line 2651 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4182 "dhcp6_parser.cc"
    break;

  case 759: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2655 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4192 "dhcp6_parser.cc"
    break;

  case 762: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2663 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4200 "dhcp6_parser.cc"
    break;

  case 781: // enable_updates: "enable-updates" ":" "boolean"
#line 2688 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4210 "dhcp6_parser.cc"
    break;

  case 782: // $@121: %empty
#line 2695 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4219 "dhcp6_parser.cc"
    break;

  case 783: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2698 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4229 "dhcp6_parser.cc"
    break;

  case 784: // $@122: %empty
#line 2704 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4238 "dhcp6_parser.cc"
    break;

  case 785: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2707 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4248 "dhcp6_parser.cc"
    break;

  case 786: // server_port: "server-port" ":" "integer"
#line 2713 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4258 "dhcp6_parser.cc"
    break;

  case 787: // $@123: %empty
#line 2719 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4267 "dhcp6_parser.cc"
    break;

  case 788: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2722 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4277 "dhcp6_parser.cc"
    break;

  case 789: // sender_port: "sender-port" ":" "integer"
#line 2728 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4287 "dhcp6_parser.cc"
    break;

  case 790: // max_queue_size: "max-queue-size" ":" "integer"
#line 2734 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 791: // $@124: %empty
#line 2740 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4306 "dhcp6_parser.cc"
    break;

  case 792: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2743 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4315 "dhcp6_parser.cc"
    break;

  case 793: // ncr_protocol_value: "UDP"
#line 2749 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4321 "dhcp6_parser.cc"
    break;

  case 794: // ncr_protocol_value: "TCP"
#line 2750 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4327 "dhcp6_parser.cc"
    break;

  case 795: // $@125: %empty
#line 2753 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4336 "dhcp6_parser.cc"
    break;

  case 796: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2756 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4346 "dhcp6_parser.cc"
    break;

  case 797: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2763 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4356 "dhcp6_parser.cc"
    break;

  case 798: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2770 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 799: // $@126: %empty
#line 2777 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4375 "dhcp6_parser.cc"
    break;

  case 800: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2780 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4384 "dhcp6_parser.cc"
    break;

  case 801: // $@127: %empty
#line 2786 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4393 "dhcp6_parser.cc"
    break;

  case 802: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2789 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4403 "dhcp6_parser.cc"
    break;

  case 803: // $@128: %empty
#line 2796 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4412 "dhcp6_parser.cc"
    break;

  case 804: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2799 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 805: // $@129: %empty
#line 2806 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 806: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2809 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 807: // $@130: %empty
#line 2818 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4453 "dhcp6_parser.cc"
    break;

  case 808: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2824 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4463 "dhcp6_parser.cc"
    break;

  case 809: // $@131: %empty
#line 2830 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4473 "dhcp6_parser.cc"
    break;

  case 810: // sub_config_control: "{" $@131 config_control_params "}"
#line 2834 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4482 "dhcp6_parser.cc"
    break;

  case 813: // config_control_params: config_control_params ","
#line 2842 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4490 "dhcp6_parser.cc"
    break;

  case 816: // $@132: %empty
#line 2852 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4502 "dhcp6_parser.cc"
    break;

  case 817: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2858 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4511 "dhcp6_parser.cc"
    break;

  case 818: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2863 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4521 "dhcp6_parser.cc"
    break;

  case 819: // $@133: %empty
#line 2871 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4533 "dhcp6_parser.cc"
    break;

  case 820: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2877 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4542 "dhcp6_parser.cc"
    break;

  case 823: // loggers_entries: loggers_entries ","
#line 2886 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4550 "dhcp6_parser.cc"
    break;

  case 824: // $@134: %empty
#line 2892 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4560 "dhcp6_parser.cc"
    break;

  case 825: // logger_entry: "{" $@134 logger_params "}"
#line 2896 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4568 "dhcp6_parser.cc"
    break;

  case 828: // logger_params: logger_params ","
#line 2902 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4576 "dhcp6_parser.cc"
    break;

  case 836: // debuglevel: "debuglevel" ":" "integer"
#line 2916 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4586 "dhcp6_parser.cc"
    break;

  case 837: // $@135: %empty
#line 2922 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4595 "dhcp6_parser.cc"
    break;

  case 838: // severity: "severity" $@135 ":" "constant string"
#line 2925 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4605 "dhcp6_parser.cc"
    break;

  case 839: // $@136: %empty
#line 2931 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4617 "dhcp6_parser.cc"
    break;

  case 840: // output_options_list: "output_options" $@136 ":" "[" output_options_list_content "]"
#line 2937 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4626 "dhcp6_parser.cc"
    break;

  case 843: // output_options_list_content: output_options_list_content ","
#line 2944 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4634 "dhcp6_parser.cc"
    break;

  case 844: // $@137: %empty
#line 2949 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4644 "dhcp6_parser.cc"
    break;

  case 845: // output_entry: "{" $@137 output_params_list "}"
#line 2953 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4652 "dhcp6_parser.cc"
    break;

  case 848: // output_params_list: output_params_list ","
#line 2959 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4660 "dhcp6_parser.cc"
    break;

  case 854: // $@138: %empty
#line 2971 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4669 "dhcp6_parser.cc"
    break;

  case 855: // output: "output" $@138 ":" "constant string"
#line 2974 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4679 "dhcp6_parser.cc"
    break;

  case 856: // flush: "flush" ":" "boolean"
#line 2980 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4689 "dhcp6_parser.cc"
    break;

  case 857: // maxsize: "maxsize" ":" "integer"
#line 2986 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4699 "dhcp6_parser.cc"
    break;

  case 858: // maxver: "maxver" ":" "integer"
#line 2992 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 859: // $@139: %empty
#line 2998 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4718 "dhcp6_parser.cc"
    break;

  case 860: // pattern: "pattern" $@139 ":" "constant string"
#line 3001 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4728 "dhcp6_parser.cc"
    break;

  case 861: // $@140: %empty
#line 3007 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4740 "dhcp6_parser.cc"
    break;

  case 862: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3013 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4749 "dhcp6_parser.cc"
    break;

  case 865: // compatibility_params: compatibility_params ","
#line 3020 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4757 "dhcp6_parser.cc"
    break;

  case 868: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3029 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4767 "dhcp6_parser.cc"
    break;


#line 4771 "dhcp6_parser.cc"

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
     419,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,    32,    30,    47,    90,    98,
     105,   123,   131,   137,   139,   175,   176,   177,   232,   243,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,    30,  -172,
      84,   276,    36,   643,    40,   162,   278,   136,    15,   218,
     -87,   431,    61,  -997,   235,   251,   263,   258,   265,  -997,
      65,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   280,   286,
     309,   310,   321,   358,   359,   380,   391,   398,   399,   414,
     418,   428,  -997,   430,   433,   434,   437,   444,  -997,  -997,
    -997,   448,   449,   450,  -997,  -997,  -997,   452,  -997,  -997,
    -997,  -997,   453,   456,   462,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   464,  -997,  -997,  -997,  -997,  -997,
    -997,   466,  -997,  -997,   467,  -997,    68,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   468,  -997,    83,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   472,   473,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,    87,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   150,
    -997,  -997,  -997,  -997,  -997,   483,  -997,   484,   488,  -997,
    -997,  -997,  -997,  -997,  -997,   154,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   274,   320,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   353,  -997,  -997,   489,  -997,  -997,  -997,
     493,  -997,  -997,   427,   423,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   495,   498,
    -997,  -997,  -997,  -997,   496,   500,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   213,  -997,
    -997,  -997,   501,  -997,  -997,   502,  -997,   503,   505,  -997,
    -997,   507,   508,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     219,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   509,   244,
    -997,  -997,  -997,  -997,    30,    30,  -997,   306,   511,  -997,
    -997,   512,   516,   517,   519,   521,   523,   322,   323,   324,
     325,   326,   327,   328,   331,   330,   334,   335,   337,   340,
     341,   531,   342,   343,   344,   345,   347,   554,   563,   564,
     354,   355,   361,   569,   570,   571,   364,   577,   579,   580,
     581,   371,   373,   374,   587,   588,   590,   605,   606,   607,
     608,   609,   610,   401,   629,   630,   632,   633,   634,   635,
     424,   637,   638,  -997,   276,  -997,   639,   429,    36,  -997,
     642,   644,   645,   646,   648,   439,   438,   651,   652,   653,
     643,  -997,   654,    40,  -997,   655,   446,   657,   451,   457,
     162,  -997,   658,   659,   660,   662,   663,   669,   670,  -997,
     278,  -997,   671,   673,   465,   674,   676,   677,   474,  -997,
      15,   678,   475,   477,  -997,   218,   679,   685,   -48,  -997,
     492,   705,   706,   497,   717,   510,   518,   718,   721,   520,
     522,   722,   729,   735,   736,   431,  -997,   737,   528,    61,
    -997,  -997,  -997,   747,   640,   539,   727,   746,   751,   752,
     749,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   547,  -997,  -997,  -997,  -997,
    -997,    22,   548,   549,  -997,  -997,  -997,   758,   760,   761,
    -997,   764,   763,   558,   336,  -997,  -997,  -997,   767,   768,
     769,   770,   771,   773,   774,   788,   789,  -997,   790,   791,
     802,   805,   567,   568,  -997,   808,   807,  -997,   810,  -997,
    -997,   811,   812,   611,   612,   613,  -997,  -997,   810,   614,
     813,  -997,   619,  -997,   622,  -997,   625,  -997,  -997,  -997,
     810,   810,   810,   626,   627,   628,   636,  -997,   647,   650,
    -997,   656,   661,   664,  -997,  -997,   665,  -997,  -997,  -997,
     666,   763,  -997,  -997,   667,   668,  -997,   672,  -997,  -997,
     -19,   641,  -997,  -997,    22,   675,   680,   681,  -997,   814,
    -997,  -997,    30,   276,  -997,    61,    36,   144,   144,   815,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   816,
     838,   839,   840,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   -90,    30,    95,   699,   841,   843,   845,    91,    51,
       0,   -50,   -44,   431,  -997,  -997,   846,  -158,  -997,  -997,
     848,   850,  -997,  -997,  -997,  -997,  -997,   -68,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,   815,  -997,   262,
     271,   273,  -997,  -997,  -997,  -997,   854,   855,   857,   860,
     861,  -997,   862,   863,  -997,  -997,  -997,  -997,   864,   866,
     867,   868,  -997,  -997,  -997,  -997,  -997,   277,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   289,  -997,   869,   870,  -997,  -997,
     876,   873,  -997,  -997,   877,   881,  -997,  -997,   880,   884,
    -997,  -997,   883,   887,  -997,  -997,  -997,   118,  -997,  -997,
    -997,   885,  -997,  -997,  -997,   128,  -997,  -997,  -997,  -997,
     290,  -997,  -997,  -997,   234,  -997,  -997,   886,   892,  -997,
    -997,   890,   894,  -997,   895,   896,   897,   898,   899,   900,
     302,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     901,   902,   903,  -997,  -997,  -997,  -997,   303,  -997,  -997,
    -997,  -997,  -997,  -997,   904,   905,   906,  -997,   304,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     312,  -997,  -997,  -997,   907,  -997,   908,  -997,  -997,  -997,
     319,  -997,  -997,  -997,  -997,  -997,   356,  -997,   245,  -997,
     909,  -997,   357,  -997,  -997,   701,  -997,   911,   915,  -997,
    -997,   913,   917,  -997,  -997,  -997,   914,  -997,   918,  -997,
    -997,  -997,   919,   921,   922,   923,   684,   712,   707,   713,
     716,   927,   719,   720,   928,   931,   932,   933,   724,   725,
     726,   731,   936,   942,   944,   945,   144,  -997,  -997,   144,
    -997,   815,   643,  -997,   816,    15,  -997,   838,   218,  -997,
     839,   730,  -997,   840,   -90,  -997,  -997,    95,  -997,   951,
     699,  -997,   155,   841,  -997,   278,  -997,   843,   -87,  -997,
     845,   742,   744,   745,   754,   757,   765,    91,  -997,   961,
     968,   782,   783,   797,    51,  -997,   759,   798,   801,     0,
    -997,   970,   998,   -50,  -997,   803,  1017,   820,  1018,   -44,
    -997,  -997,   208,   846,  -997,   819,  -158,  -997,  -997,  1024,
    1035,    40,  -997,   848,   162,  -997,   850,  1039,  -997,  -997,
     348,   879,   882,   888,  -997,  -997,  -997,  -997,  -997,   889,
    -997,  -997,   158,   891,   893,   910,  -997,  -997,  -997,  -997,
     912,   916,   920,   924,  -997,   366,  -997,   377,  -997,  1048,
    -997,  1055,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   378,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   925,  -997,
    -997,  1075,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  1078,  1086,  -997,  -997,  -997,  -997,  -997,
    1089,  -997,   379,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,    21,   926,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   929,   930,  -997,  -997,   934,  -997,    30,  -997,  -997,
    1094,  -997,  -997,  -997,  -997,  -997,   408,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   935,   409,  -997,   416,  -997,
     937,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   730,  -997,  -997,  1095,   939,
    -997,   155,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  1096,   938,  1099,   208,  -997,  -997,  -997,
    -997,  -997,  -997,   940,  -997,  -997,  1100,  -997,   947,  -997,
    -997,  1101,  -997,  -997,   318,  -997,    24,  1101,  -997,  -997,
    1103,  1105,  1106,  -997,   422,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  1107,   946,   949,   950,  1108,    24,  -997,   948,
    -997,  -997,  -997,   952,  -997,  -997,  -997
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   180,     9,   371,    11,
     574,    13,   601,    15,   633,    17,   494,    19,   503,    21,
     542,    23,   333,    25,   758,    27,   809,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   635,     0,   505,   544,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   135,   807,   178,   193,   195,   197,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,     0,     0,     0,     0,     0,   154,   161,
     163,     0,     0,     0,   362,   492,   533,     0,   440,   588,
     590,   432,     0,     0,     0,   289,   308,   298,   281,   671,
     624,   324,   345,   700,     0,   310,   725,   739,   756,   167,
     169,     0,   819,   861,     0,   134,     0,    69,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   111,   112,   113,
     114,   115,    81,   119,   120,   121,   122,   123,   124,   125,
     126,   117,   118,   127,   128,   129,   106,   133,   131,    84,
      85,    86,    87,   103,    88,    90,    89,   130,    94,    95,
      82,   108,   109,   110,   107,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   116,   132,
     190,     0,   189,     0,   182,   185,   186,   187,   188,   565,
     592,   419,   421,   423,     0,     0,   427,   425,   665,   418,
     376,   377,   378,   379,   380,   381,   382,   383,   402,   403,
     404,   405,   406,   409,   410,   411,   412,   413,   414,   415,
     416,   407,   408,   417,     0,   373,   387,   388,   389,   392,
     393,   396,   397,   398,   395,   390,   391,   384,   385,   400,
     401,   386,   394,   399,   586,   585,   581,   582,   580,     0,
     576,   579,   583,   584,   617,     0,   620,     0,     0,   616,
     610,   611,   609,   614,   615,     0,   603,   606,   607,   612,
     613,   608,   663,   651,   653,   655,   657,   659,   661,   650,
     647,   648,   649,     0,   636,   637,   642,   643,   640,   644,
     645,   646,   641,     0,   523,   248,     0,   527,   525,   530,
       0,   519,   520,     0,   506,   507,   510,   522,   511,   512,
     513,   529,   514,   515,   516,   517,   518,   559,     0,     0,
     557,   558,   561,   562,     0,   545,   546,   549,   550,   551,
     552,   553,   554,   555,   556,   341,   343,   338,     0,   335,
     339,   340,     0,   782,   784,     0,   787,     0,     0,   791,
     795,     0,     0,   799,   801,   803,   805,   780,   778,   779,
       0,   760,   763,   775,   764,   765,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   776,   777,   816,     0,     0,
     811,   814,   815,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,   184,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     375,   372,     0,   578,   575,     0,     0,     0,     0,     0,
     605,   602,     0,     0,     0,     0,     0,     0,     0,   634,
     639,   495,     0,     0,     0,     0,     0,     0,     0,   504,
     509,     0,     0,     0,   543,   548,     0,     0,   337,   334,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   762,   759,     0,     0,   813,
     810,    51,    43,     0,     0,     0,     0,     0,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,     0,   172,   173,   151,   152,
     153,     0,     0,     0,   165,   166,   171,     0,     0,     0,
     176,     0,     0,     0,     0,   429,   430,   431,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   724,     0,     0,
       0,     0,     0,     0,   177,     0,     0,    70,     0,   192,
     183,     0,     0,     0,     0,     0,   438,   439,     0,     0,
       0,   374,     0,   577,     0,   619,     0,   622,   623,   604,
       0,     0,     0,     0,     0,     0,     0,   638,     0,     0,
     521,     0,     0,     0,   532,   508,     0,   563,   564,   547,
       0,     0,   336,   781,     0,     0,   786,     0,   789,   790,
       0,     0,   797,   798,     0,     0,     0,     0,   761,     0,
     818,   812,     0,     0,   136,     0,     0,     0,     0,   199,
     175,   156,   157,   158,   159,   160,   155,   162,   164,   364,
     496,   535,   442,    40,   589,   591,   434,   435,   436,   437,
     433,     0,    48,     0,     0,     0,   626,   326,     0,     0,
       0,     0,     0,     0,   168,   170,     0,     0,    53,   191,
     567,   594,   420,   422,   424,   428,   426,     0,   587,   618,
     621,   664,   652,   654,   656,   658,   660,   662,   524,   249,
     528,   526,   531,   560,   342,   344,   783,   785,   788,   793,
     794,   792,   796,   800,   802,   804,   806,   199,    44,     0,
       0,     0,   235,   241,   243,   245,     0,     0,     0,     0,
       0,   264,     0,     0,   255,   267,   269,   271,     0,     0,
       0,     0,   273,   275,   277,   279,   234,     0,   206,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   221,
     222,   229,   223,   224,   225,   219,   220,   226,   227,   228,
     230,   231,   232,   233,     0,   204,     0,   200,   201,   369,
       0,   365,   366,   501,     0,   497,   498,   540,     0,   536,
     537,   447,     0,   443,   444,   296,   297,     0,   291,   294,
     295,     0,   306,   307,   303,     0,   300,   304,   305,   287,
       0,   283,   286,   676,     0,   673,   631,     0,   627,   628,
     331,     0,   327,   328,     0,     0,     0,     0,     0,     0,
       0,   347,   350,   351,   352,   353,   354,   355,   714,   720,
       0,     0,     0,   713,   710,   711,   712,     0,   702,   705,
     708,   706,   707,   709,     0,     0,     0,   320,     0,   312,
     315,   316,   317,   318,   319,   735,   737,   734,   732,   733,
       0,   727,   730,   731,     0,   751,     0,   754,   747,   748,
       0,   741,   744,   745,   746,   749,     0,   824,     0,   821,
       0,   867,     0,   863,   866,    55,   572,     0,   568,   569,
     599,     0,   595,   596,   669,   668,     0,   667,     0,    64,
     808,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   208,   194,   196,     0,
     198,   203,     0,   363,   368,   505,   493,   500,   544,   534,
     539,     0,   441,   446,   293,   290,   309,   302,   299,     0,
     285,   282,   678,   675,   672,   635,   625,   630,     0,   325,
     330,     0,     0,     0,     0,     0,     0,   349,   346,     0,
       0,     0,     0,     0,   704,   701,     0,     0,     0,   314,
     311,     0,     0,   729,   726,     0,     0,     0,     0,   743,
     740,   757,     0,   823,   820,     0,   865,   862,    57,     0,
      56,     0,   566,   571,     0,   593,   598,     0,   666,   817,
       0,     0,     0,     0,   247,   250,   251,   252,   253,     0,
     266,   254,     0,     0,     0,     0,   261,   262,   263,   260,
       0,     0,     0,     0,   207,     0,   202,     0,   367,     0,
     499,     0,   538,   491,   466,   467,   468,   470,   471,   472,
     456,   457,   475,   476,   477,   478,   479,   482,   483,   484,
     485,   486,   487,   488,   489,   480,   481,   490,   452,   453,
     454,   455,   464,   465,   461,   462,   463,   460,   469,     0,
     449,   458,   473,   474,   459,   445,   292,   301,     0,   284,
     697,     0,   695,   689,   690,   691,   692,   693,   694,   696,
     686,   687,   688,     0,   679,   680,   683,   684,   685,   674,
       0,   629,     0,   329,   356,   357,   358,   359,   360,   361,
     348,     0,     0,   719,   722,   723,   703,   321,   322,   323,
     313,     0,     0,   728,   750,     0,   753,     0,   742,   839,
       0,   837,   835,   829,   833,   834,     0,   826,   831,   832,
     830,   822,   868,   864,    54,    59,     0,   570,     0,   597,
       0,   237,   238,   239,   240,   236,   242,   244,   246,   265,
     257,   258,   259,   256,   268,   270,   272,   274,   276,   278,
     280,   205,   370,   502,   541,   451,   448,   288,     0,     0,
     677,   682,   632,   332,   716,   717,   718,   715,   721,   736,
     738,   752,   755,     0,     0,     0,   828,   825,    58,   573,
     600,   670,   450,     0,   699,   681,     0,   836,     0,   827,
     698,     0,   838,   844,     0,   841,     0,   843,   840,   854,
       0,     0,     0,   859,     0,   846,   849,   850,   851,   852,
     853,   842,     0,     0,     0,     0,     0,   848,   845,     0,
     856,   857,   858,     0,   847,   855,   860
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   -10,  -997,  -568,  -997,
     432,  -997,  -997,  -997,  -997,   382,  -997,  -578,  -997,  -997,
    -997,   -71,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   412,
     623,  -997,  -997,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19,  -997,    34,    37,    38,
      41,  -997,   425,    49,  -997,    52,  -997,    54,    55,    56,
    -997,    59,  -997,    62,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   410,   620,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   333,  -997,   110,  -997,  -692,
     116,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   -45,  -997,  -728,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,    94,  -997,  -997,  -997,  -997,
    -997,   102,  -711,  -997,  -997,  -997,  -997,   100,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,    71,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,    88,  -997,  -997,  -997,    93,   584,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,    89,  -997,  -997,  -997,
    -997,  -997,  -997,  -996,  -997,  -997,  -997,   120,  -997,  -997,
    -997,   129,   682,  -997,  -997,  -994,  -997,  -993,  -997,    73,
    -997,    75,  -997,    66,    69,    70,    72,  -997,  -997,  -997,
    -992,  -997,  -997,  -997,  -997,   112,  -997,  -997,  -125,  1067,
    -997,  -997,  -997,  -997,  -997,   132,  -997,  -997,  -997,   130,
    -997,   618,  -997,   -67,  -997,  -997,  -997,  -997,  -997,   -64,
    -997,  -997,  -997,  -997,  -997,     4,  -997,  -997,  -997,   126,
    -997,  -997,  -997,   133,  -997,   621,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,    85,  -997,  -997,
    -997,    86,   683,  -997,  -997,   -55,  -997,   -12,  -997,  -997,
    -997,  -997,  -997,    92,  -997,  -997,  -997,    96,   649,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   -60,  -997,  -997,  -997,
     134,  -997,  -997,  -997,   135,  -997,   687,   415,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -990,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   140,
    -997,  -997,  -997,   -97,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   121,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   113,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   108,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   436,   616,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   478,   615,  -997,  -997,  -997,  -997,
    -997,  -997,   109,  -997,  -997,  -101,  -997,  -997,  -997,  -997,
    -997,  -997,  -121,  -997,  -997,  -140,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   114,  -997
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     724,    87,    88,    41,    68,    84,    85,   749,   965,  1079,
    1080,   816,    43,    70,    90,   428,    91,    45,    71,   156,
     157,   158,   431,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   457,   716,   177,   458,   178,   459,   179,   180,   181,
     488,   182,   489,   183,   184,   185,   186,   451,   187,   188,
     189,   433,    47,    72,   223,   224,   225,   496,   226,   190,
     434,   191,   435,   192,   436,   846,   847,   848,  1009,   817,
     818,   819,   982,  1245,   820,   983,   821,   984,   822,   985,
     823,   824,   533,   825,   826,   827,   828,   829,   830,   994,
    1253,   831,   832,   833,   834,   835,   991,   836,   837,   995,
     838,   996,   839,   997,   840,  1002,   841,  1003,   842,  1004,
     843,  1005,   193,   477,   880,   881,   882,  1029,   194,   474,
     867,   868,   869,   870,   195,   476,   875,   876,   877,   878,
     196,   475,   197,   484,   928,   929,   930,   931,   932,   198,
     480,   891,   892,   893,  1038,    63,    80,   378,   379,   380,
     546,   381,   547,   199,   481,   900,   901,   902,   903,   904,
     905,   906,   907,   200,   463,   850,   851,   852,  1012,    49,
      73,   264,   265,   266,   502,   267,   503,   268,   504,   269,
     508,   270,   507,   201,   202,   203,   204,   470,   730,   275,
     276,   205,   467,   862,   863,   864,  1021,  1159,  1160,   206,
     464,    57,    77,   854,   855,   856,  1015,    59,    78,   343,
     344,   345,   346,   347,   348,   349,   532,   350,   536,   351,
     535,   352,   353,   537,   354,   207,   465,   858,   859,   860,
    1018,    61,    79,   364,   365,   366,   367,   368,   541,   369,
     370,   371,   372,   278,   500,   967,   968,   969,  1081,    51,
      74,   289,   290,   291,   512,   208,   468,   209,   469,   281,
     501,   971,   972,   973,  1084,    53,    75,   305,   306,   307,
     515,   308,   309,   517,   310,   311,   210,   479,   887,   888,
     889,  1035,    55,    76,   323,   324,   325,   326,   523,   327,
     524,   328,   525,   329,   526,   330,   527,   331,   528,   332,
     522,   283,   509,   976,   977,  1087,   211,   478,   884,   885,
    1032,  1183,  1184,  1185,  1186,  1187,  1268,  1188,   212,   482,
     917,   918,   919,  1049,  1277,   920,   921,  1050,   922,   923,
     213,   214,   485,   940,   941,   942,  1061,   943,  1062,   215,
     486,   950,   951,   952,   953,  1066,   954,   955,  1068,   216,
     487,    65,    81,   400,   401,   402,   403,   551,   404,   552,
     405,   406,   554,   407,   408,   409,   557,   781,   410,   558,
     411,   412,   413,   561,   414,   562,   415,   563,   416,   564,
     217,   432,    67,    82,   419,   420,   421,   567,   422,   218,
     491,   958,   959,  1072,  1226,  1227,  1228,  1229,  1285,  1230,
    1283,  1304,  1305,  1306,  1314,  1315,  1316,  1322,  1317,  1318,
    1319,  1320,  1326,   219,   492,   962,   963,   964
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     155,   222,   239,   285,   299,   319,    38,   341,   360,   377,
     397,   914,   362,   282,   246,   363,   844,   227,   279,   292,
     303,   321,   874,   355,   373,  1149,   398,  1150,  1151,  1158,
     240,  1164,    30,   342,   361,    31,   334,    32,   865,    33,
     960,    86,   247,   248,   723,   249,   250,   251,   375,   376,
     129,   130,   220,   221,    42,   154,   129,   130,   313,   241,
     228,   280,   293,   304,   322,   974,   356,   374,   429,   399,
     755,   494,   908,   430,   417,   418,   495,   277,   288,   302,
     320,   797,   761,   762,   763,   242,   498,   375,   376,   243,
     510,   499,   252,   244,    89,   511,   335,    44,   336,   337,
     129,   130,   338,   339,   340,    46,   245,   253,   935,   936,
     254,   255,    48,   723,   256,   129,   130,   944,   945,   946,
     126,  1024,   257,   866,  1025,   258,   154,   259,   260,   261,
      50,  1027,   262,   284,  1028,   263,   129,   130,    52,   271,
     129,   130,   272,   273,    54,   274,    56,   286,   300,   287,
     301,   129,   130,   513,   924,   925,   926,   520,   514,   779,
     780,   236,   521,   154,   237,   792,  1274,  1275,  1276,   947,
     793,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   804,    58,    60,    62,   805,   806,   807,   808,   809,
     810,   811,   812,   813,   814,   815,  1250,  1251,  1252,   909,
     910,   911,   912,   711,   712,   713,   714,    98,    99,   100,
     101,   102,   103,   154,  1309,   125,   548,  1310,  1311,  1312,
    1313,   549,   565,   865,   872,   335,   873,   566,   154,   894,
     895,   896,   897,   898,   899,   126,   335,  1033,   715,    64,
    1034,   423,   126,    34,    35,    36,    37,   569,  1073,   154,
      66,  1074,   570,   154,   424,   129,   130,   294,   295,   296,
     297,   298,   129,   130,   154,   494,   426,   425,   427,  1149,
     979,  1150,  1151,  1158,   569,  1164,   498,  1170,  1171,   980,
    1006,   981,   529,   236,   437,  1007,   237,    92,    93,   335,
     438,    94,  1006,  1030,    95,    96,    97,  1008,  1031,   335,
     357,   336,   337,   358,   359,  1047,  1054,  1059,   129,   130,
    1048,  1055,  1060,   439,   440,  1063,   874,  1115,   129,   130,
    1064,  1307,  1069,   530,  1308,   441,   914,  1070,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   154,   126,   565,
    1076,   531,   442,   443,  1071,  1077,   127,   128,   154,  1006,
    1241,  1242,  1243,  1244,  1261,   154,   129,   130,   129,   130,
     510,  1265,   548,   131,   444,  1262,  1266,  1273,   132,   133,
     134,   135,   136,   137,   138,   445,   139,  1219,   312,  1220,
    1221,   140,   446,   447,   313,   314,   315,   316,   317,   318,
     141,  1286,   513,   142,   571,   572,  1287,  1289,   448,   520,
     143,   154,   449,   155,  1290,  1327,   540,   222,   144,   145,
    1328,   154,   450,   146,   452,   539,   147,   453,   454,   239,
     148,   455,   285,   227,   726,   727,   728,   729,   456,   299,
     282,   246,   460,   461,   462,   279,   466,   471,   292,   319,
     472,   149,   150,   151,   152,   303,   473,   240,   483,   341,
     490,   493,   497,   153,   360,   321,   505,   506,   362,   247,
     248,   363,   249,   250,   251,   355,   228,   516,   518,   154,
     373,   154,   519,   534,   397,   342,   241,   538,   280,   542,
     361,   293,   543,   545,   544,   550,   553,   555,   304,   556,
     398,   559,   560,   568,   277,   574,   575,   288,   322,   573,
     576,   577,   242,   578,   302,   579,   243,   580,   356,   252,
     244,   129,   130,   374,   320,   595,   581,   582,   583,   584,
     585,   586,   587,   245,   253,   588,   589,   254,   255,   590,
     591,   256,   592,   399,   593,   594,   596,   597,   601,   257,
     598,   599,   258,   600,   259,   260,   261,   602,   603,   262,
     604,   605,   263,   607,   608,   609,   271,   606,   610,   272,
     273,   611,   274,   612,   613,   614,   286,   615,   287,   616,
     617,   618,   619,   300,   620,   301,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   621,
     622,   623,   624,   625,   626,   627,   395,   396,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   155,   628,   629,   222,   630,   631,   632,   633,
     634,   635,   636,   638,   154,   639,   641,   703,   642,   643,
     644,   227,   645,   646,   647,   648,   649,   650,   652,   654,
     655,   656,   660,   661,   662,   657,   663,   664,   913,   927,
     937,   658,   397,   665,   666,   668,   961,   669,   671,   670,
     672,   673,   676,   680,   915,   933,   938,   948,   398,   681,
     674,   677,   788,   678,   228,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   683,   684,
     685,   686,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   687,   690,   126,   688,   691,   694,   916,   934,   939,
     949,   399,   689,   695,   705,   229,   692,   230,   693,   696,
     697,   699,   700,   129,   130,   231,   232,   233,   234,   235,
     131,   702,   704,   706,   709,   132,   133,   134,   707,   708,
     710,   717,   718,   719,   236,   720,   721,   237,   140,   722,
      32,   725,   731,   732,   733,   238,   735,   734,   736,   737,
     744,   745,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   738,   739,   740,   741,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   742,
     126,   335,   743,   746,   747,   748,   750,   751,   879,   787,
     757,   782,   845,   849,   752,   753,   754,   756,   149,   150,
     129,   130,   758,   232,   233,   759,   235,   131,   760,   764,
     765,   766,   132,   133,   134,   853,   857,   861,   883,   767,
     886,   236,   890,   957,   237,   966,   154,   970,   986,   987,
     768,   988,   238,   769,   989,   990,   992,   993,   998,   770,
     999,  1000,  1001,  1011,   771,  1010,  1014,   772,   773,   774,
     776,   777,  1013,  1016,  1017,   778,  1019,  1020,   784,  1022,
    1023,  1026,  1036,   785,   786,  1037,  1039,  1040,  1094,  1041,
    1042,  1043,  1044,  1045,  1046,  1051,  1052,  1053,  1056,  1057,
    1058,  1065,  1067,  1075,  1078,   149,   150,  1082,  1083,  1085,
    1086,  1096,  1088,  1090,  1089,  1091,  1092,  1093,  1095,  1097,
    1098,  1099,  1102,  1100,  1101,  1103,  1104,  1105,  1106,  1107,
    1110,   239,  1108,   154,   341,  1109,  1111,   360,  1112,  1113,
    1123,   362,   282,   246,   363,  1168,  1194,   279,  1195,  1196,
     355,  1172,  1130,   373,   319,  1201,  1162,   377,  1197,   240,
     342,  1198,  1202,   361,  1211,  1207,  1148,  1181,  1124,  1199,
     321,   247,   248,   913,   249,   250,   251,  1179,   927,  1173,
    1131,  1132,   937,  1133,  1134,  1135,  1203,  1204,   241,   915,
     280,  1222,  1212,   356,   933,   961,   374,  1125,   938,  1163,
     285,  1205,  1208,   299,   948,  1209,   277,  1224,  1174,  1214,
    1182,  1215,  1217,   322,   242,  1161,   292,  1223,   243,   303,
    1234,   252,   244,  1126,  1216,  1232,  1180,  1127,  1235,   320,
    1136,  1128,   916,  1240,  1175,   245,   253,   934,  1176,   254,
     255,   939,  1177,   256,  1129,  1137,  1263,   949,  1138,  1139,
    1225,   257,  1140,  1264,   258,  1178,   259,   260,   261,   293,
    1141,   262,   304,  1142,   263,  1143,  1144,  1145,   271,  1269,
    1146,   272,   273,  1147,   274,   288,  1270,  1154,   302,  1271,
    1155,  1156,  1246,  1157,  1152,  1247,  1153,  1272,  1284,  1293,
    1296,  1248,  1249,  1298,  1254,  1301,  1255,  1323,  1303,  1324,
    1325,  1329,  1333,   775,   871,   789,   791,   637,   640,   783,
     978,  1116,  1114,  1256,  1169,  1257,  1166,  1167,  1193,  1258,
    1210,  1192,   682,  1259,  1118,  1165,  1200,  1260,  1267,  1278,
    1292,  1117,  1279,  1280,   333,  1119,  1122,  1281,  1288,  1120,
    1291,  1121,  1297,  1300,   286,  1294,   287,   300,   675,   301,
    1302,  1335,  1330,  1331,  1332,  1336,   679,  1236,  1237,   659,
    1190,  1191,   975,  1189,  1295,  1206,  1213,  1218,  1239,   956,
    1238,   698,  1231,   790,   701,  1299,  1321,  1334,     0,     0,
    1233,     0,   651,     0,  1123,     0,   653,     0,     0,     0,
    1172,     0,     0,     0,     0,     0,  1130,  1282,     0,     0,
    1162,     0,     0,     0,     0,  1222,  1181,   667,     0,     0,
    1148,     0,  1124,     0,     0,     0,  1179,     0,  1173,     0,
       0,  1224,     0,     0,  1131,  1132,     0,  1133,  1134,  1135,
       0,  1223,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1125,     0,  1163,     0,     0,     0,  1174,     0,  1182,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1161,
       0,     0,     0,     0,  1225,  1180,     0,  1126,     0,     0,
       0,  1127,     0,  1175,  1136,  1128,     0,  1176,     0,     0,
       0,  1177,     0,     0,     0,     0,     0,     0,  1129,  1137,
       0,     0,  1138,  1139,  1178,     0,  1140,     0,     0,     0,
       0,     0,     0,     0,  1141,     0,     0,  1142,     0,  1143,
    1144,  1145,     0,     0,  1146,     0,     0,  1147,     0,     0,
       0,  1154,     0,     0,  1155,  1156,     0,  1157,  1152,     0,
    1153
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   739,    79,    73,    73,    79,   708,    72,    73,    74,
      75,    76,   733,    78,    79,  1021,    81,  1021,  1021,  1021,
      73,  1021,     0,    78,    79,     5,    21,     7,   128,     9,
     198,   213,    73,    73,   612,    73,    73,    73,   135,   136,
     100,   101,    16,    17,     7,   213,   100,   101,   126,    73,
      72,    73,    74,    75,    76,   133,    78,    79,     3,    81,
     648,     3,    21,     8,    13,    14,     8,    73,    74,    75,
      76,    30,   660,   661,   662,    73,     3,   135,   136,    73,
       3,     8,    73,    73,    10,     8,    81,     7,    83,    84,
     100,   101,    87,    88,    89,     7,    73,    73,   158,   159,
      73,    73,     7,   681,    73,   100,   101,   161,   162,   163,
      80,     3,    73,   213,     6,    73,   213,    73,    73,    73,
       7,     3,    73,    93,     6,    73,   100,   101,     7,    73,
     100,   101,    73,    73,     7,    73,     7,    74,    75,    74,
      75,   100,   101,     3,   154,   155,   156,     3,     8,   178,
     179,   121,     8,   213,   124,    21,   145,   146,   147,   213,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     7,     7,     7,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    38,    39,    40,   148,
     149,   150,   151,   181,   182,   183,   184,    52,    53,    54,
      55,    56,    57,   213,   190,    79,     3,   193,   194,   195,
     196,     8,     3,   128,   129,    81,   131,     8,   213,   138,
     139,   140,   141,   142,   143,    80,    81,     3,   216,     7,
       6,     6,    80,   213,   214,   215,   216,     3,     3,   213,
       7,     6,     8,   213,     3,   100,   101,    95,    96,    97,
      98,    99,   100,   101,   213,     3,     8,     4,     3,  1265,
       8,  1265,  1265,  1265,     3,  1265,     3,   122,   123,     8,
       3,     8,     8,   121,     4,     8,   124,    11,    12,    81,
       4,    15,     3,     3,    18,    19,    20,     8,     8,    81,
      82,    83,    84,    85,    86,     3,     3,     3,   100,   101,
       8,     8,     8,     4,     4,     3,  1027,  1009,   100,   101,
       8,     3,     3,     3,     6,     4,  1054,     8,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   213,    80,     3,
       3,     8,     4,     4,     8,     8,    90,    91,   213,     3,
      22,    23,    24,    25,     8,   213,   100,   101,   100,   101,
       3,     3,     3,   107,     4,     8,     8,     8,   112,   113,
     114,   115,   116,   117,   118,     4,   120,   189,   120,   191,
     192,   125,     4,     4,   126,   127,   128,   129,   130,   131,
     134,     3,     3,   137,   424,   425,     8,     8,     4,     3,
     144,   213,     4,   494,     8,     3,     3,   498,   152,   153,
       8,   213,     4,   157,     4,     8,   160,     4,     4,   510,
     164,     4,   513,   498,   108,   109,   110,   111,     4,   520,
     510,   510,     4,     4,     4,   510,     4,     4,   513,   530,
       4,   185,   186,   187,   188,   520,     4,   510,     4,   540,
       4,     4,     4,   197,   545,   530,     4,     4,   545,   510,
     510,   545,   510,   510,   510,   540,   498,     4,     4,   213,
     545,   213,     4,     4,   565,   540,   510,     4,   510,     4,
     545,   513,     4,     3,     8,     4,     4,     4,   520,     4,
     565,     4,     4,     4,   510,     4,     4,   513,   530,   213,
       4,     4,   510,     4,   520,     4,   510,     4,   540,   510,
     510,   100,   101,   545,   530,     4,   214,   214,   214,   214,
     214,   214,   214,   510,   510,   214,   216,   510,   510,   215,
     215,   510,   215,   565,   214,   214,   214,   214,     4,   510,
     216,   216,   510,   216,   510,   510,   510,     4,     4,   510,
     216,   216,   510,     4,     4,     4,   510,   216,   214,   510,
     510,     4,   510,     4,     4,     4,   513,   216,   513,   216,
     216,     4,     4,   520,     4,   520,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,     4,
       4,     4,     4,     4,     4,   214,   185,   186,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   703,     4,     4,   706,     4,     4,     4,     4,
     216,     4,     4,     4,   213,   216,     4,     7,     4,     4,
       4,   706,     4,   214,   216,     4,     4,     4,     4,     4,
     214,     4,     4,     4,     4,   214,     4,     4,   739,   740,
     741,   214,   743,     4,     4,     4,   747,     4,     4,   214,
       4,     4,     4,     4,   739,   740,   741,   742,   743,     4,
     216,   216,   702,   216,   706,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,   216,     4,
       4,   214,    69,    70,    71,    72,    73,    74,    75,    76,
      77,     4,     4,    80,   214,     4,     4,   739,   740,   741,
     742,   743,   214,     4,     7,    92,   216,    94,   216,     4,
       4,     4,   214,   100,   101,   102,   103,   104,   105,   106,
     107,     4,   213,     7,     5,   112,   113,   114,     7,     7,
     213,   213,   213,     5,   121,     5,     5,   124,   125,     5,
       7,   213,     5,     5,     5,   132,     5,     7,     5,     5,
     213,   213,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     7,     7,     7,     7,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     7,
      80,    81,     7,     5,     7,     5,     5,     5,   119,     5,
       7,   180,     7,     7,   213,   213,   213,   213,   185,   186,
     100,   101,   213,   103,   104,   213,   106,   107,   213,   213,
     213,   213,   112,   113,   114,     7,     7,     7,     7,   213,
       7,   121,     7,     7,   124,     7,   213,     7,     4,     4,
     213,     4,   132,   213,     4,     4,     4,     4,     4,   213,
       4,     4,     4,     3,   213,     6,     3,   213,   213,   213,
     213,   213,     6,     6,     3,   213,     6,     3,   213,     6,
       3,     6,     6,   213,   213,     3,     6,     3,   214,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   213,   185,   186,     6,     3,     6,
       3,   214,     8,     4,     6,     4,     4,     4,   216,   216,
     214,     4,     4,   214,   214,     4,     4,     4,   214,   214,
       4,  1012,   216,   213,  1015,   214,     4,  1018,     4,     4,
    1021,  1018,  1012,  1012,  1018,     4,   214,  1012,   214,   214,
    1015,  1032,  1021,  1018,  1035,     4,  1021,  1038,   214,  1012,
    1015,   214,     4,  1018,     4,   216,  1021,  1032,  1021,   214,
    1035,  1012,  1012,  1054,  1012,  1012,  1012,  1032,  1059,  1032,
    1021,  1021,  1063,  1021,  1021,  1021,   214,   214,  1012,  1054,
    1012,  1072,     4,  1015,  1059,  1076,  1018,  1021,  1063,  1021,
    1081,   214,   214,  1084,  1069,   214,  1012,  1072,  1032,   216,
    1032,     4,     4,  1035,  1012,  1021,  1081,  1072,  1012,  1084,
       6,  1012,  1012,  1021,   214,   216,  1032,  1021,     3,  1035,
    1021,  1021,  1054,     4,  1032,  1012,  1012,  1059,  1032,  1012,
    1012,  1063,  1032,  1012,  1021,  1021,     8,  1069,  1021,  1021,
    1072,  1012,  1021,     8,  1012,  1032,  1012,  1012,  1012,  1081,
    1021,  1012,  1084,  1021,  1012,  1021,  1021,  1021,  1012,     4,
    1021,  1012,  1012,  1021,  1012,  1081,     8,  1021,  1084,     3,
    1021,  1021,   213,  1021,  1021,   213,  1021,     8,     4,     4,
       4,   213,   213,     4,   213,     5,   213,     4,     7,     4,
       4,     4,     4,   681,   732,   703,   706,   494,   498,   694,
     787,  1011,  1006,   213,  1030,   213,  1024,  1027,  1040,   213,
    1059,  1038,   548,   213,  1014,  1023,  1047,   213,   213,   213,
    1265,  1012,   213,   213,    77,  1015,  1020,   213,   213,  1017,
     213,  1018,   214,   213,  1081,   216,  1081,  1084,   540,  1084,
     213,   213,   216,   214,   214,   213,   545,  1081,  1083,   520,
    1035,  1037,   757,  1033,  1271,  1054,  1063,  1069,  1086,   743,
    1084,   565,  1073,   705,   569,  1286,  1307,  1327,    -1,    -1,
    1076,    -1,   510,    -1,  1265,    -1,   513,    -1,    -1,    -1,
    1271,    -1,    -1,    -1,    -1,    -1,  1265,  1217,    -1,    -1,
    1265,    -1,    -1,    -1,    -1,  1286,  1271,   530,    -1,    -1,
    1265,    -1,  1265,    -1,    -1,    -1,  1271,    -1,  1271,    -1,
      -1,  1286,    -1,    -1,  1265,  1265,    -1,  1265,  1265,  1265,
      -1,  1286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1265,    -1,  1265,    -1,    -1,    -1,  1271,    -1,  1271,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1265,
      -1,    -1,    -1,    -1,  1286,  1271,    -1,  1265,    -1,    -1,
      -1,  1265,    -1,  1271,  1265,  1265,    -1,  1271,    -1,    -1,
      -1,  1271,    -1,    -1,    -1,    -1,    -1,    -1,  1265,  1265,
      -1,    -1,  1265,  1265,  1271,    -1,  1265,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1265,    -1,    -1,  1265,    -1,  1265,
    1265,  1265,    -1,    -1,  1265,    -1,    -1,  1265,    -1,    -1,
      -1,  1265,    -1,    -1,  1265,  1265,    -1,  1265,  1265,    -1,
    1265
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
       0,     5,     7,     9,   213,   214,   215,   216,   233,   234,
     235,   240,     7,   249,     7,   254,     7,   299,     7,   416,
       7,   496,     7,   512,     7,   529,     7,   448,     7,   454,
       7,   478,     7,   392,     7,   598,     7,   629,   241,   236,
     250,   255,   300,   417,   497,   513,   530,   449,   455,   479,
     393,   599,   630,   233,   242,   243,   213,   238,   239,    10,
     251,   253,    11,    12,    15,    18,    19,    20,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    90,    91,   100,
     101,   107,   112,   113,   114,   115,   116,   117,   118,   120,
     125,   134,   137,   144,   152,   153,   157,   160,   164,   185,
     186,   187,   188,   197,   213,   248,   256,   257,   258,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   280,   282,   284,
     285,   286,   288,   290,   291,   292,   293,   295,   296,   297,
     306,   308,   310,   359,   365,   371,   377,   379,   386,   400,
     410,   430,   431,   432,   433,   438,   446,   472,   502,   504,
     523,   553,   565,   577,   578,   586,   596,   627,   636,   660,
      16,    17,   248,   301,   302,   303,   305,   502,   504,    92,
      94,   102,   103,   104,   105,   106,   121,   124,   132,   248,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   274,   275,   276,   277,   280,   282,   284,
     285,   286,   288,   290,   418,   419,   420,   422,   424,   426,
     428,   430,   431,   432,   433,   436,   437,   472,   490,   502,
     504,   506,   523,   548,    93,   248,   426,   428,   472,   498,
     499,   500,   502,   504,    95,    96,    97,    98,    99,   248,
     426,   428,   472,   502,   504,   514,   515,   516,   518,   519,
     521,   522,   120,   126,   127,   128,   129,   130,   131,   248,
     472,   502,   504,   531,   532,   533,   534,   536,   538,   540,
     542,   544,   546,   446,    21,    81,    83,    84,    87,    88,
      89,   248,   328,   456,   457,   458,   459,   460,   461,   462,
     464,   466,   468,   469,   471,   502,   504,    82,    85,    86,
     248,   328,   460,   466,   480,   481,   482,   483,   484,   486,
     487,   488,   489,   502,   504,   135,   136,   248,   394,   395,
     396,   398,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   185,   186,   248,   502,   504,
     600,   601,   602,   603,   605,   607,   608,   610,   611,   612,
     615,   617,   618,   619,   621,   623,   625,    13,    14,   631,
     632,   633,   635,     6,     3,     4,     8,     3,   252,     3,
       8,   259,   628,   298,   307,   309,   311,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   294,     4,     4,     4,     4,     4,   278,   281,   283,
       4,     4,     4,   411,   447,   473,     4,   439,   503,   505,
     434,     4,     4,     4,   366,   378,   372,   360,   554,   524,
     387,   401,   566,     4,   380,   579,   587,   597,   287,   289,
       4,   637,   661,     4,     3,     8,   304,     4,     3,     8,
     491,   507,   421,   423,   425,     4,     4,   429,   427,   549,
       3,     8,   501,     3,     8,   517,     4,   520,     4,     4,
       3,     8,   547,   535,   537,   539,   541,   543,   545,     8,
       3,     8,   463,   329,     4,   467,   465,   470,     4,     8,
       3,   485,     4,     4,     8,     3,   397,   399,     3,     8,
       4,   604,   606,     4,   609,     4,     4,   613,   616,     4,
       4,   620,   622,   624,   626,     3,     8,   634,     4,     3,
       8,   233,   233,   213,     4,     4,     4,     4,     4,     4,
       4,   214,   214,   214,   214,   214,   214,   214,   214,   216,
     215,   215,   215,   214,   214,     4,   214,   214,   216,   216,
     216,     4,     4,     4,   216,   216,   216,     4,     4,     4,
     214,     4,     4,     4,     4,   216,   216,   216,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   214,     4,     4,
       4,     4,     4,     4,   216,     4,     4,   257,     4,   216,
     302,     4,     4,     4,     4,     4,   214,   216,     4,     4,
       4,   419,     4,   499,     4,   214,     4,   214,   214,   515,
       4,     4,     4,     4,     4,     4,     4,   533,     4,     4,
     214,     4,     4,     4,   216,   458,     4,   216,   216,   482,
       4,     4,   395,   216,     4,     4,   214,     4,   214,   214,
       4,     4,   216,   216,     4,     4,     4,     4,   601,     4,
     214,   632,     4,     7,   213,     7,     7,     7,     7,     5,
     213,   181,   182,   183,   184,   216,   279,   213,   213,     5,
       5,     5,     5,   235,   237,   213,   108,   109,   110,   111,
     435,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   213,   213,     5,     7,     5,   244,
       5,     5,   213,   213,   213,   244,   213,     7,   213,   213,
     213,   244,   244,   244,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   237,   213,   213,   213,   178,
     179,   614,   180,   279,   213,   213,   213,     5,   233,   256,
     631,   301,    21,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,   248,   316,   317,   318,
     321,   323,   325,   327,   328,   330,   331,   332,   333,   334,
     335,   338,   339,   340,   341,   342,   344,   345,   347,   349,
     351,   353,   355,   357,   316,     7,   312,   313,   314,     7,
     412,   413,   414,     7,   450,   451,   452,     7,   474,   475,
     476,     7,   440,   441,   442,   128,   213,   367,   368,   369,
     370,   242,   129,   131,   369,   373,   374,   375,   376,   119,
     361,   362,   363,     7,   555,   556,     7,   525,   526,   527,
       7,   388,   389,   390,   138,   139,   140,   141,   142,   143,
     402,   403,   404,   405,   406,   407,   408,   409,    21,   148,
     149,   150,   151,   248,   330,   502,   504,   567,   568,   569,
     572,   573,   575,   576,   154,   155,   156,   248,   381,   382,
     383,   384,   385,   502,   504,   158,   159,   248,   502,   504,
     580,   581,   582,   584,   161,   162,   163,   213,   502,   504,
     588,   589,   590,   591,   593,   594,   600,     7,   638,   639,
     198,   248,   662,   663,   664,   245,     7,   492,   493,   494,
       7,   508,   509,   510,   133,   534,   550,   551,   312,     8,
       8,     8,   319,   322,   324,   326,     4,     4,     4,     4,
       4,   343,     4,     4,   336,   346,   348,   350,     4,     4,
       4,     4,   352,   354,   356,   358,     3,     8,     8,   315,
       6,     3,   415,     6,     3,   453,     6,     3,   477,     6,
       3,   443,     6,     3,     3,     6,     6,     3,     6,   364,
       3,     8,   557,     3,     6,   528,     6,     3,   391,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   570,
     574,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   583,   585,     3,     8,     4,   592,     4,   595,     3,
       8,     8,   640,     3,     6,     4,     3,     8,   213,   246,
     247,   495,     6,     3,   511,     6,     3,   552,     8,     6,
       4,     4,     4,     4,   214,   216,   214,   216,   214,     4,
     214,   214,     4,     4,     4,     4,   214,   214,   216,   214,
       4,     4,     4,     4,   317,   316,   314,   418,   414,   456,
     452,   480,   476,   248,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   274,   275,   276,
     277,   280,   282,   284,   285,   286,   288,   290,   328,   410,
     422,   424,   426,   428,   430,   431,   432,   433,   437,   444,
     445,   472,   502,   504,   548,   442,   368,   374,     4,   362,
     122,   123,   248,   260,   261,   262,   263,   264,   265,   328,
     472,   502,   504,   558,   559,   560,   561,   562,   564,   556,
     531,   527,   394,   390,   214,   214,   214,   214,   214,   214,
     403,     4,     4,   214,   214,   214,   568,   216,   214,   214,
     382,     4,     4,   581,   216,     4,   214,     4,   589,   189,
     191,   192,   248,   328,   502,   504,   641,   642,   643,   644,
     646,   639,   216,   663,     6,     3,   498,   494,   514,   510,
       4,    22,    23,    24,    25,   320,   213,   213,   213,   213,
      38,    39,    40,   337,   213,   213,   213,   213,   213,   213,
     213,     8,     8,     8,     8,     3,     8,   213,   563,     4,
       8,     3,     8,     8,   145,   146,   147,   571,   213,   213,
     213,   213,   233,   647,     4,   645,     3,     8,   213,     8,
       8,   213,   445,     4,   216,   560,     4,   214,     4,   642,
     213,     5,   213,     7,   648,   649,   650,     3,     6,   190,
     193,   194,   195,   196,   651,   652,   653,   655,   656,   657,
     658,   649,   654,     4,     4,     4,   659,     3,     8,     4,
     216,   214,   214,     4,   652,   213,   213
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
     257,   257,   257,   257,   257,   259,   258,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   278,   277,   279,   279,   279,   279,
     279,   281,   280,   283,   282,   284,   285,   287,   286,   289,
     288,   290,   291,   292,   294,   293,   295,   296,   298,   297,
     300,   299,   301,   301,   301,   302,   302,   302,   302,   302,
     304,   303,   305,   307,   306,   309,   308,   311,   310,   312,
     312,   313,   313,   313,   315,   314,   316,   316,   316,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   319,   318,   320,   320,   320,
     320,   322,   321,   324,   323,   326,   325,   327,   329,   328,
     330,   331,   332,   333,   334,   336,   335,   337,   337,   337,
     338,   339,   340,   341,   343,   342,   344,   346,   345,   348,
     347,   350,   349,   352,   351,   354,   353,   356,   355,   358,
     357,   360,   359,   361,   361,   361,   362,   364,   363,   366,
     365,   367,   367,   367,   368,   368,   369,   370,   372,   371,
     373,   373,   373,   374,   374,   374,   375,   376,   378,   377,
     380,   379,   381,   381,   381,   382,   382,   382,   382,   382,
     382,   383,   384,   385,   387,   386,   388,   388,   389,   389,
     389,   391,   390,   393,   392,   394,   394,   394,   394,   395,
     395,   397,   396,   399,   398,   401,   400,   402,   402,   402,
     403,   403,   403,   403,   403,   403,   404,   405,   406,   407,
     408,   409,   411,   410,   412,   412,   413,   413,   413,   415,
     414,   417,   416,   418,   418,   418,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   421,
     420,   423,   422,   425,   424,   427,   426,   429,   428,   430,
     431,   432,   434,   433,   435,   435,   435,   435,   436,   437,
     439,   438,   440,   440,   441,   441,   441,   443,   442,   444,
     444,   444,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   447,   446,   449,   448,   450,   450,   451,   451,
     451,   453,   452,   455,   454,   456,   456,   457,   457,   457,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     459,   460,   461,   463,   462,   465,   464,   467,   466,   468,
     470,   469,   471,   473,   472,   474,   474,   475,   475,   475,
     477,   476,   479,   478,   480,   480,   481,   481,   481,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   483,   485,
     484,   486,   487,   488,   489,   491,   490,   492,   492,   493,
     493,   493,   495,   494,   497,   496,   498,   498,   498,   499,
     499,   499,   499,   499,   499,   499,   501,   500,   503,   502,
     505,   504,   507,   506,   508,   508,   509,   509,   509,   511,
     510,   513,   512,   514,   514,   514,   515,   515,   515,   515,
     515,   515,   515,   515,   515,   515,   515,   517,   516,   518,
     520,   519,   521,   522,   524,   523,   525,   525,   526,   526,
     526,   528,   527,   530,   529,   531,   531,   532,   532,   532,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   535,   534,   537,   536,   539,   538,   541,   540,   543,
     542,   545,   544,   547,   546,   549,   548,   550,   550,   552,
     551,   554,   553,   555,   555,   555,   557,   556,   558,   558,
     559,   559,   559,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   561,   563,   562,   564,
     566,   565,   567,   567,   567,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   570,   569,   571,   571,   571,   572,
     574,   573,   575,   576,   577,   579,   578,   580,   580,   580,
     581,   581,   581,   581,   581,   583,   582,   585,   584,   587,
     586,   588,   588,   588,   589,   589,   589,   589,   589,   589,
     590,   592,   591,   593,   595,   594,   597,   596,   599,   598,
     600,   600,   600,   601,   601,   601,   601,   601,   601,   601,
     601,   601,   601,   601,   601,   601,   601,   601,   601,   601,
     601,   602,   604,   603,   606,   605,   607,   609,   608,   610,
     611,   613,   612,   614,   614,   616,   615,   617,   618,   620,
     619,   622,   621,   624,   623,   626,   625,   628,   627,   630,
     629,   631,   631,   631,   632,   632,   634,   633,   635,   637,
     636,   638,   638,   638,   640,   639,   641,   641,   641,   642,
     642,   642,   642,   642,   642,   642,   643,   645,   644,   647,
     646,   648,   648,   648,   650,   649,   651,   651,   651,   652,
     652,   652,   652,   652,   654,   653,   655,   656,   657,   659,
     658,   661,   660,   662,   662,   662,   663,   663,   664
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
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     3,     3,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     0,     4,     0,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     3
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
  "parked_packet_limit", "ip_reservations_unique", "interfaces_config",
  "$@28", "sub_interfaces6", "$@29", "interfaces_config_params",
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
     551,   552,   553,   554,   555,   558,   558,   567,   573,   579,
     585,   591,   597,   603,   609,   615,   621,   627,   633,   639,
     645,   651,   657,   663,   669,   669,   678,   681,   684,   687,
     690,   696,   696,   705,   705,   714,   720,   726,   726,   735,
     735,   744,   750,   756,   762,   762,   771,   777,   783,   783,
     795,   795,   804,   805,   806,   811,   812,   813,   814,   815,
     818,   818,   829,   835,   835,   848,   848,   861,   861,   872,
     873,   876,   877,   878,   883,   883,   893,   894,   895,   900,
     901,   902,   903,   904,   905,   906,   907,   908,   909,   910,
     911,   912,   913,   914,   915,   916,   917,   918,   919,   920,
     921,   922,   923,   924,   925,   928,   928,   936,   937,   938,
     939,   942,   942,   951,   951,   960,   960,   969,   975,   975,
     984,   990,   996,  1002,  1008,  1014,  1014,  1022,  1023,  1024,
    1027,  1033,  1039,  1045,  1051,  1051,  1060,  1066,  1066,  1075,
    1075,  1084,  1084,  1093,  1093,  1102,  1102,  1111,  1111,  1120,
    1120,  1129,  1129,  1140,  1141,  1142,  1147,  1149,  1149,  1168,
    1168,  1179,  1180,  1181,  1186,  1187,  1190,  1195,  1200,  1200,
    1211,  1212,  1213,  1218,  1219,  1220,  1223,  1228,  1235,  1235,
    1248,  1248,  1261,  1262,  1263,  1268,  1269,  1270,  1271,  1272,
    1273,  1276,  1282,  1288,  1294,  1294,  1305,  1306,  1309,  1310,
    1311,  1316,  1316,  1326,  1326,  1336,  1337,  1338,  1341,  1344,
    1345,  1348,  1348,  1357,  1357,  1366,  1366,  1378,  1379,  1380,
    1385,  1386,  1387,  1388,  1389,  1390,  1393,  1399,  1405,  1411,
    1417,  1423,  1432,  1432,  1446,  1447,  1450,  1451,  1452,  1461,
    1461,  1487,  1487,  1498,  1499,  1500,  1506,  1507,  1508,  1509,
    1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,
    1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,
    1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,
    1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,  1548,  1551,
    1551,  1560,  1560,  1569,  1569,  1578,  1578,  1587,  1587,  1598,
    1604,  1610,  1616,  1616,  1624,  1625,  1626,  1627,  1630,  1636,
    1644,  1644,  1656,  1657,  1661,  1662,  1663,  1668,  1668,  1676,
    1677,  1678,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,
    1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,
    1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,
    1721,  1722,  1729,  1729,  1743,  1743,  1752,  1753,  1756,  1757,
    1758,  1765,  1765,  1780,  1780,  1794,  1795,  1798,  1799,  1800,
    1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,
    1817,  1819,  1825,  1827,  1827,  1836,  1836,  1845,  1845,  1854,
    1856,  1856,  1865,  1875,  1875,  1888,  1889,  1894,  1895,  1896,
    1903,  1903,  1915,  1915,  1927,  1928,  1933,  1934,  1935,  1942,
    1943,  1944,  1945,  1946,  1947,  1948,  1949,  1950,  1953,  1955,
    1955,  1964,  1966,  1968,  1974,  1983,  1983,  1996,  1997,  2000,
    2001,  2002,  2007,  2007,  2017,  2017,  2027,  2028,  2029,  2034,
    2035,  2036,  2037,  2038,  2039,  2040,  2043,  2043,  2052,  2052,
    2077,  2077,  2107,  2107,  2120,  2121,  2124,  2125,  2126,  2131,
    2131,  2143,  2143,  2155,  2156,  2157,  2162,  2163,  2164,  2165,
    2166,  2167,  2168,  2169,  2170,  2171,  2172,  2175,  2175,  2184,
    2190,  2190,  2199,  2205,  2214,  2214,  2225,  2226,  2229,  2230,
    2231,  2236,  2236,  2245,  2245,  2254,  2255,  2258,  2259,  2260,
    2266,  2267,  2268,  2269,  2270,  2271,  2272,  2273,  2274,  2275,
    2276,  2279,  2279,  2290,  2290,  2301,  2301,  2310,  2310,  2319,
    2319,  2328,  2328,  2337,  2337,  2351,  2351,  2362,  2363,  2366,
    2366,  2378,  2378,  2389,  2390,  2391,  2396,  2396,  2406,  2407,
    2410,  2411,  2412,  2417,  2418,  2419,  2420,  2421,  2422,  2423,
    2424,  2425,  2426,  2427,  2428,  2429,  2432,  2434,  2434,  2443,
    2452,  2452,  2465,  2466,  2467,  2472,  2473,  2474,  2475,  2476,
    2477,  2478,  2479,  2480,  2483,  2483,  2491,  2492,  2493,  2496,
    2502,  2502,  2511,  2517,  2525,  2533,  2533,  2544,  2545,  2546,
    2551,  2552,  2553,  2554,  2555,  2558,  2558,  2567,  2567,  2579,
    2579,  2592,  2593,  2594,  2599,  2600,  2601,  2602,  2603,  2604,
    2607,  2613,  2613,  2622,  2628,  2628,  2638,  2638,  2651,  2651,
    2661,  2662,  2663,  2668,  2669,  2670,  2671,  2672,  2673,  2674,
    2675,  2676,  2677,  2678,  2679,  2680,  2681,  2682,  2683,  2684,
    2685,  2688,  2695,  2695,  2704,  2704,  2713,  2719,  2719,  2728,
    2734,  2740,  2740,  2749,  2750,  2753,  2753,  2763,  2770,  2777,
    2777,  2786,  2786,  2796,  2796,  2806,  2806,  2818,  2818,  2830,
    2830,  2840,  2841,  2842,  2848,  2849,  2852,  2852,  2863,  2871,
    2871,  2884,  2885,  2886,  2892,  2892,  2900,  2901,  2902,  2907,
    2908,  2909,  2910,  2911,  2912,  2913,  2916,  2922,  2922,  2931,
    2931,  2942,  2943,  2944,  2949,  2949,  2957,  2958,  2959,  2964,
    2965,  2966,  2967,  2968,  2971,  2971,  2980,  2986,  2992,  2998,
    2998,  3007,  3007,  3018,  3019,  3020,  3025,  3026,  3029
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
#line 6420 "dhcp6_parser.cc"

#line 3035 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
