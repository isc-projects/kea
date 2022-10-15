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
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 294 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 294 "dhcp6_parser.yy"
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
#line 303 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 304 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 305 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 306 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 307 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 308 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 309 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 310 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 311 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 312 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 313 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 314 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 315 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 316 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 324 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 325 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 326 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 327 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 328 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 329 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 330 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 333 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 338 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 343 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 349 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 356 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 361 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 367 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 935 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 372 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 944 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 375 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 952 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 383 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 961 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 387 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 391 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 978 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 397 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 986 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 399 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 995 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 408 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1004 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 412 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1013 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 416 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 426 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 435 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 440 "dhcp6_parser.yy"
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
#line 450 "dhcp6_parser.yy"
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
#line 459 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 467 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 473 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 477 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 484 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1116 "dhcp6_parser.cc"
    break;

  case 137: // $@21: %empty
#line 558 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 138: // data_directory: "data-directory" $@21 ":" "constant string"
#line 561 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 139: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 567 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 140: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 573 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 141: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 579 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 142: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 585 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 143: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 591 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 144: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 145: // renew_timer: "renew-timer" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 146: // rebind_timer: "rebind-timer" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 147: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 615 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 148: // t1_percent: "t1-percent" ":" "floating point"
#line 621 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 149: // t2_percent: "t2-percent" ":" "floating point"
#line 627 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 150: // cache_threshold: "cache-threshold" ":" "floating point"
#line 633 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 151: // cache_max_age: "cache-max-age" ":" "integer"
#line 639 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 152: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 645 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 153: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 651 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 154: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 657 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1295 "dhcp6_parser.cc"
    break;

  case 155: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 663 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1305 "dhcp6_parser.cc"
    break;

  case 156: // $@22: %empty
#line 669 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1314 "dhcp6_parser.cc"
    break;

  case 157: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 672 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "when-present"
#line 678 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1331 "dhcp6_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "never"
#line 681 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1339 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "always"
#line 684 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-not-present"
#line 687 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "boolean"
#line 690 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 163: // $@23: %empty
#line 696 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 164: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 699 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1383 "dhcp6_parser.cc"
    break;

  case 165: // $@24: %empty
#line 705 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 166: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 708 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 167: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 714 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 168: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 720 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 169: // $@25: %empty
#line 726 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 170: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 729 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1441 "dhcp6_parser.cc"
    break;

  case 171: // $@26: %empty
#line 735 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 172: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 738 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 173: // store_extended_info: "store-extended-info" ":" "boolean"
#line 744 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 174: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 750 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 175: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 756 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 176: // $@27: %empty
#line 762 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 177: // server_tag: "server-tag" $@27 ":" "constant string"
#line 765 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 178: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 771 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 179: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 777 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 180: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 783 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 181: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 789 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 182: // $@28: %empty
#line 795 "dhcp6_parser.yy"
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
#line 801 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 184: // $@29: %empty
#line 807 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 185: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 811 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // interfaces_config_params: interfaces_config_params ","
#line 818 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1598 "dhcp6_parser.cc"
    break;

  case 197: // $@30: %empty
#line 833 "dhcp6_parser.yy"
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
#line 839 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 199: // re_detect: "re-detect" ":" "boolean"
#line 844 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 200: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 850 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 201: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 856 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 202: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 862 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 868 "dhcp6_parser.yy"
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
#line 874 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1682 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 881 "dhcp6_parser.yy"
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
#line 887 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1705 "dhcp6_parser.cc"
    break;

  case 207: // $@33: %empty
#line 894 "dhcp6_parser.yy"
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
#line 900 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 213: // not_empty_database_list: not_empty_database_list ","
#line 911 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1734 "dhcp6_parser.cc"
    break;

  case 214: // $@34: %empty
#line 916 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1744 "dhcp6_parser.cc"
    break;

  case 215: // database: "{" $@34 database_map_params "}"
#line 920 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1754 "dhcp6_parser.cc"
    break;

  case 218: // database_map_params: database_map_params ","
#line 928 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1762 "dhcp6_parser.cc"
    break;

  case 238: // $@35: %empty
#line 954 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1771 "dhcp6_parser.cc"
    break;

  case 239: // database_type: "type" $@35 ":" db_type
#line 957 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 240: // db_type: "memfile"
#line 962 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1786 "dhcp6_parser.cc"
    break;

  case 241: // db_type: "mysql"
#line 963 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1792 "dhcp6_parser.cc"
    break;

  case 242: // db_type: "postgresql"
#line 964 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1798 "dhcp6_parser.cc"
    break;

  case 243: // $@36: %empty
#line 967 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc"
    break;

  case 244: // user: "user" $@36 ":" "constant string"
#line 970 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 245: // $@37: %empty
#line 976 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1826 "dhcp6_parser.cc"
    break;

  case 246: // password: "password" $@37 ":" "constant string"
#line 979 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1836 "dhcp6_parser.cc"
    break;

  case 247: // $@38: %empty
#line 985 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 248: // host: "host" $@38 ":" "constant string"
#line 988 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 249: // port: "port" ":" "integer"
#line 994 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 250: // $@39: %empty
#line 1000 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 251: // name: "name" $@39 ":" "constant string"
#line 1003 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1884 "dhcp6_parser.cc"
    break;

  case 252: // persist: "persist" ":" "boolean"
#line 1009 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1894 "dhcp6_parser.cc"
    break;

  case 253: // lfc_interval: "lfc-interval" ":" "integer"
#line 1015 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 254: // readonly: "readonly" ":" "boolean"
#line 1021 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 255: // connect_timeout: "connect-timeout" ":" "integer"
#line 1027 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 256: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1033 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 257: // $@40: %empty
#line 1039 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 258: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 1042 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 259: // on_fail_mode: "stop-retry-exit"
#line 1047 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1958 "dhcp6_parser.cc"
    break;

  case 260: // on_fail_mode: "serve-retry-exit"
#line 1048 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1964 "dhcp6_parser.cc"
    break;

  case 261: // on_fail_mode: "serve-retry-continue"
#line 1049 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1970 "dhcp6_parser.cc"
    break;

  case 262: // max_row_errors: "max-row-errors" ":" "integer"
#line 1052 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 263: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1058 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1990 "dhcp6_parser.cc"
    break;

  case 264: // $@41: %empty
#line 1064 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 265: // trust_anchor: "trust-anchor" $@41 ":" "constant string"
#line 1067 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1073 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 267: // cert_file: "cert-file" $@42 ":" "constant string"
#line 1076 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2028 "dhcp6_parser.cc"
    break;

  case 268: // $@43: %empty
#line 1082 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 269: // key_file: "key-file" $@43 ":" "constant string"
#line 1085 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 270: // $@44: %empty
#line 1091 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 271: // cipher_list: "cipher-list" $@44 ":" "constant string"
#line 1094 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 272: // $@45: %empty
#line 1100 "dhcp6_parser.yy"
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
#line 1106 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 276: // sanity_checks_params: sanity_checks_params ","
#line 1113 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2095 "dhcp6_parser.cc"
    break;

  case 279: // $@46: %empty
#line 1122 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2104 "dhcp6_parser.cc"
    break;

  case 280: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1125 "dhcp6_parser.yy"
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
#line 1141 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2133 "dhcp6_parser.cc"
    break;

  case 282: // extended_info_checks: "extended-info-checks" $@47 ":" "constant string"
#line 1144 "dhcp6_parser.yy"
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
#line 1159 "dhcp6_parser.yy"
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
#line 1165 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 287: // mac_sources_list: mac_sources_list ","
#line 1172 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2181 "dhcp6_parser.cc"
    break;

  case 290: // duid_id: "duid"
#line 1181 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 291: // string_id: "constant string"
#line 1186 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2199 "dhcp6_parser.cc"
    break;

  case 292: // $@49: %empty
#line 1191 "dhcp6_parser.yy"
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
#line 1197 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 296: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1204 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2228 "dhcp6_parser.cc"
    break;

  case 300: // hw_address_id: "hw-address"
#line 1214 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2237 "dhcp6_parser.cc"
    break;

  case 301: // flex_id: "flex-id"
#line 1219 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2246 "dhcp6_parser.cc"
    break;

  case 302: // $@50: %empty
#line 1226 "dhcp6_parser.yy"
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
#line 1232 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 304: // $@51: %empty
#line 1239 "dhcp6_parser.yy"
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
#line 1245 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc"
    break;

  case 308: // multi_threading_params: multi_threading_params ","
#line 1254 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2298 "dhcp6_parser.cc"
    break;

  case 315: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1267 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2308 "dhcp6_parser.cc"
    break;

  case 316: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1273 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 317: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1279 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2328 "dhcp6_parser.cc"
    break;

  case 318: // $@52: %empty
#line 1285 "dhcp6_parser.yy"
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
#line 1291 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2349 "dhcp6_parser.cc"
    break;

  case 324: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1302 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2357 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1307 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 326: // hooks_library: "{" $@53 hooks_params "}"
#line 1311 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2377 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1317 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 328: // sub_hooks_library: "{" $@54 hooks_params "}"
#line 1321 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2397 "dhcp6_parser.cc"
    break;

  case 331: // hooks_params: hooks_params ","
#line 1329 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2405 "dhcp6_parser.cc"
    break;

  case 335: // $@55: %empty
#line 1339 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp6_parser.cc"
    break;

  case 336: // library: "library" $@55 ":" "constant string"
#line 1342 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 337: // $@56: %empty
#line 1348 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2433 "dhcp6_parser.cc"
    break;

  case 338: // parameters: "parameters" $@56 ":" map_value
#line 1351 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2442 "dhcp6_parser.cc"
    break;

  case 339: // $@57: %empty
#line 1357 "dhcp6_parser.yy"
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
#line 1363 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2464 "dhcp6_parser.cc"
    break;

  case 343: // expired_leases_params: expired_leases_params ","
#line 1371 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2472 "dhcp6_parser.cc"
    break;

  case 350: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1384 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2482 "dhcp6_parser.cc"
    break;

  case 351: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1390 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2492 "dhcp6_parser.cc"
    break;

  case 352: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1396 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2502 "dhcp6_parser.cc"
    break;

  case 353: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1402 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2512 "dhcp6_parser.cc"
    break;

  case 354: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1408 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2522 "dhcp6_parser.cc"
    break;

  case 355: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1414 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 356: // $@58: %empty
#line 1423 "dhcp6_parser.yy"
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
#line 1429 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2553 "dhcp6_parser.cc"
    break;

  case 362: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1443 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2561 "dhcp6_parser.cc"
    break;

  case 363: // $@59: %empty
#line 1452 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2571 "dhcp6_parser.cc"
    break;

  case 364: // subnet6: "{" $@59 subnet6_params "}"
#line 1456 "dhcp6_parser.yy"
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
#line 1478 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2607 "dhcp6_parser.cc"
    break;

  case 366: // sub_subnet6: "{" $@60 subnet6_params "}"
#line 1482 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2617 "dhcp6_parser.cc"
    break;

  case 369: // subnet6_params: subnet6_params ","
#line 1491 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2625 "dhcp6_parser.cc"
    break;

  case 413: // $@61: %empty
#line 1542 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp6_parser.cc"
    break;

  case 414: // subnet: "subnet" $@61 ":" "constant string"
#line 1545 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2644 "dhcp6_parser.cc"
    break;

  case 415: // $@62: %empty
#line 1551 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 416: // interface: "interface" $@62 ":" "constant string"
#line 1554 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 417: // $@63: %empty
#line 1560 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp6_parser.cc"
    break;

  case 418: // interface_id: "interface-id" $@63 ":" "constant string"
#line 1563 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2682 "dhcp6_parser.cc"
    break;

  case 419: // $@64: %empty
#line 1569 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 420: // client_class: "client-class" $@64 ":" "constant string"
#line 1572 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 421: // $@65: %empty
#line 1578 "dhcp6_parser.yy"
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
#line 1584 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 423: // reservations_global: "reservations-global" ":" "boolean"
#line 1589 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 424: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1595 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 425: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1601 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2752 "dhcp6_parser.cc"
    break;

  case 426: // $@66: %empty
#line 1607 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2761 "dhcp6_parser.cc"
    break;

  case 427: // reservation_mode: "reservation-mode" $@66 ":" hr_mode
#line 1610 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2770 "dhcp6_parser.cc"
    break;

  case 428: // hr_mode: "disabled"
#line 1615 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2776 "dhcp6_parser.cc"
    break;

  case 429: // hr_mode: "out-of-pool"
#line 1616 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2782 "dhcp6_parser.cc"
    break;

  case 430: // hr_mode: "global"
#line 1617 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2788 "dhcp6_parser.cc"
    break;

  case 431: // hr_mode: "all"
#line 1618 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2794 "dhcp6_parser.cc"
    break;

  case 432: // id: "id" ":" "integer"
#line 1621 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 433: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1627 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 434: // $@67: %empty
#line 1635 "dhcp6_parser.yy"
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
#line 1641 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc"
    break;

  case 440: // shared_networks_list: shared_networks_list ","
#line 1654 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2843 "dhcp6_parser.cc"
    break;

  case 441: // $@68: %empty
#line 1659 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2853 "dhcp6_parser.cc"
    break;

  case 442: // shared_network: "{" $@68 shared_network_params "}"
#line 1663 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2861 "dhcp6_parser.cc"
    break;

  case 445: // shared_network_params: shared_network_params ","
#line 1669 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2869 "dhcp6_parser.cc"
    break;

  case 486: // $@69: %empty
#line 1720 "dhcp6_parser.yy"
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
#line 1726 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 488: // $@70: %empty
#line 1734 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2899 "dhcp6_parser.cc"
    break;

  case 489: // sub_option_def_list: "{" $@70 option_def_list "}"
#line 1737 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2907 "dhcp6_parser.cc"
    break;

  case 494: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1749 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2915 "dhcp6_parser.cc"
    break;

  case 495: // $@71: %empty
#line 1756 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 496: // option_def_entry: "{" $@71 option_def_params "}"
#line 1760 "dhcp6_parser.yy"
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
#line 1771 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2947 "dhcp6_parser.cc"
    break;

  case 498: // sub_option_def: "{" $@72 option_def_params "}"
#line 1775 "dhcp6_parser.yy"
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
#line 1791 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2967 "dhcp6_parser.cc"
    break;

  case 515: // code: "code" ":" "integer"
#line 1810 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2977 "dhcp6_parser.cc"
    break;

  case 517: // $@73: %empty
#line 1818 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 518: // option_def_type: "type" $@73 ":" "constant string"
#line 1821 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2996 "dhcp6_parser.cc"
    break;

  case 519: // $@74: %empty
#line 1827 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 520: // option_def_record_types: "record-types" $@74 ":" "constant string"
#line 1830 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 521: // $@75: %empty
#line 1836 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 522: // space: "space" $@75 ":" "constant string"
#line 1839 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 524: // $@76: %empty
#line 1847 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3043 "dhcp6_parser.cc"
    break;

  case 525: // option_def_encapsulate: "encapsulate" $@76 ":" "constant string"
#line 1850 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 526: // option_def_array: "array" ":" "boolean"
#line 1856 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 527: // $@77: %empty
#line 1866 "dhcp6_parser.yy"
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
#line 1872 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 533: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1887 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3092 "dhcp6_parser.cc"
    break;

  case 534: // $@78: %empty
#line 1894 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3102 "dhcp6_parser.cc"
    break;

  case 535: // option_data_entry: "{" $@78 option_data_params "}"
#line 1898 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 536: // $@79: %empty
#line 1906 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 537: // sub_option_data: "{" $@79 option_data_params "}"
#line 1910 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 542: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1926 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3138 "dhcp6_parser.cc"
    break;

  case 553: // $@80: %empty
#line 1946 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3147 "dhcp6_parser.cc"
    break;

  case 554: // option_data_data: "data" $@80 ":" "constant string"
#line 1949 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 557: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1959 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 558: // option_data_always_send: "always-send" ":" "boolean"
#line 1965 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 559: // $@81: %empty
#line 1974 "dhcp6_parser.yy"
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
#line 1980 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 565: // not_empty_pools_list: not_empty_pools_list ","
#line 1993 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3206 "dhcp6_parser.cc"
    break;

  case 566: // $@82: %empty
#line 1998 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 567: // pool_list_entry: "{" $@82 pool_params "}"
#line 2002 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 568: // $@83: %empty
#line 2008 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 569: // sub_pool6: "{" $@83 pool_params "}"
#line 2012 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 572: // pool_params: pool_params ","
#line 2020 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3254 "dhcp6_parser.cc"
    break;

  case 580: // $@84: %empty
#line 2034 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp6_parser.cc"
    break;

  case 581: // pool_entry: "pool" $@84 ":" "constant string"
#line 2037 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3273 "dhcp6_parser.cc"
    break;

  case 582: // $@85: %empty
#line 2043 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3281 "dhcp6_parser.cc"
    break;

  case 583: // user_context: "user-context" $@85 ":" map_value
#line 2045 "dhcp6_parser.yy"
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
#line 2068 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3316 "dhcp6_parser.cc"
    break;

  case 585: // comment: "comment" $@86 ":" "constant string"
#line 2070 "dhcp6_parser.yy"
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
#line 2098 "dhcp6_parser.yy"
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
#line 2104 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 592: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2117 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3374 "dhcp6_parser.cc"
    break;

  case 593: // $@88: %empty
#line 2122 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 594: // pd_pool_entry: "{" $@88 pd_pool_params "}"
#line 2126 "dhcp6_parser.yy"
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
#line 2134 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3406 "dhcp6_parser.cc"
    break;

  case 596: // sub_pd_pool: "{" $@89 pd_pool_params "}"
#line 2138 "dhcp6_parser.yy"
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
#line 2148 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3426 "dhcp6_parser.cc"
    break;

  case 611: // $@90: %empty
#line 2166 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 612: // pd_prefix: "prefix" $@90 ":" "constant string"
#line 2169 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 613: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2175 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3455 "dhcp6_parser.cc"
    break;

  case 614: // $@91: %empty
#line 2181 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3464 "dhcp6_parser.cc"
    break;

  case 615: // excluded_prefix: "excluded-prefix" $@91 ":" "constant string"
#line 2184 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3474 "dhcp6_parser.cc"
    break;

  case 616: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2190 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 617: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2196 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 618: // $@92: %empty
#line 2205 "dhcp6_parser.yy"
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
#line 2211 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3515 "dhcp6_parser.cc"
    break;

  case 624: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2222 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3523 "dhcp6_parser.cc"
    break;

  case 625: // $@93: %empty
#line 2227 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3533 "dhcp6_parser.cc"
    break;

  case 626: // reservation: "{" $@93 reservation_params "}"
#line 2231 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 627: // $@94: %empty
#line 2236 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 628: // sub_reservation: "{" $@94 reservation_params "}"
#line 2240 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3561 "dhcp6_parser.cc"
    break;

  case 633: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2251 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3569 "dhcp6_parser.cc"
    break;

  case 645: // $@95: %empty
#line 2270 "dhcp6_parser.yy"
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
#line 2276 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3590 "dhcp6_parser.cc"
    break;

  case 647: // $@96: %empty
#line 2281 "dhcp6_parser.yy"
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
#line 2287 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3611 "dhcp6_parser.cc"
    break;

  case 649: // $@97: %empty
#line 2292 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3620 "dhcp6_parser.cc"
    break;

  case 650: // duid: "duid" $@97 ":" "constant string"
#line 2295 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 651: // $@98: %empty
#line 2301 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 652: // hw_address: "hw-address" $@98 ":" "constant string"
#line 2304 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 653: // $@99: %empty
#line 2310 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 654: // hostname: "hostname" $@99 ":" "constant string"
#line 2313 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 655: // $@100: %empty
#line 2319 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 656: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2322 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 657: // $@101: %empty
#line 2328 "dhcp6_parser.yy"
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
#line 2334 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 659: // $@102: %empty
#line 2342 "dhcp6_parser.yy"
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
#line 2348 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3729 "dhcp6_parser.cc"
    break;

  case 663: // $@103: %empty
#line 2357 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 664: // ip_address: "ip-address" $@103 ":" "constant string"
#line 2360 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3748 "dhcp6_parser.cc"
    break;

  case 665: // $@104: %empty
#line 2369 "dhcp6_parser.yy"
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
#line 2375 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3769 "dhcp6_parser.cc"
    break;

  case 669: // client_classes_list: client_classes_list ","
#line 2382 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3777 "dhcp6_parser.cc"
    break;

  case 670: // $@105: %empty
#line 2387 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 671: // client_class_entry: "{" $@105 client_class_params "}"
#line 2391 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3797 "dhcp6_parser.cc"
    break;

  case 676: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2403 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3805 "dhcp6_parser.cc"
    break;

  case 691: // $@106: %empty
#line 2425 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 692: // client_class_test: "test" $@106 ":" "constant string"
#line 2428 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 693: // only_if_required: "only-if-required" ":" "boolean"
#line 2434 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 694: // $@107: %empty
#line 2443 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 695: // server_id: "server-id" $@107 ":" "{" server_id_params "}"
#line 2449 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3857 "dhcp6_parser.cc"
    break;

  case 698: // server_id_params: server_id_params ","
#line 2458 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3865 "dhcp6_parser.cc"
    break;

  case 708: // $@108: %empty
#line 2474 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3874 "dhcp6_parser.cc"
    break;

  case 709: // server_id_type: "type" $@108 ":" duid_type
#line 2477 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 710: // duid_type: "LLT"
#line 2482 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3889 "dhcp6_parser.cc"
    break;

  case 711: // duid_type: "EN"
#line 2483 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3895 "dhcp6_parser.cc"
    break;

  case 712: // duid_type: "LL"
#line 2484 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3901 "dhcp6_parser.cc"
    break;

  case 713: // htype: "htype" ":" "integer"
#line 2487 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 714: // $@109: %empty
#line 2493 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3920 "dhcp6_parser.cc"
    break;

  case 715: // identifier: "identifier" $@109 ":" "constant string"
#line 2496 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 716: // time: "time" ":" "integer"
#line 2502 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 717: // enterprise_id: "enterprise-id" ":" "integer"
#line 2508 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3950 "dhcp6_parser.cc"
    break;

  case 718: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2516 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3960 "dhcp6_parser.cc"
    break;

  case 719: // $@110: %empty
#line 2524 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 720: // control_socket: "control-socket" $@110 ":" "{" control_socket_params "}"
#line 2530 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 723: // control_socket_params: control_socket_params ","
#line 2537 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3989 "dhcp6_parser.cc"
    break;

  case 729: // $@111: %empty
#line 2549 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3998 "dhcp6_parser.cc"
    break;

  case 730: // socket_type: "socket-type" $@111 ":" "constant string"
#line 2552 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 731: // $@112: %empty
#line 2558 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4017 "dhcp6_parser.cc"
    break;

  case 732: // socket_name: "socket-name" $@112 ":" "constant string"
#line 2561 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 733: // $@113: %empty
#line 2570 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4039 "dhcp6_parser.cc"
    break;

  case 734: // dhcp_queue_control: "dhcp-queue-control" $@113 ":" "{" queue_control_params "}"
#line 2576 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 737: // queue_control_params: queue_control_params ","
#line 2585 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4058 "dhcp6_parser.cc"
    break;

  case 744: // enable_queue: "enable-queue" ":" "boolean"
#line 2598 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4068 "dhcp6_parser.cc"
    break;

  case 745: // $@114: %empty
#line 2604 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4077 "dhcp6_parser.cc"
    break;

  case 746: // queue_type: "queue-type" $@114 ":" "constant string"
#line 2607 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 747: // capacity: "capacity" ":" "integer"
#line 2613 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4097 "dhcp6_parser.cc"
    break;

  case 748: // $@115: %empty
#line 2619 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4106 "dhcp6_parser.cc"
    break;

  case 749: // arbitrary_map_entry: "constant string" $@115 ":" value
#line 2622 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4115 "dhcp6_parser.cc"
    break;

  case 750: // $@116: %empty
#line 2629 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 751: // dhcp_ddns: "dhcp-ddns" $@116 ":" "{" dhcp_ddns_params "}"
#line 2635 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4138 "dhcp6_parser.cc"
    break;

  case 752: // $@117: %empty
#line 2642 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4148 "dhcp6_parser.cc"
    break;

  case 753: // sub_dhcp_ddns: "{" $@117 dhcp_ddns_params "}"
#line 2646 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4158 "dhcp6_parser.cc"
    break;

  case 756: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2654 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4166 "dhcp6_parser.cc"
    break;

  case 775: // enable_updates: "enable-updates" ":" "boolean"
#line 2679 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 776: // $@118: %empty
#line 2686 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4185 "dhcp6_parser.cc"
    break;

  case 777: // dep_qualifying_suffix: "qualifying-suffix" $@118 ":" "constant string"
#line 2689 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 778: // $@119: %empty
#line 2695 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4204 "dhcp6_parser.cc"
    break;

  case 779: // server_ip: "server-ip" $@119 ":" "constant string"
#line 2698 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 780: // server_port: "server-port" ":" "integer"
#line 2704 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4224 "dhcp6_parser.cc"
    break;

  case 781: // $@120: %empty
#line 2710 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4233 "dhcp6_parser.cc"
    break;

  case 782: // sender_ip: "sender-ip" $@120 ":" "constant string"
#line 2713 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4243 "dhcp6_parser.cc"
    break;

  case 783: // sender_port: "sender-port" ":" "integer"
#line 2719 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4253 "dhcp6_parser.cc"
    break;

  case 784: // max_queue_size: "max-queue-size" ":" "integer"
#line 2725 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 785: // $@121: %empty
#line 2731 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 786: // ncr_protocol: "ncr-protocol" $@121 ":" ncr_protocol_value
#line 2734 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4281 "dhcp6_parser.cc"
    break;

  case 787: // ncr_protocol_value: "UDP"
#line 2740 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4287 "dhcp6_parser.cc"
    break;

  case 788: // ncr_protocol_value: "TCP"
#line 2741 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4293 "dhcp6_parser.cc"
    break;

  case 789: // $@122: %empty
#line 2744 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 790: // ncr_format: "ncr-format" $@122 ":" "JSON"
#line 2747 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4312 "dhcp6_parser.cc"
    break;

  case 791: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2754 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4322 "dhcp6_parser.cc"
    break;

  case 792: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2761 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4332 "dhcp6_parser.cc"
    break;

  case 793: // $@123: %empty
#line 2768 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4341 "dhcp6_parser.cc"
    break;

  case 794: // dep_replace_client_name: "replace-client-name" $@123 ":" ddns_replace_client_name_value
#line 2771 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4350 "dhcp6_parser.cc"
    break;

  case 795: // $@124: %empty
#line 2777 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 796: // dep_generated_prefix: "generated-prefix" $@124 ":" "constant string"
#line 2780 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 797: // $@125: %empty
#line 2787 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 798: // dep_hostname_char_set: "hostname-char-set" $@125 ":" "constant string"
#line 2790 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4388 "dhcp6_parser.cc"
    break;

  case 799: // $@126: %empty
#line 2797 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4397 "dhcp6_parser.cc"
    break;

  case 800: // dep_hostname_char_replacement: "hostname-char-replacement" $@126 ":" "constant string"
#line 2800 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 801: // $@127: %empty
#line 2809 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4419 "dhcp6_parser.cc"
    break;

  case 802: // config_control: "config-control" $@127 ":" "{" config_control_params "}"
#line 2815 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4429 "dhcp6_parser.cc"
    break;

  case 803: // $@128: %empty
#line 2821 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4439 "dhcp6_parser.cc"
    break;

  case 804: // sub_config_control: "{" $@128 config_control_params "}"
#line 2825 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4448 "dhcp6_parser.cc"
    break;

  case 807: // config_control_params: config_control_params ","
#line 2833 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4456 "dhcp6_parser.cc"
    break;

  case 810: // $@129: %empty
#line 2843 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4468 "dhcp6_parser.cc"
    break;

  case 811: // config_databases: "config-databases" $@129 ":" "[" database_list "]"
#line 2849 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4477 "dhcp6_parser.cc"
    break;

  case 812: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2854 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4487 "dhcp6_parser.cc"
    break;

  case 813: // $@130: %empty
#line 2862 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4499 "dhcp6_parser.cc"
    break;

  case 814: // loggers: "loggers" $@130 ":" "[" loggers_entries "]"
#line 2868 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4508 "dhcp6_parser.cc"
    break;

  case 817: // loggers_entries: loggers_entries ","
#line 2877 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4516 "dhcp6_parser.cc"
    break;

  case 818: // $@131: %empty
#line 2883 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4526 "dhcp6_parser.cc"
    break;

  case 819: // logger_entry: "{" $@131 logger_params "}"
#line 2887 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4534 "dhcp6_parser.cc"
    break;

  case 822: // logger_params: logger_params ","
#line 2893 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4542 "dhcp6_parser.cc"
    break;

  case 830: // debuglevel: "debuglevel" ":" "integer"
#line 2907 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4552 "dhcp6_parser.cc"
    break;

  case 831: // $@132: %empty
#line 2913 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4561 "dhcp6_parser.cc"
    break;

  case 832: // severity: "severity" $@132 ":" "constant string"
#line 2916 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4571 "dhcp6_parser.cc"
    break;

  case 833: // $@133: %empty
#line 2922 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4583 "dhcp6_parser.cc"
    break;

  case 834: // output_options_list: "output_options" $@133 ":" "[" output_options_list_content "]"
#line 2928 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4592 "dhcp6_parser.cc"
    break;

  case 837: // output_options_list_content: output_options_list_content ","
#line 2935 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4600 "dhcp6_parser.cc"
    break;

  case 838: // $@134: %empty
#line 2940 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4610 "dhcp6_parser.cc"
    break;

  case 839: // output_entry: "{" $@134 output_params_list "}"
#line 2944 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 842: // output_params_list: output_params_list ","
#line 2950 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4626 "dhcp6_parser.cc"
    break;

  case 848: // $@135: %empty
#line 2962 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4635 "dhcp6_parser.cc"
    break;

  case 849: // output: "output" $@135 ":" "constant string"
#line 2965 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4645 "dhcp6_parser.cc"
    break;

  case 850: // flush: "flush" ":" "boolean"
#line 2971 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4655 "dhcp6_parser.cc"
    break;

  case 851: // maxsize: "maxsize" ":" "integer"
#line 2977 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4665 "dhcp6_parser.cc"
    break;

  case 852: // maxver: "maxver" ":" "integer"
#line 2983 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4675 "dhcp6_parser.cc"
    break;

  case 853: // $@136: %empty
#line 2989 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4684 "dhcp6_parser.cc"
    break;

  case 854: // pattern: "pattern" $@136 ":" "constant string"
#line 2992 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4694 "dhcp6_parser.cc"
    break;

  case 855: // $@137: %empty
#line 2998 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4706 "dhcp6_parser.cc"
    break;

  case 856: // compatibility: "compatibility" $@137 ":" "{" compatibility_params "}"
#line 3004 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4715 "dhcp6_parser.cc"
    break;

  case 859: // compatibility_params: compatibility_params ","
#line 3011 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4723 "dhcp6_parser.cc"
    break;

  case 862: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3020 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4733 "dhcp6_parser.cc"
    break;


#line 4737 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -995;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     167,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,    46,    29,    53,    70,    73,
      83,    89,    91,    93,   103,   116,   127,   129,   137,   166,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,    29,  -163,
     102,   714,    45,   226,   212,    99,   128,   122,    23,   152,
     -91,   221,    43,  -995,   124,   172,   211,   199,   217,  -995,
      50,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   223,   231,
     245,   282,   298,   302,   308,   310,   314,   336,   338,   415,
     416,   423,  -995,   443,   444,   452,   458,   459,  -995,  -995,
    -995,   462,   463,   465,  -995,  -995,  -995,   466,  -995,  -995,
    -995,  -995,   467,   469,   472,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   473,  -995,  -995,  -995,  -995,  -995,
    -995,   474,   475,   476,  -995,  -995,   477,  -995,    71,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   478,   482,   483,   484,  -995,
     101,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   486,   488,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   105,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   123,
    -995,  -995,  -995,  -995,  -995,   489,  -995,   490,   493,  -995,
    -995,  -995,  -995,  -995,  -995,   135,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,   348,   438,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,   491,  -995,  -995,   498,  -995,  -995,  -995,
     500,  -995,  -995,   497,   448,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   508,   509,
    -995,  -995,  -995,  -995,   506,   512,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   143,  -995,
    -995,  -995,   513,  -995,  -995,   514,  -995,   515,   517,  -995,
    -995,   519,   520,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     145,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   522,   214,
    -995,  -995,  -995,  -995,    29,    29,  -995,   305,   523,  -995,
    -995,   524,   525,   526,   527,   530,   531,   325,   326,   328,
     332,   333,   334,   339,   342,   344,   337,   343,   346,   349,
     350,   544,   353,   356,   357,   358,   360,   556,   560,   566,
     361,   362,   364,   576,   578,   579,   374,   584,   586,   588,
     589,   380,   381,   382,   593,   594,   596,   599,   601,   602,
     603,   605,   607,   400,   609,   610,   612,   614,   615,   616,
     411,   412,   413,   617,   618,  -995,   714,  -995,   619,   414,
     417,   420,   421,    45,  -995,   620,   625,   626,   630,   631,
     424,   426,   633,   634,   635,   226,  -995,   637,   212,  -995,
     638,   432,   639,   433,   434,    99,  -995,   643,   644,   645,
     646,   647,   649,   650,  -995,   128,  -995,   652,   653,   446,
     655,   656,   657,   449,  -995,    23,   658,   450,   451,  -995,
     152,   663,   664,   126,  -995,   455,   666,   667,   460,   669,
     464,   468,   670,   671,   470,   471,   673,   674,   675,   677,
     221,  -995,   678,   479,    43,  -995,  -995,  -995,   679,   680,
     487,   686,   687,   688,   690,   681,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     494,  -995,  -995,  -995,  -995,  -995,   -86,   495,   496,  -995,
    -995,  -995,   699,   703,   704,  -995,   705,   706,   501,   275,
    -995,  -995,  -995,   709,   710,   711,   712,   713,   715,   716,
     717,   720,  -995,   721,   723,   724,   725,   511,   528,  -995,
    -995,  -995,   728,   727,  -995,   733,  -995,  -995,  -995,  -995,
    -995,   735,   736,   532,   533,   534,  -995,  -995,   733,   535,
     740,  -995,   537,  -995,   538,  -995,   539,  -995,  -995,  -995,
     733,   733,   733,   540,   541,   542,   543,  -995,   580,   581,
    -995,   582,   583,   585,  -995,  -995,   587,  -995,  -995,  -995,
     590,   706,  -995,  -995,   591,   592,  -995,   595,  -995,  -995,
      97,   621,  -995,  -995,   -86,   597,   600,   604,  -995,   737,
    -995,  -995,    29,   714,  -995,    43,    45,   134,   134,   748,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   783,
     788,   797,   798,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   -89,    29,   -39,   244,   800,   805,   806,    47,    92,
     109,   241,   193,   221,  -995,  -995,   807,  -159,  -995,  -995,
     810,   811,  -995,  -995,  -995,  -995,  -995,   -79,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,   748,  -995,   262,
     301,   341,  -995,  -995,  -995,  -995,   707,   815,   816,   824,
     825,   827,   828,  -995,   829,  -995,  -995,  -995,  -995,  -995,
     345,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     352,  -995,   830,   831,  -995,  -995,   832,   834,  -995,  -995,
     833,   837,  -995,  -995,   835,   839,  -995,  -995,   840,   842,
    -995,  -995,  -995,    39,  -995,  -995,  -995,   843,  -995,  -995,
    -995,   139,  -995,  -995,  -995,  -995,  -995,   354,  -995,  -995,
    -995,  -995,   203,  -995,  -995,   844,   845,  -995,  -995,   846,
     848,  -995,   849,   851,   852,   853,   854,   855,   397,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   856,   857,
     860,  -995,  -995,  -995,  -995,   398,  -995,  -995,  -995,  -995,
    -995,  -995,   861,   862,   864,  -995,   406,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   407,  -995,
    -995,  -995,   865,  -995,   867,  -995,  -995,  -995,   408,  -995,
    -995,  -995,  -995,  -995,   409,  -995,   215,  -995,   868,  -995,
     410,  -995,  -995,   632,  -995,   869,   870,  -995,  -995,   871,
     873,  -995,  -995,  -995,   872,  -995,   875,  -995,  -995,  -995,
     874,   878,   879,   880,   676,   665,   682,   672,   689,   691,
     692,   881,   693,   883,   885,   886,   887,   134,  -995,  -995,
     134,  -995,   748,   226,  -995,   783,    23,  -995,   788,   152,
    -995,   797,  1292,  -995,   798,   -89,  -995,  -995,   -39,  -995,
     888,   889,   244,  -995,   150,   800,  -995,   128,  -995,   805,
     -91,  -995,   806,   694,   695,   696,   698,   700,   701,    47,
    -995,   898,   907,   702,   708,   718,    92,  -995,   719,   722,
     726,   109,  -995,   911,   912,   241,  -995,   729,   913,   732,
     914,   193,  -995,  -995,   235,   807,  -995,   738,  -159,  -995,
    -995,   915,   916,   212,  -995,   810,    99,  -995,   811,   918,
    -995,  -995,   372,   730,   739,   743,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,   120,  -995,   747,   750,   757,   761,  -995,
     418,  -995,   425,  -995,   919,  -995,   920,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,   428,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,   762,   764,  -995,  -995,   922,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   921,
     928,  -995,  -995,  -995,  -995,  -995,   924,  -995,   431,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,   318,   765,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,   767,   770,  -995,
    -995,   772,  -995,    29,  -995,  -995,   931,  -995,  -995,  -995,
    -995,  -995,   435,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,   775,   437,  -995,   441,  -995,   776,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  1292,  -995,  -995,  -995,
     932,   777,  -995,   150,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   933,   785,   935,   235,  -995,
    -995,  -995,  -995,  -995,  -995,   791,  -995,  -995,   942,  -995,
     795,  -995,  -995,   917,  -995,  -995,   335,  -995,    20,   917,
    -995,  -995,   936,   945,  1005,  -995,   447,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  1013,   804,   812,   813,  1024,    20,
    -995,   821,  -995,  -995,  -995,   822,  -995,  -995,  -995
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
     536,    23,   327,    25,   752,    27,   803,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   629,     0,   499,   538,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   137,   801,   182,   203,   205,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   156,   163,
     165,     0,     0,     0,   356,   486,   527,     0,   434,   582,
     584,   426,     0,     0,     0,   283,   302,   292,   272,   665,
     618,   318,   339,   694,     0,   304,   719,   733,   750,   169,
     171,     0,     0,     0,   813,   855,     0,   136,     0,    69,
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
     333,   334,     0,   776,   778,     0,   781,     0,     0,   785,
     789,     0,     0,   793,   795,   797,   799,   774,   772,   773,
       0,   754,   757,   769,   758,   759,   760,   761,   762,   763,
     764,   765,   766,   767,   768,   770,   771,   810,     0,     0,
     805,   808,   809,    47,    52,     0,    39,    45,     0,    66,
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
     756,   753,     0,     0,   807,   804,    51,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,   174,   175,   153,   154,   155,     0,     0,     0,   167,
     168,   173,     0,     0,     0,   178,     0,     0,     0,     0,
     423,   424,   425,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   718,     0,     0,     0,     0,     0,     0,   179,
     180,   181,     0,     0,    70,     0,   199,   200,   201,   202,
     187,     0,     0,     0,     0,     0,   432,   433,     0,     0,
       0,   368,     0,   571,     0,   613,     0,   616,   617,   598,
       0,     0,     0,     0,     0,     0,     0,   632,     0,     0,
     515,     0,     0,     0,   526,   502,     0,   557,   558,   541,
       0,     0,   330,   775,     0,     0,   780,     0,   783,   784,
       0,     0,   791,   792,     0,     0,     0,     0,   755,     0,
     812,   806,     0,     0,   138,     0,     0,     0,     0,   209,
     177,   158,   159,   160,   161,   162,   157,   164,   166,   358,
     490,   529,   436,    40,   583,   585,   428,   429,   430,   431,
     427,     0,    48,     0,     0,     0,   620,   320,     0,     0,
       0,     0,     0,     0,   170,   172,     0,     0,    53,   198,
     561,   588,   414,   416,   418,   422,   420,     0,   581,   612,
     615,   658,   646,   648,   650,   652,   654,   656,   518,   251,
     522,   520,   525,   554,   336,   338,   777,   779,   782,   787,
     788,   786,   790,   794,   796,   798,   800,   209,    44,     0,
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
     344,   345,   346,   347,   348,   349,   708,   714,     0,     0,
       0,   707,   704,   705,   706,     0,   696,   699,   702,   700,
     701,   703,     0,     0,     0,   314,     0,   306,   309,   310,
     311,   312,   313,   729,   731,   728,   726,   727,     0,   721,
     724,   725,     0,   745,     0,   748,   741,   742,     0,   735,
     738,   739,   740,   743,     0,   818,     0,   815,     0,   861,
       0,   857,   860,    55,   566,     0,   562,   563,   593,     0,
     589,   590,   663,   662,     0,   661,     0,    64,   802,   183,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   218,   204,   206,
       0,   208,   213,     0,   357,   362,   499,   487,   494,   538,
     528,   533,     0,   435,   440,   287,   284,   303,   296,   293,
       0,     0,   276,   273,   672,   669,   666,   629,   619,   624,
       0,   319,   324,     0,     0,     0,     0,     0,     0,   343,
     340,     0,     0,     0,     0,     0,   698,   695,     0,     0,
       0,   308,   305,     0,     0,   723,   720,     0,     0,     0,
       0,   737,   734,   751,     0,   817,   814,     0,   859,   856,
      57,     0,    56,     0,   560,   565,     0,   587,   592,     0,
     660,   811,     0,     0,     0,     0,   249,   252,   253,   254,
     255,   263,   256,     0,   262,     0,     0,     0,     0,   217,
       0,   212,     0,   361,     0,   493,     0,   532,   485,   460,
     461,   462,   464,   465,   466,   450,   451,   469,   470,   471,
     472,   473,   476,   477,   478,   479,   480,   481,   482,   483,
     474,   475,   484,   446,   447,   448,   449,   458,   459,   455,
     456,   457,   454,   463,     0,   443,   452,   467,   468,   453,
     439,   286,   295,     0,     0,   275,   691,     0,   689,   683,
     684,   685,   686,   687,   688,   690,   680,   681,   682,     0,
     673,   674,   677,   678,   679,   668,     0,   623,     0,   323,
     350,   351,   352,   353,   354,   355,   342,     0,     0,   713,
     716,   717,   697,   315,   316,   317,   307,     0,     0,   722,
     744,     0,   747,     0,   736,   833,     0,   831,   829,   823,
     827,   828,     0,   820,   825,   826,   824,   816,   862,   858,
      54,    59,     0,   564,     0,   591,     0,   240,   241,   242,
     239,   244,   246,   248,   259,   260,   261,   258,   265,   267,
     269,   271,   215,   364,   496,   535,   445,   442,   280,   282,
       0,     0,   671,   676,   626,   326,   710,   711,   712,   709,
     715,   730,   732,   746,   749,     0,     0,     0,   822,   819,
      58,   567,   594,   664,   444,     0,   693,   675,     0,   830,
       0,   821,   692,     0,   832,   838,     0,   835,     0,   837,
     834,   848,     0,     0,     0,   853,     0,   840,   843,   844,
     845,   846,   847,   836,     0,     0,     0,     0,     0,   842,
     839,     0,   850,   851,   852,     0,   841,   849,   854
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,    -5,  -995,  -576,  -995,
     222,  -995,  -995,  -995,  -995,   287,  -995,  -614,  -995,  -995,
    -995,   -71,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   317,
     553,  -995,  -995,   -42,   -34,   -14,    14,    16,    22,   -67,
     -29,   -24,   -18,    24,    30,    38,  -995,    41,    42,    44,
      48,  -995,   327,    54,  -995,    56,  -995,    59,    60,    62,
    -995,    64,  -995,    66,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,   321,   536,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     258,  -995,    81,  -995,  -705,    67,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,   -52,  -995,  -737,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,    63,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,    72,  -729,  -995,
    -995,  -995,  -995,    57,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,    49,  -995,  -995,  -995,  -995,  -995,  -995,  -995,    58,
    -995,  -995,  -995,    65,   545,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,    68,  -995,  -995,  -995,  -995,  -995,  -995,  -994,
    -995,  -995,  -995,    88,  -995,  -995,  -995,    94,   598,  -995,
    -995,  -993,  -995,  -992,  -995,    80,  -995,    82,  -995,    74,
      76,    77,    79,  -995,  -995,  -995,  -990,  -995,  -995,  -995,
    -995,    85,  -995,  -995,  -150,  1034,  -995,  -995,  -995,  -995,
    -995,    95,  -995,  -995,  -995,    96,  -995,   559,  -995,   -62,
    -995,  -995,  -995,  -995,  -995,   -54,  -995,  -995,  -995,  -995,
    -995,     8,  -995,  -995,  -995,    98,  -995,  -995,  -995,   106,
    -995,   555,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,    31,  -995,  -995,  -995,    35,   606,  -995,
    -995,   -60,  -995,    -3,  -995,  -995,  -995,  -995,  -995,    32,
    -995,  -995,  -995,    36,   608,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,   -53,  -995,  -995,  -995,    87,  -995,  -995,  -995,
      84,  -995,   611,   347,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -989,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,   100,  -995,  -995,  -995,  -136,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,    75,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
      86,  -995,  -995,  -995,  -995,  -995,  -995,  -995,    61,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,   365,
     549,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
     405,   552,  -995,  -995,  -995,  -995,  -995,  -995,    69,  -995,
    -995,  -145,  -995,  -995,  -995,  -995,  -995,  -995,  -162,  -995,
    -995,  -181,  -995,  -995,  -995,  -995,  -995,  -995,  -995,  -995,
    -995,  -995,   104,  -995
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
     852,   853,   854,  1010,   830,   831,   832,   990,  1240,   833,
     991,   834,   992,   835,   993,   836,   837,   548,   838,   839,
     840,   841,   842,   843,  1001,  1247,   844,   845,   846,  1003,
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
     985,  1089,   215,   488,   892,   893,  1034,  1179,  1180,  1181,
    1182,  1183,  1260,  1184,   216,   492,   925,   926,   927,  1051,
    1269,   928,   929,  1052,   930,   931,   217,   218,   495,   948,
     949,   950,  1063,   951,  1064,   219,   496,   958,   959,   960,
     961,  1068,   962,   963,  1070,   220,   497,    65,    81,   410,
     411,   412,   413,   566,   414,   567,   415,   416,   569,   417,
     418,   419,   572,   801,   420,   573,   421,   422,   423,   576,
     424,   577,   425,   578,   426,   579,   221,   442,    67,    82,
     429,   430,   431,   582,   432,   222,   503,   966,   967,  1074,
    1222,  1223,  1224,  1225,  1277,  1226,  1275,  1296,  1297,  1298,
    1306,  1307,  1308,  1314,  1309,  1310,  1311,  1312,  1318,   223,
     504,   970,   971,   972
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     157,   229,   249,   295,   309,   329,   256,   351,   370,   387,
     407,    38,   237,   289,   302,   313,   331,   372,   365,   383,
     292,   408,   922,   850,   880,   373,   352,   371,  1144,  1145,
    1146,   250,  1153,  1159,    31,   871,    32,   968,    33,   251,
     385,   386,  1025,   323,   257,  1026,    30,   344,    86,   258,
     982,   743,   156,   439,   775,   259,   427,   428,   440,   252,
      42,   224,   225,   226,   227,   228,   781,   782,   783,   238,
     290,   303,   314,   332,   506,   366,   384,    44,   409,   507,
      46,   287,   298,   312,   330,   871,   878,   253,   879,   254,
      48,   731,   732,   733,   734,   255,    50,   260,    52,   345,
      54,   346,   347,   261,   513,   348,   349,   350,   525,   514,
      56,   262,    89,   526,   263,   264,   916,   265,   129,   130,
     156,   266,   872,    58,   817,   743,   528,   267,   735,   268,
     433,   529,   269,   270,    60,   271,    62,   272,   535,   273,
     129,   130,  1028,   536,    64,  1029,   563,   281,   580,   282,
     283,   564,   284,   581,   296,   310,   297,   311,   812,  1244,
    1245,  1246,   813,   814,   815,   816,   817,   818,   819,   820,
     821,   822,   823,    66,   126,   434,   824,   825,   826,   827,
     828,   902,   903,   904,   905,   906,   907,   129,   130,   304,
     305,   306,   307,   308,   129,   130,   125,    98,    99,   100,
     101,   102,   103,   126,   129,   130,  1035,   436,  1301,  1036,
     345,  1302,  1303,  1304,  1305,   435,   246,   584,  1075,   247,
     437,  1076,   585,   129,   130,   126,   345,   447,   345,   367,
     346,   347,   368,   369,   156,   448,   917,   918,   919,   920,
      34,    35,    36,    37,   322,   129,   130,   129,   130,   449,
     323,   324,   325,   326,   327,   328,   156,   385,   386,   932,
     933,   934,  1144,  1145,  1146,   506,  1153,  1159,  1166,  1167,
     987,   799,   800,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   450,   126,   129,   130,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   880,
     294,   126,   451,   156,   584,  1110,   452,   129,   130,   988,
     156,   345,   453,   239,   454,   240,   129,   130,   455,   922,
     156,   129,   130,   241,   242,   243,   244,   245,   131,   246,
     129,   130,   247,   132,   133,   134,   129,   130,  1299,   156,
     456,  1300,   457,   246,   513,   156,   247,   140,  1007,   989,
     952,   953,   954,  1008,   248,  1007,   544,  1032,   885,   886,
    1009,   156,  1033,   156,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   746,   747,
     748,   749,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   943,   944,  1237,  1238,  1239,
    1049,  1056,   405,   406,   955,  1050,  1057,   149,   150,  1061,
    1065,  1071,   580,  1078,  1062,  1066,  1072,  1073,  1079,   458,
     459,  1007,  1215,   156,  1216,  1217,  1252,   460,   525,   586,
     587,  1256,   156,  1253,   563,   157,  1257,   156,  1278,  1265,
     528,   545,   229,  1279,   535,  1281,   156,   462,   463,  1282,
    1319,   555,   156,   237,   249,  1320,   464,   295,   256,  1266,
    1267,  1268,   465,   466,   309,   289,   470,   471,   302,   472,
     476,   481,   292,   482,   329,   313,   483,   493,   500,   501,
     502,   505,   509,   250,   351,   331,   510,   511,   512,   370,
     520,   251,   521,   531,   533,   365,   257,   534,   372,   546,
     383,   258,   549,   352,   553,   554,   373,   259,   371,   407,
     238,   252,   557,   558,   559,   560,   588,   565,   568,   570,
     408,   571,   290,   574,   575,   303,   583,   589,   590,   591,
     592,   593,   314,   287,   594,   595,   298,   596,   597,   253,
     598,   254,   332,   312,   599,   600,   601,   255,   610,   260,
     605,   602,   366,   330,   603,   261,   606,   384,   604,   607,
     616,   608,   609,   262,   617,   611,   263,   264,   612,   265,
     618,   613,   614,   266,   615,   619,   620,   409,   621,   267,
     622,   268,   623,   624,   269,   270,   625,   271,   626,   272,
     627,   273,   628,   629,   630,   631,   632,   633,   634,   281,
     635,   282,   283,   636,   284,   637,   638,   639,   296,   640,
     297,   641,   642,   643,   644,   310,   645,   311,   646,   647,
     648,   652,   653,   655,   661,   649,   650,   651,   656,   662,
     663,   657,   658,   659,   664,   665,   666,   668,   669,   670,
     667,   672,   674,   676,   675,   677,   678,   680,   681,   682,
     683,   684,   157,   685,   686,   229,   688,   689,   690,   691,
     692,   693,   696,   694,   697,   698,   237,   700,   701,   703,
     704,   705,   706,   707,   710,   711,   708,   714,   715,   716,
     709,   717,   719,   722,   712,   713,   729,   723,   921,   935,
     945,   720,   407,   725,   726,   727,   969,   728,   724,   923,
     941,   946,   956,   408,   739,   730,   737,   738,   740,   741,
     742,   994,   745,    32,   751,   752,   753,   808,   755,   754,
     756,   757,   764,   238,   758,    92,    93,   759,   760,    94,
     761,   762,   763,   766,   767,    95,    96,    97,   768,   765,
     770,   771,   807,   772,   773,   774,   776,   777,   778,   779,
     780,   784,   785,   786,   787,   851,   924,   942,   947,   957,
     409,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     855,   788,   789,   790,   791,   859,   792,   802,   793,   127,
     128,   794,   796,   797,   863,   867,   798,   891,   804,   129,
     130,   805,   894,   898,   965,   806,   131,   974,   978,   995,
     996,   132,   133,   134,   135,   136,   137,   138,   997,   998,
     139,   999,  1000,  1002,  1012,   140,  1011,  1015,  1014,  1017,
    1018,  1020,  1021,  1080,   141,  1024,  1023,   142,  1039,  1027,
    1038,  1042,  1041,  1043,   143,  1044,  1045,  1046,  1047,  1048,
    1053,  1054,   144,   145,  1055,  1058,  1059,   146,  1060,  1067,
     147,  1069,  1077,  1085,   148,  1084,  1088,  1087,  1092,  1097,
    1090,  1091,  1093,  1094,  1095,  1103,  1099,  1105,  1096,  1106,
    1107,  1108,  1163,  1164,  1098,   149,   150,   151,   152,   153,
     154,  1100,  1197,  1101,  1102,  1104,  1190,  1191,  1192,   155,
    1193,  1198,  1194,  1195,  1199,  1207,  1208,  1211,  1213,  1231,
    1200,  1230,  1236,   795,  1295,   156,  1261,  1254,  1255,  1262,
    1201,  1263,  1264,  1203,  1204,  1276,  1285,  1288,  1205,  1290,
    1315,  1241,   249,  1210,  1212,   351,   256,  1293,   370,  1316,
    1242,  1118,  1228,   289,  1243,  1125,   365,   372,  1248,   383,
     292,  1249,  1157,  1168,   352,   373,   329,   371,  1250,   387,
    1143,   250,  1251,  1258,  1177,  1259,  1270,   331,  1271,   251,
    1119,  1272,  1175,  1273,   257,   921,  1280,  1283,  1120,   258,
     935,  1286,  1169,  1126,   945,   259,   923,  1289,  1127,   252,
    1170,   941,  1292,  1218,  1128,   946,  1294,   969,  1121,  1317,
     290,   956,   295,   366,  1220,   309,   384,  1321,  1322,  1158,
    1171,   287,  1219,   302,  1323,  1324,   313,   253,  1325,   254,
    1156,  1178,  1327,  1328,   332,   255,  1122,   260,  1123,   877,
     809,   803,  1176,   261,  1124,   330,  1129,   811,  1172,   660,
    1173,   262,  1130,   924,   263,   264,  1174,   265,   942,   654,
    1131,   266,   947,  1132,  1133,   986,  1134,   267,   957,   268,
    1135,  1221,   269,   270,  1109,   271,  1136,   272,  1137,   273,
     303,  1138,  1139,   314,  1140,  1162,  1141,   281,  1142,   282,
     283,   298,   284,  1111,   312,  1165,  1149,  1161,  1150,  1151,
    1189,  1152,  1147,  1113,  1148,  1188,  1284,  1112,   702,  1160,
    1206,   343,  1114,  1115,   695,   699,  1233,  1196,  1232,  1117,
    1235,  1186,  1234,   671,   983,  1116,  1187,  1287,   964,   718,
     810,  1202,  1214,  1291,   673,  1185,   721,  1313,  1326,     0,
       0,     0,     0,   679,  1227,     0,     0,     0,     0,     0,
       0,  1209,     0,     0,     0,     0,   687,     0,     0,     0,
       0,     0,     0,   296,     0,   297,   310,     0,   311,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1229,     0,     0,  1118,     0,     0,     0,  1125,
       0,     0,  1168,     0,     0,     0,  1157,     0,     0,     0,
       0,     0,     0,  1177,  1143,     0,     0,  1218,  1274,     0,
       0,  1175,     0,     0,  1119,     0,     0,     0,  1220,     0,
       0,  1169,  1120,     0,     0,     0,  1219,  1126,     0,  1170,
       0,     0,  1127,     0,     0,     0,     0,     0,  1128,     0,
       0,     0,  1121,     0,     0,     0,     0,     0,     0,  1171,
       0,     0,     0,  1158,     0,     0,     0,     0,     0,     0,
    1178,     0,     0,     0,  1156,     0,     0,     0,     0,     0,
    1122,  1176,  1123,     0,     0,  1221,     0,  1172,  1124,  1173,
    1129,     0,     0,     0,     0,  1174,  1130,     0,     0,     0,
       0,     0,     0,     0,  1131,     0,     0,  1132,  1133,     0,
    1134,     0,     0,     0,  1135,     0,     0,     0,     0,     0,
    1136,     0,  1137,     0,     0,  1138,  1139,     0,  1140,     0,
    1141,     0,  1142,     0,     0,     0,     0,     0,     0,     0,
    1149,     0,  1150,  1151,     0,  1152,  1147,     0,  1148,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,   126,   345,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,     0,
     242,   243,     0,   245,   131,     0,     0,     0,     0,   132,
     133,   134,     0,     0,     0,     0,     0,     0,     0,   246,
       0,     0,   247,     0,     0,     0,     0,     0,     0,     0,
     248,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   150,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   156
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    73,    78,    79,    80,
      81,    16,    72,    73,    74,    75,    76,    79,    78,    79,
      73,    81,   759,   728,   753,    79,    78,    79,  1022,  1022,
    1022,    73,  1022,  1022,     5,   124,     7,   196,     9,    73,
     131,   132,     3,   122,    73,     6,     0,    24,   211,    73,
     129,   627,   211,     3,   668,    73,    13,    14,     8,    73,
       7,    16,    17,    18,    19,    20,   680,   681,   682,    72,
      73,    74,    75,    76,     3,    78,    79,     7,    81,     8,
       7,    73,    74,    75,    76,   124,   125,    73,   127,    73,
       7,   177,   178,   179,   180,    73,     7,    73,     7,    76,
       7,    78,    79,    73,     3,    82,    83,    84,     3,     8,
       7,    73,    10,     8,    73,    73,    24,    73,    95,    96,
     211,    73,   211,     7,    32,   701,     3,    73,   214,    73,
       6,     8,    73,    73,     7,    73,     7,    73,     3,    73,
      95,    96,     3,     8,     7,     6,     3,    73,     3,    73,
      73,     8,    73,     8,    74,    75,    74,    75,    24,    39,
      40,    41,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,     7,    75,     3,    42,    43,    44,    45,
      46,   134,   135,   136,   137,   138,   139,    95,    96,    90,
      91,    92,    93,    94,    95,    96,    74,    47,    48,    49,
      50,    51,    52,    75,    95,    96,     3,     8,   188,     6,
      76,   191,   192,   193,   194,     4,   117,     3,     3,   120,
       3,     6,     8,    95,    96,    75,    76,     4,    76,    77,
      78,    79,    80,    81,   211,     4,   144,   145,   146,   147,
     211,   212,   213,   214,   116,    95,    96,    95,    96,     4,
     122,   123,   124,   125,   126,   127,   211,   131,   132,   150,
     151,   152,  1256,  1256,  1256,     3,  1256,  1256,   118,   119,
       8,   174,   175,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     4,    75,    95,    96,
      64,    65,    66,    67,    68,    69,    70,    71,    72,  1028,
      88,    75,     4,   211,     3,  1010,     4,    95,    96,     8,
     211,    76,     4,    87,     4,    89,    95,    96,     4,  1056,
     211,    95,    96,    97,    98,    99,   100,   101,   102,   117,
      95,    96,   120,   107,   108,   109,    95,    96,     3,   211,
       4,     6,     4,   117,     3,   211,   120,   121,     3,     8,
     157,   158,   159,     8,   128,     3,     8,     3,   114,   115,
       8,   211,     8,   211,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   103,   104,
     105,   106,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   154,   155,    25,    26,    27,
       3,     3,   181,   182,   211,     8,     8,   181,   182,     3,
       3,     3,     3,     3,     8,     8,     8,     8,     8,     4,
       4,     3,   187,   211,   189,   190,     8,     4,     3,   434,
     435,     3,   211,     8,     3,   506,     8,   211,     3,     8,
       3,     3,   513,     8,     3,     8,   211,     4,     4,     8,
       3,     3,   211,   513,   525,     8,     4,   528,   525,   141,
     142,   143,     4,     4,   535,   525,     4,     4,   528,     4,
       4,     4,   525,     4,   545,   535,     4,     4,     4,     4,
       4,     4,     4,   525,   555,   545,     4,     4,     4,   560,
       4,   525,     4,     4,     4,   555,   525,     4,   560,     8,
     560,   525,     4,   555,     4,     8,   560,   525,   560,   580,
     513,   525,     4,     4,     8,     3,   211,     4,     4,     4,
     580,     4,   525,     4,     4,   528,     4,     4,     4,     4,
       4,     4,   535,   525,     4,     4,   528,   212,   212,   525,
     212,   525,   545,   535,   212,   212,   212,   525,     4,   525,
     213,   212,   555,   545,   212,   525,   213,   560,   214,   213,
       4,   212,   212,   525,     4,   212,   525,   525,   212,   525,
       4,   214,   214,   525,   214,   214,   214,   580,   214,   525,
       4,   525,     4,     4,   525,   525,   212,   525,     4,   525,
       4,   525,     4,     4,   214,   214,   214,     4,     4,   525,
       4,   525,   525,     4,   525,     4,     4,     4,   528,     4,
     528,     4,   212,     4,     4,   535,     4,   535,     4,     4,
       4,     4,     4,     4,     4,   214,   214,   214,   214,     4,
       4,   214,   212,   212,     4,     4,   212,     4,     4,     4,
     214,     4,     4,     4,   212,   212,   212,     4,     4,     4,
       4,     4,   723,     4,     4,   726,     4,     4,   212,     4,
       4,     4,     4,   214,   214,   214,   726,     4,     4,   214,
       4,     4,   212,     4,     4,     4,   212,     4,     4,     4,
     212,     4,     4,     4,   214,   214,     5,     7,   759,   760,
     761,   212,   763,     7,     7,     7,   767,     7,   211,   759,
     760,   761,   762,   763,     5,   211,   211,   211,     5,     5,
       5,     4,   211,     7,     5,     5,     5,   722,     5,     7,
       5,     5,   211,   726,     7,    11,    12,     7,     7,    15,
       7,     7,     7,     5,     7,    21,    22,    23,     5,   211,
       5,     5,     5,   211,   211,   211,   211,     7,   211,   211,
     211,   211,   211,   211,   211,     7,   759,   760,   761,   762,
     763,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       7,   211,   211,   211,   211,     7,   211,   176,   211,    85,
      86,   211,   211,   211,     7,     7,   211,     7,   211,    95,
      96,   211,     7,     7,     7,   211,   102,     7,     7,     4,
       4,   107,   108,   109,   110,   111,   112,   113,     4,     4,
     116,     4,     4,     4,     3,   121,     6,     3,     6,     6,
       3,     6,     3,   211,   130,     3,     6,   133,     3,     6,
       6,     3,     6,     4,   140,     4,     4,     4,     4,     4,
       4,     4,   148,   149,     4,     4,     4,   153,     4,     4,
     156,     4,     4,     3,   160,     6,     3,     6,     4,   214,
       8,     6,     4,     4,     4,     4,   214,     4,   212,     4,
       4,     4,     4,     4,   212,   181,   182,   183,   184,   185,
     186,   212,     4,   212,   212,   212,   212,   212,   212,   195,
     212,     4,   212,   212,   212,     4,     4,     4,     4,     3,
     212,     6,     4,   701,     7,   211,     4,     8,     8,     8,
     212,     3,     8,   214,   212,     4,     4,     4,   212,     4,
       4,   211,  1013,   214,   212,  1016,  1013,     5,  1019,     4,
     211,  1022,   214,  1013,   211,  1022,  1016,  1019,   211,  1019,
    1013,   211,  1022,  1034,  1016,  1019,  1037,  1019,   211,  1040,
    1022,  1013,   211,   211,  1034,   211,   211,  1037,   211,  1013,
    1022,   211,  1034,   211,  1013,  1056,   211,   211,  1022,  1013,
    1061,   214,  1034,  1022,  1065,  1013,  1056,   212,  1022,  1013,
    1034,  1061,   211,  1074,  1022,  1065,   211,  1078,  1022,     4,
    1013,  1071,  1083,  1016,  1074,  1086,  1019,     4,   214,  1022,
    1034,  1013,  1074,  1083,   212,   212,  1086,  1013,     4,  1013,
    1022,  1034,   211,   211,  1037,  1013,  1022,  1013,  1022,   752,
     723,   714,  1034,  1013,  1022,  1037,  1022,   726,  1034,   513,
    1034,  1013,  1022,  1056,  1013,  1013,  1034,  1013,  1061,   506,
    1022,  1013,  1065,  1022,  1022,   807,  1022,  1013,  1071,  1013,
    1022,  1074,  1013,  1013,  1007,  1013,  1022,  1013,  1022,  1013,
    1083,  1022,  1022,  1086,  1022,  1028,  1022,  1013,  1022,  1013,
    1013,  1083,  1013,  1012,  1086,  1032,  1022,  1025,  1022,  1022,
    1042,  1022,  1022,  1015,  1022,  1040,  1256,  1013,   563,  1024,
    1061,    77,  1016,  1018,   555,   560,  1085,  1049,  1083,  1021,
    1088,  1037,  1086,   525,   777,  1019,  1039,  1263,   763,   580,
     725,  1056,  1071,  1278,   528,  1035,   584,  1299,  1319,    -1,
      -1,    -1,    -1,   535,  1075,    -1,    -1,    -1,    -1,    -1,
      -1,  1065,    -1,    -1,    -1,    -1,   545,    -1,    -1,    -1,
      -1,    -1,    -1,  1083,    -1,  1083,  1086,    -1,  1086,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1078,    -1,    -1,  1256,    -1,    -1,    -1,  1256,
      -1,    -1,  1263,    -1,    -1,    -1,  1256,    -1,    -1,    -1,
      -1,    -1,    -1,  1263,  1256,    -1,    -1,  1278,  1213,    -1,
      -1,  1263,    -1,    -1,  1256,    -1,    -1,    -1,  1278,    -1,
      -1,  1263,  1256,    -1,    -1,    -1,  1278,  1256,    -1,  1263,
      -1,    -1,  1256,    -1,    -1,    -1,    -1,    -1,  1256,    -1,
      -1,    -1,  1256,    -1,    -1,    -1,    -1,    -1,    -1,  1263,
      -1,    -1,    -1,  1256,    -1,    -1,    -1,    -1,    -1,    -1,
    1263,    -1,    -1,    -1,  1256,    -1,    -1,    -1,    -1,    -1,
    1256,  1263,  1256,    -1,    -1,  1278,    -1,  1263,  1256,  1263,
    1256,    -1,    -1,    -1,    -1,  1263,  1256,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1256,    -1,    -1,  1256,  1256,    -1,
    1256,    -1,    -1,    -1,  1256,    -1,    -1,    -1,    -1,    -1,
    1256,    -1,  1256,    -1,    -1,  1256,  1256,    -1,  1256,    -1,
    1256,    -1,  1256,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1256,    -1,  1256,  1256,    -1,  1256,  1256,    -1,  1256,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    -1,
      98,    99,    -1,   101,   102,    -1,    -1,    -1,    -1,   107,
     108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   181,   182,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
       0,     5,     7,     9,   211,   212,   213,   214,   231,   232,
     233,   238,     7,   247,     7,   252,     7,   299,     7,   410,
       7,   490,     7,   506,     7,   523,     7,   442,     7,   448,
       7,   472,     7,   386,     7,   592,     7,   623,   239,   234,
     248,   253,   300,   411,   491,   507,   524,   443,   449,   473,
     387,   593,   624,   231,   240,   241,   211,   236,   237,    10,
     249,   251,    11,    12,    15,    21,    22,    23,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    85,    86,    95,
      96,   102,   107,   108,   109,   110,   111,   112,   113,   116,
     121,   130,   133,   140,   148,   149,   153,   156,   160,   181,
     182,   183,   184,   185,   186,   195,   211,   246,   254,   255,
     256,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   278,
     280,   282,   283,   284,   286,   288,   289,   290,   291,   293,
     294,   295,   296,   297,   309,   311,   313,   351,   359,   365,
     371,   373,   380,   394,   404,   424,   425,   426,   427,   432,
     440,   466,   496,   498,   517,   547,   559,   571,   572,   580,
     590,   621,   630,   654,    16,    17,    18,    19,    20,   246,
     301,   302,   303,   305,   306,   307,   308,   496,   498,    87,
      89,    97,    98,    99,   100,   101,   117,   120,   128,   246,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   272,   273,   274,   275,   278,   280,   282,
     283,   284,   286,   288,   412,   413,   414,   416,   418,   420,
     422,   424,   425,   426,   427,   430,   431,   466,   484,   496,
     498,   500,   517,   542,    88,   246,   420,   422,   466,   492,
     493,   494,   496,   498,    90,    91,    92,    93,    94,   246,
     420,   422,   466,   496,   498,   508,   509,   510,   512,   513,
     515,   516,   116,   122,   123,   124,   125,   126,   127,   246,
     466,   496,   498,   525,   526,   527,   528,   530,   532,   534,
     536,   538,   540,   440,    24,    76,    78,    79,    82,    83,
      84,   246,   331,   450,   451,   452,   453,   454,   455,   456,
     458,   460,   462,   463,   465,   496,   498,    77,    80,    81,
     246,   331,   454,   460,   474,   475,   476,   477,   478,   480,
     481,   482,   483,   496,   498,   131,   132,   246,   388,   389,
     390,   392,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   181,   182,   246,   496,   498,
     594,   595,   596,   597,   599,   601,   602,   604,   605,   606,
     609,   611,   612,   613,   615,   617,   619,    13,    14,   625,
     626,   627,   629,     6,     3,     4,     8,     3,   250,     3,
       8,   257,   622,   298,   310,   312,   314,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   292,     4,     4,     4,     4,     4,   276,   279,   281,
       4,     4,     4,   405,   441,   467,     4,   433,   497,   499,
     428,     4,     4,     4,   360,   372,   366,   352,   548,   518,
     381,   395,   560,     4,   374,   573,   581,   591,   285,   287,
       4,     4,     4,   631,   655,     4,     3,     8,   304,     4,
       4,     4,     4,     3,     8,   485,   501,   415,   417,   419,
       4,     4,   423,   421,   543,     3,     8,   495,     3,     8,
     511,     4,   514,     4,     4,     3,     8,   541,   529,   531,
     533,   535,   537,   539,     8,     3,     8,   457,   332,     4,
     461,   459,   464,     4,     8,     3,   479,     4,     4,     8,
       3,   391,   393,     3,     8,     4,   598,   600,     4,   603,
       4,     4,   607,   610,     4,     4,   614,   616,   618,   620,
       3,     8,   628,     4,     3,     8,   231,   231,   211,     4,
       4,     4,     4,     4,     4,     4,   212,   212,   212,   212,
     212,   212,   212,   212,   214,   213,   213,   213,   212,   212,
       4,   212,   212,   214,   214,   214,     4,     4,     4,   214,
     214,   214,     4,     4,     4,   212,     4,     4,     4,     4,
     214,   214,   214,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   212,     4,     4,     4,     4,     4,     4,   214,
     214,   214,     4,     4,   255,     4,   214,   214,   212,   212,
     302,     4,     4,     4,     4,     4,   212,   214,     4,     4,
       4,   413,     4,   493,     4,   212,     4,   212,   212,   509,
       4,     4,     4,     4,     4,     4,     4,   527,     4,     4,
     212,     4,     4,     4,   214,   452,     4,   214,   214,   476,
       4,     4,   389,   214,     4,     4,   212,     4,   212,   212,
       4,     4,   214,   214,     4,     4,     4,     4,   595,     4,
     212,   626,     4,     7,   211,     7,     7,     7,     7,     5,
     211,   177,   178,   179,   180,   214,   277,   211,   211,     5,
       5,     5,     5,   233,   235,   211,   103,   104,   105,   106,
     429,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   211,   211,     5,     7,     5,   242,
       5,     5,   211,   211,   211,   242,   211,     7,   211,   211,
     211,   242,   242,   242,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   235,   211,   211,   211,   174,
     175,   608,   176,   277,   211,   211,   211,     5,   231,   254,
     625,   301,    24,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    42,    43,    44,    45,    46,   246,
     319,   320,   321,   324,   326,   328,   330,   331,   333,   334,
     335,   336,   337,   338,   341,   342,   343,   345,   347,   349,
     319,     7,   315,   316,   317,     7,   406,   407,   408,     7,
     444,   445,   446,     7,   468,   469,   470,     7,   434,   435,
     436,   124,   211,   361,   362,   363,   364,   240,   125,   127,
     363,   367,   368,   369,   370,   114,   115,   353,   354,   355,
     357,     7,   549,   550,     7,   519,   520,   521,     7,   382,
     383,   384,   134,   135,   136,   137,   138,   139,   396,   397,
     398,   399,   400,   401,   402,   403,    24,   144,   145,   146,
     147,   246,   333,   496,   498,   561,   562,   563,   566,   567,
     569,   570,   150,   151,   152,   246,   375,   376,   377,   378,
     379,   496,   498,   154,   155,   246,   496,   498,   574,   575,
     576,   578,   157,   158,   159,   211,   496,   498,   582,   583,
     584,   585,   587,   588,   594,     7,   632,   633,   196,   246,
     656,   657,   658,   243,     7,   486,   487,   488,     7,   502,
     503,   504,   129,   528,   544,   545,   315,     8,     8,     8,
     322,   325,   327,   329,     4,     4,     4,     4,     4,     4,
       4,   339,     4,   344,   346,   348,   350,     3,     8,     8,
     318,     6,     3,   409,     6,     3,   447,     6,     3,   471,
       6,     3,   437,     6,     3,     3,     6,     6,     3,     6,
     356,   358,     3,     8,   551,     3,     6,   522,     6,     3,
     385,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   564,   568,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   577,   579,     3,     8,     4,   586,     4,
     589,     3,     8,     8,   634,     3,     6,     4,     3,     8,
     211,   244,   245,   489,     6,     3,   505,     6,     3,   546,
       8,     6,     4,     4,     4,     4,   212,   214,   212,   214,
     212,   212,   212,     4,   212,     4,     4,     4,     4,   320,
     319,   317,   412,   408,   450,   446,   474,   470,   246,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   272,   273,   274,   275,   278,   280,   282,   283,
     284,   286,   288,   331,   404,   416,   418,   420,   422,   424,
     425,   426,   427,   431,   438,   439,   466,   496,   498,   542,
     436,   362,   368,     4,     4,   354,   118,   119,   246,   258,
     259,   260,   261,   262,   263,   331,   466,   496,   498,   552,
     553,   554,   555,   556,   558,   550,   525,   521,   388,   384,
     212,   212,   212,   212,   212,   212,   397,     4,     4,   212,
     212,   212,   562,   214,   212,   212,   376,     4,     4,   575,
     214,     4,   212,     4,   583,   187,   189,   190,   246,   331,
     496,   498,   635,   636,   637,   638,   640,   633,   214,   657,
       6,     3,   492,   488,   508,   504,     4,    25,    26,    27,
     323,   211,   211,   211,    39,    40,    41,   340,   211,   211,
     211,   211,     8,     8,     8,     8,     3,     8,   211,   211,
     557,     4,     8,     3,     8,     8,   141,   142,   143,   565,
     211,   211,   211,   211,   231,   641,     4,   639,     3,     8,
     211,     8,     8,   211,   439,     4,   214,   554,     4,   212,
       4,   636,   211,     5,   211,     7,   642,   643,   644,     3,
       6,   188,   191,   192,   193,   194,   645,   646,   647,   649,
     650,   651,   652,   643,   648,     4,     4,     4,   653,     3,
       8,     4,   214,   212,   212,     4,   646,   211,   211
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   215,   217,   216,   218,   216,   219,   216,   220,   216,
     221,   216,   222,   216,   223,   216,   224,   216,   225,   216,
     226,   216,   227,   216,   228,   216,   229,   216,   230,   216,
     231,   231,   231,   231,   231,   231,   231,   232,   234,   233,
     235,   236,   236,   237,   237,   237,   239,   238,   240,   240,
     241,   241,   241,   243,   242,   244,   244,   245,   245,   245,
     246,   248,   247,   250,   249,   249,   251,   253,   252,   254,
     254,   254,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   257,   256,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   276,   275,   277,   277,
     277,   277,   277,   279,   278,   281,   280,   282,   283,   285,
     284,   287,   286,   288,   289,   290,   292,   291,   293,   294,
     295,   296,   298,   297,   300,   299,   301,   301,   301,   302,
     302,   302,   302,   302,   302,   302,   302,   304,   303,   305,
     306,   307,   308,   310,   309,   312,   311,   314,   313,   315,
     315,   316,   316,   316,   318,   317,   319,   319,   319,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   322,   321,
     323,   323,   323,   325,   324,   327,   326,   329,   328,   330,
     332,   331,   333,   334,   335,   336,   337,   339,   338,   340,
     340,   340,   341,   342,   344,   343,   346,   345,   348,   347,
     350,   349,   352,   351,   353,   353,   353,   354,   354,   356,
     355,   358,   357,   360,   359,   361,   361,   361,   362,   362,
     363,   364,   366,   365,   367,   367,   367,   368,   368,   368,
     369,   370,   372,   371,   374,   373,   375,   375,   375,   376,
     376,   376,   376,   376,   376,   377,   378,   379,   381,   380,
     382,   382,   383,   383,   383,   385,   384,   387,   386,   388,
     388,   388,   388,   389,   389,   391,   390,   393,   392,   395,
     394,   396,   396,   396,   397,   397,   397,   397,   397,   397,
     398,   399,   400,   401,   402,   403,   405,   404,   406,   406,
     407,   407,   407,   409,   408,   411,   410,   412,   412,   412,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   415,   414,   417,   416,   419,   418,   421,
     420,   423,   422,   424,   425,   426,   428,   427,   429,   429,
     429,   429,   430,   431,   433,   432,   434,   434,   435,   435,
     435,   437,   436,   438,   438,   438,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   441,   440,   443,   442,
     444,   444,   445,   445,   445,   447,   446,   449,   448,   450,
     450,   451,   451,   451,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   453,   454,   455,   457,   456,   459,
     458,   461,   460,   462,   464,   463,   465,   467,   466,   468,
     468,   469,   469,   469,   471,   470,   473,   472,   474,   474,
     475,   475,   475,   476,   476,   476,   476,   476,   476,   476,
     476,   476,   477,   479,   478,   480,   481,   482,   483,   485,
     484,   486,   486,   487,   487,   487,   489,   488,   491,   490,
     492,   492,   492,   493,   493,   493,   493,   493,   493,   493,
     495,   494,   497,   496,   499,   498,   501,   500,   502,   502,
     503,   503,   503,   505,   504,   507,   506,   508,   508,   508,
     509,   509,   509,   509,   509,   509,   509,   509,   509,   509,
     509,   511,   510,   512,   514,   513,   515,   516,   518,   517,
     519,   519,   520,   520,   520,   522,   521,   524,   523,   525,
     525,   526,   526,   526,   527,   527,   527,   527,   527,   527,
     527,   527,   527,   527,   527,   529,   528,   531,   530,   533,
     532,   535,   534,   537,   536,   539,   538,   541,   540,   543,
     542,   544,   544,   546,   545,   548,   547,   549,   549,   549,
     551,   550,   552,   552,   553,   553,   553,   554,   554,   554,
     554,   554,   554,   554,   554,   554,   554,   554,   554,   554,
     555,   557,   556,   558,   560,   559,   561,   561,   561,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   564,   563,
     565,   565,   565,   566,   568,   567,   569,   570,   571,   573,
     572,   574,   574,   574,   575,   575,   575,   575,   575,   577,
     576,   579,   578,   581,   580,   582,   582,   582,   583,   583,
     583,   583,   583,   583,   584,   586,   585,   587,   589,   588,
     591,   590,   593,   592,   594,   594,   594,   595,   595,   595,
     595,   595,   595,   595,   595,   595,   595,   595,   595,   595,
     595,   595,   595,   595,   595,   596,   598,   597,   600,   599,
     601,   603,   602,   604,   605,   607,   606,   608,   608,   610,
     609,   611,   612,   614,   613,   616,   615,   618,   617,   620,
     619,   622,   621,   624,   623,   625,   625,   625,   626,   626,
     628,   627,   629,   631,   630,   632,   632,   632,   634,   633,
     635,   635,   635,   636,   636,   636,   636,   636,   636,   636,
     637,   639,   638,   641,   640,   642,   642,   642,   644,   643,
     645,   645,   645,   646,   646,   646,   646,   646,   648,   647,
     649,   650,   651,   653,   652,   655,   654,   656,   656,   656,
     657,   657,   658
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
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"multi-threading\"",
  "\"enable-multi-threading\"", "\"thread-pool-size\"",
  "\"packet-queue-size\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
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
  "client_class_name", "client_class_test", "$@106", "only_if_required",
  "server_id", "$@107", "server_id_params", "server_id_param",
  "server_id_type", "$@108", "duid_type", "htype", "identifier", "$@109",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@110",
  "control_socket_params", "control_socket_param", "socket_type", "$@111",
  "socket_name", "$@112", "dhcp_queue_control", "$@113",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@114", "capacity", "arbitrary_map_entry", "$@115",
  "dhcp_ddns", "$@116", "sub_dhcp_ddns", "$@117", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@118",
  "server_ip", "$@119", "server_port", "sender_ip", "$@120", "sender_port",
  "max_queue_size", "ncr_protocol", "$@121", "ncr_protocol_value",
  "ncr_format", "$@122", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@123",
  "dep_generated_prefix", "$@124", "dep_hostname_char_set", "$@125",
  "dep_hostname_char_replacement", "$@126", "config_control", "$@127",
  "sub_config_control", "$@128", "config_control_params",
  "config_control_param", "config_databases", "$@129",
  "config_fetch_wait_time", "loggers", "$@130", "loggers_entries",
  "logger_entry", "$@131", "logger_params", "logger_param", "debuglevel",
  "severity", "$@132", "output_options_list", "$@133",
  "output_options_list_content", "output_entry", "$@134",
  "output_params_list", "output_params", "output", "$@135", "flush",
  "maxsize", "maxver", "pattern", "$@136", "compatibility", "$@137",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   303,   303,   303,   304,   304,   305,   305,   306,   306,
     307,   307,   308,   308,   309,   309,   310,   310,   311,   311,
     312,   312,   313,   313,   314,   314,   315,   315,   316,   316,
     324,   325,   326,   327,   328,   329,   330,   333,   338,   338,
     349,   352,   353,   356,   361,   367,   372,   372,   379,   380,
     383,   387,   391,   397,   397,   404,   405,   408,   412,   416,
     426,   435,   435,   450,   450,   464,   467,   473,   473,   482,
     483,   484,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   558,   558,   567,
     573,   579,   585,   591,   597,   603,   609,   615,   621,   627,
     633,   639,   645,   651,   657,   663,   669,   669,   678,   681,
     684,   687,   690,   696,   696,   705,   705,   714,   720,   726,
     726,   735,   735,   744,   750,   756,   762,   762,   771,   777,
     783,   789,   795,   795,   807,   807,   816,   817,   818,   823,
     824,   825,   826,   827,   828,   829,   830,   833,   833,   844,
     850,   856,   862,   868,   868,   881,   881,   894,   894,   905,
     906,   909,   910,   911,   916,   916,   926,   927,   928,   933,
     934,   935,   936,   937,   938,   939,   940,   941,   942,   943,
     944,   945,   946,   947,   948,   949,   950,   951,   954,   954,
     962,   963,   964,   967,   967,   976,   976,   985,   985,   994,
    1000,  1000,  1009,  1015,  1021,  1027,  1033,  1039,  1039,  1047,
    1048,  1049,  1052,  1058,  1064,  1064,  1073,  1073,  1082,  1082,
    1091,  1091,  1100,  1100,  1111,  1112,  1113,  1118,  1119,  1122,
    1122,  1141,  1141,  1159,  1159,  1170,  1171,  1172,  1177,  1178,
    1181,  1186,  1191,  1191,  1202,  1203,  1204,  1209,  1210,  1211,
    1214,  1219,  1226,  1226,  1239,  1239,  1252,  1253,  1254,  1259,
    1260,  1261,  1262,  1263,  1264,  1267,  1273,  1279,  1285,  1285,
    1296,  1297,  1300,  1301,  1302,  1307,  1307,  1317,  1317,  1327,
    1328,  1329,  1332,  1335,  1336,  1339,  1339,  1348,  1348,  1357,
    1357,  1369,  1370,  1371,  1376,  1377,  1378,  1379,  1380,  1381,
    1384,  1390,  1396,  1402,  1408,  1414,  1423,  1423,  1437,  1438,
    1441,  1442,  1443,  1452,  1452,  1478,  1478,  1489,  1490,  1491,
    1497,  1498,  1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,
    1507,  1508,  1509,  1510,  1511,  1512,  1513,  1514,  1515,  1516,
    1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,
    1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,
    1537,  1538,  1539,  1542,  1542,  1551,  1551,  1560,  1560,  1569,
    1569,  1578,  1578,  1589,  1595,  1601,  1607,  1607,  1615,  1616,
    1617,  1618,  1621,  1627,  1635,  1635,  1647,  1648,  1652,  1653,
    1654,  1659,  1659,  1667,  1668,  1669,  1674,  1675,  1676,  1677,
    1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,
    1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,
    1708,  1709,  1710,  1711,  1712,  1713,  1720,  1720,  1734,  1734,
    1743,  1744,  1747,  1748,  1749,  1756,  1756,  1771,  1771,  1785,
    1786,  1789,  1790,  1791,  1796,  1797,  1798,  1799,  1800,  1801,
    1802,  1803,  1804,  1805,  1808,  1810,  1816,  1818,  1818,  1827,
    1827,  1836,  1836,  1845,  1847,  1847,  1856,  1866,  1866,  1879,
    1880,  1885,  1886,  1887,  1894,  1894,  1906,  1906,  1918,  1919,
    1924,  1925,  1926,  1933,  1934,  1935,  1936,  1937,  1938,  1939,
    1940,  1941,  1944,  1946,  1946,  1955,  1957,  1959,  1965,  1974,
    1974,  1987,  1988,  1991,  1992,  1993,  1998,  1998,  2008,  2008,
    2018,  2019,  2020,  2025,  2026,  2027,  2028,  2029,  2030,  2031,
    2034,  2034,  2043,  2043,  2068,  2068,  2098,  2098,  2111,  2112,
    2115,  2116,  2117,  2122,  2122,  2134,  2134,  2146,  2147,  2148,
    2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,  2161,  2162,
    2163,  2166,  2166,  2175,  2181,  2181,  2190,  2196,  2205,  2205,
    2216,  2217,  2220,  2221,  2222,  2227,  2227,  2236,  2236,  2245,
    2246,  2249,  2250,  2251,  2257,  2258,  2259,  2260,  2261,  2262,
    2263,  2264,  2265,  2266,  2267,  2270,  2270,  2281,  2281,  2292,
    2292,  2301,  2301,  2310,  2310,  2319,  2319,  2328,  2328,  2342,
    2342,  2353,  2354,  2357,  2357,  2369,  2369,  2380,  2381,  2382,
    2387,  2387,  2397,  2398,  2401,  2402,  2403,  2408,  2409,  2410,
    2411,  2412,  2413,  2414,  2415,  2416,  2417,  2418,  2419,  2420,
    2423,  2425,  2425,  2434,  2443,  2443,  2456,  2457,  2458,  2463,
    2464,  2465,  2466,  2467,  2468,  2469,  2470,  2471,  2474,  2474,
    2482,  2483,  2484,  2487,  2493,  2493,  2502,  2508,  2516,  2524,
    2524,  2535,  2536,  2537,  2542,  2543,  2544,  2545,  2546,  2549,
    2549,  2558,  2558,  2570,  2570,  2583,  2584,  2585,  2590,  2591,
    2592,  2593,  2594,  2595,  2598,  2604,  2604,  2613,  2619,  2619,
    2629,  2629,  2642,  2642,  2652,  2653,  2654,  2659,  2660,  2661,
    2662,  2663,  2664,  2665,  2666,  2667,  2668,  2669,  2670,  2671,
    2672,  2673,  2674,  2675,  2676,  2679,  2686,  2686,  2695,  2695,
    2704,  2710,  2710,  2719,  2725,  2731,  2731,  2740,  2741,  2744,
    2744,  2754,  2761,  2768,  2768,  2777,  2777,  2787,  2787,  2797,
    2797,  2809,  2809,  2821,  2821,  2831,  2832,  2833,  2839,  2840,
    2843,  2843,  2854,  2862,  2862,  2875,  2876,  2877,  2883,  2883,
    2891,  2892,  2893,  2898,  2899,  2900,  2901,  2902,  2903,  2904,
    2907,  2913,  2913,  2922,  2922,  2933,  2934,  2935,  2940,  2940,
    2948,  2949,  2950,  2955,  2956,  2957,  2958,  2959,  2962,  2962,
    2971,  2977,  2983,  2989,  2989,  2998,  2998,  3009,  3010,  3011,
    3016,  3017,  3020
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
#line 6418 "dhcp6_parser.cc"

#line 3026 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
