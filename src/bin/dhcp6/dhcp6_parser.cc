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
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 292 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 292 "dhcp6_parser.yy"
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
#line 301 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 302 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 303 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 304 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 305 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 306 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 307 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 308 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 309 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 310 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 311 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 312 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 313 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 314 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 322 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 323 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 324 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 325 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 326 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 327 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 328 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 331 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 336 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 341 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 347 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 354 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 359 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 365 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 370 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 373 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 381 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 385 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 389 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 395 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 397 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 406 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 410 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 414 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 424 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 433 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 438 "dhcp6_parser.yy"
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
#line 448 "dhcp6_parser.yy"
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
#line 457 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 465 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 471 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 475 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 482 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 135: // $@21: %empty
#line 554 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 136: // data_directory: "data-directory" $@21 ":" "constant string"
#line 557 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 137: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 563 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 138: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 569 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 139: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 575 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 140: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 141: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 587 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 142: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 143: // renew_timer: "renew-timer" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 144: // rebind_timer: "rebind-timer" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 145: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 611 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 146: // t1_percent: "t1-percent" ":" "floating point"
#line 617 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 147: // t2_percent: "t2-percent" ":" "floating point"
#line 623 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 148: // cache_threshold: "cache-threshold" ":" "floating point"
#line 629 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 149: // cache_max_age: "cache-max-age" ":" "integer"
#line 635 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 150: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 641 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 151: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 647 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 152: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 653 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 153: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 659 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 154: // $@22: %empty
#line 665 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 155: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 668 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "when-present"
#line 674 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "never"
#line 677 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "always"
#line 680 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-not-present"
#line 683 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "boolean"
#line 686 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 161: // $@23: %empty
#line 692 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 162: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 695 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 163: // $@24: %empty
#line 701 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 164: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 704 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 165: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 710 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 166: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 716 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 167: // $@25: %empty
#line 722 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 168: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 725 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 169: // $@26: %empty
#line 731 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 734 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 171: // store_extended_info: "store-extended-info" ":" "boolean"
#line 740 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 172: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 746 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 173: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 752 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 174: // $@27: %empty
#line 758 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 175: // server_tag: "server-tag" $@27 ":" "constant string"
#line 761 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 176: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 767 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 177: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 773 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 178: // $@28: %empty
#line 779 "dhcp6_parser.yy"
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
#line 785 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 180: // $@29: %empty
#line 791 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 181: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 795 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 184: // interfaces_config_params: interfaces_config_params ","
#line 802 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1578 "dhcp6_parser.cc"
    break;

  case 190: // $@30: %empty
#line 814 "dhcp6_parser.yy"
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
#line 820 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 192: // re_detect: "re-detect" ":" "boolean"
#line 825 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 193: // $@31: %empty
#line 831 "dhcp6_parser.yy"
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
#line 837 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1632 "dhcp6_parser.cc"
    break;

  case 195: // $@32: %empty
#line 844 "dhcp6_parser.yy"
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
#line 850 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1655 "dhcp6_parser.cc"
    break;

  case 197: // $@33: %empty
#line 857 "dhcp6_parser.yy"
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
#line 863 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1676 "dhcp6_parser.cc"
    break;

  case 203: // not_empty_database_list: not_empty_database_list ","
#line 874 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1684 "dhcp6_parser.cc"
    break;

  case 204: // $@34: %empty
#line 879 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1694 "dhcp6_parser.cc"
    break;

  case 205: // database: "{" $@34 database_map_params "}"
#line 883 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1704 "dhcp6_parser.cc"
    break;

  case 208: // database_map_params: database_map_params ","
#line 891 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1712 "dhcp6_parser.cc"
    break;

  case 231: // $@35: %empty
#line 920 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1721 "dhcp6_parser.cc"
    break;

  case 232: // database_type: "type" $@35 ":" db_type
#line 923 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1730 "dhcp6_parser.cc"
    break;

  case 233: // db_type: "memfile"
#line 928 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1736 "dhcp6_parser.cc"
    break;

  case 234: // db_type: "mysql"
#line 929 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1742 "dhcp6_parser.cc"
    break;

  case 235: // db_type: "postgresql"
#line 930 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1748 "dhcp6_parser.cc"
    break;

  case 236: // db_type: "cql"
#line 931 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1754 "dhcp6_parser.cc"
    break;

  case 237: // $@36: %empty
#line 934 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1763 "dhcp6_parser.cc"
    break;

  case 238: // user: "user" $@36 ":" "constant string"
#line 937 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1773 "dhcp6_parser.cc"
    break;

  case 239: // $@37: %empty
#line 943 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 240: // password: "password" $@37 ":" "constant string"
#line 946 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 241: // $@38: %empty
#line 952 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1801 "dhcp6_parser.cc"
    break;

  case 242: // host: "host" $@38 ":" "constant string"
#line 955 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc"
    break;

  case 243: // port: "port" ":" "integer"
#line 961 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1821 "dhcp6_parser.cc"
    break;

  case 244: // $@39: %empty
#line 967 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1830 "dhcp6_parser.cc"
    break;

  case 245: // name: "name" $@39 ":" "constant string"
#line 970 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1840 "dhcp6_parser.cc"
    break;

  case 246: // persist: "persist" ":" "boolean"
#line 976 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1850 "dhcp6_parser.cc"
    break;

  case 247: // lfc_interval: "lfc-interval" ":" "integer"
#line 982 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1860 "dhcp6_parser.cc"
    break;

  case 248: // readonly: "readonly" ":" "boolean"
#line 988 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 249: // connect_timeout: "connect-timeout" ":" "integer"
#line 994 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1880 "dhcp6_parser.cc"
    break;

  case 250: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1000 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1890 "dhcp6_parser.cc"
    break;

  case 251: // $@40: %empty
#line 1006 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 252: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1009 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1908 "dhcp6_parser.cc"
    break;

  case 253: // on_fail_mode: "stop-retry-exit"
#line 1014 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1914 "dhcp6_parser.cc"
    break;

  case 254: // on_fail_mode: "serve-retry-exit"
#line 1015 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1920 "dhcp6_parser.cc"
    break;

  case 255: // on_fail_mode: "serve-retry-continue"
#line 1016 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1926 "dhcp6_parser.cc"
    break;

  case 256: // max_row_errors: "max-row-errors" ":" "integer"
#line 1019 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 257: // request_timeout: "request-timeout" ":" "integer"
#line 1025 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 258: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1031 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 259: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1037 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 260: // $@41: %empty
#line 1043 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 261: // contact_points: "contact-points" $@41 ":" "constant string"
#line 1046 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 262: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1052 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 263: // $@42: %empty
#line 1058 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2004 "dhcp6_parser.cc"
    break;

  case 264: // keyspace: "keyspace" $@42 ":" "constant string"
#line 1061 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2014 "dhcp6_parser.cc"
    break;

  case 265: // $@43: %empty
#line 1067 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2023 "dhcp6_parser.cc"
    break;

  case 266: // consistency: "consistency" $@43 ":" "constant string"
#line 1070 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2033 "dhcp6_parser.cc"
    break;

  case 267: // $@44: %empty
#line 1076 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2042 "dhcp6_parser.cc"
    break;

  case 268: // serial_consistency: "serial-consistency" $@44 ":" "constant string"
#line 1079 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 269: // $@45: %empty
#line 1085 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2064 "dhcp6_parser.cc"
    break;

  case 270: // sanity_checks: "sanity-checks" $@45 ":" "{" sanity_checks_params "}"
#line 1091 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2073 "dhcp6_parser.cc"
    break;

  case 273: // sanity_checks_params: sanity_checks_params ","
#line 1098 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2081 "dhcp6_parser.cc"
    break;

  case 275: // $@46: %empty
#line 1105 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2090 "dhcp6_parser.cc"
    break;

  case 276: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1108 "dhcp6_parser.yy"
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
#line 2110 "dhcp6_parser.cc"
    break;

  case 277: // $@47: %empty
#line 1124 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2122 "dhcp6_parser.cc"
    break;

  case 278: // mac_sources: "mac-sources" $@47 ":" "[" mac_sources_list "]"
#line 1130 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 281: // mac_sources_list: mac_sources_list ","
#line 1137 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2139 "dhcp6_parser.cc"
    break;

  case 284: // duid_id: "duid"
#line 1146 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 285: // string_id: "constant string"
#line 1151 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2157 "dhcp6_parser.cc"
    break;

  case 286: // $@48: %empty
#line 1156 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2169 "dhcp6_parser.cc"
    break;

  case 287: // host_reservation_identifiers: "host-reservation-identifiers" $@48 ":" "[" host_reservation_identifiers_list "]"
#line 1162 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2178 "dhcp6_parser.cc"
    break;

  case 290: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1169 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2186 "dhcp6_parser.cc"
    break;

  case 294: // hw_address_id: "hw-address"
#line 1179 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2195 "dhcp6_parser.cc"
    break;

  case 295: // flex_id: "flex-id"
#line 1184 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2204 "dhcp6_parser.cc"
    break;

  case 296: // $@49: %empty
#line 1191 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2216 "dhcp6_parser.cc"
    break;

  case 297: // relay_supplied_options: "relay-supplied-options" $@49 ":" "[" list_content "]"
#line 1197 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 298: // $@50: %empty
#line 1204 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2237 "dhcp6_parser.cc"
    break;

  case 299: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1210 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 302: // multi_threading_params: multi_threading_params ","
#line 1219 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2256 "dhcp6_parser.cc"
    break;

  case 309: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1232 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2266 "dhcp6_parser.cc"
    break;

  case 310: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1238 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2276 "dhcp6_parser.cc"
    break;

  case 311: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1244 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2286 "dhcp6_parser.cc"
    break;

  case 312: // $@51: %empty
#line 1250 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2298 "dhcp6_parser.cc"
    break;

  case 313: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1256 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2307 "dhcp6_parser.cc"
    break;

  case 318: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1267 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2315 "dhcp6_parser.cc"
    break;

  case 319: // $@52: %empty
#line 1272 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2325 "dhcp6_parser.cc"
    break;

  case 320: // hooks_library: "{" $@52 hooks_params "}"
#line 1276 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 321: // $@53: %empty
#line 1282 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2345 "dhcp6_parser.cc"
    break;

  case 322: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1286 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 325: // hooks_params: hooks_params ","
#line 1294 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2363 "dhcp6_parser.cc"
    break;

  case 329: // $@54: %empty
#line 1304 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 330: // library: "library" $@54 ":" "constant string"
#line 1307 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2382 "dhcp6_parser.cc"
    break;

  case 331: // $@55: %empty
#line 1313 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2391 "dhcp6_parser.cc"
    break;

  case 332: // parameters: "parameters" $@55 ":" map_value
#line 1316 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2400 "dhcp6_parser.cc"
    break;

  case 333: // $@56: %empty
#line 1322 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2412 "dhcp6_parser.cc"
    break;

  case 334: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1328 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2422 "dhcp6_parser.cc"
    break;

  case 337: // expired_leases_params: expired_leases_params ","
#line 1336 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2430 "dhcp6_parser.cc"
    break;

  case 344: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1349 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2440 "dhcp6_parser.cc"
    break;

  case 345: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1355 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 346: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1361 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2460 "dhcp6_parser.cc"
    break;

  case 347: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1367 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2470 "dhcp6_parser.cc"
    break;

  case 348: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1373 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2480 "dhcp6_parser.cc"
    break;

  case 349: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1379 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2490 "dhcp6_parser.cc"
    break;

  case 350: // $@57: %empty
#line 1388 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2502 "dhcp6_parser.cc"
    break;

  case 351: // subnet6_list: "subnet6" $@57 ":" "[" subnet6_list_content "]"
#line 1394 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc"
    break;

  case 356: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1408 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2519 "dhcp6_parser.cc"
    break;

  case 357: // $@58: %empty
#line 1417 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2529 "dhcp6_parser.cc"
    break;

  case 358: // subnet6: "{" $@58 subnet6_params "}"
#line 1421 "dhcp6_parser.yy"
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
#line 2555 "dhcp6_parser.cc"
    break;

  case 359: // $@59: %empty
#line 1443 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2565 "dhcp6_parser.cc"
    break;

  case 360: // sub_subnet6: "{" $@59 subnet6_params "}"
#line 1447 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2575 "dhcp6_parser.cc"
    break;

  case 363: // subnet6_params: subnet6_params ","
#line 1456 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2583 "dhcp6_parser.cc"
    break;

  case 407: // $@60: %empty
#line 1507 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2592 "dhcp6_parser.cc"
    break;

  case 408: // subnet: "subnet" $@60 ":" "constant string"
#line 1510 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2602 "dhcp6_parser.cc"
    break;

  case 409: // $@61: %empty
#line 1516 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2611 "dhcp6_parser.cc"
    break;

  case 410: // interface: "interface" $@61 ":" "constant string"
#line 1519 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc"
    break;

  case 411: // $@62: %empty
#line 1525 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp6_parser.cc"
    break;

  case 412: // interface_id: "interface-id" $@62 ":" "constant string"
#line 1528 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 413: // $@63: %empty
#line 1534 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp6_parser.cc"
    break;

  case 414: // client_class: "client-class" $@63 ":" "constant string"
#line 1537 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2659 "dhcp6_parser.cc"
    break;

  case 415: // $@64: %empty
#line 1543 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 416: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1549 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 417: // reservations_global: "reservations-global" ":" "boolean"
#line 1554 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2690 "dhcp6_parser.cc"
    break;

  case 418: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1560 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2700 "dhcp6_parser.cc"
    break;

  case 419: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1566 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2710 "dhcp6_parser.cc"
    break;

  case 420: // $@65: %empty
#line 1572 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2719 "dhcp6_parser.cc"
    break;

  case 421: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1575 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc"
    break;

  case 422: // hr_mode: "disabled"
#line 1580 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2734 "dhcp6_parser.cc"
    break;

  case 423: // hr_mode: "out-of-pool"
#line 1581 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2740 "dhcp6_parser.cc"
    break;

  case 424: // hr_mode: "global"
#line 1582 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2746 "dhcp6_parser.cc"
    break;

  case 425: // hr_mode: "all"
#line 1583 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2752 "dhcp6_parser.cc"
    break;

  case 426: // id: "id" ":" "integer"
#line 1586 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 427: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1592 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2772 "dhcp6_parser.cc"
    break;

  case 428: // $@66: %empty
#line 1600 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2784 "dhcp6_parser.cc"
    break;

  case 429: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1606 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc"
    break;

  case 434: // shared_networks_list: shared_networks_list ","
#line 1619 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2801 "dhcp6_parser.cc"
    break;

  case 435: // $@67: %empty
#line 1624 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 436: // shared_network: "{" $@67 shared_network_params "}"
#line 1628 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2819 "dhcp6_parser.cc"
    break;

  case 439: // shared_network_params: shared_network_params ","
#line 1634 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2827 "dhcp6_parser.cc"
    break;

  case 480: // $@68: %empty
#line 1685 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2839 "dhcp6_parser.cc"
    break;

  case 481: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1691 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2848 "dhcp6_parser.cc"
    break;

  case 482: // $@69: %empty
#line 1699 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2857 "dhcp6_parser.cc"
    break;

  case 483: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1702 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2865 "dhcp6_parser.cc"
    break;

  case 488: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1714 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2873 "dhcp6_parser.cc"
    break;

  case 489: // $@70: %empty
#line 1721 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2883 "dhcp6_parser.cc"
    break;

  case 490: // option_def_entry: "{" $@70 option_def_params "}"
#line 1725 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 491: // $@71: %empty
#line 1736 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 492: // sub_option_def: "{" $@71 option_def_params "}"
#line 1740 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2917 "dhcp6_parser.cc"
    break;

  case 497: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1756 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2925 "dhcp6_parser.cc"
    break;

  case 509: // code: "code" ":" "integer"
#line 1775 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 511: // $@72: %empty
#line 1783 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2944 "dhcp6_parser.cc"
    break;

  case 512: // option_def_type: "type" $@72 ":" "constant string"
#line 1786 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2954 "dhcp6_parser.cc"
    break;

  case 513: // $@73: %empty
#line 1792 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc"
    break;

  case 514: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1795 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 515: // $@74: %empty
#line 1801 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp6_parser.cc"
    break;

  case 516: // space: "space" $@74 ":" "constant string"
#line 1804 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2992 "dhcp6_parser.cc"
    break;

  case 518: // $@75: %empty
#line 1812 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3001 "dhcp6_parser.cc"
    break;

  case 519: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1815 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 520: // option_def_array: "array" ":" "boolean"
#line 1821 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 521: // $@76: %empty
#line 1831 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3033 "dhcp6_parser.cc"
    break;

  case 522: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1837 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3042 "dhcp6_parser.cc"
    break;

  case 527: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1852 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3050 "dhcp6_parser.cc"
    break;

  case 528: // $@77: %empty
#line 1859 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3060 "dhcp6_parser.cc"
    break;

  case 529: // option_data_entry: "{" $@77 option_data_params "}"
#line 1863 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3069 "dhcp6_parser.cc"
    break;

  case 530: // $@78: %empty
#line 1871 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3079 "dhcp6_parser.cc"
    break;

  case 531: // sub_option_data: "{" $@78 option_data_params "}"
#line 1875 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3088 "dhcp6_parser.cc"
    break;

  case 536: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1891 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3096 "dhcp6_parser.cc"
    break;

  case 547: // $@79: %empty
#line 1911 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 548: // option_data_data: "data" $@79 ":" "constant string"
#line 1914 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3115 "dhcp6_parser.cc"
    break;

  case 551: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1924 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 552: // option_data_always_send: "always-send" ":" "boolean"
#line 1930 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 553: // $@80: %empty
#line 1939 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3147 "dhcp6_parser.cc"
    break;

  case 554: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1945 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3156 "dhcp6_parser.cc"
    break;

  case 559: // not_empty_pools_list: not_empty_pools_list ","
#line 1958 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3164 "dhcp6_parser.cc"
    break;

  case 560: // $@81: %empty
#line 1963 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3174 "dhcp6_parser.cc"
    break;

  case 561: // pool_list_entry: "{" $@81 pool_params "}"
#line 1967 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3184 "dhcp6_parser.cc"
    break;

  case 562: // $@82: %empty
#line 1973 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3194 "dhcp6_parser.cc"
    break;

  case 563: // sub_pool6: "{" $@82 pool_params "}"
#line 1977 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3204 "dhcp6_parser.cc"
    break;

  case 566: // pool_params: pool_params ","
#line 1985 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3212 "dhcp6_parser.cc"
    break;

  case 574: // $@83: %empty
#line 1999 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 575: // pool_entry: "pool" $@83 ":" "constant string"
#line 2002 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 576: // $@84: %empty
#line 2008 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 577: // user_context: "user-context" $@84 ":" map_value
#line 2010 "dhcp6_parser.yy"
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
#line 3266 "dhcp6_parser.cc"
    break;

  case 578: // $@85: %empty
#line 2033 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 579: // comment: "comment" $@85 ":" "constant string"
#line 2035 "dhcp6_parser.yy"
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
#line 3303 "dhcp6_parser.cc"
    break;

  case 580: // $@86: %empty
#line 2063 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 581: // pd_pools_list: "pd-pools" $@86 ":" "[" pd_pools_list_content "]"
#line 2069 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3324 "dhcp6_parser.cc"
    break;

  case 586: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2082 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3332 "dhcp6_parser.cc"
    break;

  case 587: // $@87: %empty
#line 2087 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3342 "dhcp6_parser.cc"
    break;

  case 588: // pd_pool_entry: "{" $@87 pd_pool_params "}"
#line 2091 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3354 "dhcp6_parser.cc"
    break;

  case 589: // $@88: %empty
#line 2099 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3364 "dhcp6_parser.cc"
    break;

  case 590: // sub_pd_pool: "{" $@88 pd_pool_params "}"
#line 2103 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3376 "dhcp6_parser.cc"
    break;

  case 593: // pd_pool_params: pd_pool_params ","
#line 2113 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3384 "dhcp6_parser.cc"
    break;

  case 605: // $@89: %empty
#line 2131 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 606: // pd_prefix: "prefix" $@89 ":" "constant string"
#line 2134 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc"
    break;

  case 607: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2140 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3413 "dhcp6_parser.cc"
    break;

  case 608: // $@90: %empty
#line 2146 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3422 "dhcp6_parser.cc"
    break;

  case 609: // excluded_prefix: "excluded-prefix" $@90 ":" "constant string"
#line 2149 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3432 "dhcp6_parser.cc"
    break;

  case 610: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2155 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3442 "dhcp6_parser.cc"
    break;

  case 611: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2161 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3452 "dhcp6_parser.cc"
    break;

  case 612: // $@91: %empty
#line 2170 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3464 "dhcp6_parser.cc"
    break;

  case 613: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2176 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3473 "dhcp6_parser.cc"
    break;

  case 618: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2187 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3481 "dhcp6_parser.cc"
    break;

  case 619: // $@92: %empty
#line 2192 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3491 "dhcp6_parser.cc"
    break;

  case 620: // reservation: "{" $@92 reservation_params "}"
#line 2196 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3500 "dhcp6_parser.cc"
    break;

  case 621: // $@93: %empty
#line 2201 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3510 "dhcp6_parser.cc"
    break;

  case 622: // sub_reservation: "{" $@93 reservation_params "}"
#line 2205 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3519 "dhcp6_parser.cc"
    break;

  case 627: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2216 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3527 "dhcp6_parser.cc"
    break;

  case 639: // $@94: %empty
#line 2235 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3539 "dhcp6_parser.cc"
    break;

  case 640: // ip_addresses: "ip-addresses" $@94 ":" list_strings
#line 2241 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3548 "dhcp6_parser.cc"
    break;

  case 641: // $@95: %empty
#line 2246 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 642: // prefixes: "prefixes" $@95 ":" list_strings
#line 2252 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3569 "dhcp6_parser.cc"
    break;

  case 643: // $@96: %empty
#line 2257 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 644: // duid: "duid" $@96 ":" "constant string"
#line 2260 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3588 "dhcp6_parser.cc"
    break;

  case 645: // $@97: %empty
#line 2266 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3597 "dhcp6_parser.cc"
    break;

  case 646: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2269 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3607 "dhcp6_parser.cc"
    break;

  case 647: // $@98: %empty
#line 2275 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 648: // hostname: "hostname" $@98 ":" "constant string"
#line 2278 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3626 "dhcp6_parser.cc"
    break;

  case 649: // $@99: %empty
#line 2284 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp6_parser.cc"
    break;

  case 650: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2287 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3645 "dhcp6_parser.cc"
    break;

  case 651: // $@100: %empty
#line 2293 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3657 "dhcp6_parser.cc"
    break;

  case 652: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2299 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 653: // $@101: %empty
#line 2307 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3678 "dhcp6_parser.cc"
    break;

  case 654: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2313 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 657: // $@102: %empty
#line 2322 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 658: // ip_address: "ip-address" $@102 ":" "constant string"
#line 2325 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 659: // $@103: %empty
#line 2334 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3718 "dhcp6_parser.cc"
    break;

  case 660: // client_classes: "client-classes" $@103 ":" "[" client_classes_list "]"
#line 2340 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 663: // client_classes_list: client_classes_list ","
#line 2347 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3735 "dhcp6_parser.cc"
    break;

  case 664: // $@104: %empty
#line 2352 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3745 "dhcp6_parser.cc"
    break;

  case 665: // client_class_entry: "{" $@104 client_class_params "}"
#line 2356 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 670: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2368 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3763 "dhcp6_parser.cc"
    break;

  case 685: // $@105: %empty
#line 2390 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 686: // client_class_test: "test" $@105 ":" "constant string"
#line 2393 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3782 "dhcp6_parser.cc"
    break;

  case 687: // only_if_required: "only-if-required" ":" "boolean"
#line 2399 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3792 "dhcp6_parser.cc"
    break;

  case 688: // $@106: %empty
#line 2408 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 689: // server_id: "server-id" $@106 ":" "{" server_id_params "}"
#line 2414 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 692: // server_id_params: server_id_params ","
#line 2423 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3823 "dhcp6_parser.cc"
    break;

  case 702: // $@107: %empty
#line 2439 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3832 "dhcp6_parser.cc"
    break;

  case 703: // server_id_type: "type" $@107 ":" duid_type
#line 2442 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3841 "dhcp6_parser.cc"
    break;

  case 704: // duid_type: "LLT"
#line 2447 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3847 "dhcp6_parser.cc"
    break;

  case 705: // duid_type: "EN"
#line 2448 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3853 "dhcp6_parser.cc"
    break;

  case 706: // duid_type: "LL"
#line 2449 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3859 "dhcp6_parser.cc"
    break;

  case 707: // htype: "htype" ":" "integer"
#line 2452 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3869 "dhcp6_parser.cc"
    break;

  case 708: // $@108: %empty
#line 2458 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3878 "dhcp6_parser.cc"
    break;

  case 709: // identifier: "identifier" $@108 ":" "constant string"
#line 2461 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3888 "dhcp6_parser.cc"
    break;

  case 710: // time: "time" ":" "integer"
#line 2467 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3898 "dhcp6_parser.cc"
    break;

  case 711: // enterprise_id: "enterprise-id" ":" "integer"
#line 2473 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3908 "dhcp6_parser.cc"
    break;

  case 712: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2481 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3918 "dhcp6_parser.cc"
    break;

  case 713: // $@109: %empty
#line 2489 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 714: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2495 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 717: // control_socket_params: control_socket_params ","
#line 2502 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3947 "dhcp6_parser.cc"
    break;

  case 723: // $@110: %empty
#line 2514 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3956 "dhcp6_parser.cc"
    break;

  case 724: // socket_type: "socket-type" $@110 ":" "constant string"
#line 2517 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3966 "dhcp6_parser.cc"
    break;

  case 725: // $@111: %empty
#line 2523 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 726: // socket_name: "socket-name" $@111 ":" "constant string"
#line 2526 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3985 "dhcp6_parser.cc"
    break;

  case 727: // $@112: %empty
#line 2535 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3997 "dhcp6_parser.cc"
    break;

  case 728: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2541 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 731: // queue_control_params: queue_control_params ","
#line 2550 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4016 "dhcp6_parser.cc"
    break;

  case 738: // enable_queue: "enable-queue" ":" "boolean"
#line 2563 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4026 "dhcp6_parser.cc"
    break;

  case 739: // $@113: %empty
#line 2569 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4035 "dhcp6_parser.cc"
    break;

  case 740: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2572 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4045 "dhcp6_parser.cc"
    break;

  case 741: // capacity: "capacity" ":" "integer"
#line 2578 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4055 "dhcp6_parser.cc"
    break;

  case 742: // $@114: %empty
#line 2584 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4064 "dhcp6_parser.cc"
    break;

  case 743: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2587 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4073 "dhcp6_parser.cc"
    break;

  case 744: // $@115: %empty
#line 2594 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4085 "dhcp6_parser.cc"
    break;

  case 745: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2600 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4096 "dhcp6_parser.cc"
    break;

  case 746: // $@116: %empty
#line 2607 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4106 "dhcp6_parser.cc"
    break;

  case 747: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2611 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4116 "dhcp6_parser.cc"
    break;

  case 750: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2619 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4124 "dhcp6_parser.cc"
    break;

  case 769: // enable_updates: "enable-updates" ":" "boolean"
#line 2644 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4134 "dhcp6_parser.cc"
    break;

  case 770: // $@117: %empty
#line 2651 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4143 "dhcp6_parser.cc"
    break;

  case 771: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2654 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4153 "dhcp6_parser.cc"
    break;

  case 772: // $@118: %empty
#line 2660 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4162 "dhcp6_parser.cc"
    break;

  case 773: // server_ip: "server-ip" $@118 ":" "constant string"
#line 2663 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4172 "dhcp6_parser.cc"
    break;

  case 774: // server_port: "server-port" ":" "integer"
#line 2669 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4182 "dhcp6_parser.cc"
    break;

  case 775: // $@119: %empty
#line 2675 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4191 "dhcp6_parser.cc"
    break;

  case 776: // sender_ip: "sender-ip" $@119 ":" "constant string"
#line 2678 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4201 "dhcp6_parser.cc"
    break;

  case 777: // sender_port: "sender-port" ":" "integer"
#line 2684 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4211 "dhcp6_parser.cc"
    break;

  case 778: // max_queue_size: "max-queue-size" ":" "integer"
#line 2690 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4221 "dhcp6_parser.cc"
    break;

  case 779: // $@120: %empty
#line 2696 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4230 "dhcp6_parser.cc"
    break;

  case 780: // ncr_protocol: "ncr-protocol" $@120 ":" ncr_protocol_value
#line 2699 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4239 "dhcp6_parser.cc"
    break;

  case 781: // ncr_protocol_value: "UDP"
#line 2705 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4245 "dhcp6_parser.cc"
    break;

  case 782: // ncr_protocol_value: "TCP"
#line 2706 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4251 "dhcp6_parser.cc"
    break;

  case 783: // $@121: %empty
#line 2709 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4260 "dhcp6_parser.cc"
    break;

  case 784: // ncr_format: "ncr-format" $@121 ":" "JSON"
#line 2712 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4270 "dhcp6_parser.cc"
    break;

  case 785: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2719 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4280 "dhcp6_parser.cc"
    break;

  case 786: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2726 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4290 "dhcp6_parser.cc"
    break;

  case 787: // $@122: %empty
#line 2733 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4299 "dhcp6_parser.cc"
    break;

  case 788: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2736 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4308 "dhcp6_parser.cc"
    break;

  case 789: // $@123: %empty
#line 2742 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4317 "dhcp6_parser.cc"
    break;

  case 790: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2745 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4327 "dhcp6_parser.cc"
    break;

  case 791: // $@124: %empty
#line 2752 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4336 "dhcp6_parser.cc"
    break;

  case 792: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2755 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4346 "dhcp6_parser.cc"
    break;

  case 793: // $@125: %empty
#line 2762 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4355 "dhcp6_parser.cc"
    break;

  case 794: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2765 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4365 "dhcp6_parser.cc"
    break;

  case 795: // $@126: %empty
#line 2774 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4377 "dhcp6_parser.cc"
    break;

  case 796: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2780 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4387 "dhcp6_parser.cc"
    break;

  case 797: // $@127: %empty
#line 2786 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4397 "dhcp6_parser.cc"
    break;

  case 798: // sub_config_control: "{" $@127 config_control_params "}"
#line 2790 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4406 "dhcp6_parser.cc"
    break;

  case 801: // config_control_params: config_control_params ","
#line 2798 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4414 "dhcp6_parser.cc"
    break;

  case 804: // $@128: %empty
#line 2808 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4426 "dhcp6_parser.cc"
    break;

  case 805: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2814 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4435 "dhcp6_parser.cc"
    break;

  case 806: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2819 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4445 "dhcp6_parser.cc"
    break;

  case 807: // $@129: %empty
#line 2827 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4457 "dhcp6_parser.cc"
    break;

  case 808: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2833 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4466 "dhcp6_parser.cc"
    break;

  case 811: // loggers_entries: loggers_entries ","
#line 2842 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4474 "dhcp6_parser.cc"
    break;

  case 812: // $@130: %empty
#line 2848 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4484 "dhcp6_parser.cc"
    break;

  case 813: // logger_entry: "{" $@130 logger_params "}"
#line 2852 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4492 "dhcp6_parser.cc"
    break;

  case 816: // logger_params: logger_params ","
#line 2858 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4500 "dhcp6_parser.cc"
    break;

  case 824: // debuglevel: "debuglevel" ":" "integer"
#line 2872 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4510 "dhcp6_parser.cc"
    break;

  case 825: // $@131: %empty
#line 2878 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4519 "dhcp6_parser.cc"
    break;

  case 826: // severity: "severity" $@131 ":" "constant string"
#line 2881 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4529 "dhcp6_parser.cc"
    break;

  case 827: // $@132: %empty
#line 2887 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4541 "dhcp6_parser.cc"
    break;

  case 828: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2893 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4550 "dhcp6_parser.cc"
    break;

  case 831: // output_options_list_content: output_options_list_content ","
#line 2900 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4558 "dhcp6_parser.cc"
    break;

  case 832: // $@133: %empty
#line 2905 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4568 "dhcp6_parser.cc"
    break;

  case 833: // output_entry: "{" $@133 output_params_list "}"
#line 2909 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4576 "dhcp6_parser.cc"
    break;

  case 836: // output_params_list: output_params_list ","
#line 2915 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4584 "dhcp6_parser.cc"
    break;

  case 842: // $@134: %empty
#line 2927 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4593 "dhcp6_parser.cc"
    break;

  case 843: // output: "output" $@134 ":" "constant string"
#line 2930 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4603 "dhcp6_parser.cc"
    break;

  case 844: // flush: "flush" ":" "boolean"
#line 2936 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4613 "dhcp6_parser.cc"
    break;

  case 845: // maxsize: "maxsize" ":" "integer"
#line 2942 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4623 "dhcp6_parser.cc"
    break;

  case 846: // maxver: "maxver" ":" "integer"
#line 2948 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4633 "dhcp6_parser.cc"
    break;

  case 847: // $@135: %empty
#line 2954 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4642 "dhcp6_parser.cc"
    break;

  case 848: // pattern: "pattern" $@135 ":" "constant string"
#line 2957 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4652 "dhcp6_parser.cc"
    break;

  case 849: // $@136: %empty
#line 2963 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4664 "dhcp6_parser.cc"
    break;

  case 850: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2969 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4673 "dhcp6_parser.cc"
    break;

  case 853: // compatibility_params: compatibility_params ","
#line 2976 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4681 "dhcp6_parser.cc"
    break;

  case 856: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2985 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4691 "dhcp6_parser.cc"
    break;


#line 4695 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -985;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     423,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,    48,    30,    31,    47,    58,
     129,   137,   158,   172,   225,   249,   251,   253,   292,   295,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,    30,  -141,
      91,   141,    24,   647,   183,   215,   252,   102,    87,   284,
     -79,   435,   208,  -985,   110,   316,   309,   321,   327,  -985,
      78,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   329,   354,
     355,   356,   365,   378,   399,   400,   415,   422,   424,   425,
     431,   432,  -985,   433,   434,   436,   437,   440,  -985,  -985,
    -985,   441,   442,   443,  -985,  -985,  -985,   444,  -985,  -985,
    -985,  -985,   448,   449,   450,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,   452,  -985,  -985,  -985,  -985,  -985,
    -985,   453,  -985,  -985,   456,  -985,    94,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   458,  -985,   123,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,   459,   460,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,   130,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   143,
    -985,  -985,  -985,  -985,  -985,   462,  -985,   464,   466,  -985,
    -985,  -985,  -985,  -985,  -985,   160,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   413,   468,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   465,  -985,  -985,   472,  -985,  -985,  -985,
     473,  -985,  -985,   479,   469,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   484,   485,
    -985,  -985,  -985,  -985,   483,   489,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   166,  -985,
    -985,  -985,   493,  -985,  -985,   495,  -985,   498,   499,  -985,
    -985,   500,   501,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
     170,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   502,   177,
    -985,  -985,  -985,  -985,    30,    30,  -985,   298,   505,  -985,
    -985,   507,   508,   509,   511,   512,   516,   311,   315,   317,
     325,   326,   328,   330,   331,   333,   335,   338,   339,   332,
     342,   519,   344,   345,   346,   348,   349,   533,   535,   552,
     351,   358,   359,   553,   563,   564,   363,   570,   571,   573,
     574,   369,   371,   372,   581,   583,   585,   586,   587,   588,
     590,   605,   606,   401,   608,   609,   610,   611,   629,   630,
     426,   632,   633,  -985,   141,  -985,   635,   428,    24,  -985,
     637,   638,   639,   641,   642,   438,   445,   643,   645,   646,
     647,  -985,   648,   183,  -985,   649,   446,   650,   451,   454,
     215,  -985,   651,   654,   655,   656,   658,   659,   661,  -985,
     252,  -985,   662,   663,   461,   669,   670,   671,   467,  -985,
      87,   673,   470,   471,  -985,   284,   674,   676,    23,  -985,
     477,   677,   686,   481,   689,   514,   515,   704,   705,   510,
     520,   706,   707,   717,   722,   435,  -985,   729,   524,   208,
    -985,  -985,  -985,   732,   731,   530,   733,   735,   744,   745,
     736,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   544,  -985,  -985,  -985,  -985,
    -985,  -122,   545,   549,  -985,  -985,  -985,   754,   755,   756,
    -985,   757,   758,   554,   171,  -985,  -985,  -985,   761,   764,
     765,   766,   767,   769,   771,   770,   772,  -985,   773,   774,
     788,   789,   562,   569,  -985,   792,   791,  -985,   804,  -985,
    -985,   807,   808,   607,   612,   613,  -985,  -985,   804,   614,
     810,  -985,   615,  -985,   616,  -985,   617,  -985,  -985,  -985,
     804,   804,   804,   618,   623,   626,   631,  -985,   636,   640,
    -985,   644,   652,   657,  -985,  -985,   660,  -985,  -985,  -985,
     664,   758,  -985,  -985,   665,   666,  -985,   667,  -985,  -985,
     152,   672,  -985,  -985,  -122,   668,   675,   678,  -985,   809,
    -985,  -985,    30,   141,  -985,   208,    24,   310,   310,   811,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   812,
     813,   831,   832,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   -92,    30,   168,   700,   834,   839,   840,   148,    79,
     -47,    27,    61,   435,  -985,  -985,   843,  -158,  -985,  -985,
     845,   848,  -985,  -985,  -985,  -985,  -985,   -46,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,   811,  -985,   226,
     227,   240,  -985,  -985,  -985,  -985,   853,   854,   855,   856,
     859,  -985,   860,   861,  -985,  -985,  -985,  -985,   863,   864,
     866,   867,  -985,   265,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,   312,  -985,   872,   869,
    -985,  -985,   873,   877,  -985,  -985,   875,   879,  -985,  -985,
     880,   882,  -985,  -985,   883,   885,  -985,  -985,  -985,    81,
    -985,  -985,  -985,   884,  -985,  -985,  -985,    85,  -985,  -985,
    -985,  -985,   313,  -985,  -985,  -985,   109,  -985,  -985,   886,
     888,  -985,  -985,   887,   891,  -985,   892,   893,   894,   895,
     896,   897,   380,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   898,   899,   900,  -985,  -985,  -985,  -985,   381,
    -985,  -985,  -985,  -985,  -985,  -985,   901,   902,   903,  -985,
     382,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   383,  -985,  -985,  -985,   904,  -985,   905,  -985,
    -985,  -985,   390,  -985,  -985,  -985,  -985,  -985,   391,  -985,
     131,  -985,   906,  -985,   392,  -985,  -985,   702,  -985,   889,
     909,  -985,  -985,   907,   911,  -985,  -985,  -985,   910,  -985,
     913,  -985,  -985,  -985,   916,   917,   918,   919,   714,   713,
     716,   715,   718,   926,   721,   723,   930,   932,   933,   940,
     737,   743,   747,   746,   310,  -985,  -985,   310,  -985,   811,
     647,  -985,   812,    87,  -985,   813,   284,  -985,   831,   734,
    -985,   832,   -92,  -985,  -985,   168,  -985,   942,   700,  -985,
      22,   834,  -985,   252,  -985,   839,   -79,  -985,   840,   750,
     752,   753,   775,   780,   790,   148,  -985,   963,   980,   793,
     797,   799,    79,  -985,   787,   800,   816,   -47,  -985,  1014,
    1018,    27,  -985,   819,  1019,   841,  1040,    61,  -985,  -985,
     221,   843,  -985,   862,  -158,  -985,  -985,  1061,   914,   183,
    -985,   845,   215,  -985,   848,  1073,  -985,  -985,   409,   871,
     874,   876,  -985,  -985,  -985,  -985,  -985,   878,  -985,  -985,
     207,   881,   890,   908,  -985,  -985,  -985,  -985,  -985,   393,
    -985,   394,  -985,  1078,  -985,  1080,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   402,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,   912,  -985,  -985,  1085,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  1083,  1089,  -985,
    -985,  -985,  -985,  -985,  1086,  -985,   404,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,    45,   915,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   920,   921,  -985,  -985,   922,
    -985,    30,  -985,  -985,  1091,  -985,  -985,  -985,  -985,  -985,
     408,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   923,
     410,  -985,   414,  -985,   924,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   734,  -985,  -985,  1092,   925,
    -985,    22,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  1093,   928,  1094,   221,  -985,  -985,  -985,
    -985,  -985,  -985,   927,  -985,  -985,  1088,  -985,   931,  -985,
    -985,  1095,  -985,  -985,   263,  -985,   181,  1095,  -985,  -985,
    1096,  1097,  1099,  -985,   417,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  1100,   929,   936,   938,  1101,   181,  -985,   934,
    -985,  -985,  -985,   941,  -985,  -985,  -985
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   180,     9,   359,    11,
     562,    13,   589,    15,   621,    17,   482,    19,   491,    21,
     530,    23,   321,    25,   746,    27,   797,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   623,     0,   493,   532,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   135,   795,   178,   193,   195,   197,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,     0,     0,     0,     0,     0,   154,   161,
     163,     0,     0,     0,   350,   480,   521,     0,   428,   576,
     578,   420,     0,     0,     0,   277,   296,   286,   269,   659,
     612,   312,   333,   688,     0,   298,   713,   727,   744,   167,
     169,     0,   807,   849,     0,   134,     0,    69,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   111,   112,   113,
     114,   115,    81,   119,   120,   121,   122,   123,   124,   125,
     126,   117,   118,   127,   128,   129,   106,   133,   131,    84,
      85,    86,    87,   103,    88,    90,    89,   130,    94,    95,
      82,   108,   109,   110,   107,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   116,   132,
     190,     0,   189,     0,   182,   185,   186,   187,   188,   553,
     580,   407,   409,   411,     0,     0,   415,   413,   653,   406,
     364,   365,   366,   367,   368,   369,   370,   371,   390,   391,
     392,   393,   394,   397,   398,   399,   400,   401,   402,   403,
     404,   395,   396,   405,     0,   361,   375,   376,   377,   380,
     381,   384,   385,   386,   383,   378,   379,   372,   373,   388,
     389,   374,   382,   387,   574,   573,   569,   570,   568,     0,
     564,   567,   571,   572,   605,     0,   608,     0,     0,   604,
     598,   599,   597,   602,   603,     0,   591,   594,   595,   600,
     601,   596,   651,   639,   641,   643,   645,   647,   649,   638,
     635,   636,   637,     0,   624,   625,   630,   631,   628,   632,
     633,   634,   629,     0,   511,   244,     0,   515,   513,   518,
       0,   507,   508,     0,   494,   495,   498,   510,   499,   500,
     501,   517,   502,   503,   504,   505,   506,   547,     0,     0,
     545,   546,   549,   550,     0,   533,   534,   537,   538,   539,
     540,   541,   542,   543,   544,   329,   331,   326,     0,   323,
     327,   328,     0,   770,   772,     0,   775,     0,     0,   779,
     783,     0,     0,   787,   789,   791,   793,   768,   766,   767,
       0,   748,   751,   763,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   764,   765,   804,     0,     0,
     799,   802,   803,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,   184,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     363,   360,     0,   566,   563,     0,     0,     0,     0,     0,
     593,   590,     0,     0,     0,     0,     0,     0,     0,   622,
     627,   483,     0,     0,     0,     0,     0,     0,     0,   492,
     497,     0,     0,     0,   531,   536,     0,     0,   325,   322,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   750,   747,     0,     0,   801,
     798,    51,    43,     0,     0,     0,     0,     0,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,     0,   172,   173,   151,   152,
     153,     0,     0,     0,   165,   166,   171,     0,     0,     0,
     176,     0,     0,     0,     0,   417,   418,   419,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   712,     0,     0,
       0,     0,     0,     0,   177,     0,     0,    70,     0,   192,
     183,     0,     0,     0,     0,     0,   426,   427,     0,     0,
       0,   362,     0,   565,     0,   607,     0,   610,   611,   592,
       0,     0,     0,     0,     0,     0,     0,   626,     0,     0,
     509,     0,     0,     0,   520,   496,     0,   551,   552,   535,
       0,     0,   324,   769,     0,     0,   774,     0,   777,   778,
       0,     0,   785,   786,     0,     0,     0,     0,   749,     0,
     806,   800,     0,     0,   136,     0,     0,     0,     0,   199,
     175,   156,   157,   158,   159,   160,   155,   162,   164,   352,
     484,   523,   430,    40,   577,   579,   422,   423,   424,   425,
     421,     0,    48,     0,     0,     0,   614,   314,     0,     0,
       0,     0,     0,     0,   168,   170,     0,     0,    53,   191,
     555,   582,   408,   410,   412,   416,   414,     0,   575,   606,
     609,   652,   640,   642,   644,   646,   648,   650,   512,   245,
     516,   514,   519,   548,   330,   332,   771,   773,   776,   781,
     782,   780,   784,   788,   790,   792,   794,   199,    44,     0,
       0,     0,   231,   237,   239,   241,     0,     0,     0,     0,
       0,   260,     0,     0,   251,   263,   265,   267,     0,     0,
       0,     0,   230,     0,   206,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   221,   222,   229,   223,   224,
     225,   219,   220,   226,   227,   228,     0,   204,     0,   200,
     201,   357,     0,   353,   354,   489,     0,   485,   486,   528,
       0,   524,   525,   435,     0,   431,   432,   284,   285,     0,
     279,   282,   283,     0,   294,   295,   291,     0,   288,   292,
     293,   275,     0,   271,   274,   664,     0,   661,   619,     0,
     615,   616,   319,     0,   315,   316,     0,     0,     0,     0,
       0,     0,     0,   335,   338,   339,   340,   341,   342,   343,
     702,   708,     0,     0,     0,   701,   698,   699,   700,     0,
     690,   693,   696,   694,   695,   697,     0,     0,     0,   308,
       0,   300,   303,   304,   305,   306,   307,   723,   725,   722,
     720,   721,     0,   715,   718,   719,     0,   739,     0,   742,
     735,   736,     0,   729,   732,   733,   734,   737,     0,   812,
       0,   809,     0,   855,     0,   851,   854,    55,   560,     0,
     556,   557,   587,     0,   583,   584,   657,   656,     0,   655,
       0,    64,   796,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   208,   194,   196,     0,   198,   203,
       0,   351,   356,   493,   481,   488,   532,   522,   527,     0,
     429,   434,   281,   278,   297,   290,   287,     0,   273,   270,
     666,   663,   660,   623,   613,   618,     0,   313,   318,     0,
       0,     0,     0,     0,     0,   337,   334,     0,     0,     0,
       0,     0,   692,   689,     0,     0,     0,   302,   299,     0,
       0,   717,   714,     0,     0,     0,     0,   731,   728,   745,
       0,   811,   808,     0,   853,   850,    57,     0,    56,     0,
     554,   559,     0,   581,   586,     0,   654,   805,     0,     0,
       0,     0,   243,   246,   247,   248,   249,     0,   262,   250,
       0,     0,     0,     0,   257,   258,   259,   256,   207,     0,
     202,     0,   355,     0,   487,     0,   526,   479,   454,   455,
     456,   458,   459,   460,   444,   445,   463,   464,   465,   466,
     467,   470,   471,   472,   473,   474,   475,   476,   477,   468,
     469,   478,   440,   441,   442,   443,   452,   453,   449,   450,
     451,   448,   457,     0,   437,   446,   461,   462,   447,   433,
     280,   289,     0,   272,   685,     0,   683,   677,   678,   679,
     680,   681,   682,   684,   674,   675,   676,     0,   667,   668,
     671,   672,   673,   662,     0,   617,     0,   317,   344,   345,
     346,   347,   348,   349,   336,     0,     0,   707,   710,   711,
     691,   309,   310,   311,   301,     0,     0,   716,   738,     0,
     741,     0,   730,   827,     0,   825,   823,   817,   821,   822,
       0,   814,   819,   820,   818,   810,   856,   852,    54,    59,
       0,   558,     0,   585,     0,   233,   234,   235,   236,   232,
     238,   240,   242,   261,   253,   254,   255,   252,   264,   266,
     268,   205,   358,   490,   529,   439,   436,   276,     0,     0,
     665,   670,   620,   320,   704,   705,   706,   703,   709,   724,
     726,   740,   743,     0,     0,     0,   816,   813,    58,   561,
     588,   658,   438,     0,   687,   669,     0,   824,     0,   815,
     686,     0,   826,   832,     0,   829,     0,   831,   828,   842,
       0,     0,     0,   847,     0,   834,   837,   838,   839,   840,
     841,   830,     0,     0,     0,     0,     0,   836,   833,     0,
     844,   845,   846,     0,   835,   843,   848
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,   -10,  -985,  -568,  -985,
     202,  -985,  -985,  -985,  -985,   374,  -985,  -566,  -985,  -985,
    -985,   -71,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   405,
     619,  -985,  -985,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19,  -985,    34,    37,    38,
      41,  -985,   416,    49,  -985,    52,  -985,    54,    55,    56,
    -985,    59,  -985,    62,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,   403,   620,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   320,  -985,   112,  -985,  -692,
     118,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   -45,  -985,  -728,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,    96,  -985,  -985,
    -985,  -985,  -985,   103,  -711,  -985,  -985,  -985,  -985,   101,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,    76,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,    92,  -985,  -985,  -985,    93,
     577,  -985,  -985,  -985,  -985,  -985,  -985,  -985,    99,  -985,
    -985,  -985,  -985,  -985,  -985,  -984,  -985,  -985,  -985,   120,
    -985,  -985,  -985,   126,   625,  -985,  -985,  -982,  -985,  -981,
    -985,    73,  -985,    75,  -985,    66,    69,    70,    72,  -985,
    -985,  -985,  -980,  -985,  -985,  -985,  -985,   116,  -985,  -985,
    -117,  1062,  -985,  -985,  -985,  -985,  -985,   144,  -985,  -985,
    -985,   149,  -985,   621,  -985,   -67,  -985,  -985,  -985,  -985,
    -985,   -64,  -985,  -985,  -985,  -985,  -985,     4,  -985,  -985,
    -985,   145,  -985,  -985,  -985,   150,  -985,   622,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,    80,
    -985,  -985,  -985,    86,   653,  -985,  -985,   -55,  -985,   -12,
    -985,  -985,  -985,  -985,  -985,    83,  -985,  -985,  -985,    82,
     679,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   -60,  -985,
    -985,  -985,   133,  -985,  -985,  -985,   136,  -985,   634,   406,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -978,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,   139,  -985,  -985,  -985,   -89,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,   127,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,   114,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,   111,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,   427,   624,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,   474,   602,  -985,  -985,
    -985,  -985,  -985,  -985,   115,  -985,  -985,   -94,  -985,  -985,
    -985,  -985,  -985,  -985,  -114,  -985,  -985,  -132,  -985,  -985,
    -985,  -985,  -985,  -985,  -985,  -985,  -985,  -985,   113,  -985
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     724,    87,    88,    41,    68,    84,    85,   749,   957,  1067,
    1068,   812,    43,    70,    90,   428,    91,    45,    71,   156,
     157,   158,   431,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   457,   716,   177,   458,   178,   459,   179,   180,   181,
     488,   182,   489,   183,   184,   185,   186,   451,   187,   188,
     189,   433,    47,    72,   223,   224,   225,   496,   226,   190,
     434,   191,   435,   192,   436,   838,   839,   840,   997,   813,
     814,   815,   974,  1229,   816,   975,   817,   976,   818,   977,
     819,   820,   533,   821,   822,   823,   824,   825,   826,   986,
    1237,   827,   828,   829,   830,   831,   983,   832,   833,   987,
     834,   988,   835,   989,   193,   477,   872,   873,   874,  1017,
     194,   474,   859,   860,   861,   862,   195,   476,   867,   868,
     869,   870,   196,   475,   197,   484,   920,   921,   922,   923,
     924,   198,   480,   883,   884,   885,  1026,    63,    80,   378,
     379,   380,   546,   381,   547,   199,   481,   892,   893,   894,
     895,   896,   897,   898,   899,   200,   463,   842,   843,   844,
    1000,    49,    73,   264,   265,   266,   502,   267,   503,   268,
     504,   269,   508,   270,   507,   201,   202,   203,   204,   470,
     730,   275,   276,   205,   467,   854,   855,   856,  1009,  1143,
    1144,   206,   464,    57,    77,   846,   847,   848,  1003,    59,
      78,   343,   344,   345,   346,   347,   348,   349,   532,   350,
     536,   351,   535,   352,   353,   537,   354,   207,   465,   850,
     851,   852,  1006,    61,    79,   364,   365,   366,   367,   368,
     541,   369,   370,   371,   372,   278,   500,   959,   960,   961,
    1069,    51,    74,   289,   290,   291,   512,   208,   468,   209,
     469,   281,   501,   963,   964,   965,  1072,    53,    75,   305,
     306,   307,   515,   308,   309,   517,   310,   311,   210,   479,
     879,   880,   881,  1023,    55,    76,   323,   324,   325,   326,
     523,   327,   524,   328,   525,   329,   526,   330,   527,   331,
     528,   332,   522,   283,   509,   968,   969,  1075,   211,   478,
     876,   877,  1020,  1167,  1168,  1169,  1170,  1171,  1248,  1172,
     212,   482,   909,   910,   911,  1037,  1257,   912,   913,  1038,
     914,   915,   213,   214,   485,   932,   933,   934,  1049,   935,
    1050,   215,   486,   942,   943,   944,   945,  1054,   946,   947,
    1056,   216,   487,    65,    81,   400,   401,   402,   403,   551,
     404,   552,   405,   406,   554,   407,   408,   409,   557,   781,
     410,   558,   411,   412,   413,   561,   414,   562,   415,   563,
     416,   564,   217,   432,    67,    82,   419,   420,   421,   567,
     422,   218,   491,   950,   951,  1060,  1210,  1211,  1212,  1213,
    1265,  1214,  1263,  1284,  1285,  1286,  1294,  1295,  1296,  1302,
    1297,  1298,  1299,  1300,  1306,   219,   492,   954,   955,   956
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     155,   222,   239,   285,   299,   319,    38,   341,   360,   377,
     397,   906,   362,   282,   246,   363,   836,   227,   279,   292,
     303,   321,   866,   355,   373,  1133,   398,  1134,  1135,  1142,
     240,  1148,   857,   342,   361,    31,   952,    32,    42,    33,
     220,   221,   247,   248,   723,   249,   250,   251,    30,   129,
     130,   154,   375,   376,    44,   711,   712,   713,   714,   241,
     228,   280,   293,   304,   322,    46,   356,   374,    86,   399,
      98,    99,   100,   101,   102,   103,   313,   277,   288,   302,
     320,   429,   755,   966,  1012,   242,   430,  1013,  1015,   243,
     715,  1016,   252,   244,   761,   762,   763,   494,   126,   335,
     900,    89,   495,   916,   917,   918,   245,   253,   334,   797,
     254,   255,  1021,   723,   256,  1022,   423,   858,   129,   130,
     129,   130,   257,   129,   130,   258,   498,   259,   260,   261,
     154,   499,   262,   510,  1061,   263,    48,  1062,   511,   271,
    1154,  1155,   272,   273,    50,   274,   513,   286,   300,   287,
     301,   514,    92,    93,   375,   376,    94,   129,   130,    95,
      96,    97,   154,   520,   335,    52,   336,   337,   521,   548,
     338,   339,   340,   565,   549,   129,   130,   125,   566,    54,
     569,   927,   928,   129,   130,   570,  1254,  1255,  1256,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   936,   937,
     938,   417,   418,   901,   902,   903,   904,   127,   128,   494,
     569,   154,    56,   154,   971,   972,   154,   129,   130,    34,
      35,    36,    37,   498,   131,  1234,  1235,  1236,   973,   132,
     133,   134,   135,   136,   137,   138,    58,   139,    60,   126,
      62,  1133,   140,  1134,  1135,  1142,  1287,  1148,   994,  1288,
     939,   141,   284,   995,   142,   726,   727,   728,   729,   129,
     130,   143,   886,   887,   888,   889,   890,   891,   154,   144,
     145,   126,   857,   864,   146,   865,   154,   147,   335,    64,
     236,   148,    66,   237,   866,  1099,   294,   295,   296,   297,
     298,   129,   130,   425,   906,   994,  1018,   129,   130,   424,
     996,  1019,   149,   150,   151,   152,   779,   780,   126,   426,
     427,   792,   236,   437,   153,   237,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   804,   129,   130,
     154,   805,   806,   807,   808,   809,   810,   811,   438,   439,
     440,   335,   357,   336,   337,   358,   359,  1289,   312,   441,
    1290,  1291,  1292,  1293,   313,   314,   315,   316,   317,   318,
     129,   130,   442,  1035,  1042,  1047,  1051,   335,  1036,  1043,
    1048,  1052,   154,  1057,   565,  1064,   994,   510,  1058,  1059,
    1065,  1241,  1242,   443,   444,  1245,  1203,   548,  1204,  1205,
    1246,  1266,  1253,   513,   571,   572,  1267,   520,  1269,   445,
    1307,   529,  1270,   155,   154,  1308,   446,   222,   447,   448,
     154,  1225,  1226,  1227,  1228,   449,   450,   452,   453,   239,
     454,   455,   285,   227,   456,   460,   461,   462,   466,   299,
     282,   246,   471,   472,   473,   279,   483,   490,   292,   319,
     493,   154,   497,   505,   506,   303,   516,   240,   518,   341,
     519,   530,   540,   531,   360,   321,   534,   538,   362,   247,
     248,   363,   249,   250,   251,   355,   228,   539,   542,   543,
     373,   544,   545,   154,   397,   342,   241,   550,   280,   553,
     361,   293,   555,   556,   559,   560,   568,   573,   304,   574,
     398,   575,   576,   577,   277,   578,   579,   288,   322,   154,
     580,   581,   242,   595,   302,   582,   243,   583,   356,   252,
     244,   129,   130,   374,   320,   584,   585,   601,   586,   602,
     587,   588,   593,   245,   253,   589,   590,   254,   255,   591,
     592,   256,   594,   399,   596,   597,   603,   607,   598,   257,
     599,   600,   258,   604,   259,   260,   261,   608,   609,   262,
     605,   606,   263,   610,   611,   612,   271,   613,   614,   272,
     273,   615,   274,   616,   617,   618,   286,   619,   287,   620,
     621,   622,   623,   300,   624,   301,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   625,
     626,   627,   628,   629,   630,   631,   395,   396,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   155,   632,   633,   222,   635,   636,   634,   638,
     639,   641,   642,   643,   154,   644,   645,   648,   646,   649,
     650,   227,   652,   654,   656,   660,   655,   647,   661,   662,
     663,   657,   664,   665,   658,   666,   668,   669,   905,   919,
     929,   670,   397,   671,   672,   673,   953,   676,   680,   674,
     681,   684,   677,   678,   907,   925,   930,   940,   398,   683,
     685,   686,   788,   687,   228,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   690,   691,
     694,   695,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   696,   692,   126,   688,   689,   697,   908,   926,   931,
     941,   399,   693,   699,   700,   229,   702,   230,   703,   704,
     705,   709,   706,   129,   130,   231,   232,   233,   234,   235,
     131,   707,   708,   710,   717,   132,   133,   134,   718,   719,
     720,   721,   722,   725,   236,    32,   731,   237,   140,   732,
     733,   744,   735,   734,   736,   238,   737,   738,   745,   739,
     740,   741,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   742,   743,   746,   747,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   748,
     126,   335,   750,   751,   787,   871,   752,   757,   837,   841,
     845,   753,   754,   756,   758,   759,   760,   764,   149,   150,
     129,   130,   765,   232,   233,   766,   235,   131,   849,   853,
     767,   875,   132,   133,   134,   768,   878,   882,   782,   769,
     949,   236,   958,   770,   237,   962,   154,   978,   979,   980,
     981,   771,   238,   982,   984,   985,   772,   990,   991,   773,
     992,   993,   999,   774,   776,   777,   778,   784,   998,  1001,
    1002,  1004,  1005,   775,   785,  1008,  1007,   786,  1011,  1010,
    1014,  1025,  1024,  1027,  1028,  1070,  1029,  1030,  1031,  1032,
    1033,  1034,  1039,  1040,  1041,  1044,  1045,  1046,  1053,  1055,
    1063,  1066,  1071,  1073,  1074,   149,   150,  1219,  1076,  1077,
    1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,   239,
    1087,  1088,   341,  1089,  1090,   360,  1091,  1092,  1107,   362,
     282,   246,   363,   154,  1093,   279,  1152,  1094,   355,  1156,
    1114,   373,   319,  1095,  1146,   377,  1097,   240,   342,  1096,
    1178,   361,  1179,  1180,  1132,  1165,  1108,  1185,   321,   247,
     248,   905,   249,   250,   251,  1163,   919,  1157,  1115,  1116,
     929,  1117,  1118,  1119,  1186,  1181,   241,   907,   280,  1206,
    1182,   356,   925,   953,   374,  1109,   930,  1147,   285,  1191,
    1183,   299,   940,  1187,   277,  1208,  1158,  1188,  1166,  1189,
    1192,   322,   242,  1145,   292,  1207,   243,   303,  1195,   252,
     244,  1110,  1196,  1199,  1164,  1111,  1193,   320,  1120,  1112,
     908,  1198,  1159,   245,   253,   926,  1160,   254,   255,   931,
    1161,   256,  1113,  1121,  1201,   941,  1122,  1123,  1209,   257,
    1124,  1200,   258,  1162,   259,   260,   261,   293,  1125,   262,
     304,  1126,   263,  1127,  1128,  1129,   271,  1218,  1130,   272,
     273,  1131,   274,   288,  1216,  1138,   302,  1224,  1139,  1140,
    1230,  1141,  1136,  1231,  1137,  1232,  1243,  1233,  1244,  1249,
    1238,  1250,  1251,  1281,  1252,  1264,  1273,  1276,  1278,  1239,
    1303,  1304,  1283,  1305,  1309,  1313,   863,   970,   789,   791,
     783,  1100,  1098,   637,  1153,  1150,  1151,  1240,   640,  1176,
    1177,  1247,  1102,  1194,  1258,   682,  1101,  1149,  1272,  1259,
    1260,  1261,  1268,  1271,  1184,   651,  1280,  1274,  1277,   333,
    1282,  1310,   286,  1315,   287,   300,  1311,   301,  1312,  1104,
    1316,  1221,  1103,  1106,  1222,  1220,  1105,  1223,  1175,  1174,
    1173,   675,  1275,   967,   667,  1197,   653,   679,  1202,  1190,
     948,   701,  1279,  1301,  1107,  1314,  1215,  1217,     0,   790,
    1156,     0,     0,     0,     0,     0,  1114,     0,     0,   698,
    1146,  1262,     0,     0,     0,  1206,  1165,     0,     0,   659,
    1132,     0,  1108,     0,     0,     0,  1163,     0,  1157,     0,
       0,  1208,     0,     0,  1115,  1116,     0,  1117,  1118,  1119,
       0,  1207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1109,     0,  1147,     0,     0,     0,  1158,     0,  1166,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1145,
       0,     0,     0,     0,  1209,  1164,     0,  1110,     0,     0,
       0,  1111,     0,  1159,  1120,  1112,     0,  1160,     0,     0,
       0,  1161,     0,     0,     0,     0,     0,     0,  1113,  1121,
       0,     0,  1122,  1123,  1162,     0,  1124,     0,     0,     0,
       0,     0,     0,     0,  1125,     0,     0,  1126,     0,  1127,
    1128,  1129,     0,     0,  1130,     0,     0,  1131,     0,     0,
       0,  1138,     0,     0,  1139,  1140,     0,  1141,  1136,     0,
    1137
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   739,    79,    73,    73,    79,   708,    72,    73,    74,
      75,    76,   733,    78,    79,  1009,    81,  1009,  1009,  1009,
      73,  1009,   124,    78,    79,     5,   194,     7,     7,     9,
      16,    17,    73,    73,   612,    73,    73,    73,     0,    96,
      97,   209,   131,   132,     7,   177,   178,   179,   180,    73,
      72,    73,    74,    75,    76,     7,    78,    79,   209,    81,
      48,    49,    50,    51,    52,    53,   122,    73,    74,    75,
      76,     3,   648,   129,     3,    73,     8,     6,     3,    73,
     212,     6,    73,    73,   660,   661,   662,     3,    76,    77,
      21,    10,     8,   150,   151,   152,    73,    73,    21,    30,
      73,    73,     3,   681,    73,     6,     6,   209,    96,    97,
      96,    97,    73,    96,    97,    73,     3,    73,    73,    73,
     209,     8,    73,     3,     3,    73,     7,     6,     8,    73,
     118,   119,    73,    73,     7,    73,     3,    74,    75,    74,
      75,     8,    11,    12,   131,   132,    15,    96,    97,    18,
      19,    20,   209,     3,    77,     7,    79,    80,     8,     3,
      83,    84,    85,     3,     8,    96,    97,    75,     8,     7,
       3,   154,   155,    96,    97,     8,   141,   142,   143,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,   157,   158,
     159,    13,    14,   144,   145,   146,   147,    86,    87,     3,
       3,   209,     7,   209,     8,     8,   209,    96,    97,   209,
     210,   211,   212,     3,   103,    38,    39,    40,     8,   108,
     109,   110,   111,   112,   113,   114,     7,   116,     7,    76,
       7,  1245,   121,  1245,  1245,  1245,     3,  1245,     3,     6,
     209,   130,    89,     8,   133,   104,   105,   106,   107,    96,
      97,   140,   134,   135,   136,   137,   138,   139,   209,   148,
     149,    76,   124,   125,   153,   127,   209,   156,    77,     7,
     117,   160,     7,   120,  1015,   997,    91,    92,    93,    94,
      95,    96,    97,     4,  1042,     3,     3,    96,    97,     3,
       8,     8,   181,   182,   183,   184,   174,   175,    76,     8,
       3,    21,   117,     4,   193,   120,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    96,    97,
     209,    41,    42,    43,    44,    45,    46,    47,     4,     4,
       4,    77,    78,    79,    80,    81,    82,   186,   116,     4,
     189,   190,   191,   192,   122,   123,   124,   125,   126,   127,
      96,    97,     4,     3,     3,     3,     3,    77,     8,     8,
       8,     8,   209,     3,     3,     3,     3,     3,     8,     8,
       8,     8,     8,     4,     4,     3,   185,     3,   187,   188,
       8,     3,     8,     3,   424,   425,     8,     3,     8,     4,
       3,     8,     8,   494,   209,     8,     4,   498,     4,     4,
     209,    22,    23,    24,    25,     4,     4,     4,     4,   510,
       4,     4,   513,   498,     4,     4,     4,     4,     4,   520,
     510,   510,     4,     4,     4,   510,     4,     4,   513,   530,
       4,   209,     4,     4,     4,   520,     4,   510,     4,   540,
       4,     3,     3,     8,   545,   530,     4,     4,   545,   510,
     510,   545,   510,   510,   510,   540,   498,     8,     4,     4,
     545,     8,     3,   209,   565,   540,   510,     4,   510,     4,
     545,   513,     4,     4,     4,     4,     4,   209,   520,     4,
     565,     4,     4,     4,   510,     4,     4,   513,   530,   209,
       4,   210,   510,     4,   520,   210,   510,   210,   540,   510,
     510,    96,    97,   545,   530,   210,   210,     4,   210,     4,
     210,   210,   210,   510,   510,   212,   211,   510,   510,   211,
     211,   510,   210,   565,   210,   210,     4,     4,   212,   510,
     212,   212,   510,   212,   510,   510,   510,     4,     4,   510,
     212,   212,   510,   210,     4,     4,   510,     4,     4,   510,
     510,   212,   510,   212,   212,     4,   513,     4,   513,     4,
       4,     4,     4,   520,     4,   520,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,     4,
       4,   210,     4,     4,     4,     4,   181,   182,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   703,     4,     4,   706,     4,     4,   212,     4,
     212,     4,     4,     4,   209,     4,     4,     4,   210,     4,
       4,   706,     4,     4,     4,     4,   210,   212,     4,     4,
       4,   210,     4,     4,   210,     4,     4,     4,   739,   740,
     741,   210,   743,     4,     4,     4,   747,     4,     4,   212,
       4,     4,   212,   212,   739,   740,   741,   742,   743,   212,
       4,   210,   702,     4,   706,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     4,     4,
       4,     4,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     4,   212,    76,   210,   210,     4,   739,   740,   741,
     742,   743,   212,     4,   210,    88,     4,    90,     7,   209,
       7,     5,     7,    96,    97,    98,    99,   100,   101,   102,
     103,     7,     7,   209,   209,   108,   109,   110,   209,     5,
       5,     5,     5,   209,   117,     7,     5,   120,   121,     5,
       5,   209,     5,     7,     5,   128,     5,     7,   209,     7,
       7,     7,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     7,     7,     5,     7,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,     5,
      76,    77,     5,     5,     5,   115,   209,     7,     7,     7,
       7,   209,   209,   209,   209,   209,   209,   209,   181,   182,
      96,    97,   209,    99,   100,   209,   102,   103,     7,     7,
     209,     7,   108,   109,   110,   209,     7,     7,   176,   209,
       7,   117,     7,   209,   120,     7,   209,     4,     4,     4,
       4,   209,   128,     4,     4,     4,   209,     4,     4,   209,
       4,     4,     3,   209,   209,   209,   209,   209,     6,     6,
       3,     6,     3,   681,   209,     3,     6,   209,     3,     6,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   209,     3,     6,     3,   181,   182,     3,     8,     6,
       4,     4,     4,     4,   210,   212,   210,   212,   210,  1000,
       4,   210,  1003,   210,     4,  1006,     4,     4,  1009,  1006,
    1000,  1000,  1006,   209,     4,  1000,     4,   210,  1003,  1020,
    1009,  1006,  1023,   210,  1009,  1026,   210,  1000,  1003,   212,
     210,  1006,   210,   210,  1009,  1020,  1009,     4,  1023,  1000,
    1000,  1042,  1000,  1000,  1000,  1020,  1047,  1020,  1009,  1009,
    1051,  1009,  1009,  1009,     4,   210,  1000,  1042,  1000,  1060,
     210,  1003,  1047,  1064,  1006,  1009,  1051,  1009,  1069,   212,
     210,  1072,  1057,   210,  1000,  1060,  1020,   210,  1020,   210,
     210,  1023,  1000,  1009,  1069,  1060,  1000,  1072,     4,  1000,
    1000,  1009,     4,     4,  1020,  1009,   210,  1023,  1009,  1009,
    1042,   212,  1020,  1000,  1000,  1047,  1020,  1000,  1000,  1051,
    1020,  1000,  1009,  1009,     4,  1057,  1009,  1009,  1060,  1000,
    1009,   210,  1000,  1020,  1000,  1000,  1000,  1069,  1009,  1000,
    1072,  1009,  1000,  1009,  1009,  1009,  1000,     6,  1009,  1000,
    1000,  1009,  1000,  1069,   212,  1009,  1072,     4,  1009,  1009,
     209,  1009,  1009,   209,  1009,   209,     8,   209,     8,     4,
     209,     8,     3,     5,     8,     4,     4,     4,     4,   209,
       4,     4,     7,     4,     4,     4,   732,   787,   703,   706,
     694,   999,   994,   494,  1018,  1012,  1015,   209,   498,  1026,
    1028,   209,  1002,  1047,   209,   548,  1000,  1011,  1245,   209,
     209,   209,   209,   209,  1035,   510,   209,   212,   210,    77,
     209,   212,  1069,   209,  1069,  1072,   210,  1072,   210,  1005,
     209,  1071,  1003,  1008,  1072,  1069,  1006,  1074,  1025,  1023,
    1021,   540,  1251,   757,   530,  1051,   513,   545,  1057,  1042,
     743,   569,  1266,  1287,  1245,  1307,  1061,  1064,    -1,   705,
    1251,    -1,    -1,    -1,    -1,    -1,  1245,    -1,    -1,   565,
    1245,  1201,    -1,    -1,    -1,  1266,  1251,    -1,    -1,   520,
    1245,    -1,  1245,    -1,    -1,    -1,  1251,    -1,  1251,    -1,
      -1,  1266,    -1,    -1,  1245,  1245,    -1,  1245,  1245,  1245,
      -1,  1266,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1245,    -1,  1245,    -1,    -1,    -1,  1251,    -1,  1251,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1245,
      -1,    -1,    -1,    -1,  1266,  1251,    -1,  1245,    -1,    -1,
      -1,  1245,    -1,  1251,  1245,  1245,    -1,  1251,    -1,    -1,
      -1,  1251,    -1,    -1,    -1,    -1,    -1,    -1,  1245,  1245,
      -1,    -1,  1245,  1245,  1251,    -1,  1245,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1245,    -1,    -1,  1245,    -1,  1245,
    1245,  1245,    -1,    -1,  1245,    -1,    -1,  1245,    -1,    -1,
      -1,  1245,    -1,    -1,  1245,  1245,    -1,  1245,  1245,    -1,
    1245
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
       0,     5,     7,     9,   209,   210,   211,   212,   229,   230,
     231,   236,     7,   245,     7,   250,     7,   295,     7,   404,
       7,   484,     7,   500,     7,   517,     7,   436,     7,   442,
       7,   466,     7,   380,     7,   586,     7,   617,   237,   232,
     246,   251,   296,   405,   485,   501,   518,   437,   443,   467,
     381,   587,   618,   229,   238,   239,   209,   234,   235,    10,
     247,   249,    11,    12,    15,    18,    19,    20,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    86,    87,    96,
      97,   103,   108,   109,   110,   111,   112,   113,   114,   116,
     121,   130,   133,   140,   148,   149,   153,   156,   160,   181,
     182,   183,   184,   193,   209,   244,   252,   253,   254,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   276,   278,   280,
     281,   282,   284,   286,   287,   288,   289,   291,   292,   293,
     302,   304,   306,   347,   353,   359,   365,   367,   374,   388,
     398,   418,   419,   420,   421,   426,   434,   460,   490,   492,
     511,   541,   553,   565,   566,   574,   584,   615,   624,   648,
      16,    17,   244,   297,   298,   299,   301,   490,   492,    88,
      90,    98,    99,   100,   101,   102,   117,   120,   128,   244,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   270,   271,   272,   273,   276,   278,   280,
     281,   282,   284,   286,   406,   407,   408,   410,   412,   414,
     416,   418,   419,   420,   421,   424,   425,   460,   478,   490,
     492,   494,   511,   536,    89,   244,   414,   416,   460,   486,
     487,   488,   490,   492,    91,    92,    93,    94,    95,   244,
     414,   416,   460,   490,   492,   502,   503,   504,   506,   507,
     509,   510,   116,   122,   123,   124,   125,   126,   127,   244,
     460,   490,   492,   519,   520,   521,   522,   524,   526,   528,
     530,   532,   534,   434,    21,    77,    79,    80,    83,    84,
      85,   244,   324,   444,   445,   446,   447,   448,   449,   450,
     452,   454,   456,   457,   459,   490,   492,    78,    81,    82,
     244,   324,   448,   454,   468,   469,   470,   471,   472,   474,
     475,   476,   477,   490,   492,   131,   132,   244,   382,   383,
     384,   386,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   181,   182,   244,   490,   492,
     588,   589,   590,   591,   593,   595,   596,   598,   599,   600,
     603,   605,   606,   607,   609,   611,   613,    13,    14,   619,
     620,   621,   623,     6,     3,     4,     8,     3,   248,     3,
       8,   255,   616,   294,   303,   305,   307,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   290,     4,     4,     4,     4,     4,   274,   277,   279,
       4,     4,     4,   399,   435,   461,     4,   427,   491,   493,
     422,     4,     4,     4,   354,   366,   360,   348,   542,   512,
     375,   389,   554,     4,   368,   567,   575,   585,   283,   285,
       4,   625,   649,     4,     3,     8,   300,     4,     3,     8,
     479,   495,   409,   411,   413,     4,     4,   417,   415,   537,
       3,     8,   489,     3,     8,   505,     4,   508,     4,     4,
       3,     8,   535,   523,   525,   527,   529,   531,   533,     8,
       3,     8,   451,   325,     4,   455,   453,   458,     4,     8,
       3,   473,     4,     4,     8,     3,   385,   387,     3,     8,
       4,   592,   594,     4,   597,     4,     4,   601,   604,     4,
       4,   608,   610,   612,   614,     3,     8,   622,     4,     3,
       8,   229,   229,   209,     4,     4,     4,     4,     4,     4,
       4,   210,   210,   210,   210,   210,   210,   210,   210,   212,
     211,   211,   211,   210,   210,     4,   210,   210,   212,   212,
     212,     4,     4,     4,   212,   212,   212,     4,     4,     4,
     210,     4,     4,     4,     4,   212,   212,   212,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   210,     4,     4,
       4,     4,     4,     4,   212,     4,     4,   253,     4,   212,
     298,     4,     4,     4,     4,     4,   210,   212,     4,     4,
       4,   407,     4,   487,     4,   210,     4,   210,   210,   503,
       4,     4,     4,     4,     4,     4,     4,   521,     4,     4,
     210,     4,     4,     4,   212,   446,     4,   212,   212,   470,
       4,     4,   383,   212,     4,     4,   210,     4,   210,   210,
       4,     4,   212,   212,     4,     4,     4,     4,   589,     4,
     210,   620,     4,     7,   209,     7,     7,     7,     7,     5,
     209,   177,   178,   179,   180,   212,   275,   209,   209,     5,
       5,     5,     5,   231,   233,   209,   104,   105,   106,   107,
     423,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   209,   209,     5,     7,     5,   240,
       5,     5,   209,   209,   209,   240,   209,     7,   209,   209,
     209,   240,   240,   240,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   233,   209,   209,   209,   174,
     175,   602,   176,   275,   209,   209,   209,     5,   229,   252,
     619,   297,    21,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    41,    42,    43,    44,    45,
      46,    47,   244,   312,   313,   314,   317,   319,   321,   323,
     324,   326,   327,   328,   329,   330,   331,   334,   335,   336,
     337,   338,   340,   341,   343,   345,   312,     7,   308,   309,
     310,     7,   400,   401,   402,     7,   438,   439,   440,     7,
     462,   463,   464,     7,   428,   429,   430,   124,   209,   355,
     356,   357,   358,   238,   125,   127,   357,   361,   362,   363,
     364,   115,   349,   350,   351,     7,   543,   544,     7,   513,
     514,   515,     7,   376,   377,   378,   134,   135,   136,   137,
     138,   139,   390,   391,   392,   393,   394,   395,   396,   397,
      21,   144,   145,   146,   147,   244,   326,   490,   492,   555,
     556,   557,   560,   561,   563,   564,   150,   151,   152,   244,
     369,   370,   371,   372,   373,   490,   492,   154,   155,   244,
     490,   492,   568,   569,   570,   572,   157,   158,   159,   209,
     490,   492,   576,   577,   578,   579,   581,   582,   588,     7,
     626,   627,   194,   244,   650,   651,   652,   241,     7,   480,
     481,   482,     7,   496,   497,   498,   129,   522,   538,   539,
     308,     8,     8,     8,   315,   318,   320,   322,     4,     4,
       4,     4,     4,   339,     4,     4,   332,   342,   344,   346,
       4,     4,     4,     4,     3,     8,     8,   311,     6,     3,
     403,     6,     3,   441,     6,     3,   465,     6,     3,   431,
       6,     3,     3,     6,     6,     3,     6,   352,     3,     8,
     545,     3,     6,   516,     6,     3,   379,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   558,   562,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   571,
     573,     3,     8,     4,   580,     4,   583,     3,     8,     8,
     628,     3,     6,     4,     3,     8,   209,   242,   243,   483,
       6,     3,   499,     6,     3,   540,     8,     6,     4,     4,
       4,     4,   210,   212,   210,   212,   210,     4,   210,   210,
       4,     4,     4,     4,   210,   210,   212,   210,   313,   312,
     310,   406,   402,   444,   440,   468,   464,   244,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   270,   271,   272,   273,   276,   278,   280,   281,   282,
     284,   286,   324,   398,   410,   412,   414,   416,   418,   419,
     420,   421,   425,   432,   433,   460,   490,   492,   536,   430,
     356,   362,     4,   350,   118,   119,   244,   256,   257,   258,
     259,   260,   261,   324,   460,   490,   492,   546,   547,   548,
     549,   550,   552,   544,   519,   515,   382,   378,   210,   210,
     210,   210,   210,   210,   391,     4,     4,   210,   210,   210,
     556,   212,   210,   210,   370,     4,     4,   569,   212,     4,
     210,     4,   577,   185,   187,   188,   244,   324,   490,   492,
     629,   630,   631,   632,   634,   627,   212,   651,     6,     3,
     486,   482,   502,   498,     4,    22,    23,    24,    25,   316,
     209,   209,   209,   209,    38,    39,    40,   333,   209,   209,
     209,     8,     8,     8,     8,     3,     8,   209,   551,     4,
       8,     3,     8,     8,   141,   142,   143,   559,   209,   209,
     209,   209,   229,   635,     4,   633,     3,     8,   209,     8,
       8,   209,   433,     4,   212,   548,     4,   210,     4,   630,
     209,     5,   209,     7,   636,   637,   638,     3,     6,   186,
     189,   190,   191,   192,   639,   640,   641,   643,   644,   645,
     646,   637,   642,     4,     4,     4,   647,     3,     8,     4,
     212,   210,   210,     4,   640,   209,   209
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   213,   215,   214,   216,   214,   217,   214,   218,   214,
     219,   214,   220,   214,   221,   214,   222,   214,   223,   214,
     224,   214,   225,   214,   226,   214,   227,   214,   228,   214,
     229,   229,   229,   229,   229,   229,   229,   230,   232,   231,
     233,   234,   234,   235,   235,   235,   237,   236,   238,   238,
     239,   239,   239,   241,   240,   242,   242,   243,   243,   243,
     244,   246,   245,   248,   247,   247,   249,   251,   250,   252,
     252,   252,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   255,   254,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   274,   273,   275,   275,   275,   275,
     275,   277,   276,   279,   278,   280,   281,   283,   282,   285,
     284,   286,   287,   288,   290,   289,   291,   292,   294,   293,
     296,   295,   297,   297,   297,   298,   298,   298,   298,   298,
     300,   299,   301,   303,   302,   305,   304,   307,   306,   308,
     308,   309,   309,   309,   311,   310,   312,   312,   312,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   315,   314,   316,   316,   316,   316,   318,   317,   320,
     319,   322,   321,   323,   325,   324,   326,   327,   328,   329,
     330,   332,   331,   333,   333,   333,   334,   335,   336,   337,
     339,   338,   340,   342,   341,   344,   343,   346,   345,   348,
     347,   349,   349,   349,   350,   352,   351,   354,   353,   355,
     355,   355,   356,   356,   357,   358,   360,   359,   361,   361,
     361,   362,   362,   362,   363,   364,   366,   365,   368,   367,
     369,   369,   369,   370,   370,   370,   370,   370,   370,   371,
     372,   373,   375,   374,   376,   376,   377,   377,   377,   379,
     378,   381,   380,   382,   382,   382,   382,   383,   383,   385,
     384,   387,   386,   389,   388,   390,   390,   390,   391,   391,
     391,   391,   391,   391,   392,   393,   394,   395,   396,   397,
     399,   398,   400,   400,   401,   401,   401,   403,   402,   405,
     404,   406,   406,   406,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   409,   408,   411,
     410,   413,   412,   415,   414,   417,   416,   418,   419,   420,
     422,   421,   423,   423,   423,   423,   424,   425,   427,   426,
     428,   428,   429,   429,   429,   431,   430,   432,   432,   432,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     435,   434,   437,   436,   438,   438,   439,   439,   439,   441,
     440,   443,   442,   444,   444,   445,   445,   445,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   447,   448,
     449,   451,   450,   453,   452,   455,   454,   456,   458,   457,
     459,   461,   460,   462,   462,   463,   463,   463,   465,   464,
     467,   466,   468,   468,   469,   469,   469,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   471,   473,   472,   474,
     475,   476,   477,   479,   478,   480,   480,   481,   481,   481,
     483,   482,   485,   484,   486,   486,   486,   487,   487,   487,
     487,   487,   487,   487,   489,   488,   491,   490,   493,   492,
     495,   494,   496,   496,   497,   497,   497,   499,   498,   501,
     500,   502,   502,   502,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   505,   504,   506,   508,   507,
     509,   510,   512,   511,   513,   513,   514,   514,   514,   516,
     515,   518,   517,   519,   519,   520,   520,   520,   521,   521,
     521,   521,   521,   521,   521,   521,   521,   521,   521,   523,
     522,   525,   524,   527,   526,   529,   528,   531,   530,   533,
     532,   535,   534,   537,   536,   538,   538,   540,   539,   542,
     541,   543,   543,   543,   545,   544,   546,   546,   547,   547,
     547,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   549,   551,   550,   552,   554,   553,
     555,   555,   555,   556,   556,   556,   556,   556,   556,   556,
     556,   556,   558,   557,   559,   559,   559,   560,   562,   561,
     563,   564,   565,   567,   566,   568,   568,   568,   569,   569,
     569,   569,   569,   571,   570,   573,   572,   575,   574,   576,
     576,   576,   577,   577,   577,   577,   577,   577,   578,   580,
     579,   581,   583,   582,   585,   584,   587,   586,   588,   588,
     588,   589,   589,   589,   589,   589,   589,   589,   589,   589,
     589,   589,   589,   589,   589,   589,   589,   589,   589,   590,
     592,   591,   594,   593,   595,   597,   596,   598,   599,   601,
     600,   602,   602,   604,   603,   605,   606,   608,   607,   610,
     609,   612,   611,   614,   613,   616,   615,   618,   617,   619,
     619,   619,   620,   620,   622,   621,   623,   625,   624,   626,
     626,   626,   628,   627,   629,   629,   629,   630,   630,   630,
     630,   630,   630,   630,   631,   633,   632,   635,   634,   636,
     636,   636,   638,   637,   639,   639,   639,   640,   640,   640,
     640,   640,   642,   641,   643,   644,   645,   647,   646,   649,
     648,   650,   650,   650,   651,   651,   652
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
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     3,     3,     3,     3,
       0,     4,     3,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     0,     4,     0,     6,     1,
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
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
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     3
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
  "consistency", "$@43", "serial_consistency", "$@44", "sanity_checks",
  "$@45", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@46", "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@48",
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
       0,   301,   301,   301,   302,   302,   303,   303,   304,   304,
     305,   305,   306,   306,   307,   307,   308,   308,   309,   309,
     310,   310,   311,   311,   312,   312,   313,   313,   314,   314,
     322,   323,   324,   325,   326,   327,   328,   331,   336,   336,
     347,   350,   351,   354,   359,   365,   370,   370,   377,   378,
     381,   385,   389,   395,   395,   402,   403,   406,   410,   414,
     424,   433,   433,   448,   448,   462,   465,   471,   471,   480,
     481,   482,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   554,   554,   563,   569,   575,
     581,   587,   593,   599,   605,   611,   617,   623,   629,   635,
     641,   647,   653,   659,   665,   665,   674,   677,   680,   683,
     686,   692,   692,   701,   701,   710,   716,   722,   722,   731,
     731,   740,   746,   752,   758,   758,   767,   773,   779,   779,
     791,   791,   800,   801,   802,   807,   808,   809,   810,   811,
     814,   814,   825,   831,   831,   844,   844,   857,   857,   868,
     869,   872,   873,   874,   879,   879,   889,   890,   891,   896,
     897,   898,   899,   900,   901,   902,   903,   904,   905,   906,
     907,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   920,   920,   928,   929,   930,   931,   934,   934,   943,
     943,   952,   952,   961,   967,   967,   976,   982,   988,   994,
    1000,  1006,  1006,  1014,  1015,  1016,  1019,  1025,  1031,  1037,
    1043,  1043,  1052,  1058,  1058,  1067,  1067,  1076,  1076,  1085,
    1085,  1096,  1097,  1098,  1103,  1105,  1105,  1124,  1124,  1135,
    1136,  1137,  1142,  1143,  1146,  1151,  1156,  1156,  1167,  1168,
    1169,  1174,  1175,  1176,  1179,  1184,  1191,  1191,  1204,  1204,
    1217,  1218,  1219,  1224,  1225,  1226,  1227,  1228,  1229,  1232,
    1238,  1244,  1250,  1250,  1261,  1262,  1265,  1266,  1267,  1272,
    1272,  1282,  1282,  1292,  1293,  1294,  1297,  1300,  1301,  1304,
    1304,  1313,  1313,  1322,  1322,  1334,  1335,  1336,  1341,  1342,
    1343,  1344,  1345,  1346,  1349,  1355,  1361,  1367,  1373,  1379,
    1388,  1388,  1402,  1403,  1406,  1407,  1408,  1417,  1417,  1443,
    1443,  1454,  1455,  1456,  1462,  1463,  1464,  1465,  1466,  1467,
    1468,  1469,  1470,  1471,  1472,  1473,  1474,  1475,  1476,  1477,
    1478,  1479,  1480,  1481,  1482,  1483,  1484,  1485,  1486,  1487,
    1488,  1489,  1490,  1491,  1492,  1493,  1494,  1495,  1496,  1497,
    1498,  1499,  1500,  1501,  1502,  1503,  1504,  1507,  1507,  1516,
    1516,  1525,  1525,  1534,  1534,  1543,  1543,  1554,  1560,  1566,
    1572,  1572,  1580,  1581,  1582,  1583,  1586,  1592,  1600,  1600,
    1612,  1613,  1617,  1618,  1619,  1624,  1624,  1632,  1633,  1634,
    1639,  1640,  1641,  1642,  1643,  1644,  1645,  1646,  1647,  1648,
    1649,  1650,  1651,  1652,  1653,  1654,  1655,  1656,  1657,  1658,
    1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,
    1669,  1670,  1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,
    1685,  1685,  1699,  1699,  1708,  1709,  1712,  1713,  1714,  1721,
    1721,  1736,  1736,  1750,  1751,  1754,  1755,  1756,  1761,  1762,
    1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1773,  1775,
    1781,  1783,  1783,  1792,  1792,  1801,  1801,  1810,  1812,  1812,
    1821,  1831,  1831,  1844,  1845,  1850,  1851,  1852,  1859,  1859,
    1871,  1871,  1883,  1884,  1889,  1890,  1891,  1898,  1899,  1900,
    1901,  1902,  1903,  1904,  1905,  1906,  1909,  1911,  1911,  1920,
    1922,  1924,  1930,  1939,  1939,  1952,  1953,  1956,  1957,  1958,
    1963,  1963,  1973,  1973,  1983,  1984,  1985,  1990,  1991,  1992,
    1993,  1994,  1995,  1996,  1999,  1999,  2008,  2008,  2033,  2033,
    2063,  2063,  2076,  2077,  2080,  2081,  2082,  2087,  2087,  2099,
    2099,  2111,  2112,  2113,  2118,  2119,  2120,  2121,  2122,  2123,
    2124,  2125,  2126,  2127,  2128,  2131,  2131,  2140,  2146,  2146,
    2155,  2161,  2170,  2170,  2181,  2182,  2185,  2186,  2187,  2192,
    2192,  2201,  2201,  2210,  2211,  2214,  2215,  2216,  2222,  2223,
    2224,  2225,  2226,  2227,  2228,  2229,  2230,  2231,  2232,  2235,
    2235,  2246,  2246,  2257,  2257,  2266,  2266,  2275,  2275,  2284,
    2284,  2293,  2293,  2307,  2307,  2318,  2319,  2322,  2322,  2334,
    2334,  2345,  2346,  2347,  2352,  2352,  2362,  2363,  2366,  2367,
    2368,  2373,  2374,  2375,  2376,  2377,  2378,  2379,  2380,  2381,
    2382,  2383,  2384,  2385,  2388,  2390,  2390,  2399,  2408,  2408,
    2421,  2422,  2423,  2428,  2429,  2430,  2431,  2432,  2433,  2434,
    2435,  2436,  2439,  2439,  2447,  2448,  2449,  2452,  2458,  2458,
    2467,  2473,  2481,  2489,  2489,  2500,  2501,  2502,  2507,  2508,
    2509,  2510,  2511,  2514,  2514,  2523,  2523,  2535,  2535,  2548,
    2549,  2550,  2555,  2556,  2557,  2558,  2559,  2560,  2563,  2569,
    2569,  2578,  2584,  2584,  2594,  2594,  2607,  2607,  2617,  2618,
    2619,  2624,  2625,  2626,  2627,  2628,  2629,  2630,  2631,  2632,
    2633,  2634,  2635,  2636,  2637,  2638,  2639,  2640,  2641,  2644,
    2651,  2651,  2660,  2660,  2669,  2675,  2675,  2684,  2690,  2696,
    2696,  2705,  2706,  2709,  2709,  2719,  2726,  2733,  2733,  2742,
    2742,  2752,  2752,  2762,  2762,  2774,  2774,  2786,  2786,  2796,
    2797,  2798,  2804,  2805,  2808,  2808,  2819,  2827,  2827,  2840,
    2841,  2842,  2848,  2848,  2856,  2857,  2858,  2863,  2864,  2865,
    2866,  2867,  2868,  2869,  2872,  2878,  2878,  2887,  2887,  2898,
    2899,  2900,  2905,  2905,  2913,  2914,  2915,  2920,  2921,  2922,
    2923,  2924,  2927,  2927,  2936,  2942,  2948,  2954,  2954,  2963,
    2963,  2974,  2975,  2976,  2981,  2982,  2985
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
#line 6326 "dhcp6_parser.cc"

#line 2991 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
