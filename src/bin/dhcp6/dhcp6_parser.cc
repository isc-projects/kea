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
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 290 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 290 "dhcp6_parser.yy"
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
#line 299 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 300 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 301 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 302 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 303 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 304 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 305 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 306 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 307 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 308 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 309 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 310 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 311 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 312 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 320 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 321 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 322 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 323 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 324 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 325 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 326 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 329 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 334 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 339 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 345 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 352 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 357 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 363 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 368 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 371 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 379 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 383 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 387 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 393 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 395 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 404 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 408 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 412 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 422 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 431 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 436 "dhcp6_parser.yy"
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
#line 446 "dhcp6_parser.yy"
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
#line 455 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 463 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 469 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 473 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 480 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 137: // $@21: %empty
#line 554 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 138: // data_directory: "data-directory" $@21 ":" "constant string"
#line 557 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 139: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 563 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 140: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 569 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 141: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 575 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 587 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 611 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 617 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 623 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 629 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 635 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 641 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 153: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 647 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 154: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 653 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 155: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 659 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 156: // $@22: %empty
#line 665 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 668 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "when-present"
#line 674 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "never"
#line 677 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "always"
#line 680 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-not-present"
#line 683 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "boolean"
#line 686 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 163: // $@23: %empty
#line 692 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 164: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 695 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 165: // $@24: %empty
#line 701 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 166: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 704 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 167: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 710 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 168: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 716 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 169: // $@25: %empty
#line 722 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 725 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 171: // $@26: %empty
#line 731 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 734 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 173: // store_extended_info: "store-extended-info" ":" "boolean"
#line 740 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 174: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 746 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 175: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 752 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 176: // $@27: %empty
#line 758 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 177: // server_tag: "server-tag" $@27 ":" "constant string"
#line 761 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 178: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 767 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 179: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 773 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 180: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 779 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 181: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 785 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 182: // $@28: %empty
#line 791 "dhcp6_parser.yy"
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
#line 797 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 184: // $@29: %empty
#line 803 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 185: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 807 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // interfaces_config_params: interfaces_config_params ","
#line 814 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1598 "dhcp6_parser.cc"
    break;

  case 194: // $@30: %empty
#line 826 "dhcp6_parser.yy"
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
#line 832 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 196: // re_detect: "re-detect" ":" "boolean"
#line 837 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 843 "dhcp6_parser.yy"
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
#line 849 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1652 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 856 "dhcp6_parser.yy"
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
#line 862 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1675 "dhcp6_parser.cc"
    break;

  case 201: // $@33: %empty
#line 869 "dhcp6_parser.yy"
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
#line 875 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1696 "dhcp6_parser.cc"
    break;

  case 207: // not_empty_database_list: not_empty_database_list ","
#line 886 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1704 "dhcp6_parser.cc"
    break;

  case 208: // $@34: %empty
#line 891 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1714 "dhcp6_parser.cc"
    break;

  case 209: // database: "{" $@34 database_map_params "}"
#line 895 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1724 "dhcp6_parser.cc"
    break;

  case 212: // database_map_params: database_map_params ","
#line 903 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1732 "dhcp6_parser.cc"
    break;

  case 232: // $@35: %empty
#line 929 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 233: // database_type: "type" $@35 ":" db_type
#line 932 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1750 "dhcp6_parser.cc"
    break;

  case 234: // db_type: "memfile"
#line 937 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1756 "dhcp6_parser.cc"
    break;

  case 235: // db_type: "mysql"
#line 938 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1762 "dhcp6_parser.cc"
    break;

  case 236: // db_type: "postgresql"
#line 939 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1768 "dhcp6_parser.cc"
    break;

  case 237: // $@36: %empty
#line 942 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 238: // user: "user" $@36 ":" "constant string"
#line 945 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1787 "dhcp6_parser.cc"
    break;

  case 239: // $@37: %empty
#line 951 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp6_parser.cc"
    break;

  case 240: // password: "password" $@37 ":" "constant string"
#line 954 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1806 "dhcp6_parser.cc"
    break;

  case 241: // $@38: %empty
#line 960 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 242: // host: "host" $@38 ":" "constant string"
#line 963 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 243: // port: "port" ":" "integer"
#line 969 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 244: // $@39: %empty
#line 975 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 245: // name: "name" $@39 ":" "constant string"
#line 978 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 246: // persist: "persist" ":" "boolean"
#line 984 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 247: // lfc_interval: "lfc-interval" ":" "integer"
#line 990 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 248: // readonly: "readonly" ":" "boolean"
#line 996 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1884 "dhcp6_parser.cc"
    break;

  case 249: // connect_timeout: "connect-timeout" ":" "integer"
#line 1002 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1894 "dhcp6_parser.cc"
    break;

  case 250: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1008 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 251: // $@40: %empty
#line 1014 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1913 "dhcp6_parser.cc"
    break;

  case 252: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1017 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 253: // on_fail_mode: "stop-retry-exit"
#line 1022 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1928 "dhcp6_parser.cc"
    break;

  case 254: // on_fail_mode: "serve-retry-exit"
#line 1023 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1934 "dhcp6_parser.cc"
    break;

  case 255: // on_fail_mode: "serve-retry-continue"
#line 1024 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1940 "dhcp6_parser.cc"
    break;

  case 256: // max_row_errors: "max-row-errors" ":" "integer"
#line 1027 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1950 "dhcp6_parser.cc"
    break;

  case 257: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1033 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 258: // $@41: %empty
#line 1039 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc"
    break;

  case 259: // trust_anchor: "trust-anchor" $@41 ":" "constant string"
#line 1042 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc"
    break;

  case 260: // $@42: %empty
#line 1048 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1988 "dhcp6_parser.cc"
    break;

  case 261: // cert_file: "cert-file" $@42 ":" "constant string"
#line 1051 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 262: // $@43: %empty
#line 1057 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2007 "dhcp6_parser.cc"
    break;

  case 263: // key_file: "key-file" $@43 ":" "constant string"
#line 1060 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2017 "dhcp6_parser.cc"
    break;

  case 264: // $@44: %empty
#line 1066 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2026 "dhcp6_parser.cc"
    break;

  case 265: // cipher_list: "cipher-list" $@44 ":" "constant string"
#line 1069 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2036 "dhcp6_parser.cc"
    break;

  case 266: // $@45: %empty
#line 1075 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2048 "dhcp6_parser.cc"
    break;

  case 267: // sanity_checks: "sanity-checks" $@45 ":" "{" sanity_checks_params "}"
#line 1081 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 270: // sanity_checks_params: sanity_checks_params ","
#line 1088 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2065 "dhcp6_parser.cc"
    break;

  case 272: // $@46: %empty
#line 1095 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2074 "dhcp6_parser.cc"
    break;

  case 273: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1098 "dhcp6_parser.yy"
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
#line 2094 "dhcp6_parser.cc"
    break;

  case 274: // $@47: %empty
#line 1114 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 275: // mac_sources: "mac-sources" $@47 ":" "[" mac_sources_list "]"
#line 1120 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 278: // mac_sources_list: mac_sources_list ","
#line 1127 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2123 "dhcp6_parser.cc"
    break;

  case 281: // duid_id: "duid"
#line 1136 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2132 "dhcp6_parser.cc"
    break;

  case 282: // string_id: "constant string"
#line 1141 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2141 "dhcp6_parser.cc"
    break;

  case 283: // $@48: %empty
#line 1146 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2153 "dhcp6_parser.cc"
    break;

  case 284: // host_reservation_identifiers: "host-reservation-identifiers" $@48 ":" "[" host_reservation_identifiers_list "]"
#line 1152 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2162 "dhcp6_parser.cc"
    break;

  case 287: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1159 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2170 "dhcp6_parser.cc"
    break;

  case 291: // hw_address_id: "hw-address"
#line 1169 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2179 "dhcp6_parser.cc"
    break;

  case 292: // flex_id: "flex-id"
#line 1174 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2188 "dhcp6_parser.cc"
    break;

  case 293: // $@49: %empty
#line 1181 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2200 "dhcp6_parser.cc"
    break;

  case 294: // relay_supplied_options: "relay-supplied-options" $@49 ":" "[" list_content "]"
#line 1187 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2209 "dhcp6_parser.cc"
    break;

  case 295: // $@50: %empty
#line 1194 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 296: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1200 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2232 "dhcp6_parser.cc"
    break;

  case 299: // multi_threading_params: multi_threading_params ","
#line 1209 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2240 "dhcp6_parser.cc"
    break;

  case 306: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1222 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 307: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1228 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2260 "dhcp6_parser.cc"
    break;

  case 308: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1234 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2270 "dhcp6_parser.cc"
    break;

  case 309: // $@51: %empty
#line 1240 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2282 "dhcp6_parser.cc"
    break;

  case 310: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1246 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 315: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1257 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2299 "dhcp6_parser.cc"
    break;

  case 316: // $@52: %empty
#line 1262 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2309 "dhcp6_parser.cc"
    break;

  case 317: // hooks_library: "{" $@52 hooks_params "}"
#line 1266 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2319 "dhcp6_parser.cc"
    break;

  case 318: // $@53: %empty
#line 1272 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2329 "dhcp6_parser.cc"
    break;

  case 319: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1276 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2339 "dhcp6_parser.cc"
    break;

  case 322: // hooks_params: hooks_params ","
#line 1284 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2347 "dhcp6_parser.cc"
    break;

  case 326: // $@54: %empty
#line 1294 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2356 "dhcp6_parser.cc"
    break;

  case 327: // library: "library" $@54 ":" "constant string"
#line 1297 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2366 "dhcp6_parser.cc"
    break;

  case 328: // $@55: %empty
#line 1303 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2375 "dhcp6_parser.cc"
    break;

  case 329: // parameters: "parameters" $@55 ":" map_value
#line 1306 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 330: // $@56: %empty
#line 1312 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2396 "dhcp6_parser.cc"
    break;

  case 331: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1318 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2406 "dhcp6_parser.cc"
    break;

  case 334: // expired_leases_params: expired_leases_params ","
#line 1326 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2414 "dhcp6_parser.cc"
    break;

  case 341: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1339 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 342: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1345 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2434 "dhcp6_parser.cc"
    break;

  case 343: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1351 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2444 "dhcp6_parser.cc"
    break;

  case 344: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1357 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2454 "dhcp6_parser.cc"
    break;

  case 345: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1363 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2464 "dhcp6_parser.cc"
    break;

  case 346: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1369 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2474 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1378 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 348: // subnet6_list: "subnet6" $@57 ":" "[" subnet6_list_content "]"
#line 1384 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc"
    break;

  case 353: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1398 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2503 "dhcp6_parser.cc"
    break;

  case 354: // $@58: %empty
#line 1407 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2513 "dhcp6_parser.cc"
    break;

  case 355: // subnet6: "{" $@58 subnet6_params "}"
#line 1411 "dhcp6_parser.yy"
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
#line 2539 "dhcp6_parser.cc"
    break;

  case 356: // $@59: %empty
#line 1433 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2549 "dhcp6_parser.cc"
    break;

  case 357: // sub_subnet6: "{" $@59 subnet6_params "}"
#line 1437 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 360: // subnet6_params: subnet6_params ","
#line 1446 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2567 "dhcp6_parser.cc"
    break;

  case 404: // $@60: %empty
#line 1497 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 405: // subnet: "subnet" $@60 ":" "constant string"
#line 1500 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 406: // $@61: %empty
#line 1506 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2595 "dhcp6_parser.cc"
    break;

  case 407: // interface: "interface" $@61 ":" "constant string"
#line 1509 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 408: // $@62: %empty
#line 1515 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2614 "dhcp6_parser.cc"
    break;

  case 409: // interface_id: "interface-id" $@62 ":" "constant string"
#line 1518 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2624 "dhcp6_parser.cc"
    break;

  case 410: // $@63: %empty
#line 1524 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 411: // client_class: "client-class" $@63 ":" "constant string"
#line 1527 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2643 "dhcp6_parser.cc"
    break;

  case 412: // $@64: %empty
#line 1533 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2655 "dhcp6_parser.cc"
    break;

  case 413: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1539 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2664 "dhcp6_parser.cc"
    break;

  case 414: // reservations_global: "reservations-global" ":" "boolean"
#line 1544 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2674 "dhcp6_parser.cc"
    break;

  case 415: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1550 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 416: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1556 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 417: // $@65: %empty
#line 1562 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 418: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1565 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 419: // hr_mode: "disabled"
#line 1570 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2718 "dhcp6_parser.cc"
    break;

  case 420: // hr_mode: "out-of-pool"
#line 1571 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2724 "dhcp6_parser.cc"
    break;

  case 421: // hr_mode: "global"
#line 1572 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2730 "dhcp6_parser.cc"
    break;

  case 422: // hr_mode: "all"
#line 1573 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2736 "dhcp6_parser.cc"
    break;

  case 423: // id: "id" ":" "integer"
#line 1576 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2746 "dhcp6_parser.cc"
    break;

  case 424: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1582 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2756 "dhcp6_parser.cc"
    break;

  case 425: // $@66: %empty
#line 1590 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2768 "dhcp6_parser.cc"
    break;

  case 426: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1596 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2777 "dhcp6_parser.cc"
    break;

  case 431: // shared_networks_list: shared_networks_list ","
#line 1609 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2785 "dhcp6_parser.cc"
    break;

  case 432: // $@67: %empty
#line 1614 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 433: // shared_network: "{" $@67 shared_network_params "}"
#line 1618 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2803 "dhcp6_parser.cc"
    break;

  case 436: // shared_network_params: shared_network_params ","
#line 1624 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2811 "dhcp6_parser.cc"
    break;

  case 477: // $@68: %empty
#line 1675 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 478: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1681 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 479: // $@69: %empty
#line 1689 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2841 "dhcp6_parser.cc"
    break;

  case 480: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1692 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 485: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1704 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2857 "dhcp6_parser.cc"
    break;

  case 486: // $@70: %empty
#line 1711 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 487: // option_def_entry: "{" $@70 option_def_params "}"
#line 1715 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2879 "dhcp6_parser.cc"
    break;

  case 488: // $@71: %empty
#line 1726 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2889 "dhcp6_parser.cc"
    break;

  case 489: // sub_option_def: "{" $@71 option_def_params "}"
#line 1730 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2901 "dhcp6_parser.cc"
    break;

  case 494: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1746 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2909 "dhcp6_parser.cc"
    break;

  case 506: // code: "code" ":" "integer"
#line 1765 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 508: // $@72: %empty
#line 1773 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 509: // option_def_type: "type" $@72 ":" "constant string"
#line 1776 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2938 "dhcp6_parser.cc"
    break;

  case 510: // $@73: %empty
#line 1782 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2947 "dhcp6_parser.cc"
    break;

  case 511: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1785 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2957 "dhcp6_parser.cc"
    break;

  case 512: // $@74: %empty
#line 1791 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp6_parser.cc"
    break;

  case 513: // space: "space" $@74 ":" "constant string"
#line 1794 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2976 "dhcp6_parser.cc"
    break;

  case 515: // $@75: %empty
#line 1802 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 516: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1805 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 517: // option_def_array: "array" ":" "boolean"
#line 1811 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 518: // $@76: %empty
#line 1821 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 519: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1827 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3026 "dhcp6_parser.cc"
    break;

  case 524: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1842 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3034 "dhcp6_parser.cc"
    break;

  case 525: // $@77: %empty
#line 1849 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3044 "dhcp6_parser.cc"
    break;

  case 526: // option_data_entry: "{" $@77 option_data_params "}"
#line 1853 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 527: // $@78: %empty
#line 1861 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 528: // sub_option_data: "{" $@78 option_data_params "}"
#line 1865 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3072 "dhcp6_parser.cc"
    break;

  case 533: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1881 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3080 "dhcp6_parser.cc"
    break;

  case 544: // $@79: %empty
#line 1901 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 545: // option_data_data: "data" $@79 ":" "constant string"
#line 1904 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 548: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1914 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 549: // option_data_always_send: "always-send" ":" "boolean"
#line 1920 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 550: // $@80: %empty
#line 1929 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 551: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1935 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 556: // not_empty_pools_list: not_empty_pools_list ","
#line 1948 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3148 "dhcp6_parser.cc"
    break;

  case 557: // $@81: %empty
#line 1953 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 558: // pool_list_entry: "{" $@81 pool_params "}"
#line 1957 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 559: // $@82: %empty
#line 1963 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3178 "dhcp6_parser.cc"
    break;

  case 560: // sub_pool6: "{" $@82 pool_params "}"
#line 1967 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 563: // pool_params: pool_params ","
#line 1975 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3196 "dhcp6_parser.cc"
    break;

  case 571: // $@83: %empty
#line 1989 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3205 "dhcp6_parser.cc"
    break;

  case 572: // pool_entry: "pool" $@83 ":" "constant string"
#line 1992 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3215 "dhcp6_parser.cc"
    break;

  case 573: // $@84: %empty
#line 1998 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3223 "dhcp6_parser.cc"
    break;

  case 574: // user_context: "user-context" $@84 ":" map_value
#line 2000 "dhcp6_parser.yy"
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
#line 3250 "dhcp6_parser.cc"
    break;

  case 575: // $@85: %empty
#line 2023 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3258 "dhcp6_parser.cc"
    break;

  case 576: // comment: "comment" $@85 ":" "constant string"
#line 2025 "dhcp6_parser.yy"
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
#line 3287 "dhcp6_parser.cc"
    break;

  case 577: // $@86: %empty
#line 2053 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3299 "dhcp6_parser.cc"
    break;

  case 578: // pd_pools_list: "pd-pools" $@86 ":" "[" pd_pools_list_content "]"
#line 2059 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3308 "dhcp6_parser.cc"
    break;

  case 583: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2072 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3316 "dhcp6_parser.cc"
    break;

  case 584: // $@87: %empty
#line 2077 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3326 "dhcp6_parser.cc"
    break;

  case 585: // pd_pool_entry: "{" $@87 pd_pool_params "}"
#line 2081 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 586: // $@88: %empty
#line 2089 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 587: // sub_pd_pool: "{" $@88 pd_pool_params "}"
#line 2093 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3360 "dhcp6_parser.cc"
    break;

  case 590: // pd_pool_params: pd_pool_params ","
#line 2103 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3368 "dhcp6_parser.cc"
    break;

  case 602: // $@89: %empty
#line 2121 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 603: // pd_prefix: "prefix" $@89 ":" "constant string"
#line 2124 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 604: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2130 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 605: // $@90: %empty
#line 2136 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3406 "dhcp6_parser.cc"
    break;

  case 606: // excluded_prefix: "excluded-prefix" $@90 ":" "constant string"
#line 2139 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3416 "dhcp6_parser.cc"
    break;

  case 607: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2145 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3426 "dhcp6_parser.cc"
    break;

  case 608: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2151 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3436 "dhcp6_parser.cc"
    break;

  case 609: // $@91: %empty
#line 2160 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 610: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2166 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3457 "dhcp6_parser.cc"
    break;

  case 615: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2177 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3465 "dhcp6_parser.cc"
    break;

  case 616: // $@92: %empty
#line 2182 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3475 "dhcp6_parser.cc"
    break;

  case 617: // reservation: "{" $@92 reservation_params "}"
#line 2186 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 618: // $@93: %empty
#line 2191 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 619: // sub_reservation: "{" $@93 reservation_params "}"
#line 2195 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3503 "dhcp6_parser.cc"
    break;

  case 624: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2206 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3511 "dhcp6_parser.cc"
    break;

  case 636: // $@94: %empty
#line 2225 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp6_parser.cc"
    break;

  case 637: // ip_addresses: "ip-addresses" $@94 ":" list_strings
#line 2231 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3532 "dhcp6_parser.cc"
    break;

  case 638: // $@95: %empty
#line 2236 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 639: // prefixes: "prefixes" $@95 ":" list_strings
#line 2242 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 640: // $@96: %empty
#line 2247 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 641: // duid: "duid" $@96 ":" "constant string"
#line 2250 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3572 "dhcp6_parser.cc"
    break;

  case 642: // $@97: %empty
#line 2256 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3581 "dhcp6_parser.cc"
    break;

  case 643: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2259 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3591 "dhcp6_parser.cc"
    break;

  case 644: // $@98: %empty
#line 2265 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3600 "dhcp6_parser.cc"
    break;

  case 645: // hostname: "hostname" $@98 ":" "constant string"
#line 2268 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3610 "dhcp6_parser.cc"
    break;

  case 646: // $@99: %empty
#line 2274 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3619 "dhcp6_parser.cc"
    break;

  case 647: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2277 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3629 "dhcp6_parser.cc"
    break;

  case 648: // $@100: %empty
#line 2283 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3641 "dhcp6_parser.cc"
    break;

  case 649: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2289 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3650 "dhcp6_parser.cc"
    break;

  case 650: // $@101: %empty
#line 2297 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 651: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2303 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3671 "dhcp6_parser.cc"
    break;

  case 654: // $@102: %empty
#line 2312 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3680 "dhcp6_parser.cc"
    break;

  case 655: // ip_address: "ip-address" $@102 ":" "constant string"
#line 2315 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 656: // $@103: %empty
#line 2324 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3702 "dhcp6_parser.cc"
    break;

  case 657: // client_classes: "client-classes" $@103 ":" "[" client_classes_list "]"
#line 2330 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 660: // client_classes_list: client_classes_list ","
#line 2337 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3719 "dhcp6_parser.cc"
    break;

  case 661: // $@104: %empty
#line 2342 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3729 "dhcp6_parser.cc"
    break;

  case 662: // client_class_entry: "{" $@104 client_class_params "}"
#line 2346 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 667: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2358 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3747 "dhcp6_parser.cc"
    break;

  case 682: // $@105: %empty
#line 2380 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 683: // client_class_test: "test" $@105 ":" "constant string"
#line 2383 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 684: // only_if_required: "only-if-required" ":" "boolean"
#line 2389 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 685: // $@106: %empty
#line 2398 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3788 "dhcp6_parser.cc"
    break;

  case 686: // server_id: "server-id" $@106 ":" "{" server_id_params "}"
#line 2404 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3799 "dhcp6_parser.cc"
    break;

  case 689: // server_id_params: server_id_params ","
#line 2413 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3807 "dhcp6_parser.cc"
    break;

  case 699: // $@107: %empty
#line 2429 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3816 "dhcp6_parser.cc"
    break;

  case 700: // server_id_type: "type" $@107 ":" duid_type
#line 2432 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3825 "dhcp6_parser.cc"
    break;

  case 701: // duid_type: "LLT"
#line 2437 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3831 "dhcp6_parser.cc"
    break;

  case 702: // duid_type: "EN"
#line 2438 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3837 "dhcp6_parser.cc"
    break;

  case 703: // duid_type: "LL"
#line 2439 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3843 "dhcp6_parser.cc"
    break;

  case 704: // htype: "htype" ":" "integer"
#line 2442 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 705: // $@108: %empty
#line 2448 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3862 "dhcp6_parser.cc"
    break;

  case 706: // identifier: "identifier" $@108 ":" "constant string"
#line 2451 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 707: // time: "time" ":" "integer"
#line 2457 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 708: // enterprise_id: "enterprise-id" ":" "integer"
#line 2463 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 709: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2471 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 710: // $@109: %empty
#line 2479 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3914 "dhcp6_parser.cc"
    break;

  case 711: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2485 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 714: // control_socket_params: control_socket_params ","
#line 2492 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3931 "dhcp6_parser.cc"
    break;

  case 720: // $@110: %empty
#line 2504 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 721: // socket_type: "socket-type" $@110 ":" "constant string"
#line 2507 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3950 "dhcp6_parser.cc"
    break;

  case 722: // $@111: %empty
#line 2513 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3959 "dhcp6_parser.cc"
    break;

  case 723: // socket_name: "socket-name" $@111 ":" "constant string"
#line 2516 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3969 "dhcp6_parser.cc"
    break;

  case 724: // $@112: %empty
#line 2525 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 725: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2531 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 728: // queue_control_params: queue_control_params ","
#line 2540 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4000 "dhcp6_parser.cc"
    break;

  case 735: // enable_queue: "enable-queue" ":" "boolean"
#line 2553 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 736: // $@113: %empty
#line 2559 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 737: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2562 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 738: // capacity: "capacity" ":" "integer"
#line 2568 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4039 "dhcp6_parser.cc"
    break;

  case 739: // $@114: %empty
#line 2574 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4048 "dhcp6_parser.cc"
    break;

  case 740: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2577 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4057 "dhcp6_parser.cc"
    break;

  case 741: // $@115: %empty
#line 2584 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 742: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2590 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4080 "dhcp6_parser.cc"
    break;

  case 743: // $@116: %empty
#line 2597 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 744: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2601 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4100 "dhcp6_parser.cc"
    break;

  case 747: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2609 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4108 "dhcp6_parser.cc"
    break;

  case 766: // enable_updates: "enable-updates" ":" "boolean"
#line 2634 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 767: // $@117: %empty
#line 2641 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 768: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2644 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 769: // $@118: %empty
#line 2650 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4146 "dhcp6_parser.cc"
    break;

  case 770: // server_ip: "server-ip" $@118 ":" "constant string"
#line 2653 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 771: // server_port: "server-port" ":" "integer"
#line 2659 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 772: // $@119: %empty
#line 2665 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4175 "dhcp6_parser.cc"
    break;

  case 773: // sender_ip: "sender-ip" $@119 ":" "constant string"
#line 2668 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4185 "dhcp6_parser.cc"
    break;

  case 774: // sender_port: "sender-port" ":" "integer"
#line 2674 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 775: // max_queue_size: "max-queue-size" ":" "integer"
#line 2680 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 776: // $@120: %empty
#line 2686 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 777: // ncr_protocol: "ncr-protocol" $@120 ":" ncr_protocol_value
#line 2689 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4223 "dhcp6_parser.cc"
    break;

  case 778: // ncr_protocol_value: "UDP"
#line 2695 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4229 "dhcp6_parser.cc"
    break;

  case 779: // ncr_protocol_value: "TCP"
#line 2696 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4235 "dhcp6_parser.cc"
    break;

  case 780: // $@121: %empty
#line 2699 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4244 "dhcp6_parser.cc"
    break;

  case 781: // ncr_format: "ncr-format" $@121 ":" "JSON"
#line 2702 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4254 "dhcp6_parser.cc"
    break;

  case 782: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2709 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4264 "dhcp6_parser.cc"
    break;

  case 783: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2716 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4274 "dhcp6_parser.cc"
    break;

  case 784: // $@122: %empty
#line 2723 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 785: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2726 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4292 "dhcp6_parser.cc"
    break;

  case 786: // $@123: %empty
#line 2732 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4301 "dhcp6_parser.cc"
    break;

  case 787: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2735 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4311 "dhcp6_parser.cc"
    break;

  case 788: // $@124: %empty
#line 2742 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4320 "dhcp6_parser.cc"
    break;

  case 789: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2745 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4330 "dhcp6_parser.cc"
    break;

  case 790: // $@125: %empty
#line 2752 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4339 "dhcp6_parser.cc"
    break;

  case 791: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2755 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4349 "dhcp6_parser.cc"
    break;

  case 792: // $@126: %empty
#line 2764 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4361 "dhcp6_parser.cc"
    break;

  case 793: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2770 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4371 "dhcp6_parser.cc"
    break;

  case 794: // $@127: %empty
#line 2776 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4381 "dhcp6_parser.cc"
    break;

  case 795: // sub_config_control: "{" $@127 config_control_params "}"
#line 2780 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4390 "dhcp6_parser.cc"
    break;

  case 798: // config_control_params: config_control_params ","
#line 2788 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4398 "dhcp6_parser.cc"
    break;

  case 801: // $@128: %empty
#line 2798 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4410 "dhcp6_parser.cc"
    break;

  case 802: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2804 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4419 "dhcp6_parser.cc"
    break;

  case 803: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2809 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4429 "dhcp6_parser.cc"
    break;

  case 804: // $@129: %empty
#line 2817 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 805: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2823 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 808: // loggers_entries: loggers_entries ","
#line 2832 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4458 "dhcp6_parser.cc"
    break;

  case 809: // $@130: %empty
#line 2838 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4468 "dhcp6_parser.cc"
    break;

  case 810: // logger_entry: "{" $@130 logger_params "}"
#line 2842 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4476 "dhcp6_parser.cc"
    break;

  case 813: // logger_params: logger_params ","
#line 2848 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4484 "dhcp6_parser.cc"
    break;

  case 821: // debuglevel: "debuglevel" ":" "integer"
#line 2862 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4494 "dhcp6_parser.cc"
    break;

  case 822: // $@131: %empty
#line 2868 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4503 "dhcp6_parser.cc"
    break;

  case 823: // severity: "severity" $@131 ":" "constant string"
#line 2871 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4513 "dhcp6_parser.cc"
    break;

  case 824: // $@132: %empty
#line 2877 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4525 "dhcp6_parser.cc"
    break;

  case 825: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2883 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4534 "dhcp6_parser.cc"
    break;

  case 828: // output_options_list_content: output_options_list_content ","
#line 2890 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4542 "dhcp6_parser.cc"
    break;

  case 829: // $@133: %empty
#line 2895 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4552 "dhcp6_parser.cc"
    break;

  case 830: // output_entry: "{" $@133 output_params_list "}"
#line 2899 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4560 "dhcp6_parser.cc"
    break;

  case 833: // output_params_list: output_params_list ","
#line 2905 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4568 "dhcp6_parser.cc"
    break;

  case 839: // $@134: %empty
#line 2917 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4577 "dhcp6_parser.cc"
    break;

  case 840: // output: "output" $@134 ":" "constant string"
#line 2920 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4587 "dhcp6_parser.cc"
    break;

  case 841: // flush: "flush" ":" "boolean"
#line 2926 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4597 "dhcp6_parser.cc"
    break;

  case 842: // maxsize: "maxsize" ":" "integer"
#line 2932 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4607 "dhcp6_parser.cc"
    break;

  case 843: // maxver: "maxver" ":" "integer"
#line 2938 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4617 "dhcp6_parser.cc"
    break;

  case 844: // $@135: %empty
#line 2944 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4626 "dhcp6_parser.cc"
    break;

  case 845: // pattern: "pattern" $@135 ":" "constant string"
#line 2947 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4636 "dhcp6_parser.cc"
    break;

  case 846: // $@136: %empty
#line 2953 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4648 "dhcp6_parser.cc"
    break;

  case 847: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2959 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4657 "dhcp6_parser.cc"
    break;

  case 850: // compatibility_params: compatibility_params ","
#line 2966 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4665 "dhcp6_parser.cc"
    break;

  case 853: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2975 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4675 "dhcp6_parser.cc"
    break;


#line 4679 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -984;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     203,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,    32,    30,    45,    47,    51,
      58,    61,   105,   117,   126,   130,   137,   144,   157,   180,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,    30,   103,
     160,   163,    67,   659,    84,   -17,   260,   124,   113,   208,
     -87,   445,   289,  -984,   238,   251,   356,   286,   311,  -984,
      79,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   363,   373,
     389,   406,   407,   426,   434,   435,   436,   440,   442,   443,
     446,   447,  -984,   448,   449,   450,   454,   455,  -984,  -984,
    -984,   456,   458,   459,  -984,  -984,  -984,   462,  -984,  -984,
    -984,  -984,   464,   465,   466,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,   468,  -984,  -984,  -984,  -984,  -984,
    -984,   470,   472,   473,  -984,  -984,   474,  -984,    83,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,   475,  -984,    87,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   478,   479,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,    97,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,   118,  -984,  -984,  -984,  -984,  -984,   489,
    -984,   490,   491,  -984,  -984,  -984,  -984,  -984,  -984,   128,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,   420,   494,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,   497,  -984,  -984,
     495,  -984,  -984,  -984,   504,  -984,  -984,   502,   508,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,   509,   511,  -984,  -984,  -984,  -984,   510,   514,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,   138,  -984,  -984,  -984,   515,  -984,  -984,   517,
    -984,   518,   521,  -984,  -984,   522,   523,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,   154,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,   525,   158,  -984,  -984,  -984,  -984,    30,    30,
    -984,   291,   527,  -984,  -984,   529,   537,   538,   539,   540,
     541,   338,   339,   340,   343,   344,   347,   348,   350,   351,
     353,   354,   355,   352,   359,   562,   361,   366,   367,   369,
     370,   569,   572,   577,   374,   377,   379,   579,   586,   587,
     385,   591,   592,   593,   594,   390,   405,   408,   612,   613,
     615,   616,   617,   620,   621,   622,   623,   421,   624,   626,
     627,   628,   629,   630,   425,   427,   428,   632,   635,  -984,
     163,  -984,   637,   432,    67,  -984,   640,   641,   642,   643,
     644,   441,   444,   646,   647,   649,   659,  -984,   651,    84,
    -984,   652,   452,   653,   453,   457,   -17,  -984,   654,   658,
     660,   662,   663,   664,   665,  -984,   260,  -984,   666,   667,
     467,   668,   669,   670,   469,  -984,   113,   677,   476,   477,
    -984,   208,   678,   679,   206,  -984,   480,   681,   684,   481,
     687,   493,   524,   693,   694,   506,   507,   695,   714,   715,
     725,   445,  -984,   726,   526,   289,  -984,  -984,  -984,   729,
     505,   533,   656,   734,   735,   737,   741,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,   542,  -984,  -984,  -984,  -984,  -984,   182,   543,   552,
    -984,  -984,  -984,   742,   743,   755,  -984,   756,   759,   555,
     334,  -984,  -984,  -984,   762,   763,   764,   766,   765,   769,
     772,   771,   773,  -984,   774,   775,   777,   778,   564,   580,
    -984,  -984,  -984,   781,   782,  -984,   783,  -984,  -984,   785,
     786,   598,   599,   600,  -984,  -984,   783,   601,   812,  -984,
     618,  -984,   619,  -984,   625,  -984,  -984,  -984,   783,   783,
     783,   631,   638,   648,   650,  -984,   655,   661,  -984,   671,
     672,   673,  -984,  -984,   674,  -984,  -984,  -984,   675,   759,
    -984,  -984,   676,   680,  -984,   682,  -984,  -984,   243,   607,
    -984,  -984,   182,   683,   685,   686,  -984,   817,  -984,  -984,
      30,   163,  -984,   289,    67,   296,   296,   816,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,   820,   821,   822,
     823,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   -84,
      30,   156,   713,   824,   826,   827,   290,   109,   -44,   -42,
     -36,   445,  -984,  -984,   828,  -154,  -984,  -984,   832,   835,
    -984,  -984,  -984,  -984,  -984,   -37,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,   816,  -984,   164,   165,   176,
    -984,  -984,  -984,  -984,   844,   845,   846,   847,   852,   854,
     855,  -984,   856,  -984,  -984,  -984,  -984,  -984,   177,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   188,  -984,
     857,   862,  -984,  -984,   861,   866,  -984,  -984,   864,   868,
    -984,  -984,   867,   871,  -984,  -984,   869,   873,  -984,  -984,
    -984,    91,  -984,  -984,  -984,   878,  -984,  -984,  -984,    95,
    -984,  -984,  -984,  -984,   195,  -984,  -984,  -984,   110,  -984,
    -984,   879,   874,  -984,  -984,   880,   885,  -984,   887,   890,
     891,   892,   893,   894,   196,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,   895,   896,   897,  -984,  -984,  -984,
    -984,   233,  -984,  -984,  -984,  -984,  -984,  -984,   898,   899,
     900,  -984,   239,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,   240,  -984,  -984,  -984,   901,  -984,
     902,  -984,  -984,  -984,   250,  -984,  -984,  -984,  -984,  -984,
     285,  -984,   152,  -984,   903,  -984,   301,  -984,  -984,   701,
    -984,   904,   906,  -984,  -984,   905,   909,  -984,  -984,  -984,
     907,  -984,   908,  -984,  -984,  -984,   912,   913,   914,   915,
     705,   710,   716,   711,   719,   721,   722,   918,   724,   919,
     929,   931,   932,   296,  -984,  -984,   296,  -984,   816,   659,
    -984,   820,   113,  -984,   821,   208,  -984,   822,   748,  -984,
     823,   -84,  -984,  -984,   156,  -984,   938,   713,  -984,   302,
     824,  -984,   260,  -984,   826,   -87,  -984,   827,   738,   744,
     750,   751,   753,   754,   290,  -984,   939,   941,   758,   776,
     790,   109,  -984,   779,   791,   794,   -44,  -984,   979,  1002,
     -42,  -984,   798,  1005,   809,  1017,   -36,  -984,  -984,   205,
     828,  -984,   815,  -154,  -984,  -984,  1016,  1027,    84,  -984,
     832,   -17,  -984,   835,  1039,  -984,  -984,   242,   843,   859,
     872,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   349,  -984,
     875,   877,   881,   882,  -984,   303,  -984,   310,  -984,  1065,
    -984,  1068,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   358,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   883,  -984,
    -984,  1081,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  1078,  1084,  -984,  -984,  -984,  -984,  -984,
    1083,  -984,   365,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,   304,   886,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,   888,   889,  -984,  -984,   910,  -984,    30,  -984,  -984,
    1088,  -984,  -984,  -984,  -984,  -984,   368,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,   911,   381,  -984,   423,  -984,
     916,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
     748,  -984,  -984,  1090,   917,  -984,   302,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  1093,   920,
    1094,   205,  -984,  -984,  -984,  -984,  -984,  -984,   922,  -984,
    -984,  1095,  -984,   923,  -984,  -984,  1092,  -984,  -984,   284,
    -984,   175,  1092,  -984,  -984,  1097,  1098,  1099,  -984,   424,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  1100,   921,   924,
     925,  1101,   175,  -984,   927,  -984,  -984,  -984,   928,  -984,
    -984,  -984
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   184,     9,   356,    11,
     559,    13,   586,    15,   618,    17,   479,    19,   488,    21,
     527,    23,   318,    25,   743,    27,   794,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   620,     0,   490,   529,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   137,   792,   182,   197,   199,   201,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   156,   163,
     165,     0,     0,     0,   347,   477,   518,     0,   425,   573,
     575,   417,     0,     0,     0,   274,   293,   283,   266,   656,
     609,   309,   330,   685,     0,   295,   710,   724,   741,   169,
     171,     0,     0,     0,   804,   846,     0,   136,     0,    69,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   117,   118,   127,   128,   129,   106,   135,
     131,   132,   133,    84,    85,    86,    87,   103,    88,    90,
      89,   130,    94,    95,    82,   108,   109,   110,   107,    83,
      92,    93,   101,   102,   104,    91,    96,    97,    98,    99,
     100,   105,   116,   134,   194,     0,   193,     0,   186,   189,
     190,   191,   192,   550,   577,   404,   406,   408,     0,     0,
     412,   410,   650,   403,   361,   362,   363,   364,   365,   366,
     367,   368,   387,   388,   389,   390,   391,   394,   395,   396,
     397,   398,   399,   400,   401,   392,   393,   402,     0,   358,
     372,   373,   374,   377,   378,   381,   382,   383,   380,   375,
     376,   369,   370,   385,   386,   371,   379,   384,   571,   570,
     566,   567,   565,     0,   561,   564,   568,   569,   602,     0,
     605,     0,     0,   601,   595,   596,   594,   599,   600,     0,
     588,   591,   592,   597,   598,   593,   648,   636,   638,   640,
     642,   644,   646,   635,   632,   633,   634,     0,   621,   622,
     627,   628,   625,   629,   630,   631,   626,     0,   508,   244,
       0,   512,   510,   515,     0,   504,   505,     0,   491,   492,
     495,   507,   496,   497,   498,   514,   499,   500,   501,   502,
     503,   544,     0,     0,   542,   543,   546,   547,     0,   530,
     531,   534,   535,   536,   537,   538,   539,   540,   541,   326,
     328,   323,     0,   320,   324,   325,     0,   767,   769,     0,
     772,     0,     0,   776,   780,     0,     0,   784,   786,   788,
     790,   765,   763,   764,     0,   745,   748,   760,   749,   750,
     751,   752,   753,   754,   755,   756,   757,   758,   759,   761,
     762,   801,     0,     0,   796,   799,   800,    47,    52,     0,
      39,    45,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      71,    68,     0,     0,   188,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   360,   357,     0,   563,
     560,     0,     0,     0,     0,     0,   590,   587,     0,     0,
       0,     0,     0,     0,     0,   619,   624,   480,     0,     0,
       0,     0,     0,     0,     0,   489,   494,     0,     0,     0,
     528,   533,     0,     0,   322,   319,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   747,   744,     0,     0,   798,   795,    51,    43,     0,
       0,     0,     0,     0,     0,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,   174,   175,   153,   154,   155,     0,     0,     0,
     167,   168,   173,     0,     0,     0,   178,     0,     0,     0,
       0,   414,   415,   416,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   709,     0,     0,     0,     0,     0,     0,
     179,   180,   181,     0,     0,    70,     0,   196,   187,     0,
       0,     0,     0,     0,   423,   424,     0,     0,     0,   359,
       0,   562,     0,   604,     0,   607,   608,   589,     0,     0,
       0,     0,     0,     0,     0,   623,     0,     0,   506,     0,
       0,     0,   517,   493,     0,   548,   549,   532,     0,     0,
     321,   766,     0,     0,   771,     0,   774,   775,     0,     0,
     782,   783,     0,     0,     0,     0,   746,     0,   803,   797,
       0,     0,   138,     0,     0,     0,     0,   203,   177,   158,
     159,   160,   161,   162,   157,   164,   166,   349,   481,   520,
     427,    40,   574,   576,   419,   420,   421,   422,   418,     0,
      48,     0,     0,     0,   611,   311,     0,     0,     0,     0,
       0,     0,   170,   172,     0,     0,    53,   195,   552,   579,
     405,   407,   409,   413,   411,     0,   572,   603,   606,   649,
     637,   639,   641,   643,   645,   647,   509,   245,   513,   511,
     516,   545,   327,   329,   768,   770,   773,   778,   779,   777,
     781,   785,   787,   789,   791,   203,    44,     0,     0,     0,
     232,   237,   239,   241,     0,     0,     0,     0,     0,     0,
       0,   251,     0,   258,   260,   262,   264,   231,     0,   210,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     224,   225,   226,   223,   227,   228,   229,   230,     0,   208,
       0,   204,   205,   354,     0,   350,   351,   486,     0,   482,
     483,   525,     0,   521,   522,   432,     0,   428,   429,   281,
     282,     0,   276,   279,   280,     0,   291,   292,   288,     0,
     285,   289,   290,   272,     0,   268,   271,   661,     0,   658,
     616,     0,   612,   613,   316,     0,   312,   313,     0,     0,
       0,     0,     0,     0,     0,   332,   335,   336,   337,   338,
     339,   340,   699,   705,     0,     0,     0,   698,   695,   696,
     697,     0,   687,   690,   693,   691,   692,   694,     0,     0,
       0,   305,     0,   297,   300,   301,   302,   303,   304,   720,
     722,   719,   717,   718,     0,   712,   715,   716,     0,   736,
       0,   739,   732,   733,     0,   726,   729,   730,   731,   734,
       0,   809,     0,   806,     0,   852,     0,   848,   851,    55,
     557,     0,   553,   554,   584,     0,   580,   581,   654,   653,
       0,   652,     0,    64,   793,   183,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   212,   198,   200,     0,   202,   207,     0,
     348,   353,   490,   478,   485,   529,   519,   524,     0,   426,
     431,   278,   275,   294,   287,   284,     0,   270,   267,   663,
     660,   657,   620,   610,   615,     0,   310,   315,     0,     0,
       0,     0,     0,     0,   334,   331,     0,     0,     0,     0,
       0,   689,   686,     0,     0,     0,   299,   296,     0,     0,
     714,   711,     0,     0,     0,     0,   728,   725,   742,     0,
     808,   805,     0,   850,   847,    57,     0,    56,     0,   551,
     556,     0,   578,   583,     0,   651,   802,     0,     0,     0,
       0,   243,   246,   247,   248,   249,   257,   250,     0,   256,
       0,     0,     0,     0,   211,     0,   206,     0,   352,     0,
     484,     0,   523,   476,   451,   452,   453,   455,   456,   457,
     441,   442,   460,   461,   462,   463,   464,   467,   468,   469,
     470,   471,   472,   473,   474,   465,   466,   475,   437,   438,
     439,   440,   449,   450,   446,   447,   448,   445,   454,     0,
     434,   443,   458,   459,   444,   430,   277,   286,     0,   269,
     682,     0,   680,   674,   675,   676,   677,   678,   679,   681,
     671,   672,   673,     0,   664,   665,   668,   669,   670,   659,
       0,   614,     0,   314,   341,   342,   343,   344,   345,   346,
     333,     0,     0,   704,   707,   708,   688,   306,   307,   308,
     298,     0,     0,   713,   735,     0,   738,     0,   727,   824,
       0,   822,   820,   814,   818,   819,     0,   811,   816,   817,
     815,   807,   853,   849,    54,    59,     0,   555,     0,   582,
       0,   234,   235,   236,   233,   238,   240,   242,   253,   254,
     255,   252,   259,   261,   263,   265,   209,   355,   487,   526,
     436,   433,   273,     0,     0,   662,   667,   617,   317,   701,
     702,   703,   700,   706,   721,   723,   737,   740,     0,     0,
       0,   813,   810,    58,   558,   585,   655,   435,     0,   684,
     666,     0,   821,     0,   812,   683,     0,   823,   829,     0,
     826,     0,   828,   825,   839,     0,     0,     0,   844,     0,
     831,   834,   835,   836,   837,   838,   827,     0,     0,     0,
       0,     0,   833,   830,     0,   841,   842,   843,     0,   832,
     840,   845
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,   -10,  -984,  -574,  -984,
     417,  -984,  -984,  -984,  -984,   371,  -984,  -516,  -984,  -984,
    -984,   -71,  -984,  -984,  -984,  -984,  -984,  -984,  -984,   396,
     608,  -984,  -984,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19,  -984,    34,    37,    38,
      41,  -984,   410,    49,  -984,    52,  -984,    54,    55,    56,
    -984,    59,  -984,    62,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,   395,   606,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,   318,  -984,   116,
    -984,  -700,   122,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,   -45,  -984,  -736,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,    99,  -984,  -984,  -984,
    -984,  -984,   108,  -719,  -984,  -984,  -984,  -984,   106,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,    76,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,    94,  -984,  -984,  -984,   100,   570,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,    92,  -984,  -984,
    -984,  -984,  -984,  -984,  -983,  -984,  -984,  -984,   135,  -984,
    -984,  -984,   139,   633,  -984,  -984,  -981,  -984,  -980,  -984,
      73,  -984,    75,  -984,    66,    69,    70,    72,  -984,  -984,
    -984,  -979,  -984,  -984,  -984,  -984,   127,  -984,  -984,  -101,
    1063,  -984,  -984,  -984,  -984,  -984,   141,  -984,  -984,  -984,
     140,  -984,   602,  -984,   -67,  -984,  -984,  -984,  -984,  -984,
     -64,  -984,  -984,  -984,  -984,  -984,     4,  -984,  -984,  -984,
     143,  -984,  -984,  -984,   142,  -984,   603,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,    81,  -984,
    -984,  -984,    85,   636,  -984,  -984,   -55,  -984,   -12,  -984,
    -984,  -984,  -984,  -984,    86,  -984,  -984,  -984,    89,   639,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,   -60,  -984,  -984,
    -984,   132,  -984,  -984,  -984,   136,  -984,   634,   387,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -977,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
     146,  -984,  -984,  -984,   -89,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,   120,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,   112,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,   107,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,   413,   596,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,   460,   597,  -984,  -984,  -984,
    -984,  -984,  -984,   111,  -984,  -984,   -93,  -984,  -984,  -984,
    -984,  -984,  -984,  -108,  -984,  -984,  -126,  -984,  -984,  -984,
    -984,  -984,  -984,  -984,  -984,  -984,  -984,   114,  -984
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     732,    87,    88,    41,    68,    84,    85,   757,   959,  1066,
    1067,   817,    43,    70,    90,   432,    91,    45,    71,   158,
     159,   160,   435,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   461,   724,   179,   462,   180,   463,   181,   182,   183,
     492,   184,   493,   185,   186,   187,   188,   455,   189,   190,
     191,   192,   193,   437,    47,    72,   227,   228,   229,   502,
     230,   194,   438,   195,   439,   196,   440,   840,   841,   842,
     996,   818,   819,   820,   976,  1224,   821,   977,   822,   978,
     823,   979,   824,   825,   539,   826,   827,   828,   829,   830,
     831,   987,  1231,   832,   833,   834,   989,   835,   990,   836,
     991,   837,   992,   197,   481,   874,   875,   876,  1016,   198,
     478,   861,   862,   863,   864,   199,   480,   869,   870,   871,
     872,   200,   479,   201,   488,   922,   923,   924,   925,   926,
     202,   484,   885,   886,   887,  1025,    63,    80,   382,   383,
     384,   552,   385,   553,   203,   485,   894,   895,   896,   897,
     898,   899,   900,   901,   204,   467,   844,   845,   846,   999,
      49,    73,   268,   269,   270,   508,   271,   509,   272,   510,
     273,   514,   274,   513,   205,   206,   207,   208,   474,   738,
     279,   280,   209,   471,   856,   857,   858,  1008,  1139,  1140,
     210,   468,    57,    77,   848,   849,   850,  1002,    59,    78,
     347,   348,   349,   350,   351,   352,   353,   538,   354,   542,
     355,   541,   356,   357,   543,   358,   211,   469,   852,   853,
     854,  1005,    61,    79,   368,   369,   370,   371,   372,   547,
     373,   374,   375,   376,   282,   506,   961,   962,   963,  1068,
      51,    74,   293,   294,   295,   518,   212,   472,   213,   473,
     285,   507,   965,   966,   967,  1071,    53,    75,   309,   310,
     311,   521,   312,   313,   523,   314,   315,   214,   483,   881,
     882,   883,  1022,    55,    76,   327,   328,   329,   330,   529,
     331,   530,   332,   531,   333,   532,   334,   533,   335,   534,
     336,   528,   287,   515,   970,   971,  1074,   215,   482,   878,
     879,  1019,  1163,  1164,  1165,  1166,  1167,  1243,  1168,   216,
     486,   911,   912,   913,  1036,  1252,   914,   915,  1037,   916,
     917,   217,   218,   489,   934,   935,   936,  1048,   937,  1049,
     219,   490,   944,   945,   946,   947,  1053,   948,   949,  1055,
     220,   491,    65,    81,   404,   405,   406,   407,   557,   408,
     558,   409,   410,   560,   411,   412,   413,   563,   789,   414,
     564,   415,   416,   417,   567,   418,   568,   419,   569,   420,
     570,   221,   436,    67,    82,   423,   424,   425,   573,   426,
     222,   497,   952,   953,  1059,  1206,  1207,  1208,  1209,  1260,
    1210,  1258,  1279,  1280,  1281,  1289,  1290,  1291,  1297,  1292,
    1293,  1294,  1295,  1301,   223,   498,   956,   957,   958
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     157,   226,   243,   289,   303,   323,    38,   345,   364,   381,
     401,   908,   366,   286,   250,   367,   838,   231,   283,   296,
     307,   325,   868,   359,   377,  1129,   402,  1130,  1131,  1138,
     244,  1144,    30,   346,   365,    31,   859,    32,   954,    33,
     379,   380,   251,   252,   731,   253,   254,   255,   129,   130,
     129,   130,    42,   156,    44,   126,   129,   130,    46,   245,
     232,   284,   297,   308,   326,    48,   360,   378,    50,   403,
     298,   299,   300,   301,   302,   129,   130,   281,   292,   306,
     324,   317,   433,   224,   225,   246,   500,   434,   968,   247,
     504,   501,   256,   248,  1011,   505,   240,  1012,  1014,   241,
     516,  1015,   918,   919,   920,   517,   249,   257,   929,   930,
     258,   259,    52,  1020,   260,   731,  1021,   938,   939,   940,
     156,   519,   261,   860,    54,   262,   520,   263,   264,   265,
     902,   526,   266,    56,   338,   267,   527,    58,   805,   275,
     763,   554,   276,   277,    60,   278,   555,   290,   304,   291,
     305,    62,   769,   770,   771,  1060,   126,   571,  1061,   129,
     130,   575,   572,   156,    64,   156,   576,   500,   575,   288,
      89,   941,   973,   974,    92,    93,   129,   130,    94,   504,
     993,    95,    96,    97,   975,   994,   339,    66,   340,   341,
     156,   993,   342,   343,   344,   125,   995,   240,  1017,  1034,
     241,   129,   130,  1018,  1035,   129,   130,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,  1041,    34,    35,    36,
      37,  1042,  1046,  1050,   427,   127,   128,  1047,  1051,   903,
     904,   905,   906,  1056,   428,   129,   130,  1129,  1057,  1130,
    1131,  1138,   131,  1144,  1221,  1222,  1223,   132,   133,   134,
     135,   136,   137,   138,   156,   139,   859,   866,   339,   867,
     140,   339,   361,   340,   341,   362,   363,  1282,   571,   141,
    1283,   156,   142,  1058,   430,   868,  1095,   129,   130,   143,
     129,   130,   421,   422,  1063,   908,   993,   144,   145,  1064,
      86,  1236,   146,   516,   431,   147,   156,   800,  1237,   148,
     156,   801,   802,   803,   804,   805,   806,   807,   808,   809,
     810,   811,   126,   379,   380,   812,   813,   814,   815,   816,
     149,   150,   151,   152,   153,   154,    98,    99,   100,   101,
     102,   103,   129,   130,   155,   719,   720,   721,   722,  1284,
     429,  1240,  1285,  1286,  1287,  1288,  1241,   441,   554,   339,
     156,  1261,   316,  1248,   126,   339,  1262,   442,   317,   318,
     319,   320,   321,   322,   519,  1228,  1229,  1230,  1199,  1264,
    1200,  1201,   723,   443,   129,   130,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     444,   445,   156,   787,   788,   156,  1150,  1151,   577,   578,
     888,   889,   890,   891,   892,   893,   526,  1302,   535,   157,
     446,  1265,  1303,   226,   734,   735,   736,   737,   447,   448,
     449,  1249,  1250,  1251,   450,   243,   451,   452,   289,   231,
     453,   454,   456,   457,   458,   303,   286,   250,   459,   460,
     464,   283,   465,   466,   296,   323,   470,   156,   475,   476,
     477,   307,   487,   244,   494,   345,   495,   496,   499,   503,
     364,   325,   511,   512,   366,   251,   252,   367,   253,   254,
     255,   359,   232,   522,   524,   525,   377,   536,   579,   540,
     401,   346,   245,   156,   284,   537,   365,   297,   544,   156,
     545,   546,   711,   548,   308,   549,   402,   551,   550,   556,
     281,   559,   561,   292,   326,   562,   565,   566,   246,   574,
     306,   580,   247,   581,   360,   256,   248,   129,   130,   378,
     324,   582,   583,   584,   585,   586,   587,   588,   589,   249,
     257,   590,   591,   258,   259,   592,   593,   260,   594,   403,
     599,   595,   596,   597,   598,   261,   601,   600,   262,   602,
     263,   264,   265,   607,   603,   266,   608,   604,   267,   605,
     606,   609,   275,   613,   610,   276,   277,   611,   278,   612,
     614,   615,   290,   616,   291,   617,   618,   619,   620,   304,
     621,   305,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   622,   624,   625,   623,   626,
     627,   628,   399,   400,   629,   630,   631,   632,   634,   633,
     635,   636,   637,   638,   639,   640,   643,   641,   642,   644,
     157,   646,   647,   226,   649,   650,   651,   652,   653,   654,
     656,   657,   156,   658,   655,   660,   662,   664,   668,   231,
     663,   665,   669,   713,   670,   666,   671,   672,   673,   674,
     676,   677,   679,   680,   681,   678,   907,   921,   931,   682,
     401,   684,   688,   689,   955,   692,   685,   686,   693,   694,
     691,   695,   909,   927,   932,   942,   402,   698,   699,   702,
     796,   696,   232,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   700,   701,   703,   704,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   705,
     707,   126,   697,   710,   708,   910,   928,   933,   943,   403,
     712,   714,   715,   233,   716,   234,   717,   727,   728,   718,
     725,   129,   130,   235,   236,   237,   238,   239,   131,   726,
     729,   730,   733,   132,   133,   134,    32,   739,   740,   741,
     743,   752,   240,   742,   744,   241,   140,   745,   746,   790,
     747,   748,   749,   242,   750,   751,   754,   753,   756,   755,
     758,   759,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   760,   761,   762,   764,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   765,
     126,   339,   795,   839,   873,   766,   767,   843,   847,   851,
     855,   877,   768,   880,   884,   951,   149,   150,   772,   960,
     129,   130,   964,   236,   237,   773,   239,   131,   980,   981,
     982,   983,   132,   133,   134,   774,   984,   775,   985,   986,
     988,   240,   776,   997,   241,   998,   156,  1000,   777,  1001,
    1003,  1004,   242,  1006,  1007,  1009,  1010,  1024,   778,   779,
     780,   781,   782,   784,  1013,  1023,  1026,   785,  1027,   786,
     792,  1028,   793,   794,  1029,  1030,  1031,  1032,  1033,  1038,
    1039,  1040,  1043,  1044,  1045,  1052,  1054,  1062,  1065,  1070,
    1069,  1072,  1073,  1081,  1076,  1075,  1077,  1078,  1079,  1080,
    1082,  1084,  1088,  1090,  1083,   149,   150,  1085,   243,  1086,
    1087,   345,  1089,  1091,   364,  1092,  1093,  1103,   366,   286,
     250,   367,  1148,  1181,   283,  1182,  1174,   359,  1152,  1110,
     377,   323,  1175,  1142,   381,   156,   244,   346,  1176,  1177,
     365,  1178,  1179,  1128,  1161,  1104,  1183,   325,   251,   252,
     907,   253,   254,   255,  1159,   921,  1153,  1111,  1112,   931,
    1113,  1114,  1115,  1191,  1184,   245,   909,   284,  1202,  1187,
     360,   927,   955,   378,  1105,   932,  1143,   289,  1185,  1188,
     303,   942,  1189,   281,  1204,  1154,  1192,  1162,  1194,  1195,
     326,   246,  1141,   296,  1203,   247,   307,  1196,   256,   248,
    1106,  1197,  1214,  1160,  1107,  1212,   324,  1116,  1108,   910,
    1215,  1155,   249,   257,   928,  1156,   258,   259,   933,  1157,
     260,  1109,  1117,  1220,   943,  1118,  1119,  1205,   261,  1120,
    1225,   262,  1158,   263,   264,   265,   297,  1121,   266,   308,
    1122,   267,  1123,  1124,  1125,   275,  1226,  1126,   276,   277,
    1127,   278,   292,  1238,  1134,   306,  1239,  1135,  1136,  1227,
    1137,  1132,  1232,  1133,  1233,  1244,  1245,  1246,  1234,  1235,
    1242,  1247,  1259,  1253,  1268,  1254,  1255,  1271,  1273,  1278,
    1276,  1298,  1299,  1300,  1304,  1308,   783,   797,   645,   799,
     648,   865,   791,   972,  1096,  1094,  1149,  1256,  1263,  1146,
    1147,  1173,  1190,  1266,   690,  1172,  1180,  1269,  1272,  1275,
    1277,  1305,  1306,  1307,  1310,  1311,  1098,  1145,  1097,  1267,
     337,   290,  1099,   291,   304,  1100,   305,  1101,   683,   659,
    1102,  1217,   969,  1216,   687,   661,  1171,  1270,  1170,  1219,
    1218,  1186,  1193,  1198,   950,   667,  1169,   706,  1274,  1103,
     675,  1211,   709,   798,  1296,  1152,  1309,  1213,     0,     0,
       0,  1110,     0,     0,     0,  1142,     0,  1257,     0,     0,
    1202,  1161,     0,     0,     0,  1128,     0,  1104,     0,     0,
       0,  1159,     0,  1153,     0,     0,  1204,     0,     0,  1111,
    1112,     0,  1113,  1114,  1115,     0,  1203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1105,     0,  1143,     0,
       0,     0,  1154,     0,  1162,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1141,     0,     0,     0,     0,  1205,
    1160,     0,  1106,     0,     0,     0,  1107,     0,  1155,  1116,
    1108,     0,  1156,     0,     0,     0,  1157,     0,     0,     0,
       0,     0,     0,  1109,  1117,     0,     0,  1118,  1119,  1158,
       0,  1120,     0,     0,     0,     0,     0,     0,     0,  1121,
       0,     0,  1122,     0,  1123,  1124,  1125,     0,     0,  1126,
       0,     0,  1127,     0,     0,     0,  1134,     0,     0,  1135,
    1136,     0,  1137,  1132,     0,  1133
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   747,    79,    73,    73,    79,   716,    72,    73,    74,
      75,    76,   741,    78,    79,  1008,    81,  1008,  1008,  1008,
      73,  1008,     0,    78,    79,     5,   120,     7,   192,     9,
     127,   128,    73,    73,   618,    73,    73,    73,    92,    93,
      92,    93,     7,   207,     7,    72,    92,    93,     7,    73,
      72,    73,    74,    75,    76,     7,    78,    79,     7,    81,
      87,    88,    89,    90,    91,    92,    93,    73,    74,    75,
      76,   118,     3,    16,    17,    73,     3,     8,   125,    73,
       3,     8,    73,    73,     3,     8,   113,     6,     3,   116,
       3,     6,   146,   147,   148,     8,    73,    73,   150,   151,
      73,    73,     7,     3,    73,   689,     6,   153,   154,   155,
     207,     3,    73,   207,     7,    73,     8,    73,    73,    73,
      21,     3,    73,     7,    21,    73,     8,     7,    29,    73,
     656,     3,    73,    73,     7,    73,     8,    74,    75,    74,
      75,     7,   668,   669,   670,     3,    72,     3,     6,    92,
      93,     3,     8,   207,     7,   207,     8,     3,     3,    85,
      10,   207,     8,     8,    11,    12,    92,    93,    15,     3,
       3,    18,    19,    20,     8,     8,    73,     7,    75,    76,
     207,     3,    79,    80,    81,    71,     8,   113,     3,     3,
     116,    92,    93,     8,     8,    92,    93,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     3,   207,   208,   209,
     210,     8,     3,     3,     6,    82,    83,     8,     8,   140,
     141,   142,   143,     3,     3,    92,    93,  1240,     8,  1240,
    1240,  1240,    99,  1240,    22,    23,    24,   104,   105,   106,
     107,   108,   109,   110,   207,   112,   120,   121,    73,   123,
     117,    73,    74,    75,    76,    77,    78,     3,     3,   126,
       6,   207,   129,     8,     8,  1014,   996,    92,    93,   136,
      92,    93,    13,    14,     3,  1041,     3,   144,   145,     8,
     207,     8,   149,     3,     3,   152,   207,    21,     8,   156,
     207,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    72,   127,   128,    39,    40,    41,    42,    43,
     177,   178,   179,   180,   181,   182,    44,    45,    46,    47,
      48,    49,    92,    93,   191,   173,   174,   175,   176,   184,
       4,     3,   187,   188,   189,   190,     8,     4,     3,    73,
     207,     3,   112,     8,    72,    73,     8,     4,   118,   119,
     120,   121,   122,   123,     3,    36,    37,    38,   183,     8,
     185,   186,   210,     4,    92,    93,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
       4,     4,   207,   170,   171,   207,   114,   115,   428,   429,
     130,   131,   132,   133,   134,   135,     3,     3,     8,   500,
       4,     8,     8,   504,   100,   101,   102,   103,     4,     4,
       4,   137,   138,   139,     4,   516,     4,     4,   519,   504,
       4,     4,     4,     4,     4,   526,   516,   516,     4,     4,
       4,   516,     4,     4,   519,   536,     4,   207,     4,     4,
       4,   526,     4,   516,     4,   546,     4,     4,     4,     4,
     551,   536,     4,     4,   551,   516,   516,   551,   516,   516,
     516,   546,   504,     4,     4,     4,   551,     3,   207,     4,
     571,   546,   516,   207,   516,     8,   551,   519,     4,   207,
       8,     3,     7,     4,   526,     4,   571,     3,     8,     4,
     516,     4,     4,   519,   536,     4,     4,     4,   516,     4,
     526,     4,   516,     4,   546,   516,   516,    92,    93,   551,
     536,     4,     4,     4,     4,     4,   208,   208,   208,   516,
     516,   208,   208,   516,   516,   208,   208,   516,   208,   571,
     208,   210,   209,   209,   209,   516,     4,   208,   516,   208,
     516,   516,   516,     4,   208,   516,     4,   210,   516,   210,
     210,     4,   516,     4,   210,   516,   516,   210,   516,   210,
       4,     4,   519,   208,   519,     4,     4,     4,     4,   526,
     210,   526,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   210,     4,     4,   210,     4,
       4,     4,   177,   178,     4,     4,     4,     4,     4,   208,
       4,     4,     4,     4,     4,   210,     4,   210,   210,     4,
     711,     4,   210,   714,     4,     4,     4,     4,     4,   208,
       4,     4,   207,     4,   210,     4,     4,     4,     4,   714,
     208,   208,     4,     7,     4,   208,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   208,   747,   748,   749,   210,
     751,     4,     4,     4,   755,     4,   210,   210,     4,   208,
     210,     4,   747,   748,   749,   750,   751,     4,     4,     4,
     710,   208,   714,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   210,   210,     4,     4,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     4,
       4,    72,   208,     4,   208,   747,   748,   749,   750,   751,
     207,     7,     7,    84,     7,    86,     5,     5,     5,   207,
     207,    92,    93,    94,    95,    96,    97,    98,    99,   207,
       5,     5,   207,   104,   105,   106,     7,     5,     5,     5,
       5,   207,   113,     7,     5,   116,   117,     5,     7,   172,
       7,     7,     7,   124,     7,     7,     5,   207,     5,     7,
       5,     5,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,   207,   207,   207,   207,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,     7,
      72,    73,     5,     7,   111,   207,   207,     7,     7,     7,
       7,     7,   207,     7,     7,     7,   177,   178,   207,     7,
      92,    93,     7,    95,    96,   207,    98,    99,     4,     4,
       4,     4,   104,   105,   106,   207,     4,   207,     4,     4,
       4,   113,   207,     6,   116,     3,   207,     6,   207,     3,
       6,     3,   124,     6,     3,     6,     3,     3,   207,   207,
     207,   207,   207,   207,     6,     6,     6,   207,     3,   207,
     207,     4,   207,   207,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   207,     3,
       6,     6,     3,   208,     6,     8,     4,     4,     4,     4,
     210,   210,     4,     4,   208,   177,   178,   208,   999,   208,
     208,  1002,   208,     4,  1005,     4,     4,  1008,  1005,   999,
     999,  1005,     4,     4,   999,     4,   208,  1002,  1019,  1008,
    1005,  1022,   208,  1008,  1025,   207,   999,  1002,   208,   208,
    1005,   208,   208,  1008,  1019,  1008,   208,  1022,   999,   999,
    1041,   999,   999,   999,  1019,  1046,  1019,  1008,  1008,  1050,
    1008,  1008,  1008,     4,   208,   999,  1041,   999,  1059,   210,
    1002,  1046,  1063,  1005,  1008,  1050,  1008,  1068,   208,   208,
    1071,  1056,   208,   999,  1059,  1019,     4,  1019,   210,     4,
    1022,   999,  1008,  1068,  1059,   999,  1071,   208,   999,   999,
    1008,     4,     6,  1019,  1008,   210,  1022,  1008,  1008,  1041,
       3,  1019,   999,   999,  1046,  1019,   999,   999,  1050,  1019,
     999,  1008,  1008,     4,  1056,  1008,  1008,  1059,   999,  1008,
     207,   999,  1019,   999,   999,   999,  1068,  1008,   999,  1071,
    1008,   999,  1008,  1008,  1008,   999,   207,  1008,   999,   999,
    1008,   999,  1068,     8,  1008,  1071,     8,  1008,  1008,   207,
    1008,  1008,   207,  1008,   207,     4,     8,     3,   207,   207,
     207,     8,     4,   207,     4,   207,   207,     4,     4,     7,
       5,     4,     4,     4,     4,     4,   689,   711,   500,   714,
     504,   740,   702,   795,   998,   993,  1017,   207,   207,  1011,
    1014,  1027,  1046,   207,   554,  1025,  1034,   210,   208,   207,
     207,   210,   208,   208,   207,   207,  1001,  1010,   999,  1240,
      77,  1068,  1002,  1068,  1071,  1004,  1071,  1005,   546,   516,
    1007,  1070,   765,  1068,   551,   519,  1024,  1246,  1022,  1073,
    1071,  1041,  1050,  1056,   751,   526,  1020,   571,  1261,  1240,
     536,  1060,   575,   713,  1282,  1246,  1302,  1063,    -1,    -1,
      -1,  1240,    -1,    -1,    -1,  1240,    -1,  1197,    -1,    -1,
    1261,  1246,    -1,    -1,    -1,  1240,    -1,  1240,    -1,    -1,
      -1,  1246,    -1,  1246,    -1,    -1,  1261,    -1,    -1,  1240,
    1240,    -1,  1240,  1240,  1240,    -1,  1261,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1240,    -1,  1240,    -1,
      -1,    -1,  1246,    -1,  1246,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1240,    -1,    -1,    -1,    -1,  1261,
    1246,    -1,  1240,    -1,    -1,    -1,  1240,    -1,  1246,  1240,
    1240,    -1,  1246,    -1,    -1,    -1,  1246,    -1,    -1,    -1,
      -1,    -1,    -1,  1240,  1240,    -1,    -1,  1240,  1240,  1246,
      -1,  1240,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1240,
      -1,    -1,  1240,    -1,  1240,  1240,  1240,    -1,    -1,  1240,
      -1,    -1,  1240,    -1,    -1,    -1,  1240,    -1,    -1,  1240,
    1240,    -1,  1240,  1240,    -1,  1240
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
       0,     5,     7,     9,   207,   208,   209,   210,   227,   228,
     229,   234,     7,   243,     7,   248,     7,   295,     7,   401,
       7,   481,     7,   497,     7,   514,     7,   433,     7,   439,
       7,   463,     7,   377,     7,   583,     7,   614,   235,   230,
     244,   249,   296,   402,   482,   498,   515,   434,   440,   464,
     378,   584,   615,   227,   236,   237,   207,   232,   233,    10,
     245,   247,    11,    12,    15,    18,    19,    20,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    82,    83,    92,
      93,    99,   104,   105,   106,   107,   108,   109,   110,   112,
     117,   126,   129,   136,   144,   145,   149,   152,   156,   177,
     178,   179,   180,   181,   182,   191,   207,   242,   250,   251,
     252,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   274,
     276,   278,   279,   280,   282,   284,   285,   286,   287,   289,
     290,   291,   292,   293,   302,   304,   306,   344,   350,   356,
     362,   364,   371,   385,   395,   415,   416,   417,   418,   423,
     431,   457,   487,   489,   508,   538,   550,   562,   563,   571,
     581,   612,   621,   645,    16,    17,   242,   297,   298,   299,
     301,   487,   489,    84,    86,    94,    95,    96,    97,    98,
     113,   116,   124,   242,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   268,   269,   270,
     271,   274,   276,   278,   279,   280,   282,   284,   403,   404,
     405,   407,   409,   411,   413,   415,   416,   417,   418,   421,
     422,   457,   475,   487,   489,   491,   508,   533,    85,   242,
     411,   413,   457,   483,   484,   485,   487,   489,    87,    88,
      89,    90,    91,   242,   411,   413,   457,   487,   489,   499,
     500,   501,   503,   504,   506,   507,   112,   118,   119,   120,
     121,   122,   123,   242,   457,   487,   489,   516,   517,   518,
     519,   521,   523,   525,   527,   529,   531,   431,    21,    73,
      75,    76,    79,    80,    81,   242,   324,   441,   442,   443,
     444,   445,   446,   447,   449,   451,   453,   454,   456,   487,
     489,    74,    77,    78,   242,   324,   445,   451,   465,   466,
     467,   468,   469,   471,   472,   473,   474,   487,   489,   127,
     128,   242,   379,   380,   381,   383,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   177,
     178,   242,   487,   489,   585,   586,   587,   588,   590,   592,
     593,   595,   596,   597,   600,   602,   603,   604,   606,   608,
     610,    13,    14,   616,   617,   618,   620,     6,     3,     4,
       8,     3,   246,     3,     8,   253,   613,   294,   303,   305,
     307,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   288,     4,     4,     4,     4,
       4,   272,   275,   277,     4,     4,     4,   396,   432,   458,
       4,   424,   488,   490,   419,     4,     4,     4,   351,   363,
     357,   345,   539,   509,   372,   386,   551,     4,   365,   564,
     572,   582,   281,   283,     4,     4,     4,   622,   646,     4,
       3,     8,   300,     4,     3,     8,   476,   492,   406,   408,
     410,     4,     4,   414,   412,   534,     3,     8,   486,     3,
       8,   502,     4,   505,     4,     4,     3,     8,   532,   520,
     522,   524,   526,   528,   530,     8,     3,     8,   448,   325,
       4,   452,   450,   455,     4,     8,     3,   470,     4,     4,
       8,     3,   382,   384,     3,     8,     4,   589,   591,     4,
     594,     4,     4,   598,   601,     4,     4,   605,   607,   609,
     611,     3,     8,   619,     4,     3,     8,   227,   227,   207,
       4,     4,     4,     4,     4,     4,     4,   208,   208,   208,
     208,   208,   208,   208,   208,   210,   209,   209,   209,   208,
     208,     4,   208,   208,   210,   210,   210,     4,     4,     4,
     210,   210,   210,     4,     4,     4,   208,     4,     4,     4,
       4,   210,   210,   210,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   208,     4,     4,     4,     4,     4,     4,
     210,   210,   210,     4,     4,   251,     4,   210,   298,     4,
       4,     4,     4,     4,   208,   210,     4,     4,     4,   404,
       4,   484,     4,   208,     4,   208,   208,   500,     4,     4,
       4,     4,     4,     4,     4,   518,     4,     4,   208,     4,
       4,     4,   210,   443,     4,   210,   210,   467,     4,     4,
     380,   210,     4,     4,   208,     4,   208,   208,     4,     4,
     210,   210,     4,     4,     4,     4,   586,     4,   208,   617,
       4,     7,   207,     7,     7,     7,     7,     5,   207,   173,
     174,   175,   176,   210,   273,   207,   207,     5,     5,     5,
       5,   229,   231,   207,   100,   101,   102,   103,   420,     5,
       5,     5,     7,     5,     5,     5,     7,     7,     7,     7,
       7,     7,   207,   207,     5,     7,     5,   238,     5,     5,
     207,   207,   207,   238,   207,     7,   207,   207,   207,   238,
     238,   238,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   231,   207,   207,   207,   170,   171,   599,
     172,   273,   207,   207,   207,     5,   227,   250,   616,   297,
      21,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    39,    40,    41,    42,    43,   242,   312,   313,
     314,   317,   319,   321,   323,   324,   326,   327,   328,   329,
     330,   331,   334,   335,   336,   338,   340,   342,   312,     7,
     308,   309,   310,     7,   397,   398,   399,     7,   435,   436,
     437,     7,   459,   460,   461,     7,   425,   426,   427,   120,
     207,   352,   353,   354,   355,   236,   121,   123,   354,   358,
     359,   360,   361,   111,   346,   347,   348,     7,   540,   541,
       7,   510,   511,   512,     7,   373,   374,   375,   130,   131,
     132,   133,   134,   135,   387,   388,   389,   390,   391,   392,
     393,   394,    21,   140,   141,   142,   143,   242,   326,   487,
     489,   552,   553,   554,   557,   558,   560,   561,   146,   147,
     148,   242,   366,   367,   368,   369,   370,   487,   489,   150,
     151,   242,   487,   489,   565,   566,   567,   569,   153,   154,
     155,   207,   487,   489,   573,   574,   575,   576,   578,   579,
     585,     7,   623,   624,   192,   242,   647,   648,   649,   239,
       7,   477,   478,   479,     7,   493,   494,   495,   125,   519,
     535,   536,   308,     8,     8,     8,   315,   318,   320,   322,
       4,     4,     4,     4,     4,     4,     4,   332,     4,   337,
     339,   341,   343,     3,     8,     8,   311,     6,     3,   400,
       6,     3,   438,     6,     3,   462,     6,     3,   428,     6,
       3,     3,     6,     6,     3,     6,   349,     3,     8,   542,
       3,     6,   513,     6,     3,   376,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   555,   559,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   568,   570,
       3,     8,     4,   577,     4,   580,     3,     8,     8,   625,
       3,     6,     4,     3,     8,   207,   240,   241,   480,     6,
       3,   496,     6,     3,   537,     8,     6,     4,     4,     4,
       4,   208,   210,   208,   210,   208,   208,   208,     4,   208,
       4,     4,     4,     4,   313,   312,   310,   403,   399,   441,
     437,   465,   461,   242,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   268,   269,   270,
     271,   274,   276,   278,   279,   280,   282,   284,   324,   395,
     407,   409,   411,   413,   415,   416,   417,   418,   422,   429,
     430,   457,   487,   489,   533,   427,   353,   359,     4,   347,
     114,   115,   242,   254,   255,   256,   257,   258,   259,   324,
     457,   487,   489,   543,   544,   545,   546,   547,   549,   541,
     516,   512,   379,   375,   208,   208,   208,   208,   208,   208,
     388,     4,     4,   208,   208,   208,   553,   210,   208,   208,
     367,     4,     4,   566,   210,     4,   208,     4,   574,   183,
     185,   186,   242,   324,   487,   489,   626,   627,   628,   629,
     631,   624,   210,   648,     6,     3,   483,   479,   499,   495,
       4,    22,    23,    24,   316,   207,   207,   207,    36,    37,
      38,   333,   207,   207,   207,   207,     8,     8,     8,     8,
       3,     8,   207,   548,     4,     8,     3,     8,     8,   137,
     138,   139,   556,   207,   207,   207,   207,   227,   632,     4,
     630,     3,     8,   207,     8,     8,   207,   430,     4,   210,
     545,     4,   208,     4,   627,   207,     5,   207,     7,   633,
     634,   635,     3,     6,   184,   187,   188,   189,   190,   636,
     637,   638,   640,   641,   642,   643,   634,   639,     4,     4,
       4,   644,     3,     8,     4,   210,   208,   208,     4,   637,
     207,   207
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   211,   213,   212,   214,   212,   215,   212,   216,   212,
     217,   212,   218,   212,   219,   212,   220,   212,   221,   212,
     222,   212,   223,   212,   224,   212,   225,   212,   226,   212,
     227,   227,   227,   227,   227,   227,   227,   228,   230,   229,
     231,   232,   232,   233,   233,   233,   235,   234,   236,   236,
     237,   237,   237,   239,   238,   240,   240,   241,   241,   241,
     242,   244,   243,   246,   245,   245,   247,   249,   248,   250,
     250,   250,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   253,   252,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   272,   271,   273,   273,
     273,   273,   273,   275,   274,   277,   276,   278,   279,   281,
     280,   283,   282,   284,   285,   286,   288,   287,   289,   290,
     291,   292,   294,   293,   296,   295,   297,   297,   297,   298,
     298,   298,   298,   298,   300,   299,   301,   303,   302,   305,
     304,   307,   306,   308,   308,   309,   309,   309,   311,   310,
     312,   312,   312,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   315,   314,   316,   316,   316,   318,   317,   320,
     319,   322,   321,   323,   325,   324,   326,   327,   328,   329,
     330,   332,   331,   333,   333,   333,   334,   335,   337,   336,
     339,   338,   341,   340,   343,   342,   345,   344,   346,   346,
     346,   347,   349,   348,   351,   350,   352,   352,   352,   353,
     353,   354,   355,   357,   356,   358,   358,   358,   359,   359,
     359,   360,   361,   363,   362,   365,   364,   366,   366,   366,
     367,   367,   367,   367,   367,   367,   368,   369,   370,   372,
     371,   373,   373,   374,   374,   374,   376,   375,   378,   377,
     379,   379,   379,   379,   380,   380,   382,   381,   384,   383,
     386,   385,   387,   387,   387,   388,   388,   388,   388,   388,
     388,   389,   390,   391,   392,   393,   394,   396,   395,   397,
     397,   398,   398,   398,   400,   399,   402,   401,   403,   403,
     403,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   406,   405,   408,   407,   410,   409,
     412,   411,   414,   413,   415,   416,   417,   419,   418,   420,
     420,   420,   420,   421,   422,   424,   423,   425,   425,   426,
     426,   426,   428,   427,   429,   429,   429,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   432,   431,   434,
     433,   435,   435,   436,   436,   436,   438,   437,   440,   439,
     441,   441,   442,   442,   442,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   444,   445,   446,   448,   447,
     450,   449,   452,   451,   453,   455,   454,   456,   458,   457,
     459,   459,   460,   460,   460,   462,   461,   464,   463,   465,
     465,   466,   466,   466,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   468,   470,   469,   471,   472,   473,   474,
     476,   475,   477,   477,   478,   478,   478,   480,   479,   482,
     481,   483,   483,   483,   484,   484,   484,   484,   484,   484,
     484,   486,   485,   488,   487,   490,   489,   492,   491,   493,
     493,   494,   494,   494,   496,   495,   498,   497,   499,   499,
     499,   500,   500,   500,   500,   500,   500,   500,   500,   500,
     500,   500,   502,   501,   503,   505,   504,   506,   507,   509,
     508,   510,   510,   511,   511,   511,   513,   512,   515,   514,
     516,   516,   517,   517,   517,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   520,   519,   522,   521,
     524,   523,   526,   525,   528,   527,   530,   529,   532,   531,
     534,   533,   535,   535,   537,   536,   539,   538,   540,   540,
     540,   542,   541,   543,   543,   544,   544,   544,   545,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   546,   548,   547,   549,   551,   550,   552,   552,   552,
     553,   553,   553,   553,   553,   553,   553,   553,   553,   555,
     554,   556,   556,   556,   557,   559,   558,   560,   561,   562,
     564,   563,   565,   565,   565,   566,   566,   566,   566,   566,
     568,   567,   570,   569,   572,   571,   573,   573,   573,   574,
     574,   574,   574,   574,   574,   575,   577,   576,   578,   580,
     579,   582,   581,   584,   583,   585,   585,   585,   586,   586,
     586,   586,   586,   586,   586,   586,   586,   586,   586,   586,
     586,   586,   586,   586,   586,   586,   587,   589,   588,   591,
     590,   592,   594,   593,   595,   596,   598,   597,   599,   599,
     601,   600,   602,   603,   605,   604,   607,   606,   609,   608,
     611,   610,   613,   612,   615,   614,   616,   616,   616,   617,
     617,   619,   618,   620,   622,   621,   623,   623,   623,   625,
     624,   626,   626,   626,   627,   627,   627,   627,   627,   627,
     627,   628,   630,   629,   632,   631,   633,   633,   633,   635,
     634,   636,   636,   636,   637,   637,   637,   637,   637,   639,
     638,   640,   641,   642,   644,   643,   646,   645,   647,   647,
     647,   648,   648,   649
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
       1,     1,     0,     4,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     1,     3,     2,
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
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"", "\"port\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
  "$@30", "re_detect", "lease_database", "$@31", "hosts_database", "$@32",
  "hosts_databases", "$@33", "database_list", "not_empty_database_list",
  "database", "$@34", "database_map_params", "database_map_param",
  "database_type", "$@35", "db_type", "user", "$@36", "password", "$@37",
  "host", "$@38", "port", "name", "$@39", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "on_fail", "$@40",
  "on_fail_mode", "max_row_errors", "max_reconnect_tries", "trust_anchor",
  "$@41", "cert_file", "$@42", "key_file", "$@43", "cipher_list", "$@44",
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
       0,   299,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     308,   308,   309,   309,   310,   310,   311,   311,   312,   312,
     320,   321,   322,   323,   324,   325,   326,   329,   334,   334,
     345,   348,   349,   352,   357,   363,   368,   368,   375,   376,
     379,   383,   387,   393,   393,   400,   401,   404,   408,   412,
     422,   431,   431,   446,   446,   460,   463,   469,   469,   478,
     479,   480,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   554,   554,   563,
     569,   575,   581,   587,   593,   599,   605,   611,   617,   623,
     629,   635,   641,   647,   653,   659,   665,   665,   674,   677,
     680,   683,   686,   692,   692,   701,   701,   710,   716,   722,
     722,   731,   731,   740,   746,   752,   758,   758,   767,   773,
     779,   785,   791,   791,   803,   803,   812,   813,   814,   819,
     820,   821,   822,   823,   826,   826,   837,   843,   843,   856,
     856,   869,   869,   880,   881,   884,   885,   886,   891,   891,
     901,   902,   903,   908,   909,   910,   911,   912,   913,   914,
     915,   916,   917,   918,   919,   920,   921,   922,   923,   924,
     925,   926,   929,   929,   937,   938,   939,   942,   942,   951,
     951,   960,   960,   969,   975,   975,   984,   990,   996,  1002,
    1008,  1014,  1014,  1022,  1023,  1024,  1027,  1033,  1039,  1039,
    1048,  1048,  1057,  1057,  1066,  1066,  1075,  1075,  1086,  1087,
    1088,  1093,  1095,  1095,  1114,  1114,  1125,  1126,  1127,  1132,
    1133,  1136,  1141,  1146,  1146,  1157,  1158,  1159,  1164,  1165,
    1166,  1169,  1174,  1181,  1181,  1194,  1194,  1207,  1208,  1209,
    1214,  1215,  1216,  1217,  1218,  1219,  1222,  1228,  1234,  1240,
    1240,  1251,  1252,  1255,  1256,  1257,  1262,  1262,  1272,  1272,
    1282,  1283,  1284,  1287,  1290,  1291,  1294,  1294,  1303,  1303,
    1312,  1312,  1324,  1325,  1326,  1331,  1332,  1333,  1334,  1335,
    1336,  1339,  1345,  1351,  1357,  1363,  1369,  1378,  1378,  1392,
    1393,  1396,  1397,  1398,  1407,  1407,  1433,  1433,  1444,  1445,
    1446,  1452,  1453,  1454,  1455,  1456,  1457,  1458,  1459,  1460,
    1461,  1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,
    1471,  1472,  1473,  1474,  1475,  1476,  1477,  1478,  1479,  1480,
    1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,  1490,
    1491,  1492,  1493,  1494,  1497,  1497,  1506,  1506,  1515,  1515,
    1524,  1524,  1533,  1533,  1544,  1550,  1556,  1562,  1562,  1570,
    1571,  1572,  1573,  1576,  1582,  1590,  1590,  1602,  1603,  1607,
    1608,  1609,  1614,  1614,  1622,  1623,  1624,  1629,  1630,  1631,
    1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,
    1652,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,
    1662,  1663,  1664,  1665,  1666,  1667,  1668,  1675,  1675,  1689,
    1689,  1698,  1699,  1702,  1703,  1704,  1711,  1711,  1726,  1726,
    1740,  1741,  1744,  1745,  1746,  1751,  1752,  1753,  1754,  1755,
    1756,  1757,  1758,  1759,  1760,  1763,  1765,  1771,  1773,  1773,
    1782,  1782,  1791,  1791,  1800,  1802,  1802,  1811,  1821,  1821,
    1834,  1835,  1840,  1841,  1842,  1849,  1849,  1861,  1861,  1873,
    1874,  1879,  1880,  1881,  1888,  1889,  1890,  1891,  1892,  1893,
    1894,  1895,  1896,  1899,  1901,  1901,  1910,  1912,  1914,  1920,
    1929,  1929,  1942,  1943,  1946,  1947,  1948,  1953,  1953,  1963,
    1963,  1973,  1974,  1975,  1980,  1981,  1982,  1983,  1984,  1985,
    1986,  1989,  1989,  1998,  1998,  2023,  2023,  2053,  2053,  2066,
    2067,  2070,  2071,  2072,  2077,  2077,  2089,  2089,  2101,  2102,
    2103,  2108,  2109,  2110,  2111,  2112,  2113,  2114,  2115,  2116,
    2117,  2118,  2121,  2121,  2130,  2136,  2136,  2145,  2151,  2160,
    2160,  2171,  2172,  2175,  2176,  2177,  2182,  2182,  2191,  2191,
    2200,  2201,  2204,  2205,  2206,  2212,  2213,  2214,  2215,  2216,
    2217,  2218,  2219,  2220,  2221,  2222,  2225,  2225,  2236,  2236,
    2247,  2247,  2256,  2256,  2265,  2265,  2274,  2274,  2283,  2283,
    2297,  2297,  2308,  2309,  2312,  2312,  2324,  2324,  2335,  2336,
    2337,  2342,  2342,  2352,  2353,  2356,  2357,  2358,  2363,  2364,
    2365,  2366,  2367,  2368,  2369,  2370,  2371,  2372,  2373,  2374,
    2375,  2378,  2380,  2380,  2389,  2398,  2398,  2411,  2412,  2413,
    2418,  2419,  2420,  2421,  2422,  2423,  2424,  2425,  2426,  2429,
    2429,  2437,  2438,  2439,  2442,  2448,  2448,  2457,  2463,  2471,
    2479,  2479,  2490,  2491,  2492,  2497,  2498,  2499,  2500,  2501,
    2504,  2504,  2513,  2513,  2525,  2525,  2538,  2539,  2540,  2545,
    2546,  2547,  2548,  2549,  2550,  2553,  2559,  2559,  2568,  2574,
    2574,  2584,  2584,  2597,  2597,  2607,  2608,  2609,  2614,  2615,
    2616,  2617,  2618,  2619,  2620,  2621,  2622,  2623,  2624,  2625,
    2626,  2627,  2628,  2629,  2630,  2631,  2634,  2641,  2641,  2650,
    2650,  2659,  2665,  2665,  2674,  2680,  2686,  2686,  2695,  2696,
    2699,  2699,  2709,  2716,  2723,  2723,  2732,  2732,  2742,  2742,
    2752,  2752,  2764,  2764,  2776,  2776,  2786,  2787,  2788,  2794,
    2795,  2798,  2798,  2809,  2817,  2817,  2830,  2831,  2832,  2838,
    2838,  2846,  2847,  2848,  2853,  2854,  2855,  2856,  2857,  2858,
    2859,  2862,  2868,  2868,  2877,  2877,  2888,  2889,  2890,  2895,
    2895,  2903,  2904,  2905,  2910,  2911,  2912,  2913,  2914,  2917,
    2917,  2926,  2932,  2938,  2944,  2944,  2953,  2953,  2964,  2965,
    2966,  2971,  2972,  2975
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
#line 6309 "dhcp6_parser.cc"

#line 2981 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
